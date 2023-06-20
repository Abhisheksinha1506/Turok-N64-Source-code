#include <R4300.h>
#include <ultra64.h>
/*
#include "setjmp.h"
*/
#include "cpu.h"


static jmp_buf	faultbuf;

s32
tlbMod(s32 *pt)
{
	int	error = 0;
	int	i;
	u32	tlb_attrib = TLBLO_V | TLBLO_UNCACHED;

	XDEBUG(PRINTF("TLB mod bit test\n"));

	for (i = 0; i < NTLBENTRIES; i++) {
		tlbwired(i, 0, 0,
			(pt[i * 2] >> 6) | tlb_attrib,
			(pt[i * 2 + 1] >> 6) | tlb_attrib);

		if (__osSetJmp((u32 *)faultbuf)) {
			if (_badvaddr != 1) {
				XDEBUG(PRINTF (
					"ERR: BadVaddr, Exp: 0x00000001, Act: 0x%08x, #%d\n",
					_badvaddr, i));
				error++;
			}

		} else {
			RegisterNoFault((u32 *)faultbuf);
			*(volatile u8 *)1 = i * 2;
			ClearNoFault();
			XDEBUG(PRINTF (
				"ERR: Did not receive expected exception\n"));
			error++;
		}

		osUnmapTLB(i);
	}

	for (i = 0; i < NTLBENTRIES; i++) {
		tlbwired(i, 0, 0,
			(pt[i * 2] >> 6) | tlb_attrib | TLBLO_D,
			(pt[i * 2 + 1] >> 6) | tlb_attrib | TLBLO_D);

		if (__osSetJmp((u32 *)faultbuf)) {
			XDEBUG(PRINTF("ERR: Test failed %d\n", i));
			return ++error;
		} else {
			RegisterNoFault((u32 *)faultbuf);
			*(volatile u8 *)1 = i * 2;
			ClearNoFault();
			if (*(u8 *)1 != *(u8 *)0) {
				XDEBUG(PRINTF (
					"ERR: Bad data, Exp: 0x%02x, Act: 0x%02x, #%d\n",
				   *(u8 *)0, *(u8 *)1, i));
				error++;
			}
		}

		osUnmapTLB(i);
	}

        XDEBUG(PRINTF("******** Test DONE with %d errors ********\n",
                error));

	return error;
}

