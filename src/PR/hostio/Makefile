#!smake
#
# Makefile for game <> host I/O test application 
#
#

include $(ROOT)/usr/include/make/PRdefs

OPTIMIZER =	-g

TARGETS =	game host

HFILES =	hostio.h

BOOTFILES   =	game.c

BOOTOBJECTS =	$(BOOTFILES:.c=.o)

BOOTSEGMENT =	boot.o

OBJECTS =	$(BOOTSEGMENT)

LCDEFS =
LCINCS =	-I.
LCOPTS =	-fullwarn -wlint,-f -woff 813,819,826,827,852 -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

LDIRT  =	rom

host:		host.c
		$(CC) -o host \
			-fullwarn -wlint,-f -woff 813,819,826,827,852 \
			-nostdinc -I$(ROOT)/usr/include $(MKDEPOPT) \
			host.c -nostdlib -L -L$(ROOT)/usr/lib -lultrahost

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/hostio \
			$(HFILES) game.c host.c Makefile spec


$(BOOTSEGMENT):	$(BOOTOBJECTS)
		$(LD) -o $(BOOTSEGMENT) -r $(BOOTOBJECTS) $(LDFLAGS)

game:		spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec



