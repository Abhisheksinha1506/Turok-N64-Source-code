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
 * File:	texture.h
 * Creator:	hal@sgi.com
 * Create Date:	Wed Sep 27 17:40:23 PDT 1995
 * Purpose:
 *
 * External declarations for texture data which is to be loaded at a fixed, 
 * known location (0x80196000) by makerom, so that we'll know
 * where to load this data when we go to generate .rdram files.
 *
 * If you feel the urge to modify a test, see the comment at
 * the top of main.c for details.
 */

extern unsigned short RGBA16checkerMM[];
extern unsigned char  spacer[];
extern unsigned short RGBA16data[];
extern unsigned short RGBA16longspan[];
extern unsigned short loadTlut[];
extern unsigned short RGBA16data_bar[];

extern unsigned short map_a5[];
extern unsigned short map_rand[];
extern unsigned short map_5a[];
extern unsigned short map_rand_comp[];
extern unsigned long  map_rand32[];
extern unsigned short RGBA16powersOfTwoMM[];

extern unsigned short cc_texture[];
extern unsigned char cc_lerp_texture[];

extern unsigned char YUVbars[];
extern unsigned char TF_multiplicands[];
extern unsigned char tf_lerp_texture[];
extern unsigned char RGBA32pattern[];
extern unsigned short RGBA16dana[];

extern unsigned short map_cs16_rand[]; 
