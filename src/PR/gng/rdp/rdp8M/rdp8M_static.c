
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
#include "gng.h"
#include "dldriver.h"
#include "rdp8M.h"
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

extern Gfx rdpew_triangle15[];
extern Vp bigscreen_viewport_d[];

static Vtx place_vtx[5] =  {
        {        -40,  40, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {         40,  40, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         40, -40, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {        -40, -40, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},
        {          0,   0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
};

static Vtx q1a[25] =  {
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


Gfx rdp8M_placebo_dl[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPViewport(&bigscreen_viewport_d),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD,
                                OS_K0_TO_PHYSICAL(H28R)),
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

Gfx rdp8M_test1[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPViewport(&bigscreen_viewport_d),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD,
                                OS_K0_TO_PHYSICAL(H28R)),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&place_vtx, 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};


Gfx rdp8M_big_image_test[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(0x0C084148,0),
    gsDPPipeSync(),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, 1024, OS_K0_TO_PHYSICAL(H28R)),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,1023,511),
    gsSPViewport(&bigscreen_viewport_d),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPDisplayList(rdpew_triangle15),

    gsSPEndDisplayList(),
};


#include "RGBA16checkerMM.h"

/*
 * Test 2, Frame 2:
 *
 * Test of perspective-corrected texture.
 * Uses same data from Test 1.
 *
 * Tue Oct 18 13:53:34 PDT 1994
 *
 */
Gfx rdp8M_square2[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 5, G_TX_RENDERTILE, G_ON),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, 1024, OS_K0_TO_PHYSICAL(H28R)),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,1023,511),
    gsSPViewport(&bigscreen_viewport_d),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),

    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetCombineMode(G_CC_TRILERP, G_CC_DECALRGB2),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_OPA_SURF2),

    /* 
     * Unroll the LoadTextureBlock for mipmapping test:
     *
     * The size of the LoadBlock and the tmem addresses of the
     * SetTile's are magic numbers fixed on how RGBA16checkerMM
     * was created...
     *
     * There may be other sized-related constants hard-coded...
     *
     */
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rdp8M_RGBA16checkerMM),
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
    gsDPSetColorDither(G_CD_BAYER),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPVertex(&(q1a[0]), 10, 0),
	gsSP1Triangle(0, 1, 5, 0),
	gsSP1Triangle(1, 5, 6, 0),
	gsSP1Triangle(1, 2, 6, 0),
	gsSP1Triangle(2, 6, 7, 0),
	gsSP1Triangle(2, 3, 7, 0),
	gsSP1Triangle(3, 7, 8, 0),
	gsSP1Triangle(3, 4, 8, 0),
	gsSP1Triangle(4, 8, 9, 0),


    gsSPVertex(&(q1a[5]), 10, 0),
	gsSP1Triangle(0, 1, 5, 0),
	gsSP1Triangle(1, 5, 6, 0),
	gsSP1Triangle(1, 2, 6, 0),
	gsSP1Triangle(2, 6, 7, 0),
	gsSP1Triangle(2, 3, 7, 0),
	gsSP1Triangle(3, 7, 8, 0),
	gsSP1Triangle(3, 4, 8, 0),
	gsSP1Triangle(4, 8, 9, 0),


    gsSPVertex(&(q1a[10]), 10, 0),
	gsSP1Triangle(0, 1, 5, 0),
	gsSP1Triangle(1, 5, 6, 0),
	gsSP1Triangle(1, 2, 6, 0),
	gsSP1Triangle(2, 6, 7, 0),
	gsSP1Triangle(2, 3, 7, 0),
	gsSP1Triangle(3, 7, 8, 0),
	gsSP1Triangle(3, 4, 8, 0),
	gsSP1Triangle(4, 8, 9, 0),


    gsSPVertex(&(q1a[15]), 10, 0),
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
 *
 * Try toggling as many nodes internal to the RDP as possible
 * using RDP commands.
 * 
 * 
 *
 */

