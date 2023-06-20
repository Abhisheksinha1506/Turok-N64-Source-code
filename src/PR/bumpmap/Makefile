#!smake -k
#
# Makefile for bumpmap demo application 
#
#

include $(ROOT)/usr/include/make/PRdefs

.NOTPARALLEL:

APP =		bumpmap

OPTIMIZER =	-g

TARGETS =	rom

OBJHFILES =	./obj_dls.h ./obj_texs.h ./obj_verts.h

TEXHFILES =	obj_real.h

HFILES =	$(TEXHFILES) $(OBJHFILES) bumpmap.h

CODEFILES   =	bumpmap.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	static.c cfb.c rsp_cfb.c zbuf.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =
LCINCS =	-I.
LCOPTS =	-fullwarn -wlint,-f -woff 813,819,826,827,852 -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

LDIRT  =	$(APP) $(OBJHFILES)

default:	$(TARGETS)

SUBDIRS =	texlit

install:	default
	(cd texlit; make install)
	$(INSTALL) -m 444 -F /usr/src/PR/bumpmap \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec

#
# use $(COMMONRULES) conventions to descend into subdirectories
# for common targets:
#
COMMONPREF =	bumpmap

include $(COMMONRULES)

$(COMMONTARGS) : $(COMMONPREF)$$@
	$(SUBDIRS_MAKERULE)


$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec

static.c:	$(OBJHFILES)

$(OBJHFILES):
	(cd texlit; make obj_texs.h )
	cp texlit/obj_*.h .


