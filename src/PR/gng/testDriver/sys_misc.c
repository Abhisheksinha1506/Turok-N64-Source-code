/**************************************************************************
 *									  *
 *		 Copyright (C) 1996, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/
/*
 * File:        sys_misc.c
 * Creator:     scott@sgi.com
 * Create Date: Thu Feb  8 17:42:30 PST 1996
 * Purpose:     Misc tests for the Ultra 64 system, clock freq, INT 1, NMI,
 *		RDRAM
 *
 */
 
#include <ultra64.h>
#include <os_internal.h>
#include "gng.h"
#include "zaru.h"

extern void playSubway(void);

#define CART_TIMER_MESSAGE	10
#define CART_INTERRUPT_MESSAGE	11
#define GNG_PRENMI_MSG		20

static OSMesg cartmsg, prenmimsg, timermsg;
static OSMesgQueue cartq, prenmiq, timerq;
static OSTimer timer;

/*
 * main.c's boot() function will read the reserved memory locations used
 * by the rdram diagnostic prior to calling osInitialize(), since this 
 * function clobbers the reserved rdram space used for this purpose.
 */
int rdramDiagErrors;
int rdramDiagStatus;

/*
 * CLOCK FREQUENCY TEST
 *
 * The frequency test for the CPU.  Assume that the video clock is good
 * because the operator can see video on the screen.  Check that the
 * CPU frequency is within correct range.
 *
 * XXX need to change for PAL
 */
int
clocktest()
{
    OSTime starttime, endtime;	    /* in clock cycles */
    u64 retracetime;		    /* in usec */
    OSPri pri;
    OSIntMask savemask;
    u32 rcp_intr;
    
    /* Use the video clock as a reference */
    
    pri = osGetThreadPri(NULL);
    osSetThreadPri(NULL, OS_PRIORITY_APPMAX+1);
    
    /* make sure video retrace queue is empty */
    while ( !MQ_IS_EMPTY(&retraceMessageQ) )
	(void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);
	
    (void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK); /* for good luck */
    (void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);
    starttime = osGetTime();
    (void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);
    endtime = osGetTime();
    
    osSetThreadPri(NULL, pri);

#ifdef ALTERNATE
    savemask = osSetIntMask(OS_IM_NONE);
    
    while (!(IO_READ(MI_INTR_REG) & MI_INTR_VI))
	;
    IO_WRITE(VI_CURRENT_REG, 0);
    
    while (!(IO_READ(MI_INTR_REG) & MI_INTR_VI))
	starttime = osGetTime();;
    IO_WRITE(VI_CURRENT_REG, 0);
    
    while (!(IO_READ(MI_INTR_REG) & MI_INTR_VI))
	endtime = osGetTime();;
    IO_WRITE(VI_CURRENT_REG, 0);
    
    osSetIntMask(savemask);
#endif
    
    
    
    retracetime = OS_CYCLES_TO_USEC(endtime - starttime);
    
    if ( retracetime < NTSC_USEC_PER_RETRACE - NTSC_USEC_RANGE ||
	    retracetime > NTSC_USEC_PER_RETRACE + NTSC_USEC_RANGE )
	return GNG_TEST_FAILURE;
    else
	return GNG_TEST_SUCCESS;

}

/*
 * INT1 TEST
 * 
 * The INT1, also known as CARTINT test.  This test uses the special HW
 * in the GNG ROM cartridge to generate the interrupt that comes in over
 * the AD16 bus.  We read a Zaru register bit to detect whether or not the
 * interrupt was detected on the bottom connector (the interrupt is generated
 * by a write to the rom cartridge on the top connector).
 *
 * We only perform this test if we have detected that we are running from a
 * ROM cartridge.
 */
int
intr1test()
{
    extern void clearint1();
    u32 saveMask;
    int retval;

    /* Be optimistic, assume success */
    retval = GNG_TEST_SUCCESS;

    if (runningFromRom) {

	osCreateMesgQueue(&cartq, &cartmsg, 1);
	__osSetHWIntrRoutine(1, clearint1);
	osSetEventMesg(OS_EVENT_CART, &cartq, (OSMesg)CART_INTERRUPT_MESSAGE);
	
	/* fire off a half second timer.  Should receive message before then */
	osSetTimer(&timer, OS_USEC_TO_CYCLES(500000), 0, &cartq, 
	    (OSMesg)CART_TIMER_MESSAGE);
	
	/*
	 * XXX any need to check INT bit in Zaru now?
	 */

	/* Block all interrupts before setting the bit. */
	saveMask = __osDisableInt();
	
	/* Cause the interrupt (IO_WRITE does the PHYS_TO_K1 conversion) */
	IO_WRITE((u32)(INT1_ADDR), INT1_SET_DATA);
	
	/* 
	 * Check Zaru bit to see if bottom pin detects interrupt line active 
	 */
	if (ZaruGetInt1() == 0) {
	    retval = GNG_TEST_FAILURE;
	}
	
	/*
	 * Enable interrupts to check board connection of interrupt to CPU.
	 * The exception handler will call clearint1() to clear the HW
	 * interrupt with interrupts blocked, and then send the OS_EVENT_CART
	 * message to this thread.
	 */
	__osRestoreInt(saveMask);

	/* 
	 * now block for either the cartridge interrupt or the timer interrupt 
	 */
	osRecvMesg(&cartq, &cartmsg, OS_MESG_BLOCK);

	if (cartmsg == (OSMesg)CART_INTERRUPT_MESSAGE) {
	    osStopTimer(&timer);	/* retval was set to SUCCESS above */
	} else {
	    retval = GNG_TEST_FAILURE;
	}

	/*
	 * XXX any need to check INT bit in Zaru now?
	 */

	/* clean up */
	__osSetHWIntrRoutine(1, NULL);

    }
    /* indicate success or failure */
    return retval;
}

/*
 * RESET/INT2/NMI TEST
 *
 * Test for the RESET Switch. Here is what happens when RESET is pushed:
 * 
 * When the RESET switch is pushed, the hardware generates an
 * INT2 that gets turned into a PRENMI event.  GNG should set up to catch
 * the PRENMI event early.  The PRENMI event will be followed by a NMI to
 * the R4300 CPU in .5 seconds. If the RESET switch is pushed and held for
 * more than .5 seconds, the NMI will not occur until immediately after
 * the switch is released. The NMI will "reboot" the game.

 * After the NMI occurs, the game reboots.  The hardware is initialized,
 * the first Meg of the game in ROM is copied into the first Megabyte of
 * RAM after the boot address, the BSS for the boot segment is cleared and
 * the boot procedure is called.  This is exactly the same as a power on
 * reset with some minor differences.  The hardware initialization is
 * different.  On a power on reset, the caches are invalidated, after a
 * NMI the caches are flushed before they are invalidated.  The power on
 * reset also configures the RAM, while after a NMI the RAMs are left
 * alone.  The contents of memory, except for the 1 Meg that is copied in,
 * are the same as before the NMI occured.  The global variable,
 * osResetType, is set to 0 on a power up reset and to 1 on a NMI.
 *
 * The GNG test for RESET/NMI should check the following:
 * 1) INT2 occurs after prompting the operator to push the reset
 * 2) NMI occurs between .4 seconds & 2 seconds after the INT2 (If the operator
 *    holds the RESET button down for 2 seconds the test will fail)
 * 3) Check that NMI does not occur at other times
 *
 */
