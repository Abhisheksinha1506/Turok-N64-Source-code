#!smake -k
#
# Makefile for turbo demo application 
#

include $(ROOT)/usr/include/make/PRdefs

APP =		gtdemo

OPTIMIZER =	-g

TARGETS =	rom

TEXHFILES =	../Texture/RGBA16checkerMM.h

HFILES =	gtdemo.h controller.h turbo.h character.h char_data.h 	\
		timer.h walk.h punch.h

CODEFILES   =	gtdemo.c floor.c turbo.c character.c controller.c 	\
		timer.c walk.c punch.c rdp_output.c rdp_output_len.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	static.c zbuffer.c cfb.c

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

LCDEFS =	
LCINCS =	-I. -I$(ROOT)/usr/include/PR -I $(ROOT)/usr/include
LCOPTS =	-fullwarn -non_shared -G 0

LDIRT  =	$(APP) *.so walktable walktable.h punchtable punchtable.h

#
# Use non debug library just so we have some demos using it to test it
#
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR -lultra

default:	$(TARGETS)

include $(COMMONRULES)

install:        default
		$(INSTALL) -m 444 -F /usr/src/PR/gtdemo \
			README $(HFILES) $(CODEFILES) $(DATAFILES) 	\
			Makefile spec walktable.c punchtable.c

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

#
# These must depend on the generated h-files.
# If we don't do this, smake fails.
#
walk.o:	walktable.h

punch.o:	punchtable.h

static.o: $(TEXHFILES)

$(OBJECTS): $(HFILES) $(TEXHFILES)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec

gtdemo.o: gtdemo.c
	$(CC) $(CFLAGS) -c $< 

#
# Header file build rules
#
walktable:	walktable.c
	cc -o $@ walktable.c

walktable.h:	walktable
	./walktable > walktable.h	

punchtable:	punchtable.c
	cc -o $@ punchtable.c

punchtable.h:	punchtable
	./punchtable > punchtable.h	

