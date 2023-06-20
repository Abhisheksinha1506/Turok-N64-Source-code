#!smake -k
#
# Makefile for lines demo application 
#
#

include $(ROOT)/usr/include/make/PRdefs

APP =		lines 

OPTIMIZER =	-g

TARGETS =	rom makesphere

HFILES =	lines.h static.h

CODEFILES   =	lines.c static.c 

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	zbuffer.c cfb.c 

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =
LCINCS =	-I. -I$(ROOT)/usr/include/PR
LCOPTS =	-fullwarn -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

LDIRT  =	$(APP) makesphere sphere.dat sphere.dl

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/polyline \
			$(HFILES) $(CODEFILES) $(DATAFILES) makesphere.c Makefile spec README

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM) 
		$(MAKEROM) -r rom spec

static.c:	sphere.dat sphere.dl

sphere.dat sphere.dl:	makesphere
		./makesphere -t > sphere.dl
		./makesphere > sphere.dat
		touch static.c

makesphere:	makesphere.c
		cc -o makesphere makesphere.c -I /usr/include -L /usr/lib -lm


