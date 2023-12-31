
/*====================================================================
 * os.h
 *
 * Copyright 1995, Silicon Graphics, Inc.
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

/**************************************************************************
 *
 *  $Revision: 1.1 $
 *  $Date: 1996/02/29 05:21:41 $
 *  $Source: /mdev2/PR/apps.released/gng/cpu/user/RCS/nos.h,v $
 *
 **************************************************************************/


#ifndef _OS_H_
#define	_OS_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/ultratypes.h>

#ifdef _LANGUAGE_C

/**************************************************************************
 *
 * Type definitions
 *
 */

typedef s32	OSPri;
typedef s32	OSId;
typedef union	{ struct { f32 f_odd; f32 f_even; } f; f64 d; }	__OSfp;

typedef struct {
	u64	at, v0, v1, a0, a1, a2, a3;
	u64	t0, t1, t2, t3, t4, t5, t6, t7;
	u64	s0, s1, s2, s3, s4, s5, s6, s7;
	u64	t8, t9,         gp, sp, s8, ra;
	u64	lo, hi;
	u32	sr, pc, cause, badvaddr, rcp;
	u32	fpcsr;
	__OSfp	 fp0,  fp2,  fp4,  fp6,  fp8, fp10, fp12, fp14;
	__OSfp	fp16, fp18, fp20, fp22, fp24, fp26, fp28, fp30;
} __OSThreadContext;

typedef struct OSThread_s {
	struct OSThread_s	*next;		/* run/mesg queue link */
	OSPri			priority;	/* run/mesg queue priority */
	struct OSThread_s	**queue;	/* queue thread is on */
	struct OSThread_s	*tlnext;	/* all threads queue link */
	u16			state;		/* OS_STATE_* */
	u16			flags;		/* flags for rmon */
	OSId			id;		/* id for debugging */
	int			fp;		/* thread has used fp unit */
	__OSThreadContext	context;	/* register/interrupt mask */
} OSThread;

typedef u32 OSEvent;
typedef u32 OSIntMask;
typedef u32 OSPageMask;

/*
 * Structure for message
 */
typedef void *	OSMesg;

/*
 * Structure for message queue
 */
typedef struct OSMesgQueue_s {
	OSThread	*mtqueue;	/* Queue to store threads blocked
					   on empty mailboxes (receive) */
	OSThread	*fullqueue;	/* Queue to store threads blocked
					   on full mailboxes (send) */
	s32		validCount;	/* Contains number of valid message */
	s32		first;		/* Points to first valid message */
	s32		msgCount;	/* Contains total # of messages */
	OSMesg		*msg;		/* Points to message buffer array */
} OSMesgQueue;

/*
 * Structure for I/O message block
 */
typedef struct {
        u16 		type;		/* Message type */
        u8 		pri;		/* Message priority (High or Normal) */
        u8		status;		/* Return status */
	OSMesgQueue	*retQueue;	/* Return message queue to notify I/O 
					 * completion */
} OSIoMesgHdr;

typedef struct {
	OSIoMesgHdr	hdr;		/* Message header */
	void *		dramAddr;	/* RDRAM buffer address (DMA) */
	u32		devAddr;	/* Device buffer address (DMA) */
	u32 		size;		/* DMA transfer size in bytes */
} OSIoMesg;

/*
 * Structure for device manager block
 */
typedef struct {
        s32             active;		/* Status flag */
	OSThread	*thread;	/* Calling thread */
        OSMesgQueue  	*cmdQueue;	/* Command queue */
        OSMesgQueue  	*evtQueue;	/* Event queue */
        OSMesgQueue  	*acsQueue;	/* Access queue */
					/* Raw DMA routine */
        s32             (*dma)(s32, u32, void *, u32);
} OSDevMgr;


/*
 * Structure to store VI register values that remain the same between 2 fields
 */
typedef struct {
    u32	ctrl;
    u32	width;
    u32	burst;
    u32	vSync;
    u32	hSync;
    u32	leap;
    u32	hStart;
    u32	xScale;
    u32	vCurrent;
} OSViCommonRegs;


/*
 * Structure to store VI register values that change between fields
 */
typedef struct {
    u32	origin;
    u32	yScale;
    u32	vStart;	
    u32	vBurst;
    u32	vIntr;
} OSViFieldRegs;


/*
 * Structure for VI mode
 */
typedef struct {
    u8			type;		/* Mode type */
    OSViCommonRegs	comRegs;	/* Common registers for both fields */
    OSViFieldRegs	fldRegs[2];	/* Registers for Field 1  & 2 */
} OSViMode;

/*
 * Structure for time value 
 */
typedef u64	OSTime;

/*
 * Structure for interval timer
 */
typedef struct OSTimer_s {
	struct OSTimer_s	*next;	/* point to next timer in list */
	struct OSTimer_s	*prev;	/* point to previous timer in list */
	OSTime			interval;	/* duration set by user */
	OSTime			value;		/* time remaining before */
						/* timer fires           */
	OSMesgQueue		*mq;		/* Message Queue */
	OSMesg			msg;		/* Message to send */
} OSTimer;

/*
 * Structure for controllers 
 */

typedef struct {
	u16     type;                   /* Controller Type */
	u8      status;                 /* Controller status */
	u8	errno;
}OSContStatus;

typedef struct {
	u16     button;
	s8      stick_x;		/* -80 <= stick_x <= 80 */
	s8      stick_y;		/* -80 <= stick_y <= 80 */
	u8	errno;
} OSContPad;

typedef struct {
	void    *address;               /* Ram pad Address:  11 bits */
	u8      databuffer[32];         /* address of the data buffer */
        u8      addressCrc;             /* CRC code for address */
	u8      dataCrc;                /* CRC code for data */
	u8	errno;
} OSContRamIo;

/*
 * Structure for file system
 */



typedef struct {
	int		status;
	OSMesgQueue 	*queue;
	int		channel;
	u8		id[32];
	u8		backup_id[32];
	u8		label[32];
	int		pack_size;
	int		version;
	int		dir_size;
	int		inode_start_page;
} OSPfs;


typedef struct {
	u32	file_size;	/* bytes */
  	u16 	company_code;
  	u16 	game_code;
  	char  	ext_name[4];
  	char 	game_name[16];
} OSPfsState;
	
/*
 * Structure for Profiler 
 */
typedef struct {
	u16	*histo_base;		/* histogram base */
	u32	histo_size;		/* histogram size */
	u32	*text_start;		/* start of text segment */
	u32	*text_end;		/* end of text segment */
} OSProf;

#endif /* _LANGUAGE_C */

/**************************************************************************
 *
 * Global definitions
 *
 */

/* Thread states */

#define OS_STATE_STOPPED	1
#define OS_STATE_RUNNABLE	2
#define OS_STATE_RUNNING	4
#define OS_STATE_WAITING	8

/* Events */

#define	OS_NUM_EVENTS		16

#define	OS_EVENT_SW1		0	/* CPU SW1 interrupt */
#define	OS_EVENT_SW2		1	/* CPU SW2 interrupt */
#define	OS_EVENT_CART		2	/* Cartridge interrupt: used by rmon */
#define	OS_EVENT_COUNTER	3	/* Counter int: used by VI/Timer Mgr */
#define	OS_EVENT_SP		4	/* SP task done interrupt */
#define	OS_EVENT_SI		5	/* SI (controller) interrupt */
#define	OS_EVENT_AI		6	/* AI interrupt */
#define	OS_EVENT_VI		7	/* VI interrupt: used by VI/Timer Mgr */
#define	OS_EVENT_PI		8	/* PI interrupt: used by PI Manager */
#define	OS_EVENT_DP		9	/* DP full sync interrupt */
#define	OS_EVENT_CPU_BREAK	10	/* CPU breakpoint: used by rmon */
#define OS_EVENT_SP_BREAK	11	/* SP breakpoint:  used by rmon */
#define OS_EVENT_FAULT		12	/* CPU fault event: used by rmon */
#define OS_EVENT_THREADSTATUS	13	/* CPU thread status: used by rmon */
#define OS_EVENT_PRENMI		14	/* Pre NMI interrupt */
#define OS_EVENT_RDB_READ_OK	15	/* RDB read ok event: used by rmon */

#if 0
#define OS_EVENT_SYSCALL	16	/* System call event */
#define OS_EVENT_TLB_REFILL	17	/* TLB miss: refill */
#define OS_EVENT_TLB_INV	18	/* TLB miss: invalid */
#define OS_EVENT_TLB_MOD	19	/* TLB miss: modified */
#define OS_EVENT_ADDR_ERROR	20	/* Address error - instruction fetch */
#define OS_EVENT_BUS_ERROR	21	/* Bus error - instruction fetch */
#define OS_EVENT_WATCH		22	/* Watch point */
#endif

