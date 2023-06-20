
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
 * File:	gng_report.c
 *
 * Report diagnostic test status by generating a DL with sprite text data.
 *
 */

#include <ultra64.h>
#include <assert.h>
#include <PR/ramrom.h>
#include "dldriver.h"
#include "font_ext.h"
#include "gng.h"
#include "../uji/uji_audio.h"

#define  GLIST_LEN       2048

extern int sprintf(char *s, const char *fmt, ...);

extern OSMesgQueue	dmaMessageQ, rspMessageQ, rdpMessageQ, retraceMessageQ;
extern OSMesg		dmaMessageBuf, rspMessageBuf, rdpMessageBuf, 
			retraceMessageBuf;
extern OSMesg		dummyMessage;
extern OSIoMesg		dmaIOMessageBuf;

extern Dynamic dynamic;

extern int frame_count;
extern int module_num;
extern int rdp_DRAM_io;
extern int checksumRequest;
extern int rdp_regressionFlag;
extern int rdp_mspanFlushFlag;
extern int draw_buffer;
extern void *cfb_ptrs[];
extern int cfb_size;
extern int controlFrame;
extern int lastFrameNum;
extern int generateFullSync;
extern int controllerSlot;
extern int uselines;

extern u64 dram_stack[];
extern u64 dram_yield[];

extern u64 rdp_output_len;
extern u64 rdp_output[];

extern OSTask	tlist;

extern char *staticSegment;
extern char *textureSegment;

extern Gfx *glistp;

/*
 * Render a frame to the framebuffer with a string identifying the test, 
 * followed (in LARGE letters) the PASS/FAIL status of the test.
 */
