
#include <stdio.h>

#include "vert.h"

int load_next_object( void );
void texture_object( void );
void generate_normals( void );

void    draw_sphere( void );

int
main( int argc, char **argv )
{
    generate_normals();

    while( load_next_object() ) {
	texture_object();
    };

    return( 0 );
}

void
generate_normals( void )
{

    draw_sphere();
}


Vertex dodeca_cents[12];

Vertex dodeca_verts[] = {
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

#define NUM_DODECA_VERTS	(sizeof(dodeca_verts)/(sizeof(Vertex)))

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


void
avg3( Vertex v1, Vertex v2, Vertex v3 )
{
    int i;
    Vertex cent;
    extern void add_vertex_table( Vertex );

    for(i=0; i<3; i++ )
	cent[i] = v1[i] + v2[i] + v3[i];

    cent[0] /= 3;
    cent[1] /= 3;
    cent[2] /= 3;

    normalize( cent );

    add_vertex_table( cent );

}



void
calc_tris( int fnum, int j, double alpha )
{
    double *cent;
    double *vert1;
    double *vert2;
    Vertex rad1;
    Vertex rad2;
    Vertex ecent;
    int *face;

    cent = dodeca_cents[fnum];
    face = &(dodeca_faces[fnum][0]);

/*    printf("(Using face %d, verts %d and %d)", fnum, face[0] - 1, face[1] - 1 );
*/

    vert1 = dodeca_verts[ face[j] - 1 ];
    vert2 = dodeca_verts[ face[(j+1)%5] - 1 ];

    vinterp( vert1, vert2, 0.5, ecent );

    vinterp( cent, vert1, alpha, rad1 );

    vinterp( cent, vert2, alpha, rad2 );

    avg3( vert1, rad1, ecent );
    avg3( rad1, cent, rad2 );
    avg3( rad1, rad2, ecent );
    avg3( vert2, ecent, rad2 );

/*    printf("Alpha = %6.4f, a1= %g, a2= %g, a3= %g, total area = %11.8f\n",
	    alpha, a1, a2, a3, 12*5*(a1+2*a2+a3) );
*/
}

void
draw_sphere( void )
{
    int i, j;
    double alpha;

    for(i=0; i<NUM_DODECA_VERTS; i++)
	normalize( dodeca_verts[i] );
    
    for(i=0; i<NUM_DODECA_FACES; i++) {
	calc_cent( dodeca_faces[i], 5, dodeca_verts, dodeca_cents[i] );
    };

    for(i=0; i<NUM_DODECA_FACES; i++) {
	normalize( dodeca_cents[i] );
    };

    alpha = 0.5102;
    for(i=0; i<NUM_DODECA_FACES; i++)
	for(j=0;j<5;j++)
	    calc_tris( i, j, alpha );

}


