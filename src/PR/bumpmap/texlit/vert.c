
#include "vert.h"

#include <math.h>

double
vlen( Vertex vert )
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
vdot( Vertex vert1, Vertex vert2 )
{
    double x;

    x = vert1[0] * vert2[0] +
	vert1[1] * vert2[1] +
	vert1[2] * vert2[2];

    return( x );
}

double
vdist( Vertex vert1, Vertex vert2 )
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
normalize( Vertex vert )
{
    double len;

    len = vlen( vert );

    vert[0] /= len;
    vert[1] /= len;
    vert[2] /= len;
}

void
calc_cent( int face[], int num_ps, Vertex verts[], Vertex cent )
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
area( Vertex pa, Vertex pb, Vertex pc )
{
    double a,b,c,s;

    a = vdist( pa, pb );
    b = vdist( pb, pc );
    c = vdist( pc, pa );

    s = (a+b+c)/2;

    a = sqrt( s*(s-a)*(s-b)*(s-c) );

    return( a );
}

void
vadd( Vertex va, Vertex vb, Vertex vres )
{
    vres[0] = va[0] + vb[0];
    vres[1] = va[1] + vb[1];
    vres[2] = va[2] + vb[2];
}


void
vsub( Vertex va, Vertex vb, Vertex vres )
{
    vres[0] = va[0] - vb[0];
    vres[1] = va[1] - vb[1];
    vres[2] = va[2] - vb[2];
}

void
vinterp( Vertex va, Vertex vb, double fmix, Vertex vres )
{
    vres[0] = va[0]*fmix + vb[0]*(1-fmix);
    vres[1] = va[1]*fmix + vb[1]*(1-fmix);
    vres[2] = va[2]*fmix + vb[2]*(1-fmix);

    normalize( vres );
}

