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
 * File:	bl.h
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:	Declarations & definitions for the blender test module
 */

/*
 * ifdef needed because this file may be included by "spec"
 */
#ifdef _LANGUAGE_C

/* ADD VARIABLES */

/* ADD TEST CASE: test frame display lists: */
extern Gfx 	BL_placebo_dl[];
extern Gfx 	BL_test2_dl_all[];
extern Gfx 	BL_test2_dl1[];
extern Gfx 	BL_test2_dl2[];
extern Gfx 	BL_test2_dl3[];
extern void	testCaseBL1(Dynamic *dynamicp, Gfx *module_test);

#endif	/* _LANGUAGE_C */
