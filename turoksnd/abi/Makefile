#!smake
#
# Makefile for audio library subdirectory
#

SUBDIR=audio

COMMONPREF=$(SUBDIR)

PRDEPTH=../..
include $(PRDEPTH)/PRdefs

LIBDEPTH=..
include $(LIBDEPTH)/libdefs

LCOPTS = -mips2 -non_shared -fullwarn -G 0
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
	seqpgetchlvol.c \
	seqpgetpriority.c \
	seqpgetprogram.c \
	seqpgetseq.c \
	seqpgettempo.c \
	seqpgetvol.c \
	seqpgetstate.c \
	seqploop.c \
	seqpplay.c  \
	seqpsendmidi.c  \
	seqpsetbank.c  \
	seqpsetfxmix.c  \
	seqpsetpan.c  \
	seqpsetchlvol.c \
	seqpsetpriority.c \
	seqpsetprogram.c \
	seqpsetseq.c  \
	seqpsettempo.c \
	seqpsetvol.c \
	seqpstop.c \
	seqplayer.c \
	cseq.c \
	cspdelete.c \
	cspgetfxmix.c \
	cspgetpan.c \
	cspgetchlvol.c \
	cspgetpriority.c \
	cspgetprogram.c \
	cspgetseq.c \
	cspgettempo.c \
	cspgetvol.c \
	cspgetstate.c \
	cspplay.c  \
	cspsendmidi.c \
	cspsetbank.c  \
	cspsetfxmix.c  \
	cspsetpan.c  \
	cspsetchlvol.c \
	cspsetpriority.c \
	cspsetprogram.c \
	cspsetseq.c  \
	cspsettempo.c \
	cspsetvol.c \
	cspstop.c \
	csplayer.c \
	sndplayer.c \
	sndpdelete.c \
	sndpallocate.c \
	sndpdeallocate.c \
	sndpsetsound.c \
	sndpplay.c \
	sndpplayat.c \
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

sinclude locdefs

include $(LIBDEPTH)/librules

include $(PRDEPTH)/PRrules

install! default
