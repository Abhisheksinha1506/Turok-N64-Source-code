#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <miditime.h>
#include <midi.h>
#include <midiio.h>

#include <libaudio.h>

MIport *MInewport(void);
MIconfig *MInewconfig(void);
 
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

main(int argc, char **argv)
{
    MIport      *port;
    MIconfig    *c;
    MIevent     e;
    ALSeq       seq;    
    int         done = 0;
    ALSeqMarker marker;
    
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
    
    long        uspt = 6250;   /* microseconds per tick */
    long        tempo;
    char        status;
    char        channel;
    ALEvent     evt;
    
    /*
     * parse the command line arguments
     */
    while ((ch = getopt(argc, argv, "v")) != EOF) {        
        switch (ch) {
	    case 'v':
                verbose = 1;
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

    /*
     * set up the MIDI port
     */
    c = MInewconfig();
    MICsetstamp(c, MIDELTASTAMP);
    
    port = MInewport();
    if (MIopen(port, "w", c) < 0) {
	perror("open");
	exit(-1);
    }

    /*
     * load the sequence file
     */
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

    alSeqNew(&seq, ptr, len);    
    alSeqNewMarker(&seq, &marker, 0);
    
    /*
     * play
     */
    while (!done) {

        alSeqNextEvent(&seq, &evt, &marker);
        
        status  = evt.msg.midi.status;
        channel = evt.msg.midi.status & MIDI_ChannelMask;
        
        if (status == MIDI_Meta) {
            if (evt.msg.tempo.type == 0x51) {
                tempo = (evt.msg.tempo.byte1 << 16) |
                    (evt.msg.tempo.byte2 <<  8) |
                    (evt.msg.tempo.byte3 <<  0);

                uspt = (long)(seq.qnpt*((float)tempo));
            } else {
                done = 1;
                break;
            }
            
        } else if ((status & MIDI_StatusMask) != MIDI_SysEx) {
            e.dt = MItimecreatemicros(evt.msg.midi.ticks*uspt);        
            e.t  = MIMESSAGE;
            MImakemessage(&e.mm.msgbuf, status, channel, evt.msg.midi.byte1,
                          evt.msg.midi.byte2);
	
            if (MIsend(port, &e, 1) < 0) {
                perror("send midi message");
                exit(-1);
            }
        } else {
            printf("bogus message\n");
        }
    }
    sleep(5);
    printf("done!");
}  

