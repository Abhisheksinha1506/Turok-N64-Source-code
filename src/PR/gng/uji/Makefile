#!smake -k
#
# Makefile for Go/No-go Zaru test jig tests
#

include $(ROOT)/usr/include/make/PRdefs

include ../gngdefs

CODEFILES = uji.c uji_pif.c uji_audio.c

HFILES = uji_audio.h uji_pif.h

CODEOBJECTS =	$(CODEFILES:.c=.o)
CODESEGMENT =	ujiCodeSegment.o
TARGETS = $(CODEOBJECTS)

default: $(CODESEGMENT)

include $(COMMONRULES)

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

install: default
	$(INSTALL) -m 444 -F /usr/src/PR/gng/uji \
		$(CODEFILES) $(HFILES) Makefile

