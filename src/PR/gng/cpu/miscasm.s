#include <asm.h>
#include <regdef.h>
#include <R4300.h>


/************************************************************************/

/*
 * Delay a0 micro seconds. Calibrated for a 60Mhz R4x00 (100 Mhz) series part
 * assuming that the branch taken penalty is 3 cycles.
 */
LEAF(Delay)		/* void Delay(unsigned usec); */

	sll	t0,a0,2		/* t0 = a0*4 */
	addu	t0,a0		/* t0 = a0*5 */
	sll	t0,t0,2		/* t0 = a0*20 */
	beqz	a0,2f

	/* 5 cycle spin loop */
	.set	noreorder
1:	subu	t0,1
	bnez	t0,1b
	 nop
2:
	.set	reorder
	j	ra
	END(Delay)


