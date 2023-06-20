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

extern Vtx trivtx10a[];
extern Vtx trivtx10b[];
extern Vtx trivtx10c[];
extern Vtx trivtx10d[];
extern Vtx trivtx10e[];
extern Vtx trivtx10f[];
extern Vtx trivtx10g[];
extern Vtx trivtx10h[];
extern Vtx trivtx10i[];
extern Vtx trivtx10j[];
extern Vtx trivtx10k[];
extern Vtx trivtx10l[];
extern Vtx trivtx11a[];
extern Vtx trivtx11b[];
extern Vtx trivtx11c[];
extern Vtx trivtx11d[];
extern Vtx trivtx11i[];
extern Vtx trivtx11j[];
extern Vtx trivtx11k[];
extern Vtx trivtx11l[];
extern Vtx trivtx12a[];
extern Vtx trivtx12b[];
extern Vtx trivtx12c[];

extern Gfx rdpew_placebo_dl[];

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

/* end of case -1 */
Gfx rdpew_big_image_test[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(0x0C084148,0),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage(5, G_IM_SIZ_16b, 1024, cfb_16_a),
    gsDPPipeSync(),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1024, cfb_16_a),
    gsDPSetCycleType(G_CYC_1CYCLE),
    /*
     * use scissoring to lower number of clocks to complete sim
     */
    gsDPSetScissor(G_SC_NON_INTERLACE, 1018,0,1023,1023),
    gsSPDisplayList(rdpew_triangle15),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,1023,5),
    gsSPDisplayList(rdpew_triangle15),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,1018,1023,1023),
    gsSPDisplayList(rdpew_triangle15),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,5,1023),
    gsSPDisplayList(rdpew_triangle15),

    gsDPSetScissor(G_SC_NON_INTERLACE, 512,0,517,1023),
    gsSPDisplayList(rdpew_triangle15),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,513,1023,518),
    gsSPDisplayList(rdpew_triangle15),

    gsSPEndDisplayList(),
};


/* end of case 15 */

/*
 * Test 16, Frame 16:
 *
 *
 * wed Oct 19 1994
 *
 * Draw 8 identical triangles with the scissor box scissoring each
 * at a different subpixel location.
 *
 */

