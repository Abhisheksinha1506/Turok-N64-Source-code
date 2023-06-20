/*
 * fpu/foverflow.c
 *
 *
 *
 * Copyright 1991, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied or
 * duplicated in any form, in whole or in part, without the prior written
 * permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
 * rights reserved under the Copyright Laws of the United States.
 */

#ident "$Revision: 1.2 $"

/*
 *					
 *	Floating Point Exerciser - basic functions with simple single
 *	overflow  
 *					
 */

#include <ultra64.h>
#include <os_internal.h>
#include <osint.h>
#include <fpu.h>
#include "cpu.h"


#define OVERFLOW	0x5014

extern void OVERFLOW_OP(void);

int
foverflow()
{
    register long status;
    register int fail;
    u32      stat1, stat2;

    fail = 0;

    /* enable cache and fpu - cache ecc errors still enabled */
    status = __osGetSR();
    status |= SR_CU0|SR_CU1;
    __osSetSR(status);

    /* clear cause register */
    __osSetCause(0);

    /* clear fpu status register */
    __osSetFpcCsr(0);

    stat1 = __osGetFpcCsr();

    OVERFLOW_OP();

    if ((stat2 = __osGetFpcCsr()) != OVERFLOW) {
        PRINTF("%s:%d: stat1=0x%08x, stat2=0x%08x\n", __FILE__, __LINE__, 
		stat1, stat2);
        fail = 1;
    }

    /* report any error */
    
    return(fail);
}
