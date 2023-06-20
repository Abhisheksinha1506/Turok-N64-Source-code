/**************************************************************************
 *									  *
 *		 Copyright (C) 1994, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

/**************************************************************************
 *
 *  Module: exceptasms.s
 *
 *  $Revision: 1.1 $
 *  $Date: 1996/02/29 05:20:28 $
 *  $Author: chn $
 *  $Source: /mdev2/PR/apps.released/gng/cpu/RCS/except2asm.s,v $
 *
 *  Description:
 *      This file contains exception handling routines for Ultra 64 OS.
 *	When an exception of interest occurs, the exception handler sends
 *	a message to a message queue; both the message and the message queue
 *	must be	pre-registered via the osSetEventMesg routine.
 *
 *	The exception handler calls the dispatcher to generate a thread 
 *	context switch when the associated message queue contains a blocking 
 *	thread that has higher priority than the current running thread. 
 *	Otherwise, the interrupted thread should resume normal processing 
 *	after the completion of the exception handler. 
 *
 *	A running thread should only be preempted by a higher priority thread
 *	(waiting for the event message), but NOT by a thread with the
 *	 same priority.
 *
 *  Pseudo-code:
 *	save the registers into the context of the running thread
 *	read the cause register
 *	if not an interrupt, breakpoint, or coprocessor unusable exception, then
 *		jump to panic (spin forever since it's a real exception)
 *	if an interrupt, then
 *		find the correct interrupt handler
 *		clear the interrupt, if necessary
 *	find which event message queue/message to load
 *	load the proper message queue/message from the interrupt message array
 *	insert message to message queue
 *	advance corresponding message queue counters (i.e. first, validCount)
 *	if (message queue is not full) and 
 *		(there is a blocking thread in message queue)
 *		dequeue blocking thread from message queue
 *		enqueue the blocking thread to run queue
 *		if (blocking thread's priority > current thread's priority) 
 *			enqueue the current thread to run queue behind other
 *			threads of same priority
 *		else
 *			enqueue the running thread to FRONT of run queue
 *		jump to dispatcher
 *	else
 *		enqueue the running thread to FRONT of run queue
 *		jump to dispatcher
 */

#include <asm.h>
#include <regdef.h>
#include <R4300.h>
#include <os.h>
#include <rcp.h>
#include <task.h>
#include <rdb.h>

#include "exceptasm.h"
#include "threadasm.h"

#define TLB_FAULT	4

/*
 * LLEAF -- declare leaf routine
 */
#define MLEAF(x)					\
	.ent    x,0;					\
x:;							\
	.frame  sp,0,ra

	.rdata

	/*
	 * Lookup table for offset into interrupt handler table below
	 */
__osIntOffTable:
	.byte 0*4, 5*4, 6*4, 6*4, 7*4, 7*4, 7*4, 7*4
	.byte 8*4, 8*4, 8*4 ,8*4, 8*4, 8*4, 8*4, 8*4
	.byte 0*4, 1*4, 2*4, 2*4, 3*4, 3*4, 3*4, 3*4
	.byte 4*4, 4*4, 4*4, 4*4, 4*4, 4*4, 4*4, 4*4

	/*
	 * Interrupt handler table, ordered in increasing order of priority
	 */
__osIntTable:
	.word	redispatch
	.word	sw1			# CAUSE_SW1
	.word	sw2			# CAUSE_SW2
	.word	rcp			# INT0 - CAUSE_IP3
	.word	cart			# INT1 - CAUSE_IP4
	.word	prenmi			# INT2 - CAUSE_IP5
	.word	panic			# INT3 - CAUSE_IP6
	.word	panic			# INT4 - CAUSE_IP7
	.word	counter			# CAUSE_IP8

	/*
	 * Optional HW interrupt support routines from game
	 */
/* .globl __osHwIntTable; */
__osHwIntTable:
	.word	0			# INT0 - RCP
	.word	0			# INT1 - Cart from AD16
	.word	0			# INT2 - PRENMI from PIF
	.word	0			# INT3 - NC (rdb read on Indy dev board)
	.word	0			# INT4 - NC (rdb write on Indy dev board)

	/* RDB variables */
__osIsRdbWrite:
	.word	0
__osIsRdbRead:
	.word	0

	.text
	.set	noat
	.set	noreorder

LEAF(__osExceptionPreamble2)
	la	k0,__osException
	jr	k0
	nop
END(__osExceptionPreamble2)


MLEAF(__osException)

	mfc0	k0,C0_CAUSE			# k0 = CAUSE 
	li	k1,EXC_SYSCALL
	andi	k0,CAUSE_EXCMASK		# t0 = CAUSE
	beq	k0,k1,handle_syscall		# jump to syscall handler
	nop

	/*
	 * Save registers into the context of a temporary thread structure
	 *
	 */

	la	k0,__osThreadSave

	/*
	 * Save AT first, so we can enable use of AT by the assembler early on.
	 */
	sd	AT,T_CONTEXT_AT(k0)

	.set	at

	/*
	 * Save the SR with the EXL bit ON, but then turn it off during the
	 * the exception handler (aids debugging.)  Turning off SR_IE will
	 * disable further interrupts.
	 *
	 * The SR contents will be accessible in k1 for the entire handler.
	 */
	mfc0	k1,C0_SR
	sw	k1,T_CONTEXT_SR(k0)
	and	k1,~(SR_EXL|SR_IE|SR_KSU_MASK)
	mtc0	k1,C0_SR
        nop; nop; nop; nop/*XXX*/

	/* save t0-t2 so that they can be used as scratch pad */
	sd	t0,T_CONTEXT_T0(k0)
	sd	t1,T_CONTEXT_T1(k0)
	sd	t2,T_CONTEXT_T2(k0)
	sw	zero,T_FP(k0)
	mfc0	t0,C0_CAUSE

	.set	reorder


	/* check the type of interrupt, process rdb read and write seperately */
	andi	t1,t0,CAUSE_EXCMASK
	li	t2,EXC_INT
	bne	t1,t2,2f
	and	t1,k1,t0
	and	t2,t1,CAUSE_IP7
	beq	t2,zero,1f
	/* rdb write interrupt, Indy has written to U64 */
	li	t1,1
	sw	t1,__osIsRdbWrite
	b	3f
1:
	and	t2,t1,CAUSE_IP6
	beq	t2,zero,2f
	/* rdb read interrupt, Indy has read from U64 */
	li	t1,1
	sw	t1,__osIsRdbRead
	b	3f
2:
	/* not rdb interrupts, copy context to the current thread context */
	sw	zero,__osIsRdbWrite
	sw	zero,__osIsRdbRead
	move	t0,k0
	lw	k0,__osRunningThread
	ld	t1,T_CONTEXT_AT(t0)
	sd	t1,T_CONTEXT_AT(k0)
	ld	t1,T_CONTEXT_SR(t0)
	sd	t1,T_CONTEXT_SR(k0)
	ld	t1,T_CONTEXT_T0(t0)
	sd	t1,T_CONTEXT_T0(k0)
	ld	t1,T_CONTEXT_T1(t0)
	sd	t1,T_CONTEXT_T1(k0)
	ld	t1,T_CONTEXT_T2(t0)
	sd	t1,T_CONTEXT_T2(k0)
3:
	/*
	 * Save the rest of the registers.
	 */
	sd	v0,T_CONTEXT_V0(k0)
	sd	v1,T_CONTEXT_V1(k0)
	sd	a0,T_CONTEXT_A0(k0)
	sd	a1,T_CONTEXT_A1(k0)
	sd	a2,T_CONTEXT_A2(k0)
	sd	a3,T_CONTEXT_A3(k0)
	sd	t3,T_CONTEXT_T3(k0)
	sd	t4,T_CONTEXT_T4(k0)
	sd	t5,T_CONTEXT_T5(k0)
	sd	t6,T_CONTEXT_T6(k0)
	sd	t7,T_CONTEXT_T7(k0)
	sd	s0,T_CONTEXT_S0(k0)
	sd	s1,T_CONTEXT_S1(k0)
	sd	s2,T_CONTEXT_S2(k0)
	sd	s3,T_CONTEXT_S3(k0)
	sd	s4,T_CONTEXT_S4(k0)
	sd	s5,T_CONTEXT_S5(k0)
	sd	s6,T_CONTEXT_S6(k0)
	sd	s7,T_CONTEXT_S7(k0)
	sd	t8,T_CONTEXT_T8(k0)
	sd	t9,T_CONTEXT_T9(k0)
	sd	gp,T_CONTEXT_GP(k0)
	sd	sp,T_CONTEXT_SP(k0)
	sd	s8,T_CONTEXT_S8(k0)
	sd	ra,T_CONTEXT_RA(k0)
	mflo	t0
	sd	t0,T_CONTEXT_LO(k0)
	mfhi	t0
	sd	t0,T_CONTEXT_HI(k0)

	.set	noreorder

	mfc0	t0,C0_EPC
	sw	t0,T_CONTEXT_PC(k0)

	/*
	 * If the thread has ever touched the floating point unit,
	 * save the floating point registers away.
	 */
	lw	t0,T_FP(k0)
	beqz	t0,1f
	nop

	cfc1	t0, $31
	nop
	sw	t0, T_CONTEXT_FPCSR(k0)
	s.d     $f0,T_CONTEXT_FP0(k0)
	s.d     $f2,T_CONTEXT_FP2(k0)
	s.d     $f4,T_CONTEXT_FP4(k0)
	s.d     $f6,T_CONTEXT_FP6(k0)
	s.d     $f8,T_CONTEXT_FP8(k0)
	s.d     $f10,T_CONTEXT_FP10(k0)
	s.d     $f12,T_CONTEXT_FP12(k0)
	s.d     $f14,T_CONTEXT_FP14(k0)
	s.d     $f16,T_CONTEXT_FP16(k0)
	s.d     $f18,T_CONTEXT_FP18(k0)
	s.d     $f20,T_CONTEXT_FP20(k0)
	s.d     $f22,T_CONTEXT_FP22(k0)
	s.d     $f24,T_CONTEXT_FP24(k0)
	s.d     $f26,T_CONTEXT_FP26(k0)
	s.d     $f28,T_CONTEXT_FP28(k0)
	s.d     $f30,T_CONTEXT_FP30(k0)

