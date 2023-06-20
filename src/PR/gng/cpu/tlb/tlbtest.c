/*
 * Based on #ident	"IP22diags/tlb/tlbtest.c:  $Revision: 1.1 $"
 */

#include <R4300.h>
#include <ultra64.h>
#include "cpu.h"


static s32 (*testfun[])() = {
	tlbMem,
	tlbProbe,
	tlbTranslate,
	tlbValid,
	tlbMod,
	tlbPid,
	tlbGlobal,
	tlbNocache,
	0,
};

static s32	pt[NTLBENTRIES * 2];	/* Page table array */


/*
 * The tlb test functions wire tlb entries from a page table which maps
 * various test-specific virtual addresses to NTLBENTRIES * PAGESIZE * 2 worth
 * of physical memory.
 */
s32
tlbTest(void)
{
	u32	*cachedp;
	s32	error = 0;
	s32	i;
	u8	*k;
	u8	*p;
	s32	(**tf)();
	u32	*uncachedp;

	XDEBUG(PRINTF("Translation Lookaside Buffer (TLB) test\n"));

	set_pgmask(0x0);	/* set to 4K page? */

	/*
	 * The memory mapped via pt[] starts at TLB_TESTADDR
	 */
	k = (u8 *)(((TLB_TESTADDR + PAGESIZE - 1) / PAGESIZE) * PAGESIZE);
	p = (u8 *)K1_TO_PHYS(k);
	uncachedp = (u32 *)k;
	cachedp = (u32 *)PHYS_TO_K0(p);

	for (i = 0; i < NTLBENTRIES * 2; i += 2) {
	    *k = i;
	    pt[i] = (u32) p;
	    k += PAGESIZE;
	    p += PAGESIZE;

	    *k = i + 1;
	    pt[i + 1] = (u32) p;
	    k += PAGESIZE;
	    p += PAGESIZE;
	}

	for (tf = testfun; *tf != 0; tf++) {
	    osUnmapTLBAll();
	    osSetTLBASID(0);
	    error += (**tf)(pt, uncachedp, cachedp); 
	}

	osWritebackDCacheAll();
	osInvalDCache(cachedp, DCACHE_SIZE);
	osUnmapTLBAll();

	if (!error) {
	    XDEBUG(PRINTF("=> TLB test PASSED!\n"));
        }
	else {
	    PRINTF("=> TLB test FAILED with %d errors\n", error);
        }

	return error;
}


