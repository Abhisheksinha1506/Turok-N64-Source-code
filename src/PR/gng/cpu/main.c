/*====================================================================
 * main.c
 *
 * Copyright 1995-1996, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/

#include <os.h>
#include <ultra64.h>
#include <rmon.h>
#include <string.h>
#include <bstring.h>
#include "os_internal.h"
#include "osint.h"
#include "cpu.h"

/*====================================================================
 * 
 * This is the main module for the CPU subsystem of the Go/No-go test
 * program. The idea here is to do test the followings:
 *	1) TLB facility
 *	2) User/Kernel space 
 *	3) System call facility
 *	4) Basic floating-point functions 
 *
 * The main function CpuTest() performs the followings:
 *	- Start the high-priority fault thread to handle CPU fault messages
 *	  This thread should block and listen to fault message.
 *	- Install a new exception handler that can handles system call
 *	  exceptions
 *	- Run the stand-alone TLB test 
 *	- If test fails return	
 *	- Start the timer thread
 *	  After setting a timer, this thread should block and listen to 
 *	  time-out message.
 *	- Load the user segment (via TLB map)
 *	- Start the first user thread; this user thread, in turn, starts
 *	  another user thread. These 2 threads takes turn running by
 *	  sofware interrupt/message to invoke each other.
 *	- Start the FPU thread; this thread runs a series of floating
 *	  point tests and returns.
 *	- Verify that the user thread executes correctly.
 *	- Kill the timer and fault threads.
 *	- Restore the original exception handler.
 *	- Return to caller with error number.
 * 
 *====================================================================*/

/* Flag to print out thread structure */
/*
#define _DUMP_THREAD
*/

/**************************************************************************
 *
 * Definitions
 *
 */
#define TIMESLICE_INTERVAL      OS_USEC_TO_CYCLES(250)
#define TIMER_MOD		100



/**************************************************************************
 *
 * Global variables
 *
 */
OSFault		__osFault = { 0 };
u32		CpuErrorCount = 0;


/**************************************************************************
 *
 * Local variables
 *
 */

static OSThread		faultThread;
static char		faultThreadStack[STACKSIZE];
static OSMesgQueue	faultMesgQueue;
static OSMesg		faultMesgBuf[5];

static	OSThread	fpThread;
static	char		fpThreadStack[STACKSIZE];

static OSThread         timerThread;
static char             timerThreadStack[STACKSIZE];
static OSMesgQueue      timerMesgQueue;
static OSMesg           timerMesgBuf[2];
static OSTimer          timer;


/**************************************************************************
 *
 * Extern references
 *
 */
extern char 		_userSegmentRomStart[];
extern char 		_userSegmentRomEnd[];
extern char		_userSegmentStart[];
extern char		_userSegmentTextStart[];
extern char		_userSegmentTextEnd[];
extern char		_userSegmentDataStart[];
extern char		_userSegmentDataEnd[];
extern char		_userSegmentBssStart[];
extern char		_userSegmentBssEnd[];
extern char		_bufferSegmentBssStart[];
extern char		_bufferSegmentBssEnd[];

extern OSThread 	userThread;
extern char		userThreadStack[];
extern void		userMain(void *);
extern void		userCleanupThread(void);
extern u32		userThread1Count;
extern u32		userThread2Count;
extern u32		userCtxtSwHi, userCtxtSwLo, userCtxtSwAvg;

extern u32		__osSetJmp(u32 *);
extern void		__osRestoreJmp(u32 *, OSThread *);

extern s32		tlbTest(void);
extern s32		fpTest(void);


/**************************************************************************
 *
 * Function prototypes
 *
 */
static void		faultMain(void *);
static void		timerMain(void *);
static void		fpMain(void *);

static void		dumpThread(char *, OSThread *);


/**************************************************************************
 *
 * Functions
 *
 */

/* 
 * Increment global error counter
 */
