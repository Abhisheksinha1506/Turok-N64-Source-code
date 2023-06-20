/*=====================================================================
  uji_audio.c
  ＮＵＳ本体検査器のサウンドメインルーチン
                                Creator:     和田 将樹
                                             wada@hamster.nintendo.co.jp
                                Last Update: 96/02/28
				
  このプログラムはＮＵＳ本体検査プログラムのサウンド発生ルーチンです。
  サウンドを鳴らしたい場合、あらかじめ../audio/audio.c内のinitAudio()
ルーチンが呼び出し済みでオーディオシンセサイザが設定されていることを確認
してから、chkAppendSoundPlayer()をコールしてください。
  その後、chkPlaySound( int sound_number )関数をコールすると、sound_number
の値に応じた音が出力されます。

  注意:このファイルをリンクするには、
    １） ../audio/audio.cの一部のローカル変数をグローバル変数に変更すること
    ２） specファイルに効果音データのセグメントを追加すること
                        以上、２点が必要になります。


 I'm sorry. I cannot write English well.
 Comments in this program is included 8-bit codes.
 If you could not look JIS code, These codes may change garbage.
 But as garbage is in Comments field, you don't have to care.


  This program is functions that play sounds.
  If you want to play sound, you must do below: 

   At first you must confirm the audio synthesizer have been already set up. 
   Audio synsthesizer is made up by initAudio() in ../audio/audio.c.

   Next, you must call chkAppendSoundPlayer().

   At last,when you  call chkPlaySound( int sound_number ), 
   A sound which is selected by sound_number is output.


  Note: To link this file, you should do two works.

    1) Change some of private variables to public variables in
        ../audio/audio.c.

    2) Append sound data segments in spec file.  
      

 ====================================================================*/
#include <ultra64.h>
#include <assert.h>
#include <PR/ramrom.h>
#include <gng.h>
#include <controller.h>
#include "uji_audio.h"

 /* グローバル用プロトタイプ宣言                         */
/* function prototype  for public function in this file */
void chkAppendSoundPlayer(void);
void chkPlaySoundPass( int sound_number );

 /* プロトタイプ宣言                                     */ 
/* function prototype for private function in this file */
static void romCopy(const char *src, const char *dest, const int len);

static s32       __DMAAlloc(s32 addr, s32 len, void *state);
static void      __clearAudioDMA(void);
static ALDMAproc __dmaNew(DMAState **state);


 /* 外部宣言変数                 */
/* extern variable in this file */
extern OSMesgQueue  rspMessageQ,dmaMessageQ;
extern DMAState     dmaState;
extern DMABuffer    dmaBuffs[NBUFFERS];
extern u32          audFrameCt;
extern u32          curBuf;
extern u32          nextDMA;

extern Acmd         *cmdList[2];
extern OSTask       *taskPtr[2];
extern s16          *audioBuffer[2];

extern OSMesgQueue  AIMessageQ;
extern OSMesg       AIMessageBuf[4];

extern OSIoMesg     audDMAIOMesgBuf[NUM_DMA_MESSAGES];
extern OSMesgQueue  audDMAMessageQ;
extern OSMesg       audDMAMessageBuf[NUM_DMA_MESSAGES];

extern ALHeap       aHeapRec;
extern u8           audioHeap[AUDIO_HEAP_SIZE];

 /* 効果音用変数   */
/** Sound Globals**/
static ALSndpConfig SPConfig;
static ALSndPlayer  Sndp, *sndp = &Sndp;
static ALSndId      *idPtr;


