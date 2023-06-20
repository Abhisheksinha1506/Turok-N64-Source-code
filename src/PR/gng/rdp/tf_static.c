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
 * File:	tf_static.c
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:
 *
 * This file holds tiny display list segments that are 'static' data, for use
 * by the texture filter test module in tf.c
 *
 * If you feel the urge to modify a test, see the comment at
 * the top of main.c for details.
 */

#include <ultratypes.h>
#include <mbi.h>
#include "dldriver.h"
#include "texture.h"

/*
 * Test conventions:
 *
 * Data variable names can be about anything, as long as they are unique
 * and consistent in the table entry.
 *
 * In order to get around compiler weirdness, the table of tests
 * is in tf.c, and the Gfx lists must be extern'd in rdpvector.h
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
static Vtx tf_place_vtx[5] =  {
/*     x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */	
    { -40,  40,    0,    0,	0,	0,	0xff,     0,     0,	0xff },	  /* R */   
    {  40,  40,    0,    0,	0,	0,	   0,  0xff,     0,	0xff },	  /* G */   
    {  40, -40,    0,    0,	0,	0,	   0,     0,  0xff,	0xff },	  /* B */   
    { -40, -40,    0,    0,	0,	0,	0xff,  0xff,     0,	0xff },	  /* Y */   
    {   0,   0,    0,    0,	0,	0,	0xff,  0xff,  0xff,	0xff },	  /* W */   
};

Gfx TF_placebo_dl[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&tf_place_vtx, 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};
/* end of case -1 */

/*
 * Test 1, Frame 1:
 *
 * Convert textures with powers of 2, random data values; pump these data
 * values through the YUV conversion process, and display the resulting pixels.
 */

/*
 *  YUV-RGB Conversion coefficients
 */

#define MY_K0	(175 & 0x1ff)
#define MY_K1	(-43 & 0x1ff)
#define MY_K2	(-89 & 0x1ff)
#define MY_K3	(222 & 0x1ff)
#define MY_K4	(114 & 0x1ff)
#define MY_K5	(42 & 0x1ff)

/*
 * Create a pair of triangles that forms a rectangle 65 pixels on the side;
 * this forces us to iterate through S & T fractions, thereby exercising the
 * tf lerps better than a t frac of zero or 0.5.
 */
static Vtx TF_yuvtile_powersOfTwo[] =  {
/*   x,    y,  z, flag,	   s,	      t,    r,	  g,	b,     a     */	
    {120, 225,  0, 0, ( 0 << 6), ( 0 << 6), 0,    0,    0xff, 0xff},
    {185, 225,  0, 0, (31 << 6), ( 0 << 6), 0x1f, 0,    0xff, 0xff},
    {185, 160,  0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff},
    {120, 160,  0, 0, ( 0 << 6), (31 << 6), 0,    0x1f, 0xff, 0xff}
};

/*
 * Create a pair of triangles that forms a rectangle 65 pixels on the side;
 * this forces us to iterate through S & T fractions, thereby exercising the
 * tf lerps better than a t frac of zero or 0.5.  Put it on screen in a 
 * different location so that the combined tests don't overlap their pixels.
 */
static Vtx TF_yuvtile_rand[] =  {
/*   x,    y,  z, flag,	   s,	      t,    r,	  g,	b,     a     */	
    {120, 155,  0, 0, ( 0 << 6), ( 0 << 6), 0,    0,    0xff, 0xff},
    {185, 155,  0, 0, (31 << 6), ( 0 << 6), 0x1f, 0,    0xff, 0xff},
    {185,  90,  0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff},
    {120,  90,  0, 0, ( 0 << 6), (31 << 6), 0,    0x1f, 0xff, 0xff}
};


Gfx TF_yuv_multiplicand_dl[] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_CONV),

    /*
     * Test with a legitimate set of coefficients.
     */
    gsDPSetConvert(MY_K0, MY_K1, MY_K2, MY_K3, MY_K4, MY_K5),

    gsDPSetCombineMode(G_CC_1CYUV2RGB, G_CC_1CYUV2RGB),

    /*
     * Load texture with embedded powers of 2, this will yuv convert it.
     */
    gsDPLoadTextureBlock(RGBA32pattern, G_IM_FMT_YUV, G_IM_SIZ_32b, 32, 32, 0,
                         G_TX_NOMIRROR, G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&TF_yuvtile_powersOfTwo, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),

    gsDPPipeSync(),

    /*
     * Load texture with embedded powers of 2, this will yuv convert it.
     */
    gsDPLoadTextureBlock(map_rand32, G_IM_FMT_YUV, G_IM_SIZ_32b, 32, 32, 0,
                         G_TX_NOMIRROR, G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&TF_yuvtile_rand, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),

    gsSPEndDisplayList(),
};

/*
 * Create a pair of triangles that forms a rectangle 65 pixels on the side;
 * this forces us to iterate through S & T fractions, thereby exercising the
 * tf lerps better than a t frac of zero or 0.5.
 */
static Vtx TF_RGBApattern_geom[] =  {
/*   x,    y,  z, flag,	   s,	      t,    r,	  g,	b,     a     */	
    {-128,65,  0, 0, ( 0 << 6), ( 0 << 6), 0,    0,    0xff, 0xff},
    {-63, 65,  0, 0, (31 << 6), ( 0 << 6), 0x1f, 0,    0xff, 0xff},
    {-63,  0,  0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff},
    {-128, 0,  0, 0, ( 0 << 6), (31 << 6), 0,    0x1f, 0xff, 0xff}
};

