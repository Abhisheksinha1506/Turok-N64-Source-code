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
 * File:	rdpcov.h
 * Creator:	hal@sgi.com
 * Purpose:	Declarations & definitions for the rdp coverage test module
 */

/*
 * ifdef needed because this file is included by "spec"
 */
#ifdef _LANGUAGE_C

/* ADD VARIABLES */

/* ADD TEST CASE: test frame display lists: */
extern Gfx 	rdpcov_placebo_dl[];
extern Gfx 	rdpcov_square0[];
extern Gfx 	rdpcov_square1[];
extern Gfx 	rdpcov_square2[];
extern Gfx 	rdpcov_square3[];
extern Gfx	rdpcov_triangles[];
extern Gfx	rdpcov_fogtriangles[];
extern Gfx 	rdpcov_subpix_scissor[];
extern Gfx 	rdpcov_triangle10[];

extern Gfx 	rdpcov_square20[];
extern Gfx 	rdpcov_square21[];
extern Gfx 	rdpcov_square22[];
extern Gfx 	rdpcov_square23[];
extern Gfx 	rdpcov_square24[];

extern Gfx 	rdpcov_gfx_25[];
extern Gfx 	rdpcov_case_edge_00[];
extern Gfx 	rdpcov_case_vertex_00[];
extern Gfx 	rdpcov_case_skinny_00[];
extern Gfx 	rdpcov_case_tiny_00[];
extern Gfx 	rdpcov_case_disc_00[];

extern Gfx      rdpcov_lines1[];
extern Gfx      rdpcov_lines2[];
extern Gfx      rdpcov_lclip1[];
extern Gfx      rdpcov_cbar1[];
extern Gfx      rdpcov_FooTri[];

extern Gfx 	rdpcov_ball_dl[];
extern Gfx 	rdpcov_test32_dl[];

extern Gfx 	rdpcov_logo_dl[];
extern Gfx 	rdpcov_bg33_dl[];

extern Gfx 	rdpcov_ball_tex_dl[];

extern Gfx	rdpcov_dithertest[];

extern Gfx	rdpcov_CSEWcritical_list[];

extern unsigned char 	RGBA16grid[];

#endif	/* _LANGUAGE_C */
