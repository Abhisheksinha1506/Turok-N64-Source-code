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
 * File:	rdpatt_static.c
 * Creator:	hal@sgi.com
 * Purpose:
 *
 * This file holds tiny display list segments that are 'static' data, for use
 * by the texture filter test module in rdpatt.c
 *
 * If you feel the urge to modify a test, see the comment at
 * the top of main.c for details.
 */

#include <ultratypes.h>
#include <mbi.h>
#include "dldriver.h"
#include "texture.h"
#include "rdpatt.h"

/*
 * Test conventions:
 *
 * Data variable names can be about anything, as long as they are unique
 * and consistent in the table entry.
 *
 * In order to get around compiler weirdness, the table of tests
 * is in rdpatt.c, and the Gfx lists must be extern'd in rdpvector.h
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

Gfx rdpatt_placebo_dl[] = {
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
        {        -40,  40, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {         40,  40, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         40, -40, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {        -40, -40, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},
        {          0,   0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
};

Gfx rdpatt_square0[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF,G_RM_AA_OPA_SURF2),
    gsSPVertex(&q0, 5, 0),
    /* two triangle case: */
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
#if 0
    /* four triangle case: */
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
#endif
    gsSPEndDisplayList(),

#if 0
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF,G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&q0, 5, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
#endif
};
/* end of case 0 */



/*
 * Test 1, Frame 1:
 *
 * Simple square with a texture.
 *
 * Wed Oct  5 22:12:43 PDT 1994
 *
 */

#include "RGBA16grid.h"

static Vtx q1[4] =  {
        {        -64,  64, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff	},
        {         64,  64, 0, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff	},
        {         64, -64, 0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff	},
        {        -64, -64, 0, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff	},
};

Gfx rdpatt_square1[] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(RGBA16grid, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&q1, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};
/* end of case 1 */



/*
 * Test 2, Frame 2:
 *
 * Simple square (4 triangles), each vertex a different color.
 *
 * Wed Oct  5 22:12:43 PDT 1994
 *
 */
static Vtx q2[5] =  {
        {        -40,  40, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {         40,  40, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         40, -40, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {        -40, -40, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},
        {          0,   0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
};

Gfx rdpatt_square2[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&q2, 5, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};
/* end of case 2 */




/*
 * Test 3, Frame 3:
 *
 * Rectangle tests.  Tests top-left inclusive, bottom-right
 * exclusive edges, z-buffered rects using primitive Z,
 * attribute updates by selecting through color combiner,
 * attribute sync's between primitives, thin rectangles,
 * scissored rectangles.
 *
 * 
 *  Thu Oct  6 17:19:23 PDT 1994
 *
 */

Gfx rdpatt_rectangle3[] = {
    gsDPPipeSync(),
    /* make scissor box smaller so we can test some scissoring too */
    gsDPSetScissor(G_SC_NON_INTERLACE, 10, 13, 310, 219),
    gsSPClearGeometryMode(G_ZBUFFER),

    /* set attributes, to be used as colors for rects */
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetFogColor(0, 0, 255, 180),
    gsDPSetEnvColor(255, 0, 0, 156),
    gsDPSetKeyR(134, 87, 211), 
    gsDPSetKeyGB(54, 21, 148, 237, 214, 90), 
    gsDPSetConvert(45, 114, 250, 77, 66, 69),

    /* center of screen, 40x40, white */
    gsDPSetCombineLERP (0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPFillRectangle(140, 100, 180, 140),
    gsDPPipeSync(),

    /* on top of white rect above, 30x30, magenta alpha 128/255 */
    /* check RM, Combine mode, Combine LERP */
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPFillRectangle(145, 105, 175, 135),
    gsDPPipeSync(),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),   /* restore original prim color */
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2), /* restore original bl mode */

    /* on top of white rect above, 20x20, black */
    gsDPSetCombineLERP (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPFillRectangle(150, 110, 170, 130),
    gsDPPipeSync(),

    /* place rect at each corner of center rect, make sure no overlap */
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPFillRectangle(120, 90, 140, 100),
    gsDPFillRectangle(180, 85, 185, 100),
    gsDPFillRectangle(135, 140, 140, 185),
    gsDPFillRectangle(180, 140, 196, 144),
    gsDPPipeSync(),

    /* make three 1-pixel high rects, two get scissored completely, 
	one only left/right is scissored */ 
    gsDPSetCombineLERP (0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPFillRectangle(0, 3, 320, 4),
    gsDPFillRectangle(0, 110, 320, 111),
    gsDPFillRectangle(0, 220, 320, 221),

    /* make three 1-pixel wide rects, two get scissored completely, 
	one only top/bottom is scissored */ 
    gsDPFillRectangle(1, 0, 2, 240),
    gsDPFillRectangle(150, 0, 151, 240),
    gsDPFillRectangle(311, 0, 312, 240),
    gsDPPipeSync(),

    /* do 2x2 rectangle mesh at upper left corner, check for overlaps,
       proper scissoring, proper attributes */
    gsDPSetCombineLERP (1, CENTER, ENV_ALPHA, 0, 0, 0, 0, 0, 1, CENTER, ENV_ALPHA, 0, 0, 0, 0, 0),
    gsDPFillRectangle(5, 5, 13, 20),
    gsDPPipeSync(),
    gsDPSetCombineLERP (1, CENTER, PRIMITIVE_ALPHA, 0, 0, 0, 0, 0, 1, CENTER, PRIMITIVE_ALPHA, 0, 0, 0, 0, 0),
    gsDPFillRectangle(13, 5, 21, 20),
    gsDPPipeSync(),
    gsDPSetCombineLERP (1, CENTER, ENVIRONMENT, 0, 0, 0, 0, 0, 1, CENTER, ENVIRONMENT, 0, 0, 0, 0, 0),
    gsDPFillRectangle(5, 20, 13, 35),
    gsDPPipeSync(),
    gsDPSetCombineLERP (1, CENTER, PRIMITIVE, 0, 0, 0, 0, 0, 1, CENTER, PRIMITIVE, 0, 0, 0, 0, 0),
    gsDPFillRectangle(13, 20, 21, 35),
    gsDPPipeSync(),

    /* turn on zbuffering using primitive Z */
    gsSPSetGeometryMode(G_ZBUFFER),
    gsDPSetDepthSource(G_ZS_PRIM), /* primitive depth */
    gsDPSetRenderMode(G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2),

    /* do a zbuffered group of rects at upper right corner, check for
       proper zbuffering, scissoring, attribute update */
    gsDPSetPrimDepth(0x1fd, 0),  /* nearest */
    gsDPSetCombineLERP (1, 0, SCALE, 0, 0, 0, 0, 0, 1, 0, SCALE, 0, 0, 0, 0, 0),
    gsDPFillRectangle(300, 7, 315, 23),
    gsDPPipeSync(),
    gsDPSetPrimDepth(0x1fe, 0),  /* middle */
    gsDPSetCombineLERP (1, 0, PRIMITIVE_ALPHA, 0, 0, 0, 0, 0, 1, 0, PRIMITIVE_ALPHA, 0, 0, 0, 0, 0),
    gsDPFillRectangle(281, 6, 305, 40),
    gsDPPipeSync(),
    gsDPSetPrimDepth(0x1ff, 0),  /* farthest */
    gsDPSetCombineLERP (1, 0, ENV_ALPHA, 0, 0, 0, 0, 0, 1, 0, ENV_ALPHA, 0, 0, 0, 0, 0),
    gsDPFillRectangle(290, 35, 319, 67),
    gsDPPipeSync(),
    
    /* do a zbuffered group of rects at lower left corner, check for
       proper zbuffering, scissoring, attribute update */
    gsDPSetPrimDepth(0x55, 0),  /* nearest */
    gsDPSetCombineLERP (1, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, 0, 1, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, 0),
    gsDPFillRectangle(1, 201, 80, 235),
    gsDPPipeSync(),
    gsDPSetPrimDepth(0x88, 0),  /* middle */
    gsDPSetCombineLERP (1, K4, PRIMITIVE, 0, 0, 0, 0, 0, 1, K4, PRIMITIVE, 0, 0, 0, 0, 0),
    gsDPFillRectangle(10, 180, 60, 219),
    gsDPPipeSync(),
    gsDPSetPrimDepth(0xaa, 0),  /* farthest */
    gsDPSetCombineLERP (1, 0, K5, 0, 0, 0, 0, 0, 1, 0, K5, 0, 0, 0, 0, 0),
    gsDPFillRectangle(40, 157, 75, 200),
    gsDPPipeSync(),

    /* do a zbuffered group of rects at lower right corner, check for
       proper zbuffering, scissoring, attribute update */
    gsDPSetPrimDepth(0x001, 0),  /* nearest */
    gsDPSetCombineLERP (1, 0, PRIMITIVE, 0, 0, 0, 0, 0, 1, 0, PRIMITIVE, 0, 0, 0, 0, 0),
    gsDPFillRectangle(231, 186, 277, 210),
    gsDPPipeSync(),
    gsDPSetPrimDepth(0x876, 0),  /* middle */
    gsDPSetCombineLERP (1, 0, ENVIRONMENT, 0, 0, 0, 0, 0, 1, 0, ENVIRONMENT, 0, 0, 0, 0, 0),
    gsDPFillRectangle(251, 205, 312, 222),
    gsDPPipeSync(),
    gsDPSetPrimDepth(0xfff, 0),  /* farthest */
    gsDPSetCombineLERP (1, 0, ENV_ALPHA, 0, 0, 0, 0, 0, 1, 0, ENV_ALPHA, 0, 0, 0, 0, 0),
    gsDPFillRectangle(260, 152, 318, 253),
    gsDPPipeSync(),

    /* restore original modes */

    gsSPEndDisplayList(),
};
/* end of case 3 */

/*
 * Test 4, Frame 4:
 *
 * Zbuffered triangles
 *
 */
#define Z1	-200	/* In distance */
#define Z2	-180	/* closer */
/*#define Z1	0 */
/*#define Z2	0 */

static Vtx tris[] = {
/*    x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */
	
    { -40,  34,     Z1, 0,	0,	0,	0xff,	0,	0,	0xff },	  /* R */   
    {  30,   0,	    Z2, 0,	0,	0,	0,	0,	0xff,	0xff },	  /* B */	     
    { -40, -34,     Z1, 0,	0,	0,	0,	0xff,	0,	0xff },	  /* G */
    	     
    {  35,   24,    Z1, 0,	0,	0,	0,	0,	0xff,	0xff },	  /* B */	     
    {  35,  -24,    Z1, 0,	0,	0,	0,	0xff,	0,	0xff },	  /* G */	     
    { -20,   0,	    Z2, 0,	0,	0,	0xff,	0,	0,	0xff },	  /* R */	     
};

Gfx rdpatt_triangles[] = {
    { gsSPClearGeometryMode(0xffffffff) }, 
    { gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER) }, 
    { gsDPSetRenderMode(G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2) },
    { gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE) },
    { gsSPVertex(&tris, sizeof(tris)/sizeof(tris[0]), 0) },
    { gsSP1Triangle(0, 1, 2, 0) }, 
    { gsSP1Triangle(3, 4, 5, 0) },
    { gsSPEndDisplayList() }
};

Gfx rdpatt_fogtriangles[] = {
    { gsDPSetFogColor(128, 128, 128, 128) }, 
    { gsDPSetCycleType(G_CYC_2CYCLE) }, 
    { gsSPClearGeometryMode(0xffffffff) }, 
    { gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER) }, 
    { gsDPSetRenderMode(G_RM_FOG_PRIM_A, G_RM_ZB_OPA_SURF2) },
    { gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE) },
    { gsSPVertex(&tris, sizeof(tris)/sizeof(tris[0]), 0) },
    { gsSP1Triangle(0, 1, 2, 0) }, 
    { gsSP1Triangle(3, 4, 5, 0) },
    { gsSPEndDisplayList() }
};
/* end of case 4 */

