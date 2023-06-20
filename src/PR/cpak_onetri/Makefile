#!smake -k
#
# Makefile for onetri demo application 
#
#

include $(ROOT)/usr/include/make/PRdefs

APP =		onetri

#OPTIMIZER =	-g
OPTIMIZER =	-O2

TARGETS =	rom

TEXHFILES =	brick.h

HFILES =	$(TEXHFILES) onetri.h 

CODEFILES   =	onetri.c dram_stack.c rdp_output.c rdp_output_len.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	static.c cfb.c rsp_cfb.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =
LCINCS =	-I. -I../lib
LCOPTS =	-fullwarn -wlint,-f -woff 813,819,822,826,827,852 -non_shared -G 0 -Xcpluscomm
#LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lnos_jpn -lultra_d
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lnos -lultra_d

LDIRT  =	$(APP)

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/cpak_onetri \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec
