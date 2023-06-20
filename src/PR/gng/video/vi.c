/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1995, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

/*
 * File:	lines.c
 * Create Date:	Thu Jun 22 09:28:01 PDT 1995
 *
 *
 */

#include <ultra64.h>
#include <PR/ramrom.h>	/* needed for argument passing into the app */
#include <assert.h>
#include "gng.h"

#define	STATIC_SEGMENT		1
#define	STACKSIZE	   0x2000
#define	GLIST_LEN	     2048
#define MAXTESTNUM              5
#define NUMDITHERTYPES          4

#define FAST3D                  0
#define LINE3D                  1

#define PAL                     0
#define NTSC                    1

extern int controllerslot;

static int SCREEN_WD    =     320;
static int SCREEN_HT    =     240;

static float theta      =     0.0;

static int BackgroundColor = 0x0;

static enum VideoTypes {
  NTSC_LPN1,
  NTSC_LPF1,
  NTSC_LAN1,
  NTSC_LAF1,
  NTSC_HPN1,
  NTSC_HPF1,
  NTSC_HAN1,
  NTSC_HAF1,
  NTSC_LPN2,
  NTSC_LPF2,
  NTSC_LAN2,
  NTSC_LAF2,
  NTSC_HPN2,
  NTSC_HPF2,
  PAL_LPN1,
  PAL_LPF1,
  PAL_LAN1,
  PAL_LAF1,
  PAL_HPN1,
  PAL_HPF1,
  PAL_HAN1,
  PAL_HAF1,
  PAL_LPN2,
  PAL_LPF2,
  PAL_LAN2,
  PAL_LAF2,
  PAL_HPN2,
  PAL_HPF2
};

extern int zaruexists;

extern unsigned int cfb_16_a[];
extern void     *cfb_ptrs[2];

extern int      noprintf;

static int   CurrentTestNum              =          0;
static int   TranslateHorizontal         =          0;
static int   TranslateVertical           =          0;
static int   VideoModeIndex              =  NTSC_LPN1;
static int   MinVideoModeIndex           =  NTSC_LPN1;
static int   MaxVideoModeIndex           =  NTSC_HPF2;
static int   DitherEnable                =          0;
static int   ViDitherEnable              =          0;
static int   ViGammaEnable               =          1;
static int   ViGammaDither               =          1;
static int   ViDivotEnable               =          0;
static int   WantToChangeVideoMode       =          0;
static int   EraseRegister               =          0;

static int   NoEngines                   =          0;

static int   ReadTestIncrementController =          1;

static void TwirlFunc(void);
static void PlaneFunc(void);
static void GammaFunc(void);
static void DitherFunc(void);
static void DivotFunc(void);

static void TwirlInit(void);
static void PlaneInit(void);
static void GammaInit(void);
static void DitherInit(void);
static void DivotInit(void);

static void TwirlEngine(void);
static void PlaneEngine(void);
static void GammaEngine(void);
static void DitherEngine(void);
static void DivotEngine(void);

static void doLinePoly(void);
static void doOneShot(void);
static void doFrameTest(void);

static struct 
{
  char TestName[80];
  int  ZaruInitialLEDValue;
  int  DoBackgroundRects;
  int  ZaruVideoMode;
  int  VideoModeIndex;
  int  FrameBufferIndex;
  void (*TestDisplayFunc)(void);
  void (*TestMainLoop)(void);
  void (*TestInitFunc)(void);
  void (*TestEngineFunc)(void);
} TestStruct[] =
  {
    "Twirl",  0xf0, 0, ZARU_COMPOSITE, NTSC_LPN2, 1, TwirlFunc,  doLinePoly,  TwirlInit,  TwirlEngine,  
    "Plane",  0xf2, 0, ZARU_SVIDEO,    NTSC_LPN2, 1, PlaneFunc,  doLinePoly,  PlaneInit,  PlaneEngine,  
    "Divot",  0xf9, 0, ZARU_COMPOSITE, NTSC_LAF2, 2, DivotFunc,  doFrameTest, DivotInit,  DivotEngine, 
    "Dither", 0xf5, 0, ZARU_SVIDEO,    NTSC_HAF1, 0, DitherFunc, doOneShot,   DitherInit, DitherEngine,  
    "Gamma",  0xf3, 0, ZARU_COMPOSITE, NTSC_HPF1, 0, GammaFunc,  doOneShot,   GammaInit,  GammaEngine,  
  };		 

static unsigned int *FrameBufferPointer[3];

static struct 
{
  int DitherConst;
  char DitherName[80];
} DitherTypes[NUMDITHERTYPES] = {
  G_CD_DISABLE, "G_CD_DISABLE",
  G_CD_NOISE,   "G_CD_NOISE",
  G_CD_MAGICSQ, "G_CD_MAGICSQ",
  G_CD_BAYER,   "G_CD_BAYER",
};

static struct VideoEntry 
{
  char ModeName[80];
  int  ModeNumber;
  int  NumColorBits;
  int  ScreenWidth;
  int  ScreenHeight;
} VideoModeArray[] = {

/* NTSC Modes */
/*  0 */  "NTSC/LPN1", OS_VI_NTSC_LPN1, 16, 320, 240, 
/*  1 */  "NTSC/LPF1", OS_VI_NTSC_LPF1, 16, 320, 240, 
/*  2 */  "NTSC/LAN1", OS_VI_NTSC_LAN1, 16, 320, 240, 
/*  3 */  "NTSC/LAF1", OS_VI_NTSC_LAF1, 16, 320, 240, 
/*  4 */  "NTSC/HPN1", OS_VI_NTSC_HPN1, 16, 640, 480,
/*  5 */  "NTSC/HPF1", OS_VI_NTSC_HPF1, 16, 640, 480,
/*  6 */  "NTSC/HAN1", OS_VI_NTSC_HAN1, 16, 640, 480, 
/*  7 */  "NTSC/HAF1", OS_VI_NTSC_HAF1, 16, 640, 480, 
/*  8 */  "NTSC/LPN2", OS_VI_NTSC_LPN2, 32, 320, 240, 
/*  9 */  "NTSC/LPF2", OS_VI_NTSC_LPF2, 32, 320, 240, 
/* 10 */  "NTSC/LAN2", OS_VI_NTSC_LAN2, 32, 320, 240, 
/* 11 */  "NTSC/LAF2", OS_VI_NTSC_LAF2, 32, 320, 240, 
/* 12 */  "NTSC/HPN2", OS_VI_NTSC_HPN2, 32, 640, 480,
/* 13 */  "NTSC/HPF2", OS_VI_NTSC_HPF2, 32, 640, 480,

/* PAL Modes */	  

/* 14 */  "PAL/LPN1", OS_VI_PAL_LPN1, 16, 320, 240, 
/* 15 */  "PAL/LPF1", OS_VI_PAL_LPF1, 16, 320, 240, 
/* 16 */  "PAL/LAN1", OS_VI_PAL_LAN1, 16, 320, 240, 
/* 17 */  "PAL/LAF1", OS_VI_PAL_LAF1, 16, 320, 240, 
/* 18 */  "PAL/HPN1", OS_VI_PAL_HPN1, 16, 640, 480,
/* 19 */  "PAL/HPF1", OS_VI_PAL_HPF1, 16, 640, 480,
/* 20 */  "PAL/HAN1", OS_VI_PAL_HAN1, 16, 640, 480, 
/* 21 */  "PAL/HAF1", OS_VI_PAL_HAF1, 16, 640, 480, 
/* 22 */  "PAL/LPN2", OS_VI_PAL_LPN2, 32, 320, 240, 
/* 23 */  "PAL/LPF2", OS_VI_PAL_LPF2, 32, 320, 240, 
/* 24 */  "PAL/LAN2", OS_VI_PAL_LAN2, 32, 320, 240, 
/* 25 */  "PAL/LAF2", OS_VI_PAL_LAF2, 32, 320, 240, 
/* 26 */  "PAL/HPN2", OS_VI_PAL_HPN2, 32, 640, 480,
/* 27 */  "PAL/HPF2", OS_VI_PAL_HPF2, 32, 640, 480,

};

static struct VideoEntry LastFrameClearVideoMode;

static int     ControllerInput       =  0;
static int     PrintInstructions     =  1;

/* initialize the RSP state: */
static Gfx rspinit_dl[] = 
{
  gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH |
			G_FOG | G_LIGHTING | G_TEXTURE_GEN |
			G_TEXTURE_GEN_LINEAR | G_LOD ),
  gsSPTexture(0, 0, 0, 0, G_OFF),
  gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
  gsSPEndDisplayList(),
};

/* initialize the RDP state: */
static Gfx rdpinit_dl[] = 
{
  gsDPSetCycleType(G_CYC_1CYCLE),
  gsDPPipelineMode(G_PM_1PRIMITIVE),
  gsDPSetTextureLOD(G_TL_TILE),
  gsDPSetTextureLUT(G_TT_NONE),
  gsDPSetTextureDetail(G_TD_CLAMP),
  gsDPSetTexturePersp(G_TP_PERSP),
  gsDPSetTextureFilter(G_TF_BILERP),
  gsDPSetTextureConvert(G_TC_FILT),
  gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
  gsDPSetCombineKey(G_CK_NONE),
  gsDPSetAlphaCompare(G_AC_NONE),
  gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
  gsDPPipeSync(),
  gsSPEndDisplayList(),
};

extern char _codeSegmentEnd[];
extern char _staticSegmentRomStart[], _staticSegmentRomEnd[];

#define NUM_PI_MSGS     8

static OSMesg PiMessages[NUM_PI_MSGS];
static OSMesgQueue PiMessageQ;

extern OSMesgQueue     dmaMessageQ, rspMessageQ, rdpMessageQ, retraceMessageQ;
extern OSMesg          dmaMessageBuf, rspMessageBuf, rdpMessageBuf, retraceMessageBuf;
extern OSMesg          dummyMessage;
extern OSIoMesg        dmaIOMessageBuf;

extern char		*staticSegment;

static OSTask		*tlistp;

static void ReadController(void);
static void InitVariables(void);

typedef struct {
  Mtx	projection;

  Mtx	modeling1;
  Mtx   modeling2;
  Mtx   modeling3;
  Mtx   modeling4;

  Mtx   modeling5;
  Mtx   modeling6;
  Mtx   modeling7;
  Mtx   modeling8;
  Mtx   modeling9;
  Mtx   modeling10;
  Mtx   modeling11;
  Mtx   modeling12;
  Mtx   modeling13;
  Mtx   modeling14;
  Mtx   modeling15;
  Mtx   modeling16;
  Mtx   modeling17;
  Mtx   modeling18;

  Mtx	viewing;
  Mtx   identity;
  Gfx	glist[GLIST_LEN];
} ViDynamic;

static ViDynamic	*dynamicp;
static ViDynamic         dynamic;

static u64 dram_stack[SP_DRAM_STACK_SIZE64];	
    
static OSTask	tlist =
{
    M_GFXTASK,			
    OS_TASK_DP_WAIT,		
    NULL,			
    0,				
    NULL,			
    SP_UCODE_SIZE,		
    NULL,			
    SP_UCODE_DATA_SIZE,		
    &(dram_stack[0]),		
    SP_DRAM_STACK_SIZE8,	
    NULL,
    NULL,
    NULL,			
    0,				
    NULL,			
    0				
};

static Gfx		*glistp;	
    
/*
 * global variables
 */
static int	rdp_DRAM_io = 0;
static int	debugflag   = 0;
static int      draw_buffer = 0;
static int      verbose     = 0;
static int      FrameRate   = 1;

static float  XScale               = 1.0;
static float  YScale               = 1.0;

static void SetupSegments(void)
{
  /* Tell RCP where each segment is */

  gSPSegment(glistp++, 0, 0x0);   
  gSPSegment(glistp++, STATIC_SEGMENT, osVirtualToPhysical(staticSegment));
}

static void CreateTaskStructure(int type)
{
  /* Build graphics task */

  tlistp->t.ucode_boot = (u64 *) rspbootTextStart;
  tlistp->t.ucode_boot_size = (u32)rspbootTextEnd - (u32)rspbootTextStart;

  /* choose which ucode to run */

  if (rdp_DRAM_io) 
    {
      /* re-direct output to DRAM: */
      if (type == FAST3D)
	{
	  tlistp->t.ucode      = (u64 *) gspFast3D_dramTextStart;
	  tlistp->t.ucode_data = (u64 *) gspFast3D_dramDataStart; 
	}
      else
	{
	  tlistp->t.ucode      = (u64 *) gspLine3D_dramTextStart;
	  tlistp->t.ucode_data = (u64 *) gspLine3D_dramDataStart; 
	}
    } 
  else 
    {
      /* RSP output over XBUS to RDP: */
      if (type == FAST3D)
	{
	  tlistp->t.ucode      = (u64 *) gspFast3DTextStart;
	  tlistp->t.ucode_data = (u64 *) gspFast3DDataStart;
	}
      else
	{
	  tlistp->t.ucode      = (u64 *) gspLine3DTextStart;
	  tlistp->t.ucode_data = (u64 *) gspLine3DDataStart;
	}
    }	
  
  /* initial display list: */
  tlistp->t.data_ptr = (u64 *) dynamicp->glist;
}

static void SwapViBuffer(void)
{
  /* setup to swap buffers */
  osViSwapBuffer(cfb_ptrs[draw_buffer]);

  /* Make sure there isn't an old retrace in queue */
  if (MQ_IS_FULL(&retraceMessageQ))
    (void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);
  
  /* Wait for Vertical retrace to finish swap buffers */
  (void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);

  draw_buffer ^= 1;
}

static void DontSwapViBuffer(void)
{
  /* setup to swap buffers */
  osViSwapBuffer(FrameBufferPointer[0]);

  /* Make sure there isn't an old retrace in queue */
  if (MQ_IS_FULL(&retraceMessageQ))
    (void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);
  
  /* Wait for Vertical retrace to finish swap buffers */
  (void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);
}


static void IdentMatrices(void)
{
  guRotate(&dynamicp->modeling1, 0, 0.0F, 0.0F, 1.0F); 

  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamic.modeling1)),
	    G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
}

static void SetupViewing(void)
{
  guOrtho(&dynamicp->projection,
	  0.00, SCREEN_WD-1,
	  0.00, SCREEN_HT-1, 
	  -200, 200, 
	  1.0);

  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamic.projection)),
		G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);        
}

