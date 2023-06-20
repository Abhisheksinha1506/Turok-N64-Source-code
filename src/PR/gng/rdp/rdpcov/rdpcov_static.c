/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1996, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

/*
 * File:	rdpcov_static.c
 * Creator:	hal@sgi.com
 * Purpose:
 *
 * This file holds tiny display list segments that are 'static' data, for use
 * by the texture filter test module in rdpcov.c
 *
 * If you feel the urge to modify a test, see the comment at
 * the top of main.c for details.
 */

#include <ultratypes.h>
#include <mbi.h>
#include "dldriver.h"
#include "texture.h"
#include "rdpcov.h"

/*
 * Test conventions:
 *
 * Data variable names can be about anything, as long as they are unique
 * and consistent in the table entry.
 *
 * In order to get around compiler weirdness, the table of tests
 * is in rdpatt.c, and the Gfx lists must be extern'd in rdpvector.h
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

Gfx rdpcov_placebo_dl[MAX_STATIC_GFX_SIZE] = {
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
        {        -10,  10, 0, 0, 0, 0, 0, 0, 0x1f, 0x1f		},
        {         10,  10, 0, 0, 0, 0, 0x2f, 0x2f, 0x2f, 0x2f	},
        {         10, -10, 0, 0, 0, 0, 0, 0x1f, 0, 0x1f		},
        {        -10, -10, 0, 0, 0, 0, 0x0f, 0, 0, 0x0f		},
        {          0,   0, 0, 0, 0, 0, 0x0f, 0x0f, 0x0f, 0x0f	},
};

Gfx rdpcov_square0[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
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
 * Test 1, Frame 1:
 *
 * Simple square with a texture.
 *
 * Wed Oct  5 22:12:43 PDT 1994
 *
 */

static Vtx q1[4] =  {
        {        -64,  64, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff	},
        {         64,  64, 0, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff	},
        {         64, -64, 0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff	},
        {        -64, -64, 0, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff	},
};

