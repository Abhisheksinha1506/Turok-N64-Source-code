
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
 * File:	static.c
 *
 *
 * This file holds tiny display list segments that are 'static' data.
 * If you feel the urge to modify a test, see the comment at
 * the top of main.c for details.
 *
 */

#include <ultra64.h>
#include "dldriver.h"
#include "rdpfb.h"
#include "cs.h"

/*
 * Test conventions:
 *
 * Data variable names can be about anything, as long as they are unique
 * and consistent in the table entry.
 *
 * In order to get around compiler weirdness, the table of tests
 * is in rdpverif.c, and the Gfx rdpfb_lists must be extern'd in rdpverif.h
 *
 * Your test case display list must end with gsSPEndDisplayList(),
 * otherwise there are length hassles.
 *
 * Your test case should set any special mode you want (texture, zbuff,
 * etc.) and also turn it off when you are done, so as not to affect
 * other tests.
 *
 */

/*
 * Test -1, default frame. Used as a placeholder.
 *
 * Simple square (4 triangles), each vertex a different color.
 *
 * Wed Oct  5 22:12:43 PDT 1994
 *
 */
static Vtx place_vtx[5] =  {
        {        -40,  40, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {         40,  40, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         40, -40, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {        -40, -40, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},
        {          0,   0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
};

Gfx rdpfb_placebo_dl[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&place_vtx, 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};
/* end of case -1 */

/*
 * Test 0, Frame 0:
 *
 * Simple square (4 triangles), each vertex a different color.
 *
 * Wed Oct  5 22:12:43 PDT 1994
 *
 */
static Vtx q0[5] =  {
        {        -10,  10, 0, 0, 0, 0, 0, 0, 0x1f, 0x1f		},
        {         10,  10, 0, 0, 0, 0, 0x2f, 0x2f, 0x2f, 0x2f	},
        {         10, -10, 0, 0, 0, 0, 0, 0x1f, 0, 0x1f		},
        {        -10, -10, 0, 0, 0, 0, 0x0f, 0, 0, 0x0f		},
        {          0,   0, 0, 0, 0, 0, 0x0f, 0x0f, 0x0f, 0x0f	},
};

Gfx rdpfb_square0[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSPVertex(&q0, 5, 0),
#if 0
    /* two triangle case: */
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
#endif
    /* four triangle case: */
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};
/* end of case 0 */

/*
 * rdpatt Shading Accuracy Test 0, Frame 5/25:
 *
 * Shading attribute accuracy test.  Two triangles cut a trapezoid
 * from a gray scale gradient that goes from 0(left) to 255(right).
 * One triangle is left major, the other is right major with the
 * minor edge of the left triangle abutted with the major edge of
 * the right triangle.  The gradient should remain undisturbed along 
 * the diagonal of the trapezoid.  If there is enough error in the
 * stepping of the attributes for the two triangles, a first order
 * Mach band will be observed along the diagonal.  Since the shading
 * gradient is in only one direction, second order Mach bands should not
 * occur.
 *
 *
 * NOTE:  Should rerun this test at 640x480 once clipper and memspan
 *        support variable size viewports.  Also run various rotations
 *        of same case.
 * 
 * Sun Oct  9 11:44:40 PDT 1994
 *
 */

static Vtx shade_acc0q[4] =  {
        {          5,    5, 0, 0, 0, 0,   4,   4,   4, 255 },
        {        310,    0, 0, 0, 0, 0, 248, 248, 248, 255 },
        {          0,  234, 0, 0, 0, 0,   0,   0,   0, 255 },
        {        315,  239, 0, 0, 0, 0, 252, 252, 252, 255 },
};

Gfx rdpfb_shade_acc0[] = {
    /*
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, 320, cfb_a),
    */
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&shade_acc0q, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(1, 3, 2, 1),

    gsSPEndDisplayList(),
};
/* end of case shade_acc0 */

/*
 * rdpatt Shading Accuracy Test 1, Frame 6/26:
 *
 * Shading attribute accuracy test.  Two triangles cut a trapezoid
 * from a gray scale gradient that goes from 0(left) to 255(right).
 * One triangle is right major, the other is left major with the
 * major edge of the left triangle abutted with the major edge of
 * the right triangle.  The gradient should remain undisturbed along 
 * the diagonal of the trapezoid.  If there is enough error in the
 * stepping of the attributes for the two triangles, a first order
 * Mach band will be observed along the diagonal.  Since the shading
 * gradient is in only one direction, second order Mach bands should not
 * occur.
 *
 *
 * NOTE:  Should rerun this test at 640x480 once clipper and memspan
 *        support variable size viewports.  Also run various rotations
 *        of same case.
 * 
 * Sun Oct  9 11:44:40 PDT 1994
 *
 */

static Vtx shade_acc1q[4] =  {
        {          5,    5, 0, 0, 0, 0,   4,   4,   4, 255 },
        {        310,    0, 0, 0, 0, 0, 248, 248, 248, 255 },
        {          0,  239, 0, 0, 0, 0,   0,   0,   0, 255 },
        {        315,  234, 0, 0, 0, 0, 252, 252, 252, 255 },
};

Gfx rdpfb_shade_acc1[] = {
    /*
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, 320, cfb_a),
    */
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&shade_acc1q, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(1, 3, 2, 1),
    gsSPEndDisplayList(),
};
/* end of case shade_acc1 */

/*
 * rdpatt Shading Accuracy Test 2, Frame 7/27:
 *
 * Shading attribute accuracy test.  Two triangles cut a trapezoid
 * from a gray scale gradient that goes from 0(left) to 255(right).
 * One triangle is right major, the other is left major with the
 * minor edge of the left triangle abutted with the minor edge of
 * the right triangle.  The gradient should remain undisturbed along 
 * the diagonal of the trapezoid.  If there is enough error in the
 * stepping of the attributes for the two triangles, a first order
 * Mach band will be observed along the diagonal.  Since the shading
 * gradient is in only one direction, second order Mach bands should not
 * occur.
 *
 *
 * NOTE:  Should rerun this test at 640x480 once clipper and memspan
 *        support variable size viewports.  Also run various rotations
 *        of same case.
 * 
 * 
 *  Tue Oct 11 07:26:42 PDT 1994
 *
 */

static Vtx shade_acc2q[4] =  {
        {          5,    0, 0, 0, 0, 0,   4,   4,   4, 255 },
        {        310,    5, 0, 0, 0, 0, 248, 248, 248, 255 },
        {          0,  234, 0, 0, 0, 0,   0,   0,   0, 255 },
        {        310,  239, 0, 0, 0, 0, 248, 248, 248, 255 },
};

Gfx rdpfb_shade_acc2[] = {
    /*
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, 320, cfb_a),
    */
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&shade_acc2q, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(1, 3, 2, 1),
    gsSPEndDisplayList(),
};
/* end of case shade_acc2 */

/*
 * rdpatt Alpha Ramp, Frame 11:
 *
 * Make ramp in alpha and solid white faces.  Use alpha to blend to
 * memory (black) creating a gray scale ramp.
 *
 * 
 * 
 *  Thu Oct 13 00:19:06 PDT 1994
 *
 */

static Vtx xluramp_q[4] =  {
        {          5,    5, 0, 0, 0, 0, 255, 255, 255,   4 },
        {        310,    0, 0, 0, 0, 0, 255, 255, 255, 248 },
        {          0,  234, 0, 0, 0, 0, 255, 255, 255,   0 },
        {        315,  239, 0, 0, 0, 0, 255, 255, 255, 252 },
};

Gfx rdpfb_xluramp[] = {
    /*
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, 320, cfb_a),
    */
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPVertex(&xluramp_q, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(1, 3, 2, 1),

    gsSPEndDisplayList(),
};
/* end of case xluramp */

/* 2vtx in, 1vtx out, flat insde edge */
static Vtx trivtx10a[12] =  {
        {         20, 112, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         20, 128, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        -20, 120, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300, 112, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        300, 128, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        340, 120, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        168, 220, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        152, 220, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        160, 260, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        168,  20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        152,  20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        160, -20, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* 2vtx in, 1vtx max, flat insde edge */
static Vtx trivtx10b[12] =  {
        {         20,  132, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         20,  148, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,  140, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,  132, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        300,  148, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,  140, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        188,  220, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        172,  220, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        180, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        188,   20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        172,   20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        180,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* 2vtx in, 1vtx max, leftmajor top/bot; high out left/right */
static Vtx trivtx10c[12] =  {
        {         20,   92, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         30,  108, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,   70, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,   92, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        290,  108, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,   70, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        148,  220, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        132,  210, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        140, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        148,   20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        132,   30, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        140,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* 2vtx in, 1vtx max, rightmajor top/bot; low out left/right */
static Vtx trivtx10d[12] =  {
        {         30,  152, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         20,  168, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,  190, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        290,  152, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        300,  168, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,  190, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        208,  210, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        192,  220, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        200, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        208,   30, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        192,   20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        200,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* upper corner from sides */
static Vtx trivtx10i[12] =  {
        {         30,   88, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         20,   85, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,   88, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        310,   85, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {         30,   52, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         20,   68, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -1045,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,   52, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        310,   68, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       1045,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* lower corner from sides */
static Vtx trivtx10j[12] =  {
        {         30,  192, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         20,  195, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,  192, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        310,  195, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {         30,  228, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         20,  212, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -1046, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,  228, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        310,  212, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       1046, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* upped corner from top */
static Vtx trivtx10k[12] =  {
        {         82,   20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        108,   25, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,-1044, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        112,   25, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        128,   20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        212,   20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        228,   25, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        232,   25, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        258,   20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,-1044, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* lower corner from bot */
static Vtx trivtx10l[12] =  {
        {         82,  220, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        108,  215, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000, 1044, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        112,  215, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        128,  220, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        212,  220, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        228,  215, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        232,  215, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        258,  220, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000, 1044, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/*
 * rdpew Test 14, Frame 14:
 *
 *
 * wed Oct 19 1994
 * 640x480 screensize (uses data from test 10)
 *
 * Draws the triangles from test 10 but on a bigger screen.
 * to use this test with the RDP CSIM use the options:
 *    -W 640 -H 480
 *
 */
Gfx rdpfb_triangle14[MAX_STATIC_GFX_SIZE] = {
    gsSPVertex(&trivtx10j, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10k, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10l, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10i, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10a, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10b, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10c, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10d, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPEndDisplayList(),
};

Gfx rdpfb_hires_image_test[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(0x0C084148,0),
    /*
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage(5, G_IM_SIZ_16b, 640, cfb_a),
    gsDPPipeSync(),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 640, cfb_a),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,640,480),
    */
    gsSPDisplayList(rdpfb_triangle14),

#ifdef OTHER_SCISSORS
    /*
     * use scissoring to lower number of clocks to complete sim
     */
    gsDPSetScissor(G_SC_NON_INTERLACE, 635,0,640,480),
    gsSPDisplayList(rdpfb_triangle14),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,480,5),
    gsSPDisplayList(rdpfb_triangle14),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,475,1023,480),
    gsSPDisplayList(rdpfb_triangle14),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,5,480),
    gsSPDisplayList(rdpfb_triangle14),

    gsDPSetScissor(G_SC_NON_INTERLACE, 315,0,320,480),
    gsSPDisplayList(rdpfb_triangle14),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,233,640,240),
    gsSPDisplayList(rdpfb_triangle14),
#endif
    gsSPEndDisplayList(),
};
/* end of case 14 */

/*
 * ADD TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx rdpfb_display list must be extern'd in rdpverif.h, then
 * added to the 'testList' table in rdpverif.c
 *
 */
