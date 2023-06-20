#!smake -k
#
# Makefile for performance demo application 
#
#

include $(ROOT)/usr/include/make/PRdefs

APP =		autofill

OPTIMIZER =	-g

TARGETS =	rom 

HFILES =	fill.h controller.h static.h timer.h

CODEFILES   =	fill.c static.c tris.c controller.c timer.c rdp_output.c \
				rdp_output_len.c dram_stack.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	zbuffer.c cfb.c cfb_b.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =	$(HW_FLAGS)
LCINCS =	-I. -I$(ROOT)/usr/include/PR
LCOPTS =	-fullwarn -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d 

LDIRT  =	$(APP)  *.ps *.data *.bak

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/$(APP) \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec README

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM) 
		$(MAKEROM) -r rom spec

