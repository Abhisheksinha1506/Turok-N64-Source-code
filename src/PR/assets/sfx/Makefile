#!smake
#
# Makefile for GenMidiSounds
#
include $(ROOT)/usr/include/make/PRdefs

TARGETS= sounds

AIFFFILES =  Airhorn.22k.aiff\
             Grunt.22k.aiff\
             PnchThrw.44k.aiff\
             Select.6k.aiff\
             Skate.22k.aiff\
             SkateStop.11k.aiff\
             Slapshot.11k.aiff\
             Warnhorn.9k.aiff\
             Bodyhit.14k.aiff\
             Dungeon.22k.aiff\
             EngRev.22k.aiff\
             GlassBreak.22k.aiff\
             LionRoar.22k.aiff\
             Thunder.32k.aiff\
             TireSqueal.22k.aiff


AIFCFILES=$(AIFFFILES:.aiff=.aifc)
TABLEFILES=$(AIFFFILES:.aiff=.table)

LDIRT=	$(TABLEFILES) $(AIFCFILES)

default: $(TARGETS)

include $(COMMONRULES)

.SUFFIXES: .aiff .aifc

.aiff.aifc:
	$(TABLEDESIGN) $< > $*.table
	$(VADPCM_ENC) -t -c $*.table $< $@

sounds: $(AIFCFILES)

exports: default
	$(INSTALL) -F /usr/lib/PR/$(TARGETS) $(AIFCFILES)

install: default
	$(INSTALL) -m 444 -F /usr/lib/PR/$(TARGETS) $(AIFCFILES)
	$(INSTALL) -m 444 -F /usr/src/PR/assets/sfx $(AIFFFILES) Makefile