/*
 * Shading Accuracy Test 0, Frame 5/25:
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

Gfx rdpatt_shade_acc0[] = {
    /*
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD, cfb_16_a),
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
 * Shading Accuracy Test 1, Frame 6/26:
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

Gfx rdpatt_shade_acc1[] = {
    /*
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD, cfb_16_a),
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
 * Shading Accuracy Test 2, Frame 7/27:
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

Gfx rdpatt_shade_acc2[] = {
    /*
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD, cfb_16_a),
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
 * Texture Accuracy Test 0, Frame 8:
 *
 * Texture attribute accuracy test.  Two triangles cut a trapezoid
 * from a vertical stripe texture.  The texture is slightly
 * magnified (1 texel every 1.1 pixel).  The vertices are on 
 * integer texture coordinates.
 *
 * One triangle is left major, the other is right major with the
 * major edge of the left triangle abutted with the major edge of
 * the right triangle.  The texture stripes should remain undisturbed 
 * along the diagonal of the trapezoid.  If there is enough error in the
 * stepping of the attributes for the two triangles, a glitch in the stripes
 * will be observed along the diagonal.  
 *
 * This test also involves wrapping, mirroring, and clamping functions
 * in the texture coordinate unit.  Some scissoring may also be involved
 * depending on the rotation.
 *
 * NOTE:  Should rerun this test at 640x480 once clipper and memspan
 *        support variable size viewports.  Also run various rotations
 *        of the same case.
 * 
 *        scale 2xcoords by 0.5
 *        should step 10 texels every 11 pixels in both directions
 *
 *  Sun Oct  9 22:04:37 PDT 1994
 *
 */

/*  XXX What scale are the texture coords? what is the orientation of s/t? */
static Vtx tex_acc0q[4] =  {
/*                 x     y   z      s         t         r    g    b    a      */
        {          11,   11, 0, 0,  10 << 6,  10 << 6,   4,   4,   4, 255 },
        {         308,   11, 0, 0, 280 << 6,  10 << 6, 248, 248, 248, 255 },
        {         308,  231, 0, 0, 280 << 6, 210 << 6, 252, 252, 252, 255 },
        {          11,  231, 0, 0,  10 << 6, 210 << 6,   0,   0,   0, 255 },
};


Gfx rdpatt_tex_acc0[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_SHADE),
    /* texture scale (0.5,0.5) */
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetCombineMode (G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(RGBA16grid, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 1, 0,
			 G_TX_WRAP | G_TX_MIRROR, G_TX_CLAMP,
			 3, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&tex_acc0q, 4, 0),
    gsSP1Triangle(0, 1, 3, 0),
    gsSP1Triangle(1, 2, 3, 1),
    gsSPEndDisplayList(),
};
/* end of case tex_acc0 */


/*
 * Test 9, Frame 9:
 *
 * Simple square (2 triangles), each vertex a different color.
 * Tests accurate integer pixel positioning.
 *
 * Wed Oct 12 11:27:23 PDT 1994
 *
 */
static Vtx q9[5] =  {
        {        120, 160, 0, 0, 0, 0, 0, 0, 0xff, 0xff       },
        {        200, 160, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff },
        {        200,  80, 0, 0, 0, 0, 0, 0xff, 0, 0xff       },
        {        120,  80, 0, 0, 0, 0, 0xff, 0, 0, 0xff       },
        {          0,   0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff },
};

Gfx rdpatt_square9[10] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&q9, 5, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};
/* end of case 9 */

/*
 * Test 10, Frame 10:
 *
 * Test all possible edge-types next to each other:
 *
 *	HH, HM, HL, LM, LL, MM
 *
 * The RED-BLUE diagonal is the joining edge; if this transition
 * isn't smooth, we have a problem with rasterization/attribute
 * adjustments.
 *
 * Thu Oct 13 20:54:49 PDT 1994
 *
 */
static Vtx q10a[12] =  {
    /* high edge next to high edge: */
        {         30,  20, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {         80,  30, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {        100, 100, 0, 0, 0, 0, 0, 0, 0xff, 0xff  },
        {         10,  80, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff  },

    /* high edge next to mid edge: */
        {        120,  20, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {        180,  40, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {        200,  70, 0, 0, 0, 0, 0, 0, 0xff, 0xff  },
        {        130, 110, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff  },

    /* high edge next to low edge: */
        {        220, 100, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {        260,  10, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {        280,  60, 0, 0, 0, 0, 0, 0, 0xff, 0xff  },
        {        310,  80, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff  },
};

/* two groups of vertices, don't overflow points buffer */
static Vtx q10b[12] =  {
    /* low edge next to mid edge: */
        {         40, 200, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {         10, 130, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {         80, 170, 0, 0, 0, 0, 0, 0, 0xff, 0xff  },
        {        100, 230, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff  },

    /* low edge next to low edge: */
        {        150, 230, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {        110, 130, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {        160, 190, 0, 0, 0, 0, 0, 0, 0xff, 0xff  },
        {        200, 140, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff  },

    /* mid edge next to mid edge: */
        {        290, 130, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {        220, 230, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {        270, 200, 0, 0, 0, 0, 0, 0, 0xff, 0xff  },
        {        310, 230, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff  },

};

Gfx rdpatt_square10[32] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsSPVertex(&q10a, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(4, 5, 6, 0),
    gsSP1Triangle(4, 6, 7, 0),
    gsSP1Triangle(8, 9, 10, 0),
    gsSP1Triangle(8, 10, 11, 0),

    gsSPVertex(&q10b, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(4, 5, 6, 0),
    gsSP1Triangle(4, 6, 7, 0),
    gsSP1Triangle(8, 9, 10, 0),
    gsSP1Triangle(8, 10, 11, 0),

    gsSPEndDisplayList(),
};
/* end of case 10 */


/*
 * Alpha Ramp, Frame 11:
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

Gfx rdpatt_xluramp[] = {
    /*
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD, cfb_16_a),
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


/*
 * Color bars, Test 12.
 *
 *
 * Sat Oct 15 21:48:40 PDT 1994
 *
 */
static Vtx clrbar_vtx0[10] =  {
        {          0,    0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         31,    0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         63,    0, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff	},
        {         95,    0, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        127,    0, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {          0,   63, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         31,   63, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         63,   63, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff	},
        {         95,   63, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        127,   63, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
};

static Vtx clrbar_vtx1[10] =  {
        {        127,    0, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        159,    0, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        191,    0, 0, 0, 0, 0, 0xff, 0xff, 0x00, 0xff	},
        {        223,    0, 0, 0, 0, 0, 0x00, 0xff, 0xff, 0xff	},
        {        255,    0, 0, 0, 0, 0, 0xff, 0x00, 0xff, 0xff	},
        {        127,   63, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        159,   63, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        191,   63, 0, 0, 0, 0, 0xff, 0xff, 0x00, 0xff	},
        {        223,   63, 0, 0, 0, 0, 0x00, 0xff, 0xff, 0xff	},
        {        255,   63, 0, 0, 0, 0, 0xff, 0x00, 0xff, 0xff	},
};

static Vtx clrbar_vtx2[4] =  {
        {          0,   63, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff	},
        {          0,   95, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff	},
        {        255,   63, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {        255,   95, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
};

static Vtx clrbar_vtx3[4] =  {
        {          0,   95, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff	},
        {          0,  127, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff	},
        {        255,   95, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        255,  127, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
};

static Vtx clrbar_vtx4[4] =  {
        {          0,  127, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff	},
        {          0,  159, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff	},
        {        255,  127, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        255,  159, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
};

static Vtx clrbar_vtx5[4] =  {
        {          0,  159, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff	},
        {          0,  191, 0, 0, 0, 0, 0x00, 0x00, 0x00, 0xff	},
        {        255,  159, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        255,  191, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

Gfx rdpatt_clrbar[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&clrbar_vtx0, 10, 0),
    gsSP1Triangle(0, 6, 5, 0),
    gsSP1Triangle(0, 1, 6, 0),
    gsSP1Triangle(1, 7, 6, 1),
    gsSP1Triangle(1, 2, 7, 1),
    gsSP1Triangle(2, 8, 7, 1),
    gsSP1Triangle(2, 3, 8, 1),
    gsSP1Triangle(3, 9, 8, 1),
    gsSP1Triangle(3, 4, 9, 1),
    gsSPVertex(&clrbar_vtx1, 10, 0),
    gsSP1Triangle(0, 6, 5, 0),
    gsSP1Triangle(0, 1, 6, 0),
    gsSP1Triangle(1, 7, 6, 1),
    gsSP1Triangle(1, 2, 7, 1),
    gsSP1Triangle(2, 8, 7, 1),
    gsSP1Triangle(2, 3, 8, 1),
    gsSP1Triangle(3, 9, 8, 1),
    gsSP1Triangle(3, 4, 9, 1),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(&clrbar_vtx2, 4, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSP1Triangle(1, 2, 3, 0),
    gsSPVertex(&clrbar_vtx3, 4, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSP1Triangle(1, 2, 3, 0),
    gsSPVertex(&clrbar_vtx4, 4, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSP1Triangle(1, 2, 3, 0),
    gsSPVertex(&clrbar_vtx5, 4, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSP1Triangle(1, 2, 3, 0),
    gsSPEndDisplayList(),
};
/* end of case clrbar, frame 12 */

/*
 * Color bars, Test 13.
 *
 *
 * 
 * Mon Oct 17 10:43:51 PDT 1994
 *
 */
static Vtx cc_modes_q0[4] =  {
        {       -159, -119, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {       -108, -119, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {       -159,  -88, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {       -108,  -88, 0, 0, 0, 0, 0x10, 0x10, 0x10, 0xff	},
};

static Vtx cc_modes_q1[4] =  {
        {       -108,  -88, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {        -44,  -88, 0, 0, 0, 0, 0x80, 0x80, 0x80, 0xff	},
        {       -108,  -24, 0, 0, 0, 0, 0x10, 0x10, 0x10, 0xff	},
        {        -44,  -24, 0, 0, 0, 0, 0xc0, 0xc0, 0xc0, 0xff	},
};

Gfx rdpatt_cc_modes[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),

    /* noise case */
#ifdef NOISE
    gsDPSetCombineLERP (NOISE, 0, SHADE, 0, 0, 0, 0, 0, NOISE, 0, SHADE, 0, 0, 0, 0, 0),
#endif
    gsSPVertex(&cc_modes_q0, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(1, 3, 2, 0),

    /* keying case */
    gsDPPipeSync(),
    gsDPSetKeyR(0x40, 0xff, 0xc0),
    gsDPSetKeyGB(0x40, 0xff, 0xc0, 0x40, 0xff, 0xc0),
    gsDPSetCombineKey(G_CK_KEY),
    gsDPSetCombineLERP (SHADE, CENTER, SCALE, 0, 0, 0, 0, 0, SHADE, CENTER, SCALE, 0, 0, 0, 0, 0),
    gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2),
    gsSPVertex(&cc_modes_q1, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(1, 3, 2, 0),
    gsSPEndDisplayList(),
};
/* end of keying case, frame 13 */

/*
 * Test 14, Frame 14:
 *
 * more rectangle tests
 * These tests cover many of the attributes and whether they synchronize correctly 
 * via pipesync's.
 *
 * 
 *  Fri Oct 21 
 *
 */

static Vtx rect14a[4] = {
        { 100, 120, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff        },
        {  60, 120, 0, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff     },
        {  60, 100, 0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff   },
        { 100, 100, 0, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff      },
};

static Vtx rect14b[12] = {
        { 100, 129, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0xff, 0, 0xff        },
        {  60, 129, 0, 0, (00 << 6), ( 0 << 6), 0, 0xff, 0, 0xff     },
        {  60, 125, 0, 0, (00 << 6), (00 << 6), 0, 0xff, 0, 0xff   },
        { 100, 125, 0, 0, ( 0 << 6), (00 << 6), 0, 0xff, 0, 0xff      },
        { 100, 134, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff        },
        {  60, 134, 0, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff     },
        {  60, 130, 0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff   },
        { 100, 130, 0, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff      },
        { 100, 139, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff        },
        {  60, 139, 0, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff     },
        {  60, 135, 0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff   },
        { 100, 135, 0, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff      },
};

#include "RGBA16blue.h"
#include "RGBA16red.h"
#include "RGBA16green.h"

Gfx rdpatt_rectangle14[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),





	/* texture mapping on/off */
	/* picture of dana.  Ensure lower right corner pixel draws (should be skin-color) */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF,G_RM_AA_ZB_OPA_SURF2),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPLoadTextureBlock(RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),

    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle(150<<2, 50<<2, 181<<2, 81<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),

    gsSPVertex(&rect14a, 4, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
	/* texture loads */
    gsDPSetPrimColor(150, 205, 0, 255, 0, 228),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(RGBA16blue, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 1, 0,
                         0, 0,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),


    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, RGBA16red),

    gsSPVertex(&rect14b, 12, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),

    gsDPLoadSync(),			/* needed to add */
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 0, (1<<G_TX_DXT_FRAC)),

    gsSP1Triangle(4, 6, 7, 0),
    gsSP1Triangle(4, 5, 6, 0),

    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, RGBA16green),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 0, (1<<G_TX_DXT_FRAC)),

    gsSP1Triangle(8, 10, 11, 0),
    gsSP1Triangle(8, 9, 10, 0),

    gsDPPipeSync(),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */




    /* set attributes, to be used as colors for rects */
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),

	/* test prim color */
	/* 3 bars: magenta over green over grey, all solid colors */
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 10, 50, 15),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 228),
    gsDPFillRectangle(10, 20, 50, 25),
    gsDPSetPrimColor(150, 205, 128, 128, 128, 228),
    gsDPFillRectangle(10, 30, 50, 35),
    gsDPPipeSync(),

	/* test 4 AA rendering modes */
	/* 5 bars: opaque, transp, transline, decalline, opaque */
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 128),
    gsDPFillRectangle(30, 38, 45, 87),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 40, 50, 45),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsDPFillRectangle(10, 50, 50, 55),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_XLU_LINE, G_RM_AA_XLU_LINE2),
    gsDPFillRectangle(10, 60, 50, 65),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_DEC_LINE, G_RM_AA_DEC_LINE2),
    gsDPFillRectangle(10, 70, 50, 75),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPFillRectangle(10, 80, 50, 85),
    gsDPPipeSync(),

	/* test 2 PT rendering modes */
	/* 3 bars: opaque, transp, opaque */
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 128),
    gsDPFillRectangle(30, 88, 45, 117),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 90, 50, 95),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPFillRectangle(10, 100, 50, 105),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPFillRectangle(10, 110, 50, 115),
    gsDPPipeSync(),

    	/* turn on zbuffering using primitive Z */
    gsSPSetGeometryMode(G_ZBUFFER),
    gsDPSetDepthSource(G_ZS_PRIM), /* primitive depth */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 128),

	/* from left to right horizontal bars are: */
	/* behind; behind-in-range; in-front-in-range; in-front; */
	/* of vertical bars */

	/* draw 4 vertical bars: full coverage */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimDepth(0x100,0x1),
    gsDPFillRectangle(12,118,15,240),
    gsDPSetPrimDepth(0x300,0x400),
    gsDPFillRectangle(22,118,25,240),
    gsDPSetPrimDepth(0x500,0x400),
    gsDPFillRectangle(32,118,35,240),
    gsDPSetPrimDepth(0x800,0x1),
    gsDPFillRectangle(42,118,45,240),
    gsDPPipeSync(),

	/* draw 4 vertical bars: half (3) coverage */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF | CVG_X_ALPHA, G_RM_AA_ZB_OPA_SURF2 | CVG_X_ALPHA),
    gsDPSetPrimDepth(0x100,0x1),
    gsDPFillRectangle(15,118,18,240),
    gsDPSetPrimDepth(0x300,0x400),
    gsDPFillRectangle(25,118,28,240),
    gsDPSetPrimDepth(0x500,0x400),
    gsDPFillRectangle(35,118,38,240),
    gsDPSetPrimDepth(0x800,0x1),
    gsDPFillRectangle(45,118,48,240),
    gsDPPipeSync(),

	/* test 4 ZB rendering modes */
	/* 4 bars: opaque, transp, decal, decal-transp */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPSetPrimDepth(0x400,0x1),
    gsDPFillRectangle(10, 120, 50, 125),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2),
    gsDPFillRectangle(10, 130, 50, 135),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_ZB_OPA_DECAL, G_RM_ZB_OPA_DECAL2),
    gsDPFillRectangle(10, 140, 50, 145),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_ZB_XLU_DECAL, G_RM_ZB_XLU_DECAL2),
    gsDPFillRectangle(10, 150, 50, 155),
    gsDPPipeSync(),

	/* test 8 AA ZB rendering modes */
	/* 9 bars: opaque, transp, decal, decal-transp, interpen, interpen-transp, dec-line, transp-line, opaque */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(10, 160, 50, 164),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPFillRectangle(10, 165, 50, 169),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_DECAL, G_RM_AA_ZB_OPA_DECAL2),
    gsDPFillRectangle(10, 170, 50, 174),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2),
    gsDPFillRectangle(10, 175, 50, 179),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_INTER, G_RM_AA_ZB_OPA_INTER2),
    gsDPFillRectangle(10, 180, 50, 184),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2),
    gsDPFillRectangle(10, 185, 50, 189),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_DEC_LINE, G_RM_AA_ZB_DEC_LINE2),
    gsDPFillRectangle(10, 190, 50, 194),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_LINE, G_RM_AA_ZB_XLU_LINE2),
    gsDPFillRectangle(10, 195, 50, 199),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(10, 200, 50, 204),
    gsDPPipeSync(),

	/* test prim depth (z and dz) */
	/* 5 bars: behind all, middle, in front of all, behind-not in range, behind-in range of 3, behind-in range of all */
	/* 5 bars should be: behind all, behind left 2, infront of all, invisible, decal on right 3, decal on all 4 */
    gsDPSetPrimDepth(0x7fff,0x1),
    gsDPFillRectangle(10, 210, 50, 214),
    gsDPSetPrimDepth(0x400,0x1),
    gsDPFillRectangle(10, 215, 50, 219),
    gsDPSetPrimDepth(0x0,0x1),
    gsDPFillRectangle(10, 220, 50, 224),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_DECAL, G_RM_AA_ZB_OPA_DECAL2),
    gsDPSetPrimDepth(0xa00,0x0),
    gsDPFillRectangle(10, 225, 50, 229),
    gsDPSetPrimDepth(0xa00,0x800),
    gsDPFillRectangle(10, 230, 50, 234),
    gsDPSetPrimDepth(0xa00,0x8000),
    gsDPFillRectangle(10, 235, 50, 239),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),

	/* dithering */
    gsDPSetPrimColor(150, 205, 0xaa, 0x55, 0x81, 128),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPFillRectangle(60, 10, 100, 15),
    gsDPSetColorDither(G_CD_BAYER),
    gsDPFillRectangle(60, 20, 100, 25),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPFillRectangle(60, 30, 100, 35),
    gsDPPipeSync(),

	/* overlap */
	/* a one-pixel high rectangle and a single pixel rectangle */
	/* both should have color:  r=0xe8 g=0x18 b=0x0 cvg=7 (truncated to 5/5/5/3) */
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0x20, 0x00, 0x80),
    gsDPFillRectangle(60, 40, 100, 41),
    gsDPFillRectangle(60, 40, 100, 41),
    gsDPFillRectangle(60, 40, 100, 41),
    gsDPFillRectangle(60, 40, 100, 41),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPPipeSync(),

	/* scissor */
	/* 2 red bars.  1st half as long as second */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0x00, 0x00, 0x80),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 80, 240),
    gsDPFillRectangle(60, 50, 100, 54),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 320, 240),
    gsDPFillRectangle(60, 55, 100, 59),
    gsDPPipeSync(),

	/* other colors: environment, blend, and fog: */
	/* 3 pairs of 2 bars: blue, yellow, blue, cyan, blue, cyan */
    gsDPSetCombineLERP (0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT), /* env color */
    gsDPSetEnvColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 60, 100, 64),
    gsDPPipeSync(),
    gsDPSetEnvColor(0xff,0xff,0,0xff),
    gsDPFillRectangle(60, 65, 100, 69),
    gsDPPipeSync(),
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c1(G_BL_CLR_BL, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM),AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c2(G_BL_CLR_BL, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetBlendColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 70, 100, 74),
    gsDPPipeSync(),
    gsDPSetBlendColor(0,0xff,0xff,0xff),
    gsDPFillRectangle(60, 75, 100, 79),
    gsDPPipeSync(),
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c1(G_BL_CLR_FOG, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM),AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c2(G_BL_CLR_FOG, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetFogColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 80, 100, 84),
    gsDPPipeSync(),
    gsDPSetFogColor(0,0xff,0xff,0xff),
    gsDPFillRectangle(60, 85, 100, 89),
    gsDPPipeSync(),

	/* set render mopde and combine lerp: */
	/* 2 bars: yellow, red */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(60, 90, 100, 94),
    gsDPPipeSync(),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPFillRectangle(60, 95, 100, 99),
    gsDPPipeSync(),


    /* restore original modes */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0xff, 0x00, 0x80),
    gsDPFillRectangle(310, 230, 320, 240),

    gsSPEndDisplayList(),
};
/* end of case 14 */

/*
 * Test 15, Frame 15:
 *
 * more rectangle tests
 * Same as test 14 but with 2 cycle mode
 *
 * 
 *  Thu Oct 27
 *
 */
