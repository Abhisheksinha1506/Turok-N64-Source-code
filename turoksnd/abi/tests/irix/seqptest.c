/* sequence player test */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <libaudio.h>

#define MAX_VOICES      16
#define MAX_UPDATES     128
#define EVT_COUNT       32
#define	FRAME_SIZE	736


#define	FX_BUFFER_SIZE	8192
#define AUDIO_HEAP_SIZE 320000

void meminit(char *ptr, int len);

ALGlobals       g;
ALSynConfig     c;
ALSeqpConfig    seqc;
ALSeqPlayer     sequencePlayer;
ALSeq           sequence;
Acmd            cmdList[10*1024];
s16           outBuf[2048];
s16		fxBuf[8192];
u8            audioHeap[AUDIO_HEAP_SIZE];

static char usage[] = "-verbose <filename>";

/* ###
 * ### hack from file virtual.c
 */
#define K0_TO_PHYS(x)   ((unsigned)(x)&0x1FFFFFFF) /* kseg0 to physical */
unsigned int
osVirtualToPhysical(void *virtualAddress)
{
        return(K0_TO_PHYS(virtualAddress));
}

s32    osSetIntMask(s32 i)

{
    return 0;
}

s32 dmaCallBack(s32 addr, s32 len, void *state)
{
    return addr;
}

ALDMAproc dmaNew(void **state)
{
    return dmaCallBack;
}


main(int argc, char **argv)
{
    ALSeqPlayer   *seqp = &sequencePlayer;
    ALSeq    *seq  = &sequence;
    ALHeap      hp;

    s32         ch;
    extern char *optarg;
    extern int  optind;
    int         errflg=0;
    char        *ifile;
    int         verbose;
    int         len;
    char        *ptr;
    FILE        *seqfile;
    int         rv;
    s32         done=0;
    s32         count;
    char        *ofile=0;
    FILE        *cmdfile;
    s32         frameCount=0;
    FILE        *wavefile;
    s32         theTempo = 0;
    char        *wfile = "tst.tbl";
    s32         wavelen;
    char        *waveptr;
    FILE        *bankfile;
    char        *bfile = "tst.bnk";
    s32         banklen;
    char        *bankptr;
    ALBank        *bank=0;
    ALBankFile    *bnkf=0;
    s32         heapSize;
    s32		i;
    
    meminit((char *)&g, sizeof(ALGlobals));
    meminit((char *)&c, sizeof(ALSynConfig));
    meminit((char *)&sequencePlayer, sizeof(sequencePlayer));
    meminit((char *)&sequence, sizeof(sequence));
    meminit((char *)&fxBuf, sizeof(fxBuf));
    
    /*************************************************************
     * parse the command line arguments
     *************************************************************/
    while ((ch = getopt(argc, argv, "vt:o:")) != EOF) {        
        switch (ch) {
	    case 'v':
                verbose = 1;
		break;
            case 'o':
                ofile = optarg;
                break;
            case 't':
                theTempo = atoi(optarg);
                break;
                
            case '?':
                errflg++;
                break;
        }
    }

    if (errflg || optind == argc) {
        (void)fprintf(stderr, "%s %s\n", argv[0], usage);
        exit (2);
    }

    ifile = argv[optind++];
    if (optind != argc) {
	fprintf(stderr, "warning: only first file (%s) used, rest ignored\n",
	   ifile);
    }

    /*************************************************************
     * open the output file
     *************************************************************/
    if (ofile) {
        cmdfile = fopen(ofile, "w");
        if (!cmdfile) {
            printf("Can't open command file\n");
            exit(1);
        }
    }
    
    /*************************************************************
     * load the sequence
     *************************************************************/
    seqfile = fopen(ifile, "r");
    if (!seqfile) {
        printf("Can't open sequence file\n");
        exit(1);
    }
    
    fseek(seqfile, 0, SEEK_END);
    len = ftell(seqfile);
    rewind(seqfile);
    ptr = malloc(len);
    if (!ptr) {
        printf("Can't allocate memory for sequence\n");
        exit(1);
    }

    rv = fread(ptr, sizeof(char), len, seqfile);
    if (rv != len) {
        printf("Can't read sequence file, len = %d\n",len);
        exit(1);
    }

    /*************************************************************
     * load the wavetable
     *************************************************************/
    wavefile = fopen(wfile, "r");
    if (!wavefile) {
        printf("Can't open sound file\n");
        exit(1);
    }
    
    fseek(wavefile, 0, SEEK_END);
    wavelen = ftell(wavefile);
    rewind(wavefile);
    waveptr = malloc(wavelen);
    if (!waveptr) {
        printf("Can't allocate memory for wave table\n");
        exit(1);
    }

    rv = fread(waveptr, sizeof(char), wavelen, wavefile);
    if (rv != wavelen) {
        printf("Can't read sound file, len = %d\n",wavelen);
        exit(1);
    }

    /*************************************************************
     * load the bank
     *************************************************************/
    bankfile = fopen(bfile, "r");
    if (!bankfile) {
        printf("Can't open sound file\n");
        exit(1);
    }
    
    fseek(bankfile, 0, SEEK_END);
    banklen = ftell(bankfile);
    rewind(bankfile);
    bankptr = malloc(banklen);
    if (!bankptr) {
        printf("Can't allocate memory for sound\n");
        exit(1);
    }

    rv = fread(bankptr, sizeof(char), banklen, bankfile);
    if (rv != banklen) {
        printf("Can't read bank file, len = %d\n",banklen);
        exit(1);
    }

    /*************************************************************
     * initialize the Audio Library
     *************************************************************/
    alHeapInit(&hp, audioHeap, AUDIO_HEAP_SIZE);
    c.maxVVoices = MAX_VOICES;
    c.maxPVoices = MAX_VOICES;
    c.maxUpdates = MAX_UPDATES;
    c.dmaproc    = &dmaNew;
    c.heap       = &hp;
    c.outputRate = 44100;
    c.fxType	 = AL_FX_CUSTOM;

    if (c.fxType == AL_FX_CUSTOM) {
	s32	delay_size = 0;
	/*
	 * if you wanted to build an effect, you would specify c.fxType
	 * to be AL_FX_CUSTOM, and then allocate and fill in the effect
	 * parameters. An example follows:
	 */
#define OUTPUT_RATE     44100
#define ms *(((s32) ((f32) OUTPUT_RATE/1000))&~0x7)
#define SECTION_SIZE  8

#define SECTION_COUNT 1

	s32	params[SECTION_COUNT*SECTION_SIZE+2] = {

	    /* sections	   total length */
	    SECTION_COUNT,    100 ms,
                                           /*       chorus  chorus   filter
            input  output  fbcoef  ffcoef   gain     rate   depth     coef      */
	       0,   10 ms, 10000,     0,  0x7fff,     100,   750,      0
	};

	c.params = params;

	/*
	 * since fx params are only needed in alInit, call from here
	 * so stack storage is freed up
	 */

	alInit(&g, &c);
    } else {
	alInit(&g, &c);
    }

    
    seqc.maxVoices      = MAX_VOICES;
    seqc.maxEvents      = EVT_COUNT;
    seqc.maxChannels    = 16;
    seqc.heap           = &hp;

    alSeqpNew(seqp, &seqc);
    
    alSeqNew(seq, ptr, len);    

    alSeqpSetSeq(seqp, seq);

    alBnkfNew((ALBankFile *)bankptr, waveptr);
    bank = ((ALBankFile *)bankptr)->bankArray[0];
    alSeqpSetBank(seqp, bank);

    if (theTempo){
        printf("The default tempo was: %d\n",seqp->uspt);
        alSeqpSetTempo(seqp, theTempo);
    }
    
    alSeqpPlay(seqp);

    while (seqp->state == AL_PLAYING) {
        alAudioFrame(cmdList, &count, outBuf, FRAME_SIZE);
        frameCount++;
        if (ofile)
            fwrite(cmdList, sizeof(Acmd), count, cmdfile);
    }

    printf("total frames = %d\n", frameCount);
    
    alSeqpStop(seqp);
    
    alSeqpStop(seqp);

    alClose(&g);

    if (ofile) {
        fflush(cmdfile);
        fclose(cmdfile);
    }
}

void meminit(char *ptr, int len)
{
    int i;

    for (i = 0; i < len; i++){
        *ptr++ = 0x5a;
    }
}