/* up facing triangles */
static Vtx trivtx16a[15] =  {
        {      10,   15, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      15,   10, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      20,   15, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {      25,   15, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      30,   10, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      35,   15, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {      40,   15, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      45,   10, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      50,   15, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {      55,   15, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      60,   10, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      65,   15, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {      70,   15, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      75,   10, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      80,   15, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* down facing triangles */
static Vtx trivtx16b[15] =  {
        {      10,   20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      15,   25, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      20,   20, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {      25,   20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      30,   25, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      35,   20, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {      40,   20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      45,   25, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      50,   20, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {      55,   20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      60,   25, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      65,   20, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {      70,   20, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      75,   25, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      80,   20, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* right facing triangles */
static Vtx trivtx16c[15] =  {
        {      90,   15, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {      90,   10, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {     100,   13, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {     110,   15, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {     110,   10, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {     120,   13, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {     130,   15, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {     130,   10, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {     140,   13, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {     150,   15, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {     150,   10, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {     160,   13, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {     170,   15, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {     170,   10, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {     180,   13, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

/* right facing triangles */
static Vtx trivtx16d[15] =  {
        {     100,   25, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {     100,   20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {      90,   23, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {     120,   25, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {     120,   20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {     110,   23, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {     140,   25, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {     140,   20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {     130,   23, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {     160,   25, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {     160,   20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {     150,   23, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
        {     180,   25, 0, 0, 0, 0, 0xff, 0x00, 0x00, 0xff	},
        {     180,   20, 0, 0, 0, 0, 0x00, 0xff, 0x00, 0xff	},
        {     170,   23, 0, 0, 0, 0, 0x00, 0x00, 0xff, 0xff	},
};

Gfx rdpew_triangle16[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsDPSetRenderMode(0x0C084148,0),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,320,240),

    gsSPVertex(&trivtx16a, 15, 0),
    gsSP1Triangle( 0, 1, 2, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0,11.00,320,14.75),
    gsSP1Triangle( 3, 4, 5, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0,11.25,320,14.50),
    gsSP1Triangle( 6, 7, 8, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0,11.50,320,14.25),
    gsSP1Triangle( 9,10,11, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0,11.75,320,14.00),
    gsSP1Triangle(12,13,14, 0),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,320,240),

    gsSPVertex(&trivtx16b, 15, 0),
    gsSP1Triangle( 0, 1, 2, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0,21.00,320,24.75),
    gsSP1Triangle( 3, 4, 5, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0,21.25,320,24.50),
    gsSP1Triangle( 6, 7, 8, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0,21.50,320,24.25),
    gsSP1Triangle( 9,10,11, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0,21.75,320,24.00),
    gsSP1Triangle(12,13,14, 0),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,320,240),

    gsSPVertex(&trivtx16c, 15, 0),
    gsSP1Triangle( 0, 1, 2, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 111.00,0,119.75,240),
    gsSP1Triangle( 3, 4, 5, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 131.25,0,139.50,240),
    gsSP1Triangle( 6, 7, 8, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 151.50,0,159.25,240),
    gsSP1Triangle( 9,10,11, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 171.75,0,179.00,240),
    gsSP1Triangle(12,13,14, 0),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,320,240),

    gsSPVertex(&trivtx16d, 15, 0),
    gsSP1Triangle( 0, 1, 2, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 111.00,0,119.75,240),
    gsSP1Triangle( 3, 4, 5, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 131.25,0,139.50,240),
    gsSP1Triangle( 6, 7, 8, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 151.50,0,159.25,240),
    gsSP1Triangle( 9,10,11, 0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 171.75,0,179.00,240),
    gsSP1Triangle(12,13,14, 0),

    gsSPEndDisplayList(),
};
/* end of case 16 */

/*
 * Test 17, Frame 17:
 *
 *
 * wed Oct 19 1994
 * 
 * The intention of this case is to test interlace mode.
 * Right now the .rdp file must be modified to turn
 * interlacing on.  (How to turn interlacing on from
 * the gsDPSetScissor macro???)
 *
 */
Gfx rdpew_triangle17[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsDPSetRenderMode(0x0C084148,0),

    gsDPSetScissor(G_SC_NON_INTERLACE, 0,0,320,240),
    
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
/* end of case 17 */

/*
 * Test 18, Frame 18:
 *
 *
 * wed Oct 19 1994
 * with pixel size=16:
 * different cycle types.  Uses data from test 16 
 * 
 * try different cycle types with 16 bit pixels on 8 triangles.
 *
 */
Gfx rdpew_triangle18[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, cfb_16_a),
    gsDPSetFillColor(GPACK_RGBA5551(0,0,0,1) << 16 | GPACK_RGBA5551(0,0,0,1)),
    gsDPPipeSync(),

    gsDPSetRenderMode(0x0C084148,0),

    gsSPVertex(&trivtx16a, 15, 0),
    gsSP1Triangle( 0, 1, 2, 0),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSP1Triangle( 3, 4, 5, 0),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSP1Triangle( 6, 7, 8, 0),
/**					Illegal operation ?
    gsDPSetCycleType(G_CYC_COPY),
    gsSP1Triangle( 9,10,11, 0),
    gsDPSetCycleType(G_CYC_FILL),
    gsSP1Triangle(12,13,14, 0),
**/

    gsSPEndDisplayList(),
};
/* end of case 18 */

/*
 * Test 19, Frame 19:
 *
 *
 * wed Oct 19 1994
 * with pixel size=32:
 * different cycle types.  Uses data from test 16 
 * 
 * try different cycle types with 32 bit pixels on 8 triangles.
 *
 */
Gfx rdpew_triangle19[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, 320, cfb_16_a),
    gsDPSetFillColor(0xffffffff),
    gsDPPipeSync(),

    gsDPSetRenderMode(0x0C084148,0),

    gsSPVertex(&trivtx16a, 15, 0),
    gsSP1Triangle( 0, 1, 2, 0),

    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSP1Triangle( 3, 4, 5, 0),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSP1Triangle( 6, 7, 8, 0),
/****
    gsDPSetCycleType(G_CYC_COPY),
    gsSP1Triangle( 9,10,11, 0),
    gsDPSetCycleType(G_CYC_FILL),
    gsSP1Triangle(12,13,14, 0),
*****/


    gsSPEndDisplayList(),
};
/* end of case 19 */

/*
 * Test 20, Frame 20:
 *
 *
 * wed Oct 19 1994
 * with pixel size=8:
 * different cycle types.  Uses data from test 16 
 * 
 * try different cycle types with 8 bit pixels on 8 triangles.
 *
 */
Gfx rdpew_triangle20[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_8b, 320, cfb_16_a),
    gsDPSetFillColor(0xffffffff),
    gsDPPipeSync(),

    gsDPSetRenderMode(0x0C084148,0),

    gsSPVertex(&trivtx16a, 15, 0),
    gsSP1Triangle( 0, 1, 2, 0),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSP1Triangle( 3, 4, 5, 0),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSP1Triangle( 6, 7, 8, 0),
/*****
    gsDPSetCycleType(G_CYC_COPY),
    gsSP1Triangle( 9,10,11, 0),
    gsDPSetCycleType(G_CYC_FILL),
    gsSP1Triangle(12,13,14, 0),
*****/

    gsSPEndDisplayList(),
};
/* end of case 20 */

/*
 * Test 21, Frame 21:
 *
 *
 * wed Oct 19 1994
 * with pixel size=4:
 * different cycle types.  Uses data from test 16 
 * 
 * try different cycle types with 4 bit pixels on 8 triangles.
 *
 */
Gfx rdpew_triangle21[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),

    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, cfb_16_a),
    gsDPSetFillColor(0xffffffff),
    gsDPPipeSync(),

    gsDPSetRenderMode(0x0C084148,0),

    gsSPVertex(&trivtx16a, 15, 0),
    gsSP1Triangle( 0, 1, 2, 0),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSP1Triangle( 3, 4, 5, 0),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSP1Triangle( 6, 7, 8, 0),
/****
    gsDPSetCycleType(G_CYC_COPY),
    gsSP1Triangle( 9,10,11, 0),
    gsDPSetCycleType(G_CYC_FILL),
    gsSP1Triangle(12,13,14, 0),
*****/

    gsSPEndDisplayList(),
};
/* end of case 21 */

/*
 * Test 22, Frame 22:
 *
 *
 * Used for odd interlacing test
 *
 */
Gfx rdpew_triangle22[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),


/*
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),

    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, cfb_16_a),
    gsDPPipeSync(),

    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, cfb_16_a),
    gsDPSetCycleType(G_CYC_1CYCLE),
*/


    gsDPSetScissor(G_SC_ODD_INTERLACE, 0,0,320,240),

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

    gsSPEndDisplayList(),
};
/* end of case 22 */

/*
 * Test 23, Frame 23:
 *
 *
 * Used for even interlacing test
 *
 */
Gfx rdpew_triangle23[MAX_STATIC_GFX_SIZE] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),


    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),

    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, cfb_16_a),
    gsDPPipeSync(),

    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, cfb_16_a),
    gsDPSetCycleType(G_CYC_1CYCLE),


    gsDPSetScissor(G_SC_EVEN_INTERLACE, 0,0,320,240),

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

    gsSPEndDisplayList(),
};
/* end of case 23 */

/*
 * Test 24, Frame 24:
 *
 *
 * not used yet
 *
 */
Gfx rdpew_triangle24[MAX_STATIC_GFX_SIZE] = {
    gsSPEndDisplayList(),
};
/* end of case 24 */

/*
 * Test 25, Frame 25:
 *
 * 
 * not used yet
 *
 */
Gfx rdpew_triangle25[MAX_STATIC_GFX_SIZE] = {
    gsSPEndDisplayList(),
};
/* end of case 25 */

/*
 * Test 30, Frame 30:
 *
 * A 2K poly skull centered.
 * Fri Nov 25 11:19:06 PST 1994
 *
 */
#include "skull_vtx.h"

Gfx rdpew_skull_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),

#include "skull_tri.h"

    gsSPEndDisplayList(),
};
/* end of case 30 */

/*
 * Test 31, Frame 31:
 *
 * A 1K poly VW centered.
 * Fri Nov 25 11:19:25 PST 1994
 *
 */
#if 1
#include "vw_vtx.h"
#endif

Gfx rdpew_vw_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPClearGeometryMode(G_CULL_FRONT),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),

#if 1
#include "vw_tri.h"
#endif

    gsSPEndDisplayList(),
};
/* end of case 31 */

/*
 * Test 32, Frame 32:
 *
 * A 3K poly cow centered.
 * Fri Nov 25 11:46:29 PST 1994
 *
 */
#if 1
#include "cow_vtx.h"
#endif

Gfx rdpew_cow_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),

#if 1
#include "cow_tri.h"
#endif

    gsSPEndDisplayList(),
};
/* end of case 32 */

/* Test 33 uses the above data... */

/*
 * Test 34, Frame 34:
 *
 * A 500 polygon paperclip. Tests thin polygons.
 * Sat Nov 26 14:43:20 PST 1994
 *
 */
#include "clip_vtx.h"

Gfx rdpew_clip_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),

#include "clip_tri.h"

    gsSPEndDisplayList(),
};
/* end of case 34 */

/*
 * Test 35, Frame 35:
 *
 * A 3K polygon rocking chair.
 * Mon Nov 28 14:46:01 PST 1994
 *
 */
#include "chair_vtx.h"

Gfx rdpew_chair_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),

#include "chair_tri.h"

    gsSPEndDisplayList(),
};

#define FLOOR_R	205
#define FLOOR_G	183
#define FLOOR_B	158
#define FLOOR_Y	0
static Vtx chair_floor_vtx[5] =  {
        {   -300, FLOOR_Y,  300, 0, 0, 0, FLOOR_R, FLOOR_G, FLOOR_B, 0xff },
        {    300, FLOOR_Y,  300, 0, 0, 0, FLOOR_R, FLOOR_G, FLOOR_B, 0xff },
        {    300, FLOOR_Y, -300, 0, 0, 0, FLOOR_R, FLOOR_G, FLOOR_B, 0xff },
        {   -300, FLOOR_Y, -300, 0, 0, 0, FLOOR_R, FLOOR_G, FLOOR_B, 0xff },
        {      0, FLOOR_Y,    0, 0, 0, 0, FLOOR_R, FLOOR_G, FLOOR_B, 0xff },
};

Gfx rdpew_chair_floor_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&chair_floor_vtx, 5, 0),
    gsSP1Triangle(0, 1, 4, 0),
    gsSP1Triangle(1, 2, 4, 0),
    gsSP1Triangle(2, 3, 4, 0),
    gsSP1Triangle(3, 0, 4, 0),
    gsSPEndDisplayList(),
};

/* end of case 35 */

/*
 * Test 36, Frame 36:
 *
 * A 4K B-25
 * Wed Nov 30 17:31:04 PST 1994
 *
 */
#if 0
#include "b25_vtx.h"
#endif

Gfx rdpew_b25_dl[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsSPSetGeometryMode(G_SHADE),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),

#if 0
#include "b25_tri.h"
#endif

    gsSPEndDisplayList(),
};
/* end of case 36 */

/*
 * ADD TEST CASE:
 * Put data and display list for the new case above here:
 *
 * The Gfx rdpew_display list must be extern'd in rdpverif.h, then
 * added to the 'testList' table in rdpverif.c
 *
 */