static void SetupPolyMatrices(void)
{
  guTranslate(&dynamicp->modeling2,  
	      SCREEN_WD/2.0 + TranslateHorizontal/320.0 * SCREEN_WD, 
	      SCREEN_HT/2.0 - TranslateVertical/240.0 * SCREEN_HT,
	      0.0);

  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamic.modeling2)),
	    G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

  guRotate(&dynamicp->modeling3, 0, 1.0, 1.0, 0.0);  
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamic.modeling3)),
	    G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

  guTranslate(&dynamicp->modeling4, 
	      -SCREEN_WD/2.0,
	      -SCREEN_HT/2.0,
	      0.0); 

  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamic.modeling4)),
	    G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
}


static void DoScalePolys(int NumTriangles)
{
  static Vtx background_vtx[4];

  background_vtx[0].v.ob[0] = (int) (50.0/320.0 * SCREEN_WD);
  background_vtx[0].v.ob[1] = (int) (SCREEN_HT-50.0/240.0 * SCREEN_HT);
  background_vtx[0].v.ob[2] = 0;
  background_vtx[0].v.flag  = 0;
  background_vtx[0].v.tc[0] = 0;
  background_vtx[0].v.tc[1] = 0;
  background_vtx[0].v.cn[0] = 0xff;
  background_vtx[0].v.cn[1] = 0;
  background_vtx[0].v.cn[2] = 0;
  background_vtx[0].v.cn[3] = 0xff;

  background_vtx[1].v.ob[0] = (int) (SCREEN_WD-50.0/320.0 * SCREEN_WD);
  background_vtx[1].v.ob[1] = (int) (50.0/240.0 * SCREEN_HT);
  background_vtx[1].v.ob[2] = 0;
  background_vtx[1].v.flag  = 0;
  background_vtx[1].v.tc[0] = 0;
  background_vtx[1].v.tc[1] = 0;
  background_vtx[1].v.cn[0] = 0;
  background_vtx[1].v.cn[1] = 0xff;
  background_vtx[1].v.cn[2] = 0;
  background_vtx[1].v.cn[3] = 0xff;

  background_vtx[2].v.ob[0] = (int) (50.0/320.0 * SCREEN_WD);
  background_vtx[2].v.ob[1] = (int) (50.0/240.0 * SCREEN_HT);
  background_vtx[2].v.ob[2] = 0;
  background_vtx[2].v.flag  = 0;
  background_vtx[2].v.tc[0] = 0;
  background_vtx[2].v.tc[1] = 0;
  background_vtx[2].v.cn[0] = 0;
  background_vtx[2].v.cn[1] = 0;
  background_vtx[2].v.cn[2] = 0;
  background_vtx[2].v.cn[3] = 0xff;

  /* Setup display modes antialiased in 1 cycle */
  gDPPipeSync(glistp++);

  gSPVertex(glistp++, &(background_vtx[0]), 4, 0);
  gSP1Triangle(glistp++, 0, 1, 2, 0);  
}

static Vtx twirl1[] =  {
        {   -7, -21, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0, 0, 0xff },
        {    7, -21, 0, 0, (31 << 6), ( 0 << 6), 0xff, 0, 0, 0xff },
        {    7,  -7, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0, 0, 0xff },
        {   -7,  -7, 0, 0, (31 << 6), ( 0 << 6), 0xff, 0, 0, 0xff },
	   					       	
        {   -7,   7, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0xff, 0, 0xff },
        {    7,   7, 0, 0, (31 << 6), ( 0 << 6), 0, 0xff, 0, 0xff },
        {    7,  21, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0xff, 0, 0xff },
        {   -7,  21, 0, 0, (31 << 6), ( 0 << 6), 0, 0xff, 0, 0xff },
	   					       	
        {  -21,  -7, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff },
        {   -7,  -7, 0, 0, (31 << 6), ( 0 << 6), 0, 0, 0xff, 0xff },
        {   -7,   7, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff },
        {  -21,   7, 0, 0, (31 << 6), ( 0 << 6), 0, 0, 0xff, 0xff },
	   					       	
	   					       	
        {    7,  -7, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0xff, 0, 0xff },
        {   21,  -7, 0, 0, (31 << 6), ( 0 << 6), 0xff, 0xff, 0, 0xff },
        {   21,   7, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0xff, 0, 0xff },
        {    7,   7, 0, 0, (31 << 6), ( 0 << 6), 0xff, 0xff, 0, 0xff },
};

Gfx TwirlFigure1[] = {
  gsSPVertex(&twirl1, 16, 0),

  gsSP1Triangle(0, 1, 2, 0),
  gsSP1Triangle(0, 2, 3, 0),

  gsSP1Triangle(4, 5, 6, 0),
  gsSP1Triangle(4, 6, 7, 0),

  gsSP1Triangle(8, 9,  10, 0),
  gsSP1Triangle(8, 10, 11, 0),

  gsSP1Triangle(12, 13, 14, 0),
  gsSP1Triangle(12, 14, 15, 0),
  gsSPEndDisplayList(),
};

static Vtx twirl2[] =  {

        {         0, -21, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0, 0, 0xff       },
        {        21,   0, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0, 0, 0xff       },
        {         0,  21, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0, 0, 0xff       },
        {       -21,   0, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0, 0, 0xff       },

        {       -17, -17, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0xff, 0xff, 0xff       },
        {        17, -17, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0xff, 0xff, 0xff       },
        {        17,  17, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0xff, 0xff, 0xff       },
        {       -17,  17, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0xff, 0xff, 0xff       },

};

Gfx TwirlFigure2[] = {
  gsSPVertex(&twirl2,  8, 0),
  gsSP1Triangle(0, 1, 2, 0),
  gsSP1Triangle(0, 2, 3, 0),

  gsSP1Triangle(4, 5, 6, 0),
  gsSP1Triangle(4, 6, 7, 0),


  gsSPEndDisplayList(),
};

static Vtx twirl3[] =  {

        {       -21, -21, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0, 0xff, 0xff       },
        {        21, -21, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0, 0xff, 0xff       },
        {        21,  21, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0, 0xff, 0xff       },
        {       -21,  21, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0, 0xff, 0xff       },
							     
        {         0, -21, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0, 0xff, 0xff       },
        {        21,   0, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0, 0xff, 0xff       },
        {         0,  21, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0, 0xff, 0xff       },
        {       -21,   0, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0, 0xff, 0xff       },


};

Gfx TwirlFigure3[] = {
  gsSPVertex(&twirl3,  8, 0),
  gsSP1Triangle(1, 5, 4, 0),
  gsSP1Triangle(5, 2, 6, 0),
  gsSP1Triangle(6, 3, 7, 0),
  gsSP1Triangle(7, 0, 4, 0),

  gsSPEndDisplayList(),
};

static Vtx twirl4[] =  {

        {       -21, -21, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0xff, 0, 0xff       },
        {        21, -21, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0xff, 0, 0xff       },
        {        21,  21, 0, 0, ( 0 << 6), ( 0 << 6), 0xff, 0xff, 0, 0xff       },

        {        17,  21, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff       },
        {       -21,  21, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff       },
        {       -21, -17, 0, 0, ( 0 << 6), ( 0 << 6), 0, 0, 0xff, 0xff       },
};

Gfx TwirlFigure4[] = {
  gsSPVertex(&twirl4,  6, 0),

  gsSP1Triangle(0, 1, 2, 0),
  gsSP1Triangle(3, 4, 5, 0),

  gsSPEndDisplayList(),
};

