/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1996, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

/*
 * File:	rdpcov.c
 * Creator:	hal@sgi.com
 * Purpose:	dynamic DL tests for rdp coverage testing
 *
 *
 * This application is a test-bed of single frame tests for RDP
 * verification. The idea is that each frame possibly uses a different
 * dataset (see rdpatt_static.c) to render a particular test.
 *
 * This is a MODULE and TEST-SPECIFIC file, see comment in main.c for more
 * information.
 *
 * TO ADD A TEST CASE:
 *
 * New test cases require that you define the display list and add
 * a few simple things in the files rdpcov.h, rdpcov.c, rdpcov_static.c.
 *
 * All locations are marked with comments that say "ADD TEST CASE"
 * and give some hints what you need to do there. See main.c for
 * detailed instructions.
 *
 */

#include <ultra64.h>

#include "dldriver.h"
#include "toplevel.h"
#include "rdpcov.h"
#include "cs.h"

int rdpcovProc33Theta;
int rdpcovSlowRotateTheta;

/* procedure to do the work for placebo case: */
void
rdpcov_testCasePlacebo(Dynamic *dynamicp, Gfx *module_test)
{
    float		theta = 1.0;
    u16			perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
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
    
    gSPPerspNormalize(glistp++, perspNorm);

    gSPDisplayList(glistp++, module_test);


    if (generateFullSync == 1) {
	gDPFullSync(glistp++);
    } else {
	gDPPipeSync(glistp++);
    }
}

/*
 * An SGI logo.
 *
 */
void
rdpcov_testCaseProc33(Dynamic *dynamicp, Gfx *module_test)
{
    u16			perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 400, 2000, 1.0);

    guLookAt(&dynamicp->viewing, 
	     0, 0, 1000,
	     0, 0, 0,
	     0, 1, 0);
    
    gSPPerspNormalize(glistp++, perspNorm);

    /* draw the background first */
    guScale(&dynamicp->model1, 12.0, 8.0, 1.0);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model1)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPDisplayList(glistp++, &(rdpcov_bg33_dl[0]));

    /* draw an SGI logo: */
    guRotate(&dynamicp->model2, rdpcovProc33Theta, 0.0, 1.0, 0.0);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model2)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPDisplayList(glistp++, &(rdpcov_logo_dl[0]));

        gDPFullSync(glistp++);
/**
    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
**/
}

void
rdpcov_testCaseProc5(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovProc33Theta = 0;
    rdpcov_testCaseProc33(dynamicp, module_test);
}

void
rdpcov_testCaseProc6(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovProc33Theta = 1.0;
    rdpcov_testCaseProc33(dynamicp, module_test);
}

void
rdpcov_testCaseProc7(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovProc33Theta = 2.0;
    rdpcov_testCaseProc33(dynamicp, module_test);
}

void
rdpcov_testCaseProc8(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovProc33Theta = 3.0;
    rdpcov_testCaseProc33(dynamicp, module_test);
}

void
rdpcov_testCaseProc11(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovProc33Theta = 4.0;
    rdpcov_testCaseProc33(dynamicp, module_test);
}

void
rdpcov_testCaseProc12(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovProc33Theta = 5.0;
    rdpcov_testCaseProc33(dynamicp, module_test);
}

void
rdpcov_testCaseProc13(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovProc33Theta = 6.0;
    rdpcov_testCaseProc33(dynamicp, module_test);
}

void
rdpcov_testCaseProc14(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovProc33Theta = 7.0;
    rdpcov_testCaseProc33(dynamicp, module_test);
}

void
rdpcov_testCaseProc16(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovProc33Theta = 8.0;
    rdpcov_testCaseProc33(dynamicp, module_test);
}

void
rdpcov_testCaseProc17(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovProc33Theta = 9.0;
    rdpcov_testCaseProc33(dynamicp, module_test);
}

void
rdpcov_testCaseProc18(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovProc33Theta = 10.0;
    rdpcov_testCaseProc33(dynamicp, module_test);
}

void
rdpcov_testCaseProc19(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovProc33Theta = 11.0;
    rdpcov_testCaseProc33(dynamicp, module_test);
}

/* procedure to do the work for test 0: */
void
rdpcov_testCaseProc0(Dynamic *dynamicp, Gfx *module_test)
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
rdpcov_testCaseProc1(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = -15.0;

    guOrtho(&dynamicp->projection,
	    -SCREEN_WD/2.0, SCREEN_WD/2.0,
	    -SCREEN_HT/2.0, SCREEN_HT/2.0, -1, 1, 1.0);

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
rdpcov_testCaseProc2(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 30.0;

    guOrtho(&dynamicp->projection,
	    -SCREEN_WD/2.0, SCREEN_WD/2.0,
	    -SCREEN_HT/2.0, SCREEN_HT/2.0, -1, 1, 1.0);
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
rdpcov_testCaseProc3(Dynamic *dynamicp, Gfx *module_test)
{
    guOrtho(&dynamicp->projection,
	    0, SCREEN_WD,
	    0, SCREEN_HT, -1, 1, 1.0);

    guTranslate(&dynamicp->modeling, 0.25, 0.25, 0.0);

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
rdpcov_testCaseProc4(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    u16			perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);
		  
    guLookAt(&dynamicp->viewing, 
	     0, 0, 0,
	     0, 0, -200,
	     0, 1, 0);

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
rdpcov_testCaseProc9(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 1.0;

    guOrtho(&dynamicp->projection,
	    -SCREEN_WD/2.0, SCREEN_WD/2.0,
	    -SCREEN_HT/2.0, SCREEN_HT/2.0, -1, 1, 1.0);

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
rdpcov_testCaseProc10(Dynamic *dynamicp, Gfx *module_test)
{
    guOrtho(&dynamicp->projection,
                -100,100,-100,100,-100,100,1.0);
    guScale(&dynamicp->viewing,
                1,1,1);
    guScale(&dynamicp->modeling,
                1,1,1);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpcov_testCaseProc15(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    u16			perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);
		  
    guLookAt(&dynamicp->viewing, 
	     0, 0, 0,
	     0, 0, -200,
	     0, 1, 0);

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



/* procedure to do the work for test 20: */
void
rdpcov_testCaseProc20(Dynamic *dynamicp, Gfx *module_test)
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

/* procedure to do the work for test 21: */
void
rdpcov_testCaseProc21(Dynamic *dynamicp, Gfx *module_test)
{
    guOrtho(&dynamicp->projection,
	    0, SCREEN_WD,
	    0, SCREEN_HT, -1, 1, 1.0);

    guScale(&dynamicp->modeling, 1.0, 1.0, 1.0);

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

/* procedure to do the work for test 22: */
void
rdpcov_testCaseProc22(Dynamic *dynamicp, Gfx *module_test)
{
    guOrtho(&dynamicp->projection,
	    0, SCREEN_WD,
	    0, SCREEN_HT, -1, 1, 1.0);

    guTranslate(&dynamicp->modeling, 0.25, 0.25, 0.0);

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

/* procedure to do the work for test 23: */
void
rdpcov_testCaseProc23(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.3;
    u16			perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);
    guLookAt(&dynamicp->viewing, 
	     0, 0, 200, 0, 0, 0, 0, 1, 0);

/*    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);*/
    guScale(&dynamicp->modeling, 1.0, theta, 1.0);

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

/* procedure to do the work for test 24: */
void
rdpcov_testCaseProc24(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    u16			perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
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
    
    gSPPerspNormalize(glistp++, perspNorm);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}


/* procedure to do the work for placebo case: */
void
rdpcov_testCaseCases(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    u16			perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);
    guLookAt(&dynamicp->viewing, 
	     0, 0, 200, 0, 0, 0, 0, 1, 0);

    guScale(&dynamicp->modeling, 1.0, 1.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    
    gSPPerspNormalize(glistp++, perspNorm);

    gDPPipeSync(glistp++);
    gSPClearGeometryMode(glistp++, G_ZBUFFER);
    gSPClearGeometryMode(glistp++, G_CULL_BACK);
    gSPSetGeometryMode(glistp++, G_SHADE);
    gDPSetCombineMode (glistp++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/* procedure to do the work for placebo case: */
void
rdpcov_testCaseCasesQtr(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.05;
    u16			perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);
    guLookAt(&dynamicp->viewing, 
	     0, 0, 200, 0, 0, 0, 0, 1, 0);

    guScale(&dynamicp->modeling, theta, theta, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    
    gSPPerspNormalize(glistp++, perspNorm);

    gDPPipeSync(glistp++);
    gSPClearGeometryMode(glistp++, G_ZBUFFER);
    gSPClearGeometryMode(glistp++, G_CULL_BACK);
    gSPSetGeometryMode(glistp++, G_SHADE);
    gDPSetCombineMode (glistp++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/*
 * Animation balls.
 *
 */
void
rdpcov_testCaseProc31(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0, alpha = 0;
    u16			perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 100, 4000, 1.0);

    guLookAt(&dynamicp->viewing, 
	     50, 50, 1500,
	     0, 0, 0,
	     0, 1, 0);
    
    gSPPerspNormalize(glistp++, perspNorm);


    /* ball */
    guTranslate(&dynamicp->model1, 0.0, 0.0, 300.0 - theta);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model1)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPDisplayList(glistp++, &(rdpcov_ball_dl[0]));

    /* ball */
    guTranslate(&dynamicp->model2, -300.0, 300.0 - theta, 0.0);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model2)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPDisplayList(glistp++, &(rdpcov_ball_dl[0]));

    /* ball */
    guTranslate(&dynamicp->model3, 300.0 - theta, 300.0, 0.0);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model3)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPDisplayList(glistp++, &(rdpcov_ball_dl[0]));

    /* ball */
    guTranslate(&dynamicp->model4, -300.0, -300.0, 0.0);
    guRotate(&dynamicp->modeling, alpha, 0.0, 0.0, 1.0);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model4)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPDisplayList(glistp++, &(rdpcov_ball_dl[0]));


    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/*
 *
 */
void
rdpcov_testCaseProc32(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0, alpha = 0;
    u16			perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 100, 4000, 1.0);

    guLookAt(&dynamicp->viewing, 
	     5, 0, 500,
	     0, 0, 0,
	     0, 1, 0);
    
    gSPPerspNormalize(glistp++, perspNorm);


    guTranslate(&dynamicp->model1, 0.0, 0.0, theta);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model1)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPDisplayList(glistp++, &(rdpcov_test32_dl[0]));

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}


/*
 * shading test.
 *
 */
void
rdpcov_testCaseProc34(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0, alpha = 0;
    u16			perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 100, 4000, 1.0);

    guLookAt(&dynamicp->viewing, 
	     50, 50, 400,
	     0, 0, 0,
	     0, 1, 0);
    
    gSPPerspNormalize(glistp++, perspNorm);


    /* ball */
    guTranslate(&dynamicp->model1, 0.0, 0.0, 0.0);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model1)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPDisplayList(glistp++, &(rdpcov_ball_tex_dl[0]));


    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

static Vp linevp = {
	SCREEN_WD,   SCREEN_HT,   G_MAXZ/2, 0,	/* scale */
	SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* translate */
};

Mtx identity={
        0x00010000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00010000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00010000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00010000,
};

void
rdpcov_testCaseProc35(Dynamic *dynamicp, Gfx *module_test)
{
    /* Sets up orthogonal transformation such
       that world X and Y coordinates are the
       same as screen x and y coordinates */


    static float	theta;

    guOrtho(&dynamicp->projection,
	     0.00, 4*SCREEN_WD-1,
	     0.00, 4*SCREEN_HT-1, 
	    -4.00, 4.00, 
	    1.00);

    /* theta = 5.1; */
    theta = 0.0;

    gSPMatrix(glistp++, K0_TO_PHYS(&identity), G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    guTranslate(&dynamicp->model1, 640, 480, -400);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model1)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH); 

    guRotate(&dynamicp->model2, theta, 0.0, 0.0, 1.0);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->model2)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH); 

    guTranslate(&dynamicp->modeling, -640, -480, 400);
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH); 


    /*
    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    */

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    /* gSPViewport(glistp++, &linevp); */

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpcov_testCaseProc36(Dynamic *dynamicp, Gfx *module_test)
{
    /* Sets up orthogonal transformation such
       that world X and Y coordinates are the
       same as screen x and y coordinates */

    static float	theta = 0.0;

    guOrtho(&dynamicp->projection,
	    0, 4*SCREEN_WD-1,
	    0, 4*SCREEN_HT-1, -1, 1, 1.0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH); 

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH); 


    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpcov_testCaseProc37(Dynamic *dynamicp, Gfx *module_test)
{
    /* Sets up orthogonal transformation such
       that world X and Y coordinates are the
       same as screen x and y coordinates */

    static float	theta = 0.0;

    guOrtho(&dynamicp->projection,
	     0.00, SCREEN_WD-1,
	     0.00, SCREEN_HT-1, 
	    -0.01, 1.00, 
	    1.0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH); 

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH); 

    gSPViewport(glistp++, &linevp);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpcov_testCaseProc38(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = -15.0;
    
    guOrtho(&dynamicp->projection,
	    -SCREEN_WD/2.0, SCREEN_WD/2.0,
	    -SCREEN_HT/2.0, SCREEN_HT/2.0, -4, 4, 1.0);
    
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
rdpcov_testCaseProc39(Dynamic *dynamicp, Gfx *module_test)
{

    static float	theta = 0.0;

    /*
    guOrtho(&dynamicp->projection,
	    -SCREEN_WD/2.0, SCREEN_WD/2.0,
	    -SCREEN_HT/2.0, SCREEN_HT/2.0, -1, 1, 1.0);
    */

    guOrtho(&dynamicp->projection,
	     0.00, 4*SCREEN_WD-1,
	     0.00, 4*SCREEN_HT-1, 
	    -4.00, 4.00, 
	    1.00);

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


/* procedure to slowly rotate */
void
rdpcov_testCaseSlowRotate(Dynamic *dynamicp, Gfx *module_test)
{
    u16			perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);
    guLookAt(&dynamicp->viewing, 
	     0, 0, 200, 0, 0, 0, 0, 1, 0);
    /*
	     200, 200, 200, 0, 0, 0, 0, 1, 0);
     */

    guRotate(&dynamicp->modeling,rdpcovSlowRotateTheta , 0.0, 0.0, 1.0);

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
rdpcov_testCaseProc40(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovSlowRotateTheta = 10.0;
    rdpcov_testCaseSlowRotate(dynamicp, module_test);
}

void
rdpcov_testCaseProc41(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovSlowRotateTheta = 11.0;
    rdpcov_testCaseSlowRotate(dynamicp, module_test);
}

void
rdpcov_testCaseProc42(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovSlowRotateTheta = 12.0;
    rdpcov_testCaseSlowRotate(dynamicp, module_test);
}

void
rdpcov_testCaseProc43(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovSlowRotateTheta = 13.0;
    rdpcov_testCaseSlowRotate(dynamicp, module_test);
}

void
rdpcov_testCaseProc44(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovSlowRotateTheta = 14.0;
    rdpcov_testCaseSlowRotate(dynamicp, module_test);
}

void
rdpcov_testCaseProc45(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovSlowRotateTheta = 15.0;
    rdpcov_testCaseSlowRotate(dynamicp, module_test);
}

void
rdpcov_testCaseProc46(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovSlowRotateTheta = 16.0;
    rdpcov_testCaseSlowRotate(dynamicp, module_test);
}

void
rdpcov_testCaseProc47(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovSlowRotateTheta = 17.0;
    rdpcov_testCaseSlowRotate(dynamicp, module_test);
}

void
rdpcov_testCaseProc48(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovSlowRotateTheta = 18.0;
    rdpcov_testCaseSlowRotate(dynamicp, module_test);
}

void
rdpcov_testCaseProc49(Dynamic *dynamicp, Gfx *module_test)
{
    rdpcovSlowRotateTheta = 19.0;
    rdpcov_testCaseSlowRotate(dynamicp, module_test);
}



/* 
 * ADD TEST CASE: test frames:
 *
 * Display lists from rdpcov_static.c (which are placed in the static segment 
 * via the spec file) must be inserted in this table, in the same position as 
 * the test's frame number, along with a mneumonic name (which will be used to 
 * name the resulting .rdp display list file), and a pointer to the top level 
 * DL function which will be used to invoke this static display list.
 * 
 * NOTE: a test doesn't need to have a static display list, if
 * the corresponding testCaseProc doesn't use one. But you still
 * need to put a NULL entry here in the table.
 */
GfxTest_t testList_rdpcov[] = {

    &(rdpcov_square0[0]),	"rdpcov_square0",
	rdpcov_testCaseProc0, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_square1[0]),	"rdpcov_square1",
	rdpcov_testCaseProc1, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_square2[0]),	"rdpcov_square2",
	rdpcov_testCaseProc2, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_square3[0]),	"rdpcov_square3",
	rdpcov_testCaseProc3, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_triangles[0]),	"rdpcov_triangles",
	rdpcov_testCaseProc4, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",	/* test 5 */
	rdpcov_testCaseProc5, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCaseProc6, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCaseProc7, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCaseProc8, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_subpix_scissor[0]),"rdpcov_subpix_scissor",
	rdpcov_testCaseProc9, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpcov_triangle10[0]),	"rdpcov_triangle10",	/* test 10 */
	rdpcov_testCaseProc10, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCaseProc11, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCaseProc12, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCaseProc13, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCaseProc14, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpcov_fogtriangles[0]),	"rdpcov_fogtriangles",	/* test 15 */
	rdpcov_testCaseProc15, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCaseProc16, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCaseProc17, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCaseProc18, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCaseProc19, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpcov_square20[0]),	"rdpcov_square20",	/* test 20 */
	rdpcov_testCaseProc20, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_square21[0]),	"rdpcov_square21",
	rdpcov_testCaseProc21, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_square22[0]),	"rdpcov_square22",
	rdpcov_testCaseProc22, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_square23[0]),	"rdpcov_square23",
	rdpcov_testCaseProc23, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_square24[0]),	"rdpcov_square24",
	rdpcov_testCaseProc24, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpcov_gfx_25[0]),	"rdpcov_gfx_25",	/* test 25 */
	rdpcov_testCaseCases, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_case_edge_00[0]),	"rdpcov_case_edge_00",
	rdpcov_testCaseCasesQtr, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_case_vertex_00[0]),"rdpcov_case_vertex_00",
	rdpcov_testCaseCasesQtr, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_case_skinny_00[0]),"rdpcov_case_skinny_00",
	rdpcov_testCaseCases, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_case_tiny_00[0]),	"rdpcov_case_tiny_00",
	rdpcov_testCaseCases, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpcov_case_disc_00[0]),	"rdpcov_case_disc_00",	/* test 30 */
	rdpcov_testCaseCases, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCaseProc31, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCaseProc32, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCasePlacebo, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_placebo_dl[0]),	"rdpcov_placebo_dl",
	rdpcov_testCaseProc34, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpcov_lines1[0]),	"rdpcov_lines1",       /* test 35 */
	rdpcov_testCaseProc35, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_lines2[0]),	"rdpcov_lines2",
	rdpcov_testCaseProc36, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_lclip1[0]),	"rdpcov_lclip1",
	rdpcov_testCaseProc37, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_cbar1[0]),		"rdpcov_cbar1",
	rdpcov_testCaseProc38, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_FooTri[0]),	"rdpcov_FooTri",
	rdpcov_testCaseProc39, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpcov_dithertest[0]),	"rdpcov_dithertest",	/* test 40 */
	rdpcov_testCaseProc40, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_dithertest[0]),	"rdpcov_dithertest",
	rdpcov_testCaseProc41, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_dithertest[0]),	"rdpcov_dithertest",
	rdpcov_testCaseProc42, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_dithertest[0]),	"rdpcov_dithertest",
	rdpcov_testCaseProc43, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_dithertest[0]),	"rdpcov_dithertest",
	rdpcov_testCaseProc44, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpcov_dithertest[0]),	"rdpcov_dithertest", 	/* test 45 */
	rdpcov_testCaseProc45, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_dithertest[0]),	"rdpcov_dithertest",
	rdpcov_testCaseProc46, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_dithertest[0]),	"rdpcov_dithertest",
	rdpcov_testCaseProc47, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_dithertest[0]),	"rdpcov_dithertest",
	rdpcov_testCaseProc48, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpcov_dithertest[0]),	"rdpcov_dithertest",
	rdpcov_testCaseProc49, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpcov_CSEWcritical_list[0]),"rdpcov_CSEWcritical_list",/* test 50 */
	rdpcov_testCaseProc4, G_IM_SIZ_16b, CLEAR_AQUA,

    /* Last entry must be NULL, so we can count them in main.c */
    (Gfx *) NULL,	"",		(CaseProc_t) NULL,
	G_IM_SIZ_16b, CLEAR_AQUA,
};
