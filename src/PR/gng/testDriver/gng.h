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
 * File:	gng.h
 * Creator:	hal@sgi.com
 * Purpose:	Definitions for the go/no-go test program.
 *
 */

#define STACKSIZE	0x2000

#define reserved_rdram		0xa0000300

#define PASS_MESSAGE_RETRACE_COUNT 0

/* Various frame and zbuffer hardcoded addresses for rdp/vi tests */
/* Make sure that you don't have anything at these addresses that */
/* are going to be clobbered when the rdp/vi tests are run if you */
/* need them later.                                               */

#define L26V            0x80544800
#define L28V            0x80744800
#define L26R		0x80500000
#define H28R		0x80500000
#define LL24R		0x80396000 /*mini frame buffer (80x32) for rdp display*/

#define MEM_4M		0x400000
#define MEM_6M		0x600000
#define MEM_8M		0x800000

#define STATIC_SEGMENT1_DRAM_6M	0x80400000
#define STATIC_SEGMENT2_DRAM_8M	0x80700000

#define game_addr	0x8
#define game_offset	0x1000
#define game_size	0xfffff		/* Real DMA size = game_size - 1 */

#define GNG_INHIBIT_PRINT	0x00000000
#define GNG_PASS_FAIL_BIT	0x00000001
#define GNG_NMI_TEST_BIT	0x00000002
#define GNG_FINAL_TEST_BIT	0x00000004

/* individual tests return number of failures */
#define GNG_TEST_SUCCESS	0
#define GNG_TEST_FAILURE	1

#define	STATIC_SEGMENT		1
#define	DYNAMIC_SEGMENT		2
#define	TEXTURE_SEGMENT		3
#define	CFB_SEGMENT		4
#define	STATIC_SEGMENT1		5
#define	STATIC_SEGMENT2		6

#define INT1_ADDR	0x1f000000
#define INT1_SET_DATA	0xffffffff
#define INT1_CLR_DATA	0x00000000

#define NTSC_USEC_PER_RETRACE	16667
#define NTSC_USEC_RANGE		100

#define EXPANSION_MEM_BASE	0x80400000

/*
 * the following ifdef is needed because this file is included by the spec file
 * and by rdramTest.s
 */
#ifdef _LANGUAGE_C

#include "zaru.h"

#ifdef _FINALROM
/* cc will give warnings about argument mismatch in rom version */
#define PRINTF(a)
#else
#define PRINTF rmonPrintf
#endif


/*
 * The following structure exists in locore.  Cleared on cold reset
 * during osInitialize().  Untouched after NMI
 */
typedef struct {
    u32		rdram_diag_status;
    u32		rdram_diag_errors;
    u32		nmi_count;
    u32		nmi_first_timer;
    u32		nmi_second_timer;
    u32		testFailed;		/* TRUE if any test FAILs */
} gngstatus;

void gng_report(char *message, int testStatus, int flags, int delay);

/* Global variables tests need */
extern int zaruexists;
extern int runningFromRom;
extern int controllerSlot;
extern OSMesgQueue retraceMessageQ;
extern OSMesgQueue siMessageQ;
#endif

/*
 * Provide offsets to the rdram_diag_status, rdram_diag_errors variables
 * so that they can be accessed by the assembly code in rdramTest.s
 */
#define rdram_diag_status_offset	0x1c
#define rdram_diag_errors_offset	0x20
