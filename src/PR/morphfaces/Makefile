#
# This demo has the following features
#
#	CPU vertex morphing
#       Multi-pass rendering using transparency
#
#	Bill Mark
#

include $(ROOT)/usr/include/make/PRdefs

APP =		morphfaces
APP_EM =	morphfaces_em

#
# instead of -g to do some testing
#
OPTIMIZER =	-O

TARGETS =	rom

HFILES =	morphfaces.h

CODEFILES =     morphfaces.c morph.c data.c dram_stack.c
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

LDIRT  =        $(APP) medit medit2c load.map mstatic.h mcode.h

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/morphfaces \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec \
			ed.ppm tj.ppm ed_tj.v ed_tj.t \
			medit.c medit2c.c aux.h libaux.a

$(CODESEGMENT):	$(CODEOBJECTS) $(SCODEOBJECTS)
		$(LD) -m -o $(CODESEGMENT) -r $(CODEOBJECTS) \
			$(SCODEOBJECTS) $(LDFLAGS) > load.map

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) spec

$(CODESEGMENT_EM):	$(CODEOBJECTS) $(SCODEOBJECTS_EM)
		$(LD) -m -o $(CODESEGMENT_EM) -r $(CODEOBJECTS) \
			$(SCODEOBJECTS_EM) $(LDFLAGS_EM) > load_em.map

rom_em $(APP_EM):	spec_em $(OBJECTS_EM) $(MAKEROM)
		$(MAKEROM) -e -r rom_em spec_em


static.o: static.c ./mstatic.h

morphfaces.o: morphfaces.c morphfaces.h

data.o: ./mcode.h data.c

./mstatic.h: ./mcode.h

# program is not actually dependent on medit, but put it here to force it to
# be kept up to date
# (I've now commented out this dependency because it requires X11 header files
#  which some people don't have)
#
# Note: run medit as follows:
# medit -p ed.ppm -p tj.ppm -v ed_tj.v -t ed_tj.t [-m 6]

#./mcode.h: medit medit2c ed_tj.v ed_tj.t
./mcode.h: medit2c ed_tj.v ed_tj.t
	./medit2c -v ed_tj.v -t ed_tj.t -i ed.ppm -j tj.ppm \
	        -s mstatic.h -c mcode.h -m 16
medit: medit.c
	$(CC) -o medit medit.c libaux.a -lX11 -lGL -lGLU -lm

medit2c: medit2c.c
	$(CC) -o medit2c medit2c.c
