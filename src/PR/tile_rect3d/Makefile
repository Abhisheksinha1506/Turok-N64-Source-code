#!smake -k
#
# Makefile for tile_rect demo application 
#
#

include $(ROOT)/usr/include/make/PRdefs


APP =		tile_rect

OPTIMIZER =	-g

TARGETS =	rom

ROADHFILES = rd01.h rd02.h rd03.h rd04.h rd05.h rd06.h
CAFEHFILES = cv01.h cv03.h cv04.h cv05.h cv06.h
WORLDHFILES = world01.h world02.h world03.h world04.h world05.h world06.h

TEXHFILES =	$(ROADHFILES) $(CAFEHFILES) $(WORLDHFILES)

HFILES =	$(TEXHFILES) tile_rect.h controller.h cafe.h road.h world.h

CODEFILES   =	main.c tile_rectangle.c controller.c dram_stack.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	static.c cfb.c rsp_cfb.c cafe.c road.c world.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =	$(HW_FLAGS)
LCINCS =	-I.
LCOPTS =	-fullwarn -wlint,-f -woff 813,819,826,827,852 -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

LDIRT  =	$(APP) $(TEXHFILES)

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/$(APP)3d \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec *.rgb

cafe.o:	$(CAFEHFILES)

road.o:	$(ROADHFILES)

world.o: $(WORLDHFILES)

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec


.SUFFIXES: .rgb .h

.rgb.h:
	$(RGB2C) -F -s 16 -m RGBA16$* $*.rgb > $*.h

