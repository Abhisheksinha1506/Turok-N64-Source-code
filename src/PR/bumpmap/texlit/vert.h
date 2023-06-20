typedef double Vertex[3];

void vinterp( Vertex, Vertex, double, Vertex );

void vadd( Vertex, Vertex, Vertex );
void vsub( Vertex, Vertex, Vertex );

double vlen( Vertex );

double vdist( Vertex, Vertex );

double vdot( Vertex, Vertex );

void normalize( Vertex );

void calc_cent( int *, int, Vertex *, Vertex );

double area( Vertex, Vertex, Vertex );