/*
 * Create a pair of triangles that forms a rectangle 65 pixels on the side;
 * this forces us to iterate through S & T fractions, thereby exercising the
 * tf lerps better than a t frac of zero or 0.5.  Put it on screen in a 
 * different location so that the combined tests don't overlap their pixels.
 */
static Vtx TF_RGBA_rand_pattern_geom[] =  {
/*   x,    y,  z, flag,	   s,	      t,    r,	  g,	b,     a     */	
    {-63,65,  0, 0, ( 0 << 6), ( 0 << 6), 0,    0,    0xff, 0xff},
    { 1, 65,  0, 0, (31 << 6), ( 0 << 6), 0x1f, 0,    0xff, 0xff},
    { 1,  0,  0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff},
    {-63, 0,  0, 0, ( 0 << 6), (31 << 6), 0,    0x1f, 0xff, 0xff}
};

Gfx TF_load_RGBA32pattern_dl[] = {
    /*
     *  Load a 32x32x32 texture (fills Tmem)
     */
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_AVERAGE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_PERSP),

    gsDPLoadTextureBlock(RGBA32pattern, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0,
                         G_TX_NOMIRROR, G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&TF_RGBApattern_geom, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),

    gsSPEndDisplayList(),
};

Gfx TF_load_rand_dl[] = {
    /*
     *  Load a 32x32x32 texture (fills Tmem)
     */
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_AVERAGE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_PERSP),

    gsDPLoadTextureBlock(map_rand32, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0,
                         G_TX_NOMIRROR, G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&TF_RGBA_rand_pattern_geom, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};

/* 
 * Perspective corrected texture, using powers of two mipmap texture
 */

static Vtx tf_q1a[25] =  {
	{ -64, 0, -64, 0, (0 << 6), (0 << 6), 0, 0, 0, 0xff },
	{ -32, 0, -64, 0, (31 << 6), (0 << 6), 0, 0, 0, 0xff },
	{ 0, 0, -64, 0, (63 << 6), (0 << 6), 0, 0, 0, 0xff },
	{ 32, 0, -64, 0, (95 << 6), (0 << 6), 0, 0, 0, 0xff },
	{ 64, 0, -64, 0, (127 << 6), (0 << 6), 0, 0, 0, 0xff },
	{ -64, 0, -32, 0, (0 << 6), (31 << 6), 0, 0, 0, 0xff },
	{ -32, 0, -32, 0, (31 << 6), (31 << 6), 0, 0, 0, 0xff },
	{ 0, 0, -32, 0, (63 << 6), (31 << 6), 0, 0, 0, 0xff },
	{ 32, 0, -32, 0, (95 << 6), (31 << 6), 0, 0, 0, 0xff },
	{ 64, 0, -32, 0, (127 << 6), (31 << 6), 0, 0, 0, 0xff },
	{ -64, 0, 0, 0, (0 << 6), (63 << 6), 0, 0, 0, 0xff },
	{ -32, 0, 0, 0, (31 << 6), (63 << 6), 0, 0, 0, 0xff },
	{ 0, 0, 0, 0, (63 << 6), (63 << 6), 0, 0, 0, 0xff },
	{ 32, 0, 0, 0, (95 << 6), (63 << 6), 0, 0, 0, 0xff },
	{ 64, 0, 0, 0, (127 << 6), (63 << 6), 0, 0, 0, 0xff },
	{ -64, 0, 32, 0, (0 << 6), (95 << 6), 0, 0, 0, 0xff },
	{ -32, 0, 32, 0, (31 << 6), (95 << 6), 0, 0, 0, 0xff },
	{ 0, 0, 32, 0, (63 << 6), (95 << 6), 0, 0, 0, 0xff },
	{ 32, 0, 32, 0, (95 << 6), (95 << 6), 0, 0, 0, 0xff },
	{ 64, 0, 32, 0, (127 << 6), (95 << 6), 0, 0, 0, 0xff },
	{ -64, 0, 64, 0, (0 << 6), (127 << 6), 0, 0, 0, 0xff },
	{ -32, 0, 64, 0, (31 << 6), (127 << 6), 0, 0, 0, 0xff },
	{ 0, 0, 64, 0, (63 << 6), (127 << 6), 0, 0, 0, 0xff },
	{ 32, 0, 64, 0, (95 << 6), (127 << 6), 0, 0, 0, 0xff },
	{ 64, 0, 64, 0, (127 << 6), (127 << 6), 0, 0, 0, 0xff },
};

/* 
 * Perspective corrected texture
 */
Gfx TF_perspectivetex_dl[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 5, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_OPA_SURF2),

    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetCombineMode(G_CC_TRILERP, G_CC_DECALRGB2),

    /* 
     * Unroll the LoadTextureBlock for mipmapping test:
     *
     * The size of the LoadBlock and the tmem addresses of the
     * SetTile's are magic numbers fixed on how RGBA16powersOfTwoMM
     * was created...
     *
     * There may be other sized-related constants hard-coded...
     *
     */
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, RGBA16powersOfTwoMM),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 	
		0, 0, G_TX_LOADTILE, 0,
		0, 0, 0,
		0, 0, 0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1368, 0),
		

    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 
		(((32 * G_IM_SIZ_16b_BYTES)+7)>>3), 0x000, 0, 0,
		G_TX_WRAP | G_TX_NOMIRROR, 5, 0,
		G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 
		    (16 - 1) << G_TEXTURE_IMAGE_FRAC,
		    (16 - 1) << G_TEXTURE_IMAGE_FRAC),

    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 
		(((16 * G_IM_SIZ_16b_BYTES)+7)>>3), 0x100, 1, 0,
		G_TX_WRAP | G_TX_NOMIRROR, 4, 1,
		G_TX_WRAP | G_TX_NOMIRROR, 4, 1),
    gsDPSetTileSize(1, 0, 0, 
		    (16 - 1) << G_TEXTURE_IMAGE_FRAC,
		    (16 - 1) << G_TEXTURE_IMAGE_FRAC),

    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 
		(((8 * G_IM_SIZ_16b_BYTES)+7)>>3), 0x140, 2, 0,
		G_TX_WRAP | G_TX_NOMIRROR, 3, 2,
		G_TX_WRAP | G_TX_NOMIRROR, 3, 2),
    gsDPSetTileSize(2, 0, 0, 
		    (8 - 1) << G_TEXTURE_IMAGE_FRAC,
		    (8 - 1) << G_TEXTURE_IMAGE_FRAC),

    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 
		(((4 * G_IM_SIZ_16b_BYTES)+7)>>3), 0x150, 3, 0,
		G_TX_WRAP | G_TX_NOMIRROR, 2, 3,
		G_TX_WRAP | G_TX_NOMIRROR, 2, 3),
    gsDPSetTileSize(3, 0, 0, 
		    (4 - 1) << G_TEXTURE_IMAGE_FRAC,
		    (4 - 1) << G_TEXTURE_IMAGE_FRAC),

    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 
		(((2 * G_IM_SIZ_16b_BYTES)+7)>>3), 0x154, 4, 0,
		G_TX_WRAP | G_TX_NOMIRROR, 1, 4,
		G_TX_WRAP | G_TX_NOMIRROR, 1, 4),
    gsDPSetTileSize(4, 0, 0, 
		    (2 - 1) << G_TEXTURE_IMAGE_FRAC,
		    (2 - 1) << G_TEXTURE_IMAGE_FRAC),

    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 
		(((1 * G_IM_SIZ_16b_BYTES)+7)>>3), 0x156, 5, 0,
		G_TX_WRAP | G_TX_NOMIRROR, 0, 5,
		G_TX_WRAP | G_TX_NOMIRROR, 0, 5),
    gsDPSetTileSize(5, 0, 0, 
		    (1 - 1) << G_TEXTURE_IMAGE_FRAC,
		    (1 - 1) << G_TEXTURE_IMAGE_FRAC),

    /* all the tiles are now set up */

    gsDPSetTextureLOD(G_TL_LOD),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPSetCycleType(G_CYC_2CYCLE),

    gsSPVertex(&(tf_q1a[0]), 10, 0),
	gsSP1Triangle(0, 1, 5, 0),
	gsSP1Triangle(1, 5, 6, 0),
	gsSP1Triangle(1, 2, 6, 0),
	gsSP1Triangle(2, 6, 7, 0),
	gsSP1Triangle(2, 3, 7, 0),
	gsSP1Triangle(3, 7, 8, 0),
	gsSP1Triangle(3, 4, 8, 0),
	gsSP1Triangle(4, 8, 9, 0),


    gsSPVertex(&(tf_q1a[5]), 10, 0),
	gsSP1Triangle(0, 1, 5, 0),
	gsSP1Triangle(1, 5, 6, 0),
	gsSP1Triangle(1, 2, 6, 0),
	gsSP1Triangle(2, 6, 7, 0),
	gsSP1Triangle(2, 3, 7, 0),
	gsSP1Triangle(3, 7, 8, 0),
	gsSP1Triangle(3, 4, 8, 0),
	gsSP1Triangle(4, 8, 9, 0),


    gsSPVertex(&(tf_q1a[10]), 10, 0),
	gsSP1Triangle(0, 1, 5, 0),
	gsSP1Triangle(1, 5, 6, 0),
	gsSP1Triangle(1, 2, 6, 0),
	gsSP1Triangle(2, 6, 7, 0),
	gsSP1Triangle(2, 3, 7, 0),
	gsSP1Triangle(3, 7, 8, 0),
	gsSP1Triangle(3, 4, 8, 0),
	gsSP1Triangle(4, 8, 9, 0),


    gsSPVertex(&(tf_q1a[15]), 10, 0),
	gsSP1Triangle(0, 1, 5, 0),
	gsSP1Triangle(1, 5, 6, 0),
	gsSP1Triangle(1, 2, 6, 0),
	gsSP1Triangle(2, 6, 7, 0),
	gsSP1Triangle(2, 3, 7, 0),
	gsSP1Triangle(3, 7, 8, 0),
	gsSP1Triangle(3, 4, 8, 0),
	gsSP1Triangle(4, 8, 9, 0),


    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};

/* 
 * Test 5: To exercize lerps
 */

#define TF_STATIC_GFX_SIZE 2048

Gfx TF_lerp_dl[TF_STATIC_GFX_SIZE] = {

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
#define CC_OP	0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0
    gsDPSetCombineMode (CC_OP, CC_OP),
	gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
#define BL_OP1    IM_RD | CVG_DST_WRAP | CVG_X_ALPHA |       \
			FORCE_BL | ZMODE_OPA | ALPHA_CVG_SEL |           \
			GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_FOG, G_BL_1)
#define BL_OP2    IM_RD | CVG_DST_WRAP | CVG_X_ALPHA |       \
			FORCE_BL | ZMODE_OPA | ALPHA_CVG_SEL |           \
			GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_FOG, G_BL_1)
	gsDPSetFogColor (0x0, 0x0, 0x0, 0x0),
	gsDPSetRenderMode(BL_OP1, BL_OP2),
	/*
	gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
	*/
	gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLOD(G_TL_TILE),

