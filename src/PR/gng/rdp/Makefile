#!smake -k
#
# Makefile for Go/No-go rdp display list checksum test
#
include $(ROOT)/usr/include/make/PRdefs

include ../gngdefs

OPTIMIZER =	-g


RDPATT =        ./rdpatt
RDPCOV =        ./rdpcov
RDPTEX =        ./rdptex
RDPMS =         ./rdpms
RDPEW =         ./rdpew
RDPFB =         ./rdpfb
RDP6M =         ./rdp6M
RDP8M =         ./rdp8M

TEXDIR =	Texture
TEXTURES =	$(TEXDIR)/Noise.rgb \
		$(TEXDIR)/Tymes-Elfin.bw \
		$(TEXDIR)/checker.rgb \
		$(TEXDIR)/colorbar.rgb \
		$(TEXDIR)/dana_tiny.rgb \
		$(TEXDIR)/eye.rgb \
		$(TEXDIR)/granite.2.bw \
		$(TEXDIR)/granite.3.bw \
		$(TEXDIR)/grid.rgb \
		$(TEXDIR)/haeberli_fixed.bw \
		$(TEXDIR)/letters.rgb \
		$(TEXDIR)/luna.rgb \
		$(TEXDIR)/mario_1.rgb \
		$(TEXDIR)/mario_2.rgb \
		$(TEXDIR)/mario_32.rgb \
		$(TEXDIR)/phong.rgba

RDPATT_TEXDIR =		$(RDPATT)/Texture
RDPATT_TEXTURES =	$(RDPATT_TEXDIR)/Tymes-Elfin.bw \
			$(RDPATT_TEXDIR)/checker.rgb \
			$(RDPATT_TEXDIR)/dana_tiny.rgb \
			$(RDPATT_TEXDIR)/granite.3.bw \
			$(RDPATT_TEXDIR)/grid.rgb \
			$(RDPATT_TEXDIR)/haeberli_fixed.bw \
			$(RDPATT_TEXDIR)/luna.rgb

RDPATT_TEXHFILES =	$(RDPATT)/I4Tymes-Elfin.h \
			$(RDPATT)/I4granite3.h \
			$(RDPATT)/I4haeberli_fixed.h \
			$(RDPATT)/I4luna.h \
			$(RDPATT)/IA4Tymes-Elfin.h \
			$(RDPATT)/IA4checker.h \
			$(RDPATT)/IA4circle.h \
			$(RDPATT)/IA4haeberli_fixed.h \
			$(RDPATT)/IA4tree2.h \
			$(RDPATT)/RGBA16blue.h \
			$(RDPATT)/RGBA16blue2.h \
			$(RDPATT)/RGBA16dana.h \
			$(RDPATT)/RGBA16green.h \
			$(RDPATT)/RGBA16green2.h \
			$(RDPATT)/RGBA16grid.h \
			$(RDPATT)/RGBA16red.h \
			$(RDPATT)/Tymes-Elfin.h

RDPATT_HFILES =		$(RDPATT)/rdpatt.h

RDPTEX_TEXHFILES =	$(RDPTEX)/CI4circle.h \
			$(RDPTEX)/CI8circle.h \
			$(RDPTEX)/CItest0.h \
			$(RDPTEX)/I4grid.h \
			$(RDPTEX)/I4oddcheck.h \
			$(RDPTEX)/I8crater16MM.h \
			$(RDPTEX)/I8crater32.h \
			$(RDPTEX)/I8grid.h \
			$(RDPTEX)/IA16Noise.h \
			$(RDPTEX)/IA16grid.h \
			$(RDPTEX)/IA4grid.h \
			$(RDPTEX)/IA4tree2.h \
			$(RDPTEX)/IA8grid.h \
			$(RDPTEX)/RGBA16checker.h \
			$(RDPTEX)/RGBA16checkerMM.h \
			$(RDPTEX)/RGBA16dana.h \
			$(RDPTEX)/RGBA16grid.h \
			$(RDPTEX)/RGBA16gridMM.h \
			$(RDPTEX)/RGBA16grid_32.h \
			$(RDPTEX)/RGBA16grid_32mip.h \
			$(RDPTEX)/RGBA16mario.h \
			$(RDPTEX)/RGBA16mario32.h \
			$(RDPTEX)/RGBA16mario_2.h \
			$(RDPTEX)/RGBA16mario_32.h \
			$(RDPTEX)/RGBA16tree.h \
			$(RDPTEX)/RGBA32eye.h \
			$(RDPTEX)/Tlut0.h \
			$(RDPTEX)/Tlut1.h \
			$(RDPTEX)/Tlut2.h \
			$(RDPTEX)/Tlut3.h \
			$(RDPTEX)/YUVbars.h

