
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
 * File:	rdpverif.c
 * Creator:	hsa@sgi.com
 * Create Date:	Fri Oct 14 11:54:21 PDT 1994
 *
 *
 * This application is a test-bed of single frame tests for RDP
 * verification. The idea is that each frame possibly uses a different
 * dataset (see static.c) to render a particular test.
 *
 * This is the TEST-SPECIFIC file, see comment in main.c for more
 * information.
 *
 * TO ADD A TEST CASE:
 * New test cases require that you define the display list and add
 * a few simple things in the files rspverif.h, rspverif.c, static.c.
 * All locations are marked with comments that say "ADD TEST CASE"
 * and give some hints what you need to do there. See main.c for
 * detailed instructions.
 *
 * Fri Oct 14 11:21:49 PDT 1994
 *
 */

#include <ultra64.h>

#include "dldriver.h"
#include "toplevel.h"
#include "rdptex.h"
#include "cs.h"

extern Gfx rww_lodRGBA16MM[];
int frameNum = 0;

static int f20 = 0;
static int f21 = 0;
static int f22 = 0;
static float theta22 = 0.0;

/* procedure to do the work for placebo case: */
void
rdptex_testCasePlacebo(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);
    guLookAt(&dynamicp->viewing, 
	     0, 0, 200, 0, 0, 0, 0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, perspNorm);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/* procedure to do the work for test 0: */
void
rdptex_testCaseProc0(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);
    guLookAt(&dynamicp->viewing, 
	     0, 0, 200, 0, 0, 0, 0, 1, 0);
    /*
	     200, 200, 200, 0, 0, 0, 0, 1, 0);
     */

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, perspNorm);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdptex_testCaseProc1(Dynamic *dynamicp, Gfx *module_test)
{
#ifdef ONETRI
    static float	theta = 22.0;

    guOrtho(&dynamicp->projection,
	    -SCREEN_WD/2.0, SCREEN_WD/2.0,
	    -SCREEN_HT/2.0, SCREEN_HT/2.0, 1, 10.0, 1.0);
#else
    static float	theta = -15.0;

    guOrtho(&dynamicp->projection,
	    -SCREEN_WD/2.0, SCREEN_WD/2.0,
	    -SCREEN_HT/2.0, SCREEN_HT/2.0, -1, 1, 1.0);
#endif

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdptex_testCaseProc2(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    u16   		perspNorm;


    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 100, 4000, 1.0);
    guLookAt(&dynamicp->viewing, 
	     0, 50, 250, 0, 0, 0, 0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 0.0, 1.0, 0.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, perspNorm);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdptex_testCaseProc3(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;

    guOrtho(&dynamicp->projection,
	    -SCREEN_WD/2.0, SCREEN_WD/2.0,
	    -SCREEN_HT/2.0, SCREEN_HT/2.0, -1, 1, 1.0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/*
 *  Test 20, Frame 20
 *
 *  Scroll a texture map when entire texture fits in Tmem
 *
 */
void
rdptex_testCaseProc20(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    int			cur_s[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int			cur_t[] = {0, 1, 2, 3, 4, 5, 6, 7, 6, 5,  4,  3,  2, 1};
    int  		i, j, max_s, max_t;
    u16   		perspNorm;

    max_s = sizeof(cur_s) / sizeof(int);
    max_t = sizeof(cur_t) / sizeof(int);

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);

    guLookAt(&dynamicp->viewing, 
	     0, 0, 200, 0, 0, 0, 0, 1, 0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

      gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->identity)),
	        G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);

    gSPPerspNormalize(glistp++, perspNorm);

    /*
     *  Create display list
     */

    gSPClearGeometryMode(glistp++,G_ZBUFFER);
    gSPClearGeometryMode(glistp++,G_CULL_BACK);
    gSPTexture(glistp++,0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++,G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineMode(glistp++,G_CC_MODULATEI, G_CC_MODULATEI);
    gDPSetTextureFilter(glistp++,G_TF_BILERP);
    gDPLoadTextureBlock_4b(glistp++, I4oddcheck, G_IM_FMT_I, 32, 32, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    /* animated section */
    gDPTileSync(glistp++);
    gDPSetTileSize(glistp++, G_TX_RENDERTILE, 
	cur_s[f20 % max_s] << 2, cur_t[f20 % max_t] << 2, 31 << 2, 31 << 2);
    /* end animated section */

    guTranslate(&dynamicp->move_x, 34.0,  0.0, 0.0);
    guTranslate(&dynamicp->move_y,  0.0, 34.0, 0.0);
    guTranslate(&dynamicp->identity, 0.0,  0.0, 0.0);

    /* make 3x3 grid of faces */
    for(i = 0; i < 3; i++)
    {
      for(j = 0; j < 3; j++)
      {
        gSPVertex(glistp++,&txfmt_q20, 4, 0);
        gSP1Triangle(glistp++,0, 1, 2, 0);
        gSP1Triangle(glistp++,0, 2, 3, 0);

        gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->move_x)),
	          G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

      }

      gSPPopMatrix(glistp++, G_MTX_MODELVIEW);

      gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->move_y)),
	        G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

      gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->identity)),
	        G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    }

    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
    gSPTexture(glistp++,128, 128, 0, G_TX_RENDERTILE, G_OFF); /* done; turn texture off */

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdptex_testCaseProc68(Dynamic *dynamicp, Gfx *module_test)
{
 f20 = 0.0;
 rdptex_testCaseProc20(dynamicp, module_test);
}

