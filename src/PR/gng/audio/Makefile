#!smake -k
#
# Makefile for Go/No-go audio
#

include $(ROOT)/usr/include/make/PRdefs

include ../gngdefs

H_FILES = audio.h

CODEFILES = audio.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

TARGETS = $(CODEOBJECTS)

LDIRT = audio.o

SUBDIRS = audAssets

default : $(_FORCE) $(TARGETS)
	$(SUBDIRS_MAKERULE)

clobber: $(_FORCE)
	rm -rf $(CODEOBJECTS) Makedepend
	$(SUBDIRS_MAKERULE)

install: default
	$(SUBDIRS_MAKERULE)
	$(INSTALL) -m 444 -F /usr/src/PR/gng/audio \
		$(H_FILES) $(CODEFILES) Makefile

include $(COMMONRULES)

