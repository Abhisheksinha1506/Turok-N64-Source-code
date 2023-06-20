#
# This demo has the following features
#
#	CPU vertex morphing
#	mipmap texture tiling
#
#	Bill Mark
#

include $(ROOT)/usr/include/make/PRdefs

APP =		morphdemo
APP_EM =	morphdemo_em

#
# instead of -g to do some testing
#
OPTIMIZER =	-O

TARGETS =	rom

HFILES =	morphdemo.h

CODEFILES =     morphdemo.c morph.c makeverts.c dram_stack.c
CODEOBJECTS =	$(CODEFILES:.c=.o)

# recompile for real & emulator environments
SPECIFICCODEFILES =
SCODEOBJECTS =	$(SPECIFICCODEFILES:.c=.o)
SCODEOBJECTS_EM = $(SPECIFICCODEFILES:.c=_em.o)

CODESEGMENT =	codesegment.o
CODESEGMENT_EM =codesegment_em.o

DATAFILES =	static.c dynamic.c zbuf.c cfb.c
DATAOBJECTS =	$(DATAFILES:.c=.o)

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)
OBJECTS_EM =	$(CODESEGMENT_EM) $(DATAOBJECTS)

LCINCS =	-I. -I$(ROOT)/usr/include/PR 
LCOPTS =	-D_DEBUG -fullwarn -non_shared -G 0

LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR \
		-lultra_d
LDFLAGS_EM =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR \
		-lem -lultra_em

LDIRT  =        $(APP) ppm2cTex mariotex.h load.map

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/morphcube \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec \
			ppm2cTex.c \
			mario.ppm

$(CODESEGMENT):	mariotex.h $(CODEOBJECTS) $(SCODEOBJECTS)
		$(LD) -m -o $(CODESEGMENT) -r $(CODEOBJECTS) \
			$(SCODEOBJECTS) $(LDFLAGS) > load.map

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) spec

$(CODESEGMENT_EM):	$(CODEOBJECTS) $(SCODEOBJECTS_EM)
		$(LD) -m -o $(CODESEGMENT_EM) -r $(CODEOBJECTS) \
			$(SCODEOBJECTS_EM) $(LDFLAGS_EM) > load_em.map

rom_em $(APP_EM):	spec_em $(OBJECTS_EM) $(MAKEROM)
		$(MAKEROM) -e -r rom_em spec_em

mariotex.h: ppm2cTex mario.ppm
	./ppm2cTex -m -s < mario.ppm > mariotex.h

ppm2cTex: ppm2cTex.c
	$(CC) -o ppm2cTex ppm2cTex.c

static.o: mariotex.h