void
rdptex_testCaseProc69(Dynamic *dynamicp, Gfx *module_test)
{
 f20 = 1.0;
 rdptex_testCaseProc20(dynamicp, module_test);
}

void
rdptex_testCaseProc70(Dynamic *dynamicp, Gfx *module_test)
{
 f20 = 2.0;
 rdptex_testCaseProc20(dynamicp, module_test);
}

void
rdptex_testCaseProc71(Dynamic *dynamicp, Gfx *module_test)
{
 f20 = 3.0;
 rdptex_testCaseProc20(dynamicp, module_test);
}

void
rdptex_testCaseProc72(Dynamic *dynamicp, Gfx *module_test)
{
 f20 = 4.0;
 rdptex_testCaseProc20(dynamicp, module_test);
}

void
rdptex_testCaseProc73(Dynamic *dynamicp, Gfx *module_test)
{
 f20 = 5.0;
 rdptex_testCaseProc20(dynamicp, module_test);
}

void
rdptex_testCaseProc74(Dynamic *dynamicp, Gfx *module_test)
{
 f20 = 6.0;
 rdptex_testCaseProc20(dynamicp, module_test);
}


void
rdptex_testCaseProc75(Dynamic *dynamicp, Gfx *module_test)
{
 f20 = 7.0;
 rdptex_testCaseProc20(dynamicp, module_test);
}

void
rdptex_testCaseProc76(Dynamic *dynamicp, Gfx *module_test)
{
 f20 = 8.0;
 rdptex_testCaseProc20(dynamicp, module_test);
}

void
rdptex_testCaseProc77(Dynamic *dynamicp, Gfx *module_test)
{
 f20 = 9.0;
 rdptex_testCaseProc20(dynamicp, module_test);
}

void
rdptex_testCaseProc78(Dynamic *dynamicp, Gfx *module_test)
{
 f20 = 10.0;
 rdptex_testCaseProc20(dynamicp, module_test);
}

void
rdptex_testCaseProc79(Dynamic *dynamicp, Gfx *module_test)
{
 f20 = 11.0;
 rdptex_testCaseProc20(dynamicp, module_test);
}

void
rdptex_testCaseProc80(Dynamic *dynamicp, Gfx *module_test)
{
 f20 = 12.0;
 rdptex_testCaseProc20(dynamicp, module_test);
}

void
rdptex_testCaseProc81(Dynamic *dynamicp, Gfx *module_test)
{
 f20 = 13.0;
 rdptex_testCaseProc20(dynamicp, module_test);
}

/*
 *  Test 21, Frame 21
 *
 *  Scroll a texture when texture is larger than Tmem
 *
 */

void
rdptex_testCaseProc21(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = 0.0;
    int			cur_s[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int			cur_t[] = {2, 4, 6, 8, 10,  8,  6,  4,  2,  0};
    int			inc_s;
    int			inc_t;
    int  		i, j, maxframeNum;
    u16   		perspNorm;

    maxframeNum = (sizeof(cur_s) / sizeof(int));
  
    if(f21 > (maxframeNum-1))
    {
      theta += 5.0;
      f21 %= maxframeNum;
    }
 
    gDPSetTexturePersp(glistp++, G_TP_PERSP);

    guRotate(&dynamicp->modeling, theta, 0.0, 1.0, 0.0);

    guPerspective(&dynamicp->projection,&perspNorm,
		  33, 320.0/240.0, 1, 500, 1.0);

    guLookAt(&dynamicp->viewing, 
	     0, 0, 200, 0, 0, 0, 0, 1, 0);

    gSPPerspNormalize(glistp++, perspNorm);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
              G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    guTranslate(&dynamicp->move_x, 17.0,  0.0, 0.0);
    guTranslate(&dynamicp->move_y,  0.0, 17.0, 0.0);
    guTranslate(&dynamicp->identity, 0.0,  0.0, 0.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->identity)),
	        G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);

    /*
     *  Create display list
     */

    gSPClearGeometryMode(glistp++,G_ZBUFFER);
    gSPClearGeometryMode(glistp++,G_CULL_BACK);
    gSPTexture(glistp++,0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++,G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gDPSetCombineMode(glistp++,G_CC_DECALRGB, G_CC_DECALRGB);
    gDPSetTextureFilter(glistp++,G_TF_BILERP);



    /* make 3x3 grid of faces */
    for(inc_t = cur_t[f21], i = 0; i < 6; i++, inc_t += 31)
    {
      for(inc_s = cur_s[f21], j = 0; j < 8; j++, inc_s += 31)
      {
        /* animated section */
        gDPLoadTextureTile(glistp++, RGBA16mario, G_IM_FMT_RGBA, G_IM_SIZ_16b, 
			 268, 237, 
			 inc_s, inc_t, MIN(268,inc_s+31), MIN(237,inc_t+31), 0,
                         G_TX_NOMIRROR, G_TX_NOMIRROR,
                         G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        gDPTileSync(glistp++);
        gDPSetTileSize(glistp++, G_TX_RENDERTILE, 0, 0, 31 << 2, 31 << 2);

        gSPVertex(glistp++,&txfmt_q21, 4, 0);
        gSP1Triangle(glistp++,0, 1, 2, 0);
        gSP1Triangle(glistp++,0, 2, 3, 0);

        gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->move_x)),
	          G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
      }

      gSPPopMatrix(glistp++, G_MTX_MODELVIEW);

      gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->move_y)),
	        G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
      gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->identity)),
	        G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    }
    /* end animated section */

    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
    gSPTexture(glistp++,128, 128, 0, G_TX_RENDERTILE, G_OFF); /* done; turn texture off */

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdptex_testCaseProc82(Dynamic *dynamicp, Gfx *module_test)
{
  f21 = 0.0;
  rdptex_testCaseProc21(dynamicp, module_test);
}

