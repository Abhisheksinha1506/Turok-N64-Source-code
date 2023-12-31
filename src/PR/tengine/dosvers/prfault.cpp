/*
 * Copyright 1995, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied or
 * duplicated in any form, in whole or in part, without the prior written
 * permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
 * rights reserved under the Copyright Laws of the United States.
 *
 * $Revision: 1.1 $
 */

#include "stdafx.h"

#include "tengine.h"
#include "version.h"
#include "scaling.h"

#include "debug.h"

#define X_MARGIN 7
#define Y_MARGIN 3

#define LOW  1
#define HIGH 2
#define RESOLUTION HIGH
#define PATTERN_SIZE_X 8
#define PATTERN_SIZE_Y 16
#define SCREEN_SIZE_X 320*RESOLUTION
#define SCREEN_SIZE_Y 240*RESOLUTION
#define SCREEN_SIZE_VY 240*2*RESOLUTION
//#define NUM_OF_X (SCREEN_SIZE_X/PATTERN_SIZE_X - X_MARGIN)
#define NUM_OF_Y (SCREEN_SIZE_Y/PATTERN_SIZE_Y - Y_MARGIN)
#define NUM_OF_VY SCREEN_SIZE_VY/PATTERN_SIZE_Y
int NUM_OF_X;
//#define NUM_OF_X (SCREEN_SIZE_X/PATTERN_SIZE_X - X_MARGIN)

#define NUM_OF_CHAR 0x5f

#define N_R		160
#define N_G		160
#define N_B		160

#define HL_R	240
#define HL_G	240
#define HL_B	160

extern char _codeSegmentTextStart[];
extern char _codeSegmentTextEnd[];

extern void draw_char(int code);
extern void draw_uint( unsigned long num );
extern void draw_ushort( unsigned short num );
extern void draw_hex(int code);
extern void draw_decimal(int num);
extern void setcolor(int r,int g,int b);
extern void setbgcolor( int r, int g, int b);
extern void init_draw(void);
extern void clear_draw(void);
extern void draw_puts(const char *s);
extern void v_sync_double_buffer(OSMesgQueue *queue);

#define PRINTF	osSyncPrintf


