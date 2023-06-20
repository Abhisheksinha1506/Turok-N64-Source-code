#
# Makefile for application test case 'tron'
#

include $(ROOT)/usr/include/make/PRdefs

APP =		tron
APP_EM =	tron_em

OPTIMIZER =	-g

TARGETS =	rom

HFILES =	tron.h

CODEFILES =	tron.c dram_stack.c dram_yield.c
CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES =	dynamic.c zbuffer.c init.c cfb.c grid.c
DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o
CODESEGMENT_EM = codesegment_em.o

OBJECTS =	$(CODESEGMENT) $(CODEOBJECTS) $(DATAOBJECTS)
OBJECTS_EM =	$(CODESEGMENT_EM) $(DATAOBJECTS)

LCINCS =	-I. -I$(ROOT)/usr/include/PR
LCOPTS =	-fullwarn -non_shared -G 0

LDIRT  =	$(APP) grid.c makegrid

LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR \
			-lultra_d

LDFLAGS_EM =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR \
			-lem -lultra_em

SOURCES =	Makefile spec $(HFILES) $(CODEFILES) \
		dynamic.c zbuffer.c init.c cfb.c makegrid.c

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/tron $(SOURCES)

$(CODESEGMENT_EM): tron_em.o
		$(LD) -o $(CODESEGMENT_EM) -r tron_em.o $(LDFLAGS_EM)

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec

rom_em $(APP_EM): spec_em $(OBJECTS_EM) $(MAKEROM)
		$(MAKEROM) -e -r rom_em spec_em

grid.c:		makegrid
		./makegrid >grid.c

makegrid:	makegrid.c
		$(HOST_CC) -g makegrid.c -o makegrid

tron.o: tron.c
	$(CC) $(CFLAGS) -c $<

tron_em.o: tron.c
	$(CC) $(CFLAGS) -D_EMULATOR -o tron_em.o -c tron.c