#define XBASE 24
#define YBASE 152
#define X0 XBASE
#define Y0 YBASE
#undef YOFF
#define YOFF Y0
#define WIDTH 4
#define HEIGHT 4
#undef TEX_WIDTH
#define TEX_WIDTH 512
#undef TEX_HEIGHT
#define TEX_HEIGHT 2
	gsDPLoadTextureBlock(tf_lerp_texture, G_IM_FMT_RGBA, G_IM_SIZ_32b,
		TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+0*HEIGHT+0*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 0 << 5, 0 << 5, 0xaa << 2, 0xfd << 2),

#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 2 << 5, 0 << 5, 0x1b << 2, 0x68 << 2),

#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 4 << 5, 0 << 5, 0x58 << 2, 0x43 << 2),

#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 6 << 5, 0 << 5, 0xd6 << 2, 0xdd << 2),

#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 8 << 5, 0 << 5, 0xff << 2, 0x2 << 2),

#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 10 << 5, 0 << 5, 0x18 << 2, 0x45 << 2),

#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 12 << 5, 0 << 5, 0xf3 << 2, 0xab << 2),

#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 14 << 5, 0 << 5, 0xc << 2, 0xa6 << 2),

#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 16 << 5, 0 << 5, 0x40 << 2, 0x2 << 2),

#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 18 << 5, 0 << 5, 0x1b << 2, 0x6d << 2),

#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 20 << 5, 0 << 5, 0x6d << 2, 0xbe << 2),

#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 22 << 5, 0 << 5, 0xcd << 2, 0xb2 << 2),

#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 24 << 5, 0 << 5, 0x88 << 2, 0xc2 << 2),

#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 26 << 5, 0 << 5, 0x58 << 2, 0x40 << 2),

#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 28 << 5, 0 << 5, 0xc0 << 2, 0x9 << 2),

#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 30 << 5, 0 << 5, 0x74 << 2, 0xe4 << 2),

#undef XOFF
#define XOFF (X0+16*WIDTH+16*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 32 << 5, 0 << 5, 0x99 << 2, 0x5a << 2),

#undef XOFF
#define XOFF (X0+17*WIDTH+17*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 34 << 5, 0 << 5, 0x53 << 2, 0xa8 << 2),

#undef XOFF
#define XOFF (X0+18*WIDTH+18*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 36 << 5, 0 << 5, 0x18 << 2, 0x48 << 2),

#undef XOFF
#define XOFF (X0+19*WIDTH+19*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 38 << 5, 0 << 5, 0xba << 2, 0x78 << 2),

#undef XOFF
#define XOFF (X0+20*WIDTH+20*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 40 << 5, 0 << 5, 0xaa << 2, 0xf1 << 2),

#undef XOFF
#define XOFF (X0+21*WIDTH+21*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 42 << 5, 0 << 5, 0x59 << 2, 0x5d << 2),

#undef XOFF
#define XOFF (X0+22*WIDTH+22*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 44 << 5, 0 << 5, 0x7b << 2, 0x61 << 2),

#undef XOFF
#define XOFF (X0+23*WIDTH+23*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 46 << 5, 0 << 5, 0x2d << 2, 0xb7 << 2),

#undef XOFF
#define XOFF (X0+24*WIDTH+24*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 48 << 5, 0 << 5, 0xbf << 2, 0xf << 2),

#undef XOFF
#define XOFF (X0+25*WIDTH+25*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 50 << 5, 0 << 5, 0x52 << 2, 0xb6 << 2),

#undef XOFF
#define XOFF (X0+26*WIDTH+26*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 52 << 5, 0 << 5, 0xb4 << 2, 0xed << 2),

#undef XOFF
#define XOFF (X0+27*WIDTH+27*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 54 << 5, 0 << 5, 0xe8 << 2, 0xc1 << 2),

#undef XOFF
#define XOFF (X0+28*WIDTH+28*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 56 << 5, 0 << 5, 0x48 << 2, 0xce << 2),

#undef XOFF
#define XOFF (X0+29*WIDTH+29*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 58 << 5, 0 << 5, 0x18 << 2, 0x40 << 2),

#undef XOFF
#define XOFF (X0+30*WIDTH+30*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 60 << 5, 0 << 5, 0xc2 << 2, 0x30 << 2),

#undef XOFF
#define XOFF (X0+31*WIDTH+31*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 62 << 5, 0 << 5, 0x15 << 2, 0xf9 << 2),

#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+1*HEIGHT+1*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 64 << 5, 0 << 5, 0x21 << 2, 0x17 << 2),

#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 66 << 5, 0 << 5, 0xdb << 2, 0x68 << 2),

#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 68 << 5, 0 << 5, 0x5a << 2, 0x76 << 2),

#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 70 << 5, 0 << 5, 0xf7 << 2, 0xc6 << 2),

#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 72 << 5, 0 << 5, 0x65 << 2, 0x75 << 2),

#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 74 << 5, 0 << 5, 0xe0 << 2, 0x5 << 2),

#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 76 << 5, 0 << 5, 0x31 << 2, 0x98 << 2),

#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 78 << 5, 0 << 5, 0x9 << 2, 0xde << 2),

#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 80 << 5, 0 << 5, 0xe9 << 2, 0xdb << 2),

#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 82 << 5, 0 << 5, 0xdc << 2, 0x25 << 2),

#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 84 << 5, 0 << 5, 0xd7 << 2, 0xcb << 2),

#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 86 << 5, 0 << 5, 0x28 << 2, 0xc5 << 2),

#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 88 << 5, 0 << 5, 0x74 << 2, 0xe0 << 2),

#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 90 << 5, 0 << 5, 0xa7 << 2, 0x41 << 2),

#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 92 << 5, 0 << 5, 0xcd << 2, 0xb2 << 2),

#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 94 << 5, 0 << 5, 0x8d << 2, 0xbd << 2),

