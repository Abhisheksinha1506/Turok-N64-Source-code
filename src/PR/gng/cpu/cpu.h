#ifndef _CPUTEST_H_
#define _CPUTEST_H_

/*====================================================================
 * cputest.h
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

/*
 * Nested includes are evil.  The -I$(ROOT)/PR/apps/gng/testDriver directive 
 * from locdefs doesn't work when this file is installed to /usr/src/PR/gng, 
 * so we specify a relative path to the gng.h include file instead, as this
 * method will always work.
 */
#include "../testDriver/gng.h"

/**************************************************************************
 *
 * Definitions
 *
 */

#define	NUM_ITERATIONS		5000

/* TLB page size */
#define _4K			(4*1024)
#define _16K			(16*1024)
#define _64K			(64*1024)
#define _256K			(256*1024)
#define _1M			(1024*1024)
#define _4M			(4*1024*1024)

/* Thread priorities */
#define	FAULT_THREAD_PRI	125
#define	TIMER_THREAD_PRI	124
#define	FP_THREAD_PRI		20
#define	USER_THREAD_PRI		20
#define	SLAVE_THREAD_PRI	20
#define	MAIN_THREAD_PRI		10
#define	IDLE_THREAD_PRI		0

/* Messages */
#define MSG_FAULT		0xdead
#define MSG_TLB_MOD		0x101
#define MSG_TLB_REFILL		0x202
#define MSG_TLB_INV		0x303
#define MSG_TIMER_EXP		0x404

#define	STACKSIZE		0x2000
#define	BUFSIZE			(3*64*1024)	/* Max size needed by tlb0 */
#define PAGESIZE		4096		/* Test TLB page size */

#define BOOT_K0ADDR		0x80000400      /* Boot address */
#define BUF_K0ADDR     		0x80180000      /* Test buffer address */
#define TLB_TESTADDR		0xA0200000      /* Starting at 2 MB? */

#define APP_PADDR		0x003C0000	/* 4MB - 256KB boundary */
#define APP_VADDR		0x003C0000	/* Starting virtual address */

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#ifdef _LANGUAGE_C

/**************************************************************************
 *
 * Structure defintions
 *
 */
typedef struct {
        unsigned int inst1;             /* lui  k0,XXXX */
        unsigned int inst2;             /* addiu k0,k0,XXXX */
        unsigned int inst3;             /* jr k0 */
        unsigned int inst4;             /* nop */
} __osExceptionVector;

typedef struct {
    u32         *nofault;
    OSThread    *thread;
}  OSFault;

#define _MJBLEN 512
typedef s32	jmp_buf[_MJBLEN]; 

extern OSFault	__osFault;

#define _badvaddr       __osFault.thread->context.badvaddr

#ifdef _PRINT_DEBUG_
#define XDEBUG(a)       {PRINTF("%s:%d: ",__FILE__, __LINE__); (a);}
#else
#define XDEBUG(a)
#endif


/**************************************************************************
 *
 * Global structures
 *
 */


/**************************************************************************
 *
 * Function prototypes
 *
 */
extern void     	set_pgmask(u32);
extern void     	tlbwired(u32, u32, u32, u32, u32);
extern u32      	probe_tlb(u32, u32);

extern void		__osExceptionPreamble2(void);

extern u32		__osSetJmp(u32 *);
extern void		__osRestoreJmp(u32 *, OSThread *);

extern OSThread 	*FindFaultedThread(void);
extern void 		RegisterNoFault(u32 *);
extern void		ClearNoFault(void);

extern int		tlb0(void);
extern int		tlb1(void);
extern s32		tlbMem(void);
extern s32		tlbProbe(s32 *);
extern s32		tlbTranslate(s32 *, u32 *);
extern s32		tlbValid(s32 *);
extern s32		tlbMod(s32 *);
extern s32		tlbPid(s32 *);
extern s32		tlbGlobal(s32 *);
extern s32		tlbNocache(s32 *, u32 *, u32 *);


#endif	/* _LANGUAGE_C */

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif  /* _CPUTEST_H_ */

