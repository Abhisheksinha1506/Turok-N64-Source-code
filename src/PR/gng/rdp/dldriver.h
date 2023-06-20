/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1995, 1996 Silicon Graphics, Inc.          *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

/*
 * File:	dldriver.h
 * Creator:	hal@sgi.com
 * Create Date:	Tue Sep 26 14:01:01 PDT 1995
 * Purpose:	Declarations & definitions common across all test modules
 *
 */

/*
 * A separate set of files should be modified when producing display lists for
 * per module testing (e.g. cs.h, cs.c, cs_static.c).  A template display list
 * test has been provided; some real gfx dl's are provided as samples in the ms
 * test series.
 *
 * TO ADD A TEST CASE:
 *
 * decide which module your test will focus on, then:
 *
 * <module_name>.h		- extern the static display list, so that it is
 *				  visible from <module_name>_static.c
 *
 * <module_name>_static.c	- add the static display list for the test.
 *
 * <module_name>.c		- add the procedure to be called to
 *				  perform the test case. (also put it
 *				  in the testCaseProc table appropriate for
 *				  this module)
 *
 *				- put the static display list pointer
 *				  in the testList table (appropriately named
 *				  for your module under test) as a Gfx pointer 
 *				  in the GfxTest_t struct; also provide a name
 *				  for your test so that the rdpascii2rdp tool
 *				  can provide a filename for the resulting
 *				  binary .rdp file.
 *
 * plus any new textures, include files, etc.
 *
 */

#define	MAX_STATIC_GFX_SIZE	256
#define	MAX_GRAPHICS_SIZE	1024

#define	SCREEN_HT	240
#define	SCREEN_WD	320

#define CLEAR_BLACK     0
#define CLEAR_AQUA      1

#define zbuffer    0x80325800

#ifdef _LANGUAGE_C

/*
 * Layout of our dynamic segment
 */
typedef struct {
	Mtx	projection;
	Mtx	modeling;
	Mtx	viewing;
        Mtx     identity;
        Mtx     projection1;
        Mtx     modeling1;
        Mtx     move_x;
        Mtx     move_y;
        Mtx     box;
        Mtx     box1;
        Mtx     icosa;
        Mtx     torus;
        Mtx     tree;
        Mtx     model1;
        Mtx     model2;
        Mtx     model3;
        Mtx     model4;
	Mtx     skull;
        Mtx     cow;
        Mtx     vw;
	Gfx	glist[MAX_GRAPHICS_SIZE];
	LookAt	lookat[10];
	Hilite	hilite[10];
	u16	perspNorm;
} Dynamic;

extern unsigned int    cfb_16_a[];

extern Dynamic	dynamic;

extern Gfx      rspinit_dl[];
extern Gfx      rdpinit_dl[];
extern Gfx      clear_16fb_z[];
extern Gfx      clear_32fb_z[];
extern Gfx      clear_1024fb_z[];
extern Gfx      clear_16fb_aqua[];
extern Gfx      clear_32fb_aqua[];
extern Gfx      clear_640fb_aqua[];
extern Gfx      clear_1024fb_aqua[];
extern Gfx      clear_16fb_black[];
extern Gfx      clear_32fb_black[];
extern Gfx      clear_640fb_black[];
extern Gfx      clear_1024fb_black[];
extern Gfx      regression_viewport[];
extern Gfx      bigscreen_viewport[];
extern Gfx      clearcfb_dl[];

extern int 	generateFullSync;
extern int 	memSize;

typedef void (*CaseProc_t)(Dynamic *, Gfx *);

typedef struct {
    Gfx	*gfx_dl; 		/* A pointer to the test's static (gfx) DL */
    char testname[80];		/* this becomes the filename for the rdp dl */
    CaseProc_t toplevel_dl;	/* A pointer to the tests's top level DL */
    int	cfb_pixSize;		/* G_IM_SIZ_16b or G_IM_SIZ_32b */
    int cfb_clearColor;
} GfxTest_t;

typedef struct {
	int		testListCount; /* number of tests for this module */
	GfxTest_t	*gfxTests;      /* ptr to this module's dl's */
} ModuleTest_t;

extern Gfx	*glistp;	/* global for test case procs */

extern GfxTest_t testList_cs[];	/* list of per module Gfx display list tests */
extern GfxTest_t testList_ew[];	/* list of per module Gfx display list tests */
extern GfxTest_t testList_st[];	/* list of per module Gfx display list tests */
extern GfxTest_t testList_tm[];	/* list of per module Gfx display list tests */
extern GfxTest_t testList_tc[];	/* list of per module Gfx display list tests */
extern GfxTest_t testList_tf[];	/* list of per module Gfx display list tests */
extern GfxTest_t testList_cc[];	/* list of per module Gfx display list tests */
extern GfxTest_t testList_bl[];	/* list of per module Gfx display list tests */
extern GfxTest_t testList_ms[];	/* list of per module Gfx display list tests */
extern GfxTest_t testList_rdpatt[];
extern GfxTest_t testList_rdpcov[];
extern GfxTest_t testList_rdptex[];
extern GfxTest_t testList_rdpms[];
extern GfxTest_t testList_rdpew[];
extern GfxTest_t testList_rdpfb[];
extern GfxTest_t testList_rdp6M[];
extern GfxTest_t testList_rdp8M[];

#endif	/* _LANGUAGE_C */

#define CS_MODULE	0
#define EW_MODULE	1
#define ST_MODULE	2
#define TM_MODULE	3
#define TC_MODULE	4
#define TF_MODULE	5
#define CC_MODULE	6
#define BL_MODULE	7
#define MS_MODULE	8
#define RDPATT_MODULE	9
#define RDPCOV_MODULE	10
#define RDPTEX_MODULE   11
#define RDPMS_MODULE    12
#define RDPEW_MODULE    13
#define RDPFB_MODULE    14
#define RDP6M_MODULE    15
#define RDP8M_MODULE    16

#define MODULE_COUNT    17
