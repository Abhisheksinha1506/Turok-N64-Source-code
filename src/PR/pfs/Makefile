#!smake -k
#
#

include $(ROOT)/usr/include/make/PRdefs

APP =		pfs

OPTIMIZER =	-g

TARGETS =	rom

TEXHFILES =	textlib.h

HFILES =	$(TEXHFILES) thread.h

CODEFILES   =	main.c nu64sys.c textlib.c asci.c eep_test.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES   =	cfb.c 

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

#LCDEFS =	-DFORMAT -DCREATE  -D_DEBUG
LCDEFS =	-D_DEBUG  
LCINCS =	-I.
LCOPTS =	-fullwarn -wlint,-f -woff 813,819,826,827,852 -non_shared -G 0
LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

LDIRT  =	$(APP)

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/pfs \
			$(HFILES) $(CODEFILES) $(DATAFILES) \
			Makefile spec 

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

rom $(APP):	spec $(OBJECTS) $(MAKEROM)
		$(MAKEROM) -r rom spec



