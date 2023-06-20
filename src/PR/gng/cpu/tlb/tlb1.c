#include <ultra64.h>
#include <R4300.h>
#include <os_internal.h>
#include "cpu.h"

#define	MAX_PAGESIZE	(64*1024)
#define	MAX_PAGESHIFT	16
#define	MIN_PAGESHIFT	12

static char testBuffer[4*MAX_PAGESIZE];

/*
 * tlb1
 *
 * Tests for:
 *	osMapTLB (asid argument)
 *	osSetTLBASID
 *
 * Assumed working:
 *
 *	osUnmapTLB
 *	osUnmapTLBAll
 *	osVirtualToPhysical
 *	osWritebackDCache
 *	osInvalDCache
 *
 * Description:
 */


void
printTLB(void)
{
    s32 index;

    PRINTF("TLB ASID = %d (0x%x)\n", __osGetTLBASID(), __osGetTLBASID());
    for (index = 0; index < 1; index++) {
    PRINTF("%02d. pagemask 0x%08x hi 0x%08x lo0 0x%08x lo1 0x%08x\n",
	      index, __osGetTLBPageMask(index), __osGetTLBHi(index),
	      __osGetTLBLo0(index), __osGetTLBLo1(index));
    }
}

int
tlb1(void)
{
    int numFailures = 0;
    u32 paddr;
    u8 *evenVaddr, *oddVaddr;
    unsigned int expectedValue, actualValue;
    s32 i, j;

/*
    XDEBUG(PRINTF("TLB1 test\n"));
*/

    paddr = osVirtualToPhysical(buffer);
    osUnmapTLBAll();

    evenVaddr = (u8 *)(2*4096);
    oddVaddr =  (u8 *)(3*4096);

    /*
     * Check that global mappings work regardless of the ASID
     */
    for (i = 0; i < 0x100; i++) {
 	osSetTLBASID(i);

	/*
	 * Map the even and odd pages one physical page apart.
	 */
	osMapTLB(0, OS_PM_4K, evenVaddr, paddr, paddr + 2 * 4096, -1);

	/*
	 * Verify the even page address.
	 */
	expectedValue = paddr;
	actualValue = osVirtualToPhysical(evenVaddr);
	if (expectedValue != actualValue) {
	    XDEBUG(PRINTF("ERR: expected physical address 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
	    numFailures++;
	}

	/*
	 * Verify the odd page address.
	 */
	expectedValue = paddr + 2 * 4096;
	actualValue = osVirtualToPhysical(oddVaddr);
	if (expectedValue != actualValue) {
	    XDEBUG(PRINTF("ERR: expected physical address 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
	    numFailures++;
	}
        osUnmapTLB(0);
    }


    /*
     * Check that non-global mappings work only when the correct ASID is set.
     */
    for (i = 0; i < 0x100; i++) {

	/*
	 * Map the even and odd pages one physical page apart.
	 */
	osMapTLB(0, OS_PM_4K, evenVaddr, paddr, paddr + 2 * 4096, i);

	for (j = 0; j < 0x100; j++) {
 	    osSetTLBASID(j);

	    /*
	     * Map, unmap another TLB entry here to test if ASID gets modified
	     */
	    osMapTLB(1, OS_PM_4K, evenVaddr+(2*4096),
		     paddr, paddr + 2 * 4096, i);
	    osUnmapTLB(1);

	    if (i == j) {
		/*
		 * Verify the even page address.
		 */
		expectedValue = paddr;
		actualValue = osVirtualToPhysical(evenVaddr);
		if (expectedValue != actualValue) {
		    XDEBUG(PRINTF(
			"ERR: expected physical address 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
		    numFailures++;
printTLB();
		}

		/*
		 * Verify the odd page address.
		 */
		expectedValue = paddr + 2 * 4096;
		actualValue = osVirtualToPhysical(oddVaddr);
		if (expectedValue != actualValue) {
		    XDEBUG(PRINTF(
			"ERR: expected physical address 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
		    numFailures++;
printTLB();
		}
	    } else {
		/*
		 * Verify the even page address is not mapped.
		 */
		expectedValue = (u32)-1;
		actualValue = osVirtualToPhysical(evenVaddr);
		if (expectedValue != actualValue) {
		    XDEBUG(PRINTF(
			"ERR: expected return value 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
		    numFailures++;
printTLB();
		}

		/*
		 * Verify the odd page address is not mapped.
		 */
		expectedValue = (u32)-1;
		actualValue = osVirtualToPhysical(oddVaddr);
		if (expectedValue != actualValue) {
		    XDEBUG(PRINTF(
			"ERR: expected return value 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
		    numFailures++;
printTLB();
		}
	    }
	}
        osUnmapTLB(0);
    }

/*
    XDEBUG(PRINTF("******** Test DONE with %d errors ********\n",
            numFailures));
*/

    return(numFailures);
}
