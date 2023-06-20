#!smake -k
#
# Makefile for Go/No-go rsp
#

include $(ROOT)/usr/include/make/PRdefs

include ../gngdefs

CODEFILES = rsp.c
CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES = rspcode rspdiaglist

TARGETS =  $(CODEOBJECTS)

default : $(_FORCE) $(TARGETS) 

install: default
	$(INSTALL) -m 444 -F /usr/src/PR/gng/rsp \
		$(DATAFILES) $(CODEFILES) Makefile

include $(COMMONRULES)
