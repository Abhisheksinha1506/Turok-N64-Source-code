/**************************************************************************    X
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
 * File:	zaru.h
 * Creator:	scott@sgi.com
 * Purpose:	Definitions for the Zaru Pitts Memorial test jig.
 *
 */

#ifndef _ZARU_H_
#define _ZARU_H_

/*
 * The Zaru test jig is designed to be used in the Go/No Go test for Ultra 64.
 * Various registers are mapped into the Joy Port #1 RAMPACK address space.
 * When writing a Zaru register, the data must be replicated in all 32 bytes of 
 * the RAMPACK page.  Just look at the first byte of the data buffer for reads
 */

typedef enum {
    REG_0800 = 0x0800,
    REG_1000 = 0x1000, 
    REG_1800 = 0x1800, 
    REG_2000 = 0x2000, 
    REG_2800 = 0x2800, 
    REG_3000 = 0x3000
} ZARUReg;

/*		    HARDWARE BITS		    */


/* Register 0x0800 - Memory A 8 bit Read/Write register, drives LED */

/* Register 0x1000 - Memory B 8 bit Read/Write register */

/* Register 0x1800 */
/* Read - Power line check */
#define ZARU_G2			0x01		/* GND of cont 2 0:OK */
#define ZARU_G3			0x02		/* GND of cont 3 0:OK */
#define ZARU_G4			0x04		/* GND of cont 4 0:OK */
#define ZARU_V2			0x08		/* 3.3V of cont 2 1:OK */
#define ZARU_V3			0x10		/* 3.3V of cont 3 1:OK */
#define ZARU_V4			0x20		/* 3.3V of cont 4 1:OK */
#define ZARU_GND1CHK		0x40		/* GND of 12P 1:OK */
#define ZARU_GND2CHK		0x80		/* GND of 12P 1:OK */

/* Write - Switch Check: 8 bits for buttons on controllers */
#define ZARU_UP_SW		0x01
#define ZARU_DOWN_SW		0x02
#define ZARU_LEFT_SW		0x04
#define ZARU_RIGHT_SW		0x08
#define ZARU_A_SW		0x10
#define ZARU_B_SW		0x20
#define ZARU_C_SW		0x40
#define ZARU_D_SW		0x80


/* Register 0x2000 - Signal Select */
/* Read - Misc signals */
#define ZARU_MISC_5VCHKCON	0x01		/* 5V of 1p 1:OK */
#define ZARU_MISC_EUTPOFF	0x02		/* Cont1 ????? */
#define ZARU_MISC_SWITCH	0x04		/* Big Yellow Button 0:on */

/* Write bits */
/* NOTE: The following three lines are not typos */
#define ZARU_JOY_SELECT_2	    0	    /* Select joy channel 2 */
#define ZARU_JOY_SELECT_3	    1	    /* Select joy channel 3 */
#define ZARU_JOY_SELECT_4	    2	    /* Select joy channel 4 */
#define ZARU_JOY_SELECT_MASK	    0x07

#define ZARU_VIDEO_NTSC		    0x08
#define ZARU_VIDEO_PAL		    0x00
#define ZARU_VIDEO_MASK		    0x08

#define ZARU_VIDEO_SOURCE_COMPOSITE 0x10
#define ZARU_VIDEO_SOURCE_SVIDEO    0x00
#define ZARU_VIDEO_SOURCE_MASK	    0x10

#define ZARU_RESTART_BOARD2	    0x20    /* some commands need to toggle */

/* Register 0x2800 - Expansion High */
/* Read bits - depend on what is written to EXP_CMD bits in register 0x2800 */
/* For ZARU_EXP_CMD_GND: */
#define ZARU_GND8		0x01	    /* 0:OK, 1:no good */
#define ZARU_GND9		0x02	    /* 0:OK, 1:no good */
#define ZARU_GND10		0x04	    /* 0:OK, 1:no good */
#define ZARU_GND11		0x08	    /* 0:OK, 1:no good */
#define ZARU_SEC1   		0x10	    /* 1:OK, 0:no good */
#define ZARU_SEC2   		0x20	    /* 1:OK, 0:no good */
#define ZARU_CCLK   		0x40	    /* 1:OK, 0:no good */
#define ZARU_CSYNC   		0x80	    /* 1:OK, 0:no good */

/* For ZARU_EXP_CMD_DIP: */
/*	an 8 bit dip switch: bottommost two bits denote expected memory size */
#define ZARU_4MB		0x0
#define ZARU_6MB		0x1
#define ZARU_8MB		0x2

/* For ZARU_EXP_CMD_UPPER_AD16: */
/*	Upper 8 bits of upper half of ADBUS */

/* For ZARU_EXP_CMD_LOWER_AD16: */
/*	Lower 8 bits of upper half of ADBUS */

/* For ZARU_EXP_CMD_INT1: */
#define ZARU_INT1		0x80	    /* 1:OK, 0:no good */

/* For ZARU_EXP_CMD_RESET_TIME: */
/*	upper half of Reset time */

