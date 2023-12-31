/*
 * fmuldivs.c
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

#ident "$Revision: 1.1 $"

/*
 *					
 *	Floating Point Exerciser - basic functions with single precision
 *	arithmetic (multiply and divide)
 *					
 */

#include <ultra64.h>
#include <os_internal.h>
#include <osint.h>
#include <fpu.h>


#define TESTVAL		0xdeadbeef
#define TESTBAK		0xffffdeae

int
fmuldivs()
{
    float f1, f2, f3, f4, f5, f6;
    register long status;
    register long i1;
    register int fail = 0;

    /* enable cache and fpu - cache ecc errors still enabled */
    status = __osGetSR();
    status |= SR_CU0|SR_CU1;
    __osSetSR(status);

    /* clear cause register */
    __osSetCause(0);

    /* clear fpu status register */
    __osSetFpcCsr(0);

    /* let's try some single precision division and multiplication */
    i1 = TESTVAL;	/* start with fixed point number */
    f1 = i1;		/* convert to floating point number */
    i1 = 0x10000;	/* this is our divide test divisor */
    f3 = i1;		/* convert to floating point number */
    f4 = f1 / f3;
    i1 = f4;		/* convert back to fixed point number */
    if (i1 != TESTBAK){
	fail = 1;
    }

    /* note: we're about to assume addition is working */
    f2 = f1 + f1;	/* we'll also need 2 times our test value */
    i1 = 2;
    f5 = i1;
    f6 = f5 * f1;
    if (f6 != f2){
	fail = 1;
    }

    /* report any error */
    
    return(fail);
}