void
rdptex_testCaseProc83(Dynamic *dynamicp, Gfx *module_test)
{
  f21 = 1.0;
  rdptex_testCaseProc21(dynamicp, module_test);
}

void
rdptex_testCaseProc84(Dynamic *dynamicp, Gfx *module_test)
{
  f21 = 2.0;
  rdptex_testCaseProc21(dynamicp, module_test);
}

void
rdptex_testCaseProc85(Dynamic *dynamicp, Gfx *module_test)
{
  f21 = 3.0;
  rdptex_testCaseProc21(dynamicp, module_test);
}

void
rdptex_testCaseProc86(Dynamic *dynamicp, Gfx *module_test)
{
  f21 = 4.0;
  rdptex_testCaseProc21(dynamicp, module_test);
}

void
rdptex_testCaseProc87(Dynamic *dynamicp, Gfx *module_test)
{
  f21 = 5.0;
  rdptex_testCaseProc21(dynamicp, module_test);
}

void
rdptex_testCaseProc88(Dynamic *dynamicp, Gfx *module_test)
{
  f21 = 6.0;
  rdptex_testCaseProc21(dynamicp, module_test);
}

void
rdptex_testCaseProc89(Dynamic *dynamicp, Gfx *module_test)
{
  f21 = 7.0;
  rdptex_testCaseProc21(dynamicp, module_test);
}

void
rdptex_testCaseProc90(Dynamic *dynamicp, Gfx *module_test)
{
  f21 = 8.0;
  rdptex_testCaseProc21(dynamicp, module_test);
}

void
rdptex_testCaseProc91(Dynamic *dynamicp, Gfx *module_test)
{
  f21 = 9.0;
  rdptex_testCaseProc21(dynamicp, module_test);
}


/*
 *  Test 22, Frame 22
 *
 *  Scroll a small texture map in perspective
 *
 */
void
rdptex_testCaseProc22(Dynamic *dynamicp, Gfx *module_test)
{
    u16   		perspNorm;

    guRotateRPY(&dynamicp->modeling, theta22, 45, theta22);

    guPerspective(&dynamicp->projection,&perspNorm,
                  33, 320.0/240.0, 50, 500, 1.0);

    guLookAt(&dynamicp->viewing,
                0, 0, 200,
                0, 0, 0,
                0, 1, 0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
              G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, perspNorm);

    /*
     *  Create display list
     */

    gSPClearGeometryMode(glistp++,G_ZBUFFER);
    gSPSetGeometryMode(glistp++,G_CULL_BACK);
    gSPTexture(glistp++,0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++,G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineMode(glistp++,G_CC_MODULATEI, G_CC_MODULATEI);
    /* gDPSetCombineMode(glistp++,G_CC_DECALRGB, G_CC_DECALRGB); */
    gDPSetTexturePersp(glistp++, G_TP_PERSP);
    gDPSetTextureFilter(glistp++,G_TF_BILERP);

    gDPLoadTextureTile(glistp++, RGBA16mario_2, G_IM_FMT_RGBA, G_IM_SIZ_16b,
                         32, 32,
                         0, 0, 31, 31, 0,
                         G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                         5, 5,
                         0, 0);

    gDPTileSync(glistp++);
    gDPSetTileSize(glistp++, G_TX_RENDERTILE,
        ((f22 % 32) << 2), 0, 31 << 2, 31 << 2);

    gSPVertex(glistp++,&box_vtx[0], 16, 0);
    gSP1Triangle(glistp++, 0, 1, 2, 0);
    gSP1Triangle(glistp++, 0, 2, 3, 0);

    gDPTileSync(glistp++);
    gDPSetTileSize(glistp++, G_TX_RENDERTILE,
        0, ((f22 % 32) << 2), 31 << 2, 31 << 2);

    gSP1Triangle(glistp++, 4, 5, 6, 0);
    gSP1Triangle(glistp++, 4, 6, 7, 0);

    gDPTileSync(glistp++);
    gDPSetTileSize(glistp++, G_TX_RENDERTILE,
        ((f22 % 32) << 2), ((f22 % 32) << 2), 31 << 2, 31 << 2);

    gSP1Triangle(glistp++, 8, 9, 10, 0);
    gSP1Triangle(glistp++, 8, 10, 11, 0);

    gDPTileSync(glistp++);
    gDPSetTileSize(glistp++, G_TX_RENDERTILE,
        (((f22 % 32)) << 2), 0, 31 << 2, 31 << 2);

    gSP1Triangle(glistp++, 12, 13, 14, 0);
    gSP1Triangle(glistp++, 12, 14, 15, 0);

    gDPTileSync(glistp++);
    gDPSetTileSize(glistp++, G_TX_RENDERTILE,
        0, (((f22 % 32)) << 2), 31 << 2, 31 << 2);

    gSPVertex(glistp++, &box_vtx[16], 8, 0);
    gSP1Triangle(glistp++, 0, 1, 2, 0);
    gSP1Triangle(glistp++, 0, 2, 3, 0);

    gDPTileSync(glistp++);
    gDPSetTileSize(glistp++, G_TX_RENDERTILE,
        (((f22 % 32)) << 2), (((f22 % 32)) << 2), 31 << 2, 31 << 2);

    gSP1Triangle(glistp++, 4, 5, 6, 0);
    gSP1Triangle(glistp++, 4, 6, 7, 0);

    gSPTexture(glistp++,128, 128, 0, G_TX_RENDERTILE, G_OFF); /* done; turn texture off */
    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdptex_testCaseProc92(Dynamic *dynamicp, Gfx *module_test)
{
  f22 = 0.0;
  theta22 = 0.0;
  rdptex_testCaseProc22(dynamicp, module_test);
}

void
rdptex_testCaseProc93(Dynamic *dynamicp, Gfx *module_test)
{
  f22 = 1.0;
  theta22 = 0.5;
  rdptex_testCaseProc22(dynamicp, module_test);
}
  
void
rdptex_testCaseProc94(Dynamic *dynamicp, Gfx *module_test)
{
  f22 = 2.0;
  theta22 = 1.0;
  rdptex_testCaseProc22(dynamicp, module_test);
}

void
rdptex_testCaseProc95(Dynamic *dynamicp, Gfx *module_test)
{
  f22 = 3.0;
  theta22 = 1.5;
  rdptex_testCaseProc22(dynamicp, module_test);
}

void
rdptex_testCaseProc96(Dynamic *dynamicp, Gfx *module_test)
{
  f22 = 4.0;
  theta22 = 2.0;
  rdptex_testCaseProc22(dynamicp, module_test);
}

void
rdptex_testCaseProc97(Dynamic *dynamicp, Gfx *module_test)
{
  f22 = 5.0;
  theta22 = 2.5;
  rdptex_testCaseProc22(dynamicp, module_test);
}

void
rdptex_testCaseProc98(Dynamic *dynamicp, Gfx *module_test)
{
  f22 = 6.0;
  theta22 = 3.0;
  rdptex_testCaseProc22(dynamicp, module_test);
}

void
rdptex_testCaseProc99(Dynamic *dynamicp, Gfx *module_test)
{
  f22 = 7.0;
  theta22 = 3.5;
  rdptex_testCaseProc22(dynamicp, module_test);
}


#include "RGBA16grid_32.h"

void
rdptex_testCaseProc38(Dynamic *dynamicp, Gfx *module_test)
{
    static float        theta = -88.5;
    static float dist = 530;
    static Image im;
    static Image *imp = &im;
    static unsigned char tbuf[4096];
    u16   		perspNorm;

    imp->base = (unsigned char *)&RGBA16grid_32[0];
    imp->fmt  = G_IM_FMT_RGBA;
    imp->siz  = G_IM_SIZ_16b;
    imp->xsize= 32;
    imp->ysize= 32;
    imp->lsize= 32* sizeof(unsigned short);
    imp->addr = 0;
    imp->w    = 32;
    imp->h    = 32;
    imp->s    = 0;
    imp->t    = 0;

    guPerspective(&dynamicp->projection,&perspNorm,
                  80, 320.0/240.0, 10, 2000, 1.0);
		  /*
                  80, 320.0/240.0, 100, 2000, 1.0);
		  */
    guLookAt(&dynamicp->viewing,
             0, 0, dist, 0, 0, 0, 0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 1.0, 0.0, 0.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
              G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, perspNorm);

    /* generate mipmaps, load data and set tiles */
    guLoadTextureBlockMipMap(&glistp, tbuf, imp, 0, 0, G_TX_WRAP | G_TX_NOMIRROR,
        G_TX_WRAP | G_TX_NOMIRROR, 5, 5, G_TX_NOLOD, G_TX_NOLOD, FILTER_WRAP,
	FILTER_WRAP);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

#include "RGBA16grid_32mip.h"

void
rdptex_testCaseProc61(Dynamic *dynamicp, Gfx *module_test)
{
    static float        theta = -88.5;
    static float        dist = 530;
    extern Gfx RGBA16grid_32mip_dl[];
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
                  80, 320.0/240.0, 100, 2000, 1.0);
    guLookAt(&dynamicp->viewing,
             0, 0, dist, 0, 0, 0, 0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 1.0, 0.0, 0.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
              G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, perspNorm);

    /* use pre-generate mipmaps, load data and set tiles */

    gSPDisplayList(glistp++, K0_TO_PHYS(&(RGBA16grid_32mip_dl[0])));

    gSPDisplayList(glistp++, module_test );

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}


void
rdptex_testCaseProc39(Dynamic *dynamicp, Gfx *module_test)
{
    static float theta = -88.5;
    static float dist = 530;
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
                  80, 320.0/240.0, 10, 2000, 1.0);
		  /*
                  80, 320.0/240.0, 100, 2000, 1.0);
		  */
    guLookAt(&dynamicp->viewing,
             0, 0, dist, 0, 0, 0, 0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 1.0, 0.0, 0.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
              G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, perspNorm);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}


void
rdptex_testCaseProc40(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = -17.0;

    guOrtho(&dynamicp->projection,
	    -SCREEN_WD/2.0, SCREEN_WD/2.0,
	    -SCREEN_HT/2.0, SCREEN_HT/2.0, -1, 1, 1.0);

    guRotate(&dynamicp->modeling, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

/*
 * iorand_cosim_regression environment test. This code performs the following
 *	1. procedurally generates the fillmode spirals in left upper quarter.
 *	2. do 1 clock varying texture cases in right upper quarter.
 */

/*
#define MAX_FP_SIZE     30
*/
#define MAX_FP_SIZE     120
#define ARRAY_SIZE      (sizeof(vpx) / sizeof(float))


/*
 *  Determine cubic coefficients for set of points given in
 *  t,y.  Results returned in z.  Number of points is n.
 */
static void
  find_spline_coeffs( int n, float *t, float *y, float *z)
{
  float h[MAX_FP_SIZE],
        b[MAX_FP_SIZE],
        u[MAX_FP_SIZE],
        v[MAX_FP_SIZE];
  int   i;

  for(i = 0; i < n; i++)
  {
    h[i] = t[i+1] - t[i];
    b[i] = (y[i+1] - y[i]) / h[i];
  }

  u[1] = 2.0 * (h[0] + h[1]);
  v[1] = 6.0 * (b[1] - b[0]);

  for( i = 2; i < n-1; i++)
  {
    u[i] = 2.0 * (h[i] + h[i-1]) - (h[i-1] * h[i-1]) / u[i-1];
    v[i] = 6.0 * (b[i] - b[i-1]) - (h[i-1] * v[i-1]) / u[i-1];
  }

  z[n-1] = 0.0;

  for(i = n-2; i >= 1; i--)
    z[i] = (v[i] - h[i] * z[i+1]) / u[i];

  z[0] = 0.0;

}

/*
 *  Evaluate cubic spline at given point.
 *  First determines the interval in t containing x and then
 *  returns Si(x) using nested form of cubic polynomial.
 */
static float
  eval_spline(int n, float *t, float *y, float *z, float x)
{
  float h, b, p, diff;
  int i;

  for(i = n-2; i >= 0; i--)
  {
    diff = x - t[i];
    if(diff >= 0.0)
      break;
  }

  h = t[i+1] - t[i];
  b = ((y[i+1] - y[i]) / h) - h * (z[i+1] + 2.0 * z[i]) / 6.0;
  p = 0.5 * z[i] + diff * (z[i+1] - z[i]) / (6.0 * h);
  p = b + diff * p;
  return(y[i] + diff * p);
}

/*
 *  Create a little database of interesting shapes
 *  that we can fly around in.
 */

void
rdptex_testCaseProc30(Dynamic *dynamicp, Gfx *module_test)
{
  static float	theta = -90.0;
  /*
   *  Enter your flight path way points here
   */
  /*
  static float frame[] = {0, 	15, 	31};
  */
  static float frame[] = {0, 	60, 	121};
  static float   vpx[] = {50, 	-40, 	10};
  static float   vpy[] = {300, 	30, 	300};
  static float   vpz[] = {600, 	370, 	200};
  static float   atx[] = {0, 	-110, 	0};
  static float   aty[] = {50, 	10, 	0};
  static float   atz[] = {0, 	195, 	0};
  static float   upx[] = {0, -0.173648, 0.173648};
  static float   upy[] = {1, 0.9848077, 0.9848077};
  static float   upz[] = {0, 0, 	0};

  static float vpx_c[ARRAY_SIZE];
  static float vpy_c[ARRAY_SIZE];
  static float vpz_c[ARRAY_SIZE];
  static float atx_c[ARRAY_SIZE];
  static float aty_c[ARRAY_SIZE];
  static float atz_c[ARRAY_SIZE];
  static float upx_c[ARRAY_SIZE];
  static float upy_c[ARRAY_SIZE];
  static float upz_c[ARRAY_SIZE];
  static float f = 0;

  float rvpx, rvpy, rvpz;
  float ratx, raty, ratz;
  float rupx, rupy, rupz;
  u16   		perspNorm;

  guPerspective(&dynamicp->projection,&perspNorm,
		33, 320.0/240.0, 200, 2800, 1.0);

  if(frameNum == 41)
  {
    if(f == 0)
    {
      find_spline_coeffs( ARRAY_SIZE, frame, vpx, vpx_c);
      find_spline_coeffs( ARRAY_SIZE, frame, vpy, vpy_c);
      find_spline_coeffs( ARRAY_SIZE, frame, vpz, vpz_c);
      find_spline_coeffs( ARRAY_SIZE, frame, atx, atx_c);
      find_spline_coeffs( ARRAY_SIZE, frame, aty, aty_c);
      find_spline_coeffs( ARRAY_SIZE, frame, atz, atz_c);
      find_spline_coeffs( ARRAY_SIZE, frame, upx, upx_c);
      find_spline_coeffs( ARRAY_SIZE, frame, upy, upy_c);
      find_spline_coeffs( ARRAY_SIZE, frame, upz, upz_c);
    }
    else if (f < 0.0)
      return;

    rvpx = eval_spline(ARRAY_SIZE, frame, vpx, vpx_c, f);
    rvpy = eval_spline(ARRAY_SIZE, frame, vpy, vpy_c, f);
    rvpz = eval_spline(ARRAY_SIZE, frame, vpz, vpz_c, f);
    ratx = eval_spline(ARRAY_SIZE, frame, atx, atx_c, f);
    raty = eval_spline(ARRAY_SIZE, frame, aty, aty_c, f);
    ratz = eval_spline(ARRAY_SIZE, frame, atz, atz_c, f);
    rupx = eval_spline(ARRAY_SIZE, frame, upx, upx_c, f);
    rupy = eval_spline(ARRAY_SIZE, frame, upy, upy_c, f);
    rupz = eval_spline(ARRAY_SIZE, frame, upz, upz_c, f);

    guLookAt(&dynamicp->viewing, 
	     rvpx, rvpy, rvpz,
	     ratx, raty, ratz,
	     rupx, rupy, rupz);

    gSPPerspNormalize(glistp++, perspNorm);

    f = f + 1.0;
    if(f > 31.0)
      f = 0.0;
  }
  else if(frameNum == 31)
  {
    /* LOOK_OVERALL */
    guLookAt(&dynamicp->viewing, 
	     50, 300, 700,
	     0, 50, 0,
	     0, 1, 0);
  }
  else if(frameNum == 32)
  {
    /* LOOK_ALL_FOUR_TREES */
    guLookAt(&dynamicp->viewing, 
	     -40, 30, 370,
	     -110, 10, 195,
	       0.173648, 0.9848077, 0);
  }
  else if(frameNum == 33)
  {
    /* LOOK_ICOSA */
    guLookAt(&dynamicp->viewing, 
	     10, 300, 200,
	     0, 0, 0,
	     0, 1, 0);
  }
  else if(frameNum == 34)
  {
    /* LOOK BOX */
    guLookAt(&dynamicp->viewing, 
	     10, 100, 200,
	     0, 0, 0,
	     0, 1, 0);
  }
  else if(frameNum == 35)
  {
    /* LOOK_FIRST_TREE */
    guLookAt(&dynamicp->viewing, 
	     -115, 30, 430,
	     -100, 10, 200,
	     0, 1, 0);
  }
  else if(frameNum == 36)
  {
    /* LOOK_SECOND_TREE */
    guLookAt(&dynamicp->viewing, 
	     -40, 30, 280,
	     -110, 10, 185,
	       0, 1, 0);
  }
  else
  {
    guLookAt(&dynamicp->viewing, 
	     50, 300, 600,
	     0, 50, 0,
	     0, 1, 0);
  }

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);


    /*   for cone   */
    guRotate(&dynamicp->modeling, theta, 1.0, 0.0, 0.0);

    /* gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 133, 102, 136, 103); */

#ifndef CONE
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdptex_cone_dl[0]);

#endif /* CONE */


#ifndef TORUS
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    guRotate(&dynamicp->torus, 90.0, 1.0, 0.333, 0.0);
    /* set the y and z translate elements by hand: */
    dynamicp->torus.m[1][2] = 130;
    dynamicp->torus.m[1][3] = (20 << 16) | 1;

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->torus)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdptex_torus_dl[0]);
#endif /* TORUS */