static void DoTwirlPolys(void)
{
  guTranslate(&dynamicp->modeling5, 37, 207, 0.0); 
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamic.modeling5)),
	    G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_PUSH);
  guRotate(&dynamicp->modeling6, theta, 0.0F, 0.0F, 1.0F); 
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamic.modeling6)),
	    G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
  gSPDisplayList(glistp++, TwirlFigure1);
  gSPPopMatrix(glistp++, G_MTX_MODELVIEW);

  guTranslate(&dynamicp->modeling7, 108, 207, 0.0); 
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamic.modeling7)),
	    G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_PUSH);
  guRotate(&dynamicp->modeling8, theta, 0.0F, 0.0F, 1.0F); 
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamic.modeling8)),
	    G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
  gSPDisplayList(glistp++, TwirlFigure2);
  gSPPopMatrix(glistp++, G_MTX_MODELVIEW);

  guTranslate(&dynamicp->modeling9, 37, 155, 0.0); 
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamic.modeling9)),
	    G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_PUSH);
  guRotate(&dynamicp->modeling10, theta, 0.0F, 0.0F, 1.0F); 
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamic.modeling10)),
	    G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
  gSPDisplayList(glistp++, TwirlFigure3);
  gSPPopMatrix(glistp++, G_MTX_MODELVIEW);


  guTranslate(&dynamicp->modeling11, 108, 155, 0.0); 
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamic.modeling11)),
	    G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
  guRotate(&dynamicp->modeling12, theta, 0.0F, 0.0F, 1.0F); 
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamic.modeling12)),
	    G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
  gSPDisplayList(glistp++, TwirlFigure4);
  gSPPopMatrix(glistp++, G_MTX_MODELVIEW);


  theta += 0.12F;
}

static void SetupVi(void)
{
  osViSetXScale(XScale);
  osViSetYScale(YScale);

  if (ViDitherEnable)
    {
      osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON);
    }
  else
    {
      osViSetSpecialFeatures(OS_VI_DITHER_FILTER_OFF);
    }

  if (ViGammaEnable)
    {
      osViSetSpecialFeatures(OS_VI_GAMMA_ON);
    }
  else
    {
      osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
    }

  if (ViDivotEnable)
    {
      osViSetSpecialFeatures(OS_VI_DIVOT_ON);
    }
  else
    {
      osViSetSpecialFeatures(OS_VI_DIVOT_OFF);
    }
}

static void DoCommonSetup(void)
{
  /* Setup display modes antialiased in 1 cycle */

  gDPSetRenderMode(glistp++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
  
  SetupViewing();
  IdentMatrices(); 
  SetupPolyMatrices();

  if (verbose) 
    {
      PRINTF("Setting dither modes RDP %s VI %d \n", 
		 DitherTypes[DitherEnable].DitherName, ViDitherEnable);
    }

  gDPSetColorDither(glistp++, DitherTypes[DitherEnable].DitherConst);

  SetupVi();
}

static void CleanupAndSendDisplayList(int MicrocodeType)
{
  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);
	
  assert((glistp-dynamicp->glist) < GLIST_LEN);
	
  tlistp->t.data_size = (u32)((glistp - dynamicp->glist) * sizeof(Gfx));
	
  /* Write back dirty cache lines that need to be read by the RCP */
  osWritebackDCache(&dynamic, sizeof(dynamic));
	
  /* start up the RSP task */
  CreateTaskStructure(MicrocodeType);
  osSpTaskStart(tlistp);

  /* wait for SP completion */
  (void)osRecvMesg(&rspMessageQ, NULL, OS_MESG_BLOCK);
	
  (void)osRecvMesg(&rdpMessageQ, NULL, OS_MESG_BLOCK);
}

static void InitViewport(void)
{
  static Vp mvp;
  
  mvp.vp.vscale[0] = SCREEN_WD*2;
  mvp.vp.vscale[1] = SCREEN_HT*2;
  mvp.vp.vscale[2] = G_MAXZ/2;
  mvp.vp.vscale[3] = 0;
  
  mvp.vp.vtrans[0] = SCREEN_WD*2;
  mvp.vp.vtrans[1] = SCREEN_HT*2;
  mvp.vp.vtrans[2] = G_MAXZ/2;
  mvp.vp.vtrans[3] = 0;
  
  gSPViewport(glistp++, &mvp);
}

static void InitDisplayLists(void)
{
  /* pointers to build the display list */
  glistp = dynamicp->glist;
  
  SetupSegments();

  /* Setup scissor values */

  gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT);

  /* Initialize RDP state */
  gSPDisplayList(glistp++, rdpinit_dl);

   /* Setup the Viewport */
  InitViewport();
  
  /* Initialize RSP state */
  gSPDisplayList(glistp++, rspinit_dl);  
}

static void WriteBackgroundRects(void)
{
  if (VideoModeArray[VideoModeIndex].NumColorBits == 32)
    {
      gDPSetFillColor(glistp++, 
		      (0x40 << 24) | (0x40 << 16) | (0x40 << 8) | (0xff << 0)); 
    }
  else
    {
      gDPSetFillColor(glistp++, GPACK_RGBA5551(64,64,64,1) << 16 | 
		      GPACK_RGBA5551(64,64,64,1));
    }
      
  gDPFillRectangle(glistp++, 
		   (int) (20.0/320.0 * SCREEN_WD), 
		   (int) (20.0/240.0 * SCREEN_HT), 
		   SCREEN_WD - (int)(20.0/320.0*SCREEN_WD), 
		   SCREEN_HT - (int)(20.0/240.0*SCREEN_HT));
      
  gDPPipeSync(glistp++);
      
  if (VideoModeArray[VideoModeIndex].NumColorBits == 32)
    {
      gDPSetFillColor(glistp++, 
		      (0xff << 24) | (0x40 << 16) | (0xff << 8) | (0xff << 0)); 
    }
  else
    {
      gDPSetFillColor(glistp++, GPACK_RGBA5551(255,64,255,1) << 16 | 
		      GPACK_RGBA5551(255,64,255,1));
    }
      

  gDPFillRectangle(glistp++, 
		   (int) (40.0/320.0 * SCREEN_WD), 
		   (int) (40.0/240.0 * SCREEN_HT), 
		   SCREEN_WD - (int)(40.0/320.0*SCREEN_WD), 
		   SCREEN_HT - (int)(40.0/240.0*SCREEN_HT));
  gDPPipeSync(glistp++);   
}

static void ClearFrameBuffer(int DoBackgroundRects, void *FrameBufferPointer)
{
  /* Clear color framebuffer */

  gDPSetCycleType(glistp++, G_CYC_FILL);

  if (VideoModeArray[VideoModeIndex].NumColorBits == 32)
    {
      gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD, 
		       OS_K0_TO_PHYSICAL(FrameBufferPointer));
      
      gDPSetFillColor(glistp++, 
		      (BackgroundColor << 24) | 
		      (BackgroundColor << 16) | 
		      (BackgroundColor << 8)  | 
		      (0xff << 0)); 
    }
  else
    {
      gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, 
		       OS_K0_TO_PHYSICAL(FrameBufferPointer));
      gDPSetFillColor(glistp++, GPACK_RGBA5551( 0, 0, 0,1) << 16 | 
		      GPACK_RGBA5551( 0, 0, 0,1));
    }
      

  gDPFillRectangle(glistp++, 0, 0, SCREEN_WD-1, SCREEN_HT-1);
  gDPPipeSync(glistp++);

  if (DoBackgroundRects)
    WriteBackgroundRects();

  gDPSetCycleType(glistp++, G_CYC_1CYCLE);  

  LastFrameClearVideoMode.ScreenWidth  = VideoModeArray[VideoModeIndex].ScreenWidth;
  LastFrameClearVideoMode.NumColorBits = VideoModeArray[VideoModeIndex].NumColorBits;
}

static void WriteToFrameBuffer(void)
{
  int i, j, Width, BitSize;

  Width   = VideoModeArray[VideoModeIndex].ScreenWidth;
  BitSize = VideoModeArray[VideoModeIndex].NumColorBits;

  for (j=0; j<(Width == 640 ? 480 : 240); j++)
    for (i=0; i<Width; i++)
      {
	if (BitSize == 32)
	  *((unsigned int * ) FrameBufferPointer[0] + j*Width  + i) = (j/32 % 2) ? 
	    (((i%3) == 2) ? 0xffff00df : 0x000000ff) : 
	  (((i%3) == 2) ? 0xffff00ff : 0x000000ff);
	else
	  *((unsigned short * ) FrameBufferPointer[0] + j*Width  + i) = (j/32 % 2) ? 
	    (((i%3) == 2) ? 0xffc0 : 0x0001) : 
	      (((i%3) == 2) ? 0xffc1 : 0x0001);	  
      }
  
  LastFrameClearVideoMode.ScreenWidth  = Width;
  LastFrameClearVideoMode.NumColorBits = BitSize;
}

static void TwirlInit(void)
{
  XScale = 0.50;
  YScale = 0.50;

  ReadTestIncrementController = 0;

  WantToChangeVideoMode       = 1;
}

static void TwirlFunc(void)
{
  DoTwirlPolys();
  CleanupAndSendDisplayList(FAST3D);	
}

static void TwirlEngine(void)
{
  static int LastNext   = 1;

  if (!ReadTestIncrementController)
    {
      if (ZaruGetNextTestButton()) 
	{
	  if (!LastNext)
	    {
	      if (VideoModeIndex == NTSC_LAN2) 
		{
		  ReadTestIncrementController = 1;
		}
	      else
		{	  	  	  
		  VideoModeIndex              = NTSC_LAN2;
	      
		  WantToChangeVideoMode       = 1;
		  ControllerInput             = 1;

		  if (zaruexists) 
		    {
		      ZaruSetMemA(TestStruct[CurrentTestNum].ZaruInitialLEDValue + 1);
		    }
		}
	    }
	  LastNext = 1;
	}
      else
	{
	  LastNext = 0;
	}
    }
}

static void PlaneInit(void)
{
  TranslateHorizontal         = -100;
  TranslateVertical           = -100;

  ReadTestIncrementController = 0;
  WantToChangeVideoMode       = 1;
}

static void PlaneFunc(void)
{
  DoScalePolys(1);
  CleanupAndSendDisplayList(FAST3D);	
}

#define SCALEDELTA .02

static void PlaneEngine(void)
{
  static float XScaleDelta = 0.99;
  static float YScaleDelta = 0.98;
  static int   GotAHit = 0;

  XScale *= XScaleDelta;
  YScale *= YScaleDelta; 

  if (XScale > 1.00) 
    {
      XScale      = 1.0;
      XScaleDelta = 0.99;
    }
  if (XScale < 0.25)
    {
      XScale      = 0.25;
      XScaleDelta = 1.01;
    }

  if (YScale > 1.00) 
    {
      YScale      = 1.0;
      YScaleDelta = 0.98;
    }
  if (YScale < 0.05)
    {
      YScale      = 0.05;
      YScaleDelta = 1.02;
    }

  if ((1.0 - XScale) <= SCALEDELTA)
    {
      if (GotAHit == 9) 
	{
	  ReadTestIncrementController = 1;
	  BackgroundColor = 0xff;
	}

      GotAHit++;
    }

  ControllerInput = 1;
}

static void DoGammaPolys(void)
{
  static Vtx gamma_vtx[8];

  gamma_vtx[0].v.ob[0] = (int) ( 5.0/320.0 * SCREEN_WD);
  gamma_vtx[0].v.ob[1] = (int) (SCREEN_HT- 5.0/240.0 * SCREEN_HT);
  gamma_vtx[0].v.ob[2] = 0;
  gamma_vtx[0].v.flag  = 0;
  gamma_vtx[0].v.tc[0] = 0;
  gamma_vtx[0].v.tc[1] = 0;
  gamma_vtx[0].v.cn[0] = 0x00;
  gamma_vtx[0].v.cn[1] = 0x00;
  gamma_vtx[0].v.cn[2] = 0x00;
  gamma_vtx[0].v.cn[3] = 0xff;

  gamma_vtx[1].v.ob[0] = (int) (SCREEN_WD- 5.0/320.0 * SCREEN_WD);
  gamma_vtx[1].v.ob[1] = (int) (SCREEN_HT- 5.0/240.0 * SCREEN_HT);
  gamma_vtx[1].v.ob[2] = 0;
  gamma_vtx[1].v.flag  = 0;
  gamma_vtx[1].v.tc[0] = 0;
  gamma_vtx[1].v.tc[1] = 0;
  gamma_vtx[1].v.cn[0] = 0x00;
  gamma_vtx[1].v.cn[1] = 0x00;
  gamma_vtx[1].v.cn[2] = 0x00;
  gamma_vtx[1].v.cn[3] = 0xff;

  gamma_vtx[2].v.ob[0] = (int) (SCREEN_WD- 0.0/320.0 * SCREEN_WD);
  gamma_vtx[2].v.ob[1] = (int) ( 5.0/240.0 * SCREEN_HT);
  gamma_vtx[2].v.ob[2] = 0;
  gamma_vtx[2].v.flag  = 0;
  gamma_vtx[2].v.tc[0] = 0;
  gamma_vtx[2].v.tc[1] = 0;
  gamma_vtx[2].v.cn[0] = 0x00;
  gamma_vtx[2].v.cn[1] = 0x00;
  gamma_vtx[2].v.cn[2] = 0x00;
  gamma_vtx[2].v.cn[3] = 0xff;

  gamma_vtx[3].v.ob[0] = (int) ( 0.0/320.0 * SCREEN_WD);
  gamma_vtx[3].v.ob[1] = (int) ( 5.0/240.0 * SCREEN_HT);
  gamma_vtx[3].v.ob[2] = 0;
  gamma_vtx[3].v.flag  = 0;
  gamma_vtx[3].v.tc[0] = 0;
  gamma_vtx[3].v.tc[1] = 0;
  gamma_vtx[3].v.cn[0] = 0x00;
  gamma_vtx[3].v.cn[1] = 0x00;
  gamma_vtx[3].v.cn[2] = 0x00;
  gamma_vtx[3].v.cn[3] = 0xff;

  gamma_vtx[4].v.ob[0] = (int) ( 160.0/320.0 * SCREEN_WD);
  gamma_vtx[4].v.ob[1] = (int) ( 120.0/240.0 * SCREEN_HT);
  gamma_vtx[4].v.ob[2] = 0;
  gamma_vtx[4].v.flag  = 0;
  gamma_vtx[4].v.tc[0] = 0;
  gamma_vtx[4].v.tc[1] = 0;
  gamma_vtx[4].v.cn[0] = 0xff;
  gamma_vtx[4].v.cn[1] = 0xff;
  gamma_vtx[4].v.cn[2] = 0xff;
  gamma_vtx[4].v.cn[3] = 0xff;



  /* Setup display modes antialiased in 1 cycle */
  gDPPipeSync(glistp++);

  gSPVertex(glistp++, &(gamma_vtx[0]), 8, 0);

  gSP1Triangle(glistp++, 0, 1, 4, 0);
  gSP1Triangle(glistp++, 1, 2, 4, 1);
  gSP1Triangle(glistp++, 4, 2, 3, 4);
  gSP1Triangle(glistp++, 0, 4, 3, 0);
}

