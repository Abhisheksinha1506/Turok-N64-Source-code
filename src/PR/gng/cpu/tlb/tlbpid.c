#include <R4300.h>
#include <ultra64.h>
/*
#include "setjmp.h"
*/
#include "cpu.h"

static jmp_buf	faultbuf;

s32
tlbPid(s32 *pt)
{
	s32	error = 0;
	s32	i;
	u8	pidmismatch;
	s32	vpid;
	u32	tlblo_attrib = TLBLO_V | TLBLO_UNCACHED;
	s32	tpid;

	XDEBUG(PRINTF("TLB pid test starting...\n"));

	for (i = 0; i < NTLBENTRIES; i++) {
	    for (vpid = 0x1; vpid < TLBHI_NPID; vpid <<= 1) {

	        osSetTLBASID(vpid);

		for (tpid = 0x1; tpid < TLBHI_NPID; tpid <<= 1) {

		    tlbwired(i, tpid, 0,
		   	(pt[i * 2] >> 6) | tlblo_attrib,
			(pt[i * 2 + 1] >> 6) | tlblo_attrib);

		    pidmismatch = (tpid != vpid);

		    if (__osSetJmp((u32 *)faultbuf)) {
/*
			XDEBUG(PRINTF("==> SetJmp %d\n",i));
*/
			if (!pidmismatch) {
			    XDEBUG(PRINTF("ERR: Test failed %d\n",i));
			    return ++error;
			}
					
			if (_badvaddr != 0x0) {
			    XDEBUG(PRINTF(
				"ERR: BadVaddr, Exp: 0x0, Act: 0x%08x\n",
				_badvaddr));
			    error++;
			}

		    } else {
			u8 bucket;

			RegisterNoFault((u32 *)faultbuf);
			bucket = *(volatile u8 *)0;
			ClearNoFault();

			if (pidmismatch) {
			    XDEBUG(PRINTF (
				"ERR: Did not get expected exception\n"));
			    error++;
			}
		    }

		    osUnmapTLB(i);
		}
	    }
        }

        XDEBUG(PRINTF("******** Test DONE with %d errors ********\n",
                error));

        return error;
}