void
gng_report( char *message, int testStatus, int flags, int delay)
{
    int i;
    OSTask	*tlistp;
    Dynamic	*dynamicp;
    int 	soundEffect = SOUND_NONE;
    gngstatus	*pstatus;

    /*
     * osAppNMIBuffer == 0x8000031c in locore rdram
     */
    pstatus = (gngstatus *)osAppNMIBuffer;

    /*
     * set up pointers to build the display list.
     */
    tlistp = &tlist;
    dynamicp = &dynamic;
    glistp = &(dynamicp->glist[0]);

    /*
     * Display 16 bit pixels.
     */
    osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]);

    
    /*
     * Tell RCP where each segment is
     */
    gSPSegment(glistp++, 0, 0x0); /* K0 (physical) address segment */
    gSPSegment(glistp++, STATIC_SEGMENT,
	       osVirtualToPhysical(staticSegment));
    
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
     * If the rdp_regressionFlag is set, apply a 1/4 shrink to the 
     * viewport so that the tests will render more quickly (because they
     * won't be as fill limited).  Do this after we invoke the display
     * list pointed to by setup_rspstate.
     */
    if (rdp_regressionFlag) {
	gSPDisplayList(glistp++, regression_viewport);
    } 

    /*
     * 16 bit rendering.  Width of Z buffer is determined
     * by width of color frame buffer.
     */

    gDPSetDepthImage( glistp++, zbuffer );
    gDPPipeSync(glistp++);

    gDPSetColorImage( glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 
	SCREEN_WD, OS_K0_TO_PHYSICAL(cfb_16_a) );
    gDPPipeSync(glistp++);

    gSPDisplayList(glistp++, clearcfb_dl);

    font_init( &glistp );			/* Initialize fonts */

    gDPSetBlendColor( glistp++, 0, 0, 0, 0 );
    gDPSetAlphaCompare( glistp++, G_AC_THRESHOLD );

    font_set_pos( 50, 40 );		  /* Setup where and how to draw text */
    font_set_color( 55, 55, 255, 255 );
    font_set_scale( 1.0, 1.0 );
    font_set_win( 27, 7 );

    font_show_string( &glistp, message);

    if(flags & GNG_PASS_FAIL_BIT) {
	/*
	 * For standard tests, show "PASS" at the current text position.
	 * For the final 'PASS', display the "PASS" in large green letters.
	 *
	 * Also play a tune for the final 'PASS', and a nasty tone for 
	 * any 'FAIL' messages.
	 */
	if (testStatus == 0) {
	    if (flags & GNG_FINAL_TEST_BIT) {
		font_set_pos( 60, 100 );
		font_set_win( 5, 3 );
		font_set_scale( 6.0, 6.0 );		/* BIG */
		/*
		 * Check to see if any tests failed during the sequence.
		 */
		if (pstatus->testFailed == 0) {
		    font_set_color( 8, 255, 8, 255 );		/* GREEN */
		    font_show_string( &glistp, "PASS" );
		    soundEffect = SOUND_PASS;
		} else {
		    font_set_color( 255, 8, 8, 255 );		/* RED */
		    font_show_string( &glistp, "FAIL" );
		    soundEffect = SOUND_FAIL;
		}
	    } else {
		font_set_color( 8, 255, 8, 255 );		/* GREEN */
		font_show_string( &glistp, "PASS" );
	    } 
	} else {
	    font_set_pos( 50, 180 );
	    font_show_string( &glistp, "Press yellow button\nto continue..." );
	    font_set_pos( 60, 100 );
	    font_set_win( 5, 3 );
	    font_set_scale( 6.0, 6.0 );			/* BIG */
	    font_set_color( 255, 8, 8, 255 );		/* RED */
	    font_show_string( &glistp, "FAIL" );
	    soundEffect = SOUND_FAIL;
	}
    }
    font_finish( &glistp );		

    /*
     * Complete the display list, then render to the framebuffer.
     */

    gDPFullSync(glistp++);
    gSPEndDisplayList(glistp++);

    assert((glistp-dynamicp->glist) < GLIST_LEN);

    /* 
     * Build graphics task:
     *
     */
    tlistp->t.ucode_boot = (u64 *) rspbootTextStart;
    tlistp->t.ucode_boot_size = (u32)rspbootTextEnd - (u32)rspbootTextStart;

    /* 
     * Use RSP ucode which outputs over XBUS to RDP: 
     */
    tlistp->t.ucode = (u64 *) gspFast3DTextStart;
    tlistp->t.ucode_data = (u64 *) gspFast3DDataStart;
    
    /* initial display list: */
    tlistp->t.data_ptr = (u64 *) dynamicp->glist;
    tlistp->t.data_size = (u32)((glistp - dynamicp->glist) * sizeof(Gfx));

    /*
     * Write back dirty cache lines that need to be read by the RCP.
     */
    osWritebackDCache(&dynamic, sizeof(dynamic));
    
    /*
     * start up the RSP task
     */

    osSpTaskStart(tlistp);
    
    /* wait for SP completion */
    (void)osRecvMesg(&rspMessageQ, NULL, OS_MESG_BLOCK);

    (void)osRecvMesg(&rdpMessageQ, NULL, OS_MESG_BLOCK);

    /* swap buffers, to display what we rendered. */
    osViSwapBuffer(cfb_16_a);

    /* 
     * Make sure there isn't an old retrace in queue 
     * (assumes queue has a depth of 1) 
     */
    if (MQ_IS_FULL(&retraceMessageQ))
	(void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);
    
    /* Wait for Vertical retrace to finish swap buffers */
    (void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);

    switch (soundEffect) {
        case SOUND_PASS:
	    chkPlaySound(SOUND_PASS);
	    break;
        case SOUND_FAIL:
	    chkPlaySound(SOUND_FAIL);
	    break;
        case SOUND_NONE:
	default:
	    break;
    }

    /*
     * Now wait for number of retrace intervals specified by delay
     */
    for (i = 0; i < delay; i++) {
	(void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);
    }
    /*
     * If a test failed, set a global variable to indicate this
     * (so that we'll not print "PASS" at the end of the test sequence),
     * then stall & wait for the user to press the yellow button.
     */
    if ( (flags & GNG_PASS_FAIL_BIT) && (testStatus != 0) ) {
	pstatus->testFailed = 1;
	ZaruWaitForNextTestButton();
    }
}