#undef XOFF
#define XOFF (X0+16*WIDTH+16*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 96 << 5, 0 << 5, 0xda << 2, 0x7c << 2),

#undef XOFF
#define XOFF (X0+17*WIDTH+17*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 98 << 5, 0 << 5, 0x93 << 2, 0xa9 << 2),

#undef XOFF
#define XOFF (X0+18*WIDTH+18*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 100 << 5, 0 << 5, 0x14 << 2, 0xe4 << 2),

#undef XOFF
#define XOFF (X0+19*WIDTH+19*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 102 << 5, 0 << 5, 0x9c << 2, 0x2a << 2),

#undef XOFF
#define XOFF (X0+20*WIDTH+20*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 104 << 5, 0 << 5, 0x81 << 2, 0x13 << 2),

#undef XOFF
#define XOFF (X0+21*WIDTH+21*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 106 << 5, 0 << 5, 0xe1 << 2, 0x1c << 2),

#undef XOFF
#define XOFF (X0+22*WIDTH+22*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 108 << 5, 0 << 5, 0xb6 << 2, 0xd8 << 2),

#undef XOFF
#define XOFF (X0+23*WIDTH+23*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 110 << 5, 0 << 5, 0xcf << 2, 0x8f << 2),

#undef XOFF
#define XOFF (X0+24*WIDTH+24*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 112 << 5, 0 << 5, 0xd1 << 2, 0x91 << 2),

#undef XOFF
#define XOFF (X0+25*WIDTH+25*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 114 << 5, 0 << 5, 0x7d << 2, 0x3f << 2),

#undef XOFF
#define XOFF (X0+26*WIDTH+26*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 116 << 5, 0 << 5, 0x40 << 2, 0x3 << 2),

#undef XOFF
#define XOFF (X0+27*WIDTH+27*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 118 << 5, 0 << 5, 0xaf << 2, 0xff << 2),

#undef XOFF
#define XOFF (X0+28*WIDTH+28*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 120 << 5, 0 << 5, 0x53 << 2, 0x1 << 2),

#undef XOFF
#define XOFF (X0+29*WIDTH+29*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 122 << 5, 0 << 5, 0xab << 2, 0xfb << 2),

#undef XOFF
#define XOFF (X0+30*WIDTH+30*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 124 << 5, 0 << 5, 0x51 << 2, 0x5 << 2),

#undef XOFF
#define XOFF (X0+31*WIDTH+31*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 126 << 5, 0 << 5, 0xbe << 2, 0xfa << 2),

#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+2*HEIGHT+2*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 128 << 5, 0 << 5, 0x5f << 2, 0xf << 2),

#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 130 << 5, 0 << 5, 0xbd << 2, 0xd9 << 2),

#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 132 << 5, 0 << 5, 0x53 << 2, 0x25 << 2),

#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 134 << 5, 0 << 5, 0xad << 2, 0xdf << 2),

#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 136 << 5, 0 << 5, 0x4e << 2, 0x2b << 2),

#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 138 << 5, 0 << 5, 0xb5 << 2, 0xd6 << 2),

#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 140 << 5, 0 << 5, 0x56 << 2, 0x39 << 2),

#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 142 << 5, 0 << 5, 0xb5 << 2, 0xfe << 2),

#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 144 << 5, 0 << 5, 0xde << 2, 0x67 << 2),

#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 146 << 5, 0 << 5, 0x59 << 2, 0xfc << 2),

#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 148 << 5, 0 << 5, 0xa1 << 2, 0x5 << 2),

#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 150 << 5, 0 << 5, 0x53 << 2, 0xfe << 2),

#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 152 << 5, 0 << 5, 0xae << 2, 0xd << 2),

#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 154 << 5, 0 << 5, 0x57 << 2, 0xf5 << 2),

#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 156 << 5, 0 << 5, 0xa5 << 2, 0xa << 2),

#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 158 << 5, 0 << 5, 0x5a << 2, 0xf5 << 2),

#undef XOFF
#define XOFF (X0+16*WIDTH+16*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 160 << 5, 0 << 5, 0xa5 << 2, 0xe << 2),

#undef XOFF
#define XOFF (X0+17*WIDTH+17*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 162 << 5, 0 << 5, 0x5c << 2, 0xf5 << 2),

#undef XOFF
#define XOFF (X0+18*WIDTH+18*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 164 << 5, 0 << 5, 0x8b << 2, 0x3a << 2),

#undef XOFF
#define XOFF (X0+19*WIDTH+19*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 166 << 5, 0 << 5, 0xab << 2, 0x3a << 2),

#undef XOFF
#define XOFF (X0+20*WIDTH+20*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 168 << 5, 0 << 5, 0x57 << 2, 0xd7 << 2),

#undef XOFF
#define XOFF (X0+21*WIDTH+21*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 170 << 5, 0 << 5, 0xae << 2, 0x6d << 2),

#undef XOFF
#define XOFF (X0+22*WIDTH+22*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 172 << 5, 0 << 5, 0x5a << 2, 0x92 << 2),

#undef XOFF
#define XOFF (X0+23*WIDTH+23*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 174 << 5, 0 << 5, 0x86 << 2, 0x6f << 2),

#undef XOFF
#define XOFF (X0+24*WIDTH+24*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 176 << 5, 0 << 5, 0x70 << 2, 0x93 << 2),

#undef XOFF
#define XOFF (X0+25*WIDTH+25*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 178 << 5, 0 << 5, 0x8e << 2, 0x68 << 2),

#undef XOFF
#define XOFF (X0+26*WIDTH+26*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 180 << 5, 0 << 5, 0x65 << 2, 0x97 << 2),

#undef XOFF
#define XOFF (X0+27*WIDTH+27*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 182 << 5, 0 << 5, 0xbb << 2, 0x6b << 2),

