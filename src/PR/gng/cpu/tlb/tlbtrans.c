#include <R4300.h>
#include <ultra64.h>
/*
#include "setjmp.h"
*/
#include "cpu.h"


static jmp_buf	faultbuf;

s32
tlbTranslate(s32 *pt, u32 *uncachedp)
{
	s32	error = 0;
	s32	i;
	u32	tlblo_attrib = TLBLO_V | TLBLO_UNCACHED;

	XDEBUG(PRINTF("TLB translation test\n"));

	for (i = 0; i < NTLBENTRIES; i++) {
		u32 addr;

		for (addr = 0; addr < K0BASE; addr = (addr << 1) + PAGESIZE) {
			u32	_addr = addr & ~PAGESIZE;
			u8	bucket;
			u8	*ptr = (u8 *)uncachedp;

			tlbwired(i, 0, _addr,
				(pt[i * 2] >> 6) | tlblo_attrib,
				(pt[i * 2 + 1] >> 6) | tlblo_attrib);

			if (__osSetJmp((u32 *)faultbuf)) {
				return ++error;
			}

			RegisterNoFault((u32 *)faultbuf);
			bucket = *(u8 *)_addr;
			ClearNoFault();

			if (bucket != *ptr) {
				XDEBUG(PRINTF (
					"ERR: Data, Exp: 0x%x, Act: 0x%x\n",
					*ptr, bucket));
				error++;
			}

			_addr |= PAGESIZE;
			RegisterNoFault((u32 *)faultbuf);
			bucket = *(u8 *)_addr;
			ClearNoFault();

			ptr += PAGESIZE;
			if (bucket != *ptr) {
				XDEBUG(PRINTF (
					"ERR: Data, Exp: 0x%x, Act: 0x%x\n",
					*ptr, bucket));
				error++;
			}

			osUnmapTLB(i);
		}

		uncachedp += PAGESIZE * 2 / sizeof(*uncachedp);
	}

        XDEBUG(PRINTF("******** Test DONE with %d errors ********\n",
                error));

	return error;
}
