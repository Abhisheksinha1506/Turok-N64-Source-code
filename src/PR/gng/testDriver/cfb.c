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
 * File:	cfb.c
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:	Define the cfb so it may be fixed in memory by the spec file
 *
 */

/*
 * Put the Color Frame Buffer below zbuffer.  Place it so that 16 bit or
 * 32 bit buffer will fit
 * This gives space for 2 16 bit or 1 32 bit buffers
 */

#include <ultra64.h>

/* Create space for 2 high-res 32 bit framebuffers. retain */
/* old name for compatibility with existing tests          */

unsigned short    cfb_16_a[640*480];




