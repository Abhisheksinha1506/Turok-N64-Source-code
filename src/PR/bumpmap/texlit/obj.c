
#include <stdio.h>

#include "vert.h"

#include "obj.h"

int load_next_object( void );
void texture_object( void );

extern Object obj1;
extern Object obj2;

Object *(obj_list[]) = {
    &obj1,
};

Object *cur_obj = NULL;
static int obj_num = -1;

FILE *obj_dls = NULL;
FILE *obj_texs = NULL;
FILE *obj_verts = NULL;

#define TMAX (16)
#define SMAX (16)

void
open_files( void )
{
    obj_dls = fopen( "obj_dls.h", "w" );

    fprintf( obj_dls, "/*  Object Display Lists  */\n");
    fprintf( obj_dls, "/*  Automatically Generated File  */\n");
    fprintf( obj_dls, "\n");
    fprintf( obj_dls, "#include \"obj_texs.h\"\n");
    fprintf( obj_dls, "\n");
    fprintf( obj_dls, "#include \"obj_verts.h\"\n");
    fprintf( obj_dls, "\n");
    fprintf( obj_dls, "\n");

    obj_texs = fopen( "obj_texs.h", "w" );

    fprintf( obj_texs, "/*  Object Textures  */\n");
    fprintf( obj_texs, "/*  Automatically Generated File  */\n");
    fprintf( obj_texs, "\n");
    fprintf( obj_texs, "#define OBJ_SMAX (%d)\n", SMAX);
    fprintf( obj_texs, "#define OBJ_TMAX (%d)\n", TMAX);
    fprintf( obj_texs, "\n");

    obj_verts = fopen( "obj_verts.h", "w" );

    fprintf( obj_verts, "/*  Object Verticies  */\n");
    fprintf( obj_verts, "/*  Automatically Generated File  */\n");
    fprintf( obj_verts, "\n");

}


int
load_next_object( void )
{
    if( obj_dls == NULL ) {
	open_files();
    };

    cur_obj = NULL;

    obj_num ++;

    if( obj_num >= sizeof( obj_list ) / sizeof( Object *) ) {

	fclose( obj_dls );
	fclose( obj_texs );
	fclose( obj_verts );

	return( 0 );
    };
    
    cur_obj = obj_list[ obj_num ];

    return( 1 );
}

void light_obj( Object * );

void calc_lighting_texture3( Object *, Vertex, Vertex, Vertex, unsigned char *, int, int );


void
texture_object( void )
{
    int b;
    int f;
    unsigned char tex[TMAX][SMAX];
    int s,t;
    objVert *v;
    int *face;

    fprintf( obj_dls, "\n");
    fprintf( obj_dls, "Gfx obj%d_dl[] = {\n", obj_num);

    light_obj( cur_obj );

    fprintf( obj_verts, "\n");
    fprintf( obj_verts, "Vtx obj%d_verts[] = {\n", obj_num);

    for(b=0; b<cur_obj->mat.nbumps; b++)
	if( cur_obj->mat.bumps[b].type == BUMP_RADIAL ) { /* RANDOMIZE!!!! */
	    extern double frand( void );
	    extern void vrand( Vertex, Vertex );
	    Vertex vr_scale;

	    vr_scale[0] = 1.0;
	    vr_scale[1] = 1.0;
	    vr_scale[2] = 1.0;

	    vrand( cur_obj->mat.bumps[b].direction, vr_scale );
	    normalize( cur_obj->mat.bumps[b].direction );

	    cur_obj->mat.bumps[b].scale[0] = 0.002 + 0.035*frand()*frand();
	    cur_obj->mat.bumps[b].scale[2] = 0.75 + 2.5*frand()*frand();
	};

    v = cur_obj->verts;
    face = cur_obj->faces;

    for(f=0; f<cur_obj->nfaces; f++, face+=3 ) {

	for(t=0; t<TMAX; t++)
	    for(s=0; s<SMAX; s++)
		tex[t][s] = 255;

#define VSCALE	(100)

	fprintf( obj_verts, "\t{%d, %d, %d, 0, 0<<6, 0<<6, %d, %d, %d, 255},\n",
		(int) ( VSCALE * (v[face[0]].vert[0] + cur_obj->center[0]) ),
		(int) ( VSCALE * (v[face[0]].vert[1] + cur_obj->center[1]) ),
		(int) ( VSCALE * (v[face[0]].vert[2] + cur_obj->center[2]) ),
		v[face[0]].red, v[face[0]].green, v[face[0]].blue     );

	fprintf( obj_verts, "\t{%d, %d, %d, 0, OBJ_SMAX<<6, 0<<6, %d, %d, %d, 255},\n",
		(int) ( VSCALE * (v[face[1]].vert[0] + cur_obj->center[0]) ),
		(int) ( VSCALE * (v[face[1]].vert[1] + cur_obj->center[1]) ),
		(int) ( VSCALE * (v[face[1]].vert[2] + cur_obj->center[2]) ),
		v[face[1]].red, v[face[1]].green, v[face[1]].blue     );


	fprintf( obj_verts, "\t{%d, %d, %d, 0, 0<<6, OBJ_TMAX<<6, %d, %d, %d, 255},\n",
		(int) ( VSCALE * (v[face[2]].vert[0] + cur_obj->center[0]) ),
		(int) ( VSCALE * (v[face[2]].vert[1] + cur_obj->center[1]) ),
		(int) ( VSCALE * (v[face[2]].vert[2] + cur_obj->center[2]) ),
		v[face[2]].red, v[face[2]].green, v[face[2]].blue     );

	calc_lighting_texture3( 
		cur_obj,
		v[face[0]].normal,
		v[face[1]].normal,
		v[face[2]].normal,
		&(tex[0][0]), SMAX, TMAX );

    fprintf( obj_dls, "gsDPLoadTextureBlock(obj%d_face%d_tex, G_IM_FMT_CI, G_IM_SIZ_8b, OBJ_SMAX, OBJ_TMAX, 0,\n",
	     obj_num, f);
    fprintf( obj_dls, "\t\t\tG_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),\n");
    fprintf( obj_dls, "\tgsDPLoadSync(),\n" );
    fprintf( obj_dls, "\tgsSPVertex(&(obj%d_verts[%d]), 3, 0),\n", obj_num, f*3 );
    fprintf( obj_dls, "\tgsSP1Triangle(0, 1, 2, 0),\n" );
    fprintf( obj_dls, "\tgsDPPipeSync(),\n" );

	fprintf( obj_texs, "\n");
	fprintf( obj_texs, "unsigned char obj%d_face%d_tex[] = {\n", obj_num, f);

	for(t=0; t<TMAX; t++) {
	    for(s=0; s<SMAX; s++)
		fprintf( obj_texs, "%3d,", tex[t][s] );
	    fprintf( obj_texs, "\n");
	} ;

	fprintf( obj_texs, "};\n");
	fprintf( obj_texs, "\n");
    };

    fprintf( obj_dls, "gsSPEndDisplayList()\n");
    fprintf( obj_dls, "};\n");
    fprintf( obj_dls, "\n");

    fprintf( obj_verts, "};\n");
    fprintf( obj_verts, "\n");
}

Vertex lights[] = {
    {  0.707, 0.0, 0.707 },
    {  0.866, 0.0, -0.5 },
#if 0
    {  1.0, 0.0, 0.0 },
    { -1.0, 0.0, 0.0 },
    {  1.0,-1.0, 0.0 },
#endif
};


Vertex ambient_color = { 0.05000, 0.15000, 0.10000 };

Vertex colors[] = {
    {  0.8, 0.8, 0.00000 },
    {  0.20000, 0.20000, 0.2000000 },
#if 0
    {  0.8, 0.8, 0.8 },
    {  0.15, 0.05, 0.0 },
    {  0.0, 0.0, 1.0 },
#endif
};

#define NUM_LIGHTS	(sizeof( lights )/sizeof( Vertex ) )

#define RGBA5551(r,g,b,a) (((r & 0xf8)<<8)| \
			   ((g & 0xf8)<<3)| \
			   ((b & 0xf8)>>2)| \
			   ((a & 0x80)>>7)    )

void
light_obj( Object *obj )
{
    unsigned short *tlut;
    int r,g,b;
    double fr,fg,fb;
    unsigned char mat_r,mat_g,mat_b;
    int lnum;
    int vnum, v;
    Vertex *dirs;
    double s;


    fprintf( obj_verts, "float obj%d_lightclrs[%d][6] = {\n", obj_num, NUM_LIGHTS+1);
    fprintf( obj_verts, "\t{ %8.6f, %8.6f, %8.6f,  ",
	    1.0*obj->mat.red, 1.0*obj->mat.green, 1.0*obj->mat.blue );
    fprintf( obj_verts, " %8.6f, %8.6f, %8.6f }, /* Material + Ambient */\n",
	    ambient_color[0], ambient_color[1], ambient_color[2]);

    for( lnum=0; lnum< NUM_LIGHTS; lnum++ ) {
	normalize( lights[lnum] );
	fprintf( obj_verts, "\t{ %8.6f, %8.6f, %8.6f, ", 
		lights[lnum][0], lights[lnum][1], lights[lnum][2]);
	fprintf( obj_verts, " %8.6f, %8.6f, %8.6f },\n",
		colors[lnum][0], colors[lnum][1], colors[lnum][2]);
    };
    fprintf( obj_verts, "};\n\n");

    vnum = obj->mat.lut.ndirs;
    dirs = obj->mat.lut.dirs;

    tlut = &(obj->mat.lut.table[0]);

    mat_r = obj->mat.red;
    mat_g = obj->mat.green;
    mat_b = obj->mat.blue;

    fprintf( obj_texs, "\n");
    fprintf( obj_texs, "unsigned short obj%d_tlut[] = {\n", obj_num);

    fprintf( obj_verts, "\n");
    fprintf( obj_verts, "float obj%d_vects[%d][3] = {\n", obj_num, vnum);

    for(v=0; v<vnum; v++ ) {

	fprintf( obj_verts, "\t{ %8.6f, %8.6f, %8.6f },\n", 
		dirs[0][0], dirs[0][1], dirs[0][2]);

	fr = mat_r * ambient_color[0];
	fg = mat_g * ambient_color[1];
	fb = mat_b * ambient_color[2];

	for( lnum=0; lnum< NUM_LIGHTS; lnum++ ) {
	    s = vdot( dirs[0], lights[lnum] );
	    if( s > 0 ) {
		fr += s * colors[lnum][0] * mat_r;
		fg += s * colors[lnum][1] * mat_g;
		fb += s * colors[lnum][2] * mat_b;
	    };
	};


	r = fr;
	g = fg;
	b = fb;

	if( r > 255 ) r = 255;
	if( g > 255 ) g = 255;
	if( b > 255 ) b = 255;

	*tlut = RGBA5551(r,g,b,255);

	fprintf( obj_texs, "%5d, %5d, %5d, %5d%s", *tlut, *tlut, *tlut, *tlut, 
		((v&1)==1)?",\n":", " );

	tlut++;

	dirs++;
    };

    fprintf( obj_verts, "};\n\n");

    fprintf( obj_texs, "};\n");
    fprintf( obj_texs, "\n");
}


