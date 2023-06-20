
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
#include "gng.h"
#include "rdpew.h"
#include "cs.h"

static float	xrot34 = 0, yrot34 = 0, zrot34 = 0;
static float 	frame35 = 0.0;

/* procedure to do the work for placebo case: */
void
rdpew_testCasePlacebo(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);
    guLookAt(&dynamicp->viewing, 
	     0, 0, 200, 0, 0, 0, 0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->viewing),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->modeling),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, perspNorm);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/* procedure to do the work for test 0: */
void
rdpew_testCaseProc0(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);
    guLookAt(&dynamicp->viewing, 
	     0, 0, 200, 0, 0, 0, 0, 1, 0);
    /*
	     200, 200, 200, 0, 0, 0, 0, 1, 0);
     */

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->viewing),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->modeling),
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
rdpew_testCaseProc1(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpew_testCaseProc2(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);
		  
    guLookAt(&dynamicp->viewing, 
	     0, 0, 0,
	     0, 0, -200,
	     0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->viewing),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->modeling),
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
rdpew_testCaseProc3(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guOrtho(&dynamicp->projection,
	    -SCREEN_WD/2.0, SCREEN_WD/2.0,
	    -SCREEN_HT/2.0, SCREEN_HT/2.0, -1, 1, 1.0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &dynamic.modeling,
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpew_testCaseProc4(Dynamic *dynamicp, Gfx *module_test)
{
    guOrtho(&dynamicp->projection,
                -100,100,-100,100,-100,100, 1.0);
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

/* procedure to do the work for test 5: */
void
rdpew_testCaseProc5(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guOrtho(&dynamicp->projection,
	    0, SCREEN_WD,
	    0, SCREEN_HT, -1, 1, 1.0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->modeling),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/* procedure to do the work for test 6: */
void
rdpew_testCaseProc6(Dynamic *dynamicp, Gfx *module_test)
{
    guOrtho(&dynamicp->projection,
	    0, SCREEN_WD,
	    0, SCREEN_HT, -1, 1, 1.0);

    guScale(&dynamicp->modeling, 1.0, 1.0, 1.0);

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->modeling),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/* procedure to do the work for test 7: */
void
rdpew_testCaseProc7(Dynamic *dynamicp, Gfx *module_test)
{
    guOrtho(&dynamicp->projection,
	    0, SCREEN_WD,
	    0, SCREEN_HT, -1, 1, 1.0);

    guTranslate(&dynamicp->modeling, 0.25, 0.25, 0.0);

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->modeling),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpew_testCaseProc8(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);
		  
    guLookAt(&dynamicp->viewing, 
	     0, 0, 0,
	     0, 0, -200,
	     0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->viewing),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->modeling),
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
rdpew_testCaseProc10(Dynamic *dynamicp, Gfx *module_test)
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
rdpew_testCaseProc15(Dynamic *dynamicp, Gfx *module_test)
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

static Vp vp640 = {
        640*2, 480*2, G_MAXZ/2, 0,  /* scale */
        640*2, 480*2, G_MAXZ/2, 0,  /* translate */
};
void
rdpew_testCaseProc640(Dynamic *dynamicp, Gfx *module_test)
{
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

#define PERIOD                  5
#define INIT_RADIUS             50
#define SAMPLE_PER_ROTATION     50
#define	MISC_COMMANDS		128

Gfx rdpew_gpoints[(PERIOD*SAMPLE_PER_ROTATION + MISC_COMMANDS) * 4];
Gfx *rdpew_glocalp;

void
rdpew_do_spiral(int nsamples, int xoff, int yoff, int incl_x, int incl_y)
{
	float   dradius = (float)INIT_RADIUS / (float)PERIOD /
		 (float)SAMPLE_PER_ROTATION;
	float   dangle = 2.0 * M_PI / SAMPLE_PER_ROTATION;

	int     i;
	float   angle = 0;
	float   radius = INIT_RADIUS;
	int	x, y;

	for (i=0; i<nsamples; i++) {
		x = (int)(radius * cosf(angle) + 0.5);
		y = (int)(radius * sinf(angle) + 0.5);
		x += xoff;
		y += yoff;
		gDPFillRectangle(rdpew_glocalp++, x, y, (x+incl_x), (y+incl_y));
		radius -= dradius;
		angle += dangle;
	}
}

void
rdpew_testCaseParticle(Dynamic *dynamicp, Gfx *module_test)
{
    int nsamples = SAMPLE_PER_ROTATION * PERIOD;

    rdpew_glocalp = &rdpew_gpoints[0];

    guOrtho(&dynamicp->projection,
	    0, SCREEN_WD,
	    0, SCREEN_HT, -1, 1, 1.0);

    guScale(&dynamicp->viewing,
                1,1,1);
    guScale(&dynamicp->modeling,
                1,1,1);

    gSPMatrix(rdpew_glocalp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(rdpew_glocalp++, &(dynamicp->modeling),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    /*
     * Turn off non overlap primitive mode
     */
    gDPPipeSync(rdpew_glocalp++);
    gDPPipelineMode(rdpew_glocalp++, G_PM_NPRIMITIVE);

    /*
     * Do fill mode Spiral
     */
    gDPPipeSync(rdpew_glocalp++);
    gDPSetCycleType(rdpew_glocalp++, G_CYC_FILL);
    gDPSetFillColor(rdpew_glocalp++,	GPACK_RGBA5551(0x00,0xff,0x00,1) << 16 |
				GPACK_RGBA5551(0x00,0xff,0x00,1));
    rdpew_do_spiral(nsamples, SCREEN_WD*1/2, SCREEN_HT*1/2, 0, 0);

#ifdef XXX

/*
 * Don't need to do particle systems in 1 and 2 clock mode since we are
 * subpixel sampling and would need to give the points "size".
 */
    /*
     * Do 1 clock Spiral
     */
    gDPPipeSync(rdpew_glocalp++);
    gDPSetCycleType(rdpew_glocalp++, G_CYC_1CYCLE);
    gDPSetPrimColor(rdpew_glocalp++, 0, 0, 0xff, 0xff, 0x00, 0xff);
    gDPSetCombineMode(rdpew_glocalp++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    rdpew_do_spiral(nsamples, SCREEN_WD*3/4, SCREEN_HT*1/4, 0, 0);

    /*
     * Do 2 clock Spiral
     */
    gDPPipeSync(rdpew_glocalp++);
    gDPSetCycleType(rdpew_glocalp++, G_CYC_2CYCLE);
    gDPSetPrimColor(rdpew_glocalp++, 0, 0, 0x00, 0xff, 0xff, 0xff);
    gDPSetCombineMode(rdpew_glocalp++, G_CC_PRIMITIVE, G_CC_PASS2);
    gDPSetRenderMode(rdpew_glocalp++, G_RM_PASS, G_RM_OPA_SURF2)
    rdpew_do_spiral(nsamples, SCREEN_WD*1/4, SCREEN_HT*3/4, 0, 0);
#endif

    /*
     * The full pipe sync must occur before the end display list request,
     * otherwise it won't get appended to the display list.
     */
    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
    gSPEndDisplayList(rdpew_glocalp++);

    gSPDisplayList(glistp++, rdpew_gpoints);
}

/*
 * basic rectangles for the iosim random environment
 *
 * Thu Dec  1 21:24:22 PST 1994
 */

#define SAMPLES     		15
#undef INIT_RADIUS
#define INIT_RADIUS             40

void
rdpew_do_spiral2(int nsamples, int xoff, int yoff, int incl_x, int incl_y)
{
	float   dradius = 0.0;
	float   dangle = 2.0 * M_PI / SAMPLES;

	int     i;
	float   angle = 0;
	float   radius = INIT_RADIUS;
	int	x, y;
	int	xsize, ysize;

	xsize = SAMPLES-1;
	ysize = SAMPLES-1;

	for (i=0; i<nsamples; i++) {
		x = (int)(radius * cosf(angle) + 0.5);
		y = (int)(radius * sinf(angle) + 0.5);
		x += xoff;
		y += yoff;

		gDPFillRectangle(rdpew_glocalp++, x, y, (x+xsize+incl_x), (y+ysize+incl_y));

		radius -= dradius;
		angle += dangle;
		xsize--;
		ysize--;
	}
}

void
rdpew_testCaseFillParticle(Dynamic *dynamicp, Gfx *module_test)
{
    rdpew_glocalp = &rdpew_gpoints[0];

    guOrtho(&dynamicp->projection,
	    0, SCREEN_WD,
	    0, SCREEN_HT, -1, 1, 1.0);

    guScale(&dynamicp->viewing,
                1,1,1);
    guScale(&dynamicp->modeling,
                1,1,1);

    gSPMatrix(rdpew_glocalp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(rdpew_glocalp++, &(dynamicp->modeling),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    /*
     * Turn off non overlap primitive mode
     */
    gDPPipeSync(rdpew_glocalp++);
    gDPPipelineMode(rdpew_glocalp++, G_PM_NPRIMITIVE);

    /*
     * Do fill mode Spiral
     */
    gDPPipeSync(rdpew_glocalp++);
    gDPSetCycleType(rdpew_glocalp++, G_CYC_FILL);
    gDPSetFillColor(rdpew_glocalp++, GPACK_RGBA5551(0xff, 0x00, 0xff, 1) << 16 |
	GPACK_RGBA5551(0xff, 0x00, 0xff, 1));


    rdpew_do_spiral2(SAMPLES, SCREEN_WD*1/4, SCREEN_HT*1/4, 0, 0);
    rdpew_do_spiral2(SAMPLES, SCREEN_WD*3/4, SCREEN_HT*1/4, 0, 0);
    rdpew_do_spiral2(SAMPLES, SCREEN_WD*1/4, SCREEN_HT*3/4, 0, 0);
    rdpew_do_spiral2(SAMPLES, SCREEN_WD*3/4, SCREEN_HT*3/4, 0, 0);

    /*
     * The full pipe sync must occur before the end display list request,
     * otherwise it won't get appended to the display list.
     */
    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
    gSPEndDisplayList(rdpew_glocalp++);

    gSPDisplayList(glistp++, rdpew_gpoints);
}

/*
 * draws a skull...
 *
 */
void
rdpew_testCaseProc30(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0;
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 200, 2800, 1.0);

    guLookAt(&dynamicp->viewing, 
	     50, 50, 500,
	     0, 0, 0,
	     0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 0.0, 1.0, 0.0);

/*    theta += 10.0;*/

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->viewing),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->modeling),
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
 * draws a vw...
 *
 */
void
rdpew_testCaseProc31(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 30;
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 200, 2800, 1.0);

    guLookAt(&dynamicp->viewing, 
	     50, 150, 500,
	     0, 50, 0,
	     0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 0.0, 1.0, 0.0);

/*    theta += 10.0;*/

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->viewing),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->modeling),
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
 * draws a cow...
 *
 */
void
rdpew_testCaseProc32(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0;
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 200, 2800, 1.0);

    guLookAt(&dynamicp->viewing, 
	     50, 150, 500,
	     0, 50, 0,
	     0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 0.0, 1.0, 0.0);

/*    theta += 10.0;*/

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->viewing),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->modeling),
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
 * draws a skull, a vw, and a cow...
 *
 */
void
rdpew_testCaseProc33(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0;
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 200, 2800, 1.0);

    guLookAt(&dynamicp->viewing, 
	     0, 100, 500,
	     0, 0, 0,
	     0, 1, 0);

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->viewing),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    guRotate(&dynamicp->modeling, theta, 0.0, 1.0, 0.0);

    gSPMatrix(glistp++, &(dynamicp->modeling),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, perspNorm);

/*    theta += 10.0; */


    guTranslate(&dynamicp->skull, 0.0, -60.0, 0.0);
    gSPMatrix(glistp++, &(dynamicp->skull),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    gSPDisplayList(glistp++, &(rdpew_skull_dl[0]));
    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);

    guRotate(&dynamicp->vw, 60, 0.0, 1.0, 0.0);
    gSPMatrix(glistp++, &(dynamicp->vw),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    gSPDisplayList(glistp++, &(rdpew_vw_dl[0]));
    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);

    guTranslate(&dynamicp->cow, -100.0, 0.0, 75.0);
    gSPMatrix(glistp++, &(dynamicp->cow),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    gSPDisplayList(glistp++, &(rdpew_cow_dl[0]));
    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/*
 * draws a paper clip...
 *
 */
void
rdpew_testCaseProc34(Dynamic *dynamicp, Gfx *module_test)
{
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 200, 2800, 1.0);

    guLookAt(&dynamicp->viewing, 
	     0, 0, 500,
	     0, 0, 0,
	     0, 1, 0);

    gSPPerspNormalize(glistp++, perspNorm);

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->viewing),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);


    guRotate(&dynamicp->modeling, zrot34, 0.0, 0.0, 1.0);
    gSPMatrix(glistp++, &(dynamicp->modeling),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    guRotate(&dynamicp->cow, yrot34, 0.0, 1.0, 0.0);
    gSPMatrix(glistp++, &(dynamicp->cow),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    guRotate(&dynamicp->vw, xrot34, 1.0, 0.0, 0.0);
    gSPMatrix(glistp++, &(dynamicp->vw),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }

}


void
rdpew_testCaseProc40(Dynamic *dynamicp, Gfx *module_test)
{
    xrot34 = 0.0;
    yrot34 = 0.0;
    zrot34 = 0.0;

   rdpew_testCaseProc34(dynamicp, module_test);

}

void
rdpew_testCaseProc41(Dynamic *dynamicp, Gfx *module_test)
{
    xrot34 = 0.5;
    yrot34 = 1.0;
    zrot34 = 0.5;

   rdpew_testCaseProc34(dynamicp, module_test);

}

void
rdpew_testCaseProc42(Dynamic *dynamicp, Gfx *module_test)
{
    xrot34 = 1.0;
    yrot34 = 2.0;
    zrot34 = 1.0;

   rdpew_testCaseProc34(dynamicp, module_test);

}

void
rdpew_testCaseProc43(Dynamic *dynamicp, Gfx *module_test)
{
    xrot34 = 1.5;
    yrot34 = 3.0;
    zrot34 = 1.5;

   rdpew_testCaseProc34(dynamicp, module_test);

}

void
rdpew_testCaseProc44(Dynamic *dynamicp, Gfx *module_test)
{
    xrot34 = 2.0;
    yrot34 = 4.0;
    zrot34 = 2.0;

   rdpew_testCaseProc34(dynamicp, module_test);

}

void
rdpew_testCaseProc45(Dynamic *dynamicp, Gfx *module_test)
{
    xrot34 = 2.5;
    yrot34 = 5.0;
    zrot34 = 2.5;

   rdpew_testCaseProc34(dynamicp, module_test);

}

void
rdpew_testCaseProc46(Dynamic *dynamicp, Gfx *module_test)
{
    xrot34 = 3.0;
    yrot34 = 6.0;
    zrot34 = 3.0;

   rdpew_testCaseProc34(dynamicp, module_test);

}

void
rdpew_testCaseProc47(Dynamic *dynamicp, Gfx *module_test)
{
    xrot34 = 3.5;
    yrot34 = 7.0;
    zrot34 = 3.5;

   rdpew_testCaseProc34(dynamicp, module_test);

}

void
rdpew_testCaseProc48(Dynamic *dynamicp, Gfx *module_test)
{
    xrot34 = 4.0;
    yrot34 = 8.0;
    zrot34 = 4.0;

   rdpew_testCaseProc34(dynamicp, module_test);

}

void
rdpew_testCaseProc49(Dynamic *dynamicp, Gfx *module_test)
{
    xrot34 = 4.5;
    yrot34 = 9.0;
    zrot34 = 4.5;

   rdpew_testCaseProc34(dynamicp, module_test);

}

/*
 * draws a rocking chair.
 *
 */
void
rdpew_testCaseProc35(Dynamic *dynamicp, Gfx *module_test)
{
    static float	xrot = 0.0, yrot = 45.0, zrot = 0;
    int			i;
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 100, 2800, 1.0);

    guLookAt(&dynamicp->viewing, 
	     -400, 500, -800,
	     0, 100, 0,
	     0, 1, 0);

    gSPPerspNormalize(glistp++, perspNorm);

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    xrot = (((float)frame35/30.0) * 20.0) - 10.0;

    /* chair floor */
    gSPMatrix(glistp++, &(dynamicp->viewing),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    guRotate(&dynamicp->vw, -28.0, 0.0, 1.0, 0.0);

    gSPMatrix(glistp++, &(dynamicp->vw),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPDisplayList(glistp++, &(rdpew_chair_floor_dl[0]));

    /* the chair */
    gSPMatrix(glistp++, &(dynamicp->viewing),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    /* rock the chair */
    guRotate(&dynamicp->cow, xrot, 0.0, 0.0, 1.0);
    gSPMatrix(glistp++, &(dynamicp->cow),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    /* move chair to the floor */
    guTranslate(&dynamicp->skull, 57.0, 220.0, 0.0);
    gSPMatrix(glistp++, &(dynamicp->skull),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    /* line up chair with x axis: */
    guRotate(&dynamicp->modeling, yrot, 0.0, 1.0, 0.0);
    gSPMatrix(glistp++, &(dynamicp->modeling),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &(rdpew_chair_dl[0]));

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpew_testCaseProc50(Dynamic *dynamicp, Gfx *module_test)
{
   frame35 = 0.0;
   rdpew_testCaseProc35(dynamicp, module_test);
}

void
rdpew_testCaseProc51(Dynamic *dynamicp, Gfx *module_test)
{
   frame35 = 1.0;
   rdpew_testCaseProc35(dynamicp, module_test);
}

void
rdpew_testCaseProc52(Dynamic *dynamicp, Gfx *module_test)
{
   frame35 = 2.0;
   rdpew_testCaseProc35(dynamicp, module_test);
}

void
rdpew_testCaseProc53(Dynamic *dynamicp, Gfx *module_test)
{
   frame35 = 3.0;
   rdpew_testCaseProc35(dynamicp, module_test);
}

void
rdpew_testCaseProc54(Dynamic *dynamicp, Gfx *module_test)
{
   frame35 = 4.0;
   rdpew_testCaseProc35(dynamicp, module_test);
}

void
rdpew_testCaseProc55(Dynamic *dynamicp, Gfx *module_test)
{
   frame35 = 5.0;
   rdpew_testCaseProc35(dynamicp, module_test);
}

void
rdpew_testCaseProc56(Dynamic *dynamicp, Gfx *module_test)
{
   frame35 = 6.0;
   rdpew_testCaseProc35(dynamicp, module_test);
}

void
rdpew_testCaseProc57(Dynamic *dynamicp, Gfx *module_test)
{
   frame35 = 7.0;
   rdpew_testCaseProc35(dynamicp, module_test);
}

void
rdpew_testCaseProc58(Dynamic *dynamicp, Gfx *module_test)
{
   frame35 = 8.0;
   rdpew_testCaseProc35(dynamicp, module_test);
}

void
rdpew_testCaseProc59(Dynamic *dynamicp, Gfx *module_test)
{
   frame35 = 9.0;
   rdpew_testCaseProc35(dynamicp, module_test);
}

/*
 * draws a b25...
 *
 */
void
rdpew_testCaseProc36(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 45;
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 200, 2800, 1.0);

    guLookAt(&dynamicp->viewing, 
	     50, 50, 600,
	     0, 0, 0,
	     0, 1, 0);

    gSPPerspNormalize(glistp++, perspNorm);

    guRotate(&dynamicp->modeling, theta, 0.9, 0.5, 0.5);

    theta += 10.0;

    gSPMatrix(glistp++, &(dynamicp->projection),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->viewing),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, &(dynamicp->modeling),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

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
 * the corresponding rdpew_testCaseProc doesn't use. But you still
 * need to put a NULL entry here in the table.
 *
 * It is a good idea to put your name beside the test, so others
 * can track you down with questions.
 *
 */
GfxTest_t testList_rdpew[] = {	/* list of specific test Gfx display lists: */
    &(rdpew_square0[0]), "square0",		/* Test 0 */
	rdpew_testCaseProc0, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_placebo_dl[0]), "placebo_dl",
	rdpew_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_triangles[0]), "triangles",
	rdpew_testCaseProc2, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_placebo_dl[0]), "placebo_dl",
	rdpew_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_triangle4[0]), "triangle4",
	rdpew_testCaseProc4, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpew_square5[0]), "square5",		/* Test 5 */
	rdpew_testCaseProc5, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_square6[0]), "square6", 
	rdpew_testCaseProc6, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_square7[0]), "square7",
	rdpew_testCaseProc7, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_fogtriangles[0]), "fogtriangles",
	rdpew_testCaseProc8, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_fogtriangles[0]),	 "fogtriangles",
	rdpew_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpew_triangle10[0]), "triangle10",	/* Test 10*/
	rdpew_testCaseProc10, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_triangle11[0]), "triangle11",
	rdpew_testCaseProc10, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_triangle12[0]), "triangle12",
	rdpew_testCaseProc10, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_triangle13[0]), "triangle13",
	rdpew_testCaseProc10, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_hires_image_test[0]), "hires_image_test",
	rdpew_testCaseProc640, 640, CLEAR_AQUA,

    &(rdpew_placebo_dl[0]), "placebo_dl",
	rdpew_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_triangle16[0]),"triangle16",
	rdpew_testCaseProc10, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_triangle17[0]), "triangle17",
	rdpew_testCaseProc10, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_triangle18[0]), "triangle18",
	rdpew_testCaseProc10, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_triangle19[0]), "triangle19",
	rdpew_testCaseProc10, G_IM_SIZ_32b, CLEAR_BLACK,

    &(rdpew_triangle20[0]), "triangle20",	/* Test 20*/
	rdpew_testCaseProc10, G_IM_SIZ_8b, CLEAR_BLACK,
    &(rdpew_triangle21[0]), "triangle21",
	rdpew_testCaseProc10, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_triangle22[0]), "triangle22",
	rdpew_testCaseProc10, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_triangle23[0]), "triangle23",
	rdpew_testCaseProc10, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_triangle24[0]), "triangle24",
	rdpew_testCaseProc10, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpew_triangle25[0]), "triangle25",	/* Test 25*/
	rdpew_testCaseProc10, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_placebo_dl[0]), "placebo_dl",
	rdpew_testCaseParticle, G_IM_SIZ_16b, CLEAR_BLACK,