1:
	/*
	 * Get CAUSE register contents and save it away.  Although not
	 * strictly part of the thread context (it isn't restored), save
	 * the actual bits were are using for debugging purposes.
	 *
	 * The CAUSE contents will be accessible in t0 for the entire handler.
	 */
	mfc0	t0,C0_CAUSE
	sw	t0,T_CONTEXT_CAUSE(k0)

	.set	reorder

	/*
	 * save rcp interrupt mask
	 */
	lw	t1,PHYS_TO_K1(MI_INTR_MASK_REG)	# get rcp interrupt register
	sw	t1,T_CONTEXT_RCP(k0)

	/*
	 * Mark the previously running thread as merely runnable.
	 */
	li	t1,OS_STATE_RUNNABLE
	sh	t1,T_STATE(k0)

	/* see if it is rdb write interrupt */
	lw	t1,__osIsRdbWrite
	beq	t1,zero,1f
	/* Indy has written */
	la	t2,RDB_WRITE_INTR_REG
	sw	$0,0(t2)		/* clear interrupt condition */
	lw	a0,RDB_BASE_REG
	jal	kdebugserver
	b	__osDispatchThreadSave
1:
	/* see if it is rdb read interrupt */
	lw	t1,__osIsRdbRead
	beq	t1,zero,3f
	/* Indy has read */
	la	t2,RDB_READ_INTR_REG
	sw	$0,0(t2)
	lw	t1,__osRdbSendMessage
	beq	t1,zero,2f
	li	a0,OS_EVENT_RDB_READ_OK * ES_SIZE
	jal	send_mesg
2:
	lw	t1,__osRdbWriteOK
	add	t1,1
	sw	t1,__osRdbWriteOK
	b	__osDispatchThreadSave
3:
	/* not rdb interrupts */

	/*
	 * Vector to handler of interest.  Currently we are only interested
	 * in break exceptions, coprocessor unusable exceptions, and interrupts.
	 * Other interrupts go to the fault event mailbox (if someone is
	 * registered) or just cause a panic
	 */
	andi	t1,t0,CAUSE_EXCMASK		# t0 = CAUSE
#ifdef _CHN_
	li	t2,EXC_MOD
	beq	t1,t2,handle_tlbfault		# jump to TLB handler
	li	t2,EXC_RMISS
	beq	t1,t2,handle_tlbfault		# jump to TLB handler
	li	t2,EXC_WMISS
	beq	t1,t2,handle_tlbfault		# jump to TLB handler
#endif
	li	t2,EXC_BREAK
	beq	t1,t2,handle_break
	li	t2,EXC_CPU
	beq	t1,t2,handle_CpU
	li	t2,EXC_INT
	bne	t1,t2,panic

	/*
	 * We know we're an interrupt here.  Vector to appropriate handler.
	 */
handle_interrupt:
	and	s0,k1,t0			# AND pending bits with enabled
						# k1 = SR, t0 = CAUSE
next_interrupt:
	and	t1,s0,CAUSE_IPMASK		# Mask out remaining int bits
	srl	t2,t1,CAUSE_IPSHIFT+4		# shift to high nibble
	bne	t2,zero,1f			# bits set in high nibble?
	srl	t2,t1,CAUSE_IPSHIFT		# get low nibble
	add	t2,16				# get second half of table
1:	lbu	t2,__osIntOffTable(t2)		# get value from table
	lw	t2,__osIntTable(t2)		# get handler
	j	t2				# and jump to it

	/*
	 * Counter interrupt - clear interrupt condition and send message.
	 */
counter:
	.set	noreorder
	mfc0	t1,C0_COMPARE			# read COMPARE reg
	mtc0	t1,C0_COMPARE			# and re-write it to clear int
	.set	reorder

	li	a0,OS_EVENT_COUNTER * ES_SIZE
	jal	send_mesg
	and	s0,~SR_IBIT8
	b	next_interrupt

	/*
	 * Cartridge interrupt
	 */
cart:
	li	a0,OS_EVENT_CART * ES_SIZE
	jal	send_mesg
	and	s0,~SR_IBIT4
	li	t2,HW_INT2_OFFSET
	lw	t2,__osHwIntTable(t2)		# get handler
	beqz	t2,1f
	jal	t2
1:
	b	next_interrupt

	/*
	 * Rcp interrupt
	 */
rcp:
	lw	s1,PHYS_TO_K1(MI_INTR_REG)	# get rcp interrupt register
	andi	s1,0x3f				# look at 6 bits only
	andi	t1,s1,MI_INTR_SP
	beqz	t1,vi

	/*
	 * handle SP interrupt
	 */

	andi	s1,~MI_INTR_SP & 0x3f		# note that this was seen
	lw	t4,PHYS_TO_K1(SP_STATUS_REG)	# fetch the status register
	li	t1,SP_CLR_INTR
	sw	t1,PHYS_TO_K1(SP_STATUS_REG)	# clear sp interrupt
	andi	t4, (SP_STATUS_TASKDONE | SP_STATUS_YIELDED)
	beqz	t4, sp_other_break
	li	a0,OS_EVENT_SP * ES_SIZE
	jal	send_mesg
	beqz	s1,NoMoreRcpInts		# are we done?
	b	vi				# handle the next one

