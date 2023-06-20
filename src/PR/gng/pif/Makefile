#!smake -k
#
# Makefile for Go/No-go pif test
#

include $(ROOT)/usr/include/make/PRdefs

include ../gngdefs

H_FILES =	pif.h

CODEFILES =	pif.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

TARGETS =	$(CODEOBJECTS)

LDIRT =		pif.o

# XXXXX Remove when pif.c is fixed
LCOPTS += -g

default : $(_FORCE) $(TARGETS)

install: default
	$(INSTALL) -m 444 -F /usr/src/PR/gng/pif \
		$(H_FILES) $(CODEFILES) Makefile

include $(COMMONRULES)