/* オーディオシンセサイザにサウンドプレイヤを追加する */
void chkAppendSoundPlayer(void)
{
    u32           bankLen;
    u32           i;

    /** Sound Variable **/
    ALSound       *snd;
    ALBankFile    *sfxBankPtr;
    ALBank        *sfxBank;
    ALInstrument  *inst;
    s32           numAllocated;


    /* Load the sfxbank file from rom */
    bankLen = _sfxbankSegmentRomEnd - _sfxbankSegmentRomStart;
    sfxBankPtr = alHeapAlloc(&aHeapRec, 1, bankLen);
    romCopy(_sfxbankSegmentRomStart, (char *)sfxBankPtr, bankLen);
    alBnkfNew(sfxBankPtr, (u8 *) _sfxtableSegmentRomStart);

    /* 効果音用サウンドプレイヤ */
    SPConfig.maxSounds = MAX_VOICES;
    SPConfig.maxEvents = EVT_COUNT;
    SPConfig.heap      = &aHeapRec;
    alSndpNew( sndp, &SPConfig );

    /*
     * Allocate all Sounds
     */
    sfxBank = ((ALBankFile *)sfxBankPtr)->bankArray[0];
    inst    = sfxBank->instArray[0];
    idPtr   = alHeapAlloc( &aHeapRec, 1, inst->soundCount*sizeof(ALSndId) );
    for( i=0, numAllocated=0 ; i < inst->soundCount ; i++ ) {
	snd = inst->soundArray[i];
	if( (idPtr[i] = alSndpAllocate( sndp, snd )) != -1 ) numAllocated++;
    }
}
/* 音を鳴らす */
void
chkPlaySound( int sound_number )
{
    s16      *audioOp;
    Acmd     *cmdLp;
    u32      i;
    s32      clcount;
    OSTask   *task;

    /* Make up active sound  */
    alSndpSetSound( sndp, idPtr[sound_number] );
    alSndpSetPitch( sndp,      0.5 );
    alSndpSetFXMix( sndp,        0 );
    alSndpSetPan  ( sndp,       64 );
    alSndpSetVol  ( sndp,    32767 );
    alSndpPlay    ( sndp           ); 
    osAiSetFrequency(44100);		/* all chk sounds are at 44Khz */
	   
    do {
	__clearAudioDMA();
	audioOp = (s16*) osVirtualToPhysical(audioBuffer[curBuf]);
	cmdLp = alAudioFrame(cmdList[curBuf], &clcount, audioOp,
			     NUM_SMPL_PER_FRAME);

	if(clcount)
	{
	    task = taskPtr[curBuf];     
            task->t.type = M_AUDTASK;
            task->t.flags = 0x0;
            task->t.ucode_boot = (u64 *) rspbootTextStart;
            task->t.ucode_boot_size = ((s32)rspbootTextEnd -
                                         (s32)rspbootTextStart);
            task->t.ucode = (u64 *) aspMainTextStart;
            task->t.ucode_data = (u64 *) aspMainDataStart;
            task->t.ucode_size = 4096;
            task->t.ucode_data_size = sizeof(u64)*
	                               (aspMainDataEnd - aspMainDataStart); 
            task->t.data_ptr = (u64 *) cmdList[curBuf];
            task->t.data_size = (cmdLp - cmdList[curBuf]) * sizeof(Acmd);
            
            /* Empty the dma queue to make sure all DMAs have completed.   */
            for (i=0; i<nextDMA; i++)
		osRecvMesg(&audDMAMessageQ, NULL, OS_MESG_NOBLOCK);


            osWritebackDCacheAll();
            osSpTaskStart(task);

	    osRecvMesg(&rspMessageQ, NULL, OS_MESG_BLOCK);

	    osAiSetNextBuffer(audioBuffer[curBuf], NUM_SMPL_PER_FRAME * 4);
	    osRecvMesg(&AIMessageQ, NULL, OS_MESG_BLOCK);
	}
	
	curBuf ^= 1;

    } while ( alSndpGetState(sndp) != AL_STOPPED );
}

static void romCopy(const char *src, const char *dest, const int len)
{
    OSIoMesg dmaIoMesgBuf;
    OSMesg dummyMesg;
    
    /*
     * Always invalidate cache before dma'ing data into the buffer.
     * This is to prevent a flush of the cache in the future from 
     * potentially trashing some data that has just been dma'ed in.
     * Since you don't care if old data makes it from cache out to 
     * memory, you can use the cheaper osInvalDCache() instead of one
     * of the writeback commands
     */
    osInvalDCache((void *)dest, (s32) len);
    osPiStartDma(&dmaIoMesgBuf, OS_MESG_PRI_NORMAL, OS_READ,
                 (u32)src, (void *)dest, (u32)len, &dmaMessageQ);
    (void) osRecvMesg(&dmaMessageQ, &dummyMesg, OS_MESG_BLOCK);
}

/******************************************************************************
 *
 * __amDMA This routine handles the dma'ing of samples from rom to ram.
 * First it checks the current buffers to see if the samples needed are
 * already in place. Because buffers are linked sequentially by the
 * addresses where the samples are on rom, it doesn't need to check all
 * of them, only up to the address that it needs. If it finds one, it
 * returns the address of that buffer. If it doesn't find the samples 
 * that it needs, it will initiate a DMA of the samples that it needs.
 * In either case, it updates the lastFrame variable, to indicate that
 * this buffer was last used in this frame. This is important for the
 * __clearAudioDMA routine.
 *
 *****************************************************************************/
