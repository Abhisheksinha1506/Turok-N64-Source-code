/*
 * NOTICE: This source code includes data structures for the MultiGen Flight
 * Format which is the proprietary property of MultiGen Inc.  It is furnished
 * here under a license to Silicon Graphics and Nintendo soley for use in this
 * program.  If you wish to use the Flight Format for any other purpose, a no
 * charge license is noramlly available; contact MultiGen Inc. at
 * 408-247-4326.
 */

/*
 * flt2c.c -- converts .flt files to .c files for Reality
 *
 * Lawrence Kesteloot
 * June 8th, 1994
 *
 * Richard Webb
 * 11jan95
 * Added lighting and centering and scaling.
 *
 * $Id: flt2c.c,v 1.34 1995/09/29 17:32:48 hsa Exp $
 */

/*
 * Log:

$Log: flt2c.c,v $
 * Revision 1.34  1995/09/29  17:32:48  hsa
 * use special SP decal hack for decal mode.
 *
 * Revision 1.33  1995/06/29  04:37:24  rww
 * Added shuffle_mask to readtex arg list.  This whole
 * program should probably resort to using pre-shuffled
 * textures to avoid LoadBlock bugs.
 *
 * Revision 1.24  1995/05/26  20:35:58  lipes
 * modified code to account for texture size in generating s,t vertex parameters; added capability of input arguments for changing SetRenderMode to handle "decal" textures
 *
 * Revision 1.23  1995/04/20  22:43:18  hsa
 * remove material stuff
 *
 * Revision 1.20  1995/03/30  23:17:00  rww
 * Propagate Full lighting model support from old tree.
 * Type "flt2c" for a usage message.
 *
 * Revision 1.18  1995/03/07  19:42:26  lipes
 * modified code to generate gsSPDisplayList w/ correct arguments
 *
 * Revision 1.17  1995/01/18  02:04:47  rww
 * Added arguments for light sources and flat shading.
 * Removed material and lighting references from the
 * generated display list.
 *
 * Revision 1.16  1994/11/23  06:32:29  hsa
 * correct mbi to enforce 64-bit alignment.
 *
 * Revision 1.15  1994/11/04  22:04:08  howardc
 * updated flt2c and topgun now builds again
 *
 * Revision 1.12  1994/08/10  21:00:01  kluster
 * "garbage" was misspelled
 *
 * Revision 1.11  1994/08/08  22:15:38  jeffd
 * Modified to use new g*SetTile command with clamping bits.
 *
 * Revision 1.10  1994/08/02  16:11:49  jeffd
 * Include <mbi.h> since we ship this as source.
 *
 * Revision 1.9  1994/07/29  00:27:01  lk
 * Added support for texture-only vertex type; fixed bug with unsupported
 * tree node.
 *
 * Revision 1.8  1994/07/22  17:43:35  kluster
 * Updated parameter list in calls to readtex
 *
 * Revision 1.7  1994/07/18  23:17:15  lk
 * Changed gsLighting calls to gsSetGeometryMode (G_LIGHTING).
 *
 * Revision 1.6  1994/07/06  19:36:26  kluster
 * re-normalized vectors after being converted from int into float
 * to compensate for rounding errors
 *
 * Revision 1.4  1994/06/29  20:32:20  lk
 * Switched order of loadblock/settile.
 *
 * Revision 1.4  1994/06/10  20:08:44  howardc
 * added multigen note
 *
 * Revision 1.3  1994/06/08  23:22:13  lk
 * Re-wrote to keep data structure in memory.
 *
 */

/*
 * Revision 1.19  1995/02/08  19:53:42  rww
 * Added feature to keep normals if no lights are on.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

/* temp (old) material definition: */
typedef struct {
    unsigned char       amb[4];	/* ambient reflectivity value (rgba) */
    unsigned char       diff[4]; /* ambient reflectivity value (rgba) */
    unsigned char       spec[4]; /* ambient reflectivity value (rgba) */
    unsigned char       shiny;	/* phong power. 0-127 */
    unsigned char       rolloff; /* transparency roll-off */
    char                flag;	/* to be used later */
    char                pad;
} Material_t;

typedef union {
    Material_t          m;
    long long int       force_structure_alignment;
} Material;


#include "flt2c.h"
#include "readtex.h"

/*
 * Maximum number of textures we load/keep track of.  This should probably
 * be much bigger or dynamic.
 */

#define MAXTEX		1024

/*
 * Set ONLYSUBFACE to 1 if you only want to draw polygons that are subfaces
 * of other polygons.  This is useful when debugging to find out where
 * your textured polygons went.
 */

#define ONLYSUBFACE	0

/*
 * Set TRUNCTEX to 1 to truncate texture coordinates to 0..1.
 */

#define TRUNCTEX	0

/*
 * List of op-code names to help in debugging.
 */

char *opcode_name[] = {
	"0",
	"Header",
	"Group",
	"* Level of detail",
	"Object",
	"Polygon",
	"* Vertex with ID",
	"* Short vertex",
	"* Vertex with color",
	"* Vertex with color and normal",
	"Push level",
	"Pop level",
	"* Translate",
	"* Degree of freedom",
	"Degree of freedom",
	"15",
	"Local instance record",
	"Local instance bead",
	"18",
	"Push subface",
	"Pop subface",
	"21",
	"22",
	"23",
	"24",
	"25",
	"26",
	"27",
	"28",
	"29",
	"30",
	"Text comment",
	"Color table",
	"33",
	"34",
	"35",
	"36",
	"37",
	"38",
	"39",
	"* Translate",
	"* Rotate about point transform",
	"* Rotate about edge transform",
	"* Scale transform",
	"* Translate transform",
	"* Scale transform with independent XYZ",
	"* Rotate about point transform",
	"* Rotate/Scale to point transform",
	"* Put transform",
	"Transformation matrix",
	"Vector",
	"* Bounding box",
	"52",
	"53",
	"54",
	"55",
	"56",
	"57",
	"58",
	"59",
	"Replicate",
	"Local instance",
	"Local instance library",
	"External reference",
	"Texture reference record",
	"65",
	"Material table",
	"Shared vertex table",
	"Vertex coordinate",
	"Vertex with normal",
	"Vertex with normal and UV",
	"Vertex with UV",
	"Vertex list",
	"Level of detail",
	"Bounding box",
	"75",
	"Rotate about edge transform",
	"Scale transform",
	"Translate transform",
	"Scale with independent XYZ scale",
	"Rotate about point transform",
	"Rotate and/or scale transform",
	"Put transform",
	"Eyepoint record",
	"84",
	"85",
	"86",
	"Road record",
	"Morphing vertex list",
	"89",
	"Linkage record",
	"Sound bead",
	"Sound palette",
	"93",
	"General matrix transform",
	"95",
	"96",
	"97",
	"98",
	"99"
};

