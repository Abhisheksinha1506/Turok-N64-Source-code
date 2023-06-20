
/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1994, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

/*
 * File:	rdpverif.c
 *
 *
 * This application is a test-bed of single frame tests for RDP
 * verification. The idea is that each frame possibly uses a different
 * dataset (see static.c) to render a particular test.
 *
 * This is the TEST-SPECIFIC file, see comment in main.c for more
 * information.
 *
 * TO ADD A TEST CASE:
 * New test cases require that you define the display list and add
 * a few simple things in the files rspverif.h, rspverif.c, static.c.
 * All locations are marked with comments that say "ADD TEST CASE"
 * and give some hints what you need to do there. See main.c for
 * detailed instructions.
 *
 * Fri Oct 14 11:21:49 PDT 1994
 *
 */

#include <ultra64.h>
#include "dldriver.h"
#include "rdp6M.h"
#include "cs.h"


/* procedure to do the work for placebo case: */
void
rdp6M_testCasePlacebo(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guPerspective(&dynamicp->projection, &(dynamicp->perspNorm),
		  33, 320.0/240.0, 1, 500, 1.0);
    guLookAt(&dynamicp->viewing, 
	     0, 0, 200, 0, 0, 0, 0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, dynamicp->perspNorm);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdp6M_testCaseProc1(Dynamic *dynamicp, Gfx *module_test)
{
#ifdef ONETRI
    static float        theta = 22.0;

    guOrtho(&dynamicp->projection,
            -SCREEN_WD/2.0, SCREEN_WD/2.0,
            -SCREEN_HT/2.0, SCREEN_HT/2.0, 1, 10.0, 1.0);
#else
    static float        theta = -15.0;

    guOrtho(&dynamicp->projection,
            -SCREEN_WD/2.0, SCREEN_WD/2.0,
            -SCREEN_HT/2.0, SCREEN_HT/2.0, -1, 1, 1.0);
#endif

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}


/* 
 * ADD TEST CASE: test frames:
 *
 * Static display lists from static.c must be inserted in this
 * table, in the same position as the test's frame number.
 * 
 * NOTE: a test doesn't need to have a static display list, if
 * the corresponding rdpfb_testCaseProc doesn't use. But you still
 * need to put a NULL entry here in the table.
 *
 * It is a good idea to put your name beside the test, so others
 * can track you down with questions.
 *
 */
GfxTest_t testList_rdp6M[] = {	/* list of specific test Gfx display lists: */
    &(rdp6M_test1[0]), "rdp6M_test1",
	rdp6M_testCasePlacebo, 1024, CLEAR_BLACK,
    &(rdp6M_square1[0]), "rdp6M_square1",
	rdp6M_testCaseProc1, 1024, CLEAR_BLACK,

    /* add cases above here: */
    (Gfx *) NULL,	/* last one, to count them... */
};
