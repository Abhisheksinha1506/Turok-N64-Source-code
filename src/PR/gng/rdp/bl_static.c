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
 * File:	bl_static.c
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:
 *
 * This file holds tiny display list segments that are 'static' data, for use
 * by the blender test module in bl.c
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
 * is in bl.c, and the Gfx lists must be extern'd in rdpvector.h
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
static Vtx bl_place_vtx[5] =  {
/*     x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */	
    { -40,  40,    0,    0,	0,	0,	0xff,     0,     0,	0xff },	  /* R */   
    {  40,  40,    0,    0,	0,	0,	   0,  0xff,     0,	0xff },	  /* G */   
    {  40, -40,    0,    0,	0,	0,	   0,     0,  0xff,	0xff },	  /* B */   
    { -40, -40,    0,    0,	0,	0,	0xff,  0xff,     0,	0xff },	  /* Y */   
    {   0,   0,    0,    0,	0,	0,	0xff,  0xff,  0xff,	0xff },	  /* W */   
};

Gfx BL_placebo_dl[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&bl_place_vtx, 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};
/* end of case -1 */

/*#include "bl_tex1.h"*/
extern u32 bl_tex_llm1[];
extern u32 bl_tex_llm2[];
extern u32 bl_tex_llm3[];
extern u32 bl_tex_aa1[];
extern u32 bl_tex_aa2[];
extern u32 bl_tex_div1[];
extern u32 bl_tex_div2[];
extern u32 bl_tex_div3[];
extern u32 bl_tex_div4[];

Gfx BL_test2_dl_all[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode (G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTexturePersp(G_TP_NONE),

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* LEFT & RIGHT LERP MUL */
#define YPOS_LLM1	20
#define YPOS_LLM2	21
#define YPOS_LLM3	22
#define YPOS_RLM1	23
#define YPOS_RLM2	24
#define YPOS_RLM3	25
#define YWID_LM 	1
    gsDPSetBlendColor(0,0,0,0),		/* blendcol=0 (for memcol) */

    gsDPLoadTextureBlock(bl_tex_llm1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 256, 1, 0,
                         G_TX_CLAMP, G_TX_CLAMP,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),

/* LEFT PART 1/3 */
    gsDPWord(0xef800cff,0x00af4200),	/* G_RM: p=tex, a=tex, m=0, b=0 */
    gsSPTextureRectangle(
		30<<2,YPOS_LLM1<<2,286<<2,(YPOS_LLM1+YWID_LM)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),
/* RIGHT PART 1/3 */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xa0004200),	/* G_RM: p=0, a=tex, m=tex, b=1-a*/
    gsSPTextureRectangle(
		30<<2,YPOS_RLM1<<2,286<<2,(YPOS_RLM1+YWID_LM)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),

    gsDPLoadTextureBlock(bl_tex_llm2, G_IM_FMT_RGBA, G_IM_SIZ_32b, 256, 1, 0,
                         G_TX_CLAMP, G_TX_CLAMP,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
/* LEFT PART 2/3 */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x00af4200),	/* G_RM: p=tex, a=tex, m=0, b=0 */
    gsSPTextureRectangle(
		30<<2,YPOS_LLM2<<2,286<<2,(YPOS_LLM2+YWID_LM)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),
/* RIGHT PART 2/3 */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xa0004200),	/* G_RM: p=0, a=tex, m=tex, b=1-a*/
    gsSPTextureRectangle(
		30<<2,YPOS_RLM2<<2,286<<2,(YPOS_RLM2+YWID_LM)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),

    gsDPLoadTextureBlock(bl_tex_llm3, G_IM_FMT_RGBA, G_IM_SIZ_32b, 202, 1, 0,
                         G_TX_CLAMP, G_TX_CLAMP,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
/* LEFT PART 3/3 */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x00af4200),	/* G_RM: p=tex, a=tex, m=0, b=0 */
    gsSPTextureRectangle(
		30<<2,YPOS_LLM3<<2,232<<2,(YPOS_LLM3+YWID_LM)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),
/* RIGHT PART 3/3 */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xa0004200),	/* G_RM: p=0, a=tex, m=tex, b=1-a*/
    gsSPTextureRectangle(
		30<<2,YPOS_RLM3<<2,232<<2,(YPOS_RLM3+YWID_LM)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* alpha adder test */
#if 0
#define YPOS_AA		27

    gsDPPipeSync(),
    gsDPLoadTextureBlock(bl_tex_aa1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 1, 0,
                         G_TX_WRAP, G_TX_CLAMP,
                         3, 0, G_TX_NOLOD, G_TX_NOLOD),
/* make coverage full */
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetFillColor(0x00000000),
    gsDPFillRectangle(30<<0,YPOS_AA<<0,94<<0,(YPOS_AA+1)<<0),

/* make coverage partial and fill in color */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPWord(0xef800cff,0xaf0a7140),	/* G_RM: p=0, a=0, m=tex, b=1 */
    gsSPTextureRectangle(
    		30<<2,YPOS_AA<<2,94<<2,(YPOS_AA+1)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),

/* do additions: mem a + pixel a*/
    gsDPPipeSync(),
    gsDPSetPrimDepth(0x4000,0x8000),
    gsDPLoadTextureBlock(bl_tex_aa2, G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 1, 0,
                         G_TX_WRAP, G_TX_CLAMP,
                         3, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPWord(0xef800cff,0x00550269),	/* G_RM: p=tex, a=texa, m=mem, b=mema */
    gsSPTextureRectangle(
    		30<<2,YPOS_AA<<2,94<<2,((YPOS_AA)<<2)+1,
		G_TX_RENDERTILE, 0<<5,0<<5,(1<<10)>>3,0<<10),
    
#endif /* 0 */
/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* div test */ /* INCLUDES ALPHA ADDER TEST AT END */
#define YPOS_DIV	30
#define YPOS_DIVa	30
#define YPOS_DIV2	33
#define YPOS_DIVa2	33

    gsDPPipeSync(),
/* make coverage full */
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetFillColor(0x00000000),
    gsDPFillRectangle(30<<0,YPOS_DIV<<0,263<<0,(YPOS_DIV+1)<<0),
    gsDPFillRectangle(30<<0,YPOS_DIV2<<0,117<<0,(YPOS_DIV2+1)<<0),

/* make coverage partial and fill in color */
    gsDPPipeSync(),
    gsDPLoadTextureBlock(bl_tex_div2, G_IM_FMT_RGBA, G_IM_SIZ_32b, 233+23, 1, 0,
                         G_TX_CLAMP, G_TX_CLAMP,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimDepth(0x1000,0x4000),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPWord(0xef800cff,0xaf0a7164),	/* G_RM: p=0, a=0, m=tex, b=1 */
    gsSPTextureRectangle(
    		30<<2,YPOS_DIV<<2,263<<2,(YPOS_DIV+1)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),

    gsDPPipeSync(),
    gsDPLoadTextureBlock(bl_tex_div4, G_IM_FMT_RGBA, G_IM_SIZ_32b, 87+9, 1, 0,
                         G_TX_CLAMP, G_TX_CLAMP,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(
    		30<<2,YPOS_DIV2<<2,117<<2,(YPOS_DIV2+1)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),

/* do additions: mem a + pixel a*/
    gsDPPipeSync(),
    gsDPSetPrimDepth(0x2000,0x4000),
    gsDPLoadTextureBlock(bl_tex_div1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 233+23, 1, 0,
                         G_TX_CLAMP, G_TX_CLAMP,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPWord(0xef800cff,0x0055026c),	/* G_RM: p=tex, a=texa, m=mem, b=mema */
    gsSPTextureRectangle(
    		30<<2,YPOS_DIVa<<2,263<<2,((YPOS_DIVa)<<2)+1,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),

    gsDPPipeSync(),
    gsDPLoadTextureBlock(bl_tex_div3, G_IM_FMT_RGBA, G_IM_SIZ_32b, 87+9, 1, 0,
                         G_TX_CLAMP, G_TX_CLAMP,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(
    		30<<2,YPOS_DIVa2<<2,117<<2,((YPOS_DIVa2)<<2)+1,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),
    
/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
    /* draw 1 pix triangle macro*/
#define TRI_X 	46
#define TRI_Y 	YPOS_MXA
#define TRI_RGB	0x000000
#define TRI_A	0x55
#define TRI_W	1
#define TRI_H	1

#define YL	((TRI_Y+TRI_H)<<(2))
#define YM	((TRI_Y+TRI_H)<<(2+16))
#define YH	((TRI_Y)<<(2))
#define XL	((TRI_X)<<(16))
#define XH	((TRI_X)<<(16))
#define XM	((TRI_X+TRI_W)<<(16))
#define TR	((TRI_RGB&0xff0000))
#define TG	((TRI_RGB&0xff00  )>>8)
#define TB	((TRI_RGB&0xff    )<<16)
#define TA	(TRI_A)
#define DOTRI					\
    gsDPWord(0xcc800000 | YL, YM|YH),		\
    gsDPWord(XL,0),				\
    gsDPWord(XH,0),				\
    gsDPWord(XM,0),				\
    gsDPWord(TR|TG,TB|TA),			\
    gsDPWord(0,0),				\
    gsDPWord(0,0),				\
    gsDPWord(0,0),				\
    gsDPWord(0,0),				\
    gsDPWord(0,0),				\
    gsDPWord(0,0),				\
    gsDPWord(0,0),

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* a mux test */
#define YPOS_MXA	36
#define YPOS_MXA2	38

    gsDPPipeSync(),
			/* p=pix=fog=0xff, m=blencol=0, b=0*/
			/* force blend on */
    gsDPSetCombineMode (G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsDPSetBlendColor(0,0,0,0),		/* blendcol=0 (for memcol) */

/* asel=0 ,pixa */
    gsDPWord(0xef800cff,0xf1af4200),	/* G_RM: p=fog, a=pix, m=blend, b=0 */
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x55),	/* a=0x55 */
    gsDPFillRectangle(30,YPOS_MXA,31,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0x55),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xaa),	/* a=0xaa */
    gsDPFillRectangle(32,YPOS_MXA,33,YPOS_MXA+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xf4af4200),	/* 2 CYCLE MODE */
    gsDPFillRectangle(34,YPOS_MXA,35,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x55),	/* a=0x55 */
    gsDPFillRectangle(36,YPOS_MXA,37,YPOS_MXA+1),

/* asel=1 ,foga */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xf4af4200),	/* G_RM: p=fog, a=fog, m=blend, b=0 */
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x55),	/* a=0x55 */
    gsDPFillRectangle(38,YPOS_MXA,39,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0x55),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xaa),	/* a=0xaa */
    gsDPFillRectangle(40,YPOS_MXA,41,YPOS_MXA+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xf1af4200),	/* 2 CYCLE MODE */
    gsDPFillRectangle(42,YPOS_MXA,43,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x55),	/* a=0x55 */
    gsDPFillRectangle(44,YPOS_MXA,45,YPOS_MXA+1),
    
/* asel=2 ,shade */
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xaa),	/* a=0x55 */
    gsDPWord(0xef800cff,0xf8af4200),	/* G_RM: p=fog, a=shade, m=blend, b=0 */

#   define TRI_X 	46
#   define TRI_Y 	YPOS_MXA
#   define TRI_RGB	0x000000
#   define TRI_A	0x55
#   define TRI_W	1
#   define TRI_H	1
    DOTRI

    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0x55),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x55),	/* a=0x55 */
#   undef TRI_X
#   undef TRI_A
#   define TRI_X 	48
#   define TRI_A	0xaa
    DOTRI

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xf2af4200),	/* G_RM: p=fog, a=shade, m=blend, b=0 */
#   undef TRI_X
#   define TRI_X 	50
    DOTRI

    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xaa),	/* a=0x55 */
