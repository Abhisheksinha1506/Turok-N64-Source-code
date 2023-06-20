#include <stdio.h>

main()
{
    int		i, j;
    unsigned short	stmp;
    FILE	*fd;

    fd = fopen("map_a5.h","w+");

    /*
    fprintf(fd,"static Gfx map_a5_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n\n");
    */

    fprintf(fd,"unsigned short map_a5[] = {\n");
    
    for (j = 0; j < 32; j++ ) {
        for (i = 0; i < 32; i++) {
    	    stmp = 0xaaaa;
    	    fprintf(fd," 0x%x,",stmp);
    	    stmp = 0x5555;
    	    fprintf(fd," 0x%x,",stmp);
        }
    fprintf(fd,"\n");
    }
    fprintf(fd,"\n};\n");

    fclose(fd);

    fd = fopen("map_5a.h","w+");

    /*
    fprintf(fd,"static Gfx map_5a_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n\n");
    */

    fprintf(fd,"unsigned short map_5a[] = {\n");
    
    for (j = 0; j < 32; j++ ) {
        for (i = 0; i < 32; i++) {
    	    stmp = 0x5555;
    	    fprintf(fd," 0x%x,",stmp);
    	    stmp = 0xaaaa;
    	    fprintf(fd," 0x%x,",stmp);
        }
    fprintf(fd,"\n");
    }
    fprintf(fd,"\n};\n");

    fclose(fd);

}

 
