/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1995, 1996 Silicon Graphics, Inc.          *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

#include <ultra64.h>
#include "gng.h"

extern void playSubway(void);

/*
 * File:	uji.c
 * Creator:	scott@sgi.com
 * Purpose:	Ported code, from uji_diags.c, for tests that require 
 *		the Zaru jig.
 */

static u8 controllerdata[] = {
    0x00, 
    0x55, 
    0xaa, 
    0xff, 
    0x01, 
    0x02, 
    0x04, 
    0x08, 
    0x10, 
    0x20, 
    0x40, 
    0x80, 
};

/*
 * Check the power, ground, and other signal bits.
 * These are scattered around in the zaru address space
 */
int
VoltageTest()
{
    int retvalue = GNG_TEST_SUCCESS;	    /* assume success */
    u8 data;

    if (!zaruexists)	    /* Assume everything is OK if no Zaru */
	return GNG_TEST_SUCCESS;
    
    /* First check the Power line register (0x1800) */
    data = ZaruGetPowerCheck();

    /*
     * check that only the bits that should be on are on
     * and that only those bits are on.
     */
    if (data ^ (ZARU_V2 | ZARU_V3 | ZARU_V4 | ZARU_GND1CHK | ZARU_GND2CHK))
	retvalue = GNG_TEST_FAILURE;
	
    data = ZaruGetMisc();
    if ( (data & ZARU_MISC_5VCHKCON) == 0)
	retvalue = GNG_TEST_FAILURE;

    ZaruSetExpCommand(ZARU_EXP_CMD_GND);
    
    data = ZaruGetExpHigh();
    /*
     * check that only the bits that should be on are on
     * and that only those bits are on.
     * XXXX - also checking SEC1, SEC2,  CCLK & CSYNC
     */
    if (data ^ (ZARU_SEC1 | ZARU_SEC2 | ZARU_CCLK | ZARU_CSYNC))
	retvalue = GNG_TEST_FAILURE;
    
    data = ZaruGetExpLow();
    /*
     * check that only the bits that should be on are on
     * and that only those bits are on.
     */
    if (data)
	retvalue = GNG_TEST_FAILURE;
	
    ZaruSetExpCommand(ZARU_EXP_CMD_VOLT);
    data = ZaruGetExpLow();
    data &= (ZARU_12V1 | ZARU_3V0 | ZARU_3V1 | ZARU_3V2);   /* some bits unused!!! */
    /*
     * check that only the bits that should be on are on
     * and that only those bits are on.
     */
    if (data ^ (ZARU_12V1 | ZARU_3V0 | ZARU_3V1 | ZARU_3V2))
	retvalue = GNG_TEST_FAILURE;
    
    return retvalue;
}

/*
 * Check that the reset time is in acceptable range
 */
int
ResetTimeTest()
{
    int resettime;
    
    if (!zaruexists)	    /* Assume everything is OK if no Zaru */
	return GNG_TEST_SUCCESS;
    
    resettime = ZaruGetResetTime();
    
    if (resettime >= ZARU_RESET_LOW && resettime <= ZARU_RRESET_HIGH)
	return GNG_TEST_SUCCESS;
    else 
	return GNG_TEST_FAILURE;
}

/*
 * Test Joy ports 2, 3, and 4
 * There is only one switch register.  You cannot write different
 * data values to 2, 3, and 4 and then expect those values to be
 * read back.  Only the data from the last write is available.
 */
int
ControllerTest()
{
    u16 buttons;
    u8 select;
    int i, j;
    char message[256];

    if (!zaruexists)	    /* Assume everything is OK if no Zaru */
	return GNG_TEST_SUCCESS;

    gng_report(
    "Controller test:\nPlease wiggle (shake)\ncontroller inputs\nduring test.\n\nPress yellow button\nto continue...", 
    0, GNG_INHIBIT_PRINT, 0);

    /*
     * Play an alert noise to indicate to the user that they need to press
     * the button.
     */
    playSubway();
    
    while (ZaruGetNextTestButton() == 0) {
	/*
	 * test joy ports 2, 3, and 4.
	 */
	for (i = 2; i < 5; i++) {

        switch (i) {
	    case 2:
		select = ZARU_JOY_SELECT_2;
		break;
		
	    case 3:
		select = ZARU_JOY_SELECT_3;
		break;
		
	    case 4:
		select = ZARU_JOY_SELECT_4;
		break;

	    default:
		sprintf(message, "Controller test:\nillegal controller index %d", i);
		gng_report(message, 0, GNG_INHIBIT_PRINT, 120);
		break;
	    }
	    
	    ZaruSetJoySelect(select);

	    for (j = 0; j < sizeof(controllerdata)/sizeof(u8); j++) {
		ZaruSetJoyButtons(controllerdata[j]);
		if (ZaruButtonCheck(controllerdata[j], ZaruReadControllerButton(i-1))
			== GNG_TEST_FAILURE) {
			
		    sprintf(message, "Controller test:\ncontroller %d no good", i);
		    gng_report(message, 1, GNG_PASS_FAIL_BIT, 0);

		    /*
		     * Not reached.
		     */
		    return GNG_TEST_FAILURE;
		}
	    }
	}
    }
    return GNG_TEST_SUCCESS;
}

