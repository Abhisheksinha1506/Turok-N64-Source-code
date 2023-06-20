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
 * File:	testDriver.h
 * Creator:	hal@sgi.com
 * Purpose:	Declarations & definitions common across test modules
 *
 */

typedef struct {
    int ((*pTestFunction)());	/* pointer to test to be invoked */
    char gngMessageText[1024];	/* text to be printed out on PASS or FAIL */
    int testFlags;		/* to control gng messaging, nmiEntry, etc... */
    int	retraceCount;		/* amount of time to delay after gng message */
    int testNumber;		/* numerical test number; display on LED & TV */
} Test_t;

/*
 * External test declarations
 */
extern int dlDriver(void);
extern int audMain(void);
extern int uji_diags(void);
extern int piAllTest(void);
extern int pifCheck(void);
extern int nmitest_phase1(void);
extern int nmitest_phase2(void);
extern int clocktest(void);
extern int intr1test(void);
extern int RunViTests(void);
extern int VoltageTest(void);
extern int ResetTimeTest(void);
extern int ControllerTest(void);
extern int rsp(void);
extern int CpuTest(void);
extern int rdramTest(void);
extern int chk50PReadWrite(void);
extern int chk50PExtjoy(void);
extern int AD16_LatchedAddressTest(void);