/* Write bits - 0x2800 - Expansion Select */
/* All writes to 0x2800 must be followed by a ZaruRestartBoard2() */
#define ZARU_EXP_CMD_GND	    0
#define ZARU_EXP_CMD_DIP	    1
#define ZARU_EXP_CMD_VOLT	    1
#define ZARU_EXP_CMD_UPPER_AD16	    2 
#define ZARU_EXP_CMD_LOWER_AD16	    3
#define ZARU_EXP_CMD_INT1	    4
#define ZARU_EXP_CMD_RW_COUNTS	    4
#define ZARU_EXP_CMD_RESET_TIME	    5
#define ZARU_EXP_CMD_RESERVED	    6
#define ZARU_EXP_CMD_NOOP	    7
#define ZARU_EXP_CMD_MASK	    0x07

#define ZARU_EXP_RDWR_ENABLE	    0x08    /* !enable R/W check of AD16 */
#define ZARU_EXP_SOUND_L	    0x40
#define ZARU_EXP_SOUND_R	    0x80
#define ZARU_EXP_SOUND_MASK	    0xc0

/* lowest value for combined reset value = 15 ms */
#define ZARU_RESET_LOW		    15
/* highest value for combined reset value = 480 ms */
#define	ZARU_RRESET_HIGH	    480

/* Register 0x3000 - Expansion Low (Read Only) */
/* Read bits - depend on what is written to EXP_CMD bits in register 0x2800 */
/* For ZARU_EXP_CMD_GND: */
#define ZARU_GND0		0x01	    /* 0:OK, 1:no good */
#define ZARU_GND1		0x02	    /* 0:OK, 1:no good */
#define ZARU_GND2		0x04	    /* 0:OK, 1:no good */
#define ZARU_GND3		0x08	    /* 0:OK, 1:no good */
#define ZARU_GND4		0x10	    /* 0:OK, 1:no good */
#define ZARU_GND5		0x20	    /* 0:OK, 1:no good */
#define ZARU_GND6		0x40	    /* 0:OK, 1:no good */
#define ZARU_GND7		0x80	    /* 0:OK, 1:no good */

/* For ZARU_EXP_CMD_VOLT: */
#define ZARU_12V1		0x02	    /* 12V >= 10V 1:OK, 0:no good */
#define ZARU_3V0		0x08	    /* 3.3V 1:OK, 0:no good */
#define ZARU_3V1		0x10	    /* 3.3V 1:OK, 0:no good */
#define ZARU_3V2		0x20	    /* 3.3V 1:OK, 0:no good */

/* For ZARU_EXP_CMD_UPPER_AD16: */
/*	Upper 8 bits of lower half of ADBUS */

/* For ZARU_EXP_CMD_LOWER_AD16: */
/*	Lower 8 bits of lower half of ADBUS */

/* For ZARU_EXP_CMD_RW_COUNTS: */
#define ZARU_READ_BYTES_SHIFT	0
#define ZARU_WRITE_BYTES_SHIFT	4
#define ZARU_RW_BYTES_MASK	0x0f

/* Zaru function prototypes: */

/* lowest level (interfaces to PIF code) */
extern s32 ZaruWriteReg(ZARUReg, u8);
extern u8  ZaruReadReg(ZARUReg);
extern u16 ZaruReadControllerButton(int);

/* middle level */
extern void ZaruSetMemA(u8);		    /* REG_0800, also LED */
extern void ZaruSetMemB(u8);		    /* REG_1000 */
extern void ZaruSetJoyButtons(u8);	    /* REG_1800 */
extern void ZaruSetJoySelect(u8);	    /* REG_2000 D0, D1, & D2 */
extern void ZaruSetVideoStd(u8);	    /* REG_2000 D3 */
extern void ZaruSetVideoSource(u8);	    /* REG_2000 D4 */
extern void ZaruRestartBoard2(void);	    /* REG_2000 D5 */
extern void ZaruSetExpCommand(u8);	    /* REG_2800 D0,D1,D2 */
extern void ZaruSetADBusCheck(u8, int);	    /* REG_2800 D3 */
extern void ZaruSetSound(u8);		    /* REG_2800 D6, D7 */
extern u8   ZaruGetMemA(void);		    /* REG_0800 */
extern u8   ZaruGetMemB(void);		    /* REG_1000 */
extern u8   ZaruGetPowerCheck(void);	    /* REG_1800 */
extern u8   ZaruGetMisc(void);		    /* REG_2000 */
extern u8   ZaruGetExpHigh(void);	    /* REG_2800 */
extern u8   ZaruGetExpLow(void);	    /* REG_3000 */

/* Highest level */
extern int  ZaruInit(OSMesgQueue *, int);
extern int  ZaruGetNextTestButton(void);	/* 1 if pushed, 0 if not */
extern void ZaruWaitForNextTestButton(void);    /* block for button push */
extern int  ZaruGetResetTime(void);
extern u8   ZaruGetDIPSwitch(void);
extern int  ZaruButtonCheck(u8, u16);
extern int  ZaruGetInt1(void);
extern unsigned int *
	    ZaruGetAD16Address(unsigned int *pAddress);

/* Zaru function arguments: */
/* ZaruSetADBusCheck(), ... */
#define ZARU_OFF	    0
#define ZARU_ON		    1

/* For ZaruSetVideoStd() */
#define ZARU_NTSC	    0
#define ZARU_PAL	    1

/* For ZaruSetVideoSource() */
#define ZARU_SVIDEO	    0
#define ZARU_COMPOSITE	    1


/* For ZaruSetSound() */
#define ZARU_SOUND_OFF	    0
#define ZARU_SOUND_R	    1
#define ZARU_SOUND_L	    2
#define ZARU_SOUND_LR	    3

#endif /* _ZARU_H_ */
