
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
 * File:	rdpverif.h
 * Creator:	hsa@sgi.com
 * Create Date:	Fri Oct 14 11:55:15 PDT 1994
 *
 */

/*
 * ifdef needed because this file is included by "spec"
 */
#ifdef _LANGUAGE_C

/* ADD VARIABLES */


/* ADD TEST CASE: test frame display lists: */
extern Gfx	rdptex_placebo_dl[];
extern Gfx	rdptex_square0[];
extern Gfx	rdptex_square1[];
extern Gfx	rdptex_square2[];
extern Gfx	rdptex_texfmt_RGBA16[];
extern Gfx	rdptex_texfmt_IA16[];
extern Gfx	rdptex_texfmt_IA8[];
extern Gfx	rdptex_texfmt_IA4[];
extern Gfx	rdptex_loadtile_RGBA16[];
extern Gfx	rdptex_loadtile_I4[];
extern Gfx	rdptex_loadtile_I8[];
extern Gfx	rdptex_loadtile_IA16[];
extern Gfx	rdptex_loadtile_nonalign_RGBA16[];
extern Gfx	rdptex_loadtile_8b[];
extern Gfx	rdptex_loadtile_4b[];
extern Gfx	rdptex_texfmt_I8[];
extern Gfx	rdptex_texfmt_I4[];
extern Gfx	rdptex_texture_regression[];
extern Gfx	rdptex_texture_regression2[];
extern Gfx	rdptex_cpyfmt_RGBA16[];
extern Gfx	rdptex_cpyfmt_IA8[];
extern Gfx	rdptex_interlace_odd_texture_regression[];
extern Gfx	rdptex_interlace_even_texture_regression[];
extern Gfx	rdptex_interlace_odd_texture_regression2[];
extern Gfx	rdptex_interlace_even_texture_regression2[];
extern Gfx	rdptex_copyRGBA16[];
extern Gfx	rdptex_magRGBA16[];
extern Gfx	rdptex_lodRGBA16MM[];
extern Gfx	rdptex_rww_lodRGBA16MM[];
extern Gfx	rdptex_detail32RGBA16MM[];
extern Gfx	rdptex_iorand_cosim_regression[];
extern Gfx	rdptex_sharpenRGBA16[];
extern Gfx	rdptex_copyAlphaRGBA16[];
extern Gfx	rdptex_detail16RGBA16MM[];
extern Gfx	rdptex_cycle2_exact[];

extern Gfx 	rdptex_cone_dl[];
extern Gfx 	rdptex_box_dl[];
extern Gfx 	rdptex_box1_dl[];
extern Gfx 	rdptex_icosa_dl[];
extern Gfx 	rdptex_torus_dl[];
extern Gfx 	rdptex_ground_dl[];
extern Gfx 	rdptex_tree0_dl[];
extern Gfx 	rdptex_tree1_dl[];
extern Gfx 	rdptex_tree2_dl[];
extern Gfx 	rdptex_tree3_dl[];

extern Vp		iorand_cosim_regression_viewport_lr;

extern Vtx		txfmt_q20[];
extern unsigned char	I4oddcheck[];

extern Vtx		txfmt_q21[];
extern unsigned short	RGBA16mario[];

extern Vtx              box_vtx[];
extern unsigned short   RGBA16mario_2[];

extern unsigned short RGBA16mario32[];

extern Gfx	rdptex_load_tlut_dl[];
extern unsigned short	Tlut0[];

extern Gfx	rdptex_frame_clear16b[];
extern Gfx	rdptex_frame1_clear8b[];
extern Gfx	rdptex_frame2_clear8b[];
extern Gfx	rdptex_frame_clear32b[];
extern Gfx	rdptex_frame1_clear16b_ilo[];
extern Gfx	rdptex_frame2_clear16b_ilo[];
extern Gfx	rdptex_frame1_clear16b_ile[];
extern Gfx	rdptex_frame2_clear16b_ile[];
extern Gfx	rdptex_frame1_clear8b_ilo[];
extern Gfx	rdptex_frame2_clear8b_ilo[];
extern Gfx	rdptex_frame1_clear8b_ile[];
extern Gfx	rdptex_frame2_clear8b_ile[];
extern Gfx	rdptex_frame1_clear32b_ilo[];
extern Gfx	rdptex_frame2_clear32b_ilo[];
extern Gfx	rdptex_frame_clear32b_ile[];

extern Gfx	rdptex_yuvbars_dl[];

#endif	/* _LANGUAGE_C */
