#include <R4300.h>
#include <ultra64.h>
#include <os_internal.h>
/*
#include "setjmp.h"
*/
#include "cpu.h"

#define TLBLO_PFN2MASK		0x03ffffc0  /* Bit 26-35 are 0s */


/*
 * Test the tlb as a small memory array.  Just see if all the read/write
 * bits can be toggled and that all undefined bit read back zero.
 */
s32
tlbMem(void)
{
	s32	error = 0;
	u32	expected_pat;
	s32	i;
	s32	j;
	u32	rpat;
/*
	u32	tlbhi_mask = TLBHI_VPNMASK | TLBHI_PIDMASK;
*/
	u32	tlbhi_mask = TLBHI_VPN2MASK | TLBHI_PIDMASK;
	u32	tlblo_mask = TLBLO_PFN2MASK | TLBLO_CACHMASK | TLBLO_D | TLBLO_V;
	u32	wpat;

	XDEBUG(PRINTF("TLB data test, himask=0x%08x, lomask=0x%08x\n",
		tlbhi_mask, tlblo_mask));

	wpat = 0xa5a5a5a5;
	for (i = 0; i < NTLBENTRIES; i++) {
		for (j = 0; j < 2; j++) {
			tlbwired(i, 0, 0, wpat, ~wpat);

			rpat = __osGetTLBLo0(i);

			expected_pat = wpat & tlblo_mask;
			if (rpat != expected_pat) {
				XDEBUG(PRINTF(
					"ERR: entry %2d LO 0: Exp:0x%08x, Act:0x%08x\n",
					i, expected_pat, rpat));
				error++;
			}

			wpat = ~wpat;

			rpat = __osGetTLBLo1(i);
			expected_pat = wpat & tlblo_mask;
			if (rpat != expected_pat) {
				XDEBUG(PRINTF(
					"ERR: entry %2d LO 1: Exp:0x%08x, Act:0x%08x\n",
					i, expected_pat, rpat));
				error++;
			}
		}
		osUnmapTLB(i);
	}

	for (i = 0; i < NTLBENTRIES; i++) {
		for (j = 0; j < 2; j++) {
			tlbwired(i, wpat & 0xff, wpat, 0, 0);

			rpat = __osGetTLBHi(i);
			expected_pat = wpat & tlbhi_mask;
			if (rpat != expected_pat) {
				XDEBUG(PRINTF(
					"ERR: entry %2d HI: Exp:0x%08x, Act:0x%08x\n",
					i, expected_pat, rpat));
				error++;
			}

			wpat = ~wpat;
		}
		osUnmapTLB(i);
	}

	XDEBUG(PRINTF("******** Test DONE with %d errors ********\n",
		error));

	return error;
}