Gfx rdpatt_rectangle15[4*MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),

    gsDPSetCycleType(G_CYC_2CYCLE),

    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),

	/* texture mapping on/off */
	/* picture of dana.  Ensure lower right corner pixel draws (should be skin-color) */
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_ZB_OPA_SURF2),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPLoadTextureBlock(RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),

    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle(150<<2, 50<<2, 181<<2, 81<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),

    gsSPVertex(&rect14a, 4, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
	/* texture loads */
    gsDPSetPrimColor(150, 205, 0, 255, 0, 228),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(RGBA16blue, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 1, 0,
                         0, 0,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),


    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, RGBA16red),

    gsSPVertex(&rect14b, 12, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),

    gsDPLoadSync(),			/* needed to add */
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 0, (1<<G_TX_DXT_FRAC)),

    gsSP1Triangle(4, 6, 7, 0),
    gsSP1Triangle(4, 5, 6, 0),

    gsDPLoadSync(),			/* needed to add */
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, RGBA16green),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 0, (1<<G_TX_DXT_FRAC)),

    gsSP1Triangle(8, 10, 11, 0),
    gsSP1Triangle(8, 9, 10, 0),

    gsDPPipeSync(),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */






    /* set attributes, to be used as colors for rects */
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_OPA_SURF2),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),

	/* test prim color */
	/* 3 bars: magenta over green over grey, all solid colors */
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 10, 50, 15),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 228),
    gsDPFillRectangle(10, 20, 50, 25),
    gsDPSetPrimColor(150, 205, 128, 128, 128, 228),
    gsDPFillRectangle(10, 30, 50, 35),
    gsDPPipeSync(),

	/* test 4 AA rendering modes */
	/* 5 bars: opaque, transp, transline, decalline, opaque */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 128),
    gsDPFillRectangle(30, 38, 45, 87),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 40, 50, 45),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
    gsDPFillRectangle(10, 50, 50, 55),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_LINE2),
    gsDPFillRectangle(10, 60, 50, 65),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_DEC_LINE2),
    gsDPFillRectangle(10, 70, 50, 75),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_OPA_SURF2),
    gsDPFillRectangle(10, 80, 50, 85),
    gsDPPipeSync(),

	/* test 2 PT rendering modes */
	/* 3 bars: opaque, transp, opaque */
    gsDPSetRenderMode(G_RM_PASS, G_RM_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 128),
    gsDPFillRectangle(30, 88, 45, 117),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 90, 50, 95),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPFillRectangle(10, 100, 50, 105),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_OPA_SURF2),
    gsDPFillRectangle(10, 110, 50, 115),
    gsDPPipeSync(),

    	/* turn on zbuffering using primitive Z */
    gsSPSetGeometryMode(G_ZBUFFER),
    gsDPSetDepthSource(G_ZS_PRIM), /* primitive depth */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 128),

	/* from left to right horizontal bars are: */
	/* behind; behind-in-range; in-front-in-range; in-front; */
	/* of vertical bars */

	/* draw 4 vertical bars: full coverage */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimDepth(0x100,0x1),
    gsDPFillRectangle(12,118,15,240),
    gsDPSetPrimDepth(0x300,0x400),
    gsDPFillRectangle(22,118,25,240),
    gsDPSetPrimDepth(0x500,0x400),
    gsDPFillRectangle(32,118,35,240),
    gsDPSetPrimDepth(0x800,0x1),
    gsDPFillRectangle(42,118,45,240),
    gsDPPipeSync(),

	/* draw 4 vertical bars: half (3) coverage */
    gsDPSetRenderMode(G_RM_PASS | CVG_X_ALPHA, G_RM_AA_ZB_OPA_SURF2 | CVG_X_ALPHA),
    gsDPSetPrimDepth(0x100,0x1),
    gsDPFillRectangle(15,118,18,240),
    gsDPSetPrimDepth(0x300,0x400),
    gsDPFillRectangle(25,118,28,240),
    gsDPSetPrimDepth(0x500,0x400),
    gsDPFillRectangle(35,118,38,240),
    gsDPSetPrimDepth(0x800,0x1),
    gsDPFillRectangle(45,118,48,240),
    gsDPPipeSync(),

	/* test 4 ZB rendering modes */
	/* 4 bars: opaque, transp, decal, decal-transp */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPSetPrimDepth(0x400,0x1),
    gsDPFillRectangle(10, 120, 50, 125),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_XLU_SURF2),
    gsDPFillRectangle(10, 130, 50, 135),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_OPA_DECAL2),
    gsDPFillRectangle(10, 140, 50, 145),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_XLU_DECAL2),
    gsDPFillRectangle(10, 150, 50, 155),
    gsDPPipeSync(),

	/* test 8 AA ZB rendering modes */
	/* 9 bars: opaque, transp, decal, decal-transp, interpen, interpen-transp, dec-line, transp-line, opaque */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(10, 160, 50, 164),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_SURF2),
    gsDPFillRectangle(10, 165, 50, 169),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_DECAL2),
    gsDPFillRectangle(10, 170, 50, 174),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_DECAL2),
    gsDPFillRectangle(10, 175, 50, 179),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_INTER2),
    gsDPFillRectangle(10, 180, 50, 184),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_INTER2),
    gsDPFillRectangle(10, 185, 50, 189),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_DEC_LINE2),
    gsDPFillRectangle(10, 190, 50, 194),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_LINE2),
    gsDPFillRectangle(10, 195, 50, 199),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(10, 200, 50, 204),
    gsDPPipeSync(),

	/* test prim depth (z and dz) */
	/* 5 bars: behind all, middle, in front of all, behind-not in range, behind-in range of 3, behind-in range of all */
	/* 5 bars should be: behind all, behind left 2, infront of all, invisible, decal on right 3, decal on all 4 */
    gsDPSetPrimDepth(0x7fff,0x1),
    gsDPFillRectangle(10, 210, 50, 214),
    gsDPSetPrimDepth(0x400,0x1),
    gsDPFillRectangle(10, 215, 50, 219),
    gsDPSetPrimDepth(0x0,0x1),
    gsDPFillRectangle(10, 220, 50, 224),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_DECAL2),
    gsDPSetPrimDepth(0xa00,0x0),
    gsDPFillRectangle(10, 225, 50, 229),
    gsDPSetPrimDepth(0xa00,0x800),
    gsDPFillRectangle(10, 230, 50, 234),
    gsDPSetPrimDepth(0xa00,0x8000),
    gsDPFillRectangle(10, 235, 50, 239),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),

	/* dithering */
    gsDPSetPrimColor(150, 205, 0xaa, 0x55, 0x81, 128),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPFillRectangle(60, 10, 100, 15),
    gsDPSetColorDither(G_CD_BAYER),
    gsDPFillRectangle(60, 20, 100, 25),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPFillRectangle(60, 30, 100, 35),
    gsDPPipeSync(),

	/* overlap */
	/* a one-pixel high rectangle and a single pixel rectangle */
	/* both should have color:  r=0xe8 g=0x18 b=0x0 cvg=7 (truncated to 5/5/5/3) */
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0x20, 0x00, 0x80),
    gsDPFillRectangle(60, 40, 100, 41),
    gsDPFillRectangle(60, 40, 100, 41),
    gsDPFillRectangle(60, 40, 100, 41),
    gsDPFillRectangle(60, 40, 100, 41),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPPipeSync(),

	/* scissor */
	/* 2 red bars.  1st half as long as second */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0x00, 0x00, 0x80),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 80, 240),
    gsDPFillRectangle(60, 50, 100, 54),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 320, 240),
    gsDPFillRectangle(60, 55, 100, 59),
    gsDPPipeSync(),

	/* other colors: environment, blend, and fog: */
	/* 3 pairs of 2 bars: blue, yellow, blue, cyan, blue, cyan */
    gsDPSetCombineLERP (0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT), /* env color */
    gsDPSetEnvColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 60, 100, 64),
    gsDPPipeSync(),
    gsDPSetEnvColor(0xff,0xff,0,0xff),
    gsDPFillRectangle(60, 65, 100, 69),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS,AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c2(G_BL_CLR_BL, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetBlendColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 70, 100, 74),
    gsDPPipeSync(),
    gsDPSetBlendColor(0,0xff,0xff,0xff),
    gsDPFillRectangle(60, 75, 100, 79),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS,AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c2(G_BL_CLR_FOG, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetFogColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 80, 100, 84),
    gsDPPipeSync(),
    gsDPSetFogColor(0,0xff,0xff,0xff),
    gsDPFillRectangle(60, 85, 100, 89),
    gsDPPipeSync(),

	/* set render mopde and combine lerp: */
	/* 2 bars: yellow, red */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(60, 90, 100, 94),
    gsDPPipeSync(),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPFillRectangle(60, 95, 100, 99),
    gsDPPipeSync(),

    /* restore original modes */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0xff, 0x00, 0x80),
    gsDPFillRectangle(310, 230, 320, 240),

    gsSPEndDisplayList(),
};
/* end of case 15 */

/*
 * Test 16, Frame 16:
 *
 * more rectangle tests
 * Same as test 14 but with fill mode
 *
 * 
 *  Thu Oct 27
 *
 */
Gfx rdpatt_rectangle16[4*MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),

    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetFillColor(0xFDC1FDC1),

    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),

	/* texture mapping on/off */
	/* picture of dana.  Ensure lower right corner pixel draws (should be skin-color) */
    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB2),
    gsDPSetTextureFilter(G_TF_POINT),

    gsDPLoadTextureBlock(RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),

    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle(150<<2, 50<<2, 181<<2, 81<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),


    	/* set attributes, to be used as colors for rects */
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),

	/* test fill color */
	/* 3 bars: magenta over green over grey, all solid colors */
    gsDPFillRectangle(60, 140, 100, 143),
    gsDPPipeSync(),
    gsDPSetFillColor(0x783e783e),
    gsDPFillRectangle(60, 145, 100, 148),

	/* test prim color */
	/* 3 bars: magenta over green over grey, all solid colors */
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 10, 50, 15),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 228),
    gsDPFillRectangle(10, 20, 50, 25),
    gsDPSetPrimColor(150, 205, 128, 128, 128, 228),
    gsDPFillRectangle(10, 30, 50, 35),
    gsDPPipeSync(),


    /* restore original modes */
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0xff, 0x00, 0x80),
    gsDPFillRectangle(310, 230, 320, 240),

    gsSPEndDisplayList(),
};
/* end of case 16 */

/*
 * Test 17, Frame 17:
 *
 * more rectangle tests
 * Same as test 14 but with copy mode
 *
 * 
 *  Thu Oct 27
 *
 */

#include "RGBA16blue2.h"
#include "RGBA16red2.h"
#include "RGBA16green2.h"

Gfx rdpatt_rectangle17[4*MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),

    gsDPSetCycleType(G_CYC_COPY),

    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),

	/* texture mapping on/off */
	/* picture of dana.  Ensure lower right corner pixel draws (should be skin-color) */
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_POINT),

    gsDPLoadTextureBlock(RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),

    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle(150<<2, 50<<2, 181<<2, 81<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),
    gsSPTextureRectangle(60<<2, 100<<2, 100<<2, 120<<2, G_TX_RENDERTILE, 0, 0, (int) ((32.0/40.0)*((float) (4<<10))), (int) ((32.0/20.0)*((float) (1<<10)))),

    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */

	/* texture loads */
    gsDPSetPrimColor(150, 205, 0, 255, 0, 228),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(RGBA16blue2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 1, 0,
                         0, 0,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),


    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, RGBA16red2),

    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle(60<<2, 125<<2, 100<<2, 130<<2, G_TX_RENDERTILE, 0, 0, 0, 0),

    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 0, (1<<G_TX_DXT_FRAC)),

    gsSPTextureRectangle(60<<2, 135<<2, 100<<2, 140<<2, G_TX_RENDERTILE, 0, 0, 0, 0),

    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, RGBA16green2),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 0, (1<<G_TX_DXT_FRAC)),

    gsSPTextureRectangle(60<<2, 145<<2, 100<<2, 150<<2, G_TX_RENDERTILE, 0, 0, 0, 0),

    gsDPPipeSync(),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */


	/* scissor */
	/* 2 red bars.  1st half as long as second */
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0x00, 0x00, 0x80),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 80, 240),
    gsSPTextureRectangle(60<<2, 50<<2, 100<<2, 55<<2, G_TX_RENDERTILE, 0, 0, 0, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 320, 240),
    gsSPTextureRectangle(60<<2, 60<<2, 100<<2, 65<<2, G_TX_RENDERTILE, 0, 0, 0, 0),
    gsDPPipeSync(),

    gsDPSetTexturePersp(G_TP_PERSP),



    /* restore original modes */
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0xff, 0x00, 0x80),
    gsDPFillRectangle(310, 230, 340, 240),

    gsSPEndDisplayList(),
};
/* end of case 17 */

/*
 * Test 18, Frame 18:
 *
 * simple rectangles for verilog memspan tests
 * stolen from tests 14-17
 *
 * 
 *  Thu Nov 17
 *
 */

Gfx rdpatt_rectangle18[4*MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),





	/* texture mapping on/off */
	/* picture of dana.  Ensure lower right corner pixel draws (should be skin-color) */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF,G_RM_AA_ZB_OPA_SURF2),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPLoadTextureBlock(RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),

    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle(150<<2, 50<<2, 181<<2, 81<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),

    gsSPVertex(&rect14a, 4, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
	/* texture loads */
    gsDPSetPrimColor(150, 205, 0, 255, 0, 228),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(RGBA16blue, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 1, 0,
                         0, 0,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),


    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, RGBA16red),

    gsSPVertex(&rect14b, 12, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),

    gsDPLoadSync(),			/* needed to add */
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 0, (1<<G_TX_DXT_FRAC)),

    gsSP1Triangle(4, 6, 7, 0),
    gsSP1Triangle(4, 5, 6, 0),

    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, RGBA16green),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 0, (1<<G_TX_DXT_FRAC)),

    gsSP1Triangle(8, 10, 11, 0),
    gsSP1Triangle(8, 9, 10, 0),

    gsDPPipeSync(),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */




    /* set attributes, to be used as colors for rects */
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),

	/* test prim color */
	/* 3 bars: magenta over green over grey, all solid colors */
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 10, 50, 15),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 228),
    gsDPFillRectangle(10, 20, 50, 25),
    gsDPSetPrimColor(150, 205, 128, 128, 128, 228),
    gsDPFillRectangle(10, 30, 50, 35),
    gsDPPipeSync(),

	/* test 4 AA rendering modes */
	/* 5 bars: opaque, transp, transline, decalline, opaque */
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 128),
    gsDPFillRectangle(30, 38, 45, 87),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 40, 50, 45),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsDPFillRectangle(10, 50, 50, 55),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_XLU_LINE, G_RM_AA_XLU_LINE2),
    gsDPFillRectangle(10, 60, 50, 65),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_DEC_LINE, G_RM_AA_DEC_LINE2),
    gsDPFillRectangle(10, 70, 50, 75),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPFillRectangle(10, 80, 50, 85),
    gsDPPipeSync(),

	/* test 2 PT rendering modes */
	/* 3 bars: opaque, transp, opaque */
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 128),
    gsDPFillRectangle(30, 88, 45, 117),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 90, 50, 95),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPFillRectangle(10, 100, 50, 105),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPFillRectangle(10, 110, 50, 115),
    gsDPPipeSync(),

    	/* turn on zbuffering using primitive Z */
    gsSPSetGeometryMode(G_ZBUFFER),
    gsDPSetDepthSource(G_ZS_PRIM), /* primitive depth */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 128),

	/* from left to right horizontal bars are: */
	/* behind; behind-in-range; in-front-in-range; in-front; */
	/* of vertical bars */

	/* draw 4 vertical bars: full coverage */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimDepth(0x100,0x1),
    gsDPFillRectangle(12,118,15,240),
    gsDPSetPrimDepth(0x300,0x400),
    gsDPFillRectangle(22,118,25,240),
    gsDPSetPrimDepth(0x500,0x400),
    gsDPFillRectangle(32,118,35,240),
    gsDPSetPrimDepth(0x800,0x1),
    gsDPFillRectangle(42,118,45,240),
    gsDPPipeSync(),

	/* draw 4 vertical bars: half (3) coverage */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF | CVG_X_ALPHA, G_RM_AA_ZB_OPA_SURF2 | CVG_X_ALPHA),
    gsDPSetPrimDepth(0x100,0x1),
    gsDPFillRectangle(15,118,18,240),
    gsDPSetPrimDepth(0x300,0x400),
    gsDPFillRectangle(25,118,28,240),
    gsDPSetPrimDepth(0x500,0x400),
    gsDPFillRectangle(35,118,38,240),
    gsDPSetPrimDepth(0x800,0x1),
    gsDPFillRectangle(45,118,48,240),
    gsDPPipeSync(),

	/* test 4 ZB rendering modes */
	/* 4 bars: opaque, transp, decal, decal-transp */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPSetPrimDepth(0x400,0x1),
    gsDPFillRectangle(10, 120, 50, 125),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2),
    gsDPFillRectangle(10, 130, 50, 135),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_ZB_OPA_DECAL, G_RM_ZB_OPA_DECAL2),
    gsDPFillRectangle(10, 140, 50, 145),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_ZB_XLU_DECAL, G_RM_ZB_XLU_DECAL2),
    gsDPFillRectangle(10, 150, 50, 155),
    gsDPPipeSync(),

	/* test 8 AA ZB rendering modes */
	/* 9 bars: opaque, transp, decal, decal-transp, interpen, interpen-transp, dec-line, transp-line, opaque */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(10, 160, 50, 164),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPFillRectangle(10, 165, 50, 169),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_DECAL, G_RM_AA_ZB_OPA_DECAL2),
    gsDPFillRectangle(10, 170, 50, 174),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2),
    gsDPFillRectangle(10, 175, 50, 179),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_INTER, G_RM_AA_ZB_OPA_INTER2),
    gsDPFillRectangle(10, 180, 50, 184),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2),
    gsDPFillRectangle(10, 185, 50, 189),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_DEC_LINE, G_RM_AA_ZB_DEC_LINE2),
    gsDPFillRectangle(10, 190, 50, 194),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_LINE, G_RM_AA_ZB_XLU_LINE2),
    gsDPFillRectangle(10, 195, 50, 199),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(10, 200, 50, 204),
    gsDPPipeSync(),

	/* test prim depth (z and dz) */
	/* 5 bars: behind all, middle, in front of all, behind-not in range, behind-in range of 3, behind-in range of all */
	/* 5 bars should be: behind all, behind left 2, infront of all, invisible, decal on right 3, decal on all 4 */
    gsDPSetPrimDepth(0x7fff,0x1),
    gsDPFillRectangle(10, 210, 50, 214),
    gsDPSetPrimDepth(0x400,0x1),
    gsDPFillRectangle(10, 215, 50, 219),
    gsDPSetPrimDepth(0x0,0x1),
    gsDPFillRectangle(10, 220, 50, 224),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_DECAL, G_RM_AA_ZB_OPA_DECAL2),
    gsDPSetPrimDepth(0xa00,0x0),
    gsDPFillRectangle(10, 225, 50, 229),
    gsDPSetPrimDepth(0xa00,0x800),
    gsDPFillRectangle(10, 230, 50, 234),
    gsDPSetPrimDepth(0xa00,0x8000),
    gsDPFillRectangle(10, 235, 50, 239),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),

	/* dithering */
    gsDPSetPrimColor(150, 205, 0xaa, 0x55, 0x81, 128),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPFillRectangle(60, 10, 100, 15),
    gsDPSetColorDither(G_CD_BAYER),
    gsDPFillRectangle(60, 20, 100, 25),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPFillRectangle(60, 30, 100, 35),
    gsDPPipeSync(),

	/* overlap */
	/* a one-pixel high rectangle and a single pixel rectangle */
	/* both should have color:  r=0xe8 g=0x18 b=0x0 cvg=7 (truncated to 5/5/5/3) */
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0x20, 0x00, 0x80),
    gsDPFillRectangle(60, 40, 100, 41),
    gsDPFillRectangle(60, 40, 100, 41),
    gsDPFillRectangle(60, 40, 100, 41),
    gsDPFillRectangle(60, 40, 100, 41),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPPipeSync(),

	/* scissor */
	/* 2 red bars.  1st half as long as second */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0x00, 0x00, 0x80),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 80, 240),
    gsDPFillRectangle(60, 50, 100, 54),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 320, 240),
    gsDPFillRectangle(60, 55, 100, 59),
    gsDPPipeSync(),

	/* other colors: environment, blend, and fog: */
	/* 3 pairs of 2 bars: blue, yellow, blue, cyan, blue, cyan */
    gsDPSetCombineLERP (0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT), /* env color */
    gsDPSetEnvColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 60, 100, 64),
    gsDPPipeSync(),
    gsDPSetEnvColor(0xff,0xff,0,0xff),
    gsDPFillRectangle(60, 65, 100, 69),
    gsDPPipeSync(),
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c1(G_BL_CLR_BL, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM),AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c2(G_BL_CLR_BL, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetBlendColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 70, 100, 74),
    gsDPPipeSync(),
    gsDPSetBlendColor(0,0xff,0xff,0xff),
    gsDPFillRectangle(60, 75, 100, 79),
    gsDPPipeSync(),
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c1(G_BL_CLR_FOG, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM),AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c2(G_BL_CLR_FOG, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetFogColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 80, 100, 84),
    gsDPPipeSync(),
    gsDPSetFogColor(0,0xff,0xff,0xff),
    gsDPFillRectangle(60, 85, 100, 89),
    gsDPPipeSync(),

	/* set render mopde and combine lerp: */
	/* 2 bars: yellow, red */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(60, 90, 100, 94),
    gsDPPipeSync(),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPFillRectangle(60, 95, 100, 99),
    gsDPPipeSync(),


    /* restore original modes */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0xff, 0x00, 0x80),
    gsDPFillRectangle(310, 230, 320, 240),

    gsSPEndDisplayList(),
};
/* end of case 14 */

/*
 * Test 20
 *
 * Z testing.
 *
 * Fri Nov  4 13:58:55 PST 1994
 *
 */
static Vtx q20[11] =  {
        {         0,  0,    -0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         0,  0,    -1, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         0,  0,   -10, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         1,  0,  -100, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         2,  0,  -200, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         3,  0,  -400, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         4,  0,  -800, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         5,  0, -1600, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         6,  0, -2400, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         7,  0, -3200, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         8,  0, -4000, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
};

Gfx rdpatt_square20[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF,G_RM_AA_OPA_SURF2),
    gsSPVertex(&q20, 11, 0),
    /* no triangles */
    gsSPEndDisplayList(),
};
/* end of case 20 */

/*
 * Test 21, Frame 21:
 *
 * Z test
 *
 */
static Vtx q21[10] =  {
        {        -40,  40, -1000, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {         40,  40, -1000, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {        -40,   0,  -500, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {         40,   0,  -500, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {        -40, -40,     0, 0, 0, 0, 0, 0, 0xff, 0xff	},
        {         40, -40,     0, 0, 0, 0, 0, 0, 0xff, 0xff	},

        {        -20,  20,  -200, 0, 0, 0, 0, 0xff, 0xff, 0xff	},
        {         20,  20,  -200, 0, 0, 0, 0, 0xff, 0xff, 0xff	},
        {        -20,   0,  -200, 0, 0, 0, 0, 0xff, 0xff, 0xff	},
        {         20,   0,  -200, 0, 0, 0, 0, 0xff, 0xff, 0xff	},
};

Gfx rdpatt_square21[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF,G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&q21, 10, 0),

    gsSP1Triangle(6, 7, 9, 0),
    gsSP1Triangle(6, 9, 8, 0),

    gsSP1Triangle(0, 1, 5, 0),
    gsSP1Triangle(0, 5, 4, 0),
/*
    gsSP1Triangle(0, 1, 3, 0),
    gsSP1Triangle(0, 3, 2, 0),
    gsSP1Triangle(2, 3, 5, 0),
    gsSP1Triangle(2, 5, 4, 0),
*/

    gsSPEndDisplayList(),
};
/* end of case 21 */

/*
 * Test 22, Frame 22:
 *
 *  12/28/94
 *
 */

static Vtx vitri[3] = {
        { 200, 213, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff        },
        {  46, 137, 0, 0, (31 << 6), ( 0 << 6), 0xff, 0, 0, 0xff     },
        {  60, 0, 0, 0, (31 << 6), (31 << 6), 0, 0xff, 0, 0xff   },
};

Gfx rdpatt_vitriangle[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),

    /* set attributes, to be used as colors for rects */
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetCombineLERP (0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE),

    gsSPVertex(&vitri, 3, 0),
    gsSP1Triangle(0, 2, 1, 0),

    gsSPEndDisplayList(),
};
/* end of case 22 */

/*
 * Test 40, alpha blending range
 */

static Vtx blendrange_tris[6] =  {
	{	-40,  40, 0, 0, 0, 0, 0xff, 0x0, 0x0, 0xff	},
	{	-20,  40, 0, 0, 0, 0, 0xff, 0x0, 0x0, 0xff	},
	{	-30,  50, 0, 0, 0, 0, 0xff, 0x0, 0x0, 0xff	},

	{	-20,  40, 0, 0, 0, 0, 0xff, 0x0, 0x0, 0x00	},
	{	  0,  40, 0, 0, 0, 0, 0xff, 0x0, 0x0, 0x80	},
	{	-10,  50, 0, 0, 0, 0, 0xff, 0x0, 0x0, 0xff	},
};

Gfx rdpatt_blendrange_dl[] = {
    gsSPVertex(&blendrange_tris, 6, 0),
    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),

    gsSPEndDisplayList(),
};

/*
 *  Test 30 - ??
 *
 *  Define simple textures, use clamp, wrap, mirror to create
 *  striped and checkerboard textures.
 */
#include "IA4tree2.h"

/* IA 4, 16x1 */
static char  test30_IA4[] = {
        0x13, 0x57, 0x9b, 0xdf,	0xfd, 0xb1, 0x57, 0xb3 };

/* IA 8, 8x2 */
static char  test30_IA8[] = {
        0xf5, 0x9f, 0xaf, 0xbf,	0xcf, 0xdf, 0xef, 0x05,
        0xf5, 0x1f, 0x2f, 0x3f,	0x4f, 0x5f, 0x6f, 0x05 };

/* IA 16, 8x4 */
static char  test30_IA16[] = {
        0xc0, 0x80, 0xc0, 0x80,	0xc0, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	0xff, 0xff, 0xff, 0xff,
        0xc0, 0x80, 0xc0, 0x80,	0xc0, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	0xff, 0xff, 0xff, 0xff,
        0x00, 0xff, 0x00, 0xff,	0x00, 0xff, 0x00, 0xff, 0x95, 0x40, 0x95, 0x40,	0x95, 0x40, 0x95, 0x40,
        0x00, 0xff, 0x00, 0xff,	0x00, 0xff, 0x00, 0xff, 0x95, 0x40, 0x95, 0x40,	0x95, 0x40, 0x95, 0x40 };

/* I 8, 8x4, last row not used */
static char  test30_I8[] = {
/* 
        0x00, 0xff, 0x00, 0x00,	0x00, 0x00, 0x00, 0x44,
        0x00, 0xff, 0xcc, 0x00,	0x00, 0x00, 0x66, 0x44,
        0x00, 0xff, 0xcc, 0xaa,	0x00, 0x88, 0x66, 0x44,
        0x00, 0xff, 0xcc, 0x00,	0x00, 0x00, 0x66, 0x44 
*/
        0x10, 0x10, 0x10, 0xff,	0x10, 0x10, 0x10, 0x10,
        0x10, 0xff, 0xff, 0xff,	0xff, 0xff, 0xff, 0x10,
        0x10, 0xff, 0xff, 0xff,	0xff, 0xff, 0xff, 0x10,
        0x10, 0x10, 0x10, 0xff,	0x10, 0x10, 0x10, 0x10 
};

/* RGBA 16, Texture Look Up Table (TLUT), for tree0_dl */
static char test30_tlutRGBA[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* indx 0 */
	0xf8, 0x01, 0xf8, 0x01, 0xf8, 0x01, 0xf8, 0x01, /* indx 1 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* indx 2 */
	0x07, 0xc1, 0x07, 0xc1, 0x07, 0xc1, 0x07, 0xc1, /* indx 3 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* indx 4 */
	0x00, 0x3f, 0x00, 0x3f, 0x00, 0x3f, 0x00, 0x3f, /* indx 5 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* indx 6 */
	0xff, 0xc1, 0xff, 0xc1, 0xff, 0xc1, 0xff, 0xc1, /* indx 7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* indx 8 */
	0x07, 0xff, 0x07, 0xff, 0x07, 0xff, 0x07, 0xff, /* indx 9 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* indx a */
	0xf8, 0x3f, 0xf8, 0x3f, 0xf8, 0x3f, 0xf8, 0x3f, /* indx b */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* indx c */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /* indx d */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* indx e */
	0xaf, 0xff, 0xaf, 0xff, 0xaf, 0xff, 0xaf, 0xff, /* indx f */
};

/* IA 16, Texture Look Up Table (TLUT), for tree1_dl */
static char test30_tlutIA[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* indx 0 */
	0x10, 0xff, 0x10, 0xff, 0x10, 0xff, 0x10, 0xff, /* indx 1 */
	0x20, 0xff, 0x20, 0xff, 0x20, 0xff, 0x20, 0xff, /* indx 2 */
	0x30, 0xff, 0x30, 0xff, 0x30, 0xff, 0x30, 0xff, /* indx 3 */
	0x40, 0xff, 0x40, 0xff, 0x40, 0xff, 0x40, 0xff, /* indx 4 */
	0x50, 0xff, 0x50, 0xff, 0x50, 0xff, 0x50, 0xff, /* indx 5 */
	0x60, 0xff, 0x60, 0xff, 0x60, 0xff, 0x60, 0xff, /* indx 6 */
	0x70, 0xff, 0x70, 0xff, 0x70, 0xff, 0x70, 0xff, /* indx 7 */
	0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, /* indx 8 */
	0x90, 0xff, 0x90, 0xff, 0x90, 0xff, 0x90, 0xff, /* indx 9 */
	0xa0, 0xff, 0xa0, 0xff, 0xa0, 0xff, 0xa0, 0xff, /* indx a */
	0xb0, 0xff, 0xb0, 0xff, 0xb0, 0xff, 0xb0, 0xff, /* indx b */
	0xc0, 0xff, 0xc0, 0xff, 0xc0, 0xff, 0xc0, 0xff, /* indx c */
	0xd0, 0xff, 0xd0, 0xff, 0xd0, 0xff, 0xd0, 0xff, /* indx d */
	0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xff, /* indx e */
	0xf0, 0xff, 0xf0, 0xff, 0xf0, 0xff, 0xf0, 0xff, /* indx f */
};

/*
 * Test 30, regression test. Used as a placeholder.
 *
 * Opaque and translucent interpenetrating geometry
 * some shaded and textured objects.  On a large flat
 * floor with perspective checkerboard.
 *
 * Wed Oct  5 22:12:43 PDT 1994
 *
 */

/* box vertices */
static Vtx box_vtx[8] = {
{  -50, -50,   0, 0, 0, 0,   0,   0,   0, 128 },
{  -50, -50, 100, 0, 0, 0, 255,   0,   0, 128 },
{  -50,  50, 100, 0, 0, 0,   0, 254,   0, 128 },
{  -50,  50,   0, 0, 0, 0, 255, 254,   0, 128 },
{   50, -50,   0, 0, 0, 0,   0,   0, 252, 128 },
{   50, -50, 100, 0, 0, 0, 255,   0, 252, 128 },
{   50,  50, 100, 0, 0, 0,   0, 254, 252, 128 },
{   50,  50,   0, 0, 0, 0, 255, 254, 252, 128 }};

Gfx rdpatt_box_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2),

    /* Box display list */
    gsSPVertex(&box_vtx, 8, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(3, 2, 6, 0),
    gsSP1Triangle(3, 6, 7, 0),
    gsSP1Triangle(7, 6, 5, 0),
    gsSP1Triangle(7, 5, 4, 0),
    gsSP1Triangle(4, 5, 1, 0),
    gsSP1Triangle(4, 1, 0, 0),
    gsSP1Triangle(5, 6, 2, 0),
    gsSP1Triangle(5, 2, 1, 0),
    gsSP1Triangle(7, 4, 0, 0),
    gsSP1Triangle(7, 0, 3, 0),

    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

static Vtx box1_vtx[8] = {
{  -25, -25,   0, 0,  (0 << 5), (0 << 5),   0,   0,   0, 255 },
{  -25, -25,  40, 0,  (0 << 5), (0 << 5), 255,   0,   0, 255 },
{  -25,  25,  40, 0,  (0 << 5), (16 << 5),   0, 254,   0, 255 },
{  -25,  25,   0, 0,  (0 << 5), (16 << 5), 255, 254,   0, 255 },
{   25, -25,   0, 0, (32 << 5), (0 << 5),   0,   0, 252, 255 },
{   25, -25,  40, 0, (32 << 5), (0 << 5), 255,   0, 252, 255 },
{   25,  25,  40, 0, (32 << 5), (16 << 5),   0, 254, 252, 255 },
{   25,  25,   0, 0, (32 << 5), (16 << 5), 255, 254, 252, 255 }};

Gfx rdpatt_box1_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_INTER, G_RM_AA_ZB_OPA_INTER2),

    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEI, G_CC_MODULATEI),

    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPLoadTextureBlock(test30_I8, G_IM_FMT_I, G_IM_SIZ_8b, 8, 4, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         3, 2, G_TX_NOLOD, G_TX_NOLOD),

    /* Box display list */
    gsSPVertex(&box1_vtx, 8, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(3, 2, 6, 0),
    gsSP1Triangle(3, 6, 7, 0),
    gsSP1Triangle(7, 6, 5, 0),
    gsSP1Triangle(7, 5, 4, 0),
    gsSP1Triangle(4, 5, 1, 0),
    gsSP1Triangle(4, 1, 0, 0),
    gsSP1Triangle(5, 6, 2, 0),
    gsSP1Triangle(5, 2, 1, 0),
    gsSP1Triangle(7, 4, 0, 0),
    gsSP1Triangle(7, 0, 3, 0),

    gsSPTexture(8, 4, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

/* cone vertices */
static Vtx cone_vtx[12] = {
{ 100, 0, 0, 0, 0, 0, 127, 127, 127, 255 },
{ 80, 58, 0, 0, 0, 0, 160, 160, 160, 255 },
{ 30, 95, 0, 0, 0, 0, 190, 190, 190, 255 },
{ -30, 95, 0, 0, 0, 0, 220, 220, 220, 255 },
{ -80, 58, 0, 0, 0, 0, 250, 250, 250, 255 },
{ -100, 0, 0, 0, 0, 0, 255, 255, 255, 255 },
{ -80, -58, 0, 0, 0, 0, 250, 250, 250, 255 },
{ -30, -95, 0, 0, 0, 0, 220, 220, 220, 255 },
{ 30, -95, 0, 0, 0, 0, 190, 190, 190, 255 },
{ 80, -58, 0, 0, 0, 0, 160, 160, 160, 255 },
{ 0, 0, 0, 0, 0, 0, 127, 127, 127, 255 },
{ 0, 0, 200, 0, 0, 0, 127, 127, 127, 255 }};

Gfx rdpatt_cone_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    /* gsDPSetRenderMode(G_RM_AA_ZB_OPA_INTER, G_RM_AA_ZB_OPA_INTER2), */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),

    /* cone display list */
    gsSPVertex(&cone_vtx, 12, 0),
    gsSP1Triangle(1, 0, 10, 0),
    gsSP1Triangle(2, 1, 10, 0),
    gsSP1Triangle(3, 2, 10, 0),
    gsSP1Triangle(4, 3, 10, 0),
    gsSP1Triangle(5, 4, 10, 0),
    gsSP1Triangle(6, 5, 10, 0),
    gsSP1Triangle(7, 6, 10, 0),
    gsSP1Triangle(8, 7, 10, 0),
    gsSP1Triangle(9, 8, 10, 0),
    gsSP1Triangle(0, 9, 10, 0),
    gsSP1Triangle(0, 1, 11, 0),
    gsSP1Triangle(1, 2, 11, 0),
    gsSP1Triangle(2, 3, 11, 0),
    gsSP1Triangle(3, 4, 11, 0),
    gsSP1Triangle(4, 5, 11, 0),
    gsSP1Triangle(5, 6, 11, 0),
    gsSP1Triangle(6, 7, 11, 0),
    gsSP1Triangle(7, 8, 11, 0),
    gsSP1Triangle(8, 9, 11, 0),
    gsSP1Triangle(9, 0, 11, 0),

    gsSPEndDisplayList(),
};

