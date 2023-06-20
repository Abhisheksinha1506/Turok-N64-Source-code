#!smake -k
#
# Makefile for game template
#
#

include $(ROOT)/usr/include/make/PRdefs

APP =		game

OPTIMIZER =	-g

TARGETS =	rom

HFILES =	boot.h game.h controller.h font.h font_ext.h \
		I4spec.h static.h teapot_tri.h teapot_vtx.h texture.h

CODEFILES   =	boot.c game.c controller.c font.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	gfxinit.c gfxstatic.c texture.c cfb.c rsp_cfb.c zbuffer.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =	$(HW_FLAGS)
LCINCS =	-I.
LCOPTS =	-fullwarn -wlint,-f -woff 813,819,826,827,852 -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

LDIRT  =	$(APP)

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/texlight \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec

