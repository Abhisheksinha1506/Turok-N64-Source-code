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
 * File:	pif.c
 * Creator:	miya@sgi.com
 * Create Date:	Thr Jun 18 14:01:01 PDT 1996
 * Purpose:	PIf test 
 *
 *  XXXXX this only works when compiled with "-g", that is 
 *   because nothing is declared volatile.  Change to use the IO_READ
 *   and IO_WRITE macros
 */

#include	<ultra64.h>
#include	"pif.h"
#include        "gng.h"

extern int controllerSlot, initControllers(void), __osContinitialized;

static void writeSi(OSMesgQueue *queue, uint *ramBuf)
/***** send write64byte-command to PIf *****/
{
  osWritebackDCache( ramBuf, sizeof(SIBuffer));
  osRecvMesg(queue, NULL, OS_MESG_NOBLOCK);
  *(uint **)PHYS_TO_K1( SI_DRAM_ADDR_REG ) = ramBuf;
  *(uint *)PHYS_TO_K1(SI_PIF_ADDR_WR64B_REG) = PIF_RAM_START;
  osRecvMesg(queue, NULL, OS_MESG_BLOCK);
}

static void readSi(OSMesgQueue *queue, uint *ramBuf)
/***** send read64byte-command to PIf *****/
{
  osRecvMesg(queue, NULL, OS_MESG_NOBLOCK);
  *(uint **)PHYS_TO_K1(SI_DRAM_ADDR_REG) = ramBuf;
  *(uint *)PHYS_TO_K1(SI_PIF_ADDR_RD64B_REG) = PIF_RAM_START;
  osRecvMesg(queue, NULL, OS_MESG_BLOCK);
  osInvalDCache( ramBuf, sizeof(SIBuffer));
}

static void performPifMacro(OSMesgQueue *queue, SIBuffer *siBuffer, int numOfCount,uint comm, uint data,uchar status)
{
  int i;
  uint *temp;
  temp = (uint *)siBuffer;

  for(i = 0 ; i < numOfCount*2 ; i += 2) {
    *temp++ = comm;
    *temp++ = data;
  }
  for( ; i < 15 ; i++)
    *temp++ = 0;
  *temp = (uint)status;

  writeSi(queue,(uint *)siBuffer);
  readSi(queue,(uint *)siBuffer);
}

static int pifCompare(SIBuffer *siBuffer, int numOfCount,uint comm, uint data,uchar status)
{
  int error=0;
  uint *temp;
  int i;
  temp = (uint *)siBuffer;

  for(i = 0 ; i < numOfCount*2 ; i+=2) {
    if( *temp++ != comm )
      error++;
    if( *temp++ != data )
      error++;
  }
  for( ; i < 15 ; i++)
    if( *temp++ != 0 )
      error++;
  if( *temp != (uint)status )
    error++;
  return(error);
}

static int bootromUnreadableCheck(void)
{
  /*
    when boot-program runs,BootRom is readable(It is natural).
    after IPL3 is finish,it is unreadable untill ResetSwitch is pushed.
  */
  int i,error=0,count=0;
  uint *inst_ptr,*inst_end;

  inst_ptr = (uint *)PHYS_TO_K1( PIF_ROM_START );
  inst_end = (uint *)PHYS_TO_K1( PIF_ROM_END );
  while( inst_ptr < inst_end )
    if( *inst_ptr++ != 0 )
      error++;
  return( error );
}

static int siPifRamWrite(uint pattern,uint offset)
{
  if( offset <= 16 )
    pattern &= 0xfffffffc;

  *(((uint *)PHYS_TO_K1(PIF_RAM_START)) + offset) = pattern;
  while( *(u32 *)PHYS_TO_K1(SI_STATUS_REG) & SI_STATUS_RD_BUSY )
    ;
  return(0);
}

static int siPifRamVerify(uint pattern,uint offset)
{
  int error=0;
  if( offset <= 16 )
    pattern &= 0xfffffffc;

  if(pattern != *(((uint *)PHYS_TO_K1(PIF_RAM_START)) + offset))
    error = 1;
  while( *(u32 *)PHYS_TO_K1(SI_STATUS_REG) & SI_STATUS_RD_BUSY )
    ;
  return(error);
}

static int butterfly(void)
{
  int i,error=0;
  /* write */
  for(i = 0 ; i < 8 ; i++) {
    siPifRamWrite(0x55555555,i);
    siPifRamWrite(0xaaaaaaaa,15-i);
  }
  /* verify */
  for(i = 0 ; i < 8 ; i++) {
    error += siPifRamVerify(0x55555555,7-i);
    error += siPifRamVerify(0xaaaaaaaa,8+i);
  }
  /* write */
  for(i = 0 ; i < 8 ; i++) {
    siPifRamWrite(0x55555555,15-i);
    siPifRamWrite(0xaaaaaaaa,i);
  }
  /* verify */
  for(i = 0 ; i < 8 ; i++) {
    error += siPifRamVerify(0x55555555,8+i);
    error += siPifRamVerify(0xaaaaaaaa,7-i);
  }
  return(error);
}