RDPTEX_HFILES =		$(RDPTEX)/controller.h \
			$(RDPTEX)/rdptex.h \
			$(RDPTEX)/runway_cmds.h \
			$(RDPTEX)/runway_vtx.h \
			$(RDPTEX)/torus_cmds.h \
			$(RDPTEX)/torus_vtx.h

RDPMS_TEXHFILES =	$(RDPMS)/I4spec.h \
			$(RDPMS)/I4specA.h \
			$(RDPMS)/I4specC.h \
			$(RDPMS)/IA8spec.h \
			$(RDPMS)/IA8specA.h \
			$(RDPMS)/RGBA16dana.h \
			$(RDPMS)/RGBA16rainbow.h \
			$(RDPMS)/RGBA16town.h

RDPMS_HFILES =		$(RDPMS)/rdpms.h \
			$(RDPMS)/sphere.dat \
			$(RDPMS)/sphere.dl

#
# rdpcov has no texture header files
#
RDPCOV_HFILES = 	$(RDPCOV)/rdpcov.h


RDPEW_TEXHFILES =	$(RDPEW)/IA16Noise.h

RDPEW_HFILES = 		$(RDPEW)/Qsim_prims.h \
			$(RDPEW)/b25_tri.h \
			$(RDPEW)/b25_vtx.h \
			$(RDPEW)/chair_tri.h \
			$(RDPEW)/chair_vtx.h \
			$(RDPEW)/clip_tri.h \
			$(RDPEW)/clip_vtx.h \
			$(RDPEW)/cow_tri.h \
			$(RDPEW)/cow_vtx.h \
			$(RDPEW)/rdpew.h \
			$(RDPEW)/skull_tri.h \
			$(RDPEW)/skull_vtx.h \
			$(RDPEW)/vw_tri.h \
			$(RDPEW)/vw_vtx.h

RDP6M_TEXHFILES = 	$(RDP6M)/RGBA16grid.h

RDP6M_HFILES = 		$(RDP6M)/rdp6M.h \
			$(RDP6M)/rdp6M_static.c

RDP8M_TEXHFILES = 	$(RDP8M)/IA16Noise.h \
			$(RDP8M)/RGBA16checkerMM.h

RDP8M_HFILES = 		$(RDP8M)/Qsim_prims.h \
			$(RDP8M)/rdp8M.h \
			$(RDP8M)/rdp8M_static.c

RDPFB_HFILES = 		$(RDPFB)/rdpfb.h

RDP_HFILES =		./CSEWCritical_tex.h \
			./I4luna.h \
			./IA4circle.h \
			./IA4tree2.h \
			./IA8phong.h \
			./RGBA16blue.h \
			./RGBA16blue2.h \
			./RGBA16cbar.h \
			./RGBA16checkerMM.h \
			./RGBA16dana.h \
			./RGBA16data.h \
			./RGBA16data_bar.h \
			./RGBA16green.h \
			./RGBA16green2.h \
			./RGBA16longspan.h \
			./RGBA16powersOfTwoMM.h \
			./RGBA16red.h \
			./RGBA16red2.h \
			./RGBA32pattern.h \
			./Tymes-Elfin.h \
			./YUVbars.h \
			./ball_tri.h \
			./ball_vtx.h \
			./bl.h \
			./bl_tex1.h \
			./cc.h \
			./cc_tex.h \
			./checksum.h \
			./cs.h \
			./cs_hardcoded_tris.h \
			./cs_hardcoded_tris2.h \
			./dldriver.h \
			./frac_tri.h \
			./frac_vtx.h \
			./letters_img.h \
			./loadTlut.h \
			./logo_tri.h \
			./logo_vtx.h \
			./map.h \
			./ms.h \
			./spacer.h \
			./spin_torus_tri.h \
			./spin_torus_vtx.h \
			./tc.h \
			./texture.h \
			./tf.h \
			./tf_tex.h \
			./tm.h \
			./toplevel.h \
			./torus_cmds.h \
			./torus_vtx.h \
			./u64_tri.h \
			./u64_vtx.h \
			./lsphere.dat \
			./lsphere.dl \
			./sphere.dat \
			./sphere.dl \
			./ssphere.dat \
			./ssphere.dl

