/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1995, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/


#include <ultra64.h>
#include <PR/ramrom.h>		/* needed for argument passing into the app */
#include <assert.h>

#include "game.h"
#include "controller.h"
#include "n64audio.h"


#define DMA_QUEUE_SIZE		50


#define DEBUGGER			0

/*
 * Symbol genererated by "makerom" (RAM)
 */
extern char     _codeSegmentEnd[];
extern char     _codeSegmentTextEnd[];
extern char     _codeSegmentTextStart[];
extern char		yield_buffer[];
extern char		*yield_bufferptr;
extern OSTask   taskHeader; 

/*
 * Symbols generated by "makerom" (ROM)
 */
extern char     _staticSegmentRomStart[],
                _staticSegmentRomEnd[];
extern char     _textureSegmentRomStart[],
                _textureSegmentRomEnd[];

/*
 * Stacks for the threads as well as message queues for synchronization
 * This stack is ridiculously large, and could also be reclaimed once
 * the main thread is started.
 */
/*
 * This stack is used only during boot and could be reclaimed later
 */
u64             bootStack[STACKSIZE / sizeof(u64)];

/*
 * Threads
 */
static void     idle(void *);
static void     mainproc(void *);
extern void		game(void);

static OSThread idleThread;
static u64      idleThreadStack[STACKSIZE / sizeof(u64)];

static OSThread AudioThread;
static u64      AudioThreadStack[STACKSIZE / sizeof(u64)];

static OSThread mainThread;
static u64      mainThreadStack[STACKSIZE / sizeof(u64)];

static OSThread rmonThread;
static u64      rmonStack[RMON_STACKSIZE / sizeof(u64)];

/*
 * Messages and message queues
 */
static OSMesg   PiMessages[NUM_PI_MSGS];
static OSMesgQueue PiMessageQ;



OSMesgQueue     dmaMessageQ,
                rspMessageQ,
                rdpMessageQ,
                retraceMessageQ,
                AudioRetraceMessageQ;
OSMesg          dmaMessageBuf,
                rspMessageBuf,
                rdpMessageBuf,
                retraceMessageBuf,
                AudioRetraceMessageBuf;
OSIoMesg        dmaIOMessageBuf;	/* * see man page to understand this */

/*
 * global variables
 */
static int	debugflag = 0;
int		rdp_DRAM_io = 0;
char		*staticSegment;
char		*textureSegment;
static u32      argbuf[256];

// my globals
extern u8 _sfxbankSegmentRomStart[], _sfxbankSegmentRomEnd[];
extern u8 _sfxtableSegmentRomStart[], _sfxtableSegmentRomEnd[];
OSMesg			AudioDmaMessageBuf[DMA_QUEUE_SIZE], AudioTaskMessageBuf;
OSMesgQueue		AudioTaskMessageQ;
OSTask			*tlist[2];               /* global task list      */
OSTask			*tlistp;
s32				curBuf = 0;
OSIoMesg		dmaIOMesgBuf[DMA_QUEUE_SIZE];
INT16			SwitchCounter = 0;


void boot(void)
{
	int             i;
	char           *ap;
	u32            *argp;

	/*
	 * notice that you can't call rmonPrintf() until you set
	 * * up the rmon thread.
	 */

	osInitialize();

	/*
	 * get arguments (options)
	 */
	argp = (u32 *) RAMROM_APP_WRITE_ADDR;
	for (i = 0; i < sizeof(argbuf) / 4; i++, argp++) {
		osPiRawReadIo((u32) argp, &argbuf[i]);	/* Assume no DMA */
	}
	((char *) argbuf)[sizeof(argbuf)-1] = '\0';

	/*
	 * Parse the options 
	 */
	ap = (char *) argbuf;
	position_str = (char *) 0;
	while (*ap != '\0') {
		while (*ap == ' ')
			ap++;
		if (*ap == '-' && *(ap + 1) == 'd') {
			debugflag = 1;
			ap += 2;
		} else if (*ap == '-' && *(ap + 1) == 'r') {
			rdp_DRAM_io = 1;
			ap += 2;
		} else if (*ap == '-' && *(ap + 1) == 'i') {
			ap += 2;
			position_str = ap;
			break;			/* -i must be last argument */
		} 
	}

#if DEBUGGER

	debugflag = 1;

#endif


	osCreateThread(&idleThread, 1, idle, (void *) 0,
			   idleThreadStack + STACKSIZE / sizeof(u64), 10);

	osStartThread(&idleThread);

	/*
	 * never reached 
	 */
}

static void
idle(void *arg)
{
	/*
	 * Initialize video 
	 */
	osCreateViManager(OS_PRIORITY_VIMGR);
	osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]);

	/*
	 * Start PI Mgr for access to cartridge
	 */
	osCreatePiManager((OSPri) OS_PRIORITY_PIMGR, &PiMessageQ, PiMessages,
		  NUM_PI_MSGS);

	/*
	 * Start RMON for debugging & data xfer (make sure to start 
	 * PI Mgr first)
	 */
	osCreateThread(&rmonThread, 0, rmonMain, (void *) 0,
		   (void *) (rmonStack + RMON_STACKSIZE / 8),
		   (OSPri) OS_PRIORITY_RMON);
	osStartThread(&rmonThread);

	/*
	 * at this point, AND NOT BEFORE, we can now do an
	 * rmonPrintf()
	 */

	/*
	 * Create main thread
	 */
	osCreateThread(&mainThread, 3, mainproc, arg,
		   mainThreadStack + STACKSIZE / sizeof(u64), 10);

	if (!debugflag)
		osStartThread(&mainThread);

	/*
	 * Become the idle thread
	 */
	osSetThreadPri(0, 0);

	for (;;) ;
}