static int marching(void)
{
  int i,error=0;
  for(i = 0; i < 16 ; i++)
    siPifRamWrite(0,i);
  for(i = 0; i < 16 ; i++) {
    error += siPifRamVerify(0,i);
    siPifRamWrite(0xffffffff,i);
    error += siPifRamVerify(0xffffffff,i);
  }
  for(i = 15 ; i > 0 ; i--) {
    error += siPifRamVerify(0xffffffff,i);
    siPifRamWrite(0,i);
    error += siPifRamVerify(0,i);
  }
  return(error);
}
  
static int walking(void)
{
  int i,j,error=0;
  uint walking_1s=0x01;
  
  for(i = 0 ; i < 16 ; i++) {
    for(j = 0 ; j < sizeof(uint); j++) {
      siPifRamWrite(walking_1s, i);
      error += siPifRamVerify(walking_1s,i);
      walking_1s <<= 1;
    }
  }
  walking_1s = 0xfffffffe;
  for(i = 0 ; i < 16 ; i++) {
    for(j = 0 ; j < sizeof(uint); j++) {
      siPifRamWrite(walking_1s, i);
      error += siPifRamVerify(walking_1s,i);
      walking_1s <<= 1;
    }
  }
  return(error);
}

static int kh(void)
{
  int i,error=0;

  /* set Patition 1,2 to 0x00000000 */
  for(i = 1 ; i < 16 ; i += 2) {
    siPifRamWrite(0, i);
    i++;
    if(i < 16)
      siPifRamWrite(0, i);
  }

  /* set Patition 0 to 0xffffffff */
  for(i = 0 ; i < 16 ; i += 3)
    siPifRamWrite(0xffffffff, i);

  /* verify Patition 1 is still 0*/
  for(i = 1 ; i < 16 ; i += 3)
    error += siPifRamVerify(0,i);
  
  /* set Patition 1 is 0xffffffff */
  for(i = 1 ; i < 16 ; i += 3)
    siPifRamWrite(0xffffffff, i);
  
  /* verify Patition 2 is still 0*/
  for(i = 2 ; i < 16 ; i += 3)
    error += siPifRamVerify(0,i);

  /* verify Patition 0 is still 0*/
  for(i = 0 ; i < 16 ; i += 3)
    error += siPifRamVerify(0xffffffff,i);

  /* verify Patition 1 is still 0*/
  for(i = 1 ; i < 16 ; i += 3)
    error += siPifRamVerify(0xffffffff,i);
  
  /* Set Patition 0 to 0 */
  for(i = 0 ; i < 16 ; i += 3)
    siPifRamWrite(0, i);

  /* verify Patition 0 is 0*/
  for(i = 0 ; i < 16 ; i += 3)
    error += siPifRamVerify(0,i);

  /* set Patition 2 to 0xffffffff */
  for(i = 2 ; i < 16 ; i += 3)
    siPifRamWrite(0xffffffff, i);

  /* verify Patition 2 is 0xffffffff */
  for(i = 2 ; i < 16 ; i += 3)
    error += siPifRamVerify(0xffffffff,i);

  return(error);
}


static int siPifRamCompare64(OSMesgQueue *queue, SIBuffer *siBuffer, uint pattern)
{
  int i,error=0;
  uint *temp1,*temp2;
  temp1 = temp2 = (uint *)siBuffer;
  for(i = 0 ; i < 16 ; i++) {
    if(i < 15)
      *temp1++ = pattern;
    else
      *temp1++ = (pattern & 0xfffffffc);
  }
  writeSi(queue,temp2);
  readSi(queue,temp2);
  for(i = 0 ; i < 16 ; i++) {
    if(i < 15) {
      if( *temp2++ != pattern )
	error++;
    }
    else {
      if( *temp2++ != (pattern & 0xfffffffc) )
	error++;
    }
  }
  return(error);
}

#define NUM_MESSAGE 1
#define CONTROLLER_CONNECT_TIMEOUT -1
#define CONTROLLER_JOYSTICK_TIMEOUT -2
#define BITPATTERNS 5

static uchar dummy_buffer[PIF_RAM_SIZE+DMA_ALIGNMENT];

static uint bitpattern[BITPATTERNS]= { 0x00000000, 0xffffffff, 0x55555555,
					 0xaaaaaaaa,0xdeadbeef}; 

int pifCheck(void)
{
  int i,result,timeout_count=0,error=0;
  SIBuffer *siBuf;

#ifdef RMON_DEBUG
  OSTime       time_p,time_n,time;
  unsigned int d_time;
#endif

  siBuf = (SIBuffer *)( ((unsigned int)dummy_buffer & ~(0x07)) + 0x10 );

  /* Initialize PIf Ram */
  performPifMacro(&siMessageQ, siBuf,CONTROLLERS,0,0,FORMAT);
  error += (result = pifCompare(siBuf,CONTROLLERS,0,0,0));

#ifdef RMON_DEBUG
  if(result)
    PRINTF("init failure\n");
  else
    PRINTF("init success\n");
#endif


#ifdef RMON_DEBUG
  time_p = osGetTime();
#endif

  /* 10 sec */

  /* SI check */
  for(i = 0 ; i < BITPATTERNS ; i++) {
    error += (result = siPifRamCompare64(&siMessageQ, siBuf,bitpattern[i]));
  }
  
  error += (result = butterfly());

  error += (result = marching());

  error += (result = walking());

  error += (result = kh());

#ifdef RMON_DEBUG
  if(result)
    PRINTF("kh failure = %d\n",result);
  else
    PRINTF("kh success = %d\n",result);
#endif

#ifdef RMON_DEBUG
  time_n = osGetTime();
  if(time_p < time_n)
    time = time_n - time_p;
  else
    time = time_n + ~time_p + 1;
  d_time = (unsigned int)(time / 45);
  PRINTF("si check time = %lu micro sec\n",d_time);
  PRINTF("si check time = %lu milli sec\n",d_time/1000);

  if(result)
    PRINTF("si check failure = %d\n",result);
  else
    PRINTF("si check success = %d\n",result);
#endif


#ifdef WITH_CONTROLLER
  /* Now controllers are not connected */
  performPifMacro(&siMessageQ, siBuf, CONTROLLERS, CONT_NONCON_SEND, 0xffffffff, FORMAT);
  error += (result = pifCompare(siBuf,CONTROLLERS, CONT_NONCON_RECV, 0xffffffff, 0));

#ifdef RMON_DEBUG
  if(result)
    PRINTF("Nonconn failure\n");
  else
    PRINTF("Nonconn success\n");
#endif

  gng_report("connect controllers",0,1,120);

  /* Make controllers connect */
  while(1) {
    performPifMacro(&siMessageQ, siBuf, CONTROLLERS, CONT_NONCON_SEND, 0xffffffff, FORMAT);
    if( (siBuf->ch1.comm | siBuf->ch2.comm) & NONCONNECTERR ) {
      if( timeout_count++ > 0x0fffffff )
	return(CONTROLLER_CONNECT_TIMEOUT);
    }
    else
      break;
  }

  performPifMacro(&siMessageQ, siBuf, CONTROLLERS, CONT_NORMAL_SEND, 0xffffffff, FORMAT);
  error += (result = pifCompare(siBuf,CONTROLLERS, CONT_NORMAL_RECV, 0x00000000, 0));

#ifdef RMON_DEBUG
  if(result)
    PRINTF("Normal failure\n");
  else
    PRINTF("Normal success\n");
#endif

  gng_report("Slant Joystick",0,1,120);

  /* Keep joy-sticks slanting in any direction */
  while(1) {
    performPifMacro(&siMessageQ, siBuf, CONTROLLERS, CONT_NORMAL_SEND, 0xffffffff, FORMAT);
    if( (siBuf->ch1.data == 0) || (siBuf->ch2.data == 0) ) {
      if( timeout_count++ > 0x7fffffff )
	return(CONTROLLER_JOYSTICK_TIMEOUT);
    }
    else
      break;
  }

  performPifMacro(&siMessageQ, siBuf, CONTROLLERS, CONT_RESET_SEND, 0xffffffff, FORMAT);

  gng_report("Release Joystick",0,1,120);

  /* release joy-sticks */
  while(1) {
    performPifMacro(&siMessageQ, siBuf, CONTROLLERS, CONT_NORMAL_SEND, 0xffffffff, FORMAT);
    if( (siBuf->ch1.data == 0) || (siBuf->ch2.data == 0) ) {
      if( timeout_count++ > 0x7fffffff )
	return(CONTROLLER_JOYSTICK_TIMEOUT);
    }
    else
      break;
  }
  performPifMacro(&siMessageQ, siBuf, CONTROLLERS, CONT_RESET_SEND, 0xffffffff, FORMAT);
  performPifMacro(&siMessageQ, siBuf, CONTROLLERS, CONT_SENDERR_SEND, 0xffffffff, SEND_ERR | FORMAT);
  error += (result = pifCompare(siBuf, CONTROLLERS, CONT_SENDERR_RECV, 0xffffffff, SEND_ERR));

#ifdef RMON_DEBUG
  if(result)
    PRINTF("CollisionErr failure\n");
  else
    PRINTF("CollisionErr success\n");
#endif

  performPifMacro(&siMessageQ, siBuf, CONTROLLERS, CONT_RECVERR_SEND, 0xffffffff, RECV_ERR | FORMAT);
  error += (result = pifCompare(siBuf, CONTROLLERS, CONT_RECVERR_RECV, 0xffffffff, RECV_ERR));

#ifdef RMON_DEBUG
  if(result)
    PRINTF("OverrunErr failure\n");
  else
    PRINTF("OverrunErr success\n");
#endif

#endif	/* WITHOUT_CONTROLLER */

  error += (result = bootromUnreadableCheck());

#ifdef RMON_DEBUG
  if(result)
    PRINTF("boot rom failure\n");
  else
    PRINTF("boot rom success\n");
#endif

  performPifMacro(&siMessageQ, siBuf,CONTROLLERS,0,0,FORMAT);
    
  if (!zaruexists) {
    __osContinitialized = 0;
    controllerSlot = initControllers();
  }

  return( error );
}
