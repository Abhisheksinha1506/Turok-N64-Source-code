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

/*
 * File:  boot.c
 * Created: Thu Dec 14 16:48:01 PST 1995
 *
 */

#include <ultra64.h>
#include <PR/ramrom.h>		/* needed for argument passing into the app */
#include <assert.h>

#include "game.h"
#include "controller.h"

/*
 * Symbol genererated by "makerom" (RAM)
 */
extern char     _codeSegmentEnd[];
extern char     _zbufferSegmentEnd[];
extern char     _codeSegmentTextEnd[];
extern char     _codeSegmentTextStart[];

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
extern void	game(void);

static OSThread idleThread;
static u64      idleThreadStack[STACKSIZE / sizeof(u64)];

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
                retraceMessageQ;
OSMesg          dmaMessageBuf,
                rspMessageBuf,
                rdpMessageBuf,
                retraceMessageBuf;
OSIoMesg        dmaIOMessageBuf;	/* * see man page to understand this */

/*
 * global variables
 */
static int	debugflag = 0;
int		rdp_DRAM_io = 0;
char		*staticSegment;
char		*textureSegment;
static u32      argbuf[256];




void
boot(void)
{
	int             i;
	char           *ap;
	u32            *argp;

	/*
	 * notice that you can't call osSyncPrintf() until you set
	 * up an idle thread.
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

/*
 * This is the main routine of the app.
 */
static void
mainproc(void *arg)
{

	/*
	 * Setup the message queues
	 */
	osCreateMesgQueue(&dmaMessageQ, &dmaMessageBuf, 1);

	osCreateMesgQueue(&rspMessageQ, &rspMessageBuf, 1);
	osSetEventMesg(OS_EVENT_SP, &rspMessageQ, NULL);

	osCreateMesgQueue(&rdpMessageQ, &rdpMessageBuf, 1);
	osSetEventMesg(OS_EVENT_DP, &rdpMessageQ, NULL);

	osCreateMesgQueue(&retraceMessageQ, &retraceMessageBuf, 1);
	osViSetEvent(&retraceMessageQ, NULL, 1);

	/*
	 * Stick the static segment right after the code/data segment
	 */
	staticSegment = _zbufferSegmentEnd;
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