static s32 __DMAAlloc(s32 addr, s32 len, void *state)
{
    void            *foundBuffer;
    s32             delta, addrEnd, buffEnd;
    DMABuffer     *dmaPtr, *lastDmaPtr;
    
    lastDmaPtr = 0;
    dmaPtr = dmaState.firstUsed;
    addrEnd = addr+len;

    /* first check to see if a currently existing buffer contains the
       sample that you need.  */
    
    while(dmaPtr)
    {
        buffEnd = dmaPtr->startAddr + DMA_BUFFER_LENGTH;
        if(dmaPtr->startAddr > addr) /* since buffers are ordered */
            break;                   /* abort if past possible */

        else if(addrEnd <= buffEnd) /* yes, found a buffer with samples */
        {
            dmaPtr->lastFrame = audFrameCt; /* mark it used */
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return (int) osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (DMABuffer*)dmaPtr->node.next;
    }

    /* get here, and you didn't find a buffer, so dma a new one */

    /* get a buffer from the free list */
    dmaPtr = dmaState.firstFree;

    assert(dmaPtr);  /* be sure you have a buffer, */
                    /* if you don't have one, this is a major problem */

    dmaState.firstFree = (DMABuffer*)dmaPtr->node.next;
    alUnlink((ALLink*)dmaPtr);

    /* add it to the used list */
    if(lastDmaPtr) /* if you have other dmabuffers used, add this one */
    {              /* to the list, after the last one checked above */
        alLink((ALLink*)dmaPtr,(ALLink*)lastDmaPtr);
    }
    else if(dmaState.firstUsed) /* if this buffer is before any others */
    {                           /* jam at begining of list */ 
        lastDmaPtr = dmaState.firstUsed;
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = (ALLink*)lastDmaPtr;
        dmaPtr->node.prev = 0;
        lastDmaPtr->node.prev = (ALLink*)dmaPtr;
    }
    else /* no buffers in list, this is the first one */
    {
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = 0;
        dmaPtr->node.prev = 0;
    }
    
    foundBuffer = dmaPtr->ptr;
    delta = addr & 0x1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = audFrameCt;  /* mark it */
    osPiStartDma(&audDMAIOMesgBuf[nextDMA++], OS_MESG_PRI_NORMAL, OS_READ,
                 (u32)addr, foundBuffer, DMA_BUFFER_LENGTH, &audDMAMessageQ);

    return (int) osVirtualToPhysical(foundBuffer) + delta;
}

/******************************************************************************
 *
 * __amDmaNew.  Initialize the dma buffers and return the address of the
 * procedure that will be used to dma the samples from rom to ram. This 
 * routine will be called once for each physical voice that is created. 
 * In this case, because we know where all the buffers are, and since 
 * they are not attached to a specific voice, we will only really do any
 * initialization the first time. After that we just return the address
 * to the dma routine.
 *
 *****************************************************************************/
static ALDMAproc __dmaNew(DMAState **state)
{
    int         i;
    
    if(!dmaState.initialized)  /* only do this once */
    {
        dmaState.firstUsed = 0;
        dmaState.firstFree = &dmaBuffs[0];
        dmaState.initialized = 1;
    }

    *state = &dmaState;  /* state is never used in this case */

    return __DMAAlloc;
}

/******************************************************************************
 *
 * __clearAudioDMA.  Routine to move dma buffers back to the unused list.
 * First clear out your dma messageQ. Then check each buffer to see when
 * it was last used. If that was more than FRAME_LAG frames ago, move it
 * back to the unused list. 
 *
 *****************************************************************************/
static void __clearAudioDMA(void)
{
    u32          i;
    DMABuffer  *dmaPtr,*nextPtr;
    
    /*
     * Don't block here. If dma's aren't complete, you've had an audio
     * overrun. (Bad news, but go for it anyway, and try and recover.
     */
/*    for (i=0; i<nextDMA; i++)
        osRecvMesg(&audDMAMessageQ,NULL,OS_MESG_NOBLOCK);*/

    nextDMA = 0;  /* reset */
    
    dmaPtr = dmaState.firstUsed;
    while(dmaPtr)
    {
        nextPtr = (DMABuffer*)dmaPtr->node.next;

        /* remove old dma's from list */
        /* Can change FRAME_LAG value.  Should be at least one.  */
        /* Larger values mean more buffers needed, but fewer DMA's */
        if(dmaPtr->lastFrame + FRAME_LAG  < audFrameCt) 
        {
            if(dmaState.firstUsed == dmaPtr)
                dmaState.firstUsed = (DMABuffer*)dmaPtr->node.next;
            alUnlink((ALLink*)dmaPtr);
            if(dmaState.firstFree)
                alLink((ALLink*)dmaPtr,(ALLink*)dmaState.firstFree);
            else
            {
                dmaState.firstFree = dmaPtr;
                dmaPtr->node.next = 0;
                dmaPtr->node.prev = 0;
            }
        }
        dmaPtr = nextPtr;
    }
    

    audFrameCt++;
}


