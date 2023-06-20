
#include "vert.h"

#include "obj.h"

#include <math.h>
#include <stdio.h>

int
fmin( int a, int b )
{
    if( a < b )
	return( a );

    return(b);
}

void calc_lighting_texture4( Object *, Vertex, Vertex, Vertex, Vertex, unsigned char *, int, int );

void simple_closest_norm_obj( Vertex, Object *, Vertex );

void
calc_lighting_texture3( Object *obj, Vertex n0, Vertex ns, Vertex nt,
			unsigned char *img, int smax, int tmax )
{
    Vertex nst;

    normalize( n0 );
    normalize( ns );
    normalize( nt );

    vadd( ns, nt, nst );
    vsub( nst, n0, nst );

    normalize( nst );

    simple_closest_norm_obj( nst, obj, nst );

    calc_lighting_texture4( obj, n0, ns, nt, nst, img, smax, tmax );
}

int simple_closest_vert( Vertex );

void
calc_lighting_texture4( Object *obj, Vertex n0, Vertex ns, Vertex nt, Vertex nst,
			unsigned char *img, int smax, int tmax )
{
    int s,t;
    double ft, fs;
    int sbig;
    int i;
    Vertex ns0, ns1, n;
    void apply_bumps( Vertex, Object * );

    for(t=0; t<tmax; t++) {
	ft = (((float)t)/tmax);
	if( t == 0 )
	    sbig = fmin( smax, smax*((tmax - (float)t)/tmax) + 3 );
	else
	    sbig = fmin( smax, smax*((tmax-1.0-t)/tmax) + 3 );

	vinterp(  nt, n0, ft, ns0 );
	vinterp( nst, ns, ft, ns1 );

	for(s=0; s<sbig; s++) {
	    fs = (((float)s)/smax);
	    vinterp( ns1, ns0, fs, n );

	    apply_bumps( n, obj );

	    i = simple_closest_vert( n );
	    img[s+t*smax] = i;
	}
    };
}


int num_vtab = 0;
Vertex vertex_table[512];

int 
simple_closest_vert( Vertex n )
{
    int closest = -1;
    int i;
    double d_max = -2;
    double d;

    for(i=0; i<num_vtab; i++) {
	d = vdot( n, vertex_table[i] );
	if( d > d_max ) {
	    closest = i;
	    d_max = d;
	};
    };

    return( closest );
}


void 
simple_closest_norm_obj( Vertex n, Object *obj, Vertex vbest )
{
    int closest = -1;
    int i;
    double d_max = -2;
    double d;

    for(i=0; i<obj->nverts; i++) {
	d = vdot( n, obj->verts[i].normal );
	if( d > d_max ) {
	    closest = i;
	    d_max = d;
	};
    };

    vbest[0] = obj->verts[closest].normal[0];
    vbest[1] = obj->verts[closest].normal[1];
    vbest[2] = obj->verts[closest].normal[2];
}


void
add_vertex_table( Vertex v )
{
    int i;

    i = num_vtab++;

    vertex_table[i][0] = v[0];
    vertex_table[i][1] = v[1];
    vertex_table[i][2] = v[2];
}

#define RSCALE (1.0/0x7fffffff)

#include <sys/types.h>
#include <unistd.h>
#include <time.h>

double
frand( void )
{
    static int seed = -1;

    if( seed == -1 ) {
	time_t t_dum;

	seed = getpid() + time( &t_dum );
	(void) srandom( seed );
    };

    return( random() * RSCALE );
}

void
vrand( Vertex vout, Vertex vscale )
{
    do {
	vout[0] = 2*frand() - 1.0;
	vout[1] = 2*frand() - 1.0;
	vout[2] = 2*frand() - 1.0;
    } while( vlen( vout ) > 1.0 );

    vout[0] *= vscale[0];
    vout[1] *= vscale[1];
    vout[2] *= vscale[2];
}


int
vradial( Vertex vout, Vertex vcur, objBump *bump )
{
    Vertex vdif;
    double d, f;
    int id;
    signed char *data;

    d = 1.0 - vdot( bump->direction, vcur );
    if( d  < bump->scale[0]  ) {
	d = d / bump->scale[0] * (bump->shape->xdim - 1);	/* Index into bump_map */
	id = d;
	d = d - id;

	data = (signed char *) bump->shape->data;

	f = data[id] * (1-d) + d * data[id+1];

	f /= 128;	/* Normalize to -1...+1 */

	f *= bump->scale[2];

	vsub( bump->direction, vcur, vdif );

	normalize( vdif );

	vout[0] = vdif[0] * f;
	vout[1] = vdif[1] * f;
	vout[2] = vdif[2] * f;

	return( 1 );

    } else {
	vout[0] = 0.0;
	vout[1] = 0.0;
	vout[2] = 0.0;

	return( 0 );
    }
}

void 
apply_bumps( Vertex v, Object *obj )
{
    int bnum;
    objBump *bump;
    Vertex vsum, bumpv;

    vsum[0] = vsum[1] = vsum[2] = 0.0;
    vadd( v, vsum, vsum );

    bump = obj->mat.bumps;

    for(bnum=0; bnum<obj->mat.nbumps; bnum++, bump++) {
	switch( bump->type ) {
	    case BUMP_UNOISE:
		vrand( bumpv, bump->scale );
		vadd( vsum, bumpv, vsum );	/* Accumulate effects of bumps */
		break;
	    case BUMP_DNOISE:
		break;
	    case BUMP_RADIAL:
		if( vradial( bumpv, v, bump ) )
		    vadd( v, bumpv, vsum );		/* Overwrite previous bumps */
		break;
	    default:
		break;
	};

    };


    v[0] = vsum[0];
    v[1] = vsum[1];
    v[2] = vsum[2];

    normalize( v );

}


#if 0

/* this Vertex list structure defines some information
   about the adjacency of some vertecies.
   The structure is hierarchical, with each level consisting
   of a cloud of verticies (stored in a linked list defined
   by the "next" field and terminated by NULL.  For each
   point in this set there is an associated "children" list
   which consists of points close to the parent.
*/

typedef struct vert_list_struct {
	int vnum;
	Vertex *v;
	struct vert_list_struct **children;
} Vert_list;


Vertex tetraherdron[] = {
	{  1.0/6,  1.0/6, -5.0/6 },
	{  1.0/6, -5.0/6,  1.0/6 },
	{ -5.0/6,  1.0/6,  1.0/6 },
	{  1.0/2,  1.0/2,  1.0/2 }    };


int 
closest_vert( Vertex *n, Vert_list *vl )
{
    Vert_list *vlclose = NULL;
    Vertex *v;
    double d_min = -2;
    double d;

    do {
	/* find closest vertex */

	for( v=vl->v; vl; vl = vl->next ) {

	    if( v && ((d=vdot( n, v )) > d_max )) {
		vlclose = vl;
		d_max = d;
	    }
	};

	vl = vlclose->children;

    } while( vl );

    return( vertex_table - vlclose->v );
}

#endif /* 0 */