static void GammaInit(void)
{
  ReadTestIncrementController = 0;

  WantToChangeVideoMode =         1;
}

static void GammaFunc(void)
{
  DoGammaPolys();

  CleanupAndSendDisplayList(FAST3D);	
}

static void GammaEngine(void)
{
  static int LastNext   = 1;

  if (!ReadTestIncrementController)
    {
      if (ZaruGetNextTestButton()) 
	{
	  if (!LastNext)
	    {
	      ViGammaEnable  ^= 1;  
	      ViGammaDither  ^= 1;
	      ControllerInput = 1;
	      
	      ReadTestIncrementController = 1;

	      if (zaruexists) 
		{
		  ZaruSetMemA(TestStruct[CurrentTestNum].ZaruInitialLEDValue + 1);
		}
	    }
	  LastNext = 1;
	}
      else
	{
	  LastNext = 0;
	}
    }
}

static void DoDitherPolys(void)
{
  static Vtx Dither_vtx[16];

  float WindowStart =  120.0;
  float YDivisor    =  320.0;

  Dither_vtx[0].v.ob[0] = (int) (WindowStart/320.0 * SCREEN_WD);
  Dither_vtx[0].v.ob[1] = (int) (SCREEN_HT-WindowStart/YDivisor * SCREEN_HT);
  Dither_vtx[0].v.ob[2] = 0;
  Dither_vtx[0].v.flag  = 0;
  Dither_vtx[0].v.tc[0] = 0;
  Dither_vtx[0].v.tc[1] = 0;
  Dither_vtx[0].v.cn[0] = 0x5f;
  Dither_vtx[0].v.cn[1] = 0;
  Dither_vtx[0].v.cn[2] = 0;
  Dither_vtx[0].v.cn[3] = 0x00;

  Dither_vtx[1].v.ob[0] = (int) (SCREEN_WD-WindowStart/320.0 * SCREEN_WD);
  Dither_vtx[1].v.ob[1] = (int) (SCREEN_HT-WindowStart/YDivisor * SCREEN_HT);
  Dither_vtx[1].v.ob[2] = 0;
  Dither_vtx[1].v.flag  = 0;
  Dither_vtx[1].v.tc[0] = 0;
  Dither_vtx[1].v.tc[1] = 0;
  Dither_vtx[1].v.cn[0] = 0;
  Dither_vtx[1].v.cn[1] = 0x5f;
  Dither_vtx[1].v.cn[2] = 0;
  Dither_vtx[1].v.cn[3] = 0xff;

  Dither_vtx[2].v.ob[0] = (int) (SCREEN_WD-WindowStart/320.0 * SCREEN_WD);
  Dither_vtx[2].v.ob[1] = (int) (WindowStart/YDivisor * SCREEN_HT);
  Dither_vtx[2].v.ob[2] = 0;
  Dither_vtx[2].v.flag  = 0;
  Dither_vtx[2].v.tc[0] = 0;
  Dither_vtx[2].v.tc[1] = 0;
  Dither_vtx[2].v.cn[0] = 0;
  Dither_vtx[2].v.cn[1] = 0;
  Dither_vtx[2].v.cn[2] = 0x5f;
  Dither_vtx[2].v.cn[3] = 0xff;

  Dither_vtx[3].v.ob[0] = (int) (WindowStart/320.0 * SCREEN_WD);
  Dither_vtx[3].v.ob[1] = (int) (WindowStart/YDivisor * SCREEN_HT);
  Dither_vtx[3].v.ob[2] = 0;
  Dither_vtx[3].v.flag  = 0;
  Dither_vtx[3].v.tc[0] = 0;
  Dither_vtx[3].v.tc[1] = 0;
  Dither_vtx[3].v.cn[0] = 0x5f;
  Dither_vtx[3].v.cn[1] = 0x5f;
  Dither_vtx[3].v.cn[2] = 0x5f;
  Dither_vtx[3].v.cn[3] = 0xff;

  Dither_vtx[4].v.ob[0] = (Dither_vtx[0].v.ob[0] + Dither_vtx[1].v.ob[0]) >> 1;
  Dither_vtx[4].v.ob[1] = Dither_vtx[0].v.ob[1];
  Dither_vtx[4].v.ob[2] = 0;
  Dither_vtx[4].v.flag  = 0;
  Dither_vtx[4].v.tc[0] = 0;
  Dither_vtx[4].v.tc[1] = 0;
  Dither_vtx[4].v.cn[0] = 0x2f;
  Dither_vtx[4].v.cn[1] = 0;
  Dither_vtx[4].v.cn[2] = 0;
  Dither_vtx[4].v.cn[3] = 0x00;

  Dither_vtx[5].v.ob[0] = (Dither_vtx[0].v.ob[0] + Dither_vtx[1].v.ob[0]) >> 1;
  Dither_vtx[5].v.ob[1] = Dither_vtx[0].v.ob[1];
  Dither_vtx[5].v.ob[2] = 0;
  Dither_vtx[5].v.flag  = 0;
  Dither_vtx[5].v.tc[0] = 0;
  Dither_vtx[5].v.tc[1] = 0;
  Dither_vtx[5].v.cn[0] = 0;
  Dither_vtx[5].v.cn[1] = 0x2f;
  Dither_vtx[5].v.cn[2] = 0;
  Dither_vtx[5].v.cn[3] = 0x00;

  Dither_vtx[6].v.ob[0] = Dither_vtx[1].v.ob[0];
  Dither_vtx[6].v.ob[1] = (Dither_vtx[1].v.ob[1] + Dither_vtx[2].v.ob[1]) >> 1;
  Dither_vtx[6].v.ob[2] = 0;
  Dither_vtx[6].v.flag  = 0;
  Dither_vtx[6].v.tc[0] = 0;
  Dither_vtx[6].v.tc[1] = 0;
  Dither_vtx[6].v.cn[0] = 0;
  Dither_vtx[6].v.cn[1] = 0x2f;
  Dither_vtx[6].v.cn[2] = 0;
  Dither_vtx[6].v.cn[3] = 0x00;

  Dither_vtx[7].v.ob[0] = Dither_vtx[1].v.ob[0];
  Dither_vtx[7].v.ob[1] = (Dither_vtx[1].v.ob[1] + Dither_vtx[2].v.ob[1]) >> 1;
  Dither_vtx[7].v.ob[2] = 0;
  Dither_vtx[7].v.flag  = 0;
  Dither_vtx[7].v.tc[0] = 0;
  Dither_vtx[7].v.tc[1] = 0;
  Dither_vtx[7].v.cn[0] = 0;
  Dither_vtx[7].v.cn[1] = 0;
  Dither_vtx[7].v.cn[2] = 0x2f;
  Dither_vtx[7].v.cn[3] = 0x00;

  Dither_vtx[8].v.ob[0] = (Dither_vtx[2].v.ob[0] + Dither_vtx[3].v.ob[0]) >> 1;
  Dither_vtx[8].v.ob[1] = Dither_vtx[2].v.ob[1];
  Dither_vtx[8].v.ob[2] = 0;
  Dither_vtx[8].v.flag  = 0;
  Dither_vtx[8].v.tc[0] = 0;
  Dither_vtx[8].v.tc[1] = 0;
  Dither_vtx[8].v.cn[0] = 0;
  Dither_vtx[8].v.cn[1] = 0;
  Dither_vtx[8].v.cn[2] = 0x2f;
  Dither_vtx[8].v.cn[3] = 0x00;

  Dither_vtx[9].v.ob[0] = (Dither_vtx[2].v.ob[0] + Dither_vtx[3].v.ob[0]) >> 1;
  Dither_vtx[9].v.ob[1] = Dither_vtx[2].v.ob[1];
  Dither_vtx[9].v.ob[2] = 0;
  Dither_vtx[9].v.flag  = 0;
  Dither_vtx[9].v.tc[0] = 0;
  Dither_vtx[9].v.tc[1] = 0;
  Dither_vtx[9].v.cn[0] = 0x2f;
  Dither_vtx[9].v.cn[1] = 0x2f;
  Dither_vtx[9].v.cn[2] = 0x2f;
  Dither_vtx[9].v.cn[3] = 0x00;

  Dither_vtx[10].v.ob[0] = Dither_vtx[0].v.ob[0];
  Dither_vtx[10].v.ob[1] = (Dither_vtx[0].v.ob[1] + Dither_vtx[3].v.ob[1]) >> 1;
  Dither_vtx[10].v.ob[2] = 0;
  Dither_vtx[10].v.flag  = 0;
  Dither_vtx[10].v.tc[0] = 0;
  Dither_vtx[10].v.tc[1] = 0;
  Dither_vtx[10].v.cn[0] = 0x2f;
  Dither_vtx[10].v.cn[1] = 0x2f;
  Dither_vtx[10].v.cn[2] = 0x2f;
  Dither_vtx[10].v.cn[3] = 0x00;
	     
  Dither_vtx[11].v.ob[0] = Dither_vtx[0].v.ob[0];
  Dither_vtx[11].v.ob[1] = (Dither_vtx[0].v.ob[1] + Dither_vtx[3].v.ob[1]) >> 1;
  Dither_vtx[11].v.ob[2] = 0;
  Dither_vtx[11].v.flag  = 0;
  Dither_vtx[11].v.tc[0] = 0;
  Dither_vtx[11].v.tc[1] = 0;
  Dither_vtx[11].v.cn[0] = 0x2f;
  Dither_vtx[11].v.cn[1] = 0;
  Dither_vtx[11].v.cn[2] = 0;
  Dither_vtx[11].v.cn[3] = 0x00;

  Dither_vtx[12].v.ob[0] = (Dither_vtx[2].v.ob[0] + Dither_vtx[3].v.ob[0]) >> 1;
  Dither_vtx[12].v.ob[1] = (Dither_vtx[0].v.ob[1] + Dither_vtx[3].v.ob[1]) >> 1;
  Dither_vtx[12].v.ob[2] = 0;
  Dither_vtx[12].v.flag  = 0;
  Dither_vtx[12].v.tc[0] = 0;
  Dither_vtx[12].v.tc[1] = 0;
  Dither_vtx[12].v.cn[0] = 0;
  Dither_vtx[12].v.cn[1] = 0;
  Dither_vtx[12].v.cn[2] = 0;
  Dither_vtx[12].v.cn[3] = 0x00;

  Dither_vtx[13].v.ob[0] = (Dither_vtx[2].v.ob[0] + Dither_vtx[3].v.ob[0]) >> 1;
  Dither_vtx[13].v.ob[1] = (Dither_vtx[0].v.ob[1] + Dither_vtx[3].v.ob[1]) >> 1;
  Dither_vtx[13].v.ob[2] = 0;
  Dither_vtx[13].v.flag  = 0;
  Dither_vtx[13].v.tc[0] = 0;
  Dither_vtx[13].v.tc[1] = 0;
  Dither_vtx[13].v.cn[0] = 0;
  Dither_vtx[13].v.cn[1] = 0;
  Dither_vtx[13].v.cn[2] = 0;
  Dither_vtx[13].v.cn[3] = 0;

  Dither_vtx[14].v.ob[0] = (Dither_vtx[2].v.ob[0] + Dither_vtx[3].v.ob[0]) >> 1;
  Dither_vtx[14].v.ob[1] = (Dither_vtx[0].v.ob[1] + Dither_vtx[3].v.ob[1]) >> 1;
  Dither_vtx[14].v.ob[2] = 0;
  Dither_vtx[14].v.flag  = 0;
  Dither_vtx[14].v.tc[0] = 0;
  Dither_vtx[14].v.tc[1] = 0;
  Dither_vtx[14].v.cn[0] = 0x00;
  Dither_vtx[14].v.cn[1] = 0;
  Dither_vtx[14].v.cn[2] = 0;
  Dither_vtx[14].v.cn[3] = 0x00;

  Dither_vtx[15].v.ob[0] = (Dither_vtx[2].v.ob[0] + Dither_vtx[3].v.ob[0]) >> 1;
  Dither_vtx[15].v.ob[1] = (Dither_vtx[0].v.ob[1] + Dither_vtx[3].v.ob[1]) >> 1;
  Dither_vtx[15].v.ob[2] = 0;
  Dither_vtx[15].v.flag  = 0;
  Dither_vtx[15].v.tc[0] = 0;
  Dither_vtx[15].v.tc[1] = 0;
  Dither_vtx[15].v.cn[0] = 0x00;
  Dither_vtx[15].v.cn[1] = 0;
  Dither_vtx[15].v.cn[2] = 0;
  Dither_vtx[15].v.cn[3] = 0x00;

  /* Setup display modes antialiased in 1 cycle */
  gDPPipeSync(glistp++);

  gSPVertex(glistp++, &(Dither_vtx[0]), 16, 0);

  gSP1Triangle(glistp++,  0,  4, 12, 0);  
  gSP1Triangle(glistp++,  0, 12, 11, 0);  

  gSP1Triangle(glistp++,  5,  1,  6, 0);  
  gSP1Triangle(glistp++,  5,  6, 13, 0);  

  gSP1Triangle(glistp++, 14,  7,  2, 0);  
  gSP1Triangle(glistp++, 14,  2,  8, 0);  

  gSP1Triangle(glistp++, 10, 15,  9, 0);  
  gSP1Triangle(glistp++, 10,  9,  3, 0);  
}

static void DitherInit(void)
{
  ViDitherEnable        =         0;
  DitherEnable          =         0;
  
  TranslateHorizontal   =      -121;
  TranslateVertical     =       -88;
  XScale                =      0.25;
  YScale                =      0.25; 

  ReadTestIncrementController = 0; 

  WantToChangeVideoMode = 1;
}

static void DitherFunc(void)
{
  DoDitherPolys();
  CleanupAndSendDisplayList(FAST3D);
}

static void DitherEngine(void)
{
  static int LastNext   = 1;

  if (!ReadTestIncrementController)
    {
      if (ZaruGetNextTestButton()) 
	{
	  if (!LastNext)
	    {
	      DitherEnable++;
	      ViDitherEnable++;

	      if (zaruexists) 
		{
		  ZaruSetMemA(TestStruct[CurrentTestNum].ZaruInitialLEDValue + DitherEnable);
		}
	    
	  
	      if (DitherEnable == 3)
		{
		  ReadTestIncrementController = 1;
		}

	      ControllerInput = 1;
	    }
	  LastNext = 1;
	}
      else
	{
	  LastNext = 0;
	}
    }
}

static void DivotInit(void)
{
  XScale                = 0.25;

  /* osViBlack(TRUE); */
  WriteToFrameBuffer();
  /* osViBlack(FALSE); */

  ReadTestIncrementController = 0;

  WantToChangeVideoMode       = 1;
}

