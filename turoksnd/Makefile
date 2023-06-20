#!smake
#
# Makefile for audio library
#
include $(ROOT)/usr/include/make/PRdefs

TARGETS= $(BANKFILES) $(TABLEFILES)

INSTFILES = testsfx.inst

BANKFILES=$(INSTFILES:.inst=.ctl)
TABLEFILES=$(INSTFILES:.inst=.tbl)
SYMFILES=$(INSTFILES:.inst=.sym)

default: $(TARGETS)

include $(COMMONRULES)

.SUFFIXES: .inst .ctl .tbl

.inst.ctl:
	$(IC) -o $* $<

.inst.tbl:	# Dummy target for tables
	@echo ''

banks: $(BANKFILES)

exports: default
	$(INSTALL) -F /usr/lib/PR/soundbanks $(TARGETS)

install: default
	$(INSTALL) -m 444 -F /usr/lib/PR/soundbanks $(TARGETS) $(SYMFILES)
	$(INSTALL) -m 444 -F /usr/src/PR/assets/banks $(INSTFILES) Makefile