#ifndef GROUND
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdptex_ground_dl[0]);

#endif /* GROUND */


#ifndef BOX1

    /*  BOX1, textured box  */
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    guRotate(&dynamicp->box1, 45.0, 1.0, 1.0, 1.0);

    /* set the x, y, and z translate elements by hand: */
    dynamicp->box1.m[1][2] = (50 << 16) | (10);
    dynamicp->box1.m[1][3] = (100 << 16) | 1;

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->box1)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdptex_box1_dl[0]);
#endif /* BOX1 */


#ifndef ICOSA
    /*   ICOSAHEDRON   translucent objects last */
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    guRotate(&dynamicp->icosa, 90.0, 0.7, 0.8, 0.7);

    /* set the x, y, and z translate elements by hand: */
    dynamicp->icosa.m[1][2] = (40 << 16) | ((u16) -40);
    dynamicp->icosa.m[1][3] = (50 << 16) | 1;

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->icosa)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdptex_icosa_dl[0]);

#endif /* ICOSA */


#ifndef BOX
    /*  BOX   translucent objects last */
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    guTranslate(&dynamicp->box, -35.0, 50.0, 0.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->box)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdptex_box_dl[0]);
#endif /* BOX */

    /* for trees */
    guTranslate(&dynamicp->tree, 15.0, 0.0, -50.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

#ifndef TREE0

    gSPDisplayList(glistp++, &rdptex_tree0_dl[0]);

#endif /* TREE0 */


#ifndef TREE1
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->tree)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdptex_tree1_dl[0]);
#endif /* TREE1 */