/* Interrupt masks */

#define	OS_IM_NONE	0x00000001
#define	OS_IM_SW1	0x00000501
#define	OS_IM_SW2	0x00000601
#define	OS_IM_CART	0x00000c01
#define	OS_IM_PRENMI	0x00001401
#define OS_IM_RDBWRITE	0x00002401
#define OS_IM_RDBREAD	0x00004401
#define	OS_IM_COUNTER	0x00008401
#define	OS_IM_CPU	0x0000ff01
#define	OS_IM_SP	0x00010401
#define	OS_IM_SI	0x00020401
#define	OS_IM_AI	0x00040401
#define	OS_IM_VI	0x00080401
#define	OS_IM_PI	0x00100401
#define	OS_IM_DP	0x00200401
#define	OS_IM_ALL	0x003fff01
#define	RCP_IMASK	0x003f0000
#define	RCP_IMASKSHIFT	16

/* Recommended thread priorities for the system threads */

#define OS_PRIORITY_MAX		255
#define OS_PRIORITY_VIMGR	254
#define OS_PRIORITY_RMON	250
#define OS_PRIORITY_RMONSPIN	200
#define OS_PRIORITY_PIMGR	150
#define OS_PRIORITY_SIMGR	140
#define	OS_PRIORITY_APPMAX	127
#define OS_PRIORITY_IDLE	  0	/* Must be 0 */


/* Flags to turn blocking on/off when sending/receiving message */

#define	OS_MESG_NOBLOCK		0
#define	OS_MESG_BLOCK		1

/* Flags to indicate direction of data transfer */

#define	OS_READ			0		/* device -> RDRAM */
#define	OS_WRITE		1		/* device <- RDRAM */

/*
 * I/O message types
 */
#define OS_MESG_TYPE_BASE	(10)
#define OS_MESG_TYPE_LOOPBACK	(OS_MESG_TYPE_BASE+0)
#define OS_MESG_TYPE_DMAREAD	(OS_MESG_TYPE_BASE+1)
#define OS_MESG_TYPE_DMAWRITE	(OS_MESG_TYPE_BASE+2)
#define OS_MESG_TYPE_VRETRACE	(OS_MESG_TYPE_BASE+3)
#define OS_MESG_TYPE_COUNTER	(OS_MESG_TYPE_BASE+4)

/*
 * I/O message priority
 */
#define OS_MESG_PRI_NORMAL	0
#define OS_MESG_PRI_HIGH	1

/*
 * Page size argument for TLB routines
 */
#define OS_PM_4K	0x0000000
#define OS_PM_16K	0x0006000
#define OS_PM_64K	0x001e000
#define OS_PM_256K	0x007e000
#define OS_PM_1M	0x01fe000
#define OS_PM_4M	0x07fe000
#define OS_PM_16M	0x1ffe000

/*
 * Stack size for I/O device managers: PIM (PI Manager), VIM (VI Manager),
 *	SIM (SI Manager)
 *
 */
#define OS_PIM_STACKSIZE	4096
#define OS_VIM_STACKSIZE	4096
#define OS_SIM_STACKSIZE	4096

#define	OS_MIN_STACKSIZE	72

/*
 * Video Interface (VI) mode type
 */
#define OS_VI_NTSC_LPN1		0
#define OS_VI_NTSC_LPF1		1
#define OS_VI_NTSC_LAN1		2
#define OS_VI_NTSC_LAF1		3
#define OS_VI_NTSC_LPN2		4
#define OS_VI_NTSC_LPF2		5
#define OS_VI_NTSC_LAN2		6
#define OS_VI_NTSC_LAF2		7
#define OS_VI_NTSC_HPN1		8
#define OS_VI_NTSC_HPF1		9
#define OS_VI_NTSC_HAN1		10
#define OS_VI_NTSC_HAF1		11
#define OS_VI_NTSC_HPN2		12
#define OS_VI_NTSC_HPF2		13
#define OS_VI_PAL_LPN1		14
#define OS_VI_PAL_LPF1		15
#define OS_VI_PAL_LAN1		16
#define OS_VI_PAL_LAF1		17
#define OS_VI_PAL_LPN2		18
#define OS_VI_PAL_LPF2		19
#define OS_VI_PAL_LAN2		20
#define OS_VI_PAL_LAF2		21
#define OS_VI_PAL_HPN1		22
#define OS_VI_PAL_HPF1		23
#define OS_VI_PAL_HAN1		24
#define OS_VI_PAL_HAF1		25
#define OS_VI_PAL_HPN2		26
#define OS_VI_PAL_HPF2		27

