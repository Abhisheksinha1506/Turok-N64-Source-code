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
 * File:	tm_static.c
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:
 *
 * This file holds tiny display list segments that are 'static' data, for use
 * by the texture memory test module in tm.c
 *
 * If you feel the urge to modify a test, see the comment at
 * the top of main.c for details.
 */

#include <ultra64.h>
#include "dldriver.h"
#include "texture.h"

/*
 * Test conventions:
 *
 * Data variable names can be about anything, as long as they are unique
 * and consistent in the table entry.
 *
 * In order to get around compiler weirdness, the table of tests
 * is in tm.c, and the Gfx lists must be extern'd in rdpvector.h
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
static Vtx tm_place_vtx[5] =  {
/*     x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */	
    { -40,  40,    0,    0,	0,	0,	0xff,     0,     0,	0xff },/* R */ 
    {  40,  40,    0,    0,	0,	0,	   0,  0xff,     0,	0xff },/* G */ 
    {  40, -40,    0,    0,	0,	0,	   0,     0,  0xff,	0xff },/* B */ 
    { -40, -40,    0,    0,	0,	0,	0xff,  0xff,     0,	0xff },/* Y */ 
    {   0,   0,    0,    0,	0,	0,	0xff,  0xff,  0xff,	0xff },/* W */ 
};

Gfx TM_placebo_dl[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&tm_place_vtx, 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};
/* end of case 0 */

/*
 * Test 1
 *
 * Type RGBA, size 16b
 *
 * Textues of a5, 5a, rand, rand complement
 * 1 Cycle and Copy modes, tmem low and high
 * 
 */
#define XBASE 15
#define YBASE 15
#define X0 XBASE
#define Y0 YBASE
#define TEX_WIDTH 32
#define TEX_HEIGHT 32

Gfx TM_RGBA16_dl[MAX_STATIC_GFX_SIZE] = {

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_BILERP),

    /* display a5 pattern */

#define XOFF 2*X0
#define YOFF (2*Y0+8*HEIGHT+16)
#define WIDTH 32
#define HEIGHT 32

    gsDPLoadTextureBlock(map_a5, G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 TEX_WIDTH, 2*TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_COPY),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, 
			OS_K0_TO_PHYSICAL(cfb_16_a)),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 0, 0, (4096*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (2*X0+2*WIDTH+8)

    /* access high tmem */
    gsDPLoadSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 256, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 0, 0, (4096*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),
    gsDPPipeSync(),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD, 
			OS_K0_TO_PHYSICAL(cfb_16_a)),

#undef WIDTH
#undef HEIGHT
#define WIDTH 64
#define HEIGHT 64
#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF Y0

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),

    /* access low tmem */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH+4)

    /* access high tmem */
    gsDPLoadSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 256, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    /* display random pattern */

#undef XOFF
#define XOFF 2*X0
#undef YOFF
#define YOFF (2*Y0+10*HEIGHT+24)
#undef WIDTH
#undef HEIGHT
#define WIDTH 32
#define HEIGHT 32

    gsDPLoadTextureBlock(map_rand, G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 TEX_WIDTH, 2*TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPPipeSync(),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, 
			OS_K0_TO_PHYSICAL(cfb_16_a)),
    gsDPSetCycleType(G_CYC_COPY),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 0, 0, (4096*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (2*X0+2*WIDTH+8)

    /* access high tmem */
    gsDPLoadSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 256, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 0, 0, (4096*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),
    gsDPPipeSync(),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD, 
			OS_K0_TO_PHYSICAL(cfb_16_a)),

#undef WIDTH
#undef HEIGHT
#define WIDTH 64
#define HEIGHT 64
#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+HEIGHT+4)

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),

    /* access low tmem */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH+4)

    /* access high tmem */
    gsDPLoadSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 256, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    /* display 5a pattern */

#undef XOFF
#define XOFF (2*X0+4*WIDTH+16)
#undef YOFF
#define YOFF (2*Y0+8*HEIGHT+16)
#undef WIDTH
#undef HEIGHT
#define WIDTH 32
#define HEIGHT 32

    gsDPLoadTextureBlock(map_5a, G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 TEX_WIDTH, 2*TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_COPY),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, 
			OS_K0_TO_PHYSICAL(cfb_16_a)),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 0, 0, (4096*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (2*X0+6*WIDTH+24)

    /* access high tmem */
    gsDPLoadSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 256, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 0, 0, (4096*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),
    gsDPPipeSync(),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD, 
			OS_K0_TO_PHYSICAL(cfb_16_a)),

#undef WIDTH
#undef HEIGHT
#define WIDTH 64
#define HEIGHT 64
#undef XOFF
#define XOFF (X0+2*WIDTH+8)
#undef YOFF
#define YOFF Y0

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),

    /* access low tmem */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+3*WIDTH+12)

    /* access high tmem */
    gsDPLoadSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 256, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    /* display random pattern complement */

#undef XOFF
#define XOFF (2*X0+4*WIDTH+16)
#undef YOFF
#define YOFF (2*Y0+10*HEIGHT+24)
#undef WIDTH
#undef HEIGHT
#define WIDTH 32
#define HEIGHT 32

    gsDPLoadTextureBlock(map_rand_comp, G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 TEX_WIDTH, 2*TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_COPY),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, 
			OS_K0_TO_PHYSICAL(cfb_16_a)),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 0, 0, (4096*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (2*X0+6*WIDTH+24)

    /* access high tmem */
    gsDPLoadSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 256, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 0, 0, (4096*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),
    gsDPPipeSync(),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD, 
			OS_K0_TO_PHYSICAL(cfb_16_a)),

#undef WIDTH
#undef HEIGHT
#define WIDTH 64
#define HEIGHT 64
#undef XOFF
#define XOFF (X0+2*WIDTH+8)
#undef YOFF
#define YOFF (Y0+HEIGHT+4)

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),

    /* access low tmem */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+3*WIDTH+12)

    /* access high tmem */
    gsDPLoadSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 256, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    gsSPEndDisplayList(),
};
/* end of Test 1 */

/*
 * Test 2
 *
 * Type RGBA, size 32b
 *
 * Textues of a5, 5a, rand, rand complement
 * 1 Cycle modes, tmem low and high
 * 
 */
Gfx TM_RGBA32_dl[MAX_STATIC_GFX_SIZE] = {

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_BILERP),

    /* display a5 pattern */

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF Y0
#undef WIDTH
#define WIDTH 32
#undef HEIGHT
#define HEIGHT 16

    gsDPLoadTextureBlock(map_a5, G_IM_FMT_RGBA, G_IM_SIZ_32b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

    /* tile 0 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(0, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 0,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 1 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 4, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 1,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+HEIGHT)

    /* tile 2 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 64, 2, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(2, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 2,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 3 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 64+4, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(3, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 3,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+2*HEIGHT)

    /* tile 4 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 128, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 4,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 5 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 128+4, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 5,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+3*HEIGHT)

    /* tile 6 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 192, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 6,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 7 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 192+4, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(7, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 7,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

    /* display 5a pattern */

#undef X0
#define X0 (XBASE+64+4)
#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF Y0
#undef WIDTH
#define WIDTH 32
#undef HEIGHT
#define HEIGHT 16

    gsDPLoadTextureBlock(map_5a, G_IM_FMT_RGBA, G_IM_SIZ_32b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

    /* tile 1 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 0, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 1,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 0 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 4, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(0, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 0,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+HEIGHT)

    /* tile 3 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 64, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(3, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 3,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 2 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 64+4, 2, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(2, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 2,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+2*HEIGHT)

    /* tile 5 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 128, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 5,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 4 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 128+4, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 4,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+3*HEIGHT)

    /* tile 7 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 192, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(7, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 7,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 6 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 192+4, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 6,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

    /* display random pattern */

#undef X0
#define X0 (XBASE+2*64+2*4)
#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF Y0
#undef WIDTH
#define WIDTH 32
#undef HEIGHT
#define HEIGHT 16

    gsDPLoadTextureBlock(map_rand, G_IM_FMT_RGBA, G_IM_SIZ_32b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

    /* tile 0 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(0, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 0,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 4 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 4, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 4,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+HEIGHT)

    /* tile 1 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 64, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 1,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 5 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 64+4, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 5,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+2*HEIGHT)

    /* tile 2 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 128, 2, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(2, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 2,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 6 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 128+4, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 6,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+3*HEIGHT)

    /* tile 3 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 192, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(3, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 3,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 7 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 192+4, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(7, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 7,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

    /* display random pattern complement */

#undef X0
#define X0 (XBASE+3*64+3*4)
#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF Y0
#undef WIDTH
#define WIDTH 32
#undef HEIGHT
#define HEIGHT 16

    gsDPLoadTextureBlock(map_rand_comp, G_IM_FMT_RGBA, G_IM_SIZ_32b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

    /* tile 3 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 0, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(3, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 3,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 4 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 4, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 4,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+HEIGHT)

    /* tile 5 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 64, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 5,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 6 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 64+4, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 6,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+2*HEIGHT)

    /* tile 7 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 128, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(7, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 7,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 0 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 128+4, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(0, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 0,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+3*HEIGHT)

    /* tile 1 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 192, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 1,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 2 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 192+4, 2, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(2, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 2,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

    gsSPEndDisplayList(),
};
/* end of Test 2 */

/*
 * Test 3
 *
 * Type YUV, size 16b
 *
 * Textues of a5, 5a, rand, rand complement
 * 1 Cycle modes, tmem low and high
 * 
 */
#define MY_K0   (175 & 0x1ff)
#define MY_K1   (-43 & 0x1ff)
#define MY_K2   (-89 & 0x1ff)
#define MY_K3   (222 & 0x1ff)
#define MY_K4   (114 & 0x1ff)
#define MY_K5   (42 & 0x1ff)

Gfx TM_YUV_dl[MAX_STATIC_GFX_SIZE] = {

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),

    gsDPSetTextureConvert(G_TC_FILTCONV),
    gsDPSetConvert(MY_K0, MY_K1, MY_K2, MY_K3, MY_K4, MY_K5),
    gsDPSetCombineMode(G_CC_YUV2RGB, G_CC_PASS2),

    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_BILERP),

    /* display a5 pattern */

#undef X0
#define X0 XBASE
#undef Y0
#define Y0 YBASE
#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF Y0
#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42
#undef WIDTH
#define WIDTH 32 
#undef HEIGHT
#define HEIGHT 16

    gsDPLoadTextureBlock(map_a5, G_IM_FMT_YUV, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

    /* tile 0 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(0, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 0,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 1 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 2, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 1,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+HEIGHT)

    /* tile 2 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 59, 2, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(2, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 2,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 3 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 59+3, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(3, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 3,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+2*HEIGHT)

    /* tile 4 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 119, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 4,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 5 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 119+3, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 5,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+3*HEIGHT)

    /* tile 6 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 179, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 6,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 7 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 179+3, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(7, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 7,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

    /* display 5a pattern */

#undef X0
#define X0 (XBASE+64+4)
#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF Y0
#undef WIDTH
#define WIDTH 32 
#undef HEIGHT
#define HEIGHT 16

    gsDPLoadTextureBlock(map_5a, G_IM_FMT_YUV, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

    /* tile 1 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 0, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 1,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 0 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 2, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(0, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 0,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+HEIGHT)

    /* tile 3 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 59, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(3, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 3,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 2 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 59+3, 2, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(2, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 2,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+2*HEIGHT)

    /* tile 5 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 119, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 5,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 4 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 119+3, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 4,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+3*HEIGHT)

    /* tile 7 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 179, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(7, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 7,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 6 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 179+3, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 6,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

    /* display random pattern */

#undef X0
#define X0 (XBASE+2*64+2*4)
#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF Y0
#undef WIDTH
#define WIDTH 32 
#undef HEIGHT
#define HEIGHT 16

    gsDPLoadTextureBlock(map_rand, G_IM_FMT_YUV, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

    /* tile 0 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(0, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 0,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 4 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 2, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 4,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+HEIGHT)

    /* tile 1 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 59, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 1,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 5 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 59+3, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 5,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+2*HEIGHT)

    /* tile 2 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 119, 2, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(2, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 2,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 6 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 119+3, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 6,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+3*HEIGHT)

    /* tile 3 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 179, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(3, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 3,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 7 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 179+3, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(7, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 7,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

    /* display random pattern complement */

#undef X0
#define X0 (XBASE+3*64+3*4)
#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF Y0
#undef WIDTH
#define WIDTH 32 
#undef HEIGHT
#define HEIGHT 16

    gsDPLoadTextureBlock(map_rand_comp, G_IM_FMT_YUV, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

    /* tile 3 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 0, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(0, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 3,
		 0, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 4 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 2, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 4,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+HEIGHT)

    /* tile 5 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 59, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 5,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 6 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 59+3, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 6,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+2*HEIGHT)

    /* tile 7 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 119, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(7, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 7,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 0 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 119+3, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(0, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 0,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+3*HEIGHT)

    /* tile 1 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 179, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 1,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH)

    /* tile 2 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 179+3, 2, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(2, 0, 0,
		 ((TEX_WIDTH)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((TEX_HEIGHT)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 2,
		 8<<5, 0, (512*TEX_WIDTH)/WIDTH, (256*TEX_HEIGHT)/HEIGHT),

    gsSPEndDisplayList(),
};
/* end of Test 3 */

/*
 * Test 4
 *
 * Type IA, sizes 16b, 8b, 4b
 *
 * Textues of a5, 5a, rand, rand complement
 * 1 Cycle mode, tmem low and high
 * 
 */

Gfx TM_IA_dl[MAX_STATIC_GFX_SIZE] = {

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_BILERP),

    /* display a5 pattern */

#undef X0
#define X0 XBASE
#undef Y0
#define Y0 YBASE
#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF Y0
#undef WIDTH
#define WIDTH 32 
#undef HEIGHT
#define HEIGHT 32

#undef TEX_WIDTH
#define TEX_WIDTH 64
#undef TEX_HEIGHT
#define TEX_HEIGHT 32
    gsDPLoadTextureBlock(map_a5, G_IM_FMT_IA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42
    /* fmt IA size 16b */
    gsDPPipeSync(),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 72
#undef TEX_HEIGHT
#define TEX_HEIGHT 56
#undef YOFF
#define YOFF (Y0+HEIGHT+4)

    /* fmt IA size 8b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 96
#undef TEX_HEIGHT
#define TEX_HEIGHT 85
#undef YOFF
#define YOFF (Y0+2*HEIGHT+8)

    /* fmt IA size 4b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    /* display rand pattern */

#undef XOFF
#define XOFF (XBASE+WIDTH+4)
#undef YOFF
#define YOFF Y0
#undef TEX_WIDTH
#define TEX_WIDTH 64
#undef TEX_HEIGHT
#define TEX_HEIGHT 32
    gsDPLoadTextureBlock(map_rand, G_IM_FMT_IA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42

    /* fmt IA size 16b */
    gsDPPipeSync(),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 72
#undef TEX_HEIGHT
#define TEX_HEIGHT 56
#undef YOFF
#define YOFF (Y0+HEIGHT+4)

    /* fmt IA size 8b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 96
#undef TEX_HEIGHT
#define TEX_HEIGHT 85
#undef YOFF
#define YOFF (Y0+2*HEIGHT+8)

    /* fmt IA size 4b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    /* display 5a pattern */

#undef XOFF
#define XOFF (XBASE+2*WIDTH+8)
#undef YOFF
#define YOFF Y0
#undef TEX_WIDTH
#define TEX_WIDTH 64
#undef TEX_HEIGHT
#define TEX_HEIGHT 32
    gsDPLoadTextureBlock(map_5a, G_IM_FMT_IA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42

    /* fmt IA size 16b */
    gsDPPipeSync(),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 72
#undef TEX_HEIGHT
#define TEX_HEIGHT 56
#undef YOFF
#define YOFF (Y0+HEIGHT+4)

    /* fmt IA size 8b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 96
#undef TEX_HEIGHT
#define TEX_HEIGHT 85
#undef YOFF
#define YOFF (Y0+2*HEIGHT+8)

    /* fmt IA size 4b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    /* display rand_comp pattern */

#undef XOFF
#define XOFF (XBASE+3*WIDTH+12)
#undef YOFF
#define YOFF Y0
#undef TEX_WIDTH
#define TEX_WIDTH 64
#undef TEX_HEIGHT
#define TEX_HEIGHT 32
    gsDPLoadTextureBlock(map_rand_comp, G_IM_FMT_IA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42
    /*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_IA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    */

    /* fmt IA size 16b */
    gsDPPipeSync(),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 72
#undef TEX_HEIGHT
#define TEX_HEIGHT 56
#undef YOFF
#define YOFF (Y0+HEIGHT+4)
    /*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_IA, G_IM_SIZ_8b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    */

    /* fmt IA size 8b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 96
#undef TEX_HEIGHT
#define TEX_HEIGHT 85
#undef YOFF
#define YOFF (Y0+2*HEIGHT+8)
    /*
    gsDPLoadTextureBlock_4b(pyra, G_IM_FMT_IA,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    */

    /* fmt IA size 4b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    gsSPEndDisplayList(),
};
/* end of Test 4 */

/*
 * Test 5
 *
 * Type I, sizes 4b and 8b
 *
 * Textues of a5, 5a, rand, rand complement
 * 1 Cycle modes, tmem low and high
 * 
 */

Gfx TM_I_dl[MAX_STATIC_GFX_SIZE] = {

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_BILERP),

    /* display a5 pattern */

#undef X0
#define X0 XBASE
#undef Y0
#define Y0 YBASE
#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF Y0
#undef WIDTH
#define WIDTH 32 
#undef HEIGHT
#define HEIGHT 32

#undef TEX_WIDTH
#define TEX_WIDTH 64
#undef TEX_HEIGHT
#define TEX_HEIGHT 32
    gsDPLoadTextureBlock(map_a5, G_IM_FMT_IA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef TEX_WIDTH
#define TEX_WIDTH 72
#undef TEX_HEIGHT
#define TEX_HEIGHT 56

    /* fmt I size 8b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 96
#undef TEX_HEIGHT
#define TEX_HEIGHT 85
#undef YOFF
#define YOFF (Y0+HEIGHT+4)

    /* fmt I size 4b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    /* display rand pattern */

#undef XOFF
#define XOFF (XBASE+WIDTH+4)
#undef YOFF
#define YOFF Y0
#undef TEX_WIDTH
#define TEX_WIDTH 64
#undef TEX_HEIGHT
#define TEX_HEIGHT 32
    gsDPLoadTextureBlock(map_rand, G_IM_FMT_IA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef TEX_WIDTH
#define TEX_WIDTH 72
#undef TEX_HEIGHT
#define TEX_HEIGHT 56

    /* fmt I size 8b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 96
#undef TEX_HEIGHT
#define TEX_HEIGHT 85
#undef YOFF
#define YOFF (Y0+HEIGHT+4)

    /* fmt I size 4b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    /* display 5a pattern */

#undef XOFF
#define XOFF (XBASE+2*WIDTH+8)
#undef YOFF
#define YOFF Y0
#undef TEX_WIDTH
#define TEX_WIDTH 64
#undef TEX_HEIGHT
#define TEX_HEIGHT 32
    gsDPLoadTextureBlock(map_5a, G_IM_FMT_IA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef TEX_WIDTH
#define TEX_WIDTH 72
#undef TEX_HEIGHT
#define TEX_HEIGHT 56

    /* fmt I size 8b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 96
#undef TEX_HEIGHT
#define TEX_HEIGHT 85
#undef YOFF
#define YOFF (Y0+HEIGHT+4)

    /* fmt I size 4b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    /* display rand_comp pattern */

#undef XOFF
#define XOFF (XBASE+3*WIDTH+12)
#undef YOFF
#define YOFF Y0
#undef TEX_WIDTH
#define TEX_WIDTH 64
#undef TEX_HEIGHT
#define TEX_HEIGHT 32
    gsDPLoadTextureBlock(map_rand_comp, G_IM_FMT_IA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef TEX_WIDTH
#define TEX_WIDTH 72
#undef TEX_HEIGHT
#define TEX_HEIGHT 56
    /*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_I, G_IM_SIZ_8b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    */

    /* fmt I size 8b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 96
#undef TEX_HEIGHT
#define TEX_HEIGHT 85
#undef YOFF
#define YOFF (Y0+HEIGHT+4)
    /*
    gsDPLoadTextureBlock_4b(pyra, G_IM_FMT_I,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    */

    /* fmt I size 4b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    gsSPEndDisplayList(),
};
/* end of Test 5 */

/*
 * Test 6
 *
 * Type CI, sizes 4b and 8b
 *
 * Textues of a5, 5a, rand, rand complement
 * 1 Cycle modes, tmem low and high
 * 
 */

Gfx TM_CI_dl[MAX_STATIC_GFX_SIZE] = {

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureLUT(G_TT_RGBA16),

    /* display a5 pattern */

#undef X0
#define X0 XBASE
#undef Y0
#define Y0 YBASE
#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF Y0
#undef WIDTH
#define WIDTH 32 
#undef HEIGHT
#define HEIGHT 32

#undef TEX_WIDTH
#define TEX_WIDTH 64
#undef TEX_HEIGHT
#define TEX_HEIGHT 32
    gsDPLoadTextureBlock(map_a5, G_IM_FMT_IA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42

    /* fmt CI size 8b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 80
#undef TEX_HEIGHT
#define TEX_HEIGHT 51
#undef YOFF
#define YOFF (Y0+HEIGHT+4)

    /* fmt CI size 4b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    /* display rand pattern */

#undef XOFF
#define XOFF (XBASE+WIDTH+4)
#undef YOFF
#define YOFF Y0
#undef TEX_WIDTH
#define TEX_WIDTH 64
#undef TEX_HEIGHT
#define TEX_HEIGHT 32
    gsDPLoadTextureBlock(map_rand, G_IM_FMT_IA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42

    /* fmt CI size 8b */
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_IA16),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 80
#undef TEX_HEIGHT
#define TEX_HEIGHT 51
#undef YOFF
#define YOFF (Y0+HEIGHT+4)

    /* fmt CI size 4b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, G_TX_RENDERTILE, 4, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    /* display 5a pattern */

#undef XOFF
#define XOFF (XBASE+2*WIDTH+8)
#undef YOFF
#define YOFF Y0
#undef TEX_WIDTH
#define TEX_WIDTH 64
#undef TEX_HEIGHT
#define TEX_HEIGHT 32
    gsDPLoadTextureBlock(map_5a, G_IM_FMT_IA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42

    /* fmt CI size 8b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 80
#undef TEX_HEIGHT
#define TEX_HEIGHT 51
#undef YOFF
#define YOFF (Y0+HEIGHT+4)
    /*
    gsDPLoadTLUT_pal16(8,pyratlut),
    gsDPPipeSync(),
    gsDPLoadTextureBlock_4b(pyra, G_IM_FMT_CI,
	TEX_WIDTH, TEX_HEIGHT, 0,
	G_TX_MIRROR, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    */

    /* fmt CI size 4b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, G_TX_RENDERTILE, 8, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    /* display rand_comp pattern */

#undef XOFF
#define XOFF (XBASE+3*WIDTH+12)
#undef YOFF
#define YOFF Y0
#undef TEX_WIDTH
#define TEX_WIDTH 64
#undef TEX_HEIGHT
#define TEX_HEIGHT 32
    gsDPLoadTextureBlock(map_rand_comp, G_IM_FMT_IA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42
    /*
    gsDPLoadTLUT_pal256(pyratlut),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(pyra, G_IM_FMT_CI, G_IM_SIZ_8b,
	TEX_WIDTH, TEX_HEIGHT, 0,
	G_TX_MIRROR, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    */

    /* fmt CI size 8b */
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef TEX_WIDTH
#define TEX_WIDTH 80
#undef TEX_HEIGHT
#define TEX_HEIGHT 51
#undef YOFF
#define YOFF (Y0+HEIGHT+4)
    /*
    gsDPLoadTLUT_pal16(12,pyratlut),
    gsDPPipeSync(),
    gsDPLoadTextureBlock_4b(pyra, G_IM_FMT_CI,
	TEX_WIDTH, TEX_HEIGHT, 0,
	G_TX_MIRROR, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    */

    /* fmt CI size 4b */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, G_TX_RENDERTILE, 12, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    gsSPEndDisplayList(),
};
/* end of Test 6 */

/*
 * Test 7
 * 
 *
 * All types and sizes, compressed test
 *
 * Textues of rand
 * 1 Cycle modes, tmem low and high
 * 
 */

Gfx TM_all_dl[MAX_STATIC_GFX_SIZE] = {

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetEnvColor (0xff, 0xff, 0xff, 0x80),
#define CC_OP    TEXEL0, 0, ENV_ALPHA, 0, 0, 0, 0, TEXEL0
#define CC_OP2   COMBINED, TEXEL0, TEXEL0_ALPHA, TEXEL0, 0, 0, 0, TEXEL0
    gsDPSetCombineMode(CC_OP, CC_OP2),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_BILERP),

#undef X0
#define X0 XBASE
#undef Y0
#define Y0 (YBASE+8+4)
#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF Y0
#undef WIDTH
#define WIDTH 32 
#undef HEIGHT
#define HEIGHT 32

#undef TEX_WIDTH
#define TEX_WIDTH 64
#undef TEX_HEIGHT
#define TEX_HEIGHT 32

    /* display rand pattern */

    gsDPLoadTextureBlock(map_rand, G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42
	/*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_RGBA, G_IM_SIZ_16b,
    TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
	*/

    /* fmt RGBA size 16b */
    /* tile 0 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH+4)
#undef TEX_WIDTH
#define TEX_WIDTH 32
#undef TEX_HEIGHT
#define TEX_HEIGHT 32
	/*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_RGBA, G_IM_SIZ_32b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
	*/

    /* fmt RGBA size 32b */
    /* tile 1 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b,
		 (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 0, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b,
		 (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 0, 2, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(2, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 1,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+2*WIDTH+8)
#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42

    /* fmt YUV size 16b */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),

    gsDPSetTextureConvert(G_TC_FILTCONV),
    gsDPSetConvert(MY_K0, MY_K1, MY_K2, MY_K3, MY_K4, MY_K5),
    gsDPSetCombineMode(G_CC_YUV2RGB, G_CC_PASS2),

	/*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_YUV, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
	*/

    /* tile 2 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 0, 2, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(2, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 2,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+3*WIDTH+12)
#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42

    /* fmt CI size 8b */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
#undef CC_OP
#define CC_OP    TEXEL0, 0, ENV_ALPHA, 0, 0, 0, 0, TEXEL0
#undef CC_OP2
#define CC_OP2   COMBINED, TEXEL0, TEXEL0_ALPHA, TEXEL0, 0, 0, 0, TEXEL0
    gsDPSetCombineMode(CC_OP, CC_OP2),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_RGBA16),

	/*
    gsDPLoadTLUT_pal256(pyratlut),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(pyra, G_IM_FMT_CI, G_IM_SIZ_8b,
	TEX_WIDTH, TEX_HEIGHT, 0,
	G_TX_MIRROR, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
	*/

    /* tile 3 */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(3, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 3,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+4*WIDTH+16)
#undef TEX_WIDTH
#define TEX_WIDTH 80
#undef TEX_HEIGHT
#define TEX_HEIGHT 51
	/*
    gsDPLoadTLUT_pal16(15,pyratlut),
    gsDPPipeSync(),
    gsDPLoadTextureBlock_4b(pyra, G_IM_FMT_CI,
		TEX_WIDTH, TEX_HEIGHT, 0,
		G_TX_MIRROR, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
	*/

    /* fmt CI size 4b */
    /* tile 4 */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 4,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, 4, 15, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, 5, 15, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 4,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+HEIGHT+4)
#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42
	/*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_IA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    */

    /* fmt IA size 16b */
    /* tile 5 */
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b,
		 (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b,
		 (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 5,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+WIDTH+4)
#undef TEX_WIDTH
#define TEX_WIDTH 72
#undef TEX_HEIGHT
#define TEX_HEIGHT 56
	/*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_IA, G_IM_SIZ_8b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
	*/

    /* fmt IA size 8b */
    /* tile 6 */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b,
		 (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b,
		 (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(7, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 6,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+2*WIDTH+8)
#undef TEX_WIDTH
#define TEX_WIDTH 96
#undef TEX_HEIGHT
#define TEX_HEIGHT 85
	/*
    gsDPLoadTextureBlock_4b(pyra, G_IM_FMT_IA,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
	*/

    /* fmt IA size 4b */
    /* tile 7 */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(7, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 7,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+3*WIDTH+12)
#undef TEX_WIDTH
#define TEX_WIDTH 72
#undef TEX_HEIGHT
#define TEX_HEIGHT 56
	/*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_I, G_IM_SIZ_8b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    */

    /* fmt I size 8b */
    /* tile 3 */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b,
		 (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(3, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b,
		 (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 3,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (X0+4*WIDTH+16)
#undef TEX_WIDTH
#define TEX_WIDTH 96
#undef TEX_HEIGHT
#define TEX_HEIGHT 85
	/*
    gsDPLoadTextureBlock_4b(pyra, G_IM_FMT_I,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    */

    /* fmt I size 4b */
    /* tile 5 */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 5,
		 0, 0, (1024*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+2*32+8)

#undef TEX_WIDTH
#define TEX_WIDTH 64
#undef TEX_HEIGHT
#define TEX_HEIGHT 32

    /* display rand_comp pattern */

    gsDPSetTextureFilter(G_TF_AVERAGE),
    gsDPLoadTextureBlock(map_rand_comp, G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42
#define OFFS 16*(TEX_WIDTH-WIDTH+1)
#define OFFT 16*(TEX_HEIGHT-HEIGHT+1)
	/*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
	*/

    /* fmt RGBA size 16b */
    /* tile 0 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, G_TX_RENDERTILE,
		 OFFS, OFFT, 1024, 1024),

#undef XOFF
#define XOFF (X0+WIDTH+4)
#undef TEX_WIDTH
#define TEX_WIDTH 32
#undef TEX_HEIGHT
#define TEX_HEIGHT 32
	/*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_RGBA, G_IM_SIZ_32b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    */

    /* fmt RGBA size 32b */
    /* tile 1 */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b,
		 (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 0, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b,
		 (TEX_WIDTH*G_IM_SIZ_32b_LINE_BYTES+7)/8,
		 0, 2, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(2, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 1,
		 OFFS, OFFT, 1024, 1024),

#undef XOFF
#define XOFF (X0+2*WIDTH+8)
#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42

    /* fmt YUV size 16b */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),

    gsDPSetTextureConvert(G_TC_FILTCONV),
    gsDPSetConvert(MY_K0, MY_K1, MY_K2, MY_K3, MY_K4, MY_K5),
    gsDPSetCombineMode(G_CC_YUV2RGB, G_CC_PASS2),

	/*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_YUV, G_IM_SIZ_16b,
		 TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    */

    /* tile 2 */
    gsDPSetTile(G_IM_FMT_YUV, G_IM_SIZ_16b, (TEX_WIDTH+7)/8,
		 0, 2, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(2, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 2,
		 OFFS, OFFT, 1024, 1024),

#undef XOFF
#define XOFF (X0+3*WIDTH+12)
#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42

    /* fmt CI size 8b */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetCombineMode(CC_OP, CC_OP2),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_RGBA16),

	/*
    gsDPLoadTLUT_pal256(pyratlut),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPPipeSync(),
    gsDPLoadTextureBlock(pyra, G_IM_FMT_CI, G_IM_SIZ_8b,
	TEX_WIDTH, TEX_HEIGHT, 0,
	G_TX_MIRROR, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
	*/

    /* tile 3 */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(3, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 3,
		 OFFS, OFFT, 1024, 1024),

#undef XOFF
#define XOFF (X0+4*WIDTH+16)
#undef TEX_WIDTH
#define TEX_WIDTH 80
#undef TEX_HEIGHT
#define TEX_HEIGHT 51
#undef OFFT
#define OFFT 16*(TEX_HEIGHT-HEIGHT)
	/*
    gsDPLoadTLUT_pal16(12,pyratlut),
    gsDPPipeSync(),
    gsDPLoadTextureBlock_4b(pyra, G_IM_FMT_CI,
	TEX_WIDTH, TEX_HEIGHT, 0,
	G_TX_MIRROR, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD),
    */
    /* fmt CI size 4b */
    /* tile 4 */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, 4, 3, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, 5, 3, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 4,
		 OFFS, OFFT, 1024, 1024),

    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, 4, 12, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, 5, 12, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 4,
		 OFFS, OFFT, 1024, 1024),

#undef XOFF
#define XOFF X0
#undef YOFF
#define YOFF (Y0+3*HEIGHT+12)
#undef TEX_WIDTH
#define TEX_WIDTH 48
#undef TEX_HEIGHT
#define TEX_HEIGHT 42
#undef OFFT
#define OFFT 16*(TEX_HEIGHT-HEIGHT+1)
	/*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_IA, G_IM_SIZ_16b,
    TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
	*/

    /* fmt IA size 16b */
    /* tile 5 */
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b,
		 (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b,
		 (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 5,
		 OFFS, OFFT, 1024, 1024),

#undef XOFF
#define XOFF (X0+WIDTH+4)
#undef TEX_WIDTH
#define TEX_WIDTH 72
#undef TEX_HEIGHT
#define TEX_HEIGHT 56
	/*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_IA, G_IM_SIZ_8b,
    TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
	*/

    /* fmt IA size 8b */
    /* tile 6 */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b,
		 (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b,
		 (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(7, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 6,
		 OFFS, OFFT, 1024, 1024),

#undef XOFF
#define XOFF (X0+2*WIDTH+8)
#undef TEX_WIDTH
#define TEX_WIDTH 96
#undef TEX_HEIGHT
#define TEX_HEIGHT 85
#undef OFFT
#define OFFT 16*(TEX_HEIGHT-HEIGHT)
	/*
    gsDPLoadTextureBlock_4b(pyra, G_IM_FMT_IA,
    TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
	*/

    /* fmt IA size 4b */
    /* tile 7 */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(7, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 7,
		 OFFS, OFFT, 1024, 1024),

#undef XOFF
#define XOFF (X0+3*WIDTH+12)
#undef TEX_WIDTH
#define TEX_WIDTH 72
#undef TEX_HEIGHT
#define TEX_HEIGHT 56
#undef OFFT
#define OFFT 16*(TEX_HEIGHT-HEIGHT+1)
	/*
    gsDPLoadTextureBlock(pyra, G_IM_FMT_I, G_IM_SIZ_8b,
    TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
	*/

    /* fmt I size 8b */
    /* tile 3 */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b,
		 (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(3, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b,
		 (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(4, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 3,
		 OFFS, OFFT, 1024, 1024),

#undef XOFF
#define XOFF (X0+4*WIDTH+16)
#undef TEX_WIDTH
#define TEX_WIDTH 96
#undef TEX_HEIGHT
#define TEX_HEIGHT 85
#undef OFFT
#define OFFT 16*(TEX_HEIGHT-HEIGHT)
	/*
    gsDPLoadTextureBlock_4b(pyra, G_IM_FMT_I,
    TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
	*/

    /* fmt I size 4b */
    /* tile 5 */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(5, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, (TEX_WIDTH+15)/16,
		 0, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(6, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH,
		 4*YOFF + 4*HEIGHT, 5,
		 OFFS, OFFT, 1024, 1024),

#undef XOFF
#define XOFF (2*X0)
#undef YOFF
#define YOFF (2*Y0+8*HEIGHT+32)
#undef TEX_WIDTH
#define TEX_WIDTH 32
#undef TEX_HEIGHT
#define TEX_HEIGHT 32

    /* copy size 16b, low tmem */
    gsDPPipeSync(),
	gsDPSetTextureFilter(G_TF_BILERP),

	/*
    _gsDPLoadTextureBlock(pyra, 0, G_IM_FMT_RGBA, G_IM_SIZ_16b,
    TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
    _gsDPLoadTextureBlock(pyra, 256, G_IM_FMT_RGBA, G_IM_SIZ_16b,
    TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),
	*/

    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC,
		 ((1024)-1) << G_TEXTURE_IMAGE_FRAC),
    gsDPPipeSync(),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, 
			OS_K0_TO_PHYSICAL(cfb_16_a)),
    gsDPSetCycleType(G_CYC_COPY),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 0, 0, (4096*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (2*X0+WIDTH+8)

    /* copy size 16b, high tmem */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 (TEX_WIDTH*G_IM_SIZ_16b_LINE_BYTES+7)/8,
		 256, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 0, 0, (4096*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (4*X0)
#undef YOFF
#define YOFF (4*YBASE)
#undef TEX_WIDTH
#define TEX_WIDTH 64

    /* copy size 8b, low tmem */

    gsDPPipeSync(),
    gsDPSetColorImage(G_IM_FMT_I, G_IM_SIZ_8b, SCREEN_WD, 
			OS_K0_TO_PHYSICAL(cfb_16_a)),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b,
		 (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 0, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 0, 0, (4096*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),

#undef XOFF
#define XOFF (4*X0+WIDTH+4)

    /* copy size 8b, high tmem */
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b,
		 (TEX_WIDTH*G_IM_SIZ_8b_LINE_BYTES+7)/8,
		 256, G_TX_RENDERTILE, 0, 0, 0, 0, 0, 0, 0),
    gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 0, 0, (4096*TEX_WIDTH)/WIDTH, (1024*TEX_HEIGHT)/HEIGHT),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD, 
			OS_K0_TO_PHYSICAL(cfb_16_a)),

    gsSPEndDisplayList(),
};
/* end of Test 7 */

/*
 * TO ADD A TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx display list must be extern'd in tm.h, then
 * added to the 'testList_tm' table in tm.c as a Gfx pointer field of a
 * GfxTest_t struct.  You must also decide whether the existing top level DL's
 * will suffice for your application (you may need to provide a new top level
 * DL of your own design in toplevel.c).
 *
 */
