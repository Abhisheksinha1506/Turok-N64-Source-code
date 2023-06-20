/*
 * fpu/faddsubs.c
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
 *	precision arithmetic (addition and subtraction)
 *					
 */

#include <ultra64.h>
#include <os_internal.h>
#include <osint.h>
#include <fpu.h>


#define TESTPAT		0xdbeef

int
faddsubs()
{
    float f1, f2, f3;
    register long i1;
    register long status;
    register int fail;

    fail = 0;

    /* enable cache and fpu - cache ecc errors still enabled */
    status = __osGetSR();
    status |= SR_CU0|SR_CU1;
    __osSetSR(status);

    /* clear cause register */
    __osSetCause(0);

    /* clear fpu status register */
    __osSetFpcCsr(0);

    /* try some simple single precision arithmetic operations */
    i1 = TESTPAT;	/* start with fixed point number */
    f1 = i1;		/* convert to floating point */
    f2 = f1 + f1;
    f3 = f2 - f1;
    if (f3 != f1){
	fail = 1;
    }
    if (f3 == f2){
	fail = 1;
    }
    i1 = f3;		/* convert back to fixed point number */
    if (i1 != TESTPAT){
	fail = 1;
    }
    if (__osGetFpcCsr()){
        fail = 1;
    }

    /* report any error */
    
    return(fail);
}
