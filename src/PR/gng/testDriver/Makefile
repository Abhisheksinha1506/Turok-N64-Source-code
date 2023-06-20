#!smake -k
#
# Makefile for Go/No-go diagnostic 
#
include $(ROOT)/usr/include/make/PRdefs

include ../gngdefs

APP =		gng

OPTIMIZER =	-g

TARGETS =	rom rdramTest

HFILES =	controller.h gng.h

RDRAMTEST_LASOPTS=-Wab,-mips3 -Wab,-diag -non_shared -coff -G 0
RDRAMTEST_LDFLAGS =-allow_jump_at_eop -coff -N -T A4000000 -G 0

#
# main.c MUST be first, so that the boot() function is the first function in
#        the module.
#
CODEFILES =	main.c controller.c sys_misc.c testDriver.c zaru.c
CODEOBJECTS =	$(CODEFILES:.c=.o) int1.o

OTHEROBJS = 	../audio/audio.o \
		../gng_report/gng_report.o \
		../gng_report/font.o \
		../pi/pi.o \
		../pif/pif.o \
		../rdp/rdpCodeSegment.o \
		../rsp/rsp.o \
		../cpu/cpuseg.o \
		../uji/ujiCodeSegment.o \
		../video/vi.o

CODESEGMENT =   testDriverCodeSegment.o

DATAFILES =	cfb.c
DATAOBJECTS =	$(DATAFILES:.c=.o) rdp/rdpStaticSegment.o

BOOTFILES =     boot.c
BOOTOBJECTS =   $(BOOTFILES:.c=.o)
BOOTSEGMENT =   bootsegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS) rdramTest.o

LASINCS =	-I$(ROOT)/usr/include/PR -I$(ROOT)/usr/include
LDIRT  =	$(APP) boot load.map rdramTest2c rdramTest_data.c \
		rdramTest_data.h

HFILES =	controller.h gng.h testDriver.h zaru.h

UTILITIES = rdramTest2c.c rdramTest.s boot.c int1.s

LCOPTS += -woff 835

LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR \
		-l$(ULTRALIB)

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/gng/testDriver \
		    $(HFILES) $(CODEFILES) $(DATAFILES) $(UTILITIES) \
		    spec Makefile

$(CODESEGMENT):	$(CODEOBJECTS) $(OTHEROBJS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) \
		    $(OTHEROBJS) $(LDFLAGS)

$(BOOTSEGMENT): $(BOOTOBJECTS)
		$(LD) -m -o $(BOOTSEGMENT) -r $(BOOTOBJECTS) $(LDFLAGS) > load.map

$(OBJECTS): $(HFILES)

rdramTest.o: rdramTest.s
	$(AS) $(RDRAMTEST_LASOPTS) $(LASINCS) rdramTest.s -o rdramTest.o

rdramTest:	rdramTest.o Makefile
	$(LD) $(RDRAMTEST_LDFLAGS) rdramTest.o -o rdramTest
	$(SIZE) -x rdramTest | grep "Size of rdramTest"

rdramTest_data.h:	rdramTest rdramTest2c
	./rdramTest2c rdramTest > rdramTest_data.h

rdramTest2c:	rdramTest2c.c
	cc -O -L $(ROOT)/usr/lib rdramTest2c.c -o $@ -lmld

boot.o: rdramTest_data.h

rom $(APP):	spec $(OBJECTS) $(MAKEROM) $(BOOTSEGMENT) ../rsp/rspcode
		$(MAKEROM) $(MAKEROMDEFS) spec