#include "IA16Noise.h"
#include "Qsim_prims.h"

#define G_QSIM_BLEND	AA_EN | IM_RD | CVG_DST_CLAMP | CVG_X_ALPHA |           \
			ALPHA_CVG_SEL | FORCE_BL | ZMODE_OPA |                  \
			GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_IN, G_BL_1MA)

#define G_QSIM_BLEND2	AA_EN | IM_RD | CVG_DST_CLAMP | CVG_X_ALPHA |           \
			ALPHA_CVG_SEL | FORCE_BL | ZMODE_OPA |                  \
			GBL_c2(G_BL_CLR_IN, G_BL_A_SHADE, G_BL_CLR_IN, G_BL_1MA)

/* vertices for different types of triangles */
static Vtx test_qsim_v0[] =  {
        {   0, 0,  0, 0, 0x0000, 0xaa00, 0xaa, 0x55, 0xcc, 0x00 },
        {   2, 3,  4, 0, 0xaa00, 0x0000, 0x55, 0xaa, 0x33, 0xff },
        {   4, 2,  3, 0, 0x00aa, 0x00aa, 0x00, 0x00, 0x00, 0xaa },
};

static Vtx test_qsim_v1[] =  {
        {    900,  900,  1000, 0, 0x1111, 0xffff, 0x55, 0x66, 0xff, 0xff },
        {    902,  903,  1004, 0, 0x0000, 0x2302, 0x22, 0x99, 0xcc, 0x18 },
        {    904,  902,  1003, 0, 0xffff, 0x11aa, 0x44, 0x11, 0x12, 0x44 },
};

static Vtx test_qsim_v2[] =  {
        {    900, 0,  0, 0, 0xdead, 0xdada, 0xff, 0xff, 0xff, 0xff },
        {    902, 3,  4, 0, 0xbeef, 0xfeed, 0x55, 0xaa, 0x33, 0x55 },
        {    904, 2,  3, 0, 0xbaba, 0xeeaa, 0x00, 0x00, 0x00, 0xaa },
};

static Vtx test_qsim_v3[] =  {
        {   0,  900,  0, 0, 0xcaca, 0xaa00, 0xaa, 0x55, 0xcc, 0x00 },
        {   2,  903,  4, 0, 0xeaac, 0x0000, 0x55, 0xaa, 0x33, 0xff },
        {   4,  902,  3, 0, 0x00aa, 0x00aa, 0x00, 0x00, 0x00, 0xaa },
};

static Vtx test_qsim_v4[] =  {
        {   0, 0,   900, 0, 0x0000, 0xaa00, 0xaa, 0x55, 0xcc, 0x00 },
        {   2, 3,   904, 0, 0xaa00, 0x0000, 0x55, 0xaa, 0x33, 0xff },
        {   4, 2,   903, 0, 0x00aa, 0x00aa, 0x00, 0x00, 0x00, 0xaa },
};

static Vtx test_qsim_v5[] =  {
        {    900, 0,   900, 0, 0x0000, 0xaa00, 0xaa, 0x55, 0xcc, 0x00 },
        {    902, 3,   904, 0, 0xaa00, 0x0000, 0x55, 0xaa, 0x33, 0xff },
        {    904, 2,   903, 0, 0x00aa, 0x00aa, 0x00, 0x00, 0x00, 0xaa },
};

static Vtx test_qsim_v6[] =  {
        {   0,  900,   900, 0, 0x0000, 0xaa00, 0xaa, 0x55, 0xcc, 0x00 },
        {   2,  903,   904, 0, 0xaa00, 0x0000, 0x55, 0xaa, 0x33, 0xff },
        {   4,  902,   903, 0, 0x00aa, 0x00aa, 0x00, 0x00, 0x00, 0xaa },
};

