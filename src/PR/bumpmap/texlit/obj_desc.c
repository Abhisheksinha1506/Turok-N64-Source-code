
#include <stdio.h>

#include "vert.h"

#include "obj.h"

extern Vertex vertex_table[];

#define LUT1		{	\
	{ 255 },		\
	0,			\
	240,			\
	&(vertex_table[0]) }

#define MATERIAL1	{	\
	LUT1,			\
	128, 128, 128,		\
	(sizeof(bumps1)/sizeof(bumps1[0])), \
	&(bumps1[0]) }

signed char crater_profile[] = { 
    -50, -12, -6, 0, 0,	0,		/* Center peak to flat base */
    0, 0, 0, 3, 5, 10, 20, 40, 80, 127,	/* flat base  to rim */
    -50, -20, -10, -5, -2, 0		/* outer rim  */
};

objBumpShape crater_bump = {
    sizeof( crater_profile ), 1, 1,

    (unsigned char *)( &(crater_profile[0]) )
};

#define BNOISE1 (0.15)

static objBump bumps1[] = {

    { BUMP_RADIAL,
      { 0.2, -0.6, -1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, -1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.9, 0.1, -1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.5, -0.15, -1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.2, -0.6, 1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, 1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.1, 0.9, 1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 1.0, 0.15, 1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },


    { BUMP_RADIAL,
      { 0.2, -0.6, -1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, -1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.9, 0.1, -1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.5, -0.15, -1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.2, -0.6, 1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, 1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.1, 0.9, 1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 1.0, 0.15, 1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },


    { BUMP_RADIAL,
      { 0.2, -0.6, -1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, -1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.9, 0.1, -1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.5, -0.15, -1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.2, -0.6, 1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, 1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.1, 0.9, 1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 1.0, 0.15, 1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },


    { BUMP_RADIAL,
      { 0.2, -0.6, -1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, -1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.9, 0.1, -1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.5, -0.15, -1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.2, -0.6, 1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, 1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.1, 0.9, 1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 1.0, 0.15, 1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },


    { BUMP_RADIAL,
      { 0.2, -0.6, -1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, -1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.9, 0.1, -1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.5, -0.15, -1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.2, -0.6, 1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, 1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.1, 0.9, 1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 1.0, 0.15, 1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },


    { BUMP_RADIAL,
      { 0.2, -0.6, -1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, -1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.9, 0.1, -1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.5, -0.15, -1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.2, -0.6, 1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, 1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.1, 0.9, 1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 1.0, 0.15, 1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },


    { BUMP_RADIAL,
      { 0.2, -0.6, -1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, -1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.9, 0.1, -1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.5, -0.15, -1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.2, -0.6, 1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, 1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.1, 0.9, 1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 1.0, 0.15, 1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },


    { BUMP_RADIAL,
      { 0.2, -0.6, -1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, -1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.9, 0.1, -1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.5, -0.15, -1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.2, -0.6, 1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, 1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.1, 0.9, 1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 1.0, 0.15, 1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },


    { BUMP_RADIAL,
      { 0.2, -0.6, -1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, -1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.9, 0.1, -1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.5, -0.15, -1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.2, -0.6, 1.0 },
      { 0.01, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.8, -0.3, 1.0 },
      { 0.015, 0.0, 0.1 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 0.1, 0.9, 1.0 },
      { 0.02, 0.0, 0.25 },
      &(crater_bump) },

    { BUMP_RADIAL,
      { 1.0, 0.15, 1.0 },
      { 0.025, 0.0, 0.3 },
      &(crater_bump) },

    { BUMP_UNOISE,
      { 0.0, 0.0, 0.0 },
      { BNOISE1, BNOISE1, BNOISE1 },
      NULL },
};

static objVert verts1[] = {
#include "b240_vs.h"
};


static int faces1[][3] = {
#include "b240_fs.h"
};

Object obj1 = {
    MATERIAL1,

    { 0.0, 0.0, 0.0 },			/* center */
    0.0, 0.0, 0.0,			/* rotations x,y,z */

    sizeof( verts1 )/ sizeof(objVert),
    &(verts1[0]),

    sizeof( faces1 )/(3*sizeof(int)),
    &(faces1[0][0])

};

static objVert verts2[] = {
    { {  0.0,  1.0,  0.0 },
      {  0.0,  1.0, -1.0 },
      255, 255, 255 },

    { {  1.0,  0.0,  0.0 },
      {  1.0,  0.0, -1.0 },
      255, 255, 255 },

    { {  0.0, -1.0,  0.0 },
      {  0.0, -1.0, -1.0 },
      255, 255, 255 },

    { { -1.0,  0.0,  0.0 },
      { -1.0,  0.0, -1.0 },
      255, 255, 255 },

    { {  0.0, 0.0,  0.0 },
      {  0.0, 0.0, -1.0 },
      255, 255, 255 },

};

Object obj2 = {
    MATERIAL1,

    { 1.0, 1.0, 1.0 },			/* center */
    0.0, 0.0, 0.0,			/* rotations x,y,z */

    sizeof( verts1 )/ sizeof(objVert),
    &(verts2[0]),

    sizeof( faces1 )/(3*sizeof(int)),
    &(faces1[0][0])

};

