
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
 * Creator:	hsa@sgi.com
 * Create Date:	Fri Oct 14 11:54:21 PDT 1994
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
#include "toplevel.h"
#include "rdpms.h"


/* procedure to do the work for placebo case: */
void
rdpms_testCasePlacebo(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guPerspective(&dynamicp->projection,&(dynamicp->perspNorm),
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

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/* procedure to do the work with simple ortho projection: */
void
rdpms_testCaseProcSimpleOrtho(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guOrtho(&dynamicp->projection,
	    0, SCREEN_WD,
	    0, SCREEN_HT, -1, 1, 1.0);

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

/* procedure to do the work with right side up ortho projection: */
void
rdpms_testCaseProcRSUOrtho(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guOrtho(&dynamicp->projection,
	    0, SCREEN_WD,
	    SCREEN_HT, 0, 0, 20, 1.0);

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

/* procedure to do the work with simple Z ortho projection: */
void
rdpms_testCaseProcZOrtho(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guOrtho(&dynamicp->projection,
	    -100, 100,
	    -100, 100,
	    150, 2000, 1.0);

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

void
rdpms_testCaseSimpleLookAt(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    Mtx m,n;

    guPerspective(&(dynamicp->projection),&(dynamicp->perspNorm),
		  33, 320.0/240.0, 150, 500, 1.0);

    guLookAt(&(dynamicp->viewing), 
	     0, 0, 200,
	     0, 0, 0, 
	     0, 1, 0);

/*
    guLookAt(&(dynamicp->viewing), 
	     141, 0, 141,
	     0, 0, 0, 
	     0, 1, 0);
    guLookAt(&(dynamicp->viewing), 
	     0, 141, 141,
	     0, 0, 0, 
	     0, 1, -1);
    guLookAt(&(dynamicp->viewing), 
	     0, 200, 0,
	     0, 0, 0, 
	     0, 0, -1);
*/

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_PROJECTION|G_MTX_MUL|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);


    gSPDisplayList(glistp++, module_test);
		   
    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpms_testCaseLookAtReflect(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    Mtx m,n;

    guPerspective(&(dynamicp->projection),&(dynamicp->perspNorm),
		  33, 320.0/240.0, 150, 500, 1.0);

/*
    guLookAt(&(dynamicp->viewing),
	     0, 0, 200,
	     0, 0, 0, 
	     0, 1, 0);
*/
    guLookAtReflect(&(dynamicp->viewing), &(dynamicp->lookat[0]),
	     0, 0, 200,
	     0, 0, 0, 
	     0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_PROJECTION|G_MTX_MUL|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPLookAt(glistp++, &(dynamicp->lookat[0]));

    gSPDisplayList(glistp++, module_test);
		   
    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpms_testCaseLookAtHilite(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    Mtx m,n;

    guPerspective(&(dynamicp->projection),&(dynamicp->perspNorm),
		  33, 320.0/240.0, 150, 500, 1.0);

/*
    guLookAt(&(dynamicp->viewing),
	     0, 0, 200,
	     0, 0, 0, 
	     0, 1, 0);
*/
/*
    guLookAtReflect(&(dynamicp->viewing), &(dynamicp->lookat[0]),
	     0, 0, 200,
	     0, 0, 0, 
	     0, 1, 0);
*/
    guLookAtHilite(&(dynamicp->viewing), &(dynamicp->lookat[0]), 
	     &(dynamicp->hilite[0]),
	     0, 0, 200,
	     0, 0, 0, 
	     0, 1, 0,
             -64.0,  0.0, 32.0,	/* light direction */
             64.0,-64.0, 32.0,
             32,32);


    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_PROJECTION|G_MTX_MUL|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPLookAt(glistp++, &(dynamicp->lookat[0]));

    gSPDisplayList(glistp++, &rdpms_light6a);

    gDPSetHilite1Tile(glistp++,G_TX_RENDERTILE,&(dynamicp->hilite[0]),32,32);
    gDPSetHilite2Tile(glistp++,G_TX_RENDERTILE+1,&(dynamicp->hilite[0]),32,32);

    gSPDisplayList(glistp++, &rdpms_light6b);

		   
    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpms_testCaseLookAtXluHili(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
/*    Mtx m,n; */
    Mtx tmpm;
    Hilite tmph;

    guPerspective(&(dynamicp->projection),&(dynamicp->perspNorm),
		  33, 320.0/240.0, 150, 500, 1.0);

/*
    guLookAt(&(dynamicp->viewing),
	     0, 0, 200,
	     0, 0, 0, 
	     0, 1, 0);
*/
/*
    guLookAtReflect(&(dynamicp->viewing), &(dynamicp->lookat[0]),
	     0, 0, 200,
	     0, 0, 0, 
	     0, 1, 0);
*/
    guLookAtHilite(&(dynamicp->viewing), &(dynamicp->lookat[0]), 
	     &(dynamicp->hilite[0]),
	     0, 0, 200,
	     0, 0, 0, 
	     0, 1, 0,
             64.0,-64.0, 32.0,
             -64.0,  0.0, 32.0,	/* light direction */
             32,32);
    guLookAtHilite(&tmpm, &(dynamicp->lookat[1]), 
	     &(dynamicp->hilite[1]),
	     0, 0, 200,
	     28, 0, 0, 
	     0, 1, 0,
             64.0,-64.0, 32.0,
             -64.0,  0.0, 32.0,	/* light direction */
             32,32);
    guLookAtHilite(&tmpm, &(dynamicp->lookat[2]), 
	     &(dynamicp->hilite[2]),
	     0, 0, 200,
	     -28, 0, 0, 
	     0, 1, 0,
             64.0,-64.0, 32.0,
             -64.0,  0.0, 32.0,	/* light direction */
             32,32);


    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_PROJECTION|G_MTX_MUL|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);


    gSPDisplayList(glistp++, &rdpms_light7a);

    dynamicp->hilite[0].h.x1 = 32*4;
    dynamicp->hilite[0].h.y1 = 32*4;
    dynamicp->hilite[1].h.x1 = 32*4;
    dynamicp->hilite[1].h.y1 = 32*4;
    dynamicp->hilite[2].h.x1 = 32*4;
    dynamicp->hilite[2].h.y1 = 32*4;

    gSPLookAt(glistp++, &(dynamicp->lookat[1]));
    gDPSetHilite1Tile(glistp++,G_TX_RENDERTILE,&(dynamicp->hilite[1]),32,32);
    gDPSetHilite2Tile(glistp++,G_TX_RENDERTILE+1,&(dynamicp->hilite[1]),32,32);
    gSPDisplayList(glistp++, rdpms_light7b);

    gSPLookAt(glistp++, &(dynamicp->lookat[0]));
    gDPSetHilite1Tile(glistp++,G_TX_RENDERTILE,&(dynamicp->hilite[0]),32,32);
    gDPSetHilite2Tile(glistp++,G_TX_RENDERTILE+1,&(dynamicp->hilite[0]),32,32);
    gSPDisplayList(glistp++, rdpms_light7c);

    gSPLookAt(glistp++, &(dynamicp->lookat[2]));
    gDPSetHilite1Tile(glistp++,G_TX_RENDERTILE,&(dynamicp->hilite[2]),32,32);
    gDPSetHilite2Tile(glistp++,G_TX_RENDERTILE+1,&(dynamicp->hilite[2]),32,32);
    gSPDisplayList(glistp++, rdpms_light7d);

		   
    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpms_testCaseLookAtClipFog(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    Mtx tmpm;
    Hilite tmph;

/*
    guPerspective(&(dynamicp->projection),&(dynamicp->perspNorm),
		  33, 320.0/240.0, 150, 500, 1.0);
*/
    guPerspective(&(dynamicp->projection),&(dynamicp->perspNorm),
		  16, 290.0/120.0, 150, 500, 1.0);

    guLookAtHilite(&(dynamicp->viewing), &(dynamicp->lookat[0]), 
	     &(dynamicp->hilite[0]),
	     0, 20, 200,
	     0, 20, 0, 
	     0, 1, 0,
             64.0,-64.0, 32.0,
             -64.0,  0.0, 32.0,	/* light direction */
             32,32);
    guLookAtHilite(&tmpm, &(dynamicp->lookat[1]), 
	     &(dynamicp->hilite[1]),
	     0, 20, 200,
	     28, 20, -28, 
	     0, 1, 0,
             64.0,-64.0, 32.0,
             -64.0,  0.0, 32.0,	/* light direction */
             32,32);
    guLookAtHilite(&tmpm, &(dynamicp->lookat[2]), 
	     &(dynamicp->hilite[2]),
	     0, 20, 200,
	     -28, 20, 28, 
	     0, 1, 0,
             64.0,-64.0, 32.0,
             -64.0,  0.0, 32.0,	/* light direction */
             32,32);


    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_PROJECTION|G_MTX_MUL|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);


    gSPDisplayList(glistp++, rdpms_light8a);

    gSPLookAt(glistp++, &(dynamicp->lookat[1]));
    gDPSetHilite1Tile(glistp++,G_TX_RENDERTILE,&(dynamicp->hilite[1]),32,32);
    gDPSetHilite2Tile(glistp++,G_TX_RENDERTILE+1,&(dynamicp->hilite[1]),32,32);
    gSPDisplayList(glistp++, rdpms_light8b);

    gSPLookAt(glistp++, &(dynamicp->lookat[0]));
    gDPSetHilite1Tile(glistp++,G_TX_RENDERTILE,&(dynamicp->hilite[0]),32,32);
    gDPSetHilite2Tile(glistp++,G_TX_RENDERTILE+1,&(dynamicp->hilite[0]),32,32);
    gSPDisplayList(glistp++, rdpms_light8c);

    gSPLookAt(glistp++, &(dynamicp->lookat[2]));
    gDPSetHilite1Tile(glistp++,G_TX_RENDERTILE,&(dynamicp->hilite[2]),32,32);
    gDPSetHilite2Tile(glistp++,G_TX_RENDERTILE+1,&(dynamicp->hilite[2]),32,32);
    gSPDisplayList(glistp++, rdpms_light8d);

		   
    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}


void
rdpms_testCaseProcASOrtho(Dynamic *dynamicp, Gfx *module_test)
{
    static float theta = 0.0;
    static float beta = -30.0;
    static Image im;
    static Image *imp = &im;
    static unsigned char tbuf[4096];
    static float dist = 1000;

    guOrtho(&dynamicp->projection,
            -1.5*SCREEN_WD, 1.5*SCREEN_WD,
            -1.5*SCREEN_HT, 1.5*SCREEN_HT, 50, 250, 1.0);

    guLookAt(&dynamicp->viewing,
             0, 0, 200, 0, 0, 0, 0, 2, 0);

    guRotate(&dynamicp->modeling, theta, 0.0, 1.0, 0.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
              G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);
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
 * the corresponding rdpms_testCaseProc doesn't use. But you still
 * need to put a NULL entry here in the table.
 *
 * It is a good idea to put your name beside the test, so others
 * can track you down with questions.
 *
 */
GfxTest_t testList_rdpms[] = {	/* list of specific test Gfx display lists: */

    &(rdpms_simplefill[0]), 	"rdpms_simplefill",	/* test 0 */
	rdpms_testCaseProcSimpleOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_firsttri[0]),    	"rdpms_firsttri",
	rdpms_testCaseProcSimpleOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_righttri[0]),    	"rdpms_righttri",
	rdpms_testCaseProcSimpleOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_ztriangles[0]),  	"rdpms_ztriangles",
	rdpms_testCaseSimpleLookAt,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_fogtriangles[0]),	"rdpms_fogtriangles",
	rdpms_testCaseSimpleLookAt,	G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpms_bltriangles[0]), 	"rdpms_bltriangles",	/* test 5 */
	rdpms_testCaseSimpleLookAt,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_aaztriangles[0]), 	"rdpms_aaztriangles",		
	rdpms_testCaseSimpleLookAt,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_bltri[0]), 		"rdpms_bltri",		
	rdpms_testCaseProcSimpleOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_placebo_dl[0]),	"rdpms_placebo_dl",
	rdpms_testCasePlacebo,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_placebo_dl[0]),	"rdpms_placebo_dl",
	rdpms_testCasePlacebo,	G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpms_filldl[0]),		"rdpms_filldl",		/* test 10 */
	rdpms_testCaseProcRSUOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_copyloaddl[0]),	"rdpms_copyloaddl",	
	rdpms_testCaseProcRSUOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_copyload8b[0]),	"rdpms_copyload8b",
	rdpms_testCaseProcRSUOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_filldl2[0]),	"rdpms_filldl2",
	rdpms_testCaseProcRSUOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_loadrend[0]),	"rdpms_loadrend",
	rdpms_testCaseProcRSUOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpms_rmode1cyc[0]),	"rdpms_rmode1cyc",	/* test 15 */
	rdpms_testCaseProcRSUOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_rmode2cyc[0]),	"rdpms_rmode2cyc",
	rdpms_testCaseProcRSUOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_txalign[0]),	"rdpms_txalign",
	rdpms_testCaseProcRSUOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_cliptri[0]),	"rdpms_cliptri",
	rdpms_testCaseProcZOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_txalign32[0]),	"rdpms_txalign32",
	rdpms_testCaseProcRSUOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpms_ditherColor[0]),	"rdpms_ditherColor",	/* test 20 */
	rdpms_testCaseProcASOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_ditherAlpha[0]),	"rdpms_ditherAlpha",
	rdpms_testCaseProcASOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_exhFill[0]),	"rdpms_exhFill",
	rdpms_testCaseProcSimpleOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_placebo_dl[0]),	"rdpms_placebo_dl",
	rdpms_testCasePlacebo,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_placebo_dl[0]),	"rdpms_placebo_dl",
	rdpms_testCasePlacebo,	G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpms_placebo_dl[0]),	"rdpms_placebo_dl",	/* test 25 */
	rdpms_testCasePlacebo,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_msdiag1[0]),	"rdpms_msdiag1",
	rdpms_testCaseProcZOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_msdiag2[0]),	"rdpms_msdiag2",
	rdpms_testCaseProcZOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_msdiag3[0]),	"rdpms_msdiag3",
	rdpms_testCaseProcZOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_msdiag4[0]),	"rdpms_msdiag4",
	rdpms_testCaseProcZOrtho,	G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpms_light1[0]),		"rdpms_light1",		/* test 30 */
	rdpms_testCaseSimpleLookAt,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_light2[0]),		"rdpms_light2",
	rdpms_testCaseSimpleLookAt,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_light3[0]),		"rdpms_light3",
	rdpms_testCaseSimpleLookAt,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_light4[0]),		"rdpms_light4",
	rdpms_testCaseSimpleLookAt,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_light5[0]),		"rdpms_light5",
	rdpms_testCaseLookAtReflect,	G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpms_light6a[0]),	"rdpms_light6a",	/* test 35 */
	rdpms_testCaseLookAtHilite,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_light7a[0]),	"rdpms_light7a",
	rdpms_testCaseLookAtXluHili,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_light8a[0]),	"rdpms_light8a",
	rdpms_testCaseLookAtClipFog,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_light9[0]),		"rdpms_light9",
	rdpms_testCaseSimpleLookAt,	G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpms_light10[0]),	"rdpms_light10",
	rdpms_testCaseSimpleLookAt,	G_IM_SIZ_16b, CLEAR_BLACK,

    /* add cases above here: */
    (Gfx *) NULL,	/* last one, to count them... */
};