/*
 * New functions from uji "checker" program 
 */
/*
 * Import globals from ../testDriver/main.c:
 */
extern OSMesgQueue	dmaMessageQ, rspMessageQ, rdpMessageQ, retraceMessageQ;
extern OSMesg		dmaMessageBuf, rspMessageBuf, rdpMessageBuf, 
			    retraceMessageBuf;
extern OSMesg		dummyMessage;
extern OSIoMesg		dmaIOMessageBuf;

extern char		*staticSegment;

#define AD16BUSTEST 0x12345678

/*
 * Symbols generated by "makerom" to tell us where the static segment is
 * in ROM.
 */
extern char _staticSegmentRomStart[], _staticSegmentRomEnd[];

char ssnRWchk(void){
    volatile u32* ptr0;
    int itmp0,itmp1;
    volatile unsigned long ltmp0;

    ZaruSetADBusCheck(ZARU_ON, 1);
    
    /*
     * Perform 4 reads to AD16 address space
     * (these will be counted by the Zaru)
     */
    ptr0=(u32*)(PHYS_TO_K1(AD16BUSTEST));
    osInvalDCache((void *)ptr0, 4);
    ltmp0=*(ptr0++);
    osInvalDCache((void *)ptr0, 4);
    ptr0=(u32*)(PHYS_TO_K1(AD16BUSTEST));
    ltmp0=*(ptr0++);

    ZaruSetExpCommand(ZARU_EXP_CMD_RW_COUNTS);
    ZaruSetADBusCheck(ZARU_OFF, 0); 
    ZaruSetADBusCheck(ZARU_ON, 1); 

    /*
     * Perform 8 writes to AD16 using DMA (to avoid dcache problems)
     * (these will be counted by the Zaru)
     */
    osPiStartDma(&dmaIOMessageBuf,OS_MESG_PRI_NORMAL,OS_WRITE,
	   (u32)_staticSegmentRomStart,staticSegment,0x10,&dmaMessageQ);
    (void)osRecvMesg(&dmaMessageQ,&dummyMessage,OS_MESG_BLOCK);

    ZaruSetExpCommand(ZARU_EXP_CMD_RW_COUNTS);
    ZaruSetADBusCheck(ZARU_OFF, 0);
    itmp0 = ZaruReadReg(REG_3000);

    return(0x84^itmp0);
}

/*
 * Return values from ssnRWchk
 */
#define MASK_READ  0x000f
#define MASK_WRITE 0x00f0
 
int chk50PReadWrite( ) {

    char state = 0;
    char		message[256];

    if (!zaruexists)	    /* Assume everything is OK if no Zaru */
	return GNG_TEST_SUCCESS;


    state  = ssnRWchk();      /* ^[$B:{Ln$5$s$N%W%m%0%i%`$+$i8!::7k2L$rF@$k^[(B
*/

    if (state) {
	sprintf(message, 
	  "AD16 BUS RW ERROR:\nexpected 0x0\nread 0x%x\n",
	  state);
	gng_report(message, 1, GNG_PASS_FAIL_BIT, 0);
        return GNG_TEST_FAILURE;
    } else {
	return GNG_TEST_SUCCESS;
    }
}

#define AD16_TEST_ADDRESS	0x12345678

/*
 * Check that we are properly generating AD16 addresses on the bottom connector.
 */
int
AD16_LatchedAddressTest()
{
    unsigned int *latchedAddress;
    char message[256];

    if (!zaruexists)	    /* Assume everything is OK if no Zaru */
	return GNG_TEST_SUCCESS;

    latchedAddress = ZaruGetAD16Address((unsigned int *)AD16_TEST_ADDRESS);
    if (latchedAddress == (unsigned int *)AD16_TEST_ADDRESS) {
        return GNG_TEST_SUCCESS;
    } else {
	sprintf(message,
	    "AD16 BUS ADDRESS LATCH ERROR:\nexpected 0x%x\nread 0x%x\n",
	    AD16_TEST_ADDRESS, latchedAddress);
        gng_report(message, 1, GNG_INHIBIT_PRINT, 1200);
        return GNG_TEST_FAILURE;
    }
}
