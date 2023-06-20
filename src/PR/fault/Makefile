#
# Makefile for app "fault"
#

include $(ROOT)/usr/include/make/PRdefs

APP =		fault

OPTIMIZER =	-g

TARGETS =	rom


CODE_HFILES =	fault.h

CODE_CFILES =	fault.c printfault.c

CODE_OBJECTS=	$(CODE_CFILES:.c=.o)

LCINCS =	-I. -I$(ROOT)/usr/include/PR
LCOPTS =	-mips2 -fullwarn -non_shared -G 0

LASINCS =	$(LCINCS)
LASOPTS =	-non_shared -G 0

LDIRT  =	$(APP)

LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/fault \
			$(CODE_HFILES) $(CODE_CFILES) Makefile spec


code.o:		$(CODE_OBJECTS) $(ROOT)/usr/lib/libultra.a
		$(LD) -o $@ -r $(CODE_OBJECTS) $(LDFLAGS)

rom $(APP):	spec code.o $(MAKEROM)
		$(MAKEROM) -r rom spec

