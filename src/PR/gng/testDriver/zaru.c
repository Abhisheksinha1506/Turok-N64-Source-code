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

/*
 * File:	zaru.c
 * Creator:	scott@sgi.com
 * Purpose:	Code for the Zaru Pitts Memorial test jig.
 *
 */

#define USE_UJI_PIF 1

#include <ultra64.h>
#include "gng.h"
#include "zaru.h"

extern void playSubway(void);

#ifdef USE_UJI_PIF
#include "../uji/uji_pif.h"

SI si1, *si;
#endif

/* Shadowed registers */
static u8 Register2000;
static u8 Register2800;

static OSMesgQueue *siqueue;
static int zaruchannel;
static u8 buffer[BLOCKSIZE];

/*
 * Initialize the Zaru, return 0 on failure, 1 on success
 */
int
ZaruInit(OSMesgQueue *mq, int joychannel)
{
    siqueue = mq;
    zaruchannel = joychannel;
    zaruexists = 1; /* Assume it exists for the first write to MemA */
    
#ifdef USE_UJI_PIF
    si = &si1;
#endif
    /* Use Uji's procedure to write and read 0x55 then 0xaa */
    ZaruSetMemA(0x55);
    if (ZaruGetMemA() == 0x55) {
	ZaruSetMemA(0xaa);
	if (ZaruGetMemA() != 0xaa) {
	    zaruexists = 0;
	    return 0;
	}
    } else {
	zaruexists = 0;
	return 0;
    }
    
    /* more intialization */
    Register2000 = 0;
    Register2800 = 0;
    ZaruWriteReg(REG_2000, Register2000);
    ZaruWriteReg(REG_2800, Register2800);
    
    zaruexists = 1;
    return 1;
}

#ifdef USE_LIBULTRA
/*
 * This code was an attempt to use the PIF routines in libultra.  However, 
 * the libultra routines would have to be modified to add direct access to
 * the rampack.  Currently they only support the filesystem and full checking
 * of the CRCs
 */
 
/*
 * Write data value to the Zaru register.  Use PIF routines to Write to
 * Joy1's "rampack"
 */
s32
ZaruWriteReg(ZARUReg reg, u8 data)
{
    int i;
    s32 retvalue;
    
    for (i = 0; i < BLOCKSIZE; i++)
	buffer[i] = data;
	
PRINTF("ZaruWriteReg calling __osContRamWrite\n");
    retvalue = __osContRamWrite(siqueue, zaruchannel, reg/BLOCKSIZE, buffer, 1);
    
    PRINTF("retvalue of osContRamWrite is 0x%x\n", retvalue);
    
    return retvalue;
}

u8
ZaruReadReg(ZARUReg reg)
{
    int i;
    s32 retvalue;
    
    for (i = 0; i < BLOCKSIZE; i++)
	buffer[i] = 0xff;
PRINTF("ZaruReadReg calling __osContRamRead\n");
	
    retvalue = __osContRamRead(siqueue, zaruchannel, reg/BLOCKSIZE, buffer, 1);

PRINTF("ZaruReadReg returning 0x%x\n", buffer[0]);    
    return buffer[0];
   
}
#endif

#ifdef USE_UJI_PIF
/*
 * Write data value to the Zaru register.  Use PIF routines to Write to
 * Joy1's "rampack"
 */
s32
ZaruWriteReg(ZARUReg reg, u8 data)
{
    int i;

    for(i = 0; i < MAXCONTROLLERS ; i++) {
	if( i == zaruchannel )
	    si->command[i] = CNT_WRITE;
        else
	    si->command[i] = NOP;
    }

    FormatSiBuffer(si);

    SetWritePadRam(si, zaruchannel, reg/BLOCKSIZE);
    for(i = 0 ; i < BLOCKSIZE ; i++)
	RAW_DATA(si,zaruchannel,i+5) = data;
    WriteSi(siqueue,si);
    ReadSi(siqueue,si);

    return 0;

}

u8
ZaruReadReg(ZARUReg reg)
{
    int i;

    InitSi(siqueue, si);

    for(i = 0; i < MAXCONTROLLERS ; i++) {
	if( i == zaruchannel )
	    si->command[i] = CNT_READ;
        else
	    si->command[i] = NOP;
    }

    FormatSiBuffer(si);

    SetReadPadRam(si, zaruchannel, reg/BLOCKSIZE);
    WriteSi(siqueue, si);
    ReadSi(siqueue,si);
    for(i = 0 ; i < BLOCKSIZE ; i++)
	buffer[i]=RAW_DATA(si,zaruchannel,i+5);

    return(RAW_DATA(si,zaruchannel,5));
   
}

u16
ZaruReadControllerButton(int joychannel)
{
    SiContStartReadData(siqueue, si);
    return((RAW_DATA((si),joychannel,4)<<8)+RAW_DATA((si),joychannel,3));
}

#endif	/* USE_UJI_PIF */

/* Set the data in register A. This also controls the LEDs */
void
ZaruSetMemA(u8 data)
{
    if (zaruexists) {
	ZaruWriteReg(REG_0800, data);
    }
}

