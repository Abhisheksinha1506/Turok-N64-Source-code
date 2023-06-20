#
#
# Makefile for sequences
#
include $(ROOT)/usr/include/make/PRdefs

TARGETS = $(COLLECTION) $(CMPCOLLECTION)

MIDIFILES = Sweeps.mid \
		Midnight.mid \
		BassDrive.mid \
		TechnoRiff.mid 

COLLECTION = ship.sbk

CMPCOLLECTION = cmpship.sbk

SEQFILES = $(MIDIFILES:.mid=.seq)

CMFFILES = $(MIDIFILES:.mid=.cmf)

LDIRT = $(SEQFILES) $(CMFFILES)

default: $(TARGETS)

include $(COMMONRULES)

.SUFFIXES: .mid .seq .sbk .cmf

.mid.seq:
	$(MIDICVT) -s $< $*.seq

.mid.cmf:
	$(MIDICOMP) $< $*.cmf

$(CMPCOLLECTION): $(CMFFILES)
	$(SBC) -o $(CMPCOLLECTION) $(CMFFILES) 

$(COLLECTION): $(SEQFILES)
	$(SBC) -o $(COLLECTION) $(SEQFILES) 

exports: default
	$(INSTALL) -F /usr/lib/PR/sequences $(SEQFILES) $(COLLECTION) $(CMPCOLLECTION)

install: default
	$(INSTALL) -m 444 -F /usr/lib/PR/sequences $(SEQFILES) $(COLLECTION)
	$(INSTALL) -m 444 -F /usr/src/PR/assets/sequences $(MIDIFILES) Makefile
	$(INSTALL) -m 444 -F /usr/lib/PR/sequences $(CMFFILES) $(CMPCOLLECTION)
