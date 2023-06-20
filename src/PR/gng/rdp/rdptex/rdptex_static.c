
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
#include "rdptex.h"

/*
 * Test conventions:
 *
 * Data variable names can be about anything, as long as they are unique
 * and consistent in the table entry.
 *
 * In order to get around compiler weirdness, the table of tests
 * is in rdpverif.c, and the Gfx rdptex_lists must be extern'd in rdpverif.h
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

Gfx rdptex_placebo_dl[MAX_STATIC_GFX_SIZE] = {
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

Gfx rdptex_square0[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),

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

/* a texture */
#include "RGBA16grid.h"

static Vtx q1[8] =  {
#ifdef ONETRI
        {        -64,  64, -5, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff	},
        {         64,  64, -5, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff	},
        {         64, -64, -5, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff	},
        {        -64, -64, -5, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff	},
#else
        {        -64,  64, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff	},
        {         64,  64, 0, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff	},
        {         64, -64, 0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff	},
        {        -64, -64, 0, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff	},
#endif

	/* second 4 points used for perspective test... */
        { -64,  0,  64, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff	},
        {  64,  0,  64, 0, (127 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff	},
        {  64,  0, -64, 0, (127 << 6), (127 << 6), 0x1f, 0x1f, 0xff, 0xff },
        { -64,  0, -64, 0, ( 0 << 6), (127 << 6), 0, 0x1f, 0xff, 0xff	},
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

Gfx rdptex_square1[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(rdptex_RGBA16grid, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&(q1[0]), 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};
/* end of case 1 */

#define USE_MIPMAP
#ifdef USE_MIPMAP
/*#include "gridmm.h"*/
#   include "RGBA16checkerMM.h"
#else
#   include "RGBA16checker.h"
#endif

/*
 * Test 2, Frame 2:
 *
 * Test of perspective-corrected texture.
 * Uses same data from Test 1.
 *
 * Tue Oct 18 13:53:34 PDT 1994
 *
 */
Gfx rdptex_square2[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 5, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),

#ifdef USE_MIPMAP
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
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, rdptex_RGBA16checkerMM),
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
#else
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPLoadTextureBlock(RGBA16checker, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 5, 5, G_TX_NOLOD, G_TX_NOLOD),
#endif
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


/*
    gsSPVertex(&(q1[4]), 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
*/
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};
/* end of case 2 */

/*
 * Test 3, Frame 3:
 *
 * Simple square with a RGBA 16 texture.
 *
 * Thu Oct 13 16:21:07 PDT 1994
 *
 */

/* a texture */
#include "RGBA16dana.h"

static Vtx texfmt_q1[4] =  {
        { -50, 100, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff	},
        {   0, 100, 0, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff	},
        {   0, 50, 0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff	},
        { -50, 50, 0, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff	},
};

Gfx rdptex_texfmt_RGBA16[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPLoadTextureBlock(rdptex_RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&texfmt_q1, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};
/* end of case 3 */

/*
 * Test 4, Frame 4:
 *
 * Simple square with a IA 8 texture.
 *
 * Thu Oct 13 16:21:07 PDT 1994
 *
 */

#include "IA8grid.h"

static Vtx texfmt_q2[4] =  {
        {   0, 100, 0, 0, ( 0 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  50, 100, 0, 0, (31 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff	},
        {  50, 50, 0, 0, (31 << 6), (31 << 6), 0x00, 0xff, 0x00, 0xff	},
        {   0, 50, 0, 0, ( 0 << 6), (31 << 6), 0xff, 0x00, 0x00, 0xff	},
};

Gfx rdptex_texfmt_IA8[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(IA8grid, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&texfmt_q2, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};
/* end of case 4 */

/*
 * Test 5, Frame 5:
 *
 * Simple square with a IA 4 texture.
 *
 * Thu Oct 13 16:21:07 PDT 1994
 *
 */

#include "IA4grid.h"

static Vtx texfmt_q3[4] =  {
        {   50, 100, 0, 0, ( 0 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  100, 100, 0, 0, (31 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff	},
        {  100, 50, 0, 0, (31 << 6), (31 << 6), 0x00, 0xff, 0x00, 0xff	},
        {   50, 50, 0, 0, ( 0 << 6), (31 << 6), 0xff, 0x00, 0x00, 0xff	},
};

Gfx rdptex_texfmt_IA4[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock_4b(IA4grid, G_IM_FMT_IA, 32, 32, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&texfmt_q3, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};
/* end of case 5 */

/*
 * Test 6, Frame 6:
 *
 * Simple square with a IA 16 texture.
 *
 * Thu Oct 13 16:21:07 PDT 1994
 *
 */

#include "IA16grid.h"

static Vtx texfmt_q4[4] =  {
        {  -100, 50, 0, 0, ( 0 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  -50, 50, 0, 0, (31 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff	},
        {  -50, 0, 0, 0, (31 << 6), (31 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  -100, 0, 0, 0, ( 0 << 6), (31 << 6), 0xff, 0x00, 0x00, 0xff	},
};

Gfx rdptex_texfmt_IA16[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(IA16grid, G_IM_FMT_IA, G_IM_SIZ_16b, 32, 32, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&texfmt_q4, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};
/* end of case 6 */

/*
 * Test 7, Frame 7:
 *
 * Simple square with a RGBA texture using loadtile to loada subtile
 * 64 bit aligned and non aligned tile
 *
 * Thu Oct 20 13:31:14 PDT 1994
 *
 */

static Vtx loadtile_q1[4] =  {
        {  -50, 50, 0, 0, ( 4 << 6), ( 4 << 6), 0x00, 0xff, 0x00, 0xff	},
        {    0, 50, 0, 0, (27 << 6), ( 4 << 6), 0xff, 0x00, 0x00, 0xff	},
        {    0, 0, 0, 0, (27 << 6), (27 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  -50, 0, 0, 0, ( 4 << 6), (27 << 6), 0xff, 0x00, 0x00, 0xff	},
};


Gfx rdptex_loadtile_RGBA16[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureTile(rdptex_RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32,
			 5, 5, 27, 27, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&loadtile_q1, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};

#include "I4grid.h"
#include "I8grid.h"
#include "IA16Noise.h"

static Vtx loadtile_q5[4] =  {
        {  50, 0, 0, 0, ( 4 << 6), ( 4 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  100, 0, 0, 0, (27 << 6), ( 4 << 6), 0xff, 0x00, 0x00, 0xff	},
        {  100, -50, 0, 0, (27 << 6), (27 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  50, -50, 0, 0, ( 4 << 6), (27 << 6), 0xff, 0x00, 0x00, 0xff},
};

Gfx rdptex_loadtile_I4[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureTile_4b(I4grid, G_IM_FMT_I, 32, 32,
			 5, 5, 27, 27, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&loadtile_q5, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};

static Vtx loadtile_q6[4] =  {
        {  50, -50, 0, 0, ( 4 << 6), ( 4 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  100, -50, 0, 0, (27 << 6), ( 4 << 6), 0xff, 0x00, 0x00, 0xff	},
        {  100, -100, 0, 0, (27 << 6), (27 << 6), 0x00, 0xff, 0x00, 0xff},
        {  50, -100, 0, 0, ( 4 << 6), (27 << 6), 0xff, 0x00, 0x00, 0xff},
};

Gfx rdptex_loadtile_I8[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureTile(I8grid, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32,
			 5, 5, 27, 27, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&loadtile_q6, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};

static Vtx loadtile_q7[4] =  {
        {  0, -50, 0, 0, ( 4 << 6), ( 4 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  50, -50, 0, 0, (27 << 6), ( 4 << 6), 0xff, 0x00, 0x00, 0xff	},
        {  50, -100, 0, 0, (27 << 6), (27 << 6), 0x00, 0xff, 0x00, 0xff},
        {  0, -100, 0, 0, ( 4 << 6), (27 << 6), 0xff, 0x00, 0x00, 0xff},
};

Gfx rdptex_loadtile_IA16[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0,0,0,128),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureTile(IA16Noise, G_IM_FMT_IA, G_IM_SIZ_16b, 32, 32,
			 5, 5, 27, 27, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&loadtile_q7, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};
/*
 * Test 8, Frame 8:
 *
 * Simple square with a RGBA texture using loadtile to loada subtile
 * non aligned tile
 *
 * Mon Oct 24 15:03:26 PDT 1994
 *
 */

static Vtx loadtile_q2[4] =  {
        {    0, 50, 0, 0, ( 5 << 6), ( 5 << 6), 0x00, 0xff, 0x00, 0xff	},
        {   50, 50, 0, 0, (26 << 6), ( 5 << 6), 0xff, 0x00, 0x00, 0xff	},
        {   50, 0, 0, 0, (26 << 6), (26 << 6), 0x00, 0xff, 0x00, 0xff	},
        {    0, 0, 0, 0, ( 5 << 6), (26 << 6), 0xff, 0x00, 0x00, 0xff	},
};

Gfx rdptex_loadtile_nonalign_RGBA16[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureTile(rdptex_RGBA16grid, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32,
			 6, 6, 26, 26, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&loadtile_q2, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};
/* end of case 8 */

/*
 * Test 9, Frame 9:
 *
 * 8 bit load tiles
 *
 * Mon Oct 24 15:03:26 PDT 1994
 *
 */

static Vtx loadtile_q3[4] =  {
        {  50, 50, 0, 0, ( 4 << 6), ( 4 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  100, 50, 0, 0, (27 << 6), ( 4 << 6), 0xff, 0x00, 0x00, 0xff	},
        {  100, 0, 0, 0, (27 << 6), (27 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  50, 0, 0, 0, ( 4 << 6), (27 << 6), 0xff, 0x00, 0x00, 0xff},
};

Gfx rdptex_loadtile_8b[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureTile(IA8grid, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32,
			 6, 6, 26, 26, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&loadtile_q3, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};
/* end of case 9 */

/*
 * Test 10, Frame 10:
 *
 * 4 bit load tiles
 *
 * Mon Oct 24 15:03:26 PDT 1994
 *
 */

static Vtx loadtile_q4[4] =  {
        {  -100, 0, 0, 0, ( 4 << 6), ( 4 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  -50, 0, 0, 0, (27 << 6), ( 4 << 6), 0xff, 0x00, 0x00, 0xff	},
        {  -50, -50, 0, 0, (27 << 6), (27 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  -100, -50, 0, 0, ( 4 << 6), (27 << 6), 0xff, 0x00, 0x00, 0xff},
};

Gfx rdptex_loadtile_4b[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureTile_4b(IA4grid, G_IM_FMT_IA, 32, 32,
			 5, 5, 27, 27, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&loadtile_q4, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};
/* end of case 10 */

/*
 * Test 11, Frame 11:
 *
 * 8 bit I texture
 *
 * Tue Oct 25 14:02:24 PDT 1994
 *
 */


static Vtx texfmt_q5[4] =  {
        {  -50, 0, 0, 0, ( 0 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  0, 0, 0, 0, (31 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff	},
        {  0, -50, 0, 0, (31 << 6), (31 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  -50, -50, 0, 0, ( 0 << 6), (31 << 6), 0xff, 0x00, 0x00, 0xff},
};

Gfx rdptex_texfmt_I8[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEI, G_CC_MODULATEI),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(I8grid, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&texfmt_q5, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};
/* end of case 11 */

/*
 * Test 12, Frame 12:
 *
 * 4 bit I texture
 *
 * Tue Oct 25 14:02:24 PDT 1994
 *
 */


static Vtx texfmt_q6[4] =  {
        {  0, 0, 0, 0, ( 0 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  50, 0, 0, 0, (31 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff	},
        {  50, -50, 0, 0, (31 << 6), (31 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  0, -50, 0, 0, ( 0 << 6), (31 << 6), 0xff, 0x00, 0x00, 0xff},
};

Gfx rdptex_texfmt_I4[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEI, G_CC_MODULATEI),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock_4b(I4grid, G_IM_FMT_I, 32, 32, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&texfmt_q6, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};
/* end of case 12 */

/*
 * Test 15, Frame 15:
 *
 * Simple square with a texture.
 * uses date from test 1
 *
 */

Gfx rdptex_cpyfmt_RGBA16[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(rdptex_RGBA16grid, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCycleType(G_CYC_COPY),
    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle(50<<2, 50<<2, 81<<2, 81<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipeSync(),
    gsSPVertex(&q1, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};
/* end of case 15 */

/*
 * Test 20, Frame 20:
 *
 *  4 bit I texture, test sliding texture when entire texture fits in
 *  Tmem.
 *
 */

#include "I4oddcheck.h"

Vtx txfmt_q20[4] =  {
        { -51,-51, 0, 0, ( 0 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff	},
        { -17,-51, 0, 0, (31 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff	},
        { -17,-17, 0, 0, (31 << 6), (31 << 6), 0x00, 0xff, 0x00, 0xff	},
        { -51,-17, 0, 0, ( 0 << 6), (31 << 6), 0xff, 0x00, 0x00, 0xff	},
};
/* end of case 20 */

/*
 * Test 21, Frame 21:
 *
 *  16b bit RGBA texture, test scrolling large texture around screen
 *
 */

#include "RGBA16mario.h"

Vtx txfmt_q21[4] =  {
        { -68,-51, 0, 0, ( 0 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff	},
        { -51,-51, 0, 0, (31 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff	},
        { -51,-34, 0, 0, (31 << 6), (31 << 6), 0x00, 0xff, 0x00, 0xff	},
        { -68,-34, 0, 0, ( 0 << 6), (31 << 6), 0xff, 0x00, 0x00, 0xff	},
};
/* end of case 21 */


/*
 * Test 22, Frame 22:
 *
 *  16b bit RGBA texture, test scrolling small texture on box (uses perspective) *  each face has texture scrolling in different direction while box is
 *  tumbling.
 */

#include "RGBA16mario_2.h"

/* box vertices */
Vtx box_vtx[] = {
{  -25, -25,   0, 0, (31 << 6),         0,   0,   0,   0, 128 }, /* side 0 */
{  -25, -25,  50, 0, (31 << 6), (31 << 6), 255,   0,   0, 128 },
{  -25,  25,  50, 0,         0, (31 << 6),   0, 254,   0, 128 },
{  -25,  25,   0, 0,         0,         0, 255, 254,   0, 128 },

{  -25,  25,   0, 0, (31 << 6),         0, 230, 230, 230, 255 }, /* side 1 */
{  -25,  25,  50, 0, (31 << 6), (31 << 6), 230, 230, 230, 255 },
{   25,  25,  50, 0,         0, (31 << 6), 230, 230, 230, 255 },
{   25,  25,   0, 0,         0,         0, 230, 230, 230, 255 },

{   25,  25,   0, 0,         0,         0, 255, 254, 252, 128 }, /* side 2 */
{   25,  25,  50, 0,         0, (31 << 6),   0, 254, 252, 128 },
{   25, -25,  50, 0, (31 << 6), (31 << 6), 255,   0, 252, 128 },
{   25, -25,   0, 0, (31 << 6),         0,   0,   0, 252, 128 },

{   25, -25,   0, 0,         0,         0,   0,   0, 252, 128 }, /* side 3 */
{   25, -25,  50, 0,         0, (31 << 6), 255,   0, 252, 128 },
{  -25, -25,  50, 0, (31 << 6), (31 << 6), 255,   0,   0, 128 },
{  -25, -25,   0, 0, (31 << 6),         0,   0,   0,   0, 128 },

{   25, -25,  50, 0,         0,         0, 255, 130, 130, 255 }, /* top */
{   25,  25,  50, 0, (31 << 6),         0, 255, 130, 130, 255 },
{  -25,  25,  50, 0, (31 << 6), (31 << 6), 255, 130, 130, 255 },
{  -25, -25,  50, 0,         0, (31 << 6), 255, 130, 130, 255 },

{   25,  25,   0, 0, (31 << 6),         0, 255, 254, 252, 128 }, /* bottom */
{   25, -25,   0, 0, (31 << 6), (31 << 6),   0,   0, 252, 128 },
{  -25, -25,   0, 0,         0, (31 << 6),   0,   0,   0, 128 },
{  -25,  25,   0, 0,         0,         0, 255, 254,   0, 128 }};

/* end of case 22 */



/*
 * Test 30, Frame 30:
 *
 * Collection of texture tests to run for nightly toplevel texture regression
 * DP in 1 clock mode
 *
 * Mon Oct 24 15:03:26 PDT 1994
 *
 */

Gfx rdptex_texture_regression[MAX_STATIC_GFX_SIZE] = {
    gsSPDisplayList(rdptex_texfmt_RGBA16),
    gsSPDisplayList(rdptex_texfmt_IA8),
    gsSPDisplayList(rdptex_texfmt_IA4),
    gsSPDisplayList(rdptex_texfmt_IA16),
    gsSPDisplayList(rdptex_loadtile_RGBA16),
    gsSPDisplayList(rdptex_loadtile_nonalign_RGBA16),
    gsSPDisplayList(rdptex_loadtile_8b),
    gsSPDisplayList(rdptex_loadtile_4b),
    gsSPDisplayList(rdptex_texfmt_I8),
    gsSPDisplayList(rdptex_texfmt_I4),
    gsSPDisplayList(rdptex_loadtile_I4),
    gsSPDisplayList(rdptex_loadtile_I8),
    gsSPDisplayList(rdptex_loadtile_IA16),
    gsSPEndDisplayList(),
};
/* end of case 30 */

/*
 * Test 31, Frame 31:
 *
 * Collection of texture tests to run for nightly toplevel texture regression
 * DP in 2 clock mode
 *
 * Tue Oct 25 11:37:39 PDT 1994
 *
 */

Gfx rdptex_texfmt_IA8_2clock[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_PASS2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(IA8grid, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&texfmt_q2, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};

static Vtx loadtile_2clk[4] =  {
        {  -50, 50, 0, 0, ( 4 << 6), ( 4 << 6), 0x00, 0xff, 0x00, 0xff	},
        {    0, 50, 0, 0, (27 << 6), ( 4 << 6), 0xff, 0x00, 0x00, 0xff	},
        {    0, 0, 0, 0, (27 << 6), (27 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  -50, 0, 0, 0, ( 4 << 6), (27 << 6), 0xff, 0x00, 0x00, 0xff	},
};

Gfx rdptex_loadtile_RGBA16_2clock[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetPrimColor(0, 0, 0, 64, 0, 64),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureTile(rdptex_RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32,
			 5, 5, 27, 27, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&loadtile_2clk, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};

/*
 * Test 45, Frame 45:
 *
 * 2 clock test with exact differences between clock 1 and 2 in CC/BL/MS
 * has random noise, therefore, visual checks only
 *
 * Fri Dec 30 12:18:02 PST 1994
 *
 */

/*
#define	G_CC_NIGHTVISION1	NOISE, TEXEL0, PRIMITIVE_ALPHA, TEXEL0, 0, 0, 0, 0

Changed noise to env to avoid inconsistent checksums
*/
#define	G_CC_NIGHTVISION1	ENVIRONMENT, TEXEL0, PRIMITIVE_ALPHA, TEXEL0, 0, 0, 0, 0
#define	G_CC_NIGHTVISION2	PRIMITIVE, COMBINED, PRIMITIVE_ALPHA, COMBINED, 0, 0, 0, SHADE

Gfx rdptex_cycle2_exact[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetPrimColor(0, 0, 0, 64, 0, 64),
    gsDPSetEnvColor(195, 0, 232, 0),
    gsDPSetCombineMode(G_CC_NIGHTVISION1, G_CC_NIGHTVISION2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureTile(rdptex_RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32,
			 5, 5, 27, 27, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&loadtile_2clk, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx rdptex_loadtile_4b_2clock[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_PASS2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureTile_4b(IA4grid, G_IM_FMT_IA, 32, 32,
			 5, 5, 27, 27, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&loadtile_q4, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};

Gfx rdptex_texture_regression2[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPDisplayList(rdptex_texfmt_IA8_2clock),
    gsSPDisplayList(rdptex_loadtile_RGBA16_2clock),
    gsSPDisplayList(rdptex_loadtile_4b_2clock),
    gsSPEndDisplayList(),
};
/* end of case 31 */

/*
 * Test 32, Frame 32:
 *
 * 1 clock texture regression test with interlace mode on, odd field
 *
 * Tue Nov  8 17:37:54 PST 1994
 *
 */

Gfx rdptex_interlace_odd_texture_regression[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    /*
     * set scissoring to make sure rendering is scissored but not texture load
     */
    gsDPSetScissor(G_SC_ODD_INTERLACE, 85, 32, SCREEN_WD-1-50, SCREEN_HT-1-75),
    gsSPDisplayList(rdptex_texture_regression),
    gsSPEndDisplayList(),
};
/* end of case 32 */

/*
 * Test 33, Frame 33:
 *
 * 1 clock texture regression test with interlace mode on, even field
 *
 * Tue Nov  8 17:37:54 PST 1994
 *
 */

Gfx rdptex_interlace_even_texture_regression[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    /*
     * set scissoring to make sure rendering is scissored but not texture load
     */
    gsDPSetScissor(G_SC_EVEN_INTERLACE, 85, 32, SCREEN_WD-1-50, SCREEN_HT-1-75),
    gsSPDisplayList(rdptex_texture_regression),
    gsSPEndDisplayList(),
};
/* end of case 33 */

/*
 * Test 34, Frame 34:
 *
 * 2 clock texture regression test with interlace mode on, odd field
 *
 * Tue Nov  8 17:37:54 PST 1994
 *
 */

Gfx rdptex_interlace_odd_texture_regression2[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    /*
     * set scissoring to make sure rendering is scissored but not texture load
     */
    gsDPSetScissor(G_SC_ODD_INTERLACE, 85, 32, SCREEN_WD-1-50, SCREEN_HT-1-75),
    /* gsDPSetScissor(G_SC_NON_INTERLACE, 0, 113, SCREEN_WD-1, 114), */
    gsSPDisplayList(rdptex_texture_regression2),
    gsSPEndDisplayList(),
};
/* end of case 34 */

/*
 * Test 35, Frame 35:
 *
 * 2 clock texture regression test with interlace mode on, even field
 *
 * Tue Nov  8 17:37:54 PST 1994
 *
 */

Gfx rdptex_interlace_even_texture_regression2[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    /*
     * set scissoring to make sure rendering is scissored but not texture load
     */
    gsDPSetScissor(G_SC_EVEN_INTERLACE, 85, 32, SCREEN_WD-1-50, SCREEN_HT-1-75),
    /* gsDPSetScissor(G_SC_NON_INTERLACE, 0, 110, SCREEN_WD-1, 111), */
    gsSPDisplayList(rdptex_texture_regression2),
    gsSPEndDisplayList(),
};
/* end of case 35 */

/*
 * Test 36, Frame 36:
 *
 * 16-bit copies
 *
 * Fri Nov 18 17:35:27 PST 1994
 *
 */

#include "RGBA16mario32.h"

static Vtx copy_q1[4] =  {
        {        -64,  64, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff },
        {         64,  64, 0, 0, (63 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff      },
        {         64, -64, 0, 0, (63 << 6), (63 << 6), 0x1f, 0x1f, 0xff, 0xff   },
        {        -64, -64, 0, 0, ( 0 << 6), (63 << 6), 0, 0x1f, 0xff, 0xff      },
};

static TexRect copy_trect4[] = {
/* set offset in tile   */
    gsDPTextureRectangle(228<<2, 20<<2, 291<<2, 83<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10)
};

/* offset texture start point by 3 texels and the rectangle by 1 pixels */
static TexRect copy_trect3[] = {
    gsDPTextureRectangle(156<<2, 20<<2, 218<<2, 82<<2, G_TX_RENDERTILE, 3<<5, 3<<5,
4<<10, 1<<10)
};

static TexRect copy_trect2[] = {
    gsDPTextureRectangle(83<<2, 20<<2, 146<<2, 83<<2, G_TX_RENDERTILE, 0, 0, 4<<10,
1<<10)
};

static TexRect copy_trect1[] = {
    gsDPTextureRectangle(10<<2, 20<<2, 73<<2, 83<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10)
};

Gfx rdptex_copyRGBA16[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_COPY),

    gsDPLoadTextureBlock(RGBA16mario32, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32,32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         5, 5, G_TX_NOLOD, G_TX_NOLOD),

    gsDPSetTileSize(G_TX_RENDERTILE, 2<<2, 2<<2,
            (32-1) << G_TEXTURE_IMAGE_FRAC,
            (32-1) << G_TEXTURE_IMAGE_FRAC),

    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle(228<<2, 20<<2, 291<<2, 83<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

    gsDPLoadTextureBlock(RGBA16mario32, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32,32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         5, 5, G_TX_NOLOD, G_TX_NOLOD),

    gsSPTextureRectangle(156<<2, 20<<2, 218<<2, 82<<2, G_TX_RENDERTILE, 3<<5, 3<<5, 4<<10, 1<<10),
    gsSPTextureRectangle(83<<2, 20<<2, 146<<2, 83<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),
    gsDPPipeSync(),

    gsDPLoadTextureBlock(RGBA16mario32, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(10<<2, 20<<2, 73<<2, 83<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPEndDisplayList(),

};


/*
 * Test 37, Frame 37
 *
 * 16-bit texture rectangle in 1cycle mode
 * 123pixels x 125pixels
 * Fri Nov 18 18:59:20 PST 1994
 *
 */

static TexRect mag_trect1[] = {
    gsDPTextureRectangle(20<<2, 20<<2, 143<<2, 145<<2, G_TX_RENDERTILE, 0, 0, 1<<9,
0x7f<<9)
};
static TexRect mag_trect2[] = {
    gsDPTextureRectangleFlip(163<<2, 20<<2, 286<<2, 145<<2, G_TX_RENDERTILE, 0, 0, 0x7f<<9, 1<<9)
};

Gfx rdptex_magRGBA16[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(RGBA16mario32, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle(20<<2, 20<<2, 143<<2, 145<<2, G_TX_RENDERTILE, 0, 0, 1<<9, 0x7f<<9),
    gsSPTextureRectangleFlip(163<<2, 20<<2, 286<<2, 145<<2, G_TX_RENDERTILE, 0, 0, 0x7f<<9, 1<<9),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /*done; turn texture off*/
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPEndDisplayList(),
};


/*
 * Test 38, Frame 38
 *
 * 1 cycle LOD test
 * 
 * Mon Dec 19 17:26:39 PST 1994
 * -Ashok
 */
#include "RGBA16gridMM.h"
#include "runway_vtx.h"

Gfx rdptex_lodRGBA16MM[512] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),  
    gsDPSetPrimColor(0,0,0,0,0,0),
    gsSPTexture(0x8000, 0x8000, 5, 0x0, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_LOD),
    gsDPSetTextureFilter(G_TF_BILERP),

#include "runway_cmds.h"

    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};


/*
 * Test 61, Frame 61
 *
 * 1 cycle LOD test w/ static MIPMAP
 *
 * Mon Feb  6 14:01:51 PST 1995
 *
 * Made mipmap be automatically generated with rgb2c -c MIP
 *
 * Thu Feb  9 10:19:58 PST 1995
 *
 * -Rich W.  (see test 38)
 */

Gfx rdptex_rww_lodRGBA16MM[512] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsSPTexture(0x8000, 0x8000, 5, 0x0, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_LOD),
    gsDPSetTextureFilter(G_TF_BILERP),

#include "runway_cmds.h"

    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};



/*
 * Test 39, Frame 39
 *
 * 2 cycle trilerp texture + detail test
 *
 * Mon Dec 19 13:11:30 PST 1994
 * -Ashok
 *
 */

#include "I8crater32.h"

#define gsDPLoadTextureBlockDet32(timg, fmt, siz, width, height, length,	\
                pal, cms, cmt, masks, maskt, shifts, shiftt)            \
									\
        gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 1, I8crater32),	\
        gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 0, 0, G_TX_LOADTILE,   	\
			0 , G_TX_WRAP | G_TX_NOMIRROR, 5 ,G_TX_NOLOD, 	\
			G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),     	\
        gsDPLoadSync(),                                                 \
        gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 0x0),      		\
	gsDPTileSync(),							\
        gsDPSetTextureImage(fmt, siz, 1, timg),                         \
        gsDPSetTile(fmt, siz, 0, 128, G_TX_LOADTILE, 0 , cmt, maskt,	\
                shiftt, cms, masks, shifts),                            \
        gsDPLoadSync(),                                                 \
        gsDPLoadBlock(G_TX_LOADTILE, 0, 0, length-1,0x0),      		\
        gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 4, 0, 			\
                0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0xe, 		\
		G_TX_WRAP | G_TX_NOMIRROR, 5,                       	\
		0xe),							\
        gsDPSetTileSize(0, 0, 0,                                        \
                (32-1) << G_TEXTURE_IMAGE_FRAC,                        	\
                (32-1) << G_TEXTURE_IMAGE_FRAC),                       	\
        gsDPSetTile(fmt, siz, ((((width) * siz##_BYTES)+7)>>3), 128,	\
                1, pal, cmt, maskt, 0, cms, masks,   			\
                0),        			                      	\
        gsDPSetTileSize(1, 0, 0,                          		\
                (32-1) << G_TEXTURE_IMAGE_FRAC,                      	\
                (32-1) << G_TEXTURE_IMAGE_FRAC),			\
        gsDPSetTile(fmt, siz, ((((16) * siz##_BYTES)+7)>>3), 384,      	\
                2, pal, cmt, (maskt - 1), 1, cms, (masks -1), 		\
		1),							\
        gsDPSetTileSize(2, 0, 0,                          		\
                (16-1) << G_TEXTURE_IMAGE_FRAC,                      	\
                (16-1) << G_TEXTURE_IMAGE_FRAC),			\
        gsDPSetTile(fmt, siz, ((((8) * siz##_BYTES)+7)>>3), 448,      	\
                3, pal, cmt, (maskt-2), 2, cms, (masks-2),   		\
                2),                                                	\
        gsDPSetTileSize(3, 0, 0,                          		\
                (8-1) << G_TEXTURE_IMAGE_FRAC,                      	\
                (8-1) << G_TEXTURE_IMAGE_FRAC),				\
        gsDPSetTile(fmt, siz, ((((4) * siz##_BYTES)+7)>>3), 464,      	\
                4, pal, cmt, (maskt-3), 3, cms, (masks-3),   		\
                3),                                                	\
        gsDPSetTileSize(4, 0, 0,                          		\
                (4-1) << G_TEXTURE_IMAGE_FRAC,                      	\
                (4-1) << G_TEXTURE_IMAGE_FRAC),				\
        gsDPSetTile(fmt, siz, ((((2) * siz##_BYTES)+7)>>3), 468,      	\
                5, pal, cmt, (maskt-4), 4, cms, (masks-4),   		\
                4),                                                	\
        gsDPSetTileSize(5, 0, 0,                          		\
                (2-1) << G_TEXTURE_IMAGE_FRAC,                      	\
                (2-1) << G_TEXTURE_IMAGE_FRAC),				\
        gsDPSetTile(fmt, siz, ((((1) * siz##_BYTES)+7)>>3), 470,      	\
                6, pal, cmt, (maskt-5), 5, cms, (masks-5),   		\
                5),                                                	\
        gsDPSetTileSize(6, 0, 0,                          		\
                (1-1) << G_TEXTURE_IMAGE_FRAC,                      	\
                (1-1) << G_TEXTURE_IMAGE_FRAC)

Gfx rdptex_detail32RGBA16MM[512] = {

    gsDPPipeSync(),
   gsDPLoadTextureBlockDet32(rdptex_RGBA16gridMM,G_IM_FMT_RGBA,G_IM_SIZ_16b,32,32,1372,0,
			G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			5,5, G_TX_NOLOD,G_TX_NOLOD),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetPrimColor(0,0,0,0,0,0),
    gsDPSetCombineMode(G_CC_TRILERP, G_CC_DECALRGB2),  
    gsSPTexture(0x8000, 0x8000, 5, 0x0, G_ON),
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_LOD),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureDetail(G_TD_DETAIL),

#include "runway_cmds.h"

    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};




/*
 *  Test 40, test load_tlut command, color-index textures
 */
#include "Tlut0.h"
#include "CItest0.h"
#include "Tlut1.h"
#include "CI4circle.h"
#include "Tlut2.h"
#include "CI8circle.h"
#include "Tlut3.h"
#include "RGBA32eye.h"

unsigned short OneEntryTlut[] = { 0xf83f };

static Vtx load_tlut_q1[] =  {
        {         -64,   64, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff 	},
        {          64,   64, 0, 0, (15 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff    },
        {          64,  -64, 0, 0, (15 << 6), (15 << 6), 0x1f, 0x1f, 0xff, 0xff },
        {         -64,  -64, 0, 0, ( 0 << 6), (15 << 6), 0, 0x1f, 0xff, 0xff    },
        {        -128,  -64, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff 	},
        {         -64,  -64, 0, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff	},
        {         -64, -128, 0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff	},
        {        -128, -128, 0, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff	},
        {          64,  128, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff 	},
        {         128,  128, 0, 0, (15 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff    },
        {         128,   64, 0, 0, (15 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff },
        {          64,   64, 0, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff    },
        {          64,   64, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff 	},
        {         128,   64, 0, 0, (63 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff    },
        {         128,  -64, 0, 0, (63 << 6), (127 << 6), 0x1f, 0x1f, 0xff, 0xff},
        {          64,  -64, 0, 0, ( 0 << 6), (127 << 6), 0, 0x1f, 0xff, 0xff   }
};


static Vtx load_tlut_q2[] =  {
        {        -128,   64, 0, 0, ( 0 << 5), ( 0 << 5), 0, 0, 0xff, 0xff 	},
        {         -64,   64, 0, 0, (31 << 6), ( 0 << 5), 0x1f, 0, 0xff, 0xff	},
        {         -64,    0, 0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff	},
        {        -128,    0, 0, 0, ( 0 << 5), (31 << 6), 0, 0x1f, 0xff, 0xff	}
};


Gfx rdptex_load_tlut_dl[] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSPVertex(&load_tlut_q1, 16, 0),

    gsDPLoadTLUT(1, 256+(0*16), &(OneEntryTlut[0])),
    gsDPLoadSync(),

    gsDPLoadTLUT(16, 256+(1*16), &(Tlut0[0])),
    gsDPLoadSync(),

    gsDPLoadTLUT(16, 256+(12*16), &(Tlut1[0])),
    gsDPLoadSync(),

    gsDPLoadTextureBlock_4b(CItest0, G_IM_FMT_CI, 16, 16, 1,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 4, 4, G_TX_NOLOD, G_TX_NOLOD),



    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),

    gsDPLoadTextureBlock_4b(CI4circle, G_IM_FMT_CI, 32, 32, 12,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         5, 5, G_TX_NOLOD, G_TX_NOLOD),

    gsSP1Triangle(4, 5, 6, 0),
    gsSP1Triangle(4, 6, 7, 0),

    /*
     *  try TLUT loads in 2-cycle mode
     */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_PASS2),

    gsDPLoadTLUT(48, 256+(7*16), &(Tlut2[0])),
    gsDPPipeSync(),

    /* texture indices offset to palette 7 */
    gsDPLoadTextureBlock(CI8circle, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         4, 5, G_TX_NOLOD, G_TX_NOLOD),

    gsSP1Triangle(8, 9, 10, 0),
    gsSP1Triangle(8, 10, 11, 0),

    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_IA16),
    gsDPLoadTLUT(256, 256, &(Tlut3[0])),
    gsDPPipeSync(),

    gsDPLoadTextureTile(IA16Noise, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 64, 
			 0, 0, 31, 63, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         5, 6, G_TX_NOLOD, G_TX_NOLOD),

    gsSP1Triangle(12, 13, 14, 0),
    gsSP1Triangle(12, 14, 15, 0),


    /*
     *  Load a 32x32x32 texture (fills Tmem)
     */
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),

    gsDPLoadTextureBlock(RGBA32eye, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0,
                         G_TX_NOMIRROR, G_TX_NOMIRROR,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),

    gsSPVertex(&load_tlut_q2, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),

    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /*done; turn texture off*/

    gsSPEndDisplayList(),
};

/*
 * Test 41, Frame 41:
 *
 * Generate big DP DL with lots of random variability. do the major rendering
 * modes and so on for the nightly iorand, cosim regression run.
 *
 * Thu Dec 15 21:35:39 PST 1994
 *
 */

/*
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
static Vtx box0_vtx[8] = {
{  -50, -50,   0, 0, 0, 0,   0,   0,   0, 128 },
{  -50, -50, 100, 0, 0, 0, 255,   0,   0, 128 },
{  -50,  50, 100, 0, 0, 0,   0, 254,   0, 128 },
{  -50,  50,   0, 0, 0, 0, 255, 254,   0, 128 },
{   50, -50,   0, 0, 0, 0,   0,   0, 252, 128 },
{   50, -50, 100, 0, 0, 0, 255,   0, 252, 128 },
{   50,  50, 100, 0, 0, 0,   0, 254, 252, 128 },
{   50,  50,   0, 0, 0, 0, 255, 254, 252, 128 }};

Gfx rdptex_box_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2),

    /* Box display list */
    gsSPVertex(&box0_vtx, 8, 0),
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

Gfx rdptex_box1_dl[] = {
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

Gfx rdptex_cone_dl[] = {
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

Gfx rdptex_icosa_dl[] = {
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
                         3, 2, G_TX_NOLOD, G_TX_NOLOD),

    gsSP1Triangle(2, 4, 5, 0),
    gsSP1Triangle(2, 0, 4, 0),
    gsSP1Triangle(4, 3, 5, 0),
    gsSP1Triangle(0, 3, 4, 0),
    
    gsSPTexture(16, 2, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};



#include "torus_vtx.h"



Gfx rdptex_torus_dl[] = {
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

Gfx rdptex_ground_dl[] = {
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
Gfx rdptex_tree0_dl[] = {
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
    gsDPLoadTextureBlock_4b(rdptex_IA4tree2, G_IM_FMT_CI, 32, 64, 0,
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
Gfx rdptex_tree1_dl[] = {
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
    gsDPLoadTextureBlock_4b(rdptex_IA4tree2, G_IM_FMT_CI, 32, 64, 0,
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
Gfx rdptex_tree2_dl[] = {
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
    gsDPLoadTextureBlock_4b(rdptex_IA4tree2, G_IM_FMT_IA, 32, 64, 0,
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
Gfx rdptex_tree3_dl[] = {
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
    gsDPLoadTextureBlock_4b(rdptex_IA4tree2, G_IM_FMT_IA, 32, 64, 0,
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

Vp iorand_cosim_regression_viewport_ur = {	/* upper right */
        SCREEN_WD, SCREEN_HT, G_MAXZ, 0,	/* scale */
        SCREEN_WD*3, SCREEN_HT*1, 0, 0,		/* translate */
};

Vp iorand_cosim_regression_viewport_ll = {	/* lower left */
        SCREEN_WD, SCREEN_HT, G_MAXZ, 0,	/* scale */
        SCREEN_WD*1, SCREEN_HT*3, 0, 0,		/* translate */
};

Vp iorand_cosim_regression_viewport_lr = {	/* lower left */
        SCREEN_WD, SCREEN_HT, G_MAXZ, 0,	/* scale */
        SCREEN_WD*3, SCREEN_HT*3, 0, 0,		/* translate */
};

Gfx rdptex_iorand_cosim_regression[MAX_STATIC_GFX_SIZE] = {

    /* 1 clock texture variety cases */

    gsSPViewport(&iorand_cosim_regression_viewport_ur),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPDisplayList(rdptex_texfmt_RGBA16),
    gsSPDisplayList(rdptex_texfmt_IA8),
    gsSPDisplayList(rdptex_texfmt_IA4),
    gsSPDisplayList(rdptex_texfmt_IA16),
    gsSPDisplayList(rdptex_loadtile_RGBA16),
    gsSPDisplayList(rdptex_loadtile_nonalign_RGBA16),
    gsSPDisplayList(rdptex_loadtile_8b),
    gsSPDisplayList(rdptex_loadtile_4b),
    gsSPDisplayList(rdptex_texfmt_I8),
    gsSPDisplayList(rdptex_texfmt_I4),

    /* 2 clock texture variety cases */

    gsSPViewport(&iorand_cosim_regression_viewport_ll),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPDisplayList(rdptex_texfmt_IA8_2clock),
    gsSPDisplayList(rdptex_loadtile_RGBA16_2clock),
    gsSPDisplayList(rdptex_loadtile_4b_2clock),

    gsSPEndDisplayList(),
};
/* end of case 41 */


/*
 * Test 42, Frame 42
 * 
 * Texture sharpen test
 *
 * Sun Dec 18 18:08:07 PST 1994
 * -Ashok
 *
 */

static Vtx qMM[8] =  {
        {        -128,  0, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff
},
        {         0,  0, 0, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff
},
        {         0, -128, 0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff
},
        {        -128, -128, 0, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff
},
        {        -20,  108, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff
},
        {         108,  108, 0, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff
},
        {         108, -20, 0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff
},
        {        -20, -20, 0, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff
},
};

Gfx rdptex_sharpenRGBA16[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),
    /*
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
    gsDPSetFillColor(GPACK_RGBA5551(0,0,0,1) << 16 | GPACK_RGBA5551(0,0,0,1)),
    gsDPSetColorImage(5, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,  cfb_16_a),
    */

    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 5, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetPrimColor(0,0,0,0,0,0),
    gsDPSetCombineMode(G_CC_TRILERP, G_CC_DECALRGB2),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_LOD),
    gsDPSetTextureFilter(G_TF_BILERP),

    gsSPVertex(&qMM, 8, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsSP1Triangle(0, 2, 3, 0),
    gsDPPipeSync(),

    gsDPSetTextureDetail(G_TD_SHARPEN),
    gsSP1Triangle(4, 5, 6, 0),
    gsDPPipeSync(),
    gsSP1Triangle(4, 6, 7, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};


/*
 * Test 43, Frame 43:
 *
 * Copy mode with Alpha compare
 * Sun Dec 18 20:50:06 PST 1994
 * -Ashok
 */

#include "RGBA16tree.h"

static TexRect trect6[] = {
    gsDPTextureRectangle(87<<2, 88<<2, 150<<2, 151<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10)
};

static TexRect trect7[] = {
    gsDPTextureRectangle(170<<2, 88<<2, 233<<2, 151<<2, G_TX_RENDERTILE, 0, 0, 2<<10, 0x7f << 9)
};

Gfx rdptex_copyAlphaRGBA16[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_COPY),
    gsDPSetBlendColor(0x0,0x0,0x0,0x0), /* set alpha ref value */
    gsDPSetEnvColor(0x0,0x0,0x0,0x0),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),

    gsDPLoadTextureBlock(rdptex_RGBA16grid, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
                         5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTexturePersp(G_TP_NONE),
    gsSPTextureRectangle(87<<2, 88<<2, 150<<2, 151<<2, G_TX_RENDERTILE, 0, 0, 4<<10, 1<<10),

    gsDPLoadTextureBlock(RGBA16tree, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(170<<2, 88<<2, 233<<2, 151<<2, G_TX_RENDERTILE, 0, 0, 2<<10, 0x7f << 9),


    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPEndDisplayList(),

};

/*
 * Test 44, Frame 44
 *
 * 2 cycle trilerp texture + detail test
 * (different mask and shift from Test 39)
 * Wed Dec 21 10:06:09 PST 1994
 * -Ashok
 */

#include "I8crater16MM.h"

#define gsDPLoadTextureBlockDet16(timg, fmt, siz, width, height, length,	\
                pal, cms, cmt, masks, maskt, shifts, shiftt)            \
									\
        gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 1, I8crater16MM),	\
        gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 0, 0, G_TX_LOADTILE,   	\
			0 , G_TX_WRAP | G_TX_NOMIRROR, 4 ,G_TX_NOLOD, 	\
			G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),     	\
        gsDPLoadSync(),                                                 \
        gsDPLoadBlock(G_TX_LOADTILE, 0, 0, (256-1), 0x0),      		\
	gsDPTileSync(),							\
        gsDPSetTextureImage(fmt, siz, 1, timg),                         \
        gsDPSetTile(fmt, siz, 0, 32, G_TX_LOADTILE, 0 , cmt, maskt,	\
                shiftt, cms, masks, shifts),                            \
        gsDPLoadSync(),                                                 \
        gsDPLoadBlock(G_TX_LOADTILE, 0, 0, length-1,0x0),      		\
        gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 2, 0, 			\
                0, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0xf, 		\
		G_TX_WRAP | G_TX_NOMIRROR, 4,                       	\
		0xf),							\
        gsDPSetTileSize(0, 0, 0,                                        \
                (16-1) << G_TEXTURE_IMAGE_FRAC,                        	\
                (16-1) << G_TEXTURE_IMAGE_FRAC),                       	\
        gsDPSetTile(fmt, siz, ((((width) * siz##_BYTES)+7)>>3), 32,	\
                1, pal, cmt, maskt, 0, cms, masks,   			\
                0),        			                      	\
        gsDPSetTileSize(1, 0, 0,                          		\
                (32-1) << G_TEXTURE_IMAGE_FRAC,                      	\
                (32-1) << G_TEXTURE_IMAGE_FRAC),			\
        gsDPSetTile(fmt, siz, ((((16) * siz##_BYTES)+7)>>3), 288,      	\
                2, pal, cmt, (maskt - 1), 1, cms, (masks -1), 		\
		1),							\
        gsDPSetTileSize(2, 0, 0,                          		\
                (16-1) << G_TEXTURE_IMAGE_FRAC,                      	\
                (16-1) << G_TEXTURE_IMAGE_FRAC),			\
        gsDPSetTile(fmt, siz, ((((8) * siz##_BYTES)+7)>>3), 352,      	\
                3, pal, cmt, (maskt-2), 2, cms, (masks-2),   		\
                2),                                                	\
        gsDPSetTileSize(3, 0, 0,                          		\
                (8-1) << G_TEXTURE_IMAGE_FRAC,                      	\
                (8-1) << G_TEXTURE_IMAGE_FRAC),				\
        gsDPSetTile(fmt, siz, ((((4) * siz##_BYTES)+7)>>3), 368,      	\
                4, pal, cmt, (maskt-3), 3, cms, (masks-3),   		\
                3),                                                	\
        gsDPSetTileSize(4, 0, 0,                          		\
                (4-1) << G_TEXTURE_IMAGE_FRAC,                      	\
                (4-1) << G_TEXTURE_IMAGE_FRAC),				\
        gsDPSetTile(fmt, siz, ((((2) * siz##_BYTES)+7)>>3), 372,      	\
                5, pal, cmt, (maskt-4), 4, cms, (masks-4),   		\
                4),                                                	\
        gsDPSetTileSize(5, 0, 0,                          		\
                (2-1) << G_TEXTURE_IMAGE_FRAC,                      	\
                (2-1) << G_TEXTURE_IMAGE_FRAC),				\
        gsDPSetTile(fmt, siz, ((((1) * siz##_BYTES)+7)>>3), 374,      	\
                6, pal, cmt, (maskt-5), 5, cms, (masks-5),   		\
                5),                                                	\
        gsDPSetTileSize(6, 0, 0,                          		\
                (1-1) << G_TEXTURE_IMAGE_FRAC,                      	\
                (1-1) << G_TEXTURE_IMAGE_FRAC)

Gfx rdptex_detail16RGBA16MM[512] = {

    gsDPPipeSync(),
   gsDPLoadTextureBlockDet16(rdptex_RGBA16gridMM,G_IM_FMT_RGBA,G_IM_SIZ_16b,32,32,1372,
			0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			5,5, G_TX_NOLOD,G_TX_NOLOD),

    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_TRILERP, G_CC_DECALRGB2),  
    gsSPTexture(0x8000, 0x8000, 5, 0x0, G_ON),
    gsDPSetPrimColor(0,0,0,0,0,0),
    gsDPSetRenderMode(G_RM_PASS,G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLOD(G_TL_LOD),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureDetail(G_TD_DETAIL),

#include "runway_cmds.h"

    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};


/*
 *  Tests 50-58
 *
 *  Test clearing Z/Color buffer, check hidden bits.  Mostly for testing
 *  memspan in iosim environment.
 *
 *  Just because a certain size color image is set during the fill doesn't
 *  mean that you will use the image with that same size.  For example, we
 *  (should) be able to fill the z buffer with it's size set to 8b and then
 *  later use it as the required 16b size.
 *
 *  Designed so that test can ping pong frame buffer and run a different display
 *  list.
 */

/*
 *  Test 50
 */
Gfx rdptex_frame_clear16b[] = {
  gsDPPipeSync(),
  gsDPSetCycleType(G_CYC_FILL),
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),

  /* fill 16b RGBA color image with 0x55 pattern */
  gsDPSetFillColor(0xaaaa5555),
  gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* fill 16b RGBA color image with 0xaa pattern */
  gsDPSetFillColor(0x5555aaaa),
  gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* fill 16b z buffer with 0x55 pattern */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, zbuffer), 
  gsDPSetFillColor(0xaaaa5555),
  gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* fill 16b z buffer with 0xaa pattern */
  gsDPSetFillColor(0x5555aaaa),
  gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* reset color image pointer before dumping image */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
  gsSPEndDisplayList(),
};


/*
 *   Test 51
 */
Gfx rdptex_frame1_clear8b[] = {
  gsDPPipeSync(),
  gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD * 2, SCREEN_HT),
  gsDPSetCycleType(G_CYC_FILL),
  gsDPSetColorImage(G_IM_FMT_CI, G_IM_SIZ_8b, SCREEN_WD * 2, cfb_16_a),

  /* fill 8b RGBA color image with 0x55 pattern */
  gsDPSetFillColor(0xa5a55a5a),
  gsDPFillRectangle(0, 0, (SCREEN_WD * 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* fill 8b z buffer with 0xaa pattern */
  gsDPSetFillColor(0xa5a55a5a),
  gsDPFillRectangle(0, 0, (SCREEN_WD * 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* reset color image pointer before dumping image */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
  gsDPPipeSync(),
  gsSPEndDisplayList(),
};

/*
 *   Test 62
 */
Gfx rdptex_frame2_clear8b[] = {
  gsDPPipeSync(),
  gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD * 2, SCREEN_HT),
  gsDPSetCycleType(G_CYC_FILL),
  gsDPSetColorImage(G_IM_FMT_CI, G_IM_SIZ_8b, SCREEN_WD * 2, cfb_16_a),

  /* fill 8b RGBA color image with 0xaa pattern */
  gsDPSetFillColor(0x5a5aa5a5),
  gsDPFillRectangle(0, 0, (SCREEN_WD * 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* fill 8b z buffer with 0x55 pattern */
  gsDPSetColorImage(G_IM_FMT_CI, G_IM_SIZ_8b, SCREEN_WD * 2, zbuffer), 
  gsDPSetFillColor(0x5a5aa5a5),
  gsDPFillRectangle(0, 0, (SCREEN_WD * 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* reset color image pointer before dumping image */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
  gsDPPipeSync(),
  gsSPEndDisplayList(),
};


/*
 *  Test 52 320X240 32-bit fill mode
 */
Gfx rdptex_frame_clear32b[] = {
  /* change color image size to 32b and repeat */ 
  gsDPPipeSync(),
  gsDPSetCycleType(G_CYC_FILL),

  /* fill 32b RGBA color image with pattern */
  gsDPSetFillColor(0xaabbccdd),
  gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
  gsDPPipeSync(),

  gsSPEndDisplayList(),
};


/*
 *  Test 53, Same clear cases but with interlacing enabled
 */
Gfx rdptex_frame1_clear16b_ilo[] = {
  gsDPPipeSync(),
  gsDPSetScissor(G_SC_ODD_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT),
  gsDPSetCycleType(G_CYC_FILL),
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),

  /* fill 16b RGBA color image with 0x55 pattern */
  gsDPSetFillColor(0x55555555),
  gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT),
  gsDPPipeSync(),

  /* fill 16b z buffer with 0xaa pattern */
  gsDPSetFillColor(0xaaaaaaaa),
  gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* reset color image pointer before dumping image */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
  gsSPEndDisplayList(),
};

/*
 *  Test 63,
 */
Gfx rdptex_frame2_clear16b_ilo[] = {
  gsDPPipeSync(),
  gsDPSetScissor(G_SC_ODD_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT),
  gsDPSetCycleType(G_CYC_FILL),
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),

  /* fill 16b RGBA color image with 0xaa pattern */
  gsDPSetFillColor(0xaaaaaaaa),
  gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT),
  gsDPPipeSync(),

  /* fill 16b z buffer with 0x55 pattern */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, zbuffer), 
  gsDPSetFillColor(0x55555555),
  gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* reset color image pointer before dumping image */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
  gsSPEndDisplayList(),
};

/*
 *  Test 54
 */
Gfx rdptex_frame1_clear16b_ile[] = {
  gsDPPipeSync(),
  gsDPSetScissor(G_SC_EVEN_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT-1),
  gsDPSetCycleType(G_CYC_FILL),
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),

  /* fill 16b RGBA color image with 0x55 pattern */
  gsDPSetFillColor(0x55555555),
  gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT),
  gsDPPipeSync(),

  /* fill 16b z buffer with 0xaa pattern */
  gsDPSetFillColor(0xaaaaaaaa),
  gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* reset color image pointer before dumping image */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
  gsSPEndDisplayList(),
};

/*
 *  Test 64
 */
Gfx rdptex_frame2_clear16b_ile[] = {
  gsDPPipeSync(),
  gsDPSetScissor(G_SC_EVEN_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT-1),
  gsDPSetCycleType(G_CYC_FILL),
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),

  /* fill 16b RGBA color image with 0xaa pattern */
  gsDPSetFillColor(0xaaaaaaaa),
  gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT),
  gsDPPipeSync(),

  /* fill 16b z buffer with 0x55 pattern */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, zbuffer), 
  gsDPSetFillColor(0x55555555),
  gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* reset color image pointer before dumping image */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
  gsSPEndDisplayList(),

};

/*
 *  Test 55
 */ 
Gfx rdptex_frame1_clear8b_ilo[] = {
  gsDPPipeSync(),
  gsDPSetScissor(G_SC_ODD_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT-1),
  gsDPSetCycleType(G_CYC_FILL),
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_8b, SCREEN_WD * 2, cfb_16_a),

  /* fill 8b RGBA color image with 0x55 pattern */
  gsDPSetFillColor(0x55555555),
  gsDPFillRectangle(0, 0, (SCREEN_WD * 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* fill 8b z buffer with 0xaa pattern */
  gsDPSetFillColor(0xaaaaaaaa),
  gsDPFillRectangle(0, 0, (SCREEN_WD * 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* reset color image pointer before dumping image */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
  gsSPEndDisplayList(),
};

/*
 *  Test 65
 */ 
Gfx rdptex_frame2_clear8b_ilo[] = {
  gsDPPipeSync(),
  gsDPSetScissor(G_SC_ODD_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT-1),
  gsDPSetCycleType(G_CYC_FILL),
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_8b, SCREEN_WD * 2, cfb_16_a),

  /* fill 8b RGBA color image with 0xaa pattern */
  gsDPSetFillColor(0xaaaaaaaa),
  gsDPFillRectangle(0, 0, (SCREEN_WD * 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* fill 8b z buffer with 0x55 pattern */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_8b, SCREEN_WD * 2, zbuffer), 
  gsDPSetFillColor(0x55555555),
  gsDPFillRectangle(0, 0, (SCREEN_WD * 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* reset color image pointer before dumping image */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
  gsSPEndDisplayList(),
};
/*
 *  Test 56
 */ 
Gfx rdptex_frame1_clear8b_ile[] = {
  gsDPPipeSync(),
  gsDPSetScissor(G_SC_EVEN_INTERLACE, 0, 0, (SCREEN_WD * 2)-1, SCREEN_HT-1),
  gsDPSetCycleType(G_CYC_FILL),
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_8b, SCREEN_WD * 2, cfb_16_a),

  /* fill 8b RGBA color image with 0x55 pattern */
  gsDPSetFillColor(0x55555555),
  gsDPFillRectangle(0, 0, (SCREEN_WD * 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* fill 8b z buffer with 0xaa pattern */
  gsDPSetFillColor(0xaaaaaaaa),
  gsDPFillRectangle(0, 0, (SCREEN_WD * 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* reset color image pointer before dumping image */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
  gsSPEndDisplayList(),
};

/*
 *  Test 66
 */ 
Gfx rdptex_frame2_clear8b_ile[] = {
  gsDPPipeSync(),
  gsDPSetScissor(G_SC_EVEN_INTERLACE, 0, 0, (SCREEN_WD * 2)-1, SCREEN_HT-1),
  gsDPSetCycleType(G_CYC_FILL),
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_8b, SCREEN_WD * 2, cfb_16_a),

  /* fill 8b RGBA color image with 0xaa pattern */
  gsDPSetFillColor(0xaaaaaaaa),
  gsDPFillRectangle(0, 0, (SCREEN_WD * 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* fill 8b z buffer with 0x55 pattern */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_8b, SCREEN_WD * 2, zbuffer), 
  gsDPSetFillColor(0x55555555),
  gsDPFillRectangle(0, 0, (SCREEN_WD * 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* reset color image pointer before dumping image */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
  gsSPEndDisplayList(),
};

/*
 *  Test 57
 */ 
Gfx rdptex_frame1_clear32b_ilo[] = {
  gsDPSetScissor(G_SC_ODD_INTERLACE, 0, 0, (SCREEN_WD / 2)-1, SCREEN_HT-1),
  /* change color image size to 32b and repeat */ 
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD / 2, cfb_16_a),

  /* fill 32b RGBA color image with 0x55 pattern */
  gsDPSetFillColor(0x55555555),
  gsDPFillRectangle(0, 0, (SCREEN_WD / 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* fill 32b z buffer with 0xaa pattern */
  gsDPSetFillColor(0xaaaaaaaa),
  gsDPFillRectangle(0, 0, ((SCREEN_WD / 2) * 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* reset color image pointer before dumping image */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
  gsSPEndDisplayList(),
};

/*
 *  Test 67
 */ 
Gfx rdptex_frame2_clear32b_ilo[] = {
  gsDPSetScissor(G_SC_ODD_INTERLACE, 0, 0, (SCREEN_WD / 2)-1, SCREEN_HT-1),
  /* change color image size to 32b and repeat */ 
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD / 2, cfb_16_a),

  /* fill 32b RGBA color image with 0xaa pattern */
  gsDPSetFillColor(0xaaaaaaaa),
  gsDPFillRectangle(0, 0, (SCREEN_WD / 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* fill 32b z buffer with 0x55 pattern */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD / 2, zbuffer), 
  gsDPSetFillColor(0x55555555),
  gsDPFillRectangle(0, 0, (SCREEN_WD / 2)-1, SCREEN_HT-1),
  gsDPPipeSync(),

  /* reset color image pointer before dumping image */
  gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
  gsSPEndDisplayList(),
};
/*
 *  Test 58 320X240, 32-bit, Even Interlace
 */ 
Gfx rdptex_frame_clear32b_ile[] = {

  /* change color image size to 32b and repeat */
  gsDPPipeSync(),
  gsDPSetCycleType(G_CYC_FILL),
  gsDPSetScissor(G_SC_EVEN_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),

  /* fill 32b RGBA color image with pattern */
  gsDPSetFillColor(0xaabbccdd),
  gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
  gsDPPipeSync(),

  gsSPEndDisplayList(),
};


/*
 * Test 60, Frame 60:
 *
 * Simple square with a YUV texture using loadtile
 *
 * rmoore
 */

/*
 *  YUV-RGB Conversion coefficients
 *
 *  Also tests wrap *and* clamp in T
 */

#include "YUVbars.h"

#define MY_K0	(175 & 0x1ff)
#define MY_K1	(-43 & 0x1ff)
#define MY_K2	(-89 & 0x1ff)
#define MY_K3	(222 & 0x1ff)
#define MY_K4	(114 & 0x1ff)
#define MY_K5	(42 & 0x1ff)

static Vtx yuvtile_q1[8] =  {
        {  -50, 50, 0, 0, ( 0 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  -25, 50, 0, 0, (27 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff	},
        {  -25, 0, 0, 0, (27 << 6), (27 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  -50, 0, 0, 0, ( 0 << 6), (27 << 6), 0xff, 0x00, 0x00, 0xff	},
        {  -25, 50, 0, 0, ( 0 << 6), ( 0 << 6), 0x00, 0xff, 0x00, 0xff	},
        {    0, 50, 0, 0, (27 << 6), ( 0 << 6), 0xff, 0x00, 0x00, 0xff	},
        {    0, 0, 0, 0, (27 << 6), (27 << 6), 0x00, 0xff, 0x00, 0xff	},
        {  -25, 0, 0, 0, ( 0 << 6), (27 << 6), 0xff, 0x00, 0x00, 0xff	},
};


Gfx rdptex_yuvbars_dl[] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_CONV),
    gsDPSetConvert(MY_K0, MY_K1, MY_K2, MY_K3, MY_K4, MY_K5),
    gsDPSetCombineMode(G_CC_1CYUV2RGB, G_CC_1CYUV2RGB),
    gsDPLoadTextureTile(rdptex_YUVbars, G_IM_FMT_YUV, G_IM_SIZ_16b, 2, 8,
			 0, 0, 0, 15, 0,
			 G_TX_NOMIRROR, G_TX_WRAP | G_TX_CLAMP,
			 G_TX_NOMASK, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&yuvtile_q1, 8, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILTCONV),
    gsDPSetCombineMode(G_CC_YUV2RGB, G_CC_PASS2),
    gsSP1Triangle(4, 5, 6, 0),
    gsSP1Triangle(4, 6, 7, 0),

    gsSPEndDisplayList(),
};

