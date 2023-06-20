/*
 * tlb.s -- tlb code
 */

#include <sys/sbd.h>
#include <regdef.h>
#include <asm.h>

#define SC_TLBHI_VPNMASK	0xfff80000
	.text

/*
 * get_tlblo(index) -- return entry low contents of tlb entry "index"
 */
LEAF(get_tlblo0)
XLEAF(get_tlblo)
	.set	noreorder
	mfc0	t0,C0_SR		# save sr
	mtc0	zero,C0_SR		# disable interrupts
	nop
	mfc0	t1,C0_TLBHI		# save current pid
	sll	a0,TLBINX_INXSHIFT	# position index
	mtc0	a0,C0_INX		# drop it in C0 register
	nop
	c0	C0_READI		# read entry to entry hi/lo
	nop
	nop
	nop
	mfc0	v0,C0_TLBLO		# to return value
	mtc0	t1,C0_TLBHI		# restore current pid
	mtc0	t0,C0_SR		# restore sr
	j	ra
	nop
	.set	reorder
	END(get_tlblo)

#if R4000
/*
 * get_tlblo1(index) -- return entry low1 contents of tlb entry "index"
 */
LEAF(get_tlblo1)
	.set	noreorder
	mfc0	t0,C0_SR		# save sr
	mtc0	zero,C0_SR		# disable interrupts
	nop
	mfc0	t1,C0_TLBHI		# save current pid
	sll	a0,TLBINX_INXSHIFT	# position index
	mtc0	a0,C0_INX		# drop it in C0 register
	nop
	c0	C0_READI		# read entry to entry hi/lo
	nop
	nop
	nop
	mfc0	v0,C0_TLBLO_1		# to return value
	mtc0	t1,C0_TLBHI		# restore current pid
	mtc0	t0,C0_SR		# restore sr
	j	ra
	nop
	.set	reorder
	END(get_tlblo)


/*
 * get_pgmaski(index) -- return page mask associated with index
 */
LEAF(get_pgmaski)
	.set	noreorder
	mfc0	t0,C0_SR		# save sr
	mtc0	zero,C0_SR		# disable interrupts
	nop
	mfc0	t1,C0_TLBHI		# save current pid
	sll	a0,TLBINX_INXSHIFT	# position index
	mtc0	a0,C0_INX		# drop it in C0 register
	nop
	c0	C0_READI		# read entry to entry hi/lo
	nop
	nop
	nop
	mfc0	v0,C0_PGMASK
	nop
	mtc0	t1,C0_TLBHI		# restore current pid
	mtc0	t0,C0_SR		# restore sr
	j	ra
	nop
	.set	reorder
	END(get_pgmaski)


/* read TLB page mask register */
LEAF(get_pgmask)
	.set	noreorder
	mfc0	v0,C0_PGMASK
	nop
	j	ra
	nop
	.set	reorder
	END(get_pgmask)

/* write TLB page mask register */
LEAF(set_pgmask)
	.set	noreorder
	mtc0	a0,C0_PGMASK
	j	ra
	nop
	.set	reorder
	END(set_pgmask)
#endif /* R4000 */

/*
 * get_tlbhi(index) -- return entry high contents of tlb entry "index"
 */
LEAF(get_tlbhi)
	.set	noreorder
	mfc0	t0,C0_SR		# save sr
	mtc0	zero,C0_SR		# disable interrupts
	nop
	mfc0	t1,C0_TLBHI		# save current pid
	sll	a0,TLBINX_INXSHIFT	# position index
	mtc0	a0,C0_INX		# drop it in C0 register
	nop
	c0	C0_READI		# read entry to entry hi/lo
	nop
	nop
	nop
	mfc0	v0,C0_TLBHI		# to return value
	mtc0	t1,C0_TLBHI		# restore current pid
	mtc0	t0,C0_SR		# restore sr
	j	ra
	nop
	.set	reorder
	END(get_tlbhi)

/*
 * get_tlbpid() -- return current tlb pid
 */
LEAF(get_tlbpid)
	.set	noreorder
	mfc0	v0,C0_TLBHI		# to return value
	nop
	and	v0,TLBHI_PIDMASK
	srl	v0,TLBHI_PIDSHIFT
	j	ra
	nop
	.set	reorder
	END(get_tlbpid)

/*
 * set_tlbpid() -- set current tlb pid
 */
LEAF(set_tlbpid)
	.set	noreorder
	sll	a0,TLBHI_PIDSHIFT
	and	a0,TLBHI_PIDMASK
	mtc0	a0,C0_TLBHI		# set new pid
	j	ra
	nop
	.set	reorder
	END(set_tlbpid)

/*
 * probe_tlb(address, pid) -- return index for tlb probe of address:pid
 */
LEAF(probe_tlb)
	.set	noreorder
	mfc0	t0,C0_SR		# save sr
	mtc0	zero,C0_SR		# disable interrupts
	nop
	mfc0	t1,C0_TLBHI		# save current pid
	and	a0,TLBHI_VPNMASK	# construct tlbhi for probe
	sll	a1,TLBHI_PIDSHIFT
	and	a1,TLBHI_PIDMASK
	or	a0,a1
	mtc0	a0,C0_TLBHI
	nop
	c0	C0_PROBE		# probe entry to entry hi/lo
	nop
	nop
	mfc0	v0,C0_INX
	nop
	sra	v0,TLBINX_INXSHIFT	# position index
	mtc0	t1,C0_TLBHI		# restore current pid
	mtc0	t0,C0_SR		# restore sr
	j	ra
	nop
	.set	reorder
	END(probe_tlb)