TEXHFILES =		letters_img.h   \
			$(RDPATT_TEXHFILES) \
			$(RDPTEX_TEXHFILES) \
			$(RDPMS_TEXHFILES) \
			$(RDPEW_TEXHFILES) \
			$(RDP6M_TEXHFILES) \
			$(RDP8M_TEXHFILES)

HFILES =		$(RDPATT_HFILES) \
			$(RDPTEX_HFILES) \
			$(RDPMS_HFILES) \
			$(RDPCOV_HFILES) \
			$(RDPEW_HFILES) \
			$(RDP6M_HFILES) \
			$(RDP8M_HFILES) \
			$(RDPFB_HFILES) \
			$(RDP_HFILES)

# These header files are generated by the programs mka5tex, mkrandtex, & cases
#
MKA5TEXFILES =	map_a5.h map_5a.h

MKRANDTEXFILES = map_rand.h map_rand_comp.h map_rand32.h map_cs16_rand.h

CASESFILES =	$(RDPCOV)/rdpcov_case_edge_00.h $(RDPCOV)/rdpcov_case_vertex_00.h \
		$(RDPCOV)/rdpcov_case_skinny_00.h $(RDPCOV)/rdpcov_case_tiny_00.h \
		$(RDPCOV)/rdpcov_case_disc_00.h


GENHFILES = 	$(MKA5TEXFILES) $(MKRANDTEXFILES) $(CASESFILES)

CODEFILES =     dldriver.c toplevel.c \
                cs.c tm.c tc.c tf.c cc.c bl.c ms.c $(RDPATT)/rdpatt.c \
                $(RDPCOV)/rdpcov.c $(RDPTEX)/rdptex.c $(RDPMS)/rdpms.c \
                $(RDPEW)/rdpew.c $(RDPFB)/rdpfb.c $(RDP6M)/rdp6M.c \
		$(RDP8M)/rdp8M.c

CODEOBJECTS =	$(CODEFILES:.c=.o)

DATAFILES =     init.c \
                cs_static.c tm_static.c tc_static.c \
                tf_static.c cc_static.c bl_static.c ms_static.c texture.c \
                $(RDPTEX)/rdptex_static.c $(RDPCOV)/rdpcov_static.c \
                $(RDPATT)/rdpatt_static.c $(RDPMS)/rdpms_static.c \
                $(RDPEW)/rdpew_static.c $(RDPEW)/rdpew_static1.c \
		$(RDPFB)/rdpfb_static.c


DATAOBJECTS =	$(DATAFILES:.c=.o)

OBJECTS =	$(CODEOBJECTS) $(DATAOBJECTS)

UTILITIES =	cases.c mka5tex.c mkrandtex.c

STATIC_SEGMENT =	rdpStaticSegment.o
CODESEGMENT =		rdpCodeSegment.o

LDIRT  =	$(APP) load.map $(GENHFILES) cases mka5tex mkrandtex \
		$(OBJECTS) $(STATIC_SEGMENT) $(CODESEGMENT) \
		$(RDP6M)/rdp6M_static.o $(RDP8M)/rdp8M_static.o

