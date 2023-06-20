

#include <ultra64.h>
#include <assert.h>
#include <PR/ramrom.h>
#include <gng.h>
#include <controller.h>
#include "audio.h"
#include "../testDriver/zaru.h"

#define TEST_LEFT   0
#define TEST_RIGHT   1
#define TEST_MUSIC   2

extern int controllerSlot;

extern OSMesgQueue   rspMessageQ,dmaMessageQ;

static void AudioTest(int outRate);
void InitAudio(void);
static void romCopy(const char *src, const char *dest, const int len);
static void doSequence(int seqLen,int testNum);

static s32       __DMAAlloc(s32 addr, s32 len, void *state);
static void      __clearAudioDMA(void);
static ALDMAproc __dmaNew(DMAState **state);


DMAState    dmaState;
DMABuffer   dmaBuffs[NBUFFERS];
u32         audFrameCt;
ALSeqPlayer *seqp;
ALSeq       *seq;
u8          *seqData;
ALGlobals   audGlbs;
u32         curBuf;
u32         nextDMA;

Acmd        *cmdList[2];
OSTask      *taskPtr[2];
s16         *audioBuffer[2];

OSMesgQueue      AIMessageQ;
OSMesg           AIMessageBuf[4];

OSMesgQueue    timerMsgQ;
OSMesg         timerMsgBuf;

/** Queues and storage for use with audio DMA's ****/
OSIoMesg        audDMAIOMesgBuf[NUM_DMA_MESSAGES];
OSMesgQueue     audDMAMessageQ;
OSMesg          audDMAMessageBuf[NUM_DMA_MESSAGES];

ALHeap          aHeapRec;
u8              audioHeap[AUDIO_HEAP_SIZE];

char tstring[] = "test 00";

int audMain(void)
{
    static int   curTest = 0;
    int          thisFrame;

    ZaruSetSound(ZARU_SOUND_OFF);

    ZaruWaitForNextTestButton();


    AudioTest(TEST_LEFT);
    AudioTest(TEST_RIGHT);
    AudioTest(TEST_MUSIC);

    return(0);
}

static void MoveAudio(void)
{
    int    i, *ipt;
    u8     *hpStart;

    if(osMemSize > 0x400000)
    {
	hpStart = audioHeap + 0x400000;
	ipt = (int*)hpStart;
	for(i = 0; i < (AUDIO_HEAP_SIZE/4); i++)
	    ipt[i] = 0;

	alHeapInit(&aHeapRec, hpStart, AUDIO_HEAP_SIZE);    
	cmdList[0] = alHeapAlloc(&aHeapRec, 1, MAX_RSP_CMDS*sizeof(Acmd));
	cmdList[1] = alHeapAlloc(&aHeapRec, 1, MAX_RSP_CMDS*sizeof(Acmd));
	taskPtr[0] = alHeapAlloc(&aHeapRec, 1, sizeof(OSTask));
	taskPtr[1] = alHeapAlloc(&aHeapRec, 1, sizeof(OSTask));
	audioBuffer[0] = alHeapAlloc(&aHeapRec, 1, sizeof(s32)*NUM_SMPL_PER_FRAME);
	audioBuffer[1] = alHeapAlloc(&aHeapRec, 1, sizeof(s32)*NUM_SMPL_PER_FRAME);
    
	dmaBuffs[0].node.prev = 0; 
	dmaBuffs[0].node.next = 0;
	for (i=0; i<NUM_DMA_BUFFERS-1; i++)
	{
	    alLink((ALLink*)&dmaBuffs[i+1],(ALLink*)&dmaBuffs[i]);
	    dmaBuffs[i].ptr = alHeapAlloc(&aHeapRec, 1, DMA_BUFFER_LENGTH);
	}

	dmaBuffs[i].ptr = alHeapAlloc(&aHeapRec, 1, DMA_BUFFER_LENGTH);
    }
}