static void DivotFunc(void)
{
}

static void DivotEngine(void)
{
  static int LastNext   = 1;

  if (!ReadTestIncrementController)
    {
      if (ZaruGetNextTestButton()) 
	{
	  if (!LastNext)
	    {
	      ViDivotEnable  ^= 1;
	      ControllerInput = 1;
	      
	      ReadTestIncrementController = 1;

	      if (zaruexists) 
		{
		  ZaruSetMemA(TestStruct[CurrentTestNum].ZaruInitialLEDValue + 1);
		}
	    }
	  LastNext = 1;
	}
      else
	{
	  LastNext = 0;
	}
    }
}

static void CleanupGlobals(void)
{
  if (VideoModeIndex > MaxVideoModeIndex)
    VideoModeIndex = MinVideoModeIndex;
  else if (VideoModeIndex < MinVideoModeIndex)
    VideoModeIndex = MaxVideoModeIndex;
}

static void doLinePoly(void)
{
  ClearFrameBuffer(TestStruct[CurrentTestNum].DoBackgroundRects, cfb_ptrs[draw_buffer]); 
  DoCommonSetup(); 
      
  (*(TestStruct[CurrentTestNum]).TestDisplayFunc)();
  if (! NoEngines) (*(TestStruct[CurrentTestNum]).TestEngineFunc)();
      
  SwapViBuffer();      
}

static void doOneShot(void)
{
  if  ((LastFrameClearVideoMode.ScreenWidth != 
	VideoModeArray[VideoModeIndex].ScreenWidth) ||
       (LastFrameClearVideoMode.NumColorBits != 
	VideoModeArray[VideoModeIndex].NumColorBits))
    {
      ClearFrameBuffer(0, FrameBufferPointer[0]);
    }

  if (VideoModeArray[VideoModeIndex].NumColorBits == 32)
    {
      gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_32b, SCREEN_WD, 
		       OS_K0_TO_PHYSICAL(cfb_ptrs[0]));
    }
  else
    {
      gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, 
		       OS_K0_TO_PHYSICAL(cfb_ptrs[0]));
    }

  gDPSetCycleType(glistp++, G_CYC_1CYCLE);  

  DoCommonSetup(); 
      
  (*(TestStruct[CurrentTestNum]).TestDisplayFunc)();
  if (! NoEngines) (*(TestStruct[CurrentTestNum]).TestEngineFunc)();
      
  DontSwapViBuffer();      
}

static void doFrameTest(void)
{
  DoCommonSetup(); 
      
  (*(TestStruct[CurrentTestNum]).TestDisplayFunc)();
  if (! NoEngines) (*(TestStruct[CurrentTestNum]).TestEngineFunc)();
      
  DontSwapViBuffer();      
}

void DoTestSetup(void)
{
  cfb_ptrs[0] = FrameBufferPointer[TestStruct[CurrentTestNum].FrameBufferIndex];
  cfb_ptrs[1] = (unsigned int *) ((unsigned int *) cfb_ptrs[0] + 320*240);

  VideoModeIndex = TestStruct[CurrentTestNum].VideoModeIndex;

  if (zaruexists) 
    {
      ZaruSetVideoSource(TestStruct[CurrentTestNum].ZaruVideoMode);
      ZaruSetMemA(TestStruct[CurrentTestNum].ZaruInitialLEDValue);
    }

  (*(TestStruct[CurrentTestNum]).TestInitFunc)();  
}

static void IncrementTestNumber(void)
{  
  CurrentTestNum++;
  
  /*
   * Force RunViTests() to return if we've cycled through all five screens;
   * thus we return instead of setting CurrentTestNum to zero.
   */
  if (CurrentTestNum == MAXTESTNUM) {
    
    /* CurrentTestNum = 0; */
    
    return;
  }
  
  if (CurrentTestNum < 0) {
    
    /* CurrentTestNum = MAXTESTNUM -1; */
    
    return;
  }
  
  
  InitVariables();
  
  DoTestSetup();
  ControllerInput = 1;
}

static void InitVariables(void)
{
  DitherEnable          = 0;
  ViDitherEnable        = 0;
  ViGammaEnable         = 1;
  ViGammaDither         = 1;
  ViDitherEnable        = 0;
  VideoModeIndex        = 0;
  TranslateHorizontal   = 0;
  TranslateVertical     = 0;
  XScale                = 1.0;
  YScale                = 1.0;
  
}

static ChangeVideoModes(void)
{
  SCREEN_WD = VideoModeArray[VideoModeIndex].ScreenWidth;
  SCREEN_HT = VideoModeArray[VideoModeIndex].ScreenHeight;
  
  osViSetMode(&osViModeTable[VideoModeArray[VideoModeIndex].ModeNumber]);
  
  WantToChangeVideoMode = 0;
}

static void ReadController(void)
{
  static LastNext = 0;

  if (ZaruGetNextTestButton()) 
    {
      if (!LastNext) 
	{
	  IncrementTestNumber();
	}
      LastNext = 1;
    } 
  else 
    {
      LastNext = 0;
    }
}

static void DoMainAppLoops(void)
{
  while (1)
    {
      if (ReadTestIncrementController) ReadController();
      if (CurrentTestNum == MAXTESTNUM)
	  return;
      CleanupGlobals();

      if (WantToChangeVideoMode)
	{	
	  ChangeVideoModes();
	}

      InitDisplayLists();
      (*(TestStruct[CurrentTestNum]).TestMainLoop)();
    }
}

void SetupFrameBufferPointers(void)
{
  FrameBufferPointer[0] = cfb_16_a;

  if (osMemSize == 0x400000)
    {
      FrameBufferPointer[1] = cfb_16_a;
      FrameBufferPointer[2] = cfb_16_a;
    }
  else if (osMemSize == 0x600000)
    {       
      FrameBufferPointer[1] = (unsigned int *) L26V;
      FrameBufferPointer[2] = (unsigned int *) L26V;
    }
  else if (osMemSize == 0x800000)
    {
      FrameBufferPointer[1] = (unsigned int *) L26V;
      FrameBufferPointer[2] = (unsigned int *) L28V;
    }
}

int RunViTests()
{
  
  int i;
  tlistp = &tlist;
  dynamicp = &dynamic;

  ZaruWaitForNextTestButton();

  SetupFrameBufferPointers();

  DoTestSetup();
  DoMainAppLoops();

  return(0);
}

