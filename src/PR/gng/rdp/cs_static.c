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
 * File:	cs_static.c
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:
 *
 * This file holds tiny display list segments that are 'static' data, for use
 * by the command shuffle test module in cs.c
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
 * is in cs.c, and the Gfx lists must be extern'd in rdpvector.h
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
static Vtx cs_place_vtx[5] =  {
/*     x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */	
    { -40,  40,    0,    0,	0,	0,	0xff,     0,     0,	0xff },	  /* R */   
    {  40,  40,    0,    0,	0,	0,	   0,  0xff,     0,	0xff },	  /* G */   
    {  40, -40,    0,    0,	0,	0,	   0,     0,  0xff,	0xff },	  /* B */   
    { -40, -40,    0,    0,	0,	0,	0xff,  0xff,     0,	0xff },	  /* Y */   
    {   0,   0,    0,    0,	0,	0,	0xff,  0xff,  0xff,	0xff },	  /* W */   
};

Gfx CS_placebo_dl[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&cs_place_vtx, 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};
/* end of case -1 */

#define BS 1024 /* BigScreen size */

/* x,	y,	z,	flag,	s,	t,	r,	g,	b,	a */
/*
static Vtx CS_EW_bigtri_vertices[6] =  {
{ 20,	(BS-1),	0,	0,  20<<5,   0<<5,	0,	0,	0,	0 },
{ 42,	(BS-2),	0,	0,  41<<5,   6<<5,	0xff,	0xff,	0xff,	0xff },
{ 0,	(BS-21),0,	0,   5<<5,  20<<5,	0xff,	0xff,	0xff,	0xff },

{ (BS-21), 20,	0,	0,1001<<5,1023<<5,	0xff,	0xff,	0xff,	0xff },
{ (BS-43), 19,	0,	0,1023<<5,1017<<5,	0xff,	0xff,	0xff,	0xff },
{ (BS-1),   0,	0,	0, 986<<5,1013<<5,	0,	0,	0,	0 },
};
*/
static Vtx CS_EW_bigtri_vertices[6] =  {
{ 20,	(BS-0),	0,	0,  20<<5,   0<<5,	0,	0,	0,	0 },
{ 42,	(BS-1),	0,	0,  41<<5,   6<<5,	0xff,	0xff,	0xff,	0xff },
{ 0,	(BS-20),0,	0,   5<<5,  20<<5,	0xff,	0xff,	0xff,	0xff },

{ (BS-21), 21,	0,	0,1001<<5,1023<<5,	0xff,	0xff,	0xff,	0xff },
{ (BS-43), 20,	0,	0,1023<<5,1017<<5,	0xff,	0xff,	0xff,	0xff },
{ (BS-1),   1,	0,	0, 986<<5,1013<<5,	0,	0,	0,	0 },
};


Gfx CS_EW_bigtris_dl[MAX_STATIC_GFX_SIZE] = {

    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPSetGeometryMode(G_ZBUFFER),

    /* set attributes, to be used as colors for rects */

    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    /*
     * Mike's hardcode render mode settings:
     *
     * Extract Z directly; Alpha is output from coverage unit.
     */
    gsDPWord(0x2f000cff, 0xaf0a6160),

    gsDPSetCycleType(G_CYC_1CYCLE),

    gsSPTexture(0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),

    /*
     * Use the color combiner to blend texels with the shaded color using
     * shaded alpha.
     */
#define CC_OP SHADE, TEXEL0, SHADE_ALPHA, TEXEL0, 0, 0, 0, 0
    gsDPSetCombineMode(CC_OP, CC_OP), 

    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPWord(0x2f000cff, 0xaf0a6160),

#define CS_EW_TEX_WIDTH 43
#define CS_EW_TEX_HEIGHT 21

    /*
     * Load up a high-frequency, random data texture.
     */
    gsDPLoadTextureBlock(map_rand, G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 CS_EW_TEX_WIDTH, CS_EW_TEX_HEIGHT, 
		 0, 
		 G_TX_CLAMP, G_TX_CLAMP, 
		 G_TX_NOMASK, G_TX_NOMASK, 
		 G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&CS_EW_bigtri_vertices, 6, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),

    /*
     * Now slide the tile with respect to the texture so that we'll step along
     * the maximum extents of our 1K x 1K texture coordinate space.
     */

    gsDPSetTileSize(G_TX_RENDERTILE, 
      ( (1023 - CS_EW_TEX_WIDTH) << G_TEXTURE_IMAGE_FRAC ), 
      (( 1023 - CS_EW_TEX_HEIGHT) << G_TEXTURE_IMAGE_FRAC ),
      ( 1023 << G_TEXTURE_IMAGE_FRAC ), ( 1023 << G_TEXTURE_IMAGE_FRAC) ),

    gsSP1Triangle(3, 4, 5, 3),

    gsSPEndDisplayList(),
};

#define XS 320
#define YS 240
static Vtx CS_EW_smalltri_vertices[6] =  {
/* x,	y,	z,	flag,	s,	t,	r,	g,	b,	a */

#ifdef foo

{ 20,	(YS-1),	0,	0,  20<<5,   0<<5,	0,	0,	0,	0 },
{ 42,	(YS-2),	0,	0,  41<<5,   6<<5,	0xff,	0xff,	0xff,	0xff },
{ 0,	(YS-21),0,	0,   5<<5,  20<<5,	0xff,	0xff,	0xff,	0xff },

{ (XS-21), 20,	0,	0,1001<<5,1023<<5,	0xff,	0xff,	0xff,	0xff },
{ (XS-43), 19,	0,	0,1023<<5,1017<<5,	0xff,	0xff,	0xff,	0xff },
{ (XS-1),   0,	0,	0, 986<<5,1013<<5,	0,	0,	0,	0 },

#else

{20+50,	(YS-1-50),	0,	0,  20<<5,   0<<5,	0,	0,	0,	0 },
{42+50,	(YS-2-50),	0,	0,  41<<5,   6<<5,	0xff,	0xff,	0xff,	0xff },
{0+50,	(YS-21-50),	0,	0,   5<<5,  20<<5,	0xff,	0xff,	0xff,	0xff },

{ (XS-21-50), 20+50,	0,	0,1001<<5,1023<<5,	0xff,	0xff,	0xff,	0xff },
{ (XS-43-50),  19+50,	0,	0,1023<<5,1017<<5,	0xff,	0xff,	0xff,	0xff },
{ (XS-1-50),   0+50,	0,	0, 986<<5,1013<<5,	0,	0,	0,	0 },

#endif
};

Gfx CS_EW_smalltris_dl[MAX_STATIC_GFX_SIZE] = {

    gsSPClearGeometryMode(G_CULL_BOTH),

    /* set attributes, to be used as colors for rects */

    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    gsDPWord(0xef000cff, 0xaf0a6160),
    gsDPSetCombineLERP (0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),

    gsDPSetCycleType(G_CYC_1CYCLE),

/*    gsDPSetRenderMode(G_RM_OPA_SURF,G_RM_OPA_SURF2),  */
/*    gsSPClearGeometryMode(G_ZBUFFER), */
    gsSPTexture(0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
#define CC_OP SHADE, TEXEL0, SHADE_ALPHA, TEXEL0, 0, 0, 0, 0
    gsDPSetCombineMode(CC_OP, CC_OP), 
/*    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB), */
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTexturePersp(G_TP_PERSP),

#define CS_EW_TEX_WIDTH 43
#define CS_EW_TEX_HEIGHT 21

    /*
     * Load up a high-frequency, random data texture.
     */
    gsDPLoadTextureBlock(map_rand, G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 CS_EW_TEX_WIDTH, CS_EW_TEX_HEIGHT, 
		 0, 
		 G_TX_CLAMP, G_TX_CLAMP, 
		 G_TX_NOMASK, G_TX_NOMASK, 
		 G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&CS_EW_smalltri_vertices, 6, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_NONE), 
/*    gsDPSetTexturePersp(G_TP_PERSP), */

    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsSPTextureRectangle( 75<<2, 75<<2, 
      (75+CS_EW_TEX_WIDTH) << 2, (75+CS_EW_TEX_HEIGHT) << 2,
      G_TX_RENDERTILE,
      0, 0, 1 << 10,1 << 10),
    gsDPPipeSync(),

    /*
     * Now slide the tile with respect to the texture so that we'll step along
     * the maximum extents of our 1K x 1K texture coordinate space.
     */


    gsDPSetCombineMode(CC_OP, CC_OP), 
    gsDPSetTileSize(G_TX_RENDERTILE, 
      ( (1023 - CS_EW_TEX_WIDTH) << G_TEXTURE_IMAGE_FRAC ), 
      (( 1023 - CS_EW_TEX_HEIGHT) << G_TEXTURE_IMAGE_FRAC ),
      ( 1023 << G_TEXTURE_IMAGE_FRAC ), ( 1023 << G_TEXTURE_IMAGE_FRAC) ),

    gsDPSetTexturePersp(G_TP_PERSP),
    gsSP1Triangle(3, 4, 5, 3),
    gsDPPipeSync(),
/*
 * Display the slid texture (debugging only)
 */
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle( 150<<2, 150<<2, 
      (150+CS_EW_TEX_WIDTH) << 2, (150+CS_EW_TEX_HEIGHT) << 2,
      G_TX_RENDERTILE,
      ( (1023 - CS_EW_TEX_WIDTH) << 5 ), 
      (( 1023 - CS_EW_TEX_HEIGHT) << 5 ),
      1 << 10,1 << 10),
    gsSPEndDisplayList(),
};

Gfx CS_EW_big_hardcoded_tris_dl[MAX_STATIC_GFX_SIZE] = {

    gsSPClearGeometryMode(G_CULL_BOTH),
    /*gsSPSetGeometryMode(G_ZBUFFER), */

    /* set attributes, to be used as colors for rects */

    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),
    /*
     * Mike's hardcode render mode settings:
     *
     * Extract Z directly; Alpha is output from coverage unit.
     */
/*    gsDPWord(0xef080cff, 0xaf0a6160), */

/*    gsDPSetCycleType(G_CYC_1CYCLE), */

    gsSPTexture(0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON),
/*    gsDPPipeSync(), */

    /*
     * Use the color combiner to blend texels with the shaded color using
     * shaded alpha.
     */
#define CC_OP SHADE, TEXEL0, SHADE_ALPHA, TEXEL0, 0, 0, 0, 0
/*    gsDPSetCombineMode(CC_OP, CC_OP),  */

    /* gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_NONE),
*/
#define CS_EW_TEX_WIDTH 43
#define CS_EW_TEX_HEIGHT 21

    /*
     * Load up a high-frequency, random data texture.
     */
    gsDPLoadTextureBlock(map_rand, G_IM_FMT_RGBA, G_IM_SIZ_16b,
		 CS_EW_TEX_WIDTH, CS_EW_TEX_HEIGHT, 
		 0, 
		 G_TX_CLAMP, G_TX_CLAMP, 
		 G_TX_NOMASK, G_TX_NOMASK, 
		 G_TX_NOLOD, G_TX_NOLOD),
/*
    gsSPTextureRectangle( 0<<2, 0<<2,
	9<<2, 9<<2,
	G_TX_RENDERTILE,
	21, 21, (-2) << 10, (-2) << 10),

    gsSPTextureRectangle( (0x0fd8), (0x0fd8),
	(0x0ffc), (0x0ffc),
	G_TX_RENDERTILE,
	0, 0, 1 << 10, 1 << 10),
*/
    gsDPPipeSync(),
    /* gsDPSetTexturePersp(G_TP_PERSP),
    gsDPNoOp(),  */
    gsDPSetCombineMode(CC_OP, CC_OP), 
/*
#define	RM_CVGALPHA_STEPZ_WRITE			\
	XXX
*/
#define G_RM_CVGALPHA_STEPZ_WRITE1    RM_CVGALPHA_STEPZ_WRITE(1)
#define G_RM_CVGALPHA_STEPZ_WRITE2    RM_CVGALPHA_STEPZ_WRITE(2)

/*    gsDPWord(0xef080cff, 0xaf0a6160), 
    gsDPSetTexturePersp(G_TP_PERSP),  */
    gsDPWord(0xef080cff, 0xaf0a6160),  

    /* gsSPVertex(&CS_EW_bigtri_vertices, 6, 0), */
    /* 
     * Use the hardcoded triangle commands found in cs_hardcoded_tris.h
     */
#include "cs_hardcoded_tris2.h"

    gsSPEndDisplayList(),
};

/*
 * TO ADD A TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx display list must be extern'd in cs.h, then
 * added to the 'testList_cs' table in cs.c as a Gfx pointer field of a
 * GfxTest_t struct.  You must also decide whether the existing top level DL's
 * will suffice for your application (you may need to provide a new top level
 * DL of your own design in toplevel.c).
 *
 */
