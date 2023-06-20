/**************************************************************************
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
 * File:	rdpatt.c
 * Creator:	hal@sgi.com
 * Purpose:	dynamic DL tests for rdp attribute testing
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
 * a few simple things in the files rdpatt.h, rdpatt.c, rdpatt_static.c.
 *
 * All locations are marked with comments that say "ADD TEST CASE"
 * and give some hints what you need to do there. See main.c for
 * detailed instructions.
 *
 */

#include <ultra64.h>

#include "dldriver.h"
#include "gng.h"
#include "rdpatt.h"
#include "cs.h"

float ff = 0.0;
int  randSeed = 1234;

/* procedure to do the work for placebo case: */
void
rdpatt_testCasePlacebo(Dynamic *dynamicp, Gfx *module_test)
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
rdpatt_testCaseProc0(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 10.0;

    guPerspective(&dynamicp->projection, &(dynamicp->perspNorm),
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

    gSPPerspNormalize(glistp++, dynamicp->perspNorm);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpatt_testCaseProc1(Dynamic *dynamicp, Gfx *module_test)
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
rdpatt_testCaseProc2(Dynamic *dynamicp, Gfx *module_test)
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
rdpatt_testCaseProc3(Dynamic *dynamicp, Gfx *module_test)
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
rdpatt_testCaseProc4(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guPerspective(&dynamicp->projection, &(dynamicp->perspNorm),
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

    gSPPerspNormalize(glistp++, dynamicp->perspNorm);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }

}

void
rdpatt_testCaseProc5(Dynamic *dynamicp, Gfx *module_test)
{
    static float        theta = 0.0;

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

void
rdpatt_testCaseProc6(Dynamic *dynamicp, Gfx *module_test)
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

void
rdpatt_testCaseProc7(Dynamic *dynamicp, Gfx *module_test)
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

void
rdpatt_testCaseProc8(Dynamic *dynamicp, Gfx *module_test)
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

/* procedure to do the work for test 9: */
void
rdpatt_testCaseProc9(Dynamic *dynamicp, Gfx *module_test)
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

/* procedure to do the work for test 10: */
void
rdpatt_testCaseProc10(Dynamic *dynamicp, Gfx *module_test)
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

void
rdpatt_testCaseProc11(Dynamic *dynamicp, Gfx *module_test)
{
    static float        theta = 0.0;

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

void
rdpatt_testCaseProc12(Dynamic *dynamicp, Gfx *module_test)
{
    static float        theta = 0.0;

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

void
rdpatt_testCaseProc13(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

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
rdpatt_testCaseProc14(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guOrtho(&dynamicp->projection,
                0,320,239,0,-1,1, 1.0);
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
rdpatt_testCaseProc20(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guPerspective(&dynamicp->projection, &(dynamicp->perspNorm),
		  33, 320.0/240.0, 100, 4096, 1.0);
		  
    guLookAt(&dynamicp->viewing, 
	     0, 0, 200,
	     0, 0, 0,
	     0, 1, 0);

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

/* procedure to do the work for test 21: */
void
rdpatt_testCaseProc21(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guPerspective(&dynamicp->projection, &(dynamicp->perspNorm),
		  33, 320.0/240.0, 100, 4000, 1.0);
    guLookAt(&dynamicp->viewing, 
	     50, 50, 200, 0, 0, 0, 0, 1, 0);

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
rdpatt_testCaseProc22(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guOrtho(&dynamicp->projection,
                0,320,239,0,-1,1, 1.0);
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

/***********************************************************
 *  Stuff for flight path generation, Frame 30
/***********************************************************
 */

#define MAX_FP_SIZE     30
#define ARRAY_SIZE      (sizeof(vpx) / sizeof(float))

/*
 *  Determine cubic coefficients for set of points given in
 *  t,y.  Results returned in z.  Number of points is n.
 */

static void
  find_spline_coeffs( int n, float *t, float *y, float *z)
{
  float h[MAX_FP_SIZE],
        b[MAX_FP_SIZE],
        u[MAX_FP_SIZE],
        v[MAX_FP_SIZE];
  int   i;

  for(i = 0; i < n; i++)
  {
    h[i] = t[(i+1)%n] - t[i];
    b[i] = (y[(i+1)%n] - y[i]) / h[i];
  }

  u[1] = 2.0 * (h[0] + h[1]);
  v[1] = 6.0 * (b[1] - b[0]);

  for( i = 2; i < n-1; i++)
  {
    u[i] = 2.0 * (h[i] + h[i-1]) - (h[i-1] * h[i-1]) / u[i-1];
    v[i] = 6.0 * (b[i] - b[i-1]) - (h[i-1] * v[i-1]) / u[i-1];
  }

  z[n-1] = 0.0;

  for(i = n-2; i >= 1; i--)
    z[i] = (v[i] - h[i] * z[(i+1)%n]) / u[i];

  z[0] = 0.0;

}

/*
 *  Evaluate cubic spline at given point.
 *  First determines the interval in t containing x and then
 *  returns Si(x) using nested form of cubic polynomial.
 */
static float
  eval_spline(int n, float *t, float *y, float *z, float x)
{
  float h, b, p, diff;
  int i;

  for(i = n-2; i >= 0; i--)
  {
    diff = x - t[i];
    if(diff >= 0.0)
      break;
  }

  h = t[i+1] - t[i];
  b = ((y[i+1] - y[i]) / h) - h * (z[i+1] + 2.0 * z[i]) / 6.0;
  p = 0.5 * z[i] + diff * (z[i+1] - z[i]) / (6.0 * h);
  p = b + diff * p;
  return(y[i] + diff * p);
}

/*
 *  Create a little database of interesting shapes
 *  that we can fly around in.
 */


void
rdpatt_testCaseProcFly(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = -90.0;
    /*
     *  Enter your flight path way points here
     */
    static float frame[] = {0, 	15, 	31};
    static float   vpx[] = {50, 	-40, 	10};
    static float   vpy[] = {300, 	30, 	300};
    static float   vpz[] = {600, 	370, 	200};
    static float   atx[] = {0, 	-110, 	0};
    static float   aty[] = {50, 	10, 	0};
    static float   atz[] = {0, 	195, 	0};
    static float   upx[] = {0, -0.173648, 0.173648};
    static float   upy[] = {1, 0.9848077, 0.9848077};
    static float   upz[] = {0, 0, 	0};

    static float vpx_c[ARRAY_SIZE];
    static float vpy_c[ARRAY_SIZE];
    static float vpz_c[ARRAY_SIZE];
    static float atx_c[ARRAY_SIZE];
    static float aty_c[ARRAY_SIZE];
    static float atz_c[ARRAY_SIZE];
    static float upx_c[ARRAY_SIZE];
    static float upy_c[ARRAY_SIZE];
    static float upz_c[ARRAY_SIZE];


    float rvpx, rvpy, rvpz;
    float ratx, raty, ratz;
    float rupx, rupy, rupz;


    guPerspective(&dynamicp->projection, &(dynamicp->perspNorm),
		  33, 320.0/240.0, 200, 2800, 1.0);

    find_spline_coeffs( ARRAY_SIZE, frame, vpx, vpx_c);
    find_spline_coeffs( ARRAY_SIZE, frame, vpy, vpy_c);
    find_spline_coeffs( ARRAY_SIZE, frame, vpz, vpz_c);
    find_spline_coeffs( ARRAY_SIZE, frame, atx, atx_c);
    find_spline_coeffs( ARRAY_SIZE, frame, aty, aty_c);
    find_spline_coeffs( ARRAY_SIZE, frame, atz, atz_c);
    find_spline_coeffs( ARRAY_SIZE, frame, upx, upx_c);
    find_spline_coeffs( ARRAY_SIZE, frame, upy, upy_c);
    find_spline_coeffs( ARRAY_SIZE, frame, upz, upz_c);

    rvpx = eval_spline(ARRAY_SIZE, frame, vpx, vpx_c, ff);
    rvpy = eval_spline(ARRAY_SIZE, frame, vpy, vpy_c, ff);
    rvpz = eval_spline(ARRAY_SIZE, frame, vpz, vpz_c, ff);
    ratx = eval_spline(ARRAY_SIZE, frame, atx, atx_c, ff);
    raty = eval_spline(ARRAY_SIZE, frame, aty, aty_c, ff);
    ratz = eval_spline(ARRAY_SIZE, frame, atz, atz_c, ff);
    rupx = eval_spline(ARRAY_SIZE, frame, upx, upx_c, ff);
    rupy = eval_spline(ARRAY_SIZE, frame, upy, upy_c, ff);
    rupz = eval_spline(ARRAY_SIZE, frame, upz, upz_c, ff);

    guLookAt(&dynamicp->viewing, 
	     rvpx, rvpy, rvpz,
	     ratx, raty, ratz,
	     rupx, rupy, rupz);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, dynamicp->perspNorm);

    /*   for cone   */
    guRotate(&dynamicp->modeling, theta, 1.0, 0.0, 0.0);

    /* gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 133, 102, 136, 103); */

#ifndef CONE
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdpatt_cone_dl[0]);

#endif /* CONE */


#ifndef TORUS
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    guRotate(&dynamicp->torus, 90.0, 1.0, 0.333, 0.0);
    /* set the y and z translate elements by hand: */
    dynamicp->torus.m[1][2] = 130;
    dynamicp->torus.m[1][3] = (20 << 16) | 1;

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->torus)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdpatt_torus_dl[0]);
#endif /* TORUS */

#ifndef GROUND
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdpatt_ground_dl[0]);

#endif /* GROUND */


#ifndef BOX1

    /*  BOX1, textured box  */
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    guRotate(&dynamicp->box1, 45.0, 1.0, 1.0, 1.0);

    /* set the x, y, and z translate elements by hand: */
    dynamicp->box1.m[1][2] = (50 << 16) | (10);
    dynamicp->box1.m[1][3] = (100 << 16) | 1;

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->box1)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdpatt_box1_dl[0]);
#endif /* BOX1 */


#ifndef ICOSA
    /*   ICOSAHEDRON   translucent objects last */
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    guRotate(&dynamicp->icosa, 90.0, 0.7, 0.8, 0.7);

    /* set the x, y, and z translate elements by hand: */
    dynamicp->icosa.m[1][2] = (40 << 16) | ((u16) -40);
    dynamicp->icosa.m[1][3] = (50 << 16) | 1;

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->icosa)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdpatt_icosa_dl[0]);

#endif /* ICOSA */


#ifndef BOX
    /*  BOX   translucent objects last */
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    guTranslate(&dynamicp->box, -35.0, 50.0, 0.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->box)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdpatt_box_dl[0]);
#endif /* BOX */

    /* for trees */
    guTranslate(&dynamicp->tree, 15.0, 0.0, -50.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

#ifndef TREE0

    gSPDisplayList(glistp++, &rdpatt_tree0_dl[0]);

#endif /* TREE0 */


#ifndef TREE1
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->tree)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdpatt_tree1_dl[0]);
#endif /* TREE1 */


