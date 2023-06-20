#ifndef __SYSCALL_H_
#define __SYSCALL_H_

#ifdef _LANGUAGE_ASSEMBLY

/*
** Arguments to system calls are in a0,a1,a2,a3,t0,t1,t2.
*/
#define OS_SYSCALL(name)		       \
	LEAF(name);		       \
	li	v0,__OS_TRAP_/**/name; \
	syscall;		       \
	j	ra;		       \
	END(name);

#define OS_SYSCALL5(name)	       \
	LEAF(name);		       \
	li	v0,__OS_TRAP_/**/name; \
	lw	t0,0+4*4(sp);	       \
	syscall;		       \
	j	ra;		       \
	END(name);

#define OS_SYSCALL6(name)	       \
	LEAF(name);		       \
	li	v0,__OS_TRAP_/**/name; \
	lw	t0,0+4*4(sp);	       \
	lw	t1,4+4*4(sp);	       \
	syscall;		       \
	j	ra;		       \
	END(name);

#define OS_SYSCALL0(a) OS_SYSCALL(a)
#define OS_SYSCALL1(a) OS_SYSCALL(a)
#define OS_SYSCALL2(a) OS_SYSCALL(a)
#define OS_SYSCALL3(a) OS_SYSCALL(a)
#define OS_SYSCALL4(a) OS_SYSCALL(a)

#endif

/************************************************************************/

/* Extra bit set of exception was in delay slot */
#define OS_EXC_IN_DELAY_SLOT		0x8000

/* Base for rk system calls */
#define __OS_TRAP_BASE	0


/************************************************************************/
/* Define OS system calls */

#define __OS_TRAP_nosCreateThread	(__OS_TRAP_BASE + 0)
#define __OS_TRAP_nosDestroyThread	(__OS_TRAP_BASE + 1)
#define __OS_TRAP_nosYieldThread	(__OS_TRAP_BASE + 2)
#define __OS_TRAP_nosStartThread	(__OS_TRAP_BASE + 3)
#define __OS_TRAP_nosStopThread		(__OS_TRAP_BASE + 4)
#define __OS_TRAP_nosGetThreadId	(__OS_TRAP_BASE + 5)
#define __OS_TRAP_nosGetThreadPri	(__OS_TRAP_BASE + 6)

#define __OS_TRAP_nosCreateMesgQueue	(__OS_TRAP_BASE + 7)
#define __OS_TRAP_nosSendMesg		(__OS_TRAP_BASE + 8)
#define __OS_TRAP_nosJamMesg		(__OS_TRAP_BASE + 9)
#define __OS_TRAP_nosRecvMesg		(__OS_TRAP_BASE + 10)

#define __OS_TRAP_nosSetEventMesg	(__OS_TRAP_BASE + 11)

#define __OS_TRAP_nosGetIntMask		(__OS_TRAP_BASE + 12)
#define __OS_TRAP_nosSetIntMask		(__OS_TRAP_BASE + 13)

#define __OS_TRAP_nosInvalDCache	(__OS_TRAP_BASE + 14)
#define __OS_TRAP_nosInvalICache	(__OS_TRAP_BASE + 15)
#define __OS_TRAP_nosWritebackDCache	(__OS_TRAP_BASE + 16)
#define __OS_TRAP_nosWritebackDCacheAll	(__OS_TRAP_BASE + 17)

#define __OS_TRAP_nosMapTLB		(__OS_TRAP_BASE + 18)
#define __OS_TRAP_nosUnmapTLB		(__OS_TRAP_BASE + 19)
#define __OS_TRAP_nosUnmapTLBAll	(__OS_TRAP_BASE + 20)
#define __OS_TRAP_nosSetTLBASID		(__OS_TRAP_BASE + 21)

#define __OS_TRAP_nosVirtualToPhysical	(__OS_TRAP_BASE + 22)
#define __OS_TRAP_nosPhysicalToVirtual	(__OS_TRAP_BASE + 23)
#define __OS_TRAP_nosGetCount		(__OS_TRAP_BASE + 24)
#define __OS_TRAP_nosSetCause		(__OS_TRAP_BASE + 25)


#endif /* __SYSCALL_H_ */
