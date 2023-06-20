/* sequence player test */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <libaudio.h>
#include "player.h"

#define MAX_PVOICES     16
#define MAX_UPDATES     16
#define MAX_DMA_BUFFERS 4
#define EVT_COUNT       32
#define	FRAME_SIZE	160

#define	REVERB_DELAY_LENGTH	2048
#define AUDIO_HEAP_SIZE (32767 + 2*REVERB_DELAY_LENGTH)

void meminit(char *ptr, int len);

ALGlobals       g;
ALSynConfig     c;
MyPlayer        myPlayer;
MyPlayerConfig  pc;
Acmd            cmdList[10*1024];
short           outBuf[2048];
ALSound         sound;
short		fxBuf[8192];
char            audioHeap[AUDIO_HEAP_SIZE];

ALEventListItem   evtList[EVT_COUNT];
ALVoiceState      voiceList[MAX_VOICES];

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

int dmaCallBack(int addr, int len)
{
    return addr;
}

main(int argc, char **argv)
{
    MyPlayer   *p = &myPlayer;
    int         ch;
    extern char *optarg;
    extern int  optind;
    int         errflg=0;
    char        *ifile;
    int         verbose;
    int         len;
    char        *ptr;
    FILE        *seqfile;
    int         rv;
    int         done=0;
    int         count;
    char        *ofile=0;
    FILE        *cmdfile;
    int         frameCount=0;
    FILE        *wavefile;
    char        *wfile = "tst.tbl";
    int         wavelen;
    char        *waveptr;
    FILE        *bankfile;
    char        *bfile = "tst.bnk";
    int         banklen;
    char        *bankptr;
    ALBank        *bank=0;
    ALBankFile    *bnkf=0;
    int         totalFrames = 1000;
    ALHeap      hp;
    
    meminit((char *)&g, sizeof(ALGlobals));
    meminit((char *)&c, sizeof(ALSynConfig));
    meminit((char *)&myPlayer, sizeof(MyPlayer));
    meminit((char *)&fxBuf, sizeof(fxBuf));
    
    /*************************************************************
     * parse the command line arguments
     *************************************************************/
    while ((ch = getopt(argc, argv, "vf:o:")) != EOF) {        
        switch (ch) {
	    case 'v':
                verbose = 1;
		break;
            case 'o':
                ofile = optarg;
                break;
            case 'f':
                totalFrames = atoi(optarg);
                break;
                
            case '?':
                errflg++;
                break;
        }
    }

    if (errflg) {
        (void)fprintf(stderr, "%s %s\n", argv[0], usage);
        exit (2);
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
    c.maxPVoices = MAX_PVOICES;
    c.maxUpdates = MAX_UPDATES;
    c.dmaproc    = &dmaCallBack;
    c.heap       = &hp;

    alInit(&g, &c);

    pc.numVoices = MAX_VOICES;

    playerNew(p, &pc);
    
    alBnkfNew((ALBankFile *)bankptr, waveptr);
    bank = ((ALBankFile *)bankptr)->bankArray[0];
    playerSetBank(p, bank);

    while (frameCount < totalFrames) {
        alAudioFrame(cmdList, &count, outBuf, FRAME_SIZE);
        frameCount++;
        if (ofile)
            fwrite(cmdList, sizeof(Acmd), count, cmdfile);
    }

    printf("total frames = %d\n", frameCount);
    
    playerDelete(p);
    
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
