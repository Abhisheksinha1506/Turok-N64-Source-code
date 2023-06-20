
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
 * Creator:	hsa@sgi.com
 * Create Date:	Fri Oct 14 11:53:47 PDT 1994
 *
 *
 * This file holds tiny display list segments that are 'static' data.
 * If you feel the urge to modify a test, see the comment at
 * the top of main.c for details.
 *
 */

#include <ultratypes.h>
#include <mbi.h>
#include "dldriver.h"
#include "rdpms.h"

/*
 * Test conventions:
 *
 * Data variable names can be about anything, as long as they are unique
 * and consistent in the table entry.
 *
 * In order to get around compiler weirdness, the table of tests
 * is in rdpverif.c, and the Gfx rdpms_lists must be extern'd in rdpverif.h
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
/*     x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */	
    { -40,  40,    0,    0,	0,	0,	0xff,     0,     0,	0xff },	  /* R */   
    {  40,  40,    0,    0,	0,	0,	   0,  0xff,     0,	0xff },	  /* G */   
    {  40, -40,    0,    0,	0,	0,	   0,     0,  0xff,	0xff },	  /* B */   
    { -40, -40,    0,    0,	0,	0,	0xff,  0xff,     0,	0xff },	  /* Y */   
    {   0,   0,    0,    0,	0,	0,	0xff,  0xff,  0xff,	0xff },	  /* W */   
};

Gfx rdpms_placebo_dl[MAX_STATIC_GFX_SIZE] = {
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
 */
 
Gfx rdpms_simplefill[MAX_STATIC_GFX_SIZE] = {
    { gsDPPipeSync() }, 
    { gsDPSetCycleType(G_CYC_FILL) }, 
    { gsDPSetFillColor(GPACK_RGBA5551(255,0,0,1) << 16 | GPACK_RGBA5551(255,0,0,1)) }, 
    { gsDPFillRectangle(100, 100, 150, 105) }, 
    { gsDPPipeSync() }, 
    { gsDPSetCycleType(G_CYC_1CYCLE) }, 
    { gsSPEndDisplayList() }
};
/* end of case 0 */

/* Test 1, Frame 1: Simple Left major tri */
static Vtx firsttri_vtx[5] =  {
/*     x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */	
    { 160, 200,    0,    0,	0,	0,     0xff,     0,     0,	0xff },	  /* R */   
    { 130, 130,    0,    0,	0,	0,	  0,  0xff,     0,	0xff },	  /* G */   
    { 180, 160,    0,    0,	0,	0,	  0,     0,  0xff,	0xff },	  /* B */   
    { 110, 160,    0,    0,	0,	0,	  0,     0,  0xff,	0xff },	  /* B */   
};

 
Gfx rdpms_firsttri[MAX_STATIC_GFX_SIZE] = {
    { gsDPPipeSync() }, 
    { gsSPClearGeometryMode(G_ZBUFFER) },
    { gsSPClearGeometryMode(G_CULL_BOTH) },
    { gsSPSetGeometryMode(G_SHADE) },
    { gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE) },
    { gsDPSetCycleType(G_CYC_1CYCLE) }, 
    { gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2) },
    { gsSPVertex(&firsttri_vtx, 4, 0) },
    { gsSP1Triangle(0, 1, 2, 0) },
    { gsSPEndDisplayList() }
};

/* Test 2, Frame 2: */
Gfx rdpms_righttri[MAX_STATIC_GFX_SIZE] = {
    { gsDPPipeSync() }, 
    { gsSPClearGeometryMode(G_ZBUFFER) },
    { gsSPClearGeometryMode(G_CULL_BOTH) },
    { gsSPSetGeometryMode(G_SHADE) },
    { gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE) },
    { gsDPSetCycleType(G_CYC_1CYCLE) }, 
    { gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2) },
    { gsSPVertex(&firsttri_vtx, 4, 0) },
    { gsSP1Triangle(0, 1, 3, 0) },
    { gsSPEndDisplayList() }
};

/* Test 3, Frame 3: Zbuffered triangles */
#define Z1	-200	/* Far away */
#define Z2	-180	/* Closer */
#define YA	 24
#define YB	 18
#define YC	 5

static Vtx tris[] = {
/*    x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */
	
    { -40,  YA,     Z1, 0,	0,	0,	0xff,	0,	0,	0xff },	  /* R */   
    {  30,   0,	    Z2, 0,	0,	0,	0,	0,	0xff,	0xff },	  /* B */	     
    { -40, -YA,     Z1, 0,	0,	0,	0,	0xff,	0,	0xff },	  /* G */
    	     
    {  35,  YB,     Z1, 0,	0,	0,	0,	0,	0xff,	0xff },	  /* B */	     
    {  35, -YB,     Z1, 0,	0,	0,	0,	0xff,	0,	0xff },	  /* G */	     
    { -20,   0,	    Z2, 0,	0,	0,	0xff,	0,	0,	0xff },	  /* R */	     
};

Gfx rdpms_ztriangles[MAX_STATIC_GFX_SIZE] = {
    { gsSPClearGeometryMode(0xffffffff) }, 
    { gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER) }, 
    { gsDPSetRenderMode(G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2) },
    { gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE) },
    { gsSPVertex(&tris, sizeof(tris)/sizeof(tris[0]), 0) },
    { gsSP1Triangle(0, 1, 2, 0) }, 
    { gsSP1Triangle(3, 4, 5, 0) },
    { gsSPEndDisplayList() }
};

/*
 * Test 4, Frame 4: Simple 2 cycle test
 *
 */
Gfx rdpms_fogtriangles[MAX_STATIC_GFX_SIZE] = {
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


static Vtx tri2[] = {
/*    x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */
	
    { -40,  YA,     Z1, 0,	0,	0,	0xff,	0,	0,	0xff },	  /* R */   
    {  30,   0,	    Z2, 0,	0,	0,	0,	0,	0xff,	0xff },	  /* B */	     
    { -40, -YA,     Z1, 0,	0,	0,	0,	0xff,	0,	0xff },	  /* G */
    	     
    {  35,  YC,     Z1, 0,	0,	0,	0,	0,	0xff,	0xcc },	  /* B */	     
    {  35, YC-20,   Z1, 0,	0,	0,	0,	0xff,	0,	0xcc },	  /* G */	     
    { -20, YC-10,   Z2, 0,	0,	0,	0xff,	0,	0,	0xcc },	  /* R */	     

    { -25, YA-10,   Z2, 0,	0,	0,	0xff,	0xff,	0xff,	0xcc },	
    { -20, YA-15,   Z2, 0,	0,	0,	0xff,	0xff,	0xff,	0xcc },	
    { -35, YA-18,   Z2, 0,	0,	0,	0xff,	0xff,	0xff,	0xcc },	
};

/* Test 5, Frame 5: Z buffered xlu triangles after opaque tri */
Gfx rdpms_bltriangles[MAX_STATIC_GFX_SIZE] = {
    { gsSPClearGeometryMode(0xffffffff) }, 
    { gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER) }, 
    { gsDPSetRenderMode(G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2) },
    { gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE) },
    { gsSPVertex(&tri2, sizeof(tri2)/sizeof(tri2[0]), 0) },
    { gsSP1Triangle(0, 1, 2, 0) }, 
    { gsDPPipeSync() }, 
    { gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2) },
    { gsSP1Triangle(3, 4, 5, 0) },
    { gsSP1Triangle(6, 7, 8, 0) },
    { gsSPEndDisplayList() }
};

/* Test 6, Frame 6: Zbuffered triangles from test 3 but AA not pt sampled */
Gfx rdpms_aaztriangles[MAX_STATIC_GFX_SIZE] = {
    { gsSPClearGeometryMode(0xffffffff) }, 
    { gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER) }, 
    { gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2) },
    { gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE) },
    { gsSPVertex(&tris, sizeof(tris)/sizeof(tris[0]), 0) },
    { gsSP1Triangle(0, 1, 2, 0) }, 
    { gsSP1Triangle(3, 4, 5, 0) },
    { gsSPEndDisplayList() }
};

static Vtx tri3[] = {
/*    x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */
  { 147,  100,	    Z1,    0,   0,      0,    0xff,	0xff,	0xff,	0x80 },	    
  { 170,  110,	    Z1,    0,   0,      0,    0xff,	0xff,	0xff,	0x80 },	    
  { 147,  115,	    Z1,    0,   0,      0,    0xff,	0xff,	0xff,	0x80 },	    
};

/* Test 7, Frame 7: blend */
Gfx rdpms_bltri[MAX_STATIC_GFX_SIZE] = {
    { gsDPPipeSync() }, 
    { gsDPSetCycleType(G_CYC_FILL) }, 
    { gsDPSetFillColor(GPACK_RGBA5551(255,0,0,1) << 16 | GPACK_RGBA5551(255,0,0,1)) }, 
    { gsDPFillRectangle(120-3, 120-3, 159-3, 180-3) }, 
    { gsDPPipeSync() },
    { gsDPSetFillColor(GPACK_RGBA5551(0,0,255,1) << 16 | GPACK_RGBA5551(0,0,255,1)) }, 
    { gsDPFillRectangle(160-3, 120-3, 200-3, 180-3) }, 
    { gsDPPipeSync() },
    { gsDPSetCycleType(G_CYC_1CYCLE) }, 
    { gsSPClearGeometryMode(0xffffffff) }, 
    { gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER) }, 
    { gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2) },
    { gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE) },
    { gsSPVertex(&tri3, sizeof(tri3)/sizeof(tri3[0]), 0) },
    { gsSP1Triangle(0, 1, 2, 0) }, 
    { gsSPEndDisplayList() }
};


/* Test 8, Frame 8: blend w/ z */


/*
 * Test 10, Frame 10:
 * 4 fillrects with different colors and different horizontal lengths
 *
 */
Gfx rdpms_filldl[4*MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),


    /* set attributes, to be used as colors for rects */

    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),


        /* test fill mode */
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetFillColor(0xF801F801),
    gsDPFillRectangle(10, 10, 50, 15),
    gsDPPipeSync(),
    gsDPSetFillColor(0x07FF07FF),
    gsDPFillRectangle(10, 20, 310, 25),
    gsDPPipeSync(),
    gsDPSetFillColor(0xFFFFFFFF),
    gsDPFillRectangle(10, 30, 11, 35),
    gsDPPipeSync(),
    gsDPSetFillColor(0x55555555),
    gsDPFillRectangle(10, 40, 50, 45),
    gsDPPipeSync(),


    gsSPEndDisplayList(),
};
/* end of case 10 */

/*
 * Test 11, Frame 11:
 * a 16 bit texture load followed by a textured rectangle in copy mode
 *
 */
#include "RGBA16dana.h"

Gfx rdpms_copyloaddl[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),


    /* set attributes, to be used as colors for rects */

    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),


    gsDPSetCycleType(G_CYC_COPY),

    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPLoadTextureBlock(rdpms_RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),

    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle(162<<2, 50<<2, 193<<2, 81<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),

    gsSPEndDisplayList(),
};
/* end of case 11 */

/*
 * Test 12, Frame 12:
 * an 8 bit texture load followed by a textured rectangle in copy mode (8 bit)
 * By the way, this doesn't work.
 *
 */
#if 0
#include "RGBA8dana.h"
#endif /* 0 */
Gfx rdpms_copyload8b[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),

#if 0
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_8b, 320, cfb_16_a),


    /* set attributes, to be used as colors for rects */

    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),


    gsDPSetCycleType(G_CYC_COPY),

    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPLoadTextureBlock(RGBA8dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),

    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle(162<<2, 50<<2, 193<<2, 81<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),



        /* test fill mode */
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetFillColor(0xc0c0c0c0),
    gsDPFillRectangle(10, 10, 50, 15),
    gsDPPipeSync(),
    gsDPSetFillColor(0x3c3c3c3c),
    gsDPFillRectangle(10, 20, 310, 25),
    gsDPPipeSync(),
    gsDPSetFillColor(0x03030303),
    gsDPFillRectangle(10, 30, 11, 35),
    gsDPPipeSync(),
    gsDPSetFillColor(0xffffffff),
    gsDPFillRectangle(10, 40, 50, 45),
    gsDPPipeSync(),

#endif /* 0 */

    gsSPEndDisplayList(),
};
/* end of case 12 */

/*
 * Test 13, Frame 13:
 * more coprehensive fill, 1cycle and 2cycle tests
 *
 */
Gfx rdpms_filldl2[4*MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),


    /* set attributes, to be used as colors for rects */

    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),

    gsDPSetCycleType(G_CYC_FILL),

        /* test 2 pixel spans (red) */
    gsDPSetFillColor(0xF801F801),
    gsDPFillRectangle(10, 10, 11, 10),
    gsDPFillRectangle(11, 12, 12, 12),
    gsDPFillRectangle(12, 14, 13, 14),
    gsDPFillRectangle(13, 16, 14, 16),
    gsDPFillRectangle(14, 18, 15, 18),
    gsDPFillRectangle(15, 20, 16, 20),
    gsDPFillRectangle(16, 22, 17, 22),
    gsDPFillRectangle(17, 24, 18, 24),
    gsDPFillRectangle(18, 26, 19, 26),
    gsDPFillRectangle(19, 28, 20, 28),
    gsDPFillRectangle(20, 30, 21, 30),
    gsDPFillRectangle(21, 32, 22, 32),
    gsDPFillRectangle(22, 34, 23, 34),
    gsDPFillRectangle(23, 36, 24, 36),
    gsDPFillRectangle(24, 38, 25, 38),
    gsDPFillRectangle(25, 40, 26, 40),
    gsDPFillRectangle(26, 42, 27, 42),
    gsDPFillRectangle(27, 44, 28, 44),
    gsDPFillRectangle(28, 46, 29, 46),
    gsDPFillRectangle(29, 48, 30, 48),
    gsDPFillRectangle(30, 10, 31, 10),
    gsDPFillRectangle(31, 12, 32, 12),
    gsDPFillRectangle(32, 14, 33, 14),
    gsDPFillRectangle(33, 16, 34, 16),
    gsDPFillRectangle(34, 18, 35, 18),
    gsDPFillRectangle(35, 20, 36, 20),
    gsDPFillRectangle(36, 22, 37, 22),
    gsDPFillRectangle(37, 24, 38, 24),
    gsDPFillRectangle(38, 26, 39, 26),
    gsDPFillRectangle(39, 28, 40, 28),
    gsDPFillRectangle(40, 30, 41, 30),
    gsDPFillRectangle(41, 32, 42, 32),
    gsDPFillRectangle(42, 34, 43, 34),
    gsDPFillRectangle(43, 36, 44, 36),
    gsDPFillRectangle(44, 38, 45, 38),
    gsDPFillRectangle(45, 40, 46, 40),
    gsDPFillRectangle(46, 42, 47, 42),
    gsDPFillRectangle(47, 44, 48, 44),
    gsDPFillRectangle(48, 46, 49, 46),
    gsDPFillRectangle(49, 48, 50, 48),
    gsDPFillRectangle(50, 10, 51, 10),
    gsDPFillRectangle(51, 12, 52, 12),
    gsDPFillRectangle(52, 14, 53, 14),
    gsDPFillRectangle(53, 16, 54, 16),
    gsDPFillRectangle(54, 18, 55, 18),
    gsDPFillRectangle(55, 20, 56, 20),
    gsDPFillRectangle(56, 22, 57, 22),
    gsDPFillRectangle(57, 24, 58, 24),
    gsDPFillRectangle(58, 26, 59, 26),
    gsDPFillRectangle(59, 28, 60, 28),
    gsDPFillRectangle(60, 30, 61, 30),
    gsDPFillRectangle(61, 32, 62, 32),
    gsDPFillRectangle(62, 34, 63, 34),
    gsDPFillRectangle(63, 36, 64, 36),
    gsDPFillRectangle(64, 38, 65, 38),
    gsDPFillRectangle(65, 40, 66, 40),
    gsDPFillRectangle(66, 42, 67, 42),
    gsDPFillRectangle(67, 44, 68, 44),
    gsDPFillRectangle(68, 46, 69, 46),
    gsDPFillRectangle(69, 48, 70, 48),
    gsDPPipeSync(),

	/* longer spans (cyan) */
    gsDPSetFillColor(0x07FF07FF),
    gsDPFillRectangle(10, 50, 50, 50),
    gsDPFillRectangle(11, 52, 51, 52),
    gsDPFillRectangle(12, 54, 52, 54),
    gsDPFillRectangle(13, 56, 53, 56),
    gsDPFillRectangle(14, 58, 54, 58),
    gsDPFillRectangle(15, 60, 55, 60),
    gsDPFillRectangle(16, 62, 56, 62),
    gsDPFillRectangle(17, 64, 57, 64),
    gsDPFillRectangle(18, 66, 58, 66),
    gsDPFillRectangle(19, 68, 59, 68),
    gsDPFillRectangle(20, 70, 60, 70),
    gsDPFillRectangle(21, 72, 61, 72),
    gsDPFillRectangle(22, 74, 62, 74),
    gsDPFillRectangle(23, 76, 63, 76),
    gsDPFillRectangle(24, 78, 64, 78),
    gsDPFillRectangle(25, 80, 65, 80),
    gsDPFillRectangle(26, 82, 66, 82),
    gsDPFillRectangle(27, 84, 67, 84),
    gsDPFillRectangle(28, 86, 68, 86),
    gsDPFillRectangle(29, 88, 69, 88),
    gsDPFillRectangle(30, 90, 70, 90),
    gsDPFillRectangle(31, 92, 71, 92),
    gsDPFillRectangle(32, 94, 72, 94),
    gsDPFillRectangle(33, 96, 73, 96),
    gsDPFillRectangle(34, 98, 74, 98),
    gsDPFillRectangle(35,100, 75,100),
    gsDPFillRectangle(36,102, 76,102),
    gsDPFillRectangle(37,104, 77,104),
    gsDPFillRectangle(38,106, 78,106),
    gsDPFillRectangle(39,108, 79,108),
    gsDPFillRectangle(40,110, 80,110),
    gsDPFillRectangle(41,112, 81,112),
    gsDPFillRectangle(42,114, 82,114),
    gsDPFillRectangle(43,116, 83,116),
    gsDPFillRectangle(44,118, 84,118),
    gsDPFillRectangle(45,120, 85,120),
    gsDPFillRectangle(46,122, 86,122),
    gsDPFillRectangle(47,124, 87,124),
    gsDPFillRectangle(48,126, 88,126),
    gsDPFillRectangle(49,128, 89,128),
    gsDPPipeSync(),

	/* one pixel spans (white) */
    gsDPSetFillColor(0xFFFFFFFF),
    gsDPFillRectangle(10, 130, 10, 130),
    gsDPFillRectangle(11, 132, 11, 132),
    gsDPFillRectangle(12, 134, 12, 134),
    gsDPFillRectangle(13, 136, 13, 136),
    gsDPFillRectangle(14, 138, 14, 138),
    gsDPFillRectangle(15, 140, 15, 140),
    gsDPFillRectangle(16, 142, 16, 142),
    gsDPFillRectangle(17, 144, 17, 144),
    gsDPFillRectangle(18, 146, 18, 146),
    gsDPFillRectangle(19, 148, 19, 148),
    gsDPFillRectangle(20, 150, 20, 150),
    gsDPFillRectangle(21, 152, 21, 152),
    gsDPFillRectangle(22, 154, 22, 154),
    gsDPFillRectangle(23, 156, 23, 156),
    gsDPFillRectangle(24, 158, 24, 158),
    gsDPFillRectangle(25, 160, 25, 160),
    gsDPFillRectangle(26, 162, 26, 162),
    gsDPFillRectangle(27, 164, 27, 164),
    gsDPFillRectangle(28, 166, 28, 166),
    gsDPFillRectangle(29, 168, 29, 168),
    gsDPFillRectangle(30, 130, 30, 130),
    gsDPFillRectangle(31, 132, 31, 132),
    gsDPFillRectangle(32, 134, 32, 134),
    gsDPFillRectangle(33, 136, 33, 136),
    gsDPFillRectangle(34, 138, 34, 138),
    gsDPFillRectangle(35, 140, 35, 140),
    gsDPFillRectangle(36, 142, 36, 142),
    gsDPFillRectangle(37, 144, 37, 144),
    gsDPFillRectangle(38, 146, 38, 146),
    gsDPFillRectangle(39, 148, 39, 148),
    gsDPFillRectangle(40, 150, 40, 150),
    gsDPFillRectangle(41, 152, 41, 152),
    gsDPFillRectangle(42, 154, 42, 154),
    gsDPFillRectangle(43, 156, 43, 156),
    gsDPFillRectangle(44, 158, 44, 158),
    gsDPFillRectangle(45, 160, 45, 160),
    gsDPFillRectangle(46, 162, 46, 162),
    gsDPFillRectangle(47, 164, 47, 164),
    gsDPFillRectangle(48, 166, 48, 166),
    gsDPFillRectangle(49, 168, 49, 168),
    gsDPFillRectangle(50, 130, 50, 130),
    gsDPFillRectangle(51, 132, 51, 132),
    gsDPFillRectangle(52, 134, 52, 134),
    gsDPFillRectangle(53, 136, 53, 136),
    gsDPFillRectangle(54, 138, 54, 138),
    gsDPFillRectangle(55, 140, 55, 140),
    gsDPFillRectangle(56, 142, 56, 142),
    gsDPFillRectangle(57, 144, 57, 144),
    gsDPFillRectangle(58, 146, 58, 146),
    gsDPFillRectangle(59, 148, 59, 148),
    gsDPFillRectangle(60, 150, 60, 150),
    gsDPFillRectangle(61, 152, 61, 152),
    gsDPFillRectangle(62, 154, 62, 154),
    gsDPFillRectangle(63, 156, 63, 156),
    gsDPFillRectangle(64, 158, 64, 158),
    gsDPFillRectangle(65, 160, 65, 160),
    gsDPFillRectangle(66, 162, 66, 162),
    gsDPFillRectangle(67, 164, 67, 164),
    gsDPFillRectangle(68, 166, 68, 166),
    gsDPFillRectangle(69, 168, 69, 168),
    gsDPPipeSync(),

    /* ONE CYCLE MODE */

    gsDPSetCycleType(G_CYC_1CYCLE),

        /* test 2 pixel spans (red) */
    gsDPSetPrimColor(150, 205, 255, 0, 0, 228),
    gsDPFillRectangle(80, 10, 81, 11),
    gsDPFillRectangle(81, 12, 82, 13),
    gsDPFillRectangle(82, 14, 83, 15),
    gsDPFillRectangle(83, 16, 84, 17),
    gsDPFillRectangle(84, 18, 85, 19),
    gsDPFillRectangle(85, 20, 86, 21),
    gsDPFillRectangle(86, 22, 87, 23),
    gsDPFillRectangle(87, 24, 88, 25),
    gsDPFillRectangle(88, 26, 89, 27),
    gsDPFillRectangle(89, 28, 90, 29),
    gsDPFillRectangle(90, 30, 91, 31),
    gsDPFillRectangle(91, 32, 92, 33),
    gsDPFillRectangle(92, 34, 93, 35),
    gsDPFillRectangle(93, 36, 94, 37),
    gsDPFillRectangle(94, 38, 95, 39),
    gsDPFillRectangle(95, 40, 96, 41),
    gsDPFillRectangle(96, 42, 97, 43),
    gsDPFillRectangle(97, 44, 98, 45),
    gsDPFillRectangle(98, 46, 99, 47),
    gsDPFillRectangle(99, 48,100, 49),
    gsDPFillRectangle(100, 10,101, 11),
    gsDPFillRectangle(101, 12,102, 13),
    gsDPFillRectangle(102, 14,103, 15),
    gsDPFillRectangle(103, 16,104, 17),
    gsDPFillRectangle(104, 18,105, 19),
    gsDPFillRectangle(105, 20,106, 21),
    gsDPFillRectangle(106, 22,107, 23),
    gsDPFillRectangle(107, 24,108, 25),
    gsDPFillRectangle(108, 26,109, 27),
    gsDPFillRectangle(109, 28,110, 29),
    gsDPFillRectangle(110, 30,111, 31),
    gsDPFillRectangle(111, 32,112, 33),
    gsDPFillRectangle(112, 34,113, 35),
    gsDPFillRectangle(113, 36,114, 37),
    gsDPFillRectangle(114, 38,115, 39),
    gsDPFillRectangle(115, 40,116, 41),
    gsDPFillRectangle(116, 42,117, 43),
    gsDPFillRectangle(117, 44,118, 45),
    gsDPFillRectangle(118, 46,119, 47),
    gsDPFillRectangle(119, 48,120, 49),
    gsDPFillRectangle(120, 10,121, 11),
    gsDPFillRectangle(121, 12,122, 13),
    gsDPFillRectangle(122, 14,123, 15),
    gsDPFillRectangle(123, 16,124, 17),
    gsDPFillRectangle(124, 18,125, 19),
    gsDPFillRectangle(125, 20,126, 21),
    gsDPFillRectangle(126, 22,127, 23),
    gsDPFillRectangle(127, 24,128, 25),
    gsDPFillRectangle(128, 26,129, 27),
    gsDPFillRectangle(129, 28,130, 29),
    gsDPFillRectangle(130, 30,131, 31),
    gsDPFillRectangle(131, 32,132, 33),
    gsDPFillRectangle(132, 34,133, 35),
    gsDPFillRectangle(133, 36,134, 37),
    gsDPFillRectangle(134, 38,135, 39),
    gsDPFillRectangle(135, 40,136, 41),
    gsDPFillRectangle(136, 42,137, 43),
    gsDPFillRectangle(137, 44,138, 45),
    gsDPFillRectangle(138, 46,139, 47),
    gsDPFillRectangle(139, 48,140, 49),
    gsDPPipeSync(),

	/* longer spans (cyan) */
    gsDPSetPrimColor(150, 205, 0, 255, 255, 228),
    gsDPFillRectangle(80, 50,120, 51),
    gsDPFillRectangle(81, 52,121, 53),
    gsDPFillRectangle(82, 54,122, 55),
    gsDPFillRectangle(83, 56,123, 57),
    gsDPFillRectangle(84, 58,124, 59),
    gsDPFillRectangle(85, 60,125, 61),
    gsDPFillRectangle(86, 62,126, 63),
    gsDPFillRectangle(87, 64,127, 65),
    gsDPFillRectangle(88, 66,128, 67),
    gsDPFillRectangle(89, 68,129, 69),
    gsDPFillRectangle(90, 70,130, 71),
    gsDPFillRectangle(91, 72,131, 73),
    gsDPFillRectangle(92, 74,132, 75),
    gsDPFillRectangle(93, 76,133, 77),
    gsDPFillRectangle(94, 78,134, 79),
    gsDPFillRectangle(95, 80,135, 81),
    gsDPFillRectangle(96, 82,136, 83),
    gsDPFillRectangle(97, 84,137, 85),
    gsDPFillRectangle(98, 86,138, 87),
    gsDPFillRectangle(99, 88,139, 89),
    gsDPFillRectangle(100, 90,140, 91),
    gsDPFillRectangle(101, 92,141, 93),
    gsDPFillRectangle(102, 94,142, 95),
    gsDPFillRectangle(103, 96,143, 97),
    gsDPFillRectangle(104, 98,144, 99),
    gsDPFillRectangle(105,100,145,101),
    gsDPFillRectangle(106,102,146,103),
    gsDPFillRectangle(107,104,147,105),
    gsDPFillRectangle(108,106,148,107),
    gsDPFillRectangle(109,108,149,109),
    gsDPFillRectangle(110,110,150,111),
    gsDPFillRectangle(111,112,151,113),
    gsDPFillRectangle(112,114,152,115),
    gsDPFillRectangle(113,116,153,117),
    gsDPFillRectangle(114,118,154,119),
    gsDPFillRectangle(115,120,155,121),
    gsDPFillRectangle(116,122,156,123),
    gsDPFillRectangle(117,124,157,125),
    gsDPFillRectangle(118,126,158,127),
    gsDPFillRectangle(119,128,159,129),
    gsDPPipeSync(),

	/* one pixel spans (white) */
    gsDPSetPrimColor(150, 205, 255, 255, 255, 228),
    gsDPFillRectangle(80, 130, 82, 131),
    gsDPFillRectangle(81, 132, 83, 133),
    gsDPFillRectangle(82, 134, 84, 135),
    gsDPFillRectangle(83, 136, 85, 137),
    gsDPFillRectangle(84, 138, 86, 139),
    gsDPFillRectangle(85, 140, 87, 141),
    gsDPFillRectangle(86, 142, 88, 143),
    gsDPFillRectangle(87, 144, 89, 145),
    gsDPFillRectangle(88, 146, 90, 147),
    gsDPFillRectangle(89, 148, 91, 149),
    gsDPFillRectangle(90, 150, 92, 151),
    gsDPFillRectangle(91, 152, 93, 153),
    gsDPFillRectangle(92, 154, 94, 155),
    gsDPFillRectangle(93, 156, 95, 157),
    gsDPFillRectangle(94, 158, 96, 159),
    gsDPFillRectangle(95, 160, 97, 161),
    gsDPFillRectangle(96, 162, 98, 163),
    gsDPFillRectangle(97, 164, 99, 165),
    gsDPFillRectangle(98, 166, 100, 167),
    gsDPFillRectangle(99, 168, 101, 169),
    gsDPFillRectangle(100, 130,102, 131),
    gsDPFillRectangle(101, 132,103, 133),
    gsDPFillRectangle(102, 134,104, 135),
    gsDPFillRectangle(103, 136,105, 137),
    gsDPFillRectangle(104, 138,106, 139),
    gsDPFillRectangle(105, 140,107, 141),
    gsDPFillRectangle(106, 142,108, 143),
    gsDPFillRectangle(107, 144,109, 145),
    gsDPFillRectangle(108, 146,110, 147),
    gsDPFillRectangle(109, 148,111, 149),
    gsDPFillRectangle(110, 150,112, 151),
    gsDPFillRectangle(111, 152,113, 153),
    gsDPFillRectangle(112, 154,114, 155),
    gsDPFillRectangle(113, 156,115, 157),
    gsDPFillRectangle(114, 158,116, 159),
    gsDPFillRectangle(115, 160,117, 161),
    gsDPFillRectangle(116, 162,118, 163),
    gsDPFillRectangle(117, 164,119, 165),
    gsDPFillRectangle(118, 166,120, 167),
    gsDPFillRectangle(119, 168,121, 169),
    gsDPFillRectangle(120, 130,122, 131),
    gsDPFillRectangle(121, 132,123, 133),
    gsDPFillRectangle(122, 134,124, 135),
    gsDPFillRectangle(123, 136,125, 137),
    gsDPFillRectangle(124, 138,126, 139),
    gsDPFillRectangle(125, 140,127, 141),
    gsDPFillRectangle(126, 142,128, 143),
    gsDPFillRectangle(127, 144,129, 145),
    gsDPFillRectangle(128, 146,130, 147),
    gsDPFillRectangle(129, 148,131, 149),
    gsDPFillRectangle(130, 150,132, 151),
    gsDPFillRectangle(131, 152,133, 153),
    gsDPFillRectangle(132, 154,134, 155),
    gsDPFillRectangle(133, 156,135, 157),
    gsDPFillRectangle(134, 158,136, 159),
    gsDPFillRectangle(135, 160,137, 161),
    gsDPFillRectangle(136, 162,138, 163),
    gsDPFillRectangle(137, 164,139, 165),
    gsDPFillRectangle(138, 166,140, 167),
    gsDPFillRectangle(139, 168,141, 169),
    gsDPPipeSync(),


	/* Scissoring (unscissored in red, */
	/* x-scissored in blue, y-scissored in green */
    gsDPSetPrimColor(150, 205, 255, 0, 0, 228),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 319, 239),
    gsDPFillRectangle(80, 169, 160, 170),
    gsDPPipeSync(),
    gsDPSetPrimColor(150, 205, 0, 0, 255, 228),
    gsDPSetScissor(G_SC_NON_INTERLACE, 80, 0, 160, 239),
    gsDPFillRectangle(80, 170, 160, 171),
    gsDPSetScissor(G_SC_NON_INTERLACE, 82, 0, 158, 239),
    gsDPFillRectangle(80, 172, 160, 173),
    gsDPSetScissor(G_SC_NON_INTERLACE, 84, 0, 156, 239),
    gsDPFillRectangle(80, 174, 160, 175),
    gsDPSetScissor(G_SC_NON_INTERLACE, 86, 0, 154, 239),
    gsDPFillRectangle(80, 176, 160, 177),
    gsDPSetScissor(G_SC_NON_INTERLACE, 88, 0, 152, 239),
    gsDPFillRectangle(80, 178, 160, 179),
    gsDPSetScissor(G_SC_NON_INTERLACE, 90, 0, 150, 239),
    gsDPFillRectangle(80, 180, 160, 181),
    gsDPSetScissor(G_SC_NON_INTERLACE, 92, 0, 148, 239),
    gsDPFillRectangle(80, 182, 160, 183),
    gsDPSetScissor(G_SC_NON_INTERLACE, 94, 0, 146, 239),
    gsDPFillRectangle(80, 184, 160, 185),
    gsDPSetScissor(G_SC_NON_INTERLACE, 96, 0, 144, 239),
    gsDPFillRectangle(80, 186, 160, 187),
    gsDPSetScissor(G_SC_NON_INTERLACE, 98, 0, 142, 239),
    gsDPFillRectangle(80, 188, 160, 189),
    gsDPSetScissor(G_SC_NON_INTERLACE, 100, 0, 140, 239),
    gsDPFillRectangle(80, 190, 160, 191),
    gsDPSetScissor(G_SC_NON_INTERLACE, 102, 0, 138, 239),
    gsDPFillRectangle(80, 192, 160, 193),
    gsDPSetScissor(G_SC_NON_INTERLACE, 104, 0, 136, 239),
    gsDPFillRectangle(80, 194, 160, 195),
    gsDPSetScissor(G_SC_NON_INTERLACE, 106, 0, 134, 239),
    gsDPFillRectangle(80, 196, 160, 197),
    gsDPSetScissor(G_SC_NON_INTERLACE, 108, 0, 132, 239),
    gsDPFillRectangle(80, 198, 160, 199),
    gsDPSetScissor(G_SC_NON_INTERLACE, 110, 0, 130, 239),
    gsDPFillRectangle(80, 200, 160, 201),
    gsDPSetScissor(G_SC_NON_INTERLACE, 112, 0, 128, 239),
    gsDPFillRectangle(80, 202, 160, 203),
    gsDPSetScissor(G_SC_NON_INTERLACE, 113, 0, 127, 239),
    gsDPFillRectangle(80, 204, 160, 205),
    gsDPSetScissor(G_SC_NON_INTERLACE, 114, 0, 126, 239),
    gsDPFillRectangle(80, 206, 160, 207),
    gsDPSetScissor(G_SC_NON_INTERLACE, 115, 0, 125, 239),
    gsDPFillRectangle(80, 208, 160, 209),
    gsDPSetScissor(G_SC_NON_INTERLACE, 116, 0, 124, 239),
    gsDPFillRectangle(80, 210, 160, 211),
    gsDPSetScissor(G_SC_NON_INTERLACE, 117, 0, 123, 239),
    gsDPFillRectangle(80, 212, 160, 213),
    gsDPSetScissor(G_SC_NON_INTERLACE, 118, 0, 122, 239),
    gsDPFillRectangle(80, 214, 160, 215),
    gsDPSetScissor(G_SC_NON_INTERLACE, 119, 0, 121, 239),
    gsDPFillRectangle(80, 216, 160, 217),
    gsDPSetScissor(G_SC_NON_INTERLACE, 120, 0, 120, 239),
    gsDPFillRectangle(80, 218, 160, 219),
    gsDPPipeSync(),
    gsDPSetPrimColor(150, 205, 255, 0, 0, 228),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 319, 239),
    gsDPFillRectangle(80, 219, 160, 220),

	/* y scissoring */
    gsDPPipeSync(),
    gsDPSetPrimColor(150, 205, 255, 0, 0, 228),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 319, 239),
    gsDPFillRectangle( 80, 220, 85, 225),
    gsDPPipeSync(),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 228),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 220, 319, 225),
    gsDPFillRectangle( 90, 220, 95, 225),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 221, 319, 225),
    gsDPFillRectangle(100, 220,105, 225),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 221, 319, 224),
    gsDPFillRectangle(110, 220,115, 225),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 222, 319, 224),
    gsDPFillRectangle(120, 220,125, 225),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 222, 319, 223),
    gsDPFillRectangle(130, 220,135, 225),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 223, 319, 223),
    gsDPFillRectangle(140, 220,145, 225),
    gsDPPipeSync(),
    gsDPSetPrimColor(150, 205, 255, 0, 0, 228),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 319, 239),
    gsDPFillRectangle(150, 220,155, 225),
    gsDPPipeSync(),


    /* TWO CYCLE MODE */

    gsDPSetCycleType(G_CYC_2CYCLE),

        /* test 2 pixel spans (red) */
    gsDPSetPrimColor(150, 205, 255, 0, 0, 228),
    gsDPFillRectangle(180, 10, 181, 11),
    gsDPFillRectangle(181, 12, 182, 13),
    gsDPFillRectangle(182, 14, 183, 15),
    gsDPFillRectangle(183, 16, 184, 17),
    gsDPFillRectangle(184, 18, 185, 19),
    gsDPFillRectangle(185, 20, 186, 21),
    gsDPFillRectangle(186, 22, 187, 23),
    gsDPFillRectangle(187, 24, 188, 25),
    gsDPFillRectangle(188, 26, 189, 27),
    gsDPFillRectangle(189, 28, 190, 29),
    gsDPFillRectangle(190, 30, 191, 31),
    gsDPFillRectangle(191, 32, 192, 33),
    gsDPFillRectangle(192, 34, 193, 35),
    gsDPFillRectangle(193, 36, 194, 37),
    gsDPFillRectangle(194, 38, 195, 39),
    gsDPFillRectangle(195, 40, 196, 41),
    gsDPFillRectangle(196, 42, 197, 43),
    gsDPFillRectangle(197, 44, 198, 45),
    gsDPFillRectangle(198, 46, 199, 47),
    gsDPFillRectangle(199, 48,200, 49),
    gsDPFillRectangle(200, 10,201, 11),
    gsDPFillRectangle(201, 12,202, 13),
    gsDPFillRectangle(202, 14,203, 15),
    gsDPFillRectangle(203, 16,204, 17),
    gsDPFillRectangle(204, 18,205, 19),
    gsDPFillRectangle(205, 20,206, 21),
    gsDPFillRectangle(206, 22,207, 23),
    gsDPFillRectangle(207, 24,208, 25),
    gsDPFillRectangle(208, 26,209, 27),
    gsDPFillRectangle(209, 28,210, 29),
    gsDPFillRectangle(210, 30,211, 31),
    gsDPFillRectangle(211, 32,212, 33),
    gsDPFillRectangle(212, 34,213, 35),
    gsDPFillRectangle(213, 36,214, 37),
    gsDPFillRectangle(214, 38,215, 39),
    gsDPFillRectangle(215, 40,216, 41),
    gsDPFillRectangle(216, 42,217, 43),
    gsDPFillRectangle(217, 44,218, 45),
    gsDPFillRectangle(218, 46,219, 47),
    gsDPFillRectangle(219, 48,220, 49),
    gsDPFillRectangle(220, 10,221, 11),
    gsDPFillRectangle(221, 12,222, 13),
    gsDPFillRectangle(222, 14,223, 15),
    gsDPFillRectangle(223, 16,224, 17),
    gsDPFillRectangle(224, 18,225, 19),
    gsDPFillRectangle(225, 20,226, 21),
    gsDPFillRectangle(226, 22,227, 23),
    gsDPFillRectangle(227, 24,228, 25),
    gsDPFillRectangle(228, 26,229, 27),
    gsDPFillRectangle(229, 28,230, 29),
    gsDPFillRectangle(230, 30,231, 31),
    gsDPFillRectangle(231, 32,232, 33),
    gsDPFillRectangle(232, 34,233, 35),
    gsDPFillRectangle(233, 36,234, 37),
    gsDPFillRectangle(234, 38,235, 39),
    gsDPFillRectangle(235, 40,236, 41),
    gsDPFillRectangle(236, 42,237, 43),
    gsDPFillRectangle(237, 44,238, 45),
    gsDPFillRectangle(238, 46,239, 47),
    gsDPFillRectangle(239, 48,240, 49),
    gsDPPipeSync(),

	/* longer spans (cyan) */
    gsDPSetPrimColor(150, 205, 0, 255, 255, 228),
    gsDPFillRectangle(180, 50,220, 51),
    gsDPFillRectangle(181, 52,221, 53),
    gsDPFillRectangle(182, 54,222, 55),
    gsDPFillRectangle(183, 56,223, 57),
    gsDPFillRectangle(184, 58,224, 59),
    gsDPFillRectangle(185, 60,225, 61),
    gsDPFillRectangle(186, 62,226, 63),
    gsDPFillRectangle(187, 64,227, 65),
    gsDPFillRectangle(188, 66,228, 67),
    gsDPFillRectangle(189, 68,229, 69),
    gsDPFillRectangle(190, 70,230, 71),
    gsDPFillRectangle(191, 72,231, 73),
    gsDPFillRectangle(192, 74,232, 75),
    gsDPFillRectangle(193, 76,233, 77),
    gsDPFillRectangle(194, 78,234, 79),
    gsDPFillRectangle(195, 80,235, 81),
    gsDPFillRectangle(196, 82,236, 83),
    gsDPFillRectangle(197, 84,237, 85),
    gsDPFillRectangle(198, 86,238, 87),
    gsDPFillRectangle(199, 88,239, 89),
    gsDPFillRectangle(200, 90,240, 91),
    gsDPFillRectangle(201, 92,241, 93),
    gsDPFillRectangle(202, 94,242, 95),
    gsDPFillRectangle(203, 96,243, 97),
    gsDPFillRectangle(204, 98,244, 99),
    gsDPFillRectangle(205,100,245,101),
    gsDPFillRectangle(206,102,246,103),
    gsDPFillRectangle(207,104,247,105),
    gsDPFillRectangle(208,106,248,107),
    gsDPFillRectangle(209,108,249,109),
    gsDPFillRectangle(210,110,250,111),
    gsDPFillRectangle(211,112,251,113),
    gsDPFillRectangle(212,114,252,115),
    gsDPFillRectangle(213,116,253,117),
    gsDPFillRectangle(214,118,254,119),
    gsDPFillRectangle(215,120,255,121),
    gsDPFillRectangle(216,122,256,123),
    gsDPFillRectangle(217,124,257,125),
    gsDPFillRectangle(218,126,258,127),
    gsDPFillRectangle(219,128,259,129),
    gsDPPipeSync(),

	/* one pixel spans (white) */
    gsDPSetPrimColor(150, 205, 255, 255, 255, 228),
    gsDPFillRectangle(180, 130, 182, 131),
    gsDPFillRectangle(181, 132, 183, 133),
    gsDPFillRectangle(182, 134, 184, 135),
    gsDPFillRectangle(183, 136, 185, 137),
    gsDPFillRectangle(184, 138, 186, 139),
    gsDPFillRectangle(185, 140, 187, 141),
    gsDPFillRectangle(186, 142, 188, 143),
    gsDPFillRectangle(187, 144, 189, 145),
    gsDPFillRectangle(188, 146, 190, 147),
    gsDPFillRectangle(189, 148, 191, 149),
    gsDPFillRectangle(190, 150, 192, 151),
    gsDPFillRectangle(191, 152, 193, 153),
    gsDPFillRectangle(192, 154, 194, 155),
    gsDPFillRectangle(193, 156, 195, 157),
    gsDPFillRectangle(194, 158, 196, 159),
    gsDPFillRectangle(195, 160, 197, 161),
    gsDPFillRectangle(196, 162, 198, 163),
    gsDPFillRectangle(197, 164, 199, 165),
    gsDPFillRectangle(198, 166, 200, 167),
    gsDPFillRectangle(199, 168, 201, 169),
    gsDPFillRectangle(200, 130,202, 131),
    gsDPFillRectangle(201, 132,203, 133),
    gsDPFillRectangle(202, 134,204, 135),
    gsDPFillRectangle(203, 136,205, 137),
    gsDPFillRectangle(204, 138,206, 139),
    gsDPFillRectangle(205, 140,207, 141),
    gsDPFillRectangle(206, 142,208, 143),
    gsDPFillRectangle(207, 144,209, 145),
    gsDPFillRectangle(208, 146,210, 147),
    gsDPFillRectangle(209, 148,211, 149),
    gsDPFillRectangle(210, 150,212, 151),
    gsDPFillRectangle(211, 152,213, 153),
    gsDPFillRectangle(212, 154,214, 155),
    gsDPFillRectangle(213, 156,215, 157),
    gsDPFillRectangle(214, 158,216, 159),
    gsDPFillRectangle(215, 160,217, 161),
    gsDPFillRectangle(216, 162,218, 163),
    gsDPFillRectangle(217, 164,219, 165),
    gsDPFillRectangle(218, 166,220, 167),
    gsDPFillRectangle(219, 168,221, 169),
    gsDPFillRectangle(220, 130,222, 131),
    gsDPFillRectangle(221, 132,223, 133),
    gsDPFillRectangle(222, 134,224, 135),
    gsDPFillRectangle(223, 136,225, 137),
    gsDPFillRectangle(224, 138,226, 139),
    gsDPFillRectangle(225, 140,227, 141),
    gsDPFillRectangle(226, 142,228, 143),
    gsDPFillRectangle(227, 144,229, 145),
    gsDPFillRectangle(228, 146,230, 147),
    gsDPFillRectangle(229, 148,231, 149),
    gsDPFillRectangle(230, 150,232, 151),
    gsDPFillRectangle(231, 152,233, 153),
    gsDPFillRectangle(232, 154,234, 155),
    gsDPFillRectangle(233, 156,235, 157),
    gsDPFillRectangle(234, 158,236, 159),
    gsDPFillRectangle(235, 160,237, 161),
    gsDPFillRectangle(236, 162,238, 163),
    gsDPFillRectangle(237, 164,239, 165),
    gsDPFillRectangle(238, 166,240, 167),
    gsDPFillRectangle(239, 168,241, 169),
    gsDPPipeSync(),

	/* Scissoring (unscissored in red, */
	/* x-scissored in blue, y-scissored in green */
    gsDPSetPrimColor(150, 205, 255, 0, 0, 228),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 319, 239),
    gsDPFillRectangle(180, 169, 260, 170),
    gsDPPipeSync(),
    gsDPSetPrimColor(150, 205, 0, 0, 255, 228),
    gsDPSetScissor(G_SC_NON_INTERLACE, 180, 0, 260, 239),
    gsDPFillRectangle(180, 170, 260, 171),
    gsDPSetScissor(G_SC_NON_INTERLACE, 182, 0, 258, 239),
    gsDPFillRectangle(180, 172, 260, 173),
    gsDPSetScissor(G_SC_NON_INTERLACE, 184, 0, 256, 239),
    gsDPFillRectangle(180, 174, 260, 175),
    gsDPSetScissor(G_SC_NON_INTERLACE, 186, 0, 254, 239),
    gsDPFillRectangle(180, 176, 260, 177),
    gsDPSetScissor(G_SC_NON_INTERLACE, 188, 0, 252, 239),
    gsDPFillRectangle(180, 178, 260, 179),
    gsDPSetScissor(G_SC_NON_INTERLACE, 190, 0, 250, 239),
    gsDPFillRectangle(180, 180, 260, 181),
    gsDPSetScissor(G_SC_NON_INTERLACE, 192, 0, 248, 239),
    gsDPFillRectangle(180, 182, 260, 183),
    gsDPSetScissor(G_SC_NON_INTERLACE, 194, 0, 246, 239),
    gsDPFillRectangle(180, 184, 260, 185),
    gsDPSetScissor(G_SC_NON_INTERLACE, 196, 0, 244, 239),
    gsDPFillRectangle(180, 186, 260, 187),
    gsDPSetScissor(G_SC_NON_INTERLACE, 198, 0, 242, 239),
    gsDPFillRectangle(180, 188, 260, 189),
    gsDPSetScissor(G_SC_NON_INTERLACE, 200, 0, 240, 239),
    gsDPFillRectangle(180, 190, 260, 191),
    gsDPSetScissor(G_SC_NON_INTERLACE, 202, 0, 238, 239),
    gsDPFillRectangle(180, 192, 260, 193),
    gsDPSetScissor(G_SC_NON_INTERLACE, 204, 0, 236, 239),
    gsDPFillRectangle(180, 194, 260, 195),
    gsDPSetScissor(G_SC_NON_INTERLACE, 206, 0, 234, 239),
    gsDPFillRectangle(180, 196, 260, 197),
    gsDPSetScissor(G_SC_NON_INTERLACE, 208, 0, 232, 239),
    gsDPFillRectangle(180, 198, 260, 199),
    gsDPSetScissor(G_SC_NON_INTERLACE, 210, 0, 230, 239),
    gsDPFillRectangle(180, 200, 260, 201),
    gsDPSetScissor(G_SC_NON_INTERLACE, 212, 0, 228, 239),
    gsDPFillRectangle(180, 202, 260, 203),
    gsDPSetScissor(G_SC_NON_INTERLACE, 213, 0, 227, 239),
    gsDPFillRectangle(180, 204, 260, 205),
    gsDPSetScissor(G_SC_NON_INTERLACE, 214, 0, 226, 239),
    gsDPFillRectangle(180, 206, 260, 207),
    gsDPSetScissor(G_SC_NON_INTERLACE, 215, 0, 225, 239),
    gsDPFillRectangle(180, 208, 260, 209),
    gsDPSetScissor(G_SC_NON_INTERLACE, 216, 0, 224, 239),
    gsDPFillRectangle(180, 210, 260, 211),
    gsDPSetScissor(G_SC_NON_INTERLACE, 217, 0, 223, 239),
    gsDPFillRectangle(180, 212, 260, 213),
    gsDPSetScissor(G_SC_NON_INTERLACE, 218, 0, 222, 239),
    gsDPFillRectangle(180, 214, 260, 215),
    gsDPSetScissor(G_SC_NON_INTERLACE, 219, 0, 221, 239),
    gsDPFillRectangle(180, 216, 260, 217),
    gsDPSetScissor(G_SC_NON_INTERLACE, 220, 0, 220, 239),
    gsDPFillRectangle(180, 218, 260, 219),
    gsDPPipeSync(),
    gsDPSetPrimColor(150, 205, 255, 0, 0, 228),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 319, 239),
    gsDPFillRectangle(180, 219, 260, 220),

	/* y scissoring */
    gsDPPipeSync(),
    gsDPSetPrimColor(150, 205, 255, 0, 0, 228),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 319, 239),
    gsDPFillRectangle( 180, 220, 185, 225),
    gsDPPipeSync(),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 228),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 220, 319, 225),
    gsDPFillRectangle( 190, 220, 195, 225),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 221, 319, 225),
    gsDPFillRectangle(200, 220,205, 225),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 221, 319, 224),
    gsDPFillRectangle(210, 220,215, 225),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 222, 319, 224),
    gsDPFillRectangle(220, 220,225, 225),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 222, 319, 223),
    gsDPFillRectangle(230, 220,235, 225),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 223, 319, 223),
    gsDPFillRectangle(240, 220,245, 225),
    gsDPPipeSync(),
    gsDPSetPrimColor(150, 205, 255, 0, 0, 228),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 319, 239),
    gsDPFillRectangle(250, 220,255, 225),

    gsSPEndDisplayList(),
};
/* end of case 13 */

/*
 * Test 14, Frame 14:
 * a 16 bit texture load followed by 2 1-cycle triangles (to make a square)
 *
 */
static Vtx lr_cube[4] = {
        { 100, 120, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff        },
        {  60, 120, 0, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff     },
        {  60, 100, 0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff   },
        { 100, 100, 0, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff      },
};

Gfx rdpms_loadrend[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),


    /* set attributes, to be used as colors for rects */

    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),


    gsDPSetCycleType(G_CYC_1CYCLE),

    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPLoadTextureBlock(rdpms_RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&lr_cube, 4, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),

    gsSPEndDisplayList(),
};
/* end of case 14 */

/*
 * Test 15, Frame 15:
 * all the render modes and pipe sync's tested here for one cycle mode
 *
 */
Gfx rdpms_rmode1cyc[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),

    gsDPSetCycleType(G_CYC_1CYCLE),

    /* set attributes, to be used as colors for rects */
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),


        /* test prim color */
        /* 3 bars: magenta over green over grey, all solid colors */
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 10, 12, 11),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 228),
    gsDPFillRectangle(10, 20, 12, 21),
    gsDPSetPrimColor(150, 205, 128, 128, 128, 228),
    gsDPFillRectangle(10, 30, 12, 31),
    gsDPPipeSync(),

        /* test 4 AA rendering modes */
        /* 5 bars: opaque, transp, transline, decalline, opaque */
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 128),
    gsDPFillRectangle(11, 39, 12, 50),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 40, 13, 41),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsDPFillRectangle(10, 42, 13, 43),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_XLU_LINE, G_RM_AA_XLU_LINE2),
    gsDPFillRectangle(10, 44, 13, 45),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_DEC_LINE, G_RM_AA_DEC_LINE2),
    gsDPFillRectangle(10, 46, 13, 47),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPFillRectangle(10, 48, 13, 49),
    gsDPPipeSync(),

        /* test 2 PT rendering modes */
        /* 3 bars: opaque, transp, opaque */
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 128),
    gsDPFillRectangle(11, 89, 12, 96),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 90, 13, 91),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPFillRectangle(10, 92, 13, 93),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPFillRectangle(10, 94, 13, 95),
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
    gsDPFillRectangle(11,119,12,162),
    gsDPSetPrimDepth(0x300,0x400),
    gsDPFillRectangle(14,119,15,162),
    gsDPSetPrimDepth(0x500,0x400),
    gsDPFillRectangle(17,119,18,162),
    gsDPSetPrimDepth(0x800,0x1),
    gsDPFillRectangle(20,119,21,162),
    gsDPPipeSync(),

        /* draw 4 vertical bars: half (3) coverage */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF | CVG_X_ALPHA, G_RM_AA_ZB_OPA_SURF2 |
CVG_X_ALPHA),
    gsDPSetPrimDepth(0x100,0x1),
    gsDPFillRectangle(12,119,13,162),
    gsDPSetPrimDepth(0x300,0x400),
    gsDPFillRectangle(15,119,16,162),
    gsDPSetPrimDepth(0x500,0x400),
    gsDPFillRectangle(18,119,19,162),
    gsDPSetPrimDepth(0x800,0x1),
    gsDPFillRectangle(21,119,22,162),
    gsDPPipeSync(),

        /* test 4 ZB rendering modes */
        /* 4 bars: opaque, transp, decal, decal-transp */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPSetPrimDepth(0x400,0x1),
    gsDPFillRectangle(10, 120, 23, 121),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2),
    gsDPFillRectangle(10, 122, 23, 123),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_ZB_OPA_DECAL, G_RM_ZB_OPA_DECAL2),
    gsDPFillRectangle(10, 124, 23, 125),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_ZB_XLU_DECAL, G_RM_ZB_XLU_DECAL2),
    gsDPFillRectangle(10, 126, 23, 127),
    gsDPPipeSync(),

        /* test 8 AA ZB rendering modes */
        /* 9 bars: opaque, transp, decal, decal-transp, interpen, interpen-transp, dec-line, transp-line, opaque */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(10, 130, 23, 131),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPFillRectangle(10, 132, 23, 133),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_DECAL, G_RM_AA_ZB_OPA_DECAL2),
    gsDPFillRectangle(10, 134, 23, 135),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2),
    gsDPFillRectangle(10, 136, 23, 137),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_INTER, G_RM_AA_ZB_OPA_INTER2),
    gsDPFillRectangle(10, 138, 23, 139),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2),
    gsDPFillRectangle(10, 140, 23, 141),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_DEC_LINE, G_RM_AA_ZB_DEC_LINE2),
    gsDPFillRectangle(10, 142, 23, 143),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_LINE, G_RM_AA_ZB_XLU_LINE2),
    gsDPFillRectangle(10, 144, 23, 145),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(10, 146, 23, 147),
    gsDPPipeSync(),

        /* test prim depth (z and dz) */
        /* 5 bars: behind all, middle, in front of all, behind-not in range, behind-in range of 3, behind-in range of all */
        /* 5 bars should be: behind all, behind left 2, infront of all, invisible, decal on right 3, decal on all 4 */
    gsDPSetPrimDepth(0x7fff,0x1),
    gsDPFillRectangle(10, 150, 23, 151),
    gsDPSetPrimDepth(0x400,0x1),
    gsDPFillRectangle(10, 152, 23, 153),
    gsDPSetPrimDepth(0x0,0x1),
    gsDPFillRectangle(10, 154, 23, 155),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_DECAL, G_RM_AA_ZB_OPA_DECAL2),
    gsDPSetPrimDepth(0xa00,0x0),
    gsDPFillRectangle(10, 156, 23, 157),
    gsDPSetPrimDepth(0xa00,0x800),
    gsDPFillRectangle(10, 158, 23, 159),
    gsDPSetPrimDepth(0xa00,0x8000),
    gsDPFillRectangle(10, 160, 23, 161),
    gsDPPipeSync(),

        /* dithering */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xaa, 0x55, 0x81, 128),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPFillRectangle(60, 10, 100, 15),
    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_BAYER),
    gsDPFillRectangle(60, 20, 100, 25),
    gsDPPipeSync(),
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

    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),

    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPFillRectangle(60, 45, 61, 46),
    gsDPFillRectangle(60, 45, 61, 46),
    gsDPFillRectangle(60, 45, 61, 46),
    gsDPFillRectangle(60, 45, 61, 46),

    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPFillRectangle(60, 47, 61, 48),
    gsDPFillRectangle(60, 47, 61, 48),
    gsDPFillRectangle(60, 47, 61, 48),
    gsDPFillRectangle(60, 47, 61, 48),

    gsDPPipeSync(),

        /* scissor */
        /* 2 red bars.  1st half as long as second */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0x00, 0x00, 0x80),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 80, 240),
    gsDPFillRectangle(60, 50, 100, 50),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 320, 240),
    gsDPFillRectangle(60, 55, 100, 55),
    gsDPPipeSync(),

        /* other colors: environment, blend, and fog: */
        /* 3 pairs of 2 bars: blue, yellow, blue, cyan, blue, cyan */
    gsDPSetCombineLERP (0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT), /* env color */
    gsDPSetEnvColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 60,  65, 61),
    gsDPPipeSync(),
    gsDPSetEnvColor(0xff,0xff,0,0xff),
    gsDPFillRectangle(60, 65,  65, 66),
    gsDPPipeSync(),
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c1(G_BL_CLR_BL, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM),AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c2(G_BL_CLR_BL, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetBlendColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 70,  65, 71),
    gsDPPipeSync(),
    gsDPSetBlendColor(0,0xff,0xff,0xff),
    gsDPFillRectangle(60, 75,  65, 76),
    gsDPPipeSync(),
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c1(G_BL_CLR_FOG, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM),AA_EN
| Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c2(G_BL_CLR_FOG, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetFogColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 80,  65, 81),
    gsDPPipeSync(),
    gsDPSetFogColor(0,0xff,0xff,0xff),
    gsDPFillRectangle(60, 85,  65, 86),
    gsDPPipeSync(),

        /* set render mopde and combine lerp: */
        /* 2 bars: yellow, red */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(60, 90, 70, 91),
    gsDPPipeSync(),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPFillRectangle(60, 95, 70, 96),
    gsDPPipeSync(),

    /* restore original modes */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0xff, 0x00, 0x80),
    gsDPFillRectangle(310, 230, 315, 231),



    gsSPEndDisplayList(),
};
/* end of case 15 */


/*
 * Test 16, Frame 16:
 * same as test 15 but 2 cycle mode
 *
 */
Gfx rdpms_rmode2cyc[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),

    gsDPSetCycleType(G_CYC_2CYCLE),

    /* set attributes, to be used as colors for rects */
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_OPA_SURF2),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),


        /* test prim color */
        /* 3 bars: magenta over green over grey, all solid colors */
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 10, 12, 11),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 228),
    gsDPFillRectangle(10, 20, 12, 21),
    gsDPSetPrimColor(150, 205, 128, 128, 128, 228),
    gsDPFillRectangle(10, 30, 12, 31),
    gsDPPipeSync(),

        /* test 4 AA rendering modes */
        /* 5 bars: opaque, transp, transline, decalline, opaque */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 128),
    gsDPFillRectangle(11, 39, 12, 50),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 40, 13, 41),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
    gsDPFillRectangle(10, 42, 13, 43),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_LINE2),
    gsDPFillRectangle(10, 44, 13, 45),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_DEC_LINE2),
    gsDPFillRectangle(10, 46, 13, 47),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_OPA_SURF2),
    gsDPFillRectangle(10, 48, 13, 49),
    gsDPPipeSync(),

        /* test 2 PT rendering modes */
        /* 3 bars: opaque, transp, opaque */
    gsDPSetRenderMode(G_RM_PASS, G_RM_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0, 255, 0, 128),
    gsDPFillRectangle(11, 89, 12, 96),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPFillRectangle(10, 90, 13, 91),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPFillRectangle(10, 92, 13, 93),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_OPA_SURF2),
    gsDPFillRectangle(10, 94, 13, 95),
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
    gsDPFillRectangle(11,119,12,162),
    gsDPSetPrimDepth(0x300,0x400),
    gsDPFillRectangle(14,119,15,162),
    gsDPSetPrimDepth(0x500,0x400),
    gsDPFillRectangle(17,119,18,162),
    gsDPSetPrimDepth(0x800,0x1),
    gsDPFillRectangle(20,119,21,162),
    gsDPPipeSync(),

        /* draw 4 vertical bars: half (3) coverage */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2 |