u8 patterns[NUM_OF_CHAR][PATTERN_SIZE_Y] = {
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,},
{0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x10,0x38,0x10,0x00,},
{0x00,0x6c,0x6c,0x24,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,},
{0x00,0x24,0x24,0x24,0x26,0x3c,0x64,0x24,0x24,0x26,0x3c,0x64,0x24,0x24,0x24,0x00,},
{0x00,0x08,0x1c,0x2a,0x49,0x48,0x28,0x1c,0x0a,0x09,0x09,0x49,0x2a,0x1c,0x08,0x00,},
{0x00,0x22,0x54,0x54,0x54,0x28,0x08,0x08,0x10,0x10,0x14,0x2a,0x2a,0x2a,0x44,0x00,},
{0x00,0x38,0x44,0x44,0x44,0x44,0x28,0x30,0x20,0x52,0x52,0x4a,0x4a,0x44,0x3a,0x00,},
{0x00,0x60,0x60,0x20,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,},
{0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x20,0x20,0x20,0x20,0x10,0x10,0x08,0x08,0x04,},
{0x20,0x10,0x10,0x08,0x08,0x04,0x04,0x04,0x04,0x04,0x04,0x08,0x08,0x10,0x10,0x20,},
{0x00,0x00,0x08,0x08,0x49,0x49,0x2a,0x1c,0x08,0x1c,0x2a,0x49,0x49,0x08,0x08,0x00,},
{0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x7f,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x20,0x40,},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x00,},
{0x00,0x02,0x04,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x10,0x20,0x20,0x20,0x40,0x00,},
{0x00,0x3c,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,0x00,},
{0x00,0x08,0x18,0x28,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x1c,0x00,},
{0x00,0x18,0x24,0x42,0x42,0x42,0x02,0x04,0x08,0x10,0x20,0x20,0x40,0x40,0x7e,0x00,},
{0x00,0x18,0x24,0x42,0x42,0x02,0x04,0x18,0x04,0x02,0x42,0x42,0x42,0x24,0x18,0x00,},
{0x00,0x04,0x0c,0x0c,0x14,0x14,0x14,0x24,0x24,0x44,0x44,0x7e,0x04,0x04,0x04,0x00,},
{0x00,0x7e,0x40,0x40,0x40,0x58,0x64,0x42,0x02,0x02,0x02,0x42,0x42,0x24,0x18,0x00,},
{0x00,0x18,0x24,0x42,0x42,0x40,0x58,0x64,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,},
{0x00,0x7e,0x42,0x42,0x42,0x04,0x04,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,},
{0x00,0x18,0x24,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x42,0x24,0x18,0x00,},
{0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x26,0x1a,0x02,0x42,0x42,0x24,0x18,0x00,},
{0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x08,0x10,},
{0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x00,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,},
{0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x02,0x04,0x08,0x10,0x20,0x40,0x00,0x00,},
{0x00,0x18,0x24,0x42,0x42,0x02,0x04,0x08,0x10,0x10,0x00,0x00,0x10,0x38,0x10,0x00,},
{0x00,0x1c,0x22,0x41,0x49,0x55,0x55,0x55,0x55,0x55,0x55,0x4a,0x40,0x21,0x1e,0x00,},
{0x00,0x18,0x18,0x24,0x24,0x24,0x24,0x24,0x3c,0x42,0x42,0x42,0x42,0x42,0x00,0x00,},
{0x00,0x78,0x44,0x42,0x42,0x42,0x44,0x78,0x44,0x42,0x42,0x42,0x44,0x78,0x00,0x00,},
{0x00,0x18,0x24,0x42,0x42,0x40,0x40,0x40,0x40,0x42,0x42,0x42,0x24,0x18,0x00,0x00,},
{0x00,0x78,0x44,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0x78,0x00,0x00,},
{0x00,0x7e,0x40,0x40,0x40,0x40,0x40,0x7c,0x40,0x40,0x40,0x40,0x40,0x7e,0x00,0x00,},
{0x00,0x7e,0x40,0x40,0x40,0x40,0x40,0x7c,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,},
{0x00,0x18,0x24,0x42,0x40,0x40,0x40,0x4e,0x42,0x42,0x42,0x42,0x26,0x1a,0x00,0x00,},
{0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x7e,0x42,0x42,0x42,0x42,0x42,0x42,0x00,0x00,},
{0x00,0x1c,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x1c,0x00,0x00,},
{0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x42,0x42,0x24,0x18,0x00,0x00,},
{0x00,0x42,0x44,0x44,0x48,0x48,0x50,0x60,0x50,0x48,0x48,0x44,0x44,0x42,0x00,0x00,},
{0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7e,0x00,0x00,},
{0x00,0x41,0x63,0x63,0x55,0x55,0x49,0x49,0x41,0x41,0x41,0x41,0x41,0x41,0x00,0x00,},
{0x00,0x62,0x62,0x52,0x52,0x52,0x52,0x4a,0x4a,0x4a,0x4a,0x4a,0x46,0x46,0x00,0x00,},
{0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,},
{0x00,0x78,0x44,0x42,0x42,0x42,0x44,0x78,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,},
{0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x52,0x4a,0x24,0x1a,0x00,0x00,},
{0x00,0x78,0x44,0x42,0x42,0x42,0x44,0x78,0x48,0x48,0x44,0x44,0x42,0x42,0x00,0x00,},
{0x00,0x18,0x24,0x42,0x40,0x40,0x20,0x18,0x04,0x02,0x42,0x42,0x24,0x18,0x00,0x00,},
{0x00,0x7f,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,},
{0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,},
{0x00,0x41,0x41,0x41,0x41,0x22,0x22,0x22,0x22,0x14,0x14,0x14,0x08,0x08,0x00,0x00,},
{0x00,0x41,0x41,0x41,0x41,0x49,0x49,0x49,0x55,0x55,0x55,0x55,0x22,0x22,0x00,0x00,},
{0x00,0x42,0x42,0x42,0x24,0x24,0x18,0x18,0x24,0x24,0x24,0x42,0x42,0x42,0x00,0x00,},
{0x00,0x41,0x41,0x41,0x22,0x22,0x14,0x14,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,},
{0x00,0x7e,0x02,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x40,0x7e,0x00,0x00,},
{0x0e,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0e,},
{0x00,0x41,0x41,0x22,0x22,0x14,0x14,0x7f,0x08,0x08,0x7f,0x08,0x08,0x08,0x08,0x00,},
{0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x38,},
{0x18,0x24,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x00,0x00,},
{0x30,0x18,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x02,0x1e,0x22,0x42,0x42,0x46,0x3a,0x00,0x00,},
{0x00,0x40,0x40,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x42,0x42,0x64,0x58,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x18,0x24,0x42,0x40,0x40,0x40,0x42,0x24,0x18,0x00,0x00,},
{0x00,0x02,0x02,0x02,0x02,0x1a,0x26,0x42,0x42,0x42,0x42,0x42,0x26,0x1a,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x7e,0x40,0x40,0x22,0x1c,0x00,0x00,},
{0x00,0x08,0x14,0x10,0x10,0x7c,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x1a,0x26,0x42,0x42,0x42,0x42,0x26,0x1a,0x02,0x44,0x38,},
{0x00,0x40,0x40,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x00,0x00,},
{0x00,0x00,0x10,0x10,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,},
{0x00,0x00,0x04,0x04,0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x24,0x24,0x18,},
{0x00,0x40,0x40,0x40,0x40,0x42,0x44,0x48,0x50,0x60,0x50,0x48,0x44,0x42,0x00,0x00,},
{0x00,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x56,0x69,0x49,0x49,0x49,0x49,0x49,0x49,0x49,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x58,0x64,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x58,0x64,0x42,0x42,0x42,0x42,0x64,0x58,0x40,0x40,0x40,},
{0x00,0x00,0x00,0x00,0x00,0x1a,0x26,0x42,0x42,0x42,0x42,0x26,0x1a,0x02,0x02,0x02,},
{0x00,0x00,0x00,0x00,0x00,0x2c,0x32,0x22,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x42,0x20,0x18,0x04,0x42,0x42,0x3c,0x00,0x00,},
{0x00,0x00,0x00,0x10,0x10,0x7c,0x10,0x10,0x10,0x10,0x10,0x12,0x12,0x0c,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x26,0x1a,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x24,0x24,0x24,0x18,0x18,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x41,0x49,0x49,0x55,0x55,0x55,0x55,0x22,0x22,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x24,0x18,0x18,0x24,0x42,0x42,0x42,0x00,0x00,},
{0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x24,0x24,0x14,0x18,0x08,0x10,0x10,0x20,},
{0x00,0x00,0x00,0x00,0x00,0x7e,0x02,0x04,0x08,0x08,0x10,0x20,0x40,0x7e,0x00,0x00,},
{0x06,0x08,0x08,0x08,0x08,0x08,0x10,0x30,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x06,},
{0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,},
{0x30,0x08,0x08,0x08,0x08,0x08,0x04,0x06,0x04,0x08,0x08,0x08,0x08,0x08,0x08,0x30,},
{0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,},
};



