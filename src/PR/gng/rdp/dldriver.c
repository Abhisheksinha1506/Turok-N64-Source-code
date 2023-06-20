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
 * File:	dldriver.c
 *
 * Routines which render frames of various display lists, where each rendered
 * frame tests a specific functional portion of the RCP.
 *
 */
#include <ultra64.h>
#include <ramrom.h>
#include <assert.h>
#include "controller.h"

#include "dldriver.h"
#include "checksum.h"
#include "../gng_report/font_ext.h"
#include "gng.h"

extern ModuleTest_t moduleTestSet[];

extern int frame_count;
extern int module_num;
extern int rdp_DRAM_io;
extern int checksumRequest;
extern int rdp_regressionFlag;
extern int rdp_mspanFlushFlag;
extern int draw_buffer;
extern int cfb_size;
extern int controlFrame;
extern int lastFrameNum;
extern int generateFullSync;
extern int controllerSlot;
extern int uselines;

int lastModuleNum;
/*
 * should be set in main.c and		
 * extern'ed here if needed to be set from command line.
 */
int dumpRdp = 0;			

extern int doChecksum;		/* checksum */

extern void  clear_framebuffers(int pixSize, int clearColor);
extern void
computeChecksum(	int ModuleNum,
			int frameNum,
			int avoidTest,
			int pixSize,
			int width,
			int height,
			unsigned long *fb,
			unsigned long long oldchecksumValue);

extern OSMesgQueue	dmaMessageQ, rspMessageQ, rdpMessageQ, retraceMessageQ;
extern OSMesg		dmaMessageBuf, rspMessageBuf, rdpMessageBuf, 
			retraceMessageBuf;
extern OSMesg		dummyMessage;
extern OSIoMesg		dmaIOMessageBuf;

extern Dynamic dynamic;

extern u64 dram_stack[];
extern u64 dram_yield[];

extern u64 rdp_output_len;
extern u64 rdp_output[];

extern OSTask	tlist;

extern char *staticSegment;
extern char *static1Segment;
extern char *static2Segment;
extern char *textureSegment;

extern Gfx *glistp;

int errTotal = 0;
unsigned long *cfb_current;

void
computeChecksum(	int moduleNum,
			int frameNum,
			int avoidTest,
			int pixSize,
			int width,
			int height,
			unsigned long *fb,
			unsigned long long oldchecksumValue)
{
    unsigned long	*longPixels;
    unsigned long long	checksumValue;
    int			row, column;
    char		message[256];

    /*
     * checksum calculates 32 bits, so if 16 bit fb, than 2 pixels at a time.
     * if 8 bit fb, than 4 pixels at a time
     */

    if ( pixSize == G_IM_SIZ_8b )
	width >>= 2;

    if ( pixSize == G_IM_SIZ_16b )
	width >>= 1;

    longPixels = (unsigned long *) (fb);
    checksumValue = 0;

    for (column = 0; column < height; column++){
      for (row = 0; row < width; row++) {
	checksumValue += *longPixels++;
      }
    }

    if (oldchecksumValue != checksumValue && !avoidTest) {
	PRINTF("ERROR: (%d:%d): exp 0x%llx, computed 0x%llx\n", 
	 moduleNum,frameNum,oldchecksumValue, checksumValue);
	sprintf(message, 
	  "RDP DL ERROR: (%d:%d):\nexpected 0x%llx\ncomputed 0x%llx\n",
	  moduleNum,frameNum,oldchecksumValue, checksumValue);
	gng_report(message, 1, GNG_PASS_FAIL_BIT, 0);
	errTotal++;
    } else {
	if (!avoidTest)
	  PRINTF("       (%d:%d):     0x%0llx,\n",moduleNum,frameNum, 
			checksumValue);
	else
	  PRINTF("       (%d:%d):\n",moduleNum,frameNum);
    }
/* XXX do the hidden bits */
}

/*
 * Returns number of checksum errors found (if a checksum compare was 
 * requested), zero otherwise.
 */
