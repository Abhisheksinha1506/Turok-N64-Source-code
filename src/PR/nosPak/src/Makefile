#!smake
include $(ROOT)/usr/include/make/PRdefs

SRCFILES =	Makefile canvas.c canvas.s loadfont.s	\
		pakmenu.c pakmenu.h pakmenu.s

default:

install:
	$(INSTALL) -m 444 -F /usr/src/PR/nosPak/src $(SRCFILES)

include $(COMMONRULES)