sp_other_break:
	li	a0,OS_EVENT_SP_BREAK * ES_SIZE
	jal	send_mesg
	beqz	s1,NoMoreRcpInts		# are we done?

vi:
	andi	t1,s1,MI_INTR_VI
	beqz	t1,ai

	/*
	 * handle VI interrupt
	 */
	andi	s1,~MI_INTR_VI & 0x3f		# note that this was seen
	sw	zero,PHYS_TO_K1(VI_CURRENT_REG)	# clear vi interrupt
	li	a0,OS_EVENT_VI * ES_SIZE
	jal	send_mesg
	beqz	s1,NoMoreRcpInts		# are we done?

ai:
	andi	t1,s1,MI_INTR_AI
	beqz	t1,si

	/*
	 * handle AI interrupt
	 */
	andi	s1,~MI_INTR_AI & 0x3f		# note that this was seen
	li	t1,1
	sw	t1,PHYS_TO_K1(AI_STATUS_REG)	# clear ai interrupt
	li	a0,OS_EVENT_AI * ES_SIZE
	jal	send_mesg
	beqz	s1,NoMoreRcpInts		# are we done?

si:
	andi	t1,s1,MI_INTR_SI
	beqz	t1,pi

	/*
	 * handle SI interrupt
	 */
	andi	s1,~MI_INTR_SI & 0x3f		# note that this was seen
	sw	zero,PHYS_TO_K1(SI_STATUS_REG)	# clear si interrupt
	li	a0,OS_EVENT_SI * ES_SIZE
	jal	send_mesg
	beqz	s1,NoMoreRcpInts		# are we done?

pi:
	andi	t1,s1,MI_INTR_PI
	beqz	t1,dp

	/*
	 * handle PI interrupt
	 */
	andi	s1,~MI_INTR_PI & 0x3f		# note that this was seen
	li	t1,PI_CLR_INTR
	sw	t1,PHYS_TO_K1(PI_STATUS_REG)	# clear pi interrupt
	li	a0,OS_EVENT_PI * ES_SIZE
	jal	send_mesg
	beqz	s1,NoMoreRcpInts		# are we done?

dp:
	andi	t1,s1,MI_INTR_DP
	beqz	t1,NoMoreRcpInts
	
	/*
	 * handle DP interrupt
	 */
	andi	s1,~MI_INTR_DP & 0x3f		# note that this was seen
	li	t1,MI_CLR_DP_INTR
	sw	t1,PHYS_TO_K1(MI_BASE_REG)	# clear dp interrupt
	li	a0,OS_EVENT_DP * ES_SIZE
	jal	send_mesg

NoMoreRcpInts:

	/* 
	 * We get here when there are no more RCP interrupts to
	 * process. All threads blocked on RCP int messages have 
	 * been queued on the ready queue at this point.
	 */

	and	s0,~SR_IBIT3
	b 	next_interrupt


prenmi:
	/*
	 * Pre NMI interrupt - application need to shut down gfx and audio
	 */
	
	/*
	 * We need to turn off INT2 mask bit for the old thread
	 */

	lw	k1,T_CONTEXT_SR(k0)
	and	k1, ~SR_IBIT5
	sw	k1,T_CONTEXT_SR(k0)

	la	t1, __osShutdown
	lw	t2, 0(t1)
	beqz	t2, firstnmi
	and     s0,~SR_IBIT5
	b       redispatch
	
firstnmi:
	li	t2, 1
	sw	t2, 0(t1)			# Turn on shutdown mode
	li	a0,OS_EVENT_PRENMI * ES_SIZE
	jal     send_mesg
	and     s0,~SR_IBIT5
	lw	t2,__osRunQueue
	lw	k1,T_CONTEXT_SR(t2)
	and	k1, ~SR_IBIT5
	sw	k1,T_CONTEXT_SR(t2)
	b       redispatch


	/*
	 * SW2 interrupt - clear interrupt condition and send message.
	 */
sw2:
	and	t0,~CAUSE_SW2			# t0 has CAUSE reg contents
	.set	noreorder
	mtc0	t0,C0_CAUSE			# clear int by turning off bit
	.set	reorder

	li	a0,OS_EVENT_SW2 * ES_SIZE
	jal	send_mesg
	and	s0,~SR_IBIT2
	b	next_interrupt

	/*
	 * SW1 interrupt - clear interrupt condition and send message.
	 */
sw1:
	and	t0,~CAUSE_SW1			# t0 has CAUSE reg contents
	.set	noreorder
	mtc0	t0,C0_CAUSE			# clear int by turning off bit
	.set	reorder

	li	a0,OS_EVENT_SW1 * ES_SIZE
	jal	send_mesg
	and	s0,~SR_IBIT1
	b	next_interrupt

	/*
	 * Break exception - send appropriate message.
	 */
handle_break:
	li	t1,1
	sh	t1,T_FLAGS(k0)
	li	a0,OS_EVENT_CPU_BREAK * ES_SIZE
	jal	send_mesg
	b	redispatch

#ifdef _CHN_
	/*
	 * TLB Mod exception - send appropriate message.
	 */
handle_tlbfault:
	/* Clear TLB? */
	li	t3,OS_STATE_STOPPED	# leave thread stopped
	sh	t3,T_STATE(k0)
	li	t3,TLB_FAULT		# set fault flag in TCB
	sh	t3,T_FLAGS(k0)
	.set	noreorder
	mfc0	t4,C0_BADVADDR		# get and save useful badvaddr
	.set	reorder
	sw	t4,T_CONTEXT_BADVADDR(k0)# k0 = __osRunningThread

	li	t2,EXC_MOD		# if mod, load the proper mesg
	bne	t1,t2,1f		# 
	li	a0,OS_EVENT_TLB_MOD * ES_SIZE
	j	end_tlbfault
1:
	li	t2,EXC_RMISS		# if rmiss, load the proper mesg
	bne	t1,t2,2f		# 
	li	a0,OS_EVENT_TLB_REFILL * ES_SIZE
	j	end_tlbfault
2:
	li	a0,OS_EVENT_TLB_INV * ES_SIZE
end_tlbfault:
	jal	send_mesg
        j       __osDispatchThread      # and jump to dispatch new thread

#endif  /* _CHN_ */

redispatch:
	/*
	 * Now, we compare the current thread's priority with that of the
	 * thread at the head of the run queue. If current thread's
	 * priority is higher, we stuff it in front of the run queue and
	 * call dispatcher. If not, we simply enqueue current thread behind
	 * other threads of same priority and call dispatcher to switch
	 * to new thread.
	 */
	lw	t1,T_PRIORITY(k0)	# t1 = current.priority (k0 = current)
	lw	t2,__osRunQueue
	lw	t3,T_PRIORITY(t2)	# t3 = new.priority (t2 = new)
	bge	t1,t3,enqueueRunning	# if current.priority >= new.priority, 
					#    insert current to front of run Q
	move	a1,k0			# k0 = __osRunningThread
	la	a0,__osRunQueue		# else enqueue current normally
	jal	__osEnqueueThread	
	j	__osDispatchThread	# and jump to dispatch new thread

enqueueRunning:
	/*
	 * Here, we enqueue the current running thread to the FRONT of
	 * the run queue and call dispatcher to invoke it again. 
	 *
	 * Recall k0 = __osRunningThread
	 */

	la	t1,__osRunQueue		# t1 = list = __osRunQueue
	lw	t2,T_NEXT(t1)		# t2 = list->next
	sw	t2,T_NEXT(k0)		# new->next = list->next
	sw	k0,T_NEXT(t1)		# list->next = new
	j	__osDispatchThread

	/*
	 * Panic: store additional registers of interest and print
	 * exception frame. However, if someone (like the debugger)
	 * has registered to receive faults, just send them instead.
	 */
panic:
	li	t1,OS_STATE_STOPPED	# leave thread stopped
	sh	t1,T_STATE(k0)
	li	t1,2			# set fault flag in TCB
	sh	t1,T_FLAGS(k0)
	.set	noreorder
	mfc0	t2,C0_BADVADDR		# get and save useful badvaddr
	.set	reorder
	sw	t2,T_CONTEXT_BADVADDR(k0)# k0 = __osRunningThread
	li	a0,OS_EVENT_FAULT * ES_SIZE
	jal	send_mesg
	j       __osDispatchThread	# don't re-queue faulting thread
	END(__osException)

	/*
	 * This is now a function call, rather than a branch target.
	 * On entry, a0 contains the offset into the event queue table.
	 * If a thread has registered to receive this event, then we
	 * will re-awaken that thread if it is blocked on the queue
	 * by sending it the specified message.
	 */
MLEAF(send_mesg)
	move	s2,ra			# Save return address
	la	t2,__osEventStateTab	# Need to get the message & queue
	addu	t2,a0			# a0 = index to interrupt message table

	/*
	 * Here, we prepare to send the message to the given message queue
	 */
	lw	t1,ES_QUEUE(t2)		# t2 = _InterruptMessage entry
	beqz	t1,send_done		# If empty queue, we simply return
					# t1 = message queue (mq)

	lw	t3,MQ_VALIDCOUNT(t1)	# t3 = mq->validCount
	lw	t4,MQ_MSGCOUNT(t1)	# t4 = mq->msgCount
					
	/* 
	 * If message queue is full, we simply return.
	 * if (mq->validCount >= mq->msgCount) return;
	 */
	bge	t3,t4,send_done

	/* 
	 * Calculate the next available empty slot to write message.
	 * last = (mq->first + mq->validCount) % msgCount;
	 */
	lw	t5,MQ_FIRST(t1)		# t5 = mq->first
	addu	t5,t5,t3		# t5 = first+validCount
	rem	t5,t5,t4		# t5 = (first+validCount) % msgCount

	/* 
	 * Now, we insert the message into the empty slot.
	 * mq->msg[last] = msg;
	 */
	lw	t4,MQ_MSG(t1)		# t4 = mq->msg
	mul	t5,t5,4			# t5 = msg array offset
	addu	t4,t4,t5		# t4 = message array slot
	lw	t5,ES_MESSAGE(t2)	# t5 = message
	sw	t5,0(t4)		# Write message into slot
		
	/* 
	 * Increment the valid message counter.
	 * mq->validCount++;
	 */
	addu	t2,t3,1			# t2 = validCount (t3) +1
	sw	t2,MQ_VALIDCOUNT(t1)	# Store updated validCount to msg queue

	/* 
	 * If there is no thread blocked on the queue being empty,
	 * we just return.
	 * if (mq->queue->next == NULL) return;
	 */
	lw	t2,MQ_MTQUEUE(t1)	# if mtqueue->next == NULL
	lw	t3,0(t2)		#
	beq	t3,0,send_done		# then we simply return

	/* 
	 * Otherwise, we dequeue the blocking thread and enqueue it to 
	 * the run queue behind other threads of same priority
	 */
	move	a0,t1			# else we dequeue the blocking thread,
	jal	__osPopThread
	move	t2,v0			# save returned thread in t2

	move	a1,t2			# and enqueue it to the run queue
	la	a0,__osRunQueue		# behind other threads of same priority
	jal	__osEnqueueThread