/*
 * Video Interface (VI) special features
 */
#define	OS_VI_GAMMA_ON			0x0001
#define	OS_VI_GAMMA_OFF			0x0002
#define	OS_VI_GAMMA_DITHER_ON		0x0004
#define	OS_VI_GAMMA_DITHER_OFF		0x0008
#define	OS_VI_DIVOT_ON			0x0010
#define	OS_VI_DIVOT_OFF			0x0020
#define	OS_VI_DITHER_FILTER_ON		0x0040
#define	OS_VI_DITHER_FILTER_OFF		0x0080

/*
 * Video Interface (VI) mode attribute bit
 */
#define OS_VI_BIT_NONINTERLACE		0x0001          /* lo-res */
#define OS_VI_BIT_INTERLACE		0x0002          /* lo-res */
#define OS_VI_BIT_NORMALINTERLACE	0x0004          /* hi-res */
#define OS_VI_BIT_DEFLICKINTERLACE	0x0008          /* hi-res */
#define OS_VI_BIT_ANTIALIAS		0x0010
#define OS_VI_BIT_POINTSAMPLE		0x0020
#define OS_VI_BIT_16PIXEL		0x0040
#define OS_VI_BIT_32PIXEL		0x0080
#define OS_VI_BIT_LORES			0x0100
#define OS_VI_BIT_HIRES			0x0200
#define OS_VI_BIT_NTSC			0x0400
#define OS_VI_BIT_PAL			0x0800

/*
 *  Controllers  number
 */

#ifndef _HW_VERSION_1
#define MAXCONTROLLERS  4
#else
#define MAXCONTROLLERS  6
#endif

/* controller errors */
#define CONT_NO_RESPONSE_ERROR          0x8
#define CONT_OVERRUN_ERROR              0x4
#ifdef _HW_VERSION_1
#define CONT_FRAME_ERROR                0x2
#define CONT_COLLISION_ERROR            0x1
#endif 

/* Controller type */

#define CONT_ABSOLUTE           0x0001
#define CONT_RELATIVE           0x0002
#define CONT_JOYPORT            0x0004
#define CONT_EEPROM		0x8000

/* Controller status */

#define CONT_CARD_ON            0x01
#define CONT_CARD_PULL          0x02
#define CONT_ADDR_CRC_ER        0x04
#define CONT_EEPROM_BUSY	0x80

/* Buttons */

#define CONT_A      0x8000
#define CONT_B      0x4000
#define CONT_G	    0x2000
#define CONT_START  0x1000
#define CONT_UP     0x0800
#define CONT_DOWN   0x0400
#define CONT_LEFT   0x0200
#define CONT_RIGHT  0x0100
#define CONT_L      0x0020
#define CONT_R      0x0010
#define CONT_E      0x0008
#define CONT_D      0x0004
#define CONT_C      0x0002
#define CONT_F      0x0001

/* Nintendo's official buttons name */

#define A_BUTTON	CONT_A
#define B_BUTTON	CONT_B
#define L_TRIG		CONT_L
#define R_TRIG		CONT_R
#define Z_TRIG		CONT_G
#define START_BUTTON	CONT_START
#define U_JPAD		CONT_UP
#define L_JPAD		CONT_LEFT
#define R_JPAD		CONT_RIGHT
#define D_JPAD		CONT_DOWN
#define U_CBUTTONS	CONT_E
#define L_CBUTTONS	CONT_C
#define R_CBUTTONS	CONT_F
#define D_CBUTTONS	CONT_D

/* File System size */

#define PFS_FILE_NAME_LEN       16
#define PFS_FILE_EXT_LEN        4
#define BLOCKSIZE		32		/* bytes */
#define PFS_ONE_PAGE            8		/* blocks */
#define PFS_MAX_FILE_SIZE       BLOCKSIZE*PFS_ONE_PAGE*128	/* bytes */