/*
    &(rdpew_placebo_dl[0]), "placebo_dl",
	rdpew_testCaseFillParticle, G_IM_SIZ_16b, CLEAR_BLACK,
*/
    &(rdpew_placebo_dl[0]), "placebo_dl",
	rdpew_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_placebo_dl[0]), "placebo_dl",
	rdpew_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_placebo_dl[0]), "placebo_dl",
	rdpew_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpew_skull_dl[0]), "skull_dl",	/* Test 30*/
	rdpew_testCaseProc30, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_vw_dl[0]), "vw_dl",
	rdpew_testCaseProc31, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_cow_dl[0]), "cow_dl",
	rdpew_testCaseProc32, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_placebo_dl[0]), "placebo_dl",
	rdpew_testCaseProc33, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_placebo_dl[0]), "placebo_dl",
	rdpew_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpew_placebo_dl[0]), "placebo_dl",	/* Test 35 */
	rdpew_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_b25_dl[0]), "b25_dl",
	rdpew_testCaseProc36, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_placebo_dl[0]), "placebo_dl",
	rdpew_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_placebo_dl[0]), "placebo_dl",
	rdpew_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_placebo_dl[0]), "placebo_dl",
	rdpew_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpew_clip_dl[0]), "clip_dl",
	rdpew_testCaseProc40, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_clip_dl[0]), "clip_dl",
	rdpew_testCaseProc41, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_clip_dl[0]), "clip_dl",
	rdpew_testCaseProc42, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_clip_dl[0]), "clip_dl",
	rdpew_testCaseProc43, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_clip_dl[0]), "clip_dl",
	rdpew_testCaseProc44, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpew_clip_dl[0]), "clip_dl",
	rdpew_testCaseProc45, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_clip_dl[0]), "clip_dl",
	rdpew_testCaseProc46, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_clip_dl[0]), "clip_dl",
	rdpew_testCaseProc47, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_clip_dl[0]), "clip_dl",
	rdpew_testCaseProc48, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_clip_dl[0]), "clip_dl",
	rdpew_testCaseProc49, G_IM_SIZ_16b, CLEAR_BLACK,


    &(rdpew_chair_dl[0]), "chair_dl",	/* Test 50*/
	rdpew_testCaseProc50, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_chair_dl[0]), "chair_dl",	/* Test 50*/
	rdpew_testCaseProc51, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_chair_dl[0]), "chair_dl",	/* Test 50*/
	rdpew_testCaseProc52, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_chair_dl[0]), "chair_dl",	/* Test 50*/
	rdpew_testCaseProc53, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_chair_dl[0]), "chair_dl",	/* Test 50*/
	rdpew_testCaseProc54, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdpew_chair_dl[0]), "chair_dl",	/* Test 50*/
	rdpew_testCaseProc55, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_chair_dl[0]), "chair_dl",	/* Test 50*/
	rdpew_testCaseProc56, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_chair_dl[0]), "chair_dl",	/* Test 50*/
	rdpew_testCaseProc57, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_chair_dl[0]), "chair_dl",	/* Test 50*/
	rdpew_testCaseProc58, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdpew_chair_dl[0]), "chair_dl",	/* Test 50*/
	rdpew_testCaseProc59, G_IM_SIZ_16b, CLEAR_BLACK,

    /* add cases above here: */
 (Gfx *) NULL,       "",             (CaseProc_t) NULL,
        G_IM_SIZ_16b, CLEAR_BLACK,

};
