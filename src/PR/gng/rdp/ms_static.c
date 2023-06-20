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
 * File:	ms_static.c
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:
 *
 * This file holds tiny display list segments that are 'static' data, for use
 * by the memspan test modules in ms.c
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
 * is in ms.c, and the Gfx lists must be extern'd in rdpvector.h
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

static Vtx ms_place_vtx[5] =  {
/*     x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */	
    { -40,  40,    0,    0,	0,	0,	0xff,     0,     0,	0xff },	  /* R */   
    {  40,  40,    0,    0,	0,	0,	   0,  0xff,     0,	0xff },	  /* G */   
    {  40, -40,    0,    0,	0,	0,	   0,     0,  0xff,	0xff },	  /* B */   
    { -40, -40,    0,    0,	0,	0,	0xff,  0xff,     0,	0xff },	  /* Y */   
    {   0,   0,    0,    0,	0,	0,	0xff,  0xff,  0xff,	0xff },	  /* W */   
};

Gfx MS_placebo_dl[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&ms_place_vtx, 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};
/* end of case -1 */

/*
 * Groups of tests are being labelled as ms_vector, ms_vector2 etc. since the vectors
 * for these groups of tests are generated separately to avoid running large vector
 * files each time a new set of tests is added. The vector files are run separately
 * and the results are composited. Currentl set : ms_vector and ms_vector2
 */

/******************************* Start ms_vector *******************************************/

#define RM_ZB_ACCUM_DECAL(clk)                       		\
	Z_CMP | IM_RD | Z_UPD | CVG_DST_FULL | ALPHA_CVG_SEL |  \
        ZMODE_DEC | FORCE_BL |                          	\
        GBL_c##clk(G_BL_CLR_IN, G_BL_A_FOG, G_BL_CLR_MEM, G_BL_1)

#define G_RM_ZB_ACCUM_DECAL RM_ZB_ACCUM_DECAL(1)
#define G_RM_ZB_ACCUM_DECAL2 RM_ZB_ACCUM_DECAL(2)


/* 
 * Test 8, Frame 0: load copy 
 * This test hits all possible start alignments of 8,16 and 32 bit data
 * within a 64-bit word during loads and copies. Not all possible
 * combinations of start and end alignments are hit though. Only
 * end = start and end = start+1. data_bar is the complement of data
 */
Gfx MS_loadCopy[MAX_STATIC_GFX_SIZE] = {
	gsDPPipeSync(),
	gsDPSetCycleType(G_CYC_COPY),

	/*
	 * 8b texture, 8b frame buffer
	 * Eight possible load and copy alignments, 
	 * End Alignment = Start Alignment
	 * 8-bit load followed by 8-bit copy
	 */
	gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_8b, SCREEN_WD+1,
				OS_K0_TO_PHYSICAL(cfb_16_a)),
	gsDPLoadTextureTile(RGBA16data, G_IM_FMT_RGBA, G_IM_SIZ_8b, 65, 64,
                         0, 0, 8, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 150<<2, 38<<2, 157<<2, G_TX_RENDERTILE, 0, 0, 8<<10, 1<<10),

	gsDPPipeSync(),

	/* complement data */
	gsDPLoadTextureTile(RGBA16data_bar, G_IM_FMT_RGBA, G_IM_SIZ_8b, 65, 64,
                         0, 0, 8, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 170<<2, 38<<2, 177<<2, G_TX_RENDERTILE, 0, 0, 8<<10, 1<<10),

	gsDPPipeSync(),

	/*
	 * 8b texture, 8b frame buffer
	 * Eight possible load and copy alignments, 
         * End Alignment = Start Alignment+1
	 */
	gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_8b, SCREEN_WD+1,
				OS_K0_TO_PHYSICAL(cfb_16_a)),
	gsDPLoadTextureTile(RGBA16data, G_IM_FMT_RGBA, G_IM_SIZ_8b, 65, 64,
                         0, 0, 9, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 200<<2, 39<<2, 207<<2, G_TX_RENDERTILE, 0, 0, 8<<10, 1<<10),
	gsDPPipeSync(),

	/* complement data */
	gsDPLoadTextureTile(RGBA16data_bar, G_IM_FMT_RGBA, G_IM_SIZ_8b, 65, 64,
                         0, 0, 9, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 220<<2, 39<<2, 227<<2, G_TX_RENDERTILE, 0, 0, 8<<10, 1<<10),

