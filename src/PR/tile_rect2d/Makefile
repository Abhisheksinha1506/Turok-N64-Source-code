#!smake -k
#
# Makefile for tile_rect demo application 
#
#

include $(ROOT)/usr/include/make/PRdefs

APP =		tile_rect

OPTIMIZER =	-g

TARGETS =	rom

TEXHFILES =	RGBA16cv01.h RGBA16cv02.h RGBA16cv03.h RGBA16cv04.h

HFILES =	$(TEXHFILES) tile_rect.h controller.h

CODEFILES   =	main.c tile_rectangle.c controller.c dram_stack.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	static.c cfb.c rsp_cfb.c

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
		$(INSTALL) -m 444 -F /usr/src/PR/$(APP)2d \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec *.rgb

main.o:	$(TEXHFILES)

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec


RGBA16cv01.h: cv01.rgb
	$(RGB2C) -F -s 16 -m RGBA16cv01 cv01.rgb > RGBA16cv01.h

RGBA16cv02.h: cv02.rgb
	$(RGB2C) -F -s 16 -m RGBA16cv02 cv02.rgb > RGBA16cv02.h

RGBA16cv03.h: cv03.rgb
	$(RGB2C) -F -s 16 -m RGBA16cv03 cv03.rgb > RGBA16cv03.h

RGBA16cv04.h: cv04.rgb
	$(RGB2C) -F -s 16 -m RGBA16cv04 cv04.rgb > RGBA16cv04.h

