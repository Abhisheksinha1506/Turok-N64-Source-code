include $(ROOT)/usr/include/make/PRdefs

APP =		cptest

OPTIMIZER =	-g

TARGETS =	rom

HFILES = main.h perf.h
C++FILES = main.c++ libC.c++


#LCINCS =	-I. -I$(ROOT)/usr/include/PR
LC++INCS =	-I. -I$(ROOT)/usr/include/PR
#LCOPTS =	-fullwarn -non_shared -G 0
LC++OPTS =	-fullwarn -non_shared -G 0

LASINCS =	$(LCINCS)
LASOPTS =	-non_shared -G 0

LDIRT  =	$(APP)

LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -lultra_d

default:	$(TARGETS)

include $(COMMONRULES)

install:	default
		$(INSTALL) -m 444 -F /usr/src/PR/cptest $(C++FILES)	\
			$(HFILES) Makefile spec README

codesegment.o:	$(OBJECTS) $(ROOT)/usr/lib/libultra_d.a
		$(LD) -o codesegment.o -r $(OBJECTS) $(LDFLAGS)

rom $(APP):	codesegment.o $(MAKEROM)
		$(MAKEROM) -r rom spec
