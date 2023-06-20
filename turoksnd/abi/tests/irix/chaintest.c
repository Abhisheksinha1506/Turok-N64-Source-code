/*====================================================================
 * chaintest.c
 *
 * Copyright 1993, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/

#include <libaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <em.h>
#include <math.h>

#define MAX_VOICES 32
void    *mixList[MAX_VOICES];


#define AUD_UCODE_POINTER 0x7000
#define AUD_UCODE_SIZE 4095         /* In bytes */

#define AUD_PDATA_POINTER 0x8000
#define AUD_PDATA_SIZE 1536          /* In bytes */

#define ADPCM_TABLE_LOC 48
#define ADPCM_TABLE_SIZE (12*16)

#define AUD_CL_POINTER 48

#define PSCALE 0x8000
#define PI 3.1415926

Acmd *audioInit(Acmd * cmdList)
{
    /* Initialization of segments - anything else to do here? */
    
    aSegment(cmdList++, 0, 0xa000); /* Bitstream in DRAM 0x4000 */
    aSegment(cmdList++, 1, 0x10000); /* Decoded samples in DRAM 0x100000 */
    aSegment(cmdList++, 2, 0x9fe0); /* Use this for ADPCM state */
    aSegment(cmdList++, 3, 0x9fc0); /* Use this for RESAMPLE state */
    aSegment(cmdList++, 4, 0x0);	/* ADPCM table */
    aSegment(cmdList++, 5, 0x9f70); /* env state */
    aSegment(cmdList++, 6, 0x20000); /* outR */
    aSegment(cmdList++, 7, 0x30000); /* auxL */
    aSegment(cmdList++, 8, 0x40000); /* auxR */
    aLoadADPCM(cmdList++, ADPCM_TABLE_SIZE, 4<<26 | ADPCM_TABLE_LOC);
    return cmdList;
}

/* Put these in the global data segment */

ADPCMfilter a0;
ADPCMfilter a1;
Resampler   r0;
Resampler   r1;
EnvMixer    e0;
EnvMixer    e1;
Mixer	    m0;

/* ###
 * ### hack from file virtual.c
 */
#define K0_TO_PHYS(x)   ((unsigned)(x)&0x1FFFFFFF) /* kseg0 to physical */

unsigned int
VirtualToPhysical(void *virtualAddress)
{
        return(K0_TO_PHYS(virtualAddress));
}

main(int argc, char **argv)
{
    Task        tlist;
    Task        *tlistp;

    int         i;
    int         dramout = 0x100000; /* Hacks for testing */
    int         dramin = 0xa000;
    int         w0, w1, clcount;
    int         nsam = 160;
    short       outBuf = 0;
    Acmd        cmdList[4096];
    Acmd        *cmdlp = cmdList;
    short	volL, tgtL, volR, tgtR, pan, wet, dry;
    int		nupL, nupR;
    float	fninput, pitchL, pitchR, deltaL, deltaR;
    int		ninput;
    float	LFOdepthL, LFOdepthR;

    FILE        *outp;
    
    if((outp = fopen(argv[1], "w")) == NULL){
        fprintf(stderr,"Can't open %s\n",argv[1]);
        exit(1);        
    }
    tlistp = &tlist;

    volL = 0x7fff;
    tgtL = 0x3fff;
    nupL = 1000;
    volR = 0x3fff;
    tgtR = 0x7fff;
    nupR = 2000;
    pan = 0x40;
    wet = 0x7fff;
    dry = 0x7fff;
    LFOdepthL = .1;
    LFOdepthR = .2;

    pitchL = 1.0;
    pitchR = .5;

    /*
     * build the chain of processing elements
     */
    adpcmNew(&a0);
    adpcmParam(&a0, FILTER_SET_DMA_CHAIN, &dramin);
    
    resampleNew(&r0);
    resampleParam(&r0, FILTER_SET_SOURCE, &a0);
    r0.ratio = pitchL;
    r0.motion = SL_PLAYING;
    
    envmixerNew(&e0);
    e0.motion = SL_PLAYING;
    
    adpcmNew(&a1);
    adpcmParam(&a1, FILTER_SET_SOURCE, &dramin);
    
    resampleNew(&r1);
    resampleParam(&r1, FILTER_SET_SOURCE, &a1);
    r1.ratio = pitchR;
    r1.motion = SL_PLAYING;

    envmixerNew(&e1);
    e1.motion = SL_PLAYING;
    
    mixerNew(&m0, mixList, sizeof(mixList));
    mixerParam(&m0, SL_MIXER_ADD_SOURCE, &e0);
    mixerParam(&m0, SL_MIXER_ADD_SOURCE, &e1);

    /*
     * construct command lists for these elements
     */
    cmdlp = audioInit(cmdlp);
    for (i = 0; i < 4; i++) {
        outBuf = 0;
        cmdlp = mixerPull(&m0, &outBuf, nsam, 0, cmdlp);
        aSetBuffer(cmdlp++, A_MAIN, 0, MAIN_L_OUT, nsam<<1);
        aSaveBuffer(cmdlp++, 1<<26 | dramout);
	aSetBuffer(cmdlp++, A_MAIN, 0, MAIN_R_OUT, nsam<<1); 
        aSaveBuffer(cmdlp++, 6<<26 | dramout);
	aSetBuffer(cmdlp++, A_MAIN, 0, AUX_L_OUT, nsam<<1); 
        aSaveBuffer(cmdlp++, 7<<26 | dramout);
	aSetBuffer(cmdlp++, A_MAIN, 0, AUX_R_OUT, nsam<<1); 
        aSaveBuffer(cmdlp++, 8<<26 | dramout);
        dramout += (nsam<<1);
    }
    /* Write the stuff out to file - another hack for testing */

    clcount = (int) (cmdlp - cmdList);
    cmdlp = cmdList;
    tlistp->t.dl = AUD_CL_POINTER;
    tlistp->t.len = clcount*8;
    tlistp->t.type = M_AUDTASK | ((AUD_UCODE_SIZE)<<12); 
    tlistp->t.ucode = (unsigned long *) AUD_UCODE_POINTER;
    tlistp->t.ucode_data = (unsigned long *) AUD_PDATA_POINTER;
    tlistp->t.ucode_data_len = AUD_PDATA_SIZE;
    fwrite(tlistp, 1, 48, outp);
    for (i=0; i<clcount; i++){ 
        w0 = cmdlp->words.w0;
        w1 = cmdlp->words.w1;
        fwrite(&w0, 1, 4, outp);
        fwrite(&w1, 1, 4, outp);
        cmdlp++;
    }
    fclose(outp);
    fprintf(stderr,"Command list length: %d\n",clcount);
    
}