static Vtx icosa_vtx[6] = {
{    0,   0,   0, 0, (32 << 5), (64 << 5), 255,   0,   0, 255 },
{  -50,   0,  50, 0, (0 << 5),         0,   0, 254,   0, 255 },
{    0,  50,  50, 0, (64 << 5),         0, 255, 254,   0, 255 },
{    0, -50,  50, 0, (64 << 5),         0,   0,   0, 252, 255 },
{   50,   0,  50, 0, (0 << 5),         0, 255,   0, 252, 255 },
{    0,   0, 100, 0, (32 << 5), (64 << 5),   0, 254, 252, 255 }};

Gfx rdpatt_icosa_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2),

    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),

    gsDPLoadTextureBlock(test30_IA16, G_IM_FMT_IA, G_IM_SIZ_16b, 8, 4, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         3, 2, G_TX_NOLOD, G_TX_NOLOD),

    /* Icosa display list */
    gsSPVertex(&icosa_vtx, 6, 0),
    gsSP1Triangle(0, 1, 3, 0),
    gsSP1Triangle(1, 5, 3, 0),
    gsSP1Triangle(2, 1, 0, 0),
    gsSP1Triangle(2, 5, 1, 0),

    gsDPLoadTextureBlock(test30_IA8, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 2, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         3, 1, G_TX_NOLOD, G_TX_NOLOD),

    gsSP1Triangle(2, 4, 5, 0),
    gsSP1Triangle(2, 0, 4, 0),
    gsSP1Triangle(4, 3, 5, 0),
    gsSP1Triangle(0, 3, 4, 0),
    
    gsSPTexture(16, 2, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};



#include "torus_vtx.h"



Gfx rdpatt_torus_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_INTER, G_RM_AA_ZB_OPA_INTER2),

#include "torus_cmds.h"

    gsSPEndDisplayList(),
};


static Vtx ground_vtx[6] = {
{ -150, 0, -500, 0, 0, (400 << 5), 21, 21, 201, 255 },
{ -150, 0,  300, 0, 0, 0, 21, 201, 21, 255 },
{    0, 0, -500, 0, (75 << 5), (400 << 5), 201, 21, 21, 255 },
{    0, 0,  300, 0, (75 << 5), 0, 201, 21, 21, 255 },
{  150, 0, -500, 0, 0, (400 << 5), 21, 21, 201, 255 },
{  150, 0,  300, 0, 0, 0, 21, 201, 21, 255 },

/*
 * longitudal cutting plane...
 *
{  100,  150, -500, 0, 0, 0, 210, 210, 210, 255 },
{  100, -150, -500, 0, 0, 0, 210, 210, 210, 255 },
{ -100,  150,  200, 0, 0, 0, 210, 210, 210, 255 },
{ -100, -150,  200, 0, 0, 0, 210, 210, 210, 255 },
*/
};

Gfx rdpatt_ground_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_INTER, G_RM_AA_ZB_OPA_INTER2),

    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPLoadTextureBlock_4b(test30_IA4, G_IM_FMT_IA, 16, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         4, 0, G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&ground_vtx[0], 6, 0),

    gsSP1Triangle (0, 1, 2, 0),
    gsSP1Triangle (1, 3, 2, 0),
    gsSP1Triangle (2, 3, 5, 0),
    gsSP1Triangle (2, 5, 4, 0),

/*
 * longitudal cutting plane...
 *
    gsSP1Triangle (8, 7, 6, 0),
    gsSP1Triangle (8, 9, 7, 0),
*/

    gsSPTexture(16, 2, 0, G_TX_RENDERTILE, G_OFF),

    gsSPEndDisplayList(),
};

/*
 *  non-zbuffered version of ground
 */
Gfx rdpatt_ground_nzb_dl[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),

    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPLoadTextureBlock_4b(test30_IA4, G_IM_FMT_IA, 16, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         4, 0, G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&ground_vtx[0], 6, 0),

    gsSP1Triangle (0, 1, 2, 0),
    gsSP1Triangle (1, 3, 2, 0),
    gsSP1Triangle (2, 3, 5, 0),
    gsSP1Triangle (2, 5, 4, 0),

/*
 * longitudal cutting plane...
 *
    gsSP1Triangle (8, 7, 6, 0),
    gsSP1Triangle (8, 9, 7, 0),
*/

    gsSPTexture(16, 2, 0, G_TX_RENDERTILE, G_OFF),

    gsSPEndDisplayList(),
};

/*
 *  Tree vertices, used by tree0,1,2,3_dl below.
 */
static Vtx tree_vtx[8] = {
{ -120,  0,  270, 0, (-31 << 6),         0,  0,  51,  0, 255 },
{  -90,  0,  290, 0,  (31 << 6),         0,  0,  21,  0, 255 },
{  -90, 45,  290, 0,  (31 << 6), (63 << 6), 19, 150, 21, 255 },
{ -120, 45,  270, 0, (-31 << 6), (63 << 6), 21, 150, 21, 255 },
{ -120,  0,  290, 0, (-31 << 6),         0,  0,  21,  0, 255 },
{  -90,  0,  270, 0,  (31 << 6),         0,  0,  41,  0, 255 },
{  -90, 45,  270, 0,  (31 << 6), (63 << 6), 19, 150, 21, 255 },
{ -120, 45,  290, 0, (-31 << 6), (63 << 6), 21, 150, 21, 255 }};

/*
 *  Tree 0, loads a TLUT, then a 4-bit IA texture that is also
 *  used as a CI texture.
 *
 *  Color Index, 4 bit, TLUT is 16-bit RGBA
 */
