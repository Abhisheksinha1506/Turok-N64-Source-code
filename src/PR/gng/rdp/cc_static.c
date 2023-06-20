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
 * File:	cc_static.c
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:
 *
 * This file holds tiny display list segments that are 'static' data, for use
 * by the color combiner test module in cc.c
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
 * is in cc.c, and the Gfx lists must be extern'd in rdpvector.h
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
static Vtx cc_place_vtx[5] =  {
/*     x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */	
    { -40,  40,    0,    0,	0,	0,	0xff,     0,     0,	0xff },	  /* R */   
    {  40,  40,    0,    0,	0,	0,	   0,  0xff,     0,	0xff },	  /* G */   
    {  40, -40,    0,    0,	0,	0,	   0,     0,  0xff,	0xff },	  /* B */   
    { -40, -40,    0,    0,	0,	0,	0xff,  0xff,     0,	0xff },	  /* Y */   
    {   0,   0,    0,    0,	0,	0,	0xff,  0xff,  0xff,	0xff },	  /* W */   
};

Gfx CC_placebo_dl[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&cc_place_vtx, 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};
/* end of case -1 */

/*
 * Test 1
 *
 * Simple square (4 triangles), each vertex a different color.
 *
 *
 */

#define     CC_STATIC_GFX_SIZE     2048

static Vtx cc_ramp_vtx[10] =  {
/*     x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */	
 { -40,  40,	 0,	 0,	0<<6,	0<<6,	0xff,	  0,	  0,	0xff },	  /* R */
 {  40,  40,	 0,	 0,	3<<6,	0<<6,	0,  0xff,	  0,	0xcc },	  /* G */	
 {  40, -40,	 0,	 0,	3<<6,	3<<6,		0,	  0,  0xff,	0x88 },	  /* B */	
 { -40, -40,	 0,	 0,	0<<6,	3<<6,	0xff,  0xff,	  0,	0x44 },	  /* Y */
 {	0,	0,	 0,	 0,	0x60,	0x60,	0xff,  0xff,  0xff,	0x00 },	  /* W */	

 { -40,  40,	 0,	 0,	0<<6,	0<<6,	0xff,	  0,	  0,	0xff },	  /* R */
 {  40,  40,	 0,	 0,	3<<6,	0<<6,	0,  0xff,	  0,	0xcc },	  /* G */	
 {  40, -40,-4980,	 0,	3<<6,	3<<6,		0,	  0,  0xff,	0x88 },	  /* B */	
 { -40, -40,-4980,	 0,	0<<6,	3<<6,	0xff,  0xff,	  0,	0x44 },	  /* Y */
 {	0,	0,	-2490,	 0,	0x60,	0x60,	0xff,  0xff,  0xff,	0x00 },	  /* W */	
};

#define XINC	4
static Vtx cc_vtx[85] =  {
/*   x,		   y, z,	flag,	s,	t,     	   r,	  g,	b,	a */	
 { -68,		  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66,		  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66,		  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68,		  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67,		  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66+XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+2*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+2*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66+2*XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+2*XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+2*XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+3*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+3*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66+3*XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+3*XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+3*XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+4*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+4*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66+4*XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+4*XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+4*XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+5*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+5*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66+5*XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+5*XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+5*XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+6*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+6*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66+6*XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+6*XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+6*XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+7*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+7*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66+7*XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+7*XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+7*XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+8*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+8*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66+8*XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+8*XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+8*XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+9*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+9*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66+9*XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+9*XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+9*XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+10*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+10*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xcc },	  /* G */
 { -66+10*XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0x88 },	  /* B */
 { -68+10*XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0x44 },	  /* Y */
 { -67+10*XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0x00 },	  /* W */

 { -68+11*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+11*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66+11*XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+11*XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+11*XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+12*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -67+12*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -67+12*XINC,  48,-4980, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+12*XINC,  48,-4980, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+12*XINC,  48,-2490, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+13*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+13*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66+13*XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+13*XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+13*XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+14*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+14*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66+14*XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+14*XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+14*XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+15*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+15*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66+15*XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+15*XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+15*XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

 { -68+16*XINC,  49, 0, 0,	0<<6, 0<<6, 0xff,     0,    0,	0xff },	  /* R */
 { -66+16*XINC,  49, 0, 0,	3<<6, 0<<6,	0, 0xff,    0,	0xff },	  /* G */
 { -66+16*XINC,  47, 0, 0,	3<<6, 3<<6,	0,	0,  0xff,	0xff },	  /* B */
 { -68+16*XINC,  47, 0, 0,	0<<6, 3<<6, 0xff,  0xff,     0,	0xff },	  /* Y */
 { -67+16*XINC,  48, 0, 0,	0x60, 0x60, 0xff,  0xff,  0xff,	0xff },	  /* W */

};

unsigned short ramp[] = {
	0x0000, 0x5295, 0xad6b, 0xffff, 0x5295, 0xad6b, 0xffff, 0x0000,
	0xad6b, 0xffff, 0x0000, 0x5295, 0xffff, 0x0000, 0x5295, 0xad6b,
	0x5555, 0xaaaa, 0x0000, 0x0000, 0x0000, 0x0000, 0xaaaa, 0x5555,
	0xaaaa, 0x0000, 0x0000, 0x0000,
};

#define MINL	0x1f
#define LOD	0xdf
#define RED	0xaa
#define GRN	0x55
#define BLU	0xdd
#define ALPHA	0x77

Gfx CC_dl[CC_STATIC_GFX_SIZE] = {

	/* CC pattern	1X	2X	1X	1X	1X	2X	1X	1X */
	/* CC patter2	0X	31	3	31	0X	7	3	7 */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
#define CC_OP	TEXEL0, TEXEL1, TEXEL0, TEXEL0, TEXEL0, TEXEL1, TEXEL0, TEXEL0
#define CC_OP2	COMBINED, 0, PRIMITIVE, 0, COMBINED, 0, PRIMITIVE, 0
    gsDPSetCombineMode (CC_OP, CC_OP2),
	gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
	gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
	gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
	gsDPLoadTextureBlock(cc_texture, G_IM_FMT_RGBA, G_IM_SIZ_16b,
		4, 4, 0,
		G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPPipeSync(),
    gsSPVertex(&cc_vtx, 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	2X	1X	2X	2X	2X	1X	2X	2X */
	/* CC patter2	6	0X	3	31	6	0X	3	7 */
    gsDPPipeSync(),
#undef CC_OP
#define CC_OP	TEXEL1, TEXEL0, TEXEL1, TEXEL1, TEXEL1, TEXEL0, TEXEL1, TEXEL1
#undef CC_OP2
#define CC_OP2	1, COMBINED, PRIMITIVE, 0, 1, COMBINED, PRIMITIVE, 0
    gsDPSetCombineMode (CC_OP, CC_OP2),
    gsSPVertex(&cc_vtx[5], 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	3X	4X	3X	3X	3X	4X	3X	3X */
	/* CC patter2	6	31	0X	31	3	4	3	3 */
    gsDPPipeSync(),
#undef	RED
#define RED	0x55
#undef	GRN
#define GRN	0xaa
#undef	BLU
#define BLU	0x87
    gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef CC_OP
#define CC_OP	PRIMITIVE, SHADE, PRIMITIVE, PRIMITIVE, PRIMITIVE, SHADE, PRIMITIVE, PRIMITIVE
#undef CC_OP2
#define CC_OP2	1, 0, COMBINED, 0, PRIMITIVE, SHADE, PRIMITIVE, PRIMITIVE
    gsDPSetCombineMode (CC_OP, CC_OP2),
    gsSPVertex(&(cc_vtx[10]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	4X	3X	4X	4X	4X	3X	4X	4X */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
#undef CC_OP
#define CC_OP	SHADE, PRIMITIVE, SHADE, SHADE, SHADE, PRIMITIVE, SHADE, SHADE
    gsDPSetCombineMode (CC_OP, CC_OP),
    gsSPVertex(&(cc_vtx[15]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	5X	6X	5X	5X	5X	6X	5X	5X */
    gsDPPipeSync(),
#undef RED
#define RED	0x25
#undef GRN
#define GRN	0xff
#undef BLU
#define BLU	0x4f
#undef ALPHA
#define ALPHA	0x89
    gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
    gsDPSetCombineKey (G_CK_KEY),
    gsDPSetKeyR (0xaa, 0xff, 0x20),
    gsDPSetKeyGB (0x88, 0xff, 0x30, 0xcc, 0xff, 0x40),
#undef CC_OP
#define CC_OP	ENVIRONMENT, CENTER, ENVIRONMENT, ENVIRONMENT, ENVIRONMENT, 1, ENVIRONMENT, ENVIRONMENT
    gsDPSetCombineMode (CC_OP, CC_OP),
    gsSPVertex(&(cc_vtx[20]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	1	6	6X	31	6	5X	5	5 */
    gsDPPipeSync(),
#undef CC_OP
#define CC_OP	TEXEL0, CENTER, SCALE, 0, 1, ENVIRONMENT, ENVIRONMENT, ENVIRONMENT
    gsDPSetCombineMode (CC_OP, CC_OP),
    gsSPVertex(&(cc_vtx[25]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	31	31	31	31	6X	7X	1	7X */
	/* CC patter2	7X	7X	7X	31	7	7	7	7 */
#define MY_K0   (175 & 0x1ff)
#define MY_K1   (-43 & 0x1ff)
#define MY_K2   (-89 & 0x1ff)
#define MY_K3   (222 & 0x1ff)
#define MY_K4   (114 & 0x1ff)
#define MY_K5   (42 & 0x1ff)

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetConvert(MY_K0, MY_K1, MY_K2, MY_K3, MY_K4, MY_K5),
    gsDPSetCombineKey (G_CK_NONE),
#undef CC_OP
#define CC_OP	0, 0, 0, 0, PRIM_LOD_FRAC, 0, TEXEL0, 0
#undef CC_OP2
/*
 * Don't specify NOISE; we want repeatable checksum behavior for go/no-go.
#define CC_OP2	NOISE, K4, COMBINED_ALPHA, 0, 0, 0, 0, 0
*/
#define CC_OP2	0, K4, COMBINED_ALPHA, 0, 0, 0, 0, 0
    gsDPSetCombineMode (CC_OP, CC_OP2),
    gsSPVertex(&(cc_vtx[30]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	6X	31X	8X	31	7X	4	4	4 */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
#undef CC_OP
#define CC_OP	1, 0, TEXEL0_ALPHA, 0, 0, SHADE, SHADE, SHADE
    gsDPSetCombineMode (CC_OP, CC_OP),
    gsSPVertex(&(cc_vtx[35]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	6	31	9X	31	4	7	4	7 */
    gsDPPipeSync(),
#undef CC_OP
#define CC_OP	1, 0, TEXEL1_ALPHA, 0, SHADE, 0, SHADE, 0
    gsDPSetCombineMode (CC_OP, CC_OP),
    gsSPVertex(&(cc_vtx[40]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	6	5X	10X	31X	6	5	6X	7 */
    gsDPPipeSync(),
#undef BLU
#define BLU	0xff
#undef ALPHA
#define ALPHA	0xaa
    gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef CC_OP
#define CC_OP	1, ENVIRONMENT, PRIMITIVE_ALPHA, 0, 1, ENVIRONMENT, 1, 0
    gsDPSetCombineMode (CC_OP, CC_OP),
    gsSPVertex(&(cc_vtx[45]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	6	3	11X	31	7	6	4	6X */
    gsDPPipeSync(),
#undef RED
#define RED	0xaa
#undef GRN
#define GRN	0x88
#undef BLU
#define BLU	0x55
#undef ALPHA
#define ALPHA	0xaa
    gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef CC_OP
#define CC_OP	1, PRIMITIVE, SHADE_ALPHA, 0, 0, 1, SHADE, 1
    gsDPSetCombineMode (CC_OP, CC_OP),
    gsSPVertex(&(cc_vtx[50]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	6	3	12X	31	4	4	4	4 */
    gsDPPipeSync(),
#undef RED
#define RED	0x88
#undef GRN
#define GRN	0x55
#undef BLU
#define BLU	0xaa
#undef ALPHA
#define ALPHA	0x77
    gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
#undef CC_OP
#define CC_OP	1, PRIMITIVE, ENV_ALPHA, 0, SHADE, SHADE, SHADE, SHADE
    gsDPSetCombineMode (CC_OP, CC_OP),
    gsSPVertex(&(cc_vtx[55]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	2	1	13X	1	2	1	0X	1 */
	/* CC patter2	31	31	31	0X	7	7	7	0X */
    gsDPPipeSync(),
#undef CC_OP
#define CC_OP	ENVIRONMENT, 0, LOD_FRACTION, 0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0
	gsDPSetCombineMode(CC_OP, G_CC_PASS2),
	gsDPSetCombineMode(G_CC_TRILERP, G_CC_PASS2),

	gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH |
			G_FOG | G_LIGHTING | G_TEXTURE_GEN |
			G_TEXTURE_GEN_LINEAR | G_LOD ),
	gsSPSetGeometryMode(G_ZBUFFER),
	gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
	gsDPSetTextureDetail (G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
	gsSPTexture(0x8000, 0x8000, 3, G_TX_RENDERTILE, G_ON),

	gsDPSetTextureImage( 0, 2, 1, cc_texture),
	gsDPSetTile( 0, 2, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0),
	gsDPLoadBlock( G_TX_LOADTILE, 0, 0, 28, 0),
	gsDPSetTile(0, 2, 1, 0, 0, 0, 0, 2, 0, 0, 2, 0),
	gsDPSetTileSize( 0,  0, 0, 3 << G_TEXTURE_IMAGE_FRAC, 3 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 1, 4, 1, 0, 0, 1, 1, 0, 1, 1),
	gsDPSetTileSize( 1,  0, 0, 1 << G_TEXTURE_IMAGE_FRAC, 1 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 1, 6, 2, 0, 0, 0, 2, 0, 0, 2),
	gsDPSetTileSize( 2,  0, 0, 0 << G_TEXTURE_IMAGE_FRAC, 0 << G_TEXTURE_IMAGE_FRAC),
	gsDPPipeSync(),
	gsDPSetTextureLOD(G_TL_LOD),
	gsDPPipelineMode(G_PM_1PRIMITIVE),
	gsDPSetCycleType(G_CYC_2CYCLE),

    gsSPVertex(&(cc_vtx[60]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/*
    gsSPVertex(&cc_ramp_vtx[5], 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
	*/

	/* CC pattern	3	31	14X	31	2	1	6	1 */
	/* CC patter2	31	31	31	0	6	4	7X	0 */
    gsDPPipeSync(),
#undef CC_OP
#define CC_OP	PRIMITIVE, 0, PRIM_LOD_FRAC, 0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0
#undef CC_OP2
#define CC_OP2	0, 0, 0, COMBINED, 1, SHADE, 0, COMBINED
	gsDPSetCombineMode(CC_OP, CC_OP2),
	gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
	gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTexturePersp(G_TP_NONE),
	gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(&(cc_vtx[65]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	2	7	15X	2	7	7	7	7 */
	/* CC patter2	31	31	31	0	7	7	7	0 */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetTextureConvert(G_TC_FILTCONV),
    gsDPSetConvert(MY_K0, MY_K1, MY_K2, MY_K3, MY_K4, MY_K5),
    gsDPSetCombineMode(G_CC_YUV2RGB, G_CC_PASS2),
    gsSPVertex(&(cc_vtx[70]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	7	1	31X	1	2	7	7	2 */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureConvert(G_TC_FILT),
#undef CC_OP
/*
 * Don't specify NOISE; we want repeatable checksum behavior for go/no-go.
#define CC_OP	NOISE, TEXEL0, 0, TEXEL0, TEXEL1, 0, 0, TEXEL1
*/
#define CC_OP	0, TEXEL0, 0, TEXEL0, TEXEL1, 0, 0, TEXEL1
    gsDPSetCombineMode (CC_OP, CC_OP),
    gsSPVertex(&(cc_vtx[75]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/* CC pattern	31X	6	4	6X	4	4	4	3 */
	/* CC patter2	0	0	0	0	0	0	2	0 */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
#undef CC_OP
#define CC_OP	0, 1, SHADE, 1, SHADE, SHADE, SHADE, PRIMITIVE
#undef CC_OP2
#define CC_OP2	COMBINED, COMBINED, COMBINED, COMBINED,  COMBINED, COMBINED, TEXEL1, COMBINED
    gsDPSetCombineMode (CC_OP, CC_OP2),
    gsSPVertex(&(cc_vtx[80]), 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),

	/*
    gsSPVertex(&cc_ramp_vtx, 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
	*/

	/* lerp vectors */
	/* CC pattern	1	3	14	5	1	3	6	5 */

#define XBASE 24
#define YBASE 85
#define X0 XBASE
#define Y0 YBASE
#undef YOFF
#define YOFF Y0
#define TEX_WIDTH 128
#define TEX_HEIGHT 1
#define WIDTH 4
#define HEIGHT 4

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
#define BL_OP1    IM_RD | CVG_DST_WRAP | CVG_X_ALPHA |       \
			FORCE_BL | ZMODE_OPA | ALPHA_CVG_SEL |           \
			GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_FOG, G_BL_1)
#define BL_OP2    IM_RD | CVG_DST_WRAP | CVG_X_ALPHA |       \
			FORCE_BL | ZMODE_OPA | ALPHA_CVG_SEL |           \
			GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_FOG, G_BL_1)
	gsDPSetFogColor (0x0, 0x0, 0x0, 0x0),
	gsDPSetRenderMode(BL_OP1, BL_OP2),
	/*
	gsDPSetRenderMode(CVG_DST_WRAP | CVG_X_ALPHA | ALPHA_CVG_SEL | 
					  IM_RD | G_RM_OPA_SURF, 
					  CVG_DST_WRAP | CVG_X_ALPHA | ALPHA_CVG_SEL | 
					  IM_RD | G_RM_OPA_SURF2),
	*/
	gsDPSetTextureFilter(G_TF_POINT),
	gsDPLoadTextureBlock(cc_lerp_texture, G_IM_FMT_RGBA, G_IM_SIZ_32b,
		TEX_WIDTH, TEX_HEIGHT, 0, 0, 0, 0, 0, 0, 0),

#undef MINL
#define MINL	0x0
#undef CC_OP
#define CC_OP	TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, ENVIRONMENT, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, ENVIRONMENT
	gsDPSetCombineMode (CC_OP, CC_OP),

#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+0*HEIGHT+0*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x9d
#undef GRN
#define GRN 0x9d
#undef BLU
#define BLU 0x9d
#undef ALPHA
#define ALPHA 0x9d
#undef LOD
#define LOD 0xaa
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x3f
#undef GRN
#define GRN 0x3f
#undef BLU
#define BLU 0x3f
#undef ALPHA
#define ALPHA 0x3f
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 0 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x0
#undef GRN
#define GRN 0x0
#undef BLU
#define BLU 0x0
#undef ALPHA
#define ALPHA 0x0
#undef LOD
#define LOD 0x38
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x1
#undef GRN
#define GRN 0x1
#undef BLU
#define BLU 0x1
#undef ALPHA
#define ALPHA 0x1
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 1 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x1b
#undef GRN
#define GRN 0x1b
#undef BLU
#define BLU 0x1b
#undef ALPHA
#define ALPHA 0x1b
#undef LOD
#define LOD 0x0
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x68
#undef GRN
#define GRN 0x68
#undef BLU
#define BLU 0x68
#undef ALPHA
#define ALPHA 0x68
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 2 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xc0
#undef GRN
#define GRN 0xc0
#undef BLU
#define BLU 0xc0
#undef ALPHA
#define ALPHA 0xc0
#undef LOD
#define LOD 0x99
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x6
#undef GRN
#define GRN 0x6
#undef BLU
#define BLU 0x6
#undef ALPHA
#define ALPHA 0x6
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 3 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x5f
#undef GRN
#define GRN 0x5f
#undef BLU
#define BLU 0x5f
#undef ALPHA
#define ALPHA 0x5f
#undef LOD
#define LOD 0x43
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x7
#undef GRN
#define GRN 0x7
#undef BLU
#define BLU 0x7
#undef ALPHA
#define ALPHA 0x7
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 4 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x49
#undef GRN
#define GRN 0x49
#undef BLU
#define BLU 0x49
#undef ALPHA
#define ALPHA 0x49
#undef LOD
#define LOD 0x63
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xd6
#undef GRN
#define GRN 0xd6
#undef BLU
#define BLU 0xd6
#undef ALPHA
#define ALPHA 0xd6
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 5 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xdd
#undef GRN
#define GRN 0xdd
#undef BLU
#define BLU 0xdd
#undef ALPHA
#define ALPHA 0xdd
#undef LOD
#define LOD 0xb1
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x33
#undef GRN
#define GRN 0x33
#undef BLU
#define BLU 0x33
#undef ALPHA
#define ALPHA 0x33
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 6 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xae
#undef GRN
#define GRN 0xae
#undef BLU
#define BLU 0xae
#undef ALPHA
#define ALPHA 0xae
#undef LOD
#define LOD 0xff
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x98
#undef GRN
#define GRN 0x98
#undef BLU
#define BLU 0x98
#undef ALPHA
#define ALPHA 0x98
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 7 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x40
#undef GRN
#define GRN 0x40
#undef BLU
#define BLU 0x40
#undef ALPHA
#define ALPHA 0x40
#undef LOD
#define LOD 0x3f
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x1
#undef GRN
#define GRN 0x1
#undef BLU
#define BLU 0x1
#undef ALPHA
#define ALPHA 0x1
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 8 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x18
#undef GRN
#define GRN 0x18
#undef BLU
#define BLU 0x18
#undef ALPHA
#define ALPHA 0x18
#undef LOD
#define LOD 0xc0
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x45
#undef GRN
#define GRN 0x45
#undef BLU
#define BLU 0x45
#undef ALPHA
#define ALPHA 0x45
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 9 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x78
#undef GRN
#define GRN 0x78
#undef BLU
#define BLU 0x78
#undef ALPHA
#define ALPHA 0x78
#undef LOD
#define LOD 0x8a
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x46
#undef GRN
#define GRN 0x46
#undef BLU
#define BLU 0x46
#undef ALPHA
#define ALPHA 0x46
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 10 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x54
#undef GRN
#define GRN 0x54
#undef BLU
#define BLU 0x54
#undef ALPHA
#define ALPHA 0x54
#undef LOD
#define LOD 0xab
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xe7
#undef GRN
#define GRN 0xe7
#undef BLU
#define BLU 0xe7
#undef ALPHA
#define ALPHA 0xe7
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 11 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x40
#undef GRN
#define GRN 0x40
#undef BLU
#define BLU 0x40
#undef ALPHA
#define ALPHA 0x40
#undef LOD
#define LOD 0xf
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xc
#undef GRN
#define GRN 0xc
#undef BLU
#define BLU 0xc
#undef ALPHA
#define ALPHA 0xc
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 12 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xa6
#undef GRN
#define GRN 0xa6
#undef BLU
#define BLU 0xa6
#undef ALPHA
#define ALPHA 0xa6
#undef LOD
#define LOD 0xc7
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x55
#undef GRN
#define GRN 0x55
#undef BLU
#define BLU 0x55
#undef ALPHA
#define ALPHA 0x55
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 13 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xfb
#undef GRN
#define GRN 0xfb
#undef BLU
#define BLU 0xfb
#undef ALPHA
#define ALPHA 0xfb
#undef LOD
#define LOD 0x40
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x6b
#undef GRN
#define GRN 0x6b
#undef BLU
#define BLU 0x6b
#undef ALPHA
#define ALPHA 0x6b
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 14 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xe8
#undef GRN
#define GRN 0xe8
#undef BLU
#define BLU 0xe8
#undef ALPHA
#define ALPHA 0xe8
#undef LOD
#define LOD 0x38
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xc1
#undef GRN
#define GRN 0xc1
#undef BLU
#define BLU 0xc1
#undef ALPHA
#define ALPHA 0xc1
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 15 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+1*HEIGHT+1*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x1b
#undef GRN
#define GRN 0x1b
#undef BLU
#define BLU 0x1b
#undef ALPHA
#define ALPHA 0x1b
#undef LOD
#define LOD 0xd8
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x6d
#undef GRN
#define GRN 0x6d
#undef BLU
#define BLU 0x6d
#undef ALPHA
#define ALPHA 0x6d
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 16 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xb7
#undef GRN
#define GRN 0xb7
#undef BLU
#define BLU 0xb7
#undef ALPHA
#define ALPHA 0xb7
#undef LOD
#define LOD 0x9b
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xce
#undef GRN
#define GRN 0xce
#undef BLU
#define BLU 0xce
#undef ALPHA
#define ALPHA 0xce
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 17 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x9e
#undef GRN
#define GRN 0x9e
#undef BLU
#define BLU 0x9e
#undef ALPHA
#define ALPHA 0x9e
#undef LOD
#define LOD 0xbe
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x1b
#undef GRN
#define GRN 0x1b
#undef BLU
#define BLU 0x1b
#undef ALPHA
#define ALPHA 0x1b
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 18 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x68
#undef GRN
#define GRN 0x68
#undef BLU
#define BLU 0x68
#undef ALPHA
#define ALPHA 0x68
#undef LOD
#define LOD 0x2e
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xcd
#undef GRN
#define GRN 0xcd
#undef BLU
#define BLU 0xcd
#undef ALPHA
#define ALPHA 0xcd
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 19 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xb2
#undef GRN
#define GRN 0xb2
#undef BLU
#define BLU 0xb2
#undef ALPHA
#define ALPHA 0xb2
#undef LOD
#define LOD 0x5f
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xbf
#undef GRN
#define GRN 0xbf
#undef BLU
#define BLU 0xbf
#undef ALPHA
#define ALPHA 0xbf
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 20 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x4
#undef GRN
#define GRN 0x4
#undef BLU
#define BLU 0x4
#undef ALPHA
#define ALPHA 0x4
#undef LOD
#define LOD 0x88
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x66
#undef GRN
#define GRN 0x66
#undef BLU
#define BLU 0x66
#undef ALPHA
#define ALPHA 0x66
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 21 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x55
#undef GRN
#define GRN 0x55
#undef BLU
#define BLU 0x55
#undef ALPHA
#define ALPHA 0x55
#undef LOD
#define LOD 0x3f
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xf9
#undef GRN
#define GRN 0xf9
#undef BLU
#define BLU 0xf9
#undef ALPHA
#define ALPHA 0xf9
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 22 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x58
#undef GRN
#define GRN 0x58
#undef BLU
#define BLU 0x58
#undef ALPHA
#define ALPHA 0x58
#undef LOD
#define LOD 0x3
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x40
#undef GRN
#define GRN 0x40
#undef BLU
#define BLU 0x40
#undef ALPHA
#define ALPHA 0x40
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 23 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x1
#undef GRN
#define GRN 0x1
#undef BLU
#define BLU 0x1
#undef ALPHA
#define ALPHA 0x1
#undef LOD
#define LOD 0x48
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x17
#undef GRN
#define GRN 0x17
#undef BLU
#define BLU 0x17
#undef ALPHA
#define ALPHA 0x17
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 24 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xcd
#undef GRN
#define GRN 0xcd
#undef BLU
#define BLU 0xcd
#undef ALPHA
#define ALPHA 0xcd
#undef LOD
#define LOD 0x9
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xb8
#undef GRN
#define GRN 0xb8
#undef BLU
#define BLU 0xb8
#undef ALPHA
#define ALPHA 0xb8
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 25 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x45
#undef GRN
#define GRN 0x45
#undef BLU
#define BLU 0x45
#undef ALPHA
#define ALPHA 0x45
#undef LOD
#define LOD 0xb
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x74
#undef GRN
#define GRN 0x74
#undef BLU
#define BLU 0x74
#undef ALPHA
#define ALPHA 0x74
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 26 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xe4
#undef GRN
#define GRN 0xe4
#undef BLU
#define BLU 0xe4
#undef ALPHA
#define ALPHA 0xe4
#undef LOD
#define LOD 0xf4
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x68
#undef GRN
#define GRN 0x68
#undef BLU
#define BLU 0x68
#undef ALPHA
#define ALPHA 0x68
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 27 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xc4
#undef GRN
#define GRN 0xc4
#undef BLU
#define BLU 0xc4
#undef ALPHA
#define ALPHA 0xc4
#undef LOD
#define LOD 0x99
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x6a
#undef GRN
#define GRN 0x6a
#undef BLU
#define BLU 0x6a
#undef ALPHA
#define ALPHA 0x6a
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 28 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xff
#undef GRN
#define GRN 0xff
#undef BLU
#define BLU 0xff
#undef ALPHA
#define ALPHA 0xff
#undef LOD
#define LOD 0x78
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x6
#undef GRN
#define GRN 0x6
#undef BLU
#define BLU 0x6
#undef ALPHA
#define ALPHA 0x6
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 29 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x53
#undef GRN
#define GRN 0x53
#undef BLU
#define BLU 0x53
#undef ALPHA
#define ALPHA 0x53
#undef LOD
#define LOD 0x3
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xa8
#undef GRN
#define GRN 0xa8
#undef BLU
#define BLU 0xa8
#undef ALPHA
#define ALPHA 0xa8
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 30 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xc1
#undef GRN
#define GRN 0xc1
#undef BLU
#define BLU 0xc1
#undef ALPHA
#define ALPHA 0xc1
#undef LOD
#define LOD 0x21
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x15
#undef GRN
#define GRN 0x15
#undef BLU
#define BLU 0x15
#undef ALPHA
#define ALPHA 0x15
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 31 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+2*HEIGHT+2*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xf4
#undef GRN
#define GRN 0xf4
#undef BLU
#define BLU 0xf4
#undef ALPHA
#define ALPHA 0xf4
#undef LOD
#define LOD 0x48
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xef
#undef GRN
#define GRN 0xef
#undef BLU
#define BLU 0xef
#undef ALPHA
#define ALPHA 0xef
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 32 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x8d
#undef GRN
#define GRN 0x8d
#undef BLU
#define BLU 0x8d
#undef ALPHA
#define ALPHA 0x8d
#undef LOD
#define LOD 0x6a
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xba
#undef GRN
#define GRN 0xba
#undef BLU
#define BLU 0xba
#undef ALPHA
#define ALPHA 0xba
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 33 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x78
#undef GRN
#define GRN 0x78
#undef BLU
#define BLU 0x78
#undef ALPHA
#define ALPHA 0x78
#undef LOD
#define LOD 0xca
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x45
#undef GRN
#define GRN 0x45
#undef BLU
#define BLU 0x45
#undef ALPHA
#define ALPHA 0x45
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 34 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x7c
#undef GRN
#define GRN 0x7c
#undef BLU
#define BLU 0x7c
#undef ALPHA
#define ALPHA 0x7c
#undef LOD
#define LOD 0xaa
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x27
#undef GRN
#define GRN 0x27
#undef BLU
#define BLU 0x27
#undef ALPHA
#define ALPHA 0x27
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 35 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x40
#undef GRN
#define GRN 0x40
#undef BLU
#define BLU 0x40
#undef ALPHA
#define ALPHA 0x40
#undef LOD
#define LOD 0x97
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x6
#undef GRN
#define GRN 0x6
#undef BLU
#define BLU 0x6
#undef ALPHA
#define ALPHA 0x6
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 36 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x59
#undef GRN
#define GRN 0x59
#undef BLU
#define BLU 0x59
#undef ALPHA
#define ALPHA 0x59
#undef LOD
#define LOD 0xc3
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5d
#undef GRN
#define GRN 0x5d
#undef BLU
#define BLU 0x5d
#undef ALPHA
#define ALPHA 0x5d
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 37 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x86
#undef GRN
#define GRN 0x86
#undef BLU
#define BLU 0x86
#undef ALPHA
#define ALPHA 0x86
#undef LOD
#define LOD 0x5c
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5c
#undef GRN
#define GRN 0x5c
#undef BLU
#define BLU 0x5c
#undef ALPHA
#define ALPHA 0x5c
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 38 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x6d
#undef GRN
#define GRN 0x6d
#undef BLU
#define BLU 0x6d
#undef ALPHA
#define ALPHA 0x6d
#undef LOD
#define LOD 0x69
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5c
#undef GRN
#define GRN 0x5c
#undef BLU
#define BLU 0x5c
#undef ALPHA
#define ALPHA 0x5c
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 39 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x32
#undef GRN
#define GRN 0x32
#undef BLU
#define BLU 0x32
#undef ALPHA
#define ALPHA 0x32
#undef LOD
#define LOD 0x27
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5c
#undef GRN
#define GRN 0x5c
#undef BLU
#define BLU 0x5c
#undef ALPHA
#define ALPHA 0x5c
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 40 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x32
#undef GRN
#define GRN 0x32
#undef BLU
#define BLU 0x32
#undef ALPHA
#define ALPHA 0x32
#undef LOD
#define LOD 0x25
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5c
#undef GRN
#define GRN 0x5c
#undef BLU
#define BLU 0x5c
#undef ALPHA
#define ALPHA 0x5c
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 41 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x6a
#undef GRN
#define GRN 0x6a
#undef BLU
#define BLU 0x6a
#undef ALPHA
#define ALPHA 0x6a
#undef LOD
#define LOD 0x52
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5c
#undef GRN
#define GRN 0x5c
#undef BLU
#define BLU 0x5c
#undef ALPHA
#define ALPHA 0x5c
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 42 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x65
#undef GRN
#define GRN 0x65
#undef BLU
#define BLU 0x65
#undef ALPHA
#define ALPHA 0x65
#undef LOD
#define LOD 0x4a
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5c
#undef GRN
#define GRN 0x5c
#undef BLU
#define BLU 0x5c
#undef ALPHA
#define ALPHA 0x5c
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 43 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x96
#undef GRN
#define GRN 0x96
#undef BLU
#define BLU 0x96
#undef ALPHA
#define ALPHA 0x96
#undef LOD
#define LOD 0xe5
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5c
#undef GRN
#define GRN 0x5c
#undef BLU
#define BLU 0x5c
#undef ALPHA
#define ALPHA 0x5c
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 44 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xa9
#undef GRN
#define GRN 0xa9
#undef BLU
#define BLU 0xa9
#undef ALPHA
#define ALPHA 0xa9
#undef LOD
#define LOD 0xd9
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5c
#undef GRN
#define GRN 0x5c
#undef BLU
#define BLU 0x5c
#undef ALPHA
#define ALPHA 0x5c
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 45 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xd
#undef GRN
#define GRN 0xd
#undef BLU
#define BLU 0xd
#undef ALPHA
#define ALPHA 0xd
#undef LOD
#define LOD 0x1d
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5c
#undef GRN
#define GRN 0x5c
#undef BLU
#define BLU 0x5c
#undef ALPHA
#define ALPHA 0x5c
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 46 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xb2
#undef GRN
#define GRN 0xb2
#undef BLU
#define BLU 0xb2
#undef ALPHA
#define ALPHA 0xb2
#undef LOD
#define LOD 0x4a
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x71
#undef GRN
#define GRN 0x71
#undef BLU
#define BLU 0x71
#undef ALPHA
#define ALPHA 0x71
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 47 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+3*HEIGHT+3*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x49
#undef GRN
#define GRN 0x49
#undef BLU
#define BLU 0x49
#undef ALPHA
#define ALPHA 0x49
#undef LOD
#define LOD 0xad
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xf
#undef GRN
#define GRN 0xf
#undef BLU
#define BLU 0xf
#undef ALPHA
#define ALPHA 0xf
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 48 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xf6
#undef GRN
#define GRN 0xf6
#undef BLU
#define BLU 0xf6
#undef ALPHA
#define ALPHA 0xf6
#undef LOD
#define LOD 0xf2
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x8
#undef GRN
#define GRN 0x8
#undef BLU
#define BLU 0x8
#undef ALPHA
#define ALPHA 0x8
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 49 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x41
#undef GRN
#define GRN 0x41
#undef BLU
#define BLU 0x41
#undef ALPHA
#define ALPHA 0x41
#undef LOD
#define LOD 0x5d
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x9
#undef GRN
#define GRN 0x9
#undef BLU
#define BLU 0x9
#undef ALPHA
#define ALPHA 0x9
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 50 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xb2
#undef GRN
#define GRN 0xb2
#undef BLU
#define BLU 0xb2
#undef ALPHA
#define ALPHA 0xb2
#undef LOD
#define LOD 0xf5
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xa
#undef GRN
#define GRN 0xa
#undef BLU
#define BLU 0xa
#undef ALPHA
#define ALPHA 0xa
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 51 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x40
#undef GRN
#define GRN 0x40
#undef BLU
#define BLU 0x40
#undef ALPHA
#define ALPHA 0x40
#undef LOD
#define LOD 0xa
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xf5
#undef GRN
#define GRN 0xf5
#undef BLU
#define BLU 0xf5
#undef ALPHA
#define ALPHA 0xf5
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 52 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xa2
#undef GRN
#define GRN 0xa2
#undef BLU
#define BLU 0xa2
#undef ALPHA
#define ALPHA 0xa2
#undef LOD
#define LOD 0xf5
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x4a
#undef GRN
#define GRN 0x4a
#undef BLU
#define BLU 0x4a
#undef ALPHA
#define ALPHA 0x4a
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 53 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x44
#undef GRN
#define GRN 0x44
#undef BLU
#define BLU 0x44
#undef ALPHA
#define ALPHA 0x44
#undef LOD
#define LOD 0xa
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xb5
#undef GRN
#define GRN 0xb5
#undef BLU
#define BLU 0xb5
#undef ALPHA
#define ALPHA 0xb5
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 54 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xaa
#undef GRN
#define GRN 0xaa
#undef BLU
#define BLU 0xaa
#undef ALPHA
#define ALPHA 0xaa
#undef LOD
#define LOD 0xf5
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x4a
#undef GRN
#define GRN 0x4a
#undef BLU
#define BLU 0x4a
#undef ALPHA
#define ALPHA 0x4a
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 55 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x4a
#undef GRN
#define GRN 0x4a
#undef BLU
#define BLU 0x4a
#undef ALPHA
#define ALPHA 0x4a
#undef LOD
#define LOD 0xa
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xf5
#undef GRN
#define GRN 0xf5
#undef BLU
#define BLU 0xf5
#undef ALPHA
#define ALPHA 0xf5
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 56 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xaa
#undef GRN
#define GRN 0xaa
#undef BLU
#define BLU 0xaa
#undef ALPHA
#define ALPHA 0xaa
#undef LOD
#define LOD 0xf5
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xa
#undef GRN
#define GRN 0xa
#undef BLU
#define BLU 0xa
#undef ALPHA
#define ALPHA 0xa
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 57 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x47
#undef GRN
#define GRN 0x47
#undef BLU
#define BLU 0x47
#undef ALPHA
#define ALPHA 0x47
#undef LOD
#define LOD 0xa
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xb5
#undef GRN
#define GRN 0xb5
#undef BLU
#define BLU 0xb5
#undef ALPHA
#define ALPHA 0xb5
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 58 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xa6
#undef GRN
#define GRN 0xa6
#undef BLU
#define BLU 0xa6
#undef ALPHA
#define ALPHA 0xa6
#undef LOD
#define LOD 0xf5
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xa
#undef GRN
#define GRN 0xa
#undef BLU
#define BLU 0xa
#undef ALPHA
#define ALPHA 0xa
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 59 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x4a
#undef GRN
#define GRN 0x4a
#undef BLU
#define BLU 0x4a
#undef ALPHA
#define ALPHA 0x4a
#undef LOD
#define LOD 0xa
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xb5
#undef GRN
#define GRN 0xb5
#undef BLU
#define BLU 0xb5
#undef ALPHA
#define ALPHA 0xb5
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 60 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xb2
#undef GRN
#define GRN 0xb2
#undef BLU
#define BLU 0xb2
#undef ALPHA
#define ALPHA 0xb2
#undef LOD
#define LOD 0xf5
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xa
#undef GRN
#define GRN 0xa
#undef BLU
#define BLU 0xa
#undef ALPHA
#define ALPHA 0xa
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 61 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x50
#undef GRN
#define GRN 0x50
#undef BLU
#define BLU 0x50
#undef ALPHA
#define ALPHA 0x50
#undef LOD
#define LOD 0x42
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x25
#undef GRN
#define GRN 0x25
#undef BLU
#define BLU 0x25
#undef ALPHA
#define ALPHA 0x25
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 62 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x6c
#undef GRN
#define GRN 0x6c
#undef BLU
#define BLU 0x6c
#undef ALPHA
#define ALPHA 0x6c
#undef LOD
#define LOD 0x65
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x25
#undef GRN
#define GRN 0x25
#undef BLU
#define BLU 0x25
#undef ALPHA
#define ALPHA 0x25
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 63 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+4*HEIGHT+4*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x92
#undef GRN
#define GRN 0x92
#undef BLU
#define BLU 0x92
#undef ALPHA
#define ALPHA 0x92
#undef LOD
#define LOD 0x9a
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5a
#undef GRN
#define GRN 0x5a
#undef BLU
#define BLU 0x5a
#undef ALPHA
#define ALPHA 0x5a
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 64 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x6a
#undef GRN
#define GRN 0x6a
#undef BLU
#define BLU 0x6a
#undef ALPHA
#define ALPHA 0x6a
#undef LOD
#define LOD 0xe5
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x66
#undef GRN
#define GRN 0x66
#undef BLU
#define BLU 0x66
#undef ALPHA
#define ALPHA 0x66
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 65 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x87
#undef GRN
#define GRN 0x87
#undef BLU
#define BLU 0x87
#undef ALPHA
#define ALPHA 0x87
#undef LOD
#define LOD 0x5a
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x69
#undef GRN
#define GRN 0x69
#undef BLU
#define BLU 0x69
#undef ALPHA
#define ALPHA 0x69
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 66 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xb1
#undef GRN
#define GRN 0xb1
#undef BLU
#define BLU 0xb1
#undef ALPHA
#define ALPHA 0xb1
#undef LOD
#define LOD 0x65
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x69
#undef GRN
#define GRN 0x69
#undef BLU
#define BLU 0x69
#undef ALPHA
#define ALPHA 0x69
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 67 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x4e
#undef GRN
#define GRN 0x4e
#undef BLU
#define BLU 0x4e
#undef ALPHA
#define ALPHA 0x4e
#undef LOD
#define LOD 0x52
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x67
#undef GRN
#define GRN 0x67
#undef BLU
#define BLU 0x67
#undef ALPHA
#define ALPHA 0x67
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 68 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x91
#undef GRN
#define GRN 0x91
#undef BLU
#define BLU 0x91
#undef ALPHA
#define ALPHA 0x91
#undef LOD
#define LOD 0x8d
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xdc
#undef GRN
#define GRN 0xdc
#undef BLU
#define BLU 0xdc
#undef ALPHA
#define ALPHA 0xdc
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 69 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x4e
#undef GRN
#define GRN 0x4e
#undef BLU
#define BLU 0x4e
#undef ALPHA
#define ALPHA 0x4e
#undef LOD
#define LOD 0xd2
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5f
#undef GRN
#define GRN 0x5f
#undef BLU
#define BLU 0x5f
#undef ALPHA
#define ALPHA 0x5f
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 70 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xf1
#undef GRN
#define GRN 0xf1
#undef BLU
#define BLU 0xf1
#undef ALPHA
#define ALPHA 0xf1
#undef LOD
#define LOD 0x39
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xa0
#undef GRN
#define GRN 0xa0
#undef BLU
#define BLU 0xa0
#undef ALPHA
#define ALPHA 0xa0
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 71 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x8e
#undef GRN
#define GRN 0x8e
#undef BLU
#define BLU 0x8e
#undef ALPHA
#define ALPHA 0x8e
#undef LOD
#define LOD 0x92
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5f
#undef GRN
#define GRN 0x5f
#undef BLU
#define BLU 0x5f
#undef ALPHA
#define ALPHA 0x5f
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 72 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x7d
#undef GRN
#define GRN 0x7d
#undef BLU
#define BLU 0x7d
#undef ALPHA
#define ALPHA 0x7d
#undef LOD
#define LOD 0xcb
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xa0
#undef GRN
#define GRN 0xa0
#undef BLU
#define BLU 0xa0
#undef ALPHA
#define ALPHA 0xa0
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 73 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xca
#undef GRN
#define GRN 0xca
#undef BLU
#define BLU 0xca
#undef ALPHA
#define ALPHA 0xca
#undef LOD
#define LOD 0x1d
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5f
#undef GRN
#define GRN 0x5f
#undef BLU
#define BLU 0x5f
#undef ALPHA
#define ALPHA 0x5f
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 74 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x15
#undef GRN
#define GRN 0x15
#undef BLU
#define BLU 0x15
#undef ALPHA
#define ALPHA 0x15
#undef LOD
#define LOD 0xb1
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xa0
#undef GRN
#define GRN 0xa0
#undef BLU
#define BLU 0xa0
#undef ALPHA
#define ALPHA 0xa0
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 75 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xea
#undef GRN
#define GRN 0xea
#undef BLU
#define BLU 0xea
#undef ALPHA
#define ALPHA 0xea
#undef LOD
#define LOD 0x4e
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x5e
#undef GRN
#define GRN 0x5e
#undef BLU
#define BLU 0x5e
#undef ALPHA
#define ALPHA 0x5e
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 76 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x15
#undef GRN
#define GRN 0x15
#undef BLU
#define BLU 0x15
#undef ALPHA
#define ALPHA 0x15
#undef LOD
#define LOD 0xb1
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x41
#undef GRN
#define GRN 0x41
#undef BLU
#define BLU 0x41
#undef ALPHA
#define ALPHA 0x41
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 77 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xea
#undef GRN
#define GRN 0xea
#undef BLU
#define BLU 0xea
#undef ALPHA
#define ALPHA 0xea
#undef LOD
#define LOD 0x4e
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xcf
#undef GRN
#define GRN 0xcf
#undef BLU
#define BLU 0xcf
#undef ALPHA
#define ALPHA 0xcf
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 78 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x15
#undef GRN
#define GRN 0x15
#undef BLU
#define BLU 0x15
#undef ALPHA
#define ALPHA 0x15
#undef LOD
#define LOD 0xb1
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xf0
#undef GRN
#define GRN 0xf0
#undef BLU
#define BLU 0xf0
#undef ALPHA
#define ALPHA 0xf0
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 79 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+5*HEIGHT+5*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x6a
#undef GRN
#define GRN 0x6a
#undef BLU
#define BLU 0x6a
#undef ALPHA
#define ALPHA 0x6a
#undef LOD
#define LOD 0x4e
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xde
#undef GRN
#define GRN 0xde
#undef BLU
#define BLU 0xde
#undef ALPHA
#define ALPHA 0xde
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 80 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x15
#undef GRN
#define GRN 0x15
#undef BLU
#define BLU 0x15
#undef ALPHA
#define ALPHA 0x15
#undef LOD
#define LOD 0xb1
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x11
#undef GRN
#define GRN 0x11
#undef BLU
#define BLU 0x11
#undef ALPHA
#define ALPHA 0x11
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 81 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x6a
#undef GRN
#define GRN 0x6a
#undef BLU
#define BLU 0x6a
#undef ALPHA
#define ALPHA 0x6a
#undef LOD
#define LOD 0x4e
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xef
#undef GRN
#define GRN 0xef
#undef BLU
#define BLU 0xef
#undef ALPHA
#define ALPHA 0xef
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 82 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x95
#undef GRN
#define GRN 0x95
#undef BLU
#define BLU 0x95
#undef ALPHA
#define ALPHA 0x95
#undef LOD
#define LOD 0xb1
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x98
#undef GRN
#define GRN 0x98
#undef BLU
#define BLU 0x98
#undef ALPHA
#define ALPHA 0x98
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 83 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x6b
#undef GRN
#define GRN 0x6b
#undef BLU
#define BLU 0x6b
#undef ALPHA
#define ALPHA 0x6b
#undef LOD
#define LOD 0x83
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x67
#undef GRN
#define GRN 0x67
#undef BLU
#define BLU 0x67
#undef ALPHA
#define ALPHA 0x67
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 84 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x90
#undef GRN
#define GRN 0x90
#undef BLU
#define BLU 0x90
#undef ALPHA
#define ALPHA 0x90
#undef LOD
#define LOD 0x81
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x98
#undef GRN
#define GRN 0x98
#undef BLU
#define BLU 0x98
#undef ALPHA
#define ALPHA 0x98
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 85 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x6f
#undef GRN
#define GRN 0x6f
#undef BLU
#define BLU 0x6f
#undef ALPHA
#define ALPHA 0x6f
#undef LOD
#define LOD 0x7f
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x77
#undef GRN
#define GRN 0x77
#undef BLU
#define BLU 0x77
#undef ALPHA
#define ALPHA 0x77
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 86 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x90
#undef GRN
#define GRN 0x90
#undef BLU
#define BLU 0x90
#undef ALPHA
#define ALPHA 0x90
#undef LOD
#define LOD 0x80
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x80
#undef GRN
#define GRN 0x80
#undef BLU
#define BLU 0x80
#undef ALPHA
#define ALPHA 0x80
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 87 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x6f
#undef GRN
#define GRN 0x6f
#undef BLU
#define BLU 0x6f
#undef ALPHA
#define ALPHA 0x6f
#undef LOD
#define LOD 0x7e
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x67
#undef GRN
#define GRN 0x67
#undef BLU
#define BLU 0x67
#undef ALPHA
#define ALPHA 0x67
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 88 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x90
#undef GRN
#define GRN 0x90
#undef BLU
#define BLU 0x90
#undef ALPHA
#define ALPHA 0x90
#undef LOD
#define LOD 0x80
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x90
#undef GRN
#define GRN 0x90
#undef BLU
#define BLU 0x90
#undef ALPHA
#define ALPHA 0x90
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 89 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x6f
#undef GRN
#define GRN 0x6f
#undef BLU
#define BLU 0x6f
#undef ALPHA
#define ALPHA 0x6f
#undef LOD
#define LOD 0x7d
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x67
#undef GRN
#define GRN 0x67
#undef BLU
#define BLU 0x67
#undef ALPHA
#define ALPHA 0x67
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 90 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x90
#undef GRN
#define GRN 0x90
#undef BLU
#define BLU 0x90
#undef ALPHA
#define ALPHA 0x90
#undef LOD
#define LOD 0x80
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x80
#undef GRN
#define GRN 0x80
#undef BLU
#define BLU 0x80
#undef ALPHA
#define ALPHA 0x80
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 91 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x6f
#undef GRN
#define GRN 0x6f
#undef BLU
#define BLU 0x6f
#undef ALPHA
#define ALPHA 0x6f
#undef LOD
#define LOD 0x6e
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xc7
#undef GRN
#define GRN 0xc7
#undef BLU
#define BLU 0xc7
#undef ALPHA
#define ALPHA 0xc7
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 92 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x90
#undef GRN
#define GRN 0x90
#undef BLU
#define BLU 0x90
#undef ALPHA
#define ALPHA 0x90
#undef LOD
#define LOD 0x91
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x38
#undef GRN
#define GRN 0x38
#undef BLU
#define BLU 0x38
#undef ALPHA
#define ALPHA 0x38
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 93 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x6f
#undef GRN
#define GRN 0x6f
#undef BLU
#define BLU 0x6f
#undef ALPHA
#define ALPHA 0x6f
#undef LOD
#define LOD 0x7e
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xc7
#undef GRN
#define GRN 0xc7
#undef BLU
#define BLU 0xc7
#undef ALPHA
#define ALPHA 0xc7
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 94 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x90
#undef GRN
#define GRN 0x90
#undef BLU
#define BLU 0x90
#undef ALPHA
#define ALPHA 0x90
#undef LOD
#define LOD 0xc3
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xc5
#undef GRN
#define GRN 0xc5
#undef BLU
#define BLU 0xc5
#undef ALPHA
#define ALPHA 0xc5
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 95 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+6*HEIGHT+6*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x6f
#undef GRN
#define GRN 0x6f
#undef BLU
#define BLU 0x6f
#undef ALPHA
#define ALPHA 0x6f
#undef LOD
#define LOD 0x3d
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xc7
#undef GRN
#define GRN 0xc7
#undef BLU
#define BLU 0xc7
#undef ALPHA
#define ALPHA 0xc7
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 96 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xb0
#undef GRN
#define GRN 0xb0
#undef BLU
#define BLU 0xb0
#undef ALPHA
#define ALPHA 0xb0
#undef LOD
#define LOD 0xdb
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xc7
#undef GRN
#define GRN 0xc7
#undef BLU
#define BLU 0xc7
#undef ALPHA
#define ALPHA 0xc7
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 97 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x4f
#undef GRN
#define GRN 0x4f
#undef BLU
#define BLU 0x4f
#undef ALPHA
#define ALPHA 0x4f
#undef LOD
#define LOD 0xf7
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xc7
#undef GRN
#define GRN 0xc7
#undef BLU
#define BLU 0xc7
#undef ALPHA
#define ALPHA 0xc7
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 98 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x9b
#undef GRN
#define GRN 0x9b
#undef BLU
#define BLU 0x9b
#undef ALPHA
#define ALPHA 0x9b
#undef LOD
#define LOD 0x18
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xb8
#undef GRN
#define GRN 0xb8
#undef BLU
#define BLU 0xb8
#undef ALPHA
#define ALPHA 0xb8
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 99 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x55
#undef GRN
#define GRN 0x55
#undef BLU
#define BLU 0x55
#undef ALPHA
#define ALPHA 0x55
#undef LOD
#define LOD 0xff
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x37
#undef GRN
#define GRN 0x37
#undef BLU
#define BLU 0x37
#undef ALPHA
#define ALPHA 0x37
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 100 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xad
#undef GRN
#define GRN 0xad
#undef BLU
#define BLU 0xad
#undef ALPHA
#define ALPHA 0xad
#undef LOD
#define LOD 0x18
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xd8
#undef GRN
#define GRN 0xd8
#undef BLU
#define BLU 0xd8
#undef ALPHA
#define ALPHA 0xd8
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 101 << 5, 0, 0, 0),

	/* "rough" booth multiply coverage */

#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x0
#undef GRN
#define GRN 0x0
#undef BLU
#define BLU 0x0
#undef ALPHA
#define ALPHA 0x0
#undef LOD
#define LOD 0xff
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x40
#undef GRN
#define GRN 0x80
#undef BLU
#define BLU 0xc0
#undef ALPHA
#define ALPHA 0xf0
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 126 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
#undef RED
#define RED 0x0
#undef GRN
#define GRN 0x0
#undef BLU
#define BLU 0x0
#undef ALPHA
#define ALPHA 0x0
#undef LOD
#define LOD 0xff
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x0
#undef GRN
#define GRN 0x0
#undef BLU
#define BLU 0x0
#undef ALPHA
#define ALPHA 0x0
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 127 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xff
#undef GRN
#define GRN 0xff
#undef BLU
#define BLU 0xff
#undef ALPHA
#define ALPHA 0xff
#undef LOD
#define LOD 0xff
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0x0
#undef GRN
#define GRN 0x0
#undef BLU
#define BLU 0x0
#undef ALPHA
#define ALPHA 0x0
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 126 << 5, 0, 0, 0),

#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
#undef RED
#define RED 0xff
#undef GRN
#define GRN 0xff
#undef BLU
#define BLU 0xff
#undef ALPHA
#define ALPHA 0xff
#undef LOD
#define LOD 0xff
	gsDPSetPrimColor (MINL, LOD, RED, GRN, BLU, ALPHA),
#undef RED
#define RED 0xf0
#undef GRN
#define GRN 0x40
#undef BLU
#define BLU 0x80
#undef ALPHA
#define ALPHA 0xc0
	gsDPSetEnvColor (RED, GRN, BLU, ALPHA),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
		 127 << 5, 0, 0, 0),

	/* chromakey coverage */

	/* CC pattern	1	6	6X	31	7	7	7	7 */
#undef RED
#define RED 0x42
#undef GRN
#define GRN 0xaa
#undef BLU
#define BLU 0xf8
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
#undef BL_OP1
#define BL_OP1    IM_RD | CVG_DST_WRAP | CVG_X_ALPHA |       \
			FORCE_BL | ZMODE_OPA |                    \
			GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_FOG, G_BL_1)
#undef BL_OP2
#define BL_OP2    IM_RD | CVG_DST_WRAP | CVG_X_ALPHA |       \
			FORCE_BL | ZMODE_OPA |                    \
			GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_FOG, G_BL_1)
	gsDPSetRenderMode(BL_OP1, BL_OP2),
	gsDPSetFogColor (0x0, 0x0, 0x0, 0x0),
    gsDPSetCombineKey (G_CK_KEY),
#undef CC_OP
#define CC_OP	TEXEL0, CENTER, SCALE, 0, 0, 0, 0, 0
    gsDPSetCombineMode (CC_OP, CC_OP),
    gsDPSetKeyGB (0xaa, 0xc7, 0xfff, 0xfd, 0xe7, 0xfff),

	/* trial red 0 */
#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+7*HEIGHT+7*4)
	gsDPPipeSync(),
    gsDPSetKeyR (RED - 0x1, 0x1, 0x7),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial red 1 */
#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
    gsDPSetKeyR (RED + 0x1, 0x2, 0xb),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial red 2 */
#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
    gsDPSetKeyR (RED - 0x1, 0x5, 0xd),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial red 3 */
#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
    gsDPSetKeyR (RED + 0x1, 0x9, 0xe),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial red 4 */
#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
    gsDPSetKeyR (RED - 0x1, 0x11, 0x11),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial red 5 */
#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
    gsDPSetKeyR (RED + 0x1, 0x21, 0x20),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial red 6 */
#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
    gsDPSetKeyR (RED - 0x1, 0x41, 0x18),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial red 7 */
#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
    gsDPSetKeyR (RED + 0x1, 0x81, 0xf),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial red 8 */
#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
    gsDPSetKeyR (RED - 0x2, 0x81, 0x22),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial red 9 */
#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
    gsDPSetKeyR (RED + 0x4, 0x81, 0x1e),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial red 10 */
#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
	/*
    gsDPSetKeyR (RED - 0x8, 0x81, 0x4a),
    gsDPSetKeyR (RED - 0x9, 0x72, 0x4a),
	*/
    gsDPSetKeyR (RED - 0x7, 0x93, 0x4a),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/*
	gsDPPipeSync(),
    gsDPSetKeyR (0x0, 0x82, 0x50),
    gsDPSetKeyR (0x0, 0x81, 0x50),
    gsDPSetKeyR (0x0, 0x80, 0x50),
    gsDPSetKeyR (0x0, 0x81, 0x50),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*0, 4*0, 4*0 + 4*100 - 4,
		 4*0 + 4*100 - 4, G_TX_RENDERTILE,
 		 105 << 5, 0, 0, 0),
	*/

	/* trial red 11 */
#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
    gsDPSetKeyR (RED + 0x10, 0x81, 0x85),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial red 12 */
#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
    gsDPSetKeyR (RED - 0x20, 0x81, 0x10c),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial red 13 */
#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
    gsDPSetKeyR (RED + 0x40, 0x81, 0x206),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial red 14 */
#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
    gsDPSetKeyR (RED + 0x80, 0x81, 0x40d),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 103 << 5, 0, 0, 0),

	/* trial red 15 */
#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
    gsDPSetKeyR (0xf9, 0xfd, 0xf32),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 104 << 5, 0, 0, 0),

	/* trial grn 0 */
#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+8*HEIGHT+8*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN - 0x1, 0x1, 0x7, BLU - 0x1, 0x1, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial grn 1 */
#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN + 0x1, 0x2, 0xb, BLU + 0x1, 0x2, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial grn 2 */
#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN - 0x1, 0x5, 0xd, BLU - 0x1, 0x5, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial grn 3 */
#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN + 0x1, 0x9, 0xe, BLU + 0x1, 0x9, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial grn 4 */
#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN - 0x1, 0x11, 0x11, BLU - 0x1, 0x11, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial grn 5 */
#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN + 0x1, 0x21, 0x20, BLU + 0x1, 0x21, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial grn 6 */
#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN - 0x1, 0x41, 0x18, BLU - 0x1, 0x41, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial grn 7 */
#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN + 0x1, 0x81, 0xf, BLU + 0x1, 0x81, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial grn 8 */
#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN - 0x2, 0x81, 0x22, BLU - 0x1, 0x81, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial grn 9 */
#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN + 0x4, 0x81, 0x1e, BLU + 0x4, 0x81, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial grn 10 */
#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN - 0x7, 0x93, 0x4a, BLU - 0x7, 0x93, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial grn 11 */
#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN + 0x10, 0x81, 0x85, BLU + 0x10, 0x81, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial grn 12 */
#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN - 0x20, 0x81, 0x10c, BLU - 0x20, 0x81, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial grn 13 */
#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN + 0x40, 0x81, 0x206, BLU + 0x40, 0x81, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial grn 14 */
#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (0x5f + 0x80, 0x81, 0x40d, 0x7f + 0x80, 0x81, 0xfff),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 103 << 5, 0, 0, 0),

	/* trial grn 15 */
#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (0xfd, 0xfd, 0xf32, 0xff, 0xfd, 0xfff),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 104 << 5, 0, 0, 0),

	/* trial blu 0 */
#undef XOFF
#define XOFF (X0+0*WIDTH+0*4)
#undef YOFF
#define YOFF (Y0+9*HEIGHT+9*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN - 0x1, 0x1, 0xfff, BLU - 0x1, 0x1, 0x7),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial blu 1 */
#undef XOFF
#define XOFF (X0+1*WIDTH+1*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN + 0x1, 0x2, 0xfff, BLU + 0x1, 0x2, 0xb),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial blu 2 */
#undef XOFF
#define XOFF (X0+2*WIDTH+2*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN - 0x1, 0x5, 0xfff, BLU - 0x1, 0x5, 0xd),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial blu 3 */
#undef XOFF
#define XOFF (X0+3*WIDTH+3*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN + 0x1, 0x9, 0xfff, BLU + 0x1, 0x9, 0xe),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial blu 4 */
#undef XOFF
#define XOFF (X0+4*WIDTH+4*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN - 0x1, 0x11, 0xfff, BLU - 0x1, 0x11, 0x11),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial blu 5 */
#undef XOFF
#define XOFF (X0+5*WIDTH+5*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN + 0x1, 0x21, 0xfff, BLU + 0x1, 0x21, 0x20),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial blu 6 */
#undef XOFF
#define XOFF (X0+6*WIDTH+6*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN - 0x1, 0x41, 0xfff, BLU - 0x1, 0x41, 0x18),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial blu 7 */
#undef XOFF
#define XOFF (X0+7*WIDTH+7*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN + 0x1, 0x81, 0xfff, BLU + 0x1, 0x81, 0xf),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial blu 8 */
#undef XOFF
#define XOFF (X0+8*WIDTH+8*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN - 0x2, 0x81, 0xfff, BLU - 0x2, 0x81, 0x22),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial blu 9 */
#undef XOFF
#define XOFF (X0+9*WIDTH+9*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN + 0x4, 0x81, 0xfff, BLU + 0x4, 0x81, 0x1e),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial blu 10 */
#undef XOFF
#define XOFF (X0+10*WIDTH+10*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN - 0x7, 0x93, 0xfff, BLU - 0x7, 0x93, 0x4a),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial blu 11 */
#undef XOFF
#define XOFF (X0+11*WIDTH+11*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN + 0x10, 0x81, 0xfff, BLU - 0x10, 0x71, 0x85),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial blu 12 */
#undef XOFF
#define XOFF (X0+12*WIDTH+12*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN - 0x20, 0x81, 0xfff, BLU - 0x20, 0x81, 0x10c),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial blu 13 */
#undef XOFF
#define XOFF (X0+13*WIDTH+13*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (GRN + 0x40, 0x81, 0xfff, BLU - 0x40, 0x7d, 0x206),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 102 << 5, 0, 0, 0),

	/* trial blu 14 */
#undef XOFF
#define XOFF (X0+14*WIDTH+14*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (0x5f + 0x80, 0x81, 0xfff, 0x7f + 0x80, 0x81, 0x40d),
	gsDPPipeSync(),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 103 << 5, 0, 0, 0),

	/* trial blu 15 */
#undef XOFF
#define XOFF (X0+15*WIDTH+15*4)
	gsDPPipeSync(),
    gsDPSetKeyGB (0xfd, 0xfd, 0xfff, 0xff, 0xfd, 0xf32),
	gsSPTextureRectangle(4*XOFF, 4*YOFF, 4*XOFF + 4*WIDTH - 4,
		 4*YOFF + 4*HEIGHT - 4, G_TX_RENDERTILE,
 		 104 << 5, 0, 0, 0),

    gsSPEndDisplayList(),
};
/* end of Test 1 */

/*
 * TO ADD A TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx display list must be extern'd in cc.h, then
 * added to the 'testList_cc' table in cc.c as a Gfx pointer field of a
 * GfxTest_t struct.  You must also decide whether the existing top level DL's
 * will suffice for your application (you may need to provide a new top level
 * DL of your own design in toplevel.c).
 *
 */
