#include <R4300.h>
#include <ultra64.h>
/*
#include "setjmp.h"
*/
#include "cpu.h"


static jmp_buf	faultbuf;

s32
tlbValid(s32 *pt)
{
	s32	error = 0;
	s32	i;

	XDEBUG(PRINTF("TLB valid bit test\n"));

	osUnmapTLBAll();
	for (i = 0; i < NTLBENTRIES; i++) {
		u8 *addr;

		addr = (u8 *)(K2BASE + i * PAGESIZE * 2);
		tlbwired(i, 0, (u32)addr,
			(pt[i * 2] >> 6) | TLBLO_UNCACHED,
			(pt[i * 2 + 1] >> 6) | TLBLO_UNCACHED);

		if (__osSetJmp((u32 *)faultbuf)) {
/*
			XDEBUG(PRINTF ( "=> Jumping back to setjmp #%d...\n", i)); 
*/
			if (_badvaddr != (u32)addr) {
				XDEBUG(PRINTF (
					"ERR: BadVaddr, Exp: 0x%08x, Act: 0x%08x\n",
					(u32)addr, _badvaddr));
				error++;
			}

		} else {
			u8 bucket;

			RegisterNoFault((u32 *)faultbuf);
			bucket = *(volatile u8 *)addr;
			ClearNoFault();

			XDEBUG(PRINTF(
				"ERR: Did not receive expected exception\n"));
			error++;
		}

		osUnmapTLB(i);
	}

        XDEBUG(PRINTF("******** Test DONE with %d errors ********\n",
                error));

	return error;
}

