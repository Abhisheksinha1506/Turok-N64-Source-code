#!smake -k
#
# Makefile for Spin demo application 
#
#
#

PRDEPTH = ../../..

include $(PRDEPTH)/PRdefs

include $(COMMONRULES)

install:
		$(INSTALL) -m 444 -F /usr/src/PR/spin/ui *.tcl *.[ch] Makefile
		$(INSTALL) -m 555 -F /usr/src/PR/spin/ui tex blModes0 blModes1
		cd scripts ; make install ; cd ..



