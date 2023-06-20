#!smake -k
#
# Makefile for Go/No-go cpu/user
#

include $(ROOT)/usr/include/make/PRdefs

include ../../gngdefs
include ../locdefs


ASFILES=	setcause.s syscalls.s
 
CFILES=		user.c

HFILES=		nos.h syscall.h

TARGET =	userseg.o

default:	$(TARGET)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/gng/cpu/user \
			$(CFILES) $(ASFILES) $(HFILES) Makefile

userseg.o:	$(OBJECTS)
		$(LD) -o $@ -r $(OBJECTS) $(LDFLAGS)

