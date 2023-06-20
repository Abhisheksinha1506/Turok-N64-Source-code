
/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1994, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

/*
 * File:	static.c
 * Creator:	hsa@sgi.com
 * Create Date:	Fri Oct 14 11:53:47 PDT 1994
 *
 *
 * This file holds tiny display list segments that are 'static' data.
 * If you feel the urge to modify a test, see the comment at
 * the top of main.c for details.
 *
 */

#include <ultra64.h>
#include "dldriver.h"
#include "rdpew.h"
#include "cs.h"


/*
 * Test conventions:
 *
 * Data variable names can be about anything, as long as they are unique
 * and consistent in the table entry.
 *
 * In order to get around compiler weirdness, the table of tests
 * is in rdpverif.c, and the Gfx rdpew_lists must be extern'd in rdpverif.h
 *
 * Your test case display list must end with gsSPEndDisplayList(),
 * otherwise there are length hassles.
 *
 * Your test case should set any special mode you want (texture, zbuff,
 * etc.) and also turn it off when you are done, so as not to affect
 * other tests.
 *
 */

/*
 * Test -1, default frame. Used as a placeholder.
 *
 * Simple square (4 triangles), each vertex a different color.
 *
 * Wed Oct  5 22:12:43 PDT 1994
 *
 */
static Vtx place_vtx[5] =  {
        {        -40,  40, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {         40,  40, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         40, -40, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {        -40, -40, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},
        {          0,   0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
};

Gfx rdpew_placebo_dl[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&place_vtx, 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};
/* end of case -1 */

/*
 * Test 0, Frame 0:
 *
 * Simple square (4 triangles), each vertex a different color.
 *
 * Wed Oct  5 22:12:43 PDT 1994
 *
 */
static Vtx q0[5] =  {
        {        -40,  40, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {         40,  40, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         40, -40, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {        -40, -40, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},
        {          0,   0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
};

Gfx rdpew_square0[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&q0, 5, 0),
#if 0
    /* two triangle case: */
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
#endif
    /* four triangle case: */
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};
/* end of case 0 */



/*
 * Test 2, Frame 2:
 *
 * Zbuffered triangles
 *
 */
#define Z1	-200	/* In distance */
#define Z2	-180	/* closer */
/*#define Z1	0 /**/
/*#define Z2	0 /**/

Vtx tris[] = {
/*    x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */
	
    { -40,  34,     Z1, 0,	0,	0,	0xff,	0,	0,	0xff },	  /* R */   
    {  30,   0,	    Z2, 0,	0,	0,	0,	0,	0xff,	0xff },	  /* B */	     
    { -40, -34,     Z1, 0,	0,	0,	0,	0xff,	0,	0xff },	  /* G */
    	     
    {  35,   24,    Z1, 0,	0,	0,	0,	0,	0xff,	0xff },	  /* B */	     
    {  35,  -24,    Z1, 0,	0,	0,	0,	0xff,	0,	0xff },	  /* G */	     
    { -20,   0,	    Z2, 0,	0,	0,	0xff,	0,	0,	0xff },	  /* R */	     
};

Gfx rdpew_triangles[MAX_STATIC_GFX_SIZE] = {
    { gsSPClearGeometryMode(0xffffffff) }, 
    { gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER) }, 
    { gsDPSetRenderMode(G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2) },
    { gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE) },
    { gsSPVertex(&tris, sizeof(tris)/sizeof(tris[0]), 0) },
    { gsSP1Triangle(0, 1, 2, 0) }, 
    { gsSP1Triangle(3, 4, 5, 0) },
    { gsSPEndDisplayList() }
};

Gfx rdpew_fogtriangles[MAX_STATIC_GFX_SIZE] = {
    { gsDPSetFogColor(128, 128, 128, 128) }, 
    { gsDPSetCycleType(G_CYC_2CYCLE) }, 
    { gsSPClearGeometryMode(0xffffffff) }, 
    { gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER) }, 
    { gsDPSetRenderMode(G_RM_FOG_PRIM_A, G_RM_ZB_OPA_SURF2) },
    { gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE) },
    { gsSPVertex(&tris, sizeof(tris)/sizeof(tris[0]), 0) },
    { gsSP1Triangle(0, 1, 2, 0) }, 
    { gsSP1Triangle(3, 4, 5, 0) },
    { gsSPEndDisplayList() }
};
/* end of case 2 */


/*
 * Test 4, Frame 4:
 *
 *
 * Mon Oct 10 1994
 *
 */
Vtx trivtx10[5] =  {
        {        -40,  40, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {         40,  40, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         40, -40, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {        -40, -40, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},
        {          0,   0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
};

Gfx rdpew_triangle4[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&trivtx10, 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};
/* end of case shade_acc2 */

/*
 * Test 5, Frame 5:
 *
 * Simple square (2 triangles), each vertex a different color.
 * Tests accurate integer pixel positioning.
 *
 * Wed Oct 12 11:27:23 PDT 1994
 *
 */
static Vtx q5[5] =  {
        {        120, 160, 0, 0, 0, 0, 0, 0, 0xff, 0xff       },
        {        200, 160, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff },
        {        200,  80, 0, 0, 0, 0, 0, 0xff, 0, 0xff       },
        {        120,  80, 0, 0, 0, 0, 0xff, 0, 0, 0xff       },
        {          0,   0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff },
};

Gfx rdpew_square5[10] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&q5, 5, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};
/* end of case 5 */

/*
 * Test 6, Frame 6:
 *
 * Some degenerate triangles.
 *
 */
static Vtx q6[12] =  {
    /* null triangle, all one point (RED) */
        {        120, 160, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {        120, 160, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {        120, 160, 0, 0, 0, 0, 0xff, 0, 0, 0xff  },

    /* null triangle, all one line (GREEN) */
        {        126, 170, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {        120, 170, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {        120, 170, 0, 0, 0, 0, 0, 0xff, 0, 0xff },

    /* small triangle, (BLUE) */
        {        120, 180, 0, 0, 0, 0, 0, 0, 0xff, 0xff },
        {        121, 180, 0, 0, 0, 0, 0, 0, 0xff, 0xff },
        {        120, 181, 0, 0, 0, 0, 0, 0, 0xff, 0xff },

    /* small triangle, (WHITE) */
        {        120, 190, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff },
        {        122, 190, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff },
        {        120, 192, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff },
};

Gfx rdpew_square6[32] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&q6, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9, 10, 11, 0),
    gsSPEndDisplayList(),
};
/* end of case 6 */


/*
 * Test 7, Frame 7:
 *
 * Test all possible edge-types next to each other:
 *
 *	HH, HM, HL, LM, LL, MM
 *
 * The RED-BLUE diagonal is the joining edge; if this transition
 * isn't smooth, we have a problem with rasterization/attribute
 * adjustments.
 *
 * Thu Oct 13 20:54:49 PDT 1994
 *
 */
static Vtx q7a[12] =  {
    /* high edge next to high edge: */
        {         30,  20, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {         80,  30, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {        100, 100, 0, 0, 0, 0, 0, 0, 0xff, 0xff  },
        {         10,  80, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff  },

    /* high edge next to mid edge: */
        {        120,  20, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {        180,  40, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {        200,  70, 0, 0, 0, 0, 0, 0, 0xff, 0xff  },
        {        130, 110, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff  },

    /* high edge next to low edge: */
        {        220, 100, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {        260,  10, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {        280,  60, 0, 0, 0, 0, 0, 0, 0xff, 0xff  },
        {        310,  80, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff  },
};

/* two groups of vertices, don't overflow points buffer */
static Vtx q7b[12] =  {
    /* low edge next to mid edge: */
        {         40, 200, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {         10, 130, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {         80, 170, 0, 0, 0, 0, 0, 0, 0xff, 0xff  },
        {        100, 230, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff  },

    /* low edge next to low edge: */
        {        150, 230, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {        110, 130, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {        160, 190, 0, 0, 0, 0, 0, 0, 0xff, 0xff  },
        {        200, 140, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff  },

    /* mid edge next to mid edge: */
        {        290, 130, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {        220, 230, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {        270, 200, 0, 0, 0, 0, 0, 0, 0xff, 0xff  },
        {        310, 230, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff  },

};

Gfx rdpew_square7[32] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsSPVertex(&q7a, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(4, 5, 6, 0),
    gsSP1Triangle(4, 6, 7, 0),
    gsSP1Triangle(8, 9, 10, 0),
    gsSP1Triangle(8, 10, 11, 0),

    gsSPVertex(&q7b, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(4, 5, 6, 0),
    gsSP1Triangle(4, 6, 7, 0),
    gsSP1Triangle(8, 9, 10, 0),
    gsSP1Triangle(8, 10, 11, 0),

    gsSPEndDisplayList(),
};
/* end of case 7 */


/*
 * Test 10, Frame 10:
 *
 *
 * Mon Oct 10 1994
 * 
 * A number of triangles which draw off-screen, many with
 * vertices near the 2K boundary of the drawing space.
 * THIS TEST TAKES A WHILE TO RUN
 *
 */

/* 2vtx in, 1vtx out, flat insde edge */
Vtx trivtx10a[12] =  {
        {         20, 112, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         20, 128, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        -20, 120, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300, 112, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        300, 128, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        340, 120, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        168, 220, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        152, 220, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        160, 260, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        168,  20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        152,  20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        160, -20, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* 2vtx in, 1vtx max, flat insde edge */
Vtx trivtx10b[12] =  {
        {         20,  132, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         20,  148, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,  140, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,  132, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        300,  148, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,  140, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        188,  220, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        172,  220, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        180, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        188,   20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        172,   20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        180,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* 2vtx in, 1vtx max, leftmajor top/bot; high out left/right */
Vtx trivtx10c[12] =  {
        {         20,   92, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         30,  108, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,   70, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,   92, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        290,  108, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,   70, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        148,  220, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        132,  210, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        140, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        148,   20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        132,   30, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        140,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* 2vtx in, 1vtx max, rightmajor top/bot; low out left/right */
Vtx trivtx10d[12] =  {
        {         30,  152, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         20,  168, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,  190, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        290,  152, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        300,  168, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,  190, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        208,  210, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        192,  220, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        200, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        208,   30, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        192,   20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        200,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* all in,  like a */
Vtx trivtx10e[12] =  {
        {         60, 112, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         60, 128, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {         45, 120, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        260, 112, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        260, 128, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        280, 120, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        168, 180, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        152, 180, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        160, 200, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        168,  60, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        152,  60, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        160,  45, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* all in,  like b */
Vtx trivtx10f[12] =  {
        {         60, 132, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         60, 148, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {         45, 140, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        260, 132, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        260, 148, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        280, 140, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        188, 180, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        172, 180, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        180, 200, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        188,  60, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        172,  60, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        180,  45, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* all in,  like c */
Vtx trivtx10g[12] =  {
        {         60,  92, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         65, 108, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {         45,  70, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        260,  92, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        255, 108, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        280,  70, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        148, 180, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        132, 170, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        140, 200, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        148,  60, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        132,  70, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        140,  45, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* all in,  like d */
Vtx trivtx10h[12] =  {
        {         65, 152, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         60, 168, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {         45, 190, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        255, 152, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        260, 168, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        280, 190, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        208, 170, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        192, 180, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        200, 200, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        208,  70, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        192,  60, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        200,  45, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* upper corner from sides */
Vtx trivtx10i[12] =  {
        {         30,   88, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         20,   85, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,   88, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        310,   85, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {         30,   52, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         20,   68, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -1045,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,   52, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        310,   68, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       1045,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* lower corner from sides */
Vtx trivtx10j[12] =  {
        {         30,  192, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         20,  195, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,  192, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        310,  195, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {         30,  228, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         20,  212, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -1046, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,  228, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        310,  212, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       1046, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* upped corner from top */
Vtx trivtx10k[12] =  {
        {         82,   20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        108,   25, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,-1044, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        112,   25, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        128,   20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        212,   20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        228,   25, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        232,   25, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        258,   20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,-1044, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* lower corner from bot */
Vtx trivtx10l[12] =  {
        {         82,  220, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        108,  215, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000, 1044, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        112,  215, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        128,  220, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        212,  220, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        228,  215, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        232,  215, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        258,  220, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000, 1044, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};


Gfx rdpew_triangle10[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsDPSetRenderMode(G_RM_AA_OPA_SURF,G_RM_AA_OPA_SURF2),
    gsDPSetRenderMode(0x0C084148,0),





    gsSPVertex(&trivtx10j, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10k, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10l, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10i, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10a, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10b, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10c, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10d, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

/*
    gsSPVertex(&trivtx10e, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10f, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10g, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10h, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),
*/

    gsSPEndDisplayList(),
};
/* end of case 10 */

/*
 * Test 11, Frame 11:
 *
 *
 * Tue Oct 18 1994
 *
 * Draws a number of triangles.  Each triangle has 1 vertex in the
 * screen (in the scissor box) and 2 vertices off screen (near the
 * 2k boundary). 
 * THIS TEST TAKES A WHILE TO RUN 
 *
 */

/* 1vtx in, 2vtx out, flat outside edge */
Vtx trivtx11a[12] =  {
        {         20, 112, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        -20, 128, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        -20, 120, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300, 112, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        340, 128, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        340, 120, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        168, 220, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        152, 260, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        160, 260, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        168,  20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        152, -20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        160, -20, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* 1vtx in, 2vtx max, flat outside edge */
Vtx trivtx11b[12] =  {
        {         60,  132, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      -2000,  148, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,  140, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        260,  132, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {       2000,  148, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,  140, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        188,  180, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        172, 2000, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        180, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        188,   60, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        172,-2000, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        180,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* 1vtx in, 1 out, 1 max, leftmajor top/bot; high out left/right */
Vtx trivtx11c[12] =  {
        {       -800,   92, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         30,  108, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,   70, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {       1120,   92, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        290,  108, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,   70, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        148, 1040, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        132,  210, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        140, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        148, -800, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        132,   30, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        140,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* 1vtx in, 1 out, 1 max, rightmajor top/bot; low out left/right */
Vtx trivtx11d[12] =  {
        {         30,  152, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {       -800,  168, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,  190, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        290,  152, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {       1120,  168, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,  190, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        208,  210, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        192, 1040, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        200, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        208,   30, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        192, -800, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {        200,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* upper corner from sides */
Vtx trivtx11i[12] =  {
        {         30,   88, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      -2000,   85, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,   88, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {       2000,   85, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {         30,   52, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      -2000,-2000, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -1045,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,   52, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {       2000,-2000, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       1045,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* lower corner from sides */
Vtx trivtx11j[12] =  {
        {         30,  192, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      -2000,  195, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,  192, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {       2000,  195, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000, 2044, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {         30,  228, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      -2000, 2000, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -1046, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        300,  228, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {       2000, 2000, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       1046, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* upped corner from top */
Vtx trivtx11k[12] =  {
        {      -2000,-2000, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        108,   25, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,-1044, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        112,   30, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        128,-2000, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        212,-2000, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        228,   30, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        232,   25, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {       2000,-2000, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,-1044, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* lower corner from bot */
Vtx trivtx11l[12] =  {
        {      -2000, 2000, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        108,  215, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000, 1044, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        112,  215, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        128, 2000, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        212, 2000, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {        228,  215, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        232,  215, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {       2000, 2000, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000, 1044, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};


Gfx rdpew_triangle11[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsDPSetRenderMode(0x0C084148,0),

    gsSPVertex(&trivtx11k, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx11j, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx11l, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx11i, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx11a, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx11b, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx11c, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx11d, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),


/*    gsDPSetScissor(G_SC_NON_INTERLACE, 10,10,310,230),
**/

    gsSPEndDisplayList(),
};
/* end of case 11 */

/*
 * Test 12, Frame 12:
 *
 *
 * wed Oct 19 1994
 *
 * Draws some triangles with all 3 vertices near the 2K
 * drawing boundary (opposite boundaries so the triangles 
 * are visible on the screen) and some with one vertex
 * inthe screen and 2 vertices at opposite 2K boundaries
 * (so they are vivible on screen).
 *
 */

/* all out, edge to edge */
Vtx trivtx12a[12] =  {
        {      -2000,   10, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      -2000,   30, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {       2000,   20, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {       2000,   40, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {       2000,   60, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,   50, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {         10,-2000, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         30,-2000, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {         20, 2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {         40, 2000, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         60, 2000, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {         50,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* 2 out edge to edge */
Vtx trivtx12b[12] =  {
        {        160,   70, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {       2000,   80, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,   80, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        160,  100, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {       2000,   90, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,   90, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {         70,  120, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         80, 2000, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {         80,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        100,  120, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {         90, 2000, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {         90,-2000, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* 2 out edge to edge */
Vtx trivtx12c[6] =  {
        {        160,  150, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {       2000,  160, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,  170, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {        160,  180, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {       2000,  200, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      -2000,  190, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

Gfx rdpew_triangle12[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsDPSetRenderMode(0x0C084148,0),

    gsSPVertex(&trivtx12a, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx12b, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx12c, 6, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),

    gsSPEndDisplayList(),
};
/* end of case 12 */

/*
 * Test 13, Frame 13:
 *
 *
 * wed Oct 19 1994
 * Scissoring - uses data from test 10
 *
 * The same triangles as in test 10 but with a scissor box
 * which removes about 10 pixels from around the edge of the screen
 *
 */
Gfx rdpew_triangle13[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsDPSetRenderMode(0x0C084148,0),

    gsDPSetScissor(G_SC_NON_INTERLACE, 10,10,310,230),

    gsSPVertex(&trivtx10j, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10k, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10l, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10i, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10a, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10b, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10c, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10d, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPEndDisplayList(),
};
/* end of case 13 */

/*
 * Test 14, Frame 14:
 *
 *
 * wed Oct 19 1994
 * 640x480 screensize (uses data from test 10)
 *
 * Draws the triangles from test 10 but on a bigger screen.
 * to use this test with the RDP CSIM use the options:
 *    -W 640 -H 480
 *
 */
Gfx rdpew_triangle14[MAX_STATIC_GFX_SIZE] = {
    gsSPVertex(&trivtx10j, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10k, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10l, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10i, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10a, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10b, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10c, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10d, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPEndDisplayList(),
};

extern Gfx  med_viewport[];

Gfx rdpew_hires_image_test[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(0x0C084148,0),
    gsDPSetCycleType(G_CYC_FILL),
    /*
    gsDPSetColorImage(5, G_IM_SIZ_16b, 640, cfb_16_a),
    */
    gsDPPipeSync(),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 640, cfb_16_a),
    gsDPSetCycleType(G_CYC_1CYCLE),

    gsSPDisplayList(med_viewport),
    gsSPDisplayList(rdpew_triangle14),

#ifdef OTHER_SCISSORS
    /*
     * use scissoring to lower number of clocks to complete sim
     */
    gsDPSetScissor(G_SC_NON_INTERLACE, 635,0,640,480),
    gsSPDisplayList(rdpew_triangle14),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,480,5),
    gsSPDisplayList(rdpew_triangle14),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,475,1023,480),
    gsSPDisplayList(rdpew_triangle14),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,5,480),
    gsSPDisplayList(rdpew_triangle14),

    gsDPSetScissor(G_SC_NON_INTERLACE, 315,0,320,480),
    gsSPDisplayList(rdpew_triangle14),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,233,640,240),
    gsSPDisplayList(rdpew_triangle14),
#endif
    gsSPEndDisplayList(),
};
/* end of case 14 */

/*
 * Test 15, Frame 15:
 *
 *
 * wed Oct 19 1994
 * 1024x1024 screensize (uses data from test 10)
 *
 * Draws the triangles from test 10 but on a bigger screen.
 * to use this test with the RDP CSIM use the options:
 *    -W 1024 -H 1024
 *
 */
Gfx rdpew_triangle15[MAX_STATIC_GFX_SIZE] = {
    gsSPVertex(&trivtx10j, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10k, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10l, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10i, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10a, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10b, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10c, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPVertex(&trivtx10d, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9,10,11, 0),

    gsSPEndDisplayList(),
};

/*
 * ADD TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx rdpew_display list must be extern'd in rdpverif.h, then
 * added to the 'testList' table in rdpverif.c
 *
 */