void InitAudio(void)
{
    ALBankFile    *bankPtr;
    u32           bankLen;
    ALSynConfig   sync;
    ALSeqpConfig  seqpc;
    u32           i,lenMax,*ipt;
    u32           len;

    osCreateMesgQueue(&AIMessageQ, AIMessageBuf, 4);
    osSetEventMesg(OS_EVENT_AI, &AIMessageQ, NULL);
    osSendMesg(&AIMessageQ,NULL,OS_MESG_BLOCK); 
    osCreateMesgQueue(&audDMAMessageQ, audDMAMessageBuf, NUM_DMA_MESSAGES);
    osCreateMesgQueue(&timerMsgQ, &timerMsgBuf, 1);
    

    ipt = (u32*)audioHeap;
    for(i = 0; i < (AUDIO_HEAP_SIZE/4); i++)
	ipt[i] = 0;

    alHeapInit(&aHeapRec, (u8 *) audioHeap, AUDIO_HEAP_SIZE);

    cmdList[0] = alHeapAlloc(&aHeapRec, 1, MAX_RSP_CMDS*sizeof(Acmd));
    cmdList[1] = alHeapAlloc(&aHeapRec, 1, MAX_RSP_CMDS*sizeof(Acmd));
    taskPtr[0] = alHeapAlloc(&aHeapRec, 1, sizeof(OSTask));
    taskPtr[1] = alHeapAlloc(&aHeapRec, 1, sizeof(OSTask));
    audioBuffer[0] = alHeapAlloc(&aHeapRec, 1, sizeof(s32)*NUM_SMPL_PER_FRAME);
    audioBuffer[1] = alHeapAlloc(&aHeapRec, 1, sizeof(s32)*NUM_SMPL_PER_FRAME);
    
    dmaState.initialized = 0;
    dmaBuffs[0].node.prev = 0; 
    dmaBuffs[0].node.next = 0;
    for (i=0; i<NUM_DMA_BUFFERS-1; i++)
    {
        alLink((ALLink*)&dmaBuffs[i+1],(ALLink*)&dmaBuffs[i]);
        dmaBuffs[i].ptr = alHeapAlloc(&aHeapRec, 1, DMA_BUFFER_LENGTH);
    }
    /* last buffer already linked, but still needs buffer */
    dmaBuffs[i].ptr = alHeapAlloc(&aHeapRec, 1, DMA_BUFFER_LENGTH);

    bankLen = _bankSegmentRomEnd - _bankSegmentRomStart;
    bankPtr = alHeapAlloc(&aHeapRec, 1, bankLen);
    romCopy(_bankSegmentRomStart, (char *)bankPtr, bankLen);
    alBnkfNew(bankPtr, (u8 *) _tableSegmentRomStart);

    sync.maxVVoices = MAX_VOICES;
    sync.maxPVoices = MAX_VOICES;
    sync.maxUpdates = MAX_UPDATES;
    sync.dmaproc    = __dmaNew; 
    sync.fxType	    = 0;
    sync.outputRate = 22050;      /* each test better reset this value */
    sync.heap       = &aHeapRec;

    alInit(&audGlbs,&sync);
        
    seqpc.maxVoices      = MAX_VOICES;
    seqpc.maxEvents      = MAX_EVENTS;
    seqpc.maxChannels    = 16;
#ifdef NOT_IN_20C
    /*
     * debugFlags and these corresponding defintions are only present in
     * releases after 2.0.C.  Since we don't use them anywhere else, 
     * it's safe to comment them out here.
     */
    seqpc.debugFlags     = NO_VOICE_ERR_MASK |NOTE_OFF_ERR_MASK | NO_SOUND_ERR_MASK;
#endif
    seqpc.heap           = &aHeapRec;
    seqpc.initOsc        = 0;
    seqpc.updateOsc      = 0;
    seqpc.stopOsc        = 0;

    seqp = alHeapAlloc(&aHeapRec, 1, sizeof(ALSeqPlayer));
    alSeqpNew(seqp, &seqpc);
    alSeqpSetBank(seqp, bankPtr->bankArray[0]); 
    seq = alHeapAlloc(&aHeapRec, 1, sizeof(ALSeq));

    len = _seq1SegmentRomEnd - _seq1SegmentRomStart;
    lenMax = _seq2SegmentRomEnd - _seq2SegmentRomStart;
    lenMax = MAX(len,lenMax);
    len = _seq3SegmentRomEnd - _seq3SegmentRomStart;
    lenMax = MAX(len,lenMax);
    len = _subwaySegmentRomEnd - _subwaySegmentRomStart;
    lenMax = MAX(len,lenMax);
    seqData = alHeapAlloc(&aHeapRec, 1, lenMax);
}

void playSubway(void)
{
    u32  seqLen;

    audGlbs.drvr.outputRate = osAiSetFrequency(44100);  
    seqLen = _subwaySegmentRomEnd - _subwaySegmentRomStart;
    romCopy(_subwaySegmentRomStart, (char *) seqData, seqLen);
    doSequence(seqLen,2);
}

static void AudioTest(int testNum)
{
    u32      seqLen;
    OSTimer  timer;
    u32      c;

    switch (testNum)
    {
	case TEST_LEFT:
	    gng_report("Audio test LEFT\nListen for two tones.", 0, 0, 0);
	    audGlbs.drvr.outputRate = osAiSetFrequency(44100);  
	    /* copy the "tune" sequence into memory */
	    seqLen = _seq1SegmentRomEnd - _seq1SegmentRomStart;
	    romCopy(_seq1SegmentRomStart, (char *) seqData, seqLen);
	    /* turn on zaru and play the "tune" sequence */
	    ZaruSetSound(ZARU_SOUND_L);
	    osSetTimer(&timer,OS_USEC_TO_CYCLES((u64)400000),0,&timerMsgQ,NULL);
	    osRecvMesg(&timerMsgQ, NULL, OS_MESG_BLOCK);
	    doSequence(seqLen,2);
	    ZaruSetSound(ZARU_SOUND_OFF);
	    gng_report("Test complete, push button.", 0, 0, 0);
	    break;
	case TEST_RIGHT:
	    ZaruWaitForNextTestButton();
	    gng_report("Audio test RIGHT\nListen for two tones.", 0, 0, 0);
	    audGlbs.drvr.outputRate = osAiSetFrequency(44100); 
	    /* copy the "tune" sequence into memory */
	    seqLen = _seq2SegmentRomEnd - _seq2SegmentRomStart;
	    romCopy(_seq2SegmentRomStart, (char *) seqData, seqLen);
	    /* turn on zaru and play the "tune" sequence */
	    ZaruSetSound(ZARU_SOUND_R);
	    osSetTimer(&timer,OS_USEC_TO_CYCLES((u64)400000),0,&timerMsgQ,NULL);
	    osRecvMesg(&timerMsgQ, NULL, OS_MESG_BLOCK);
	    doSequence(seqLen,2);
	    ZaruSetSound(ZARU_SOUND_OFF);
	    gng_report("Test complete, push button.", 0, 0, 0);
	    break;
	case TEST_MUSIC:
	    ZaruWaitForNextTestButton();
	    gng_report("Audio test 44100hz\nMusic left\nMusic right\nMusic stereo", 0, 0, 0);
	    audGlbs.drvr.outputRate = osAiSetFrequency(44100); 
	    /* copy the "tune" sequence into memory */
	    seqLen = _seq3SegmentRomEnd - _seq3SegmentRomStart;
	    romCopy(_seq3SegmentRomStart, (char *) seqData, seqLen);
	    /* play the "tune" sequence */
	    doSequence(seqLen,2);
	    gng_report("Audio test 32000hz\nMusic left\nMusic right\nMusic stereo", 0, 0, 0);
	    audGlbs.drvr.outputRate = osAiSetFrequency(32000); 
	    doSequence(seqLen,1);
	    gng_report("Audio test 22050hz\nMusic left\nMusic right\nMusic stereo", 0, 0, 0);
	    audGlbs.drvr.outputRate = osAiSetFrequency(22050); 
	    MoveAudio(); 
	    doSequence(seqLen,0);
	    break;
    }


#ifdef OLD_WAY    
    /* copy the "tune" sequence into memory */
    seqLen = _seq1SegmentRomEnd - _seq1SegmentRomStart;
    romCopy(_seq1SegmentRomStart, (char *) seqData, seqLen);
    /* play the "tune" sequence */
    doSequence(seqLen,testNum);

    /* copy the "sweep" sequence into memory */
    seqLen = _seq2SegmentRomEnd - _seq2SegmentRomStart;
    romCopy(_seq2SegmentRomStart, (char *) seqData, seqLen);
    /* turn on the zaru then wait .2 secs */
    ZaruSetSound(ZARU_SOUND_LR); 
    osSetTimer(&timer,OS_USEC_TO_CYCLES((u64)200000),0,&timerMsgQ,NULL);
    osRecvMesg(&timerMsgQ, NULL, OS_MESG_BLOCK);
    /* start the "sweep" sequence */
    doSequence(seqLen,testNum+3);
    ZaruSetSound(ZARU_SOUND_OFF);
#endif
}

static void doSequence(int seqLen,int testNum)
{
    s16      *audioOp;
    Acmd     *cmdLp;
    s32      clcount;
    OSTask   *task;
    u32      i;

    alSeqNew(seq, seqData, seqLen);
    alSeqpSetSeq(seqp, seq);
    alSeqpPlay(seqp);

    alSeqpSetChlProgram(seqp,0,(u8)testNum);
    alSeqpSetChlProgram(seqp,1,(u8)testNum);
    alSeqpSetChlProgram(seqp,2,(u8)testNum);
    alSeqpSetVol(seqp,0x7fff);

    do {

	__clearAudioDMA();
	audioOp = (s16*) osVirtualToPhysical(audioBuffer[curBuf]);
	cmdLp = alAudioFrame(cmdList[curBuf], &clcount, audioOp, NUM_SMPL_PER_FRAME);

	
	if(clcount)
	{
	    task = taskPtr[curBuf]; 
	    task->t.dram_stack = 0;
	    task->t.output_buff = 0;
	    task->t.output_buff_size = 0;
            task->t.type = M_AUDTASK;
            task->t.flags = 0x0;
            task->t.ucode_boot = (u64 *) rspbootTextStart;
            task->t.ucode_boot_size = ((s32)rspbootTextEnd -
                                         (s32)rspbootTextStart);
            task->t.ucode = (u64 *) aspMainTextStart;
            task->t.ucode_data = (u64 *) aspMainDataStart;
            task->t.ucode_size = 4096;
            task->t.ucode_data_size = sizeof(u64)*(aspMainDataEnd - aspMainDataStart); 
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

    } while (seqp->state != AL_STOPPED);

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


