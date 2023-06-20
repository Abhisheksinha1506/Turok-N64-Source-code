/**************************************************************************
 *									  *
 *		 Copyright (C) 1994, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

/*
 * Size of Event State data structure
 */
#define	ES_SIZE		8

/*
 * Offset to fields in Event State data structure
 */
#define	ES_QUEUE	0
#define ES_MESSAGE	4

/*
 * Offset to fields in Message Queue data structure
 */
#define	MQ_MTQUEUE	0
#define	MQ_FULLQUEUE	4
#define	MQ_VALIDCOUNT	8
#define	MQ_FIRST	12
#define	MQ_MSGCOUNT	16
#define	MQ_MSG		20

#define SPB_DEBUGADDR   0x80001010
#define DB_BPOFF	0x04
#define BRK_KERNELBP	1

#define HW_INT0_OFFSET	    0*4
#define HW_INT1_OFFSET	    1*4
#define HW_INT2_OFFSET	    2*4
#define HW_INT3_OFFSET	    3*4
#define HW_INT4_OFFSET	    4*4
