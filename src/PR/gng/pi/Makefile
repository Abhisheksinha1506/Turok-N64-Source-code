#!smake -k
#
# Makefile for Go/No-go pi controller (AD16 bus interface) test
#
include $(ROOT)/usr/include/make/PRdefs

include ../gngdefs

CODEFILES = pi.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

TARGETS = $(CODEOBJECTS) NumberSequence pidata

LDIRT = pi.o

#default : $(_FORCE) $(TARGETS)
default : $(TARGETS)

include $(COMMONRULES)

pidata: pidata.c
	$(CC) -o pidata pidata.c

NumberSequence: pidata
	./pidata

install: default
	$(INSTALL) -m 444 -F /usr/src/PR/gng/pi \
		$(CODEFILES) pidata.c Makefile

