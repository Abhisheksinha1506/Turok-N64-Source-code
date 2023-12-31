/* sound player test */

// debug
//#define DEBUGGER	


#include <ultra64.h>
#include <ramrom.h>
#include "smonkey.h"
#include "controller.h"
#include "n64audio.h"

/*
 * Symbol generated by "makerom" to indicate the end of the code segment
 * in virtual (and physical) memory
 */
extern u8 _codeSegmentEnd[];

extern u8 _seqSegmentRomStart[], _seqSegmentRomEnd[];
extern u8 _sfxbankSegmentRomStart[], _sfxbankSegmentRomEnd[];
extern u8 _sfxtableSegmentRomStart[], _sfxtableSegmentRomEnd[];
extern u8 _midibankSegmentRomStart[], _midibankSegmentRomEnd[];
extern u8 _miditableSegmentRomStart[], _miditableSegmentRomEnd[];


/*
 * Stacks for the threads as well as message queues for synchronization
 */

u64 	bootStack[STACKSIZE/8];

static void	mainproc(u8 *);
static void	gameproc(u8 *);

static OSThread	rmonThread;
static u64	rmonThreadStack[RMON_STACKSIZE/8];

static OSThread	mainThread;
static u64	mainThreadStack[STACKSIZE/8];

static OSThread	gameThread;
static u64	gameThreadStack[STACKSIZE/8];

/*
 * For PI manager
 */
OSMesg			PiMessages[DMA_QUEUE_SIZE];
OSMesgQueue		PiMessageQ;
OSMesgQueue		taskMessageQ, retraceMessageQ;
OSMesg			dmaMessageBuf[DMA_QUEUE_SIZE], taskMessageBuf, retraceMessageBuf;
OSIoMesg		dmaIOMessageBuf;
OSTask			*tlist[2];               /* global task list      */
OSIoMesg		dmaIOMesgBuf[DMA_QUEUE_SIZE];
s32				curBuf = 0;
int				byte_count = 0;
int				ActiveController;





boot(void *arg)
{

    osInitialize();

    osCreateThread(&mainThread, 1, (void(*)(void *))mainproc, arg,
		  ((u8 *) mainThreadStack+STACKSIZE), 10);
    osStartThread(&mainThread);
}

static void mainproc(u8 *argv)
{
    osCreateThread(&gameThread, 3, (void(*)(void *))gameproc, argv,
                   ((u8 *) gameThreadStack) + STACKSIZE, 10);
    /* Initialize video */

    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]);

    /*
     * Start PI Mgr for access to cartridge - start before debugger?
     */
    osCreatePiManager((OSPri) 150, &PiMessageQ, PiMessages, DMA_QUEUE_SIZE);

    osCreateThread(&rmonThread, 0, rmonMain, (void *)0,
		   ((u8 *) rmonThreadStack) + RMON_STACKSIZE, OS_PRIORITY_RMON);
    osStartThread(&rmonThread);

#ifndef DEBUGGER
    osStartThread(&gameThread);
#endif

    /*
     * Become the idle thread
     */
    osSetIntMask( OS_IM_ALL );
    osSetThreadPri( 0, 0 );
    for (;;);

}

static
void gameproc(u8 *argv)
{

	s32				nTries = 0, buf, frame=0,  clcount,
					bankLen, len, seqNo = 0, numAllocated, i,
					j, delay_counter = 0, snd_status;
    u8				*ptr, pan = 0, fxmix = 0, *seqPtr, *midiBankPtr,
					*sfxBankPtr;
    s16				*audioOp, vol;
	int				voice_mem;
    f32				pitch;
	t_SndPtr		*sndptr;
	ALSndId			*idPtr;
	ALSound			*newsndptr;
	ALSndPlayer		*PlayerPtr;
	t_SoundPlayer	*PlayerInfo;

	INT32		sndhandle;

    /*
     * Message queue for PI manager return messages
     */


    osCreateMesgQueue(&AW.AudioDmaMessageQ, dmaMessageBuf, DMA_QUEUE_SIZE);
    osCreateMesgQueue(&taskMessageQ, &taskMessageBuf, 1);
    osSetEventMesg(OS_EVENT_SP, &taskMessageQ, NULL);

    /*
     * Prime the task queue
     */
    osSendMesg(&taskMessageQ, NULL, OS_MESG_BLOCK);

    osCreateMesgQueue(&retraceMessageQ, &retraceMessageBuf, 1);
    osViSetEvent(&retraceMessageQ, NULL, NUM_FIELDS);


	InitAudioSystem();


#if 1
    bankLen = _sfxbankSegmentRomEnd - _sfxbankSegmentRomStart;
    sfxBankPtr = alHeapAlloc(&AW.hp, 1, bankLen);
    osWritebackDCacheAll();
    osPiStartDma(&dmaIOMessageBuf, OS_MESG_PRI_NORMAL, OS_READ,
                 (u32)_sfxbankSegmentRomStart, sfxBankPtr,
                 bankLen, &AW.AudioDmaMessageQ);
    (void) osRecvMesg(&AW.AudioDmaMessageQ, NULL, OS_MESG_BLOCK);

	
	

    /*
     * Allocate all the sounds
     */
    alBnkfNew((ALBankFile *)sfxBankPtr, _sfxtableSegmentRomStart);
	
	// sfxBank is *ALBank
    sfxBank = ((ALBankFile *)sfxBankPtr)->bankArray[0];


	// inst is of *ALInstrument
    inst = sfxBank->instArray[0];
	idPtr = AW.SndPlayerList.idlist;  
	PlayerPtr = &AW.SndPlayerList.Sndp;
	PlayerInfo = &AW.SndPlayerList; 
	//PlayerInfo->SoundCount = inst->soundCount;

    for (i=0, numAllocated = 0; i < inst->soundCount; i++)
	{	
		newsndptr = inst->soundArray[i];
        if ((idPtr[i] = alSndpAllocate(PlayerPtr, newsndptr)) != -1)
            numAllocated++;
		else
			rmonPrintf("alloc error!\n");
    }

#endif
	//allocateSFX();
    /*
     * Start up first sound
  	*/

	sndhandle = InitSFX(1);
	TRACE(("InitSFX:%d\n", sndhandle));
	playSFX(sndhandle);
	TRACE(("playSFX\n"));

    (void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);
    (void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);


	//ActiveController = initControllers();

    while (1)  
	{	
	
		//ReadController();
        frame++;
	    tlistp = tlist[curBuf];
		AW.cmdlp = cmdList[curBuf];

        /*
         * How many samples I need
         */
        buf = AW.curAudioBuf % 3;
        audioOp = (s16 *) osVirtualToPhysical(audioBuffer[buf]);
        audioSamples[buf] = 16 + (audioframeSize - samplesLeft + EXTRA_SAMPLES) & ~0xf;
        if (audioSamples[buf] < minFrameSize)
            audioSamples[buf] = minFrameSize;

        /*
         * Call the frame handler ask for samples
         */
        AW.cmdlp = alAudioFrame(AW.cmdlp, &clcount, audioOp, audioSamples[buf]);

		updateAudio();
		
   } 

    //alSndpDelete(sndp);
    alClose(&AW.GlobalAudio);
}

