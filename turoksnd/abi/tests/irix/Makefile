#!smake

include $(ROOT)/usr/include/make/PRdefs

OPTIMIZER = -g

TARGETS=porttest seqtest seqptest monkey

LCOPTS = -woff 613 -mips2 -fullwarn -G 0
LCINCS = -I. -I$(ROOT)/usr/include/PR
LLDLIBS=  -L $(ROOT)/usr/lib -L $(ROOT)/usr/lib/PR -lmidi -laudioem -lm

OPTIMIZER=-g

default: $(TARGETS)

headers exports:

monkey: monkey.o player.o
	$(CCF) monkey.o player.o $(LDFLAGS) -o $@

porttest: porttest.o
	$(CCF) porttest.o $(LDFLAGS) -o $@

seqtest: seqtest.o
	$(CCF) seqtest.o $(LDFLAGS) -o $@

seqptest: seqptest.o
	$(CCF) seqptest.o $(LDFLAGS) -o $@

chaintest: chaintest.o
	$(CCF) chaintest.o $(LDFLAGS) -o $@

install: default

include $(COMMONRULES)
