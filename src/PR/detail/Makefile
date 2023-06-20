#!smake -k
#
# Makefile for detail texture demo application 
#
#

include $(ROOT)/usr/include/make/PRdefs

APP =		detail		

OPTIMIZER =	-g

TARGETS =	rom

TEXHFILES =	brick.h

HFILES =	app.h walk_around.h \
		RGBA16field32.h		\
		RGBA16forest32.h 	\
		RGBA16drainage32.h	\
		I8water32.h		\
		RGBA16leaf32.h		\
		RGBA16sand64x32.h	\
		gorge_vtx.h		\
		gorge_dl.h		\
		river_dl.h		\
		vector.h		\
		matrix.h

CODEFILES   =	main.c walk_around.c matrix.c vector.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	static.c cfb.c rsp_cfb.c rsp_czb.c czb.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =
LCINCS =	-I.
LCOPTS =	-fullwarn -wlint,-f -woff 813,819,826,827,852 -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

LDIRT  =	$(APP)

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/detail \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec



