/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1996 Silicon Graphics, Inc.                *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

/*
 * File:	rdpatt.h
 * Creator:	hal@sgi.com
 * Purpose:	Declarations & definitions for the rdp attribute test module
 */

/*
 * ifdef needed because this file is included by "spec"
 */
#ifdef _LANGUAGE_C

/* ADD VARIABLES */
extern int frameNum;

/* ADD TEST CASE: test frame display lists: */
extern Gfx 	rdpatt_placebo_dl[];
extern Gfx 	rdpatt_square0[];
extern Gfx 	rdpatt_square1[];
extern Gfx 	rdpatt_square2[];
extern Gfx 	rdpatt_rectangle3[];
extern Gfx	rdpatt_triangles[];
extern Gfx 	rdpatt_shade_acc0[];
extern Gfx 	rdpatt_shade_acc1[];
extern Gfx 	rdpatt_shade_acc2[];
extern Gfx 	rdpatt_tex_acc0[];
extern Gfx 	rdpatt_square9[];
extern Gfx 	rdpatt_square10[];
extern Gfx 	rdpatt_xluramp[];
extern Gfx 	rdpatt_clrbar[];
extern Gfx 	rdpatt_cc_modes[];
extern Gfx 	rdpatt_rectangle14[];
extern Gfx 	rdpatt_rectangle15[];
extern Gfx 	rdpatt_rectangle16[];
extern Gfx 	rdpatt_rectangle17[];
extern Gfx 	rdpatt_rectangle18[];
extern Gfx 	rdpatt_square20[];
extern Gfx 	rdpatt_square21[];
extern Gfx 	rdpatt_cone_dl[];
extern Gfx 	rdpatt_box_dl[];
extern Gfx 	rdpatt_box1_dl[];
extern Gfx 	rdpatt_icosa_dl[];
extern Gfx 	rdpatt_torus_dl[];
extern Gfx 	rdpatt_ground_dl[];
extern Gfx 	rdpatt_ground_nzb_dl[];
extern Gfx 	rdpatt_tree0_dl[];
extern Gfx 	rdpatt_tree1_dl[];
extern Gfx 	rdpatt_tree2_dl[];
extern Gfx 	rdpatt_tree3_dl[];
extern Gfx 	rdpatt_texedge_dl[];
extern Gfx 	rdpatt_zbuf_dl[];
extern Gfx 	rdpatt_vitriangle[];
extern Gfx 	rdpatt_spin_torus_dl[];
extern Gfx	rdpatt_blendrange_dl[];
extern Gfx 	rdpatt_frac_dl[];
extern Gfx 	rdpatt_u64_dl[];

extern unsigned char 	IA4tree2[];

#endif	/* _LANGUAGE_C */
