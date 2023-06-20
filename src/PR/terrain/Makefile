#!smake -k
#
# Makefile for game template
#
#

include $(ROOT)/usr/include/make/PRdefs

APP =		game

OPTIMIZER =	-g

TARGETS =	rom terrain 

SCRIPTS =	terrainfile terrainls terrainlsMM terrainlsrgb

TEXHFILES =	

HFILES =	$(TEXHFILES) boot.h controller.h font.h font_ext.h	\
		game.h letters_img.h shared.h static.h

CODEFILES   =	boot.c game.c controller.c font.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	gfxinit.c gfxstatic.c cfb.c rsp_cfb.c zbuffer.c
		

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =	$(HW_FLAGS)
LCINCS =	-I.
LCOPTS =	-fullwarn -wlint,-f -woff 813,819,826,827,852,822 \
		-non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

LDIRT  =	$(APP) $(TEXHFILES)

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/terrain 		\
			$(HFILES) $(CODEFILES) $(DATAFILES) $(SCRIPTS)	\
			terrain.c Makefile spec README

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec

terrain: terrain.c
	$(CC) -o terrain \
		-fullwarn -wlint,-f -woff 813,819,826,827,852,822 \
		-nostdinc -I$(ROOT)/usr/include $(MKDEPOPT) \
		terrain.c -nostdlib -L -L$(ROOT)/usr/lib -lultrahost -lm


font.o:		./letters_img.h