send_done:
	jr	s2			# Jump to saved return address
END(send_mesg)

	/*
	 * We got a coprocessor unusable exception, presumably due to an
	 * access to floating point.
	 *
	 * Mark the thread as a floating point thread so that we will now
	 * save its registers on context switches. Also enable the use
	 * of the floating point register so as to not fault again.
	 */
MLEAF(handle_CpU)
	and	t1,t0,CAUSE_CEMASK		# t0 = CAUSE reg contents
	srl	t1,CAUSE_CESHIFT
	li	t2,1				# FPU?
	bne	t1,t2, panic			# Well, it better be

	li	t1,1
	sw	t1,T_FP(k0)			# flag thread for FP

	lw	k1,T_CONTEXT_SR(k0)		# retrieve original SR
	or	k1,SR_CU1			# make FPU usable
	sw	k1,T_CONTEXT_SR(k0)		# put it back in context

	/*
	 * We already have code to place the running thread back on
	 * the run queue and dispatch it very efficiently, so we will
	 * simply branch there. Be careful if enqueueRunning changes for
	 * any reason!! K0 does (correctly) contain __osRunningThread.
	 */
	b	enqueueRunning
END(handle_CpU)

MLEAF(handle_syscall)
#define REGSIZE		8
#define ARG_BUILD	(8*REGSIZE)	/* max of 8 args for syscalls */
#define	SAVE_SIZE	(6*REGSIZE)	/* 6 registers saved */

	/* We use a0-a3,t0-t2 to pass arguments */

	.frame  sp,ARG_BUILD+SAVE_SIZE,ra
	.mask   0xb0070000,-4
	.set    at
	.set    noreorder

	/* Use calling thread stack (sp) */

	subu	sp,ARG_BUILD+SAVE_SIZE
	move	k0,sp

	/*
	 * Save a few registers. Since a system call is just like a 
	 * procedure call, none of the usual temporaries need to be saved.
	 * However, save ra, sp, gp, s2, s1, and s0 because we use them.
	 */

        sd      ra,ARG_BUILD+5*REGSIZE(k0)

        sd      sp,ARG_BUILD+4*REGSIZE(k0)
        sd      gp,ARG_BUILD+3*REGSIZE(k0)
        sd      s2,ARG_BUILD+2*REGSIZE(k0)
        sd      s1,ARG_BUILD+1*REGSIZE(k0)
        sd      s0,ARG_BUILD+0*REGSIZE(k0)
	
	/* Save exception context ino in s0 and s1 */
	mfc0	s0,C0_SR
	mfc0	s1,C0_EPC

	/*
	 * Push the 5th and 6th arguments onto the stack
	 */
	sw	t0,0+4*4(k0)
	sw	t1,4+4*4(k0)

	/*
	 * Clear EXL bit. Enough state is saved at this point to allow
	 * interrupts to occur. Stop using k0 immediately. Make sure the
	 * imask bits of the sr remain untouched (this is so kernel
	 * startup will work).
	 */
	li      t4,~(SR_EXL|SR_KSU_MASK)
	and     t4,s0
	mtc0    t4,C0_SR
        nop; nop; nop; nop/*XXX*/
        nop; nop; nop; nop/*XXX*/

        /* Validate system call # (its in v0) */

	/*
	 * Call appropriate system call handler. Use v0 as an index into
	 * the __osSysCallVec
	 */
	sll	v0,2
	la	t9,__osSysCallVec
	addu	t9,v0
	lw	t9,0(t9)
	la	gp,_gp
	jalr	t9
	nop

        /*
         * Restore sr (which has EXL high), and wait a bit until k0 can
         * be safely used. We can continue to use sp until then. Add 4
         * to saved epc so that upon return we won't re-execute the syscall
         * instruction.
         */
        mtc0    s0,C0_SR
        nop; nop; nop; nop/*XXX*/
        nop; nop; nop; nop/*XXX*/

        addiu   s1,4
        move    k0,sp
        mtc0    s1,C0_EPC

        ld      ra,ARG_BUILD+5*REGSIZE(k0)
/*
        ld      sp,ARG_BUILD+4*REGSIZE(k0)
*/
        ld      gp,ARG_BUILD+3*REGSIZE(k0)
        ld      s2,ARG_BUILD+2*REGSIZE(k0)
        ld      s1,ARG_BUILD+1*REGSIZE(k0)
        ld      s0,ARG_BUILD+0*REGSIZE(k0)
	
	/* 
	 * Restore stack pointer 
	 */
	addu	sp,ARG_BUILD+SAVE_SIZE

	nop
	nop
	nop
	nop
	eret


#undef ARG_BUILD
#undef SAVE_SIZE

END(handle_syscall)


/*
 * void __osEnqueueAndYield(OSThread **q);
 *
 * If the given queue is non-NULL, enqueue the running thread on it.
 * Then yield the processor by jumping to the dispatcher.
 *
 * All interrupts should be disabled when this routine is called.
 */
MLEAF(__osEnqueueAndYield)

	.set	reorder

	/*
	 * Save context into __osRunningThread's register area.
	 *
	 * In addition to the status register, only save the callee saved
	 * registers.  The status register value saved is that of the
	 * original contents with the SR_EXL bit set, consistent with
	 * the use of the dispatcher (see below).
	 */
	lw	a1,__osRunningThread

	.set	noreorder
	mfc0	t0,C0_SR
	.set	reorder

	ori	t0,SR_EXL
	sw	t0,T_CONTEXT_SR(a1)
	sd	s0,T_CONTEXT_S0(a1)
	sd	s1,T_CONTEXT_S1(a1)
	sd	s2,T_CONTEXT_S2(a1)
	sd	s3,T_CONTEXT_S3(a1)
	sd	s4,T_CONTEXT_S4(a1)
	sd	s5,T_CONTEXT_S5(a1)
	sd	s6,T_CONTEXT_S6(a1)
	sd	s7,T_CONTEXT_S7(a1)
	sd	gp,T_CONTEXT_GP(a1)
	sd	sp,T_CONTEXT_SP(a1)
	sd	s8,T_CONTEXT_S8(a1)
	sd	ra,T_CONTEXT_RA(a1)
	sw	ra,T_CONTEXT_PC(a1)

	/*
	 * If the thread has ever touched the floating point unit,
	 * save the callee saved floating point registers away.
	 */
	lw	k1,T_FP(a1)
	beqz	k1,1f

	cfc1	k1, $31
	sw	k1, T_CONTEXT_FPCSR(a1)
	s.d     $f20,T_CONTEXT_FP20(a1)
	s.d     $f22,T_CONTEXT_FP22(a1)
	s.d     $f24,T_CONTEXT_FP24(a1)
	s.d     $f26,T_CONTEXT_FP26(a1)
	s.d     $f28,T_CONTEXT_FP28(a1)
	s.d     $f30,T_CONTEXT_FP30(a1)

1:
	/*
	 * save rcp interrupt mask
	 */
	lw	k1,PHYS_TO_K1(MI_INTR_MASK_REG)	# get rcp interrupt register
	sw	k1,T_CONTEXT_RCP(a1)

	/*
	 * Put running thread onto given queue, if one is given.
	 */
	beqz	a0,noEnqueue
	jal	__osEnqueueThread
noEnqueue:
	j	__osDispatchThread
END(__osEnqueueAndYield)

/*
 * void __osEnqueueThread(OSThread **queue, OSThread *new)
 *
 * Enqueue the given thread on to the given queue after all other threads
 * of the same priority.
 *
 * NOTE: the compiled translation of this routine should not use the stack!
 * It is called directly out of the exception handler and thus it will be
 * more difficult to describe the stack requirements of the thread to the user.
 *
 *	void
 *	__osEnqueueThread(OSThread **queue, OSThread *new)
 *	{
 *		register OSThread *pred, *succ;
 *
 *		pred = (OSThread *)queue;
 *		succ = pred->next;
 *
 *		while (succ->priority >= new->priority) {
 *			pred = succ;
 *			succ = succ->next;
 *		}
 *
 *		new->next = pred->next;
 *		pred->next = new;
 *		new->queue = queue;
 *	}
 */
MLEAF(__osEnqueueThread)
	move	t9,a0			# pred = (OSThread *)queue;
	lw	t8,T_NEXT(a0)		# succ = pred->next;
	lw	t7,T_PRIORITY(a1)
	lw	t6,T_PRIORITY(t8)
	blt	t6,t7,2f
1:
	move	t9,t8			# pred = succ;
	lw	t8,T_NEXT(t8)		# succ = succ->next;
	lw	t6,T_PRIORITY(t8)
	bge	t6,t7,1b
2:
	lw	t8,T_NEXT(t9)
	sw	t8,T_NEXT(a1)		# new->next = pred->next
	sw	a1,T_NEXT(t9)		# pred->next = new;
	sw	a0,T_QUEUE(a1)		# new->queue = queue;
	jr	ra
END(__osEnqueueThread)

