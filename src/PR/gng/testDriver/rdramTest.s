#include "regdef.h"
#include "asm.h"
#include <R4300.h>
#include <rcp.h>
#include "gng.h"

#define MANUFACTURE_NEC 0x00000500
#define MANUFACTURE_TOSHIBA 0x00000200
#define NEC_RELEASE_C2

#ifdef NEC_RELEASE_C2
/* NEC Rev C2 mode enable/disable */
#define RDRAM_DISABLE 0xc0000000
#else
/* Non NEC Rev C2 mode enable/disable */
#define RDRAM_DISABLE 0xc4000000
#endif

/*********************************************************************
 *    Defines.                                                       *
 *********************************************************************/
bulk_rom= 0xa600	#Bulk system ROM start address
cart_rom= 0xb000	#Cartridge ROM start address
#define rd_rams		0x80000000	
#define game_addr	0x8
#ifndef _HW_VERSION_1
#define game_offset	0x1000
#define auto_calibration 0x40
#else
#define game_offset	0x2000
#define auto_calibration 0x10
#endif
#define game_size	0xfffff		/* Real DMA size = game_size - 1 */
#define reserved_mem	0xa0000300

/* 16K of instruction cache and 8K of data cache */
#define icache_size	0x4000		
#define dcache_size	0x2000		
#define icache_linesize         (8*4)
#define dcache_linesize         (4*4)

clear_rsp = SP_SET_HALT|SP_CLR_BROKE|SP_CLR_INTR|SP_CLR_SSTEP|SP_CLR_SIG0|SP_CLR_SIG1|SP_CLR_SIG2|SP_CLR_SIG3|SP_CLR_SIG4|SP_CLR_SIG5|SP_CLR_SIG6|SP_CLR_SIG7|SP_CLR_INTR_BREAK
clear_in_mask  = MI_INTR_MASK_CLR_SP|MI_INTR_MASK_CLR_SI|MI_INTR_MASK_CLR_AI|MI_INTR_MASK_CLR_VI|MI_INTR_MASK_CLR_PI|MI_INTR_MASK_CLR_DP

 #*****register information
 #s3            :bulk or cartridge ROM   (0:cartridge ROM, 1:bulka)
 #              : This data is used in IPL3 or game program.
 #s4		:TV type(1=standard NTSC, 0=standard PAL). This data is used
 #		 in IPL3 or game program.
 #s5		:reset type(1=NMI, 0=cold reset). 
 #		 This data is used in IPL3 or game program.
 #s6		:CIC ID. This data is used in IPL3 or game program.
 #s7		:version. This data is used in IPL3 or game program.


#define AUTOCC        	1
#define MANUALCC      2

LEAF (RDRAM_DIAG)	# Address = 0xA4000000 (top of DMEM)

	#********<14 Initialize RD-RAM>

        .set    noreorder

	/*
	 * Reset the sp from wherever the boot code placed it; 
	 * put it at the top of SP IMEM.
	 */
	li	sp, PHYS_TO_K1(SP_IMEM_END - 15)

	mtc0	zero,C0_CAUSE	# initialize cause register
	mtc0	zero,C0_COUNT	# initialize count register
	mtc0	zero,C0_COMPARE	# initialize compare register

	# Check to see if NMI happen

	la	t0,PHYS_TO_K1(RI_BASE_REG)
	lw	t1,0xc(t0)
	nop
        bnez    t1, nmi
	nop

	# save global registers to stack

	addiu   sp,sp,-24
	sw	s3, 0(sp)
	sw	s4, 4(sp)
	sw	s5, 8(sp)
	sw	s6, 12(sp)
	sw	s7, 16(sp)
	
	# Need to initialize RD-RAM in cold reset case

	la	t0,PHYS_TO_K1(RI_BASE_REG)
	lui	t2, 0xa3f8
	lui	t3, 0xa3f0
	la	t4, PHYS_TO_K1(MI_BASE_REG)
	ori	t1, zero,  auto_calibration
	sw	t1, 0x0004(t0)		# Enable RAC auto-calibration control
        				# Delay 4096 RCP clock cycles.
	li	s1,8000
wait_rac:
	nop
	addi	s1, 0xffff		# s1 = s1 - 1
	bne	s1,zero,wait_rac
	nop
	sw	zero,  0x0008(t0)	# Load current control regs.
	ori	t1, zero,  0x0014
	sw	t1, 0x000c(t0)		# Set transmit and receive selects
	sw	zero,0(t0)		# Reset all RDRAM devices
					# Delay 100 RCP clock cycle
	li	s1,4
wait_rac1:
	nop
	addi	s1, 0xffff              # s1 = s1 - 1
	bne     s1,zero,wait_rac1
	nop
	ori	t1, zero,  0x000e
	sw	t1,0(t0)		# Enable RDRAM access
	ori	t1, zero, 0x010f
	sw	t1, 0x0000(t4)		# Initialize the delay register
	li	t1, 0x18082838
	sw	t1, 0x0008(t2)			
	sw	zero, 0x14(t2)		# Initialize Refrow regs.
	lui	t1, 0x8000
	sw	t1, 4(t2)		# move all RDRAMs to top of address

	# Place all RDRAMs at 2 Mbyte boundaries and determine the size
	# of each RDRAM

	move	t5,zero			# next_device = 0;
	move	t6,zero			# next_id = 0;
	lui	t7,0xa3f0		# next_reg = 0x03f00000;
	move	t8,zero			# next_1_id = 0;
	lui	t9,0xa3f0		# next_1_reg = 0x03f00000;
	lui	s6,0xa000		# next_1_mem = 0;
	move	s7,zero			# next_2_id = 0;
	lui	a2,0xa3f0		# next_2_reg = 0x03f00000;
	lui	a3,0xa000		# next_2_mem = 0;
	move	s2,zero			# multibank = 0;
	lui	s4,0xa000		# pdw_mem = 0;
	
	addiu	sp,sp,-72
	move	fp,sp			# save sp location for next loop

	lw	s0,PHYS_TO_K1(MI_VERSION_REG)
	la	s1,0x01010101
	bne	s0,s1,rcp2
	nop
	li	s0,0x200		# reg_step = 0x00000200;
	ori	s1,t3,0x4000		# reg_max = 0x03f04000
	b 	loop1
	nop
rcp2:
	li	s0,0x400		# reg_step = 0x00000400;
	ori	s1,t3,0x8000		# reg_max = 0x03f08000
loop1:
	# move the next RDRAM to the next 2 MByte slot
	sw	t6,4(s1)		# reg_max + 0x4 = next_id;

	# enable the RDRAM
	addiu	s5,t7, 0xc		# ccreg_address = next_reg+0xc
	jal	InitCCValue
	nop
	
	beqz	v0,done_loop1
	nop
	sw	v0,0(sp)		# cc_value[next_device] = cc

	# determine the RDRAM size

	li	t1,0x2000
	sw	t1,0(t4)		
	lw	t3,0(t7)		
	lui	t0,0xf0ff
	and	t3,t0			
	sw	t3,4(sp)		# device_type[next_device] = 
					# read_data & 0xf0ff0000;
	addi	sp,8
	li	t1,0x1000
	sw	t1,0(t4)

	lui	t0,0xb019
	bne	t3,t0,SM
	nop	
	lui	t0,0x0800
	add	t8,t0			# next_1_id = next_1_id + 0x08000000
	add	t9,s0
	add	t9,s0			# next_1_reg = next_1_reg + (reg_step*2)
	lui	t0,0x0020
	add	s6,t0
	add	s4,t0			# pdw_mem += 2M
	sll	s2,1
	addi	s2,1			# multibank = (multibank << 1) + 1
	b	LM
	nop
SM:
	
	lui	t0,0x0010
	add	s4,t0			# pdw_mem += 1M
LM:
	li	t0,0x2000
	sw	t0,0(t4)		# WriteWord(0x04300000, 0x00002000);
	lw	t1,0x24(t7)		# read devicemanufacturer
	lw	k0,0(t7)		# read devicetype
	li	t0,0x1000
	sw	t0,0(t4)		# WriteWord(0x04300000, 0x00001000);
	andi	t1,0xffff
	li	t0,MANUFACTURE_NEC
	bne	t1,t0,toshiba
	nop
	li	k1,0x01000000
	and	k0,k1
	bnez	k0,toshiba
	nop
	li	t0,0x101c0a04
	sw	t0,0x18(t7)		#WriteWord(next_reg + 0x18, 0x101c0a04)
	b	done_manufacture
toshiba:
	li	t0,0x080c1204
	sw	t0,0x18(t7)		#WriteWord(next_reg + 0x18, 0x080c1204)
	
done_manufacture:
	lui	t0,0x0800
	add	t6,t0			# next_id = next_id + 0x08000000
	add	t7,s0
	add	t7,s0			# next_reg = next_reg + (reg_step * 2)
	addiu	t5,1
	sltiu	t0,t5,8
	bne	t0,zero,loop1 	
	nop
	
done_loop1:

	# Reinitialize all the RDRAMs

	li	t0,RDRAM_DISABLE
	sw	t0,0xc(t2)		# WriteWord(0x03f8000c, RDRAM_DISABLE)
	lui	t0,0x8000
	sw	t0,0x4(t2)		# WriteWord(0x03f80004, 0x80000000)

	# Group the RDRAMs in 1 Mbyte and 2 Mbyte blocks

	move	sp,fp			# restore sp back
	move	v1,zero			# i = 0