void
IncrementErrorCount(u32 error)
{
    u32		saveMask;

    /*
     * Now, we turn off interrupts to increment global counter
     */
    saveMask = __osDisableInt();
    CpuErrorCount += error;
    __osRestoreInt(saveMask);

}  /* IncrementErrorCount */


static void
loadUserSegment(void)
{

    /*
     * Just to be safe, we unmap all TLBs first
     */
    osUnmapTLBAll();

    /*
     * Map 128 KB starting at APP_PADDR to be used for user thread
     */
    osMapTLB(0, OS_PM_64K, _userSegmentStart, APP_PADDR, APP_PADDR+_64K, -1);

    /*
     * Here, we invalidate I-cache and D-cache areas that point to 
     * the user segment
     */
    osInvalICache(_userSegmentTextStart,
                  _userSegmentTextEnd-_userSegmentTextStart);
    osInvalDCache(_userSegmentDataStart,
                  _userSegmentDataEnd-_userSegmentDataStart);
    osPiRawStartDma(OS_READ, (u32)_userSegmentRomStart, _userSegmentStart, 
                   _userSegmentRomEnd-_userSegmentRomStart);

    while(osPiGetStatus() & PI_STATUS_DMA_BUSY);

    bzero(_userSegmentBssStart, _userSegmentBssEnd-_userSegmentBssStart);

}  /* loadUserSegment */


static void
installExceptionHandler(void)
{
    u32		saveMask;

    /*
     * Now, we turn off interrupts to replace exception handler 
     */
    saveMask = __osDisableInt();

    osWritebackDCache((void*)UT_VEC,
                  E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void*)UT_VEC,
                  E_VEC - UT_VEC + sizeof(__osExceptionVector));

    *(__osExceptionVector *)UT_VEC =
            *(__osExceptionVector *)__osExceptionPreamble2;
    *(__osExceptionVector *)XUT_VEC =
            *(__osExceptionVector *)__osExceptionPreamble2;
    *(__osExceptionVector *)ECC_VEC =
            *(__osExceptionVector *)__osExceptionPreamble2;
    *(__osExceptionVector *)E_VEC =
            *(__osExceptionVector *)__osExceptionPreamble2;

    osWritebackDCache((void*)UT_VEC,
                  E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void*)UT_VEC,
                  E_VEC - UT_VEC + sizeof(__osExceptionVector));

    __osRestoreInt(saveMask);

}  /* installExceptionHandler */


static void
restoreExceptionHandler(void)
{
    u32		saveMask;

    /*
     * Now, we turn off interrupts to restore original exception handler 
     */
    saveMask = __osDisableInt();

    /*
     * Restore FPU state
     * Turn on FS bit to flush denormalized  number to zero;
     * enable "invalid operation" faulting to catch generation of NaNs.
     */
    __osSetSR(__osGetSR() | SR_CU1);
    __osSetFpcCsr(FPCSR_FS | FPCSR_EV);

    osWritebackDCache((void*)UT_VEC,
                  E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void*)UT_VEC,
                  E_VEC - UT_VEC + sizeof(__osExceptionVector));

    *(__osExceptionVector *)UT_VEC =
            *(__osExceptionVector *)__osExceptionPreamble;
    *(__osExceptionVector *)XUT_VEC =
            *(__osExceptionVector *)__osExceptionPreamble;
    *(__osExceptionVector *)ECC_VEC =
            *(__osExceptionVector *)__osExceptionPreamble;
    *(__osExceptionVector *)E_VEC =
            *(__osExceptionVector *)__osExceptionPreamble;

    osWritebackDCache((void*)UT_VEC,
                  E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void*)UT_VEC,
                  E_VEC - UT_VEC + sizeof(__osExceptionVector));

    __osRestoreInt(saveMask);

}  /* restoreExceptionHandler */


