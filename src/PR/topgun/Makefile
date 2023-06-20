#!smake -k
#
# Makefile for topgun demo application 
#
#
#
include $(ROOT)/usr/include/make/PRdefs

APP =		topgun

OPTIMIZER =	-g

TARGETS =	rom

TEXHFILES =	ground.h sky.h tree.h
TEXTURES =	Textures/clouds.rgb Textures/harrier_num.rgba \
		Textures/stree1.rgba  Textures/terrain.rgb \
		Textures/camo2.int Textures/decal.inta

MODELS =	Models/av8b.flt

HFILES =	topgun.h

CODEFILES   =	topgun.c dram_stack.c rdp_output.c rdp_output_len.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	av8b.c		\
		cfb.c		\
		ground.c	\
		static.c	\
		zbuffer.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCINCS =	-I. -I$(ROOT)/usr/include/PR -I $(ROOT)/usr/include
LCOPTS =	-fullwarn -non_shared -G 0

LDIRT  =	$(APP) topgun $(TEXHFILES) av8b.c av8b.h

LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR -lultra_d

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/topgun Makefile spec \
			$(HFILES) $(CODEFILES) \
			topgun.c cfb.c ground.c static.c zbuffer.c \
 			$(TEXTURES) $(MODELS)

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec

av8b.c:		Models/av8b.flt Textures/harrier_num.rgba Textures/camo2.int \
			Textures/decal.inta $(FLT2C)
		$(FLT2C) -m av8b -s 10 -C 1 1 1 -L 1.0 0.0 0.0 \
		-r G_RM_AA_ZB_OPA_SURF G_RM_AA_ZB_OPA_DECAL Models/av8b.flt > av8b.c

# This rule has to be here because they need to be created if Makedepend
# doesn't exist:
ground.o:	sky.h ground.h tree.h

sky.h:		Textures/clouds.rgb $(RGB2C)
		$(RGB2C) -m tex_sky -f IA -s 16 Textures/clouds.rgb >sky.h

ground.h:	Textures/terrain.rgb $(RGB2C)
		$(RGB2C) -m tex_ground -f RGBA -l 100,50,0 -h 0,50,0 \
			Textures/terrain.rgb >ground.h

tree.h:		Textures/stree1.rgba $(RGB2C)
		$(RGB2C) -m tex_tree -f IA -s 4 Textures/stree1.rgba >tree.h
