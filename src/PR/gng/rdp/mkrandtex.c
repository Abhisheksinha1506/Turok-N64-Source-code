#include <stdio.h>

#define VRAND_WIDTH 32
#define VRAND_HEIGHT 64
#define VRAND_SIZE VRAND_WIDTH*VRAND_HEIGHT

#define CS_EW_WIDTH 43
#define CS_EW_HEIGHT 21

main()
{
    int		i, j;
    unsigned short	stmp;
    unsigned long	ltmp;
    double	v[VRAND_SIZE];
    int		iy;
    float	two16m1 = 65535.0;
    FILE	*fd;

    fd = fopen("map_rand.h","w+");

    /*
    fprintf(fd,"static Gfx map_C_dummy_aligner1[] = { gsSPEndDisplayList() };\n\n");
    */

    fprintf(fd,"unsigned short map_rand[] = {\n");
    
    iy = 12345;
    vrand(VRAND_SIZE, v, &iy);

    for (j = 0; j < VRAND_HEIGHT; j++ ) {
        fprintf(fd,"\t",stmp);
        for (i = 0; i < VRAND_WIDTH; i++) {
    	    stmp = two16m1*v[VRAND_WIDTH*j + i];
    	    fprintf(fd," 0x%x,",stmp);
        }
    fprintf(fd,"\n");
    }
    fprintf(fd,"\n};\n");

    fclose(fd);

    fd = fopen("map_rand_comp.h","w+");

    /*
    fprintf(fd,"static Gfx map_C_dummy_aligner2[] = { gsSPEndDisplayList() };\n\n");
    */

    fprintf(fd,"unsigned short map_rand_comp[] = {\n");
    
    iy = 12345;
    vrand(VRAND_SIZE, v, &iy);

    for (j = 0; j < VRAND_HEIGHT; j++ ) {
        fprintf(fd,"\t",stmp);
        for (i = 0; i < VRAND_WIDTH; i++) {
    	    stmp = two16m1*v[VRAND_WIDTH*j + i];
    	    stmp = ~(stmp);
    	    fprintf(fd," 0x%x,",stmp);
        }
    fprintf(fd,"\n");
    }
    fprintf(fd,"\n};\n");

    fclose(fd);

    /*
     * Now generate a 32 x 32 texture.
     */
    fd = fopen("map_rand32.h","w+");

    fprintf(fd,"unsigned long map_rand32[] = {\n");

    for (j = 0; j < 32; j++ ) {
        fprintf(fd,"\t");
        for (i = 0; i < 32; i++) {
    	    ltmp = random();
    	    fprintf(fd," 0x%x,",ltmp);
        }
    fprintf(fd,"\n");
    }
    fprintf(fd,"\n};\n");

    fclose(fd);

    fd = fopen("map_cs16_rand.h","w+");

    fprintf(fd,"unsigned short map_cs16_rand[] = {\n");
    
    iy = 12345;
    vrand(CS_EW_WIDTH * CS_EW_HEIGHT, v, &iy);

    for (j = 0; j < CS_EW_HEIGHT; j++ ) {
        fprintf(fd,"\t");
        for (i = 0; i < CS_EW_WIDTH; i++) {
    	    stmp = two16m1*v[CS_EW_WIDTH*j + i];
    	    fprintf(fd," 0x%x,",stmp);
        }
    fprintf(fd,"\n");
    }
    fprintf(fd,"\n};\n");

    fclose(fd);


}

union
  {
  double d;
  struct
    {
    int i1;
    int i2;
    } s;
  } ss;


/*========================vrand=========================*/
/*     Generates n uniformly distributed random numbers */
/*     Uses iy as seed and changes it			*/
/*========================vrand=========================*/
vrand (n, v, iy)
  double v[];
  int n;
  int *iy;
  {
  static int ia = 0x3243f6ad;
  static int ic = 0x1b0cb175;
  static int m2 = 0x40000000;
  int i;

  ss.s.i1 = 0x3e000000;
  ss.s.i2 = 0;

  for (i = 0; i < n; i++)
    {
    *iy = (*iy) * ia + ic;
    if (*iy < 0) 
      *iy = (*iy + m2) + m2;
    v[i] = ss.d * (*iy);
    }
  }
