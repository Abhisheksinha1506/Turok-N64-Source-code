#include <ultra64.h>
#include <os_internal.h>
#include <R4300.h>
#include "cpu.h"

#define	MAX_PAGESIZE	(64*1024)
#define	MAX_PAGESHIFT	16
#define	MIN_PAGESHIFT	12

static void printTLB(void);

/*
 * tlb0
 *
 * Tests for:
 *	osMapTLB
 *	osUnmapTLB
 *	osVirtualToPhysical
 *
 * Assumed working:
 *	osUnmapTLBAll
 *	osWritebackDCache
 *	osInvalDCache
 *
 * Description:
 *	For a range of page sizes (4K, 16K, and 64K) map each TLB
 *	entry with the size to an initialized portion of physical
 *	memory.  Verify that the mapping is correct with both
 *	the osVirtualToPhysical() call and by verifying the contents.
 */

int
tlb0(void)
{
    int numFailures = 0;
    int pageSize;
    OSPageMask pageMask;
    unsigned int *evenVaddr, *oddVaddr;
    unsigned int paddr;
    unsigned int *ip, *k0vaddr;
    unsigned int expectedValue, actualValue;
    int i, j;

/*
    XDEBUG(PRINTF("TLB0 test\n"));
*/

    paddr = osVirtualToPhysical(buffer);
    paddr = (paddr + MAX_PAGESIZE - 1) & ~(MAX_PAGESIZE - 1);

    k0vaddr = (unsigned int *)osPhysicalToVirtual(paddr);

    /*
     * Initialize each memory location to its KSEG0 virtual address.
     */
    ip = k0vaddr;
    for (i = 0; i < (3*MAX_PAGESIZE)/sizeof(int); i++) {
	*ip++ = (unsigned int)ip;
    }

    /*
     * Write it back and invalidate it to avoid any VCEs.
     */
    osWritebackDCache(k0vaddr, 3*MAX_PAGESIZE);
    osInvalDCache(k0vaddr, 3*MAX_PAGESIZE);

    osUnmapTLBAll();
    osSetTLBASID(0xff);		/* some non-zero value */

    /*
     * For each page size ...
     */
    for (i = MIN_PAGESHIFT; i <= MAX_PAGESHIFT; i += 2) {
	pageSize = 1<<i;
	pageMask = (pageSize << 1) - 0x2000;

	/*
	 * For each TLB entry ...
	 */
	for (j = 0; j < NTLBENTRIES; j++) {
	    evenVaddr = (unsigned int *)((j<<1)<<i);
	    oddVaddr =  (unsigned int *)(((j<<1)<<i) + (1<<i));


	    /*
	     * Map the even and odd pages one physical page apart.
	     */

	    osMapTLB(j, pageMask, evenVaddr, paddr, paddr + 2 * pageSize, -1);

	    /*
	     * Invalidate the region to avoid VCEs (on following passes).
	     */
	    osInvalDCache(evenVaddr, 2 * pageSize);
/*
PRINTF("evenVaddr 0x%x paddr1 0x%x paddr2 0x%x\n",
evenVaddr, paddr, paddr + 2 * pageSize);
PRINTF("osVirtualToPhysical(0x%x) = 0x%x\n",
evenVaddr, osVirtualToPhysical(evenVaddr));
PRINTF("osVirtualToPhysical(0x%x) = 0x%x\n",
oddVaddr, osVirtualToPhysical(oddVaddr));
*/
	
	    /*
	     * Verify the first even page address.
	     */
	    expectedValue = paddr;
	    actualValue = osVirtualToPhysical(evenVaddr);
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected physical address 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
		numFailures++;
	    }

            expectedValue = (unsigned int)k0vaddr;
	    actualValue = *evenVaddr;
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected value 0x%x, actual 0x%x at addr 0x%x\n",
			expectedValue, actualValue, evenVaddr));
		numFailures++;
	    }

	    /*
	     * Verify the last even page address.
	     */
	    expectedValue = paddr + pageSize - sizeof(unsigned int);
	    actualValue = osVirtualToPhysical(evenVaddr + 
				pageSize/sizeof(unsigned int) - 1);
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected physical address 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
		numFailures++;
	    }

	    expectedValue = (unsigned int)
			    (k0vaddr + pageSize/sizeof(unsigned int) - 1);
	    actualValue = *(evenVaddr + pageSize/sizeof(unsigned int) - 1);
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected value 0x%x, actual 0x%x at addr 0x%x\n",
			expectedValue, actualValue,
			evenVaddr + pageSize/sizeof(unsigned int) - 1));
	        numFailures++;
	    }

	    /*
	     * Verify the first odd page address.
	     */
	    expectedValue = paddr + 2 * pageSize;
	    actualValue = osVirtualToPhysical(oddVaddr);
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected physical address 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
		numFailures++;
	    }

            expectedValue = (unsigned int)(k0vaddr +
				       2*pageSize/sizeof(unsigned int));
	    actualValue = *oddVaddr;
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected value 0x%x, actual 0x%x at addr 0x%x\n",
			expectedValue, actualValue, oddVaddr));
		numFailures++;
	    }

	    /*
	     * Verify the last odd page address.
	     */
	    expectedValue = paddr + 3 * pageSize - sizeof(unsigned int);
	    actualValue = osVirtualToPhysical(oddVaddr +
					      pageSize/sizeof(unsigned int)-1);
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected physical address 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
		numFailures++;
	    }

            expectedValue = (unsigned int)(k0vaddr +
					   3*pageSize/sizeof(unsigned int) - 1);
	    actualValue = *(oddVaddr + pageSize/sizeof(unsigned int) - 1);
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected value 0x%x, actual 0x%x at addr 0x%x\n",
			expectedValue, actualValue,
			oddVaddr + pageSize/sizeof(unsigned int) - 1));
			numFailures++;
	    }

	    /*
	     * Now map only the even page.
	     */
	    osMapTLB(j, pageMask, evenVaddr, paddr, -1, -1);

	    /*
	     * Check even page mapping.
	     */
	    expectedValue = paddr;
	    actualValue = osVirtualToPhysical(evenVaddr);
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected physical address 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
		numFailures++;
	    }

            expectedValue = (unsigned int)k0vaddr;
	    actualValue = *evenVaddr;
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected value 0x%x, actual 0x%x at addr 0x%x\n",
			expectedValue, actualValue, evenVaddr));
		numFailures++;
	    }

	    /*
	     * Verify odd page no longer maps.
	     */
	    expectedValue = (unsigned int)-1;
	    actualValue = osVirtualToPhysical(oddVaddr);
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected physical address 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
		numFailures++;
	    }

	    /*
	     * Now map only the odd page.
	     */
	    osMapTLB(j, pageMask, evenVaddr, -1, paddr + 2 * pageSize, -1);

	     /*
	      * Verify even page no longer maps.
	      */
	    expectedValue = (unsigned int)-1;
	    actualValue = osVirtualToPhysical(evenVaddr);
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected physical address 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
		numFailures++;
	    }

	    /*
	     * Check odd page mapping.
	     */
	    expectedValue = paddr + 2 * pageSize;
	    actualValue = osVirtualToPhysical(oddVaddr);
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected physical address 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
		numFailures++;
	    }

            expectedValue = (unsigned int)(k0vaddr +
				       2*pageSize/sizeof(unsigned int));
	    actualValue = *oddVaddr;
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected value 0x%x, actual 0x%x at addr 0x%x\n",
			expectedValue, actualValue, oddVaddr));
		numFailures++;
	    }

	    /*
	     * Invalidate the entire entry by either of two ways.
	     */
	    if (j % 2)
	   	 osUnmapTLB(j);
	    else
	         osMapTLB(j, pageMask, evenVaddr, -1, -1, -1);

	    /*
	     * Verify both even and odd pages no longer map.
	     */
	    expectedValue = (unsigned int)-1;
	    actualValue = osVirtualToPhysical(evenVaddr);
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected physical address 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
		numFailures++;
	    }

	    expectedValue = (unsigned int)-1;
	    actualValue = osVirtualToPhysical(oddVaddr);
	    if (expectedValue != actualValue) {
		XDEBUG(PRINTF("tlb0: expected physical address 0x%x, actual 0x%x\n",
			expectedValue, actualValue));
		numFailures++;
	    }
	}
    }

/*
    XDEBUG(PRINTF("******** Test DONE with %d errors ********\n",
            numFailures));
*/

    return(numFailures);
}

void
printTLB(void)
{
	s32 index;

	for (index = 0; index < NTLBENTRIES; index++) {
	   PRINTF("%02d. pagemask 0x%08x hi 0x%08x lo0 0x%08x lo1 0x%08x\n",
		      index, __osGetTLBPageMask(index), __osGetTLBHi(index),
		      __osGetTLBLo0(index), __osGetTLBLo1(index));
	}
}
