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
 * File:	pif.h
 * Creator:	miya@sgi.com
 * Create Date:	Thr Jun 18 14:01:01 PDT 1996
 * Purpose:	PIf test 
 *
 */


#undef WITH_CONTROLLER
#undef RMON_DEBUG

#define CONTROLLERS 2

#define PIF_RAM_SIZE 64
#define DMA_ALIGNMENT 0xf

#define NONCONNECTERR 0x00008000
#define OTHERSERR     0x00004000

#define FORMAT 0x01
#define SEND_ERR 0x04
#define RECV_ERR 0x0c

#define CONT_NORMAL_SEND 0xff010401
#define CONT_NORMAL_RECV 0xff010401

#define CONT_RESET_SEND 0xff410401
#define CONT_RESET_RECV 0xff410401

#define CONT_NONCON_SEND 0xff010401
#define CONT_NONCON_RECV 0xff018401

#define CONT_SENDERR_SEND 0xff010401
#define CONT_SENDERR_RECV 0xff014401

#define CONT_RECVERR_SEND 0xff010401
#define CONT_RECVERR_RECV 0xff014401

typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct {
  uint comm;
  uint data;
} CH;

typedef struct {
  CH ch1;
  CH ch2;
  CH ch3;
  CH ch4;
  CH ch5;
  uchar dummy[23];
  uchar status;
} SIBuffer;
  

