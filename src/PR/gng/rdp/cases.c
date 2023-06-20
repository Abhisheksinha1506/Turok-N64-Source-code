/*
 *    Generate coverage cases
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CASES 5

#define SC_WIDTH 320
#define SC_HEIGHT 240
#define SC_SCALE 4		/*
				   for 1/4 subpixel resolution 
				 */
#define CO_SCALE 4

#define TRUE -1
#define FALSE 0

#define MAX_VTX 16

#define VTX_ELS 10		/*
				   x, y, z, s, t, w, r, g, b, a 
				 */
#define VX 0
#define VY 1
#define VZ 2
#define VS 3
#define VT 4
#define VW 5
#define VR 6
#define VG 7
#define VB 8
#define VA 9

char    output_file[CASES][80] =
{
   "rdpcov_case_edge_",
   "rdpcov_case_vertex_",
   "rdpcov_case_skinny_",
   "rdpcov_case_tiny_",
   "rdpcov_case_disc_"};
FILE   *fp;

struct Vertex
  {
     float   e[VTX_ELS];
  };

struct Vertex vtx[100];

char	vtx_strings[10000][128];
char	tri_strings[10000][128];
int	vtx_count = 0, tri_count = 0, vtx_group = 0;
int     xi = 0;
int     yi = 0;
int     which = 0;

main (argc, argv)
int     argc;
char  **argv;
{
   char    filename[80];
   int     i, j;
   float   ang, dang;
   int     dxi, dyi;

   while (--argc)
     {
	if ((*++argv)[0] == '-')
	  {
	     switch ((*argv)[1])
		{
		case 'x':
		   argc--;
		   argv++;
		   sscanf (*argv, "%d", &xi);
		   break;
		case 'y':
		   argc--;
		   argv++;
		   sscanf (*argv, "%d", &yi);
		   break;
		case 'w':
		   argc--;
		   argv++;
		   sscanf (*argv, "%d", &which);
		   break;

		}
	  }
     }
   if (which >= CASES || which < 0)
      which = 0;
   sprintf (filename, "%s%d%d.h", output_file[which], xi, yi);
   fp = fopen (filename, "w");

/*
   initialize vertex attributes 
 */
   for (i = 0; i < MAX_VTX; i++)
     {
	vtx[i].e[VS] = vtx[i].e[VT] = vtx[i].e[VW] = 0;
	vtx[i].e[VR] = vtx[i].e[VG] = vtx[i].e[VB] = vtx[i].e[VA] = 255;
     }


#define X_SIZE (SC_WIDTH/4*SC_SCALE*CO_SCALE)
#define Y_SIZE (SC_HEIGHT/4*SC_SCALE*CO_SCALE)
   switch (which)
      {
      case 0:
	 /*
	    diamond with nearly horiztonal edge 
	  */

	 for (i = 0; i < MAX_VTX; i++) {
	     vtx[i].e[VG] = 255;
	     vtx[i].e[VR] = vtx[i].e[VB] = 0;
	     vtx[i].e[VA] = 255;
	 }

	 /*
	  *  jitter shared vertices y by xi, yi 
	  */
	 vtx[0].e[VX] = -X_SIZE;
	 vtx[1].e[VX] = 0;
	 vtx[2].e[VX] = X_SIZE;
	 vtx[3].e[VX] = 0;
	 vtx[0].e[VY] = yi;
	 vtx[1].e[VY] = Y_SIZE;
	 vtx[2].e[VY] = xi;
	 vtx[3].e[VY] = -Y_SIZE;
	 do_vertex (4);
	 do_tri (0, 1, 2);
	 do_tri (0, 2, 3);
	 break;
      case 1:
	 /*
	    6 triangles share vertex 
	  */

	 for (i = 0; i < MAX_VTX; i++) {
	     vtx[i].e[VB] = 255;
	     vtx[i].e[VR] = vtx[i].e[VG] = 0;
	     vtx[i].e[VA] = 255;
	 }


	 /*
	    jitter center vertex by xi, yi 
	  */
	 vtx[0].e[VX] = 0;
	 vtx[1].e[VX] = X_SIZE;
	 vtx[2].e[VX] = -X_SIZE;
	 vtx[3].e[VX] = xi;
	 vtx[4].e[VX] = X_SIZE;
	 vtx[5].e[VX] = -X_SIZE;
	 vtx[6].e[VX] = 0;
	 vtx[0].e[VY] = Y_SIZE;
	 vtx[1].e[VY] = Y_SIZE;
	 vtx[2].e[VY] = 0;
	 vtx[3].e[VY] = yi;
	 vtx[4].e[VY] = 0;
	 vtx[5].e[VY] = -Y_SIZE;
	 vtx[6].e[VY] = -Y_SIZE;
	 do_vertex (7);
	 do_tri (0, 3, 2);
	 do_tri (0, 1, 3);
	 do_tri (1, 4, 3);
	 do_tri (2, 3, 5);
	 do_tri (3, 6, 5);
	 do_tri (3, 4, 6);
	 break;
      case 2:
	 /*
	    lots of long skinny triangles 
	  */
	 /*
	    offset by xi and yi 
	  */
#define Y_DIMEN 4
#define Y_STEP 1
#define X_DIMEN 4
#define X_STEP 1
	 vtx[0].e[VX] = -X_SIZE + xi;
	 vtx[1].e[VX] = -X_SIZE + xi;
	 vtx[2].e[VX] = X_SIZE + xi;
	 vtx[3].e[VX] = X_SIZE + xi;
	 for (i = 0; i < Y_DIMEN; i += Y_STEP)
	   {
	      vtx[0].e[VY] = Y_DIMEN/* / 2*/ - i;
	      vtx[2].e[VY] = Y_DIMEN/* / 2*/ - i + yi;
	      vtx[1].e[VY] = Y_DIMEN/* / 2*/ - i - Y_STEP;
	      vtx[3].e[VY] = Y_DIMEN/* / 2*/ - i - Y_STEP + yi;
	      do_vertex (4);
	      do_tri (0, 2, 3);
	      do_tri (0, 3, 1);
	   }
	 break;

      case 3:
	 /*
	    tiny grid of triangles 
	  */
	 /*
	    offset by xi and yi 
	  */
	 dxi = 0;
	 for (i = 0; i < Y_DIMEN; i += Y_STEP)
	   {
	      vtx[0].e[VY] = Y_DIMEN / 2 - i + yi;
	      vtx[2].e[VY] = Y_DIMEN / 2 - i + yi;
	      vtx[1].e[VY] = Y_DIMEN / 2 - i - Y_STEP + yi;
	      vtx[3].e[VY] = Y_DIMEN / 2 - i - Y_STEP + yi;
	      for (j = 0; j < X_DIMEN; j += X_STEP)
		{
		   vtx[0].e[VX] = (-X_DIMEN / 2 + j + xi)*10;
		   vtx[1].e[VX] = (-X_DIMEN / 2 + j + xi)*10;
		   vtx[2].e[VX] = (-X_DIMEN / 2 + j + X_STEP + xi)*10;
		   vtx[3].e[VX] = (-X_DIMEN / 2 + j + X_STEP + xi)*10;
		   do_vertex (4);
		   do_tri (0, 2, 3);
		   do_tri (0, 3, 1);
		}
	      dxi += xi;
	   }
	 break;
      case 4:
	 /*
	  * disc, eg top of sphere 
	  */

	 /*
	  *  jitter center vertex by xi, yi 
	  */
#define DEG2RAD( a) ((a)*(float)(3.141/180.))
#define RADIUS (Y_SIZE/16)
#define COUNT 19	/* nice prime number */
	 vtx[0].e[VX] = xi;
	 vtx[0].e[VY] = yi;
	 ang = 0;
	 dang = (float) 360 / COUNT;

	 for (i = 0; i < MAX_VTX; i++) {
	     vtx[i].e[VR] = 255;
	     vtx[i].e[VG] = vtx[i].e[VB] = 0;
	     vtx[i].e[VA] = 255;
	 }

	 for (i = 0; i < COUNT; i++)
	   {
	      vtx[1].e[VX] = -RADIUS * cos (DEG2RAD (ang));
	      vtx[1].e[VY] = RADIUS * sin (DEG2RAD (ang));
/*
   end up exactly at the start 
 */
	      if (i < COUNT - 1)
		{
		   vtx[2].e[VX] = -RADIUS * cos (DEG2RAD (ang + dang));
		   vtx[2].e[VY] = RADIUS * sin (DEG2RAD (ang + dang));
		}
	      else
		{
		   vtx[2].e[VX] = -RADIUS * cos (DEG2RAD (0));
		   vtx[2].e[VY] = RADIUS * sin (DEG2RAD (0));
		}
	      do_vertex (3);
	      do_tri (0, 1, 2);
	      ang += dang;
	   }


      }				/*
				   end switch 
				 */

   for (i=0; i<vtx_count; i++) {
       fprintf(fp, "%s", vtx_strings[i]);
   }

   fprintf(fp,"Gfx %s%d%d[%d] = {\n",
	   output_file[which],xi,yi,tri_count+2);
   for (i=0; i<tri_count; i++) {
       fprintf(fp, "%s", tri_strings[i]);
   }

   fprintf(fp,"\tgsSPEndDisplayList(),\n");
   fprintf(fp,"};\n\n");

   fclose (fp);
}


do_tri (int v1, int v2, int v3)
{
   sprintf (tri_strings[tri_count++], "\tgsSP1Triangle(%d, %d, %d, 0),\n", 
	    v1, v2, v3);
}


do_vertex ( int nverts)
{
   int     i, j;
   char		tmp_str[80];
   
   sprintf(vtx_strings[vtx_count++],
	   "static Vtx %s%d%d_vtx%d[%d] = {\n",
	   output_file[which],xi,yi,vtx_group,nverts);

   for (i = 0; i < nverts; i++) {
       sprintf (vtx_strings[vtx_count], "\t{ ");
       for(j = 0; j < VTX_ELS-1; j++) {
	   sprintf(tmp_str, "%d, ", (int) vtx[i].e[j]);
	   strcat(vtx_strings[vtx_count], tmp_str);
       }
       sprintf(tmp_str, " },\n");
       strcat(vtx_strings[vtx_count], tmp_str);
       vtx_count++;
   }

   sprintf(vtx_strings[vtx_count++],"};\n");

   sprintf(tri_strings[tri_count++],
	   "\tgsSPVertex(&(%s%d%d_vtx%d[0]), %d, 0),\n",
	   output_file[which],xi,yi,vtx_group,nverts);

   vtx_group++;
}

