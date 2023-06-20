#!smake
include $(ROOT)/usr/include/make/PRdefs

APP =		print

OPTIMIZER =	-g

TARGETS =	rom

HFILES =	print.h

# recompile for real & emulator environments
SPECIFICCODEFILES =	print.c
SCODEOBJECTS =	$(SPECIFICCODEFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT)
DFLAG = -D_DEBUG

LCINCS =	-I. -I$(ROOT)/usr/include/PR 
LCOPTS =	$(DFLAG) -fullwarn -non_shared -G 0
LCDEFS =

LDIRT  =	$(APP) load.map

LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR \
		-lultra

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/print \
			$(HFILES) $(SPECIFICCODEFILES) Makefile spec 

$(CODESEGMENT):	$(CODEOBJECTS) $(SCODEOBJECTS)
		$(LD) -m -o $(CODESEGMENT) -r $(CODEOBJECTS) \
			$(SCODEOBJECTS) $(LDFLAGS) > load.map

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) spec