typedef struct bead *bead;

struct bead {
	int	opcode, numinst;
	void	*data;
	bead	child, sibling;
};

struct          opColor ColorTable;
struct          opMaterial MaterialTable;

Material_t mat_saved[50];

Material_t mat_default = {
    {  179,  179,  179, 255 },
    {  179,  179,  179,   0 },
    {   51,   51,   51,   0 },
    0,
    255,
    0,
    0
};


struct	opMatHash {
    int mat_id;
    unsigned char FaColor[4];
    int new_mat_id;
    } mat_save_hash[64] ;

int mat_hash_num = 0;
int mat_lookup( int , unsigned char * );

int tex_flags = 0;
int tex_siz = -1;
int tex_fmt = -1;

FILE            *dothFilePointer;
char            dothFileName[1024];
int             CurrentMaterialIndex = 0;
int             LightingCurrentlyOn  = 0;

float		obscale;
struct opVertexNUV center;
struct opVertexNUV eye;
struct opVertexNUV lights[16];

#define MATERIAL_NONE (0xffff)

int		light_num = 0;
int		color_num = 0;
int		flat_shade_flag = 0;
int		specular_flag = 0;
int		texture_flag = 1;
int		texture_index = -1;

int		render_mode = 0;
char		*render_current;
char		*render_normal;
char		*render_decal;

char		*model_name;
int		numtex;
bead		root;
uchar		*buf, *ptr, *end;
ulong		*vtx = NULL;
int		vtxoffset = 0, vtxcount;
int		subface = 0;
struct texture	tex[MAXTEX];
struct opVertexNUV *VertexTable;
int VertexTableMallocCount;
#define VERTEXTABLEMALLOCINCREMENT 100
unsigned char FaceColor[4];

bead loadtree (void)
{
	int		opcode, len, reallen, i;
	struct opBead	*opBead, *opNext;
	bead		*child, root;

	if (ptr >= end) {
		return NULL;
	}

	opBead = (struct opBead *)ptr;
	opcode = opBead->opcode;
	len = opBead->length;

	if (opcode == MG_POP) {
		ptr += len; /* Skip pop */
		return NULL;
	}

	root = (bead)malloc (sizeof (struct bead));
	root->opcode = opcode;
	if (opcode == MG_VTXTABLE) {
		reallen = ((struct opVertexTable *)ptr)->lengthvert;
	} else {
		reallen = len;
	}
	/*
	 * It's necessary to malloc() and memcpy() here instead of just
	 * saying root->data = ptr because we want to make sure that
	 * p->data is double-word aligned, otherwise references to doubles
	 * will bus-error.  The malloc() is guarenteed to be double-word
	 * aligned.
	 */
	root->data = malloc (reallen);
	memcpy (root->data, ptr, reallen);
	root->child = NULL;
	root->sibling = NULL;

	ptr += reallen; /* Skip bead */
	opNext = (struct opBead *)ptr;

	if (opNext->opcode == MG_PUSH) {
		ptr += opNext->length; /* Skip push */
		child = &root->child;
		while ((*child = loadtree ()) != NULL) {
			child = &(*child)->sibling;
		}
	}

	return root;
}

void printtree (bead ptr, int level)
{
	int opcode, len, i;

	if (ptr == NULL) {
		return;
	}

	for (i = 0; i < level; i++) {
		printf ("  ");
	}

	opcode = ptr->opcode;

	printf ("/* %s (%d) */\n", opcode_name[opcode], opcode);

	printtree (ptr->child, level+1);
	printtree (ptr->sibling, level);
}

/*
 * Load a file into memory and parse it into the tree.
 */

void loadfile (char *fn)
{
	bead	*child;
	int	size, inf;

	inf = open (fn, O_RDONLY);
	if (inf == -1) {
		perror (fn);
		exit (1);
	}

	size = lseek (inf, 0, SEEK_END);
	lseek (inf, 0, SEEK_SET);

	buf = (uchar *)malloc (size);
	read (inf, buf, size);
	close (inf);

	end = buf + size;

	child = &root;
	ptr = buf;
	while ((*child = loadtree ()) != NULL) {
		child = &(*child)->sibling;
	}
}

#define MIN( x, y )    (((x) > (y))?(y):(x))
#define MAX( x, y )    (((x) > (y))?(x):(y))

static double min_x, max_x;
static double min_y, max_y;
static double min_z, max_z;

void light_vertex( struct opVertexNUV *, int );
void print_vertex( struct opVertexNUV *, int, double );

void printvtxtable(void)
{
  int i;
  double r;

  fprintf (dothFilePointer, "static Vtx v[] = {\n");
  fprintf (dothFilePointer, "/* %d vertices */ \n", vtxcount);
  for (i=0; i<vtxcount; i++)
    {
	if( light_num > 0 ) {
	    struct opVertexNUV TmpVert;

	    TmpVert = VertexTable[i];

	    light_vertex( &TmpVert, TmpVert.opcode );

	    print_vertex( &TmpVert, i, 255.0 );
	} else 
	    print_vertex( &(VertexTable[i]), i, 127.0 );
    }
  fprintf (dothFilePointer, "};\n\n");

    r = max_x - min_x;
    r = MAX( r, max_y - min_y );
    r = MAX( r, max_z - min_z );

  fprintf (dothFilePointer, 
	  "/*    Center and max_scale with args:  -c %g %g %g  -s %g */\n\n",
		  (max_x + min_x)/2.0,
		  (max_y + min_y)/2.0,
		  (max_z + min_z)/2.0,
		  0xffff/r );
    
  fprintf( stderr,"Center and max_scale with args:  -c %g %g %g  -s %g\n",
		  (max_x + min_x)/2.0,
		  (max_y + min_y)/2.0,
		  (max_z + min_z)/2.0,
		  0xffff/r );
    

}

int
fix_u( double fu , int tx)
{
	int i;

	i = fu * (tx) + 0.5;

	if( i < 0 )
		i = 0;
	else if( i > (tx) )
		i = tx;

	return( i );
}


int
fix_v( double fv , int ty)
{
	int i;

	i = ((ty) - (fv *(ty)) + 0.5);

	if( i < 0 )
		i = 0;
	else if( i > (ty) )
		i = ty;

	return( i );
}

void
light_vertex( struct opVertexNUV *vp, int mat_id )
{
    double r,g,b;
    double norm;
    double diffuse_fact;
    double specular_fact;
    double sqrt(double);
    double pow(double, double);
    double spec_x;
    double spec_y;
    double spec_z;
    double snorm;
    int i;
    Material TempMaterial;

#ifdef DEBUG
    fprintf(stderr," Using Mat %d\n", mat_id );
#endif

    if( mat_id != MATERIAL_NONE )
	TempMaterial.m = mat_saved[mat_id];
    else
	TempMaterial.m = mat_default;

    norm         =  vp->nx * vp->nx +
		    vp->ny * vp->ny +
		    vp->nz * vp->nz;
    norm = sqrt(norm);
    r = TempMaterial.m.amb[0];
    g = TempMaterial.m.amb[1];
    b = TempMaterial.m.amb[2];

    for(i=0; i<light_num; i++) {
	diffuse_fact =  vp->nx * lights[i].x +
			vp->ny * lights[i].y +
			vp->nz * lights[i].z;
	diffuse_fact /= norm;
	if( diffuse_fact < 0 )
	    continue;
	r +=diffuse_fact * TempMaterial.m.diff[0] * lights[i].nx;
	g +=diffuse_fact * TempMaterial.m.diff[1] * lights[i].ny;
	b +=diffuse_fact * TempMaterial.m.diff[2] * lights[i].nz;

	if( specular_flag == 0 )
	    continue;

	spec_x = eye.x + lights[i].x;
	spec_y = eye.y + lights[i].y;
	spec_z = eye.z + lights[i].z;
	snorm = sqrt(spec_x * spec_x + spec_y * spec_y + spec_z * spec_z);

	if( snorm < 0.01 )	/* eye is almost exactly opposite this light */
	    continue;

	specular_fact=  vp->nx * spec_x +
			vp->ny * spec_y +
			vp->nz * spec_z;
	if( specular_fact < 0 )
	    continue;

	specular_fact /=  (snorm * norm);
	specular_fact =pow( specular_fact, (double)TempMaterial.m.shiny);

	r +=specular_fact*TempMaterial.m.spec[0] * lights[i].nx;
	g +=specular_fact*TempMaterial.m.spec[1] * lights[i].ny;
	b +=specular_fact*TempMaterial.m.spec[2] * lights[i].nz;
    };

    r = MIN( r, 255.0 );
    g = MIN( g, 255.0 );
    b = MIN( b, 255.0 );

    vp->nx = r/255.0;
    vp->ny = g/255.0;
    vp->nz = b/255.0;
}

void
print_vertex( struct opVertexNUV *vp, int i, double nv_scale )
{
    static int first=1;
    double x, y, z;
    int nx, ny, nz;

    x = vp->x - center.x;
    y = vp->y - center.y;
    z = vp->z - center.z;

    if( first ) {
	max_x = min_x = x;
	max_y = min_y = y;
	max_z = min_z = z;
	first = 0;
    };


    min_x = MIN( min_x, x );
    min_y = MIN( min_y, y );
    min_z = MIN( min_z, z );

    max_x = MAX( max_x, x );
    max_y = MAX( max_y, y );
    max_z = MAX( max_z, z );

    nx = (int) (x * obscale + 0.5);
    ny = (int) (y * obscale + 0.5);
    nz = (int) (z * obscale + 0.5);

    if( (x > 0x7fff) || (ny > 0x7fff) || (nz > 0x7fff) ||
        (x < -0x7fff) || (ny < -0x7fff) || (nz < -0x7fff) ) {
	fprintf( stderr, "Point(%d) out of range (%g, %g,%g) => (%d,%d,%d)\n",
		i, vp->x, vp->y, vp->z, nx, ny, nz );
    };

	fprintf(dothFilePointer, "\t{ %d, %d, %d, 0, %d<<5, %d<<5, %d, %d, %d, %d },   /* v%d */ \n",
	nx,
	ny,
	nz,
	fix_u(vp->u, vp->tx),
	fix_v(vp->v, vp->ty), /* Flip T for PR */
	0xff & (int)(vp->nx * nv_scale + 0.5),
	0xff & (int)(vp->ny * nv_scale + 0.5),
	0xff & (int)(vp->nz * nv_scale + 0.5), 
	/* Colors, so 0 -> 0 and 1.0 -> 127 */
	/* Need to scale the normals to be unsigned chars, so -1.0 -> 0 and 1.0 -> 255 */
#ifdef OLD_ALPHA
	(unsigned char)(vp->unused), i);   
#else
	255, i);   
#endif

}


void setupvtxtable (uchar *ptr, uchar *end)
{
	struct opBead	*d;
	int		opcode, len;

	while (ptr < end) {
		opcode = ((struct opBead *)ptr)->opcode;
		len = ((struct opBead *)ptr)->length;
		
		if (vtxcount == VertexTableMallocCount)
		  {
		    VertexTableMallocCount += VERTEXTABLEMALLOCINCREMENT;
		    VertexTable = 
		      realloc(VertexTable, 
			      VertexTableMallocCount * sizeof(struct opVertexNUV));
		  }

		VertexTable[vtxcount].opcode = MATERIAL_NONE;
		VertexTable[vtxcount].length = MATERIAL_NONE;
		VertexTable[vtxcount].color  = MATERIAL_NONE;
		VertexTable[vtxcount].flags  = MATERIAL_NONE;

		if (opcode == MG_DVERT_ABS) {
			struct opVertex *d = (struct opVertex *)ptr;

			VertexTable[vtxcount].x  = d->x;
			VertexTable[vtxcount].y  = d->y;
			VertexTable[vtxcount].z  = d->z;
			VertexTable[vtxcount].u  = 0;
			VertexTable[vtxcount].v  = 0;
			VertexTable[vtxcount].nx = 0;
			VertexTable[vtxcount].ny = 0;
			VertexTable[vtxcount].nz = 0;

			vtx[vtxoffset] = vtxcount++;
			vtxoffset += len;
		} else if (opcode == MG_DVERT_NORM) {
			struct opVertexN *d = (struct opVertexN *)ptr;
			float NormalLength;

			VertexTable[vtxcount].x  = d->x;
			VertexTable[vtxcount].y  = d->y;
			VertexTable[vtxcount].z  = d->z;
			VertexTable[vtxcount].u  = 0;
			VertexTable[vtxcount].v  = 0;

			NormalLength = 
			  fsqrt(d->nx * d->nx + d->ny * d->ny + d->nz * d->nz);
			
			VertexTable[vtxcount].nx = d->nx / NormalLength;
			VertexTable[vtxcount].ny = d->ny / NormalLength;
			VertexTable[vtxcount].nz = d->nz / NormalLength;

			vtx[vtxoffset] = vtxcount++;
			vtxoffset += len;
		} else if (opcode == MG_DVERT_ABS_TEX) {
			struct opVertexUV *d = (struct opVertexUV *)ptr;

			VertexTable[vtxcount].x  = d->x;
			VertexTable[vtxcount].y  = d->y;
			VertexTable[vtxcount].z  = d->z;
			VertexTable[vtxcount].u  = d->u;
			VertexTable[vtxcount].v  = d->v;
			VertexTable[vtxcount].nx = 0;
			VertexTable[vtxcount].ny = 0;
			VertexTable[vtxcount].nz = 0;

			vtx[vtxoffset] = vtxcount++;
			vtxoffset += len;
		} else if (opcode == MG_DVERT_NORM_TEX) {
			struct opVertexNUV *d = (struct opVertexNUV *)ptr;
			float NormalLength;
#if TRUNCTEX
			if (d->u > 1) {
				d->u = 1;
			}
			if (d->v > 1) {
				d->v = 1;
			}
			if (d->u < 0) {
				d->u = 0;
			}
			if (d->v < 0) {
				d->v = 0;
			}
#endif
			VertexTable[vtxcount].x  = d->x;
			VertexTable[vtxcount].y  = d->y;
			VertexTable[vtxcount].z  = d->z;
			VertexTable[vtxcount].u  = d->u;
			VertexTable[vtxcount].v  = d->v;

			NormalLength = 
			  fsqrt(d->nx * d->nx + d->ny * d->ny + d->nz * d->nz);			

			VertexTable[vtxcount].nx = d->nx / NormalLength;
			VertexTable[vtxcount].ny = d->ny / NormalLength;
			VertexTable[vtxcount].nz = d->nz / NormalLength;

			vtx[vtxoffset] = vtxcount++;
			vtxoffset += len;
		} else {
			fprintf (stderr, "setupvtxtable(): unknown vertex %d\n",
				opcode);
			exit (1);
		}
		ptr += len;
	}
}

int		mat_id = -1;

int parsetree (bead p, int flag)
{
	static int	polynum, level = 0;
	int		opcode, i, numinst;

	if (p == NULL) {
		return 0;
	}

	numinst = 0;
	opcode = p->opcode;
	if (flag == 0) {
		printf ("/* %s (%d) */\n", opcode_name[opcode], opcode);
	}
	switch (opcode) {
		case MG_HEADER: {
			parsetree (p->child, flag);
			break;
		}
		case MG_COMMENT: {
			struct opComment *d = (struct opComment *)p->data;
			uchar *s;
			int col;

			if (flag == 1) {
				parsetree (p->child, flag);
				break;
			}
			col = 0;
			printf ("/*\n");
			printf (" * Comment:\n");
			for (s = d->comment; *s; s++) {
				if (col == 0) {
					printf (" *   ");
				}
				if ((col > 65 && *s == ' ') || *s == '\n') {
					printf ("\n");
					col = 0;
				} else {
					printf ("%c", *s);
					col++;
				}
			}
			if (col != 0) {
				printf ("\n");
			}
			printf (" */\n\n");
			parsetree (p->child, flag);
			break;
		}
		case MG_COLOR_TABLE: {
 		        /* *d = (struct opColor *)p->data; */
			ColorTable = *(struct opColor *)p->data;

			if (flag == 1) {
				parsetree (p->child, flag);
				break;
			}
			printf ("#if 0\n");
			for (i = 0; i < 32; i++) {
				printf ("\t%d = %d %d %d\n", i,
					ColorTable.brightest[i].red,
					ColorTable.brightest[i].green,
					ColorTable.brightest[i].blue);
			}
			for (i = 0; i < 56; i++) {
				printf ("\t%d = %d %d %d\n", i,
					ColorTable.fixed[i].red,
					ColorTable.fixed[i].green,
					ColorTable.fixed[i].blue);
			}
			printf ("#endif\n\n");
			parsetree (p->child, flag);
			break;
		}
		case MG_MATERIAL_TABLE: {
			/* struct opMaterial *d = (struct opMaterial *)p->data; */
			MaterialTable = *(struct opMaterial *)p->data;

			if (flag == 1) {
				parsetree (p->child, flag);
				break;
			}
			printf ("#if 0\n");
			for (i = 0; i < 64; i++) {
			  printf ("%d: %.2f %.2f %.2f, %.2f %.2f %.2f, %.2f %.2f %.2f, %.2f %.2f %.2f, %.2f %.2f, %d\n", 
				  i,
				  MaterialTable.mat[i].ambient.red,
				  MaterialTable.mat[i].ambient.green,
				  MaterialTable.mat[i].ambient.blue,
				  MaterialTable.mat[i].diffuse.red,
				  MaterialTable.mat[i].diffuse.green,
				  MaterialTable.mat[i].diffuse.blue,
				  MaterialTable.mat[i].specular.red,
				  MaterialTable.mat[i].specular.green,
				  MaterialTable.mat[i].specular.blue,
				  MaterialTable.mat[i].emissive.red,
				  MaterialTable.mat[i].emissive.green,
				  MaterialTable.mat[i].emissive.blue,
				  MaterialTable.mat[i].shininess,
				  MaterialTable.mat[i].alpha,
				  MaterialTable.mat[i].flags & 1); 
			}
			printf ("#endif\n\n"); 
			parsetree (p->child, flag);
			break;
		}
		case MG_TEXTURE_REF: {
			struct opTexture *d = (struct opTexture *)p->data;
			uchar *fn;
			char path[256];

			if (flag == 1) {
				parsetree (p->child, flag);
				break;
			}
			printf ("/*\n");
			printf (" * Texture:\n");
			printf (" *   name = %s\n", d->name);
			printf (" *   index = %d\n", d->index);
			printf (" *   x = %d\n", d->x);
			printf (" *   y = %d\n", d->y);

			/* For now, strip path: */

			fn = strrchr (d->name, '/');
			if (fn == NULL) {
				fn = d->name;
			} else {
				fn++;
			}

			strcpy (path, "Textures/");
			strcat (path, fn);

			tex[numtex].index = d->index;
			sprintf (tex[numtex].name, "tex_%d", d->index);
			if (readtex (path, &tex[numtex], tex_fmt, tex_siz, 1,
					0, 0, 0, 255, 255, 255, C, tex_flags, 0)) {
				numtex++;
			}
			parsetree (p->child, flag);

			break;
		}
		case MG_VTXTABLE: {
			struct opVertexTable *d =
				(struct opVertexTable *)p->data;
			uchar	*ptr, *end;

			if (flag == 1) {
				parsetree (p->child, flag);
				break;
			}
			vtx = (ulong *)malloc (d->lengthvert * sizeof (ulong));
			vtxcount = 0;
			vtxoffset = d->length;
			ptr = (uchar *)p->data + d->length;
			end = (uchar *)p->data + d->lengthvert;
			setupvtxtable (ptr, end);
			/* Child of VTXTABLE is usually geometry: */
			parsetree (p->child, flag);
			break;
		}
		case MG_PUSH_SF: {
			subface = 1;
			parsetree (p->child, flag);
			break;
		}
		case MG_POP_SF: {
			subface = 0;
			parsetree (p->child, flag);
			break;
		}
		case MG_GROUP: {
			struct opGroup *d = (struct opGroup *)p->data;

			if (flag == 1) {
				printf ("\tgsSPDisplayList (grp_%s),\n",
					d->id);
				numinst++;
				break;
			}
			parsetree (p->child, 0);
			printf ("/*\n");
			printf (" * Group:\n");
			printf (" *   Id = %s\n", d->id);
			printf (" *   Flags = 0x%x\n", d->flags);
			printf (" *   Priority = %d\n", d->priority);
			printf (" *   Special effect 1 = %d\n", d->effect1);
			printf (" *   Special effect 2 = %d\n", d->effect2);
			printf (" *   Significance = %d\n", d->significance);
			printf (" */\n\n");
			printf ("static Gfx grp_%s[] = {\n", d->id);
			p->numinst = parsetree (p->child, 1);
			printf ("\tgsSPEndDisplayList(),\n");
			numinst++;

			printf ("};\n\n");
			break;
		}
		case MG_LODFLOAT: {
			struct opLODFloat *d = (struct opLODFloat *)p->data;

			if (flag == 1) {
				printf ("\tgsSPDisplayList (lod_%s),\n",
					d->id);
				numinst++;
				break;
			}
			parsetree (p->child, 0);
			printf ("/*\n");
			printf (" * LOD Float:\n");
			printf (" *   Id = %s\n", d->id);
			printf (" *   Switch in dist = %g\n", d->switchin);
			printf (" *   Switch out dist = %g\n", d->switchout);
			printf (" *   Special effect 1 = %d\n", d->effect1);
			printf (" *   Special effect 2 = %d\n", d->effect2);
			printf (" *   Flags = 0x%x\n", d->flags);
			printf (" *   Center = %g %g %g\n", d->x, d->y, d->z);
			printf (" *   Transition range = %g\n", d->morph);
			printf (" */\n\n");
			printf ("static Gfx lod_%s[] = {\n", d->id);
			p->numinst = parsetree (p->child, 1);
			printf ("\tgsSPEndDisplayList(),\n");
			numinst++;

			printf ("};\n\n");
			break;
		}
		case MG_OBJECT: {
			struct opObject *d = (struct opObject *)p->data;

			if (flag == 1) {
				printf ("\tgsSPDisplayList (obj_%s),\n",
					d->id);
				numinst++;
				break;
			}
			printf ("/*\n");
			printf (" * Object:\n");
			printf (" *   Id = %s\n", d->id);
			printf (" *   Flags = 0x%x\n", d->flags);
			printf (" *   Priority = %d\n", d->priority);
			printf (" *   Transparency = %d\n", d->transparency);
			printf (" *   Special effect 1 = %d\n", d->effect1);
			printf (" *   Special effect 2 = %d\n", d->effect2);
			printf (" *   Significance = %d\n", d->significance);
			printf (" */\n\n");
			polynum = 0;
			printf ("static Gfx obj_%s[] = {\n", d->id);
			/* XXX - possibly remove this: */
			printf ("\tgsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),\n");
			numinst += parsetree (p->child, 0) + 1;

			printf ("\tgsSPEndDisplayList(),\n");
			numinst++;

			printf ("};\n\n");
			p->numinst = numinst;
			break;
		}
		case MG_POLYGON: {
			struct opPolygon *d = (struct opPolygon *)p->data;
			static ushort texture = (ushort)-1;
			int t;

			polynum++;
			printf ("\t/* Polygon #%d (%s) */\n", polynum, d->id);
			if (d->detail != (ushort)-1) {
				printf ("\t/* Detail = %d */\n", (int)d->detail);
			}
			if (d->texture != (ushort)-1) {
				printf ("\t/* Texture = %d */\n",
					(int)d->texture);
			}
			if (texture_flag && (d->texture != texture)) {
				if (d->texture != (ushort)-1) {
					for (t = 0; t < numtex; t++) {
						if (tex[t].index == d->texture) {
							break;
						}
					}
					if (t == numtex) {
						fprintf (stderr,
							"ERROR: Texture %d"
							" not found.\n",
							d->texture);
						exit (1);
					}
					if (render_mode == 1) {
					   if (subface == 0) {
					       printf ("\tgsSPTexture (0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON),\n");
	       /* XXX do the modulate with respect to component */
					       printf ("\tgsDPPipeSync(),\n");
					       render_current = render_normal;
					   }
					   if (subface == 1) {
					       printf ("\tgsSPTextureL (0xffff, 0xffff, 0, 4, G_TX_RENDERTILE, G_ON),\n");
	       /* XXX do the modulate with respect to component */
					       printf ("\tgsDPPipeSync(),\n");
					       render_current = render_decal;
					   }
					   printf ("\tgsDPSetRenderMode(%s, %s2),\n", render_current, render_current);
					}
					printf ("\tgsDPSetCombineMode(G_CC_MODULATE%s, G_CC_MODULATE%s),\n", cmbstr (tex[t].fmt), cmbstr (tex[t].fmt));
					printf ("\tgsDPLoadTextureBlock(%s, %s, %s,\n", tex[t].name, fmtstr (tex[t].fmt), sizstr (tex[t].siz));
					printf ("\t\t%d, %d, 0,\n", tex[t].width, tex[t].height);
					printf ("\t\tG_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,\n");
					printf ("\t\tG_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),\n");
					numinst += 9;
				} else {
					printf ("\tgsSPTexture (0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON),\n");
					printf ("\tgsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),\n");
					numinst += 2;

				}
				texture = d->texture;
				texture_index = t;
			}

			if (d->color1 >= 4096)
			  {
			    FaceColor[0] = (unsigned char) ColorTable.fixed[d->color1-4096].red;
			    FaceColor[1] = (unsigned char) ColorTable.fixed[d->color1-4096].green;
			    FaceColor[2] = (unsigned char) ColorTable.fixed[d->color1-4096].blue;
			  }
			else
			  {
			    int Intensity = (d->color1 & 0x7F);
			    int Index     = (d->color1 >> 7);			     

			    FaceColor[0]  = (int) ((float) ColorTable.brightest[Index].red * 
						   (float) Intensity / 127.0);
			    FaceColor[1]  = (int) ((float) ColorTable.brightest[Index].green * 
						   (float) Intensity / 127.0);
			    FaceColor[2]  = (int) ((float) ColorTable.brightest[Index].blue * 
						   (float) Intensity / 127.0);
			  }						

			if (d->material != (ushort)-1) {
			  /* Compute the material properties in here. Oh Boy(tm) */
			  Material TempMaterial;
			  int i;

			  FaceColor[3] = 
			    (unsigned char) (MaterialTable.mat[(int)d->material].alpha * 
					     (1.0 - (float) d->transparency / (float) 0xffff) * 255.0 + 0.5);

			  mat_id = mat_lookup( (int)d->material, FaceColor );

			  if( mat_id < 0 ) { /* New one! */

			  mat_id = -mat_id;
			  mat_id = mat_id - 1;

			  TempMaterial.m.amb[0] = 
			    (unsigned int) (MaterialTable.mat[(int)d->material].ambient.red   * (float) FaceColor[0] + 0.5);
			  TempMaterial.m.amb[1] = 
			    (unsigned int) (MaterialTable.mat[(int)d->material].ambient.green * (float) FaceColor[1] + 0.5);
			  TempMaterial.m.amb[2] = 
			    (unsigned int) (MaterialTable.mat[(int)d->material].ambient.blue  * (float) FaceColor[2] + 0.5);
			  TempMaterial.m.amb[3] = FaceColor[3];

			  TempMaterial.m.diff[0] = 
			    (unsigned int) (MaterialTable.mat[(int)d->material].diffuse.red   * (float) FaceColor[0] + 0.5);
			  TempMaterial.m.diff[1] = 
			    (unsigned int) (MaterialTable.mat[(int)d->material].diffuse.green * (float) FaceColor[1] + 0.5);
			  TempMaterial.m.diff[2] = 
			    (unsigned int) (MaterialTable.mat[(int)d->material].diffuse.blue  * (float) FaceColor[2] + 0.5);
			  TempMaterial.m.diff[3] = FaceColor[3];

			  TempMaterial.m.spec[0] = 
			    (unsigned int) (MaterialTable.mat[(int)d->material].specular.red   * 255.0 + 0.5);
			  TempMaterial.m.spec[1] = 
			    (unsigned int) (MaterialTable.mat[(int)d->material].specular.green * 255.0 + 0.5);
			  TempMaterial.m.spec[2] = 
			    (unsigned int) (MaterialTable.mat[(int)d->material].specular.blue  * 255.0 + 0.5);
			  TempMaterial.m.spec[3] = FaceColor[3];

			  TempMaterial.m.shiny   = (int) (MaterialTable.mat[(int)d->material].shininess + 0.5);

			  if (TempMaterial.m.shiny == 128)
			    TempMaterial.m.shiny == 127;

			  TempMaterial.m.rolloff = 0;
			  TempMaterial.m.flag    = 0;

 			  /* HAVE TO PRINT THIS CRAP OUT TO A SEPARATE .h FILE*/

#if 0
/* no more Material type */
			  fprintf (dothFilePointer, "{%d,\t%d,\t%d,\t%d,\t /* ambient (mat_id = %d) \n", 
				  TempMaterial.m.amb[0],  TempMaterial.m.amb[1],  TempMaterial.m.amb[2],  TempMaterial.m.amb[3], mat_id);
			  fprintf (dothFilePointer, "%d,\t%d,\t%d,\t%d,\t /* diffuse            */ \n",
				  TempMaterial.m.diff[0], TempMaterial.m.diff[1], TempMaterial.m.diff[2], TempMaterial.m.diff[3]);
			  fprintf (dothFilePointer, "%d,\t%d,\t%d,\t%d,\t /* specular           */ \n",
				   TempMaterial.m.spec[0], TempMaterial.m.spec[1], TempMaterial.m.spec[2], TempMaterial.m.spec[3]);
			  fprintf (dothFilePointer, "%d,\t%d,\t%d,\t0},       /* shininess plus random unused garbage */ \n",
				   TempMaterial.m.shiny ,    TempMaterial.m.rolloff, TempMaterial.m.flag);
#endif

			    mat_saved[mat_id] = TempMaterial.m;
			  } else {
			    TempMaterial.m = mat_saved[mat_id];
			  };

			  printf("/* Specular %d %d %d %d, Shiny %d | Initial %f %f %f, %f*/ \n",
				 TempMaterial.m.spec[0], TempMaterial.m.spec[1], TempMaterial.m.spec[2],
				 TempMaterial.m.spec[3], TempMaterial.m.shiny,
				 MaterialTable.mat[(int)d->material].specular.red,
				 MaterialTable.mat[(int)d->material].specular.green,
				 MaterialTable.mat[(int)d->material].specular.blue,
				 MaterialTable.mat[(int)d->material].shininess);

			  printf ("\t/* Material = %d (mat_id = %d) */\n", (int)d->material, mat_id);			  
			  printf ("\t/* Face intensity = %d, Face Index = %d */ \n", 
				  (d->color1 & 0x7F), (d->color1 >> 7));			  
#ifdef UCODE_LIGHTING
			  printf ("\tgsSPMaterial(material+%d), \n", mat_id);
			  numinst++;
			  if (!LightingCurrentlyOn)
			    {
			      printf("\tgsSPSetGeometryMode (G_LIGHTING),\n");
			      LightingCurrentlyOn = 1;
			      numinst++;
			    }
#endif
			  
			}
			else {
			      /* Compute the material properties in here. Oh Boy(tm) */
			      Material TempMaterial;
			      int i;
			        unsigned int PrimColorInt;

			        printf ("\t/* Material = default (diffuse white) */ \n");
				printf ("\t/* Face intensity = %d, Face Index = %d */ \n", 
					(d->color1 & 0x7F), (d->color1 >> 7));
				printf ("\t/* Face color %d %d %d */ \n", 
					FaceColor[0], FaceColor[1], FaceColor[2]);

				FaceColor[3] = (unsigned char) ((1.0 - (float) d->transparency / (float) 0xffff) * 255.0 + 0.5);

			  mat_id = mat_lookup( (int)d->material, FaceColor );

			  if( mat_id < 0 ) { /* New one! */

			  mat_id = -mat_id;
			  mat_id = mat_id - 1;

			  TempMaterial.m.amb[0] = 
			    (unsigned int) (mat_default.amb[0]/255.0   * (float) FaceColor[0] + 0.5);
			  TempMaterial.m.amb[1] = 
			    (unsigned int) (mat_default.amb[1]/255.0 * (float) FaceColor[1] + 0.5);
			  TempMaterial.m.amb[2] = 
			    (unsigned int) (mat_default.amb[2]/255.0  * (float) FaceColor[2] + 0.5);
			  TempMaterial.m.amb[3] = FaceColor[3];

			  TempMaterial.m.diff[0] = 
			    (unsigned int) (mat_default.diff[0]/255.0   * (float) FaceColor[0] + 0.5);
			  TempMaterial.m.diff[1] = 
			    (unsigned int) (mat_default.diff[1]/255.0 * (float) FaceColor[1] + 0.5);
			  TempMaterial.m.diff[2] = 
			    (unsigned int) (mat_default.diff[2]/255.0  * (float) FaceColor[2] + 0.5);
			  TempMaterial.m.diff[3] = FaceColor[3];

			  TempMaterial.m.spec[0] = 
			    (unsigned int) (mat_default.spec[0]/255.0   * 255.0 + 0.5);
			  TempMaterial.m.spec[1] = 
			    (unsigned int) (mat_default.spec[1]/255.0 * 255.0 + 0.5);
			  TempMaterial.m.spec[2] = 
			    (unsigned int) (mat_default.spec[2]/255.0  * 255.0 + 0.5);
			  TempMaterial.m.spec[3] = FaceColor[3];

			  TempMaterial.m.shiny   = (int) (mat_default.shiny + 0.5);

			  if (TempMaterial.m.shiny >= 128)
			    TempMaterial.m.shiny == 127;

			  TempMaterial.m.rolloff = 0;
			  TempMaterial.m.flag    = 0;

 			  /* HAVE TO PRINT THIS CRAP OUT TO A SEPARATE .h FILE*/

#if 0
/* no more Material type */
			  fprintf (stderr, "{%d,\t%d,\t%d,\t%d,\t /* ambient (mat_id = %d) */ \n", 
				  TempMaterial.m.amb[0],  TempMaterial.m.amb[1],  TempMaterial.m.amb[2],  TempMaterial.m.amb[3], mat_id);
			  fprintf (stderr, "%d,\t%d,\t%d,\t%d,\t /* diffuse            */ \n",
				  TempMaterial.m.diff[0], TempMaterial.m.diff[1], TempMaterial.m.diff[2], TempMaterial.m.diff[3]);
			  fprintf (stderr, "%d,\t%d,\t%d,\t%d,\t /* specular           */ \n",
				   TempMaterial.m.spec[0], TempMaterial.m.spec[1], TempMaterial.m.spec[2], TempMaterial.m.spec[3]);
			  fprintf (stderr, "%d,\t%d,\t%d,\t0},       /* shininess plus random unused garbage */ \n",
				   TempMaterial.m.shiny ,    TempMaterial.m.rolloff, TempMaterial.m.flag);
#endif

			    mat_saved[mat_id] = TempMaterial.m;
			  } else {
			    TempMaterial.m = mat_saved[mat_id];
			  };

#ifdef UCODE_LIGHTING
				if (LightingCurrentlyOn)
				  {
			            printf("\tgsSPClearGeometryMode (G_LIGHTING),\n");
				    LightingCurrentlyOn = 0;
				    numinst++;
				  }
#endif
			}
			numinst += parsetree (p->child, 0);
			break;
		}
		case MG_VTXLIST: {
			struct opVertexList *d = (struct opVertexList *)p->data;
			int last, numv;

			numv = (d->length - 4) / 4;
#if ONLYSUBFACE
			if (!subface) {
				numv = 0;
			}
#endif
			if( numv <= 16 ) {

			    for (i = 0; i < numv; i++) {
				if( VertexTable[vtx[d->vertex[i]]].opcode == MATERIAL_NONE ) { 
				    VertexTable[vtx[d->vertex[i]]].opcode = mat_id;
				} else if( VertexTable[vtx[d->vertex[i]]].opcode != mat_id ) {
	    fprintf(stderr,"Vertex %d is already using mat_id %d (new=%d)\n",
		    vtx[d->vertex[i]], VertexTable[vtx[d->vertex[i]]].opcode, mat_id );
    				};

				if( texture_index != -1 ) {
				    VertexTable[vtx[d->vertex[i]]].tx = tex[texture_index].width;
				    VertexTable[vtx[d->vertex[i]]].ty = tex[texture_index].height;
				} else {
				    VertexTable[vtx[d->vertex[i]]].tx = 2;
				    VertexTable[vtx[d->vertex[i]]].ty = 2;
				};


				printf ("\tgsSPVertex(v + %d, 1, %d),\n",
					vtx[d->vertex[i]], i);

				numinst++;

#ifdef SIMPLE_LIGHTING
				if (!LightingCurrentlyOn)
				  {
				    VertexTable[vtx[d->vertex[i]]].nx     =
						(float) FaceColor[0] / 255.0;
				    VertexTable[vtx[d->vertex[i]]].ny     =
						(float) FaceColor[1] / 255.0;
				    VertexTable[vtx[d->vertex[i]]].nz     =
						(float) FaceColor[2] / 255.0;
				    VertexTable[vtx[d->vertex[i]]].unused =
						(int) FaceColor[3];
				  }
#endif
			    };

			    printf ("/* %d */\n", numinst);

			    last = 1;
			    for (i = 2; i < numv; i++) {
				printf ("\tgsSP1Triangle(0, %d, %d, 0),\n",
					last, i );
				numinst++;
				last = i;
			    };

			    printf ("/* %d */\n", numinst);

			} else {
			    fprintf(stderr,
				"Too many (%d) VTXs for this polygon!\n",
				numv );

			    last = 1;
			    for (i = 2; i < numv; i++) {
				/* Rewrite this to be more optimal */
				printf ("\tgsSPVertex(v + %d, 1, 0),\n",
					vtx[d->vertex[0]]);

#ifdef SIMPLE_LIGHTING
				if (!LightingCurrentlyOn)
				  {
				    VertexTable[vtx[d->vertex[0]]].nx     = (float) FaceColor[0] / 255.0;
				    VertexTable[vtx[d->vertex[0]]].ny     = (float) FaceColor[1] / 255.0;
				    VertexTable[vtx[d->vertex[0]]].nz     = (float) FaceColor[2] / 255.0;
				    VertexTable[vtx[d->vertex[0]]].unused = (int) FaceColor[3];
				  }
#endif

				printf ("\tgsSPVertex(v + %d, 1, 1),\n",
					vtx[d->vertex[last]]);

#ifdef SIMPLE_LIGHTING
				if (!LightingCurrentlyOn)
				  {
				    VertexTable[vtx[d->vertex[last]]].nx     = (float) FaceColor[0] / 255.0;
				    VertexTable[vtx[d->vertex[last]]].ny     = (float) FaceColor[1] / 255.0;
				    VertexTable[vtx[d->vertex[last]]].nz     = (float) FaceColor[2] / 255.0;
				    VertexTable[vtx[d->vertex[last]]].unused = (int) FaceColor[3];
				  }
#endif

				printf ("\tgsSPVertex(v + %d, 1, 2),\n",
					vtx[d->vertex[i]]);

#ifdef SIMPLE_LIGHTING
				if (!LightingCurrentlyOn)
				  {
				    VertexTable[vtx[d->vertex[i]]].nx     = (float) FaceColor[0] / 255.0;
				    VertexTable[vtx[d->vertex[i]]].ny     = (float) FaceColor[1] / 255.0;
				    VertexTable[vtx[d->vertex[i]]].nz     = (float) FaceColor[2] / 255.0;
				    VertexTable[vtx[d->vertex[i]]].unused = (int) FaceColor[3];
				  }
#endif

				printf ("\tgsSP1Triangle(0, 1, 2, 0),\n");
				numinst += 4;
				printf ("/* %d */\n", numinst);
				last = i;

			    };
			}

			break;
		}
		default: {
			printf ("/* UNSUPPORTED opcode: %s */\n",
				opcode_name[opcode]);
			numinst += parsetree (p->child, flag);
		}
	}

	numinst += parsetree (p->sibling, flag);

	return numinst;
}