#ifndef TREE2
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->tree)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdptex_tree2_dl[0]);

#endif /* TREE2 */


#ifndef TREE3
    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->tree)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPDisplayList(glistp++, &rdptex_tree3_dl[0]);
#endif /* TREE3 */

}

#define PERIOD			1
#define SAMPLES     		15
#define MISC_COMMANDS		128
#define INIT_RADIUS             40

Gfx gpoints[(PERIOD*SAMPLES + MISC_COMMANDS)];
Gfx *glocalp;


void
do_spiral2(int nsamples, int xoff, int yoff, int incl_x, int incl_y)
{
	float   dradius = 0.0;
	float   dangle = 2.0 * M_PI / SAMPLES;

	int     i;
	float   angle = 0;
	float   radius = INIT_RADIUS;
	int	x, y;
	int	xsize, ysize;

	xsize = SAMPLES-1;
	ysize = SAMPLES-1;

	for (i=0; i<nsamples; i++) {
		x = (int)(radius * cosf(angle) + 0.5);
		y = (int)(radius * sinf(angle) + 0.5);
		x += xoff;
		y += yoff;

		gDPFillRectangle(glocalp++, x, y, (x+xsize+incl_x), (y+ysize+incl_y));

		radius -= dradius;
		angle += dangle;
		xsize--;
		ysize--;
	}
}


void
rdptex_testCase_iorand_cosim_regression(Dynamic *dynamicp, Gfx *module_test)
{
    static float	theta = -15.0;

    guOrtho(&dynamicp->projection1,
	    -SCREEN_WD/2.0, SCREEN_WD/2.0,
	    -SCREEN_HT/2.0, SCREEN_HT/2.0, -1, 1, 1.0);

    guRotate(&dynamicp->modeling1, theta, 0.0, 0.0, 1.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection1)),
	      G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling1)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    /*
     * Turn off non overlap primitive mode
     */

    glocalp = &gpoints[0];
    gDPPipeSync(glistp++);
    gDPPipelineMode(glistp++, G_PM_NPRIMITIVE);


    /*
     * Do fill mode Spiral
     */

    gDPPipeSync(glocalp++);
    gDPSetCycleType(glocalp++, G_CYC_FILL);
    gDPSetFillColor(glocalp++, GPACK_RGBA5551(0xff, 0x00, 0xff, 1) << 16 |
	GPACK_RGBA5551(0xff, 0x00, 0xff, 1));


    do_spiral2(SAMPLES, SCREEN_WD*1/4, SCREEN_HT*1/4, 0, 0);

    gSPEndDisplayList(glocalp++);

    gSPDisplayList(glistp++, K0_TO_PHYS(gpoints));

    /*
     * do misc 1/2 cycle texture cases
     */

    gSPDisplayList(glistp++, rdptex_iorand_cosim_regression);

    /*
     * do random 1 cycle scene w/zbuffer and proper cvg bits for AA
     */

    gSPViewport(glistp++, &iorand_cosim_regression_viewport_lr);
    gDPPipeSync(glistp++);
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gDPPipelineMode(glistp++, G_PM_1PRIMITIVE);
    rdptex_testCaseProc30(dynamicp, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
    gSPEndDisplayList(glistp++);
}

#include "RGBA16mario_32.h"

void
rdptex_testCaseProc42(Dynamic *dynamicp, Gfx *module_test)
{
    static float        theta = 0.0;
    static Image im;
    static Image *imp = &im;
    static unsigned char tbuf[4096];
    u16   		perspNorm;

    imp->base = (unsigned char*)&RGBA16mario_32[0];
    imp->fmt  = G_IM_FMT_RGBA;
    imp->siz  = G_IM_SIZ_16b;
    imp->xsize= 32;
    imp->ysize= 32;
    imp->lsize= 32* sizeof(unsigned short);
    imp->addr = 0;
    imp->w    = 32;
    imp->h    = 32;
    imp->s    = 0;
    imp->t    = 0;


    guPerspective(&dynamicp->projection,&perspNorm,
                  33, 320.0/240.0, 1, 1000, 1.0);
    guLookAt(&dynamicp->viewing,
             0, 0, 800, 0, 0, 0, 0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 1.0, 0.0, 0.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
              G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, perspNorm);

    /* generate mipmaps, load data and set tiles */
    guLoadTextureBlockMipMap(&glistp, tbuf, imp, 0, 0, G_TX_WRAP | G_TX_NOMIRROR,
        G_TX_WRAP | G_TX_NOMIRROR, 5, 5, G_TX_NOLOD, G_TX_NOLOD, FILTER_WRAP,
	FILTER_WRAP);


    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}

void
rdptex_testCaseProc43(Dynamic *dynamicp, Gfx *module_test)
{
    static float theta = 0.0;
    u16   		perspNorm;

    guPerspective(&dynamicp->projection,&perspNorm,
                  35, 320.0/240.0, 100, 2000, 1.0);
    guLookAt(&dynamicp->viewing,
             0, 0, 600, 0, 0, 0, 0, 1, 0);

    guRotate(&dynamicp->modeling, theta, 1.0, 0.0, 0.0);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->projection)),
              G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->viewing)),
              G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPMatrix(glistp++, K0_TO_PHYS(&(dynamicp->modeling)),
              G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    gSPPerspNormalize(glistp++, perspNorm);

    gSPDisplayList(glistp++, module_test);

    if (generateFullSync == 1) {
        gDPFullSync(glistp++);
    } else {
        gDPPipeSync(glistp++);
    }
}


/* ADD TEST CASE: test frames: */
/* add procedure to do the work above here. */

/*
 * ADD TEST CASE: test frames:
 *
 * Display lists from rdpatt_static.c (which are placed in the static segment
 * via the spec file) must be inserted in this table, in the same position as
 * the test's frame number, along with a mneumonic name (which will be used to
 * name the resulting .rdp display list file), and a pointer to the top level
 * DL function which will be used to invoke this static display list.
 *
 * NOTE: a test doesn't need to have a static display list, if
 * the corresponding testCaseProc doesn't use one. But you still
 * need to put a NULL entry here in the table.
 */


GfxTest_t testList_rdptex[] =  {	/* list of specific test Gfx display lists: */
    &(rdptex_square0[0]), "rdptex_square0",		/* Test 0*/
	rdptex_testCaseProc0, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_square1[0]), "rdptex_square1",
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_square2[0]), "rdptex_square2",	
	rdptex_testCaseProc2, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_texfmt_RGBA16[0]), "rdptex_texfmt_RGBA16",
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_texfmt_IA8[0]), "rdptex_texfmt_IA8",
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,


    &(rdptex_texfmt_IA4[0]), "rdptex_texfmt_IA4",  	/* Test 5*/
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_texfmt_IA16[0]),"rdptex_texfmt_IA16",	 
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_loadtile_RGBA16[0]), "rdptex_loadtile_RGBA16",
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_loadtile_nonalign_RGBA16[0]), "rdptex_loadtile_nonalign_RGBA16",
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_loadtile_8b[0]), "rdptex_loadtile_8b",
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdptex_loadtile_4b[0]), "rdptex_loadtile_4b", 	/* Test 10*/
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_texfmt_I8[0]), "rdptex_texfmt_I8",
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_texfmt_I4[0]), "rdptex_texfmt_I4",
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_cpyfmt_RGBA16[0]), "rdptex_cpyfmt_RGBA16",
	rdptex_testCaseProc3, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,


    &(rdptex_texture_regression[0]), "rdptex_texture_regression", /* Test 15*/
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_texture_regression2[0]), "rdptex_texture_regression2",
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_interlace_odd_texture_regression[0]), "rdptex_interlace_odd_texture_regression",
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_interlace_even_texture_regression[0]), "rdptex_interlace_even_texture_regression",
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_interlace_odd_texture_regression2[0]), "rdptex_interlace_odd_texture_regression2",
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdptex_interlace_even_texture_regression2[0]), "rdptex_interlace_even_texture_regression2",  /* Test 20 */
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_copyRGBA16[0]), "rdptex_copyRGBA16", 			
	rdptex_testCaseProc3, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_magRGBA16[0]), "rdptex_magRGBA16", 		
	rdptex_testCaseProc3, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_lodRGBA16MM[0]), "rdptex_lodRGBA16MM", 	
	rdptex_testCaseProc38, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_detail32RGBA16MM[0]), "rdptex_detail32RGBA16MM",
	rdptex_testCaseProc39, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdptex_load_tlut_dl[0]), "rdptex_load_tlut_dl",	   	/* Test 25 */
	rdptex_testCaseProc40, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_iorand_cosim_regression[0]), "rdptex_iorand_cosim_regression", 
	rdptex_testCase_iorand_cosim_regression, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_sharpenRGBA16[0]), "rdptex_sharpenRGBA16",
	rdptex_testCaseProc42, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_copyAlphaRGBA16[0]), "rdptex_copyAlphaRGBA16",
	rdptex_testCaseProc43, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_detail16RGBA16MM[0]), "rdptex_detail16RGBA16MM",	
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdptex_cycle2_exact[0]), "rdptex_cycle2_exact",	/* Test 30 */
	rdptex_testCaseProc1, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdptex_frame_clear16b[0]), "rdptex_frame_clear16b", /* Test 35 */
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_frame1_clear8b[0]), "rdptex_frame1_clear8b",
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_frame_clear32b[0]), "rdptex_frame_clear32b",	
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_frame1_clear16b_ilo[0]), "rdptex_frame1_clear16b_ilo",
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_frame1_clear16b_ile[0]), "rdptex_frame1_clear16b_ile",
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdptex_frame1_clear8b_ilo[0]), "rdptex_frame1_clear8b_ilo",/* Test 40 */
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_frame1_clear8b_ile[0]), "rdptex_frame1_clear8b_ile",
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_frame1_clear32b_ilo[0]), "rdptex_frame1_clear32b_ilo",	
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_frame_clear32b_ile[0]), "rdptex_frame_clear32b_ile",
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",	
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdptex_yuvbars_dl[0]), "rdptex_yuvbars_dl",	/* Test 45 */
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_rww_lodRGBA16MM[0]), "rdptex_rww_lodRGBA16MM",
	rdptex_testCaseProc61, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_frame2_clear8b[0]), "rdptex_frame2_clear8b",
	rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_frame2_clear16b_ilo[0]), "rdptex_frame2_clear16b_ilo",
        rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_frame2_clear16b_ile[0]), "rdptex_frame2_clear16b_ile",
        rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdptex_frame2_clear8b_ilo[0]), "rdptex_frame2_clear8b_ilo",/* Test 50 */        rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_frame2_clear8b_ile[0]), "rdptex_frame2_clear8b_ile",
        rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_frame2_clear32b_ilo[0]), "rdptex_frame2_clear32b_ilo",
        rdptex_testCasePlacebo, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",	
	rdptex_testCaseProc68, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",	
	rdptex_testCaseProc69, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",	/* Test 55 */
	rdptex_testCaseProc70, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc71, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc72, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc73, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc74, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl", 	/* Test 60 */
	rdptex_testCaseProc75, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc76, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc77, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc78, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc79, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl", 	/* Test 65 */
	rdptex_testCaseProc80, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc81, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc82, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc83, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc84, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl", 	/* Test 70 */
	rdptex_testCaseProc85, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc86, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc87, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc88, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc89, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl", 	/* Test 75 */
	rdptex_testCaseProc90, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc91, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc92, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc93, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc94, G_IM_SIZ_16b, CLEAR_BLACK,

    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl", 	/*  Test 80 */
	rdptex_testCaseProc95, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc96, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc97, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc98, G_IM_SIZ_16b, CLEAR_BLACK,
    &(rdptex_placebo_dl[0]), "rdptex_placebo_dl",
	rdptex_testCaseProc99, G_IM_SIZ_16b, CLEAR_BLACK,

    /* Last entry must be NULL, so we can count them in main.c */
    (Gfx *) NULL,       "",             (CaseProc_t) NULL,
        G_IM_SIZ_16b, CLEAR_BLACK,
};