static Vtx test_qsim_v7[] =  {
        {    900, 0,  0, 0, 0x0000, 0xaa00, 0xaa, 0x55, 0xcc, 0x00 },
        {    902, 3,  4, 0, 0xaa00, 0x0000, 0x55, 0xaa, 0x33, 0xff },
        {    904, 2,  3, 0, 0x00aa, 0x00aa, 0x00, 0x00, 0x00, 0xaa },
};


/*
 *  Qsim display list, designed to toggle as many internal nodes in the
 *  RDP as possible.  All NOISE params have been replaced by 1 for
 *  checksum consistency.
 */

Gfx rdp8M_qsim_test[] = {
    /* fill 1024x512 screen */
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, 1024, OS_K0_TO_PHYSICAL(H28R)),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,1023,511),
    gsSPViewport(&bigscreen_viewport_d),
    gsDPPipeSync(),
 
    /* set rendering modes */
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetColorDither(G_CD_ENABLE),
    gsDPSetCombineKey(G_CK_KEY),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILTCONV),
    gsDPSetCombineLERP (TEXEL0, TEXEL1, LOD_FRACTION, TEXEL0, 
			TEXEL0, TEXEL1, LOD_FRACTION, TEXEL0, 
			1, COMBINED, SHADE_ALPHA, SHADE, 
			1, COMBINED, SHADE, COMBINED),

    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetFogColor(39, 171, 255, 180),
    gsDPSetEnvColor(255, 14, 52, 156),
    gsDPSetKeyR(134, 87, 211),
    gsDPSetKeyGB(54, 21, 148, 237, 214, 90),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),

    gsDPPipeSync(),
    gsDPSetRenderMode(G_QSIM_BLEND, G_QSIM_BLEND2),
    gsDPSetTile(3, 2, 16, 0, 1, 0, 0, 5, 0, 0, 6, 0),

    /* Load Noise texture, 32x64 IA */
    gsDPLoadTextureBlock(rdpew_IA16Noise, G_IM_FMT_IA, G_IM_SIZ_16b, 32, 64, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         5, 6, G_TX_NOLOD, G_TX_NOLOD),

    /* 
     *  do a triangle to get steppers going, they will continue to
     *  step until next primitive.  Use this fact to check attribute
     *  muxes.
     */
#ifdef ALLOW_RDPBLOCK
    gsSPRDPBlock(&qsim_p0, sizeof(qsim_p0)),
#endif

    /* set registered values */
    gsDPPipeSync(),
    gsDPSetPrimColor(0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55),
    gsDPSetBlendColor(0x55, 0xaa, 0x55, 0xaa),
    gsDPSetFogColor(0xcc, 0x33, 0xcc, 0x33),
    gsDPSetFillColor(0xa5a5a5a5),
    gsDPSetEnvColor(0x55, 0xaa, 0x55, 0xaa),
    gsDPSetKeyR(0x33, 0xcc, 0x333),
    gsDPSetKeyGB(0xaa, 0x55, 0xaaa, 0x55, 0xaa, 0x555),
    gsDPSetConvert(0x155, 0x1aa, 0x155, 0x1aa, 0x155, 0x1aa),

    /* roll through each mux select one time, invert pattern in combiner */
    /* a/b mux */
    gsDPSetCombineLERP(	COMBINED,	0,		1,		0,
			COMBINED,	0,		LOD_FRACTION,	0,
			1,		COMBINED,	1,		0,
			1,		COMBINED,	PRIM_LOD_FRAC,	0),
    gsDPSetCombineLERP(	TEXEL0,		0,		1,		0,
			TEXEL0,         0,              LOD_FRACTION,   0,
			1,		TEXEL0,		1,		0,
			1,              TEXEL0,         PRIM_LOD_FRAC,  0),
    gsDPSetCombineLERP(	TEXEL1,		0,		1,		0,
			TEXEL1,         0,              LOD_FRACTION,   0,
			1,		TEXEL1,		1,		0,
			1,              TEXEL1,         PRIM_LOD_FRAC,  0),
    gsDPSetCombineLERP(	PRIMITIVE,	0,		1,		0,
			PRIMITIVE,      0,              LOD_FRACTION,   0,
			1,		PRIMITIVE,	1,		0,
			1,              PRIMITIVE,      PRIM_LOD_FRAC,  0),
    gsDPSetCombineLERP(	SHADE,		0,		1,		0,
			SHADE,          0,              LOD_FRACTION,   0,
			1,		SHADE,		1,		0,
			1,              SHADE,          PRIM_LOD_FRAC,  0),
    gsDPSetCombineLERP(	ENVIRONMENT,	0,		1,		0, 
			ENVIRONMENT,    0,              LOD_FRACTION,   0,
			1,		ENVIRONMENT,	1,		0,
			1,              ENVIRONMENT,    PRIM_LOD_FRAC,  0),
    gsDPSetCombineLERP(	1,		0,		1,		0, 
			1,          	0,              LOD_FRACTION,   0,
			1,		CENTER,		1,		0,
			1,		0,		PRIM_LOD_FRAC,	0),
    gsDPSetCombineLERP(	1,		0,		1,		0, 
			1,		0,		LOD_FRACTION,	0,
			1,		K4,		1,		0,
			1,              0,              PRIM_LOD_FRAC,  1),
    gsDPSetCombineLERP(	1,           	0, 		1,		0,
			1,              0,              LOD_FRACTION,	0,
			1,		0,		1,		0,
			1,              0,              PRIM_LOD_FRAC,	0),

    /* c rgb mux, c & d alpha mux */
    gsDPSetCombineLERP(	1, 		0, 		COMBINED,        0, 
			1,		0,		COMBINED,	 0,
			1, 		0,		COMBINED,        0,
			1,		0,		TEXEL0,	 	 0),
    gsDPSetCombineLERP(	1, 		0, 		TEXEL0,          0, 
			1,		0,              LOD_FRACTION,    0,
			1, 		0,		TEXEL0,          0,
			1,              0,         	PRIMITIVE,   	 0),
    gsDPSetCombineLERP(	1, 		0, 		TEXEL1,          0, 
			1,         	0,              SHADE,    	 0,
			1,		0,		TEXEL1,          0,
			1,              0,         	ENVIRONMENT,   	 0),
    gsDPSetCombineLERP(	1, 		0, 		PRIMITIVE,       0, 
			1,      	0,              LOD_FRACTION,    0,
			1,		0,		PRIMITIVE,       0,
			1,              0,      	PRIM_LOD_FRAC,   0),
    gsDPSetCombineLERP(	1, 		0, 		SHADE,           0, 
			1,          	0,              0,    		 0,
			1, 		0,		SHADE,           0,
			1,              0,          	0,   		 COMBINED),
    gsDPSetCombineLERP(	1, 		0, 		ENVIRONMENT,     0, 
			ENVIRONMENT,    0,              0,    		 0,
			1,		0,		ENVIRONMENT,     0,
			1,              ENVIRONMENT,    0,   		 TEXEL0),
    gsDPSetCombineLERP(	1, 		0, 		SCALE,           0, 
			1,          	0,              0,    		 0,
			1, 		0,		SCALE,           0,
			1,		0,		0,	 	 TEXEL1),
    gsDPSetCombineLERP(	1, 		0, 		COMBINED_ALPHA,  0, 
			1,		0,		0,	 	 0,
			1,		0,		COMBINED_ALPHA,  0,
			1,              0,              0,   		 PRIMITIVE),
    gsDPSetCombineLERP(	1, 		0, 		TEXEL0_ALPHA,    0, 
			1,		0,		0,	 	 0,
			1,		0,		TEXEL0_ALPHA,    0,
			1,		COMBINED,	0,	 	 SHADE),
    gsDPSetCombineLERP(	1, 		0, 		TEXEL1_ALPHA,	 0, 
			TEXEL0,         0,              0,    		 0,
			1,		0,		TEXEL1_ALPHA,    0,
			1,              TEXEL0,         0,   		 ENVIRONMENT),
    gsDPSetCombineLERP(	1, 		0, 		PRIMITIVE_ALPHA, 0, 
			TEXEL1,         0,              0,    		 0,
			1,		0,		PRIMITIVE_ALPHA, 0,
			1,              TEXEL1,         0,   		 1),
    gsDPSetCombineLERP(	1, 		0, 		SHADE_ALPHA,     0, 
			PRIMITIVE,      0,              0,    		 1,
			1,		0,		SHADE_ALPHA,     0,
			1,              PRIMITIVE,      0,   		 1),
    gsDPSetCombineLERP(	1, 		0, 		ENV_ALPHA,       0, 
			SHADE,          0,              0,    		 1,
			1,		0,		ENV_ALPHA,       0,
			1,              SHADE,          0,   		 1),
    gsDPSetCombineLERP(	1, 		0, 		LOD_FRACTION,    0, 
			ENVIRONMENT,    0,              0,    		 1,
			1,		0,		LOD_FRACTION,    0,
			1,              ENVIRONMENT,    0,   		 1),
    gsDPSetCombineLERP(	1, 		0, 		PRIM_LOD_FRAC,   0, 
			ENVIRONMENT,    0,              0,    		 1,
			1,		0,		PRIM_LOD_FRAC,   0,
			1,              ENVIRONMENT,    0,   		 1),
    gsDPSetCombineLERP(	1, 		0, 		K5,              0, 
			ENVIRONMENT,    0,              0,    		 1,
			1,		0, 		K5,              0,
			1,              ENVIRONMENT,    0,   		 1),
    gsDPSetCombineLERP(	1, 		0, 		0,               0, 
			ENVIRONMENT,    0,              0,    		 1,
			1, 		0,		0,		 0,
			1,              ENVIRONMENT,    0,   		 1),

    /* d mux */
    gsDPSetCombineLERP(	0,		0,		1,		COMBINED,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		COMBINED,
			1,              TEXEL0,    	0,   		TEXEL0),
    gsDPSetCombineLERP(	0,		0,		1,		TEXEL0,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		TEXEL0,
			1,              TEXEL0,    	0,   		TEXEL0),
    gsDPSetCombineLERP(	0,		0,		1,		TEXEL1,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		TEXEL1,
			1,              TEXEL0,    	0,   		TEXEL0),
    gsDPSetCombineLERP(	0,		0,		1,		PRIMITIVE,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		PRIMITIVE,
			1,              TEXEL0,    	0,   		TEXEL0),
    gsDPSetCombineLERP(	0,		0,		1,		SHADE,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		SHADE,
			1,              TEXEL0,    	0,   		TEXEL0),
    gsDPSetCombineLERP(	0,		0,		1,		ENVIRONMENT,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		ENVIRONMENT,
			1,              TEXEL0,    	0,   		TEXEL0),
    gsDPSetCombineLERP(	0,		0,		1,		CENTER,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		CENTER,
			1,              TEXEL0,    	0,   		TEXEL0),
    gsDPSetCombineLERP(	0,		0,		1,		K4,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		K4,
			1,              TEXEL0,    	0,   		TEXEL0),

    /* 
     *  do another primitive.  Needed to advance counters for primitive
     *  color buffer.  Set render mode for maximum randomness. Invert 
     *  pattern loaded into attribute registers.
     */
    gsDPPipeSync(),
    gsDPSetPrimColor(150, 205, 255, 0, 255, 228),
    gsDPSetFogColor(39, 171, 255, 180),
    gsDPSetEnvColor(255, 14, 52, 156),
    gsDPSetKeyR(134, 87, 211),
    gsDPSetKeyGB(54, 21, 148, 237, 214, 90),
    gsDPSetConvert(45, 114, 250, 77, 66, 69),

    gsDPSetRenderMode(G_QSIM_BLEND, G_QSIM_BLEND2),
    gsDPSetTile(3, 2, 16, 0, 1, 0, 0, 5, 0, 0, 6, 0),

    /* make noise get replicated on lsb's and bias around 0.5 
       this ensures a better spread of random  values */
    gsDPSetPrimColor(0x80, 0x80, 0x80, 0x80, 0x80, 0x49),
    gsDPSetConvert(0x0aa, 0x055, 0x0aa, 0x055, 0x0aa, 0x049),

    gsDPSetCombineLERP(	1,		0,		K5,		PRIMITIVE,
			1,		0,		PRIMITIVE,	TEXEL0,
			1,		COMBINED,	SHADE,		0,
			1,		COMBINED,	PRIM_LOD_FRAC,	0 ),

#ifdef ALLOW_RDPBLOCK
    gsSPRDPBlock(&qsim_p1, sizeof(qsim_p1)),
#endif

    gsDPPipeSync(),
    gsDPSetPrimColor(0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa),
    gsDPSetBlendColor(0xaa, 0x55, 0xaa, 0x55),
    gsDPSetFogColor(0x33, 0xcc, 0x33, 0xcc),
    gsDPSetFillColor(0x5a5a5a5a),
    gsDPSetEnvColor(0xaa, 0x55, 0xaa, 0x55),
    gsDPSetKeyR(0xcc, 0x33, 0xccc),
    gsDPSetKeyGB(0x55, 0xaa, 0x555, 0xaa, 0x55, 0xaaa),
    gsDPSetConvert(0x0aa, 0x055, 0x0aa, 0x055, 0x0aa, 0x055),

    /* make noise get replicated on lsb's and bias around 0.5 
       this ensures a better spread of random  values */
    gsDPSetPrimColor(0x80, 0x80, 0x80, 0x80, 0x80, 0x49),
    gsDPSetConvert(0x0aa, 0x055, 0x0aa, 0x055, 0x0aa, 0x049),

    gsDPSetCombineLERP(	1,		0,		K5,		PRIMITIVE,
			1,		0,		PRIMITIVE,	TEXEL0,
			1,		COMBINED,	SHADE,		0,
			1,		COMBINED,	PRIM_LOD_FRAC,	0 ),

    /* make edge walker/steppers go through large range of numbers */
