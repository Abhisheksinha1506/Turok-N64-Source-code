#include <stdio.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/device.h>

Matrix Identity = { 1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1 };

#define AMB (11/256.0)

float mat[] = {
	AMBIENT, AMB, AMB, AMB,
	DIFFUSE, 0.4, 0.4, .4,
#ifdef SHINY
	SPECULAR, .1, .5, .1,
	SHININESS, 8,			
#endif
	LMNULL,
};

float bmat[] = {
	AMBIENT,  AMB, AMB, AMB,
	DIFFUSE,  0.11, 0.07, 0.0,
#ifdef SHINY
	SPECULAR, 0.3, 0.05, 0.1,
	SHININESS, 30,
#endif
	LMNULL,
};

static float lm[] = {
	AMBIENT, .1, .1, .1,
	LOCALVIEWER, 1,
	TWOSIDE, 1,
	LMNULL
};

static float lt[] = {
	LCOLOR, 0, 1, 0,
	POSITION, -1, 0, 1, 0,
	LMNULL
};

static float lt2[] = {
	LCOLOR, 1, 0.0, 0,
	POSITION, 1, 1, 1, 0,
	LMNULL
};

static float lt3[] = {
	LCOLOR, 0, 0.0, 1,
	POSITION, 1, -1, 1, 0,
	LMNULL
};

main( int argc, char **argv )
{
long int xsize = 800, ysize = 800, fov = 400, npics = -64;
long xorigin, yorigin;
float rx, ry, dx, dy;
short val;
double atof();
int count = 0;

	if( argc > 1 )
	    npics = atoi( argv[1] );

	if( argc > 3 ) {
	    xsize = atoi( argv[2] );
	    ysize = atoi( argv[3] );
	};

	if( argc > 4 ) 
	    fov = 10*atof( argv[4] );

	rx = 45; dx = 2.0;
	ry =  0; dy = 3.0;

	if( argc > 8 ) {
	    rx = atof( argv[5] );
	    ry = atof( argv[6] );
	    dx = atof( argv[7] );
	    dy = atof( argv[8] );
	}

	keepaspect(xsize, ysize);
	minsize( xsize,  ysize );
	prefsize( xsize,  ysize );
	winopen("cylinder");
	qdevice(ESCKEY);
	getorigin(&xorigin, &yorigin);
	getsize(&xsize, &ysize);
	printf("Size = %d x %d\n", xsize, ysize );
	RGBmode();

	doublebuffer();

	gconfig();
	lsetdepth(getgdesc(GD_ZMIN), getgdesc(GD_ZMAX));
	zbuffer(1);
	while (!(qtest() && qread(&val) == ESCKEY && val == 0)) {

	mmode(MPROJECTION);
	loadmatrix( Identity );
	mmode(MVIEWING);
	loadmatrix( Identity );
	translate( 0, 0, -4 );
	rot( rx, 'x' );
	rot( ry, 'y' );
	perspective(fov, xsize/(float)ysize, .25, 15.0);
	lmdef(DEFMATERIAL, 1, 0, mat);
	lmdef(DEFMATERIAL, 2, 0, bmat);
	lmdef(DEFLIGHT, 1, 0, lt);
	lmdef(DEFLIGHT, 2, 0, lt2);
	lmdef(DEFLIGHT, 3, 0, lt3);
	lmdef(DEFLMODEL, 1, 0, lm);
	lmbind(MATERIAL, 1);
	lmbind(BACKMATERIAL, 2);
	lmbind(LMODEL, 1);
	lmbind(LIGHT0, 1);
	lmbind(LIGHT1, 2);
	lmbind(LIGHT2, 3);


		czclear(0x000000, getgdesc(GD_ZMAX));
		pushmatrix();
/*		drawcyl(); */
		draw_sphere();
		popmatrix();
		swapbuffers();

                ry += dy;
                rx += dx;
		count++;

        }
}

#define NLEVS (3)
#define NSEGS (20)

drawcyl()
{
double dy = 2.0/NLEVS;
double theta, dtheta = 2*M_PI/NSEGS;
double x, y, z;
float n[3], v[3];
int i, j;

	for (i = 0, y = -1;  i < NLEVS;  i++, y += dy)  {
		bgntmesh();
		for (j = 0, theta = 0;  j <= NSEGS;  j++, theta += dtheta)  {
			if (j == NSEGS)  theta = 0;
			x = cos(theta);
			z = sin(theta);
			n[0] = x;  n[1] = 0;  n[2] = z;
			n3f(n);
			v[0] = x;  v[1] = y;  v[2] = z;
			v3f(v);
			v[1] = y + dy;
			v3f(v);
		}
		endtmesh();
	}
}


#include <math.h>

double dodeca_cents[12][3];

double dodeca_verts[][3] = {
	{ 1.618034,   0,		0.618034	},
	{ 1,	    1,		1	},
	{ 0,	    0.618034,	1.618034	},
	{ 0,	   -0.618034,	1.618034	},
	{ 1,	   -1,		1	},
	{ -1,	   -1,		1	},
	{ -0.618034,  -1.618034,	0	},
	{ 0.618034,   -1.618034,	0	},
	{ 1,	   -1,		-1	},
	{ 1.618034,   0,		-0.618034	},
	{ 1,	    1,		-1	},
	{ 0.618034,    1.618034,	0	},
	{ -0.618034,   1.618034,	0	},
	{ -1,	    1,		1	},
	{ -1.618034,  0,		0.618034	},
	{ -1.618034,  0,		-0.618034	},
	{ -1,	   -1,		-1	},
	{ 0,	   -0.618034,	-1.618034	},
	{ 0,	    0.618034,	-1.618034	},
	{ -1,	    1,		-1	}};

#define NUM_DODECA_VERTS	(sizeof(dodeca_verts)/(3*sizeof(double)))

int dodeca_faces[][5] = {
	{ 1,     5,   4,    3,    2    },
	{ 2,    12,  11,   10,    1    },
	{ 1,    10,   9,    8,    5    },
	{ 5,     8,   7,    6,    4    },
	{ 4,     6,  15,   14,    3    },
	{ 3,    14,  13,   12,    2    },
	{ 12,   13,  20,   19,   11    },
	{ 13,   14,  15,   16,   20    },
	{ 15,    6,   7,   17,   16    },
	{ 18,   17,   7,    8,    9    },
	{ 11,   19,  18,    9,   10    },
	{ 20,   16,  17,   18,   19    }};

#define NUM_DODECA_FACES	(sizeof(dodeca_faces)/(5*sizeof(dodeca_faces[0][0])))

double
vlen( double vert[3] )
{
    double len;
    double x;

    x = vert[0];
    len = x*x;
    x = vert[1];
    len += x*x;
    x = vert[2];
    len += x*x;

    len = sqrt(len);

    return( len );
}

double
vdist( double vert1[3], double vert2[3] )
{
    double len;
    double x;

    x = vert1[0] - vert2[0];
    len = x*x;
    x = vert1[1] - vert2[1];
    len += x*x;
    x = vert1[2] - vert2[2];
    len += x*x;

    len = sqrt(len);

    return( len );
}

void
normalize( double vert[3] )
{
    double len;

    len = vlen( vert );

    vert[0] /= len;
    vert[1] /= len;
    vert[2] /= len;
}

void
calc_cent( int face[], int num_ps, double verts[][3], double cent[3] )
{
    int i;
    double *vert;

    cent[0] = cent[1] = cent[2] = 0.0;

    for(i=0; i<num_ps; i++ ) {
	vert = &(verts[face[i]-1][0]);
	cent[0] += vert[0];
	cent[1] += vert[1];
	cent[2] += vert[2];
    };

    cent[0] /= num_ps;
    cent[1] /= num_ps;
    cent[2] /= num_ps;
}


double
area( double pa[3], double pb[3], double pc[3] )
{
    double a,b,c,s;

    a = vdist( pa, pb );
    b = vdist( pb, pc );
    c = vdist( pc, pa );

    s = (a+b+c)/2;

    a = sqrt( s*(s-a)*(s-b)*(s-c) );

    return( a );
}


double asum = 0;

void
avg3( double v1[3], double v2[3], double v3[3] )
{
    int i;
    double cent[3];
    float fcent[3];
    double a;

    a = area( v1, v2, v3 );

    asum += a;

    for(i=0; i<3; i++ )
	cent[i] = v1[i] + v2[i] + v3[i];

    cent[0] /= 3;
    cent[1] /= 3;
    cent[2] /= 3;

    normalize( cent );

    fcent[0] = cent[0];
    fcent[1] = cent[1];
    fcent[2] = cent[2];

    bgntmesh();
	n3f(fcent);
	v3d(v1);
	n3f(fcent);
	v3d(v2);
	n3f(fcent);
	v3d(v3);
    endtmesh();


}



void
calc_tris( int fnum, int j, double alpha )
{
    int i;
    double *cent;
    double *vert1;
    double *vert2;
    double rad1[3];
    double rad2[3];
    double ecent[3];
    int *face;
    double a1, a2, a3;
    int fv1, fv2, fr1, fr2, fc, fec;

    cent = dodeca_cents[fnum];
    face = &(dodeca_faces[fnum][0]);

/*    printf("(Using face %d, verts %d and %d)", fnum, face[0] - 1, face[1] - 1 );
*/

    vert1 = dodeca_verts[ face[j] - 1 ];
    vert2 = dodeca_verts[ face[(j+1)%5] - 1 ];
/*    fprintf(stderr,"\t{ %d, %d, %d },\n", face[j] - 1, 20 + fnum, face[(j+1)%5] - 1 ); */

    ecent[0] = (vert2[0] + vert1[0])/2;
    ecent[1] = (vert2[1] + vert1[1])/2;
    ecent[2] = (vert2[2] + vert1[2])/2;

    rad1[0] = alpha*cent[0] + (1-alpha)*vert1[0];
    rad1[1] = alpha*cent[1] + (1-alpha)*vert1[1];
    rad1[2] = alpha*cent[2] + (1-alpha)*vert1[2];

    rad2[0] = alpha*cent[0] + (1-alpha)*vert2[0];
    rad2[1] = alpha*cent[1] + (1-alpha)*vert2[1];
    rad2[2] = alpha*cent[2] + (1-alpha)*vert2[2];

    normalize( ecent );
    normalize( rad1 );
    normalize( rad2 );

	printf("\t{ { %8.6f, %8.6f, %8.6f },\n",
		rad1[0], rad1[1], rad1[2]  );
	printf("\t  { %8.6f, %8.6f, %8.6f },\n",
		rad1[0], rad1[1], rad1[2]  );
	printf("\t  255, 255, 255  },\n");

	printf("\t{ { %8.6f, %8.6f, %8.6f },\n",
		ecent[0], ecent[1], ecent[2]  );
	printf("\t  { %8.6f, %8.6f, %8.6f },\n",
		ecent[0], ecent[1], ecent[2]  );
	printf("\t  255, 255, 255  },\n");

    fv1 = face[j] - 1;
    fv2 = face[(j+1)%5] - 1;
    fc  = 20 + fnum;

    fr1 = 32+ fnum*10+ 2*j;
    fec = 32+ fnum*10+ 2*j + 1;
    fr2 = 32+ fnum*10+ 2*((j+1)%5);

    avg3( vert1, rad1, ecent );
    fprintf(stderr,"\t{ %d, %d, %d },\n", fv1, fr1, fec );
    avg3( rad1, cent, rad2 );
    fprintf(stderr,"\t{ %d, %d, %d },\n", fr1, fc, fr2 );
    avg3( rad1, rad2, ecent );
    fprintf(stderr,"\t{ %d, %d, %d },\n", fr1, fr2, fec );
    avg3( vert2, ecent, rad2 );
    fprintf(stderr,"\t{ %d, %d, %d },\n", fv2, fec, fr2 );

/*    printf("Alpha = %6.4f, a1= %g, a2= %g, a3= %g, total area = %11.8f\n",
	    alpha, a1, a2, a3, 12*5*(a1+2*a2+a3) );
*/
}

draw_sphere()
{
    int i, j;
    double a1, a2;
    double alpha;

    printf("\n/* Dodeca Verts */\n\n");
    for(i=0; i<NUM_DODECA_VERTS; i++) {
	normalize( dodeca_verts[i] );
	printf("\t{ { %8.6f, %8.6f, %8.6f },\n",
		dodeca_verts[i][0],
		dodeca_verts[i][1],
		dodeca_verts[i][2]  );
	printf("\t  { %8.6f, %8.6f, %8.6f },\n",
		dodeca_verts[i][0],
		dodeca_verts[i][1],
		dodeca_verts[i][2]  );
	printf("\t  255, 255, 255  },\n");
    };
    
    for(i=0; i<NUM_DODECA_FACES; i++) {
	calc_cent( dodeca_faces[i], 5, dodeca_verts, dodeca_cents[i] );
    };

    a1 = area(  dodeca_verts[dodeca_faces[0][0]-1], 
		dodeca_verts[dodeca_faces[0][1]-1],
		dodeca_cents[0] );

    printf("\n");

    for(i=0; i<NUM_DODECA_FACES; i++) {
	normalize( dodeca_cents[i] );
	printf("\t{ { %8.6f, %8.6f, %8.6f },\n",
		dodeca_cents[i][0],
		dodeca_cents[i][1],
		dodeca_cents[i][2]  );
	printf("\t  { %8.6f, %8.6f, %8.6f },\n",
		dodeca_cents[i][0],
		dodeca_cents[i][1],
		dodeca_cents[i][2]  );
	printf("\t  255, 255, 255  },\n");
    };

    printf("\n\t\t/* Subfaces */\n");
    a2 = area(  dodeca_verts[dodeca_faces[0][0]-1], 
		dodeca_verts[dodeca_faces[0][1]-1],
		dodeca_cents[0] );
    
/*    printf("Dodeca= %g, Bucky= %g\n", a1*12*5, a2*12*5 ); */

    fprintf(stderr,"\n/* Faces */\n");
    alpha = 0.5102;
    for(i=0; i<NUM_DODECA_FACES; i++)
	for(j=0;j<5;j++)
	    calc_tris( i, j, alpha );

/*    printf("Final Surface Area= %g\n", asum ); */

}