CVG_X_ALPHA),
    gsDPSetPrimDepth(0x100,0x1),
    gsDPFillRectangle(12,119,13,162),
    gsDPSetPrimDepth(0x300,0x400),
    gsDPFillRectangle(15,119,16,162),
    gsDPSetPrimDepth(0x500,0x400),
    gsDPFillRectangle(18,119,19,162),
    gsDPSetPrimDepth(0x800,0x1),
    gsDPFillRectangle(21,119,22,162),
    gsDPPipeSync(),

        /* test 4 ZB rendering modes */
        /* 4 bars: opaque, transp, decal, decal-transp */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 128),
    gsDPSetPrimDepth(0x400,0x1),
    gsDPFillRectangle(10, 120, 23, 121),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_XLU_SURF2),
    gsDPFillRectangle(10, 122, 23, 123),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_OPA_DECAL2),
    gsDPFillRectangle(10, 124, 23, 125),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_XLU_DECAL2),
    gsDPFillRectangle(10, 126, 23, 127),
    gsDPPipeSync(),

        /* test 8 AA ZB rendering modes */
        /* 9 bars: opaque, transp, decal, decal-transp, interpen, interpen-transp, dec-line, transp-line, opaque */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(10, 130, 23, 131),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_SURF2),
    gsDPFillRectangle(10, 132, 23, 133),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_DECAL2),
    gsDPFillRectangle(10, 134, 23, 135),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_DECAL2),
    gsDPFillRectangle(10, 136, 23, 137),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_INTER2),
    gsDPFillRectangle(10, 138, 23, 139),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_INTER2),
    gsDPFillRectangle(10, 140, 23, 141),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_DEC_LINE2),
    gsDPFillRectangle(10, 142, 23, 143),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_LINE2),
    gsDPFillRectangle(10, 144, 23, 145),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(10, 146, 23, 147),
    gsDPPipeSync(),

        /* test prim depth (z and dz) */
        /* 5 bars: behind all, middle, in front of all, behind-not in range, behind-in range of 3, behind-in range of all */
        /* 5 bars should be: behind all, behind left 2, infront of all, invisible, decal on right 3, decal on all 4 */
    gsDPSetPrimDepth(0x7fff,0x1),
    gsDPFillRectangle(10, 150, 23, 151),
    gsDPSetPrimDepth(0x400,0x1),
    gsDPFillRectangle(10, 152, 23, 153),
    gsDPSetPrimDepth(0x0,0x1),
    gsDPFillRectangle(10, 154, 23, 155),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_DECAL2),
    gsDPSetPrimDepth(0xa00,0x0),
    gsDPFillRectangle(10, 156, 23, 157),
    gsDPSetPrimDepth(0xa00,0x800),
    gsDPFillRectangle(10, 158, 23, 159),
    gsDPSetPrimDepth(0xa00,0x8000),
    gsDPFillRectangle(10, 160, 23, 161),
    gsDPPipeSync(),

        /* dithering */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xaa, 0x55, 0x81, 128),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPFillRectangle(60, 10, 100, 15),
    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_BAYER),
    gsDPFillRectangle(60, 20, 100, 25),
    gsDPPipeSync(),
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

    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),
    gsDPFillRectangle(60, 43, 61, 44),

    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPFillRectangle(60, 45, 61, 46),
    gsDPFillRectangle(60, 45, 61, 46),
    gsDPFillRectangle(60, 45, 61, 46),
    gsDPFillRectangle(60, 45, 61, 46),

    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPFillRectangle(60, 47, 61, 48),
    gsDPFillRectangle(60, 47, 61, 48),
    gsDPFillRectangle(60, 47, 61, 48),
    gsDPFillRectangle(60, 47, 61, 48),

    gsDPPipeSync(),

        /* scissor */
        /* 2 red bars.  1st half as long as second */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0x00, 0x00, 0x80),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 80, 240),
    gsDPFillRectangle(60, 50, 100, 50),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 320, 240),
    gsDPFillRectangle(60, 55, 100, 55),
    gsDPPipeSync(),

        /* other colors: environment, blend, and fog: */
        /* 3 pairs of 2 bars: blue, yellow, blue, cyan, blue, cyan */
    gsDPSetCombineLERP (0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT), /* env color */
    gsDPSetEnvColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 60,  65, 61),
    gsDPPipeSync(),
    gsDPSetEnvColor(0xff,0xff,0,0xff),
    gsDPFillRectangle(60, 65,  65, 66),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS,AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c2(G_BL_CLR_BL, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetBlendColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 70,  65, 71),
    gsDPPipeSync(),
    gsDPSetBlendColor(0,0xff,0xff,0xff),
    gsDPFillRectangle(60, 75,  65, 76),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS,AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |ZMODE_OPA | ALPHA_CVG_SEL |GBL_c2(G_BL_CLR_FOG, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsDPSetFogColor(0,0,0xff,0xff),
    gsDPFillRectangle(60, 80,  65, 81),
    gsDPPipeSync(),
    gsDPSetFogColor(0,0xff,0xff,0xff),
    gsDPFillRectangle(60, 85,  65, 86),
    gsDPPipeSync(),

        /* set render mopde and combine lerp: */
        /* 2 bars: yellow, red */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPFillRectangle(60, 90, 70, 91),
    gsDPPipeSync(),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPFillRectangle(60, 95, 70, 96),
    gsDPPipeSync(),

    /* restore original modes */
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetPrimColor(150, 205, 0xff, 0xff, 0x00, 0x80),
    gsDPFillRectangle(310, 230, 315, 231),


    gsSPEndDisplayList(),
};
/* end of case 16 */

/*
 * Test 17, Frame 17:
 * 
 *
 */

#include "RGBA16rainbow.h"

#define DEFTEXRECT1(x,y,s) \
    gsSPTextureRectangle( x<<2, y<<2, x<<2, y<<2, G_TX_RENDERTILE,s<<5,0,4<<10,1<<10)

#define RENDTEXRECT1(x,y,s) \
	gsSPTextureRectangle( x<<2, y<<2, (x+1)<<2, (y+1)<<2, G_TX_RENDERTILE,s<<5,0,4<<10,1<<10) 

#define DEFTEXRECT9(x,y,s) \
	gsSPTextureRectangle( x<<2, y<<2, (x+8)<<2, y<<2, G_TX_RENDERTILE,s<<5,0,4<<10,1<<10) 

#define DEFTEXRECT2(x,y,s) \
	gsSPTextureRectangle( x<<2, y<<2, (x+1)<<2, y<<2, G_TX_RENDERTILE,s<<5,0,4<<10,1<<10) 

#define DEFTEXRECT17(x,y,s) \
	gsSPTextureRectangle( x<<2, y<<2, (x+16)<<2, y<<2, G_TX_RENDERTILE,s<<5,0,4<<10,1<<10) 

#define RENDTEX4RECT9(x,y,s) \
	gsSPTextureRectangle( x<<2, y<<2, (x+9)<<2, (y+1)<<2, G_TX_RENDERTILE,s<<5,0,1<<10,1<<10) 

#define RENDTEX8RECT9(x,y,s) \
	gsSPTextureRectangle( x<<2, y<<2, (x+9)<<2, (y+1)<<2, G_TX_RENDERTILE,s<<5,0,1<<10,1<<10) 

#define RENDTEX32RECT9(x,y,s) \
	gsSPTextureRectangle( x<<2, y<<2, (x+9)<<2, (y+1)<<2, G_TX_RENDERTILE,s<<5,0,1<<10,1<<10) 

#define TRIVERT1(x,y,s,t)	\
        { (x+1), (y+1), 0, 0, ( (s) << 6)+0x10, ( t << 6)+0x10, 0, 0, 0, 0},	\
        { (x+0), (y+1), 0, 0, ( (s) << 6)+0x10, ( t << 6)+0x10, 0, 0, 0, 0},	\
        { (x+0), (y+0), 0, 0, ( (s) << 6)+0x10, ( t << 6)+0x10, 0, 0, 0, 0},	\
        { (x+1), (y+0), 0, 0, ( (s) << 6)+0x10, ( t << 6)+0x10, 0, 0, 0, 0},

#define DRAW2TRI(v)			\
    gsSPVertex(&v, 4, 0),		\
    gsSP1Triangle(0, 2, 3, 0),		\
    gsSP1Triangle(0, 1, 2, 0),



Gfx rdpms_txalign[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),


    /* set attributes, to be used as colors for rects */


    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureFilter(G_TF_POINT),




    gsDPSetCycleType(G_CYC_1CYCLE), 
    gsDPLoadTextureTile(roundrain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 96, 4,
                         31, 0, 64, 3, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle(138<<2,  44<<2,172<<2, 48<<2, G_TX_RENDERTILE,31<<5,0<<5,1<<10,1<<10),
    gsDPTileSync(),
    gsDPLoadTextureTile(roundrain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20,
                         0, 0, 19, 19, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(138<<2,  50<<2,158<<2, 70<<2, G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),





    gsDPSetCycleType(G_CYC_COPY),

    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPLoadTextureBlock(rainbow16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),

    DEFTEXRECT1(10,12,0),
    DEFTEXRECT1(11,13,0),
    DEFTEXRECT1(12,14,0),
    DEFTEXRECT1(13,15,0),
    DEFTEXRECT1(10,16,1),
    DEFTEXRECT1(11,17,1),
    DEFTEXRECT1(12,18,1),
    DEFTEXRECT1(13,19,1),
    DEFTEXRECT1(10,20,2),
    DEFTEXRECT1(11,21,2),
    DEFTEXRECT1(12,22,2),
    DEFTEXRECT1(13,23,2),
    DEFTEXRECT1(10,24,3),
    DEFTEXRECT1(11,25,3),
    DEFTEXRECT1(12,26,3),
    DEFTEXRECT1(13,27,3),

    DEFTEXRECT9(10,70,0),
    DEFTEXRECT9(11,71,0),
    DEFTEXRECT9(12,72,0),
    DEFTEXRECT9(13,73,0),
    DEFTEXRECT9(14,74,0),
    DEFTEXRECT9(15,75,0),
    DEFTEXRECT9(16,76,0),
    DEFTEXRECT9(17,77,0),
    DEFTEXRECT9(10,78,1),
    DEFTEXRECT9(11,79,1),
    DEFTEXRECT9(12,80,1),
    DEFTEXRECT9(13,81,1),
    DEFTEXRECT9(14,82,1),
    DEFTEXRECT9(15,83,1),
    DEFTEXRECT9(16,84,1),
    DEFTEXRECT9(17,85,1),
    DEFTEXRECT9(10,86,2),
    DEFTEXRECT9(11,87,2),
    DEFTEXRECT9(12,88,2),
    DEFTEXRECT9(13,89,2),
    DEFTEXRECT9(14,90,2),
    DEFTEXRECT9(15,91,2),
    DEFTEXRECT9(16,92,2),
    DEFTEXRECT9(17,93,2),
    DEFTEXRECT9(10,94,3),
    DEFTEXRECT9(11,95,3),
    DEFTEXRECT9(12,96,3),
    DEFTEXRECT9(13,97,3),
    DEFTEXRECT9(14,98,3),
    DEFTEXRECT9(15,99,3),
    DEFTEXRECT9(16,100,3),
    DEFTEXRECT9(17,101,3),
    DEFTEXRECT9(10,102,4),
    DEFTEXRECT9(11,103,4),
    DEFTEXRECT9(12,104,4),
    DEFTEXRECT9(13,105,4),
    DEFTEXRECT9(14,106,4),
    DEFTEXRECT9(15,107,4),
    DEFTEXRECT9(16,108,4),
    DEFTEXRECT9(17,109,4),
    DEFTEXRECT9(10,110,5),
    DEFTEXRECT9(11,111,5),
    DEFTEXRECT9(12,112,5),
    DEFTEXRECT9(13,113,5),
    DEFTEXRECT9(14,114,5),
    DEFTEXRECT9(15,115,5),
    DEFTEXRECT9(16,116,5),
    DEFTEXRECT9(17,117,5),
    DEFTEXRECT9(10,118,6),
    DEFTEXRECT9(11,119,6),
    DEFTEXRECT9(12,120,6),
    DEFTEXRECT9(13,121,6),
    DEFTEXRECT9(14,122,6),
    DEFTEXRECT9(15,123,6),
    DEFTEXRECT9(16,124,6),
    DEFTEXRECT9(17,125,6),
    DEFTEXRECT9(10,126,7),
    DEFTEXRECT9(11,127,7),
    DEFTEXRECT9(12,128,7),
    DEFTEXRECT9(13,129,7),
    DEFTEXRECT9(14,130,7),
    DEFTEXRECT9(15,131,7),
    DEFTEXRECT9(16,132,7),
    DEFTEXRECT9(17,133,7),

    DEFTEXRECT1(10,140,0),
    DEFTEXRECT1(11,141,0),
    DEFTEXRECT1(12,142,0),
    DEFTEXRECT1(13,143,0),
    DEFTEXRECT1(14,144,0),
    DEFTEXRECT1(15,145,0),
    DEFTEXRECT1(16,146,0),
    DEFTEXRECT1(17,147,0),
    DEFTEXRECT1(18,148,0),
    DEFTEXRECT1(19,149,0),
    DEFTEXRECT1(20,150,0),
    DEFTEXRECT1(21,151,0),
    DEFTEXRECT1(22,152,0),
    DEFTEXRECT1(23,153,0),
    DEFTEXRECT1(24,154,0),
    DEFTEXRECT1(25,155,0),
    DEFTEXRECT1(26,156,0),
    DEFTEXRECT1(27,157,0),
    DEFTEXRECT1(28,158,0),
    DEFTEXRECT1(29,159,0),
    DEFTEXRECT1(30,160,0),
    DEFTEXRECT1(31,161,0),
    DEFTEXRECT1(32,162,0),
    DEFTEXRECT1(33,163,0),
    DEFTEXRECT1(34,164,0),
    DEFTEXRECT1(35,165,0),
    DEFTEXRECT1(36,166,0),
    DEFTEXRECT1(37,167,0),
    DEFTEXRECT1(38,168,0),
    DEFTEXRECT1(39,169,0),
    DEFTEXRECT1(40,170,0),

    DEFTEXRECT2(10,150,0),
    DEFTEXRECT2(11,151,0),
    DEFTEXRECT2(12,152,0),
    DEFTEXRECT2(13,153,0),
    DEFTEXRECT2(14,154,0),
    DEFTEXRECT2(15,155,0),
    DEFTEXRECT2(16,156,0),
    DEFTEXRECT2(17,157,0),
    DEFTEXRECT2(18,158,0),
    DEFTEXRECT2(19,159,0),
    DEFTEXRECT2(20,160,0),
    DEFTEXRECT2(21,161,0),
    DEFTEXRECT2(22,162,0),
    DEFTEXRECT2(23,163,0),
    DEFTEXRECT2(24,164,0),
    DEFTEXRECT2(25,165,0),
    DEFTEXRECT2(26,166,0),
    DEFTEXRECT2(27,167,0),
    DEFTEXRECT2(28,168,0),
    DEFTEXRECT2(29,169,0),
    DEFTEXRECT2(30,170,0),
    DEFTEXRECT2(31,171,0),
    DEFTEXRECT2(32,172,0),
    DEFTEXRECT2(33,173,0),
    DEFTEXRECT2(34,174,0),
    DEFTEXRECT2(35,175,0),
    DEFTEXRECT2(36,176,0),
    DEFTEXRECT2(37,177,0),
    DEFTEXRECT2(38,178,0),
    DEFTEXRECT2(39,179,0),
    DEFTEXRECT2(40,180,0),

    DEFTEXRECT17(10,180,0),
    DEFTEXRECT17(11,181,0),
    DEFTEXRECT17(12,182,0),
    DEFTEXRECT17(13,183,0),
    DEFTEXRECT17(14,184,0),
    DEFTEXRECT17(15,185,0),
    DEFTEXRECT17(16,186,0),
    DEFTEXRECT17(17,187,0),
    DEFTEXRECT17(18,188,0),
    DEFTEXRECT17(19,189,0),
    DEFTEXRECT17(20,190,0),
    DEFTEXRECT17(21,191,0),
    DEFTEXRECT17(22,192,0),
    DEFTEXRECT17(23,193,0),
    DEFTEXRECT17(24,194,0),
    DEFTEXRECT17(25,195,0),
    DEFTEXRECT17(26,196,0),
    DEFTEXRECT17(27,197,0),
    DEFTEXRECT17(28,198,0),
    DEFTEXRECT17(29,199,0),
    DEFTEXRECT17(30,200,0),
    DEFTEXRECT17(31,201,0),
    DEFTEXRECT17(32,202,0),
    DEFTEXRECT17(33,203,0),
    DEFTEXRECT17(34,204,0),
    DEFTEXRECT17(35,205,0),
    DEFTEXRECT17(36,206,0),
    DEFTEXRECT17(37,207,0),
    DEFTEXRECT17(38,208,0),
    DEFTEXRECT17(39,209,0),
    DEFTEXRECT17(40,210,0),

   
   

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE), 
    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    RENDTEXRECT1(10,33,0),
    RENDTEXRECT1(11,34,0),
    RENDTEXRECT1(12,35,0),
    RENDTEXRECT1(13,36,0),
    RENDTEXRECT1(10,37,1),
    RENDTEXRECT1(11,38,1),
    RENDTEXRECT1(12,39,1),
    RENDTEXRECT1(13,40,1),
    RENDTEXRECT1(10,41,2),
    RENDTEXRECT1(11,42,2),
    RENDTEXRECT1(12,43,2),
    RENDTEXRECT1(13,44,2),
    RENDTEXRECT1(10,45,3),
    RENDTEXRECT1(11,46,3),
    RENDTEXRECT1(12,47,3),
    RENDTEXRECT1(13,48,3),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsDPSetRenderMode(G_RM_ZB_OPA_SURF,G_RM_ZB_OPA_SURF2),
    RENDTEXRECT1(12,33,0),
    RENDTEXRECT1(13,34,0),
    RENDTEXRECT1(14,35,0),
    RENDTEXRECT1(15,36,0),
    RENDTEXRECT1(12,37,1),
    RENDTEXRECT1(13,38,1),
    RENDTEXRECT1(14,39,1),
    RENDTEXRECT1(15,40,1),
    RENDTEXRECT1(12,41,2),
    RENDTEXRECT1(13,42,2),
    RENDTEXRECT1(14,43,2),
    RENDTEXRECT1(15,44,2),
    RENDTEXRECT1(12,45,3),
    RENDTEXRECT1(13,46,3),
    RENDTEXRECT1(14,47,3),
    RENDTEXRECT1(15,48,3),
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF,G_RM_AA_XLU_SURF2),
    RENDTEXRECT1(14,33,0),
    RENDTEXRECT1(15,34,0),
    RENDTEXRECT1(16,35,0),
    RENDTEXRECT1(17,36,0),
    RENDTEXRECT1(14,37,1),
    RENDTEXRECT1(15,38,1),
    RENDTEXRECT1(16,39,1),
    RENDTEXRECT1(17,40,1),
    RENDTEXRECT1(14,41,2),
    RENDTEXRECT1(15,42,2),
    RENDTEXRECT1(16,43,2),
    RENDTEXRECT1(17,44,2),
    RENDTEXRECT1(14,45,3),
    RENDTEXRECT1(15,46,3),
    RENDTEXRECT1(16,47,3),
    RENDTEXRECT1(17,48,3),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF,G_RM_AA_ZB_XLU_SURF2),
    RENDTEXRECT1(16,33,0),
    RENDTEXRECT1(17,34,0),
    RENDTEXRECT1(18,35,0),
    RENDTEXRECT1(19,36,0),
    RENDTEXRECT1(16,37,1),
    RENDTEXRECT1(17,38,1),
    RENDTEXRECT1(18,39,1),
    RENDTEXRECT1(19,40,1),
    RENDTEXRECT1(16,41,2),
    RENDTEXRECT1(17,42,2),
    RENDTEXRECT1(18,43,2),
    RENDTEXRECT1(19,44,2),
    RENDTEXRECT1(16,45,3),
    RENDTEXRECT1(17,46,3),
    RENDTEXRECT1(18,47,3),
    RENDTEXRECT1(19,48,3),

    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetCycleType(G_CYC_2CYCLE), 
    gsDPSetRenderMode(G_RM_PASS,G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    RENDTEXRECT1(10,53,0),
    RENDTEXRECT1(11,54,0),
    RENDTEXRECT1(12,55,0),
    RENDTEXRECT1(13,56,0),
    RENDTEXRECT1(10,57,1),
    RENDTEXRECT1(11,58,1),
    RENDTEXRECT1(12,59,1),
    RENDTEXRECT1(13,60,1),
    RENDTEXRECT1(10,61,2),
    RENDTEXRECT1(11,62,2),
    RENDTEXRECT1(12,63,2),
    RENDTEXRECT1(13,64,2),
    RENDTEXRECT1(10,65,3),
    RENDTEXRECT1(11,66,3),
    RENDTEXRECT1(12,67,3),
    RENDTEXRECT1(13,68,3),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsDPSetRenderMode(G_RM_PASS,G_RM_ZB_OPA_SURF2),
    RENDTEXRECT1(12,53,0),
    RENDTEXRECT1(13,54,0),
    RENDTEXRECT1(14,55,0),
    RENDTEXRECT1(15,56,0),
    RENDTEXRECT1(12,57,1),
    RENDTEXRECT1(13,58,1),
    RENDTEXRECT1(14,59,1),
    RENDTEXRECT1(15,60,1),
    RENDTEXRECT1(12,61,2),
    RENDTEXRECT1(13,62,2),
    RENDTEXRECT1(14,63,2),
    RENDTEXRECT1(15,64,2),
    RENDTEXRECT1(12,65,3),
    RENDTEXRECT1(13,66,3),
    RENDTEXRECT1(14,67,3),
    RENDTEXRECT1(15,68,3),
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_XLU_SURF2),
    RENDTEXRECT1(14,53,0),
    RENDTEXRECT1(15,54,0),
    RENDTEXRECT1(16,55,0),
    RENDTEXRECT1(17,56,0),
    RENDTEXRECT1(14,57,1),
    RENDTEXRECT1(15,58,1),
    RENDTEXRECT1(16,59,1),
    RENDTEXRECT1(17,60,1),
    RENDTEXRECT1(14,61,2),
    RENDTEXRECT1(15,62,2),
    RENDTEXRECT1(16,63,2),
    RENDTEXRECT1(17,64,2),
    RENDTEXRECT1(14,65,3),
    RENDTEXRECT1(15,66,3),
    RENDTEXRECT1(16,67,3),
    RENDTEXRECT1(17,68,3),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_ZB_XLU_SURF2),
    RENDTEXRECT1(16,53,0),
    RENDTEXRECT1(17,54,0),
    RENDTEXRECT1(18,55,0),
    RENDTEXRECT1(19,56,0),
    RENDTEXRECT1(16,57,1),
    RENDTEXRECT1(17,58,1),
    RENDTEXRECT1(18,59,1),
    RENDTEXRECT1(19,60,1),
    RENDTEXRECT1(16,61,2),
    RENDTEXRECT1(17,62,2),
    RENDTEXRECT1(18,63,2),
    RENDTEXRECT1(19,64,2),
    RENDTEXRECT1(16,65,3),
    RENDTEXRECT1(17,66,3),
    RENDTEXRECT1(18,67,3),
    RENDTEXRECT1(19,68,3),

