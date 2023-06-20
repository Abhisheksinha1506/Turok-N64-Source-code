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
 * File:	toplevel.h
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:	Contains extern declarations for common top level DL routines 
 *		used for setting up the RSP/RDP's rendering pipe.
 */

/* procedure to do the work for placebo case: */
extern void 
testCasePlacebo(Dynamic *, Gfx *);

/* procedure to do the work with simple ortho projection: */
extern void
testCaseProcSimpleOrtho(Dynamic *, Gfx *);

/* procedure to do the work with simple ortho projection: */
extern void
testCaseProcRotatedOrtho(Dynamic *, Gfx *);

/* procedure to do the work with right side up ortho projection: */
extern void
testCaseProcRSUOrtho(Dynamic *, Gfx *);

/* procedure to do the work with simple Z ortho projection: */
extern void
testCaseProcZOrtho(Dynamic *, Gfx *);

/* procedure to do the work with a simple lookat: */
extern void
testCaseSimpleLookAt(Dynamic *, Gfx *);

extern void
testCaseLookAtReflect(Dynamic *, Gfx *);

extern void
testCaseProcASOrtho(Dynamic *, Gfx *);

extern void
testCasePerspectiveTex(Dynamic *, Gfx *);

extern void
testCaseProcVideo(Dynamic *, Gfx *);

extern void
testCaseBigOrtho(Dynamic *, Gfx *);

extern void
testCaseRGBA32tex(Dynamic *, Gfx *);
