/*
 * Do edit this file.  It was generated
 * by "acorn" from the file "RGBA16dana.h".
 *
 *   Size: 1 x 1
 *   Number of channels: 3
 *   Number of bits per texel: 16 (G_IM_SIZ_16b)
 *   Format of texel: G_IM_FMT_RGBA
 *
 * Example usage:
 *
 *   gsSPTexture (128, 128, G_TX_RENDERTILE, 1),
 *   gsDPPipeSync (),
 *   gsDPSetCombineMode (G_CC_MODULATERGBA, G_CC_MODULATERGBA),
 *   gsDPSetTexturePersp (G_TP_PERSP),
 *   gsDPSetTextureDetail (G_TD_CLAMP),
 *   gsDPSetTextureLOD (G_TL_TILE),
 *   gsDPSetTextureLUT (G_TT_NONE),
 *   gsDPLoadTextureBlock (RGBA16dana, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32,
 *     G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
 *     G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
 */

#if 0	/* Image preview */
	+-+
	|*| 	one texel
	+-+
#endif

static Gfx RGBA16red2_C_dummy_aligner1[] = { gsSPEndDisplayList() };

unsigned short RGBA16red2[] = {
	0xf801, 
	0x07c1, 
	0x003f, 
	0xffff, 
	0x7fff, 
	0xf83f, 
	0xffc1, 
	0x7bdf, 
};
/* 0xdcdd  = skin color */
/* 0xf801  = red        */
/* 0x07c1  = green      */
/* 0x003f  = blue       */