/*
 * 16 bit texture load alignment
 */
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetCycleType(G_CYC_COPY),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),

#ifdef BAD_ALIGNMENT_TEST
    gsDPLoadTextureBlock(&rainbow16[1], G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    DEFTEXRECT1(10,28,0),
    gsDPLoadTextureBlock(&rainbow16[2], G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    DEFTEXRECT1(10,29,0),
    gsDPLoadTextureBlock(&rainbow16[3], G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    DEFTEXRECT1(10,30,0),
#endif /* BAD_ALIGNMENT_TEST */
    gsDPLoadTextureBlock(&rainbow16[4], G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    DEFTEXRECT1(10,31,0),
#ifdef BAD_ALIGNMENT_TEST
    gsDPLoadTextureBlock(&rainbow16[5], G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    DEFTEXRECT1(15,28,0),
    gsDPLoadTextureBlock(&rainbow16[6], G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    DEFTEXRECT1(15,29,0),
    gsDPLoadTextureBlock(&rainbow16[7], G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    DEFTEXRECT1(15,30,0),
#endif /* BAD_ALIGNMENT_TEST */
    gsDPLoadTextureBlock(&rainbow16[8], G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    DEFTEXRECT1(15,31,0),

#ifdef BAD_ALIGNMENT_TEST
/*
 * 4 bit textures 
 */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE), 
    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),

    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPPipeSync(),

    gsDPLoadTextureBlock_4b(rainbow4, G_IM_FMT_CI, 16, 1, 0,
                         G_TX_MIRROR, 0,
                         5, 0, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX4RECT9(30,10,0),
    gsDPTileSync(),
    gsDPLoadTextureBlock_4b(&rainbow4[1], G_IM_FMT_CI, 16, 1, 0,
                         G_TX_MIRROR, 0,
                         5, 0, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX4RECT9(30,12,0),
    gsDPTileSync(),
    gsDPLoadTextureBlock_4b(&rainbow4[2], G_IM_FMT_CI, 16, 1, 0,
                         G_TX_MIRROR, 0,
                         5, 0, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX4RECT9(30,14,0),
    gsDPTileSync(),
    gsDPLoadTextureBlock_4b(&rainbow4[3], G_IM_FMT_CI, 16, 1, 0,
                         G_TX_MIRROR, 0,
                         5, 0, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX4RECT9(30,16,0),
    gsDPTileSync(),
    gsDPLoadTextureBlock_4b(&rainbow4[4], G_IM_FMT_CI, 16, 1, 0,
                         G_TX_MIRROR, 0,
                         5, 0, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX4RECT9(30,18,0),
    gsDPTileSync(),
    gsDPLoadTextureBlock_4b(&rainbow4[5], G_IM_FMT_CI, 16, 1, 0,
                         G_TX_MIRROR, 0,
                         5, 0, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX4RECT9(30,20,0),
    gsDPTileSync(),
    gsDPLoadTextureBlock_4b(&rainbow4[6], G_IM_FMT_CI, 16, 1, 0,
                         G_TX_MIRROR, 0,
                         5, 0, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX4RECT9(30,22,0),
    gsDPTileSync(),
    gsDPLoadTextureBlock_4b(&rainbow4[7], G_IM_FMT_CI, 16, 1, 0,
                         G_TX_MIRROR, 0,
                         5, 0, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX4RECT9(30,24,0),
    gsDPTileSync(),

/*
 * 8 bit textures
 */

    gsDPLoadTextureBlock(rainbow8, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX8RECT9(40,10,0),
    gsDPLoadTextureBlock(&rainbow8[1], G_IM_FMT_CI, G_IM_SIZ_8b, 16, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX8RECT9(40,12,0),
    gsDPLoadTextureBlock(&rainbow8[2], G_IM_FMT_CI, G_IM_SIZ_8b, 16, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX8RECT9(40,14,0),
    gsDPLoadTextureBlock(&rainbow8[3], G_IM_FMT_CI, G_IM_SIZ_8b, 16, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX8RECT9(40,16,0),
    gsDPLoadTextureBlock(&rainbow8[4], G_IM_FMT_CI, G_IM_SIZ_8b, 16, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX8RECT9(40,18,0),
    gsDPLoadTextureBlock(&rainbow8[5], G_IM_FMT_CI, G_IM_SIZ_8b, 16, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX8RECT9(40,20,0),
    gsDPLoadTextureBlock(&rainbow8[6], G_IM_FMT_CI, G_IM_SIZ_8b, 16, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX8RECT9(40,22,0),
    gsDPLoadTextureBlock(&rainbow8[7], G_IM_FMT_CI, G_IM_SIZ_8b, 16, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX8RECT9(40,24,0),

/*
 * 32 bit textures
 */
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),

    gsDPLoadTextureBlock(rainbow32, G_IM_FMT_RGBA, G_IM_SIZ_32b, 9, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX32RECT9(50,10,0),
    gsDPLoadTextureBlock(&rainbow32[1], G_IM_FMT_RGBA, G_IM_SIZ_32b, 9, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX32RECT9(50,12,0),
    gsDPLoadTextureBlock(&rainbow32[2], G_IM_FMT_RGBA, G_IM_SIZ_32b, 9, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX32RECT9(50,14,0),
    gsDPLoadTextureBlock(&rainbow32[3], G_IM_FMT_RGBA, G_IM_SIZ_32b, 9, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX32RECT9(50,16,0),
    gsDPLoadTextureBlock(&rainbow32[4], G_IM_FMT_RGBA, G_IM_SIZ_32b, 9, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX32RECT9(50,18,0),
    gsDPLoadTextureBlock(&rainbow32[5], G_IM_FMT_RGBA, G_IM_SIZ_32b, 9, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX32RECT9(50,20,0),
    gsDPLoadTextureBlock(&rainbow32[6], G_IM_FMT_RGBA, G_IM_SIZ_32b, 9, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX32RECT9(50,22,0),
    gsDPLoadTextureBlock(&rainbow32[7], G_IM_FMT_RGBA, G_IM_SIZ_32b, 9, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    RENDTEX32RECT9(50,24,0),
#endif /*BAD_ALIGNMENT_TEST */

/*
 * Load Tile
 */

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE), 
    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),

    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 60<<2, 10<<2, 73<<2, 23<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 35<<2, 55<<2, 45<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 9, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 60<<2, 35<<2, 70<<2, 45<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 50<<2, 55<<2, 60<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         1, 0, 11, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 61<<2, 50<<2, 71<<2, 60<<2,
				    G_TX_RENDERTILE,1<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 65<<2, 55<<2, 75<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         2, 0, 12, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 62<<2, 65<<2, 72<<2, 75<<2,
				    G_TX_RENDERTILE,2<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 80<<2, 55<<2, 90<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         3, 0, 13, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 63<<2, 80<<2, 73<<2, 90<<2,
				    G_TX_RENDERTILE,3<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 95<<2, 55<<2, 105<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 1, 10, 11, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 60<<2, 96<<2, 70<<2, 106<<2,
				    G_TX_RENDERTILE,0<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 110<<2, 55<<2, 120<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         1, 1, 11, 11, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 61<<2, 111<<2, 71<<2, 121<<2,
				    G_TX_RENDERTILE,1<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 125<<2, 55<<2, 135<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         2, 1, 12, 11, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 62<<2, 126<<2, 72<<2, 136<<2,
				    G_TX_RENDERTILE,2<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 140<<2, 55<<2, 150<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         3, 1, 13, 11, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 63<<2, 141<<2, 73<<2, 151<<2,
				    G_TX_RENDERTILE,3<<5,1<<5,1<<10,1<<10),


/*
 * 8 bit LoadTile
 */

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE), 


/*	replaced by LoadTLUT below (which does not work) */
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),


/*    gsDPLoadTLUT(16, 256,rain_tlutRGBA),*/

    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 90<<2, 10<<2, 103<<2, 23<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),


    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 35<<2, 85<<2, 45<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 9, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 90<<2, 35<<2,100<<2, 45<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 50<<2, 85<<2, 60<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         1, 0, 10, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 91<<2, 50<<2,101<<2, 60<<2,
				    G_TX_RENDERTILE,1<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 65<<2, 85<<2, 75<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         2, 0, 11, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 92<<2, 65<<2,102<<2, 75<<2,
				    G_TX_RENDERTILE,2<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 80<<2, 85<<2, 90<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         3, 0, 12, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 93<<2, 80<<2,103<<2, 90<<2,
				    G_TX_RENDERTILE,3<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 95<<2, 85<<2, 105<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 1, 9, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 90<<2, 96<<2,100<<2, 106<<2,
				    G_TX_RENDERTILE,0<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 110<<2, 85<<2, 120<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_RGBA, G_IM_SIZ_8b, 13, 13,
                         1, 1, 10, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 91<<2, 111<<2,101<<2, 121<<2,
				    G_TX_RENDERTILE,1<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 125<<2, 85<<2, 135<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_RGBA, G_IM_SIZ_8b, 13, 13,
                         2, 1, 11, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 92<<2, 126<<2,102<<2, 136<<2,
				    G_TX_RENDERTILE,2<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 140<<2, 85<<2, 150<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_RGBA, G_IM_SIZ_8b, 13, 13,
                         3, 1, 12, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 93<<2, 141<<2,103<<2, 151<<2,
				    G_TX_RENDERTILE,3<<5,1<<5,1<<10,1<<10),


/*
 * 4 bit LoadTile
 */

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE), 


/*	replaced by LoadTLUT below (which does not work) */
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),


/*    gsDPLoadTLUT(16, 256,rain_tlutRGBA),*/

    gsDPLoadSync(),

    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 120<<2, 10<<2, 133<<2, 23<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 12, 12, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 35<<2,115<<2, 45<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_CI, 14, 14,
                         0, 0, 9, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(120<<2, 35<<2,130<<2, 45<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 50<<2,115<<2, 60<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_CI, 14, 14,
                         1, 0, 10, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(121<<2, 50<<2,131<<2, 60<<2,
				    G_TX_RENDERTILE,1<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 65<<2,115<<2, 75<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_CI, 14, 14,
                         2, 0, 11, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(122<<2, 65<<2,132<<2, 75<<2,
				    G_TX_RENDERTILE,2<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 80<<2,115<<2, 90<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_CI, 14, 14,
                         3, 0, 12, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(123<<2, 80<<2,133<<2, 90<<2,
				    G_TX_RENDERTILE,3<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 95<<2,115<<2, 105<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_CI, 14, 14,
                         0, 1, 9, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(120<<2, 96<<2,130<<2, 106<<2,
				    G_TX_RENDERTILE,0<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 110<<2,115<<2, 120<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_RGBA, 14, 14,
                         1, 1, 10, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(121<<2, 111<<2,131<<2, 121<<2,
				    G_TX_RENDERTILE,1<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 125<<2,115<<2, 135<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_RGBA, 14, 14,
                         2, 1, 11, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(122<<2, 126<<2,132<<2, 136<<2,
				    G_TX_RENDERTILE,2<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 140<<2,115<<2, 150<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_RGBA, 14, 14,
                         3, 1, 12, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(123<<2, 141<<2,133<<2, 151<<2,
				    G_TX_RENDERTILE,3<<5,1<<5,1<<10,1<<10),


/*
 * Loads in different modes
 */ 

    gsDPPipeSync(),
    gsDPSetDepthSource(G_ZS_PRIM),
    gsDPSetPrimColor(150, 205, 0x00, 0xff, 0x00, 128),
    gsDPSetPrimDepth(0x400,0x400),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_ZB_OPA_SURF,G_RM_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(138<<2,  8<<2,201<<2, 42<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write c (1)*/
    gsDPPipeSync(),
    gsDPSetPrimColor(150, 205, 0xFF, 0x00, 0x00, 128),
    gsDPSetPrimDepth(0x300,0x400),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 10<<2,149<<2, 12<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 10<<2,159<<2, 12<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 10<<2,169<<2, 12<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 10<<2,179<<2, 12<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 10<<2,189<<2, 12<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 10<<2,199<<2, 12<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write c read c (2)*/
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF,G_RM_XLU_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 14<<2,149<<2, 16<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 14<<2,159<<2, 16<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 14<<2,169<<2, 16<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_XLU_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 14<<2,179<<2, 16<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 14<<2,189<<2, 16<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),

    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 14<<2,199<<2, 16<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write c read z (3)*/
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_ZB_OPA_DECAL,G_RM_ZB_OPA_DECAL2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 18<<2,149<<2, 20<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 18<<2,159<<2, 20<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 18<<2,169<<2, 20<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_ZB_OPA_DECAL2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 18<<2,179<<2, 20<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 18<<2,189<<2, 20<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 18<<2,199<<2, 20<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write c read cz (4)*/
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_ZB_XLU_DECAL,G_RM_ZB_XLU_DECAL2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 22<<2,149<<2, 24<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 22<<2,159<<2, 24<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 22<<2,169<<2, 24<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_ZB_XLU_DECAL2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 22<<2,179<<2, 24<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 22<<2,189<<2, 24<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 22<<2,199<<2, 24<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write cz read c (5) (NOT A REAL MODE)*/
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF | Z_UPD,G_RM_AA_OPA_SURF2 | Z_UPD),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 26<<2,149<<2, 28<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 26<<2,159<<2, 28<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 26<<2,169<<2, 28<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_OPA_SURF2 | Z_UPD),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 26<<2,179<<2, 28<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 26<<2,189<<2, 28<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 26<<2,199<<2, 28<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write cz read z (6)*/
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_ZB_OPA_SURF,G_RM_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 30<<2,149<<2, 32<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 30<<2,159<<2, 32<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 30<<2,169<<2, 32<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 30<<2,179<<2, 32<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 30<<2,189<<2, 32<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 30<<2,199<<2, 32<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write cz read cz (7)*/
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF,G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 34<<2,149<<2, 36<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 34<<2,159<<2, 36<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 34<<2,169<<2, 36<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 34<<2,179<<2, 36<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 34<<2,189<<2, 36<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 34<<2,199<<2, 36<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write cz (8) ( NOT A REAL MODE) */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_OPA_SURF | Z_UPD,G_RM_OPA_SURF2 | Z_UPD),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 38<<2,149<<2, 40<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 38<<2,159<<2, 40<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 38<<2,169<<2, 40<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_ZB_OPA_SURF2 | Z_UPD),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 38<<2,179<<2, 40<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 38<<2,189<<2, 40<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 38<<2,199<<2, 40<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),



    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPEndDisplayList(),
};
/* end of case 17 */

/*
 * Test 18, Frame 18:
 * 1 clipped triangle
 *
 */
static Vtx tri_out_old[3] = {
        { 0,   -40, -1200, 0, ( 0 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        { 0,    40, -1200, 0, (31 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff   },
        { 1000,  0, -1300, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0xff   },
};
static Vtx tri_out[3] = {
        { 0,   -105, -1200, 0, ( 0 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        { -105,    105, -1200, 0, (31 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff   },
        { 105,  0, -1300, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0xff   },
};
Gfx rdpms_cliptri[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsSPSetGeometryMode(G_ZBUFFER),


    /* set attributes, to be used as colors for rects */

    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    /*gsDPSetConvert(45, 114, 250, 77, 66, 69), */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),


    gsSPVertex(&tri_out, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),

    gsSPEndDisplayList(),
};
/* end of case 18 */

/*
 * Test 19, Frame 19:
 * 
 *
 */
Gfx rdpms_txalign32[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPClearGeometryMode(G_SHADE),


    /* set attributes, to be used as colors for rects */


    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureFilter(G_TF_POINT),




    gsDPSetCycleType(G_CYC_1CYCLE), 
    gsDPLoadTextureTile(roundrain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 96, 4,
                         31, 0, 64, 3, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle(138<<2,  44<<2,172<<2, 48<<2, G_TX_RENDERTILE,31<<5,0<<5,1<<10,1<<10),
    gsDPTileSync(),
    gsDPLoadTextureTile(roundrain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20,
                         0, 0, 19, 19, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(138<<2,  50<<2,158<<2, 70<<2, G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),


    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPLoadTextureBlock(rainbow16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 1, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),




    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE), 
    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    RENDTEXRECT1(10,33,0),
    RENDTEXRECT1(11,34,0),
    RENDTEXRECT1(12,35,0),
    RENDTEXRECT1(13,36,0),
    RENDTEXRECT1(10,37,1),
    RENDTEXRECT1(11,38,1),
    RENDTEXRECT1(12,39,1),
    RENDTEXRECT1(13,40,1),
    RENDTEXRECT1(10,41,2),
    RENDTEXRECT1(11,42,2),
    RENDTEXRECT1(12,43,2),
    RENDTEXRECT1(13,44,2),
    RENDTEXRECT1(10,45,3),
    RENDTEXRECT1(11,46,3),
    RENDTEXRECT1(12,47,3),
    RENDTEXRECT1(13,48,3),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsDPSetRenderMode(G_RM_ZB_OPA_SURF,G_RM_ZB_OPA_SURF2),
    RENDTEXRECT1(12,33,0),
    RENDTEXRECT1(13,34,0),
    RENDTEXRECT1(14,35,0),
    RENDTEXRECT1(15,36,0),
    RENDTEXRECT1(12,37,1),
    RENDTEXRECT1(13,38,1),
    RENDTEXRECT1(14,39,1),
    RENDTEXRECT1(15,40,1),
    RENDTEXRECT1(12,41,2),
    RENDTEXRECT1(13,42,2),
    RENDTEXRECT1(14,43,2),
    RENDTEXRECT1(15,44,2),
    RENDTEXRECT1(12,45,3),
    RENDTEXRECT1(13,46,3),
    RENDTEXRECT1(14,47,3),
    RENDTEXRECT1(15,48,3),
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF,G_RM_AA_XLU_SURF2),
    RENDTEXRECT1(14,33,0),
    RENDTEXRECT1(15,34,0),
    RENDTEXRECT1(16,35,0),
    RENDTEXRECT1(17,36,0),
    RENDTEXRECT1(14,37,1),
    RENDTEXRECT1(15,38,1),
    RENDTEXRECT1(16,39,1),
    RENDTEXRECT1(17,40,1),
    RENDTEXRECT1(14,41,2),
    RENDTEXRECT1(15,42,2),
    RENDTEXRECT1(16,43,2),
    RENDTEXRECT1(17,44,2),
    RENDTEXRECT1(14,45,3),
    RENDTEXRECT1(15,46,3),
    RENDTEXRECT1(16,47,3),
    RENDTEXRECT1(17,48,3),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF,G_RM_AA_ZB_XLU_SURF2),
    RENDTEXRECT1(16,33,0),
    RENDTEXRECT1(17,34,0),
    RENDTEXRECT1(18,35,0),
    RENDTEXRECT1(19,36,0),
    RENDTEXRECT1(16,37,1),
    RENDTEXRECT1(17,38,1),
    RENDTEXRECT1(18,39,1),
    RENDTEXRECT1(19,40,1),
    RENDTEXRECT1(16,41,2),
    RENDTEXRECT1(17,42,2),
    RENDTEXRECT1(18,43,2),
    RENDTEXRECT1(19,44,2),
    RENDTEXRECT1(16,45,3),
    RENDTEXRECT1(17,46,3),
    RENDTEXRECT1(18,47,3),
    RENDTEXRECT1(19,48,3),

    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetCycleType(G_CYC_2CYCLE), 
    gsDPSetRenderMode(G_RM_PASS,G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    RENDTEXRECT1(10,53,0),
    RENDTEXRECT1(11,54,0),
    RENDTEXRECT1(12,55,0),
    RENDTEXRECT1(13,56,0),
    RENDTEXRECT1(10,57,1),
    RENDTEXRECT1(11,58,1),
    RENDTEXRECT1(12,59,1),
    RENDTEXRECT1(13,60,1),
    RENDTEXRECT1(10,61,2),
    RENDTEXRECT1(11,62,2),
    RENDTEXRECT1(12,63,2),
    RENDTEXRECT1(13,64,2),
    RENDTEXRECT1(10,65,3),
    RENDTEXRECT1(11,66,3),
    RENDTEXRECT1(12,67,3),
    RENDTEXRECT1(13,68,3),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsDPSetRenderMode(G_RM_PASS,G_RM_ZB_OPA_SURF2),
    RENDTEXRECT1(12,53,0),
    RENDTEXRECT1(13,54,0),
    RENDTEXRECT1(14,55,0),
    RENDTEXRECT1(15,56,0),
    RENDTEXRECT1(12,57,1),
    RENDTEXRECT1(13,58,1),
    RENDTEXRECT1(14,59,1),
    RENDTEXRECT1(15,60,1),
    RENDTEXRECT1(12,61,2),
    RENDTEXRECT1(13,62,2),
    RENDTEXRECT1(14,63,2),
    RENDTEXRECT1(15,64,2),
    RENDTEXRECT1(12,65,3),
    RENDTEXRECT1(13,66,3),
    RENDTEXRECT1(14,67,3),
    RENDTEXRECT1(15,68,3),
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_XLU_SURF2),
    RENDTEXRECT1(14,53,0),
    RENDTEXRECT1(15,54,0),
    RENDTEXRECT1(16,55,0),
    RENDTEXRECT1(17,56,0),
    RENDTEXRECT1(14,57,1),
    RENDTEXRECT1(15,58,1),
    RENDTEXRECT1(16,59,1),
    RENDTEXRECT1(17,60,1),
    RENDTEXRECT1(14,61,2),
    RENDTEXRECT1(15,62,2),
    RENDTEXRECT1(16,63,2),
    RENDTEXRECT1(17,64,2),
    RENDTEXRECT1(14,65,3),
    RENDTEXRECT1(15,66,3),
    RENDTEXRECT1(16,67,3),
    RENDTEXRECT1(17,68,3),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_ZB_XLU_SURF2),
    RENDTEXRECT1(16,53,0),
    RENDTEXRECT1(17,54,0),
    RENDTEXRECT1(18,55,0),
    RENDTEXRECT1(19,56,0),
    RENDTEXRECT1(16,57,1),
    RENDTEXRECT1(17,58,1),
    RENDTEXRECT1(18,59,1),
    RENDTEXRECT1(19,60,1),
    RENDTEXRECT1(16,61,2),
    RENDTEXRECT1(17,62,2),
    RENDTEXRECT1(18,63,2),
    RENDTEXRECT1(19,64,2),
    RENDTEXRECT1(16,65,3),
    RENDTEXRECT1(17,66,3),
    RENDTEXRECT1(18,67,3),
    RENDTEXRECT1(19,68,3),

/*
 * 16 bit texture load alignment
 */
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
/*
 * 4 bit textures 
 */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE), 
    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),

/*
 * Load Tile
 */

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE), 
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),

    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 60<<2, 10<<2, 73<<2, 23<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),


    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 35<<2, 55<<2, 45<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 9, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 60<<2, 35<<2, 70<<2, 45<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 50<<2, 55<<2, 60<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         1, 0, 11, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 61<<2, 50<<2, 71<<2, 60<<2,
				    G_TX_RENDERTILE,1<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 65<<2, 55<<2, 75<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         2, 0, 12, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 62<<2, 65<<2, 72<<2, 75<<2,
				    G_TX_RENDERTILE,2<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 80<<2, 55<<2, 90<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         3, 0, 13, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 63<<2, 80<<2, 73<<2, 90<<2,
				    G_TX_RENDERTILE,3<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 95<<2, 55<<2, 105<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 1, 10, 11, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 60<<2, 96<<2, 70<<2, 106<<2,
				    G_TX_RENDERTILE,0<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 110<<2, 55<<2, 120<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         1, 1, 11, 11, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 61<<2, 111<<2, 71<<2, 121<<2,
				    G_TX_RENDERTILE,1<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 125<<2, 55<<2, 135<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         2, 1, 12, 11, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 62<<2, 126<<2, 72<<2, 136<<2,
				    G_TX_RENDERTILE,2<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureBlock(black16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 45<<2, 140<<2, 55<<2, 150<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         3, 1, 13, 11, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 63<<2, 141<<2, 73<<2, 151<<2,
				    G_TX_RENDERTILE,3<<5,1<<5,1<<10,1<<10),


/*
 * 8 bit LoadTile
 */

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE), 


/*	replaced by LoadTLUT below (which does not work) */
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),


/*    gsDPLoadTLUT(16, 256,rain_tlutRGBA),*/

    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 90<<2, 10<<2, 103<<2, 23<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),


    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 35<<2, 85<<2, 45<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 9, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 90<<2, 35<<2,100<<2, 45<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 50<<2, 85<<2, 60<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         1, 0, 10, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 91<<2, 50<<2,101<<2, 60<<2,
				    G_TX_RENDERTILE,1<<5,0<<5,1<<10,1<<10) ,
    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 65<<2, 85<<2, 75<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         2, 0, 11, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 92<<2, 65<<2,102<<2, 75<<2,
				    G_TX_RENDERTILE,2<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 80<<2, 85<<2, 90<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         3, 0, 12, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 93<<2, 80<<2,103<<2, 90<<2,
				    G_TX_RENDERTILE,3<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 95<<2, 85<<2, 105<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 1, 9, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 90<<2, 96<<2,100<<2, 106<<2,
				    G_TX_RENDERTILE,0<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 110<<2, 85<<2, 120<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_RGBA, G_IM_SIZ_8b, 13, 13,
                         1, 1, 10, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 91<<2, 111<<2,101<<2, 121<<2,
				    G_TX_RENDERTILE,1<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 125<<2, 85<<2, 135<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_RGBA, G_IM_SIZ_8b, 13, 13,
                         2, 1, 11, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 92<<2, 126<<2,102<<2, 136<<2,
				    G_TX_RENDERTILE,2<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureTile(black16, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 75<<2, 140<<2, 85<<2, 150<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_RGBA, G_IM_SIZ_8b, 13, 13,
                         3, 1, 12, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 93<<2, 141<<2,103<<2, 151<<2,
				    G_TX_RENDERTILE,3<<5,1<<5,1<<10,1<<10),


/*
 * 4 bit LoadTile
 */

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE), 


/*	replaced by LoadTLUT below (which does not work) */
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),


/*    gsDPLoadTLUT(16, 256,rain_tlutRGBA),*/

    gsDPLoadSync(),

    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle( 120<<2, 10<<2, 133<<2, 23<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 12, 12, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 35<<2,115<<2, 45<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_CI, 14, 14,
                         0, 0, 9, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(120<<2, 35<<2,130<<2, 45<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10) ,
    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 50<<2,115<<2, 60<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_CI, 14, 14,
                         1, 0, 10, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(121<<2, 50<<2,131<<2, 60<<2,
				    G_TX_RENDERTILE,1<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 65<<2,115<<2, 75<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_CI, 14, 14,
                         2, 0, 11, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(122<<2, 65<<2,132<<2, 75<<2,
				    G_TX_RENDERTILE,2<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 80<<2,115<<2, 90<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_CI, 14, 14,
                         3, 0, 12, 9, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(123<<2, 80<<2,133<<2, 90<<2,
				    G_TX_RENDERTILE,3<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 95<<2,115<<2, 105<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_CI, 14, 14,
                         0, 1, 9, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(120<<2, 96<<2,130<<2, 106<<2,
				    G_TX_RENDERTILE,0<<5,1<<5,1<<10,1<<10) ,
    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 110<<2,115<<2, 120<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_RGBA, 14, 14,
                         1, 1, 10, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(121<<2, 111<<2,131<<2, 121<<2,
				    G_TX_RENDERTILE,1<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 125<<2,115<<2, 135<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_RGBA, 14, 14,
                         2, 1, 11, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(122<<2, 126<<2,132<<2, 136<<2,
				    G_TX_RENDERTILE,2<<5,1<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(black16, G_IM_FMT_CI, 14, 14,
                         0, 0, 13, 13, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(105<<2, 140<<2,115<<2, 150<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),
    gsDPLoadTextureTile_4b(round13rain4, G_IM_FMT_RGBA, 14, 14,
                         3, 1, 12, 10, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(123<<2, 141<<2,133<<2, 151<<2,
				    G_TX_RENDERTILE,3<<5,1<<5,1<<10,1<<10),


/*
 * Loads in different modes
 */ 

    gsDPPipeSync(),
    gsDPSetDepthSource(G_ZS_PRIM),
    gsDPSetPrimColor(150, 205, 0x00, 0xff, 0x00, 128),
    gsDPSetPrimDepth(0x400,0x400),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_ZB_OPA_SURF,G_RM_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(138<<2,  8<<2,201<<2, 42<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write c (1)*/
    gsDPPipeSync(),
    gsDPSetPrimColor(150, 205, 0xFF, 0x00, 0x00, 128),
    gsDPSetPrimDepth(0x300,0x400),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 10<<2,149<<2, 12<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 10<<2,159<<2, 12<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 10<<2,169<<2, 12<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 10<<2,179<<2, 12<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 10<<2,189<<2, 12<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 10<<2,199<<2, 12<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write c read c (2)*/
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF,G_RM_XLU_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 14<<2,149<<2, 16<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 14<<2,159<<2, 16<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10) ,

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 14<<2,169<<2, 16<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_XLU_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 14<<2,179<<2, 16<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 14<<2,189<<2, 16<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),

    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 14<<2,199<<2, 16<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write c read z (3)*/
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_ZB_OPA_DECAL,G_RM_ZB_OPA_DECAL2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 18<<2,149<<2, 20<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 18<<2,159<<2, 20<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 18<<2,169<<2, 20<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_ZB_OPA_DECAL2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 18<<2,179<<2, 20<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 18<<2,189<<2, 20<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 18<<2,199<<2, 20<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write c read cz (4)*/
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_ZB_XLU_DECAL,G_RM_ZB_XLU_DECAL2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 22<<2,149<<2, 24<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 22<<2,159<<2, 24<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 22<<2,169<<2, 24<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_ZB_XLU_DECAL2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 22<<2,179<<2, 24<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 22<<2,189<<2, 24<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 22<<2,199<<2, 24<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write cz read c (5) (NOT A REAL MODE)*/
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF | Z_UPD,G_RM_AA_OPA_SURF2 | Z_UPD),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 26<<2,149<<2, 28<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 26<<2,159<<2, 28<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 26<<2,169<<2, 28<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_OPA_SURF2 | Z_UPD),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 26<<2,179<<2, 28<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 26<<2,189<<2, 28<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 26<<2,199<<2, 28<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write cz read z (6)*/
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_ZB_OPA_SURF,G_RM_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 30<<2,149<<2, 32<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10) ,

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 30<<2,159<<2, 32<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 30<<2,169<<2, 32<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 30<<2,179<<2, 32<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 30<<2,189<<2, 32<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 30<<2,199<<2, 32<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10) ,

/* write cz read cz (7)*/
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF,G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 34<<2,149<<2, 36<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 34<<2,159<<2, 36<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 34<<2,169<<2, 36<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 34<<2,179<<2, 36<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 34<<2,189<<2, 36<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 34<<2,199<<2, 36<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

/* write cz (8) ( NOT A REAL MODE) */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_OPA_SURF | Z_UPD,G_RM_OPA_SURF2 | Z_UPD),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(140<<2, 38<<2,149<<2, 40<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(150<<2, 38<<2,159<<2, 40<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(160<<2, 38<<2,169<<2, 40<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_ZB_OPA_SURF2 | Z_UPD),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineLERP (0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE, 0,0,0,PRIMITIVE),
    gsSPTextureRectangle(170<<2, 38<<2,179<<2, 40<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),

    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureTile(round13rain16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(180<<2, 38<<2,189<<2, 40<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10) ,

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    _gsDPLoadTextureBlock(rain_tlutRGBA, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, 0, 0, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTextureTile(round13rain8, G_IM_FMT_CI, G_IM_SIZ_8b, 13, 13,
                         0, 0, 8, 2, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadSync(),
    gsSPTextureRectangle(190<<2, 38<<2,199<<2, 40<<2,
				    G_TX_RENDERTILE,0<<5,0<<5,1<<10,1<<10),



    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPEndDisplayList(),
};
/* end of case 19 */

/*
 * Test 20 
 * NOTE: Dither only works with the verilog memspan
 * Color dither: 1 and 2-cycle modes
 * -Ashoks
 */

static Vtx strip0[4] =  {
        { -256,  102, 110, 0, ( 0 << 6), ( 0 << 6), 0x0, 0x0, 0x0, 0xff
},
        { 256,  102, 110, 0, (31 << 6), ( 0 << 6), 0x40, 0x00, 0x00, 0xff},
        { 256, -18, 110, 0, (31 << 6), (31 << 6), 0x00, 0x40, 0x00, 0xff
},
        { -256, -18, 110, 0, ( 0 << 6), (31 << 6), 0x0, 0x0, 0x0, 0xff
},
};

static Vtx strip1[4] =  {
        { -256, -38, 90, 0, ( 0 << 6), ( 0 << 6), 0x0, 0x0, 0x0, 0xff
},
        {  256, -38, 90, 0, (31 << 6), ( 0 << 6), 0x40, 0x00, 0x00, 0xff
},
        {  256, -158, 90, 0, (31 << 6), (31 << 6), 0x00, 0x40, 0x00, 0xff
},
        { -256, -158, 90, 0, ( 0 << 6), (31 << 6), 0x0, 0x0, 0x0, 0xff
},
};

Gfx rdpms_ditherColor[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsSPClearGeometryMode(G_CULL_BACK),

    gsDPSetColorDither(G_CD_MAGICSQ),

    /* single cycle */

    gsDPSetRenderMode(G_RM_AA_OPA_SURF,G_RM_AA_OPA_SURF2),

    gsSPVertex(&strip0, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsDPPipeSync(),

    /* two cycle */

    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_ZB_OPA_SURF2),

    gsSPVertex(&strip1, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsDPPipeSync(),


    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF),
    gsDPFullSync(),
    gsSPEndDisplayList(),
};
/* end of case 20 */

/*
 * Test 21
 * Alpha dither test
 *
 */

static Vtx Astrip[4] =  {
        {        -256,  64, 110, 0, ( 0 << 6), ( 0 << 6), 0xff, 0xff, 0xff, 0x0
},
        {         256,  64, 110, 0, (31 << 6), ( 0 << 6), 0xff, 0xff, 0xff, 0xff
},
        {         256, -64, 110, 0, (31 << 6), (31 << 6), 0xff, 0xff, 0xff, 0xff
},
        {        -256, -64, 110, 0, ( 0 << 6), (31 << 6), 0xff, 0xff, 0xff, 0x0
},
};



Gfx rdpms_ditherAlpha[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_ZB_PCL_SURF2),

    gsDPSetCycleType(G_CYC_1CYCLE),

    gsDPSetBlendColor(0x0,0x0,0x0,0x7f),
    gsDPSetAlphaCompare(G_AC_DITHER),

    gsSPVertex(&Astrip, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsDPPipeSync(),

    gsDPFullSync(),
    gsSPEndDisplayList(),
};
/* end of case 20 */


/*
 * Test 22, Frame 22:
 * Fill mode test cases to hit all possible 
 * cases that straddle two spanlets
 */
Gfx rdpms_exhFill[4*MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),

    gsDPSetCycleType(G_CYC_FILL),

gsDPSetFillColor(0xa801a801),
	gsDPFillRectangle(8,20,8,20),
	gsDPFillRectangle(8,21,9,21),
	gsDPFillRectangle(8,22,10,22),
	gsDPFillRectangle(8,23,11,23),
	gsDPFillRectangle(8,24,12,24),
	gsDPFillRectangle(8,25,13,25),
	gsDPFillRectangle(8,26,14,26),
	gsDPFillRectangle(8,27,15,27),
	gsDPFillRectangle(8,28,16,28),
	gsDPFillRectangle(8,29,17,29),
	gsDPFillRectangle(8,30,18,30),
	gsDPFillRectangle(8,31,19,31),
	gsDPFillRectangle(8,32,20,32),
	gsDPFillRectangle(8,33,21,33),
	gsDPFillRectangle(8,34,22,34),
	gsDPFillRectangle(8,35,23,35),
	gsDPPipeSync(),
gsDPSetFillColor(0x50015001),
	gsDPFillRectangle(9,36,9,36),
	gsDPFillRectangle(9,37,10,37),
	gsDPFillRectangle(9,38,11,38),
	gsDPFillRectangle(9,39,12,39),
	gsDPFillRectangle(9,40,13,40),
	gsDPFillRectangle(9,41,14,41),
	gsDPFillRectangle(9,42,15,42),
	gsDPFillRectangle(9,43,16,43),
	gsDPFillRectangle(9,44,17,44),
	gsDPFillRectangle(9,45,18,45),
	gsDPFillRectangle(9,46,19,46),
	gsDPFillRectangle(9,47,20,47),
	gsDPFillRectangle(9,48,21,48),
	gsDPFillRectangle(9,49,22,49),
	gsDPFillRectangle(9,50,23,50),
	gsDPPipeSync(),
gsDPSetFillColor(0x05410541),
	gsDPFillRectangle(10,51,10,51),
	gsDPFillRectangle(10,52,11,52),
	gsDPFillRectangle(10,53,12,53),
	gsDPFillRectangle(10,54,13,54),
	gsDPFillRectangle(10,55,14,55),
	gsDPFillRectangle(10,56,15,56),
	gsDPFillRectangle(10,57,16,57),
	gsDPFillRectangle(10,58,17,58),
	gsDPFillRectangle(10,59,18,59),
	gsDPFillRectangle(10,60,19,60),
	gsDPFillRectangle(10,61,20,61),
	gsDPFillRectangle(10,62,21,62),
	gsDPFillRectangle(10,63,22,63),
	gsDPFillRectangle(10,64,23,64),
	gsDPPipeSync(),
gsDPSetFillColor(0x02810281),
	gsDPFillRectangle(11,65,11,65),
	gsDPFillRectangle(11,66,12,66),
	gsDPFillRectangle(11,67,13,67),
	gsDPFillRectangle(11,68,14,68),
	gsDPFillRectangle(11,69,15,69),
	gsDPFillRectangle(11,70,16,70),
	gsDPFillRectangle(11,71,17,71),
	gsDPFillRectangle(11,72,18,72),
	gsDPFillRectangle(11,73,19,73),
	gsDPFillRectangle(11,74,20,74),
	gsDPFillRectangle(11,75,21,75),
	gsDPFillRectangle(11,76,22,76),
	gsDPFillRectangle(11,77,23,77),
	gsDPPipeSync(),
gsDPSetFillColor(0x002b002b),
	gsDPFillRectangle(12,78,12,78),
	gsDPFillRectangle(12,79,13,79),
	gsDPFillRectangle(12,80,14,80),
	gsDPFillRectangle(12,81,15,81),
	gsDPFillRectangle(12,82,16,82),
	gsDPFillRectangle(12,83,17,83),
	gsDPFillRectangle(12,84,18,84),
	gsDPFillRectangle(12,85,19,85),
	gsDPFillRectangle(12,86,20,86),
	gsDPFillRectangle(12,87,21,87),
	gsDPFillRectangle(12,88,22,88),
	gsDPFillRectangle(12,89,23,89),
	gsDPPipeSync(),
gsDPSetFillColor(0x00150015),
	gsDPFillRectangle(13,90,13,90),
	gsDPFillRectangle(13,91,14,91),
	gsDPFillRectangle(13,92,15,92),
	gsDPFillRectangle(13,93,16,93),
	gsDPFillRectangle(13,94,17,94),
	gsDPFillRectangle(13,95,18,95),
	gsDPFillRectangle(13,96,19,96),
	gsDPFillRectangle(13,97,20,97),
	gsDPFillRectangle(13,98,21,98),
	gsDPFillRectangle(13,99,22,99),
	gsDPFillRectangle(13,100,23,100),
	gsDPPipeSync(),
gsDPSetFillColor(0xaaabaaab),
	gsDPFillRectangle(14,101,14,101),
	gsDPFillRectangle(14,102,15,102),
	gsDPFillRectangle(14,103,16,103),
	gsDPFillRectangle(14,104,17,104),
	gsDPFillRectangle(14,105,18,105),
	gsDPFillRectangle(14,106,19,106),
	gsDPFillRectangle(14,107,20,107),
	gsDPFillRectangle(14,108,21,108),
	gsDPFillRectangle(14,109,22,109),
	gsDPFillRectangle(14,110,23,110),
	gsDPPipeSync(),
gsDPSetFillColor(0x55555555),
	gsDPFillRectangle(15,111,15,111),
	gsDPFillRectangle(15,112,16,112),
	gsDPFillRectangle(15,113,17,113),
	gsDPFillRectangle(15,114,18,114),
	gsDPFillRectangle(15,115,19,115),
	gsDPFillRectangle(15,116,20,116),
	gsDPFillRectangle(15,117,21,117),
	gsDPFillRectangle(15,118,22,118),
	gsDPFillRectangle(15,119,23,119),
	gsDPPipeSync(),

    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),

    gsDPSetCycleType(G_CYC_1CYCLE),

    gsDPSetPrimColor(0, 5, 168, 0, 0, 255),
	gsDPFillRectangle(30,20,31,21),
	gsDPFillRectangle(30,21,32,22),
	gsDPFillRectangle(30,22,33,23),
	gsDPFillRectangle(30,23,34,24),
	gsDPFillRectangle(30,24,35,25),
	gsDPFillRectangle(30,25,36,26),
	gsDPFillRectangle(30,26,37,27),
	gsDPFillRectangle(30,27,38,28),
	gsDPFillRectangle(30,28,39,29),
	gsDPFillRectangle(30,29,40,30),
	gsDPFillRectangle(30,30,41,31),
	gsDPFillRectangle(30,31,42,32),
	gsDPFillRectangle(30,32,43,33),
	gsDPFillRectangle(30,33,44,34),
	gsDPFillRectangle(30,34,45,35),
	gsDPFillRectangle(30,35,46,36),
	gsDPPipeSync(),
    gsDPSetPrimColor(0, 5, 80, 0, 0, 255),
	gsDPFillRectangle(31,36,32,37),
	gsDPFillRectangle(31,37,33,38),
	gsDPFillRectangle(31,38,34,39),
	gsDPFillRectangle(31,39,35,40),
	gsDPFillRectangle(31,40,36,41),
	gsDPFillRectangle(31,41,37,42),
	gsDPFillRectangle(31,42,38,43),
	gsDPFillRectangle(31,43,39,44),
	gsDPFillRectangle(31,44,40,45),
	gsDPFillRectangle(31,45,41,46),
	gsDPFillRectangle(31,46,42,47),
	gsDPFillRectangle(31,47,43,48),
	gsDPFillRectangle(31,48,44,49),
	gsDPFillRectangle(31,49,45,50),
	gsDPFillRectangle(31,50,46,51),
	gsDPPipeSync(),
    gsDPSetPrimColor(0, 5, 0, 168, 0, 255),
	gsDPFillRectangle(32,51,33,52),
	gsDPFillRectangle(32,52,34,53),
	gsDPFillRectangle(32,53,35,54),
	gsDPFillRectangle(32,54,36,55),
	gsDPFillRectangle(32,55,37,56),
	gsDPFillRectangle(32,56,38,57),
	gsDPFillRectangle(32,57,39,58),
	gsDPFillRectangle(32,58,40,59),
	gsDPFillRectangle(32,59,41,60),
	gsDPFillRectangle(32,60,42,61),
	gsDPFillRectangle(32,61,43,62),
	gsDPFillRectangle(32,62,44,63),
	gsDPFillRectangle(32,63,45,64),
	gsDPFillRectangle(32,64,46,65),
	gsDPPipeSync(),
    gsDPSetPrimColor(0, 5, 0, 80, 0, 255),
	gsDPFillRectangle(33,65,34,66),
	gsDPFillRectangle(33,66,35,67),
	gsDPFillRectangle(33,67,36,68),
	gsDPFillRectangle(33,68,37,69),
	gsDPFillRectangle(33,69,38,70),
	gsDPFillRectangle(33,70,39,71),
	gsDPFillRectangle(33,71,40,72),
	gsDPFillRectangle(33,72,41,73),
	gsDPFillRectangle(33,73,42,74),
	gsDPFillRectangle(33,74,43,75),
	gsDPFillRectangle(33,75,44,76),
	gsDPFillRectangle(33,76,45,77),
	gsDPFillRectangle(33,77,46,78),
	gsDPPipeSync(),
    gsDPSetPrimColor(0, 5, 0, 0, 168, 255),
	gsDPFillRectangle(34,78,35,79),
	gsDPFillRectangle(34,79,36,80),
	gsDPFillRectangle(34,80,37,81),
	gsDPFillRectangle(34,81,38,82),
	gsDPFillRectangle(34,82,39,83),
	gsDPFillRectangle(34,83,40,84),
	gsDPFillRectangle(34,84,41,85),
	gsDPFillRectangle(34,85,42,86),
	gsDPFillRectangle(34,86,43,87),
	gsDPFillRectangle(34,87,44,88),
	gsDPFillRectangle(34,88,45,89),
	gsDPFillRectangle(34,89,46,90),
	gsDPPipeSync(),
    gsDPSetPrimColor(0, 5, 0, 0, 80, 255),
	gsDPFillRectangle(35,90,36,91),
	gsDPFillRectangle(35,91,37,92),
	gsDPFillRectangle(35,92,38,93),
	gsDPFillRectangle(35,93,39,94),
	gsDPFillRectangle(35,94,40,95),
	gsDPFillRectangle(35,95,41,96),
	gsDPFillRectangle(35,96,42,97),
	gsDPFillRectangle(35,97,43,98),
	gsDPFillRectangle(35,98,44,99),
	gsDPFillRectangle(35,99,45,100),
	gsDPFillRectangle(35,100,46,101),
	gsDPPipeSync(),
    gsDPSetPrimColor(0, 5, 168, 80, 168, 255),
	gsDPFillRectangle(36,101,37,102),
	gsDPFillRectangle(36,102,38,103),
	gsDPFillRectangle(36,103,39,104),
	gsDPFillRectangle(36,104,40,105),
	gsDPFillRectangle(36,105,41,106),
	gsDPFillRectangle(36,106,42,107),
	gsDPFillRectangle(36,107,43,108),
	gsDPFillRectangle(36,108,44,109),
	gsDPFillRectangle(36,109,45,110),
	gsDPFillRectangle(36,110,46,111),
	gsDPPipeSync(),
    gsDPSetPrimColor(0, 5, 80, 168, 80, 255),
	gsDPFillRectangle(37,111,38,112),
	gsDPFillRectangle(37,112,39,113),
	gsDPFillRectangle(37,113,40,114),
	gsDPFillRectangle(37,114,41,115),
	gsDPFillRectangle(37,115,42,116),
	gsDPFillRectangle(37,116,43,117),
	gsDPFillRectangle(37,117,44,118),
	gsDPFillRectangle(37,118,45,119),
	gsDPFillRectangle(37,119,46,120),
	gsDPPipeSync(),


    gsDPSetCycleType(G_CYC_2CYCLE),
gsDPSetPrimColor(0, 5, 168, 0, 0, 255),
	gsDPFillRectangle(52,20,53,21),
	gsDPFillRectangle(52,21,54,22),
	gsDPFillRectangle(52,22,55,23),
	gsDPFillRectangle(52,23,56,24),
	gsDPFillRectangle(52,24,57,25),
	gsDPFillRectangle(52,25,58,26),
	gsDPFillRectangle(52,26,59,27),
	gsDPFillRectangle(52,27,60,28),
	gsDPFillRectangle(52,28,61,29),
	gsDPFillRectangle(52,29,62,30),
	gsDPFillRectangle(52,30,63,31),
	gsDPFillRectangle(52,31,64,32),
	gsDPFillRectangle(52,32,65,33),
	gsDPFillRectangle(52,33,66,34),
	gsDPFillRectangle(52,34,67,35),
	gsDPFillRectangle(52,35,68,36),
	gsDPPipeSync(),
gsDPSetPrimColor(0, 5, 80, 0, 0, 255),
	gsDPFillRectangle(53,36,54,37),
	gsDPFillRectangle(53,37,55,38),
	gsDPFillRectangle(53,38,56,39),
	gsDPFillRectangle(53,39,57,40),
	gsDPFillRectangle(53,40,58,41),
	gsDPFillRectangle(53,41,59,42),
	gsDPFillRectangle(53,42,60,43),
	gsDPFillRectangle(53,43,61,44),
	gsDPFillRectangle(53,44,62,45),
	gsDPFillRectangle(53,45,63,46),
	gsDPFillRectangle(53,46,64,47),
	gsDPFillRectangle(53,47,65,48),
	gsDPFillRectangle(53,48,66,49),
	gsDPFillRectangle(53,49,67,50),
	gsDPFillRectangle(53,50,68,51),
	gsDPPipeSync(),
gsDPSetPrimColor(0, 5, 0, 168, 0, 255),
	gsDPFillRectangle(54,51,55,52),
	gsDPFillRectangle(54,52,56,53),
	gsDPFillRectangle(54,53,57,54),
	gsDPFillRectangle(54,54,58,55),
	gsDPFillRectangle(54,55,59,56),
	gsDPFillRectangle(54,56,60,57),
	gsDPFillRectangle(54,57,61,58),
	gsDPFillRectangle(54,58,62,59),
	gsDPFillRectangle(54,59,63,60),
	gsDPFillRectangle(54,60,64,61),
	gsDPFillRectangle(54,61,65,62),
	gsDPFillRectangle(54,62,66,63),
	gsDPFillRectangle(54,63,67,64),
	gsDPFillRectangle(54,64,68,65),
	gsDPPipeSync(),
gsDPSetPrimColor(0, 5, 0, 80, 0, 255),
	gsDPFillRectangle(55,65,56,66),
	gsDPFillRectangle(55,66,57,67),
	gsDPFillRectangle(55,67,58,68),
	gsDPFillRectangle(55,68,59,69),
	gsDPFillRectangle(55,69,60,70),
	gsDPFillRectangle(55,70,61,71),
	gsDPFillRectangle(55,71,62,72),
	gsDPFillRectangle(55,72,63,73),
	gsDPFillRectangle(55,73,64,74),
	gsDPFillRectangle(55,74,65,75),
	gsDPFillRectangle(55,75,66,76),
	gsDPFillRectangle(55,76,67,77),
	gsDPFillRectangle(55,77,68,78),
	gsDPPipeSync(),
gsDPSetPrimColor(0, 5, 0, 0, 168, 255),
	gsDPFillRectangle(56,78,57,79),
	gsDPFillRectangle(56,79,58,80),
	gsDPFillRectangle(56,80,59,81),
	gsDPFillRectangle(56,81,60,82),
	gsDPFillRectangle(56,82,61,83),
	gsDPFillRectangle(56,83,62,84),
	gsDPFillRectangle(56,84,63,85),
	gsDPFillRectangle(56,85,64,86),
	gsDPFillRectangle(56,86,65,87),
	gsDPFillRectangle(56,87,66,88),
	gsDPFillRectangle(56,88,67,89),
	gsDPFillRectangle(56,89,68,90),
	gsDPPipeSync(),
gsDPSetPrimColor(0, 5, 0, 0, 80, 255),
	gsDPFillRectangle(57,90,58,91),
	gsDPFillRectangle(57,91,59,92),
	gsDPFillRectangle(57,92,60,93),
	gsDPFillRectangle(57,93,61,94),
	gsDPFillRectangle(57,94,62,95),
	gsDPFillRectangle(57,95,63,96),
	gsDPFillRectangle(57,96,64,97),
	gsDPFillRectangle(57,97,65,98),
	gsDPFillRectangle(57,98,66,99),
	gsDPFillRectangle(57,99,67,100),
	gsDPFillRectangle(57,100,68,101),
	gsDPPipeSync(),
gsDPSetPrimColor(0, 5, 168, 80, 168, 255),
	gsDPFillRectangle(58,101,59,102),
	gsDPFillRectangle(58,102,60,103),
	gsDPFillRectangle(58,103,61,104),
	gsDPFillRectangle(58,104,62,105),
	gsDPFillRectangle(58,105,63,106),
	gsDPFillRectangle(58,106,64,107),
	gsDPFillRectangle(58,107,65,108),
	gsDPFillRectangle(58,108,66,109),
	gsDPFillRectangle(58,109,67,110),
	gsDPFillRectangle(58,110,68,111),
	gsDPPipeSync(),
gsDPSetPrimColor(0, 5, 80, 168, 80, 255),
	gsDPFillRectangle(59,111,60,112),
	gsDPFillRectangle(59,112,61,113),
	gsDPFillRectangle(59,113,62,114),
	gsDPFillRectangle(59,114,63,115),
	gsDPFillRectangle(59,115,64,116),
	gsDPFillRectangle(59,116,65,117),
	gsDPFillRectangle(59,117,66,118),
	gsDPFillRectangle(59,118,67,119),
	gsDPFillRectangle(59,119,68,120),
	gsDPPipeSync(),

    gsSPEndDisplayList(),
};
/* end of case 22 */

/*
 * Test 26, Frame 26:
 * some clipped triangles
 *
 */
static Vtx tri_ncl[3] = {
        { 80,  -10, -1200, 0, ( 0 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        { 80,   10, -1200, 0, (31 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff   },
        { 70,    0, -1300, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0xff   },
};
static Vtx tri_cl0[3] = {
        { 1005,-10, -1200, 0, ( 0 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        { 1005, 10, -1200, 0, (31 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff   },
        { 1000,  0, -1300, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0xff   },
};
static Vtx tri_cl1[3] = {
        { 90,  -10, -1200, 0, ( 0 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        { 90,   10, -1200, 0, (31 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff   },
        { 1000,  0, -1300, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0xff   },
};
static Vtx tri_cl1b[3] = {
        { 90,  -40, -1200, 0, ( 0 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        { 90,  -20, -1200, 0, (31 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff   },
        { 1000,-30, -1300, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0xff   },
};
static Vtx tri_cl1c[3] = {
        { 90,  -70, -1200, 0, ( 0 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        { 90,  -50, -1200, 0, (31 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff   },
        { 1000,-60, -1300, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0xff   },
};
static Vtx tri_cl2[3] = {
        {-90,  -10, -1200, 0, ( 0 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        {-90,   10, -1200, 0, (31 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff   },
        {-1000,  0, -1300, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0xff   },
};
static Vtx tri_cl3[3] = {
        {-10,   90, -1200, 0, ( 0 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        { 10,   90, -1200, 0, (31 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff   },
        { 0,  1000, -1300, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0xff   },
};
static Vtx tri_cl4[3] = {
        {-10,  -90, -1200, 0, ( 0 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        { 10,  -90, -1200, 0, (31 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff   },
        { 0, -1000, -1300, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0xff   },
};
static Vtx tri_clm[3] = {
        { 0,   -105, -1200, 0, ( 0 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        { -105, 105, -1200, 0, (31 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff   },
        { 105,  0, -1300, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0xff   },
};
static Vtx tri_broke[3] = {
        /*{ 1000,  0, -1300, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0xff   },*/
        { 99,  9, -1300, 0, (30 << 6), (1 << 6), 0x00, 0x00, 0xff, 0xff   },
        { 90,  -10, -1200, 0, ( 0 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        { 90,   10, -1200, 0, (31 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff   },
};
Gfx rdpms_msdiag1[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsSPSetGeometryMode(G_ZBUFFER),


    /* set attributes, to be used as colors for rects */

    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    /*gsDPSetConvert(45, 114, 250, 77, 66, 69), */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),




    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPLoadTextureBlock(rdpms_RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),




    gsSPVertex(&tri_cl1, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&tri_cl0, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&tri_ncl, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&tri_cl1b, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&tri_cl1c, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&tri_clm, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&tri_cl2, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&tri_cl3, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&tri_cl4, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
/*
    gsSPVertex(&tri_broke, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
*/


    gsSPEndDisplayList(),
};
/* end of case 26 */

/*
 * Test 27, Frame 27:
 * memspan diagnostic tests
 *
 */
static Vtx tri_ms0[3] = {
        { 11, 10, -1000, 0, ( 0 << 6), ( 0 << 6), 0x00, 0x00, 0x00, 0x80   },
        { 11, 11, -1000, 0, (31 << 6), ( 0 << 6), 0x00, 0x00, 0x00, 0x80   },
        { 30, 10, -3000, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0x80   },
};
Gfx rdpms_msdiag2[] = {
    gsDPPipeSync(),

    gsDPSetCycleType(G_CYC_1CYCLE),

    /* set attributes, to be used as colors for rects */
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&tri_ms0, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),

    gsSPEndDisplayList(),
};
/* end of case 27 */

/*
 * Test 28, Frame 28:
 * memspan diagnostic tests
 *
 */
static Vtx tri_ms1[3] = {
        { 11, 10, -1000, 0, ( 0 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        { 11, 12, -2000, 0, (31 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff   },
        { 19, 11, -3000, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0xff   },
};
Gfx rdpms_msdiag3[] = {
    gsDPPipeSync(),

    gsDPSetCycleType(G_CYC_1CYCLE),

    /* set attributes, to be used as colors for rects */
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),


        /* test prim color */
        /* 3 bars: magenta over green over grey, all solid colors */
    gsSPVertex(&tri_ms1, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),

    gsSPEndDisplayList(),
};
/* end of case 28 */

/*
 * Test 29, Frame 29:
 * memspan diagnostic tests
 *
 */
static Vtx tri_ms2[3] = {
        { 11, 10, -1000, 0, ( 0 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        { 11, 11, -1000, 0, (31 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff   },
        { 30, 10, -3000, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0xff, 0xff   },
};
Gfx rdpms_msdiag4[] = {
    gsDPPipeSync(),

    gsDPSetCycleType(G_CYC_1CYCLE),

    /* set attributes, to be used as colors for rects */
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),


        /* test prim color */
        /* 3 bars: magenta over green over grey, all solid colors */
    gsSPVertex(&tri_ms2, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),

    gsSPEndDisplayList(),
};
/* end of case 29 */


/*
 * Test 30, Frame 30:
 * lighting tests
 *
 */
static Vtx tri_lit1a[4] = {
        { -10, -10, 0, 0, ( 0 << 6), ( 0 << 6), 0x00, 0x00, 0x7f, 0xff   },
        { -10,  10, 0, 0, ( 0 << 6), (31 << 6), 0x00, 0x00, 0x7f, 0xff   },
        {  10,  10, 0, 0, (31 << 6), (31 << 6), 0x00, 0x00, 0x7f, 0xff   },
        {  10, -10, 0, 0, (31 << 6), ( 0 << 6), 0x00, 0x00, 0x7f, 0xff   },
};
static Vtx tri_lit1b[4] = {
        { -30, -10, 0, 0, ( 0 << 6), ( 0 << 6), 0xa0, 0x00, 0x5f, 0xff   },
        { -30,  10, 0, 0, ( 0 << 6), (31 << 6), 0xa0, 0x00, 0x5f, 0xff   },
        { -10,  10, 0, 0, (31 << 6), (31 << 6), 0xa0, 0x00, 0x5f, 0xff   },
        { -10, -10, 0, 0, (31 << 6), ( 0 << 6), 0xa0, 0x00, 0x5f, 0xff   },
};
static Vtx tri_lit1c[4] = {
        {  10, -10, 0, 0, ( 0 << 6), ( 0 << 6), 0x5f, 0x00, 0x5f, 0xff   },
        {  10,  10, 0, 0, ( 0 << 6), (31 << 6), 0x5f, 0x00, 0x5f, 0xff   },
        {  30,  10, 0, 0, (31 << 6), (31 << 6), 0x5f, 0x00, 0x5f, 0xff   },
        {  30, -10, 0, 0, (31 << 6), ( 0 << 6), 0x5f, 0x00, 0x5f, 0xff   },
};
static Vtx tri_lit1d[4] = {
        { -10,  10, 0, 0, ( 0 << 6), ( 0 << 6), 0x00, 0x5f, 0x5f, 0xff   },
        { -10,  30, 0, 0, ( 0 << 6), (31 << 6), 0x00, 0x5f, 0x5f, 0xff   },
        {  10,  30, 0, 0, (31 << 6), (31 << 6), 0x00, 0x5f, 0x5f, 0xff   },
        {  10,  10, 0, 0, (31 << 6), ( 0 << 6), 0x00, 0x5f, 0x5f, 0xff   },
};
static Vtx tri_lit1e[4] = {
        { -10, -30, 0, 0, ( 0 << 6), ( 0 << 6), 0x00, 0xa0, 0x5f, 0xff   },
        { -10, -10, 0, 0, ( 0 << 6), (31 << 6), 0x00, 0xa0, 0x5f, 0xff   },
        {  10, -10, 0, 0, (31 << 6), (31 << 6), 0x00, 0xa0, 0x5f, 0xff   },
        {  10, -30, 0, 0, (31 << 6), ( 0 << 6), 0x00, 0xa0, 0x5f, 0xff   },
};
Gfx rdpms_light1[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),

    /* set attributes, to be used as colors for rects */
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPLoadTextureBlock(rdpms_RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),

        /* test prim color */
        /* 3 bars: magenta over green over grey, all solid colors */
    gsSPVertex(&tri_lit1a, 4, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSP1Triangle(0, 3, 2, 0),

    gsSPVertex(&tri_lit1b, 4, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSP1Triangle(0, 3, 2, 0),

    gsSPVertex(&tri_lit1c, 4, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSP1Triangle(0, 3, 2, 0),

    gsSPVertex(&tri_lit1d, 4, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSP1Triangle(0, 3, 2, 0),

    gsSPVertex(&tri_lit1e, 4, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSP1Triangle(0, 3, 2, 0),

    gsSPEndDisplayList(),
};
/* end of case 30 */

/*
 * Test 31, Frame 31:
 * lighting tests
 *
 */
#include "sphere.dat"
Gfx rdpms_light2[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),

    /* set attributes, to be used as colors for rects */
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPSetGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPLoadTextureBlock(rdpms_RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
#include "sphere.dl"

    gsSPEndDisplayList(),
};
/* end of case 31 */

/*
 * Test 32, Frame 32:
 * lighting tests
 *
 */
Gfx rdpms_light3[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),

    /* set attributes, to be used as colors for rects */
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPSetGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

#include "sphere.dl"

    gsSPEndDisplayList(),
};
/* end of case 32 */

/*
 * Test 33, Frame 33:
 * lighting tests
 *
 */
Mtx sphere_matL={
	0x00010000, 0x00000000, 0x00000001, 0x00000000,
	0x00000000, 0x00010000, 0x00280000, 0x00000001,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
Mtx sphere_matR={
	0x00010000, 0x00000000, 0x00000001, 0x00000000,
	0x00000000, 0x00010000, 0xffd80000, 0x00000001,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
Mtx sphere_matROT={
	0x00000000, 0xffff0000, 0x00000001, 0x00000000,
	0x00010000, 0x00000000, 0x00000000, 0x00000001,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
Mtx sphere_matROTR={
	0x00000000, 0xffff0000, 0x00000001, 0x00000000,
	0x00010000, 0x00000000, 0x00000000, 0x00000001,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
Mtx sphere_matROTU={
	0x00010000, 0x00000000, 0x00000000, 0x00010000,
	0x0000ffff, 0x00000000, 0x00000000, 0x00000001,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
/*
Mtx sphere_matL={
	0x00010000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00010000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00010000, 0x00000000,
	0x00280000, 0x00000000, 0x00000000, 0x00010000,
};
Mtx sphere_matR={
	0x00010000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00010000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00010000, 0x00000000,
	0xffd80000, 0x00000000, 0x00000000, 0x00010000,
};
Mtx sphere_matROT={
	0x00000000, 0x00000000, 0xffff0000, 0x00000000,
	0x00000000, 0x00010000, 0x00000000, 0x00000000,
	0x00010000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00010000,
};
Mtx sphere_matROTR={
	0x00000000, 0x00000000, 0xffff0000, 0x00000000,
	0x00000000, 0x00010000, 0x00000000, 0x00000000,
	0x00010000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00010000,
};
Mtx sphere_matROTU={
	0x00010000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00010000, 0x00000000,
	0x00000000, 0xffff0000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00010000,
};
*/
/*
Lights lit1 = {
	{  {{0x20, 0x00, 0x20}, 0 }},
	{{ {{-64,  0, 32}, 0, {0xff, 0x00, 0x00}, 0 }},
	 { {{ 64,-64, 32}, 0, {0x00, 0x5f, 0x5f}, 0 }},
	 { {{  0,-64,-45}, 0, {0x00, 0xff, 0x00}, 0 }}},
};
*/
Light lita1 = {{ {0xff, 0x00, 0x00}, 0, {0xff, 0x00, 0x00}, 0, {-64,  0, 32}, 0 }};
Light lita2 = {{ {0x00, 0x5f, 0x5f}, 0, {0x00, 0x5f, 0x5f}, 0, { 64,-64, 32}, 0 }};
Light lita3 = {{ {0x00, 0xff, 0x00}, 0, {0x00, 0xff, 0x00}, 0, {  0,-64,-45}, 0 }};
Ambient lita4 ={{{0x20, 0x00, 0x20}, 0, {0x20, 0x00, 0x20}, 0 }};

Gfx rdpms_light4[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),

    /* set attributes, to be used as colors for rects */
    gsSPLight(&lita1,1),
    gsSPLight(&lita2,2),
    gsSPLight(&lita3,3),
    gsSPLight(&lita4,4),
    gsSPNumLights(4),




    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPSetGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsSPMatrix(&sphere_matL,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
#include "sphere.dl"
    gsSPMatrix(&sphere_matR,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
    gsSPMatrix(&sphere_matROTR,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH),
#include "sphere.dl"
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPMatrix(&sphere_matR,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
    gsSPMatrix(&sphere_matROTU,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
#include "sphere.dl"

    gsSPEndDisplayList(),
};
/* end of case 33 */

/*
 * Test 34, Frame 34:
 * lighting tests
 *
 */
#include "RGBA16town.h"
Lights1 litc1 = gdSPDefLights1(
		0x20, 0x00, 0x20,
		0xc0, 0x00, 0x00,	 -64,  0, 32);
Lights2 litc2 = gdSPDefLights2(
		0x20, 0x00, 0x20,
		0xc0, 0x00, 0x00,	 -64,  0, 32,
		0x00, 0x0, 0xff,	 64,-64, 32);
Lights3 litc = gdSPDefLights3(
		0x20, 0x00, 0x20,
		0xc0, 0x00, 0x00,	 -64,  0, 32,
		0x00, 0x5f, 0x5f,	 64,-64, 32,
		0x00, 0xc0, 0x00,	  0,-64,-45);
Lights0 lita = gdSPDefLights0(
		0x00, 0x00, 0x00);

/*
LookAt lookat1 = gdSPDefLookAt(0x7f, 0x00, 0x00,    0x00, 0x81, 0x00);
*/
LookAt lookat1 = gdSPDefLookAt(0x7f, 0x00, 0x00,    0x00, 0x81, 0x00);

Gfx rdpms_light5[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),

    /* set attributes, to be used as colors for rects */

/*
    gsSPLookAt(&lookat1),
*/

    gsSPSetLights3(litc),
    gsSPSetLights0(lita),

    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF,G_RM_AA_ZB_OPA_SURF2),
    gsSPSetGeometryMode(G_ZBUFFER | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LIGHTING),
    gsSPTexture(0x07c0, 0x07c0, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_REFLECTRGB, G_CC_REFLECTRGB),
    gsDPSetEnvColor(0x7f, 0x7f, 0x7f, 0xff),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPLoadTextureBlock(&RGBA16town[0 /*(32*32)-(4*32)*/ ], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),

    gsSPMatrix(&sphere_matL,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
#include "sphere.dl"
    gsSPMatrix(&sphere_matR,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
    gsSPMatrix(&sphere_matROTR,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH),
#include "sphere.dl"
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPMatrix(&sphere_matR,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
    gsSPMatrix(&sphere_matROTU,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
#include "sphere.dl"

    gsSPEndDisplayList(),
};
/* end of case 34 */

/*
 * Test 35, Frame 35:
 * lighting tests
 *
 */
#include "IA8spec.h"
#include "I4spec.h"

LookAt lookat2 = gdSPDefLookAt(0x7f, 0x00, 0x00,    0x00, 0x7f, 0x00);

Gfx rdpms_light6a[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),

    /* set attributes, to be used as colors for rects */

    gsSPLookAt(&lookat2),
    gsSPSetLights2(litc2),

    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsSPSetGeometryMode(G_TEXTURE_GEN | G_LIGHTING),
/*
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF,G_RM_AA_ZB_OPA_SURF2),
    gsSPSetGeometryMode(G_ZBUFFER | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPTexture(0x07c0, 0x07c0, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_REFLECTRGB, G_CC_REFLECTRGB),
    gsDPSetEnvColor(0x7f, 0x7f, 0x7f, 0xff),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPLoadTextureBlock(&RGBA16town[(32*32)-(4*32)], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
*/
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPTexture(0x07c0, 0x07c0, 0, G_TX_RENDERTILE /* | (1<<3)*/, G_ON),
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetEnvColor(000, 255, 255, 255),
    gsDPSetPrimColor(0, 0, 255, 255, 000, 255),
    gsDPSetCombineLERP(PRIMITIVE, SHADE, TEXEL0, SHADE,
                       PRIMITIVE, SHADE, TEXEL0, SHADE,
                       PRIMITIVE, SHADE, TEXEL0, SHADE,
                       PRIMITIVE, SHADE, TEXEL0, SHADE),

    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
/*
    gsDPSetCombineLERP(PRIMITIVE, SHADE, TEXEL0, SHADE,
                       PRIMITIVE, SHADE, TEXEL0, SHADE,
                       ENVIRONMENT, COMBINED, TEXEL0, COMBINED,
                       ENVIRONMENT, COMBINED, TEXEL0, COMBINED),
*/
    gsDPSetCombineMode(G_CC_HILITERGBA, G_CC_HILITERGBA2),

    gsDPSetTextureFilter(G_TF_BILERP),
    /* phong texture could be just intensity map */
/*
    gsDPLoadTextureBlock(IA8spec, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, ((((32) * G_IM_SIZ_8b_LINE_BYTES)+7)>>3), 
			0, G_TX_RENDERTILE+1, 0, G_TX_WRAP | G_TX_NOMIRROR,
			5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
*/
    gsDPLoadTextureBlock_4b(I4spec, G_IM_FMT_I, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, ((((16) )+7)>>3), 
			0, G_TX_RENDERTILE+1, 0, G_TX_WRAP | G_TX_NOMIRROR,
			5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),

    gsSPEndDisplayList(),
};
/*****
 *****
 ***** Highlight tile is set up here
 *****
 *****/
Gfx rdpms_light6b[] = {

    gsSPMatrix(&sphere_matL,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
#include "sphere.dl"
    gsSPMatrix(&sphere_matR,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
    gsSPMatrix(&sphere_matROTR,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH),
#include "sphere.dl"
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPMatrix(&sphere_matR,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
    gsSPMatrix(&sphere_matROTU,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
#include "sphere.dl"
    gsSPEndDisplayList(),
};
/* end of case 35 */

/*
 * Test 36, Frame 36:
 * lighting tests
 *
 */
Lights2 lit36 = gdSPDefLights2(
		0x20, 0x00, 0x20,
		0xc0, 0x00, 0x00,	 -64,  0, 32,
		0x00, 0x0, 0xff,	 64,-64, 32);
Lights0 lit36a = gdSPDefLights0(
		0xe0, 0x00, 0xe0);
#include "IA8specA.h"
#include "I4specA.h"
#include "I4specC.h"

Gfx rdpms_light7a[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),

    /* set attributes, to be used as colors for rects */

    gsSPLookAt(&lookat2),
    gsSPSetLights0(lit36a),

    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsSPSetGeometryMode(G_TEXTURE_GEN | G_LIGHTING),
/*
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF,G_RM_AA_ZB_OPA_SURF2),
    gsSPSetGeometryMode(G_ZBUFFER | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPTexture(0x07c0, 0x07c0, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_REFLECTRGB, G_CC_REFLECTRGB),
    gsDPSetEnvColor(0x7f, 0x7f, 0x7f, 0xff),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPLoadTextureBlock(&RGBA16town[(32*32)-(4*32)], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
*/
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPTexture(0x07c0, 0x07c0, 0, G_TX_RENDERTILE /* | (1<<3)*/, G_ON),
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetEnvColor(255, 255, 000, 255),
    gsDPSetPrimColor(0, 0, 000, 255, 000, 255),
    gsDPSetCombineLERP(PRIMITIVE, SHADE, TEXEL0, SHADE,
                       PRIMITIVE, SHADE, TEXEL0, SHADE,
                       PRIMITIVE, SHADE, TEXEL0, SHADE,
                       PRIMITIVE, SHADE, TEXEL0, SHADE),

    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_SURF2),
/*
    gsDPSetCombineLERP(PRIMITIVE, SHADE, TEXEL0, SHADE,
                       PRIMITIVE, SHADE, TEXEL0, SHADE,
                       ENVIRONMENT, COMBINED, TEXEL0, COMBINED,
                       ENVIRONMENT, COMBINED, TEXEL0, COMBINED),
*/
    gsDPSetCombineMode(G_CC_SHADEDECALA, G_CC_HILITERGBA2),

    gsDPSetTextureFilter(G_TF_BILERP),
    /* phong texture could be just intensity map */
/*
    gsDPLoadTextureBlock(IA8specA, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, ((((32) * G_IM_SIZ_8b_LINE_BYTES)+7)>>3), 
			0, G_TX_RENDERTILE+1, 0, G_TX_WRAP | G_TX_NOMIRROR,
			5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
*/
    _gsDPLoadTextureBlock_4b(I4specC, 128, G_IM_FMT_I, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, ((((16) )+7)>>3), 
			128, G_TX_RENDERTILE+1, 0, G_TX_WRAP | G_TX_NOMIRROR,
			5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),

    gsDPPipeSync(),

    gsDPLoadTextureBlock_4b(I4specA, G_IM_FMT_I, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, ((((16) )+7)>>3), 
			0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR,
			5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),


    gsSPEndDisplayList(),
};
/*****
 *****
 ***** Highlight tile is set up here
 *****
 *****/
Gfx rdpms_light7b[] = {

    gsSPMatrix(&sphere_matL,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
#include "sphere.dl"

    gsSPEndDisplayList(),
};
Gfx rdpms_light7c[] = {

    gsSPMatrix(&sphere_matR,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
    gsSPMatrix(&sphere_matROTR,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH),

    gsDPSetCombineLERP(0, 0, 0, SHADE,
                       0, 0, 0, TEXEL0,
                       0, 0, 0, COMBINED,
                       0, 0, 0, COMBINED ),

#include "sphere.dl"

    gsSPEndDisplayList(),
};
Gfx rdpms_light7d[] = {

    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPMatrix(&sphere_matR,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
    gsSPMatrix(&sphere_matROTU,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),

    gsDPSetCombineLERP(0, 0, 0, SHADE,
                       0, 0, 0, TEXEL0,
                       ENVIRONMENT, COMBINED, TEXEL0, COMBINED,
                       0, 0, 0, COMBINED ),

#include "sphere.dl"

    gsSPEndDisplayList(),
};
/* end of case 36 */

/*
 * Test 37, Frame 37:
 * lighting tests
 *
 */
Mtx sphere_matL8={
	0x00010000, 0x00000000, 0x00000001, 0x00000000,
	0x00000000, 0x00010000, 0x00280000, 0xffd80001,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
Mtx sphere_matR8={
	0x00010000, 0x00000000, 0x00000001, 0x00000000,
	0x00000000, 0x00010000, 0xffd80000, 0x00280001,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
/*
Mtx sphere_matL8={
	0x00010000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00010000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00010000, 0x00000000,
	0x00280000, 0x00000000, 0xffd80000, 0x00010000,
};
Mtx sphere_matR8={
	0x00010000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00010000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00010000, 0x00000000,
	0xffd80000, 0x00000000, 0x00280000, 0x00010000,
};
*/
static Vp vp8 = {
        SCREEN_WD*2-10, SCREEN_HT, G_MAXZ/2, 0,  /* scale */
        SCREEN_WD*2, SCREEN_HT, G_MAXZ/2, 0,  /* translate */
};
Gfx rdpms_light8a[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),

    /* set attributes, to be used as colors for rects */
    gsSPViewport(&vp8),

    gsSPLookAt(&lookat2),
    gsSPSetLights2(litc2),

    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsSPSetGeometryMode(G_TEXTURE_GEN | G_LIGHTING | G_FOG),
    gsDPSetFogColor(000, 0xc8, 0xc8, 255),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPTexture(0x07c0, 0x07c0, 0, G_TX_RENDERTILE /* | (1<<3)*/, G_ON),
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetEnvColor(255, 255, 000, 255),
    gsDPSetPrimColor(0, 0, 000, 255, 255, 255),
    gsDPSetCombineLERP(PRIMITIVE, SHADE, TEXEL0, SHADE,
                       PRIMITIVE, SHADE, TEXEL0, SHADE,
                       PRIMITIVE, SHADE, TEXEL0, SHADE,
                       PRIMITIVE, SHADE, TEXEL0, SHADE),

    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_HILITERGBA, G_CC_HILITERGBA2),

    gsDPSetTextureFilter(G_TF_BILERP),
    /* phong texture could be just intensity map */
    gsDPLoadTextureBlock_4b(I4spec, G_IM_FMT_I, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, ((((16) )+7)>>3), 
			0, G_TX_RENDERTILE+1, 0, G_TX_WRAP | G_TX_NOMIRROR,
			5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),

    gsSPEndDisplayList(),
};
/*****
 *****
 ***** Highlight tile is set up here
 *****
 *****/
Gfx rdpms_light8b[] = {

    gsSPMatrix(&sphere_matL8,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
#include "sphere.dl"
    gsSPEndDisplayList(),
};

Gfx rdpms_light8c[] = {
    gsSPMatrix(&sphere_matR8,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
    gsSPMatrix(&sphere_matROTR,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH),
#include "sphere.dl"
    gsSPEndDisplayList(),
};

Gfx rdpms_light8d[] = {
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPMatrix(&sphere_matR8,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
    gsSPMatrix(&sphere_matROTU,G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH),
#include "sphere.dl"
    gsSPEndDisplayList(),
};
/* end of case 37 */

/*
 * Test 38, Frame 38:
 * lighting tests
 *
 */
Gfx rdpms_light9[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};
/* end of case 38 */

/*
 * Test 39, Frame 39:
 * lighting tests
 *
 */
Gfx rdpms_light10[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};
/* end of case 39 */

/*
 * ADD TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx rdpms_display list must be extern'd in rdpverif.h, then
 * added to the 'testList' table in rdpverif.c
 *
 */