/* File System flag */

#define PFS_READ                0
#define PFS_WRITE               1
#define PFS_CREATE              2

/* File System error number */

#define PFS_ERR_NOPACK		1	/* no memory card is plugged or   */
#define PFS_ERR_NEW_PACK        2	/* ram pack has been changed to a */
					/* different one 		  */
#define PFS_ERR_INCONSISTENT    3	/* need to run Pfschecker 	  */
#define PFS_ERR_CONTRFAIL	CONT_OVERRUN_ERROR              
#define PFS_ERR_INVALID         5	/* invalid parameter or file not exist*/
#define PFS_ERR_BAD_DATA        6       /* the data read from pack are bad*/
#define PFS_DATA_FULL           7	/* no free pages on ram pack      */
#define PFS_DIR_FULL            8	/* no free directories on ram pack*/
#define PFS_ERR_EXIST		9	/* file exists 			  */
#define PFS_ERR_ILLEGAL_PACK	10	/* illegal ram pack */

/* definition for EEPROM */

#define EEPROM_MAXBLOCKS	64
#define EEPROM_BLOCK_SIZE	8

/*
 * Profiler constants
 */
#define PROF_MIN_INTERVAL	50	/* microseconds */

/*
 * Boot addresses
 */
#define	BOOT_ADDRESS_ULTRA	0x80000400
#define	BOOT_ADDRESS_COSIM	0x80002000
#define	BOOT_ADDRESS_EMU	0x20010000
#define	BOOT_ADDRESS_INDY 	0x88100000

#ifdef _LANGUAGE_C

/**************************************************************************
 *
 * Macro definitions
 *
 */

/* Get count of valid messages in queue */
#define MQ_GET_COUNT(mq)        ((mq)->validCount)

/* Figure out if message queue is empty or full */
#define MQ_IS_EMPTY(mq)		(MQ_GET_COUNT(mq) == 0)
#define MQ_IS_FULL(mq)		(MQ_GET_COUNT(mq) >= (mq)->msgCount)

/*
 * CPU counter increments at 3/4 of bus clock rate:
 *
 * Bus Clock	Proc Clock	Counter (1/2 Proc Clock)
 * ---------	----------	------------------------
 * 62.5 Mhz	93.75 Mhz	46.875 Mhz
 */
extern u64 osClockRate;

#define OS_NSEC_TO_CYCLES(n)	(((u64)(n)*(osClockRate))/1000000000LL)
#define OS_USEC_TO_CYCLES(n)	(((u64)(n)*(osClockRate))/1000000LL)
#define OS_CYCLES_TO_NSEC(c)	(((u64)(c)*1000000000LL)/(osClockRate))
#define OS_CYCLES_TO_USEC(c)	(((u64)(c)*1000000LL)/(osClockRate))


/**************************************************************************
 *
 * Extern variables
 *
 */
extern OSViMode	osViModeTable[];	/* Global VI mode table */

extern OSViMode	osViModeNtscLpn1;	/* Individual VI NTSC modes */
extern OSViMode	osViModeNtscLpf1;
extern OSViMode	osViModeNtscLan1;
extern OSViMode	osViModeNtscLaf1;
extern OSViMode	osViModeNtscLpn2;
extern OSViMode	osViModeNtscLpf2;
extern OSViMode	osViModeNtscLan2;
extern OSViMode	osViModeNtscLaf2;
extern OSViMode	osViModeNtscHpn1;
extern OSViMode	osViModeNtscHpf1;
extern OSViMode	osViModeNtscHan1;
extern OSViMode	osViModeNtscHaf1;
extern OSViMode	osViModeNtscHpn2;
extern OSViMode	osViModeNtscHpf2;

extern OSViMode	osViModePalLpn1;	/* Individual VI PAL modes */
extern OSViMode	osViModePalLpf1;
extern OSViMode	osViModePalLan1;
extern OSViMode	osViModePalLaf1;
extern OSViMode	osViModePalLpn2;
extern OSViMode	osViModePalLpf2;
extern OSViMode	osViModePalLan2;
extern OSViMode	osViModePalLaf2;
extern OSViMode	osViModePalHpn1;
extern OSViMode	osViModePalHpf1;
extern OSViMode	osViModePalHan1;
extern OSViMode	osViModePalHaf1;
extern OSViMode	osViModePalHpn2;
extern OSViMode	osViModePalHpf2;

