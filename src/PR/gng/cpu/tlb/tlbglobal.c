#include <R4300.h>
#include <ultra64.h>
/*
#include "setjmp.h"
*/
#include "cpu.h"

static jmp_buf	faultbuf;

s32
tlbGlobal(s32 *pt)
{
	s32	error = 0;
	s32	i;
	u32	tlb_attrib = TLBLO_V | TLBLO_G | TLBLO_UNCACHED;
	u32	tpid;
	u32	vpid;


	osUnmapTLBAll();
	/* Assume that all TLBs have been unmapped */

	XDEBUG(PRINTF("TLB global bit test\n"));

	for (i = 0; i < NTLBENTRIES; i++) {
		for (vpid = 0x1; vpid < TLBHI_NPID; vpid <<= 1) {
			osSetTLBASID(vpid);

			for (tpid = 0x1; tpid < TLBHI_NPID; tpid <<= 1) {
				volatile u8 bucket;

				tlbwired(i, vpid, tpid,
					(pt[i * 2] >> 6) | tlb_attrib,
					(pt[i * 2 + 1] >> 6) | tlb_attrib);

				if (__osSetJmp((u32 *)faultbuf)) {
					XDEBUG(PRINTF("ERR: Test failed!\n"));
					return ++error;
				}

				RegisterNoFault((u32 *)faultbuf);
				bucket = *(volatile u8 *)0;
				ClearNoFault();
				osUnmapTLB(i);
			}
		}
	}

        XDEBUG(PRINTF("******** Test DONE with %d errors ********\n",
                error));

	return error;
}