u8
ZaruGetMemA()
{
    if (zaruexists) {
	return ZaruReadReg(REG_0800);
    } else {
	return 0;
    }
}

/* Set the data in register B. */
void
ZaruSetMemB(u8 data)
{
    if (zaruexists) {
	ZaruWriteReg(REG_1000, data);
    } 
}

u8
ZaruGetMemB()
{
    if (zaruexists) {
	return ZaruReadReg(REG_1000);
    } else {
	return 0;
    }
}

/*
 * Set the data in Joy Switch register.
 * Can read back for buttons on Joy 2, 3 & 4
 * Use ZaruSetJoySelect for joy port number
 */
void
ZaruSetJoyButtons(u8 data)
{
    if (zaruexists) {
	ZaruWriteReg(REG_1800, data);
    }
}

/* 
 * Select Joy channel for setting button bits
 * Changes low order bits for 0x2000
 */
void
ZaruSetJoySelect(u8 data)
{

    if (zaruexists) {
	Register2000 &= ~ZARU_JOY_SELECT_MASK;
	Register2000 |= data;

	ZaruWriteReg(REG_2000, Register2000);
    }
}

/*
 * Set the video standard to either NTSC or PAL
 * Changes D3 in REG_2000.
 */
void
ZaruSetVideoStd(u8 std)
{
    if (zaruexists) {
	Register2000 &= ~ZARU_VIDEO_MASK;
	if (std == ZARU_NTSC) {
	    Register2000 |= ZARU_VIDEO_NTSC;
	}
	ZaruWriteReg(REG_2000, Register2000);
    }
}

/*
 * Set the video source to either SVideo or composite video
 * Changes D4 in REG_2000.
 */
void
ZaruSetVideoSource(u8 source)
{
    if (zaruexists) {
	Register2000 &= ~ZARU_VIDEO_SOURCE_MASK;
	if (source == ZARU_COMPOSITE) {
	    Register2000 |= ZARU_VIDEO_SOURCE_COMPOSITE;
	}
	ZaruWriteReg(REG_2000, Register2000);
    }
}

/*
 * Resart second board in Zaru.  Do this by toggling the restart bit.
 * REG_2000 bit D5
 */
void
ZaruRestartBoard2(void)
{
    if (zaruexists) {
	ZaruWriteReg(REG_2000, Register2000 | ZARU_RESTART_BOARD2);
	ZaruWriteReg(REG_2000, Register2000);
    }
}

/*
 * Set the expansion command.
 * (REG_2800 D0,D1,D2)
 */
void
ZaruSetExpCommand(u8 command)
{
    if (zaruexists) {
	Register2800 &= ~ZARU_EXP_CMD_MASK;
	Register2800 |= command;

	ZaruWriteReg(REG_2800, Register2800);
	ZaruRestartBoard2();
    }
}

/*
 * Return the address AD16 address latched by the Zaru.  Force writes to the AD16
 * interface using the supplied address.
 */
unsigned int *
ZaruGetAD16Address(unsigned int *pAddress)
{
    unsigned int *returnAddress, *cpuAddress, readWord;
    unsigned char nibble0, nibble1, nibble2, nibble3;

    if (zaruexists) {
	cpuAddress = (unsigned int *) ( PHYS_TO_K1(pAddress) );
	readWord = *cpuAddress;

	ZaruSetExpCommand(ZARU_EXP_CMD_UPPER_AD16);
	nibble3 = ZaruGetExpHigh();
	nibble2 = ZaruGetExpLow();

	ZaruSetExpCommand(ZARU_EXP_CMD_LOWER_AD16);
	readWord = *cpuAddress;
	nibble1 = ZaruGetExpHigh();
	nibble0 = ZaruGetExpLow();
	
	returnAddress = (unsigned int *)
	    ( (nibble3 << 24) | (nibble2 << 16) | (nibble1 << 8) | (nibble0) );
	return(returnAddress);
    } else {
	return 0;
    }
}

/*
 * Control the external sound generator.
 * 
 * Changes bits D6 & D7 in REG_2800
 */
void
ZaruSetSound(u8 sound)
{
    if (zaruexists) {
	Register2800 &= ~ZARU_EXP_SOUND_MASK;
	
	if (sound & ZARU_SOUND_R)
	    Register2800 |= ZARU_EXP_SOUND_R;
	    
	if (sound & ZARU_SOUND_L)
	    Register2800 |= ZARU_EXP_SOUND_L;
	
	ZaruWriteReg(REG_2800, Register2800);
	ZaruRestartBoard2();
    }
}

/*
 * Control the Read/Write byte count monitoring of AD16 bus.
 * 
 * Changes bit D3 in REG_2800.
 */
void
ZaruSetADBusCheck(u8 value, int doReset)
{
    if (zaruexists) {
	Register2800 &= ~ZARU_EXP_RDWR_ENABLE;
	if (value == ZARU_ON) {
	    Register2800 |= ZARU_EXP_RDWR_ENABLE;
	}
	ZaruWriteReg(REG_2800, Register2800);
	if (doReset) {
	    ZaruRestartBoard2();
	}
    }
}

/*
 * Get the value of the DIP switch
 */
u8
ZaruGetDIPSwitch()
{
    if (zaruexists) {
	ZaruSetExpCommand(ZARU_EXP_CMD_DIP);
	return ZaruGetExpHigh();
    } else {
	return 0;
    }
}

/*
 * Get the value of the INT1 or CART Interrupt signal
 * on bottom connector.  Is generated from top cartridge.
 * Note that the interrupts to the R4300 are active low.
 * XXX I don't know what the Zaru does with the bit, so check
 * this code.
 */
int
ZaruGetInt1()
{
    if (zaruexists) {
	ZaruSetExpCommand(ZARU_EXP_CMD_INT1);
	if (ZaruGetExpHigh() & ZARU_INT1) {
	    return 1;
	} else {
	    return 0;
	}
    } else {
	return 0;
    }
}
/*
 * Get the value of the reset time.
 */
int
ZaruGetResetTime()
{
    int resettime = 0;

    if (zaruexists) {
	ZaruSetExpCommand(ZARU_EXP_CMD_RESET_TIME);
	resettime =  (ZaruGetExpHigh() << 8) | ZaruGetExpLow();;

	/*
	 * resettime is in units of 256 microseconds; convert to milliseconds.
	 */
	resettime *= 256;	/* convert to microseconds first */
	resettime /= 1000;  /* then convert to milliseconds */
    }
    return resettime;
}

/*
 * Get the power check bits from Register 0x1800
 */
u8
ZaruGetPowerCheck()
{
    if (zaruexists) {
	return ZaruReadReg(REG_1800);
    } else {
	return 0;
    }
}

/*
 * Get the power check bits from Register 0x2000
 */
u8
ZaruGetMisc()
{
    if (zaruexists) {
	return ZaruReadReg(REG_2000);
    } else {
	return 0;
    }
}

/*
 * Get the expansion high bits from 0x2800.
 * Value depends on command programmed with ZaruSetExpCommand()
 */
u8
ZaruGetExpHigh()
{
    if (zaruexists) {
	return ZaruReadReg(REG_2800);
    } else {
	return 0;
    }
}

/*
 * Get the expansion high bits from 0x3000.
 * Value depends on command programmed with ZaruSetExpCommand()
 */
u8
ZaruGetExpLow()
{
    if (zaruexists) {
	return ZaruReadReg(REG_3000);
    } else {
	return 0;
    }
}

/*
 * Return state of Next test button.  This is the Yellow button on the Zaru,
 * or the A button on the controller.
 * 
 * return 1 if button is pushed,  0 if not
 */
int
ZaruGetNextTestButton()
{
    if (zaruexists) {
	if (ZaruGetMisc() & ZARU_MISC_SWITCH)
	    return 0;
	else
	    return 1;
    } else {
	if (readControllerButton(controllerSlot) & CONT_A)
	    return 1;
	else
	    return 0;
    }
}

/*
 * Block until next test button is pushed.
 */
void
ZaruWaitForNextTestButton()
{
    /*
     * Play an alert noise to indicate to the user that they need to press
     * the button.
     */
    playSubway();

    while (1) {
	if ( ZaruGetNextTestButton() == 1 ) {

	    /* 
	     * wait until the next retrace before checking button again 
	     */
	    (void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);

	    /* 
	     * wait for the button to come back up.
	     */
	    while (ZaruGetNextTestButton() == 1) {
		/* wait until next retrace */
		(void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);
	    }
	    return;
	}
	/* 
	 * wait until the next retrace before checking button again 
	 */
	(void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);
    }
}

/*
 * Check that the switch settings for the joy buttons match what is
 * read from the controller
 */
int
ZaruButtonCheck(u8 zaruswitch, u16 buttons)
{
    if (zaruswitch & ZARU_UP_SW) {
	buttons ^= U_CBUTTONS;
    }
    if (zaruswitch & ZARU_DOWN_SW) {
	buttons ^= D_CBUTTONS;
    }
    if (zaruswitch & ZARU_LEFT_SW) {
	buttons ^= L_CBUTTONS;
    }
    if (zaruswitch & ZARU_RIGHT_SW) {
	buttons ^= R_CBUTTONS;
    }
    if (zaruswitch & ZARU_A_SW) {
	buttons ^= 0x0080;	    /* no define for JSRES */
    }
    if (zaruswitch & ZARU_B_SW) {
	buttons ^= 0x0040;	    /* no define for UNUSED */
    }
    if (zaruswitch & ZARU_C_SW) {
	buttons ^= L_JPAD;
    }
    if (zaruswitch & ZARU_D_SW) {
	buttons ^= D_JPAD;
    }
    
    if (buttons != 0) {
	return GNG_TEST_FAILURE;
    } else {
	return GNG_TEST_SUCCESS;
    }
    
}
