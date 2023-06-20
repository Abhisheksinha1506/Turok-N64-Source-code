#!smake -k
#
# Makefile for u64 dev board inventory program
#
#

include $(ROOT)/usr/include/make/PRdefs

APP =		ginv

OPTIMIZER =	-g

TARGETS =	rom

TEXHFILES =	brick.h

HFILES =	ginv.h

CODEFILES   =	ginv.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) 

LCINCS =	-I.
LCOPTS =	-fullwarn -wlint,-f -woff 813,819,826,827,852 -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

LDIRT  =	$(APP)

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/ginv \
			$(HFILES) $(CODEFILES) Makefile spec

$(CODESEGMENT):	ginv.o
		$(LD) -o $(CODESEGMENT) -r ginv.o $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec



