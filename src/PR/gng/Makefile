#!smake -J 1
#
# Makefile for go/no-go test program 
#
# For each of the SUBDIRS specified below, run a make in the corresponding
# directory.  The last directory to be made is the 'testDriver' directory, 
# which will gather together all the various scattered object modules into a 
# single gng executable, which will then be converted by makerom into a 
# rom image suitable for download to the development system OR for burning
# into the flash rom cartridge.
#

include $(ROOT)/usr/include/make/PRdefs

SUBDIRS= audio pif rdp rsp uji video pi cpu gng_report testDriver

default clobber: 
	$(SUBDIRS_MAKERULE)

install exports:
	$(SUBDIRS_MAKERULE)
	$(INSTALL) -m 444 -F /usr/src/PR/gng gngdefs Makefile