#undef XOFF
#define XOFF (X0+28*WIDTH+28*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 184 << 5, 0 << 5, 0x45 << 2, 0x95 << 2),

#undef XOFF
#define XOFF (X0+29*WIDTH+29*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 186 << 5, 0 << 5, 0x9b << 2, 0x6d << 2),

#undef XOFF
#define XOFF (X0+30*WIDTH+30*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 188 << 5, 0 << 5, 0x55 << 2, 0x96 << 2),

#undef XOFF
#define XOFF (X0+31*WIDTH+31*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 190 << 5, 0 << 5, 0xa5 << 2, 0x6d << 2),

#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+3*HEIGHT+3*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 192 << 5, 0 << 5, 0x6e << 2, 0x86 << 2),

#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 194 << 5, 0 << 5, 0x86 << 2, 0x7f << 2),

#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 196 << 5, 0 << 5, 0x7d << 2, 0xc9 << 2),

#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 198 << 5, 0 << 5, 0x97 << 2, 0x3f << 2),

#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 200 << 5, 0 << 5, 0x6d << 2, 0xc1 << 2),

#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 202 << 5, 0 << 5, 0x86 << 2, 0x2c << 2),

#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 204 << 5, 0 << 5, 0x7e << 2, 0xd1 << 2),

#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 206 << 5, 0 << 5, 0xa6 << 2, 0x3c << 2),

#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 208 << 5, 0 << 5, 0x5a << 2, 0xc1 << 2),

#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 210 << 5, 0 << 5, 0xa6 << 2, 0x3d << 2),

#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 212 << 5, 0 << 5, 0x5c << 2, 0xc3 << 2),

#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 214 << 5, 0 << 5, 0xa3 << 2, 0x39 << 2),

#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 216 << 5, 0 << 5, 0x5e << 2, 0xc7 << 2),

#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 218 << 5, 0 << 5, 0xa1 << 2, 0x38 << 2),

#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 220 << 5, 0 << 5, 0x5a << 2, 0xc7 << 2),

#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 222 << 5, 0 << 5, 0xa5 << 2, 0x3a << 2),

#undef XOFF
#define XOFF (X0+16*WIDTH+16*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 224 << 5, 0 << 5, 0x12 << 2, 0xd5 << 2),

#undef XOFF
#define XOFF (X0+17*WIDTH+17*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 226 << 5, 0 << 5, 0xec << 2, 0x2d << 2),

#undef XOFF
#define XOFF (X0+18*WIDTH+18*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 228 << 5, 0 << 5, 0x15 << 2, 0xd1 << 2),

#undef XOFF
#define XOFF (X0+19*WIDTH+19*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 230 << 5, 0 << 5, 0xea << 2, 0x2a << 2),

#undef XOFF
#define XOFF (X0+20*WIDTH+20*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 232 << 5, 0 << 5, 0x15 << 2, 0xd5 << 2),

#undef XOFF
#define XOFF (X0+21*WIDTH+21*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 234 << 5, 0 << 5, 0xee << 2, 0x2a << 2),

#undef XOFF
#define XOFF (X0+22*WIDTH+22*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 236 << 5, 0 << 5, 0x15 << 2, 0xdd << 2),

#undef XOFF
#define XOFF (X0+23*WIDTH+23*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 238 << 5, 0 << 5, 0xda << 2, 0x33 << 2),

#undef XOFF
#define XOFF (X0+24*WIDTH+24*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 240 << 5, 0 << 5, 0x15 << 2, 0xd4 << 2),

#undef XOFF
#define XOFF (X0+25*WIDTH+25*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 242 << 5, 0 << 5, 0xfa << 2, 0x13 << 2),

#undef XOFF
#define XOFF (X0+26*WIDTH+26*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 244 << 5, 0 << 5, 0x1 << 2, 0xec << 2),

#undef XOFF
#define XOFF (X0+27*WIDTH+27*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 246 << 5, 0 << 5, 0xf7 << 2, 0x12 << 2),

#undef XOFF
#define XOFF (X0+28*WIDTH+28*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 248 << 5, 0 << 5, 0x20 << 2, 0xea << 2),

#undef XOFF
#define XOFF (X0+29*WIDTH+29*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 250 << 5, 0 << 5, 0x5f << 2, 0x15 << 2),

#undef XOFF
#define XOFF (X0+30*WIDTH+30*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 252 << 5, 0 << 5, 0xd0 << 2, 0xf2 << 2),

#undef XOFF
#define XOFF (X0+31*WIDTH+31*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 254 << 5, 0 << 5, 0x2f << 2, 0x15 << 2),

#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+4*HEIGHT+4*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 256 << 5, 0 << 5, 0xf9 << 2, 0xfa << 2),

#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 258 << 5, 0 << 5, 0x0 << 2, 0x4 << 2),

#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 260 << 5, 0 << 5, 0xa7 << 2, 0xab << 2),

#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 262 << 5, 0 << 5, 0x58 << 2, 0xb4 << 2),

#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 264 << 5, 0 << 5, 0xa7 << 2, 0x4b << 2),

#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 266 << 5, 0 << 5, 0x58 << 2, 0xb4 << 2),

#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 268 << 5, 0 << 5, 0xa7 << 2, 0x6b << 2),

#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 270 << 5, 0 << 5, 0x5b << 2, 0x97 << 2),

#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 272 << 5, 0 << 5, 0xac << 2, 0x69 << 2),

#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 274 << 5, 0 << 5, 0x56 << 2, 0x97 << 2),

#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 276 << 5, 0 << 5, 0xb3 << 2, 0x68 << 2),

