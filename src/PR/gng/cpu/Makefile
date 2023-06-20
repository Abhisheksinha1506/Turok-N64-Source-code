#!smake -k
#
# Makefile for Go/No-go cpu
#

include $(ROOT)/usr/include/make/PRdefs

include ../gngdefs
sinclude locdefs

SUBDIRS=	user tlb fpu
COMMONPREF=	cpu

APP =		cpu

TARGETS =	$(CPUSEG)

CFILES =	main.c fault.c sysvec.c

ASFILES=	except2asm.s miscasm.s setjmp.s

HFILES =	cpu.h exceptasm.h osint.h threadasm.h

LDIRT  =	$(APP) rom

XLDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

CPUOBJS =	except2asm.o setjmp.o sysvec.o miscasm.o fault.o main.o

FPUSEG	=	fpu/fpuseg.o

TLBSEG	=	tlb/tlbseg.o

USRSEG	=	user/userseg.o

CPUSEG	=	cpuseg.o

FPU_FILES =	fpu/Makefile \
		fpu/dtoa.s \
		fpu/dwmultu.s \
		fpu/fabs.s \
		fpu/faddsubd.c \
		fpu/faddsubs.c \
		fpu/fdivzero.c \
		fpu/finexact.c \
		fpu/finvalid.c \
		fpu/fmuldivd.c \
		fpu/fmuldivs.c \
		fpu/fmulsubd.c \
		fpu/fmulsubs.c \
		fpu/foverflow.c \
		fpu/fpcmput.c \
		fpu/fpmem.c \
		fpu/fpregs.c \
		fpu/fptest.c \
		fpu/fpu.h \
		fpu/funderflow.c \
		fpu/getfp.s \
		fpu/lfpu.s \
		fpu/lpack.c \
		fpu/lpackd.s \
		fpu/overflow.s \
		fpu/setfp.s \
		fpu/sfpu.s \
		fpu/tenscale.s \
		fpu/underflow.s

TLB_FILES =	tlb/Makefile \
		tlb/buffer.c \
		tlb/tlb.h \
		tlb/tlb0.c \
		tlb/tlb1.c \
		tlb/tlbglobal.c \
		tlb/tlbmem.c \
		tlb/tlbmod.c \
		tlb/tlbnocache.c \
		tlb/tlbpid.c \
		tlb/tlbprobe.c \
		tlb/tlbtest.c \
		tlb/tlbtrans.c \
		tlb/tlbvalid.c \
		tlb/tlbwire.s

USER_FILES =	user/Makefile \
		user/nos.h \
		user/setcause.s \
		user/syscall.h \
		user/syscalls.s \
		user/user.c

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/gng/cpu \
		    $(CFILES) $(ASFILES) $(HFILES) \
		    $(FPU_FILES) $(TLB_FILES) $(USER_FILES) Makefile locdefs

$(CPUSEG):	$(CPUOBJS) subdirs
		$(LD) -o $@ -r $(CPUOBJS) $(TLBSEG) $(FPUSEG) $(LDFLAGS)

subdirs:	
	@for i in $(SUBDIRS) ; do \
		echo ==== make default in $$i ==== ; \
		cd $$i ; \
		$(MAKE) default; \
		cd .. ; \
	done

clean clobber rmtargets:
	rm -rf $(DIRT) $(MKDEPFILE) $(TARGETS)
	@for i in $(SUBDIRS) ; do \
		echo ==== make $@ in $$i ==== ; \
		cd $$i ; \
		$(MAKE) $@; \
		cd .. ; \
	done

except2asm.o:    except2asm.s
		$(AS) $(LASDEFS) $(LASINCS) -non_shared -G 0 -mips3 -32 \
		$(GASFLAGS) -o $@ except2asm.s

setjmp.o:       setjmp.s
		$(AS) $(LASDEFS) $(LASINCS) -non_shared -G 0 -mips3 -32 \
		$(GASFLAGS) -o $@ setjmp.s

