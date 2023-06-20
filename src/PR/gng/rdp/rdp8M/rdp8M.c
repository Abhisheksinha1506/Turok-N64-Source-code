
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
#include "rdp8M.h"
#include "cs.h"


/* procedure to do the work for placebo case: */
void
rdp8M_testCasePlacebo(Dynamic *dynamicp, Gfx *module_test)
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
rdp8M_testCaseProc1(Dynamic *dynamicp, Gfx *module_test)
{
    guOrtho(&dynamicp->projection,
                0,320,239,0,-1,1, 1.0);
    guScale(&dynamicp->viewing,
                1,1,1);
    guScale(&dynamicp->modeling,
                1,1,1);

    gSPMatrix(glistp++, &(dynamicp->projection),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->viewing),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdp8M_testCaseProc2(Dynamic *dynamicp, Gfx *module_test)
{
    static float        theta = 0.0;
    u16                 perspNorm;


    guPerspective(&dynamicp->projection,&perspNorm,
                  33, 320.0/240.0, 100, 4000, 1.0);
    guLookAt(&dynamicp->viewing,
             0, 50, 250, 0, 0, 0, 0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 0.0, 1.0, 0.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
              G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, perspNorm);

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
GfxTest_t testList_rdp8M[] = {	/* list of specific test Gfx display lists: */
    &(rdp8M_big_image_test[0]), "rdp8M_big_image_test",
	rdp8M_testCaseProc1, 1024, CLEAR_BLACK,
    &(rdp8M_square2[0]), "rdp8M_square2",
	rdp8M_testCaseProc2, 1024, CLEAR_BLACK,
    &(rdp8M_qsim_test[0]), "rdp8M_qsim_test",
        rdp8M_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,

    /* add cases above here: */
    (Gfx *) NULL,	/* last one, to count them... */
};
