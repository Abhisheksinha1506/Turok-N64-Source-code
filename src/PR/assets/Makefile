#
# Makefile for libaudio assets directory
#

include $(ROOT)/usr/include/make/PRdefs

#
# there are inter directory dependencies in the order of build. For example,
# sfx generates aifc files that is later needed in building a bank
#

EXPORTS_SUBDIRS= sounds sfx banks sequences
SUBDIRS= sounds sfx banks sequences

COMMONPREF=assets

default install: $(_FORCE)
	$(SUBDIRS_MAKERULE)

exports: $(_FORCE)
	$(EXPORTS_SUBDIRS_MAKERULE)

$(COMMONTARGS): $(_FORCE)
	$(SUBDIRS_MAKERULE)

include $(COMMONRULES)

