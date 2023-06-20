#!smake -k
#
# Makefile for Go/No-go cpu/tlb
#

include $(ROOT)/usr/include/make/PRdefs

include ../../gngdefs
include ../locdefs

LASOPTS =       -non_shared -G 0 -DR4000

ASFILES=	tlbwire.s

CFILES= 	tlbglobal.c tlbmem.c tlbmod.c tlbnocache.c tlbpid.c tlbvalid.c \
		tlbprobe.c tlbtrans.c tlbtest.c

HFILES=		tlb.h

TARGET = 	tlbseg.o

default:	$(TARGET)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/gng/cpu/tlb \
			$(CFILES) $(ASFILES) $(HFILES) Makefile

tlbseg.o:	$(OBJECTS) 
		$(LD) -o $@ -r $(OBJECTS) $(LDFLAGS)

