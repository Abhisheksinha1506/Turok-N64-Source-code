#!smake -k
#
# Makefile for chrome effect demo application 
#
#
#

include $(ROOT)/usr/include/make/PRdefs

APP =		letters

OPTIMIZER =	-g

TARGETS =	rom

TEXTURES =	./Texture/metallic.rgb ./Texture/mahogany.rgb ./Texture/smroad.rgb ./Texture/gameday.rgb

TEXHFILES =	./mahogany.h ./metallic.h ./smroad.h ./sp_gameday.h

HFILES =	letters.h u64_tri.h u64_vtx.h

CODEFILES   =	letters.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	static.c	\
		zbuffer.c	\
		cfb.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(TEXHFILES) $(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =
LCINCS =	-I.
LCOPTS =	-fullwarn -non_shared -G 0

LDIRT  =	$(APP) $(TEXHFILES) *.so ./Texture/gameday*.h

LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR -lultra_d

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/chrome \
			$(HFILES) $(CODEFILES) $(DATAFILES) Makefile spec \
			$(TEXTURES)


$(CODESEGMENT):	$(TEXHFILES) $(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

#
# This must depend on the generated h-files.
# If we don't do this, smake fails.
#
static.o: $(TEXHFILES)

$(OBJECTS): $(HFILES)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec

letters.o: letters.c letters.h ./sp_gameday.h
	$(CC) $(CFLAGS) -c $< 

#
# Header file build rules
#

./mahogany.h: Texture/mahogany.rgb $(RGB2C)
	$(RGB2C) -m mahogany -f RGBA Texture/mahogany.rgb > mahogany.h

./metallic.h: Texture/metallic.rgb $(RGB2C)
	$(RGB2C) -m tex_metallic -f RGBA Texture/metallic.rgb > metallic.h

./smroad.h: Texture/smroad.rgb $(RGB2C)
	$(RGB2C) -m tex_smroad -f RGBA Texture/smroad.rgb > smroad.h

./sp_gameday.h:     Texture/gameday.rgb
	cd Texture; $(MKSPRITE) gameday gameday.rgb 64 16 0 > ./sp_gameday.h; mv ./sp_gameday.h ../



