#!smake -k -J 4
#
# Makefile for sprite demo application 
#
#

include $(ROOT)/usr/include/make/PRdefs

APP =		sprite

OPTIMIZER =	-g

TARGETS =	rom 

CODEFILES   =	sprite.c controller.c 
CODEOBJECTS =	$(CODEFILES:.c=.o)

HFILES      =   controller.h dk.h dk7.h sprite.h static.h

DATAFILES   =	static.c cfb.c 

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =
LCINCS =	-I. -I$(ROOT)/usr/include/PR
LCOPTS =	-fullwarn -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

LDIRT  =	$(APP) 

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/spritemonkey \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM) $(BOOTSEGMENT)
		$(MAKEROM) -r rom spec



