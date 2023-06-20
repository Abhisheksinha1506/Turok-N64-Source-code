#!smake -k
#
# Makefile for game template
#
#

include $(ROOT)/usr/include/make/PRdefs

APP =		game

OPTIMIZER =	-g

TARGETS =	rom

TEXHFILES =	RGBA16molecule.h RGBA16moleculeMM.h RGBA16moleculeHMM.h\
		RGBA16brick.h RGBA16brickMM.h RGBA16brickHMM.h\
		RGBA16chainlink.h RGBA16chainlinkMM.h RGBA16chainlinkHMM.h\
		RGBA16mymip.h RGBA16mymipMM.h RGBA16mymipHMM.h\
		RGBA16checker.h RGBA16checkerMM.h RGBA16checkerHMM.h

HFILES =	$(TEXHFILES) boot.h game.h controller.h font.h font_ext.h \
		static.h texture.h

CODEFILES   =	boot.c game.c controller.c font.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	gfxinit.c gfxstatic.c texture.c cfb.c rsp_cfb.c zbuffer.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =	$(HW_FLAGS)
LCINCS =	-I.
LCOPTS =	-fullwarn -wlint,-f -woff 813,819,826,827,852 -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

LDIRT  =	$(APP) $(TEXHFILES)

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/mipmap \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec
		$(INSTALL) -m 444 -F /usr/src/PR/mipmap *.rgb *.rgba 

gfxstatic.o:	$(TEXHFILES)

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec


RGBA16molecule.h: molecule.rgba
	$(RGB2C) -r -F -s 16 -m RGBA16molecule molecule.rgba > \
						RGBA16molecule.h

RGBA16moleculeMM.h: molecule.rgba
	$(RGB2C) -r -F -s 16 -m RGBA16moleculeMM -o MIP molecule.rgba > \
						RGBA16moleculeMM.h

RGBA16moleculeHMM.h: molecule[0-9].rgba
	$(RGB2C) -r -F -s 16 -m RGBA16moleculeHMM -o MIPSUPPLIED molecule0.rgba > \
						RGBA16moleculeHMM.h

RGBA16mymip.h: mymip.rgb
	$(RGB2C) -r -F -s 16 -m RGBA16mymip mymip.rgb > \
						RGBA16mymip.h

RGBA16mymipMM.h: mymip.rgb
	$(RGB2C) -r -F -s 16 -m RGBA16mymipMM -o MIP mymip.rgb > \
						RGBA16mymipMM.h

RGBA16mymipHMM.h: mymip[0-9].rgb
	$(RGB2C) -r -F -s 16 -m RGBA16mymipHMM -o MIPSUPPLIED mymip0.rgb > \
						RGBA16mymipHMM.h

RGBA16brick.h: brick.rgb
	$(RGB2C) -r -F -s 16 -m RGBA16brick brick.rgb > \
						RGBA16brick.h

RGBA16brickMM.h: brick.rgb
	$(RGB2C) -r -F -s 16 -m RGBA16brickMM -o MIP brick.rgb > \
						RGBA16brickMM.h

RGBA16brickHMM.h: brick[0-9].rgb
	$(RGB2C) -r -F -s 16 -m RGBA16brickHMM -o MIPSUPPLIED brick0.rgb > \
						RGBA16brickHMM.h

RGBA16chainlink.h: chainlink.rgb
	$(RGB2C) -r -F -s 16 -m RGBA16chainlink chainlink.rgb > \
						RGBA16chainlink.h

RGBA16chainlinkMM.h: chainlink.rgb
	$(RGB2C) -r -F -s 16 -m RGBA16chainlinkMM -o MIP chainlink.rgb > \
						RGBA16chainlinkMM.h

RGBA16chainlinkHMM.h: chainlink[0-9].rgb
	$(RGB2C) -r -F -s 16 -m RGBA16chainlinkHMM -o MIPSUPPLIED chainlink0.rgb > \
						RGBA16chainlinkHMM.h

RGBA16checker.h: checker.rgba
	$(RGB2C) -r -F -s 16 -m RGBA16checker checker.rgba > \
						RGBA16checker.h

RGBA16checkerMM.h: checker.rgba
	$(RGB2C) -r -F -s 16 -m RGBA16checkerMM -o MIP checker.rgba > \
						RGBA16checkerMM.h

RGBA16checkerHMM.h: checker[0-9].rgb
	$(RGB2C) -r -F -s 16 -m RGBA16checkerHMM -o MIPSUPPLIED checker0.rgb > \
						RGBA16checkerHMM.h

texture.o:	molecule*.rgba brick*.rgb checker*.rgb checker.rgba chainlink*.rgb mymip*.rgb

