#!smake -k
#
# Makefile for onetri demo application 
#
#

include $(ROOT)/usr/include/make/PRdefs

PRDEPTH = ../..

APP =		spgame

OPTIMIZER =	-g

TARGETS =	rom

TEXDIR  =	Texture

TEXTURES = 	${TEXDIR}/L2_TV.rgb  \
		${TEXDIR}/ball.rgba

TEXHFILES = 	./${TEXDIR}/lit_imgs.h          ./${TEXDIR}/lit_bms.h \
		./${TEXDIR}/ball_imgs.h         ./${TEXDIR}/ball_bms.h

SPRITES =       ./sp_lit.h ./sp_ball.h

HFILES =	main.h font.h font_ext.h

CODEFILES   =	main.c spgame.c font.c pics.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	static.c cfb.c rsp_cfb.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =
LCINCS =	-I.
LCOPTS =	-fullwarn -wlint,-f -woff 813,819,826,827,852 -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

LDIRT  =	$(APP) $(TEXHFILES) *.so $(SPRITES)

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/spgame \
		    $(HFILES) $(CODEFILES) $(DATAFILES) $(TEXTURES) Makefile spec

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec

spgame.o:	$(TEXHFILES) $(SPRITES)

pics.o:		./sp_lit.h

./sp_lit.h:	${TEXDIR}/L2_TV.rgb
	cd ${TEXDIR}; $(MKSPRITE) lit L2_TV.rgb 64 16 0 > ../sp_lit.h


./${TEXDIR}/lit_imgs.h ./${TEXDIR}/lit_bms.h:	./sp_lit.h


./sp_ball.h:	${TEXDIR}/ball.rgba
	cd ${TEXDIR}; $(MKSPRITE) ball ball.rgba 15 15 1 > ../sp_ball.h


./${TEXDIR}/ball_imgs.h ./${TEXDIR}/ball_bms.h:	./sp_ball.h


# DO NOT DELETE
