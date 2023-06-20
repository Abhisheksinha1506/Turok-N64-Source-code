
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

#include <ultra64.h>

#include <ramrom.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


OSMesgQueue	controllerMsgQ;
OSMesg		controllerMsgBuf;

int initControllers(void);
OSContStatus     statusdata[MAXCONTROLLERS];
OSContPad        controllerdata[MAXCONTROLLERS];
OSViMode         tempOSViModeEntry;

static u16       lastbutton;

int ControllerMode = 0;

/*
 *
 * Return the lowest number controller connected to system
 */
int initControllers()
{
    OSMesgQueue     serialMsgQ;
    OSMesg          serialMsg;
    int             i;
    u8              pattern;

    osCreateMesgQueue(&serialMsgQ, &serialMsg, 1);
    osSetEventMesg(OS_EVENT_SI, &serialMsgQ, (OSMesg)1);

    osContInit(&serialMsgQ, &pattern, &statusdata[0]);

    osCreateMesgQueue(&controllerMsgQ, &controllerMsgBuf, 1);
    osSetEventMesg(OS_EVENT_SI, &controllerMsgQ, (OSMesg)0);

    for (i = 0; i < MAXCONTROLLERS; i++) {
        if ((pattern & (1<<i)) &&
                !(statusdata[i].errno & CONT_NO_RESPONSE_ERROR))
            return i;
    }
    return -1;
}

void ResetParameters(void)
{

#if 0	
	ControllerMode      =             0;

  UseViModeX          =             0;
  ScreenWidthDelta    =             0;

  UseAAMode           =             0;
  BlockWidth          =     CUBEWIDTH;
  CurrentCubeAxis     =             0;
  CurrentPlaneAxis    =             0;
  NumCubesPerAxis     =             4;
  TimerTicks          =             7;
  UseUCode            =             0;
  OutLen              = RDP_OUTPUT_BUF_LEN;
  ClipRatio           =             2;
  
  CubeDivisions[0]    =             0;
  CubeDivisions[1]    =             0;
  CubeDivisions[2]    =             0;
    
  PlaneDivisions[0]   =             0;
  PlaneDivisions[1]   =             0;
  
  PlaneMinMax[0][0]   =     PLANEMINX;
  PlaneMinMax[0][1]   =     PLANEMAXX;
  PlaneMinMax[1][0]   =     PLANEMINY;
  PlaneMinMax[1][1]   =     PLANEMAXY;
  PlaneMinMax[2][0]   =     PLANEMINZ;
  PlaneMinMax[2][1]   =     PLANEMAXZ;
  
  EyeZPosition        =             0;
  
  TranslateHorizontal =             0;
  TranslateVertical   =             0;
  
  CreateNewCubes      =             1;
  CreateNewPlanes     =             1;
  
  RotateGlobalXAxis   =             0;
  RotateGlobalYAxis   =             0;

  ShadingMode         =             1;
  UseTextureMode      =             0;
  UseGlobalTransforms =             1;

  HorizontalOffset    =             0;
  VerticalOffset      =             0;

  (*CurrentVideoModePtr).comRegs.hStart    = OriginalVideoMode.comRegs.hStart;
  (*CurrentVideoModePtr).fldRegs[0].vStart = OriginalVideoMode.fldRegs[0].vStart;
  (*CurrentVideoModePtr).fldRegs[1].vStart = OriginalVideoMode.fldRegs[1].vStart;

#endif

}

void ReadController(void)
{
	static u16 button;
	static s16 stickX, stickY;      
    
	(void)osRecvMesg(&controllerMsgQ, NULL, OS_MESG_BLOCK);
	osContGetReadData(controllerdata);

	button = controllerdata[0].button;
	stickX = controllerdata[0].stick_x;
	stickY = controllerdata[0].stick_y;

	if (button & CONT_UP)
	{
		rmonPrintf("1\n");
	}
		
	if (button & CONT_DOWN)
    {
		rmonPrintf("2\n");
	}

	if (button & CONT_RIGHT)
    {
   		rmonPrintf("3\n");
    }
	    
	if (button & CONT_LEFT)
    {
   		rmonPrintf("4\n");
    }


	if ((button & CONT_A) && !(lastbutton & CONT_A))
    {
   		rmonPrintf("5\n");
    }

	if ((button & CONT_B) && !(lastbutton & CONT_B))
    {
   		rmonPrintf("6\n");

    }

	if ((button & CONT_C) && !(lastbutton & CONT_C))
    {
   		rmonPrintf("7\n");
    }

	if ((button & CONT_F) && !(lastbutton & CONT_F))
    {      
   		rmonPrintf("8\n");
    }

	if ((button & CONT_D) /* && !(lastbutton & CONT_D) */)
    {
   		rmonPrintf("9\n");

    }

	if ((button & CONT_E) /* && !(lastbutton & CONT_E) */)
    {      
   		rmonPrintf("10\n");
    }


	if ((button & CONT_L) && !(lastbutton & CONT_L))
    {      
   		rmonPrintf("11\n");
    }

	if ((button & CONT_R) && !(lastbutton & CONT_R))
	{      
   		rmonPrintf("12\n");
    }

	if ((button & CONT_G) && !(lastbutton & CONT_G))
    {
		rmonPrintf("13\n");
	}

	if ((button & CONT_START) && !(lastbutton & CONT_START))
    {
   		rmonPrintf("14\n");
    }
  
  lastbutton = button;
}