u16      *bitmap_buf;

unsigned int x_pos=X_MARGIN;
unsigned int y_pos=Y_MARGIN;
u16 color;
u16 bg_color=0;


typedef struct {
	u32 mask;
	u32 value;
	char *string;
} regDesc_t;

static regDesc_t causeDesc[] = {
	{ CAUSE_BD,	CAUSE_BD,		"BD" },
	{ CAUSE_IP8,	CAUSE_IP8,		"IP8" },
	{ CAUSE_IP7,	CAUSE_IP7,		"IP7" },
	{ CAUSE_IP6,	CAUSE_IP6,		"IP6" },
	{ CAUSE_IP5,	CAUSE_IP5,		"IP5" },
	{ CAUSE_IP4,	CAUSE_IP4,		"IP4" },
	{ CAUSE_IP3,	CAUSE_IP3,		"IP3" },
	{ CAUSE_SW2,	CAUSE_SW2,		"IP2" },
	{ CAUSE_SW1,	CAUSE_SW1,		"IP1" },
	{ CAUSE_EXCMASK,EXC_INT,
			"Interrupt" },
	{ CAUSE_EXCMASK,EXC_MOD,
			"TLB modification exception" },
	{ CAUSE_EXCMASK,EXC_RMISS,
			"TLB exception on load or instruction fetch" },
	{ CAUSE_EXCMASK,EXC_WMISS,
			"TLB exception on store" },
	{ CAUSE_EXCMASK,EXC_RADE,
			"Address error on load or instruction fetch" },
	{ CAUSE_EXCMASK,EXC_WADE,
			"Address error on store" },
	{ CAUSE_EXCMASK,EXC_IBE,
			"Bus error exception on instruction fetch" },
	{ CAUSE_EXCMASK,EXC_DBE,
			"Bus error exception on data reference" },
	{ CAUSE_EXCMASK,EXC_SYSCALL,
			"System call exception" },
	{ CAUSE_EXCMASK,EXC_BREAK,
			"Breakpoint exception" },
	{ CAUSE_EXCMASK,EXC_II,
			"Reserved instruction exception" },
	{ CAUSE_EXCMASK,EXC_CPU,
			"Coprocessor unusable exception" },
	{ CAUSE_EXCMASK,EXC_OV,
			"Arithmetic overflow exception" },
	{ CAUSE_EXCMASK,EXC_TRAP,
			"Trap exception" },
	{ CAUSE_EXCMASK,EXC_VCEI,
			"Virtual coherency exception on intruction fetch" },
	{ CAUSE_EXCMASK,EXC_FPE,
			"Floating point exception (see fpcsr)" },
	{ CAUSE_EXCMASK,EXC_WATCH,
			"Watchpoint exception" },
	{ CAUSE_EXCMASK,EXC_VCED,
			"Virtual coherency exception on data reference" },
	{ 0,		0,		"" }
};


static regDesc_t srDesc[] = {
	{ SR_CU3,	SR_CU3,		"CU3" },
	{ SR_CU2,	SR_CU2,		"CU2" },
	{ SR_CU1,	SR_CU1,		"CU1" },
	{ SR_CU0,	SR_CU0,		"CU0" },
	{ SR_RP,	SR_RP,		"RP" },
	{ SR_FR,	SR_FR,		"FR" },
	{ SR_RE,	SR_RE,		"RE" },
	{ SR_BEV,	SR_BEV,		"BEV" },
	{ SR_TS,	SR_TS,		"TS" },
	{ SR_SR,	SR_SR,		"SR" },
	{ SR_CH,	SR_CH,		"CH" },
	{ SR_CE,	SR_CE,		"CE" },
	{ SR_DE,	SR_DE,		"DE" },
	{ SR_IBIT8,	SR_IBIT8,	"IM8" },
	{ SR_IBIT7,	SR_IBIT7,	"IM7" },
	{ SR_IBIT6,	SR_IBIT6,	"IM6" },
	{ SR_IBIT5,	SR_IBIT5,	"IM5" },
	{ SR_IBIT4,	SR_IBIT4,	"IM4" },
	{ SR_IBIT3,	SR_IBIT3,	"IM3" },
	{ SR_IBIT2,	SR_IBIT2,	"IM2" },
	{ SR_IBIT1,	SR_IBIT1,	"IM1" },
	{ SR_KX,	SR_KX,		"KX" },
	{ SR_SX,	SR_SX,		"SX" },
	{ SR_UX,	SR_UX,		"UX" },
	{ SR_KSU_MASK,	SR_KSU_USR,	"USR" },
	{ SR_KSU_MASK,	SR_KSU_SUP,	"SUP" },
	{ SR_KSU_MASK,	SR_KSU_KER,	"KER" },
	{ SR_ERL,	SR_ERL,		"ERL" },
	{ SR_EXL,	SR_EXL,		"EXL" },
	{ SR_IE,	SR_IE,		"IE" },
	{ 0,		0,		"" }
};


