#!smake -k
#
# Makefile for overlay demo application 
#
#

include $(ROOT)/usr/include/make/PRdefs

OPTIMIZER =	-g

TARGETS =	rom

TEXHFILES =	brick.h

HFILES =	$(TEXHFILES) overlay.h

KERNCFILES   =	overlay.c dram_stack.c

KERNOBJECTS =	$(KERNCFILES:.c=.o)

SEGCFILES   =	plain.c texture.c cfb.c rsp_cfb.c

OBJECTS =	$(SEGCFILES:.c=.o) kernel.o

LCDEFS =
LCINCS =	-I.
LCOPTS =	-fullwarn -wlint,-f -woff 813,819,826,827,852 -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

LDIRT  =	plain texture

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/overlay \
			$(HFILES) $(KERNCFILES) $(SEGCFILES) Makefile spec

#
# Note the use of the "-u" flag to force inclusion of the given routines
# into the kernel segment, although they are not referenced by any other
# code in the kernel segment.  They are, however, referenced by the
# "plain" and "texture" segments and thus these routines are included in
# the kernel segment.
#

kernel.o:	$(KERNOBJECTS) Makefile
		$(LD) -o $@ -r $(KERNOBJECTS) \
			-u __assert -u osWritebackDCache \
			-u guOrtho -u guRotate \
			$(LDFLAGS)

rom:		spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec
