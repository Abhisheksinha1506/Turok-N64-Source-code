/*
 * fpu/finexact.c
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
 *	inexact
 *					
 */
#include <ultra64.h>
#include <os_internal.h>
#include <osint.h>
#include <fpu.h>
#include "cpu.h"


#define TESTPAT		0xdeadbeef
#define INEXACT		0x1004

int
finexact()
{
    volatile float f1, f2, f3;
    volatile long i1;
    register long i2;
    register long status;
    register int fail;
    u32          stat;

    fail = 0;

    /* enable cache and fpu - cache ecc errors still enabled */
    status = __osGetSR();
    status |= SR_CU0|SR_CU1;
    __osSetSR(status);

    /* clear cause register */
    __osSetCause(0);

    /* clear fpu status register */
    __osSetFpcCsr(0);

    /* Convert to floating point */
    i1 = TESTPAT;
    f1 = i1;

    if ((stat = __osGetFpcCsr()) != INEXACT) {

        PRINTF("%s:%d: stat=0x%08x\n", __FILE__, __LINE__, stat);

        fail = 1;
    }

    if (i1 != TESTPAT){

        PRINTF("%s:%d: i1=0x%x\n", __FILE__, __LINE__, i1);

	fail = 1;
    }

    /* report any error */
    
    return(fail);
}
