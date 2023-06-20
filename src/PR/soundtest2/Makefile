#!smake -k

include $(ROOT)/usr/include/make/PRdefs

APP =		game
OPTIMIZER =	-g

TARGETS =	rom

TEXHFILES =	RGBA16molecule.h RGBA16brick.h

HFILES =	$(TEXHFILES) boot.h game.h controller.h font.h font_ext.h \
		sphere_dl.h sphere_vtx.h letters_img.h static.h texture.h n64audio.h

CODEFILES   =	boot.c game.c controller.c font.c n64audio.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	gfxinit.c gfxstatic.c texture.c cfb.c rsp_cfb.c zbuffer.c 

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =	$(HW_FLAGS)
LCINCS =	-I. -I$(ROOT)/usr/include/PR
LCOPTS =	-Xcpluscomm -fullwarn -wlint,-f -woff 513,813,819,826,827,852 -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR -lultra_d

LDIRT  =	$(APP) $(TEXHFILES)

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/ground \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec
		$(INSTALL) -m 444 -F /usr/src/PR/ground \
			brick.rgb molecule.rgba

gfxstatic.o:	$(TEXHFILES)

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec


RGBA16brick.h: brick.rgb
	$(RGB2C) -F -s 16 -m RGBA16brick brick.rgb > RGBA16brick.h

RGBA16molecule.h: molecule.rgba
	$(RGB2C) -F -s 16 -m RGBA16molecule molecule.rgba > RGBA16molecule.h

texture.o:	molecule.rgba brick.rgb
font.o:		./letters_img.h
