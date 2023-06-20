#!smake -k
#
# Makefile for Go/No-go cpu/fpu
#

include $(ROOT)/usr/include/make/PRdefs

include ../../gngdefs
include ../locdefs

ASFILES= lfpu.s sfpu.s overflow.s underflow.s fabs.s getfp.s setfp.s \
	dtoa.s dwmultu.s tenscale.s

CFILES= fpregs.c faddsubd.c faddsubs.c fmuldivd.c fmuldivs.c fpmem.c \
	fdivzero.c foverflow.c funderflow.c finexact.c finvalid.c \
	fmulsubs.c fmulsubd.c fptest.c 

HFILES=	fpu.h

TARGET =	fpuseg.o

default:	$(TARGET)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/gng/cpu/fpu \
			$(CFILES) $(ASFILES) $(HFILES) Makefile

fpuseg.o:	$(OBJECTS)
		$(LD) -o $@ -r $(OBJECTS) $(LDFLAGS)

