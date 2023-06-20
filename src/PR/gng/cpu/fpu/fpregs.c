/*
 * fpu/fpregs.c
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
 *	Floating Point Exerciser - write/read fpu registers
 *					
 */

#include <ultra64.h>
#include <os_internal.h>
#include <osint.h>
#include <fpu.h>
#include "cpu.h"

extern u32	GetFP0(void);  extern u32	GetFP1(void);
extern u32	GetFP2(void);  extern u32	GetFP3(void);
extern u32	GetFP4(void);  extern u32	GetFP5(void);
extern u32	GetFP6(void);  extern u32	GetFP7(void);
extern u32	GetFP8(void);  extern u32	GetFP9(void);
extern u32	GetFP10(void); extern u32	GetFP11(void);
extern u32	GetFP12(void); extern u32	GetFP13(void);
extern u32	GetFP14(void); extern u32	GetFP15(void);
extern u32	GetFP16(void); extern u32	GetFP17(void);
extern u32	GetFP18(void); extern u32	GetFP19(void);
extern u32	GetFP20(void); extern u32	GetFP21(void);
extern u32	GetFP22(void); extern u32	GetFP23(void);
extern u32	GetFP24(void); extern u32	GetFP25(void);
extern u32	GetFP26(void); extern u32	GetFP27(void);
extern u32	GetFP28(void); extern u32	GetFP29(void);
extern u32	GetFP30(void); extern u32	GetFP31(void);

extern void	SetFP0(u32);  extern void	SetFP1(u32);
extern void	SetFP2(u32);  extern void	SetFP3(u32);
extern void	SetFP4(u32);  extern void	SetFP5(u32);
extern void	SetFP6(u32);  extern void	SetFP7(u32);
extern void	SetFP8(u32);  extern void	SetFP9(u32);
extern void	SetFP10(u32); extern void	SetFP11(u32);
extern void	SetFP12(u32); extern void	SetFP13(u32);
extern void	SetFP14(u32); extern void	SetFP15(u32);
extern void	SetFP16(u32); extern void	SetFP17(u32);
extern void	SetFP18(u32); extern void	SetFP19(u32);
extern void	SetFP20(u32); extern void	SetFP21(u32);
extern void	SetFP22(u32); extern void	SetFP23(u32);
extern void	SetFP24(u32); extern void	SetFP25(u32);
extern void	SetFP26(u32); extern void	SetFP27(u32);
extern void	SetFP28(u32); extern void	SetFP29(u32);
extern void	SetFP30(u32); extern void	SetFP31(u32);

int
fpregs()
{
    register int fail = 0;
    register long status;

    /* enable cache and fpu - cache ecc errors enabled */
    status = __osGetSR();
    status |= SR_CU0|SR_CU1;
    __osSetSR(status);

    /* clear cause register */
    __osSetCause(0);

    /* clear fpu status register */
    __osSetFpcCsr(0);

    /* write and read fpu registers */
    SetFP0(0);
    SetFP1(1);
    SetFP2(2);
    SetFP3(3);
    SetFP4(4);
    SetFP5(5);
    SetFP6(6);
    SetFP7(7);
    SetFP8(8);
    SetFP9(9);
    SetFP10(10);
    SetFP11(11);
    SetFP12(12);
    SetFP13(13);
    SetFP14(14);
    SetFP15(15);
    SetFP16(16);
    SetFP17(17);
    SetFP18(18);
    SetFP19(19);
    SetFP20(20);
    SetFP21(21);
    SetFP22(22);
    SetFP23(23);
    SetFP24(24);
    SetFP25(25);
    SetFP26(26);
    SetFP27(27);
    SetFP28(28);
    SetFP29(29);
    SetFP30(30);
    SetFP31(31);
    if (GetFP0() != 0){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP1() != 1){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP2() != 2){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP3() != 3){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP4() != 4){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP5() != 5){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP6() != 6){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP7() != 7){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP8() != 8){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP9() != 9){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP10() != 10){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP11() != 11){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP12() != 12){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP13() != 13){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP14() != 14){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP15() != 15){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP16() != 16){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP17() != 17){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP18() != 18){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP19() != 19){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP20() != 20){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP21() != 21){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP22() != 22){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP23() != 23){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP24() != 24){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP25() != 25){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP26() != 26){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP27() != 27){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP28() != 28){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP29() != 29){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP30() != 30){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP31() != 31){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }

    SetFP0(~0);
    SetFP1(~1);
    SetFP2(~2);
    SetFP3(~3);
    SetFP4(~4);
    SetFP5(~5);
    SetFP6(~6);
    SetFP7(~7);
    SetFP8(~8);
    SetFP9(~9);
    SetFP10(~10);
    SetFP11(~11);
    SetFP12(~12);
    SetFP13(~13);
    SetFP14(~14);
    SetFP15(~15);
    SetFP16(~16);
    SetFP17(~17);
    SetFP18(~18);
    SetFP19(~19);
    SetFP20(~20);
    SetFP21(~21);
    SetFP22(~22);
    SetFP23(~23);
    SetFP24(~24);
    SetFP25(~25);
    SetFP26(~26);
    SetFP27(~27);
    SetFP28(~28);
    SetFP29(~29);
    SetFP30(~30);
    SetFP31(~31);
    if (GetFP0() != ~0){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP1() != ~1){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP2() != ~2){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP3() != ~3){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP4() != ~4){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP5() != ~5){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP6() != ~6){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP7() != ~7){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP8() != ~8){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP9() != ~9){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP10() != ~10){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP11() != ~11){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP12() != ~12){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP13() != ~13){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP14() != ~14){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP15() != ~15){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP16() != ~16){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP17() != ~17){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP18() != ~18){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP19() != ~19){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP20() != ~20){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP21() != ~21){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP22() != ~22){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP23() != ~23){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP24() != ~24){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP25() != ~25){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP26() != ~26){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP27() != ~27){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP28() != ~28){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP29() != ~29){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP30() != ~30){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }
    if (GetFP31() != ~31){
        PRINTF("%s:%d: FAILED!\n", __FILE__, __LINE__);
	fail = 1;
    }

    /* report any error */
    
    return(fail);
}
