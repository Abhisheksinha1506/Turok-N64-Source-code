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
 * File:	ms.c
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:	dynamic DL tests for memspan test vector generation.
 *
 *
 * This application is a test-bed of single frame tests for RDP
 * verification. The idea is that each frame possibly uses a different
 * dataset (see ms_static.c) to render a particular test.
 *
 * This is a MODULE and TEST-SPECIFIC file, see comment in main.c for more
 * information.
 *
 * TO ADD A TEST CASE:
 *
 * New test cases require that you define the display list and add
 * a few simple things in the files ms.h, ms.c, ms_static.c.
 *
 * All locations are marked with comments that say "ADD TEST CASE"
 * and give some hints what you need to do there. See main.c for
 * detailed instructions.
 *
 */

#include <ultra64.h>

#include "dldriver.h"
#include "toplevel.h"
#include "ms.h"

/* 
 * ADD TEST CASE: test frames:
 *
 * Static display lists from ms_static.c must be inserted in this
 * table, in the same position as the test's frame number, along with
 * a mneumonic name (which will be used to name the resulting .rdp display
 * list file).
 * 
 * NOTE: a test doesn't need to have a static display list, if
 * the corresponding testCaseProc doesn't use one. But you still
 * need to put a NULL entry here in the table.
 */
GfxTest_t testList_ms[] = {
    &(MS_loadTlut[0]),		"ms_vector",		testCaseProcSimpleOrtho,
	G_IM_SIZ_16b, CLEAR_AQUA,
    &(MS_loadCopy[0]),		"ms_loadCopy",		testCaseProcSimpleOrtho,
	G_IM_SIZ_32b, CLEAR_AQUA,
    &(MS_render[0]),		"MS_render",		testCaseProcSimpleOrtho,
	G_IM_SIZ_32b, CLEAR_AQUA,
    &(MS_zCases[0]),		"MS_zCases",		testCaseProcSimpleOrtho,
	G_IM_SIZ_16b, CLEAR_AQUA,
    &(MS_cyc2Blend[0]),		"MS_2cycBlend",		testCaseProcSimpleOrtho,
	G_IM_SIZ_16b, CLEAR_AQUA,
    &(MS_fill[0]),		"MS_fill",		testCaseProcSimpleOrtho,
	G_IM_SIZ_16b, CLEAR_AQUA,
    &(MS_address[0]),		"MS_address",		testCaseProcSimpleOrtho,
	G_IM_SIZ_16b, CLEAR_AQUA,
    &(MS_longSpanLoad[0]),	"MS_longspanLoad",	testCaseProcSimpleOrtho,
	G_IM_SIZ_16b, CLEAR_AQUA,
    &(MS_longSpanRender[0]),	"MS_longspanRender",	testCaseProcSimpleOrtho,
	G_IM_SIZ_32b, CLEAR_AQUA,
    &(MS_loadCopy2[0]),		"ms_vector2",		testCaseProcSimpleOrtho,
	G_IM_SIZ_32b, CLEAR_AQUA,
    /* add new test cases above here: */

    /* Last entry must be NULL, so we can count them in main.c */
    (Gfx *) NULL,	"",		(CaseProc_t) NULL,
	G_IM_SIZ_16b, CLEAR_AQUA,
};