static regDesc_t fpcsrDesc[] = {
	{ FPCSR_FS,	FPCSR_FS,	"FS" },
	{ FPCSR_C,	FPCSR_C,	"C" },
	{ FPCSR_CE,	FPCSR_CE,	"Unimplemented operation" },
	{ FPCSR_CV,	FPCSR_CV,	"Invalid operation" },
	{ FPCSR_CZ,	FPCSR_CZ,	"Division by zero" },
	{ FPCSR_CO,	FPCSR_CO,	"Overflow" },
	{ FPCSR_CU,	FPCSR_CU,	"Underflow" },
	{ FPCSR_CI,	FPCSR_CI,	"Inexact operation" },
	{ FPCSR_EV,	FPCSR_EV,	"EV" },
	{ FPCSR_EZ,	FPCSR_EZ,	"EZ" },
	{ FPCSR_EO,	FPCSR_EO,	"EO" },
	{ FPCSR_EU,	FPCSR_EU,	"EU" },
	{ FPCSR_EI,	FPCSR_EI,	"EI" },
	{ FPCSR_FV,	FPCSR_FV,	"FV" },
	{ FPCSR_FZ,	FPCSR_FZ,	"FZ" },
	{ FPCSR_FO,	FPCSR_FO,	"FO" },
	{ FPCSR_FU,	FPCSR_FU,	"FU" },
	{ FPCSR_FI,	FPCSR_FI,	"FI" },
	{ FPCSR_RM_MASK,FPCSR_RM_RN,	"RN" },
	{ FPCSR_RM_MASK,FPCSR_RM_RZ,	"RZ" },
	{ FPCSR_RM_MASK,FPCSR_RM_RP,	"RP" },
	{ FPCSR_RM_MASK,FPCSR_RM_RM,	"RM" },
	{ 0,		0,		"" }
};

void setcolor( int r, int g, int b)
{
  color = GPACK_RGBA5551(r,g,b,1);
}

void setbgcolor( int r, int g, int b)
{
  bg_color = GPACK_RGBA5551(r,g,b,1);
}

void init_draw(void)
{
  bitmap_buf = cfb_16_a;
}

void clear_draw(void)
{
  int i;
  u16 *r;
  r = bitmap_buf;
  for (i = 0; i < SCREEN_SIZE_X * SCREEN_SIZE_Y; i ++)
    *r++  = bg_color;
}

void draw_char( int in_code )
{
  int i,j;
  int code;
  switch( in_code )
    {
    case '\n':
      x_pos = X_MARGIN;
      if( ++y_pos >= NUM_OF_Y )
	{
	  y_pos = Y_MARGIN;
	}
      break;
    case '\r':
      x_pos = X_MARGIN;
      break;
    case '\t':
                   x_pos += 8;
      if( x_pos  >= NUM_OF_X )
	{
	  x_pos = X_MARGIN;
	  if( ++y_pos >= NUM_OF_Y )
	    {
	      y_pos = Y_MARGIN;
	    }
	}
      break;
    case '\f':
      y_pos = Y_MARGIN;
      x_pos = X_MARGIN;
      break;
    default:
      if( 0 > ( code = in_code - 0x20 ))
	code = 0x1f;
      else if( 0x5f < code)
	code = 0x1f;

      for(i = 0 ; i < PATTERN_SIZE_Y ; i++)
	for(j = 0 ; j < PATTERN_SIZE_X ; j++)
	  bitmap_buf[ (y_pos * PATTERN_SIZE_Y + i) * SCREEN_SIZE_X +
		     (x_pos * PATTERN_SIZE_X + j) ]
		       = ( ((patterns[code][i]>>(7-j)) & 0x01)? color:bg_color);
      if( ++x_pos >= NUM_OF_X )
	{
	  x_pos = X_MARGIN;
	  if( ++y_pos >= NUM_OF_Y )
	    {
	      y_pos=Y_MARGIN;
	    }
	}
      break;
    }
}  