#   undef TRI_X
#   undef TRI_A
#   define TRI_X 	52
#   define TRI_A	0x55
    DOTRI

/* asel=3 ,0 */
    gsDPWord(0xef800cff,0xfcaf4200),	/* G_RM: p=fog, a=pix, m=blend, b=0 */
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x55),	/* a=0x55 */
    gsDPFillRectangle(54,YPOS_MXA,55,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0x55),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xaa),	/* a=0xaa */
    gsDPFillRectangle(56,YPOS_MXA,57,YPOS_MXA+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xf3af4200),	/* 2 CYCLE MODE */
    gsDPFillRectangle(58,YPOS_MXA,59,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x55),	/* a=0x55 */
    gsDPFillRectangle(60,YPOS_MXA,61,YPOS_MXA+1),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
	
/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* B mux test */
    
/* bsel=0 ,1-a */
    gsDPWord(0xef800cff,0xa0f34200),	/* G_RM: p=blend, a=pix, m=fog, b=1-a */
    gsDPSetFogColor(0xff,0xff,0xff,0x00),	/* fogcol = 0xff (for memcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x00),	/* a=0x00, b=0xff */
    gsDPFillRectangle(62,YPOS_MXA,63,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xa0f24200),	/* G_RM: p=blend, a=pix, m=fog, b=1-a */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xff),	/* a=0xff, b=0x00 */
    gsDPFillRectangle(64,YPOS_MXA,65,YPOS_MXA+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xa0fc4200),	/* 2 CYCLE MODE */
    gsDPFillRectangle(66,YPOS_MXA,67,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xa0f84200),	/* 2 CYCLE MODE */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x00),	/* a=0x00, b=0xff */
    gsDPFillRectangle(68,YPOS_MXA,69,YPOS_MXA+1),

/* bsel=1 ,mema */
    /* make coverage 0 */
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetFillColor(0x00000000),
    gsDPFillRectangle(30,YPOS_MXA2,49,YPOS_MXA2),
    gsDPSetFillColor(0x000000ff),
    gsDPFillRectangle(50,YPOS_MXA2,69,YPOS_MXA2),

    /* make cvg=0x00, 0xe0 for bsel=1 test */
    /* make col=0x55, 0xaa for pmux tests  */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xaffa4364),	/* G_RM: zsrc=prim, zupd, cvg=save */
    gsDPSetPrimDepth(0x2000,0x4000),
    gsDPSetFogColor(0x55,0x55,0x55,0x00),	/* fogcol = 0x55 (for memcol) */
    gsDPFillRectangle(30,YPOS_MXA2,49,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xaa,0xaa,0xaa,0x00),	/* fogcol = 0xaa (for memcol) */
    gsDPFillRectangle(50,YPOS_MXA2,69,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0x00),
    
    /* check mem coverage mux path (bsel=1) */
    gsDPPipeSync(),
    gsDPSetPrimDepth(0x1000,0x4000),
    gsDPWord(0xef800cff,0xa0f64274),	/* G_RM: p=blend, a=pix, m=fog, b=mema*/
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x00),	/* a=0x00, mema=0x00 */
    gsDPFillRectangle(30,YPOS_MXA2,31,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xa0f74274),	/* G_RM: p=blend, a=pix, m=fog, b=mema*/
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xff),	/* a=0xff, mema=0xe0 */
    gsDPFillRectangle(50,YPOS_MXA2,51,YPOS_MXA2+1),
/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xa0f94274),	/* G_RM: p=blend, a=pix, m=fog, b=mema*/
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x00),	/* a=0x00, mema=0x00 */
    gsDPFillRectangle(31,YPOS_MXA2,32,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xa0fd4274),	/* G_RM: p=blend, a=pix, m=fog, b=mema*/
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xff),	/* a=0xff, mema=0xe0 */
    gsDPFillRectangle(51,YPOS_MXA2,52,YPOS_MXA2+1),

/* bsel=2,3 ;0xff, 0x00 */
    gsDPWord(0xef800cff,0xa0fb4200),	/* G_RM: p=blend, a=pix, m=fog, b=0xff*/
    gsDPSetFogColor(0xff,0xff,0xff,0x00),	/* fogcol = 0xff (for memcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xff),	/* a=0xff, */
    gsDPFillRectangle(70,YPOS_MXA,71,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xa0fe4200),	/* G_RM: p=blend, a=pix, m=fog, b=0x00*/
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x00),	/* a=0x00,  */
    gsDPFillRectangle(72,YPOS_MXA,73,YPOS_MXA+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xa0fb4200),	/* 2 CYCLE MODE */
    gsDPFillRectangle(74,YPOS_MXA,75,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xa0fe4200),	/* 2 CYCLE MODE */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xff),	/* a=0x00, b=0xff */
    gsDPFillRectangle(76,YPOS_MXA,77,YPOS_MXA+1),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* pmux */

/* psel=0, pixcolor */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x35af4240),	/* G_RM: p=pix, a=fog, m=blend, b=0 */
    gsDPSetBlendColor(0x00,0x00,0x00,0x00),	/* blendcol=0 (for memcol) */
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0x55  */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(32,YPOS_MXA2,33,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol = 0x55 */
    gsDPFillRectangle(52,YPOS_MXA2,53,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),			/* blender path in 2nd cyc from fog */
    gsDPWord(0xef900cff,0xc5af4240),	/* G_RM: p=pix, a=fog, m=blend, b=0 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0x55  */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(33,YPOS_MXA2,34,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0x55 */
    gsDPFillRectangle(53,YPOS_MXA2,54,YPOS_MXA2+1),

/* psel=1, mem */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x75af4240),	/* G_RM: p=mem, a=fog, m=blend, b=0 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0xaa  */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(34,YPOS_MXA2,35,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(54,YPOS_MXA2,55,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xd5af4240),	/* G_RM: p=mem, a=fog, m=blend, b=0 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0xaa  */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(35,YPOS_MXA2,36,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(55,YPOS_MXA2,56,YPOS_MXA2+1),

/* psel=2, blend */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x85ff4240),	/* G_RM: p=blend, a=fog, m=fog, b=0 */
    gsDPSetBlendColor(0xaa,0xaa,0xaa,0x00),	/* blendcol=0xaa */
    gsDPSetFogColor(0x00,0x00,0x00,0xff),	/* fogcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(36,YPOS_MXA2,37,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetBlendColor(0x55,0x55,0x55,0x00),	/* blendcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(56,YPOS_MXA2,57,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0x25ff4240),	/* G_RM: p=blend, a=fog, m=fog, b=0 */
    gsDPSetBlendColor(0xaa,0xaa,0xaa,0x00),	/* blendcol=0xaa */
    gsDPSetFogColor(0x00,0x00,0x00,0xff),	/* fogcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(37,YPOS_MXA2,38,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetBlendColor(0x55,0x55,0x55,0x00),	/* blendcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(57,YPOS_MXA2,58,YPOS_MXA2+1),

/* psel=3, fog */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xc5af4240),	/* G_RM: p=fog, a=fog, m=blend, b=0 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol=0xaa */
    gsDPSetBlendColor(0x00,0x00,0x00,0xff),	/* blendcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(38,YPOS_MXA2,39,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(58,YPOS_MXA2,59,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0x35af4240),	/* G_RM: p=fog, a=fog, m=blend, b=0 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol=0xaa */
    gsDPSetBlendColor(0x00,0x00,0x00,0xff),	/* blendcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(39,YPOS_MXA2,40,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(59,YPOS_MXA2,60,YPOS_MXA2+1),


/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* mmux */

/* msel=0, pixcolor */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xaf3a4240),	/* G_RM: p=blend, a=0, m=pix, b=1 */
    gsDPSetBlendColor(0x00,0x00,0x00,0x00),	/* blendcol=0 (for memcol) */
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0x55  */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(40,YPOS_MXA2,41,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol = 0x55 */
    gsDPFillRectangle(60,YPOS_MXA2,61,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),			/* blender path in 2nd cyc from fog */
    gsDPWord(0xef900cff,0xafca4240),	/* G_RM: p=blend, a=0, m=pix, b=1 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0x55  */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(41,YPOS_MXA2,42,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0x55 */
    gsDPFillRectangle(61,YPOS_MXA2,62,YPOS_MXA2+1),

/* msel=1, mem */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xaf7a4240),	/* G_RM: p=blend, a=0, m=mem, b=1 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0xaa  */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(42,YPOS_MXA2,43,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(62,YPOS_MXA2,63,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xafda4240),	/* G_RM: p=blend, a=0, m=mem, b=1 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0xaa  */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(43,YPOS_MXA2,44,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(63,YPOS_MXA2,64,YPOS_MXA2+1),

/* psel=2, blend */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xff8a4240),	/* G_RM: p=fog, a=0, m=blend, b=1 */
    gsDPSetBlendColor(0xaa,0xaa,0xaa,0x00),	/* blendcol=0xaa */
    gsDPSetFogColor(0x00,0x00,0x00,0xff),	/* fogcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(44,YPOS_MXA2,45,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetBlendColor(0x55,0x55,0x55,0x00),	/* blendcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(64,YPOS_MXA2,65,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xff2a4240),	/* G_RM: p=fog, a=0, m=blend, b=1 */
    gsDPSetBlendColor(0xaa,0xaa,0xaa,0x00),	/* blendcol=0xaa */
    gsDPSetFogColor(0x00,0x00,0x00,0xff),	/* fogcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(45,YPOS_MXA2,46,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetBlendColor(0x55,0x55,0x55,0x00),	/* blendcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(65,YPOS_MXA2,66,YPOS_MXA2+1),

/* psel=3, fog */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xafca4240),	/* G_RM: p=blend, a=0, m=fog, b=1 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol=0xaa */
    gsDPSetBlendColor(0x00,0x00,0x00,0xff),	/* blendcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(46,YPOS_MXA2,47,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(66,YPOS_MXA2,67,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xaf3a4240),	/* G_RM: p=blend, a=0, m=fog, b=1 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol=0xaa */
    gsDPSetBlendColor(0x00,0x00,0x00,0xff),	/* blendcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(47,YPOS_MXA2,48,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(67,YPOS_MXA2,68,YPOS_MXA2+1),

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
    /* draw 1 pix triangle with Z macro*/
#undef TRI_X
#undef TRI_Y
#undef TRI_W
#undef TRI_H

#define TRI_X 	46
#define TRI_Y 	YPOS_MXA
#define TRI_W	1
#define TRI_H	1
#define	TRI_Z	0x00100000
#define TRI_DZX	0x00010000
#define TRI_DZY	0x00020000
#define TRI_DZE	0x00000000


#define YL	((TRI_Y+TRI_H)<<(2))
#define YM	((TRI_Y+TRI_H)<<(2+16))
#define YH	((TRI_Y)<<(2))
#define XL	((TRI_X)<<(16))
#define XH	((TRI_X)<<(16))
#define XM	((TRI_X+TRI_W)<<(16))
#define TR	((TRI_RGB&0xff0000))
#define TG	((TRI_RGB&0xff00  )>>8)
#define TB	((TRI_RGB&0xff    )<<16)
#define TA	(TRI_A)

#define ZZ	(TRI_Z)
#define ZX	(TRI_DZX)
#define ZY	(TRI_DZY)
#define ZE	(TRI_DZE)

#define DOTRIZ					\
    gsDPWord(0xc9800000 | YL, YM|YH),		\
    gsDPWord(XL,0),				\
    gsDPWord(XH,0),				\
    gsDPWord(XM,0),				\
    gsDPWord(ZZ,ZX),				\
    gsDPWord(ZE,ZY),

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* delta z test */
#define YPOS_DZ		40

#undef TRI_Y
#undef TRI_X
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#define TRI_Y	YPOS_DZ
#define TRI_X	30
#define TRI_Z	0x00000000
#define TRI_DZX	0x00ff0000
#define TRI_DZY	0x00ff0000
	
    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0x00,0xff,0xff),	/* blendcol = purple */
    gsDPWord(0xef900cff,0xafaa4260),	/* G_RM: p=blend, a=0, m=blend, b=1 */
	/*DOTRIZ*/

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	30
#	define TRI_DZX	0x00000000
#	define TRI_DZY	0x00000000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	31
#	define TRI_DZX	0x7fff0000
#	define TRI_DZY	0x00000000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	32
#	define TRI_DZX	0x00000000
#	define TRI_DZY	0x7fff0000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	33
#	define TRI_DZX	0x80000000
#	define TRI_DZY	0x00000000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	34
#	define TRI_DZX	0x00000000
#	define TRI_DZY	0x80000000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	35
#	define TRI_DZX	0xffff0000
#	define TRI_DZY	0x00000000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	36
#	define TRI_DZX	0x00000000
#	define TRI_DZY	0xffff0000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	37
#	define TRI_DZX	0x2aaa0000
#	define TRI_DZY	0x2aaa0000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	38
#	define TRI_DZX	0x55550000
#	define TRI_DZY	0x55550000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	39
#	define TRI_DZX	0x3fff0000
#	define TRI_DZY	0x00010000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	40
#	define TRI_DZX	0x00010000
#	define TRI_DZY	0x3fff0000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	41
#	define TRI_DZX	0xffff0000
#	define TRI_DZY	0xffff0000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	42
#	define TRI_DZX	0x2aab0000
#	define TRI_DZY	0x15550000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	43
#	define TRI_DZX	0x15550000
#	define TRI_DZY	0x2aab0000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	44
#	define TRI_DZX	0x00010000
#	define TRI_DZY	0x00010000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	45
#	define TRI_DZX	0x00020000
#	define TRI_DZY	0x00020000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	46
#	define TRI_DZX	0x00040000
#	define TRI_DZY	0x00040000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	47
#	define TRI_DZX	0x00080000
#	define TRI_DZY	0x00080000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	48
#	define TRI_DZX	0x00100000
#	define TRI_DZY	0x00100000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	49
#	define TRI_DZX	0x00200000
#	define TRI_DZY	0x00200000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	50
#	define TRI_DZX	0x00400000
#	define TRI_DZY	0x00400000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	51
#	define TRI_DZX	0x00800000
#	define TRI_DZY	0x00800000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	52
#	define TRI_DZX	0x01000000
#	define TRI_DZY	0x01000000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	53
#	define TRI_DZX	0x02000000
#	define TRI_DZY	0x02000000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	54
#	define TRI_DZX	0x04000000
#	define TRI_DZY	0x04000000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	55
#	define TRI_DZX	0x08000000
#	define TRI_DZY	0x08000000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	56
#	define TRI_DZX	0x10000000
#	define TRI_DZY	0x10000000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	57
#	define TRI_DZX	0x20000000
#	define TRI_DZY	0x20000000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	58
#	define TRI_DZX	0x40000000
#	define TRI_DZY	0x40000000
	DOTRIZ

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* mem DZ decode & max */
#define YPOS_MDZ	42

