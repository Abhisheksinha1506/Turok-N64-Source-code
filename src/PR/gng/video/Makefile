#!smake -k
#
# Makefile for Go/No-go video test
#

include $(ROOT)/usr/include/make/PRdefs

include ../gngdefs

CODEFILES = vi.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

TARGETS = $(CODEOBJECTS)

LDIRT = vi.o

default : $(_FORCE) $(TARGETS)

include $(COMMONRULES)

install: default
	$(INSTALL) -m 444 -F /usr/src/PR/gng/video \
		$(CODEFILES) Makefile