/*############################################################################*/
	/*
	 * 32b texture, 16b frame buffer
	 * Two possible load and copy alignments, 
         * End Alignment = Start Alignment+1
	 */
	gsDPPipeSync(),
	gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD+2,
				OS_K0_TO_PHYSICAL(cfb_16_a)),
	gsDPLoadTextureTile(RGBA16data, G_IM_FMT_RGBA, G_IM_SIZ_32b, 17, 16,
                         0, 0, 7, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 100<<2, 33<<2, 101<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPPipeSync(),

	/* complement data */
	gsDPLoadTextureTile(RGBA16data_bar, G_IM_FMT_RGBA, G_IM_SIZ_32b, 17, 16,
                         0, 0, 7, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 120<<2, 33<<2, 121<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPPipeSync(),

	/*
	 * 32b texture, 16b frame buffer
	 * Two possible alignments, End Alignment = Start Alignment+1
	 */
	gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD+2,
				OS_K0_TO_PHYSICAL(cfb_16_a)),
	gsDPLoadTextureTile(RGBA16data, G_IM_FMT_RGBA, G_IM_SIZ_32b, 17, 16,
                         0, 0, 8, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD),

	gsSPTextureRectangle(50<<2, 100<<2, 54<<2, 101<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPPipeSync(),

	/* complement data */
	gsDPLoadTextureTile(RGBA16data_bar, G_IM_FMT_RGBA, G_IM_SIZ_32b, 17, 16,
                         0, 0, 8, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD),

	gsSPTextureRectangle(50<<2, 120<<2, 54<<2, 121<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

/*###############################################################################*/

	/*
	 * 16b texture, 16b frame buffer
	 * All four possible alignments, End Alignment = Start Alignment 
	 */
	gsDPPipeSync(),

	gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD+1,
				OS_K0_TO_PHYSICAL(cfb_16_a)),
	gsDPLoadTextureTile(RGBA16data, G_IM_FMT_RGBA, G_IM_SIZ_16b, 33, 32,
                         0, 0, 4, 3 , 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 50<<2, 34<<2, 53<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPPipeSync(),

	
	/* complement data */
	gsDPLoadTextureTile(RGBA16data_bar, G_IM_FMT_RGBA, G_IM_SIZ_16b, 33, 32,
                         0, 0, 4, 3 , 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 70<<2, 34<<2, 73<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPPipeSync(),

	/*
	 * 16b texture, 16b frame buffer
	 * All four possible alignments, End Alignment = Start Alignment + 1
	 * Loading more than copying due to weird mismatch in rbus output pin
	 * net between expected and given output while running tdx_lsim. 
	 * However this extra load is aligned as required.
	 */
	 
	gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD+1,
				OS_K0_TO_PHYSICAL(cfb_16_a)),

	gsDPLoadTextureTile(RGBA16data, G_IM_FMT_RGBA, G_IM_SIZ_16b, 33, 32,
                         0, 0, 9 , 7 , 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(50<<2, 50<<2, 55<<2, 53<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPPipeSync(),

	/* complement data */
	gsDPLoadTextureTile(RGBA16data_bar, G_IM_FMT_RGBA, G_IM_SIZ_16b, 33, 32,
                         0, 0, 9 , 7 , 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(50<<2, 70<<2, 55<<2, 73<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),


    	gsSPEndDisplayList(),
};

Gfx MS_loadTlut[MAX_STATIC_GFX_SIZE] = {
	gsDPPipeSync(),
	gsDPLoadTLUT_pal16(0, &(loadTlut[0])),
	gsDPLoadTLUT_pal16(1, &(loadTlut[16])),
	gsSPEndDisplayList(),
};

/**************************************************************/
static Vtx BaseTri32_vtx[] =  {
        {         40,  10,   99,  0, 0, 0, 255, 000, 255, 000 },
        {          9,  41,   99,  0, 0, 0, 255, 000, 255, 000 },
        {         72,  41,  -99,  0, 0, 0, 000, 255, 000, 000 },
};

static Vtx CompTri32_vtx[] =  {
        {         40,  50,  -99,  0, 0, 0, 000, 255, 000, 000 },
        {          9,  81,  -99,  0, 0, 0, 255, 000, 255, 000 },
        {         72,  81,   99,  0, 0, 0, 255, 000, 255, 000 },
};

static Vtx BaseTriAccum32_vtx[] =  {
        {         40,  10,   99,  0, 0, 0,   2,   2,   2, 000 },
        {          9,  41,   99,  0, 0, 0,   2,   2,   2, 000 },
        {         72,  41,  -99,  0, 0, 0,   2,   2,   2, 000 },
};

static Vtx CompTriAccum32_vtx[] =  {
        {         40,  50,  -99,  0, 0, 0,   2,   2,   2, 000 },
        {          9,  81,  -99,  0, 0, 0,   2,   2,   2, 000 },
        {         72,  81,   99,  0, 0, 0,   2,   2,   2, 000 },
};
/****************************************************************/
static Vtx BaseTri16_vtx[] =  {
        {        100,  10,   99,  0, 0, 0, 255, 000, 255, 000 },
        {         69,  41,   99,  0, 0, 0, 255, 000, 255, 000 },
        {        132,  41,  -99,  0, 0, 0, 000, 255, 000, 000 },
};

static Vtx CompTri16_vtx[] =  {
        {        100,  50,  -99,  0, 0, 0, 000, 255, 000, 000 },
        {         69,  81,  -99,  0, 0, 0, 255, 000, 255, 000 },
        {        132,  81,   99,  0, 0, 0, 255, 000, 255, 000 },
};

static Vtx BaseTriAccum16_vtx[] =  {
        {        100,  10,   99,  0, 0, 0,   9,   9,   9, 000 },
        {         69,  41,   99,  0, 0, 0,   9,   9,   9, 000 },
        {        132,  41,  -99,  0, 0, 0,   9,   9,   9, 000 },
};

static Vtx CompTriAccum16_vtx[] =  {
        {        100,  50,  -99,  0, 0, 0,   9,   9,   9, 000 },
        {         69,  81,  -99,  0, 0, 0,   9,   9,   9, 000 },
        {        132,  81,   99,  0, 0, 0,   9,   9,   9, 000 },
};
/****************************************************************/
static Vtx BaseTri8_vtx[] =  {
        {        200,  10,   99,  0, 0, 0, 000, 000, 000, 000 },
        {        169,  40,   99,  0, 0, 0, 000, 000, 000, 000 },
        {        232,  41,  -99,  0, 0, 0, 255, 255, 255, 000 },
};

static Vtx CompTri8_vtx[] =  {
        {        200,  50,  -99,  0, 0, 0, 255, 255, 255, 000 },
        {        169,  80,  -99,  0, 0, 0, 255, 255, 255, 000 },
        {        232,  81,   99,  0, 0, 0, 000, 000, 000, 000 },
};

static Vtx BaseTriAccum8_vtx[] =  {
        {        200,  10,   99,  0, 0, 0,   2,   2,   2, 000 },
        {        169,  40,   99,  0, 0, 0,   2,   2,   2, 000 },
        {        232,  41,  -99,  0, 0, 0,   2,   2,   2, 000 },
};

static Vtx CompTriAccum8_vtx[] =  {
        {        200,  50,  -99,  0, 0, 0,   2,   2,   2, 000 },
        {        169,  81,  -99,  0, 0, 0,   2,   2,   2, 000 },
        {        232,  81,   99,  0, 0, 0,   2,   2,   2, 000 },
};
/****************************************************************/

static Vtx noiseTri32_vtx[] =  {
        {        140, 110,   99,  0, 0, 0, 000, 000, 000, 000 },
        {        109, 141,   99,  0, 0, 0, 255, 255, 255, 000 },
        {        172, 141,  -99,  0, 0, 0, 000, 000, 000, 000 },
};

static Vtx bayerTri32_vtx[] =  {
        {        140, 150,  -99,  0, 0, 0, 000, 000, 000, 000 },
        {        109, 181,  -99,  0, 0, 0, 255, 255, 255, 000 },
        {        172, 181,   99,  0, 0, 0, 000, 000, 000, 000 },
};

Gfx MS_render[MAX_STATIC_GFX_SIZE] = {
/*****************************************************************************
		Rendering Tests
*****************************************************************************/
	/*
	 * 8-bit frame buffer
	 */
 	gsDPPipeSync(),
        gsDPSetCycleType(G_CYC_2CYCLE),
	gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
	gsDPSetColorImage( G_IM_FMT_I, G_IM_SIZ_8b, SCREEN_WD,
            OS_K0_TO_PHYSICAL(cfb_16_a) ),
	gsDPSetFogColor(0,0,0,255),
	gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
	gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_OPA_SURF2),
	gsSPVertex(&(BaseTri8_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
	gsSPVertex(&(CompTri8_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
	gsDPPipeSync(),
	gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_ACCUM_DECAL2),
	gsSPVertex(&(BaseTriAccum8_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
	gsSPVertex(&(CompTriAccum8_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),

	/*
	 * 32-bit frame buffer
	 */
 	gsDPPipeSync(),
	gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD,
            OS_K0_TO_PHYSICAL(cfb_16_a) ),
	gsDPSetFogColor(0,0,0,255),
	gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_OPA_SURF2),
	gsSPVertex(&(BaseTri32_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
	gsSPVertex(&(CompTri32_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
	gsDPPipeSync(),
	gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_ACCUM_DECAL2),
	gsSPVertex(&(BaseTriAccum32_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
	gsSPVertex(&(CompTriAccum32_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
	/*
	 * Color Dither 32-bit mode
	 */
 	gsDPPipeSync(),
	gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
	/*
 	 * Don't specify G_CD_NOISE; we want repeatable checksum behavior 
	 * for go/no-go, so we use G_CD_MAGICSQ instead.
	gsDPSetColorDither(G_CD_NOISE),
	*/
	gsDPSetColorDither(G_CD_MAGICSQ),
	gsSPVertex(&(noiseTri32_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
	gsDPSetColorDither(G_CD_BAYER),
	gsSPVertex(&(bayerTri32_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),

	/*
	 * 16-bit frame buffer
	 */
 	gsDPPipeSync(),
        gsDPSetCycleType(G_CYC_1CYCLE),
	gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
            OS_K0_TO_PHYSICAL(cfb_16_a) ),
	gsDPSetDepthImage(zbuffer),
	gsDPSetFogColor(0,0,0,255),
	gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
	gsDPSetRenderMode(G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2),
	gsSPVertex(&(BaseTri16_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
	gsSPVertex(&(CompTri16_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
	gsDPPipeSync(),
	gsDPSetRenderMode(G_RM_ZB_ACCUM_DECAL, G_RM_ZB_ACCUM_DECAL2),
	gsSPVertex(&(BaseTriAccum16_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
	gsSPVertex(&(CompTriAccum16_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
	gsDPSetColorDither(G_CD_DISABLE),
	gsSPEndDisplayList(),
};

#define RM_AA_ZB_1CASE(clk)                       			\
	AA_EN | Z_CMP | IM_RD | CVG_DST_CLAMP |         \
        ZMODE_OPA | ALPHA_CVG_SEL |                             \
        GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_AA_ZB_2CASE(clk)                       			\
	AA_EN | Z_CMP | Z_UPD | CVG_DST_CLAMP |         \
        ZMODE_OPA | ALPHA_CVG_SEL |                             \
        GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_AA_ZB_3CASE(clk)                       			\
	AA_EN | Z_CMP | CVG_DST_CLAMP |         \
        ZMODE_OPA | ALPHA_CVG_SEL |                             \
        GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)

#define RM_AA_ZB_4CASE(clk)                       			\
	AA_EN | Z_UPD | IM_RD | CVG_DST_CLAMP |         \
        ZMODE_OPA | ALPHA_CVG_SEL |                             \
        GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


#define G_RM_AA_ZB_1CASE1 RM_AA_ZB_1CASE(1)
#define G_RM_AA_ZB_1CASE2 RM_AA_ZB_1CASE(2)

#define G_RM_AA_ZB_2CASE1 RM_AA_ZB_2CASE(1)
#define G_RM_AA_ZB_2CASE2 RM_AA_ZB_2CASE(2)

#define G_RM_AA_ZB_3CASE1 RM_AA_ZB_3CASE(1)
#define G_RM_AA_ZB_3CASE2 RM_AA_ZB_3CASE(2)

#define G_RM_AA_ZB_4CASE1 RM_AA_ZB_4CASE(1)
#define G_RM_AA_ZB_4CASE2 RM_AA_ZB_4CASE(2)

static Vtx zCasesTri1_vtx[] =  {
        {         20,  200,   99,  0, 0, 0, 000, 000, 000, 000 },
        {         25,  200,   99,  0, 0, 0, 255, 255, 255, 000 },
        {         25,  205,  -99,  0, 0, 0, 000, 000, 000, 000 },
};
static Vtx zCasesTri2_vtx[] =  {
        {         40,  200,   99,  0, 0, 0, 000, 000, 000, 000 },
        {         45,  200,   99,  0, 0, 0, 255, 255, 255, 000 },
        {         45,  205,  -99,  0, 0, 0, 000, 000, 000, 000 },
};
static Vtx zCasesTri3_vtx[] =  {
        {         60,  200,   99,  0, 0, 0, 000, 000, 000, 000 },
        {         65,  200,   99,  0, 0, 0, 255, 255, 255, 000 },
        {         65,  205,  -99,  0, 0, 0, 000, 000, 000, 000 },
};
static Vtx zCasesTri4_vtx[] =  {
        {         80,  200,   59,  0, 0, 0, 000, 000, 000, 000 },
        {         85,  200,   59,  0, 0, 0, 255, 255, 255, 000 },
        {         85,  205,   59,  0, 0, 0, 000, 000, 000, 000 },
};

static Vtx zCasesTri5_vtx[] =  {
        {         80,  200,  -90,  0, 0, 0, 255, 000, 000, 000 },
        {         85,  200,  -90,  0, 0, 0, 255, 000, 000, 000 },
        {         85,  205,  -90,  0, 0, 0, 255, 000, 000, 000 },
};

Gfx MS_zCases[MAX_STATIC_GFX_SIZE] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
	gsDPSetCycleType(G_CYC_1CYCLE), 
	gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
            OS_K0_TO_PHYSICAL(cfb_16_a) ),
	gsDPSetDepthImage(zbuffer),
        gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
        gsDPSetRenderMode(G_RM_AA_ZB_1CASE1, G_RM_AA_ZB_1CASE2),
        gsSPVertex(&(zCasesTri1_vtx[0]), 3, 0),
        gsSP1Triangle(0, 1, 2, 0),
	gsDPPipeSync(),
        gsDPSetRenderMode(G_RM_AA_ZB_2CASE1, G_RM_AA_ZB_2CASE2),
        gsSPVertex(&(zCasesTri2_vtx[0]), 3, 0),
        gsSP1Triangle(0, 1, 2, 0),
	gsDPPipeSync(),
        gsDPSetRenderMode(G_RM_AA_ZB_3CASE1, G_RM_AA_ZB_3CASE2),
        gsSPVertex(&(zCasesTri3_vtx[0]), 3, 0),
        gsSP1Triangle(0, 1, 2, 0),
	gsDPPipeSync(),
        gsDPSetRenderMode(G_RM_AA_ZB_4CASE1, G_RM_AA_ZB_4CASE2),
        gsSPVertex(&(zCasesTri4_vtx[0]), 3, 0),
        gsSP1Triangle(0, 1, 2, 0),
	gsDPPipeSync(),

	/* This triangle will always fail z-compare */
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
        gsSPVertex(&(zCasesTri5_vtx[0]), 3, 0),
        gsSP1Triangle(0, 1, 2, 0),
	gsDPPipeSync(),
	gsSPEndDisplayList(),
};

/* 
 * Same as aa_zb_xlu_surf without the z_cmp
 */
#define RM_AA_ZB_FORCE(clk)                    			\
	AA_EN | IM_RD | CVG_DST_WRAP | CLR_ON_CVG |     \
        FORCE_BL | ZMODE_XLU |                                  \
        GBL_c##clk(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)

#define G_RM_AA_ZB_FORCE1 RM_AA_ZB_FORCE(1)
#define G_RM_AA_ZB_FORCE2 RM_AA_ZB_FORCE(2)

static Vtx cyc2Blend1_vtx[] =  {
        {         20,  200,  -90,  0, 0, 0, 255, 000, 000, 128 },
        {         30,  200,  -90,  0, 0, 0, 255, 000, 000, 128 },
        {         30,  210,  -90,  0, 0, 0, 255, 000, 000, 128 },
};

static Vtx odd_address_vtx[] =  {
        {        0, 239,    0,  0, 0, 0, 0xff, 0xff, 0xff, 0xff },
        {        0, 240,    0,  0, 0, 0, 0xff, 0xff, 0xff, 0xff },
        {        3, 238,    0,  0, 0, 0, 0xff, 0xff, 0xff, 0xff },
};
/* 
 * Two cycle triangle blending with background 
 * Pixel mode is IA16 which is actually a valid mode
 */

Gfx MS_cyc2Blend[MAX_STATIC_GFX_SIZE] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
	gsDPSetCycleType(G_CYC_2CYCLE), 
	gsDPSetColorImage( G_IM_FMT_IA, G_IM_SIZ_16b, SCREEN_WD,
            OS_K0_TO_PHYSICAL(cfb_16_a) ),
	gsDPSetDepthImage(zbuffer),
        gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
	gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_FORCE2),
	gsSPVertex(&(cyc2Blend1_vtx[0]), 3, 0),
        gsSP1Triangle(0, 1, 2, 0),

	/* 
	 * z-compared, blended render with odd cfb and zb address 
	 */
/**
	gsDPPipeSync(),
	gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_SURF2),
	gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
            0x3f00007),
	gsDPSetDepthImage(0x3f00007),
	gsSPVertex(&(odd_address_vtx[0]), 3, 0),
        gsSP1Triangle(0, 1, 2, 0),
**/
	gsSPEndDisplayList(),
};

Gfx MS_fill[MAX_STATIC_GFX_SIZE] = {
 	gsDPPipeSync(),
	gsDPSetCycleType(G_CYC_FILL),
	gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
	gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
            OS_K0_TO_PHYSICAL(cfb_16_a) ),
	gsDPSetFillColor(0xa5a5a5a5),
	gsDPFillRectangle(100, 100, 101, 101),
	gsDPPipeSync(),
	gsDPSetFillColor(0x5a5a5a5a),
	gsDPFillRectangle(110, 100, 111, 101),
	gsSPEndDisplayList(),
};
static Vtx rightMajor_vtx[] =  {
        {        0, 239,    0,  0, 0, 0, 0xff, 0xff, 0xff, 0xff },
        {        0, 240,    0,  0, 0, 0, 0xff, 0xff, 0xff, 0xff },
        {       10, 238,    0,  0, 0, 0, 0xff, 0xff, 0xff, 0xff },
};

static Vtx leftMajor_vtx[] =  {
        {        0, 238,    0,  0, 0, 0, 0xff, 0xff, 0xff, 0xff },
        {       10, 240,    0,  0, 0, 0, 0xff, 0xff, 0xff, 0xff },
        {       10, 239,    0,  0, 0, 0, 0xff, 0xff, 0xff, 0xff },
};


Gfx MS_address[MAX_STATIC_GFX_SIZE] = {
 	gsDPPipeSync(),
	gsDPSetCycleType(G_CYC_1CYCLE),
	gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
/**
	Cant have this active since it trashes some DLs
	gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
            	(0x2ffff8)),
	gsDPSetDepthImage(0x2ffff8),
**/
	gsSPVertex(&(leftMajor_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
 	gsDPPipeSync(),
	gsSPVertex(&(rightMajor_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
	gsDPSetDepthImage(zbuffer),
	gsSPEndDisplayList(),
};

Gfx MS_longSpanLoad[MAX_STATIC_GFX_SIZE] = {
	gsDPPipeSync(),
	gsDPSetCycleType(G_CYC_COPY),
	gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
            OS_K0_TO_PHYSICAL(cfb_16_a)),

	/*
	 * In the display list the settimg command should display an address
         * of 0xdbff8 which is mostly the complement of the previous load
         * which was from 0xd8000. This is ensured by the texture segment
  	 * location of 0xdbff8 and a spacer texture to force RGBA16longspan
	 * to be at 0x199ff8. Alternating loads of RGBA16data and RGBA16longspan
	 * to get toggle up and down
	 */
	gsDPLoadTextureBlock(RGBA16longspan, G_IM_FMT_RGBA, G_IM_SIZ_32b,
	  		32, 32, 0,
			G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
			10,10,0,0),

	gsDPLoadTextureBlock(RGBA16data, G_IM_FMT_RGBA, G_IM_SIZ_16b,
	  		32, 32, 0,
			G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
			10,10,0,0),

	gsDPLoadTextureBlock(RGBA16longspan, G_IM_FMT_RGBA, G_IM_SIZ_32b,
	  		32, 32, 0,
			G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
			10,10,0,0),

	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD),

	gsSPTextureRectangle(50<<2, 50<<2, 82<<2, 82<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPPipeSync(),
	/*
	 * Don't use DITHER, go/no-go wants repeatable checksum behavior.
	gsDPSetAlphaCompare(G_AC_DITHER),
	*/
	gsDPSetAlphaCompare(G_AC_THRESHOLD),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, G_TX_RENDERTILE, 0,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD),

	gsSPTextureRectangle(100<<2, 50<<2, 132<<2, 66<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPPipeSync(),
	gsDPSetColorImage( G_IM_FMT_I, G_IM_SIZ_8b, 2*SCREEN_WD,
            OS_K0_TO_PHYSICAL(cfb_16_a)),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 16, 768, G_TX_RENDERTILE, 0,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD),

	gsSPTextureRectangle(150<<2, 150<<2, 182<<2, 182<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};
static Vp long_vp = {
        SCREEN_WD*8, SCREEN_HT/2, G_MAXZ/2, 0,  /* scale */
        SCREEN_WD*8, SCREEN_HT/2, G_MAXZ/2, 0,  /* translate */
};

static Vp big_vp = {
        1024*2, 1024*2, G_MAXZ/2, 0,  /* scale */
        1024*2, 1024*2, G_MAXZ/2, 0,  /* translate */
};
static Vtx longTriLeft32_vtx[] =  {
        {          0,  50, -99,  0, 0, 0, 000, 000, 000, 000 },
        {          0,  70, -99,  0, 0, 0, 255, 255, 255, 255 },
        {        300,  50,  99,  0, 0, 0, 255, 255, 255, 255 },
};
static Vtx longTriRight32_vtx[] =  {
        {          0,  80, -99,  0, 0, 0, 255, 255, 255, 255 },
        {        300, 100,  99,  0, 0, 0, 000, 000, 000, 000 },
        {        300,  78,  99,  0, 0, 0, 255, 255, 255, 255 },
};
static Vtx lastSpan_vtx[] =  {
        {        0, 239,    0,  0, 0, 0, 0xff, 0x00, 0x00, 0x00 },
        {        0, 240,    0,  0, 0, 0, 0xff, 0x00, 0x00, 0x00 },
        {        3, 238,    0,  0, 0, 0, 0xff, 0x00, 0x00, 0x00 },
};
static Vtx lastSpan1_vtx[] =  {
        {           0,    0,  0,  0, 0, 0, 0xff, 0x00, 0x00, 0x00 },
        {         1023,   5,  0,  0, 0, 0, 0xff, 0x00, 0x00, 0x00 },
        {         1023,   0,  0,  0, 0, 0, 0xff, 0x00, 0x00, 0x00 },
};
Gfx MS_longSpanRender[MAX_STATIC_GFX_SIZE] = {
	/*
	 * 1K long span 32-bit mode
	 */
#ifdef NONE
 	gsDPPipeSync(),
	gsSPViewport(&long_vp),
	gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 1023, 50),
	gsDPSetAlphaCompare(G_AC_NONE),
        gsDPSetCycleType(G_CYC_1CYCLE),
	gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
	gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_32b, 4*SCREEN_WD,
            OS_K0_TO_PHYSICAL(cfb_16_a) ),
	gsSPVertex(&(longTriLeft32_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),
	gsSPVertex(&(longTriRight32_vtx[0]), 3, 0),
    	gsSP1Triangle(0, 1, 2, 0),

	/*
	 * Blended, z-buffered rendering of last span of a 1kx1k
	 * cfb. Since a 1kx1k takes up 2M. set cfb to 2M out of 4M 
	 * rdram.
  	 */
	gsDPPipeSync(),
	gsSPViewport(&big_vp),
	gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
	gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 1023, 1023),
    	gsDPPipeSync(),
	gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_16b, 1024,
            0x200000 ),
	gsSPVertex(&(lastSpan1_vtx[0]), 3, 0),
        gsSP1Triangle(0, 1, 2, 0),
	gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 2*SCREEN_WD, 2*SCREEN_HT),
#endif
	gsSPEndDisplayList(),
};

/*********************  End ms_vector, Start ms_vector2 ***********************************/	


/* 
 * Test 8, Frame 0: load copy. redoing this test due to bug in previous 8-bit
 * test and because previous test does not hit complement of data. 
 * This test hits all possible start alignments of 8,16 and 32 bit data
 * within a 64-bit word during loads and copies. Not all possible
 * combinations of start and end alignments are hit though. Only
 * end = start and end = start+1. data_bar is the complement of data
 */
Gfx MS_loadCopy2[MAX_STATIC_GFX_SIZE] = {
	gsDPPipeSync(),
	gsDPSetCycleType(G_CYC_COPY),

	/*
	 * 8b texture, 8b frame buffer
	 * Eight possible load and copy alignments, 
	 * End Alignment = Start Alignment
	 * 8-bit load followed by 8-bit copy
	 */
	gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_8b, SCREEN_WD+1,
				OS_K0_TO_PHYSICAL(cfb_16_a)),
	gsDPLoadTextureTile(RGBA16data, G_IM_FMT_RGBA, G_IM_SIZ_8b, 65, 64,
                         0, 0, 8, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 150<<2, 38<<2, 157<<2, G_TX_RENDERTILE, 0, 0, 8<<10, 1<<10),

	gsDPPipeSync(),

	/* complement data */
	gsDPLoadTextureTile(RGBA16data_bar, G_IM_FMT_RGBA, G_IM_SIZ_8b, 65, 64,
                         0, 0, 8, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 170<<2, 38<<2, 177<<2, G_TX_RENDERTILE, 0, 0, 8<<10, 1<<10),

	gsDPPipeSync(),

	/*
	 * 8b texture, 8b frame buffer
	 * Eight possible load and copy alignments, 
         * End Alignment = Start Alignment+1
	 */
	gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_8b, SCREEN_WD+1,
				OS_K0_TO_PHYSICAL(cfb_16_a)),
	gsDPLoadTextureTile(RGBA16data, G_IM_FMT_RGBA, G_IM_SIZ_8b, 65, 64,
                         0, 0, 9, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 200<<2, 39<<2, 207<<2, G_TX_RENDERTILE, 0, 0, 8<<10, 1<<10),
	gsDPPipeSync(),

	/* complement data */
	gsDPLoadTextureTile(RGBA16data_bar, G_IM_FMT_RGBA, G_IM_SIZ_8b, 65, 64,
                         0, 0, 9, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 220<<2, 39<<2, 227<<2, G_TX_RENDERTILE, 0, 0, 8<<10, 1<<10),

/*############################################################################*/
	/*
	 * 32b texture, 16b frame buffer
	 * Two possible load and copy alignments, 
         * End Alignment = Start Alignment+1
	 */
	gsDPPipeSync(),
	gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD+2,
				OS_K0_TO_PHYSICAL(cfb_16_a)),
	gsDPLoadTextureTile(RGBA16data, G_IM_FMT_RGBA, G_IM_SIZ_32b, 17, 16,
                         0, 0, 7, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 100<<2, 33<<2, 101<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPPipeSync(),

	/* complement data */
	gsDPLoadTextureTile(RGBA16data_bar, G_IM_FMT_RGBA, G_IM_SIZ_32b, 17, 16,
                         0, 0, 7, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 120<<2, 33<<2, 121<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPPipeSync(),

	/*
	 * 32b texture, 16b frame buffer
	 * Two possible alignments, End Alignment = Start Alignment+1
	 */
	gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD+2,
				OS_K0_TO_PHYSICAL(cfb_16_a)),
	gsDPLoadTextureTile(RGBA16data, G_IM_FMT_RGBA, G_IM_SIZ_32b, 17, 16,
                         0, 0, 8, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD),

	gsSPTextureRectangle(50<<2, 100<<2, 54<<2, 101<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPPipeSync(),

	/* complement data */
	gsDPLoadTextureTile(RGBA16data_bar, G_IM_FMT_RGBA, G_IM_SIZ_32b, 17, 16,
                         0, 0, 8, 7, 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD,
		    G_TX_CLAMP | G_TX_NOMIRROR, 0, G_TX_NOLOD),

	gsSPTextureRectangle(50<<2, 120<<2, 54<<2, 121<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

/*###############################################################################*/

	/*
	 * 16b texture, 16b frame buffer
	 * All four possible alignments, End Alignment = Start Alignment 
	 */
	gsDPPipeSync(),

	gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD+1,
				OS_K0_TO_PHYSICAL(cfb_16_a)),
	gsDPLoadTextureTile(RGBA16data, G_IM_FMT_RGBA, G_IM_SIZ_16b, 33, 32,
                         0, 0, 4, 3 , 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 50<<2, 34<<2, 53<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPPipeSync(),

	
	/* complement data */
	gsDPLoadTextureTile(RGBA16data_bar, G_IM_FMT_RGBA, G_IM_SIZ_16b, 33, 32,
                         0, 0, 4, 3 , 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(30<<2, 70<<2, 34<<2, 73<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPPipeSync(),

	/*
	 * 16b texture, 16b frame buffer
	 * All four possible alignments, End Alignment = Start Alignment + 1
	 * Loading more than copying due to weird mismatch in rbus output pin
	 * net between expected and given output while running tdx_lsim. 
	 * However this extra load is aligned as required.
	 */
	 
	gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD+1,
				OS_K0_TO_PHYSICAL(cfb_16_a)),

	gsDPLoadTextureTile(RGBA16data, G_IM_FMT_RGBA, G_IM_SIZ_16b, 33, 32,
                         0, 0, 9 , 7 , 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(50<<2, 50<<2, 55<<2, 53<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

	gsDPPipeSync(),

	/* complement data */
	gsDPLoadTextureTile(RGBA16data_bar, G_IM_FMT_RGBA, G_IM_SIZ_16b, 33, 32,
                         0, 0, 9 , 7 , 0,
                         G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
 			 0, 0, G_TX_NOLOD, G_TX_NOLOD),

	gsSPTextureRectangle(50<<2, 70<<2, 55<<2, 73<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),


    	gsSPEndDisplayList(),
};

/********************* End ms_vector2 *****************************************************/


/*
 * TO ADD A TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx display list must be extern'd in ms.h, then
 * added to the 'testList_ms' table in ms.c as a Gfx pointer field of a
 * GfxTest_t struct.  You must also decide whether the existing top level DL's
 * will suffice for your application (you may need to provide a new top level
 * DL of your own design in toplevel.c).
 *
 */

/*
 * TO ADD A TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx display list must be extern'd in ms.h, then
 * added to the 'testList_ms' table in ms.c as a Gfx pointer field of a
 * GfxTest_t struct.  You must also decide whether the existing top level DL's
 * will suffice for your application (you may need to provide a new top level
 * DL of your own design in toplevel.c).
 *
 */
