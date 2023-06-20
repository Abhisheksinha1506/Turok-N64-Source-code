
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
 *
 *
 * This file holds tiny display list segments that are 'static' data.
 * If you feel the urge to modify a test, see the comment at
 * the top of main.c for details.
 *
 */

#include <ultra64.h>
#include "gng.h"
#include "dldriver.h"
#include "rdp6M.h"
#include "cs.h"

/*
 * Test conventions:
 *
 * Data variable names can be about anything, as long as they are unique
 * and consistent in the table entry.
 *
 * In order to get around compiler weirdness, the table of tests
 * is in rdpverif.c, and the Gfx rdpfb_lists must be extern'd in rdpverif.h
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

Gfx rdp6M_placebo_dl[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD,
                                OS_K0_TO_PHYSICAL(L26R)),
    gsSPVertex(&place_vtx, 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};
/* end of case -1 */

Gfx rdp6M_test1[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD,
                                OS_K0_TO_PHYSICAL(L26R)),
    gsSPVertex(&place_vtx, 5, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsSP1Triangle(1, 4, 2, 0),
    gsSP1Triangle(2, 4, 3, 0),
    gsSP1Triangle(3, 4, 0, 0),
    gsSPEndDisplayList(),
};

#include "RGBA16grid.h"

static Vtx q1[8] =  {
#ifdef ONETRI
        {        -64,  64, -5, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff
},
        {         64,  64, -5, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff
},
        {         64, -64, -5, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff
},
        {        -64, -64, -5, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff
},
#else
        {        -64,  64, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff },
        {         64,  64, 0, 0, (31 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff
},
        {         64, -64, 0, 0, (31 << 6), (31 << 6), 0x1f, 0x1f, 0xff, 0xff
},
        {        -64, -64, 0, 0, ( 0 << 6), (31 << 6), 0, 0x1f, 0xff, 0xff
},
#endif

        /* second 4 points used for perspective test... */
        { -64,  0,  64, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff       },
        {  64,  0,  64, 0, (127 << 6), ( 0 << 6), 0x1f, 0, 0xff, 0xff   },
        {  64,  0, -64, 0, (127 << 6), (127 << 6), 0x1f, 0x1f, 0xff, 0xff },
        { -64,  0, -64, 0, ( 0 << 6), (127 << 6), 0, 0x1f, 0xff, 0xff   },
};


Gfx rdp6M_square1[MAX_STATIC_GFX_SIZE] = {
    gsSPClearGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD,
                                OS_K0_TO_PHYSICAL(L26R)),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(rdp6M_RGBA16grid, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&(q1[0]), 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(128, 128, 0, G_TX_RENDERTILE, G_OFF), /* done; turn texture off*/
    gsSPEndDisplayList(),
};