#undef TRI_Y
#undef TRI_Z
#undef TRI_DZX
#define TRI_Y	YPOS_MDZ
#define TRI_Z	0x7f000000
#define TRI_DZX	0x00000000

    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0xff,0x00,0xff),	/* blendcol = yellow */

		/* 0 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	30
#	define TRI_DZY	0x00000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	31
#	define TRI_DZY	0x00020000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	32
#	define TRI_DZY	0x00040000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	33
#	define TRI_DZY	0x00080000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	34
#	define TRI_DZY	0x00100000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	35
#	define TRI_DZY	0x00200000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	36
#	define TRI_DZY	0x00400000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	37
#	define TRI_DZY	0x00800000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	38
#	define TRI_DZY	0x01000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	39
#	define TRI_DZY	0x02000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	40
#	define TRI_DZY	0x04000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	41
#	define TRI_DZY	0x08000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	42
#	define TRI_DZY	0x10000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	43
#	define TRI_DZY	0x20000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	44
#	define TRI_DZY	0x40000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	45
#	define TRI_DZY	0x80000000
	DOTRIZ

    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0xff,0x00,0xff),	/* blendcol = green */
    gsDPWord(0xef900cff,0xafaa4e50),	/* G_RM: p=blend, a=0, m=blend, b=1 */

		/* check it */

    gsDPWord(0xef900cff,0xafaa4e54),	/* G_RM: p=blend, a=0, m=blend, b=1 */



/*    gsDPSetBlendColor(0x01,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f01,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    
/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x02,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f02,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x04,0xff,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f04,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x05,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f05,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x08,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f08,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x09,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f09,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x10,0xff,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f10,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x11,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f11,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x20,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f20,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x21,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f21,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x40,0xff,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f40,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x41,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f41,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x80,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f80,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x81,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f81,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xfe,0xff,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7e00,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xd8,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7d80,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xd0,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7d00,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xcf,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7cff,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xb0,0xff,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7b00,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xaf,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7aff,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x70,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7700,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x6f,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x76ff,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xf0,0xff,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x6f00,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xef,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x6eff,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x5f,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x5f00,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x5e,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x5eff,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x3f,0xff,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x3f00,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x3e,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x3eff,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0000,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),



 /* test MAX with 0x100  (same data,rects as above) */
    gsDPSetPrimDepth(0x7f01,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f02,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f04,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f05,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f08,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f09,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f10,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f11,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f20,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f21,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f40,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f41,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f80,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f81,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7e00,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7d80,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7d00,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7cff,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7b00,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7aff,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7700,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x76ff,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x6f00,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x6eff,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x5f00,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x5eff,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x3f00,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x3eff,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x0000,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

 /* test MAX with 0x2000  (same data,rects as above) */
    gsDPSetPrimDepth(0x7f01,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f02,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f04,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f05,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f08,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f09,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f10,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f11,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f20,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f21,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f40,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f41,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f80,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f81,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7e00,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7d80,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7d00,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7cff,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7b00,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7aff,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7700,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x76ff,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x6f00,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x6eff,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x5f00,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x5eff,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x3f00,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x3eff,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x0000,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),


/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* maxz test */

    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0x00,0x00,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4260),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_X
#undef TRI_Y
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	50
#	define TRI_Y	YPOS_MDZ
#	define TRI_Z	0x7fffffff
#	define TRI_DZX	0x00000000
#	define TRI_DZY	0x00000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	51
#	define TRI_Z	0x7fffc000
	DOTRIZ

    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4270),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_X
#undef TRI_Z
#	define TRI_X	50
#	define TRI_Z	0x7fffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	51
#	define TRI_Z	0x7fffc000
	DOTRIZ

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* in_front test */
#define YPOS_FRONT1	44
#define YPOS_FRONT2	55
#define YPOS_FRONT3	57
#if 0

    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0x00,0x00,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4260),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_X
#undef TRI_Y
#undef TRI_Z
#undef TRI_W
#undef TRI_H
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE
#	define TRI_X	30
#	define TRI_Y	YPOS_FRONT1
#	define TRI_W	256
#	define TRI_H	10
#	define TRI_Z	0x00000000
#	define TRI_DZX	0x0032d000
#	define TRI_DZY	0x00000000
#	define TRI_DZE	0x00550000
	DOTRIZ


    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0xff,0x00,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4250),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE
#	define TRI_Z	0x03520000
#	define TRI_DZX	0x0032d000
#	define TRI_DZY	0x00000000
#	define TRI_DZE	0xffab0000
	DOTRIZ
#endif /* 0 */

#if 0

    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0x00,0x00,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4260),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_X
#undef TRI_Y
#undef TRI_Z
#undef TRI_W
#undef TRI_H
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE
#	define TRI_X	30
#	define TRI_Y	YPOS_FRONT2
#	define TRI_W	256
#	define TRI_H	1
#	define TRI_Z	0x01000000
#	define TRI_DZX	0x0036b000
#	define TRI_DZY	0x00000000
#	define TRI_DZE	0x00000000
	DOTRIZ


    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0xff,0x00,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4250),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE
#	define TRI_Z	0x01000000
#	define TRI_DZX	0x0036b000
#	define TRI_DZY	0x00000000
#	define TRI_DZE	0x00000000
	DOTRIZ

    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0xff,0x00,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4250),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE
#	define TRI_Z	0x02000000
#	define TRI_DZX	0x0036b000
#	define TRI_DZY	0x00000000
#	define TRI_DZE	0x00000000
	DOTRIZ

    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4250),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE
#	define TRI_Z	0x00000000
#	define TRI_DZX	0x0036b000
#	define TRI_DZY	0x00000000
#	define TRI_DZE	0x00000000
	DOTRIZ



    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0x00,0x00,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4260),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_X
#undef TRI_Y
#undef TRI_Z
#undef TRI_W
#undef TRI_H
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE
#	define TRI_X	30
#	define TRI_Y	YPOS_FRONT3
#	define TRI_W	256
#	define TRI_H	1
#	define TRI_Z	0x00000000
#	define TRI_DZX	0x0036c000
#	define TRI_DZY	0x00000000
#	define TRI_DZE	0x00000000
	DOTRIZ

    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xafaa4254),	/* G_RM: p=blend, a=0, m=blend, b=1 */

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0000,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0001,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0002,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0004,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0008,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0010,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0020,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0040,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0080,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0100,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0200,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0400,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0800,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x1000,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x2000,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x4000,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x4000,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

#endif /* 0 */


/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* in_front test 2 */
#define YPOS_FRONT4	59




/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* zencode & zsel test (dz select tested above) */
#define YPOS_ZSEL	61

#undef TRI_X
#undef TRI_Y
#undef TRI_W
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	30
#	define TRI_Y	YPOS_ZSEL
#	define TRI_W	1
#	define TRI_Z	0x55555555
#	define TRI_DZX	0x00000000
#	define TRI_DZY	0x00000000
    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x2aaa,0x0000),
    gsDPWord(0xef900cff,0xafaa4220),	/* ZSEL = STEP */
	DOTRIZ

#undef TRI_X
#	define TRI_X	31
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xafaa4224),	/* zsel = PRIM */
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	32
#	define TRI_Z	0x2aaaaaaa
    gsDPPipeSync(),
    gsDPSetPrimDepth(0x5555,0x0000),
	DOTRIZ

#undef TRI_X
#	define TRI_X	33
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xafaa4220),	/* zsel = STEP */
	DOTRIZ

	/* test high (-) bit */
#undef TRI_X
#undef TRI_Z
#	define TRI_X	34
#	define TRI_Z	0xffffffff
    gsDPPipeSync(),
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	35
#	define TRI_Z	0x2aaaaaaa
    gsDPPipeSync(),
    gsDPSetPrimDepth(0xffff,0x0000),
    gsDPWord(0xef900cff,0xafaa4224),	/* zsel = PRIM */
	DOTRIZ



		/* try all different exponants */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xafaa4220),	/* zsel = STEP */

#undef TRI_X
#undef TRI_Z
#	define TRI_X	37
#	define TRI_Z	0x00000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	38
#	define TRI_Z	0x00080000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	39
#	define TRI_Z	0x10000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	40
#	define TRI_Z	0x10080000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	41
#	define TRI_Z	0x20000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	42
#	define TRI_Z	0x20080000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	43
#	define TRI_Z	0x3ff00000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	44
#	define TRI_Z	0x3fffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	45
#	define TRI_Z	0x40000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	46
#	define TRI_Z	0x40040000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	47
#	define TRI_Z	0x5ff80000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	48
#	define TRI_Z	0x5fffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	49
#	define TRI_Z	0x60000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	50
#	define TRI_Z	0x60020000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	51
#	define TRI_Z	0x6ffc0000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	52
#	define TRI_Z	0x6fffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	53
#	define TRI_Z	0x70000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	54
#	define TRI_Z	0x70010000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	55
#	define TRI_Z	0x77fe0000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	56
#	define TRI_Z	0x77ffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	57
#	define TRI_Z	0x78000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	58
#	define TRI_Z	0x78008000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	59
#	define TRI_Z	0x7bff0000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	60
#	define TRI_Z	0x7bffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	61
#	define TRI_Z	0x7c000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	62
#	define TRI_Z	0x7c004000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	63
#	define TRI_Z	0x7dff8000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	64
#	define TRI_Z	0x7dffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	65
#	define TRI_Z	0x7e000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	66
#	define TRI_Z	0x7e002000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	67
#	define TRI_Z	0x7effc000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	68
#	define TRI_Z	0x7effffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	69
#	define TRI_Z	0x7f000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	70
#	define TRI_Z	0x7f002000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	71
#	define TRI_Z	0x7f7fc000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	72
#	define TRI_Z	0x7f7fffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	73
#	define TRI_Z	0x7f800000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	74
#	define TRI_Z	0x7f802000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	75
#	define TRI_Z	0x7fffc000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	76
#	define TRI_Z	0x7fffffff
	DOTRIZ






#undef TRI_X
#undef TRI_Z
#	define TRI_X	77
#	define TRI_Z	0x7fbfffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	78
#	define TRI_Z	0x7fc00000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	79
#	define TRI_Z	0x7fc02000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	80
#	define TRI_Z	0x7f9fffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	81
#	define TRI_Z	0x7fa00000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	82
#	define TRI_Z	0x7fa02000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	83
#	define TRI_Z	0x7f8fffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	84
#	define TRI_Z	0x7f900000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	85
#	define TRI_Z	0x7f902000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	86
#	define TRI_Z	0x7f87ffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	87
#	define TRI_Z	0x7f880000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	88
#	define TRI_Z	0x7f882000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	89
#	define TRI_Z	0x7f83ffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	90
#	define TRI_Z	0x7f840000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	91
#	define TRI_Z	0x7f842000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	92
#	define TRI_Z	0x7f81ffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	93
#	define TRI_Z	0x7f820000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	94
#	define TRI_Z	0x7f822000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	95
#	define TRI_Z	0x7f80ffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	96
#	define TRI_Z	0x7f810000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	97
#	define TRI_Z	0x7f812000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	98
#	define TRI_Z	0x7f807fff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	99
#	define TRI_Z	0x7f808000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	100
#	define TRI_Z	0x7f80a000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	101
#	define TRI_Z	0x7f803fff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	102
#	define TRI_Z	0x7f804000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	103
#	define TRI_Z	0x7f806000
	DOTRIZ





/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* farther/nearer tests (decal) */

    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0xff,0x00,0xff),	/* blendcol = green */
    gsDPWord(0xef900cff,0xafaa4214),	/* ZSEL = STEP */


    gsDPSetPrimDepth(0x0000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

    gsDPSetPrimDepth(0x7e00,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

    gsDPSetPrimDepth(0x7eff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

    gsDPSetPrimDepth(0x7dff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

    gsDPSetPrimDepth(0x7bff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

    gsDPSetPrimDepth(0x67ff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

    gsDPSetPrimDepth(0x5fff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

    gsDPSetPrimDepth(0x3fff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

#if 0

    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = blue */
    gsDPWord(0xef900cff,0xafaa4e14),		/* DECAL MODE */
/* note: below is same data as above, but using decal mode and
   repeated with several DZ values */

/* DZ = 0 */
    gsDPSetPrimDepth(0x0000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 1 */
    gsDPSetPrimDepth(0x0000,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 2 */
    gsDPSetPrimDepth(0x0000,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 4 */
    gsDPSetPrimDepth(0x0000,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 8 */
    gsDPSetPrimDepth(0x0000,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 10 */
    gsDPSetPrimDepth(0x0000,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 20 */
    gsDPSetPrimDepth(0x0000,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 40 */
    gsDPSetPrimDepth(0x0000,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 80 */
    gsDPSetPrimDepth(0x0000,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 100 */
    gsDPSetPrimDepth(0x0000,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 200 */
    gsDPSetPrimDepth(0x0000,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 400 */
    gsDPSetPrimDepth(0x0000,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 800 */
    gsDPSetPrimDepth(0x0000,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 1000 */
    gsDPSetPrimDepth(0x0000,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 2000 */
    gsDPSetPrimDepth(0x0000,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 4000 */
    gsDPSetPrimDepth(0x0000,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 8000 */
    gsDPSetPrimDepth(0x0000,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
#endif /* 0 */


/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* end  */
    gsSPTexture(0, 0, 0, 0, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
    

};

Gfx BL_test2_dl1[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode (G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTexturePersp(G_TP_NONE),

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* LEFT & RIGHT LERP MUL */
#define YPOS_LLM1	20
#define YPOS_LLM2	21
#define YPOS_LLM3	22
#define YPOS_RLM1	23
#define YPOS_RLM2	24
#define YPOS_RLM3	25
#define YWID_LM 	1
    gsDPSetBlendColor(0,0,0,0),		/* blendcol=0 (for memcol) */

    gsDPLoadTextureBlock(bl_tex_llm1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 256, 1, 0,
                         G_TX_CLAMP, G_TX_CLAMP,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),

/* LEFT PART 1/3 */
    gsDPWord(0xef800cff,0x00af4200),	/* G_RM: p=tex, a=tex, m=0, b=0 */
    gsSPTextureRectangle(
		30<<2,YPOS_LLM1<<2,286<<2,(YPOS_LLM1+YWID_LM)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),
/* RIGHT PART 1/3 */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xa0004200),	/* G_RM: p=0, a=tex, m=tex, b=1-a*/
    gsSPTextureRectangle(
		30<<2,YPOS_RLM1<<2,286<<2,(YPOS_RLM1+YWID_LM)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),

    gsDPLoadTextureBlock(bl_tex_llm2, G_IM_FMT_RGBA, G_IM_SIZ_32b, 256, 1, 0,
                         G_TX_CLAMP, G_TX_CLAMP,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
/* LEFT PART 2/3 */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x00af4200),	/* G_RM: p=tex, a=tex, m=0, b=0 */
    gsSPTextureRectangle(
		30<<2,YPOS_LLM2<<2,286<<2,(YPOS_LLM2+YWID_LM)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),
/* RIGHT PART 2/3 */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xa0004200),	/* G_RM: p=0, a=tex, m=tex, b=1-a*/
    gsSPTextureRectangle(
		30<<2,YPOS_RLM2<<2,286<<2,(YPOS_RLM2+YWID_LM)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),

    gsDPLoadTextureBlock(bl_tex_llm3, G_IM_FMT_RGBA, G_IM_SIZ_32b, 202, 1, 0,
                         G_TX_CLAMP, G_TX_CLAMP,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
/* LEFT PART 3/3 */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x00af4200),	/* G_RM: p=tex, a=tex, m=0, b=0 */
    gsSPTextureRectangle(
		30<<2,YPOS_LLM3<<2,232<<2,(YPOS_LLM3+YWID_LM)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),
/* RIGHT PART 3/3 */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xa0004200),	/* G_RM: p=0, a=tex, m=tex, b=1-a*/
    gsSPTextureRectangle(
		30<<2,YPOS_RLM3<<2,232<<2,(YPOS_RLM3+YWID_LM)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* alpha adder test */
#if 0
#define YPOS_AA		27

    gsDPPipeSync(),
    gsDPLoadTextureBlock(bl_tex_aa1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 1, 0,
                         G_TX_WRAP, G_TX_CLAMP,
                         3, 0, G_TX_NOLOD, G_TX_NOLOD),
/* make coverage full */
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetFillColor(0x00000000),
    gsDPFillRectangle(30<<0,YPOS_AA<<0,94<<0,(YPOS_AA+1)<<0),

/* make coverage partial and fill in color */
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPWord(0xef800cff,0xaf0a7140),	/* G_RM: p=0, a=0, m=tex, b=1 */
    gsSPTextureRectangle(
    		30<<2,YPOS_AA<<2,94<<2,(YPOS_AA+1)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),

/* do additions: mem a + pixel a*/
    gsDPPipeSync(),
    gsDPSetPrimDepth(0x4000,0x8000),
    gsDPLoadTextureBlock(bl_tex_aa2, G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 1, 0,
                         G_TX_WRAP, G_TX_CLAMP,
                         3, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPWord(0xef800cff,0x00550269),	/* G_RM: p=tex, a=texa, m=mem, b=mema */
    gsSPTextureRectangle(
    		30<<2,YPOS_AA<<2,94<<2,((YPOS_AA)<<2)+1,
		G_TX_RENDERTILE, 0<<5,0<<5,(1<<10)>>3,0<<10),
    
#endif /* 0 */
/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* div test */ /* INCLUDES ALPHA ADDER TEST AT END */
#define YPOS_DIV	30
#define YPOS_DIVa	30
#define YPOS_DIV2	33
#define YPOS_DIVa2	33

    gsDPPipeSync(),
/* make coverage full */
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetFillColor(0x00000000),
    gsDPFillRectangle(30<<0,YPOS_DIV<<0,263<<0,(YPOS_DIV+1)<<0),
    gsDPFillRectangle(30<<0,YPOS_DIV2<<0,117<<0,(YPOS_DIV2+1)<<0),

/* make coverage partial and fill in color */
    gsDPPipeSync(),
    gsDPLoadTextureBlock(bl_tex_div2, G_IM_FMT_RGBA, G_IM_SIZ_32b, 233+23, 1, 0,
                         G_TX_CLAMP, G_TX_CLAMP,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimDepth(0x1000,0x4000),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPWord(0xef800cff,0xaf0a7164),	/* G_RM: p=0, a=0, m=tex, b=1 */
    gsSPTextureRectangle(
    		30<<2,YPOS_DIV<<2,263<<2,(YPOS_DIV+1)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),

    gsDPPipeSync(),
    gsDPLoadTextureBlock(bl_tex_div4, G_IM_FMT_RGBA, G_IM_SIZ_32b, 87+9, 1, 0,
                         G_TX_CLAMP, G_TX_CLAMP,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(
    		30<<2,YPOS_DIV2<<2,117<<2,(YPOS_DIV2+1)<<2,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),

/* do additions: mem a + pixel a*/
    gsDPPipeSync(),
    gsDPSetPrimDepth(0x2000,0x4000),
    gsDPLoadTextureBlock(bl_tex_div1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 233+23, 1, 0,
                         G_TX_CLAMP, G_TX_CLAMP,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsDPWord(0xef800cff,0x0055026c),	/* G_RM: p=tex, a=texa, m=mem, b=mema */
    gsSPTextureRectangle(
    		30<<2,YPOS_DIVa<<2,263<<2,((YPOS_DIVa)<<2)+1,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),

    gsDPPipeSync(),
    gsDPLoadTextureBlock(bl_tex_div3, G_IM_FMT_RGBA, G_IM_SIZ_32b, 87+9, 1, 0,
                         G_TX_CLAMP, G_TX_CLAMP,
                         0, 0, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTextureRectangle(
    		30<<2,YPOS_DIVa2<<2,117<<2,((YPOS_DIVa2)<<2)+1,
		G_TX_RENDERTILE, 0<<5,0<<5,1<<10,0<<10),
    
/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
    /* draw 1 pix triangle macro*/
#undef TRI_X
#undef TRI_Y
#undef TRI_RGB
#undef TRI_A
#undef TRI_W
#undef TRI_H

#define TRI_X 	46
#define TRI_Y 	YPOS_MXA
#define TRI_RGB	0x000000
#define TRI_A	0x55
#define TRI_W	1
#define TRI_H	1

#define YL	((TRI_Y+TRI_H)<<(2))
#define YM	((TRI_Y+TRI_H)<<(2+16))
#define YH	((TRI_Y)<<(2))
#define XL	((TRI_X)<<(16))
#define XH	((TRI_X)<<(16))
#define XM	((TRI_X+TRI_W)<<(16))
#define TR	((TRI_RGB&0xff0000))
#define TG	((TRI_RGB&0xff00  )>>8)
#define TB	((TRI_RGB&0xff    )<<16)
#define TA	(TRI_A)
#define DOTRI					\
    gsDPWord(0xcc800000 | YL, YM|YH),		\
    gsDPWord(XL,0),				\
    gsDPWord(XH,0),				\
    gsDPWord(XM,0),				\
    gsDPWord(TR|TG,TB|TA),			\
    gsDPWord(0,0),				\
    gsDPWord(0,0),				\
    gsDPWord(0,0),				\
    gsDPWord(0,0),				\
    gsDPWord(0,0),				\
    gsDPWord(0,0),				\
    gsDPWord(0,0),

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* a mux test */
#define YPOS_MXA	36
#define YPOS_MXA2	38

    gsDPPipeSync(),
			/* p=pix=fog=0xff, m=blencol=0, b=0*/
			/* force blend on */
    gsDPSetCombineMode (G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsDPSetBlendColor(0,0,0,0),		/* blendcol=0 (for memcol) */

/* asel=0 ,pixa */
    gsDPWord(0xef800cff,0xf1af4200),	/* G_RM: p=fog, a=pix, m=blend, b=0 */
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x55),	/* a=0x55 */
    gsDPFillRectangle(30,YPOS_MXA,31,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0x55),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xaa),	/* a=0xaa */
    gsDPFillRectangle(32,YPOS_MXA,33,YPOS_MXA+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xf4af4200),	/* 2 CYCLE MODE */
    gsDPFillRectangle(34,YPOS_MXA,35,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x55),	/* a=0x55 */
    gsDPFillRectangle(36,YPOS_MXA,37,YPOS_MXA+1),

/* asel=1 ,foga */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xf4af4200),	/* G_RM: p=fog, a=fog, m=blend, b=0 */
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x55),	/* a=0x55 */
    gsDPFillRectangle(38,YPOS_MXA,39,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0x55),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xaa),	/* a=0xaa */
    gsDPFillRectangle(40,YPOS_MXA,41,YPOS_MXA+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xf1af4200),	/* 2 CYCLE MODE */
    gsDPFillRectangle(42,YPOS_MXA,43,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x55),	/* a=0x55 */
    gsDPFillRectangle(44,YPOS_MXA,45,YPOS_MXA+1),
    
/* asel=2 ,shade */
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xaa),	/* a=0x55 */
    gsDPWord(0xef800cff,0xf8af4200),	/* G_RM: p=fog, a=shade, m=blend, b=0 */

#   define TRI_X 	46
#   define TRI_Y 	YPOS_MXA
#   define TRI_RGB	0x000000
#   define TRI_A	0x55
#   define TRI_W	1
#   define TRI_H	1
    DOTRI

    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0x55),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x55),	/* a=0x55 */
#   undef TRI_X
#   undef TRI_A
#   define TRI_X 	48
#   define TRI_A	0xaa
    DOTRI

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xf2af4200),	/* G_RM: p=fog, a=shade, m=blend, b=0 */
#   undef TRI_X
#   define TRI_X 	50
    DOTRI

    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xaa),	/* a=0x55 */
#   undef TRI_X
#   undef TRI_A
#   define TRI_X 	52
#   define TRI_A	0x55
    DOTRI

/* asel=3 ,0 */
    gsDPWord(0xef800cff,0xfcaf4200),	/* G_RM: p=fog, a=pix, m=blend, b=0 */
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x55),	/* a=0x55 */
    gsDPFillRectangle(54,YPOS_MXA,55,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0x55),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xaa),	/* a=0xaa */
    gsDPFillRectangle(56,YPOS_MXA,57,YPOS_MXA+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xf3af4200),	/* 2 CYCLE MODE */
    gsDPFillRectangle(58,YPOS_MXA,59,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0xaa),	/* fogcol = 0xff (for pixcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x55),	/* a=0x55 */
    gsDPFillRectangle(60,YPOS_MXA,61,YPOS_MXA+1),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
	
/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* B mux test */
    
/* bsel=0 ,1-a */
    gsDPWord(0xef800cff,0xa0f34200),	/* G_RM: p=blend, a=pix, m=fog, b=1-a */
    gsDPSetFogColor(0xff,0xff,0xff,0x00),	/* fogcol = 0xff (for memcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x00),	/* a=0x00, b=0xff */
    gsDPFillRectangle(62,YPOS_MXA,63,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xa0f24200),	/* G_RM: p=blend, a=pix, m=fog, b=1-a */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xff),	/* a=0xff, b=0x00 */
    gsDPFillRectangle(64,YPOS_MXA,65,YPOS_MXA+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xa0fc4200),	/* 2 CYCLE MODE */
    gsDPFillRectangle(66,YPOS_MXA,67,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xa0f84200),	/* 2 CYCLE MODE */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x00),	/* a=0x00, b=0xff */
    gsDPFillRectangle(68,YPOS_MXA,69,YPOS_MXA+1),

/* bsel=1 ,mema */
    /* make coverage 0 */
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetFillColor(0x00000000),
    gsDPFillRectangle(30,YPOS_MXA2,49,YPOS_MXA2),
    gsDPSetFillColor(0x000000ff),
    gsDPFillRectangle(50,YPOS_MXA2,69,YPOS_MXA2),

    /* make cvg=0x00, 0xe0 for bsel=1 test */
    /* make col=0x55, 0xaa for pmux tests  */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xaffa4364),	/* G_RM: zsrc=prim, zupd, cvg=save */
    gsDPSetPrimDepth(0x2000,0x4000),
    gsDPSetFogColor(0x55,0x55,0x55,0x00),	/* fogcol = 0x55 (for memcol) */
    gsDPFillRectangle(30,YPOS_MXA2,49,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xaa,0xaa,0xaa,0x00),	/* fogcol = 0xaa (for memcol) */
    gsDPFillRectangle(50,YPOS_MXA2,69,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xff,0xff,0xff,0x00),
    
    /* check mem coverage mux path (bsel=1) */
    gsDPPipeSync(),
    gsDPSetPrimDepth(0x1000,0x4000),
    gsDPWord(0xef800cff,0xa0f64274),	/* G_RM: p=blend, a=pix, m=fog, b=mema*/
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x00),	/* a=0x00, mema=0x00 */
    gsDPFillRectangle(30,YPOS_MXA2,31,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xa0f74274),	/* G_RM: p=blend, a=pix, m=fog, b=mema*/
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xff),	/* a=0xff, mema=0xe0 */
    gsDPFillRectangle(50,YPOS_MXA2,51,YPOS_MXA2+1),
/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xa0f94274),	/* G_RM: p=blend, a=pix, m=fog, b=mema*/
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x00),	/* a=0x00, mema=0x00 */
    gsDPFillRectangle(31,YPOS_MXA2,32,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xa0fd4274),	/* G_RM: p=blend, a=pix, m=fog, b=mema*/
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xff),	/* a=0xff, mema=0xe0 */
    gsDPFillRectangle(51,YPOS_MXA2,52,YPOS_MXA2+1),

/* bsel=2,3 ;0xff, 0x00 */
    gsDPWord(0xef800cff,0xa0fb4200),	/* G_RM: p=blend, a=pix, m=fog, b=0xff*/
    gsDPSetFogColor(0xff,0xff,0xff,0x00),	/* fogcol = 0xff (for memcol) */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xff),	/* a=0xff, */
    gsDPFillRectangle(70,YPOS_MXA,71,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xa0fe4200),	/* G_RM: p=blend, a=pix, m=fog, b=0x00*/
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0x00),	/* a=0x00,  */
    gsDPFillRectangle(72,YPOS_MXA,73,YPOS_MXA+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xa0fb4200),	/* 2 CYCLE MODE */
    gsDPFillRectangle(74,YPOS_MXA,75,YPOS_MXA+1),
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xa0fe4200),	/* 2 CYCLE MODE */
    gsDPSetPrimColor(0,0,0xff,0xff,0xff,0xff),	/* a=0x00, b=0xff */
    gsDPFillRectangle(76,YPOS_MXA,77,YPOS_MXA+1),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* pmux */

/* psel=0, pixcolor */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x35af4240),	/* G_RM: p=pix, a=fog, m=blend, b=0 */
    gsDPSetBlendColor(0x00,0x00,0x00,0x00),	/* blendcol=0 (for memcol) */
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0x55  */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(32,YPOS_MXA2,33,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol = 0x55 */
    gsDPFillRectangle(52,YPOS_MXA2,53,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),			/* blender path in 2nd cyc from fog */
    gsDPWord(0xef900cff,0xc5af4240),	/* G_RM: p=pix, a=fog, m=blend, b=0 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0x55  */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(33,YPOS_MXA2,34,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0x55 */
    gsDPFillRectangle(53,YPOS_MXA2,54,YPOS_MXA2+1),

/* psel=1, mem */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x75af4240),	/* G_RM: p=mem, a=fog, m=blend, b=0 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0xaa  */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(34,YPOS_MXA2,35,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(54,YPOS_MXA2,55,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xd5af4240),	/* G_RM: p=mem, a=fog, m=blend, b=0 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0xaa  */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(35,YPOS_MXA2,36,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(55,YPOS_MXA2,56,YPOS_MXA2+1),

/* psel=2, blend */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x85ff4240),	/* G_RM: p=blend, a=fog, m=fog, b=0 */
    gsDPSetBlendColor(0xaa,0xaa,0xaa,0x00),	/* blendcol=0xaa */
    gsDPSetFogColor(0x00,0x00,0x00,0xff),	/* fogcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(36,YPOS_MXA2,37,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetBlendColor(0x55,0x55,0x55,0x00),	/* blendcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(56,YPOS_MXA2,57,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0x25ff4240),	/* G_RM: p=blend, a=fog, m=fog, b=0 */
    gsDPSetBlendColor(0xaa,0xaa,0xaa,0x00),	/* blendcol=0xaa */
    gsDPSetFogColor(0x00,0x00,0x00,0xff),	/* fogcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(37,YPOS_MXA2,38,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetBlendColor(0x55,0x55,0x55,0x00),	/* blendcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(57,YPOS_MXA2,58,YPOS_MXA2+1),

/* psel=3, fog */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xc5af4240),	/* G_RM: p=fog, a=fog, m=blend, b=0 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol=0xaa */
    gsDPSetBlendColor(0x00,0x00,0x00,0xff),	/* blendcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(38,YPOS_MXA2,39,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(58,YPOS_MXA2,59,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0x35af4240),	/* G_RM: p=fog, a=fog, m=blend, b=0 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol=0xaa */
    gsDPSetBlendColor(0x00,0x00,0x00,0xff),	/* blendcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(39,YPOS_MXA2,40,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(59,YPOS_MXA2,60,YPOS_MXA2+1),


/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* mmux */

/* msel=0, pixcolor */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xaf3a4240),	/* G_RM: p=blend, a=0, m=pix, b=1 */
    gsDPSetBlendColor(0x00,0x00,0x00,0x00),	/* blendcol=0 (for memcol) */
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0x55  */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(40,YPOS_MXA2,41,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol = 0x55 */
    gsDPFillRectangle(60,YPOS_MXA2,61,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),			/* blender path in 2nd cyc from fog */
    gsDPWord(0xef900cff,0xafca4240),	/* G_RM: p=blend, a=0, m=pix, b=1 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0x55  */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(41,YPOS_MXA2,42,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0x55 */
    gsDPFillRectangle(61,YPOS_MXA2,62,YPOS_MXA2+1),

/* msel=1, mem */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xaf7a4240),	/* G_RM: p=blend, a=0, m=mem, b=1 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0xaa  */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(42,YPOS_MXA2,43,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(62,YPOS_MXA2,63,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xafda4240),	/* G_RM: p=blend, a=0, m=mem, b=1 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol = 0xaa  */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol=0xaa */
    gsDPFillRectangle(43,YPOS_MXA2,44,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol = 0xaa */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(63,YPOS_MXA2,64,YPOS_MXA2+1),

/* psel=2, blend */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xff8a4240),	/* G_RM: p=fog, a=0, m=blend, b=1 */
    gsDPSetBlendColor(0xaa,0xaa,0xaa,0x00),	/* blendcol=0xaa */
    gsDPSetFogColor(0x00,0x00,0x00,0xff),	/* fogcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(44,YPOS_MXA2,45,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetBlendColor(0x55,0x55,0x55,0x00),	/* blendcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(64,YPOS_MXA2,65,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xff2a4240),	/* G_RM: p=fog, a=0, m=blend, b=1 */
    gsDPSetBlendColor(0xaa,0xaa,0xaa,0x00),	/* blendcol=0xaa */
    gsDPSetFogColor(0x00,0x00,0x00,0xff),	/* fogcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(45,YPOS_MXA2,46,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetBlendColor(0x55,0x55,0x55,0x00),	/* blendcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(65,YPOS_MXA2,66,YPOS_MXA2+1),

/* psel=3, fog */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xafca4240),	/* G_RM: p=blend, a=0, m=fog, b=1 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol=0xaa */
    gsDPSetBlendColor(0x00,0x00,0x00,0xff),	/* blendcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(46,YPOS_MXA2,47,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(66,YPOS_MXA2,67,YPOS_MXA2+1),

/* 2 CYCLE */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xaf3a4240),	/* G_RM: p=blend, a=0, m=fog, b=1 */
    gsDPSetFogColor(0xaa,0xaa,0xaa,0xff),	/* fogcol=0xaa */
    gsDPSetBlendColor(0x00,0x00,0x00,0xff),	/* blendcol = 0 (for memcol) */
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol=0x55 */
    gsDPFillRectangle(47,YPOS_MXA2,48,YPOS_MXA2+1),
    gsDPPipeSync(),
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol=0x55 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(67,YPOS_MXA2,68,YPOS_MXA2+1),

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* some extra pathways (color on cov, etc) */
#define YPOS_EXTRA	40

    /*
     * make coverages small so they wont wrap later
     */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xf5aa412c),	/* G_RM: p=fog, a=foga, m=blend, b=0 */
    gsDPSetPrimDepth(0x1fff,0x0000),
    gsDPSetFogColor(0x00,0x00,0x00,0x00),	/* fogcol=0x00 */
    gsDPSetBlendColor(0x00,0x00,0x00,0xff),	/* blendcol = 00 (for memcol) */
    gsSPTextureRectangle(
		30<<2,YPOS_EXTRA<<2,50<<2,(YPOS_EXTRA<<2)+2,
		G_TX_RENDERTILE, 0,0,0,0),


    /*
     * test alpha_cvg_sel path
     */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0xf5af41c8),	/* G_RM: p=fog, a=foga, m=blend, b=0 */
    gsDPSetFogColor(0x00,0x00,0x00,0x00),	/* fogcol=0x00 */
    gsDPSetBlendColor(0x55,0x55,0x55,0xff),	/* blendcol = 55 (for memcol) */
    gsSPTextureRectangle(
		30<<2,YPOS_EXTRA<<2,31<<2,(YPOS_EXTRA<<2)+1,
		G_TX_RENDERTILE, 0,0,0,0),

    gsDPPipeSync(),
    gsDPSetFogColor(0x00,0x00,0x00,0x00),	/* fogcol=0x00 */
    gsDPSetBlendColor(0xaa,0xaa,0xaa,0xff),	/* blendcol = aa (for memcol) */
    gsSPTextureRectangle(
		31<<2,YPOS_EXTRA<<2,32<<2,(YPOS_EXTRA<<2)+1,
		G_TX_RENDERTILE, 0,0,0,0),

    /*
     * test alpha1 path (where alpha=1)
     */
    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x00a041c8),	/* G_RM: p=fog, a=foga, m=blend, b=0 */
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPSetCombineMode (G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsDPSetBlendColor(0x00,0x00,0x00,0xff),	/* blendcol = 00 (for memcol) */
    gsDPFillRectangle(64,YPOS_EXTRA,65,YPOS_EXTRA+1),

    gsDPPipeSync(),
    gsDPSetPrimColor(0,0,0x55,0x55,0x55,0xff),	/* pixcol = 0xaa */
    gsDPFillRectangle(66,YPOS_EXTRA,67,YPOS_EXTRA+1),

    /*
     * test coverage dest modes (save, full, wrap, new, clamp)
     */
    gsDPPipeSync(),
    gsDPSetPrimColor(0,0,0xbb,0xbb,0xbb,0xff),	/* pixcol = 0xaa */
    gsDPWord(0xef800cff,0x00a043c8),	/* G_RM: p=fog, a=foga, m=blend, b=0 */
    gsSPTextureRectangle(
		33<<2,YPOS_EXTRA<<2,34<<2,(YPOS_EXTRA<<2)+3,
		G_TX_RENDERTILE, 0,0,0,0),

    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x00a042c8),	/* G_RM: p=fog, a=foga, m=blend, b=0 */
    gsSPTextureRectangle(
		34<<2,YPOS_EXTRA<<2,35<<2,(YPOS_EXTRA<<2)+3,
		G_TX_RENDERTILE, 0,0,0,0),

    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x00a041c8),	/* G_RM: p=fog, a=foga, m=blend, b=0 */
    gsSPTextureRectangle(
		35<<2,YPOS_EXTRA<<2,36<<2,(YPOS_EXTRA<<2)+3,
		G_TX_RENDERTILE, 0,0,0,0),

    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x00a000c8),	/* G_RM: p=fog, a=foga, m=blend, b=0 */
    gsSPTextureRectangle(
		36<<2,YPOS_EXTRA<<2,37<<2,(YPOS_EXTRA<<2)+3,
		G_TX_RENDERTILE, 0,0,0,0),

    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x00a040c8),	/* G_RM: p=fog, a=foga, m=blend, b=0 */
    gsSPTextureRectangle(
		37<<2,YPOS_EXTRA<<2,38<<2,(YPOS_EXTRA<<2)+3,
		G_TX_RENDERTILE, 0,0,0,0),

    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x00a040c8),	/* G_RM: p=fog, a=foga, m=blend, b=0 */
    gsSPTextureRectangle(
		38<<2,YPOS_EXTRA<<2,(38<<2)+2,(YPOS_EXTRA<<2)+3,
		G_TX_RENDERTILE, 0,0,0,0),

    /*
     * test interpen cvg mode
     */
    gsDPPipeSync(),
    gsDPSetPrimColor(0,0,0xcc,0xcc,0xcc,0xff),	/* pixcol = 0xaa */
    gsDPWord(0xef800cff,0x00a041ec),	/* G_RM: p=fog, a=foga, m=blend, b=0 */
    gsDPSetPrimDepth(0x1ff0,0x0010),
    gsSPTextureRectangle(
		40<<2,YPOS_EXTRA<<2,41<<2,(YPOS_EXTRA<<2)+3,
		G_TX_RENDERTILE, 0,0,0,0),

    gsDPPipeSync(),
    gsDPWord(0xef800cff,0x00a045fc),	/* G_RM: p=fog, a=foga, m=blend, b=0 */
    gsSPTextureRectangle(
		41<<2,YPOS_EXTRA<<2,42<<2,(YPOS_EXTRA<<2)+3,
		G_TX_RENDERTILE, 0,0,0,0),

    gsDPPipeSync(),
    gsDPSetPrimDepth(0x1f00,0x0100),
    gsSPTextureRectangle(
		42<<2,YPOS_EXTRA<<2,43<<2,(YPOS_EXTRA<<2)+3,
		G_TX_RENDERTILE, 0,0,0,0),

    /*
     * test tranzp z mode
     */
    gsDPPipeSync(),
    gsDPSetPrimColor(0,0,0xdd,0xdd,0xdd,0xff),	/* pixcol = 0xaa */
    gsDPWord(0xef800cff,0x00a049fc),	/* G_RM: p=fog, a=foga, m=blend, b=0 */
    gsDPSetPrimDepth(0x1ff0,0x0010),
    gsSPTextureRectangle(
		44<<2,YPOS_EXTRA<<2,45<<2,(YPOS_EXTRA<<2)+3,
		G_TX_RENDERTILE, 0,0,0,0),

    gsDPPipeSync(),
    gsDPSetPrimDepth(0x2ff0,0x0010),
    gsSPTextureRectangle(
		44<<2,YPOS_EXTRA<<2,45<<2,(YPOS_EXTRA<<2)+3,
		G_TX_RENDERTILE, 0,0,0,0),




/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* end  */
    gsSPTexture(0, 0, 0, 0, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
    

};

Gfx BL_test2_dl2[] = {
    gsDPPipeSync(),

    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTexturePersp(G_TP_NONE),





    gsDPSetCombineMode (G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsDPSetPrimColor(0,0,0xaa,0xaa,0xaa,0xff),	/* pixcol = 0xaa */
    gsDPSetFogColor(0x55,0x55,0x55,0xff),	/* fogcol=0x55 */


/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
    /* draw 1 pix triangle with Z macro*/
#undef TRI_X
#undef TRI_Y
#undef TRI_W
#undef TRI_H
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE

#define TRI_X 	46
#define TRI_Y 	YPOS_MXA
#define TRI_W	1
#define TRI_H	1
#define	TRI_Z	0x00100000
#define TRI_DZX	0x00010000
#define TRI_DZY	0x00020000
#define TRI_DZE	0x00000000


#define YL	((TRI_Y+TRI_H)<<(2))
#define YM	((TRI_Y+TRI_H)<<(2+16))
#define YH	((TRI_Y)<<(2))
#define XL	((TRI_X)<<(16))
#define XH	((TRI_X)<<(16))
#define XM	((TRI_X+TRI_W)<<(16))
#define TR	((TRI_RGB&0xff0000))
#define TG	((TRI_RGB&0xff00  )>>8)
#define TB	((TRI_RGB&0xff    )<<16)
#define TA	(TRI_A)

#define ZZ	(TRI_Z)
#define ZX	(TRI_DZX)
#define ZY	(TRI_DZY)
#define ZE	(TRI_DZE)

#define DOTRIZ					\
    gsDPWord(0xc9800000 | YL, YM|YH),		\
    gsDPWord(XL,0),				\
    gsDPWord(XH,0),				\
    gsDPWord(XM,0),				\
    gsDPWord(ZZ,ZX),				\
    gsDPWord(ZE,ZY),

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* delta z test */
#define YPOS_DZ		40

#undef TRI_Y
#undef TRI_X
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#define TRI_Y	YPOS_DZ
#define TRI_X	30
#define TRI_Z	0x00000000
#define TRI_DZX	0x00ff0000
#define TRI_DZY	0x00ff0000
	
    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0x00,0xff,0xff),	/* blendcol = purple */
    gsDPWord(0xef900cff,0xafaa4260),	/* G_RM: p=blend, a=0, m=blend, b=1 */
	/*DOTRIZ*/

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	30
#	define TRI_DZX	0x00000000
#	define TRI_DZY	0x00000000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	31
#	define TRI_DZX	0x7fff0000
#	define TRI_DZY	0x00000000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	32
#	define TRI_DZX	0x00000000
#	define TRI_DZY	0x7fff0000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	33
#	define TRI_DZX	0x80000000
#	define TRI_DZY	0x00000000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	34
#	define TRI_DZX	0x00000000
#	define TRI_DZY	0x80000000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	35
#	define TRI_DZX	0xffff0000
#	define TRI_DZY	0x00000000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	36
#	define TRI_DZX	0x00000000
#	define TRI_DZY	0xffff0000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	37
#	define TRI_DZX	0x2aaa0000
#	define TRI_DZY	0x2aaa0000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	38
#	define TRI_DZX	0x55550000
#	define TRI_DZY	0x55550000
	DOTRIZ

		/* 1+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	39
#	define TRI_DZX	0x3fff0000
#	define TRI_DZY	0x00010000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	40
#	define TRI_DZX	0x00010000
#	define TRI_DZY	0x3fff0000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	41
#	define TRI_DZX	0xffff0000
#	define TRI_DZY	0xffff0000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	42
#	define TRI_DZX	0x2aab0000
#	define TRI_DZY	0x15550000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	43
#	define TRI_DZX	0x15550000
#	define TRI_DZY	0x2aab0000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	44
#	define TRI_DZX	0x00010000
#	define TRI_DZY	0x00010000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	45
#	define TRI_DZX	0x00020000
#	define TRI_DZY	0x00020000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	46
#	define TRI_DZX	0x00040000
#	define TRI_DZY	0x00040000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	47
#	define TRI_DZX	0x00080000
#	define TRI_DZY	0x00080000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	48
#	define TRI_DZX	0x00100000
#	define TRI_DZY	0x00100000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	49
#	define TRI_DZX	0x00200000
#	define TRI_DZY	0x00200000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	50
#	define TRI_DZX	0x00400000
#	define TRI_DZY	0x00400000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	51
#	define TRI_DZX	0x00800000
#	define TRI_DZY	0x00800000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	52
#	define TRI_DZX	0x01000000
#	define TRI_DZY	0x01000000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	53
#	define TRI_DZX	0x02000000
#	define TRI_DZY	0x02000000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	54
#	define TRI_DZX	0x04000000
#	define TRI_DZY	0x04000000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	55
#	define TRI_DZX	0x08000000
#	define TRI_DZY	0x08000000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	56
#	define TRI_DZX	0x10000000
#	define TRI_DZY	0x10000000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	57
#	define TRI_DZX	0x20000000
#	define TRI_DZY	0x20000000
	DOTRIZ

		/* 0+0 */
#undef TRI_X
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	58
#	define TRI_DZX	0x40000000
#	define TRI_DZY	0x40000000
	DOTRIZ

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* mem DZ decode & max */
#define YPOS_MDZ	42

#undef TRI_Y
#undef TRI_Z
#undef TRI_DZX
#define TRI_Y	YPOS_MDZ
#define TRI_Z	0x7f000000
#define TRI_DZX	0x00000000

    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0xff,0x00,0xff),	/* blendcol = yellow */

		/* 0 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	30
#	define TRI_DZY	0x00000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	31
#	define TRI_DZY	0x00020000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	32
#	define TRI_DZY	0x00040000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	33
#	define TRI_DZY	0x00080000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	34
#	define TRI_DZY	0x00100000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	35
#	define TRI_DZY	0x00200000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	36
#	define TRI_DZY	0x00400000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	37
#	define TRI_DZY	0x00800000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	38
#	define TRI_DZY	0x01000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	39
#	define TRI_DZY	0x02000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	40
#	define TRI_DZY	0x04000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	41
#	define TRI_DZY	0x08000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	42
#	define TRI_DZY	0x10000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	43
#	define TRI_DZY	0x20000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	44
#	define TRI_DZY	0x40000000
	DOTRIZ

		/* 1 */
