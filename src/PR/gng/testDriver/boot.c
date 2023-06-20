#include <ultra64.h>
#include <bstring.h>
#include "gng.h"
#include "rdramTest_data.h"

char	bootStack[STACKSIZE];

extern char _codeSegmentRomStart[];
extern char _codeSegmentRomEnd[];
extern char _codeSegmentStart[];
extern char _codeSegmentTextStart[];
extern char _codeSegmentTextEnd[];
extern char _codeSegmentDataStart[];
extern char _codeSegmentDataEnd[];
extern char _codeSegmentBssStart[];
extern char _codeSegmentBssEnd[];

/*
 * The boot() function MUST be the first function in this module, otherwise
 * the original boot thread (loaded at 2MB in rdram) will be unable to invoke 
 * this secondary boot procedure, which loads the program low in rdram.
 *
 * The FIRST thing the boot program does is run the rdram diagnostic, if it
 * has not been run already.  That way we minimize the amount of time we spend
 * executing instructions from rdram (the test itself runs in dmem).
 */
boot(void *arg)
{
    void (*func)(void);
    unsigned volatile int *pDmem, *pTest;
    int wordCount, rdramDiagErrors, rdramDiagStatus;
    gngstatus	*pstatus;

    /*
     * osAppNMIBuffer == 0x8000031c in locore rdram
     */
    pstatus = (gngstatus *)osAppNMIBuffer;

    /*
     * Save the rdram diagnostic status in a global variable, as it will be
     * cleared by osInitialize.
     */
    rdramDiagStatus = pstatus->rdram_diag_status;

    /*
     * Check to see if this is a cold reset.  If so, load the
     * rdram diagnostic into dmem and jump to it; when the rdram diagnostic
     * completes, it will reload, then invoke this boot function again.
     *
     * osResetType will be set to 1 whenever an nmi is induced by the reset 
     * button.
     *
     * (we don't want to run the memory test after an nmi interrupt brings 
     * us here)
     */
    if ( ( osResetType == 0 ) && (rdramDiagStatus != 0xdeadbeef) ) {

	/*
	 * Halt the SP.
	 */
	__osSpSetStatus(SP_SET_HALT);

	/*
	 * Disable interrupts, flush caches.
	 */
	osSetIntMask(OS_IM_NONE);

	osInvalICache(_codeSegmentTextStart,
	    _codeSegmentTextEnd-_codeSegmentTextStart);
	osInvalDCache(_codeSegmentDataStart,
	    _codeSegmentDataEnd-_codeSegmentDataStart);

	/*
	 * Copy the rdramTest program from a global array into dmem.
	 */
        for (wordCount = 0, pTest = (unsigned int *)rdramTest_data,
          pDmem = ( (unsigned int *)( PHYS_TO_K1(SP_DMEM_START) ) );
          wordCount < (rdramTest_data_size >> 2); wordCount++) {
            *pDmem++ = *pTest++;
        }

	func = (void (*)(void))( PHYS_TO_K1(SP_DMEM_START) );
	osInvalICache(func, rdramTest_data_size);
	func();
        /* never reached */
#ifndef _FINALROM
	osExit();
#endif
    } else {
	/*
	 * Save the rdram test reserved memory variables, as both osInitialize()
	 * and bzero() below will clobber the reserved memory locations used 
	 * by the rdram test.
	 */
	rdramDiagErrors = pstatus->rdram_diag_errors;
    }
    
    osInitialize();

    /*
     * Load in the code segment.  The "boot" portion of the code segment
     * will load in the texture segment and the static segment.
     */
    osPiRawStartDma(OS_READ, (u32)_codeSegmentRomStart, _codeSegmentStart, 
		   _codeSegmentRomEnd-_codeSegmentRomStart);

    while(osPiGetStatus() & PI_STATUS_DMA_BUSY);

    osInvalICache(_codeSegmentTextStart,
		  _codeSegmentTextEnd-_codeSegmentTextStart);
    osInvalDCache(_codeSegmentDataStart,
		  _codeSegmentDataEnd-_codeSegmentDataStart);

    bzero(_codeSegmentBssStart, _codeSegmentBssEnd-_codeSegmentBssStart);

    /*
     * Restore the reserved memory locations used by the rdram test, so that
     * they can be queried by functions in the codeSegment.
     */
    pstatus->rdram_diag_status = rdramDiagStatus;
    pstatus->rdram_diag_errors = rdramDiagErrors;

    func = (void (*)(void))_codeSegmentStart;
    func();
}
