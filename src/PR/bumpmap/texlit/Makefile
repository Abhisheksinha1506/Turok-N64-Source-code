## # # !smake -k
#
# Makefile for onetri demo application 
#
#

include $(ROOT)/usr/include/make/PRdefs

PRDEPTH = ../../..

APP =		texo

OPTIMIZER =	-O

HFILES =	b240_fs.h b240_vs.h bb_faces.h bb_verts.h \
		main.h obj.h vert.h

CODEFILES   =	main.c obj.c obj_desc.c sphd.c texlit.c vert.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

OBJECTS =	$(CODEOBJECTS)

LCDEFS =	$(HW_FLAGS)
LCINCS =	-I.
LCOPTS =	-fullwarn -wlint,-f -woff 813,819,826,827,852 -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

LDIRT  =	$(APP)

default:	$(APP)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/bumpmap/texlit \
		    $(HFILES) $(CODEFILES) Makefile

sphd:	sphd.c
	cc -O -o sphd sphd.c -lgl_s -lm

$(APP):	main.o obj.o texlit.o vert.o obj_desc.o
	$(CC) -o texo main.o obj.o texlit.o vert.o obj_desc.o -lm

obj_dls.h obj_verts.h obj_texs.h:	texo
	./texo
