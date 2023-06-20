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
 * File:	tm.h
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:	Declarations & definitions for the texture memory test module
 */

/*
 * ifdef needed because this file is included by "spec"
 */
#ifdef _LANGUAGE_C

/* ADD VARIABLES */

/* ADD TEST CASE: test frame display lists: */
extern Gfx 	TM_placebo_dl[];
extern Gfx 	TM_RGBA16_dl[];
extern Gfx 	TM_RGBA32_dl[];
extern Gfx 	TM_YUV_dl[];
extern Gfx 	TM_IA_dl[];
extern Gfx 	TM_I_dl[];
extern Gfx 	TM_CI_dl[];
extern Gfx 	TM_all_dl[];

#endif	/* _LANGUAGE_C */
