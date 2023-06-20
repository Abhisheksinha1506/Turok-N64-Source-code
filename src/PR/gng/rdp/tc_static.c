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
 * File:	tc_static.c
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:
 *
 * This file holds tiny display list segments that are 'static' data, for use
 * by the texture coordinate test module in tc.c
 *
 * If you feel the urge to modify a test, see the comment at
 * the top of main.c for details.
 */

#include <ultratypes.h>
#include <mbi.h>
#include "dldriver.h"

/*
 * Test conventions:
 *
 * Data variable names can be about anything, as long as they are unique
 * and consistent in the table entry.
 *
 * In order to get around compiler weirdness, the table of tests
 * is in tc.c, and the Gfx lists must be extern'd in rdpvector.h
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
 *  Texture Coordinate Unit Test
 *
 */
static Vtx tc_place_vtx[] =  {
    {   10,  50,  0,  0,	 32767,	 32767,	0xff,     0,     0,	0xff },
    { 310,  50,  0,  0,	-32768,	-32768,	   0,  0xff,     0,	0xff },
    { 310,  51,  0,  0,	-32768,	-32768,	   0,     0,  0xff,	0xff },
    {   10,  51,  0,  0,	 32767,	 32767,	0xff,  0xff,     0,	0xff },
};

Gfx tc_div_init[MAX_STATIC_GFX_SIZE] = {
#ifdef JUNK
    gsDPPipeSync(),
	gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | 
		G_SHADING_SMOOTH | G_CULL_BOTH),
    gsSPClearGeometryMode(G_FOG | G_LIGHTING | 
		G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
	gsDPSetTextureLUT(G_TT_NONE),
	gsDPSetTextureDetail(G_TD_CLAMP),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsDPSetTextureConvert(G_TC_FILT),
	gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetColorDither(G_CD_DISABLE),

	gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetCombineMode (G_CC_DECALRGBA, G_CC_DECALRGBA),
	gsDPSetTexturePersp(G_TP_PERSP),
	gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),

	gsDPLoadTextureBlock(RGBA16dana, 
			 G_IM_FMT_RGBA, G_IM_SIZ_16b, 
			 32, 32, 
			 0,
             G_TX_MIRROR, G_TX_MIRROR,
             0xa, 0xa, G_TX_NOLOD, G_TX_NOLOD),
	gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 1023 << 2, 1023 << 2),


/* tri test */
gsDPWord(0xca0002f8, 0x02f802f4),
gsDPWord(0x0009c000, 0x01ccffb5),
gsDPWord(0x0009c000, 0x012bbf6a),
gsDPWord(0x0009c000, 0x00000000),
gsDPWord(0x1fff1fff, 0x3fff01ff),
gsDPWord(0xffc9ffc9, 0x00000000),
gsDPWord(0x40014001, 0x00010000),
gsDPWord(0x58185818, 0x00000000),
gsDPWord(0xc001c001, 0x00000000),
gsDPWord(0x00000000, 0x00000000),
gsDPWord(0x06200620, 0x00000000),
gsDPWord(0x00000000, 0x00000000),
gsDPWord(0xca8002f8, 0x02f402f4),
gsDPWord(0x01358000, 0x00000000),
gsDPWord(0x0009c000, 0x012bbf6a),
gsDPWord(0x0009c000, 0x01ccffb5),
gsDPWord(0x1fff1fff, 0x3fff01ff),
gsDPWord(0xffc9ffc9, 0x00000000),
gsDPWord(0x40014001, 0x00010000),
gsDPWord(0x581a581a, 0x00000000),
gsDPWord(0xc001c001, 0x00000000),
gsDPWord(0x00000000, 0x00000000),
gsDPWord(0x08770877, 0x00000000),
gsDPWord(0x00000000, 0x00000000),
#endif

#ifdef JUNK
    gsSPVertex(&tc_place_vtx, 4, 0),
    gsSP1Triangle(0, 1, 3, 0),
    gsSP1Triangle(3, 1, 2, 0),
#endif
    gsSPEndDisplayList(),
};

/*
 * TO ADD A TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx display list must be extern'd in tc.h, then
 * added to the 'testList_tc' table in tc.c as a Gfx pointer field of a
 * GfxTest_t struct.  You must also decide whether the existing top level DL's
 * will suffice for your application (you may need to provide a new top level
 * DL of your own design in toplevel.c).
 *
 */
