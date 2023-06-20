#!smake
#
# Makefile for game reset
#
#

include $(ROOT)/usr/include/make/PRdefs

OPTIMIZER =	-g

TARGETS =	greset

greset: greset.c
	$(CC) -o greset -xansi -fullwarn \
		-nostdinc -I$(ROOT)/usr/include \
		greset.c -nostdlib -L -L$(ROOT)/usr/lib

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/greset greset.c Makefile

