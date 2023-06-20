#include <stdio.h>
#include <stdlib.h>
#include <bstring.h>
#include <assert.h>
#include <getopt.h>
#include <math.h>

static char usage[] = "-verbose <filename>";

main(int argc, char **argv)
{
    int         ch;
    extern char *optarg;
    extern int  optind;
    int         errflg=0;
    char        *sfile;
    int         verbose;
    FILE        *seqfile;
    int         rv;
    float       qnpt;
    long        tempo;
    
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

    sfile = argv[optind++];
    if (optind != argc) {
	fprintf(stderr, "warning: only first file (%s) used, rest ignored\n",
	   sfile);
    }

    /*
     * load the sequence file
     */
    seqfile = fopen(sfile, "w");
    if (!seqfile) {
        printf("Can't open sequence file\n");
        exit(1);
    }

    /* division */
    qnpt = 1.0/(float)120;

    rv = fwrite(&qnpt, sizeof(qnpt), 1, seqfile);
    assert(rv == 1);

    /* tempo */
    tempo = 700000;
    
    putc(0, seqfile);   
    putc(0, seqfile);
    
    putc(0xff, seqfile);
    putc(0x51, seqfile);
    putc(0x03, seqfile);
    putc((tempo >> 16) & 0xff, seqfile);
    putc((tempo >>  8) & 0xff, seqfile);
    putc((tempo >>  0) & 0xff, seqfile);
    
    /* program change */
    putc(0, seqfile);   
    putc(0, seqfile);
    
    putc(0xc0, seqfile);
    putc(0x00, seqfile);

    /* midi data */
    putc(0, seqfile);           /* note 1 on */
    putc(0, seqfile);

    putc(0x90, seqfile);   
    putc(55, seqfile);
    putc(0x7f, seqfile);
    
    putc(0, seqfile);           /* note 1 off */
    putc(100, seqfile);

    putc(0x90, seqfile);   
    putc(55, seqfile);
    putc(0x0, seqfile);
    
    putc(0, seqfile);           /* note 2 on */
    putc(20, seqfile);

    putc(0x90, seqfile);   
    putc(57, seqfile);
    putc(0x7f, seqfile);
    
    putc(0, seqfile);           /* note 2 off */
    putc(100, seqfile);

    putc(0x90, seqfile);   
    putc(57, seqfile);
    putc(0x0, seqfile);
    
    putc(0, seqfile);           /* note 3 on */
    putc(20, seqfile);

    putc(0x90, seqfile);   
    putc(53, seqfile);
    putc(0x7f, seqfile);
    
    putc(0, seqfile);           /* note 3 off */
    putc(100, seqfile);

    putc(0x90, seqfile);   
    putc(53, seqfile);
    putc(0x0, seqfile);
    
    putc(0, seqfile);           /* note 4 on */
    putc(20, seqfile);

    putc(0x90, seqfile);   
    putc(41, seqfile);
    putc(0x7f, seqfile);
    
    putc(0, seqfile);           /* note 4 off */
    putc(100, seqfile);

    putc(0x90, seqfile);   
    putc(41, seqfile);
    putc(0x0, seqfile);
    
    putc(0, seqfile);           /* note 5 on */
    putc(20, seqfile);

    putc(0x90, seqfile);   
    putc(48, seqfile);
    putc(0x7f, seqfile);
    
    putc(0, seqfile);           /* note 5 off */
    putc(100, seqfile);

    putc(0x90, seqfile);   
    putc(48, seqfile);
    putc(0x0, seqfile);
    
    /* EOF */
    putc(0, seqfile);   
    putc(0, seqfile);
    
    putc(0xff, seqfile);
    putc(0x2f, seqfile);
    putc(0, seqfile);

    fflush(seqfile);
    fclose(seqfile);
}
