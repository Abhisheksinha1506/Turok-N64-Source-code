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
 * File:	init.c
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:	Declarations & definitions to be placed in the static segment.
 *
 * This file holds tiny display list segments that are 'static' data.
 *
 */

#include <ultra64.h>
#include "gng.h"
#include "dldriver.h"

/*
 * Remember, viewport structures have 2 bits of fraction in them.
 */
static Vp vp = {
	SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* scale */
	SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* translate */
};

/*
 * 640x480 viewport 
 */
static Vp med_viewport_d = {
        SCREEN_WD*4, SCREEN_HT*4, G_MAXZ/2, 0,  /* scale */
        SCREEN_WD*4, SCREEN_HT*4, G_MAXZ/2, 0,  /* translate */
};

Vp regression_viewport_d = {
	SCREEN_WD/2, SCREEN_HT/2, G_MAXZ/2, 0,	/* scale */
	SCREEN_WD/2, SCREEN_HT/2, G_MAXZ/2, 0,	/* translate */
};

Vp bigscreen_viewport_d = {
	1024*2, 512*2, G_MAXZ/2, 0,	/* scale */
	1024*2, 512*2, G_MAXZ/2, 0,	/* translate */
};

Gfx rspinit_dl[] = {
    gsDPPipeSync(),
    gsSPViewport(&vp),
    gsSPClearGeometryMode(0xffffffff),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx rdpinit_dl[] = {

    gsDPPipeSync(),
    gsDPSetEnvColor(0,0,0,0),
    gsDPSetPrimColor(0,0,0,0,0,0),
    gsDPSetBlendColor(0,0,0,0),
    gsDPSetFogColor(0,0,0,0),
    gsDPSetFillColor(0),
    gsDPSetPrimDepth(0,0),
    gsDPSetConvert(0,0,0,0,0,0),
    gsDPSetKeyR(0,0,0),
    gsDPSetKeyGB(0,0,0,0,0,0),

    /* set combine mode */
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),

    /* initialize the scissor box */
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),

    /* initialize all the texture tile descriptors to zero */
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),

    gsDPSetTileSize(0, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPSetTileSize(1, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPSetTileSize(2, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPSetTileSize(3, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPSetTileSize(4, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPSetTileSize(5, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPSetTileSize(6, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),
    gsDPSetTileSize(7, 0, 0, (1 - 1) << G_TEXTURE_IMAGE_FRAC, (1 - 1) <<
		G_TEXTURE_IMAGE_FRAC),


    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetBlendMask(0xff),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetDepthImage(zbuffer),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

/*
 * Clear the z buffer independently from the color frame buffer.
 */
Gfx clear_16fb_z[] = {
    /*
     * Clear zbuffer.
     */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, zbuffer),
    gsDPSetFillColor(GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0)),
    gsDPPipeSync(),
    gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

/*
 * Always clears the first frame buffer.  This is okay, since we only want to
 * render to the first frame buffer.
 */
Gfx clear_16fb_aqua[] = {
    /*
     * clear color, cvg = FULL or 1
     */
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, 
	OS_K0_TO_PHYSICAL(cfb_16_a) ),
    gsDPSetFillColor(GPACK_RGBA5551(0,200,200,1) << 16 | GPACK_RGBA5551(0,200,200,1)), 
    gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
    gsDPNoOp(), 
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};

Gfx clear_16fb_black[] = {
    /*
     * clear color, cvg = FULL or 1
     */
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, 
	OS_K0_TO_PHYSICAL(cfb_16_a) ),
    gsDPSetFillColor(GPACK_RGBA5551(0,0,0,1) << 16 | GPACK_RGBA5551(0,0,0,1)), 
    gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
    gsDPNoOp(), 
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};

Gfx clear_32fb_z[] = {
    /*
     * Clear zbuffer first
     */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, zbuffer),
    gsDPSetFillColor(GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0)),
    gsDPPipeSync(),
    gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx clear_32fb_aqua[] = {
    /*
     * clear color, cvg = FULL or 1
     */
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD,
	    OS_K0_TO_PHYSICAL(cfb_16_a) ),
    gsDPSetFillColor((0<<24) | (200<<16) | (200 << 8) | 0xff),  
    gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};

Gfx clear_32fb_black[] = {
    /*
     * clear color, cvg = FULL or 1
     */
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD,
	    OS_K0_TO_PHYSICAL(cfb_16_a) ),
    gsDPSetFillColor((0<<24) | (0<<16) | (0 << 8) | 0xff),  
    gsDPFillRectangle(0, 0, SCREEN_WD-1, SCREEN_HT-1),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};

/*
 * Allow only a 32-bit type for a  1024  wide framebuffer
 */

Gfx clear_1024fb_z[] = {
    /*
     * Clear zbuffer.
     */
    gsDPPipeSync(),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 1023, 255),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1024, zbuffer),
    gsDPSetFillColor(GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0)),
    gsDPPipeSync(),
    gsDPFillRectangle(0, 0, 1023, 255),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

/*
 * Always clears the first frame buffer.  This is okay, since we only want to
 * render to the first frame buffer.
 */
Gfx clear_1024fb_aqua[] = {
    /*
     * clear color, cvg = FULL or 1
     */
    /* Note: scissoring doesnt include endpoints (i.e. 1023x511 fb) 
     * and the max size is 1023x1023 
     */
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 1023, 511),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_32b, 1024,
            OS_K0_TO_PHYSICAL(L26R)),
    gsDPSetFillColor((0<<24) | (200<<16) | (200 << 8) | 0xff),
    /* clear a 1024 x 512 rectangle scissored thru a 1023x511 window 
     * (FillRect does include endpoints)
     */
    gsDPFillRectangle(0, 0, 1023, 511),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};

Gfx clear_1024fb_black[] = {
    /*
     * clear color, cvg = FULL or 1
     */
    /* Note: scissoring doesnt include endpoints (i.e. 1023x511 fb) 
     * and the max size is 1023x1023 
     */
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 1023, 511),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_32b, 1024,
            OS_K0_TO_PHYSICAL(L26R)),
    gsDPSetFillColor((0<<24) | (0<<16) | (0 << 8) | 0xff),
    /* clear a 1024 x 512 rectangle scissored thru a 1023x511 window 
     * (FillRect does include endpoints)
     */
    gsDPFillRectangle(0, 0, 1023, 511),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};

Gfx clear_640fb_aqua[] = {
    /*
     * clear color, cvg = FULL or 1
     */
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 640, 480),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_16b, 640,
            OS_K0_TO_PHYSICAL(cfb_16_a)),
    gsDPSetFillColor((0<<24) | (200<<16) | (200 << 8) | 0xff),
    gsDPFillRectangle(0, 0, 639, 479),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};

Gfx clear_640fb_black[] = {
    /*
     * clear color, cvg = FULL or 1
     */
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 640, 480),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage( G_IM_FMT_RGBA, G_IM_SIZ_16b, 640,
            OS_K0_TO_PHYSICAL(cfb_16_a)),
    gsDPSetFillColor((0<<24) | (0<<16) | (0 << 8) | 0xff),
    gsDPFillRectangle(0, 0, 639, 479),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};

/*
 * smaller viewport for optional regression tests.
 */
Gfx regression_viewport[MAX_STATIC_GFX_SIZE] = {
	gsSPViewport(&regression_viewport_d),
	gsSPEndDisplayList(),
};

/*
 * Big viewport & scissor for full extent ew tests
 */
Gfx bigscreen_viewport[MAX_STATIC_GFX_SIZE] = {
	/*
	 * Set the Scissor box to the maximum allowed by the HW.
	 */
	gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 1023, 511),
	gsSPViewport(&bigscreen_viewport_d),
	gsSPEndDisplayList(),
};

/*
 * 640x480 viewport & scissor for full extent ew tests
 */
Gfx med_viewport[MAX_STATIC_GFX_SIZE] = {
	/*
	 * Set the Scissor box to the maximum allowed by the HW.
	 */
	gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 640, 480),
	gsSPViewport(&med_viewport_d),
	gsSPEndDisplayList(),
};

/* 
 * clear the color frame buffer (to black) 
 */
Gfx clearcfb_dl[] = {
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, 
	OS_K0_TO_PHYSICAL(cfb_16_a) ),
    gsDPSetFillColor(GPACK_RGBA5551(0,0,0,1) << 16 | 
		     GPACK_RGBA5551(0,0,0,1)),
    gsDPFillRectangle(0, 0, SCREEN_WD-2, SCREEN_HT-2),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};
