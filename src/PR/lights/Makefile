#!smake -k
#
# Makefile for teapot demo application 
#
#
#

include $(ROOT)/usr/include/make/PRdefs

APP =		teapot

OPTIMIZER =	-g

TARGETS =	rom

TEXHFILES =	teapot_shad64.h

HFILES =	I4spec.h controller.h teapot_tri.h \
		IA8phong.h teapot.h teapot_vtx.h


CODEFILES   =	teapot.c controller.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	static.c	\
		zbuffer.c	\
		cfb.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =	-DUSE_HIGHLIGHT -DUSE_MIPMAP
LCINCS =	-I. -I$(ROOT)/usr/include/PR -I $(ROOT)/usr/include
LCOPTS =	-fullwarn -non_shared -G 0

LDIRT  =	$(APP) teapot $(TEXHFILES) *.so

#
# Use non debug library just so we have some demos using it to test it
#
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR -lultra

default:	$(TARGETS)

include $(COMMONRULES)

install:        default
		$(INSTALL) -m 444 -F /usr/src/PR/lights \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec \
			Texture/teapot_shad64.rgb

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

#
# This must depend on the generated h-files.
# If we don't do this, smake fails.
#
teapot.o: $(TEXHFILES)

$(OBJECTS): $(HFILES) $(TEXHFILES)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec

teapot.o: teapot.c
	$(CC) $(CFLAGS) -c $< 

#
# Header file build rules
#

teapot_shad64.h: Texture/teapot_shad64.rgb
	$(RGB2C) -s 4 -m teapot_shadow -f I Texture/teapot_shad64.rgb > teapot_shad64.h

