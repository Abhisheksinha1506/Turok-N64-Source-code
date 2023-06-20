/*
 * NOTICE: This source code includes data structures for the MultiGen Flight
 * Format which is the proprietary property of MultiGen Inc.  It is furnished
 * here under a license to Silicon Graphics and Nintendo soley for use in this
 * program.  If you wish to use the Flight Format for any other purpose, a no
 * charge license is noramlly available; contact MultiGen Inc. at
 * 408-247-4326.
 */

/*
 * These codes are stolen from Performer's loader:
 */

/*
 * Multigen opcodes
 */

#define MG_HEADER               1
#define MG_GROUP                2
#define MG_LOD                  3
#define MG_OBJECT               4
#define MG_POLYGON              5
#define MG_VERT_ABS             7
#define MG_VERT_SHAD            8
#define MG_VERT_NORM            9
#define MG_PUSH                 10
#define MG_POP                  11
#define MG_DOF                  13
#define MG_DOFFLOAT             14
#define MG_PUSH_SF              19
#define MG_POP_SF               20
#define MG_COMMENT              31
#define MG_COLOR_TABLE          32

/* opcodes 40-48 are other transformation record types */
#define MG_MATRIX               49
#define MG_VECTOR               50
#define MG_BBOX                 51
#define MG_REPLICATE            60
#define MG_INSTANCE_REF         61
#define MG_INSTANCE_DEF         62
#define MG_EXTERNAL_REF         63
#define MG_TEXTURE_REF          64
#define MG_EYEPOINTS            65
#define MG_MATERIAL_TABLE       66
#define MG_VTXTABLE             67
#define MG_DVERT_ABS            68
#define MG_DVERT_NORM           69
#define MG_DVERT_NORM_TEX       70
#define MG_DVERT_ABS_TEX        71
#define MG_VTXLIST              72
#define MG_LODFLOAT             73


/*typedef unsigned long		ulong;
typedef unsigned short		ushort;*/
typedef unsigned char		uchar;

struct color {
	ushort		red;
	ushort		green;
	ushort		blue;
};

struct fcolor {
	float		red;
	float		green;
	float		blue;
};

struct material {
	struct fcolor	ambient;
	struct fcolor	diffuse;
	struct fcolor	specular;
	struct fcolor	emissive;
	float		shininess;
	float		alpha;  /* 1 = opaque */
	ulong		flags;
	int		spare[31];
};

struct opBead {
	ushort		opcode;
	ushort		length;
};

struct opColor {
	ushort		opcode;
	ushort		length;
	struct color	brightest[32];
	struct color	fixed[56];
};

struct opVertexTable {
	ushort		opcode;
	ushort		length;
	ulong		lengthvert;
};

struct opVertex {
	ushort		opcode;
	ushort		length;
	ushort		color;
	ushort		flags;
	double		x;
	double		y;
	double		z;
};

struct opVertexN {
	ushort		opcode;
	ushort		length;
	ushort		color;
	ushort		flags;
	double		x;
	double		y;
	double		z;
	float		nx;
	float		ny;
	float		nz;
	int		unused;
};

struct opVertexUV {
	ushort		opcode;
	ushort		length;
	ushort		color;
	ushort		flags;
	double		x;
	double		y;
	double		z;
	float		u;
	float		v;
};

struct opVertexNUV {
	ushort		opcode;
	ushort		length;
	ushort		color;
	ushort		flags;
	double		x;
	double		y;
	double		z;
	float		nx;
	float		ny;
	float		nz;
	float		u;
	float		v;
	int		unused;  /* unused in .flt, but used in flt2c to store 
                                    an alpha value */
	int		tx;	/* texture X dimension	*/
	int		ty;	/* texture Y dimension	*/
};

struct opVertexList {
	ushort		opcode;
	ushort		length;
	ulong		vertex[64];
};

struct opObject {
	ushort		opcode;
	ushort		oplength;
	uchar		id[8];
	ulong		flags;
	ushort		priority;
	ushort		transparency;
	ushort		effect1;
	ushort		effect2;
	ushort		significance;
	ushort		spare;
};

struct opGroup {
	ushort		opcode;
	ushort		oplength;
	uchar		id[8];
	ushort		priority;
	ushort		dummy;  /* For alignment */
	ulong		flags;
	ushort		effect1;
	ushort		effect2;
	ushort		significance;
	ushort		spare;
};

struct opPolygon {
	ushort		opcode;
	ushort		oplength;
	uchar		id[8];
	ulong		IRcolor;
	ushort		priority;
	uchar		flags;
	uchar		texwhite;
	ushort		color1;
	ushort		color2;
	uchar		unused;
	uchar		transparency_flags;
	ushort		detail;
	ushort		texture;
	ushort		material;
	ushort		surface;
	ushort		feature;
	ulong		IRmaterial;
	ushort		transparency;
	uchar		LOD;
	uchar		spare;
};

struct opLODFloat {
	ushort		opcode;
	ushort		oplength;
	uchar		id[8];
	ulong		spare;
	double		switchin;
	double		switchout;
	ushort		effect1;
	ushort		effect2;
	ulong		flags;
	double		x;
	double		y;
	double		z;
	double		morph;
};

struct opTexture {
	ushort		opcode;
	ushort		oplength;
	uchar		name[80];
	ulong		index;
	ulong		x;
	ulong		y;
};

struct opComment {
	ushort		opcode;
	ushort		oplength;
	uchar		comment[1]; /* Variable */
};

struct opMaterial {
	ushort		opcode;
	ushort		oplength;
	struct material	mat[64];
};