LDFLAGS =	$(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR \
	

default:	$(CODESEGMENT) $(STATIC_SEGMENT)

include $(COMMONRULES)

install: default
	$(INSTALL) -m 444 -F /usr/src/PR/gng/rdp \
	    $(TEXHFILES) $(CODEFILES) $(DATAFILES) $(HFILES) \
	    $(UTILITIES) $(TEXTURES) $(RDPATT_TEXTURES) Makefile

$(OBJECTS): dldriver.h

$(CODESEGMENT):	$(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

$(STATIC_SEGMENT): $(DATAOBJECTS) $(RDP6M)/rdp6M_static.o $(RDP8M)/rdp8M_static.o 
		$(LD) -o $(STATIC_SEGMENT) -r $(DATAOBJECTS)

dldriver.o:	dldriver.c $(GENHFILES) $(TEXHFILES) checksum.h \
		../testDriver/controller.h dldriver.h

rdpvector.o: rdpvector.c
	$(CC) $(CFLAGS) $(LCDEFS) -c $< 

toplevel.o: toplevel.c
	$(CC) $(CFLAGS) $(LCDEFS) -c $< 

cs_static.o: cs_static.c cs.h
	$(CC) $(CFLAGS) $(LCDEFS) -c $< 

tm_static.o: tm_static.c tm.h
	$(CC) $(CFLAGS) $(LCDEFS) -c $< 

tc_static.o: tc_static.c tc.h
	$(CC) $(CFLAGS) $(LCDEFS) -c $< 

tf_static.o: tf_static.c tf.h
	$(CC) $(CFLAGS) $(LCDEFS) -c $< 

cc_static.o: cc_static.c cc.h
	$(CC) $(CFLAGS) $(LCDEFS) -c $< 

bl_static.o: bl_static.c bl.h
	$(CC) $(CFLAGS) $(LCDEFS) -c $< 

ms_static.o: ms_static.c ms.h
	$(CC) $(CFLAGS) $(LCDEFS) -c $< 

$(RDPATT)/rdpatt.o: $(RDPATT)/rdpatt.c $(RDPATT_TEXHFILES) $(RDPATT)/rdpatt.h
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDPATT) -o $(RDPATT)/rdpatt.o -c $<

$(RDPATT)/rdpatt_static.o: $(RDPATT)/rdpatt_static.c $(RDPATT_TEXHFILES) $(RDPATT)/rdpatt.h
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS)  -I$(RDPATT) -o $(RDPATT)/rdpatt_static.o -c $<

$(RDPCOV)/rdpcov.o: $(RDPCOV)/rdpcov.c $(RDPCOV_TEXHFILES) $(RDPCOV)/rdpcov.h 
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDPCOV) -o $(RDPCOV)/rdpcov.o -c $<

$(RDPCOV)/rdpcov_static.o: $(RDPCOV)/rdpcov_static.c $(GENHFILES) $(RDPCOV_TEXHFILES) $(RDPCOV)/rdpcov.h
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDPCOV) -o $(RDPCOV)/rdpcov_static.o -c $<

$(RDPTEX)/rdptex.o: $(RDPTEX)/rdptex.c $(RDPTEX_TEXHFILES) $(RDPTEX)/rdptex.h 
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDPTEX) -o $(RDPTEX)/rdptex.o -c $<

$(RDPTEX)/rdptex_static.o: $(RDPTEX)/rdptex_static.c $(GENHFILES) $(RDPTEX_TEXHFILES) $(RDPTEX)/rdptex.h
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDPTEX) -o $(RDPTEX)/rdptex_static.o -c $<

$(RDPMS)/rdpms.o: $(RDPMS)/rdpms.c $(RDPMS_TEXHFILES) $(RDPMS)/rdpms.h 
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDPMS) -o $(RDPMS)/rdpms.o -c $<

$(RDPMS)/rdpms_static.o: $(RDPMS)/rdpms_static.c $(GENHFILES) $(RDPMS_TEXHFILES) $(RDPMS)/rdpms.h
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDPMS) -o $(RDPMS)/rdpms_static.o -c $<

$(RDPEW)/rdpew.o: $(RDPEW)/rdpew.c $(RDPEW_TEXHFILES) $(RDPEW)/rdpew.h 
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDPEW) -o $(RDPEW)/rdpew.o -c $<

$(RDPEW)/rdpew_static.o: $(RDPEW)/rdpew_static.c $(GENHFILES) $(RDPEW_TEXHFILES) $(RDPEW)/rdpew.h 
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDPEW) -o $(RDPEW)/rdpew_static.o -c $<

$(RDPEW)/rdpew_static1.o: $(RDPEW)/rdpew_static1.c $(GENHFILES) $(RDPEW_TEXHFILES) $(RDPEW)/rdpew.h 
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDPEW) -o $(RDPEW)/rdpew_static1.o -c $<

$(RDPFB)/rdpfb.o: $(RDPFB)/rdpfb.c $(RDPFB_TEXHFILES) $(RDPFB)/rdpfb.h 
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDPFB) -o $(RDPFB)/rdpfb.o -c $<

$(RDPFB)/rdpfb_static.o: $(RDPFB)/rdpfb_static.c $(GENHFILES) $(RDPFB_TEXHFILES) $(RDPFB)/rdpfb.h 
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDPFB) -o $(RDPFB)/rdpfb_static.o -c $<

$(RDP6M)/rdp6M.o: $(RDP6M)/rdp6M.c $(RDP6M_TEXHFILES) $(RDP6M)/rdp6M.h 
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDP6M) -o $(RDP6M)/rdp6M.o -c $<

$(RDP6M)/rdp6M_static.o: $(RDP6M)/rdp6M_static.c $(GENHFILES) $(RDP6M_TEXHFILES) $(RDP6M)/rdp6M.h 
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDP6M) -o $(RDP6M)/rdp6M_static.o -c $<

$(RDP8M)/rdp8M.o: $(RDP8M)/rdp8M.c $(RDP8M_TEXHFILES) $(RDP8M)/rdp8M.h 
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDP8M) -o $(RDP8M)/rdp8M.o -c $<

$(RDP8M)/rdp8M_static.o: $(RDP8M)/rdp8M_static.c $(GENHFILES) $(RDP8M_TEXHFILES) $(RDP8M)/rdp8M.h 
	$(CC) $(CFLAGS) $(LCDEFS) $(LCINCS) -I$(RDP8M) -o $(RDP8M)/rdp8M_static.o -c $<



#
# Header file build rules
#
texture.o: texture.c RGBA16checkerMM.h $(GENHFILES)
	$(CC) $(CFLAGS) $(LCDEFS) -c $<


#
# mka5tex makes both map_a5.h and map_5a.h
#
mka5tex: mka5tex.c
	$(CC) -o mka5tex mka5tex.c

#
# mka5tex makes both map_a5.h and map_5a.h
#
map_a5.h: mka5tex
	./mka5tex

map_5a.h: mka5tex
	./mka5tex

#
# mkrandtex makes map_rand, map_rand_comp.h, map_rand32.h, & map_cs16_rand.h
#
mkrandtex: mkrandtex.c
	$(CC) -o mkrandtex mkrandtex.c

map_rand.h: mkrandtex
	./mkrandtex

map_rand_comp.h: mkrandtex
	./mkrandtex

map_rand32.h: mkrandtex
	./mkrandtex

map_cs16_rand.h: mkrandtex
	./mkrandtex

$(RDPCOV)/rdpcov_case_edge_00.h:	cases
	./cases -w 0
	mv rdpcov_case_edge_00.h $(RDPCOV)

$(RDPCOV)/rdpcov_case_vertex_00.h:	cases
	./cases -w 1
	mv rdpcov_case_vertex_00.h $(RDPCOV)

$(RDPCOV)/rdpcov_case_skinny_00.h:	cases
	./cases -w 2
	mv rdpcov_case_skinny_00.h $(RDPCOV)

$(RDPCOV)/rdpcov_case_tiny_00.h:	cases
	./cases -w 3
	mv rdpcov_case_tiny_00.h $(RDPCOV)

$(RDPCOV)/rdpcov_case_disc_00.h:	cases
	./cases -w 4
	mv rdpcov_case_disc_00.h $(RDPCOV)


#
# The program to build the above include files...
#
cases:	cases.c
	$(CC) -o $@ cases.c -lm
