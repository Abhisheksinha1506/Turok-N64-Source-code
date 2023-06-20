#!smake

include $(ROOT)/usr/include/make/PRdefs

APP =		playseq

OPTIMIZER =	-g

#if defined(DBG_FLAG) && $(DBG_FLAG) == "-D_NON_DEBUG"
    DFLAG = -DNDEBUG
    ULTRALIB = ultra
#else
    DFLAG = -D_DEBUG
    ULTRALIB = ultra_d
#endif

TARGETS =	rom

HFILES =	playseq.h

CODEFILES =	playseq.c
CODEOBJECTS =	$(CODEFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) 

LCINCS =	-I.
LCOPTS =	$(DFLAG) -fullwarn -non_shared -G 0

LDIRT  =	$(APP) $(APP_EM) sequence.aud load.map load_em.map

LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -l$(ULTRALIB)

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/playseq \
			$(HFILES) $(CODEFILES) Makefile spec

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -m -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS) > load.map

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec




