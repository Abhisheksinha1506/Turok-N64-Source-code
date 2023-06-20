/*
 * setjmp/longjmp implementation
 *
 * This is identical to libc's except that it doesn't preserve floating
 * point things.
 */

#ident "$Revision: 1.1 $"

#include <asm.h>
#include <regdef.h>
#include <R4300.h>

#include "threadasm.h"
#include <setjmp.h>

/*
 * u32 __osSetJmp(jmp_buf) -- save current context for non-local goto's
 * return 0
 */
	.text
	.set	at
	.set	reorder

LEAF(__osSetJmp)
	sd	s0,T_CONTEXT_S0(a0)
	sd	s1,T_CONTEXT_S1(a0)
	sd	s2,T_CONTEXT_S2(a0)
	sd	s3,T_CONTEXT_S3(a0)
	sd	s4,T_CONTEXT_S4(a0)
	sd	s5,T_CONTEXT_S5(a0)
	sd	s6,T_CONTEXT_S6(a0)
	sd	s7,T_CONTEXT_S7(a0)
	sd	gp,T_CONTEXT_GP(a0)
	sd	s8,T_CONTEXT_S8(a0)		/* fp = s8 = frame pointer */
	sd	sp,T_CONTEXT_SP(a0)
	sw	ra,T_CONTEXT_PC(a0)
	move	v0,zero

	j	ra
	END(__osSetJmp)


LEAF(setjmp)
	sw	ra,JB_PC*4(a0)
	sw	sp,JB_SP*4(a0)
	sw	fp,JB_FP*4(a0)		/* fp = s8 = frame pointer */
	sw	s0,JB_S0*4(a0)
	sw	s1,JB_S1*4(a0)
	sw	s2,JB_S2*4(a0)
	sw	s3,JB_S3*4(a0)
	sw	s4,JB_S4*4(a0)
	sw	s5,JB_S5*4(a0)
	sw	s6,JB_S6*4(a0)
	sw	s7,JB_S7*4(a0)
	move	v0,zero
	j	ra
	END(setjmp)


/*
 * void __osRestoreJmp(jmp_buf, OSThread *)
 */
LEAF(__osRestoreJmp)
	lw	v0,T_CONTEXT_PC(a0)
	sw	v0,T_CONTEXT_PC(a1)	/* ra ? */

	ld	v0,T_CONTEXT_SP(a0)
	sd	v0,T_CONTEXT_SP(a1)
	ld	v0,T_CONTEXT_S8(a0)	/* fp = frame pointer */
	sd	v0,T_CONTEXT_S8(a1)
	ld	v0,T_CONTEXT_S0(a0)
	sd	v0,T_CONTEXT_S0(a1)
	ld	v0,T_CONTEXT_S1(a0)
	sd	v0,T_CONTEXT_S1(a1)
	ld	v0,T_CONTEXT_S2(a0)
	sd	v0,T_CONTEXT_S2(a1)
	ld	v0,T_CONTEXT_S3(a0)
	sd	v0,T_CONTEXT_S3(a1)
	ld	v0,T_CONTEXT_S4(a0)
	sd	v0,T_CONTEXT_S4(a1)
	ld	v0,T_CONTEXT_S5(a0)
	sd	v0,T_CONTEXT_S5(a1)
	ld	v0,T_CONTEXT_S6(a0)
	sd	v0,T_CONTEXT_S6(a1)
	ld	v0,T_CONTEXT_S7(a0)
	sd	v0,T_CONTEXT_S7(a1)

	/* Set 1 in v0 to let setjmp continue */ 
	li	v0,1			
	sw	v0,T_CONTEXT_V0(a1)

	j	ra
	END(__osRestoreJmp)


/*
 * longjmp(jmp_buf, rval)
 */
LEAF(longjmp)
	lw	ra,JB_PC*4(a0)
	lw	sp,JB_SP*4(a0)
	lw	fp,JB_FP*4(a0)
	lw	s0,JB_S0*4(a0)
	lw	s1,JB_S1*4(a0)
	lw	s2,JB_S2*4(a0)
	lw	s3,JB_S3*4(a0)
	lw	s4,JB_S4*4(a0)
	lw	s5,JB_S5*4(a0)
	lw	s6,JB_S6*4(a0)
	lw	s7,JB_S7*4(a0)
	move	v0,a1			/* return rval */
	bnez	v0,1f			/* unless rval==0 */
	li	v0,1			/* in which case return 1 */
1:	j	ra
	END(longjmp)


