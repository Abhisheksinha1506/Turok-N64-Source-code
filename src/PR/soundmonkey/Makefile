#!smake

include $(ROOT)/usr/include/make/PRdefs

APP =		soundmonkey
OPTIMIZER =	-g

TARGETS =	rom

HFILES =	soundmonkey.h

CODEFILES =	soundmonkey.c
CODEOBJECTS =	$(CODEFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) 

LCINCS =	-I. -I$(ROOT)/usr/include/PR
LCOPTS =	-fullwarn -non_shared -G 0

LDIRT  =	$(APP) $(APP_EM) monkey.aud load.map load_em.map

LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR \
		-lultra

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/soundmonkey \
			$(HFILES) $(CODEFILES) Makefile spec

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec





