/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1996 Silicon Graphics, Inc.                *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

/*
 * File:	testDriver.c
 * Creator:	hal@sgi.com
 * Purpose:	Primary test driver: 
 *
 *		    compile time loaded array of structured tests
 *		    (location in array determines test sequence order),
 *
 *		    test driver loop which invokes individual tests, then
 *		    reports test status via gng message reporting.
 */

#include <ultra64.h>
#include "testDriver.h"
#include "gng.h"

extern int controllerSlot;

Test_t testList[] = {

    { &(rdramTest),	"RDRAM memory\n(test 0):",	
	GNG_PASS_FAIL_BIT,	PASS_MESSAGE_RETRACE_COUNT,	0},

    { &(clocktest),	"62.5MHz Clock\n(test 1):",	
	GNG_PASS_FAIL_BIT,	PASS_MESSAGE_RETRACE_COUNT,	1},

    { &(intr1test),	"Cartridge Interrupt\n(test 2):",
	GNG_PASS_FAIL_BIT,	PASS_MESSAGE_RETRACE_COUNT,	2},

    { &(piAllTest),   "PI RW DMA/PIO, INT\n(test 3):",
	GNG_PASS_FAIL_BIT,	PASS_MESSAGE_RETRACE_COUNT,	3},

    { &(rsp),	"RSP Diagnostic Tests\n(test 4):",
	GNG_PASS_FAIL_BIT,	PASS_MESSAGE_RETRACE_COUNT,	4},

    { &(dlDriver),	"RDP Display List Checksum\n(test 5):",
	GNG_PASS_FAIL_BIT,	PASS_MESSAGE_RETRACE_COUNT,	5},

    { &(pifCheck),	"PIF controller\n(test 6):",
	GNG_PASS_FAIL_BIT,	PASS_MESSAGE_RETRACE_COUNT,	6},

    { &(VoltageTest),	"Power and Grounds\n(test 7):",
	GNG_PASS_FAIL_BIT,	PASS_MESSAGE_RETRACE_COUNT,	7},

    { &(ResetTimeTest),	"Reset Time\n(test 8):",
	GNG_PASS_FAIL_BIT,	PASS_MESSAGE_RETRACE_COUNT,	8},

    { &(chk50PReadWrite), "AD16 BUS RW cycle count\n(test 9):",
	GNG_PASS_FAIL_BIT,	PASS_MESSAGE_RETRACE_COUNT,	9},

    { &(chk50PExtjoy), "EXTJOY controller check\n(test 10 = 0x0a):",
	GNG_PASS_FAIL_BIT,	PASS_MESSAGE_RETRACE_COUNT,	10},

    { &(AD16_LatchedAddressTest), "AD16 BUS address latch\n(test 11 = 0x0b):",
	GNG_PASS_FAIL_BIT,	PASS_MESSAGE_RETRACE_COUNT,	11},

    /*
     * All user-interaction tests are run at the end of the test sequence, with
     * the exception of the CPU test.
     */

    { &(ControllerTest), "Controllers 2, 3 and 4\n(test 12 = 0xc):",
	GNG_PASS_FAIL_BIT,	PASS_MESSAGE_RETRACE_COUNT,	12},

    { &(nmitest_phase1),	"Reset Switch\n(button check)\n(user decides PASS/FAIL)\n(test 13 = 0x0d):",
	GNG_PASS_FAIL_BIT | GNG_NMI_TEST_BIT,	PASS_MESSAGE_RETRACE_COUNT,
	13},

    { &(audMain),	"Audio Playback\n(auditory check)\n(user decides PASS/FAIL)\n(Push Button to start)\n(test 14 = 0x0e):",
	GNG_INHIBIT_PRINT,	0,	14},

    { &(RunViTests),	"Video Patterns\n(visual check)\n(user decides PASS/FAIL)\n(Use button to cycle tests)\n(Push Button to start)\n(test 15 = 0x0f):",
	GNG_INHIBIT_PRINT,	0,	15},

    { &(CpuTest), 	"R4300 CPU Test\n(test 16 = 0x10):",
	GNG_PASS_FAIL_BIT,	PASS_MESSAGE_RETRACE_COUNT,	16},

    /*
     * Last entry must have a NULL pTestFunction field entry
     */
    { NULL,	"end of tests",
	GNG_PASS_FAIL_BIT | GNG_FINAL_TEST_BIT,	
	PASS_MESSAGE_RETRACE_COUNT,	16},
};

void testLoop(int index)
{
    Test_t *pTest;
    int errCount;

    pTest = &(testList[index]);

    while (pTest->pTestFunction != NULL) {

	/*
	 * write pTest->testNumber to the LED panel on the ZARU test jig
	 */
	ZaruSetMemA(pTest->testNumber);

	/*
	 * Always print the test message before the test starts.  We'll re-print the
	 * message with PASS/FAIL reporting afterwards, if the test requested it.
	 */
	gng_report(pTest->gngMessageText, 0, GNG_INHIBIT_PRINT, PASS_MESSAGE_RETRACE_COUNT);

	/*
	 * Run the test.
	 */
	errCount = (*pTest->pTestFunction)();

	/*
	 * If test does need PASS/FAIL reporting, do so now.
	 */
	if (pTest->testFlags & GNG_PASS_FAIL_BIT) {
	    gng_report(pTest->gngMessageText, errCount,
		pTest->testFlags, pTest->retraceCount);
	}	
	pTest = &(testList[++index]);
    }
    gng_report("Go/No-go testing complete.\n", 0, 
	GNG_PASS_FAIL_BIT | GNG_FINAL_TEST_BIT, 0);
}

void
testDriver(int nmiEntryFlag) 
{
    Test_t *pTest;
    int i;


    if (nmiEntryFlag == FALSE) {

	/*
	 * Iterate through the tests; optionally do a gng_report with their
	 * status upon completion.
	 */
	testLoop(0);
    } else {
	/*
	 * Find the NMI test by examining the testFlags field, then print a
	 * gng_report() as per the testFlags, retraceCount fields.
	 *
	 * Then, iterate through the rest of the test sequence.
	 */
        i = 0;
        pTest = &(testList[i]);

        while ( (pTest->pTestFunction != NULL) && 
		(pTest->testFlags & GNG_NMI_TEST_BIT) == 0 ) {
	    pTest = &(testList[++i]);
	}
        /*
 	 * We should be pointing at the NMI test now.  Skip past it & continue.
	 */
	testLoop(++i);
    }
}