void draw_uint( unsigned long num )
{
  int i;
  for(i = 0 ; i < 4; i++)
    draw_hex( num >> (8 * (3 - i)) );
}

void draw_ushort( unsigned short num )
{
  int i;
  for(i = 0 ; i < 2; i++)
    draw_hex( num >> (8 * (1 - i)) );
}

#define DECIMAL_BUFFER_SIZE 16
void draw_decimal(int num)
{
	char buffer[DECIMAL_BUFFER_SIZE],
		  *pc;
	int  current;

	if (num < 0)
	{
		draw_char('-');
		current = -num;
	}
	else
	{
		current = num;
	}

	pc = &buffer[DECIMAL_BUFFER_SIZE - 1];
	*pc = 0;

	do
	{
		*(--pc) = current%10 + '0';
		current /= 10;
	} while (current);

	draw_puts(pc);
}
          
void draw_hex( int num )
{
  int lo,hi;
  lo = num & 0x0f;
  hi = (num >> 4) & 0x0f;
  if(hi >= 10)
    draw_char('a' + hi -10);
  else
    draw_char('0' + hi);
  if(lo >= 10)
    draw_char('a' + lo -10);
  else
    draw_char('0' + lo);
}

void draw_puts(const char *s)
{
  while( *s )
    draw_char( *s++ );
}


////////////////////////////////////////////////////////

void printRegisterScr(u32 regValue, char *regName, regDesc_t *regDesc)
{
	int first = 1;

	draw_puts(regName);
	draw_puts(": ");
	draw_uint(regValue);

	draw_puts("<");

	while (regDesc->mask != 0) {
		if ((regValue & regDesc->mask) == regDesc->value) {
			if (first)
				first = 0;
			else
				draw_puts(",");

			draw_puts(regDesc->string);
		}
		regDesc++;
	}
	draw_puts(">\n");
}


void printRegisterRow(char *s1, unsigned int v1,
							 char *s2, unsigned int v2,
							 char *s3, unsigned int v3)
{
	draw_puts(s1);
	draw_puts(": ");
	draw_uint(v1);

	draw_puts("   ");
	draw_puts(s2);
	draw_puts(": ");
	draw_uint(v2);

	draw_puts("   ");
	draw_puts(s3);
	draw_puts(": ");
	draw_uint(v3);

	draw_puts("\n");
}
void printRegisterRow2(char *s1, unsigned int v1,
							  char *s2, unsigned int v2)
{
	draw_puts(s1);
	draw_puts(": ");
	draw_uint(v1);

	draw_puts("   ");
	setcolor(HL_R, HL_G, HL_B);
	draw_puts(s2);
	draw_puts(": ");
	draw_uint(v2);
	setcolor(N_R, N_G, N_B);

	draw_puts("\n");
}
void printRegisterRow4(char *s1, unsigned int v1,
							  char *s2, unsigned int v2,
							  char *s3, unsigned int v3,
							  char *s4, unsigned int v4)
{
	draw_puts(s1);
	draw_puts(": ");
	draw_uint(v1);

	draw_puts("   ");
	draw_puts(s2);
	draw_puts(": ");
	draw_uint(v2);

	draw_puts("   ");
	draw_puts(s3);
	draw_puts(": ");
	draw_uint(v3);

	draw_puts("   ");
	draw_puts(s4);
	draw_puts(": ");
	draw_uint(v4);

	draw_puts("\n");
}