#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 278 << 5, 0 << 5, 0x54 << 2, 0x97 << 2),

#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 280 << 5, 0 << 5, 0x23 << 2, 0x78 << 2),

#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 282 << 5, 0 << 5, 0xdc << 2, 0x87 << 2),

#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 284 << 5, 0 << 5, 0xa3 << 2, 0x68 << 2),

#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 286 << 5, 0 << 5, 0x5d << 2, 0x97 << 2),

#undef XOFF
#define XOFF (X0+16*WIDTH+16*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 288 << 5, 0 << 5, 0xa1 << 2, 0x6d << 2),

#undef XOFF
#define XOFF (X0+17*WIDTH+17*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 290 << 5, 0 << 5, 0x5a << 2, 0x93 << 2),

#undef XOFF
#define XOFF (X0+18*WIDTH+18*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 292 << 5, 0 << 5, 0xa5 << 2, 0x69 << 2),

#undef XOFF
#define XOFF (X0+19*WIDTH+19*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 294 << 5, 0 << 5, 0x5a << 2, 0x97 << 2),

#undef XOFF
#define XOFF (X0+20*WIDTH+20*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 296 << 5, 0 << 5, 0xa5 << 2, 0x69 << 2),

#undef XOFF
#define XOFF (X0+21*WIDTH+21*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 298 << 5, 0 << 5, 0x58 << 2, 0x97 << 2),

#undef XOFF
#define XOFF (X0+22*WIDTH+22*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 300 << 5, 0 << 5, 0x1f << 2, 0x50 << 2),

#undef XOFF
#define XOFF (X0+23*WIDTH+23*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 302 << 5, 0 << 5, 0x88 << 2, 0xa9 << 2),

#undef XOFF
#define XOFF (X0+24*WIDTH+24*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 304 << 5, 0 << 5, 0x88 << 2, 0xa1 << 2),

#undef XOFF
#define XOFF (X0+25*WIDTH+25*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 306 << 5, 0 << 5, 0x45 << 2, 0x7e << 2),

#undef XOFF
#define XOFF (X0+26*WIDTH+26*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 308 << 5, 0 << 5, 0xb6 << 2, 0x83 << 2),

#undef XOFF
#define XOFF (X0+27*WIDTH+27*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 310 << 5, 0 << 5, 0x47 << 2, 0x55 << 2),

#undef XOFF
#define XOFF (X0+28*WIDTH+28*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 312 << 5, 0 << 5, 0xbd << 2, 0xaf << 2),

#undef XOFF
#define XOFF (X0+29*WIDTH+29*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 314 << 5, 0 << 5, 0x4a << 2, 0x51 << 2),

#undef XOFF
#define XOFF (X0+30*WIDTH+30*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 316 << 5, 0 << 5, 0xb3 << 2, 0xaf << 2),

#undef XOFF
#define XOFF (X0+31*WIDTH+31*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 318 << 5, 0 << 5, 0x4e << 2, 0x51 << 2),

#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+5*HEIGHT+5*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 320 << 5, 0 << 5, 0xb2 << 2, 0xaf << 2),

#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 322 << 5, 0 << 5, 0x4d << 2, 0x51 << 2),

#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 324 << 5, 0 << 5, 0xb5 << 2, 0xaf << 2),

#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 326 << 5, 0 << 5, 0x4c << 2, 0x55 << 2),

#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 328 << 5, 0 << 5, 0xb6 << 2, 0xaf << 2),

#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 330 << 5, 0 << 5, 0x49 << 2, 0x50 << 2),

#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 332 << 5, 0 << 5, 0xa7 << 2, 0xaf << 2),

#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 334 << 5, 0 << 5, 0x4a << 2, 0x55 << 2),

#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 336 << 5, 0 << 5, 0xbc << 2, 0xab << 2),

#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 338 << 5, 0 << 5, 0x4b << 2, 0x56 << 2),

#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 340 << 5, 0 << 5, 0xb7 << 2, 0xab << 2),

#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 342 << 5, 0 << 5, 0x49 << 2, 0x57 << 2),

#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 344 << 5, 0 << 5, 0xb7 << 2, 0xa9 << 2),

#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 346 << 5, 0 << 5, 0x44 << 2, 0x55 << 2),

#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 348 << 5, 0 << 5, 0xb1 << 2, 0xad << 2),

#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 350 << 5, 0 << 5, 0x4e << 2, 0x52 << 2),

#undef XOFF
#define XOFF (X0+16*WIDTH+16*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 352 << 5, 0 << 5, 0x30 << 2, 0x2d << 2),

#undef XOFF
#define XOFF (X0+17*WIDTH+17*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 354 << 5, 0 << 5, 0x4f << 2, 0xd3 << 2),

#undef XOFF
#define XOFF (X0+18*WIDTH+18*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 356 << 5, 0 << 5, 0xb0 << 2, 0x2c << 2),

#undef XOFF
#define XOFF (X0+19*WIDTH+19*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 358 << 5, 0 << 5, 0x4f << 2, 0xd3 << 2),

#undef XOFF
#define XOFF (X0+20*WIDTH+20*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 360 << 5, 0 << 5, 0xa0 << 2, 0x2c << 2),

#undef XOFF
#define XOFF (X0+21*WIDTH+21*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 362 << 5, 0 << 5, 0x4f << 2, 0xd3 << 2),

#undef XOFF
#define XOFF (X0+22*WIDTH+22*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 364 << 5, 0 << 5, 0xb3 << 2, 0x27 << 2),

#undef XOFF
#define XOFF (X0+23*WIDTH+23*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 366 << 5, 0 << 5, 0x4c << 2, 0xd9 << 2),

#undef XOFF
#define XOFF (X0+24*WIDTH+24*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 368 << 5, 0 << 5, 0xb1 << 2, 0x2e << 2),

#undef XOFF
#define XOFF (X0+25*WIDTH+25*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 370 << 5, 0 << 5, 0x4d << 2, 0xd4 << 2),

#undef XOFF
#define XOFF (X0+26*WIDTH+26*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 372 << 5, 0 << 5, 0xb3 << 2, 0x26 << 2),

#undef XOFF
#define XOFF (X0+27*WIDTH+27*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 374 << 5, 0 << 5, 0x4c << 2, 0xd7 << 2),

#undef XOFF
#define XOFF (X0+28*WIDTH+28*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 376 << 5, 0 << 5, 0xb3 << 2, 0x28 << 2),

#undef XOFF
#define XOFF (X0+29*WIDTH+29*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 378 << 5, 0 << 5, 0x4c << 2, 0xd7 << 2),

#undef XOFF
#define XOFF (X0+30*WIDTH+30*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 380 << 5, 0 << 5, 0xb3 << 2, 0x28 << 2),

#undef XOFF
#define XOFF (X0+31*WIDTH+31*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 382 << 5, 0 << 5, 0x4d << 2, 0xd3 << 2),

#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+6*HEIGHT+6*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 384 << 5, 0 << 5, 0x93 << 2, 0x2d << 2),

#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 386 << 5, 0 << 5, 0x60 << 2, 0xd3 << 2),

#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 388 << 5, 0 << 5, 0x95 << 2, 0x2d << 2),

#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 390 << 5, 0 << 5, 0x67 << 2, 0xd3 << 2),

#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 392 << 5, 0 << 5, 0x9c << 2, 0x2f << 2),

#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 394 << 5, 0 << 5, 0x62 << 2, 0xd3 << 2),

#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 396 << 5, 0 << 5, 0x91 << 2, 0x2d << 2),

#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 398 << 5, 0 << 5, 0x6d << 2, 0xd7 << 2),

#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 400 << 5, 0 << 5, 0x95 << 2, 0x2d << 2),

#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 402 << 5, 0 << 5, 0x6e << 2, 0xd1 << 2),

#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 404 << 5, 0 << 5, 0x94 << 2, 0x2d << 2),

#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 406 << 5, 0 << 5, 0x6b << 2, 0xd2 << 2),

#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 408 << 5, 0 << 5, 0x94 << 2, 0x2d << 2),

#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 410 << 5, 0 << 5, 0x6b << 2, 0x52 << 2),

#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 412 << 5, 0 << 5, 0x14 << 2, 0x2d << 2),

#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 414 << 5, 0 << 5, 0xf9 << 2, 0xde << 2),

#undef XOFF
#define XOFF (X0+16*WIDTH+16*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 416 << 5, 0 << 5, 0x1e << 2, 0x35 << 2),

#undef XOFF
#define XOFF (X0+17*WIDTH+17*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 418 << 5, 0 << 5, 0xe1 << 2, 0xca << 2),

#undef XOFF
#define XOFF (X0+18*WIDTH+18*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 420 << 5, 0 << 5, 0x1f << 2, 0x3d << 2),

#undef XOFF
#define XOFF (X0+19*WIDTH+19*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 422 << 5, 0 << 5, 0xe1 << 2, 0xc6 << 2),

#undef XOFF
#define XOFF (X0+20*WIDTH+20*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 424 << 5, 0 << 5, 0x19 << 2, 0x39 << 2),

#undef XOFF
#define XOFF (X0+21*WIDTH+21*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 426 << 5, 0 << 5, 0xe8 << 2, 0xc7 << 2),

#undef XOFF
#define XOFF (X0+22*WIDTH+22*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 428 << 5, 0 << 5, 0x17 << 2, 0x30 << 2),

#undef XOFF
#define XOFF (X0+23*WIDTH+23*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 430 << 5, 0 << 5, 0xed << 2, 0xcd << 2),

#undef XOFF
#define XOFF (X0+24*WIDTH+24*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 432 << 5, 0 << 5, 0x17 << 2, 0x32 << 2),

#undef XOFF
#define XOFF (X0+25*WIDTH+25*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 434 << 5, 0 << 5, 0xe8 << 2, 0xcd << 2),

#undef XOFF
#define XOFF (X0+26*WIDTH+26*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 436 << 5, 0 << 5, 0x17 << 2, 0x32 << 2),

#undef XOFF
#define XOFF (X0+27*WIDTH+27*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 438 << 5, 0 << 5, 0xe8 << 2, 0xcd << 2),

#undef XOFF
#define XOFF (X0+28*WIDTH+28*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 440 << 5, 0 << 5, 0x17 << 2, 0x32 << 2),

	/*
	gsSPTextureRectangle(4*24, 4*24, 4*24 + 4*WIDTH - 4,
		 4*24 + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 440 << 5, 0 << 5, 0x17 << 2, 0x32 << 2),
	*/

#undef XOFF
#define XOFF (X0+29*WIDTH+29*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 442 << 5, 0 << 5, 0xf9 << 2, 0xd5 << 2),

#undef XOFF
#define XOFF (X0+30*WIDTH+30*4)
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 444 << 5, 0 << 5, 0x6 << 2, 0x33 << 2),

/* number of possible discards: 110 */
    gsSPEndDisplayList(),
};
/* end of Test 5 */

/*
 * TO ADD A TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx display list must be extern'd in tf.h, then
 * added to the 'testList_tf' table in tf.c as a Gfx pointer field of a
 * GfxTest_t struct.  You must also decide whether the existing top level DL's
 * will suffice for your application (you may need to provide a new top level
 * DL of your own design in toplevel.c).
 *
 */