/*
 * invaltlb(i): Invalidate the ith ITLB entry.
 * called whenever a specific TLB entry needs to be invalidated.
 */
LEAF(invaltlb)
	.set	noreorder
	li	t2,K0BASE&TLBHI_VPNMASK
	mfc0	v0,C0_SR		# save SR and disable interrupts
	mtc0	zero,C0_SR
	nop
	mfc0	t0,C0_TLBHI		# save current TLBHI
	mtc0	t2,C0_TLBHI		# invalidate entry
	mtc0	zero,C0_TLBLO
#if R4000
	mtc0	zero,C0_TLBLO_1
#endif /* R4000 */
	sll	a0,TLBINX_INXSHIFT
	mtc0	a0,C0_INX
	nop
	c0	C0_WRITEI
	nop
	mtc0	t0,C0_TLBHI
	mtc0	v0,C0_SR
	j	ra
	nop
	.set	reorder
	END(invaltlb)

/*
 * tlbwired(indx, tlbpid, vaddr, pte, pte2) -- setup wired ITLB entry
 * a0 -- indx -- tlb entry index
 * a1 -- tlbpid -- context number to use (0..TLBHI_NPID-1)
 * a2 -- vaddr -- virtual address (could have offset bits)
 * a3 -- pte -- contents of pte
 *
 * 5th argument (sp+16) -- pte2 -- contents of 2nd pte (R4000 only)
 */
LEAF(tlbwired)
	.set	noreorder
	mfc0	t0,C0_TLBHI		# save current TLBPID
	mfc0	v0,C0_SR		# save SR and disable interrupts
	mtc0	zero,C0_SR
	.set	reorder
#if R4000
	lw	t1,16(sp)		# 5th arg - 2nd pte
#else
	sll	a0,TLBINX_INXSHIFT
	sll	a1,TLBHI_PIDSHIFT	# line up pid bits
#endif
	and	a2,TLBHI_VPNMASK	# chop offset bits
	or	a1,a2			# formatted tlbhi entry
	.set	noreorder
	mtc0	a1,C0_TLBHI		# set VPN and TLBPID
	mtc0	a3,C0_TLBLO		# set PPN and access bits
#if R4000
	mtc0	t1,C0_TLBLO_1		# set PPN and access bits for 2nd pte.
#endif
	mtc0	a0,C0_INX		# set INDEX to wired entry
	nop
	c0	C0_WRITEI		# drop it in
	nop
	mtc0	t0,C0_TLBHI		# restore TLBPID
	mtc0	v0,C0_SR		# restore SR
	j	ra
	nop				# BDSLOT
	.set	reorder
	END(tlbwired)

LEAF(tlbwired_sc)
	.set	noreorder
	mfc0	t0,C0_TLBHI		# save current TLBPID
	mfc0	v0,C0_SR		# save SR and disable interrupts
	mtc0	zero,C0_SR
	.set	reorder
#if R4000
	lw	t1,16(sp)		# 5th arg - 2nd pte
#else
	sll	a0,TLBINX_INXSHIFT
	sll	a1,TLBHI_PIDSHIFT	# line up pid bits
#endif
	and	a2,SC_TLBHI_VPNMASK	# chop offset bits
	or	a1,a2			# formatted tlbhi entry
	.set	noreorder
	mtc0	a1,C0_TLBHI		# set VPN and TLBPID
	mtc0	a3,C0_TLBLO		# set PPN and access bits
#if R4000
	mtc0	t1,C0_TLBLO_1		# set PPN and access bits for 2nd pte.
#endif
	mtc0	a0,C0_INX		# set INDEX to wired entry
	nop
	c0	C0_WRITEI		# drop it in
	nop
	mtc0	t0,C0_TLBHI		# restore TLBPID
	mtc0	v0,C0_SR		# restore SR
	j	ra
	nop				# BDSLOT
	.set	reorder
	END(tlbwired_sc)

#if !R4000
/*
 * tlb_setup(ppn, vpn, index, ncache)
 * Make tlb entry for virtual page vpn mapped to physical page ppn
 * using tlb entry index.  
 */
LEAF(tlb_setup)
	.set	noreorder
	mfc0	v0,C0_SR			# save SR and disable 
	mtc0	zero,C0_SR			# interrupt
	nop
	mfc0	t0,C0_TLBHI			# save current TLBHI
	sll	a2,TLBINX_INXSHIFT
	nop
	mtc0	a2,C0_INX			# set index
	nop
	sll	a0,TLBLO_PFNSHIFT		# move pfn over
	or	a0,TLBLO_D|TLBLO_V|TLBLO_G	# or in D, V, and G bits
	beq	a3,zero,1f			# check if no-cache
	or	a0,TLBLO_N			# set nocache
1:
	mtc0	a0,C0_TLBLO
	sll	a1,TLBHI_VPNSHIFT		# move vpn over
	mtc0	a1,C0_TLBHI
	nop
	c0	C0_WRITEI
	nop
	mtc0	t0,C0_TLBHI
	mtc0	v0,C0_SR			# restore SR
	j	ra
	nop
	.set 	reorder
	END(tlb_setup)
#endif /* !R4000 */