loop2:
	lw	t1,4(sp)
	lui	t0,0xb009
	bne	t1,t0,HM
	nop
	
	# Move the RDRAM to the next 1 Mbyte slot
	sw	t8,0x4(s1)		# WriteWord(reg_max + 0x4, next_1_id)

	addiu	s5,t9, 0xc		# ccreg_address = next_1_reg+0xc
	lw	a0,0(sp)		# cc_value[i]
	addi	sp,8
	li	a1, AUTOCC
	jal	WriteCC
	nop
	
	# Tickle the RDRAM

	lw	t0,0(s6)		#ReadWord(next_1_mem+0x00000,&read_data)
	lui	t0,0x8
	add	t0,s6
	lw	t1,0(t0)		#ReadWord(next_1_mem+0x80000,&read_data)
	lw	t0,0(s6)		#ReadWord(next_1_mem+0x00000,&read_data)
	lui	t0,0x8
	add	t0,s6
	lw	t1,0(t0)		#ReadWord(next_1_mem+0x80000,&read_data)

	lui	t0,0x0400
	add	t6,t0			# next_1_id = next_1_id + 0x04000000
	add	t9,s0			# next_1_reg = next_1_reg + reg_step
	lui	t0,0x0010
	add	s6,t0
	b	done_loop2

HM:
	# Move the RDRAM to the next 2 Mbyte slot

	sw	s7,0x4(s1)		# WriteWord(reg_max + 0x4, next_2_id)
	
	addiu	s5,a2, 0xc		# ccreg_address = next_2_reg+0xc
	lw	a0,0(sp)		# cc_value[i]
	addi	sp,8
	li	a1, AUTOCC
	jal	WriteCC
	nop

	# Tickle the RDRAM 

	lw	t0,0(a3)		#ReadWord(next_2_mem+0x00000,&read_data)
	lui	t0,0x08
	add	t0,a3
	lw	t1,0(t0)
	lui	t0,0x10
	add	t0,a3
	lw	t1,0(t0)
	lui	t0,0x18
	add	t0,a3
	lw	t1,0(t0)
	lw	t0,0(a3)		#ReadWord(next_2_mem+0x00000,&read_data)
	lui	t0,0x08
	add	t0,a3
	lw	t1,0(t0)
	lui	t0,0x10
	add	t0,a3
	lw	t1,0(t0)
	lui	t0,0x18
	add	t0,a3
	lw	t1,0(t0)

	lui	t0,0x0800
	add	s7,t0			# next_2_id = next_2_id + 0x08000000
	add	a2,s0
	add	a2,s0			# next_2_reg = next_2_reg+(reg_step * 2)
	lui	t0,0x0020	
	add	a3,t0
done_loop2:
	addiu   v1,1
        slt     t0,v1,t5
        bne     t0,zero,loop2
	nop

	# enable refresh
	
	lui	t2, 0xa470			# Enable refresh
	sll	s2,19				# multibank << 19
	li	t1, 0x63634
	or	t1, s2				# 0x63634 | (multibank << 19)
	sw	t1,  0x0010(t2)
	lw	t1,  0x0010(t2)

	# save osMemSize to reserved area

	li	t0,reserved_mem
	li	t1,0xfffffff
	and	s6,t1
	sw	s6,0x18(t0)	
	
	# restore global registers

	move	sp,fp			# restore sp back
	addiu   sp,sp,72
	lw	s3, 0(sp)
	lw	s4, 4(sp)
	lw	s5, 8(sp)
	lw	s6, 12(sp)
	lw	s7, 16(sp)
	addiu   sp,sp,24
        .set    reorder

	#*******<13 Initialize IPL3>
	# Invalidate I cache

	.set	reorder
        la	t0,K0BASE    	
	addu	t1,t0,ICACHE_SIZE
	subu	t1,ICACHE_LINESIZE

        .set    noreorder
	mtc0	zero,C0_TAGLO
	mtc0	zero,C0_TAGHI
init_icache:
        cache   CACH_PI|C_IST,0(t0) 	#  use index invalidate
        bltu    t0,t1,init_icache       #  on entire cache
        addu    t0,ICACHE_LINESIZE

        la	t0,K0BASE    	
	addu	t1,t0,DCACHE_SIZE
	subu	t1,DCACHE_LINESIZE
	
	# Invalidate D cache

init_dcache:
        cache   CACH_PD|C_IST,0(t0)  #  use index store tag to invalidate
        bltu    t0,t1,init_dcache       #  cache.
	addu	t0,DCACHE_LINESIZE	# some cache data for NMI case

	b 	rdram_diags
	nop

	# We need to write back cache if NMI happen
nmi:
	.set	reorder

        la	t0,K0BASE    	
	addu	t1,t0,ICACHE_SIZE
	subu	t1,ICACHE_LINESIZE

        .set    noreorder
	mtc0	zero,C0_TAGLO
	mtc0	zero,C0_TAGHI
ninit_icache:
        cache   CACH_PI|C_IST,0(t0) 	#  use index invalidate
        bltu    t0,t1,ninit_icache       #  on entire cache
        addu    t0,ICACHE_LINESIZE

        la	t0,K0BASE    	
	addu	t1,t0,DCACHE_SIZE
	subu	t1,DCACHE_LINESIZE

ninit_dcache:
        cache   CACH_PD|C_IWBINV,0(t0)  #  use index writeback invalidate
        bltu    t0,t1,ninit_dcache       #  on entire cache, so we can save
        addu    t0,DCACHE_LINESIZE	#  some cache data for NMI case
        .set    reorder

/*
 * Load IPL3 program segment from IMEM to RD-RAM; first, we run some quick
 * diagnostics on the RDRAM memory and the CPU, then we fall through & continue
 * with the standard boot procedure.
 */

rdram_diags:

/*
 * XXX We really ought to set up exception vectors before enabling NMI from pif.
 *
 * Enable NMI from pif; this has the side effect of preventing the PIF from
 * timing out & pulling down NMI in a constant reset pattern (similar to what
 * the PIF does for a security violation).  Apparently something the boot 
 * process does to the PIF causes it to start a security timeout, which fires 
 * off if we don't enable NMI in a timely manner.  Woof.
 */

        .set reorder
        li      t2, PHYS_TO_K1(SI_STATUS_REG)
wait:
        lw      t3, 0(t2)
        andi    t4, t3, (SI_STATUS_DMA_BUSY | SI_STATUS_RD_BUSY)
        bne     t4, zero, wait

	li	t0, PHYS_TO_K1(PIF_RAM_START)
	lw	t1, 0x3c(t0)	# Read the PIF enable register
	ori	t1, 0x8		# Set the NMI enable bit, then write it back.

        .set noreorder
        .repeat 0x1f
        nop             # Wait a bit, since we just started an SI dma
        .endr
        .set reorder
        li      t2, PHYS_TO_K1(SI_STATUS_REG)
wait2:
        lw      t3, 0(t2)
        andi    t4, t3, (SI_STATUS_DMA_BUSY | SI_STATUS_RD_BUSY)
        bne     t4, zero, wait2

	sw	t1, 0x3c(t0)

/*
 * Test starting at the 2MB boundary, which corresponds to the start of the
 * 2nd rdram.  We test up to the end of the color frame buffer.
 *
 * If we ever experience a readback failure, the address (stored in t0),
 * the expected value (stored in t1), and the readback value (stored in t2)
 * are written to the first three words of ramrom, then the R4300 spins until
 * it's reset.
 */
start_address = 0xa0000400 # Well after reserved_mem, which starts at 0xa0000300

	.set	noreorder
	li	k0,0xa0000400
	lui	k1,0xa440		# Set base pointer for VI registers
	sw	k0,4(k1)		# Set cfb origin to 0xa0000400 
	li	k0,0x00000002
	sw	k0,0xc(k1)		# VI_INTR_REG	<- 2
	sw	zero,0x10(k1)		# VI_CURRENT_REG<- 0

	# set ntsc parameters
	li	k0,0x03e52239		# Set params as per OS_VI_NTSC_HPN1
	sw	k0,0x14(k1)		# VI_BURST_REG	<- 0x03e52239
	li	k0,0x00000c15
	sw	k0,0x1c(k1)		# VI_H_SYNC_REG	<- 0x00000c15
	li	k0,0x0c150c15
	sw	k0,0x20(k1)		# VI_LEAP_REG	<- 0x0c150c15
	li	k0,0x007402f4
	sw	k0,0x24(k1)		# VI_H_START_REG<- 0x007402f4
	li	k0,0x002b0205
	sw	k0,0x28(k1)		# VI_V_START_REG<- 0x002d0207 (???)
	li	k0,0x000e0204
	sw	k0,0x2c(k1)		# VI_V_BURST_REG<- 0x000e0204 (???)
	li	k0,0x00000280
	sw	k0,0x8(k1)		# VI_WIDTH_REG	<- 0x280 (640 pixels)
	li	k0,0x0000020c
	sw	k0,0x18(k1)		# VI_V_SYNC_REG <- 0x20c (halflines/fld)
	li	k0,0x00000400
	sw	k0,0x30(k1)		# VI_X_SCALE_REG<- 0x400
	li	k0,0x00000400
	sw	k0,0x34(k1)		# VI_Y_SCALE_REG<- 0x400
	li	k0,0x0000324e
	sw	k0,0(k1)		# VI_CONTROL_REG<- 0x0000324e

	# write to memory
diags_loop:
	li	k0,start_address
	li	t0,reserved_mem
	lw	k1,0x18(t0)		# k1 gets end address from osMemSize
	or	k1, 0xa0000000		# Use K1 seg addressing
write_loop:
	sw	k0,0(k0)		# write address pattern
	addiu	k0,4
	slt	fp,k0,k1
	bne	fp,zero,write_loop
	nop

/* hal's hack to induce an error for testing the error recovery */

#ifdef HAL_HACK
	li	k0,start_address
	sw	k0,4(k0)		# write address pattern
	sw	k0,8(k0)		# write address pattern
	sw	k0,12(k0)		# write address pattern
#endif

	li	k0,start_address
check_loop:
	lw	t0,0(k0)		# write address pattern
	addiu	t1, k0, 0		# store expected value in t1
	bne	t0,k0,fail
	nop
	addiu	k0,4
	slt	fp,k0,k1
	bne	fp,zero,check_loop
	nop

	li	k0,start_address
	li	t3,0xfffffff
write_loop1:
	xor	t1,k0,t3
	sw	t1,0(k0)		# write address pattern
	addiu	k0,4
	slt	fp,k0,k1
	bne	fp,zero,write_loop1
	nop
	li	k0,start_address
	li	t3,0xfffffff
check_loop1:
	lw	t0,0(k0)		# write address pattern
	xor	t1,k0,t3
	bne	t0,t1,fail		# t1 has expected value
	addiu	k0,4
	slt	fp,k0,k1
	bne	fp,zero,check_loop1
	nop
	/*
	 * Store "0xdeadbeef" to the reserved memory boot diagnostic status 
	 * variable (this value is unlikely to be set by the random powerup
	 * state left over by the ipl3 boot program); then zero out the 
	 * reserved memory word "rdram_diag_errors" to indicate to the gng 
	 * app that the test passed.
	 */
	li	t0, reserved_mem
	li	t1, 0xdeadbeef
	sw	t1, rdram_diag_status_offset(t0)	
	sw	zero, rdram_diag_errors_offset(t0)
	b	load_app		# now load app/os...
	nop

fail:
	/*
	 * Store "0xdeadbeef" to the reserved memory boot diagnostic status 
	 * variable (this value is unlikely to be set by the random powerup
	 * state left over by the ipl3 boot program); then store a '1' to the 
	 * reserved memory word "rdram_diag_errors" to indicate to the gng 
	 * app that the test failed.
	 */
	li	t0, reserved_mem
	li	t1, 0xdeadbeef
	sw	t1, rdram_diag_status_offset(t0)	
	li	t1, 1
	sw	t1, rdram_diag_errors_offset(t0)

	/* 
	 * now fall through and load app/os...
	 */

load_app:

	#*******<17 Load game program to RD-RAM>

 # Send 1M byte game program from cartridge ROM 
 # ($19+game_offset ~ 19+game_offset+0xffffc) to RDRAM (0x80000400 ~ 0x801003fc)
 # We need to reserve the first 1k for exception vector
	
	.set	reorder
	lui	t3,cart_rom		#set source address of cartridge ROM
	beq	s3,zero,cart		#if (s3 == 0) goto cart
	lui	t3,bulk_rom		#set source address of bulk sys. ROM
cart:
	li	t2,0x1fffffff
	lw	t1,game_addr(t3)
	and	t1,t2					# game's boot address
	sw	t1,PHYS_TO_K1(PI_DRAM_ADDR_REG)
waitread:
	lw	t0,PHYS_TO_K1(PI_STATUS_REG)
	andi	t0,PI_STATUS_IO_BUSY
	bnez	t0,waitread

	la	t0,game_offset		# get rom address of the game
	add	t0,t3
	and	t0,t2
	sw	t0,PHYS_TO_K1(PI_CART_ADDR_REG)

	la	t2,game_size			# DMA size
	sw	t2,PHYS_TO_K1(PI_WR_LEN_REG)	# start DMA

	# wait for DMA to finish
	
waitdma:
        .set noreorder
        .repeat 0x20
        nop
        .endr
        .set reorder
	lw	t3,PHYS_TO_K1(PI_STATUS_REG)
	andi	t3,PI_STATUS_DMA_BUSY
	bnez	t3,waitdma

 #*******<19 Handle RSP possible halt in delay slot

	# Force nop instruction  into IMEM at (pc-4) location
	lw	t1,PHYS_TO_K1(SP_PC_REG)	# get pc
	beq	t1, zero,skip
	li	t2,SP_SET_SSTEP|SP_CLR_HALT	# force to single step
	sw	t2,PHYS_TO_K1(SP_STATUS_REG)
	sw	zero,PHYS_TO_K1(SP_PC_REG)	# set pc to zero
	# TODO Clear RSP status register 
skip:
	li	t3,clear_rsp
	sw	t3,PHYS_TO_K1(SP_STATUS_REG)
	# Clear interrupt mask

	li	t0,clear_in_mask	
	sw	t0,PHYS_TO_K1(MI_INTR_MASK_REG)

	# SP, PI and VI interrupts have been cleared. 
	# Now, clear the rest of interrupts
	sw	zero,PHYS_TO_K1(SI_STATUS_REG)	# clear SI interrupt
	sw	zero,PHYS_TO_K1(AI_STATUS_REG)	# clear AI interrupt
	li	t1,MI_CLR_DP_INTR		
	sw	t1,PHYS_TO_K1(MI_MODE_REG)	# clear DP interrupt
        li      t1, PI_STATUS_CLR_INTR
        sw      t1, PHYS_TO_K1(PI_STATUS_REG)	# clear PI interrupt

	# save reserved registers to RDRAM
	li	t0,reserved_mem
	sw	s4,0(t0)			# save osTvType
	sw	s3,4(t0)			# save osRomType
	sw	s5,0xc(t0)			# save osResetType
	sw	s6,0x10(t0)			# save osCicId
	sw	s7,0x14(t0)			# save osVersion
	beq     s3,zero,rom
        la      t1,PHYS_TO_K1(PI_DOM1_ADDR1)
        b       1f
rom:
        la      t1,PHYS_TO_K1(PI_DOM1_ADDR2)
1:
	sw	t1,8(t0)			# save osRomBase
	
 #********<21 Jump to game program in RD-RAM>
	lui	t3,cart_rom		#set source address of cartridge ROM
	beq	s3,zero,game		#if (s3 == 0) goto cart
	lui	t3,bulk_rom		#set source address of bulk sys. ROM
game:
	lw	t1,game_addr(t3)
	jr	t1
END(RDRAM_DIAG)


#define DERWMASK              0x02000000
#define ASRWMASK              0x04000000
#define X2RWMASK              0x40000000
#define CERWMASK              0x80000000
#define C0RMASK               0x00000040
#define C1RMASK               0x00004000
#define C2RMASK               0x00400000
#define C3RMASK               0x00000080
#define C4RMASK               0x00008000
#define C5RMASK               0x00800000
#define C0WMASK               0x00000001
#define C1WMASK               0x00000002
#define C2WMASK               0x00000004
#define C3WMASK               0x00000008
#define C4WMASK               0x00000010
#define C5WMASK               0x00000020
#define C0SHIFT               6
#define C1SHIFT               13
#define C2SHIFT               20
#define C3SHIFT               4
#define C4SHIFT               11
#define C5SHIFT               18

#define PASSES		4
#define SHIFPASSES	2
#define MAXTRYS       10
#define CHECKSHIFT    16
#define CCMASK        0x3f

#define MULT  22
#define MFAC  10
#define NTRY  10
#define BITS   8
#define TRYBITS (NTRY*BITS)


LEAF(InitCCValue)
	addiu	sp,sp,-160
	
	# save all the registers
	sw	v0,0(sp)
	sw	v1,4(sp)
	sw	a0,8(sp)
	sw	a1,12(sp)
	sw	a2,16(sp)
	sw	a3,20(sp)
	sw	t0,24(sp)
	sw	t1,28(sp)
	sw	t2,32(sp)
	sw	t3,36(sp)
	sw	t4,40(sp)
	sw	t5,44(sp)
	sw	t6,48(sp)
	sw	t7,52(sp)
	sw	t8,56(sp)
	sw	t9,60(sp)
	sw	s0,64(sp)
	sw	s1,68(sp)
	sw	s2,72(sp)
	sw	s3,76(sp)
	sw	s4,80(sp)
	sw	s5,84(sp)
	sw	s6,88(sp)
	sw	s7,92(sp)
	sw	fp,96(sp)
	sw	ra,100(sp)

	move	s0,zero			# i
	move	s1,zero			# sumccv
CCloop1:
	jal	FindCC
	addiu	s0,1
	addu	s1,v0
	slti	t1,s0,PASSES
	bne	t1,zero,CCloop1
	srl	a0,s1,SHIFPASSES
	li	a1, AUTOCC

	jal	WriteCC
	srl	v0,s1,SHIFPASSES	# return accv

	#restore all the registers
	
	lw	v1,4(sp)
	lw	a0,8(sp)
	lw	a1,12(sp)
	lw	a2,16(sp)
	lw	a3,20(sp)
	lw	t0,24(sp)
	lw	t1,28(sp)
	lw	t2,32(sp)
	lw	t3,36(sp)
	lw	t4,40(sp)
	lw	t5,44(sp)
	lw	t6,48(sp)
	lw	t7,52(sp)
	lw	t8,56(sp)
	lw	t9,60(sp)
	lw	s0,64(sp)
	lw	s1,68(sp)
	lw	s2,72(sp)
	lw	s3,76(sp)
	lw	s4,80(sp)
	lw	s5,84(sp)
	lw	s6,88(sp)
	lw	s7,92(sp)
	lw	fp,96(sp)
	lw	ra,100(sp)
	addiu   sp,sp,160
	jr	ra

END (InitCCValue)

LEAF(FindCC)
	addiu	sp,sp,-32
	sw	ra,28(sp)
	move	t1,zero			#i_prepass
	move	t3,zero			#i_sumv
	move	t4,zero			#j
	
prepass_loop:
	slti	k0,t4,64
	beq	k0,zero,done_findcc	#j > 63

	move	a0,t4
	jal	TestCCValue

	blez	v0,next_pass		#i_pass < 0
	subu	k0,v0,t1		# i_pass-i_prevpass
	multu	k0,t4			# j*(i_pass-i_prevpass)
	mflo	k0
	addu	t3,k0			# i_sumv += j*(i_pass-i_prevpass)
	move	t1,v0			# i_prevpass = i_pass
