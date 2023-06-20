#include <asm.h>
#include <regdef.h>
#include <R4300.h>
#include <syscall.h>


	.text

OS_SYSCALL6(nosCreateThread)
OS_SYSCALL1(nosDestroyThread)
OS_SYSCALL0(nosYieldThread)
OS_SYSCALL1(nosStartThread)
OS_SYSCALL1(nosStopThread)
OS_SYSCALL1(nosGetThreadId)
OS_SYSCALL1(nosGetThreadPri)

OS_SYSCALL3(nosCreateMesgQueue)
OS_SYSCALL3(nosSendMesg)
OS_SYSCALL3(nosJamMesg)
OS_SYSCALL3(nosRecvMesg)

OS_SYSCALL3(nosSetEventMesg)

OS_SYSCALL0(nosGetIntMask)
OS_SYSCALL1(nosSetIntMask)

OS_SYSCALL2(nosInvalDCache)
OS_SYSCALL2(nosInvalICache)
OS_SYSCALL2(nosWritebackDCache)
OS_SYSCALL0(nosWritebackDCacheAll)

OS_SYSCALL6(nosMapTLB)
OS_SYSCALL1(nosUnmapTLB)
OS_SYSCALL0(nosUnmapTLBAll)
OS_SYSCALL1(nosSetTLBASID)

OS_SYSCALL1(nosVirtualToPhysical)
OS_SYSCALL1(nosPhysicalToVirtual)

OS_SYSCALL0(nosGetCount)
OS_SYSCALL1(nosSetCause)