#define STACK_X_POS	55
#define STACK_Y_POS	Y_MARGIN
#define STACK_LINES	21

void printStack(void *pStack, int StackSize, __OSThreadContext *pTc)
{
	int	i;
	u32	*pStackEntry;
	u32	*pTopStack = (u32*) ((u32) pStack + StackSize);


	// make room for stack printout
	for (i=8; i<11; i++)
	{
		x_pos = STACK_X_POS - 1;
		y_pos = i;
		draw_puts("                   ");
	}

	x_pos = STACK_X_POS;
	y_pos = STACK_Y_POS;

	setcolor(HL_R, HL_G, HL_B);
	draw_puts(" call");
	setcolor(N_R, N_G, N_B);
	
	draw_puts("      raw");

	x_pos = STACK_X_POS;
	y_pos = STACK_Y_POS + 1;

	setcolor(HL_R, HL_G, HL_B);
	draw_puts(" stack");
	setcolor(N_R, N_G, N_B);
	
	draw_puts("     stack");

	// print call stack
	setcolor(HL_R, HL_G, HL_B);

	x_pos = STACK_X_POS;
	y_pos = STACK_Y_POS + 3;
	draw_uint(pTc->pc);

	i = 1;
	pStackEntry = (u32*) pTc->sp;
	while ((pStackEntry < pTopStack) && (i < STACK_LINES))
	{
		if ((*pStackEntry >= (u32) _codeSegmentTextStart) && (*pStackEntry < (u32) _codeSegmentTextEnd))
		{
			x_pos = STACK_X_POS;
			y_pos = STACK_Y_POS + 3 + i;

			draw_uint(*pStackEntry);
			i++;
		}

		pStackEntry++;
	}

	setcolor(N_R, N_G, N_B);

	// print raw stack
	i = 0;
	pStackEntry = (u32*) pTc->sp;
	while ((pStackEntry < pTopStack) && (i < STACK_LINES))
	{
		x_pos = STACK_X_POS + 10;
		y_pos = STACK_Y_POS + 3 + i;

		draw_uint(*pStackEntry);
		i++;

		pStackEntry++;
	}
}

