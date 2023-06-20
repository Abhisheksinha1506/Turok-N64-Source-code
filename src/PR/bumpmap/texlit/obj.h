/*	Object description Structure definitions *
/* Rich Wedd 25jul95 */

#define BUMP_NONE	(0)
#define BUMP_UNOISE	(1)		/* Uniform random [0.0...1.0) */
#define BUMP_DNOISE	(2)		/* [0.0...1.0)^3 */
#define BUMP_NORM_TEX	(3)		/* Normal Texture (r,g,b) => (nlat,nlong,nheight) */
#define BUMP_ELEV_TEX	(4)		/* Typical Bump map (elevation) */
#define BUMP_RADIAL	(5)		/* Radial Profile: (cos(theta),elev) pairs */

typedef unsigned char u8;

typedef struct obj_bumpshape_struct {
	int		xdim;
	int		ydim;
	int		zdim;

	u8		*data;
    } objBumpShape;

typedef struct obj_lookup_table_struct {
	unsigned short	table[256];		/* Colors are stored RGBA 5:5:5:1 */
	int		start_indx;

	int		ndirs;
	Vertex		*dirs;
    } objLUT;

typedef struct obj_bump_struct {
	int		type;			/* What type of bump is this */

	Vertex		direction;
	Vertex		scale;			/* How to scale the basic shape */
						/* (x,y,z) => (s,t,depth) */

	objBumpShape	*shape;
    } objBump;

typedef struct obj_material_struct {
	objLUT		lut;			/* Computed Look-up Table */

	u8		red, green, blue;	/* Basic Material Color */
						/* Used for lighting calc. */

	int 		nbumps;
	objBump		*bumps;
    } objMaterial;

typedef struct obj_vertex_struct {
	Vertex		vert;
	Vertex		normal;
	u8		red, green, blue;	/* Basic Vertex Color */
    } objVert;

typedef struct object_struct {
	objMaterial	mat;
	Vertex		center;
	float		xrot,
			yrot,
			zrot;
	
	int nverts;
	objVert		*verts;
	
	int nfaces;
	int		*faces;			/* triples of vertex indecies */
    } Object;