int
CpuTest(void)
{

    OSMesg	mesg;
    u32		i;
    u32		saveMask;

    XDEBUG(PRINTF("CpuTest\n"));

    /*
     * Create fault handler thread
     */
    osCreateThread(&faultThread, 3, faultMain, (void *)0,
		faultThreadStack+STACKSIZE, (OSPri)FAULT_THREAD_PRI);
    osStartThread(&faultThread);
    
    /*
     * Install new exception handler 
     */
    installExceptionHandler();

    /*
     * Here, we can run the TLB test
     */
    XDEBUG(PRINTF("Start TLB test...\n"));

    CpuErrorCount = tlbTest();
    if (CpuErrorCount != 0) {
        /* 
         * We don't need to restore original exception handler because
         * the new one works just fine.
         */
        PRINTF("CPU: TLB test FAILED!\n");
        return(CpuErrorCount);
    }

    XDEBUG(PRINTF("Start timer thread...\n"));
    /*
     * Create timer thread
     */
    osCreateThread(&timerThread, 4, timerMain, (void *)0,
		timerThreadStack+STACKSIZE, (OSPri)TIMER_THREAD_PRI);
    osStartThread(&timerThread);
    
    /*
     * Create user-space thread
     * First, we need to map the TLB and then dma the user segment into RDRAM.
     */
    loadUserSegment();

    XDEBUG(PRINTF("Start user thread!\n"));

    osCreateThread(&userThread, 6, userMain, (void *)0,
		userThreadStack+STACKSIZE, (OSPri)USER_THREAD_PRI);
    /* Set bits to enable CP0 access and user mode */
    userThread.context.sr |= (SR_CU0| SR_KSU_USR);
    userThread.context.ra = (u64)userCleanupThread;
    osStartThread(&userThread);

    /*
     * Create fp thread
     */
    XDEBUG(PRINTF("Start fp thread!\n"));

    osCreateThread(&fpThread, 5, fpMain, (void *)0,
		fpThreadStack+STACKSIZE, (OSPri)FP_THREAD_PRI);
    osStartThread(&fpThread);

    XDEBUG(PRINTF("Get control back!\n"));

    /*
     * Here, we get control back which means that all user and fp threads are 
     * done. We check to make sure that the user threads executed correctly.
     */
    if ((userThread1Count != NUM_ITERATIONS) ||
        (userThread2Count != NUM_ITERATIONS)) {
        CpuErrorCount++;
        PRINTF("CPU: User thread FAILED!\n");
    }

    XDEBUG(PRINTF("interrupt latency (cycles) average %d high %d low %d\n",
        userCtxtSwAvg, userCtxtSwHi, userCtxtSwLo));
    XDEBUG(PRINTF(
	"interrupt latency (ns)     average %lld high %lld low %lld\n",
        OS_CYCLES_TO_NSEC(userCtxtSwAvg),
        OS_CYCLES_TO_NSEC(userCtxtSwHi),
        OS_CYCLES_TO_NSEC(userCtxtSwLo)));

    /*
     * Need to kill fault handler and timer handler
     */
    osStopTimer(&timer);
    osDestroyThread(&timerThread);
    osDestroyThread(&faultThread);

    /*
     * Here, we unmap all TLBs, flush the D-cache, and restore
     * the original exception handler
     */
    osUnmapTLBAll();
    osWritebackDCacheAll();
    restoreExceptionHandler();

    PRINTF("CPU: return with error=%d\n", CpuErrorCount);

    return(CpuErrorCount);

}  /* main */


static void
faultMain(void *arg)
{

    OSThread	*tptr;
    OSMesg	mesg;
    int		i;

    XDEBUG(PRINTF("faultMain\n"));

    osCreateMesgQueue(&faultMesgQueue, faultMesgBuf, 5);
    osSetEventMesg(OS_EVENT_FAULT, &faultMesgQueue, (OSMesg)MSG_FAULT);

    while (1) {
        (void)osRecvMesg(&faultMesgQueue, (OSMesg *)&mesg, OS_MESG_BLOCK);

        /* If nofault is defined via a setjmp call */
        /* 
         * Search for faulted thread 
         * If faulted thread is same as nofault thread
         *     set thread pc to jmp_buffer pc
         *     set thread to OS_STATE_RUNNABLE
         *     reset thread state flag
         *     clear nofault
	 *	   enqueue thread again
         */
        tptr = FindFaultedThread();
        if (tptr) {
            dumpThread("faulted thread", tptr);
        }
	if (__osFault.nofault) {
            if (__osFault.thread == tptr) {
                /* Assume that caller has called __osSetJmp */
                __osRestoreJmp(__osFault.nofault, tptr);
                tptr->state = OS_STATE_STOPPED;
                tptr->flags = 0;
                tptr->context.sr |= SR_EXL;
                tptr->next = (OSThread *)NULL;
                tptr->queue = (OSThread **)NULL;
                osStartThread(tptr);
            } 
	}
    }  /* while */

}  /* faultMain */


static void
timerMain(void *arg)
{

    OSTime	timeSlice, delta;
    OSThread	*tptr;
    OSMesg	mesg;
    int		i;


    XDEBUG(PRINTF("timerMain\n"));

    delta = 0;
    timeSlice = TIMESLICE_INTERVAL;
    osCreateMesgQueue(&timerMesgQueue, timerMesgBuf, 2);
    osSetTimer(&timer, 0, timeSlice, &timerMesgQueue, (OSMesg)MSG_TIMER_EXP);

    while (1) {

	/* Wait for timer to expired */
        (void)osRecvMesg(&timerMesgQueue, (OSMesg *)&mesg, OS_MESG_BLOCK);

	/* Stop current timer */
        osStopTimer(&timer);

	/* Calculate new time slice value */
	delta = osGetTime() % TIMER_MOD;
        timeSlice = TIMESLICE_INTERVAL + delta;

	/* Reset timer */
        osSetTimer(&timer, 0, timeSlice, &timerMesgQueue, 
            (OSMesg)MSG_TIMER_EXP);

    }  /* while */

}  /* timerMain */


static void
fpMain(void *arg)
{
    int		i, error;
    u32		saveMask;
    float	f1, f2, f3;

    XDEBUG(PRINTF("fpMain\n"));

    /*
     * We perform floating point operations here to tell OS to save 
     * proper floating registers before we start the real test.
     * 
     */
    f1 = 1000.0;
    f2 = 10.0;
    f3 = f1/f2;

    error = 0;
    for (i = 0; i < NUM_ITERATIONS; i++) {
        error += fpTest(); 
    }

    if (error != 0) {
        PRINTF("CPU: FP test FAILED, error=%d!\n", error);
    }
    IncrementErrorCount(error);

}  /* fpMain */


void
dumpThread(char *name, OSThread *t)
{
#ifdef _DUMP_THREAD
    PRINTF("******** Thread `%s`: 0x%x ********\n", name, t);
    PRINTF("\tid\t= %d\n", t->id);
    PRINTF("\tpri\t= %d\n", t->priority);
    PRINTF("\tnext\t= 0x%x\n", t->next);
    PRINTF("\tqueue\t= 0x%x\n", t->queue);
    PRINTF("\tpc\t= 0x%x\n", t->context.pc);
    PRINTF("\ta0\t= 0x%llx\n", t->context.a0);
    PRINTF("\tsp\t= 0x%llx\n", t->context.sp);
    PRINTF("\tra\t= 0x%llx\n", t->context.ra);
    PRINTF("\tsr\t= 0x%x\n", t->context.sr);
    PRINTF("\tcause\t= 0x%x\n", t->context.cause);
    PRINTF("\tbadvaddr= 0x%x\n", t->context.badvaddr);
    PRINTF("\trcp\t= 0x%x\n", t->context.rcp);
    PRINTF("\tfpcsr\t= 0x%x\n", t->context.fpcsr);
    PRINTF("\tfp\t= 0x%x\n", t->fp);
    PRINTF("\tstate\t= 0x%x\n", t->state);
    PRINTF("\tflags\t= 0x%x\n", t->flags);
    PRINTF("******** END *******\n");
#endif
}

