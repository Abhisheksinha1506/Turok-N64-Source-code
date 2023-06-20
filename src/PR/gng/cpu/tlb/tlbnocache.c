#include <R4300.h>
#include <ultra64.h>
/*
#include "setjmp.h"
*/
#include "cpu.h"


static u32 va[sizeof(int)] = {
	KUBASE,
	KUBASE|0x20000000,
	K2BASE,
	K2BASE|0x20000000
};

static jmp_buf	faultbuf;


s32
tlbNocache(s32 *pt, u32 *uncachedp, u32 *cachedp)
{
	u32	cachepat = 0x87654321;
	int	error = 0;
	int	i;
	u32	mempat = 0x12345678;
	u32	tlb_attrib = TLBLO_V | TLBLO_D;
	u32	tlbpat;

	XDEBUG(PRINTF("TLB cached bit test\n"));

	for (i = 0; i < NTLBENTRIES; i++) {
		u32 addr = va[i & (sizeof(int) - 1)];

		tlbwired(i, 0, addr,
			(pt[0] >> 6) | tlb_attrib | TLBLO_NONCOHRNT,
			(pt[1] >> 6) | tlb_attrib | TLBLO_NONCOHRNT);

		if (__osSetJmp((u32 *)faultbuf)) {
			XDEBUG(PRINTF("ERR: Test failed %d\n",i));
			return ++error;
		}

		RegisterNoFault((u32 *)faultbuf);
		*(volatile u32 *)cachedp = cachepat;
		*(volatile u32 *)uncachedp = mempat;
		tlbpat = *(u32 *)addr;
		ClearNoFault();

		if (tlbpat != cachepat) {
			XDEBUG(PRINTF(
				"ERR: Cached TLB, Exp: 0x%08x, Act: 0x%08x\n",
				cachepat, tlbpat));
			error++;
		}

		osUnmapTLB(i);
	}

	for (i = 0; i < NTLBENTRIES; i++) {
		tlbwired(i, 0, 0,
			(pt[0] >> 6) | tlb_attrib | TLBLO_UNCACHED,
			(pt[1] >> 6) | tlb_attrib | TLBLO_UNCACHED);

		if (__osSetJmp((u32 *)faultbuf)) {
			XDEBUG(PRINTF("ERR: Test failed %d\n",i));
			return ++error;
		}

		RegisterNoFault((u32 *)faultbuf);
		*(volatile u32 *)cachedp = cachepat;
		*(volatile u32 *)uncachedp = mempat;
		/*
		 * the test may not work without this second write due to a
		 * possible R4000 bug
		 */
		*(volatile u32 *)uncachedp = mempat;
		tlbpat = *(u32 *)0;
		ClearNoFault();

		if (tlbpat != mempat) {
			XDEBUG(PRINTF(
				"ERR: Uncached TLB, Exp: 0x%08x, Act: 0x%08x\n",
				mempat, tlbpat));
			error++;
		}

		osUnmapTLB(i);
	}

        XDEBUG(PRINTF("******** Test DONE with %d errors ********\n",
                error));

	return error;
}

