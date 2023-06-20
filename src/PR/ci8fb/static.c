
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

#include <ultra64.h>
#include "fill.h"
#include "static.h"

/* Remember, viewport structures have 2 bits of fraction in them */
static Vp vp = 
{
  SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* scale */
  SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* translate */
};

/* initialize the RSP state: */
Gfx rspinit_dl[] = 
{
  gsSPViewport(&vp),
  gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH |
			G_FOG | G_LIGHTING | G_TEXTURE_GEN |
			G_TEXTURE_GEN_LINEAR | G_LOD | G_ZBUFFER),
  gsSPTexture(0, 0, 0, 0, G_OFF),
  gsSPEndDisplayList(),
};

/* initialize the RDP state: */
Gfx rdpinit_dl[] = 
{
  gsDPSetCycleType(G_CYC_1CYCLE),
  gsDPPipelineMode(G_PM_NPRIMITIVE),
  gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
  gsDPSetTextureLOD(G_TL_TILE),
  gsDPSetTextureLUT(G_TT_NONE),
  gsDPSetTextureDetail(G_TD_CLAMP),
  gsDPSetTexturePersp(G_TP_PERSP),
  gsDPSetTextureFilter(G_TF_BILERP),
  gsDPSetTextureConvert(G_TC_FILT),
  gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
  gsDPSetCombineKey(G_CK_NONE),
  gsDPSetAlphaCompare(G_AC_NONE),
  gsDPSetColorDither(G_CD_DISABLE),
  gsDPSetDepthImage(zbuffer),
  gsDPPipeSync(),
  gsSPEndDisplayList(),
};



#include "TlutCI8.h"

/*
 *  Define my own load macros to save a few instructions
 */

#define myDPSetTextureTile(fmt, siz, uls, ult, lrs, lrt, 	\
		cms, cmt, masks, maskt, shifts, shiftt) 			\
			\
	gsDPSetTile(fmt, siz, (((((lrs)-(uls)+1) * siz##_TILE_BYTES)+7)>>3), 0, \
        G_TX_LOADTILE, 0 , cmt, maskt, shiftt, cms, masks,  \
        shifts),											\
	gsDPSetTile(fmt, siz, (((((lrs)-(uls)+1) * siz##_LINE_BYTES)+7)>>3), 0, \
        G_TX_RENDERTILE, 0, cmt, maskt, shiftt, cms, masks,   \
        shifts)

#define myDPLoadTextureTile( uls, ult, lrs, lrt)	\
			\
    gsDPLoadSync(),                         		\
    gsDPLoadTile(   G_TX_LOADTILE,                  \
            (uls)<<G_TEXTURE_IMAGE_FRAC,            \
            (ult)<<G_TEXTURE_IMAGE_FRAC,            \
            (lrs)<<G_TEXTURE_IMAGE_FRAC,            \
            (lrt)<<G_TEXTURE_IMAGE_FRAC),			\
    gsDPSetTileSize(G_TX_RENDERTILE,                \
            (uls)<<G_TEXTURE_IMAGE_FRAC,            \
            (ult)<<G_TEXTURE_IMAGE_FRAC,            \
            (lrs)<<G_TEXTURE_IMAGE_FRAC,            \
            (lrt)<<G_TEXTURE_IMAGE_FRAC)



Gfx copy8b_dl[] = {

    /* init some rdp params */
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTexturePersp(G_TP_NONE),

    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, rsp_cfb),
    gsDPSetCycleType(G_CYC_COPY),

	gsDPLoadTLUT_pal256(CI8mandrilltlut),

    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b, SCREEN_WD, 
		&(rsp_cfb[SCREEN_OFF])),

	/*
 	 *  exact values for sl,tl,sh,th don't matter since chunk we are 
	 *	copying is always the same size.
	 */
	myDPSetTextureTile(G_IM_FMT_CI, G_IM_SIZ_8b, 0, 0, 319, 5,
		G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, 
		G_TX_NOLOD, G_TX_NOLOD),

	/*
 	 *  Copy 40 blocks of height 6
	 */
    myDPLoadTextureTile( 4, 0, 319, 5),
    gsSPTextureRectangle(0, 0, 1276,
            20, G_TX_RENDERTILE,
            0, 0, 4096, 1024),
    myDPLoadTextureTile( 4, 6, 319, 11),
    gsSPTextureRectangle(0, 24, 1276,
            44, G_TX_RENDERTILE,
            0, 192, 4096, 1024),
    myDPLoadTextureTile( 4, 12, 319, 17),
    gsSPTextureRectangle(0, 48, 1276,
            68, G_TX_RENDERTILE,
            0, 384, 4096, 1024),
    myDPLoadTextureTile( 4, 18, 319, 23),
    gsSPTextureRectangle(0, 72, 1276,
            92, G_TX_RENDERTILE,
            0, 576, 4096, 1024),
    myDPLoadTextureTile( 4, 24, 319, 29),
    gsSPTextureRectangle(0, 96, 1276,
            116, G_TX_RENDERTILE,
            0, 768, 4096, 1024),
    myDPLoadTextureTile( 4, 30, 319, 35),
    gsSPTextureRectangle(0, 120, 1276,
            140, G_TX_RENDERTILE,
            0, 960, 4096, 1024),
    myDPLoadTextureTile( 4, 36, 319, 41),
    gsSPTextureRectangle(0, 144, 1276,
            164, G_TX_RENDERTILE,
            0, 1152, 4096, 1024),
    myDPLoadTextureTile( 4, 42, 319, 47),
    gsSPTextureRectangle(0, 168, 1276,
            188, G_TX_RENDERTILE,
            0, 1344, 4096, 1024),
    myDPLoadTextureTile( 4, 48, 319, 53),
    gsSPTextureRectangle(0, 192, 1276,
            212, G_TX_RENDERTILE,
            0, 1536, 4096, 1024),
    myDPLoadTextureTile( 4, 54, 319, 59),
    gsSPTextureRectangle(0, 216, 1276,
            236, G_TX_RENDERTILE,
            0, 1728, 4096, 1024),
    myDPLoadTextureTile( 4, 60, 319, 65),
    gsSPTextureRectangle(0, 240, 1276,
            260, G_TX_RENDERTILE,
            0, 1920, 4096, 1024),
    myDPLoadTextureTile( 4, 66, 319, 71),
    gsSPTextureRectangle(0, 264, 1276,
            284, G_TX_RENDERTILE,
            0, 2112, 4096, 1024),
    myDPLoadTextureTile( 4, 72, 319, 77),
    gsSPTextureRectangle(0, 288, 1276,
            308, G_TX_RENDERTILE,
            0, 2304, 4096, 1024),
    myDPLoadTextureTile( 4, 78, 319, 83),
    gsSPTextureRectangle(0, 312, 1276,
            332, G_TX_RENDERTILE,
            0, 2496, 4096, 1024),
    myDPLoadTextureTile( 4, 84, 319, 89),
    gsSPTextureRectangle(0, 336, 1276,
            356, G_TX_RENDERTILE,
            0, 2688, 4096, 1024),
    myDPLoadTextureTile( 4, 90, 319, 95),
    gsSPTextureRectangle(0, 360, 1276,
            380, G_TX_RENDERTILE,
            0, 2880, 4096, 1024),
    myDPLoadTextureTile( 4, 96, 319, 101),
    gsSPTextureRectangle(0, 384, 1276,
            404, G_TX_RENDERTILE,
            0, 3072, 4096, 1024),
    myDPLoadTextureTile( 4, 102, 319, 107),
    gsSPTextureRectangle(0, 408, 1276,
            428, G_TX_RENDERTILE,
            0, 3264, 4096, 1024),
    myDPLoadTextureTile( 4, 108, 319, 113),
    gsSPTextureRectangle(0, 432, 1276,
            452, G_TX_RENDERTILE,
            0, 3456, 4096, 1024),
    myDPLoadTextureTile( 0, 114, 319, 119),
    gsSPTextureRectangle(0, 456, 1276,
            476, G_TX_RENDERTILE,
            0, 3648, 4096, 1024),
    myDPLoadTextureTile( 0, 120, 319, 125),
    gsSPTextureRectangle(0, 480, 1276,
            500, G_TX_RENDERTILE,
            0, 3840, 4096, 1024),
    myDPLoadTextureTile( 0, 126, 319, 131),
    gsSPTextureRectangle(0, 504, 1276,
            524, G_TX_RENDERTILE,
            0, 4032, 4096, 1024),
    myDPLoadTextureTile( 0, 132, 319, 137),
    gsSPTextureRectangle(0, 528, 1276,
            548, G_TX_RENDERTILE,
            0, 4224, 4096, 1024),
    myDPLoadTextureTile( 0, 138, 319, 143),
    gsSPTextureRectangle(0, 552, 1276,
            572, G_TX_RENDERTILE,
            0, 4416, 4096, 1024),
    myDPLoadTextureTile( 0, 144, 319, 149),
    gsSPTextureRectangle(0, 576, 1276,
            596, G_TX_RENDERTILE,
            0, 4608, 4096, 1024),
    myDPLoadTextureTile( 0, 150, 319, 155),
    gsSPTextureRectangle(0, 600, 1276,
            620, G_TX_RENDERTILE,
            0, 4800, 4096, 1024),
    myDPLoadTextureTile( 0, 156, 319, 161),
    gsSPTextureRectangle(0, 624, 1276,
            644, G_TX_RENDERTILE,
            0, 4992, 4096, 1024),
    myDPLoadTextureTile( 0, 162, 319, 167),
    gsSPTextureRectangle(0, 648, 1276,
            668, G_TX_RENDERTILE,
            0, 5184, 4096, 1024),
    myDPLoadTextureTile( 0, 168, 319, 173),
    gsSPTextureRectangle(0, 672, 1276,
            692, G_TX_RENDERTILE,
            0, 5376, 4096, 1024),
    myDPLoadTextureTile( 0, 174, 319, 179),
    gsSPTextureRectangle(0, 696, 1276,
            716, G_TX_RENDERTILE,
            0, 5568, 4096, 1024),
    myDPLoadTextureTile( 0, 180, 319, 185),
    gsSPTextureRectangle(0, 720, 1276,
            740, G_TX_RENDERTILE,
            0, 5760, 4096, 1024),
    myDPLoadTextureTile( 0, 186, 319, 191),
    gsSPTextureRectangle(0, 744, 1276,
            764, G_TX_RENDERTILE,
            0, 5952, 4096, 1024),
    myDPLoadTextureTile( 0, 192, 319, 197),
    gsSPTextureRectangle(0, 768, 1276,
            788, G_TX_RENDERTILE,
            0, 6144, 4096, 1024),
    myDPLoadTextureTile( 0, 198, 319, 203),
    gsSPTextureRectangle(0, 792, 1276,
            812, G_TX_RENDERTILE,
            0, 6336, 4096, 1024),
    myDPLoadTextureTile( 0, 204, 319, 209),
    gsSPTextureRectangle(0, 816, 1276,
            836, G_TX_RENDERTILE,
            0, 6528, 4096, 1024),
    myDPLoadTextureTile( 0, 210, 319, 215),
    gsSPTextureRectangle(0, 840, 1276,
            860, G_TX_RENDERTILE,
            0, 6720, 4096, 1024),
    myDPLoadTextureTile( 0, 216, 319, 221),
    gsSPTextureRectangle(0, 864, 1276,
            884, G_TX_RENDERTILE,
            0, 6912, 4096, 1024),
    myDPLoadTextureTile( 0, 222, 319, 227),
    gsSPTextureRectangle(0, 888, 1276,
            908, G_TX_RENDERTILE,
            0, 7104, 4096, 1024),
    myDPLoadTextureTile( 0, 228, 319, 233),
    gsSPTextureRectangle(0, 912, 1276,
            932, G_TX_RENDERTILE,
            0, 7296, 4096, 1024),
    myDPLoadTextureTile( 0, 234, 319, 239),
    gsSPTextureRectangle(0, 936, 1276,
            956, G_TX_RENDERTILE,
            0, 7488, 4096, 1024),

    gsSPEndDisplayList()
};

#ifdef OLD_METHOD
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 0, 319, 5, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 0, 1276,
            20, G_TX_RENDERTILE,
            0, 0, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 6, 319, 11, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 24, 1276,
            44, G_TX_RENDERTILE,
            0, 192, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 12, 319, 17, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 48, 1276,
            68, G_TX_RENDERTILE,
            0, 384, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 18, 319, 23, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 72, 1276,
            92, G_TX_RENDERTILE,
            0, 576, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 24, 319, 29, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 96, 1276,
            116, G_TX_RENDERTILE,
            0, 768, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 30, 319, 35, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 120, 1276,
            140, G_TX_RENDERTILE,
            0, 960, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 36, 319, 41, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 144, 1276,
            164, G_TX_RENDERTILE,
            0, 1152, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 42, 319, 47, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 168, 1276,
            188, G_TX_RENDERTILE,
            0, 1344, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 48, 319, 53, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 192, 1276,
            212, G_TX_RENDERTILE,
            0, 1536, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 54, 319, 59, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 216, 1276,
            236, G_TX_RENDERTILE,
            0, 1728, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 60, 319, 65, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 240, 1276,
            260, G_TX_RENDERTILE,
            0, 1920, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 66, 319, 71, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 264, 1276,
            284, G_TX_RENDERTILE,
            0, 2112, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 72, 319, 77, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 288, 1276,
            308, G_TX_RENDERTILE,
            0, 2304, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 78, 319, 83, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 312, 1276,
            332, G_TX_RENDERTILE,
            0, 2496, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 84, 319, 89, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 336, 1276,
            356, G_TX_RENDERTILE,
            0, 2688, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 90, 319, 95, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 360, 1276,
            380, G_TX_RENDERTILE,
            0, 2880, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 96, 319, 101, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 384, 1276,
            404, G_TX_RENDERTILE,
            0, 3072, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 102, 319, 107, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 408, 1276,
            428, G_TX_RENDERTILE,
            0, 3264, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            4, 108, 319, 113, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 432, 1276,
            452, G_TX_RENDERTILE,
            0, 3456, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 114, 319, 119, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 456, 1276,
            476, G_TX_RENDERTILE,
            0, 3648, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 120, 319, 125, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 480, 1276,
            500, G_TX_RENDERTILE,
            0, 3840, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 126, 319, 131, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 504, 1276,
            524, G_TX_RENDERTILE,
            0, 4032, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 132, 319, 137, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 528, 1276,
            548, G_TX_RENDERTILE,
            0, 4224, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 138, 319, 143, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 552, 1276,
            572, G_TX_RENDERTILE,
            0, 4416, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 144, 319, 149, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 576, 1276,
            596, G_TX_RENDERTILE,
            0, 4608, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 150, 319, 155, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 600, 1276,
            620, G_TX_RENDERTILE,
            0, 4800, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 156, 319, 161, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 624, 1276,
            644, G_TX_RENDERTILE,
            0, 4992, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 162, 319, 167, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 648, 1276,
            668, G_TX_RENDERTILE,
            0, 5184, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 168, 319, 173, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 672, 1276,
            692, G_TX_RENDERTILE,
            0, 5376, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 174, 319, 179, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 696, 1276,
            716, G_TX_RENDERTILE,
            0, 5568, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 180, 319, 185, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 720, 1276,
            740, G_TX_RENDERTILE,
            0, 5760, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 186, 319, 191, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 744, 1276,
            764, G_TX_RENDERTILE,
            0, 5952, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 192, 319, 197, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 768, 1276,
            788, G_TX_RENDERTILE,
            0, 6144, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 198, 319, 203, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 792, 1276,
            812, G_TX_RENDERTILE,
            0, 6336, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 204, 319, 209, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 816, 1276,
            836, G_TX_RENDERTILE,
            0, 6528, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 210, 319, 215, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 840, 1276,
            860, G_TX_RENDERTILE,
            0, 6720, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 216, 319, 221, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 864, 1276,
            884, G_TX_RENDERTILE,
            0, 6912, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 222, 319, 227, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 888, 1276,
            908, G_TX_RENDERTILE,
            0, 7104, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 228, 319, 233, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 912, 1276,
            932, G_TX_RENDERTILE,
            0, 7296, 4096, 1024),
    gsDPLoadTextureTile(&(rsp_cfb[SCREEN_OFF]), G_IM_FMT_CI, G_IM_SIZ_8b,
            320, 240,
            0, 234, 319, 239, 0,
            G_TX_CLAMP, G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(0, 936, 1276,
            956, G_TX_RENDERTILE,
            0, 7488, 4096, 1024),
#endif /* OLD_METHOD */
