#!smake -k
#
# Makefile for performance demo application 
#
#

include $(ROOT)/usr/include/make/PRdefs

APP =		blocks

OPTIMIZER =	-g

TARGETS =	rom 

HFILES =	block.h controller.h static.h subcube.h subplane.h timer.h

CODEFILES   =	block.c static.c subcube.c subplane.c controller.c timer.c rdp_output.c rdp_output_len.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	zbuffer.c cfb.c 

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =	$(HW_FLAGS)
LCINCS =	-I. -I$(ROOT)/usr/include/PR
LCOPTS =	-fullwarn -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d 

LDIRT  =	$(APP) 

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/blockmonkey \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec README

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM) 
		$(MAKEROM) -r rom spec

