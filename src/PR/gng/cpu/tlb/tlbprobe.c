#include <R4300.h>
#include <ultra64.h>
/*
#include "setjmp.h"
*/
#include "cpu.h"


/*
 * See if all the tlb slots respond to probes upon address match.
 */
s32
tlbProbe(s32 *pt)
{
	s32	error = 0;
	s32	i;
	s32	index;
	u32	tlblo_attrib = TLBLO_V | TLBLO_UNCACHED;

	XDEBUG(PRINTF("TLB probe test\n"));

	for (i = 0; i < NTLBENTRIES; i++) {
		tlbwired(i, 0, i * PAGESIZE * 2,
			(pt[i * 2] >> 6) | tlblo_attrib,
			(pt[i * 2 + 1] >> 6) | tlblo_attrib);

		index = probe_tlb(i * PAGESIZE * 2, 0);
		if (index != i) {
			XDEBUG(PRINTF (
				"ERR: Index probed, Exp: 0x%08x, Act: 0x%8x\n",
			   	i, index));
			error++;
		}

		index = probe_tlb((i * 2 + 1) * PAGESIZE, 0);
		if (index != i) {
			XDEBUG(PRINTF (
				"ERR: Index probed, Exp: 0x%08x, Act: 0x%8x\n",
			   	i, index));
			error++;
		}

		osUnmapTLB(i);
	}

        XDEBUG(PRINTF("******** Test DONE with %d errors ********\n",
                error));

	return error;
}