int
mat_lookup( int id, unsigned char *fc )
{
    int i;

    for(i=0; i<mat_hash_num; i++ )
	if( (mat_save_hash[i].mat_id == id) &&
	    (mat_save_hash[i].FaColor[0]  == fc[0]) &&
	    (mat_save_hash[i].FaColor[1]  == fc[1]) &&
	    (mat_save_hash[i].FaColor[2]  == fc[2]) &&
	    (mat_save_hash[i].FaColor[3]  == fc[3]) )
	    return(i);
    
    mat_save_hash[i].mat_id = id;
    mat_save_hash[i].FaColor[0]  = fc[0];
    mat_save_hash[i].FaColor[1]  = fc[1];
    mat_save_hash[i].FaColor[2]  = fc[2];
    mat_save_hash[i].FaColor[3]  = fc[3];
    mat_hash_num++;
    return( -(i+1) );
}


void usage (void)
{
	fprintf (stderr, "Usage:  flt2c [options] filename\n\n");
	fprintf (stderr, "options:  -m name    Name the model (defaults to \"model\")\n");
	fprintf (stderr, "          -f         Flat shading per polygon\n");
	fprintf (stderr, "          -F         Flip texture\n");
	fprintf (stderr, "          -3         Use 32-bit RGBA textures\n");
	fprintf (stderr, "          -P         Pad odd sized textures correctly\n");
	fprintf (stderr, "          -t         Turn off texturing\n");
	fprintf (stderr, "          -c x,y,z   Move (x,y,z) point to (0,0,0)\n");
	fprintf (stderr, "          -s scale   Scale model by <scale> (after centering)\n");
	fprintf (stderr, "          -L x,y,z   Light source in (x,y,z) direction\n");
	fprintf (stderr, "          -C r,g,b   Color Light source (r,g,b)\n");
	fprintf (stderr, "          -r rn,rd   SetRenderMode arguments for normal, decal texturing\n");
	exit (1);
}