extern s32 	osRomType;	/* Bulk or cartridge ROM. 0=cartridge 1=bulk */
extern void 	*osRomBase;	/* Rom base address of the game image */
extern s32 	osTvType;	/* 0 = standard PAL, 1 = standard NTSC */
extern s32 	osResetType;	/* 0 = cold reset, 1 = NMI */
extern s32 	osCicId;
extern s32 	osVersion;
extern u32	osMemSize;	/* Memory Size */


/**************************************************************************
 *
 * Function prototypes
 *
 */

/* Thread operations */

extern void		nosCreateThread(OSThread *, OSId, void (*)(void *),
				       void *, void *, OSPri);
extern void		nosDestroyThread(OSThread *);
extern void		nosYieldThread(void);
extern void		nosStartThread(OSThread *);
extern void		nosStopThread(OSThread *);
extern OSId		nosGetThreadId(OSThread *);
extern void		nosSetThreadPri(OSThread *, OSPri);
extern OSPri		nosGetThreadPri(OSThread *);

/* Message operations */

extern void		nosCreateMesgQueue(OSMesgQueue *, OSMesg *, s32);
extern s32		nosSendMesg(OSMesgQueue *, OSMesg, s32);
extern s32		nosJamMesg(OSMesgQueue *, OSMesg, s32);
extern s32		nosRecvMesg(OSMesgQueue *, OSMesg *, s32);

/* Event operations */

extern void		nosSetEventMesg(OSEvent, OSMesgQueue *, OSMesg);

/* Interrupt operations */

extern OSIntMask	nosGetIntMask(void);
extern OSIntMask	nosSetIntMask(OSIntMask);

/* Cache operations and macros */

extern void		nosInvalDCache(void *, s32);
extern void		nosInvalICache(void *, s32);
extern void		nosWritebackDCache(void *, s32);
extern void		nosWritebackDCacheAll(void);

#define	OS_DCACHE_ROUNDUP_ADDR(x)	(void *)(((((u32)(x)+0xf)/0x10)*0x10))
#define	OS_DCACHE_ROUNDUP_SIZE(x)	(u32)(((((u32)(x)+0xf)/0x10)*0x10))

/* TLB management routines */

extern void		nosMapTLB(s32, OSPageMask, void *, u32, u32, s32);
extern void		nosMapTLBRdb(void);
extern void		nosUnmapTLB(s32);
extern void		nosUnmapTLBAll(void);
extern void		nosSetTLBASID(s32);

/* Address translation routines and macros */

extern u32		 nosVirtualToPhysical(void *);
extern void *		 nosPhysicalToVirtual(u32);

#define	OS_K0_TO_PHYSICAL(x)	(u32)(((char *)(x)-0x80000000))
#define	OS_K1_TO_PHYSICAL(x)	(u32)(((char *)(x)-0xa0000000))

#define	OS_PHYSICAL_TO_K0(x)	(void *)(((u32)(x)+0x80000000))
#define	OS_PHYSICAL_TO_K1(x)	(void *)(((u32)(x)+0xa0000000))

/* I/O operations */

/* Audio interface (Ai) */
extern u32 		nosAiGetStatus(void);
extern u32 		nosAiGetLength(void);
extern s32		nosAiSetFrequency(u32);
extern s32		nosAiSetNextBuffer(void *, u32);

/* Display processor interface (Dp) */
extern u32 		nosDpGetStatus(void);
extern void		nosDpSetStatus(u32);
extern void 		nosDpGetCounters(u32 *);
extern s32		nosDpSetNextBuffer(void *, u64);

/* Peripheral interface (Pi) */
extern u32 		nosPiGetStatus(void);
extern s32		nosPiGetDeviceType(void);
extern s32		nosPiRawWriteIo(u32, u32);
extern s32		nosPiRawReadIo(u32, u32 *);
extern s32		nosPiRawStartDma(s32, u32, void *, u32);
extern s32		nosPiWriteIo(u32, u32);
extern s32		nosPiReadIo(u32, u32 *);
extern s32		nosPiStartDma(OSIoMesg *, s32, s32, u32, void *, u32,
				     OSMesgQueue *);
extern void		nosCreatePiManager(OSPri, OSMesgQueue *, OSMesg *, s32);

/* Video interface (Vi) */
extern u32		nosViGetStatus(void);
extern u32		nosViGetCurrentMode(void);
extern u32		nosViGetCurrentLine(void);
extern u32		nosViGetCurrentField(void);
extern void		*nosViGetCurrentFramebuffer(void);
extern void		*nosViGetNextFramebuffer(void);
extern void		nosViSetXScale(f32);
extern void		nosViSetYScale(f32);
extern void		nosViSetSpecialFeatures(u32);
extern void		nosViSetMode(OSViMode *);
extern void		nosViSetEvent(OSMesgQueue *, OSMesg, u32);
extern void		nosViSwapBuffer(void *);
extern void		nosViBlack(u8);
extern void		nosViFade(u8, u16);
extern void		nosRepeatLine(u8);
extern void		nosCreateViManager(OSPri);

/* Timer interface */

extern OSTime		nosGetTime(void);
extern void		nosSetTime(OSTime);
extern int		nosSetTimer(OSTimer *, OSTime, OSTime,
				   OSMesgQueue *, OSMesg);
extern int		nosStopTimer(OSTimer *);

/* Controller interface */

extern s32		nosContInit(OSMesgQueue *, u8 *, OSContStatus *);
extern s32		nosContReset(OSMesgQueue *, OSContStatus *);
extern s32		nosContStartQuery(OSMesgQueue *);
extern s32		nosContStartReadData(OSMesgQueue *);
#ifndef _HW_VERSION_1
extern s32		nosContSetCh(u8);
#endif
extern void		nosContGetQuery(OSContStatus *);
extern void		nosContGetReadData(OSContPad *);

/* file system interface */

extern s32 nosPfsInit(OSMesgQueue *, OSPfs *, int);
extern s32 nosPfsReFormat(OSPfs *, OSMesgQueue *, int);
extern s32 nosPfsChecker(OSPfs *);
extern s32 nosPfsAllocateFile(OSPfs *, u16, u16, u8 *, u8 *, int, s32 *);
extern s32 nosPfsFindFile(OSPfs *, u16, u16, u8 *, u8 *, s32 *);
extern s32 nosPfsDeleteFile(OSPfs *, u16, u16, u8 *, u8 *);
extern s32 nosPfsReadWriteFile(OSPfs *, s32, u8, int, int, u8 *);
extern s32 nosPfsFileState(OSPfs *, s32, OSPfsState *);
extern s32 nosPfsGetLabel(OSPfs *, u8 *, int *);
extern s32 nosPfsSetLabel(OSPfs *, u8 *);
extern s32 nosPfsIsPlug(OSMesgQueue *, u8 *);
extern s32 nosPfsFreeBlocks(OSPfs *, s32 *);
extern s32 nosPfsNumFiles(OSPfs *, s32 *, s32 *);
extern s32 nosPfsReSizeFile(OSPfs *, u16 , u16 , u8 *, u8 *, int);

/* EEPROM interface */

extern s32 nosEepromProbe(OSMesgQueue *);
extern s32 nosEepromRead(OSMesgQueue *, u8, u8 *);
extern s32 nosEepromWrite(OSMesgQueue *, u8, u8 *);
extern s32 nosEepromLongRead(OSMesgQueue *, u8, u8 *, int);
extern s32 nosEepromLongWrite(OSMesgQueue *, u8, u8 *, int);

/* Profiler Interface */

extern void		nosProfileInit(OSProf *, u32 profcnt);
extern void		nosProfileStart(u32);
extern void		nosProfileFlush(void);
extern void		nosProfileStop(void);

/* Game <> Host data transfer functions */

extern s32		nosTestHost(void);
extern void		nosReadHost(void *, s32);
extern void		nosWriteHost(void *, s32);

/* Miscellaneous operations */

extern void		nosInitialize(void);
extern u32		nosGetCount(void);
extern void		nosSetCause(u32);
extern void		nosExit(void);

/* Printf */

extern int		sprintf(char *s, const char *fmt, ...);
extern void		nosSyncPrintf(const char *fmt, ...);
extern void		nosAsyncPrintf(const char *fmt, ...);
extern int		nosSyncGetChars(char *buf);
extern int		nosAsyncGetChars(char *buf);

#endif /* _LANGUAGE_C */

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif /* !_OS_H */
