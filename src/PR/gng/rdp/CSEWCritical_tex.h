/*
 *   Size: 8 x 8
 *   Number of channels: 3
 *   Number of bits per texel: 16 (G_IM_SIZ_16b)
 *   Format of texel: G_IM_FMT_RGBA
 *
 * Example usage:
 *
 *   gsSPTexture (128, 128, 0, G_TX_RENDERTILE, 1),
 *   gsDPPipeSync (),
 *   gsDPSetCombineMode (G_CC_MODULATERGBA, G_CC_MODULATERGBA),
 *   gsDPSetTexturePersp (G_TP_PERSP),
 *   gsDPSetTextureDetail (G_TD_CLAMP),
 *   gsDPSetTextureLOD (G_TL_TILE),
 *   gsDPSetTextureLUT (G_TT_NONE),
 *   gsDPSetTextureFilter (G_TF_BILERP),
 *   gsDPSetTextureConvert(G_TC_FILT),
 *   gsDPLoadTextureBlock (RGBA16grid, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0
 *     G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
 *     G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
 */

#if 0	/* Image preview */
	+--------------------------------+
	|,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|++++++++++++++++++++++++++++++++|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|oooooooooooooooooooooooooooooooo|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	|~.......+.......o.......o.......|
	+--------------------------------+
#endif

static Gfx CSEWCritical_tex_C_dummy_aligner1[] = { gsSPEndDisplayList() };

unsigned short CSEWCritical_tex[] = {
	0xffff, 0xffff, 0xf801, 0xf801, 0xf801, 0xf801, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xf801, 0xf801, 0xf801, 0xf801, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xf801, 0xf801, 0xf801, 0xf801, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xf801, 0xf801, 0xf801, 0xf801, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xf801, 0xf801, 0xf801, 0xf801, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xf801, 0xf801, 0xf801, 0xf801, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xf801, 0xf801, 0xf801, 0xf801, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xf801, 0xf801, 0xf801, 0xf801, 0xffff, 0xffff, 
};