void printFaultData(OSThread *t)
{
	CCacheEntry *pEntry;
	DWORD			workingSet, totalUsed,
					cacheEntries;
	int			total, largest;
	__OSThreadContext *tc = &t->context;

	if (GetApp()->m_Mode == MODE_GAME)
	{
		workingSet = 0;
		totalUsed = 0;
		cacheEntries = 0;
		pEntry = GetApp()->m_Scene.m_Cache.m_pCacheHead;
		while (pEntry)
		{
			cacheEntries++;
			totalUsed += pEntry->m_DataLength;
			if ((pEntry->m_LastAccessed + 1) >= frame_number)
				workingSet += pEntry->m_DataLength;

			pEntry = pEntry->m_pNext;
		}
		FreeMem(&total, &largest);
	}

	init_draw();

	//setcolor(HL_R, HL_G, HL_B);
	setcolor(N_R, N_G, N_B);
	setbgcolor(40, 40, 80);

	clear_draw();
	// do second time to avoid garbage on screen due to dirty RCP cache
	clear_draw();

	NUM_OF_X = (SCREEN_SIZE_X/PATTERN_SIZE_X - X_MARGIN) - 20;

	//setcolor(255, 120, 120);
	draw_puts("TUROK ENGINE");
	//setcolor(N_R, N_G, N_B);
	
	draw_puts(" --- ");

	setcolor(HL_R, HL_G, HL_B);

	draw_puts("build ");
	draw_decimal(VERSION_NUMBER);

	setcolor(N_R, N_G, N_B);

	draw_puts(" --- ");
	draw_puts(__DATE__);
	draw_puts("\n\n");

	if (trap_file)
	{
		setcolor(HL_R, HL_G, HL_B);

		draw_puts("ASSERTION FAILED!! in thread ");
		draw_decimal(t->id);
		draw_puts("\nFile: ");
		draw_puts(trap_file);
		draw_puts("  Line: ");
		draw_decimal(trap_line);
		draw_puts("\n");

		if (trap_expr)
		{
			draw_puts("(");
			draw_puts(trap_expr);
			draw_puts(") = 0");
		}
		
		draw_puts("\n");

		setcolor(N_R, N_G, N_B);
	}
	else
	{
		setcolor(HL_R, HL_G, HL_B);

		draw_puts("Fault in thread ");
		draw_decimal(t->id);
		draw_puts("\n");

		//draw_puts("\n\nepc: ");
		//draw_uint(tc->pc);
		//draw_puts("\n");

		printRegisterScr(tc->cause, "cause", causeDesc);

		setcolor(N_R, N_G, N_B);
	}

	NUM_OF_X = (SCREEN_SIZE_X/PATTERN_SIZE_X - X_MARGIN);
	y_pos = 8;

	printRegisterScr(tc->sr, "sr", srDesc);
	printRegisterScr(tc->fpcsr, "fpcsr", fpcsrDesc);
	
	draw_puts("badvaddr: ");
	draw_uint(tc->badvaddr);
	draw_puts("\n");

	printRegisterRow("at", tc->at, "v0", tc->v0, "v1", tc->v1);
	printRegisterRow("a0", tc->a0, "a1", tc->a1, "a2", tc->a2);
	printRegisterRow("a3", tc->a0, "t0", tc->t0, "t1", tc->t1);
	printRegisterRow("t2", tc->t2, "t3", tc->t3, "t4", tc->t4);
	printRegisterRow("t5", tc->t5, "t6", tc->t6, "t7", tc->t7);
	printRegisterRow("s0", tc->s0, "s1", tc->s1, "s2", tc->s2);
	printRegisterRow("s3", tc->s3, "s4", tc->s4, "s5", tc->s5);
	printRegisterRow("s6", tc->s6, "s7", tc->s7, "t8", tc->t8);
	printRegisterRow("t9", tc->t9, "gp", tc->gp, "sp", tc->sp);
	printRegisterRow2("s8", tc->s8, "ra", tc->ra);

///*
	if (GetApp()->m_Mode == MODE_GAME)
	{
		draw_puts("\ncart cache");

		draw_puts("\nworking set: ");
		draw_uint(workingSet);

		draw_puts("  cache size:   ");
		draw_uint(MEMORY_POOL_SIZE);

		draw_puts("\nin cache:    ");
		draw_uint(totalUsed);

		draw_puts("  largest free: ");
		draw_uint(largest);

		setcolor(HL_R, HL_G, HL_B);
		
		draw_puts("\n\nplayer: (");
		draw_decimal((int) (GetApp()->m_XPos/SCALING_FACTOR));

		draw_puts(", ");
		draw_decimal((int) (GetApp()->m_YPos/SCALING_FACTOR));

		draw_puts(", ");
		draw_decimal((int) (GetApp()->m_ZPos/SCALING_FACTOR));
		draw_puts(")    level: ");
		draw_decimal(GetApp()->m_Scene.m_nLevel);
		
		setcolor(N_R, N_G, N_B);
	}
//*/

	NUM_OF_X = (SCREEN_SIZE_X/PATTERN_SIZE_X - X_MARGIN);

	switch (t->id)
	{
#ifndef MAKE_CART
		case THREAD_RMON:
			printStack(rmon_stack, RMON_STACKSIZE, tc);
			break;
#endif

		case THREAD_IDLE:
			printStack(idle_thread_stack, IDLE_STACKSIZE, tc);
			break;

		case THREAD_AUDIO:
			printStack(audio_stack, AUDIO_STACKSIZE, tc);
			break;

		case THREAD_SCHED:
			printStack(schedule_stack, OS_SC_STACKSIZE, tc);
			break;

		case THREAD_MAIN:
			printStack(main_thread_stack, MAIN_STACKSIZE, tc);
			break;
	}

	osWritebackDCacheAll();
}