Gfx rdpatt_tree0_dl[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),

    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLUT(G_TT_RGBA16),

    /* load TLUT as block, do this first so tile 0 gets overwritten */
    _gsDPLoadTextureBlock(test30_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0,
                         0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),

   gsDPPipeSync(), 
    
    /* load IA4 texture, but use as 4b CI */
    gsDPLoadTextureBlock_4b(IA4tree2, G_IM_FMT_CI, 32, 64, 0,
                         G_TX_MIRROR, 0,
                         5, 0, G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&tree_vtx, 8, 0),
    gsSP1Triangle (4, 5, 6, 0),
    gsSP1Triangle (4, 6, 7, 0),
    gsSP1Triangle (0, 1, 2, 0),
    gsSP1Triangle (0, 2, 3, 0),

    gsSPTexture(32, 64, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

/*
 *  Tree 1,
 *
 *  Color Index, 4 bit, TLUT is 16-bit IA
 */
Gfx rdpatt_tree1_dl[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    /* gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2), */
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),

    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLUT(G_TT_IA16),

    /* load TLUT as block, do this first so tile 0 gets overwritten */
    _gsDPLoadTextureBlock(test30_tlutIA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0,
                         0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),


    gsDPPipeSync(),

    /* load IA4 texture, but use as 4b CI */
    gsDPLoadTextureBlock_4b(IA4tree2, G_IM_FMT_CI, 32, 64, 0,
                         G_TX_MIRROR, 0,
                         5, 0, G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&tree_vtx, 8, 0),
    gsSP1Triangle (0, 1, 2, 0),
    gsSP1Triangle (0, 2, 3, 0),
    gsSP1Triangle (4, 5, 6, 0),
    gsSP1Triangle (4, 6, 7, 0),

    gsSPTexture(32, 64, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

/*
 *  tree2, IA texture modulates between ENV, PRIM color
 */
Gfx rdpatt_tree2_dl[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(192, 255, 62, 255),
    gsDPSetPrimColor(150, 205, 0, 0, 128, 255),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsDPSetCombineMode (_G_CC_BLENDPEDECALA, _G_CC_BLENDPEDECALA),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    /* gsDPSetRenderMode(G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2), */

    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock_4b(IA4tree2, G_IM_FMT_IA, 32, 64, 0,
                         G_TX_MIRROR, 0,
                         5, 0, G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&tree_vtx, 8, 0),
    gsSP1Triangle (0, 1, 2, 0),
    gsSP1Triangle (0, 2, 3, 0),
    gsSP1Triangle (4, 5, 6, 0),
    gsSP1Triangle (4, 6, 7, 0),

    gsSPTexture(32, 64, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

/*
 *  tree1, IA texture modulates between SHADE, ENV
 */
Gfx rdpatt_tree3_dl[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(218, 165, 32, 255),
    gsDPSetPrimColor(150, 205, 0, 255, 154, 255),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_BLENDIDECALA, G_CC_BLENDIDECALA),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),

    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock_4b(IA4tree2, G_IM_FMT_IA, 32, 64, 0,
                         G_TX_MIRROR, 0,
                         5, 0, G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&tree_vtx, 8, 0),
    gsSP1Triangle (0, 1, 2, 0),
    gsSP1Triangle (0, 2, 3, 0),
    gsSP1Triangle (4, 5, 6, 0),
    gsSP1Triangle (4, 6, 7, 0),

    gsSPTexture(32, 64, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};


/*
 * Test 37, test texture edge mode
 *
 * Circle texture
 *
 * 
 *
 */

#include "IA4circle.h"

static Vtx texedge_vtx[] =  {
        {        -80,  40,   0, 0,  (0 << 6), (31 << 6), 0, 0, 0xff, 0xff},
        {          0,  40,   0, 0, (31 << 6), (31 << 6), 0xff, 0xff, 0xff, 0xff},
        {          0, -40,   0, 0, (31 << 6),  (0 << 6), 0, 0xff, 0, 0xff},
        {        -80, -40,   0, 0,  (0 << 6),  (0 << 6), 0xff, 0, 0, 0xff},
        {          0,  40,   0, 0,  (0 << 6), (31 << 6), 0, 0, 0xff, 0xff},
        {         80,  40,   0, 0, (31 << 6), (31 << 6), 0xff, 0xff, 0xff, 0xff},
        {         80, -40,   0, 0, (31 << 6),  (0 << 6), 0, 0xff, 0, 0xff},
        {          0, -40,   0, 0,  (0 << 6),  (0 << 6), 0xff, 0, 0, 0xff},
        {        -40, -25, -10, 0,  (0 << 6),  (0 << 6), 0, 0, 0, 0xff},
        {        -40,  25, -10, 0,  (0 << 6), (31 << 6), 0, 0, 0, 0xff},
        {          0, -25, -10, 0, (31 << 6),  (0 << 6), 0, 0, 0, 0xff},
        {          0,  25, -10, 0, (31 << 6), (31 << 6), 0xff, 0xff, 0xff, 0xff},
        {          0, -25, -10, 0, (31 << 6),  (0 << 6), 0xff, 0xff, 0xff, 0xff},
        {        -40,  25, -10, 0,  (0 << 6), (31 << 6), 0xff, 0xff, 0xff, 0xff},
};

Gfx rdpatt_texedge_dl[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),

    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_SHARPEN),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),


    gsDPLoadTextureBlock_4b(IA4circle, G_IM_FMT_IA, 32, 32, 0,
                         G_TX_WRAP, G_TX_WRAP,
                         5, 5, G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&(texedge_vtx[0]), 14, 0),

    /* put high contrast line behind opaque surface with xlu render
       mode to make sure doesn't leak through */
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSP1Triangle(8, 9, 10, 0),
    gsSP1Triangle(11, 12, 13, 0),

    /* draw circle in xlu mode, show fuzzy edge */
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetCombineMode (G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSP1Triangle(3, 0, 2, 0),
    gsSP1Triangle(1, 2, 0, 0),

    /* draw circle in tex_edge mode, show sharp edge */
    gsDPPipeSync(),
    gsDPSetCombineMode (G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSP1Triangle(7, 4, 6, 0),
    gsSP1Triangle(5, 6, 4, 0),

    gsSPEndDisplayList(),
};

/* end of case 37 */




/*
 * Test 38, test zbuffer range/accuracy
 *
 * Sets of two parallel planes at different Z's.  The back plane
 * is drawn first.  If the near plane cannot be distinguished in
 * depth from the first plane then back plane's color will be visible.
 * The blender mode is set to be *not antialiased* so that delta Z is
 * not a consideration.  There are 8 sets of planes, one for each depth
 * exponent.
 *
 * For the transform, a perspective matrix is used with a near plane
 * of 1 and a far plane of 4096.
 *
 */

static Vtx zbuf_q[] =  {
	/* depth range = 0 */ 
        {        -80, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {        -70, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {        -70, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -80, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -80, 1, -2048, 0, 0, 0, 0, 255, 0, 255},
        {        -70, 1, -2048, 0, 0, 0, 0, 255, 0, 255},
        {        -70, 1,  2047, 0, 0, 0, 0, 255, 0, 255},
        {        -80, 1,  2047, 0, 0, 0, 0, 255, 0, 255},
	/* depth range = 1 */ 
        {        -70, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {        -60, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {        -60, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -70, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -70, 2, -2048, 0, 0, 0, 0, 0, 255, 255},
        {        -60, 2, -2048, 0, 0, 0, 0, 0, 255, 255},
        {        -60, 2,  2047, 0, 0, 0, 0, 0, 255, 255},
        {        -70, 2,  2047, 0, 0, 0, 0, 0, 255, 255},
	/* depth range = 2 */ 
        {        -60, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {        -50, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {        -50, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -60, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -60, 3, -2048, 0, 0, 0, 0, 255, 0, 255},
        {        -50, 3, -2048, 0, 0, 0, 0, 255, 0, 255},
        {        -50, 3,  2047, 0, 0, 0, 0, 255, 0, 255},
        {        -60, 3,  2047, 0, 0, 0, 0, 255, 0, 255},
	/* depth range = 3 */ 
        {        -50, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {        -40, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {        -40, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -50, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -50, 4, -2048, 0, 0, 0, 0, 0, 255, 255},
        {        -40, 4, -2048, 0, 0, 0, 0, 0, 255, 255},
        {        -40, 4,  2047, 0, 0, 0, 0, 0, 255, 255},
        {        -50, 4,  2047, 0, 0, 0, 0, 0, 255, 255},
	/* depth range = 4 */ 
        {        -40, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {        -30, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {        -30, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -40, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -40, 5, -2048, 0, 0, 0, 0, 255, 0, 255},
        {        -30, 5, -2048, 0, 0, 0, 0, 255, 0, 255},
        {        -30, 5,  2047, 0, 0, 0, 0, 255, 0, 255},
        {        -40, 5,  2047, 0, 0, 0, 0, 255, 0, 255},
	/* depth range = 5 */ 
        {        -30, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {        -20, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {        -20, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -30, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -30, 6, -2048, 0, 0, 0, 0, 0, 255, 255},
        {        -20, 6, -2048, 0, 0, 0, 0, 0, 255, 255},
        {        -20, 6,  2047, 0, 0, 0, 0, 0, 255, 255},
        {        -30, 6,  2047, 0, 0, 0, 0, 0, 255, 255},
	/* depth range = 6 */ 
        {        -20, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {        -10, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {        -10, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -20, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -20, 7, -2048, 0, 0, 0, 0, 255, 0, 255},
        {        -10, 7, -2048, 0, 0, 0, 0, 255, 0, 255},
        {        -10, 7,  2047, 0, 0, 0, 0, 255, 0, 255},
        {        -20, 7,  2047, 0, 0, 0, 0, 255, 0, 255},
	/* depth range = 7 */ 
        {        -10, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {          0, 0, -2048, 0, 0, 0, 255, 0, 255, 255},
        {          0, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -10, 0,  2047, 0, 0, 0, 255, 0, 255, 255},
        {        -10, 8, -2048, 0, 0, 0, 0, 0, 255, 255},
        {          0, 8, -2048, 0, 0, 0, 0, 0, 255, 255},
        {          0, 8,  2047, 0, 0, 0, 0, 0, 255, 255},
        {        -10, 8,  2047, 0, 0, 0, 0, 0, 255, 255},
};

Gfx rdpatt_zbuf_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2),

    gsSPVertex(&zbuf_q[0], 16, 0),
    gsSP1Triangle(0, 3, 1, 0), 		/* back 0 */
    gsSP1Triangle(1, 3, 2, 0),
    gsSP1Triangle(4, 7, 5, 0), 		/* front 0 */
    gsSP1Triangle(5, 7, 6, 0),
    gsSP1Triangle(8, 11, 9, 0), 	/* back 1 */
    gsSP1Triangle(9, 11, 10, 0),
    gsSP1Triangle(12, 15, 13, 0), 	/* front 1 */
    gsSP1Triangle(13, 15, 14, 0),

#ifdef TOO_MUCH

    gsSPVertex(&zbuf_q[16], 16, 0),
    gsSP1Triangle(0, 3, 1, 0), 		/* back 2 */
    gsSP1Triangle(1, 3, 2, 0),
    gsSP1Triangle(4, 7, 5, 0), 		/* front 2 */
    gsSP1Triangle(5, 7, 6, 0),
    gsSP1Triangle(8, 11, 9, 0), 	/* back 3 */
    gsSP1Triangle(9, 11, 10, 0),
    gsSP1Triangle(12, 15, 13, 0), 	/* front 3 */
    gsSP1Triangle(13, 15, 14, 0),

    gsSPVertex(&zbuf_q[32], 16, 0),
    gsSP1Triangle(0, 3, 1, 0), 		/* back 4 */
    gsSP1Triangle(1, 3, 2, 0),
    gsSP1Triangle(4, 7, 5, 0), 		/* front 4 */
    gsSP1Triangle(5, 7, 6, 0),
    gsSP1Triangle(8, 11, 9, 0), 	/* back 5 */
    gsSP1Triangle(9, 11, 10, 0),
    gsSP1Triangle(12, 15, 13, 0), 	/* front 5 */
    gsSP1Triangle(13, 15, 14, 0),

    gsSPVertex(&zbuf_q[48], 16, 0),
    gsSP1Triangle(0, 3, 1, 0), 		/* back 6 */
    gsSP1Triangle(1, 3, 2, 0),
    gsSP1Triangle(4, 7, 5, 0), 		/* front 6 */
    gsSP1Triangle(5, 7, 6, 0),
    gsSP1Triangle(8, 11, 9, 0), 	/* back 7 */
    gsSP1Triangle(9, 11, 10, 0),
    gsSP1Triangle(12, 15, 13, 0), 	/* front 7 */
    gsSP1Triangle(13, 15, 14, 0),
#endif
    gsSPEndDisplayList(),
};

/* end of case 38 */

/*
 *  Test 65 Fractal terrain
 */

#include "frac_vtx.h"
#include "I4luna.h"
#include "I4granite3.h"

static Vtx contour[] =  {
        {          0, 250,   0, 0, 0, 0, 255, 0, 255, 255},
        {        300, 250,   0, 0, 0, 0, 255, 0, 255, 255},
        {        300, 250, 300, 0, 0, 0, 255, 0, 255, 255},
        {          0, 250, 300, 0, 0, 0, 255, 0, 255, 255}
};


Gfx rdpatt_frac_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),

    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),


#include "frac_tri.h"

    gsSPTexture(16, 2, 0, G_TX_RENDERTILE, G_OFF),
#ifdef JUNK
    /* gsDPSetRenderMode(G_RM_ZB_OPA_DECAL, G_RM_ZB_OPA_DECAL2), */
    gsDPSetRenderMode(G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&contour[0], 4, 0),
    gsSP1Triangle(0, 3, 1, 0),
    gsSP1Triangle(1, 3, 2, 0),
#endif
    gsSPEndDisplayList(),
};


/*
 *  Case 66 spinning torus
 */
#include "spin_torus_vtx.h"

Gfx rdpatt_spin_torus_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
#include "spin_torus_tri.h"
    gsSPEndDisplayList(),
};

/*
 *  Case 67 spinning "U-64"
 */
#include "u64_vtx.h"

Gfx rdpatt_u64_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
#include "u64_tri.h"
    gsSPEndDisplayList(),
};


/*
 * ADD TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx display list must be extern'd in rdpatt.h, then
 * added to the 'testList' table in rdpatt.c
 *
 */