int
nmitest_phase1()
{

    gngstatus	*pstatus;
    
    /*
     * osAppNMIBuffer == 0x8000031c in locore rdram
     */
    pstatus = (gngstatus *)osAppNMIBuffer;

    pstatus->nmi_first_timer = 0;
    pstatus->nmi_second_timer = 0;

    osCreateMesgQueue(&prenmiq, &prenmimsg, 1);
    osCreateMesgQueue(&timerq, &timermsg, 1);
    osSetEventMesg(OS_EVENT_PRENMI, &prenmiq, (OSMesg)GNG_PRENMI_MSG);

    gng_report("Push RESET switch", 0, 0, 1);

    /*
     * Play an alert noise to indicate to the user that they need to press
     * the button.
     */
    playSubway();

    /* now wait for prenmi message */
    osRecvMesg(&prenmiq, &prenmimsg, OS_MESG_BLOCK);
        
    /* fire off a .4 second timer.  Should not receive NMI before then */
    osSetTimer(&timer, OS_USEC_TO_CYCLES(400000), 0, &timerq, (OSMesg)NULL);
    osRecvMesg(&timerq, &timermsg, OS_MESG_BLOCK);
    pstatus->nmi_first_timer = 1;
    
    /*
     * XXX Should start a ROM DMA here.  The NMI should clear the PI
     * DMA. However, this requires a version 4 PIF with the boot code 
     * that does not have the "jump out into a patch" code.
     */
    
    /* fire off a 1.6 second timer.  Should never return from recv message */
    osSetTimer(&timer, OS_USEC_TO_CYCLES(1600000), 0, &timerq, (OSMesg)NULL);
    osRecvMesg(&timerq, &timermsg, OS_MESG_BLOCK);
    pstatus->nmi_second_timer = 1;
    
    /* ERROR if we get here */
    return GNG_TEST_FAILURE;    
}

int
nmitest_phase2()
{
    gngstatus	*pstatus;
    
    /*
     * osAppNMIBuffer == 0x8000031c in locore rdram
     */
    pstatus = (gngstatus *)osAppNMIBuffer;

    if (pstatus->nmi_count != 1)
	return 1;
    if (pstatus->nmi_first_timer != 1)
	return 2;
    if (pstatus->nmi_second_timer != 0)
	return 3;

    return GNG_TEST_SUCCESS;
}

/* 
 * The RDRAM test is run immediately after the gng program boots.  The boot()
 * function checks a reserved word in rdram to see if the rdram test has been
 * run yet; if not, it boots a small program into dmem which runs the rdram 
 * test, then copies the gng boot segment back into rdram memory again, and 
 * jumps to it.  The second time around, the boot code figures out that the 
 * rdram test has been run, then jumps to the standard testDriver, which invokes
 * the function below to determine the results of the rdram test & gng_report
 * these results to the screen.
 *
 * We then reset the reserved word variables to zero, in case we are running
 * on a development board where the memory might not be explicitly cleared
 * by a power cycle.
 */

int
rdramTest()
{
    u8 dipSettings;
    int expectedSize;
    char message[256];
    volatile gngstatus	*pstatus;
    
    /*
     * osAppNMIBuffer == 0x8000031c in locore rdram
     */
    pstatus = (gngstatus *)osAppNMIBuffer;

    if (zaruexists) {
	dipSettings = ZaruGetDIPSwitch();
	dipSettings &= 0x3;

	switch (dipSettings) {
	    case ZARU_4MB:
		expectedSize = 0x400000;
		break;
	    case ZARU_6MB:
		expectedSize = 0x600000;
		break;
	    case ZARU_8MB:
		expectedSize = 0x800000;
		break;
	    default:
		gng_report(
		  "RDRAM memory\nillegal dip switch\n(switch = 0x3)\n", 
		   1, GNG_PASS_FAIL_BIT, 120);

		rdramDiagErrors++;
		break;
	}

	if (expectedSize != osMemSize) {

	    sprintf(message, "RDRAM memory size 0x%x\nexpected size 0x%x\n",
		osMemSize, expectedSize);
	    gng_report(message, 1, GNG_PASS_FAIL_BIT, 120);

	    rdramDiagErrors++;
	}
    }

    /*
     * Clear reserved word variables in case of program restart without
     * a power cycle to clear memory.
     */
    pstatus->rdram_diag_status = 0;
    pstatus->rdram_diag_errors = 0;

    if ( rdramDiagErrors == 0 ) {
	return GNG_TEST_SUCCESS;
    } else {
	return GNG_TEST_FAILURE;    
    }
}