#ifndef TREE2
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->tree)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdpatt_tree2_dl[0]);

#endif /* TREE2 */


#ifndef TREE3
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->tree)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdpatt_tree3_dl[0]);
#endif /* TREE3 */

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpatt_testCaseProc30(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 0.0;
  rdpatt_testCaseProcFly(dynamicp, module_test);

}


void
rdpatt_testCaseProc31(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 1.0;
  rdpatt_testCaseProcFly(dynamicp, module_test);

}

void
rdpatt_testCaseProc32(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 2.0;
  rdpatt_testCaseProcFly(dynamicp, module_test);

}

void
rdpatt_testCaseProc33(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 3.0;
  rdpatt_testCaseProcFly(dynamicp, module_test);

}

void
rdpatt_testCaseProc34(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 4.0;
  rdpatt_testCaseProcFly(dynamicp, module_test);

}

void
rdpatt_testCaseProc35(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 5.0;
  rdpatt_testCaseProcFly(dynamicp, module_test);

}

void
rdpatt_testCaseProc36(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 6.0;
  rdpatt_testCaseProcFly(dynamicp, module_test);

}

/*
 *  Texture edge mode test
 */
void
rdpatt_testCaseProc37(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guPerspective(&dynamicp->projection, &(dynamicp->perspNorm),
		  33, 320.0/240.0, 1, 500, 1.0);

    guLookAt(&dynamicp->viewing, 
	     0, 0, 200, 0, 0, 0, 0, 1, 0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

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

/*
 *  Z-buffer test case
 */
void
rdpatt_testCaseProc38(Dynamic *dynamicp, Gfx *module_test)
{
    guPerspective(&dynamicp->projection, &(dynamicp->perspNorm),
		  33, 320.0/240.0, 10, 4096, 1.0);

    guLookAt(&dynamicp->viewing, 
	     	-40,120, -2048,	/* vp */
		-40, 0, -1660, 	/* look-at */
		0, 1, 0);	/* up */

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, dynamicp->perspNorm);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/*
 *  odd interlaced version of testCaseProc30
 */
void
rdpatt_testCaseProc39(Dynamic *dynamicp, Gfx *module_test)
{
	ff = 0.0; /* set frame num for ProcFly */
	gDPPipeSync(glistp++);
	gDPSetScissor(glistp++, G_SC_ODD_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT-1);
	rdpatt_testCaseProcFly(dynamicp, module_test);
}

/*
 *  even interlaced version of testCaseProc30
 */
void
rdpatt_testCaseProc40(Dynamic *dynamicp, Gfx *module_test)
{
	ff = 0.0; /* set frame num for ProcFly */
	gDPPipeSync(glistp++);
	gDPSetScissor(glistp++, G_SC_EVEN_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT-1);
	rdpatt_testCaseProcFly(dynamicp, module_test);
}

/*
 *  Rolling doughnut animation
 *  Original red_torus_dll was missing so substituted
 *  rdpatt_torus_dl for goNogo test purposes.
 */

void
rdpatt_testCaseProcFly2(Dynamic *dynamicp, Gfx *module_test)
{
  static float	theta = -90.0;
  /*
   *  Enter doughnut path way points here
   */
  static float frame[] = {0, 	15, 	31};
  static float   vpx[] = {50, 	-40, 	10};
  static float   vpy[] = {300, 	30, 	300};
  static float   vpz[] = {600, 	370, 	200};
  static float   atx[] = {0, 	-110, 	0};
  static float   aty[] = {50, 	10, 	0};
  static float   atz[] = {0, 	195, 	0};
  static float   upx[] = {0, -0.173648, 0.173648};
  static float   upy[] = {1, 0.9848077, 0.9848077};
  static float   upz[] = {0, 0, 	0};

  static float vpx_c[ARRAY_SIZE];
  static float vpy_c[ARRAY_SIZE];
  static float vpz_c[ARRAY_SIZE];
  static float atx_c[ARRAY_SIZE];
  static float aty_c[ARRAY_SIZE];
  static float atz_c[ARRAY_SIZE];
  static float upx_c[ARRAY_SIZE];
  static float upy_c[ARRAY_SIZE];
  static float upz_c[ARRAY_SIZE];

  float rvpx, rvpy, rvpz;
  float ratx, raty, ratz;
  float rupx, rupy, rupz;

  find_spline_coeffs( ARRAY_SIZE, frame, vpx, vpx_c);
  find_spline_coeffs( ARRAY_SIZE, frame, vpy, vpy_c);
  find_spline_coeffs( ARRAY_SIZE, frame, vpz, vpz_c);
  find_spline_coeffs( ARRAY_SIZE, frame, atx, atx_c);
  find_spline_coeffs( ARRAY_SIZE, frame, aty, aty_c);
  find_spline_coeffs( ARRAY_SIZE, frame, atz, atz_c);
  find_spline_coeffs( ARRAY_SIZE, frame, upx, upx_c);
  find_spline_coeffs( ARRAY_SIZE, frame, upy, upy_c);
  find_spline_coeffs( ARRAY_SIZE, frame, upz, upz_c);


  rvpx = eval_spline(ARRAY_SIZE, frame, vpx, vpx_c, ff);
  rvpy = eval_spline(ARRAY_SIZE, frame, vpy, vpy_c, ff);
  rvpz = eval_spline(ARRAY_SIZE, frame, vpz, vpz_c, ff);
  ratx = eval_spline(ARRAY_SIZE, frame, atx, atx_c, ff);
  raty = eval_spline(ARRAY_SIZE, frame, aty, aty_c, ff);
  ratz = eval_spline(ARRAY_SIZE, frame, atz, atz_c, ff);
  rupx = eval_spline(ARRAY_SIZE, frame, upx, upx_c, ff);
  rupy = eval_spline(ARRAY_SIZE, frame, upy, upy_c, ff);
  rupz = eval_spline(ARRAY_SIZE, frame, upz, upz_c, ff);


  guLookAt(&dynamicp->modeling, 
	     rvpx, rvpy, rvpz,
	     ratx, raty, ratz,
	     rupx, rupy, rupz);


    guPerspective(&dynamicp->projection, &(dynamicp->perspNorm),
		33, 320.0/240.0, 200, 2800, 1.0);

    guLookAt(&dynamicp->viewing, 
	     0, 0, 200, 0, 0, 0, 0, 1, 0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

/**
    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);
**/

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, dynamicp->perspNorm);

    gSPDisplayList(glistp++, &rdpatt_torus_dl[0]);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}
/* end ProcFly2 */

void
rdpatt_testCaseProc41(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 0.0;
  rdpatt_testCaseProcFly2(dynamicp, module_test);
}

void
rdpatt_testCaseProc42(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 1.0;
  rdpatt_testCaseProcFly2(dynamicp, module_test);
}

void
rdpatt_testCaseProc43(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 2.0;
  rdpatt_testCaseProcFly2(dynamicp, module_test);
}

void
rdpatt_testCaseProc44(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 3.0;
  rdpatt_testCaseProcFly2(dynamicp, module_test);
}

void
rdpatt_testCaseProc45(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 4.0;
  rdpatt_testCaseProcFly2(dynamicp, module_test);
}

void
rdpatt_testCaseProc46(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 5.0;
  rdpatt_testCaseProcFly2(dynamicp, module_test);
}

void
rdpatt_testCaseProc47(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 6.0;
  rdpatt_testCaseProcFly2(dynamicp, module_test);
}

void
rdpatt_testCaseProc48(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 7.0;
  rdpatt_testCaseProcFly2(dynamicp, module_test);
}

void
rdpatt_testCaseProc49(Dynamic *dynamicp, Gfx *module_test)
{
  ff = 8.0;
  rdpatt_testCaseProcFly2(dynamicp, module_test);
}

/*****************************************************
 *  Create a random forest - Test 61-64
 *****************************************************
 */
#define DEFAULT_SEED 		12344
#define NTREES			75
#define NVTXPERTREE		8
#define HEIGHT_RANGE		30
#define WIDTH_RANGE		20
#define MIN_HEIGHT		20
#define MIN_WIDTH		10
#define MIN_RAND_X		-150
#define MAX_RAND_X		150
#define MIN_RAND_Z		-300
#define MAX_RAND_Z		300


Vtx TreesVtx[NTREES*NVTXPERTREE];
static int RandNum = DEFAULT_SEED & (~1);

void
  set_random_seed( int seed )
{
  RandNum = seed & (~1);
}

int
  get_random( void )
{
  RandNum *= (RandNum - 1);
  return(RandNum);
}

unsigned int
  get_rand_color( void )
{
  unsigned int a, b, c;
  a = ((unsigned)get_random() >> 8) & 0xff;
  b = ((unsigned)get_random() >> 8) & 0xff;
  c = ((unsigned)get_random() >> 8) & 0xff;
  if(b > a)
    a = b;
  if(c > a)
    a = c;
  return(a);
}

void
  make_tree( int tree, int x, int z )
{
  unsigned int height, width;
  unsigned char fr = 255, fg = 0, fb = 0; /* face color */
  unsigned int indx = tree*NVTXPERTREE;

  height = (((unsigned)get_random() >> 8) % HEIGHT_RANGE) + MIN_HEIGHT;
  width  = (((unsigned)get_random() >> 8) % WIDTH_RANGE) + MIN_WIDTH;
  fr = get_rand_color();
  fg = get_rand_color();
  fb = get_rand_color();
 
  TreesVtx[indx].v.ob[0]   = -width + x;
  TreesVtx[indx].v.ob[1]   = 0;
  TreesVtx[indx].v.ob[2]   = z;
  TreesVtx[indx].v.tc[0]   = (-31 << 6);
  TreesVtx[indx].v.tc[1]   = 0;
  indx++;
  TreesVtx[indx].v.ob[0]   = width + x;
  TreesVtx[indx].v.ob[1]   = 0;
  TreesVtx[indx].v.ob[2]   = width + z;
  TreesVtx[indx].v.tc[0]   = (31 << 6);
  TreesVtx[indx].v.tc[1]   = 0;
  indx++;
  TreesVtx[indx].v.ob[0]   = width + x;
  TreesVtx[indx].v.ob[1]   = height;
  TreesVtx[indx].v.ob[2]   = width + z;
  TreesVtx[indx].v.tc[0]   = (31 << 6);
  TreesVtx[indx].v.tc[1]   = (63 << 6);
  indx++;
  TreesVtx[indx].v.ob[0]   = -width + x;
  TreesVtx[indx].v.ob[1]   = height;
  TreesVtx[indx].v.ob[2]   = -width + z;
  TreesVtx[indx].v.tc[0]   = (-31 << 6);
  TreesVtx[indx].v.tc[1]   = (63 << 6);
  indx++;
  TreesVtx[indx].v.ob[0]   = -width + x;
  TreesVtx[indx].v.ob[1]   = 0;
  TreesVtx[indx].v.ob[2]   = width + z;
  TreesVtx[indx].v.tc[0]   = (-31 << 6);
  TreesVtx[indx].v.tc[1]   = 0;
  indx++;
  TreesVtx[indx].v.ob[0]   = width + x;
  TreesVtx[indx].v.ob[1]   = 0;
  TreesVtx[indx].v.ob[2]   = -width + z;
  TreesVtx[indx].v.tc[0]   = (31 << 6);
  TreesVtx[indx].v.tc[1]   = 0;
  indx++;
  TreesVtx[indx].v.ob[0]   = width + x;
  TreesVtx[indx].v.ob[1]   = height;
  TreesVtx[indx].v.ob[2]   = -width + z;
  TreesVtx[indx].v.tc[0]   = (31 << 6);
  TreesVtx[indx].v.tc[1]   = (63 << 6);
  indx++;
  TreesVtx[indx].v.ob[0]   = -width + x;
  TreesVtx[indx].v.ob[1]   = height;
  TreesVtx[indx].v.ob[2]   = width + z;
  TreesVtx[indx].v.tc[0]   = (-31 << 6);
  TreesVtx[indx].v.tc[1]   = (63 << 6);

  for(indx = tree*NVTXPERTREE; indx < tree*NVTXPERTREE + 8; indx++)
  {
    TreesVtx[indx].v.flag  = 0;
    TreesVtx[indx].v.cn[0] = fr;
    TreesVtx[indx].v.cn[1] = fg;
    TreesVtx[indx].v.cn[2] = fb;
    TreesVtx[indx].v.cn[3] = 255;
  }

  gSPVertex (glistp++, osVirtualToPhysical(&TreesVtx[tree*NVTXPERTREE]), 8, 0);
  gSP1Triangle (glistp++, 0, 1, 2, 0);
  gSP1Triangle (glistp++, 0, 2, 3, 0);
  gSP1Triangle (glistp++, 4, 5, 6, 0);
  gSP1Triangle (glistp++, 4, 6, 7, 0);

}

void
rdpatt_testCaseProcTrees(Dynamic *dynamicp, Gfx *module_test)
{
  int i;
  int randx, randz;
  static float	theta = -90.0;

  guPerspective(&dynamicp->projection, &(dynamicp->perspNorm),
		33, 320.0/240.0, 200, 2800, 1.0);

  /* LOOK_OVERALL */
  guLookAt(&dynamicp->viewing, 
	     20, 150, 300,
	     0, 10, 50,
	     0, 1, 0);

  gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

  gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, dynamicp->perspNorm);


    /* gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 135, 0, 167, 240); */

#ifndef GROUND

    gSPDisplayList(glistp++, &rdpatt_ground_nzb_dl[0]);

#endif /* GROUND */

    gDPPipeSync(glistp++);
    gSPClearGeometryMode(glistp++, G_CULL_BACK);
    gSPSetGeometryMode(glistp++, G_SHADE);
    gSPSetGeometryMode(glistp++, G_ZBUFFER);
    gDPSetCombineMode(glistp++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPTexture(glistp++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTextureFilter(glistp++, G_TF_BILERP);
    gDPSetTexturePersp(glistp++, G_TP_PERSP);
    gDPSetTextureLUT(glistp++, G_TT_NONE);
    gDPLoadTextureBlock_4b(glistp++, IA4tree2, G_IM_FMT_IA, 32, 64, 0,
                         G_TX_MIRROR, 0,
                         5, 0, G_TX_NOLOD, G_TX_NOLOD);

    set_random_seed(randSeed);

    for(i = 0; i < NTREES; i++)
    {
      randx = (get_random() >> 8) % ((MAX_RAND_X - MIN_RAND_X) / 2);
      randz = (get_random() >> 8) % ((MAX_RAND_Z - MIN_RAND_Z) / 2);

      make_tree( i, randx, randz);
    }

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdpatt_testCaseProc61(Dynamic *dynamicp, Gfx *module_test)
{
  randSeed = 23;
  rdpatt_testCaseProcTrees(dynamicp, module_test);
}

void
rdpatt_testCaseProc62(Dynamic *dynamicp, Gfx *module_test)
{
  randSeed = 90123;
  rdpatt_testCaseProcTrees(dynamicp, module_test);
}

void
rdpatt_testCaseProc63(Dynamic *dynamicp, Gfx *module_test)
{
  randSeed = 9012;
  rdpatt_testCaseProcTrees(dynamicp, module_test);
}

void
rdpatt_testCaseProc64(Dynamic *dynamicp, Gfx *module_test)
{
  randSeed = 89123;
  rdpatt_testCaseProcTrees(dynamicp, module_test);
}

/*
 *  Test 65, fractal terrain
 */
void
rdpatt_testCaseProc65(Dynamic *dynamicp, Gfx *module_test)
{
  static float f = 0.0;
  float cx, cy, cz;

    cx = (sinf(f/100*2*M_PI) * 300) + 150;
    cy = 300;
    cz = (cosf(f/100*2*M_PI) * 300) + 150;

/*
#ifndef _EMULATOR
    PRINTF("cx %f cy %f cz %f\n", cx, cy, cz);
#endif
*/
 
    guPerspective(&dynamicp->projection, &(dynamicp->perspNorm),
		33, 320.0/240.0, 200, 2800, 1.0);

    guLookAt(&dynamicp->viewing, 
	     -150, 300, -150,
	     150, 300, 150,
	     0, 1, 0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

/*
#ifndef _EMULATOR
PRINTF("PerspNorm= 0x%04X, = %d = %g\n",(int)dynamicp->perspNorm,(int)dynamicp->perspNorm,(float)dynamicp->perspNorm/65536.0);
#endif
*/
    gSPPerspNormalize(glistp++, dynamicp->perspNorm);


    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/*
 *  Test 66, Spinning torus
 */
void
rdpatt_testCaseProc66(Dynamic *dynamicp, Gfx *module_test)
{
  int i;
  int seed = 1234; 
  float randx, randy, randz;
  static float	theta = 10.0;

  set_random_seed(seed);
  randx = (float) (get_random() % 1024) / 1024.0;
  randy = (float) (get_random() % 1024) / 1024.0;
  randz = (float) (get_random() % 1024) / 1024.0;

  guPerspective(&dynamicp->projection, &(dynamicp->perspNorm),
		33, 320.0/240.0, 50, 800, 1.0);

  /* LOOK_OVERALL */
  guLookAt(&dynamicp->viewing, 
	     0, 0, -150,
	     0, 0, 0,
	     0, 1, 0);

  gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

  gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

  guRotate(&dynamicp->modeling, 90.0, 0.0, 0.0, 1.0);

  gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

  guRotate(&dynamicp->torus, theta, randx, randy, randz);

  gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->torus)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, dynamicp->perspNorm);

  gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/*
 *  Test 67, Spinning "U-64"
 */
void
rdpatt_testCaseProc67(Dynamic *dynamicp, Gfx *module_test)
{
  static float	theta = 50.0;


  guPerspective(&dynamicp->projection, &(dynamicp->perspNorm),
		33, 320.0/240.0, 200, 1400, 1.0);

  /* LOOK_OVERALL */
  guLookAt(&dynamicp->viewing, 
	     0, 0, 650,
	     0, 80, 0,
	     0, 1, 0);

  gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

  gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

  guRotate(&dynamicp->modeling, theta, 0.0, 1.0, 0.0);

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


/************************************************************
 *  Test 68, Texture Font Example
 *    Also good for load_tile and tex edge test
 ************************************************************/

#define NCHARS		100

/*
 *  Indicate position and size of currently loaded chars
 */
typedef struct {
  char c;
  int sl, sh, tl, th;
  unsigned int tmem_adrs;
} FontLoaded;
   
FontLoaded FontsLoaded[NCHARS];

/* positions of chars */
#ifdef JUNK
#include "haeberli_fixed.h"

/* two types of same texture */
#include "I4haeberli_fixed.h"
#include "IA4haeberli_fixed.h"
#endif

#include "Tymes-Elfin.h"
#include "I4Tymes-Elfin.h"

#ifdef JUNK
#include "IA4Tymes-Elfin.h"
#endif

/* buffer for created vertices */
Vtx TextVtx[NCHARS*4];

/*
 *  loadchars: load set of characters for later rendering
 *  No error checking, bounds checking.  Be careful.
 */
static void
  loadchars4b(unsigned char *texture, int type, char *str)
{
  unsigned int c, i;
  int charmin, tnchars, nwords;
  unsigned int tmem_adrs;
  TexDesc *cdbase, *cd;

  for(i = 0; i < NCHARS; i++)
  {
    FontsLoaded[i].sl = 0;
    FontsLoaded[i].tl = 0;
    FontsLoaded[i].sh = 0;
    FontsLoaded[i].th = 0;
    FontsLoaded[i].tmem_adrs = 0;
  }

  charmin = MyFont.charmin;
  tnchars = MyFont.nchars;
  cdbase  = MyFont.chars;
  tmem_adrs = 0;
  i = 0;

  gDPPipeSync(glistp++);
  gDPSetTextureImage(glistp++, type, G_IM_SIZ_8b, (128>>1), texture);

  while(*str)
  {
    c = *str-charmin;
    if(c<tnchars)
    {
      cd = cdbase+c;
      nwords = ((((cd->sh - cd->sl + 1) >> 1) + 7) >> 3) * (cd->th - cd->tl + 1);
      if((nwords + tmem_adrs) > 255)
      {
/*
#ifndef _EMULATOR
        PRINTF("Error: Unable to load all characters\n");
#endif
*/
        return;
      }

      FontsLoaded[i].c = *str;
      FontsLoaded[i].tmem_adrs = tmem_adrs;
      FontsLoaded[i].sl = cd->sl;
      FontsLoaded[i].tl = cd->tl;
      FontsLoaded[i].sh = cd->sh;
      FontsLoaded[i].th = cd->th;

/*
#ifndef _EMULATOR
      PRINTF("index for %c is %d, tmem = %d, nwords = %d\n", *str, c, tmem_adrs, nwords);
      PRINTF("sh=%d sl=%d th=%d tl=%d\n", cd->sh, cd->sl, cd->th, cd->tl);
#endif
*/
      gDPSetTile(glistp++, type, G_IM_SIZ_8b, ((((cd->sh-cd->sl+1)>>1)+7)>>3), tmem_adrs,
                G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
      gDPLoadSync(glistp++);
      gDPLoadTile(glistp++, G_TX_LOADTILE,
                        (cd->sl)<<(G_TEXTURE_IMAGE_FRAC-1),
                        (cd->tl)<<(G_TEXTURE_IMAGE_FRAC),
                        (cd->sh)<<(G_TEXTURE_IMAGE_FRAC-1),
                        (cd->th)<<(G_TEXTURE_IMAGE_FRAC)); 

      tmem_adrs += nwords;
      ++i;
      if(i > NCHARS)
        return;
    }
    str++;
  }
}


/*
 *  Render a string assuming all characters needed have already
 *  been loaded and FontLoaded structure initialized by loadchars4b.
 */
static void
  texcharstr4b(char *str, int type, int xo, int yo)
{
  static int indx = 0;
  unsigned int c, i;
  int xpos, ypos;
  int dx, dy;
  int sh, sl, th, tl;

  xpos = xo;
  ypos = yo;

  while(*str)
  {
    for(c = 0; c < NCHARS; c++)
    {
      if(FontsLoaded[c].c == *str)
	break;
    }

    if(c == NCHARS)
    {
/*
#ifndef _EMULATOR
      PRINTF("Error: char %c not found\n", *str);
#endif
*/
      return;
    }

    sh = FontsLoaded[c].sh;
    th = FontsLoaded[c].th;
    sl = FontsLoaded[c].sl;
    tl = FontsLoaded[c].tl;
    dx = sh - sl;
    dy = th - tl;
    TextVtx[indx+0].v.ob[0]   = xpos;
    TextVtx[indx+0].v.ob[1]   = ypos;
    TextVtx[indx+0].v.tc[0]   = sl << 6;
    TextVtx[indx+0].v.tc[1]   = tl << 6;
    TextVtx[indx+1].v.ob[0]   = xpos + dx;
    TextVtx[indx+1].v.ob[1]   = ypos;
    TextVtx[indx+1].v.tc[0]   = sh << 6;
    TextVtx[indx+1].v.tc[1]   = tl << 6;
    TextVtx[indx+2].v.ob[0]   = xpos;
    TextVtx[indx+2].v.ob[1]   = ypos + dy;
    TextVtx[indx+2].v.tc[0]   = sl << 6;
    TextVtx[indx+2].v.tc[1]   = th << 6;
    TextVtx[indx+3].v.ob[0]   = xpos + dx;
    TextVtx[indx+3].v.ob[1]   = ypos + dy;
    TextVtx[indx+3].v.tc[0]   = sh << 6;
    TextVtx[indx+3].v.tc[1]   = th << 6;
    for(i = indx; i < indx+4; i++)
    {
      TextVtx[i].v.ob[2] = 0;
      TextVtx[i].v.flag  = 0;
      TextVtx[i].v.cn[0] = 255;
      TextVtx[i].v.cn[1] = 000;
      TextVtx[i].v.cn[2] = 255;
      TextVtx[i].v.cn[3] = 255;
    }
    gDPPipeSync(glistp++);
    gDPSetTile(glistp++, type, G_IM_SIZ_4b, ((((sh-sl+1)>>1)+7)>>3), 
		FontsLoaded[c].tmem_adrs,
                G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0);
    gDPSetTileSize(glistp++, G_TX_RENDERTILE,
                        (sl)<<G_TEXTURE_IMAGE_FRAC,
                        (tl)<<G_TEXTURE_IMAGE_FRAC,
                        (sh)<<G_TEXTURE_IMAGE_FRAC,
                        (th)<<G_TEXTURE_IMAGE_FRAC);
    gSPVertex (glistp++, osVirtualToPhysical(&TextVtx[indx]), 4, 0);
    gSP1Triangle (glistp++, 0, 1, 2, 0);
    gSP1Triangle (glistp++, 2, 1, 3, 0);
    xpos += dx;
    str++;
    indx += 4;
    if(indx > NCHARS*4)
      indx = 0;
  }
}

#define TEXT	0, 0, 0, SHADE, 0, 0, 0, TEXEL0

void
rdpatt_testCaseProc68(Dynamic *dynamicp, Gfx *module_test)
{
  guPerspective(&dynamicp->projection, &(dynamicp->perspNorm),
		33, 320.0/240.0, 50, 1400, 1.0);

  guLookAt(&dynamicp->viewing, 
	     0, 0, 250,
	     0, 0, 0,
	     0, 1, 0);

  gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

  gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, dynamicp->perspNorm);

  gDPPipeSync(glistp++);
  gSPClearGeometryMode(glistp++, G_CULL_BACK);
  gSPSetGeometryMode(glistp++, G_SHADE);
  gSPClearGeometryMode(glistp++, G_ZBUFFER);
  gDPSetCombineMode(glistp++, TEXT, TEXT);
  gDPSetRenderMode(glistp++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
  gSPTexture(glistp++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
  gDPSetTextureFilter(glistp++, G_TF_BILERP);
  gDPSetTexturePersp(glistp++, G_TP_NONE);

  loadchars4b(I4Tymes_Elfin, G_IM_FMT_IA, " PROJECTALIY");
  texcharstr4b("REALITY", G_IM_FMT_I, -50, 60);

  gDPPipeSync(glistp++);
  gDPSetRenderMode(glistp++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
  texcharstr4b("REALITY", G_IM_FMT_I, -50, 40);

  gDPPipeSync(glistp++);
  gDPSetCombineMode(glistp++, G_CC_MODULATEI, G_CC_MODULATEI);
  texcharstr4b("REALITY", G_IM_FMT_I, -50, 20);

  gDPPipeSync(glistp++);
  gDPSetRenderMode(glistp++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
  gDPSetCombineMode(glistp++, G_CC_MODULATEIA, G_CC_MODULATEIA);
  texcharstr4b("REALITY", G_IM_FMT_I, -50, 0);

  gDPPipeSync(glistp++);
  gDPSetTextureFilter(glistp++, G_TF_POINT);
  gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
  texcharstr4b("REALITY", G_IM_FMT_I, -50, -20);

  gDPPipeSync(glistp++);
  gDPSetTextureFilter(glistp++, G_TF_BILERP);
  gDPSetRenderMode(glistp++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
  gDPSetCombineMode(glistp++, G_CC_DECALRGB, G_CC_DECALRGB);
  texcharstr4b("REALITY", G_IM_FMT_I, -50, -40);

  gDPPipeSync(glistp++);
  gDPSetRenderMode(glistp++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
  gDPSetPrimColor(glistp++, 0, 0, 0,   0, 255, 255);
  gDPSetEnvColor(glistp++,  0, 255, 0, 255);
  gDPSetCombineMode(glistp++, _G_CC_BLENDPE, _G_CC_BLENDPE);
  texcharstr4b("REALITY", G_IM_FMT_I, -50, -60);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/* 
 * ADD TEST CASE: test frames:
 *
 * Display lists from rdpatt_static.c (which are placed in the static segment 
 * via the spec file) must be inserted in this table, in the same position as 
 * the test's frame number, along with a mneumonic name (which will be used to 
 * name the resulting .rdp display list file), and a pointer to the top level 
 * DL function which will be used to invoke this static display list.
 * 
 * NOTE: a test doesn't need to have a static display list, if
 * the corresponding testCaseProc doesn't use one. But you still
 * need to put a NULL entry here in the table.
 */
GfxTest_t testList_rdpatt[] = {

    /*
     * Only the first name is significant, since the DL's are all concatenated.
     */
    &(rdpatt_square0[0]), "rdpatt_square0",			/* Test 0 */
	rdpatt_testCaseProc0, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_square1[0]), "rdpatt_square1",
	rdpatt_testCaseProc1, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_square2[0]), "rdpatt_square2",
	rdpatt_testCaseProc2, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_rectangle3[0]), "rdpatt_rectangle3",
	rdpatt_testCaseProc3, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_triangles[0]), "rdpatt_triangles",
	rdpatt_testCaseProc4, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpatt_shade_acc0[0]), "rdpatt_shade_acc0",
	rdpatt_testCaseProc5, G_IM_SIZ_32b, CLEAR_AQUA,			/* Test 5 */
    &(rdpatt_shade_acc1[0]), "rdpatt_shade_acc1",
	rdpatt_testCaseProc6, G_IM_SIZ_32b, CLEAR_AQUA,
    &(rdpatt_shade_acc2[0]), "rdpatt_shade_acc2",
	rdpatt_testCaseProc7, G_IM_SIZ_32b, CLEAR_AQUA,
    &(rdpatt_tex_acc0[0]), "rdpatt_tex_acc0",
	rdpatt_testCaseProc8, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_square9[0]), "rdpatt_square9",
	rdpatt_testCaseProc9, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpatt_square10[0]), "rdpatt_square10",
	rdpatt_testCaseProc10, G_IM_SIZ_16b, CLEAR_AQUA,			/* Test 10 */
    &(rdpatt_xluramp[0]), "rdpatt_xluramp",
	rdpatt_testCaseProc11, G_IM_SIZ_32b, CLEAR_AQUA,
    &(rdpatt_clrbar[0]), "rdpatt_clrbar",
	rdpatt_testCaseProc12, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_cc_modes[0]), "rdpatt_cc_modes",
	rdpatt_testCaseProc13, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_rectangle14[0]), "rdpatt_rectangle14",
	rdpatt_testCaseProc14, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpatt_rectangle15[0]), "rdpatt_rectangle15",		/* Test 15 */
	rdpatt_testCaseProc14, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_rectangle16[0]), "rdpatt_rectangle16",
	rdpatt_testCaseProc14, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_rectangle17[0]), "rdpatt_rectangle17",
	rdpatt_testCaseProc14, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_rectangle18[0]), "rdpatt_rectangle18",
	rdpatt_testCaseProc14, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCasePlacebo, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpatt_square20[0]), "rdpatt_square20",			/* Test 20 */
	rdpatt_testCaseProc20, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_square21[0]), "rdpatt_square21",
	rdpatt_testCaseProc20, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_vitriangle[0]), "rdpatt_vitriangle",
	rdpatt_testCaseProc22, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCasePlacebo, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCasePlacebo, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpatt_blendrange_dl[0]), "rdpatt_blendrange_dl",		/* Test 25 */
	rdpatt_testCaseProc1, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_rdpatt_placebo_dl",
	rdpatt_testCasePlacebo, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_rdpatt_placebo_dl",
	rdpatt_testCasePlacebo, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCasePlacebo, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCasePlacebo, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",		/* Test 30 */
	rdpatt_testCaseProc30, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc31, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc32, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc33, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc34, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",		/* Test 35 */
	rdpatt_testCaseProc35, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc36, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_texedge_dl[0]), "rdpatt_texedge_dl",
	rdpatt_testCaseProc37, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_zbuf_dl[0]), "rdpatt_zbuf_dl",
	rdpatt_testCaseProc38, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc39, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",		/* Test 40 */
	rdpatt_testCaseProc40, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc41, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc42, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc43, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc44, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",		/* Test 45 */
	rdpatt_testCaseProc45, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc46, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc47, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc48, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc49, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",		/* Test 50 */
	rdpatt_testCasePlacebo, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc61, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc62, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc63, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc64, G_IM_SIZ_16b, CLEAR_AQUA,

    &(rdpatt_frac_dl[0]), "rdpatt_frac_dl",			/* Test 55 */
	rdpatt_testCaseProc65, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_spin_torus_dl[0]), "rdpatt_spin_torus_dl",
	rdpatt_testCaseProc66, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_u64_dl[0]), "rdpatt_u64_dl",
	rdpatt_testCaseProc67, G_IM_SIZ_16b, CLEAR_AQUA,
    &(rdpatt_placebo_dl[0]), "rdpatt_placebo_dl",
	rdpatt_testCaseProc68, G_IM_SIZ_16b, CLEAR_AQUA,

    /* Last entry must be NULL, so we can count them in main.c */
    (Gfx *) NULL,	"",		(CaseProc_t) NULL,
	G_IM_SIZ_16b, CLEAR_AQUA,
};