next_pass:
	addiu	t4,1			# j++
	slti    k0,t1,TRYBITS		#i_prevpass < TRYBITS
	bne     k0,zero,prepass_loop

	sll	a0,t3,2			#i_sumv * 4
	subu	a0,t3			#i_sumv * 3
	sll	a0,2			#i_sumv * 12
	subu	a0,t3			#i_sumv * 11
	sll	a0,1			#i_sumv * 22
	addiu	a0,-880			#MULT*(i_sumv - (TRYBITS/2))
	jal	ConvertManualToAuto
	b 	return_findcc
	
done_findcc:
	move	v0,zero			# no memory
return_findcc:
	lw	ra,28(sp)
	addiu	sp,sp,32
	jr	ra
END(FindCC)

LEAF(TestCCValue)
	addiu	sp,sp,-40
	sw	ra,28(sp)
	move	v0,zero			# i_passcount
	li	a1,MANUALCC
	jal	WriteCC

	move	fp,zero			# j=0
jloop:
	li	k0,-1
	sw	k0,0(s4)		# dgWriteWord(pdw_mem, 0xffffffff);
	sw	k0,0(s4)		# dgWriteWord(pdw_mem, 0xffffffff);
	sw	k0,4(s4)	#dgWriteWord(pdw_mem+mgi_readoffset, 0xffffffff)
	lw	v1,4(s4)	#dgReadWord(pdw_mem+mgi_readoffset, &dw_value)
	srl	v1,CHECKSHIFT		# dw_value = (dw_value >>CHECKSHIFT)

	move	gp,zero			# k = 0
kloop:
	andi	k0,v1,1			# dw_value&0x00000001
	beq	k0,zero,no_passcount
	addiu	v0,1			#i_passcount++
no_passcount:
	srl	v1,1			# dw_value>>1
	addiu	gp,1			# k++
	slti	k0,gp,BITS
	bne	k0,zero,kloop

	addiu	fp,1			# j++
	slti	k0,fp,NTRY		# j < NTRY
	bne	k0,zero,jloop

	lw	ra,28(sp)
	addiu	sp,sp,40
	jr	ra
END(TestCCValue)

LEAF(ConvertManualToAuto)
	addiu	sp,sp,-40
	sw	ra,28(sp)
	sw	a0,32(sp)
	move 	t0,zero			# i_readccval = 0
	move	t2,zero			# i_minccval = 0
	li	t5,64*MFAC*TRYBITS	# i_delccval = 64*MFAC*TRYBITS
	sb	zero,39(sp)		# b_readccval = 0
	move	t6,zero			# i_accval = 0
big_loop:
	slti	k0,t6,64
	bne	k0,zero,coverloop	# i_accval < 64
	move	v0,zero			# return (0)
	b	convert_done
coverloop:
	move	a0,t6
	li	a1,AUTOCC
	jal	WriteCC
	
/*
* Now read back the calibrated value. The read of this register is
* done 2 times and the last value is the one that is used.
* A "dummy" transaction is required (for NEC Rev D parts) for the
* calibrated current control value to be loaded for a read.
*/

/* The first ReadCC below is a dummy transaction read: the results of
   the read are not used. In the assembly code, optimize for this case
*/
	addiu	a0,sp,39
	jal 	ReadCC
	addiu	a0,sp,39
	jal 	ReadCC

	lbu	k0,39(sp)		# b_readccval
	li	k1,MFAC*TRYBITS		
	multu	k0,k1			# (MFAC*TRYBITS)*b_readccval
	mflo	t0			#i_readccval=(MFAC*TRYBITS)*b_readccval
	lw      a0,32(sp)		# i_ccvalue
	subu	k0,t0,a0		# i_readccval-i_ccvalue
	bgez	k0,pos			# i_dccv = abs(i_readccval-i_ccvalue)
	subu	k0,a0,t0
pos:
	slt	k1,k0,t5		# i_dccv < i_delccval
	beq	k1,zero,compare_done
	move	t5,k0			# i_delccval = i_dccv
	move	t2,t6			# i_minccval = i_accval
compare_done:
	lw      a0,32(sp)		# i_ccvalue
	slt	k1,t0,a0
	beq	k1,zero,return_value	# i_readccval>=i_ccvalue
	addiu	t6,1			# i_accval++
	slti	k1,t6,65		# i_accval < 65
	bne	k1,zero,big_loop
return_value:
	addu	v0,t2,t6		# i_minccval+i_accval
	srl	v0,1			# (i_minccval+i_accval)/2

convert_done:
	lw	ra,28(sp)
	addiu	sp,sp,40
	jr	ra
END(ConvertManualToAuto)

LEAF(WriteCC)
	addiu	sp,sp,-40
	sw	ra,28(sp)

#ifdef NEC_RELEASE_C2
	li	t7,DERWMASK|X2RWMASK	# dw_value = (DERWMASK|X2RWMASK)
#else
	li	t7,DERWMASK|X2RWMASK|ASRWMASK	
