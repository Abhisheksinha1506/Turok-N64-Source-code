/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1996, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

#include <asm.h>
#include <regdef.h>
#include <R4300.h>
#include <rcp.h>

/*
 * Assume that there is no PI activity, so don't test the status register
 * send zero to PHYS_TO_K1(0x1f000000)
 */

LEAF(clearint1)
	.set noreorder
	lui       t7,0xbf00       
	sw        zero,0(t7)        
	jr        ra
	nop
END(clearint1)

