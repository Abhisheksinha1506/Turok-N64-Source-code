#include <limits.h>
#include <R4300.h>
#include <nos.h>
#include "cpu.h"

/**************************************************************************
 *
 * This module contains 2 threads running in the user space to test 
 *	1) user/kernel mode
 *	2) system call facility
 * 
 * Furthermore, these threads measures:
 *	Interrupt latency, or more specifically:
 *
 *	The time from when an interrupt condition becomes true and a
 *	thread blocking on the interrupt message wakes up reads the message.
 *
 */


/**************************************************************************
 *
 * Global variables
 *
 */
OSThread		userThread;
char			userThreadStack[STACKSIZE];

u32              	userThread1Count = 0;
u32              	userThread2Count = 0;
u32 			userCtxtSwHi	 = 0;
u32 			userCtxtSwLo	 = 0;
u32 			userCtxtSwAvg	 = 0;

/**************************************************************************
 *
 * Local variables
 *
 */
static OSThread		slaveThread;
static char		slaveStack[STACKSIZE];

static void slave(void *);

static OSMesgQueue	sw1MesgQueue;
static OSMesg		sw1MesgBuf[1];

static OSMesgQueue	slaveMesgQueue;
static OSMesg		slaveMesgBuf[1];


/**************************************************************************
 *
 * Extern references
 *
 */
extern	void	SetCause(u32);


void 
userCleanupThread(void)
{
    nosDestroyThread(0);
}


void
userMain(void *arg)
{
    OSIntMask savedMask;
    unsigned int before, after, elapsed;
    register int i;

    userCtxtSwHi  = 0;
    userCtxtSwLo  = UINT_MAX;
    userCtxtSwAvg = 0;

    savedMask = nosSetIntMask(OS_IM_SW1);

    nosCreateMesgQueue(&sw1MesgQueue, sw1MesgBuf, 1);
    nosSetEventMesg(OS_EVENT_SW1, &sw1MesgQueue, (OSMesg)NULL);

    nosCreateMesgQueue(&slaveMesgQueue, slaveMesgBuf, 1);

    userThread1Count = userThread2Count = 0;

    nosCreateThread(&slaveThread, 101, slave, (void *)0,
		   slaveStack+STACKSIZE, SLAVE_THREAD_PRI);
    /* Set bits in status register to enable CP0 access and user mode */
    slaveThread.context.sr |= (SR_CU0 | SR_KSU_USR);
    slaveThread.context.ra = (u64)userCleanupThread;
    nosStartThread(&slaveThread);

    /*
     * The master will snapshot the time and then trigger a SW1 interrupt,
     * which will cause the slave to wake up.  The slave will then immediately
     * snapshot the time and return it to the master to do a difference.
     */
     
    for (i = 0; i < NUM_ITERATIONS; i++) {
	before = nosGetCount();
	SetCause(CAUSE_SW1);
	(void)nosRecvMesg(&slaveMesgQueue, (OSMesg *)&after, OS_MESG_BLOCK);
	elapsed = after - before;
	if (elapsed > userCtxtSwHi)
		userCtxtSwHi = elapsed;
	if (elapsed < userCtxtSwLo)
		userCtxtSwLo = elapsed;
	userCtxtSwAvg += elapsed;
	userThread1Count++;
    }

    userCtxtSwAvg = userCtxtSwAvg / NUM_ITERATIONS;

    (void)nosSetIntMask(savedMask);

}  /* userMain */


static void
slave(void *arg)
{
    OSMesg mesg;
    register int i;

    /*
     * Block for the SW1 interrupt.  When it wakes up, snapshot the
     * time and send it to the master.
     */
    for (i = 0; i < NUM_ITERATIONS; i++) {
	(void)nosRecvMesg(&sw1MesgQueue, &mesg, OS_MESG_BLOCK);
	mesg = (OSMesg)nosGetCount();
	(void)nosSendMesg(&slaveMesgQueue, mesg, OS_MESG_BLOCK);
	userThread2Count++;
    }

}  /* slave */