/*
 * OSThread *__osPopThread(OSThread **queue)
 *
 * Pop (Dequeue) the highest priority thread from the given queue.
 *
 *	OSThread *
 *	__osPopThread(OSThread **queue)
 *	{
 *		register OSThread *h;
 *		register OSThread *t;
 *
 *		h = (OSThread *) queue;
 *		t = h->next;
 *		h->next = t->next;
 *	#ifdef _DEBUG
 *		t->next = (OSThread *)NULL;
 *	#endif
 *		return(t);
 *	}
 */
MLEAF(__osPopThread)
	lw	v0,0(a0)		# h = (OSThread *) queue; t = h->next;
	lw	t9,T_NEXT(v0)
	sw	t9,0(a0)		# h->next = t->next;
#ifdef _DEBUG
	sw	zero,T_NEXT(v0)		# t->next = (OSThread *)NULL;
#endif
	jr	ra
END(__osPopThread)

/*
 * void __osDispatchThread(void)
 *
 * This code is the thread dispatcher. It dequeues the highest priority
 * runnable thread from the run queue, saves it as __osRunningThread,
 * restores its registers, and does an eret to restart it.
*/
MLEAF(__osDispatchThread)
1:	la	a0,__osRunQueue
	jal	__osPopThread
	sw	v0,__osRunningThread
	li	t0, OS_STATE_RUNNING
	sh	t0, T_STATE(v0)
	move	k0,v0

__osDispatchThreadSave:

	.set	noat

	ld	AT,T_CONTEXT_AT(k0)
	ld	v0,T_CONTEXT_V0(k0)
	ld	v1,T_CONTEXT_V1(k0)
	ld	a0,T_CONTEXT_A0(k0)
	ld	a1,T_CONTEXT_A1(k0)
	ld	a2,T_CONTEXT_A2(k0)
	ld	a3,T_CONTEXT_A3(k0)
	ld	t0,T_CONTEXT_T0(k0)
	ld	t1,T_CONTEXT_T1(k0)
	ld	t2,T_CONTEXT_T2(k0)
	ld	t3,T_CONTEXT_T3(k0)
	ld	t4,T_CONTEXT_T4(k0)
	ld	t5,T_CONTEXT_T5(k0)
	ld	t6,T_CONTEXT_T6(k0)
	ld	t7,T_CONTEXT_T7(k0)
	ld	s0,T_CONTEXT_S0(k0)
	ld	s1,T_CONTEXT_S1(k0)
	ld	s2,T_CONTEXT_S2(k0)
	ld	s3,T_CONTEXT_S3(k0)
	ld	s4,T_CONTEXT_S4(k0)
	ld	s5,T_CONTEXT_S5(k0)
	ld	s6,T_CONTEXT_S6(k0)
	ld	s7,T_CONTEXT_S7(k0)
	ld	t8,T_CONTEXT_T8(k0)
	ld	t9,T_CONTEXT_T9(k0)
	ld	gp,T_CONTEXT_GP(k0)
	ld	sp,T_CONTEXT_SP(k0)
	ld	s8,T_CONTEXT_S8(k0)
	ld	ra,T_CONTEXT_RA(k0)
	ld	k1,T_CONTEXT_LO(k0)
	mtlo	k1
	ld	k1,T_CONTEXT_HI(k0)
	mthi	k1
	lw	k1,T_CONTEXT_PC(k0)
	.set	noreorder
	mtc0	k1,C0_EPC
        nop; nop; nop; nop/*XXX*/

	/*
	 * We restore the SR here, but since the SR_EXL bit is on,
	 * interrupts remain disabled.
	 */
	lw	k1,T_CONTEXT_SR(k0)
	mtc0	k1,C0_SR

	/*
	 * Restore the floating point registers only for floating point threads.
	 */

	lw	k1,T_FP(k0)
	beqz	k1,1f
	nop

	lw	k1,T_CONTEXT_FPCSR(k0)
	ctc1	k1,$31
	l.d     $f0,T_CONTEXT_FP0(k0)
	l.d     $f2,T_CONTEXT_FP2(k0)
	l.d     $f4,T_CONTEXT_FP4(k0)
	l.d     $f6,T_CONTEXT_FP6(k0)
	l.d     $f8,T_CONTEXT_FP8(k0)
	l.d     $f10,T_CONTEXT_FP10(k0)
	l.d     $f12,T_CONTEXT_FP12(k0)
	l.d     $f14,T_CONTEXT_FP14(k0)
	l.d     $f16,T_CONTEXT_FP16(k0)
	l.d     $f18,T_CONTEXT_FP18(k0)
	l.d     $f20,T_CONTEXT_FP20(k0)
	l.d     $f22,T_CONTEXT_FP22(k0)
	l.d     $f24,T_CONTEXT_FP24(k0)
	l.d     $f26,T_CONTEXT_FP26(k0)
	l.d     $f28,T_CONTEXT_FP28(k0)
	l.d     $f30,T_CONTEXT_FP30(k0)

1:
	/*
	 * restore rcp interrupt mask
	 */
	lw	k1,T_CONTEXT_RCP(k0)
	sll	k1,1
	la	k0,__osRcpImTable
	addu	k1,k0
	lhu     k1, 0(k1)
	la	k0,PHYS_TO_K1(MI_INTR_MASK_REG)
        sw      k1, 0(k0)

	nop
	nop
	nop
	nop
	eret
	.set	reorder
END(__osDispatchThread)


