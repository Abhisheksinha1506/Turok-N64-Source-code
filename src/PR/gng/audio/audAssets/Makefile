#!smake -k
#
# Makefile for gonogo audio assets
#

include $(ROOT)/usr/include/make/PRdefs

TARGETS = $(BANKFILES) $(TABLEFILES) $(SEQFILES)

MIDIFILES = gonogo1.mid noteLeft.mid noteRight.mid subway.mid

INSTFILES = gngBank.inst sfx.inst

AIFF_FILES = batu.aiff maru.aiff sinwave22k.aiff triwave22k.aiff

SEQFILES = $(MIDIFILES:.mid=.seq)
BANKFILES=$(INSTFILES:.inst=.ctl)
TABLEFILES=$(INSTFILES:.inst=.tbl)
SYMFILES=$(INSTFILES:.inst=.sym)

LDIRT = gngBank.sym sfx.sym

default: $(TARGETS)

include $(COMMONRULES)

.SUFFIXES: .inst .ctl .tbl .mid .seq

.mid.seq:
	$(MIDICVT) -s $< $*.seq

.inst.ctl:
	$(IC) -o $* $<

.inst.tbl:	# Dummy target for tables
	@echo ''

banks: $(BANKFILES)

install: default
	$(INSTALL) -m 444 -F /usr/src/PR/gng/audio/audAssets \
		$(MIDIFILES) $(INSTFILES) $(AIFF_FILES) Makefile
