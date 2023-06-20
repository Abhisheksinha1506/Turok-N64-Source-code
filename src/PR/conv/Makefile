#!smake
#
# Makefile for multigen database conversion tools
#

include $(ROOT)/usr/include/make/PRdefs

OPTIMIZER = -g

TARGETS=flt2c rgb2c ppmquant imscale
SCRIPTS= mksprite mkisprite mksprite32 mksprite8 mkspriteyuv mkspriteia

LCOPTS =-fullwarn 
LCINCS =-I. -I$(ROOT)/usr/include/PR

LLDOPTS=-L$(ROOT)/usr/lib/PR
LLDLIBS= -limage -lm

LDIRT  = libppm.a libpgm.a libpbm.a

default: $(TARGETS)

include $(COMMONRULES)

SOURCES=Makefile flt2c.h flt2c.c rgb2c.c readtex.c readtex.h \
	libpbm.h libpgm.h libppm.h pbm.h pbmplus.h pgm.h \
	ppm.h ppmcmap.h version.h \
	ppmquant.c libppm1.c libppm2.c libppm3.c libpgm1.c \
	libpbm1.c libpbm2.c libpbm4.c imscale.c \
	ppmquant.1

flt2c: flt2c.o readtex.o
	$(CCF) flt2c.o readtex.o $(LDFLAGS) -o $@

rgb2c: rgb2c.o readtex.o
	$(CCF) rgb2c.o readtex.o $(LDFLAGS) -o $@

imscale: imscale.o
	$(CCF) imscale.o $(LDFLAGS) -o $@

ppmquant: ppmquant.o libppm.a libpgm.a libpbm.a
	$(CCF) ppmquant.o libppm.a libpgm.a libpbm.a $(LDFLAGS) -o $@

ppmquant.o: ppmquant.c
	$(CCF) -woff 709 -c ppmquant.c

libppm.a: libppm1.o libppm2.o libppm3.o
	$(AR) cru $@ $?

libpgm.a: libpgm1.o
	$(AR) cru $@ $?

libpbm.a: libpbm1.o libpbm2.o libpbm4.o
	$(AR) cru $@ $?

exports: default
	$(INSTALL) -F /usr/sbin $(TARGETS) $(SCRIPTS)

install: default
	$(INSTALL) -F /usr/sbin $(TARGETS) $(SCRIPTS)
	$(INSTALL) -m 444 -F /usr/src/PR/conv $(SOURCES) $(SCRIPTS)
