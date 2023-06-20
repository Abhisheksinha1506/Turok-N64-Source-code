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
 * File:	ms.h
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:	Declarations & definitions for the memspan test modules
 */

/*
 * ifdef needed because this file is included by "spec"
 */
#ifdef _LANGUAGE_C

/* ADD VARIABLES */

/* ADD TEST CASE: test frame display lists: */
extern Gfx 	MS_placebo_dl[];
extern Gfx      MS_loadCopy[];
extern Gfx      MS_loadTlut[];
extern Gfx      MS_render[];
extern Gfx      MS_zCases[];
extern Gfx      MS_cyc2Blend[];
extern Gfx      MS_fill[];
extern Gfx      MS_address[];
extern Gfx      MS_longSpanLoad[];
extern Gfx      MS_longSpanRender[];
extern Gfx      MS_loadCopy2[];

#endif	/* _LANGUAGE_C */
