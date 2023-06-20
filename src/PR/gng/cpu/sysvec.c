/**************************************************************************
 *									  *
 *		 Copyright (C) 1996, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#include <R4300.h>
#include "osint.h"


typedef void (*OSFuncPtr)(void);

extern	void osTestSyscall4(u32 *, u32 *, u32 *, u32 *);
extern	void osTestSyscall5(u32 *, u32 *, u32 *, u32 *, u32 *);
extern	void osTestSyscall6(u32 *, u32 *, u32 *, u32 *, u32 *, u32 *);

OSFuncPtr __osSysCallVec[] = {
    /* OS system calls */

    (OSFuncPtr) osCreateThread,		/* +0 */
    (OSFuncPtr) osDestroyThread,	/* +1 */
    (OSFuncPtr) osYieldThread,		/* +2 */
    (OSFuncPtr) osStartThread,		/* +3 */
    (OSFuncPtr) osStopThread,		/* +4 */
    (OSFuncPtr) osGetThreadId,		/* +5 */
    (OSFuncPtr) osGetThreadPri,		/* +6 */

    (OSFuncPtr) osCreateMesgQueue,	/* +7 */
    (OSFuncPtr) osSendMesg,		/* +8 */
    (OSFuncPtr) osJamMesg,		/* +9 */
    (OSFuncPtr) osRecvMesg,		/* +10 */

    (OSFuncPtr) osSetEventMesg,		/* +11 */

    (OSFuncPtr) osGetIntMask,		/* +12 */
    (OSFuncPtr) osSetIntMask,		/* *13 */

    (OSFuncPtr) osInvalDCache,		/* +14 */
    (OSFuncPtr) osInvalICache,		/* +15 */
    (OSFuncPtr) osWritebackDCache,	/* +16 */
    (OSFuncPtr) osWritebackDCacheAll,	/* +17 */

    (OSFuncPtr) osMapTLB,		/* +18 */
    (OSFuncPtr) osUnmapTLB,		/* +19 */
    (OSFuncPtr) osUnmapTLBAll,		/* +20 */
    (OSFuncPtr) osSetTLBASID,		/* +21 */

    (OSFuncPtr) osVirtualToPhysical,	/* +22 */
    (OSFuncPtr) osPhysicalToVirtual,	/* +23 */

    (OSFuncPtr) osGetCount,		/* +24 */
    (OSFuncPtr) __osSetCause,		/* +25 */

    (OSFuncPtr)0,
};


