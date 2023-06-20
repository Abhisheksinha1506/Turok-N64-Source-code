/*
 * Do not edit this file.  It was automatically generated
 * by "rgb2c" from the file "mymip.rgb".
 *
/*
 *   Size: 16 x 16
 *   Number of channels: 3
 *   Number of bits per texel: 16 (G_IM_SIZ_16b)
 *   Format of texel: G_IM_FMT_RGBA
 *
 * Example usage:
 *
 *   gsSPTexture (128, 128, (levels-1), G_TX_RENDERTILE, 1),
 *   gsDPPipeSync (),
 *   gsDPSetCombineMode (G_CC_MODULATERGBA, G_CC_MODULATERGBA),
 *   gsDPSetTexturePersp (G_TP_PERSP),
 *   gsDPSetTextureDetail (G_TD_CLAMP),
 *   gsDPSetTextureLOD (G_TL_TILE),
 *   gsDPSetTextureLUT (G_TT_NONE),
 *   gsDPSetTextureFilter (G_TF_BILERP),
 *   gsDPSetTextureConvert(G_TC_FILT),
 *   gsDPLoadTextureBlock (RGBA16mymipMM, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0
 *     G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
 *     G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
 */

#if 0	/* Image preview */
	+----------------+
	|.+....+..+....+.|
	|..+..+....+..+..|
	|...++......++...|
	|....+.......+...|
	|..+..+....+..+..|
	|.+....+..+....+.|
	|+......++......+|
	|+.......+.......|
	|.+....+..+....+.|
	|..+..+....+..+..|
	|...++......++...|
	|....+.......+...|
	|..+..+....+..+..|
	|.+....+..+....+.|
	|+......++......+|
	|+.......+.......|
	+----------------+
#endif

static Gfx RGBA16mymipMM_dummy_aligner2[] = { gsSPEndDisplayList() };

