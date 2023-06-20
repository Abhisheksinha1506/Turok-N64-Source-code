
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
#include "rdpfb.h"
#include "cs.h"


/* procedure to do the work for placebo case: */
void
rdpfb_testCasePlacebo(Dynamic *dynamicp, Gfx *module_test)
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

/* procedure to do the work for test 0: */
void
rdpfb_testCaseProc0(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    u16			perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);
    guLookAt(&dynamicp->viewing, 
	     0, 0, 200, 0, 0, 0, 0, 1, 0);
    /*
	     200, 200, 200, 0, 0, 0, 0, 1, 0);
     */

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

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

void
rdpfb_testCaseProc5(Dynamic *dynamicp, Gfx *module_test)
{
    static float        theta = 0.0;
    static float        scale = 0.85;

    guOrtho(&dynamicp->projection,
	    0, SCREEN_WD,
	    0, SCREEN_HT, -1, 1, 1.0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    guTranslate(&dynamicp->model1, SCREEN_WD/2, SCREEN_HT/2, 0.0);

    guTranslate(&dynamicp->model2, -SCREEN_WD/2, -SCREEN_HT/2, 0.0);

    guScale(&dynamicp->viewing, scale, scale, scale);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model1)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model2)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpfb_testCaseProc6(Dynamic *dynamicp, Gfx *module_test)
{
    static float        theta = 0.0;
    static float        scale = 0.83;

    guOrtho(&dynamicp->projection,
	    0, SCREEN_WD,
	    0, SCREEN_HT, -1, 1, 1.0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    guTranslate(&dynamicp->model1, SCREEN_WD/2, SCREEN_HT/2, 0.0);

    guTranslate(&dynamicp->model2, -SCREEN_WD/2, -SCREEN_HT/2, 0.0);

    guScale(&dynamicp->viewing, scale, scale, scale);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model1)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model2)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}


void
rdpfb_testCaseProc7(Dynamic *dynamicp, Gfx *module_test)
{
    static float        theta = 0.0;
    static float        scale = 0.82;

    guOrtho(&dynamicp->projection,
	    0, SCREEN_WD,
	    0, SCREEN_HT, -1, 1, 1.0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    guTranslate(&dynamicp->model1, SCREEN_WD/2, SCREEN_HT/2, 0.0);

    guTranslate(&dynamicp->model2, -SCREEN_WD/2, -SCREEN_HT/2, 0.0);

    guScale(&dynamicp->viewing, scale, scale, scale);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model1)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model2)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

static Vp vp640 = {
        640*2, 480*2, G_MAXZ/2, 0,  /* scale */
        640*2, 480*2, G_MAXZ/2, 0,  /* translate */
};
void
rdpfb_testCaseProc640(Dynamic *dynamicp, Gfx *module_test)
{
/*
    guOrtho(&dynamicp->projection,
                0,320,239,0,-1,1, 1.0);
*/
    guOrtho(&dynamicp->projection,
                0,640,479,0,-1,1, 1.0);

    guScale(&dynamicp->viewing,
                1,1,1);
    guScale(&dynamicp->modeling,
                1,1,1);

    gSPViewport(glistp++, &vp640);

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

/* ADD TEST CASE: test frames: */
/* add procedure to do the work above here. */

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
GfxTest_t testList_rdpfb[] = {	/* list of specific test Gfx display lists: */
    &(rdpfb_square0[0]), "rdpfb_square0",	/* hsa */
	rdpfb_testCaseProc0, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpfb_shade_acc0[0]),"rdpfb_shade_acc0",	/* test 5 */	/* rmoore */
	rdpfb_testCaseProc5, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpfb_shade_acc1[0]),"rdpfb_shade_acc1",	/* rmoore */
	rdpfb_testCaseProc6, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpfb_shade_acc2[0]),"rdpfb_shade_acc2",	/* rmoore */
	rdpfb_testCaseProc7, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpfb_hires_image_test[0]),"rdpfb_hires_image_test", /* acorn */
	rdpfb_testCaseProc640, G_IM_SIZ_16b, CLEAR_BLACK,

    /* add cases above here: */
    (Gfx *) NULL,	/* last one, to count them... */
};