void openMaterialFile(void)
{
  sprintf(dothFileName, "%s.h", model_name);
  dothFilePointer = fopen (dothFileName, "w");  
#if 0
/* no more Material type */
  fprintf (dothFilePointer, "Material material[] = { \n");
#endif
}

int main (int argc, char *argv[])
{
	int		c;
	extern int	optind;
	extern char	*optarg;
	struct opVertexNUV tv;
	double norm, sqrt(double);

	obscale = 1;
	numtex = 0;
	light_num = 0;
	color_num = 0;
	
	VertexTable = malloc(VERTEXTABLEMALLOCINCREMENT * sizeof(struct opVertexNUV));
	VertexTableMallocCount = VERTEXTABLEMALLOCINCREMENT;

	model_name = "model";	

	while ((c = getopt (argc, argv, "E:L:C:c:s:m:r:ftFP3")) != EOF) {
		switch (c) {
			case 'L': /* Light Position Direction */
				tv.x = atof (optarg);
				tv.y = atof (argv[optind++]);
				tv.z = atof (argv[optind++]);
				norm = sqrt( tv.x * tv.x +
					     tv.y * tv.y +
					     tv.z * tv.z );
				lights[light_num].x = tv.x / norm;
				lights[light_num].y = tv.y / norm;
				lights[light_num].z = tv.z / norm;
				fprintf (stderr, "Light[%d] = (%g,%g,%g)\n",
					light_num, lights[light_num].x,
						   lights[light_num].y,
						   lights[light_num].z );
				light_num++;
				break;
			case 'C': /* Color of Light Source */
				lights[color_num].nx = atof (optarg);
				lights[color_num].ny = atof (argv[optind++]);
				lights[color_num].nz = atof (argv[optind++]);
				fprintf (stderr, "Color[%d] = (%g,%g,%g)\n",
					color_num, lights[color_num].nx,
						   lights[color_num].ny,
						   lights[color_num].nz );
				color_num++;
				break;
			case 'E': /* Eye Direction (for Specular Calc) */
				eye.x = atof (optarg);
				eye.y = atof (argv[optind++]);
				eye.z = atof (argv[optind++]);
				norm = sqrt( eye.x * eye.x +
					     eye.y * eye.y +
					     eye.z * eye.z );
				eye.x /= norm;
				eye.y /= norm;
				eye.z /= norm;
				fprintf (stderr, "Eye = (%g,%g,%g)\n",
					eye.x, eye.y, eye.z );
				specular_flag = 1;
				break;
			case 'c': /* Center of object (Move it to origin) */
				center.x = atof (optarg);
				center.y = atof (argv[optind++]);
				center.z = atof (argv[optind++]);
				fprintf (stderr, "Center = (%g,%g,%g)\n",
					center.x, center.y, center.z );
				break;
			case 's':
				obscale = atof (optarg);
				if (obscale == 0) {
					usage ();
				}
				break;
			case 'm':
				model_name = optarg;
				break;
			case 'r':
				render_normal = optarg;
				render_current = optarg;
				render_decal = argv[optind++];
				render_mode = 1;
				break;
			case 'F':
				tex_flags ^= FLIP_FLAG;
				break;
			case 'P':
				tex_flags ^= PAD_FLAG;
				break;
			case '3':
				tex_siz = 32;
				tex_fmt = RGBA;
				break;
			case 'f':
				flat_shade_flag = 1;
				break;
			case 't':
				texture_flag ^= 1;
				break;
			case '?':
				usage ();
				break;
			default:
				fprintf (stderr, "Bug in getopt <%c>\n", c );
				break;
		}
	}
	fprintf (stderr, "Doing %s\n", model_name);

	if( color_num != light_num ) {
	    fprintf (stderr, "Number of lights and color of lights is wrong (%d != %d)\n", light_num, color_num );
	    if( color_num < light_num )
		light_num = color_num;
	    else
		color_num = light_num;
	    usage ();
	};

	if (optind == argc) {
		usage ();
	}

	openMaterialFile();
	loadfile (argv[optind]);

	printf ("\n");
	printf ("/*\n");
	printf (" * Do not edit this file.  It was automatically generated\n");
	printf (" * by \"flt2c\" from the file \"%s\".\n", argv[optind]);
	printf (" */\n");
	printf ("\n");
	printf ("#include <mbi.h>\n");
	printf ("#include <%s>\n\n", dothFileName);

	/* printtree (root, 0); */

	parsetree (root, 0);
	printf ("Gfx %s[] = {\n", model_name);
	parsetree (root, 1);
	printf ("\tgsSPEndDisplayList(),\n");
	printf ("};\n\n");

	free (buf);

#if 0
/* no more Material type */
	fprintf (dothFilePointer, "}; \n\n");
#endif
	printvtxtable();
	fclose(dothFilePointer);
}

