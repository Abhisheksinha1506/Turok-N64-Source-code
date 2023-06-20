#!smake -k
#
# Makefile for Go/No-go error reporting function "gng_report"
#
include $(ROOT)/usr/include/make/PRdefs

include ../gngdefs

OPTIMIZER =	-g

TEXDIR =	Texture

TEXTURES =	${TEXDIR}/letters.rgb

TEXHFILES =	letters_img.h

CODEFILES =	font.c gng_report.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

OBJECTS =	$(CODEOJBECTS)

LDIRT  =	$(TEXHFILES)

HFILES =	font.h font_ext.h

default:	$(CODEOBJECTS) $(DATAOBJECTS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/gng/gng_report \
			$(HFILES) $(CODEFILES) $(TEXTURES) Makefile

$(OBJECTS): $(HFILES) $(TEXHFILES)

font.o: font.c $(HFILES) $(TEXHFILES)

#
# Header file build rules
#


letters_img.h:	${TEXDIR}/letters.rgb
	cd ${TEXDIR}; $(RGB2C) -F -m letters_img -f I -s 4 letters.rgb > ../letters_img.h