int
dlDriver() 
{
    OSTask	*tlistp;
    Dynamic	*dynamicp;
    int		testListCount;
    int		frameNum, endFrame;
    int		moduleNum, startModule, endModule;
    int         keep_going = 1;
    int		pixSize;
    int		clearColor;
    u32		dummy_val;
    int		i, checksumIndex;
    int button ,lastButton = 0;
    char 	message[32];

    errTotal = 0;


    /* 
     * Count number of tests to run for each module under test, and stuff
     * an array of pointers to the individual module test entry points, so 
     * that we can invoke them from the main game loop below.
     */

    /*
     * CS_MODULE
     */
    testListCount = 0;
    moduleTestSet[CS_MODULE].gfxTests = testList_cs;

    while ( (testList_cs[testListCount].gfx_dl != (Gfx *) NULL) &&
	    (testList_cs[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[CS_MODULE].testListCount = testListCount;

    /*
     * TM_MODULE
     */
    testListCount = 0;
    moduleTestSet[TM_MODULE].gfxTests = testList_tm;

    while ( (testList_tm[testListCount].gfx_dl != (Gfx *) NULL) &&
	    (testList_tm[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[TM_MODULE].testListCount = testListCount;

    /*
     * TC_MODULE
     */
    testListCount = 0;
    moduleTestSet[TC_MODULE].gfxTests = testList_tc;

    while ( (testList_tc[testListCount].gfx_dl != (Gfx *) NULL) &&
	    (testList_tc[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[TC_MODULE].testListCount = testListCount;

    /*
     * TF_MODULE
     */
    testListCount = 0;
    moduleTestSet[TF_MODULE].gfxTests = testList_tf;

    while ( (testList_tf[testListCount].gfx_dl != (Gfx *) NULL) &&
	    (testList_tf[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[TF_MODULE].testListCount = testListCount;

    /*
     * CC_MODULE
     */
    testListCount = 0;
    moduleTestSet[CC_MODULE].gfxTests = testList_cc;

    while ( (testList_cc[testListCount].gfx_dl != (Gfx *) NULL) &&
	    (testList_cc[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[CC_MODULE].testListCount = testListCount;

    /*
     * BL_MODULE
     */
    testListCount = 0;
    moduleTestSet[BL_MODULE].gfxTests = testList_bl;

    while ( (testList_bl[testListCount].gfx_dl != (Gfx *) NULL) &&
	    (testList_bl[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[BL_MODULE].testListCount = testListCount;

    /*
     * MS_MODULE
     */
    testListCount = 0;
    moduleTestSet[MS_MODULE].gfxTests = testList_ms;

    while ( (testList_ms[testListCount].gfx_dl != (Gfx *) NULL) &&
	    (testList_ms[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[MS_MODULE].testListCount = testListCount;

    /*
     * RDPATT_MODULE
     */
    testListCount = 0;
    moduleTestSet[RDPATT_MODULE].gfxTests = testList_rdpatt;

    while ( (testList_rdpatt[testListCount].gfx_dl != (Gfx *) NULL) &&
	   (testList_rdpatt[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[RDPATT_MODULE].testListCount = testListCount;

    /*
     * RDPCOV_MODULE
     */
    testListCount = 0;
    moduleTestSet[RDPCOV_MODULE].gfxTests = testList_rdpcov;

    while ( (testList_rdpcov[testListCount].gfx_dl != (Gfx *) NULL) &&
	   (testList_rdpcov[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[RDPCOV_MODULE].testListCount = testListCount;

    /*
     * RDPTEX_MODULE
     */
    testListCount = 0;
    moduleTestSet[RDPTEX_MODULE].gfxTests = testList_rdptex;

    while ( (testList_rdptex[testListCount].gfx_dl != (Gfx *) NULL) &&
	   (testList_rdptex[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[RDPTEX_MODULE].testListCount = testListCount;

    /*
     * RDPMS_MODULE
     */
    testListCount = 0;
    moduleTestSet[RDPMS_MODULE].gfxTests = testList_rdpms;

    while ( (testList_rdpms[testListCount].gfx_dl != (Gfx *) NULL) &&
	   (testList_rdpms[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[RDPMS_MODULE].testListCount = testListCount;

    /*
     * RDPEW_MODULE
     */
    testListCount = 0;
    moduleTestSet[RDPEW_MODULE].gfxTests = testList_rdpew;

    while ( (testList_rdpew[testListCount].gfx_dl != (Gfx *) NULL) &&
	   (testList_rdpew[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[RDPEW_MODULE].testListCount = testListCount;

    /*
     * RDPFB_MODULE
     */
    testListCount = 0;
    moduleTestSet[RDPFB_MODULE].gfxTests = testList_rdpfb;

    while ( (testList_rdpfb[testListCount].gfx_dl != (Gfx *) NULL) &&
	   (testList_rdpfb[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[RDPFB_MODULE].testListCount = testListCount;
    
    /*
     * RDP6M_MODULE
     */
    testListCount = 0;
    moduleTestSet[RDP6M_MODULE].gfxTests = testList_rdp6M;

    while ( (testList_rdp6M[testListCount].gfx_dl != (Gfx *) NULL) &&
	   (testList_rdp6M[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[RDP6M_MODULE].testListCount = testListCount;
    
    /*
     * RDP8M_MODULE
     */
    testListCount = 0;
    moduleTestSet[RDP8M_MODULE].gfxTests = testList_rdp8M;

    while ( (testList_rdp8M[testListCount].gfx_dl != (Gfx *) NULL) &&
	   (testList_rdp8M[testListCount].toplevel_dl != (CaseProc_t) NULL) ) {
	testListCount++;
    }
    moduleTestSet[RDP8M_MODULE].testListCount = testListCount;
    
    /*
     * Main game loop.  Send one (if specified) or all frames worth of DL to
     * be processed into test vectors, one after the other.  Optionally 
     * restrict ourselves to a single module as well; you can also run a single
     * frame from multiple module's, but that's a weird combination of -m and 
     * -f that isn't terribly interesting (but not worth ruling out).
     *
     * When dumping DL information, the commands will be sequentially numbered
     * such that we can generate separate .rdp files for each display list,
     * and thus generate separate tests to run as test vectors (providing
     * better fault isolation).
     *
     * Externally, we can write a tool to collapse redundant RDP initialization
     * from a sequence of DL's, so that if a second DL does not require as much
     * initialization as the first, we'll skip the unecessary set of mode
     * twiddling DL operations.
     */

    if (module_num < 0 || module_num > MODULE_COUNT) {
	startModule = 0;
    } else {
	startModule = module_num;
    }

	 osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]);
         osViSwapBuffer((void *)LL24R);
         osViSetXScale(0.5);
         osViSetYScale(0.13);
    
	if (osMemSize == MEM_6M) {    /* if mem = 6M, run all except 8M test */
	   endModule = MODULE_COUNT-1 ;
	}
	else if (osMemSize == MEM_8M) { /* if mem = 8M, run all tests */
	   endModule = MODULE_COUNT;
	}
	else{
	   endModule = MODULE_COUNT-2; /* if mem = 4M, run all except 6M and 8M tests */
	}

    for (moduleNum = startModule; moduleNum < endModule; moduleNum++) {

	if (controlFrame >  moduleTestSet[moduleNum].testListCount) {
	    controlFrame = 0;
	}
	if ( frame_count >= moduleTestSet[moduleNum].testListCount ) {
PRINTF("bogus -f <frame_count> %d ignored (testListCount for module %d is %d)\n",
	    frame_count, moduleNum,  moduleTestSet[moduleNum].testListCount);
PRINTF("NOTE: -f <frame_count> numbers frames from 0 .. (n-1)\n");
	    frame_count = -1;
	}

	if (frame_count < 0) {
	    frame_count = -1;
	    frameNum = -1;
	    endFrame = moduleTestSet[moduleNum].testListCount;
	}
	else {
	    frameNum = frame_count;
	}
	/*
	 * Reset this variable (which keeps us from drawing the same frame over
	 * and over again) each time we step to a new module.
	 */
	lastFrameNum = -2;
	lastModuleNum = -2;

	while (keep_going) {
	    int loopCnt;

	    /*
	     * If user requests a single frame read controller
	     */
	    if (frame_count > -1) {
#ifdef TESTING
		/*
		 * up and dn buttons control frame number
		 * left and right buttons control module number 
	 	 */
		button = readControllerButton(controllerSlot);
		if ((button == D_JPAD) && (lastButton == 0x0))  frameNum++;
		else if ((button == U_JPAD) && (lastButton == 0x0)) frameNum--;
		else if ((button == L_JPAD) && (lastButton == 0x0)) {
			moduleNum--;
		        if (moduleNum < 3) 
			  moduleNum = 3;
			else
			  frameNum = moduleTestSet[moduleNum].testListCount -1;
		} 
		else if ((button == R_JPAD) && (lastButton == 0x0)) {
			moduleNum++;
			if (moduleNum == MODULE_COUNT) 
			  moduleNum = MODULE_COUNT -1;
			else 	
			  frameNum = 0;
		}
		 
		/* 
		 * if frame number crosses min or max, switch to prev or next module
		 */
 		if (frameNum < 0){
		     moduleNum--;
		     if (moduleNum < 3) moduleNum = 3;
                     frameNum = moduleTestSet[moduleNum].testListCount -1;
		}
		if (frameNum >= moduleTestSet[moduleNum].testListCount){
			frameNum = 0;
			moduleNum++;
			if (moduleNum == MODULE_COUNT) moduleNum = MODULE_COUNT -1;
  	 	}
		lastButton = button;
#endif
	    }
	    else {
		frameNum++;
		if (frameNum == endFrame) break;

		/*
		 * If the user has requested multiple frames AND we are
		 * dumping to dram, only generate fullSync for the last
  		 * frame.
		 */

		if (rdp_DRAM_io) {
		    if (frameNum == (endFrame - 1) ) {
		        generateFullSync = 1;
		    } else 
			generateFullSync = 0;
                }

	    }

	    if ((frameNum != lastFrameNum) || (moduleNum != lastModuleNum)) {

	    /*
	     * Always clear the frame buffer, but do it as a separate task 
	     * so that the RDP instructions don't make it into the RDP DL 
	     * we dump out as input for the test vector generator.
	     */

	    pixSize = moduleTestSet[moduleNum].gfxTests[frameNum].cfb_pixSize;
	    clearColor = moduleTestSet[moduleNum].gfxTests[frameNum].cfb_clearColor;
	    clear_framebuffers(pixSize, clearColor);

	    /*
	     * Set up the video mode for either 16 bit or 32 bit pixels.
	     */

	    /*
	     * Provide a name for each display list segment we are to dump, so
	     * that rdpasciitordram can provide meaningful filenames.  Only the
	     * first frame's name is used for each module.  If a module needs
	     * to render in 16 bit and 32 bit, there will have to be two 
	     * sequences of frames (and two .rdram files), since the rdram
	     * file can only support 16 or 32 bit rendering (not both).
	     *
	     * Finally, a third type of rdram file could be a 1024x1024 cfb,
	     * which we use for edge walker testing.
	     */
	    if ( ( (rdp_DRAM_io) && (frameNum == 0) ) ||
		 ( (rdp_DRAM_io) && (frame_count > -1) ) ) {
		if ( pixSize == G_IM_SIZ_16b ) {
		    PRINTF("TEST %s %d bit framebuffer\n", 
		      moduleTestSet[moduleNum].gfxTests[frameNum].testname, 16);
		} else if ( pixSize == G_IM_SIZ_32b ) {
		    PRINTF("TEST %s %d bit framebuffer\n", 
		      moduleTestSet[moduleNum].gfxTests[frameNum].testname, 32);
		} else if ( pixSize == 1024 ) {
		    PRINTF("TEST %s 1024 x 1024 32 bit framebuffer\n", 
		      moduleTestSet[moduleNum].gfxTests[frameNum].testname);
		} else {
		    PRINTF("bogus pixel size %d for test %s\n", pixSize, 
		      moduleTestSet[moduleNum].gfxTests[frameNum].testname);
		}
	    }

	    /*
	     * set up pointers to build the display list.
	     */
	    tlistp = &tlist;
	    dynamicp = &dynamic;
	    glistp = &(dynamicp->glist[0]);
	    
	    /*
	     * Tell RCP where each segment is
	     */
	    gSPSegment(glistp++, 0, 0x0); /* K0 (physical) address segment */
	    gSPSegment(glistp++, STATIC_SEGMENT,
		       osVirtualToPhysical(staticSegment));
	    gSPSegment(glistp++, STATIC_SEGMENT1,
		       osVirtualToPhysical(static1Segment));
	    gSPSegment(glistp++, STATIC_SEGMENT2,
		       osVirtualToPhysical(static2Segment));
	    /*
	    gSPSegment(glistp++, TEXTURE_SEGMENT,
		       osVirtualToPhysical(textureSegment));
	     */
	    
	    if (rdp_mspanFlushFlag) {
		/*
		 * Force the pipeline to empty after the rendering of each
		 * display list item, to avoid incurring span buffer cache 
		 * coherency problems with DRAM r-m-w cycles.
		 */
		gDPPipelineMode(glistp++, G_PM_1PRIMITIVE);
	    }
	    
	    gSPDisplayList(glistp++, rdpinit_dl);
	    gSPDisplayList(glistp++, rspinit_dl);

    	    /*
             * Setup and render module and frame numbers into the mini frame buffer
     	     */
    	    gDPSetColorImage( glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b,
    	    SCREEN_WD, OS_K0_TO_PHYSICAL(LL24R));

    	    gDPSetScissor(glistp++,G_SC_NON_INTERLACE, 0, 0, 160, 32);
    	    gDPPipeSync(glistp++);
    	    /*
     	     * clear the auxiliary frame_buffer
     	     */
    	    gDPSetCycleType(glistp++,G_CYC_FILL);
    	    gDPSetFillColor(glistp++,GPACK_RGBA5551(0,0,0,1) << 16 |
                     GPACK_RGBA5551(0,0,0,1));
    	    gDPFillRectangle(glistp++,0, 0, 159, 31);
    	    gDPPipeSync(glistp++);

    	    font_init( &glistp );       /* Initialize fonts */

    	    gDPSetBlendColor( glistp++, 0, 0, 0, 0 );
    	    gDPSetAlphaCompare( glistp++, G_AC_THRESHOLD);
    	    gDPSetRenderMode(glistp++,G_RM_OPA_SURF, G_RM_OPA_SURF2);
    	    gDPSetCycleType(glistp++,G_CYC_1CYCLE);

    	    font_set_pos( 10, 10 );     /* Setup where and how to draw text */
    	    font_set_color( 55, 55, 255, 255 );
    	    font_set_scale(1.0, 1.0);
    	    font_set_win(80,32);

  	    /* 
  	     * Display module and frame number
   	     */
    	    sprintf(message, "RDP TESTS:(%d:%d)\n",moduleNum,frameNum);
    	    font_show_string( &glistp, message);
    	    font_finish( &glistp );

	    /* 
       	     * Re init rdp and rsp state for test DL
	     */
	    gSPDisplayList(glistp++, rdpinit_dl);
	    gSPDisplayList(glistp++, rspinit_dl);

	    /*
	     * Figure out which checksum value to use.
	     */

	    for (i = 0, checksumIndex = 0; i <  moduleNum; i++) {
	       checksumIndex += moduleTestSet[i].testListCount;
	    }
	    checksumIndex += frameNum;

	    /* check if test needs to be run in 1PRIM mode */

 	    if (checksumAttrib[checksumIndex].onePrim)
		gDPPipelineMode(glistp++, G_PM_1PRIMITIVE);

	    /*
	     * If the rdp_regressionFlag is set, apply a 1/4 shrink to the 
	     * viewport so that the tests will render more quickly (because they
	     * won't be as fill limited).  Do this after we invoke the display
	     * list pointed to by setup_rspstate.
	     */
	    if (rdp_regressionFlag) {
		gSPDisplayList(glistp++, regression_viewport);
	    } 
	    /*
	     * Determine 16/32 bit rendering, then issue the appropriate
	     * gsDPSetColorImage() calls.  Width of Z buffer is determined
	     * by width of color frame buffer.
	     */

	    gDPSetDepthImage( glistp++, zbuffer );
	    gDPPipeSync(glistp++);

	    if ( pixSize == G_IM_SIZ_16b ) {
		gDPSetColorImage( glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 
		    SCREEN_WD, OS_K0_TO_PHYSICAL(cfb_16_a) );
	    } else if ( pixSize == G_IM_SIZ_32b ) {
		gDPSetColorImage( glistp++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 
		    SCREEN_WD, OS_K0_TO_PHYSICAL(cfb_16_a) );
	    } else {
		/*
		 * 1024 x 1024 framebuffer; we'll render in 32 bits.
		 */
		gDPSetColorImage( glistp++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 
		    1024, OS_K0_TO_PHYSICAL(cfb_16_a) );
	    }
	    gDPPipeSync(glistp++);

	    /* end of standard display list part. */
	    
	    /* 
	     * Build graphics task:
	     */
	    tlistp->t.type = M_GFXTASK;
	    tlistp->t.flags = OS_TASK_DP_WAIT;
	    tlistp->t.ucode_boot = (u64 *) rspbootTextStart;
	    tlistp->t.ucode_boot_size = ((int)rspbootTextEnd - 
					 (int)rspbootTextStart);

	    /*
	     * choose which ucode to run:
	     */
	    if (rdp_DRAM_io) {
		/* re-direct output to DRAM: */
		if (uselines) {
		    tlistp->t.ucode = (u64 *) gspLine3D_dramTextStart;
		    tlistp->t.ucode_data = (u64 *) gspLine3D_dramDataStart;
		} else {
		    tlistp->t.ucode = (u64 *) gspFast3D_dramTextStart;
		    tlistp->t.ucode_data = (u64 *) gspFast3D_dramDataStart; 
		}
	    } else {
		/* RSP output over XBUS to RDP: */
		if (uselines) {
		    tlistp->t.ucode = (u64 *) gspLine3DTextStart;
		    tlistp->t.ucode_data = (u64 *) gspLine3DDataStart;
		} else {
		    tlistp->t.ucode = (u64 *) gspFast3DTextStart;
		    tlistp->t.ucode_data = (u64 *) gspFast3DDataStart;
		}
	    }
	    
	    tlistp->t.ucode_size = SP_UCODE_SIZE;
	    tlistp->t.ucode_data_size = SP_UCODE_DATA_SIZE;
	    
	    tlistp->t.dram_stack = (u64 *) &(dram_stack[0]);
	    tlistp->t.dram_stack_size = SP_DRAM_STACK_SIZE8;

	    if (rdp_DRAM_io) {
		tlistp->t.output_buff = (u64 *) &(rdp_output[0]);
		tlistp->t.output_buff_size = (u64 *) &rdp_output_len;
	    } else {
		tlistp->t.output_buff = (u64 *) 0x0;
		tlistp->t.output_buff_size = (u64 *) 0x0;
	    }

	    /* initial display list: */
	    tlistp->t.data_ptr = (u64 *) dynamicp->glist;
	    tlistp->t.data_size = ((int)(glistp - dynamicp->glist) *
				   sizeof (Gfx));
	    tlistp->t.yield_data_ptr = (u64 *) NULL;
	    tlistp->t.yield_data_size = 0xDA0;

	    /*
	     * Render the display list stored in the dynamic segment.
	     *
	     * The top level DL driver routines in toplevel.c will decide 
	     * whether to issue a FullSync or not depending on the value of
	     * generateFullSync.
	     *
	     * NOTE: this is done after setting up the task header so that
	     * the testcase procedure can modify the task list if neccessary
	     */


	    (*(moduleTestSet[moduleNum].gfxTests[frameNum].toplevel_dl)) 
	     (dynamicp, (moduleTestSet[moduleNum].gfxTests[frameNum].gfx_dl));


	    /*
	     * Force top-level display list to have an END.
	     */
	    gSPEndDisplayList(glistp++);
	    
	    assert((glistp - dynamicp->glist) < MAX_GRAPHICS_SIZE);


	    /*
	     * Can just flush 16KB and forget about each individual pieces
	     * of data to flush.
	     */
	    osWritebackDCacheAll();
	    
	    /* unwrap this macro for debugging:
	     *
	     *	osSpTaskStart(tlistp);
	     *
	     */

	    osSpTaskLoad(tlistp);
	    osSpTaskStartGo(tlistp);
	    
	    (void)osRecvMesg(&rspMessageQ, &dummyMessage, OS_MESG_BLOCK);
	if (rdp_DRAM_io) {
	    /* wait for SP completion */
	    (void)osRecvMesg(&rspMessageQ, &dummyMessage, OS_MESG_BLOCK);
	/* 
	 * Wait for a vertical retrace to go by (Total hack, but necessary, as
	 * rdp_output_len is not updated properly unless we wait for a vertical,
	 * even though the SP interrupt has arrived).  Maybe we need to flush
	 * a data cache?
	 *
	 * Make sure there isn't an old retrace in queue 
	 * (assumes queue has a depth of 1) by checking to see if the 
	 * MQ is full.
	 */

	    if (MQ_IS_FULL(&retraceMessageQ))
	    /*
	     * Eat the old retrace message prior to the real wait below.
	     */
	    (void)osRecvMesg(&retraceMessageQ, &dummyMessage, 
		OS_MESG_BLOCK);

	/* 
	 * Now really wait for vertical retrace to finish.
	 */
	(void)osRecvMesg(&retraceMessageQ, &dummyMessage, 
		OS_MESG_BLOCK);
	}


	    /* 
	     * Always wait for DP completion
	     */
		(void)osRecvMesg(&rdpMessageQ, &dummyMessage, 
		    OS_MESG_BLOCK);

#ifndef _FINALROM
if (rdp_DRAM_io && dumpRdp){
	guParseRdpDL(OS_DCACHE_ROUNDUP_ADDR(&rdp_output[0]), 
	(u32)(*((u64 *)OS_DCACHE_ROUNDUP_ADDR(rdp_output_len))), 0);
}
#endif
        	

	    /* 
	     * Wait for a vertical retrace to go by.
	     *
	     * Make sure there isn't an old retrace in queue 
	     * (assumes queue has a depth of 1) by checking to see if the 
	     * MQ is full.
	     */

	    if (MQ_IS_FULL(&retraceMessageQ))
		/*
		 * Eat the old retrace message prior to the real wait below.
		 */
		(void)osRecvMesg(&retraceMessageQ, &dummyMessage, 
		    OS_MESG_BLOCK);

	    /* 
	     * Now really wait for vertical retrace to finish.
	     */
	    (void)osRecvMesg(&retraceMessageQ, &dummyMessage, 
		    OS_MESG_BLOCK);
	    }
	    lastFrameNum = frameNum;
	    lastModuleNum = moduleNum;

	    /*
	     * do the checksums
	     */

	    if (doChecksum) {


    		if (i == 15){
			cfb_current = (unsigned long *)L26R;
		} else if (i == 16){
			cfb_current = (unsigned long *)H28R;
    		} else 
			cfb_current = (unsigned long *)cfb_16_a;

		computeChecksum(
		  i, frameNum,
		  checksumAttrib[checksumIndex].avoidtest,
		  checksumAttrib[checksumIndex].pixtype,
		  checksumAttrib[checksumIndex].width,
		  checksumAttrib[checksumIndex].height,
		  cfb_current,
		  testChecksums[checksumIndex]);

	    }


	    if (frame_count > -1) {
		if (rdp_DRAM_io) {
		    /* 
		     * User has requested a DRAM dump of a particular frame.
		     * Clear the "keep_going" variable so that we will call
		     * osExit(), which will force gload to exit & flush all
		     * pending character I/O.
		     */
		    keep_going = 0;
		} else {
		    if ((frameNum < 0) || (frameNum > 
		      moduleTestSet[moduleNum].testListCount - 1)) {
			frameNum = 0;
			controlFrame = 0;
		    }
		}
	    }
	}
    }
    return(errTotal);
}


ChecksumAttrib_t checksumAttrib[] = {
    /*
    * CS_MODULE (0)
    {1, G_IM_SIZ_32b, 1023, 255, 0},
     */

    /*
     * TM_MODULE (3)
     */
    {0, G_IM_SIZ_32b, 320, 240, 0},
    {1, G_IM_SIZ_32b, 320, 240, 0},
    {1, G_IM_SIZ_32b, 320, 240, 0},
    {0, G_IM_SIZ_32b, 320, 240, 0},
    {0, G_IM_SIZ_32b, 320, 240, 0},
    {0, G_IM_SIZ_32b, 320, 240, 0},
    {1, G_IM_SIZ_32b, 320, 240, 0},
    /*
     * TC_MODULE (4)
     */
    {1, G_IM_SIZ_16b, 320, 240, 0},
    /*
     * TF_MODULE (5)
     */
    {0, G_IM_SIZ_32b, 320, 240, 0},
    {0, G_IM_SIZ_32b, 320, 240, 0},
    {0, G_IM_SIZ_32b, 320, 240, 0},
    {0, G_IM_SIZ_32b, 320, 240, 0},
    {0, G_IM_SIZ_32b, 320, 240, 0},
    /*
     * CC_MODULE (6)
     */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {1, G_IM_SIZ_32b, 320, 240, 0},
    /*
     * BL_MODULE (7)
     */
    {0, G_IM_SIZ_32b, 320, 240, 1},
    {0, G_IM_SIZ_32b, 320, 240, 0},
    {0, G_IM_SIZ_32b, 320, 240, 0},
    /*
     * MS_MODULE (8)
     */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {1, G_IM_SIZ_32b, 320, 240, 0},
    {2, G_IM_SIZ_32b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {1, G_IM_SIZ_16b, 320, 240, 0},
    {1, G_IM_SIZ_16b, 320, 240, 0},
    {2, G_IM_SIZ_32b, 320, 240, 0},
    {1, G_IM_SIZ_32b, 320, 240, 0},
    /*
     * RDPATT_MODULE (9)
     */
    {0, G_IM_SIZ_16b, 320, 240, 0}, /* Test 0 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_32b, 320, 240, 0}, /* Test 5 */
    {0, G_IM_SIZ_32b, 320, 240, 0},
    {0, G_IM_SIZ_32b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, /* Test 10 */
    {0, G_IM_SIZ_32b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 1},

    {0, G_IM_SIZ_16b, 320, 240, 1}, /* Test 15 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, /* Test 20 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, /* Test 25 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 1}, /* Test 30 */
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},

    {0, G_IM_SIZ_16b, 320, 240, 1}, /* Test 35 */
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 1},

    {0, G_IM_SIZ_16b, 320, 240, 1}, /* Test 40 */
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},

    {0, G_IM_SIZ_16b, 320, 240, 1}, /* Test 45 */
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},

    {0, G_IM_SIZ_16b, 320, 240, 0}, /* Test 50 */
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},

    {0, G_IM_SIZ_16b, 320, 240, 1}, /* Test 55 */
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    /*
     * RDPCOV_MODULE (10)
     */
    {0, G_IM_SIZ_16b, 320, 240, 0}, /* Test  0*/
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 1}, /* Test 5*/
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, /* Test 10*/
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},

    {0, G_IM_SIZ_16b, 320, 240, 0}, /* Test 15*/
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},

    {0, G_IM_SIZ_16b, 320, 240, 0}, /* Test 20*/
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, /* Test 25*/
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 1}, /* Test 30*/
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 1},

    {0, G_IM_SIZ_16b, 320, 240, 0}, /* Test 35*/
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, /* Test 40*/
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, /* Test 45*/
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, /* Test 50*/
    /*
     * RDPTEX_MODULE (11)
     */
    {0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 0 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 5 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 10 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0}, 
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 15 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 20 */
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 25 */
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 1},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 30 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 35 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 40 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 45 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    
    {0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 50 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
  
    {0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 55 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
  
    {0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 60 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
  
    {0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 65 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
  
    {0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 70 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
  
    {0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 75 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},

    {0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 80 */
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},
    {0, G_IM_SIZ_16b, 320, 240, 0},


    /*
     * RDPMS_MODULE (12)
     */
    	{0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 0 */
    	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},

	{0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 5 */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},

	{0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 10 */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},

	{0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 15 */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},

	{0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 20 */
	{1, G_IM_SIZ_16b, 320, 240, 0}, /* uses hardcoded cfb and zbuf addrs */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},

	{0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 25 */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 1}, /*No idea why this chesksums different*/
				        /*in this test vs PR/apps/rdpms_hw */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},

	{0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 30 */
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 1},

	{0, G_IM_SIZ_16b, 320, 240, 1},	/* Test 35 */
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},

    /*
     * RDPEW_MODULE (13)
     */
	{0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 0 */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},

	{0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 5 */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},

	{0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 10 */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 640, 480, 0},

	{0, G_IM_SIZ_16b, 320, 240, 0}, /* Test 15 */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_32b, 320, 240, 1}, 

	{0, G_IM_SIZ_8b, 320, 240, 1}, 	/* Test 20 */
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},

	{0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 25 */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{1, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},

	{0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 30 */
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 0},

	{0, G_IM_SIZ_16b, 320, 240, 0}, 	/* Test 35 */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	
	{0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 40 */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},

	{0, G_IM_SIZ_16b, 320, 240, 0},	/* Test 45 */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},

	{0, G_IM_SIZ_16b, 320, 240, 1},	/* Test 50 */
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 1},

	{0, G_IM_SIZ_16b, 320, 240, 1},	/* Test 55 */
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 1},
	{0, G_IM_SIZ_16b, 320, 240, 1},


     /*
      * RDPFB_MODULE (14)
      */
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},
	{0, G_IM_SIZ_16b, 320, 240, 0},

     /*
      * RDP6M_MODULE (15)
      */
	{0, G_IM_SIZ_32b, 320, 240, 0},
	{0, G_IM_SIZ_32b, 320, 240, 0},
     /*
      * RDP8M_MODULE (16)
      */
     /*
      * Checksum only a 1023x511 region even though the frame buffer
      * allocated is a 1024x512 since the scissor box can only do 
      * 1023 max window. So for convenience the scissor box is set
      * to 1023x511 (even though it can do a 1023x512) and the 
      * checksum window is a 1023x511
      */
	{0, G_IM_SIZ_32b, 1023, 511, 0}, /* Test 15 */ /* -ditto- */
	{0, G_IM_SIZ_32b, 1023, 511, 0}, /* Test 15 */ /* -ditto- */
	{0, G_IM_SIZ_32b, 1023, 511, 0}, /* Test 15 */ /* -ditto- */
};

unsigned long long testChecksums[] = {
    /*
     * CS_MODULE
    0x3d14459e693,
     */
    /*
     * TM_MODULE
     */
    0x40a3158b6200,
    0x20bf7daab500,
    0x211814d8ba00,
    0x18ca1d647700,
    0x10d41054d000,
    0x10ea03776600,
    0x228008470c08,
    /*
     * TC_MODULE
     */
    0x105007af3f32,
    /*
     * TF_MODULE
     */
    0x146731e16fc2,
    0x6286cb99e97,
    0x508eba77740,
    0x13bc03970ef5,
    0x31df63c95f7,
    /*
     * CC_MODULE
     */
    0x24b76c4fefb4,
    0x2d12e159c57,
    /*
     * BL_MODULE
     */
    0x2b733f1fa90,
    0x1700faa28b6,
    0x107995dd12e,
    /*
     * MS_MODULE
     */
    0x3c765c76200,
    0x1254828ee2f,
    0xc06d16dfd6f,
    0x3cd966e2218,
    0x3d116787bc6,
    0x3c94bfb4832,
    0x3c765c76200,
    0x46ca02148cb,
    0x9c0f9bde0a7,
    0x1254719eb21,
    /*
     * RDPATT_MODULE
     */
    0x13da8496b724,
    0x8433de1d618,
    0x7cf9a2216ce,
    0xfcf4896debe,
    0xb6e04450fc2,

    0x8cadd0aedac2,
    0x8bb8cdccea3e,
    0x89b4e26a1325,
    0x1a73004a95f0,
    0x7a3d8d57130,

    0x16ed6113cc0c,
    0x8833f576e2c2,
    0x211fbc256b8c,
    0x671fc83eae0,
    0xcc01117bb4c,

    0xcc01117bb4c,
    0x6eec09814ee,
    0x4e87493c57a,
    0xcc01117bb4c,
    0x24e93c89eb12,

    0x3c765c76200,
    0x3600e3f0329,
    0xa7f98f87f57,
    0x24e93c89eb12,
    0x24e93c89eb12,

    0x40e2e87ea36,
    0x24e93c89eb12,
    0x24e93c89eb12,
    0x24e93c89eb12,
    0x24e93c89eb12,

    0x17c1e6092dfe,
    0x19f911b9d521,
    0x1c6092adfaae,
    0x1ef14a0d127b,
    0x213dbeabea3a,

    0x2363b9e8730e,
    0x255ade7d6293,
    0x2152a6b9f61e,
    0x3cd30e71f64,
    0xdaefc0cfcd0,

    0xdbeb1f2e8ee,
    0x730bf63102e,
    0x76f52bfd8b2,
    0x7ac2d9935ec,
    0x7f35386601b,

    0x8376d86023d,
    0x889c0eeb6a5,
    0x8e58b2c277a,
    0x945dfc8132a,
    0x9a6132b11bb,

    0x24e93c89eb12,
    0x262764dd1657,
    0x2914ab1050ca,
    0x2a17ed223457,
    0x29712e6be5e7,

    0x78a46bd7b7a,
    0x1d72ae75b380,
    0x7c7df4c7159,
    0x4362b6fb967,
    /*
     * RDPCOV_MODULE
     */
    0x3db694e0582,
    0x8433de1d618,
    0x7cf9a2216ce,
    0x528ce583e6e,
    0xb6e04450fc2,
    0xee1846c5603,
    0xed1efebf4bc,
    0xecc5307b08c,
    0xec4f73ef9be,
    0x7fe92b43845,
    0x1343eedfc074,
    0xebce72d6647,
    0xea4a663d768,
    0xea6cf7c96ec,
    0xea49197137e,
    0xdabe7915b08,
    0xea2b9e70304,
    0xe9a4f15dfd1,
    0xe864f15afc8,
    0xe7806d9c7eb,
    0x7a3d8d57130,
    0x3c952ac486c,
    0x17d8b1f9be34,
    0x7bf9b8e2574,
    0xfd92c2cd5d7,
    0x14750cc8d1bb,
    0x4086e64365f,
    0x1f92233e68c,
    0x9431e2314e0,
    0x52f19ca14a3,
    0x568419ebbf35,
    0x3484b34411d,
    0x3c545b72380,
    0x24e64aebada8,
    0x2e0ea7908ae,
    0x3c765c76200,
    0x3c765c76200,
    0x3c765c76200,
    0x3c765c76200,
    0x3e431c3e428,
    0x55d46752427,
    0x55bd5fc7f37,
    0x55c50f5598d,
    0x55eb0be779b,
    0x55df50ea80e,
    0x55d6e18e5f2,
    0x55c37d252ee,
    0x55fb8fbe86e,
    0x55f4594766a,
    0x56186090085,
    0x3e6178613a0,
    /*
     * RDPTEX_MODULE
     */
       0x111a3f8bf774,	/* Test 0 */
       0x54a1aaac930,
       0xa6769996769,
       0x1220b6e2eb0,
       0x10b85011c0,

       0x4f884e5980,	/* Test 5 */
       0x14c0d50f40,
       0xe98567edba,
       0xc26b167ad6,
       0x278da7ac80,

       0x46cb06ca40,	/* Test 10 */
       0x3d82fd8380,
       0x341233f8c0,
       0x55aedd066b0,
       0x226ccd717e76,

       0x714c353139a,
       0x13ac638db3a,
       0x1ee9c559de8,
       0x1ebd4388afa,
       0x8da9a8ade4,

       0x8eb5325d56,	/* Test 20 */
       0xcb57e0feee6, 	
       0x178edb173a94,
       0x74ba4192310,
       0xace5ea8902f,

       0x19c97eb62404,	/* Test 25 */
       0x91b5a8d99ba,
       0x64bc5e01e96,
       0xe059ea9f54,
       0xda56fd36d57,

       0x12f8625c9fc,	/* Test 30 */
       0x226ccd717e76,
       0x226ccd717e76,
       0x226ccd717e76,
       0x226ccd717e76,

       0x320031ff9c00,	/* Test 35 */
       0x610ee2f0bc00,
       0x640a0a097e00,
       0x32004b001900,
       0x32004b001900,

       0x18cb1b7b02b0,	/* Test 40 */
       0x32004b001900,
       0x4c57f7f7,
       0x320550050a00,
       0x226ccd717e76,

       0x964b5dfb1ec,	/* Test 45 */
       0x4ad43c1faa,
       0x34f11d0eae00,
       0x32004b001900,
       0x32004b001900,

       0x18cb1b7b02b0,	/* Test 50 */
       0x32004b001900,
       0x4c57f7f7, 
	0xb6b00042300,
	0xbbc6e148100,

	0xc66113c8c80,	/* Test 55 */
	0xd5b0131fcc0,
	0xe7b4190f680,
	0xebff55d3900,
	0xcdb4ecdc580,

	0x977ef70f7c0,	/* Test 60 */
	0x9b187318280,
	0x98870ce1600,
	0x815cbd0d940,
	0x682f624c680,

	0x5d778af5a80,	/* Test 65 */
	0x572288a5780,
	0x2700664b7520,
	0x270a314242b0,
	0x270a3e88f608,

	0x270cd2b18e0e,	/* Test 70 */
	0x2715d6e3741c,
	0x27118f0c4a8a,
	0x271e22ac4406,
	0x2733337b09ac,


	0x273bcdf5d594,	/* Test 75 */
	0x2736f677514a,
	0x92bcfb0e69a,
	0x8e0c3dff0b2,
	0x8bc87318568,

	0x8a59930e134,	/* Test 80 */
	0x8871f5678ea,
	0x870ae9d0784,
	0x85d73f312ea,
	0x8459b6af01a,
        
    /*
     * RDPMS_MODULE
     */
    0x97b691e600,
    0xd51f40dd4a,
    0xbf487b0b3c,
    0x17d2edec79a,
    0x1e0f51854ea,

    0x1558ad8d184,
    0x190095c826b,
    0x49fa217ac3e,
    0x222b068b3516,
    0x222b068b3516,

    0xc6eef6ee4c,
    0x828defe3e0,
    0x96009600,
    0x22f10b6c61c,
    0x96009600,

    0x13a5e1040c3,
    0x13a5e1040c3,
    0x7d1b3e0a052,
    0x143381d90f1e,
    0x706dfb7f994,

    0x13f417d9996,
    0x76a8e1d86f2,
    0x1179f3222d2,
    0x222b068b3516,
    0x222b068b3516,

    0x222b068b3516,
    0x132d3bfb3f34,
    0x9638962f,
    0x29d795541,
    0x6667ca666,

    0xa105ae9504,
    0x201c81a8600,
    0x94dcf1885c0,
    0xb7d5fcafff7,
    0x6c57263033,

    0xba8a211c97f,
    0x4c9e4688984,
    0x76e03da499d,
    0x96009600,
    0x96009600,

   /*
    * RDPEW_MODULE
    */
       0x226ccd717e76,
       0x226ccd717e76,
       0x84bd0977374,
       0x226ccd717e76,
       0x1017cfb3a474,

       0x42d9a5f3630,
       0x195fe9600,
       0x1421fc310f6c,
       0xa89b3e3beba,
       0x29ec1ca2ad0,

       0xbe5794264dc,
       0x7cde683cb40,
       0x185aa0095979,
       0x6b47023761f,
       0x32edd2fd3b68,

       0x226ccd717e76,
       0x468fad7d05,
       0xbe5794264dc,
       0xdaa067989,
       0x1a4acf8f5a,

       0x6b4161f84,
       0xdaa067989,
       0x5e64967863e,
       0x5ffc5db749e,
       0x96009600,

       0x96009600,
       0x48d439d00,
       0x94a51589568,
       0x226ccd717e76,
       0x226ccd717e76,

       0x4710d1d8cd2,
       0xdeb343836be,
       0xb8fdc6c6561,
       0x204cc5ac2149,
       0x226ccd717e76,

       0x226ccd717e76,
       0x96009600,
       0x226ccd717e76,
       0x226ccd717e76,
       0x226ccd717e76,

	0x3a5ba94b730,
	0x37960a5a6eb,
	0x392dbfd7531,
	0x38e99fbcff7,
	0x39cdbee85e6,

	0x39657e23b86,
	0x395dbef5451,
	0x392aa689ea3,
	0x39315cc22b0,
	0x37f580322d2,

	0x2b8df2ed5358,
	0x2b9402149a2e,
	0x2b89ceccb26c,
	0x2b82e4b1f317,
	0x2b70bc2eaa35,

	0x2b750cee906d,
	0x2b781fbc3038,
	0x2b65067f5feb,
	0x2b65f6524ae8,
	0x2b630cd55090,

    /*
     * RDPFB_MODULE
     */
	0x2ace616e46,
	0x32d2bdf60f70,
	0x30027688ca94,
	0x2e61462f9d26,
        0xc2fc9365164,
    /*
     * RDP6M_MODULE
     */
        0x4462c1807804,
        0xa7a6aa3cb35,

    /*
     * RDP8M_MODULE
     */
        0x9a42aa115870,
	0x88fac503dd9d,
	0x892d6aa9509d
};