#undef TRI_X
#undef TRI_DZY
#	define TRI_X	45
#	define TRI_DZY	0x80000000
	DOTRIZ

    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0xff,0x00,0xff),	/* blendcol = green */
    gsDPWord(0xef900cff,0xafaa4e50),	/* G_RM: p=blend, a=0, m=blend, b=1 */

		/* check it */

    gsDPWord(0xef900cff,0xafaa4e54),	/* G_RM: p=blend, a=0, m=blend, b=1 */



/*    gsDPSetBlendColor(0x01,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f01,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    
/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x02,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f02,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x04,0xff,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f04,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x05,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f05,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x08,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f08,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x09,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f09,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x10,0xff,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f10,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x11,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f11,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x20,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f20,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x21,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f21,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x40,0xff,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f40,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x41,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f41,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x80,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f80,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x81,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7f81,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xfe,0xff,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7e00,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xd8,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7d80,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xd0,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7d00,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xcf,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7cff,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xb0,0xff,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7b00,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xaf,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7aff,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x70,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x7700,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x6f,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x76ff,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xf0,0xff,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x6f00,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0xef,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x6eff,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x5f,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x5f00,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x5e,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x5eff,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x3f,0xff,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x3f00,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x3e,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x3eff,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

/*    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0000,0x0000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),



 /* test MAX with 0x100  (same data,rects as above) */
    gsDPSetPrimDepth(0x7f01,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f02,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f04,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f05,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f08,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f09,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f10,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f11,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f20,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f21,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f40,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f41,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f80,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f81,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7e00,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7d80,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7d00,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7cff,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7b00,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7aff,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7700,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x76ff,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x6f00,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x6eff,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x5f00,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x5eff,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x3f00,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x3eff,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x0000,0x0100),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),

 /* test MAX with 0x2000  (same data,rects as above) */
    gsDPSetPrimDepth(0x7f01,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f02,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f04,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f05,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f08,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f09,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f10,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f11,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f20,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f21,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f40,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f41,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f80,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7f81,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7e00,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7d80,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7d00,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7cff,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7b00,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7aff,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x7700,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x76ff,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x6f00,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x6eff,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x5f00,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x5eff,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x3f00,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x3eff,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),
    gsDPSetPrimDepth(0x0000,0x2000),
    gsDPFillRectangle(30,YPOS_MDZ,46,YPOS_MDZ+1),


/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* maxz test */

    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0x00,0x00,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4260),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_X
#undef TRI_Y
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	50
#	define TRI_Y	YPOS_MDZ
#	define TRI_Z	0x7fffffff
#	define TRI_DZX	0x00000000
#	define TRI_DZY	0x00000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	51
#	define TRI_Z	0x7fffc000
	DOTRIZ

    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4270),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_X
#undef TRI_Z
#	define TRI_X	50
#	define TRI_Z	0x7fffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	51
#	define TRI_Z	0x7fffc000
	DOTRIZ

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* in_front test */
#define YPOS_FRONT1	44
#define YPOS_FRONT2	55
#define YPOS_FRONT3	57
#if 0

    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0x00,0x00,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4260),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_X
#undef TRI_Y
#undef TRI_Z
#undef TRI_W
#undef TRI_H
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE
#	define TRI_X	30
#	define TRI_Y	YPOS_FRONT1
#	define TRI_W	256
#	define TRI_H	10
#	define TRI_Z	0x00000000
#	define TRI_DZX	0x0032d000
#	define TRI_DZY	0x00000000
#	define TRI_DZE	0x00550000
	DOTRIZ


    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0xff,0x00,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4250),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE
#	define TRI_Z	0x03520000
#	define TRI_DZX	0x0032d000
#	define TRI_DZY	0x00000000
#	define TRI_DZE	0xffab0000
	DOTRIZ
#endif /* 0 */

#if 0

    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0x00,0x00,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4260),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_X
#undef TRI_Y
#undef TRI_Z
#undef TRI_W
#undef TRI_H
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE
#	define TRI_X	30
#	define TRI_Y	YPOS_FRONT2
#	define TRI_W	256
#	define TRI_H	1
#	define TRI_Z	0x01000000
#	define TRI_DZX	0x0036b000
#	define TRI_DZY	0x00000000
#	define TRI_DZE	0x00000000
	DOTRIZ


    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0xff,0x00,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4250),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE
#	define TRI_Z	0x01000000
#	define TRI_DZX	0x0036b000
#	define TRI_DZY	0x00000000
#	define TRI_DZE	0x00000000
	DOTRIZ

    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0xff,0x00,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4250),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE
#	define TRI_Z	0x02000000
#	define TRI_DZX	0x0036b000
#	define TRI_DZY	0x00000000
#	define TRI_DZE	0x00000000
	DOTRIZ

    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4250),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE
#	define TRI_Z	0x00000000
#	define TRI_DZX	0x0036b000
#	define TRI_DZY	0x00000000
#	define TRI_DZE	0x00000000
	DOTRIZ



    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0x00,0x00,0xff),	/* blendcol = red */
    gsDPWord(0xef900cff,0xafaa4260),	/* G_RM: p=blend, a=0, m=blend, b=1 */
#undef TRI_X
#undef TRI_Y
#undef TRI_Z
#undef TRI_W
#undef TRI_H
#undef TRI_DZX
#undef TRI_DZY
#undef TRI_DZE
#	define TRI_X	30
#	define TRI_Y	YPOS_FRONT3
#	define TRI_W	256
#	define TRI_H	1
#	define TRI_Z	0x00000000
#	define TRI_DZX	0x0036c000
#	define TRI_DZY	0x00000000
#	define TRI_DZE	0x00000000
	DOTRIZ

    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xafaa4254),	/* G_RM: p=blend, a=0, m=blend, b=1 */

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0000,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0001,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0002,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0004,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0008,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0010,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0020,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0040,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0080,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0100,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0200,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0400,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x0800,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x1000,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x2000,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0xff,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x4000,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x4000,0x0000),
    gsDPFillRectangle(30,YPOS_FRONT3,286,YPOS_FRONT3+1),

#endif /* 0 */


/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* in_front test 2 */
#define YPOS_FRONT4	59




/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* zencode & zsel test (dz select tested above) */
#define YPOS_ZSEL	61

#undef TRI_X
#undef TRI_Y
#undef TRI_W
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	30
#	define TRI_Y	YPOS_ZSEL
#	define TRI_W	1
#	define TRI_Z	0x55555555
#	define TRI_DZX	0x00000000
#	define TRI_DZY	0x00000000
    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x2aaa,0x0000),
    gsDPWord(0xef900cff,0xafaa4220),	/* ZSEL = STEP */
	DOTRIZ

#undef TRI_X
#	define TRI_X	31
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xafaa4224),	/* zsel = PRIM */
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	32
#	define TRI_Z	0x2aaaaaaa
    gsDPPipeSync(),
    gsDPSetPrimDepth(0x5555,0x0000),
	DOTRIZ

#undef TRI_X
#	define TRI_X	33
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xafaa4220),	/* zsel = STEP */
	DOTRIZ

	/* test high (-) bit */
#undef TRI_X
#undef TRI_Z
#	define TRI_X	34
#	define TRI_Z	0xffffffff
    gsDPPipeSync(),
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	35
#	define TRI_Z	0x2aaaaaaa
    gsDPPipeSync(),
    gsDPSetPrimDepth(0xffff,0x0000),
    gsDPWord(0xef900cff,0xafaa4224),	/* zsel = PRIM */
	DOTRIZ



		/* try all different exponants */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xafaa4220),	/* zsel = STEP */

#undef TRI_X
#undef TRI_Z
#	define TRI_X	37
#	define TRI_Z	0x00000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	38
#	define TRI_Z	0x00080000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	39
#	define TRI_Z	0x10000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	40
#	define TRI_Z	0x10080000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	41
#	define TRI_Z	0x20000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	42
#	define TRI_Z	0x20080000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	43
#	define TRI_Z	0x3ff00000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	44
#	define TRI_Z	0x3fffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	45
#	define TRI_Z	0x40000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	46
#	define TRI_Z	0x40040000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	47
#	define TRI_Z	0x5ff80000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	48
#	define TRI_Z	0x5fffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	49
#	define TRI_Z	0x60000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	50
#	define TRI_Z	0x60020000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	51
#	define TRI_Z	0x6ffc0000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	52
#	define TRI_Z	0x6fffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	53
#	define TRI_Z	0x70000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	54
#	define TRI_Z	0x70010000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	55
#	define TRI_Z	0x77fe0000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	56
#	define TRI_Z	0x77ffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	57
#	define TRI_Z	0x78000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	58
#	define TRI_Z	0x78008000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	59
#	define TRI_Z	0x7bff0000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	60
#	define TRI_Z	0x7bffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	61
#	define TRI_Z	0x7c000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	62
#	define TRI_Z	0x7c004000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	63
#	define TRI_Z	0x7dff8000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	64
#	define TRI_Z	0x7dffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	65
#	define TRI_Z	0x7e000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	66
#	define TRI_Z	0x7e002000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	67
#	define TRI_Z	0x7effc000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	68
#	define TRI_Z	0x7effffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	69
#	define TRI_Z	0x7f000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	70
#	define TRI_Z	0x7f002000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	71
#	define TRI_Z	0x7f7fc000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	72
#	define TRI_Z	0x7f7fffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	73
#	define TRI_Z	0x7f800000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	74
#	define TRI_Z	0x7f802000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	75
#	define TRI_Z	0x7fffc000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	76
#	define TRI_Z	0x7fffffff
	DOTRIZ






#undef TRI_X
#undef TRI_Z
#	define TRI_X	77
#	define TRI_Z	0x7fbfffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	78
#	define TRI_Z	0x7fc00000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	79
#	define TRI_Z	0x7fc02000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	80
#	define TRI_Z	0x7f9fffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	81
#	define TRI_Z	0x7fa00000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	82
#	define TRI_Z	0x7fa02000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	83
#	define TRI_Z	0x7f8fffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	84
#	define TRI_Z	0x7f900000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	85
#	define TRI_Z	0x7f902000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	86
#	define TRI_Z	0x7f87ffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	87
#	define TRI_Z	0x7f880000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	88
#	define TRI_Z	0x7f882000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	89
#	define TRI_Z	0x7f83ffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	90
#	define TRI_Z	0x7f840000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	91
#	define TRI_Z	0x7f842000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	92
#	define TRI_Z	0x7f81ffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	93
#	define TRI_Z	0x7f820000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	94
#	define TRI_Z	0x7f822000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	95
#	define TRI_Z	0x7f80ffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	96
#	define TRI_Z	0x7f810000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	97
#	define TRI_Z	0x7f812000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	98
#	define TRI_Z	0x7f807fff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	99
#	define TRI_Z	0x7f808000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	100
#	define TRI_Z	0x7f80a000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	101
#	define TRI_Z	0x7f803fff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	102
#	define TRI_Z	0x7f804000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	103
#	define TRI_Z	0x7f806000
	DOTRIZ





/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* end  */
    gsSPTexture(0, 0, 0, 0, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
    

};

Gfx BL_test2_dl3[] = {
    gsDPPipeSync(),

    gsDPSetCombineMode (G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTexturePersp(G_TP_NONE),


    gsDPSetCombineMode (G_CC_PRIMITIVE, G_CC_PRIMITIVE),


/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* zencode & zsel test (dz select tested above) */
#define YPOS_ZSEL	61

#undef TRI_X
#undef TRI_Y
#undef TRI_W
#undef TRI_Z
#undef TRI_DZX
#undef TRI_DZY
#	define TRI_X	30
#	define TRI_Y	YPOS_ZSEL
#	define TRI_W	1
#	define TRI_Z	0x55555555
#	define TRI_DZX	0x00000000
#	define TRI_DZY	0x00000000
    gsDPPipeSync(),
    gsDPSetBlendColor(0xff,0x00,0x00,0xff),	/* blendcol = red */
    gsDPSetPrimDepth(0x2aaa,0x0000),
    gsDPWord(0xef900cff,0xafaa4220),	/* ZSEL = STEP */
	DOTRIZ

#undef TRI_X
#	define TRI_X	31
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xafaa4224),	/* zsel = PRIM */
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	32
#	define TRI_Z	0x2aaaaaaa
    gsDPPipeSync(),
    gsDPSetPrimDepth(0x5555,0x0000),
	DOTRIZ

#undef TRI_X
#	define TRI_X	33
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xafaa4220),	/* zsel = STEP */
	DOTRIZ

	/* test high (-) bit */
#undef TRI_X
#undef TRI_Z
#	define TRI_X	34
#	define TRI_Z	0xffffffff
    gsDPPipeSync(),
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	35
#	define TRI_Z	0x2aaaaaaa
    gsDPPipeSync(),
    gsDPSetPrimDepth(0xffff,0x0000),
    gsDPWord(0xef900cff,0xafaa4224),	/* zsel = PRIM */
	DOTRIZ



		/* try all different exponants */
    gsDPPipeSync(),
    gsDPWord(0xef900cff,0xafaa4220),	/* zsel = STEP */

#undef TRI_X
#undef TRI_Z
#	define TRI_X	37
#	define TRI_Z	0x00000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	38
#	define TRI_Z	0x00080000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	39
#	define TRI_Z	0x10000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	40
#	define TRI_Z	0x10080000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	41
#	define TRI_Z	0x20000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	42
#	define TRI_Z	0x20080000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	43
#	define TRI_Z	0x3ff00000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	44
#	define TRI_Z	0x3fffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	45
#	define TRI_Z	0x40000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	46
#	define TRI_Z	0x40040000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	47
#	define TRI_Z	0x5ff80000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	48
#	define TRI_Z	0x5fffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	49
#	define TRI_Z	0x60000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	50
#	define TRI_Z	0x60020000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	51
#	define TRI_Z	0x6ffc0000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	52
#	define TRI_Z	0x6fffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	53
#	define TRI_Z	0x70000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	54
#	define TRI_Z	0x70010000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	55
#	define TRI_Z	0x77fe0000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	56
#	define TRI_Z	0x77ffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	57
#	define TRI_Z	0x78000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	58
#	define TRI_Z	0x78008000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	59
#	define TRI_Z	0x7bff0000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	60
#	define TRI_Z	0x7bffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	61
#	define TRI_Z	0x7c000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	62
#	define TRI_Z	0x7c004000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	63
#	define TRI_Z	0x7dff8000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	64
#	define TRI_Z	0x7dffffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	65
#	define TRI_Z	0x7e000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	66
#	define TRI_Z	0x7e002000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	67
#	define TRI_Z	0x7effc000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	68
#	define TRI_Z	0x7effffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	69
#	define TRI_Z	0x7f000000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	70
#	define TRI_Z	0x7f002000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	71
#	define TRI_Z	0x7f7fc000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	72
#	define TRI_Z	0x7f7fffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	73
#	define TRI_Z	0x7f800000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	74
#	define TRI_Z	0x7f802000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	75
#	define TRI_Z	0x7fffc000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	76
#	define TRI_Z	0x7fffffff
	DOTRIZ






#undef TRI_X
#undef TRI_Z
#	define TRI_X	77
#	define TRI_Z	0x7fbfffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	78
#	define TRI_Z	0x7fc00000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	79
#	define TRI_Z	0x7fc02000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	80
#	define TRI_Z	0x7f9fffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	81
#	define TRI_Z	0x7fa00000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	82
#	define TRI_Z	0x7fa02000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	83
#	define TRI_Z	0x7f8fffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	84
#	define TRI_Z	0x7f900000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	85
#	define TRI_Z	0x7f902000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	86
#	define TRI_Z	0x7f87ffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	87
#	define TRI_Z	0x7f880000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	88
#	define TRI_Z	0x7f882000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	89
#	define TRI_Z	0x7f83ffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	90
#	define TRI_Z	0x7f840000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	91
#	define TRI_Z	0x7f842000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	92
#	define TRI_Z	0x7f81ffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	93
#	define TRI_Z	0x7f820000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	94
#	define TRI_Z	0x7f822000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	95
#	define TRI_Z	0x7f80ffff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	96
#	define TRI_Z	0x7f810000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	97
#	define TRI_Z	0x7f812000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	98
#	define TRI_Z	0x7f807fff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	99
#	define TRI_Z	0x7f808000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	100
#	define TRI_Z	0x7f80a000
	DOTRIZ


#undef TRI_X
#undef TRI_Z
#	define TRI_X	101
#	define TRI_Z	0x7f803fff
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	102
#	define TRI_Z	0x7f804000
	DOTRIZ

#undef TRI_X
#undef TRI_Z
#	define TRI_X	103
#	define TRI_Z	0x7f806000
	DOTRIZ





/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* farther/nearer tests (decal) */

    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0xff,0x00,0xff),	/* blendcol = green */
    gsDPWord(0xef900cff,0xafaa4214),	/* ZSEL = STEP */


    gsDPSetPrimDepth(0x0000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

    gsDPSetPrimDepth(0x7e00,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

    gsDPSetPrimDepth(0x7eff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

    gsDPSetPrimDepth(0x7dff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

    gsDPSetPrimDepth(0x7bff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

    gsDPSetPrimDepth(0x67ff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

    gsDPSetPrimDepth(0x5fff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

    gsDPSetPrimDepth(0x3fff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),


    gsDPPipeSync(),
    gsDPSetBlendColor(0x00,0x00,0xff,0xff),	/* blendcol = blue */
    gsDPWord(0xef900cff,0xafaa4e14),		/* DECAL MODE */
/* note: below is same data as above, but using decal mode and
   repeated with several DZ values */

/* DZ = 0 */
    gsDPSetPrimDepth(0x0000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 1 */
    gsDPSetPrimDepth(0x0000,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0001),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 2 */
    gsDPSetPrimDepth(0x0000,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0002),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 4 */
    gsDPSetPrimDepth(0x0000,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0004),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 8 */
    gsDPSetPrimDepth(0x0000,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0008),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 10 */
    gsDPSetPrimDepth(0x0000,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0010),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 20 */
    gsDPSetPrimDepth(0x0000,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0020),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 40 */
    gsDPSetPrimDepth(0x0000,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0040),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 80 */
    gsDPSetPrimDepth(0x0000,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0080),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 100 */
    gsDPSetPrimDepth(0x0000,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0100),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 200 */
    gsDPSetPrimDepth(0x0000,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0200),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 400 */
    gsDPSetPrimDepth(0x0000,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0400),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 800 */
    gsDPSetPrimDepth(0x0000,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x0800),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 1000 */
    gsDPSetPrimDepth(0x0000,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x1000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 2000 */
    gsDPSetPrimDepth(0x0000,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x2000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 4000 */
    gsDPSetPrimDepth(0x0000,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x4000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),

/* DZ = 8000 */
    gsDPSetPrimDepth(0x0000,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7fff,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f00,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f01,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f02,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f03,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f04,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f05,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f07,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f08,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f09,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f0f,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f10,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f11,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f1f,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f20,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f21,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f3f,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f40,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f41,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f7f,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f80,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7f81,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e00,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7e01,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7eff,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c00,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7c01,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7dff,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7800,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7801,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7bff,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7000,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x7001,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x67ff,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6000,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x6002,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x5fff,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4000,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x4004,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x3fff,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0000,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),
    gsDPSetPrimDepth(0x0008,0x8000),
    gsDPFillRectangle(37,YPOS_ZSEL,104,YPOS_ZSEL+1),


/*******************************************************************/
/*******************************************************************/
/*******************************************************************/
/* end  */
    gsSPTexture(0, 0, 0, 0, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
    

};

/*
 * TO ADD A TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx display list must be extern'd in bl.h, then
 * added to the 'testList_bl' table in bl.c as a Gfx pointer field of a
 * GfxTest_t struct.  You must also decide whether the existing top level DL's
 * will suffice for your application (you may need to provide a new top level
 * DL of your own design in toplevel.c).
 *
 */