unsigned short RGBA16mymipMM_buf[] = {
	0x003f, 0x53ff, 0x0001, 0x0001, 	0x0001, 0x0001, 0x53ff, 0x0021, 
	0x003f, 0x53ff, 0x0001, 0x0001, 	0x0001, 0x0001, 0x53ff, 0x003f, 
	0x53ff, 0x0001, 0x0021, 0x003f, 	0x003f, 0x0021, 0x0001, 0x53ff, 
	0x53ff, 0x0001, 0x0021, 0x003f, 	0x003f, 0x0021, 0x0001, 0x53ff, 
	0x0001, 0x0021, 0x003f, 0x53ff, 	0x53ff, 0x003f, 0x0021, 0x0001, 
	0x0001, 0x0021, 0x003f, 0x53ff, 	0x53ff, 0x003f, 0x0021, 0x0001, 
	0x0021, 0x003f, 0x0001, 0x0001, 	0x0001, 0x0001, 0x53ff, 0x0021, 
	0x0021, 0x003f, 0x0001, 0x0001, 	0x0001, 0x0001, 0x53ff, 0x0021, 
	0x0001, 0x0001, 0x53ff, 0x0021, 	0x003f, 0x53ff, 0x0001, 0x0001, 
	0x0001, 0x0001, 0x53ff, 0x0021, 	0x003f, 0x53ff, 0x0001, 0x0001, 
	0x003f, 0x0021, 0x0001, 0x53ff, 	0x53ff, 0x0001, 0x0021, 0x003f, 
	0x003f, 0x0021, 0x0001, 0x53ff, 	0x53ff, 0x0001, 0x0021, 0x003f, 
	0x53ff, 0x003f, 0x0021, 0x0001, 	0x0001, 0x0021, 0x003f, 0x53ff, 
	0x53ff, 0x003f, 0x0021, 0x0001, 	0x0001, 0x0021, 0x003f, 0x53ff, 
	0x0001, 0x0001, 0x53ff, 0x0021, 	0x0021, 0x003f, 0x0001, 0x0001, 
	0x0001, 0x0001, 0x53ff, 0x0021, 	0x0021, 0x003f, 0x0001, 0x0001, 
	0x003f, 0x53ff, 0x0001, 0x0001, 	0x0001, 0x0001, 0x53ff, 0x0021, 
	0x003f, 0x53ff, 0x0001, 0x0001, 	0x0001, 0x0001, 0x53ff, 0x0021, 
	0x53ff, 0x0001, 0x0021, 0x003f, 	0x003f, 0x0021, 0x0001, 0x53ff, 
	0x53ff, 0x0001, 0x0021, 0x003f, 	0x003f, 0x0021, 0x0001, 0x53ff, 
	0x0001, 0x0021, 0x003f, 0x53ff, 	0x53ff, 0x003f, 0x0021, 0x0001, 
	0x0001, 0x0021, 0x003f, 0x53ff, 	0x53ff, 0x003f, 0x0021, 0x0001, 
	0x0021, 0x003f, 0x0001, 0x0001, 	0x0001, 0x0001, 0x53ff, 0x0021, 
	0x0021, 0x003f, 0x0001, 0x0001, 	0x0001, 0x0001, 0x53ff, 0x0021, 
	0x0001, 0x0001, 0x53ff, 0x0021, 	0x003f, 0x53ff, 0x0001, 0x0001, 
	0x0001, 0x0001, 0x53ff, 0x0021, 	0x003f, 0x53ff, 0x0001, 0x0001, 
	0x003f, 0x0021, 0x0001, 0x53ff, 	0x53ff, 0x0001, 0x0021, 0x003f, 
	0x003f, 0x0021, 0x0001, 0x53ff, 	0x53ff, 0x0001, 0x0021, 0x003f, 
	0x53ff, 0x003f, 0x0021, 0x0001, 	0x0001, 0x0021, 0x003f, 0x53ff, 
	0x53ff, 0x003f, 0x0021, 0x0001, 	0x0001, 0x0021, 0x003f, 0x53ff, 
	0x0001, 0x0001, 0x53ff, 0x0021, 	0x0021, 0x003f, 0x0001, 0x0001, 
	0x0001, 0x0001, 0x53ff, 0x0021, 	0x0021, 0x003f, 0x0001, 0x0001, 
	0x1937, 0x1917, 0x0845, 0x196b, 	0x1933, 0x1917, 0x0845, 0x196d, 
	0x3231, 0x0861, 0x000f, 0x192f, 	0x3231, 0x0861, 0x000f, 0x192f, 
	0x0845, 0x196b, 0x1933, 0x1917, 	0x0845, 0x196b, 0x1933, 0x1917, 
	0x000f, 0x192f, 0x3231, 0x0861, 	0x000f, 0x192f, 0x3231, 0x0861, 
	0x1933, 0x1917, 0x0845, 0x196b, 	0x1933, 0x1917, 0x0845, 0x196b, 
	0x3231, 0x0861, 0x000f, 0x192f, 	0x3231, 0x0861, 0x000f, 0x192f, 
	0x0845, 0x196b, 0x1933, 0x1917, 	0x0845, 0x196b, 0x1933, 0x1917, 
	0x000f, 0x192f, 0x3231, 0x0861, 	0x000f, 0x192f, 0x3231, 0x0861, 
	0x1929, 0x10db, 0x1927, 0x10db, 	0x10db, 0x1927, 0x10db, 0x1927, 
	0x1927, 0x10db, 0x1927, 0x10db, 	0x10db, 0x1927, 0x10db, 0x1927, 
	0x1921, 0x1921, 0x0000, 0x0000, 	0x0000, 0x0000, 0x1921, 0x1921, 
	0x1921, 0x0000, 0x0000, 0x0000, };

Gfx RGBA16mymipMM_dl[] = {
	gsDPSetTextureImage( 0, 2, 1, RGBA16mymipMM_buf),
	gsDPSetTile( 0, 2, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0),
	gsDPLoadBlock( G_TX_LOADTILE, 0, 0, 348, 0),
	gsDPSetTile(0, 2, 4, 0, 0, 0, 0, 4, 0, 0, 4, 0),
	gsDPSetTileSize( 0,  0, 0, 15 << G_TEXTURE_IMAGE_FRAC, 15 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 2, 64, 1, 0, 0, 3, 1, 0, 3, 1),
	gsDPSetTileSize( 1,  0, 0, 7 << G_TEXTURE_IMAGE_FRAC, 7 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 1, 80, 2, 0, 0, 2, 2, 0, 2, 2),
	gsDPSetTileSize( 2,  0, 0, 3 << G_TEXTURE_IMAGE_FRAC, 3 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 1, 84, 3, 0, 0, 1, 3, 0, 1, 3),
	gsDPSetTileSize( 3,  0, 0, 1 << G_TEXTURE_IMAGE_FRAC, 1 << G_TEXTURE_IMAGE_FRAC),
	gsDPSetTile(0, 2, 1, 86, 4, 0, 0, 0, 4, 0, 0, 4),
	gsDPSetTileSize( 4,  0, 0, 0 << G_TEXTURE_IMAGE_FRAC, 0 << G_TEXTURE_IMAGE_FRAC),
	gsSPEndDisplayList(),
	gsSPEndDisplayList(),
	gsSPEndDisplayList(),
};