#ifdef ALLOW_RDPBLOCK
    gsSPRDPBlock(&qsim_p2, sizeof(qsim_p2)),
#endif

    /* roll through each mux select one time, invert pattern in combiner */
    /* a/b mux */
    gsDPSetCombineLERP(	COMBINED,	0,		1,		0,
			COMBINED,	0,		LOD_FRACTION,	0,
			1,		COMBINED,	1,		0,
			1,		COMBINED,	PRIM_LOD_FRAC,	0),
    gsDPSetCombineLERP(	TEXEL0,		0,		1,		0,
			TEXEL0,         0,              LOD_FRACTION,   0,
			1,		TEXEL0,		1,		0,
			1,              TEXEL0,         PRIM_LOD_FRAC,  0),
    gsDPSetCombineLERP(	TEXEL1,		0,		1,		0,
			TEXEL1,         0,              LOD_FRACTION,   0,
			1,		TEXEL1,		1,		0,
			1,              TEXEL1,         PRIM_LOD_FRAC,  0),
    gsDPSetCombineLERP(	PRIMITIVE,	0,		1,		0,
			PRIMITIVE,      0,              LOD_FRACTION,   0,
			1,		PRIMITIVE,	1,		0,
			1,              PRIMITIVE,      PRIM_LOD_FRAC,  0),
    gsDPSetCombineLERP(	SHADE,		0,		1,		0,
			SHADE,          0,              LOD_FRACTION,   0,
			1,		SHADE,		1,		0,
			1,              SHADE,          PRIM_LOD_FRAC,  0),
    gsDPSetCombineLERP(	ENVIRONMENT,	0,		1,		0, 
			ENVIRONMENT,    0,              LOD_FRACTION,   0,
			1,		ENVIRONMENT,	1,		0,
			1,              ENVIRONMENT,    PRIM_LOD_FRAC,  0),
    gsDPSetCombineLERP(	1,		0,		1,		0, 
			1,          	0,              LOD_FRACTION,   0,
			1,		CENTER,		1,		0,
			1,		0,		PRIM_LOD_FRAC,	0),
    gsDPSetCombineLERP(	1,		0,		1,		0, 
			1,		0,		LOD_FRACTION,	0,
			1,		K4,		1,		0,
			1,              0,              PRIM_LOD_FRAC,  1),
    gsDPSetCombineLERP(	1,           	0, 		1,		0,
			1,              0,              LOD_FRACTION,	0,
			1,		0,		1,		0,
			1,              0,              PRIM_LOD_FRAC,	0),

    /* c rgb mux, c & d alpha mux */
    gsDPSetCombineLERP(	1, 		0, 		COMBINED,        0, 
			1,		0,		COMBINED,	 0,
			1, 		0,		COMBINED,        0,
			1,		0,		TEXEL0,	 	 0),
    gsDPSetCombineLERP(	1, 		0, 		TEXEL0,          0, 
			1,		0,              LOD_FRACTION,    0,
			1, 		0,		TEXEL0,          0,
			1,              0,         	PRIMITIVE,   	 0),
    gsDPSetCombineLERP(	1, 		0, 		TEXEL1,          0, 
			1,         	0,              SHADE,    	 0,
			1,		0,		TEXEL1,          0,
			1,              0,         	ENVIRONMENT,   	 0),
    gsDPSetCombineLERP(	1, 		0, 		PRIMITIVE,       0, 
			1,      	0,              LOD_FRACTION,    0,
			1,		0,		PRIMITIVE,       0,
			1,              0,      	PRIM_LOD_FRAC,   0),
    gsDPSetCombineLERP(	1, 		0, 		SHADE,           0, 
			1,          	0,              0,    		 0,
			1, 		0,		SHADE,           0,
			1,              0,          	0,   		 COMBINED),
    gsDPSetCombineLERP(	1, 		0, 		ENVIRONMENT,     0, 
			ENVIRONMENT,    0,              0,    		 0,
			1,		0,		ENVIRONMENT,     0,
			1,              ENVIRONMENT,    0,   		 TEXEL0),
    gsDPSetCombineLERP(	1, 		0, 		SCALE,           0, 
			1,          	0,              0,    		 0,
			1, 		0,		SCALE,           0,
			1,		0,		0,	 	 TEXEL1),
    gsDPSetCombineLERP(	1, 		0, 		COMBINED_ALPHA,  0, 
			1,		0,		0,	 	 0,
			1,		0,		COMBINED_ALPHA,  0,
			1,              0,              0,   		 PRIMITIVE),
    gsDPSetCombineLERP(	1, 		0, 		TEXEL0_ALPHA,    0, 
			1,		0,		0,	 	 0,
			1,		0,		TEXEL0_ALPHA,    0,
			1,		COMBINED,	0,	 	 SHADE),
    gsDPSetCombineLERP(	1, 		0, 		TEXEL1_ALPHA,	 0, 
			TEXEL0,         0,              0,    		 0,
			1,		0,		TEXEL1_ALPHA,    0,
			1,              TEXEL0,         0,   		 ENVIRONMENT),
    gsDPSetCombineLERP(	1, 		0, 		PRIMITIVE_ALPHA, 0, 
			TEXEL1,         0,              0,    		 0,
			1,		0,		PRIMITIVE_ALPHA, 0,
			1,              TEXEL1,         0,   		 1),
    gsDPSetCombineLERP(	1, 		0, 		SHADE_ALPHA,     0, 
			PRIMITIVE,      0,              0,    		 1,
			1,		0,		SHADE_ALPHA,     0,
			1,              PRIMITIVE,      0,   		 1),
    gsDPSetCombineLERP(	1, 		0, 		ENV_ALPHA,       0, 
			SHADE,          0,              0,    		 1,
			1,		0,		ENV_ALPHA,       0,
			1,              SHADE,          0,   		 1),
    gsDPSetCombineLERP(	1, 		0, 		LOD_FRACTION,    0, 
			ENVIRONMENT,    0,              0,    		 1,
			1,		0,		LOD_FRACTION,    0,
			1,              ENVIRONMENT,    0,   		 1),
    gsDPSetCombineLERP(	1, 		0, 		PRIM_LOD_FRAC,   0, 
			ENVIRONMENT,    0,              0,    		 1,
			1,		0,		PRIM_LOD_FRAC,   0,
			1,              ENVIRONMENT,    0,   		 1),
    gsDPSetCombineLERP(	1, 		0, 		K5,              0, 
			ENVIRONMENT,    0,              0,    		 1,
			1,		0, 		K5,              0,
			1,              ENVIRONMENT,    0,   		 1),
    gsDPSetCombineLERP(	1, 		0, 		0,               0, 
			ENVIRONMENT,    0,              0,    		 1,
			1, 		0,		0,		 0,
			1,              ENVIRONMENT,    0,   		 1),

    /* d mux */
    gsDPSetCombineLERP(	0,		0,		1,		COMBINED,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		COMBINED,
			1,              TEXEL0,    	0,   		TEXEL0),
    gsDPSetCombineLERP(	0,		0,		1,		TEXEL0,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		TEXEL0,
			1,              TEXEL0,    	0,   		TEXEL0),
    gsDPSetCombineLERP(	0,		0,		1,		TEXEL1,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		TEXEL1,
			1,              TEXEL0,    	0,   		TEXEL0),
    gsDPSetCombineLERP(	0,		0,		1,		PRIMITIVE,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		PRIMITIVE,
			1,              TEXEL0,    	0,   		TEXEL0),
    gsDPSetCombineLERP(	0,		0,		1,		SHADE,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		SHADE,
			1,              TEXEL0,    	0,   		TEXEL0),
    gsDPSetCombineLERP(	0,		0,		1,		ENVIRONMENT,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		ENVIRONMENT,
			1,              TEXEL0,    	0,   		TEXEL0),
    gsDPSetCombineLERP(	0,		0,		1,		CENTER,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		CENTER,
			1,              TEXEL0,    	0,   		TEXEL0),
    gsDPSetCombineLERP(	0,		0,		1,		K4,
			1,              SHADE,          0,   		SHADE,
			1, 		0, 		0, 		K4,
			1,              TEXEL0,    	0,   		TEXEL0),

    gsDPPipeSync(),


    /* do small prims, one of each type to test decoders */
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(&test_qsim_v0, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),

    gsDPPipeSync(),
    gsSPClearGeometryMode(G_SHADE),
    gsSPVertex(&test_qsim_v1, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),

    gsDPPipeSync(),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
    gsSPVertex(&test_qsim_v2, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),

    gsDPPipeSync(),
    gsSPClearGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
    gsSPVertex(&test_qsim_v3, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),

    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(&test_qsim_v4, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),

    gsDPPipeSync(),
    gsSPClearGeometryMode(G_SHADE),
    gsSPVertex(&test_qsim_v5, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),

    gsDPPipeSync(),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
    gsSPVertex(&test_qsim_v6, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),

    gsDPPipeSync(),
    gsSPClearGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
    gsSPVertex(&test_qsim_v7, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),


    /* do many small prims at random locations */


    gsSPEndDisplayList(),
};

/*
 * ADD TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx rdpew_display list must be extern'd in rdpverif.h, then
 * added to the 'testList' table in rdpverif.c
 *
 */
