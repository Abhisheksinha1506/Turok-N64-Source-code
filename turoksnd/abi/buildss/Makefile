#!smake
#
# Makefile for audio library
#

include $(ROOT)/usr/include/make/PRdefs

.PATH: ../

OPTIMIZER = -g

TARGETS=libaudioem.a

LCOPTS = -woff 613 -mips2 -fullwarn -G 0 -DAL_IRIX
LCINCS = -I. -I$(ROOT)/usr/include/PR -I$(ROOT)/usr/include


CFILES  = \
	drvrNew.c \
	load.c \
	auxbus.c \
	bnkf.c \
	env.c \
	event.c \
	filter.c \
	mainbus.c \
	resample.c \
	reverb.c \
	save.c \
	seq.c \
	sl.c \
	heapcheck.c \
	heapinit.c \
	heapalloc.c \
	copy.c \
	seqpdelete.c \
	seqpgetfxmix.c \
	seqpgetpan.c \
	seqpgetprogram.c \
	seqpgetseq.c \
	seqpgettempo.c \
	seqpgetvol.c \
	seqploop.c \
	seqpplay.c  \
	seqpsendmidi.c  \
	seqpsetbank.c  \
	seqpsetfxmix.c  \
	seqpsetpan.c  \
	seqpsetprogram.c \
	seqpsetseq.c  \
	seqpsettempo.c \
	seqpsetvol.c \
	seqpstop.c \
	seqplayer.c \
	sndplayer.c \
	sndpdelete.c \
	sndpallocate.c \
	sndpdeallocate.c \
	sndpsetsound.c \
	sndpplay.c \
	sndpgetsound.c \
	sndpstop.c \
	sndpgetstate.c \
	sndpsetpitch.c \
	sndpsetpriority.c \
	sndpsetvol.c \
	sndpsetpan.c \
	sndpsetfxmix.c \
	synthesizer.c \
	syndelete.c \
	synaddplayer.c \
	synremoveplayer.c \
	synfreevoice.c \
	synallocvoice.c \
	synstopvoice.c \
	synstartvoice.c \
	synstartvoiceparam.c \
	synsetpitch.c \
	synsetvol.c \
	synsetfxmix.c \
	synsetpan.c \
	syngetpriority.c \
	synsetpriority.c \
	synallocfx.c \
	synfreefx.c \
	syngetfxref.c \
	synsetfxparam.c \
	cents2ratio.c

libaudioem.a: $(OBJECTS) Makefile
	$(AR) rc $@ $(OBJECTS)

default: $(TARGETS)

include $(COMMONRULES)

exports: default
	$(INSTALL) -m 444 -F /usr/lib/PR $(TARGETS)

install: default
	$(INSTALL) -m 444 -F /usr/lib/PR $(TARGETS)
