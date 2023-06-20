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
 * File:	tf.h
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:	Declarations & definitions for the texture filter test module
 */

/*
 * ifdef needed because this file could be included by "spec"
 */
#ifdef _LANGUAGE_C

/* ADD VARIABLES */

/* ADD TEST CASE: test frame display lists: */
extern Gfx 	TF_yuv_multiplicand_dl[];
extern Gfx 	TF_load_RGBA32pattern_dl[];
extern Gfx 	TF_load_rand_dl[];
extern Gfx 	TF_perspectivetex_dl[];
extern Gfx 	TF_lerp_dl[];

#ifdef SKIP
extern Gfx 	TF_yuvbars_dl[];
extern Gfx 	TF_RGBA32_point_dl[];
#endif

#endif	/* _LANGUAGE_C */
