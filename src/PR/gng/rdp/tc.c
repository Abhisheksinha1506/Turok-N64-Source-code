/**************************************************************************DD
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
* File:	tc.c
* Purpose:	dynamic DL tests for texture coordinate test vector generation.
*
*
* This application is a test-bed of single frame tests for RDP
* verification. The idea is that each frame possibly uses a different
* dataset (see tc_static.c) to render a particular test.
*
* This is a MODULE and TEST-SPECIFIC file, see comment in main.c for more
* information.
*
* TO ADD A TEST CASE:
*
* New test cases require that you define the display list and add
* a few simple things in the files tc.h, tc.c, tc_static.c.
*
* All locations are marked with comments that say "ADD TEST CASE"
* and give some hints what you need to do there. See main.c for
* detailed instructions.
*
*/

#include <ultra64.h>

#include "dldriver.h"
#include "toplevel.h"
#include "texture.h"
#include "tc.h"

/*
*  Predefined triangles sent directly to RDP
*/

typedef union {
u64 l;
u32	w[2];
} RDPRSPWord;



/*
*  Triangles to test TC divider and S/T multipliers
*  They are defined in the RDP input format so ucode can't
*  screw up our carefully choosen coefficients.
*
*  4 triangles step S/T from 1023 to -1/32, step W from
*  1.0 to -1/32K.
*/
static RDPRSPWord tc_div_tri[] = {

	/* tri 0 */
	0xca8002f802f402f4LLU, /* YL, YM, YH */
	0x0135800000000000LLU, /* XL, dXLdY */
	0x00000000012bbf6aLLU, /* XH, dXHdY */
	0x0000000001ccffb5LLU, /* XM, dXMdY */
	0x7fff7fff7fffdeadLLU, /*    Si,    Ti,    Wi, XX */
	0xffe1ffe1ffe1deadLLU, /* dSdXi, dTdXi, dWdXi, XX */
	0xffffffffffffdeadLLU, /*    Sf,    Tf,    Wf, XX */
	0x000000000000deadLLU, /* dSdXf, dTdXf, dWdXf, XX */
	0x000000000000deadLLU, /* dSdEi, dTdEi, dWdEi, XX */
	0x000000000000deadLLU, /* dSdYi, dTdYi, dWdYi, XX */
	0x000000000000deadLLU, /* dSdEf, dTdEf, dWdEf, XX */
	0x000000000000deadLLU, /* dSdYf, dTdYf, dWdYf, XX */
	/* tri 1 */
	0xca8002f402ec02ecLLU, /* YL, YM, YH */
	0x0135800000000000LLU, /* XL, dXLdY */
	0x00000000012bbf6aLLU, /* XH, dXHdY */
	0x0000000001ccffb5LLU, /* XM, dXMdY */
	0x57ef57ef57efdeadLLU, /*    Si,    Ti,    Wi, XX */
	0xffe1ffe1ffe1deadLLU, /* dSdXi, dTdXi, dWdXi, XX */
	0xffffffffffffdeadLLU, /*    Sf,    Tf,    Wf, XX */
	0x000000000000deadLLU, /* dSdXf, dTdXf, dWdXf, XX */
	0x000000000000deadLLU, /* dSdEi, dTdEi, dWdEi, XX */
	0x000000000000deadLLU, /* dSdYi, dTdYi, dWdYi, XX */
	0x000000000000deadLLU, /* dSdEf, dTdEf, dWdEf, XX */
	0x000000000000deadLLU, /* dSdYf, dTdYf, dWdYf, XX */
	/* tri 2 */
	0xca8002ec02e802e8LLU, /* YL, YM, YH */
	0x0135800000000000LLU, /* XL, dXLdY */
	0x00000000012bbf6aLLU, /* XH, dXHdY */
	0x0000000001ccffb5LLU, /* XM, dXMdY */
	0x2fef2fef2fefdeadLLU, /*    Si,    Ti,    Wi, XX */
	0xffe1ffe1ffe1deadLLU, /* dSdXi, dTdXi, dWdXi, XX */
	0xffffffffffffdeadLLU, /*    Sf,    Tf,    Wf, XX */
	0x000000000000deadLLU, /* dSdXf, dTdXf, dWdXf, XX */
	0x000000000000deadLLU, /* dSdEi, dTdEi, dWdEi, XX */
	0x000000000000deadLLU, /* dSdYi, dTdYi, dWdYi, XX */
	0x000000000000deadLLU, /* dSdEf, dTdEf, dWdEf, XX */
	0x000000000000deadLLU, /* dSdYf, dTdYf, dWdYf, XX */
	/* tri 3 */
	0xca8002e802e402e4LLU, /* YL, YM, YH */
	0x0135800000000000LLU, /* XL, dXLdY */
	0x00000000012bbf6aLLU, /* XH, dXHdY */
	0x0000000001ccffb5LLU, /* XM, dXMdY */
	0x07ef07ef07efdeadLLU, /*    Si,    Ti,    Wi, XX */
	0xffe1ffe1ffe1deadLLU, /* dSdXi, dTdXi, dWdXi, XX */
	0xffffffffffffdeadLLU, /*    Sf,    Tf,    Wf, XX */
	0x000000000000deadLLU, /* dSdXf, dTdXf, dWdXf, XX */
	0x000000000000deadLLU, /* dSdEi, dTdEi, dWdEi, XX */
	0x000000000000deadLLU, /* dSdYi, dTdYi, dWdYi, XX */
	0x000000000000deadLLU, /* dSdEf, dTdEf, dWdEf, XX */
	0x000000000000deadLLU, /* dSdYf, dTdYf, dWdYf, XX */

};



/*
 *  TC test procedure
 */
void
testTC(Dynamic *dynamicp, Gfx *module_test)
{
	int 			i, j;
	static float    theta = 0.0;
	
	guOrtho(&dynamicp->projection,
		0, SCREEN_WD,
		0, SCREEN_HT, -1, 1, 1.0);
	
	guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);
	
	gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
		G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
	
	gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
		G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

	/*
	 *  TC Inverse W; S/T mulitplier test
	 */

	gDPPipeSync(glistp++);
	gDPSetCycleType(glistp++, G_CYC_1CYCLE);
	gSPClearGeometryMode(glistp++, G_ZBUFFER | G_SHADE | 
		G_SHADING_SMOOTH | G_CULL_BOTH);
	gSPClearGeometryMode(glistp++, G_FOG | G_LIGHTING | 
		G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR);
	gDPSetTextureLUT(glistp++, G_TT_NONE);
	gDPSetTextureDetail(glistp++, G_TD_CLAMP);
	gDPSetTextureFilter(glistp++, G_TF_BILERP);
	gDPSetTextureConvert(glistp++, G_TC_FILT);
	gDPSetCombineKey(glistp++, G_CK_NONE);
	gDPSetAlphaCompare(glistp++, G_AC_NONE);
	gDPSetRenderMode(glistp++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
	gDPSetColorDither(glistp++, G_CD_DISABLE);
	
	gDPSetTextureLOD(glistp++, G_TL_TILE);
	gDPSetCombineMode (glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
	gDPSetTexturePersp(glistp++, G_TP_PERSP);
	gSPTexture(glistp++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
	
	gDPLoadTextureBlock(glistp++, map_rand, 
		 G_IM_FMT_RGBA, G_IM_SIZ_16b, 
		 32, 64, 
		 0,
		 G_TX_MIRROR, G_TX_MIRROR,
		 0xa, 0xa, G_TX_NOLOD, G_TX_NOLOD);
	gDPSetTileSize(glistp++, G_TX_RENDERTILE, 0, 0, 1023 << 2, 1023 << 2);
	
	/* send predefined triangles */
	for(i = 0; i < sizeof(tc_div_tri)/sizeof(u64); i++) {
		gDPWord(glistp++, tc_div_tri[i].w[0], tc_div_tri[i].w[1]);
	}	
	
	/*
	 *  Tile Shift Test - vary tile shift from 0->15, use 'noisy' dxs, dyt
	 */
	gDPNoOpTag(glistp++, 0x41100000);
	gDPSetTexturePersp(glistp++, G_TP_NONE);
	for(i = 0; i < 16; i++) {
		gDPTileSync(glistp++);
		gDPSetTile(glistp++, 
			G_IM_FMT_RGBA, G_IM_SIZ_16b,
			2, 0, G_TX_RENDERTILE, 0,
			0, 0xa, i, 
			0, 0xa, i);
		gSPTextureRectangle(glistp++,
			(32+i) << 2, (140+i) << 2,
			(32+i+2) << 2, (140+i+2) << 2,
			G_TX_RENDERTILE,
			i << 5, i << 5, 1921+i, 1571+i);
	}
	
	/* 
	 *  restore tile shift 
	 */
	gDPTileSync(glistp++);
	gDPSetTile(glistp++, 
		G_IM_FMT_RGBA, G_IM_SIZ_16b,
		2, 0, G_TX_RENDERTILE, 0,
		0, 0xa, 0, 
		0, 0xa, 0);
	
	
	/*
	 *  S-SL, T-TL subtractors
	 */
	gDPNoOpTag(glistp++, 0x41100001);
	gDPSetTileSize(glistp++, G_TX_RENDERTILE, 
		0x2aa, 0x2aa, 0x4095, 0x4095);
	gSPTextureRectangle(glistp++,
		180 << 2, 40 << 2,
		192 << 2, 42 << 2,
		G_TX_RENDERTILE,
		0x5555, 0x5555, 0x2aaa, 0x2aaa);
	gDPTileSync(glistp++);
	gDPSetTileSize(glistp++, G_TX_RENDERTILE, 
		0x355, 0x355, 0x4095, 0x4095);
	gSPTextureRectangle(glistp++,
		180 << 2, 42 << 2,
		192 << 2, 44 << 2,
		G_TX_RENDERTILE,
		0x5555, 0x5555, 0x2aaa, 0x2aaa);
	
	
	
	/*
	 *  Wrap/Mirror Test
	 */
	gDPTileSync(glistp++);
	gDPNoOpTag(glistp++, 0x41100002);
	gDPSetTileSize(glistp++, G_TX_RENDERTILE, 
		0x0, 0x0, 0x4095, 0x4095);
	for(i = 0; i < 2; i++) {
		for(j = 0; j < 16; j++) {
			gDPTileSync(glistp++);
			gDPSetTile(glistp++, 
				G_IM_FMT_RGBA, G_IM_SIZ_16b,
				2, 0, G_TX_RENDERTILE, 0,
				i, j, 0, 
				i, j, 0);
			gSPTextureRectangle(glistp++,
				32  << 2, (100+j*(i+1)) << 2,
				300 << 2, (100+j*(i+1)+2) << 2,
				G_TX_RENDERTILE,
				0 << 5, 0 << 5, 3912, 3913);
		}
	}
	
	
	
	/*
	 *  Clamp Test - texture rectangle steps s/t from 0->1024
	 *  for each rectangle change the SH/TH to test clamp.
	 */
	gDPTileSync(glistp++);
	gDPNoOpTag(glistp++, 0x41100003);
	gDPSetTile(glistp++, 
	G_IM_FMT_RGBA, G_IM_SIZ_16b,
	2, 0, G_TX_RENDERTILE, 0,
	G_TX_CLAMP, 15, 0, 
	G_TX_CLAMP, 15, 0);
	
	for(j = 0; j < 12; j++) {
		gDPTileSync(glistp++);
		gDPSetTileSize(glistp++, G_TX_RENDERTILE, 
			0x0, 0x0, (1 << j)-1, (1 << j)-1);
		gSPTextureRectangle(glistp++,
			32  << 2, (50+j) << 2,
			300 << 2, (50+j+2) << 2,
			G_TX_RENDERTILE,
			0 << 5, 0 << 5, 3912, 3913);
	}
	
	
	/*
	 *  Address Calculator
	 *
	 *  Walk line, and Tmem addresses, not trying to hit every
	 *  possible value.  Draw little 2x2 rectangles to see a few pixels.
	 */
	gDPTileSync(glistp++);
	gDPNoOpTag(glistp++, 0x41100004);
	gDPSetTileSize(glistp++, 
		G_TX_RENDERTILE, 
		0x0, 0x0, 4095, 4095);
	
	for(j = 1; j < 32; j++) {
	gDPTileSync(glistp++);
	gDPSetTile(glistp++, 
		G_IM_FMT_RGBA, G_IM_SIZ_16b,
		(128*j)-1, (16*j)-1, G_TX_RENDERTILE, 0,
		0, 15, 0, 
		0, 15, 0);
	gSPTextureRectangle(glistp++,
		(32+j) << 2, (40+j) << 2,
		(38+j) << 2, (48+j) << 2,
		G_TX_RENDERTILE,
		0 << 5, 0 << 5, 3912, 3913);
	}
	
	
	
	/*
	 *  Neighborhood Address Calculator - test point sample mode
	 */
	gDPPipeSync(glistp++);
	gDPNoOpTag(glistp++, 0x41100005);
	gDPSetTextureFilter(glistp++, G_TF_POINT);
	gDPSetTileSize(glistp++, 
		G_TX_RENDERTILE, 
		0x0, 0x0, (1024 << 2)-1, (1024 << 2)-1);
	gDPSetTile(glistp++, 
		G_IM_FMT_RGBA, G_IM_SIZ_16b,
		11, 45, G_TX_RENDERTILE, 0,
		0, 0xb, 0, 
		0, 0xd, 0);
	gSPTextureRectangle(glistp++,
		45 << 2, 45 << 2,
		49 << 2, 49 << 2,
		G_TX_RENDERTILE,
		0 << 5, 0 << 5, 1024, 1024);
	
	
	
	/*
	 *  Fraction Unit
	 */
	gDPPipeSync(glistp++);
	gDPNoOpTag(glistp++, 0x41100006);
	gDPSetTextureFilter(glistp++, G_TF_BILERP);
	
	
	
	/*
	 *  Tile Mem - walk through each tile number, two rectangles
	 *  toggle each bit in the tile mem.  Enable texture LUT.
	 */
	gDPPipeSync(glistp++);
	gDPNoOpTag(glistp++, 0x41100007);
	/* gDPSetTextureLUT(glistp++, G_TT_RGBA16); */
	
	for(i = 0; i < 8; i++) {
		gDPSetTileSize(glistp++, 
			i, 
			0x555, 0x555, 0xaaa, 0xaaa);
		gDPSetTile(glistp++, 
			G_IM_FMT_RGBA, G_IM_SIZ_32b,
			0x1aa, 0x1aa, i, 0xa,
			1, 5, 0xf, 
			1, 5, 0xf);
		gSPTextureRectangle(glistp++,
			 99 << 2, (40+i) << 2,
			109 << 2, (44+i) << 2,
			i,
			0 << 5, 0 << 5, 1278, 1097);
		gDPTileSync(glistp++);
		gDPSetTileSize(glistp++, 
			i, 
			0xaaa, 0xaaa, 0xddd, 0xddd);
		gDPSetTile(glistp++, 
			G_IM_FMT_IA, G_IM_SIZ_4b,
			0x055, 0x055, i, 0x5,
			0, 0xa, 0, 
			0, 0xa, 0);
		gSPTextureRectangle(glistp++,
			 99 << 2, (40+i) << 2,
			109 << 2, (44+i) << 2,
			i,
			0 << 5, 0 << 5, 2478, 3187);
	}
	
	
    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/*
 *  Triangles to test LOD
 */
static RDPRSPWord tc_lod_tri0[] = {
	/* max_level = 7, tile = 0 */
	/* check T circuit */
	0xca3800e000da00daLLU, /* YL, YM, YH */
	0x0057000000013c46LLU, /* XL, dXLdY */
	0x00bc8044ffffff7cLLU, /* XH, dXHdY */
	0x00bd4610fffe73e5LLU, /* XM, dXMdY */
	0x000005d705d3deadLLU, /*    Si,    Ti,    Wi, XX */
	0x00000009ff51deadLLU, /* dSdXi, dTdXi, dWdXi, XX */
	0x0000fe6eadfedeadLLU, /*    Sf,    Tf,    Wf, XX */
	0x0000b0b0cca5deadLLU, /* dSdXf, dTdXf, dWdXf, XX */
	0x0000fff4ffffdeadLLU, /* dSdEi, dTdEi, dWdEi, XX */
	0x0000fff4ffffdeadLLU, /* dSdYi, dTdYi, dWdYi, XX */
	0x000002168cb7deadLLU, /* dSdEf, dTdEf, dWdEf, XX */
	0x0000071632e5deadLLU, /* dSdYf, dTdYf, dWdYf, XX */

	/* check S circuit */
	0xca3800e000da00daLLU, /* YL, YM, YH */
	0x0057000000013c46LLU, /* XL, dXLdY */
	0x00bc8044ffffff7cLLU, /* XH, dXHdY */
	0x00bd4610fffe73e5LLU, /* XM, dXMdY */
	0x05d7000005d3deadLLU, /*    Si,    Ti,    Wi, XX */
	0x00090000ff51deadLLU, /* dSdXi, dTdXi, dWdXi, XX */
	0xfe6e0000adfedeadLLU, /*    Sf,    Tf,    Wf, XX */
	0xb0b00000cca5deadLLU, /* dSdXf, dTdXf, dWdXf, XX */
	0xfff40000ffffdeadLLU, /* dSdEi, dTdEi, dWdEi, XX */
	0xfff40000ffffdeadLLU, /* dSdYi, dTdYi, dWdYi, XX */
	0x021600008cb7deadLLU, /* dSdEf, dTdEf, dWdEf, XX */
	0x0716000032e5deadLLU, /* dSdYf, dTdYf, dWdYf, XX */
};

static RDPRSPWord tc_lod_tri1[] = {
	/* max_level = 2, tile = 7 */
	/* check T circuit */
	0xca1700e800e400e4LLU, /* YL, YM, YH */
	0x0057000000013c46LLU, /* XL, dXLdY */
	0x00bc8044ffffff7cLLU, /* XH, dXHdY */
	0x00bd4610fffe73e5LLU, /* XM, dXMdY */
	0x000005d705d3deadLLU, /*    Si,    Ti,    Wi, XX */
	0x00000009ff51deadLLU, /* dSdXi, dTdXi, dWdXi, XX */
	0x0000fe6eadfedeadLLU, /*    Sf,    Tf,    Wf, XX */
	0x0000b0b0cca5deadLLU, /* dSdXf, dTdXf, dWdXf, XX */
	0x0000fff4ffffdeadLLU, /* dSdEi, dTdEi, dWdEi, XX */
	0x0000fff4ffffdeadLLU, /* dSdYi, dTdYi, dWdYi, XX */
	0x000002168cb7deadLLU, /* dSdEf, dTdEf, dWdEf, XX */
	0x0000071632e5deadLLU, /* dSdYf, dTdYf, dWdYf, XX */

	/* check S circuit */
	0xca1700e800e400e4LLU, /* YL, YM, YH */
	0x0057000000013c46LLU, /* XL, dXLdY */
	0x00bc8044ffffff7cLLU, /* XH, dXHdY */
	0x00bd4610fffe73e5LLU, /* XM, dXMdY */
	0x05d7000005d3deadLLU, /*    Si,    Ti,    Wi, XX */
	0x00090000ff51deadLLU, /* dSdXi, dTdXi, dWdXi, XX */
	0xfe6e0000adfedeadLLU, /*    Sf,    Tf,    Wf, XX */
	0xb0b00000cca5deadLLU, /* dSdXf, dTdXf, dWdXf, XX */
	0xfff40000ffffdeadLLU, /* dSdEi, dTdEi, dWdEi, XX */
	0xfff40000ffffdeadLLU, /* dSdYi, dTdYi, dWdYi, XX */
	0x021600008cb7deadLLU, /* dSdEf, dTdEf, dWdEf, XX */
	0x0716000032e5deadLLU, /* dSdYf, dTdYf, dWdYf, XX */
};

static RDPRSPWord tc_lod_tri2[] = {
	/* max_level = 5, tile = 6 */
	/* check T circuit */
	0xca2e00f000ec00ecLLU, /* YL, YM, YH */
	0x0057000000013c46LLU, /* XL, dXLdY */
	0x00bc8044ffffff7cLLU, /* XH, dXHdY */
	0x00bd4610fffe73e5LLU, /* XM, dXMdY */
	0x000005d705d3deadLLU, /*    Si,    Ti,    Wi, XX */
	0x00000009ff51deadLLU, /* dSdXi, dTdXi, dWdXi, XX */
	0x0000fe6eadfedeadLLU, /*    Sf,    Tf,    Wf, XX */
	0x0000b0b0cca5deadLLU, /* dSdXf, dTdXf, dWdXf, XX */
	0x0000fff4ffffdeadLLU, /* dSdEi, dTdEi, dWdEi, XX */
	0x0000fff4ffffdeadLLU, /* dSdYi, dTdYi, dWdYi, XX */
	0x000002168cb7deadLLU, /* dSdEf, dTdEf, dWdEf, XX */
	0x0000071632e5deadLLU, /* dSdYf, dTdYf, dWdYf, XX */

	/* check S circuit */
	0xca2e00f000ec00ecLLU, /* YL, YM, YH */
	0x0057000000013c46LLU, /* XL, dXLdY */
	0x00bc8044ffffff7cLLU, /* XH, dXHdY */
	0x00bd4610fffe73e5LLU, /* XM, dXMdY */
	0x05d7000005d3deadLLU, /*    Si,    Ti,    Wi, XX */
	0x00090000ff51deadLLU, /* dSdXi, dTdXi, dWdXi, XX */
	0xfe6e0000adfedeadLLU, /*    Sf,    Tf,    Wf, XX */
	0xb0b00000cca5deadLLU, /* dSdXf, dTdXf, dWdXf, XX */
	0xfff40000ffffdeadLLU, /* dSdEi, dTdEi, dWdEi, XX */
	0xfff40000ffffdeadLLU, /* dSdYi, dTdYi, dWdYi, XX */
	0x021600008cb7deadLLU, /* dSdEf, dTdEf, dWdEf, XX */
	0x0716000032e5deadLLU, /* dSdYf, dTdYf, dWdYf, XX */
};

static RDPRSPWord tc_lod_tri3[] = {
	/* max_level = 5, tile = 6 */
	/* check T circuit */
	0xca2e00f800f400f4LLU, /* YL, YM, YH */
	0x0057000000013c46LLU, /* XL, dXLdY */
	0x00bc8044ffffff7cLLU, /* XH, dXHdY */
	0x00bd4610fffe73e5LLU, /* XM, dXMdY */
	0x000005d705d3deadLLU, /*    Si,    Ti,    Wi, XX */
	0x00000009ff51deadLLU, /* dSdXi, dTdXi, dWdXi, XX */
	0x0000fe6eadfedeadLLU, /*    Sf,    Tf,    Wf, XX */
	0x0000b0b0cca5deadLLU, /* dSdXf, dTdXf, dWdXf, XX */
	0x0000fff4ffffdeadLLU, /* dSdEi, dTdEi, dWdEi, XX */
	0x0000fff4ffffdeadLLU, /* dSdYi, dTdYi, dWdYi, XX */
	0x000002168cb7deadLLU, /* dSdEf, dTdEf, dWdEf, XX */
	0x0000071632e5deadLLU, /* dSdYf, dTdYf, dWdYf, XX */

	/* check S circuit */
	0xca2e00f800f400f4LLU, /* YL, YM, YH */
	0x0057000000013c46LLU, /* XL, dXLdY */
	0x00bc8044ffffff7cLLU, /* XH, dXHdY */
	0x00bd4610fffe73e5LLU, /* XM, dXMdY */
	0x05d7000005d3deadLLU, /*    Si,    Ti,    Wi, XX */
	0x00090000ff51deadLLU, /* dSdXi, dTdXi, dWdXi, XX */
	0xfe6e0000adfedeadLLU, /*    Sf,    Tf,    Wf, XX */
	0xb0b00000cca5deadLLU, /* dSdXf, dTdXf, dWdXf, XX */
	0xfff40000ffffdeadLLU, /* dSdEi, dTdEi, dWdEi, XX */
	0xfff40000ffffdeadLLU, /* dSdYi, dTdYi, dWdYi, XX */
	0x021600008cb7deadLLU, /* dSdEf, dTdEf, dWdEf, XX */
	0x0716000032e5deadLLU, /* dSdYf, dTdYf, dWdYf, XX */
};


/*
 *  Color combiner mode which shows l_frac
 */
#define SHOW_LOD	ENVIRONMENT, PRIMITIVE, LOD_FRACTION,\
	PRIMITIVE, ENVIRONMENT, PRIMITIVE, LOD_FRACTION, PRIMITIVE


/*
 *  LOD test for TC module
 */
void
lod_test(Dynamic *dynamicp, Gfx *module_test)
{
	int i;
	static float    theta = 0.0;
	
	gDPPipeSync(glistp++);
	gDPSetCycleType(glistp++, G_CYC_2CYCLE);
	gDPSetCombineMode (glistp++, G_CC_TRILERP, G_CC_PASS2);
	gDPSetRenderMode(glistp++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
	gDPSetTexturePersp(glistp++, G_TP_PERSP);
	gDPSetTextureLOD(glistp++, G_TL_LOD);

	gDPLoadTextureBlock(glistp++, map_rand, 
		 G_IM_FMT_RGBA, G_IM_SIZ_16b, 
		 32, 64, 
		 0,
		 G_TX_MIRROR, G_TX_MIRROR,
		 0xa, 0xa, G_TX_NOLOD, G_TX_NOLOD);

    gDPSetTile(glistp++,0, 2, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0);
    gDPSetTileSize(glistp++, 0,  0, 0, 31 << G_TEXTURE_IMAGE_FRAC, 31 << G_TEXTURE_IMAGE_FRAC);
    gDPSetTile(glistp++,0, 2, 4, 256, 1, 0, 0, 4, 1, 0, 4, 1);
    gDPSetTileSize(glistp++, 1,  0, 0, 15 << G_TEXTURE_IMAGE_FRAC, 15 << G_TEXTURE_IMAGE_FRAC);
    gDPSetTile(glistp++,0, 2, 2, 320, 2, 0, 0, 3, 2, 0, 3, 2);
    gDPSetTileSize(glistp++, 2,  0, 0, 7 << G_TEXTURE_IMAGE_FRAC, 7 << G_TEXTURE_IMAGE_FRAC);
    gDPSetTile(glistp++,0, 2, 1, 336, 3, 0, 0, 2, 3, 0, 2, 3);
    gDPSetTileSize(glistp++, 3,  0, 0, 3 << G_TEXTURE_IMAGE_FRAC, 3 << G_TEXTURE_IMAGE_FRAC);
    gDPSetTile(glistp++,0, 2, 1, 340, 4, 0, 0, 1, 4, 0, 1, 4);
    gDPSetTileSize(glistp++, 4,  0, 0, 1 << G_TEXTURE_IMAGE_FRAC, 1 << G_TEXTURE_IMAGE_FRAC);
    gDPSetTile(glistp++,0, 2, 1, 342, 5, 0, 0, 0, 5, 0, 0, 5);
    gDPSetTileSize(glistp++, 5,  0, 0, 0 << G_TEXTURE_IMAGE_FRAC, 0 << G_TEXTURE_IMAGE_FRAC);
    gDPSetTile(glistp++,0, 2, 1, 400, 6, 0, 0, 0, 6, 0, 0, 6);
    gDPSetTileSize(glistp++, 6,  0, 0, 1 << G_TEXTURE_IMAGE_FRAC, 1 << G_TEXTURE_IMAGE_FRAC);
    gDPSetTile(glistp++,0, 2, 1, 464, 7, 0, 0, 0, 7, 0, 0, 7);
    gDPSetTileSize(glistp++, 7,  0, 0, 3 << G_TEXTURE_IMAGE_FRAC, 3 << G_TEXTURE_IMAGE_FRAC);
	
	
	/* min level = 0 */
	gDPSetPrimColor(glistp++, 0, 0, 0xff, 0xff, 0xff, 0xff);
	gDPSetTextureDetail(glistp++, G_TD_SHARPEN);

	/* 
	 * Triangles that step LOD from 0 to > 256 across a scanline
	 *
	 *  max_level = 7, prim_tile = 0
	 */
	/* send predefined triangles */
	for(i = 0; i < sizeof(tc_lod_tri0)/sizeof(u64); i++) {
		gDPWord(glistp++, tc_lod_tri0[i].w[0], tc_lod_tri0[i].w[1]);
	}	
	
	/* min level = 5 */
	gDPPipeSync(glistp++);
	gDPSetPrimColor(glistp++, 5, 0, 0xff, 0xff, 0xff, 0xff);
	gDPSetTextureDetail(glistp++, G_TD_DETAIL);

	/* 
	 * Triangles that step LOD from 0 to > 256 across a scanline
	 *
	 *  max_level = 2, prim_tile = 7
	 *
	 *  tile number should wrap (7,0,1) then clamp
	 *  min_level is set to clamp the lod fraction
	 */
	/* send predefined triangles */
	for(i = 0; i < sizeof(tc_lod_tri1)/sizeof(u64); i++) {
		gDPWord(glistp++, tc_lod_tri1[i].w[0], tc_lod_tri1[i].w[1]);
	}	
	
	/* min level = 0x1a */
	gDPPipeSync(glistp++);
	gDPSetPrimColor(glistp++, 0x1a, 0, 0xff, 0xff, 0xff, 0xff);
	gDPSetTextureDetail(glistp++, G_TD_DETAIL);

	/* 
	 * Triangles that step LOD from 0 to > 256 across a scanline
	 *
	 *  max_level = 5, prim_tile = 6
	 *
	 *  tile number should wrap (6,7,0,...) then clamp
	 *  min_level is set to clamp the lod fraction
	 */

	/* send predefined triangles */
	for(i = 0; i < sizeof(tc_lod_tri2)/sizeof(u64); i++) {
		gDPWord(glistp++, tc_lod_tri2[i].w[0], tc_lod_tri2[i].w[1]);
	}

	/*
	 *  Allow lod_frac to propagate to pins
	 */
	gDPPipeSync(glistp++);
	gDPSetCombineMode (glistp++, SHOW_LOD, SHOW_LOD);
	gDPSetPrimColor(glistp++, 0x1a, 0, 255, 0, 0, 255);
	gDPSetEnvColor(glistp++, 0, 255, 0, 255);

	/* send predefined triangles */
	for(i = 0; i < sizeof(tc_lod_tri3)/sizeof(u64); i++) {
		gDPWord(glistp++, tc_lod_tri3[i].w[0], tc_lod_tri3[i].w[1]);
	}

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}


/* 
 * ADD TEST CASE: test frames:
 *
 * Display lists from tc_static.c (which are placed in the static segment via
 * the spec file) must be inserted in this table, in the same position as the 
 * test's frame number, along with a mneumonic name (which will be used to name
 * the resulting .rdp display list file), and a pointer to the top level DL
 * function which will be used to invoke this static display list.
 * 
 * NOTE: a test doesn't need to have a static display list, if
 * the corresponding testCaseProc doesn't use one. But you still
 * need to put a NULL entry here in the table.
 */
GfxTest_t testList_tc[] = {
	(Gfx *) tc_div_init,	"tc_vector",	testTC,	G_IM_SIZ_16b, CLEAR_AQUA,
#ifdef NOTDEF
	(Gfx *) tc_div_init,	"tc_vector",	lod_test,	G_IM_SIZ_16b, CLEAR_AQUA,
#endif
	/* add new test cases above here: */
	
	/* Last entry must be NULL, so we can count them in main.c */
	(Gfx *) NULL,	"End list",		(CaseProc_t) NULL, G_IM_SIZ_16b, CLEAR_AQUA,
};
