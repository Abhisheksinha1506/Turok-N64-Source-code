/*====================================================================
 * print.c
 *
 * Copyright 1995, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/

/*
 * print - measure the performance of osSyncPrintf, with and without the osRdbInit call
 * 
 */

#include <ultra64.h>
#include "print.h"

OSThread	idleThread;
OSThread	mainThread;
OSThread 	rmonThread;
u64	        bootStack[STACKSIZE/8];
u64		idleThreadStack[STACKSIZE/8];
u64		mainThreadStack[STACKSIZE/8];
u64		rmonStack[RMON_STACKSIZE/8];

void		idleproc(void *arg);
void		mainproc(void *arg);

#define RDBSENDBUF_SIZE    0x8000
u8*   rdbSendBuf[RDBSENDBUF_SIZE];

boot(void *arg)
{
    int i;
    char *ap;
    u32 *argp;
    u32 argbuf[16];
    
    osInitialize();
    osCreateThread(&idleThread, 1, idleproc, arg,
		   (void *)(idleThreadStack+STACKSIZE/8),
		   (OSPri) OS_PRIORITY_IDLE);
    osStartThread(&idleThread);
}

void idleproc(void *arg) 
{

    osCreateThread(&rmonThread, 0, rmonMain, NULL,
                   (void *)(rmonStack+RMON_STACKSIZE/8),
                   (OSPri) OS_PRIORITY_RMON );
    osStartThread(&rmonThread);

    osCreateThread(&mainThread, 6, mainproc, arg,
		   mainThreadStack+STACKSIZE/8, (OSPri) 10);
    osStartThread(&mainThread);

    while (1);
}

void mainproc(void* arg)
{
    OSTime start_time1;
    OSTime start_time2;
    OSTime elapsed_time2;
    OSTime start_time3;
    OSTime elapsed_time3;
    int i;

    start_time2 = osGetTime();
    for (i = 0; i < TIMES; i++)
	osSyncPrintf("osSyncPrintf %d\n",i);
    elapsed_time2 = osGetTime() - start_time2;

    osInitRdb((char*)rdbSendBuf,RDBSENDBUF_SIZE);

    start_time1 = osGetTime();
    while(( osGetTime() - start_time1) < 0x8000000);

    start_time3 = osGetTime();
    for (i = 0; i < TIMES; i++)
	osSyncPrintf("osSyncPrintf %d\n",i);
    elapsed_time3 = osGetTime() - start_time3;

    start_time1 = osGetTime();
    while(( osGetTime() - start_time1) < 0x8000000);

    osSyncPrintf("osSyncPrintf without osInitRdb = %llu ns\n", OS_CYCLES_TO_NSEC(elapsed_time2 / TIMES));
    osSyncPrintf("osSyncPrintf with osInitRdb = %llu ns\n", OS_CYCLES_TO_NSEC(elapsed_time3 / TIMES));
    while(1);
}