Gfx rdpcov_square1[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(RGBA16grid, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&q1, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};
/* end of case 1 */



/*
 * Test 2, Frame 2:
 *
 * Simple square (4 triangles), each vertex a different color.
 *
 * Wed Oct  5 22:12:43 PDT 1994
 *
 */
static Vtx q2[5] =  {
        {        -40,  40, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {         40,  40, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         40, -40, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {        -40, -40, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},
        {          0,   0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
};

Gfx rdpcov_square2[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&q2, 5, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};
/* end of case 2 */


/*
 * Test 3
 *
 */
static Vtx q3[4] =  {
    /* high edge next to mid edge: */
        {        145, 120, 0, 0, 0, 0, 0xff, 0, 0, 0xff },
        {        120, 160, 0, 0, 0, 0, 0, 0xff, 0, 0xff },
        {        160, 180, 0, 0, 0, 0, 0, 0, 0xff, 0xff  },
        {        150,  60, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff  },
    };

Gfx rdpcov_square3[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&q3, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};
/* end of case 3 */

/*
 * Test 4, Frame 4:
 *
 * Zbuffered triangles
 *
 */
#define Z1	-200	/* In distance */
#define Z2	-180	/* closer */
/*#define Z1	0 /**/
/*#define Z2	0 /**/

static Vtx tris[] = {
/*    x,    y,	    z,	flag,	s,	t,	r,	g,	b,	a */
	
    { -40,  34,     Z1, 0,	0,	0,	0xff,	0,	0,	0xff },	  /* R */   
    {  30,   0,	    Z2, 0,	0,	0,	0,	0,	0xff,	0xff },	  /* B */	     
    { -40, -34,     Z1, 0,	0,	0,	0,	0xff,	0,	0xff },	  /* G */
    	     
    {  35,   24,    Z1, 0,	0,	0,	0,	0,	0xff,	0xff },	  /* B */	     
    {  35,  -24,    Z1, 0,	0,	0,	0,	0xff,	0,	0xff },	  /* G */	     
    { -20,   0,	    Z2, 0,	0,	0,	0xff,	0,	0,	0xff },	  /* R */	     
};

Gfx rdpcov_triangles[MAX_STATIC_GFX_SIZE] = {
    { gsSPClearGeometryMode(0xffffffff) }, 
    { gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER) }, 
    { gsDPSetRenderMode(G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2) },
    { gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE) },
    { gsSPVertex(&tris, sizeof(tris)/sizeof(tris[0]), 0) },
    { gsSP1Triangle(0, 1, 2, 0) }, 
    { gsSP1Triangle(3, 4, 5, 0) },
    { gsSPEndDisplayList() }
};

Gfx rdpcov_fogtriangles[MAX_STATIC_GFX_SIZE] = {
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
/* end of case 4 */


/*
 * Subpixel Scissor Test, Frame 9:
 *
 * Subpixel scissoring test.  Alternating black/white pinwheel
 * with another pinwheel of opposite phase and closer  scissored
 * inside the first pinwheel.  Should be gray line with scale of
 * gray proportional to number of subpixels in fraction of
 * scissor box surrounding.
 *
 * Also check coverage at center of pinwheel.
 * 
 * Sun Oct  9 22:42:47 PDT 1994
 *
 */

/* vertices for 8-panel pinwheel */
static Vtx subpix_scissorq[9] =  {
        {          40,    0, 0, 0, 0, 0,   0,   0,   0, 255 },
        {          28,   28, 0, 0, 0, 0, 255, 255, 255, 255 },
        {           0,   40, 0, 0, 0, 0,   0,   0,   0, 255 },
        {         -28,   28, 0, 0, 0, 0, 255, 255, 255, 255 },
        {         -40,    0, 0, 0, 0, 0,   0,   0,   0, 255 },
        {         -28,  -28, 0, 0, 0, 0, 255, 255, 255, 255 },
        {           0,  -40, 0, 0, 0, 0,   0,   0,   0, 255 },
        {          28,  -28, 0, 0, 0, 0, 255, 255, 255, 255 },
        {           0,    0, 0, 0, 0, 0,   0,   0,   0, 255 },
};

Gfx rdpcov_subpix_scissor[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    /* XXX how to setup flat shading? */
    gsSPSetGeometryMode(G_SHADE),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSPVertex(&subpix_scissorq, 9, 0),
    gsSP1Triangle(0, 1, 8, 0),
    gsSP1Triangle(1, 2, 8, 0),
    gsSP1Triangle(2, 3, 8, 0),
    gsSP1Triangle(3, 4, 8, 0),
    gsSP1Triangle(4, 5, 8, 0),
    gsSP1Triangle(5, 6, 8, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(7, 0, 8, 0),
    gsDPPipeSync(),
    gsDPSetScissorFrac(G_SC_NON_INTERLACE, 562, 401, 723, 560),
    gsSP1Triangle(0, 1, 8, 1),
    gsSP1Triangle(1, 2, 8, 1),
    gsSP1Triangle(2, 3, 8, 1),
    gsSP1Triangle(3, 4, 8, 1),
    gsSP1Triangle(4, 5, 8, 1),
    gsSP1Triangle(5, 6, 8, 1),
    gsSP1Triangle(6, 7, 8, 1),
    gsSP1Triangle(7, 0, 8, 1),
    gsSPEndDisplayList(),
};
/* end of case 9 */

/*
 * Test 10, Frame 10:
 *
 *
 * Mon Oct 10 1994
 *
 */
static Vtx trivtx10[5] =  {
        {        -40,  40, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {         40,  40, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         40, -40, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {        -40, -40, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},
        {          0,   0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
};

Gfx rdpcov_triangle10[MAX_STATIC_GFX_SIZE] = {
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
/* end of case 10 */






/*
 * Test 20, Frame 20:
 *
 * Simple square (2 triangles), each vertex a different color.
 * Tests accurate integer pixel positioning.
 *
 * Wed Oct 12 11:27:23 PDT 1994
 *
 */
static Vtx q20[5] =  {
        {        120, 160, 0, 0, 0, 0, 0, 0, 0xff, 0xff       },
        {        200, 160, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff },
        {        200,  80, 0, 0, 0, 0, 0, 0xff, 0, 0xff       },
        {        120,  80, 0, 0, 0, 0, 0xff, 0, 0, 0xff       },
        {          0,   0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff },
};

Gfx rdpcov_square20[10] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&q20, 5, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};
/* end of case 20 */

/*
 * Test 21, Frame 21:
 *
 * Some degenerate triangles.
 *
 */
static Vtx q21[12] =  {
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

Gfx rdpcov_square21[32] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSPVertex(&q21, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(9, 10, 11, 0),
    gsSPEndDisplayList(),
};
/* end of case 21 */


/*
 * Test 22, Frame 22:
 *
 * Test all possible edge-types next to each other:
 *
 *	HH, HM, HL, LM, LL, MM
 *
 * The RED-BLUE diagonal is the joining edge; if this transition
 * isn't smooth, we have a problem with rasterization/attribute
 * adjustments.
 *
 * Shared edges should have full coverage.
 *
 * Thu Oct 13 20:54:49 PDT 1994
 *
 */
static Vtx q22a[12] =  {
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
static Vtx q22b[12] =  {
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

Gfx rdpcov_square22[32] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),

    gsSPVertex(&q22a, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(4, 5, 6, 0),
    gsSP1Triangle(4, 6, 7, 0),
    gsSP1Triangle(8, 9, 10, 0),
    gsSP1Triangle(8, 10, 11, 0),

    gsSPVertex(&q22b, 12, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(4, 5, 6, 0),
    gsSP1Triangle(4, 6, 7, 0),
    gsSP1Triangle(8, 9, 10, 0),
    gsSP1Triangle(8, 10, 11, 0),

    gsSPEndDisplayList(),
};
/* end of case 22 */

/*
 * Test 23, Frame 23:
 *
 * 3 pairs of triangles, testing horizontal and nearly horizontal
 * shared edges. Should have full coverage...
 *
 * Fri Oct 21 14:32:10 PDT 1994
 *
 */
static Vtx q23[12] =  {
        {        -40,  25, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {         40,  45, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         40,  25, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {        -40,   5, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},

        {        -40,  -1, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {         40,  20, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         40,   0, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {        -40, -20, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},

        {        -40, -25, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {         40,  -5, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff	},
        {         40, -26, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {        -40, -45, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},
};

Gfx rdpcov_square23[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSPVertex(&q23, 12, 0),

    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSP1Triangle(4, 5, 6, 0),
    gsSP1Triangle(4, 6, 7, 0),
    gsSP1Triangle(8, 9, 10, 0),
    gsSP1Triangle(8, 10, 11, 0),

    gsSPEndDisplayList(),
};
/* end of case 23 */


/*
 * Test 24, Frame 24:
 *
 * Triangle mesh subpixel vertex. 6 triangles meeting.
 *
 * Fri Oct 21 14:32:10 PDT 1994
 *
 */
static Vtx q24[9] =  {
        {        -40,  40, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},
        {          0,  40, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {         40,  40, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},

        {        -40,   0, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {          0,   0, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {         40,   0, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},

        {        -40, -40, 0, 0, 0, 0, 0xff, 0, 0, 0xff		},
        {          0, -40, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {         40, -40, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
};

Gfx rdpcov_square24[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSPVertex(&q24, 9, 0),

    gsSP1Triangle(0, 1, 3, 0),
    gsSP1Triangle(3, 1, 4, 0),
    gsSP1Triangle(1, 2, 4, 0),
    gsSP1Triangle(4, 2, 5, 0),
    gsSP1Triangle(3, 4, 6, 0),
    gsSP1Triangle(6, 4, 7, 0),
    gsSP1Triangle(4, 5, 7, 0),
    gsSP1Triangle(7, 5, 8, 0),

    gsSPEndDisplayList(),
};
/* end of case 24 */

/*
 * Test 25.
 *
 * Test of RDPBLOCK.
 *
 */
static unsigned int data_25[] =
{
    /* two RDP-ready triangles... */
    0xcc800324, 0x032401e0, 0x00f10000, 0x80000000,
    0x00a00000, 0xfffeff88, 0x00a00000, 0x0000ffa8,
    0x00ff00ff, 0x00ff00ff, 0xfffe0001, 0x00000000,
    0x00000000, 0x00000000, 0x6c95936b, 0x00000000,
    0x0000fffc, 0xfffc0000, 0xfffefffe, 0xfffc0000,
    0x00bdd86c, 0xd92a0000, 0x6c956c95, 0xd92a0000,
    0xcc800324, 0x01e0009b, 0x00a00000, 0xfffeff88,
    0x004ec000, 0x00000000, 0x004e002a, 0x0000ffc8,
    0xfffe0000, 0x010000ff, 0x00010003, 0x00010000,
    0x91700000, 0xae910000, 0x916d24d8, 0x936b0000,
    0x00010000, 0xfffe0000, 0x00010000, 0xfffe0000,
    0x936b0000, 0x6c950000, 0x936b0000, 0x6c950000,
};

Gfx rdpcov_gfx_25[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
/*    gsSPRDPBlock(&(data_25[0]), 48*sizeof(unsigned int)), */
    gsDPWord(0xcc800324, 0x032401e0),
    gsDPWord(0x00f10000, 0x80000000),
    gsDPWord(0x00a00000, 0xfffeff88),
    gsDPWord(0x00a00000, 0x0000ffa8),
    gsDPWord(0x00ff00ff, 0x00ff00ff),
    gsDPWord(0xfffe0001, 0x00000000),
    gsDPWord(0x00000000, 0x00000000),
    gsDPWord(0x6c95936b, 0x00000000),
    gsDPWord(0x0000fffc, 0xfffc0000),
    gsDPWord(0xfffefffe, 0xfffc0000),
    gsDPWord(0x00bdd86c, 0xd92a0000),
    gsDPWord(0x6c956c95, 0xd92a0000),
    gsDPWord(0xcc800324, 0x01e0009b),
    gsDPWord(0x00a00000, 0xfffeff88),
    gsDPWord(0x004ec000, 0x00000000),
    gsDPWord(0x004e002a, 0x0000ffc8),
    gsDPWord(0xfffe0000, 0x010000ff),
    gsDPWord(0x00010003, 0x00010000),
    gsDPWord(0x91700000, 0xae910000),
    gsDPWord(0x916d24d8, 0x936b0000),
    gsDPWord(0x00010000, 0xfffe0000),
    gsDPWord(0x00010000, 0xfffe0000),
    gsDPWord(0x936b0000, 0x6c950000),
    gsDPWord(0x936b0000, 0x6c950000),
/*
    gsDPWord(data_25[0],data_25[1]),
    gsDPWord(data_25[2],data_25[3]),
    gsDPWord(data_25[4],data_25[5]),
    gsDPWord(data_25[6],data_25[7]),
    gsDPWord(data_25[8],data_25[9]),
    gsDPWord(data_25[10],data_25[11]),
    gsDPWord(data_25[12],data_25[13]),
    gsDPWord(data_25[14],data_25[15]),
    gsDPWord(data_25[16],data_25[17]),
    gsDPWord(data_25[18],data_25[19]),
    gsDPWord(data_25[20],data_25[21]),
    gsDPWord(data_25[22],data_25[23]),
    gsDPWord(data_25[24],data_25[25]),
    gsDPWord(data_25[26],data_25[27]),
    gsDPWord(data_25[28],data_25[29]),
    gsDPWord(data_25[30],data_25[31]),
    gsDPWord(data_25[32],data_25[33]),
    gsDPWord(data_25[34],data_25[35]),
    gsDPWord(data_25[36],data_25[37]),
    gsDPWord(data_25[38],data_25[39]),
    gsDPWord(data_25[40],data_25[41]),
    gsDPWord(data_25[42],data_25[43]),
    gsDPWord(data_25[44],data_25[45]),
    gsDPWord(data_25[46],data_25[47]),
*/
    gsSPEndDisplayList(),
};
/* end of case 25 */

/*
 * case 26:
 */
#include "rdpcov_case_edge_00.h"
/* end of case 26 */

/*
 * case 27:
 */
#include "rdpcov_case_vertex_00.h"
/* end of case 27 */

/*
 * case 28:
 */
#include "rdpcov_case_skinny_00.h"
/* end of case 28 */

/*
 * case 29:
 */
#include "rdpcov_case_tiny_00.h"
/* end of case 29 */

/*
 * case 30:
 */
#include "rdpcov_case_disc_00.h"
/* end of case 30 */

/*
 * Test 31, Frame 31:
 *
 *
 */
#include "ball_vtx.h"

Gfx rdpcov_ball_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),

#include "ball_tri.h"

    gsSPEndDisplayList(),
};
/* end of case 31 */


/*
 * Test 32
 *
 * Single poly animation (precision test)
 *
 */
static Vtx test32_vtx[3] =  {
        {        0,  40, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {       -3, -40, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
        {      -40, -38, 0, 0, 0, 0, 0, 0xff, 0, 0xff		},
};

Gfx rdpcov_test32_dl[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(&test32_vtx, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

/*
 * Test 33
 *
 * SGI logo.
 *
 * Fri Dec 30 16:13:27 PST 1994
 *
 */
#include "logo_vtx.h"

Gfx rdpcov_logo_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),

#include "logo_tri.h"

    gsSPEndDisplayList(),
};

static Vtx bg33_vtx[4] =  {
        {        -40,  40, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {         40,  40, 0, 0, 0, 0, 0, 0, 0xff, 0xff		},
        {         40, -40, 0, 0, 0, 0, 0, 0, 0x10, 0xff		},
        {        -40, -40, 0, 0, 0, 0, 0, 0, 0x10, 0xff		},
};

Gfx rdpcov_bg33_dl[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetColorDither(G_CD_BAYER),
    gsSPVertex(&bg33_vtx, 4, 0),
    gsSP1Triangle(0, 2, 1, 0),
    gsSP1Triangle(0, 3, 2, 0),
    gsSPEndDisplayList(),
};

/* end of test 33 */


/*
 * Test 34
 *
 * Sat Feb 11 20:15:06 PST 1995
 *
 * Ball with shading as a texture map.
 *
 */
#include "IA8phong.h"
Gfx rdpcov_ball_tex_dl[] = {

    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsDPSetCombineLERP(PRIMITIVE, SHADE, TEXEL0, SHADE,
		       PRIMITIVE, SHADE, TEXEL0, SHADE,
		       PRIMITIVE, SHADE, TEXEL0, SHADE,
		       PRIMITIVE, SHADE, TEXEL0, SHADE),

    gsDPSetTextureFilter(G_TF_BILERP),
    /* phong texture could be just intensity map */
    gsDPLoadTextureBlock(IA8phong, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
			 G_TX_CLAMP | G_TX_NOMIRROR, G_TX_CLAMP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),

#include "ball_tri.h"

    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off */
    gsSPEndDisplayList(),
};

/*
 * Test 35
 *
 * line test
 * Set up so that vertices are lined up with screen coordinates
 *
 * Mon Feb  6 16:19:27 PST 1995
 *
 */

static Vtx q35[] = { 
        {0x4ec, 0x1e0,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4e9, 0x20d,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4e0, 0x23a,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4d1, 0x266,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4bd, 0x290,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4a3, 0x2b9,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x484, 0x2e0,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x45f, 0x304,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x436, 0x325,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x409, 0x344,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x3d8, 0x35e,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x3a4, 0x376,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x36d, 0x389,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x334, 0x398,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x2f9, 0x3a3,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x280, 0x1e0,  0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff }, 
}; 


static Vtx q36[] = { 
        {0x2bd, 0x3aa,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x280, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x243, 0x3aa,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x207, 0x3a3,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x1cc, 0x398,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x193, 0x389,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x15c, 0x376,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x128, 0x35e,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x0f7, 0x344,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x0ca, 0x325,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x0a1, 0x304,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x07c, 0x2e0,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x05d, 0x2b9,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x043, 0x290,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x02f, 0x266,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x280, 0x1e0,  0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff }, 
}; 


static Vtx q37[] = { 
        {0x020, 0x23a,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x017, 0x20d,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x1e0,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x017, 0x1b3,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x020, 0x186,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x02f, 0x15a,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x043, 0x130,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x05d, 0x107,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x07c, 0x0e0,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x0a1, 0x0bc,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x0ca, 0x09b,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x0f7, 0x07c,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x128, 0x062,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x15c, 0x04a,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x193, 0x037,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x280, 0x1e0,  0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff }, 
}; 


static Vtx q38[] = { 
        {0x1cc, 0x028,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x207, 0x01d,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x243, 0x016,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x280, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x2bd, 0x016,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x2f9, 0x01d,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x334, 0x028,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x36d, 0x037,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x3a4, 0x04a,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x3d8, 0x062,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x409, 0x07c,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x436, 0x09b,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x45f, 0x0bc,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x484, 0x0e0,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4a3, 0x107,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x280, 0x1e0,  0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff }, 
}; 


static Vtx q39[] = { 
        {0x4bd, 0x130,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4d1, 0x15a,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4e0, 0x186,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4e9, 0x1b3,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x280, 0x1e0,  0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff }, 
}; 


static Vtx r35[] = { 
        {0x4ec, 0x1e0,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4e9, 0x20d,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4e0, 0x23a,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4d1, 0x266,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4bd, 0x290,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4a3, 0x2b9,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x484, 0x2e0,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x45f, 0x304,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x436, 0x325,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x409, 0x344,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x3d8, 0x35e,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x3a4, 0x376,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x36d, 0x389,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x334, 0x398,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x2f9, 0x3a3,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x280, 0x1e0,   0, 0, 0, 0, 0xff, 0, 0, 0xff }, 
}; 


static Vtx r36[] = { 
        {0x2bd, 0x3aa,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x280, 0x3ac,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x243, 0x3aa,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x207, 0x3a3,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x1cc, 0x398,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x193, 0x389,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x15c, 0x376,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x128, 0x35e,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x0f7, 0x344,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x0ca, 0x325,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x0a1, 0x304,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x07c, 0x2e0,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x05d, 0x2b9,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x043, 0x290,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x02f, 0x266,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x280, 0x1e0,  -3, 0, 0, 0, 0xff, 0, 0, 0xff }, 
}; 


static Vtx r37[] = { 
        {0x020, 0x23a,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x017, 0x20d,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x014, 0x1e0,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x017, 0x1b3,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x020, 0x186,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x02f, 0x15a,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x043, 0x130,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x05d, 0x107,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x07c, 0x0e0,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x0a1, 0x0bc,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x0ca, 0x09b,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x0f7, 0x07c,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x128, 0x062,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x15c, 0x04a,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x193, 0x037,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x280, 0x1e0,  -3, 0, 0, 0, 0xff, 0, 0, 0xff }, 
}; 


static Vtx r38[] = { 
        {0x1cc, 0x028,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x207, 0x01d,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x243, 0x016,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x280, 0x014,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x2bd, 0x016,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x2f9, 0x01d,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x334, 0x028,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x36d, 0x037,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x3a4, 0x04a,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x3d8, 0x062,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x409, 0x07c,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x436, 0x09b,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x45f, 0x0bc,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x484, 0x0e0,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4a3, 0x107,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x280, 0x1e0,  -3, 0, 0, 0, 0xff, 0, 0, 0xff }, 
}; 


static Vtx r39[] = { 
        {0x4bd, 0x130,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4d1, 0x15a,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4e0, 0x186,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4e9, 0x1b3,  -3, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x280, 0x1e0,  -3, 0, 0, 0, 0xff, 0, 0, 0xff }, 
}; 


static Vtx s35[] = { 
        {0x4ec, 0x1e0,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4e9, 0x20d,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4e0, 0x23a,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4d1, 0x266,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4bd, 0x290,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4a3, 0x2b9,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x484, 0x2e0,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x45f, 0x304,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x436, 0x325,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x409, 0x344,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x3d8, 0x35e,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x3a4, 0x376,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x36d, 0x389,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x334, 0x398,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x2f9, 0x3a3,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x280, 0x1e0,  0, 0, 0, 0, 0xff, 0, 0, 0xff }, 
}; 


static Vtx s36[] = { 
        {0x2bd, 0x3aa,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x280, 0x3ac,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x243, 0x3aa,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x207, 0x3a3,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x1cc, 0x398,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x193, 0x389,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x15c, 0x376,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x128, 0x35e,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x0f7, 0x344,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x0ca, 0x325,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x0a1, 0x304,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x07c, 0x2e0,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x05d, 0x2b9,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x043, 0x290,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x02f, 0x266,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x280, 0x1e0,  0, 0, 0, 0, 0xff, 0, 0, 0xff }, 
}; 


static Vtx s37[] = { 
        {0x020, 0x23a,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x017, 0x20d,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x014, 0x1e0,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x017, 0x1b3,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x020, 0x186,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x02f, 0x15a,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x043, 0x130,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x05d, 0x107,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x07c, 0x0e0,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x0a1, 0x0bc,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x0ca, 0x09b,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x0f7, 0x07c,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x128, 0x062,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x15c, 0x04a,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x193, 0x037,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x280, 0x1e0,  0, 0, 0, 0, 0xff, 0, 0, 0xff }, 
}; 


static Vtx s38[] = { 
        {0x1cc, 0x028,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x207, 0x01d,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x243, 0x016,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x280, 0x014,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x2bd, 0x016,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x2f9, 0x01d,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x334, 0x028,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x36d, 0x037,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x3a4, 0x04a,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x3d8, 0x062,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x409, 0x07c,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x436, 0x09b,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x45f, 0x0bc,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x484, 0x0e0,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4a3, 0x107,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x280, 0x1e0,  0, 0, 0, 0, 0xff, 0, 0, 0xff }, 
}; 


static Vtx s39[] = { 
        {0x4bd, 0x130,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4d1, 0x15a,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4e0, 0x186,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x4e9, 0x1b3,  -4, 0, 0, 0, 0, 0, 0xff, 0xff }, 
        {0x280, 0x1e0,  0, 0, 0, 0, 0xff, 0, 0, 0xff }, 
}; 

static Vtx box1[] = {
        {0x014, 0x014,   0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
        {0x014, 0x3ac,   0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
        {0x4ec, 0x3ac,   0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
        {0x4ec, 0x014,   0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
};

static Vtx box2[] = {
        {0x14a, 0x0fa,   0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
        {0x14a, 0x2c6,   0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
        {0x3b6, 0x2c6,   0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
        {0x3b6, 0x0fa,   0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
};

static Vtx box3[] = {
        {0x1e5, 0x16d,   0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
        {0x1e5, 0x253,   0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
        {0x31b, 0x253,   0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
        {0x31b, 0x16d,   0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
};

static Vtx grid00[] = { 
        {0x014, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x031,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x031,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x04f,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x04f,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x06d,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x06d,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x08a,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x08a,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x0a8,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x0a8,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x0c6,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x0c6,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x0e3,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x0e3,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
}; 

static Vtx grid01[] = { 
        {0x014, 0x101,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x101,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x11f,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x11f,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x13c,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x13c,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x15a,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x15a,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x178,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x178,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x195,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x195,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x1b3,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x1b3,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x1d1,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x1d1,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
}; 

static Vtx grid02[] = { 
        {0x014, 0x1ee,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x1ee,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x20c,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x20c,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x22a,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x22a,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x247,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x247,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x265,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x265,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x283,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x283,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x2a0,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x2a0,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x2be,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x2be,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
}; 

static Vtx grid03[] = { 
        {0x014, 0x2dc,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x2dc,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x2f9,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x2f9,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x317,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x317,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x335,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x335,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x352,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x352,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x370,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x370,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x38e,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x38e,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
}; 

static Vtx grid04[] = { 
        {0x014, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x03c, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x03c, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x064, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x064, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x08c, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x08c, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x0b4, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x0b4, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x0dc, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x0dc, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x104, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x104, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x12c, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x12c, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
}; 

static Vtx grid05[] = { 
        {0x154, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x154, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x17c, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x17c, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x1a4, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x1a4, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x1cc, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x1cc, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x1f4, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x1f4, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x21c, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x21c, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x244, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x244, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x26c, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x26c, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
}; 

static Vtx grid06[] = { 
        {0x294, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x294, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x2bc, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x2bc, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x2e4, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x2e4, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x30c, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x30c, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x334, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x334, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x35c, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x35c, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x384, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x384, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x3ac, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x3ac, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
}; 

static Vtx grid07[] = { 
        {0x3d4, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x3d4, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x3fc, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x3fc, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x424, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x424, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x44c, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x44c, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x474, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x474, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x49c, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x49c, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4c4, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4c4, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x014,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x3ac,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
}; 


static Vtx duo[] = {
        {0x281, 0x3ac, -1, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
        {0x281, 0x1e0, -1, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
        {0x180, 0x3ac,  1, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
        {0x180, 0x1e0,  1, 0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
        {0x014, 0x264,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x264,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x014, 0x284,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x4ec, 0x284,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
};

Gfx rdpcov_lines1[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    /* gsSPSetGeometryMode(G_ZBUFFER),  */
    /*gsSPClearGeometryMode(G_CULL_BACK), */
    gsSPSetGeometryMode(G_SHADE), 
    /* gsPClearGeometryMode(G_SHADE), */
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    /* gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE), */
    /* gsDPSetPrimColor(0, 0,   0, 255,   0, 255), */

    gsDPSetRenderMode(G_RM_AA_ZB_XLU_LINE, G_RM_AA_ZB_XLU_LINE2), 
    /* gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2), */

    /* gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2), */

    /* gsDPSetScissor(G_SC_NON_INTERLACE, 40, 40, 200, 200), */
    /* gsDPSetScissor(G_SC_NON_INTERLACE, 180, 130, 240, 170), */
    /* gsDPSetScissor(G_SC_NON_INTERLACE, 120,  30, 280, 190), */

    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT-1),

    /*
    gsSPVertex(&box1, 4, 0),
    gsSPLine3D(0, 1, 0),
    gsSPLine3D(1, 2, 1),
    gsSPLine3D(2, 3, 2),
    gsSPLine3D(3, 0, 3),

    gsSPVertex(&box2, 4, 0),
    gsSPLine3D(0, 1, 0),
    gsSPLine3D(1, 2, 1),
    gsSPLine3D(2, 3, 2),
    gsSPLine3D(3, 0, 3),

    gsSPVertex(&box3, 4, 0),
    gsSPLine3D(0, 1, 0),
    gsSPLine3D(1, 2, 1),
    gsSPLine3D(2, 3, 2),
    gsSPLine3D(3, 0, 3),
    */

    /*
    gsSPVertex(&grid00, 16, 0), 
    gsSPLine3D(0, 1, 0), 
    gsSPLine3D(2, 3, 2), 
    gsSPLine3D(4, 5, 4), 
    gsSPLine3D(6, 7, 6), 
    gsSPLine3D(8, 9, 8), 
    gsSPLine3D(10, 11, 10), 
    gsSPLine3D(12, 13, 12), 
    gsSPLine3D(14, 15, 14), 

    gsSPVertex(&grid01, 16, 0), 
    gsSPLine3D(0, 1, 0), 
    gsSPLine3D(2, 3, 2), 
    gsSPLine3D(4, 5, 4), 
    gsSPLine3D(6, 7, 6), 
    gsSPLine3D(8, 9, 8), 
    gsSPLine3D(10, 11, 10), 
    gsSPLine3D(12, 13, 12), 
    gsSPLine3D(14, 15, 14), 

    gsSPVertex(&grid02, 16, 0), 
    gsSPLine3D(0, 1, 0), 
    gsSPLine3D(2, 3, 2), 
    gsSPLine3D(4, 5, 4), 
    gsSPLine3D(6, 7, 6), 
    gsSPLine3D(8, 9, 8), 
    gsSPLine3D(10, 11, 10), 
    gsSPLine3D(12, 13, 12), 
    gsSPLine3D(14, 15, 14), 

    gsSPVertex(&grid03, 16, 0), 
    gsSPLine3D(0, 1, 0), 
    gsSPLine3D(2, 3, 2), 
    gsSPLine3D(4, 5, 4), 
    gsSPLine3D(6, 7, 6), 
    gsSPLine3D(8, 9, 8), 
    gsSPLine3D(10, 11, 10), 
    gsSPLine3D(12, 13, 12), 
    gsSPLine3D(14, 15, 14), 

    gsSPVertex(&grid04, 16, 0), 
    gsSPLine3D(0, 1, 0), 
    gsSPLine3D(2, 3, 2), 
    gsSPLine3D(4, 5, 4), 
    gsSPLine3D(6, 7, 6), 
    gsSPLine3D(8, 9, 8), 
    gsSPLine3D(10, 11, 10), 
    gsSPLine3D(12, 13, 12), 
    gsSPLine3D(14, 15, 14), 

    gsSPVertex(&grid05, 16, 0), 
    gsSPLine3D(0, 1, 0), 
    gsSPLine3D(2, 3, 2), 
    gsSPLine3D(4, 5, 4), 
    gsSPLine3D(6, 7, 6), 
    gsSPLine3D(8, 9, 8), 
    gsSPLine3D(10, 11, 10), 
    gsSPLine3D(12, 13, 12), 
    gsSPLine3D(14, 15, 14), 

    gsSPVertex(&grid06, 16, 0), 
    gsSPLine3D(0, 1, 0), 
    gsSPLine3D(2, 3, 2), 
    gsSPLine3D(4, 5, 4), 
    gsSPLine3D(6, 7, 6), 
    gsSPLine3D(8, 9, 8), 
    gsSPLine3D(10, 11, 10), 
    gsSPLine3D(12, 13, 12), 
    gsSPLine3D(14, 15, 14), 

    gsSPVertex(&grid07, 16, 0), 
    gsSPLine3D(0, 1, 0), 
    gsSPLine3D(2, 3, 2), 
    gsSPLine3D(4, 5, 4), 
    gsSPLine3D(6, 7, 6), 
    gsSPLine3D(8, 9, 8), 
    gsSPLine3D(10, 11, 10), 
    gsSPLine3D(12, 13, 12), 
    gsSPLine3D(14, 15, 14), 
    */

    gsSPVertex(&q35, 16, 0),
    gsSPLine3D(0, 15, 0), 
    gsSPLine3D(1, 15, 1), 
    gsSPLine3D(2, 15, 2), 
    gsSPLine3D(3, 15, 3), 
    gsSPLine3D(4, 15, 4), 
    gsSPLine3D(5, 15, 5), 
    gsSPLine3D(6, 15, 6), 
    gsSPLine3D(7, 15, 7), 
    gsSPLine3D(8, 15, 8), 
    gsSPLine3D(9, 15, 9), 
    gsSPLine3D(10, 15, 10), 
    gsSPLine3D(11, 15, 11), 
    gsSPLine3D(12, 15, 12), 
    gsSPLine3D(13, 15, 13), 
    gsSPLine3D(14, 15, 14), 

    gsSPVertex(&q36, 16, 0),
    gsSPLine3D(0, 15, 0), 
    gsSPLine3D(1, 15, 1), 
    gsSPLine3D(2, 15, 2), 
    gsSPLine3D(3, 15, 3), 
    gsSPLine3D(4, 15, 4), 
    gsSPLine3D(5, 15, 5), 
    gsSPLine3D(6, 15, 6), 
    gsSPLine3D(7, 15, 7), 
    gsSPLine3D(8, 15, 8), 
    gsSPLine3D(9, 15, 9), 
    gsSPLine3D(10, 15, 10), 
    gsSPLine3D(11, 15, 11), 
    gsSPLine3D(12, 15, 12), 
    gsSPLine3D(13, 15, 13), 
    gsSPLine3D(14, 15, 14), 

    gsSPVertex(&q37, 16, 0),
    gsSPLine3D(0, 15, 0), 
    gsSPLine3D(1, 15, 1), 
    gsSPLine3D(2, 15, 2), 
    gsSPLine3D(3, 15, 3), 
    gsSPLine3D(4, 15, 4), 
    gsSPLine3D(5, 15, 5), 
    gsSPLine3D(6, 15, 6), 
    gsSPLine3D(7, 15, 7), 
    gsSPLine3D(8, 15, 8), 
    gsSPLine3D(9, 15, 9), 
    gsSPLine3D(10, 15, 10), 
    gsSPLine3D(11, 15, 11), 
    gsSPLine3D(12, 15, 12), 
    gsSPLine3D(13, 15, 13), 
    gsSPLine3D(14, 15, 14), 

    gsSPVertex(&q38, 16, 0),
    gsSPLine3D(0, 15, 0), 
    gsSPLine3D(1, 15, 1), 
    gsSPLine3D(2, 15, 2), 
    gsSPLine3D(3, 15, 3), 
    gsSPLine3D(4, 15, 4), 
    gsSPLine3D(5, 15, 5), 
    gsSPLine3D(6, 15, 6), 
    gsSPLine3D(7, 15, 7), 
    gsSPLine3D(8, 15, 8), 
    gsSPLine3D(9, 15, 9), 
    gsSPLine3D(10, 15, 10), 
    gsSPLine3D(11, 15, 11), 
    gsSPLine3D(12, 15, 12), 
    gsSPLine3D(13, 15, 13), 
    gsSPLine3D(14, 15, 14), 

    gsSPVertex(&q39, 5, 0),
    gsSPLine3D(0, 4, 0), 
    gsSPLine3D(1, 4, 1), 

    gsSPLine3D(2, 4, 2), 
    gsSPLine3D(3, 4, 3), 

    /*
    gsSPVertex(&duo, 8, 0),
    gsSPLine3D(0, 1, 0),
    gsSPLine3D(2, 3, 2),
    gsSPLine3D(4, 5, 4),
    gsSPLine3D(6, 7, 6),
    */

    gsSPEndDisplayList(),
};


/* end of test 35 */

/*
 * Test 36
 *
 * line test
 * Set up so that vertices are lined up with screen coordinates
 *
 * Data base is a sphere provided by Nathan
 *
 * Thu Feb 23 14:14:43 PST 1995
 *
 */

#include "sphere.dat"

Gfx rdpcov_lines2[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPClearGeometryMode(G_SHADE),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_XLU_LINE, G_RM_AA_XLU_LINE2),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT-1),

#include "sphere.dl"

    gsSPEndDisplayList(),
};


/* end of test 36 */

/*
 * Test 37
 *
 * line/clipping test
 * Set up so that vertices are lined up with screen coordinates
 *
 * Tue Mar  7 15:00:06 PST 1995
 *
 */

static Vtx border[] = { 
    {  1,   1,  0,   0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
    {  1, 239,  0,   0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
    {319, 239,  0,   0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
    {319,   1,  0,   0, 0, 0, 0xff, 0xff, 0xff, 0xff }, 
}; 

static Vtx outside[] = { 
    {-154, -114,  0,   0, 0, 0, 0x00, 0xff, 0x00, 0xff }, 
    {-154,  354,  0,   0, 0, 0, 0x00, 0xff, 0x00, 0xff }, 
    { 474,  354,  0,   0, 0, 0, 0x00, 0xff, 0x00, 0xff }, 
    { 474, -114,  0,   0, 0, 0, 0x00, 0xff, 0x00, 0xff }, 
}; 

static Vtx crosshair[] = { 
    { 160,  120,  0,   0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
    { 400,  120,  0,   0, 0, 0, 0xff, 0x00, 0x00, 0xff }, 
    { 160,  300,  0,   0, 0, 0, 0x00, 0xff, 0x00, 0xff }, 
    { -80,  120,  0,   0, 0, 0, 0xff, 0xff, 0x00, 0xff }, 
    { 160,  -60,  0,   0, 0, 0, 0x00, 0xff, 0xff, 0xff }, 
}; 

static Vtx ldiamond[] = { 
    { 160,  354,  0,   0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
    { 474,  120,  0,   0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
    { 160, -114,  0,   0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
    {-154,  120,  0,   0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
}; 

static Vtx sdiamond[] = { 
    { 400,  120,  0,   0, 0, 0, 0xff, 0x00, 0x00, 0xff }, 
    { 160,  300,  0,   0, 0, 0, 0x00, 0xff, 0x00, 0xff }, 
    { -80,  120,  0,   0, 0, 0, 0xff, 0xff, 0x00, 0xff }, 
    { 160,  -60,  0,   0, 0, 0, 0x00, 0xff, 0xff, 0xff }, 
}; 

static Vtx diagonals[]= { 
    {-154, -114,  0,   0, 0, 0, 0xff, 0xff, 0x00, 0xff }, 
    {-154,  354,  0,   0, 0, 0, 0x00, 0xff, 0xff, 0xff }, 
    { 474,  354,  0,   0, 0, 0, 0xff, 0x00, 0xff, 0xff }, 
    { 474, -114,  0,   0, 0, 0, 0x00, 0xff, 0x00, 0xff }, 
}; 
/*
demonstrates "clipping bug" in rendering above diagonals
static Vtx diagonals[]= { 
    {   1,    1,  0,   0, 0, 0, 0xff, 0xff, 0x00, 0xff }, 
    {   1,  239,  0,   0, 0, 0, 0x00, 0xff, 0xff, 0xff }, 
    { 319,  239,  0,   0, 0, 0, 0xff, 0x00, 0xff, 0xff }, 
    { 319,    1,  0,   0, 0, 0, 0x00, 0xff, 0x00, 0xff }, 
}; 
*/


Gfx rdpcov_lclip1[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_XLU_LINE, G_RM_AA_XLU_LINE2),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT-1),

    gsSPVertex(&border, 4, 0),
    gsSPLine3D(0, 1, 0), 
    gsSPLine3D(1, 2, 1), 
    gsSPLine3D(2, 3, 2), 
    gsSPLine3D(3, 0, 3), 

    gsSPVertex(&outside, 4, 0),
    gsSPLine3D(0, 1, 0), 
    gsSPLine3D(1, 2, 1), 
    gsSPLine3D(2, 3, 2), 
    gsSPLine3D(3, 0, 3), 

    gsSPVertex(&crosshair, 5, 0),
    gsSPLine3D(0, 1, 0), 
    gsSPLine3D(0, 2, 0), 
    gsSPLine3D(0, 3, 0), 
    gsSPLine3D(0, 4, 0), 

    gsSPVertex(&ldiamond, 4, 0),
    gsSPLine3D(0, 1, 0), 
    gsSPLine3D(1, 2, 1), 
    gsSPLine3D(2, 3, 2), 
    gsSPLine3D(3, 0, 3), 

    gsSPVertex(&sdiamond, 4, 0),
    gsSPLine3D(3, 0, 3), 
    gsSPLine3D(2, 3, 2), 
    gsSPLine3D(1, 2, 1), 
    gsSPLine3D(0, 1, 0), 

    gsSPVertex(&diagonals, 4, 0),
    gsSPLine3D(0, 2, 0), 
    gsSPLine3D(1, 3, 1), 

    
    gsSPEndDisplayList(),
};

/* end of test 37 */

/*
 * Test 38
 *
 * texture mapped lines. uses rgb color bar as texture
 *
 * Fri Apr  7 15:43:25 PDT 1995
 * 
 */

#include "RGBA16cbar.h"

static Vtx square38[4] =  {
    {        -64,  64, 0,   0,   ( 0 << 6), ( 0 << 6),   0x00, 0x00, 0x00,   0xff},
    {         64,  64, 0,   0,   (31 << 6), ( 0 << 6),   0xff, 0xff, 0xff,   0xff},
    {         64, -64, 0,   0,   (31 << 6), (31 << 6),   0x00, 0x00, 0x00,   0xff},
    {        -64, -64, 0,   0,   ( 0 << 6), (31 << 6),   0xff, 0xff, 0xff,   0xff},
};

static Vtx blah[4] = {
    {        -96,   0, 1,   0,   (31 << 6), ( 0 << 6),   0xff, 0xff, 0xff,   0xff},
    {         96,   0,-1,   0,   ( 0 << 6), ( 0 << 6),   0xff, 0xff, 0xff,   0xff},
    {          0, -96, 1,   0,   ( 0 << 6), ( 0 << 6),   0xff, 0xff, 0xff,   0xff},
    {          0,  96,-1,   0,   (31 << 6), ( 0 << 6),   0xff, 0xff, 0xff,   0xff},
};

Gfx rdpcov_cbar1[MAX_STATIC_GFX_SIZE] = {

    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),

    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON), 
    gsDPPipeSync(),
    /* gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA), */
    /* gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE), */
    gsDPSetCombineMode(G_CC_MODULATERGBDECALA, G_CC_MODULATERGBDECALA), 
    gsDPSetPrimColor(0, 0,   0, 255,   0, 255),


    /* gsDPSetRenderMode(G_RM_AA_XLU_LINE, G_RM_AA_XLU_LINE2), */
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2), 
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT-1),

    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(RGBA16cbar, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),



    gsSPVertex(&square38, 4, 0),
    gsSPLine3D(0, 1, 0),
    gsSPLine3D(1, 2, 1),
    gsSPLine3D(2, 3, 2),
    gsSPLine3D(3, 0, 3),

    gsDPPipeSync(),
    gsDPSetPrimColor(0, 0,   0, 0,  255, 255),
    gsSPVertex(&blah, 4, 0),
    gsSPLine3D(0, 1, 0),
    gsSPLine3D(2, 3, 2),

    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF),  
    
    gsSPEndDisplayList(),
};

/* end of case 38 */

/*
 * Test 39
 *
 * triangle test
 * See if edgewalker is puking on low sloped lines
 *
 * Mon Feb  6 16:19:27 PST 1995
 *
 */

static Vtx x39[] = { 
        {0x4bd, 0x160,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
        {0x280, 0x163,  0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff }, 
	{0x00e, 0x160,  0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff }, 
}; 

Gfx rdpcov_FooTri[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE), 
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2), 
    /* gsDPSetRenderMode(G_RM_AA_ZB_XLU_LINE, G_RM_AA_ZB_XLU_LINE2),  */
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT-1),

    gsSPVertex(&x39, 3, 0),

    gsSPLine3D(0, 1, 0),

    gsSP1Triangle(0, 1, 2, 0), 
        
    gsSPEndDisplayList(),
};


/* end of test 39 */


/*
 * Test 40, Frame 40:
 *
 * dither test, low gradient
 *
 * Fri Jun  2 20:18:09 PDT 1995
 *
 */
static Vtx lowgradient_tri_toprow[12] =  {
        {        -40,  40, 0, 0, 0, 0, 0x2f, 0x0, 0x0, 0xff	},
        {        -20,  40, 0, 0, 0, 0, 0x0, 0x2f, 0x0, 0xff	},
        {        -30,  50, 0, 0, 0, 0, 0x0, 0x0, 0x2f, 0xff	},

        {        -20,  40, 0, 0, 0, 0, 0x2f, 0x0, 0x0, 0xff	},
        {          0,  40, 0, 0, 0, 0, 0x0, 0x2f, 0x0, 0xff	},
        {        -10,  50, 0, 0, 0, 0, 0x0, 0x0, 0x2f, 0xff	},

        {          0,  40, 0, 0, 0, 0, 0x2f, 0x0, 0x0, 0xff	},
        {         20,  40, 0, 0, 0, 0, 0x0, 0x2f, 0x0, 0xff	},
        {         10,  50, 0, 0, 0, 0, 0x0, 0x0, 0x2f, 0xff	},

        {         20,  40, 0, 0, 0, 0, 0x2f, 0x0, 0x0, 0xff	},
        {         40,  40, 0, 0, 0, 0, 0x0, 0x2f, 0x0, 0xff	},
        {         30,  50, 0, 0, 0, 0, 0x0, 0x0, 0x2f, 0xff	},
};

static Vtx lowgradient_tri_2ndrow[12] =  {
        {        -40,  30, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x00	},
        {        -20,  30, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x8f	},
        {        -30,  40, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x2f	},

        {        -20,  30, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x00	},
        {          0,  30, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x8f	},
        {        -10,  40, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x2f	},

        {          0,  30, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x00	},
        {         20,  30, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x8f	},
        {         10,  40, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x2f	},

        {         20,  30, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x00	},
        {         40,  30, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x8f	},
        {         30,  40, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x2f	},
};

static Vtx lowgradient_tri_3rdrow[12] =  {
        {        -40,  20, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x00	},
        {        -20,  20, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x8f	},
        {        -30,  30, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x2f	},

        {        -20,  20, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x00	},
        {          0,  20, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x8f	},
        {        -10,  30, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x2f	},

        {          0,  20, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x00	},
        {         20,  20, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x8f	},
        {         10,  30, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x2f	},

        {         20,  20, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x00	},
        {         40,  20, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x8f	},
        {         30,  30, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x2f	},
};

static Vtx lowgradient_tri_4throw[12] =  {
        {        -40,  10, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x00	},
        {        -20,  10, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x8f	},
        {        -30,  20, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x2f	},

        {        -20,  10, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x00	},
        {          0,  10, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x8f	},
        {        -10,  20, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0x2f	},

        {          0,  10, 0, 0, 0, 0, 0x2f, 0x0, 0x0, 0x00	},
        {         20,  10, 0, 0, 0, 0, 0x0, 0x2f, 0x0, 0x8f	},
        {         10,  20, 0, 0, 0, 0, 0x0, 0x0, 0x2f, 0x2f	},

        {         20,  10, 0, 0, 0, 0, 0x2f, 0x0, 0x0, 0x00	},
        {         40,  10, 0, 0, 0, 0, 0x0, 0x2f, 0x0, 0x8f	},
        {         30,  20, 0, 0, 0, 0, 0x0, 0x0, 0x2f, 0x2f	},
};

static Vtx lowgradient_quad_5throw[12] =  {
        {        -40,   0, 0, 0, 0, 0, 0xb, 0xb, 0xb, 0xff	},
        {        -20,   0, 0, 0, 0, 0, 0xb, 0xb, 0xb, 0xff	},
        {        -30,  10, 0, 0, 0, 0, 0xb, 0xb, 0xb, 0xff	},
        {        -30, -10, 0, 0, 0, 0, 0xb, 0xb, 0xb, 0xff	},

        {        -20,   0, 0, 0, 0, 0, 0xb, 0xb, 0xb, 0xff	},
        {          0,   0, 0, 0, 0, 0, 0xb, 0xb, 0xb, 0xff	},
        {        -10,  10, 0, 0, 0, 0, 0xb, 0xb, 0xb, 0xff	},
        {        -10, -10, 0, 0, 0, 0, 0xb, 0xb, 0xb, 0xff	},

        {          0,   0, 0, 0, 0, 0, 0xb, 0xb, 0xb, 0xff	},
        {         20,   0, 0, 0, 0, 0, 0xb, 0xb, 0xb, 0xff	},
        {         10,  10, 0, 0, 0, 0, 0xb, 0xb, 0xb, 0xff	},
        {         10, -10, 0, 0, 0, 0, 0xb, 0xb, 0xb, 0xff	},
};

Gfx rdpcov_dithertest[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

/* top row, alpha dither = off, cycle thru color dither modes */
    gsSPVertex(&lowgradient_tri_toprow, 12, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),

    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSP1Triangle(0, 1, 2, 0),

    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSP1Triangle(3, 4, 5, 0),

    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_BAYER),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSP1Triangle(6, 7, 8, 0),

#ifdef NOISE
    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_NOISE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSP1Triangle(9, 10, 11, 0),
#endif

/* 2nd row, alpha dither = pattern, cycle thru color dither modes */
    gsSPVertex(&lowgradient_tri_2ndrow, 12, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),

    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetAlphaDither(G_AD_PATTERN),
    gsSP1Triangle(0, 1, 2, 0),

    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetAlphaDither(G_AD_PATTERN),
    gsSP1Triangle(3, 4, 5, 0),

    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_BAYER),
    gsDPSetAlphaDither(G_AD_PATTERN),
    gsSP1Triangle(6, 7, 8, 0),

#ifdef NOISE
    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_NOISE),
    gsDPSetAlphaDither(G_AD_PATTERN),
    gsSP1Triangle(9, 10, 11, 0),
#endif

/* 3rd row, alpha dither = ~pattern, cycle thru color dither modes */
    gsSPVertex(&lowgradient_tri_3rdrow, 12, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),

    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetAlphaDither(G_AD_NOTPATTERN),
    gsSP1Triangle(0, 1, 2, 0),

    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetAlphaDither(G_AD_NOTPATTERN),
    gsSP1Triangle(3, 4, 5, 0),

    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_BAYER),
    gsDPSetAlphaDither(G_AD_NOTPATTERN),
    gsSP1Triangle(6, 7, 8, 0),

#ifdef NOISE
    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_NOISE),
    gsDPSetAlphaDither(G_AD_NOTPATTERN),
    gsSP1Triangle(9, 10, 11, 0),
#endif

/* 4th row, alpha dither = off + noise */
    gsSPVertex(&lowgradient_tri_4throw, 12, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),

    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSP1Triangle(0, 1, 2, 0),

#ifdef NOISE
    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetAlphaDither(G_AD_NOISE),
    gsSP1Triangle(3, 4, 5, 0),
#endif

#ifdef NOISE
    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetAlphaDither(G_AD_NOISE),
    gsSP1Triangle(6, 7, 8, 0),
#endif

    gsDPPipeSync(),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetAlphaDither(G_AD_NOTPATTERN),
    gsSP1Triangle(9, 10, 11, 0),

/* 5th row, 1/2 cycle quads w/interior edges */
    gsSPVertex(&lowgradient_quad_5throw, 12, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),

    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetAlphaDither(G_AD_NOTPATTERN),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 1, 3, 0),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_PASS2),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_OPA_SURF2),
    gsSP1Triangle(4, 5, 6, 0),
    gsSP1Triangle(4, 5, 7, 0),

    gsDPPipeSync(),
    gsDPSetScissor(G_SC_ODD_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT-1),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSP1Triangle(8, 9, 10, 0),
    gsSP1Triangle(8, 9, 11, 0),

    gsDPPipeSync(),
    gsDPSetScissor(G_SC_EVEN_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT-1),
    gsSP1Triangle(8, 9, 10, 0),
    gsSP1Triangle(8, 9, 11, 0),

    gsSPEndDisplayList(),
};
/* end of case 40 */

/*
 * Test 51, Frame 51:
 *
 * ew critical path test
 *
 * Mon Oct  2 11:13:46 PDT 1995
 *
 */
/* static Vtx ewcriticalpath_vtx[3] =  {
        {        -40,   0, 0, 0, 0, 0, 0xb, 0xb, 0xb, 0xff	},
        {        -20,   0, 0, 0, (31<<6), 0, 0xb, 0xb, 0xb, 0xff	},
        {        -30,  10, 0, 0, 0, (31<<6), 0xb, 0xb, 0xb, 0xff	},
        };
Gfx rdpcov_ewcritical_path[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(RGBA16grid, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&ewcriticalpath_vtx, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
}; */

/*
 * Test 51, Frame 51:
 *
 * CS EW critical path test 
 *
 * Mon Oct  2 20:07:51 PDT 1995
 *
 */

/* a texture */
#include "CSEWCritical_tex.h"

static Vtx CSEWcrtical_q1[4] =  {
        {        -64,  64, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff	},
        {         64,  64, 0, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff	},
        {         64, -64, 0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff	},
        {        -64, -64, 0, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff	},
};

Gfx rdpcov_CSEWcritical_list[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BOTH),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPLoadTextureBlock(CSEWCritical_tex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0,
			 G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
			 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCycleType(G_CYC_COPY),
    gsSPTextureRectangle(150<<2, 150<<2, (150+7)<<2, (150+7)<<2, G_TX_RENDERTILE, 0<<5, 0<<5, 4<<10, 4<<10),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetScissor(G_SC_EVEN_INTERLACE, 0, 0, SCREEN_WD-1, SCREEN_HT-1),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
    gsSPVertex(&CSEWcrtical_q1, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};
/* end of case 1 */

/*
 * ADD TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx display list must be extern'd in rdpcov.h, then
 * added to the 'testList' table in rdpcov.c
 *
 */
