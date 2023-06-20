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
 * File:	toplevel.c
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:	Contains common top level DL routines for setting up the
 *		RSP/RDP's rendering pipe.
 *
 *
 * This application is a test-bed of single frame tests for RDP
 * verification. The idea is that each frame of rendering stresses a 
 * particular module in a unique way, to boost overall fault coverage.
 *
 * Depending on the test you write, you may need to add a new style of RSP/RDP
 * initialization if the generic ones provided here don't meet your needs.
 */

#include <ultra64.h>

#include "dldriver.h"

extern int generateFullSync;	/* from main.c */

/* procedure to do the work for placebo case: */
void
testCasePlacebo(Dynamic *dynamicp, Gfx *module_test)
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

    gSPPerspNormalize(glistp++, dynamicp->perspNorm);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
	gDPFullSync(glistp++);
    } else {
	gDPPipeSync(glistp++);
    }
}

/* procedure to do the work with simple ortho projection: */
void
testCaseProcSimpleOrtho(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guOrtho(&dynamicp->projection,
	    0, SCREEN_WD,
	    0, SCREEN_HT, -100, 100, 1.0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync) {
	gDPFullSync(glistp++);
    } else {
	gDPPipeSync(glistp++);
    }
}

/* procedure to do the work with right side up ortho projection: */
void
testCaseProcRSUOrtho(Dynamic *dynamicp, Gfx *module_test)
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

    if (generateFullSync) {
	gDPFullSync(glistp++);
    } else {
	gDPPipeSync(glistp++);
    }
}

/* procedure to do the work with simple Z ortho projection: */
void
testCaseProcZOrtho(Dynamic *dynamicp, Gfx *module_test)
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

    if (generateFullSync) {
	gDPFullSync(glistp++);
    } else {
	gDPPipeSync(glistp++);
    }
}

void
testCaseSimpleLookAt(Dynamic *dynamicp, Gfx *module_test)
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
		   
    if (generateFullSync) {
	gDPFullSync(glistp++);
    } else {
	gDPPipeSync(glistp++);
    }
}

void
testCaseLookAtReflect(Dynamic *dynamicp, Gfx *module_test)
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
		   
    if (generateFullSync) {
	gDPFullSync(glistp++);
    } else {
	gDPPipeSync(glistp++);
    }
}

void
testCaseProcASOrtho(Dynamic *dynamicp, Gfx *module_test)
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

    if (generateFullSync) {
	gDPFullSync(glistp++);
    } else {
	gDPPipeSync(glistp++);
    }
}

void
testCasePerspectiveTex(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    u16   		perspNorm;


    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 100, 4000, 1.0);
    guLookAt(&dynamicp->viewing, 
	     0, 50, 250, 0, 0, 0, 0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 0.0, 1.0, 0.0);

    /*
    theta += 10.0;
    */

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

/* procedure to set video mode (uses placebo case) */
void
testCaseProcVideo(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

/*
    osViSetMode(&osViModeTable[OS_VI_NTSC_LPN2]);
*/

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

    if (generateFullSync) {
	gDPFullSync(glistp++);
    } else {
	gDPPipeSync(glistp++);
    }
}

void
testCaseBigOrtho(Dynamic *dynamicp, Gfx *module_test)
{
    gSPDisplayList(glistp++, bigscreen_viewport);

    guOrtho(&dynamicp->projection,
	    0, 1023,
	    0, 1023, -1, 1, 1.0);
    guScale(&dynamicp->viewing,
                1,1,1);
    guScale(&dynamicp->modeling,
                1,1,1);

    gSPMatrix(glistp++, &(dynamicp->projection),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->viewing),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync) {
	gDPFullSync(glistp++);
    } else {
	gDPPipeSync(glistp++);
    }
}

void
testCaseRGBA32tex(Dynamic *dynamicp, Gfx *module_test)
{
    static float        theta = -17.0;

    guOrtho(&dynamicp->projection,
            -SCREEN_WD/2.0, SCREEN_WD/2.0,
            -SCREEN_HT/2.0, SCREEN_HT/2.0, -1, 1, 1.0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync) {
	gDPFullSync(glistp++);
    } else {
	gDPPipeSync(glistp++);
    }
    /*
     * Bump theta up to generate different ds/dx, dt/dy
    theta += 5.0;
     */
}