static void
soundproc(void *arg)
{
	static int i = 0;
	s32				buf, frame=0, clcount;
	INT32			bankLen, numAllocated;
	u8				*sfxBankPtr;
	ALInstrument	*inst; 
	ALBank			*sfxBank;
	ALSndId			*idPtr;
	ALSound			*newsndptr;
	ALSndPlayer		*PlayerPtr;
	t_SoundPlayer	*PlayerInfo;
    s16				*audioOp;
	INT32			sndhandle;


	// create dma message buffers
    osCreateMesgQueue(&AW.AudioDmaMessageQ, AudioDmaMessageBuf, DMA_QUEUE_SIZE);
    osCreateMesgQueue(&AudioTaskMessageQ, &AudioTaskMessageBuf, 1);
    osSetEventMesg(OS_EVENT_SP, &AudioTaskMessageQ, NULL);

	//Prime the task queue
    //osSendMesg(&AudioTaskMessageQ, NULL, OS_MESG_BLOCK);

	// create retrace message buffers
	osCreateMesgQueue(&AudioRetraceMessageQ, &AudioRetraceMessageBuf, 1);
	osViSetEvent(&AudioRetraceMessageQ, NULL, 1);

	InitAudioSystem();

	// set address of yield buffer and align it
	yield_bufferptr = (char*)(((int)yield_buffer+15) & (-16));
	taskHeader.t.yield_data_ptr = (u64*)yield_bufferptr;
	audio_yield_buffer_ptr = (char*)(((int)audio_yield_buffer+15) & (-16));


	TRACE(("allocate sounds\n"));



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

	//allocateSFX();
	TRACE(("%d sounds allocated\n", numAllocated));
    //(void)osRecvMesg(&AudioRetraceMessageQ, NULL, OS_MESG_BLOCK);
    //(void)osRecvMesg(&AudioRetraceMessageQ, NULL, OS_MESG_BLOCK);

	TRACE(("gtask:%x", taskHeader.t.yield_data_ptr));

	while(1)
	{
		osRecvMesg(&AudioRetraceMessageQ, NULL, OS_MESG_BLOCK);
		osSendMesg(&retraceMessageQ, NULL, OS_MESG_NOBLOCK); 
	
		TRACE(("s:%d\n", SwitchCounter));
		frame++;
		tlistp = tlist[curBuf];
		AW.cmdlp = cmdList[curBuf];

	    // How many samples I need
		buf = AW.curAudioBuf % 3;
		audioOp = (s16 *) osVirtualToPhysical(audioBuffer[buf]);
		audioSamples[buf] = 16 + (audioframeSize - samplesLeft + EXTRA_SAMPLES) & ~0xf;			if (audioSamples[buf] < minFrameSize)
			audioSamples[buf] = minFrameSize;

		/*
		 * Call the frame handler ask for samples
		 */
		AW.cmdlp = alAudioFrame(AW.cmdlp, &clcount, audioOp, audioSamples[buf]);
		updateAudio();
		SwitchCounter++;
	}
}

/*
 * This is the main routine of the app.
 */
static void
mainproc(void *arg)
{

	/*  Create Audio thread */
	osCreateThread(&AudioThread, 1, soundproc, (void *) 0,
		   AudioThreadStack + STACKSIZE / sizeof(u64), 11);
	osStartThread(&AudioThread);

	/*
	 * Setup the message queues
	 */
	osCreateMesgQueue(&dmaMessageQ, &dmaMessageBuf, 1);

	osCreateMesgQueue(&rspMessageQ, &rspMessageBuf, 1);
	//osSetEventMesg(OS_EVENT_SP, &rspMessageQ, NULL);

	osCreateMesgQueue(&rdpMessageQ, &rdpMessageBuf, 1);
	osSetEventMesg(OS_EVENT_DP, &rdpMessageQ, NULL);

	osCreateMesgQueue(&retraceMessageQ, &retraceMessageBuf, 1);
	//osViSetEvent(&retraceMessageQ, NULL, 1);

	/*
	 * Stick the static segment right after the code/data segment
	 */
	staticSegment = _codeSegmentEnd;
	osPiStartDma(&dmaIOMessageBuf, OS_MESG_PRI_NORMAL, OS_READ,
		 (u32) _staticSegmentRomStart, staticSegment,
		 (u32) _staticSegmentRomEnd - (u32) _staticSegmentRomStart,
		 &dmaMessageQ);

	/*
	 * Wait for DMA to finish
	 */
	(void) osRecvMesg(&dmaMessageQ, NULL, OS_MESG_BLOCK);

	/*
	 * Stick the texture segment right after the static segment
	 */
	textureSegment = staticSegment + 
		(u32) _staticSegmentRomEnd - (u32) _staticSegmentRomStart;
	osPiStartDma(&dmaIOMessageBuf, OS_MESG_PRI_NORMAL, OS_READ,
		 (u32) _textureSegmentRomStart, textureSegment,
		 (u32) _textureSegmentRomEnd - (u32) _textureSegmentRomStart,
		 &dmaMessageQ);

	/*
	 * Wait for DMA to finish
	 */
	(void) osRecvMesg(&dmaMessageQ, NULL, OS_MESG_BLOCK);

	initControllers(MAXCONTROLLERS);

	game();
}