#endif
	andi	a0,0xff
	xori	a0,CCMASK		# b_value ^= (CCMASK)
	li	k1,AUTOCC
	bne	a1,k1,non_auto		# b_auto != AUTOCC
	li	k0,CERWMASK
	or	t7,k0			# dw_value |= CERWMASK
non_auto:
	andi	k0,a0,C0WMASK		#b_value&C0WMASK
	sll	k0,C0SHIFT		# (b_value&C0WMASK)<<C0SHIFT
	or	t7,k0			# dw_value |=(b_value&C0WMASK)<<C0SHIFT
	andi	k0,a0,C1WMASK		#b_value&C1WMASK
	sll	k0,C1SHIFT		# (b_value&C1WMASK)<<C1SHIFT
	or	t7,k0			# dw_value |=(b_value&C1WMASK)<<C1SHIFT
	andi	k0,a0,C2WMASK		#b_value&C2WMASK
	sll	k0,C2SHIFT		# (b_value&C2WMASK)<<C2SHIFT
	or	t7,k0			# dw_value |=(b_value&C2WMASK)<<C2SHIFT
	andi	k0,a0,C3WMASK		#b_value&C3WMASK
	sll	k0,C3SHIFT		# (b_value&C3WMASK)<<C3SHIFT
	or	t7,k0			# dw_value |=(b_value&C3WMASK)<<C3SHIFT
	andi	k0,a0,C4WMASK		#b_value&C4WMASK
	sll	k0,C4SHIFT		# (b_value&C4WMASK)<<C4SHIFT
	or	t7,k0			# dw_value |=(b_value&C4WMASK)<<C4SHIFT
	andi	k0,a0,C5WMASK		#b_value&C5WMASK
	sll	k0,C5SHIFT		# (b_value&C5WMASK)<<C5SHIFT
	or	t7,k0			# dw_value |=(b_value&C5WMASK)<<C5SHIFT
	
	sw	t7,0(s5)		# dgWriteWord(ccreg_address, dw_value)

/*
 * In auto-mode, introduce a delay of 512 (Rambus bus) clocks to ensure
 * that the auto current control circuitry calibrates to the new value
 * Code this as a simple delay loop that delays for about 2048ns.
*/
	li	k1,AUTOCC
	bne	a1,k1,write_done
	lui	k0,0xa430		# 
	sw	zero,0(k0)		# dgWriteWord(0x04300000, 0x00000000)
	
write_done:
	lw	ra,28(sp)
	addiu	sp,sp,40
	jr	ra
END(WriteCC)

LEAF(ReadCC)
	addiu	sp,sp,-40
	sw	ra,28(sp)

	move	fp,zero			# dw_value = 0
	li	k0,0x2000
	lui	k1,0xa430
	sw	k0,0(k1)		# dgWriteWord(0x04300000, 0x00002000)
	lw	fp,0(s5)		# dgReadWord(ccreg_address, &dw_value)
	li      k0,0x1000
	sw      k0,0(k1)		# dgWriteWord(0x04300000, 0x00001000)

	move	k0,zero			# dw_tmp = 0

	li	k1,C0RMASK
	and	k1,fp			# dw_value&C0RMASK
	srl	k1,C0SHIFT		# (dw_value&C0RMASK)>>C0SHIFT
	or	k0,k1			# dw_tmp |= (dw_value&C0RMASK)>>C0SHIFT
	li	k1,C1RMASK
	and	k1,fp			# dw_value&C1RMASK
	srl	k1,C1SHIFT		# (dw_value&C1RMASK)>>C1SHIFT
	or	k0,k1			# dw_tmp |= (dw_value&C1RMASK)>>C1SHIFT
	li	k1,C2RMASK
	and	k1,fp			# dw_value&C2RMASK
	srl	k1,C2SHIFT		# (dw_value&C2RMASK)>>C2SHIFT
	or	k0,k1			# dw_tmp |= (dw_value&C2RMASK)>>C2SHIFT
	li	k1,C3RMASK
	and	k1,fp			# dw_value&C3RMASK
	srl	k1,C3SHIFT		# (dw_value&C3RMASK)>>C3SHIFT
	or	k0,k1			# dw_tmp |= (dw_value&C3RMASK)>>C3SHIFT
	li	k1,C4RMASK
	and	k1,fp			# dw_value&C4RMASK
	srl	k1,C4SHIFT		# (dw_value&C4RMASK)>>C4SHIFT
	or	k0,k1			# dw_tmp |= (dw_value&C4RMASK)>>C4SHIFT
	li	k1,C5RMASK
	and	k1,fp			# dw_value&C5RMASK
	srl	k1,C5SHIFT		# (dw_value&C5RMASK)>>C5SHIFT
	or	k0,k1			# dw_tmp |= (dw_value&C5RMASK)>>C5SHIFT
	
	sb	k0,0(a0)		# *b_value = (unsigned char) dw_tmp

	lw	ra,28(sp)
	addiu	sp,sp,40
	jr	ra
END(ReadCC)
