#include <ultra64.h>

/* #include <rom.h> */
#include <ramrom.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <controller.h>
#include "gng.h"

OSContStatus     statusdata[MAXCONTROLLERS];
OSContPad        controllerdata[MAXCONTROLLERS];

/*
 *
 * Return the lowest number controller connected to system
 */
int initControllers()
{
    int             i;
    u8              pattern;

    if (osContInit(&siMessageQ, &pattern, &statusdata[0]) == -1) {
#ifndef _FINALROM
	PRINTF("initControllers(): osContInit() returns in error.\n");
#endif
	return -1;
    }

    for (i = 0; i < MAXCONTROLLERS; i++) {
        if ((pattern & (1<<i)) &&
                !(statusdata[i].errno & CONT_NO_RESPONSE_ERROR))
            return i;
    }
    return -1;
}


int
readControllerButton(int controllerSlot)
{
    u16 button;
    s32	retval;
	
    if (controllerSlot < 0) {
#ifndef _FINALROM
	PRINTF("no controller connection\n");
#endif
	return 0;
    }
    
    retval = osContStartReadData(&siMessageQ);

    if (retval != 0) {
#ifndef _FINALROM
	PRINTF("readControllerButton(): osContStartReadData returns 0x%x\n", retval);
#endif
	return(0);
    }

    (void)osRecvMesg(&siMessageQ, NULL, OS_MESG_BLOCK);
    osContGetReadData(controllerdata);
    button = controllerdata[controllerSlot].button;
    
    return button;
}
