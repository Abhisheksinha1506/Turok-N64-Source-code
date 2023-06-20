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

#include <ultra64.h>
#include "gng.h"

static OSMesgQueue	PIdmaMessageQ;
static OSMesg		PIdmaMessageBuf;
static OSIoMesg		PIdmaIOMessageBuf;

#define	PI_PASS	1
#define	PI_FAIL	0

void PI_TestInit(void)
{
    osCreateMesgQueue(&PIdmaMessageQ, &PIdmaMessageBuf, 1);
}

/*
 * In general, the PIF channel is slow so limit number of tests that calls
 * PI_CheckIO
 */

int PI_CheckIO(u32 rawROMAddr, int nbytes, int rw, u32 PGS)
{
    u32	expaddr;
    u32 pgaddr;
    u32	addr;
    u8	len;

    if (!zaruexists)
	return PI_PASS;

    if (nbytes == sizeof (u32)) {
	expaddr = rawROMAddr;
    }
    else {
	pgaddr = rawROMAddr & ~((PGS * 2) - 1);
	expaddr = (rawROMAddr > pgaddr) ? rawROMAddr : pgaddr;
    }

    /* get address bits from ZARU */

    ZaruSetExpCommand(ZARU_EXP_CMD_UPPER_AD16);
    ZaruRestartBoard2();

    addr = ZaruGetExpHigh() & 0xff;
    addr <<=8;
    addr |= ZaruGetExpLow() & 0xff;
    addr <<=8;

    ZaruSetExpCommand(ZARU_EXP_CMD_LOWER_AD16);
    ZaruRestartBoard2();

    addr |= ZaruGetExpHigh() & 0xff;
    addr <<=8;
    addr |= ZaruGetExpLow() & 0xff;

    /* get transfer length from ZARU */

/*
 * ZaruGetXferLen() was totally bogus, so I removed it; the proper way to read the
 * transfer lengths from the Zaru is found in uji/uji_pif.c in the function ssnRWchk().
 */
#ifdef SEE_SSNRW_CHK_FOR_XFERLEN_TEST
    if (rw == OS_READ)
	len = ((ZaruGetXferLen() >> ZARU_READ_BYTES_SHIFT) & ZARU_RW_BYTES_MASK) * 2;
    else
	len = ((ZaruGetXferLen() >> ZARU_WRITE_BYTES_SHIFT) & ZARU_RW_BYTES_MASK) * 2;
#else
    len = 0;
#endif


#ifdef DEBUG
    osRomBase = (void *)0x10000000;
    PRINTF("e: %08x r: %08x el:%d rl:%d\n", expaddr, addr, nbytes, len);
    osRomBase = (void *)0x0;
#endif

    if (addr != expaddr)
	return PI_FAIL;

    if ((nbytes <= 28) && nbytes != len)
	return PI_FAIL;

    return PI_PASS;
}

#define	PI_DEF_DOMAIN	0x10000000
#define	PI_DEF_TIMING	0x80371240

#define ROMBASE	(u32)_PI_num_seqSegmentRomStart
#define	RAMPAD	0x10			/* 16 byte pad around dram block */
					/* so we can loaded with garbage */						/* to make sure didn't DMA extra */
#define RAMBASE		(u32)(0x803c0000 - 2*RAMPAD)
#define EXTRAMBASE_4M	(u32)(0x804c0000 - 2*RAMPAD)
#define EXTRAMBASE_5M	(u32)(0x805c0000 - 2*RAMPAD)
#define EXTRAMBASE_6M	(u32)(0x806c0000 - 2*RAMPAD)
#define EXTRAMBASE_7M	(u32)(0x807c0000 - 2*RAMPAD)

extern char _PI_num_seqSegmentRomStart[], _PI_num_seqSegmentRomEnd[];

#define	DO_DMA(rom, dram, nbytes, rw)	\
	osPiStartDma(&PIdmaIOMessageBuf, OS_MESG_PRI_NORMAL, rw,	\
		 rom, dram, nbytes, &PIdmaMessageQ);			\
	(void)osRecvMesg(&PIdmaMessageQ, NULL, OS_MESG_BLOCK)		\
/*
 * DMA ROM data into dram
 *	- check for PI interrupt handling
 *	- performs CRC to check for data correctness
 *	- timestamp to check performance w/res PI register timing
 *
 *	- returns pass/fail
 */

int PI_DMARead(u32 romaddr, u32 *dramaddr, u32 nbytes, OSTime *dmaTime)
{
    u32		seq;
    u16		*sp = (u16 *)dramaddr;

#ifdef DEBUG
    if (romaddr & 0x1)
	PRINTF("PI_DMARead: romaddr %08x not 2 byte aligned\n", romaddr);
    if ((u32)dramaddr & 0xf)
	PRINTF("PI_DMARead: dramaddr %08x not 16 byte aligned\n", dramaddr);
    if (nbytes % 16)
	PRINTF("PI_DMARead: nbytes (%d) must be multiples of 16\n", nbytes);
#endif

    osWritebackDCacheAll();
    osInvalDCache((u32 *)((u32)dramaddr - (u32)RAMPAD), nbytes + 2*RAMPAD);
    osSetTime((OSTime)0);
    DO_DMA(romaddr, dramaddr, nbytes, OS_READ);
    *dmaTime = osGetTime();

    /* check the data pattern sequence */
    seq = (romaddr - (u32)_PI_num_seqSegmentRomStart) / sizeof(u16);
    while (nbytes -= 2) {
	if (*sp++ != (u16)(seq++ & 0xffff)) {
#ifndef DEBUG
	    PRINTF("dramaddr: %04x seq %04x\n", *(sp-1), seq-1);
#endif
	    return PI_FAIL;
	}
    }
    return PI_PASS;
}

float PI_Speed(u32 size, u32 usec)
{
    return (size/(1024.0*1024.0)) / (usec/1000000.0);
}

void PI_ExtractSpeedParam(u32 tLtPtRPGS, int *tL, int *tP, int *tR, int *PGS)
{

    *tL = tLtPtRPGS & 0xff;
    *tP = (tLtPtRPGS >> 8) & 0xff;
    *PGS = (tLtPtRPGS >> 16) & 0xf;
    *tR = ((tLtPtRPGS >> 20) & 0x3);
}

void PI_UseDomain(u32 domainBase, u32 tLtPtRPGS)
{
    int	tL, tP, tR, PGS;
    int	domain=1;

    PI_ExtractSpeedParam(tLtPtRPGS, &tL, &tP, &tR, &PGS);

    /* check which domain is the domainBase address in */

    if (domainBase >= 0x05000000 && domainBase <= 0x05ffffff)
	domain = 2;
    if (domainBase >= 0x06000000 && domainBase <= 0x07ffffff)
	domain = 1;
    if (domainBase >= 0x08000000 && domainBase <= 0x0fffffff)
	domain = 2;
    if (domainBase >= 0x10000000 && domainBase <= 0x1fbfffff)
	domain = 1;
    if (domainBase >= 0x1fd00000 && domainBase <= 0x7fffffff)
	domain = 1;

    /* setup the domain speed parameters */

    if (domain == 1) {
	IO_WRITE(PI_BSD_DOM1_LAT_REG, tL);
	IO_WRITE(PI_BSD_DOM1_PWD_REG, tP);
	IO_WRITE(PI_BSD_DOM1_PGS_REG, PGS);
	IO_WRITE(PI_BSD_DOM1_RLS_REG, tR);
    }

    if (domain == 2) {
	IO_WRITE(PI_BSD_DOM2_LAT_REG, tL);
	IO_WRITE(PI_BSD_DOM2_PWD_REG, tP);
	IO_WRITE(PI_BSD_DOM2_PGS_REG, PGS);
	IO_WRITE(PI_BSD_DOM2_RLS_REG, tR);
    }

    /* setup the domain base in OS */

    osRomBase = (void *)domainBase;
}

#define	PI_tALCS	7
#define	PI_tALED	7
#define	PI_tWSD		1
#define	PI_DMASIZE	128
#define	PI_DMASETUP	48

static int PI_PGSTable[16] = {
    4,		8,		16,		32,
    64	,	128,		256,		512,
    1024,	2048,		4096,		8192,
    16384,	32768,		65536,		131072
};

float PI_ComputeSpeed(u32 tLtPtRPGS)
{
    int	tL, tP, tR, PGS;
    int	cycles;

    /* compute tL, tP, tR in real cycles, and PGS in bytes */

    PI_ExtractSpeedParam(tLtPtRPGS, &tL, &tP, &tR, &PGS);
    PGS = PI_PGSTable[PGS];
    tR++;

    cycles = PI_tALCS + PI_tALED + tR /*PI_tWRC*/ + PI_tWSD +
	tL + PGS/2*(tP+tR) /*data clocks*/ +
	PGS/PI_DMASIZE*PI_DMASETUP /*dma pkt setup*/ +
	PGS/4 /*rdram packet dma clocks */;

    return (float)PGS/cycles*62.5*1000000.0/1024.0/1024.0 ;
}

typedef struct {
	u32	romaddr;
	u32	*dramaddr;
	u32	nbytes;
} TYPE_PIDMA;

typedef struct {
	u32	romaddr;
	u32	data;
} TYPE_PIO;

#define	ABS(x)	((x > 0) ? (x) : -(x))

int PI_DataTests(u32 SpeedParam)
{
    static TYPE_PIDMA	DMAReadTests[] = {
	{ ROMBASE + 0x00000000, (u32 *)(EXTRAMBASE_4M + 0x0000), 256*1024 },
	{ ROMBASE + 0x00000000, (u32 *)(EXTRAMBASE_5M + 0x0000), 256*1024 },
	{ ROMBASE + 0x00000000, (u32 *)(EXTRAMBASE_6M + 0x0000), 256*1024 },
	{ ROMBASE + 0x00000000, (u32 *)(EXTRAMBASE_7M + 0x0000), 256*1024 },
	{ ROMBASE + 0x00000000, (u32 *)(RAMBASE + 0x0000), 256*1024 },
	{ ROMBASE + 0x00000010, (u32 *)(RAMBASE + 0x0000), 128*1024 },
	{ ROMBASE + 0x00000100, (u32 *)(RAMBASE + 0x0000), 16*1024 },
	{ ROMBASE + 0x00001000, (u32 *)(RAMBASE + 0x9000), 1*1024 },
	{ ROMBASE + 0x00002000, (u32 *)(RAMBASE + 0x0900), 1*1024 },
	{ ROMBASE + 0x00010000, (u32 *)(RAMBASE + 0x0090), 1*1024 },
	{ ROMBASE + 0x00020000, (u32 *)(RAMBASE + 0x0000), 1*1024 },
	{ ROMBASE + 0x00020002, (u32 *)(RAMBASE + 0x0000), 16 },
	{0, 0, 0},
    };

    #define PIOBASE	(u32)_PI_num_seqSegmentRomStart

    static TYPE_PIO		PIORTests[] = {
	{ PIOBASE + 0x00000000, 0x00000001 },
	{ PIOBASE + 0x00000004, 0x00020003 },
	{ PIOBASE + 0x00000008, 0x00040005 },
	{ PIOBASE + 0x0000000c, 0x00060007 },
	{ PIOBASE + 0x00000010, 0x00080009 },
	{ PIOBASE + 0x00000020, 0x00100011 },
	{ PIOBASE + 0x00000040, 0x00200021 },
	{ PIOBASE + 0x00000080, 0x00400041 },
	{ PIOBASE + 0x00000100, 0x00800081 },
	{ PIOBASE + 0x00000200, 0x01000101 },
	{ PIOBASE + 0x00000400, 0x02000201 },
	{ PIOBASE + 0x00000800, 0x04000401 },
	{ PIOBASE + 0x00001000, 0x08000801 },
	{ PIOBASE + 0x00002000, 0x10001001 },
	{ PIOBASE + 0x00004000, 0x20002001 },
	{ PIOBASE + 0x00008000, 0x40004001 },
	{ PIOBASE + 0x00010000, 0x80008001 },
	{ PIOBASE + 0x00020000, 0x00000001 },
	{0, 0},
    };

    TYPE_PIDMA		*dmaTest;
    TYPE_PIO		*pioTest = PIORTests;
    OSTime		time;
    u32			usec;
    float		ComputedSpeed;
    float		diff;

    ComputedSpeed = PI_ComputeSpeed(SpeedParam);

    /*
     * DMA read test
     */

    for (dmaTest = DMAReadTests; dmaTest->nbytes; dmaTest++) {
	int	i;
	u32	*u32p;
	u32	lastaddr;

	/* check memory size to skip tests that needs more memory */

	if (((u32)dmaTest->dramaddr & 0x007fffff) > osMemSize) {
#ifdef DEBUG
PRINTF("skip test %08x %08x\n", dmaTest->dramaddr, osMemSize);
#endif
	    continue;
	}

	/* clear dram buffer region */

	u32p = (u32 *)((u32)dmaTest->dramaddr - (u32)RAMPAD);
	for (i=0; i<(dmaTest->nbytes + 2*RAMPAD)/sizeof(u32); i++)
	    *u32p++ = 0xdeadbeef;

	/* run read test */

	if (PI_DMARead(dmaTest->romaddr, dmaTest->dramaddr,
	 dmaTest->nbytes, &time) == PI_FAIL)
	    return PI_FAIL;

	/* check pading */

	u32p = (u32 *)((u32)dmaTest->dramaddr - (u32)RAMPAD);
	for (i=0; i<RAMPAD/sizeof(u32); i++)
	    if (*u32p++ != 0xdeadbeef)
		return PI_FAIL;

	u32p = (u32 *)((u32)dmaTest->dramaddr + (u32)dmaTest->nbytes);
	for (i=0; i<RAMPAD/sizeof(u32); i++)
	    if (*u32p++ != 0xdeadbeef)
		return PI_FAIL;

	/* check timing if size >= .5 MB */

	if (dmaTest->nbytes >= 1024*256) {
	    usec = OS_CYCLES_TO_USEC(time);

#ifdef DEBUG
	    PRINTF("C: %f R: %f\n", ComputedSpeed, PI_Speed(dmaTest->nbytes, usec));
#endif
	    diff = (ComputedSpeed - PI_Speed(dmaTest->nbytes, usec)) / ComputedSpeed;
	    if ( ABS(diff) > 0.3 )
		return PI_FAIL;
	}
    }

    while (pioTest->romaddr) {
	u32	*int4meg = (u32 *)RAMBASE;
	u32	*ext5meg = (u32 *)EXTRAMBASE_5M;
	u32	*ext7meg = (u32 *)EXTRAMBASE_7M;

	/* 4 MB config test */

	if (osMemSize >= 0x400000) {

#ifdef DEBUG
static int i=0;
if (i==0) PRINTF("doing 4MB test\n");
i++;
#endif
	    *int4meg = 0xdeadbeef;
	    osPiReadIo(pioTest->romaddr, int4meg);
	    if (*int4meg != pioTest->data)
		return PI_FAIL;
	}

	/* 6 MB config test */

	if (osMemSize >= 0x600000) {
#ifdef DEBUG
static int i=0;
if (i==0) PRINTF("doing 6MB test\n");
i++;
#endif
	    *ext5meg = 0xdeadbeef;
	    osPiReadIo(pioTest->romaddr, ext5meg);
	    if (*ext5meg != pioTest->data)
		return PI_FAIL;
	}

	/* 8 MB config test */

	if (osMemSize >= 0x800000) {
#ifdef DEBUG
static int i=0;
if (i==0) PRINTF("doing 8MB test\n");
i++;
#endif
	    *ext7meg = 0xdeadbeef;
	    osPiReadIo(pioTest->romaddr, ext7meg);
	    if (*ext7meg != pioTest->data)
		return PI_FAIL;
	}

	pioTest++;
    }

    return PI_PASS;
}

int PI_TimingAddrTests(void)
{
    static TYPE_PIDMA	IOTests[] = {

#define NUM_TIMING_ZARUCHECK	1
#define NUM_IOTEST_ZARUCHECK	4
#define NUM_DMATEST_ZARUCHECK	1

	/*
	 * First 4 tests are used with ZARU for checking AD16 address and
	 * length of writes. Here are the limitations
	 *
	 * 1. controller port is slow, can't use it a lot
	 * 2. PIO length = 4 bytes, DMA length = N * 16 bytes for cache line
	 *	alignment. So we only try these 2 lengths.
	 */

	{ 0x05555554, (u32 *)RAMBASE, 16 }, /* alternating 1s & 0s */
	{ 0x05aaaaa8, (u32 *)RAMBASE, 16 }, /* inverted */
	{ 0x05249248, (u32 *)RAMBASE, 16 }, /* 2 0s between each 1 */
	{ 0x05db6db4, (u32 *)RAMBASE, 16 }, /* inverted */

        /* walking 1 address test */

	{ 0x05000000, (u32 *)RAMBASE, 16 },
	{ 0x05000004, (u32 *)RAMBASE, 16 },
	{ 0x05000008, (u32 *)RAMBASE, 16 },
	{ 0x05000010, (u32 *)RAMBASE, 16 },
	{ 0x05000020, (u32 *)RAMBASE, 16 },
	{ 0x05000040, (u32 *)RAMBASE, 16 },
	{ 0x05000080, (u32 *)RAMBASE, 16 },
	{ 0x05000100, (u32 *)RAMBASE, 16 },
	{ 0x05000200, (u32 *)RAMBASE, 16 },
	{ 0x05000400, (u32 *)RAMBASE, 16 },
	{ 0x05000800, (u32 *)RAMBASE, 16 },
	{ 0x05001000, (u32 *)RAMBASE, 16 },
	{ 0x05002000, (u32 *)RAMBASE, 16 },
	{ 0x05004000, (u32 *)RAMBASE, 16 },
	{ 0x05008000, (u32 *)RAMBASE, 16 },
	{ 0x05010000, (u32 *)RAMBASE, 16 },
	{ 0x05020000, (u32 *)RAMBASE, 16 },
	{ 0x05040000, (u32 *)RAMBASE, 16 },
	{ 0x05080000, (u32 *)RAMBASE, 16 },
	{ 0x05100000, (u32 *)RAMBASE, 16 },
	{ 0x05200000, (u32 *)RAMBASE, 16 },
	{ 0x05400000, (u32 *)RAMBASE, 16 },
	{ 0x05800000, (u32 *)RAMBASE, 16 },
	{ 0x06000000, (u32 *)RAMBASE, 16 },
#ifdef _GONOGOROM
	{ 0x08000000, (u32 *)RAMBASE, 16 },
	{ 0x10000000, (u32 *)RAMBASE, 16 },
	{ 0x60000000, (u32 *)RAMBASE, 16 },
	{ 0x40000000, (u32 *)RAMBASE, 16 },
#endif

	/* walking 0 address test, LSB must be 0, must be 32b aligned  */

	{ 0x05fffffc, (u32 *)RAMBASE, 16 },
	{ 0x05fffff8, (u32 *)RAMBASE, 16 },
	{ 0x05ffffec, (u32 *)RAMBASE, 16 },
	{ 0x05ffffdc, (u32 *)RAMBASE, 16 },
	{ 0x05ffffbc, (u32 *)RAMBASE, 16 },
	{ 0x05ffff7c, (u32 *)RAMBASE, 16 },
	{ 0x05fffefc, (u32 *)RAMBASE, 16 },
	{ 0x05fffdfc, (u32 *)RAMBASE, 16 },
	{ 0x05fffbfc, (u32 *)RAMBASE, 16 },
	{ 0x05fff7fc, (u32 *)RAMBASE, 16 },
	{ 0x05ffeffc, (u32 *)RAMBASE, 16 },
	{ 0x05ffdffc, (u32 *)RAMBASE, 16 },
	{ 0x05ffbffc, (u32 *)RAMBASE, 16 },
	{ 0x05ff7ffc, (u32 *)RAMBASE, 16 },
	{ 0x05fefffc, (u32 *)RAMBASE, 16 },
	{ 0x05fdfffc, (u32 *)RAMBASE, 16 },
	{ 0x05fbfffc, (u32 *)RAMBASE, 16 },
	{ 0x05f7fffc, (u32 *)RAMBASE, 16 },
	{ 0x05effffc, (u32 *)RAMBASE, 16 },
	{ 0x05dffffc, (u32 *)RAMBASE, 16 },
	{ 0x05bffffc, (u32 *)RAMBASE, 16 },
	{ 0x057ffffc, (u32 *)RAMBASE, 16 },

	{0, 0, 0},
    };

    static u32	TimingTable[] = {

	/* walking 1 on tL */

	PI_DEF_TIMING,
	0x80371280,
	0x80371220,
	0x80371210,
	0x80371208,
	0x80371204,
	0x80371202,
	0x80371201,

	/* walking 1 on tP */

	0x80378040,
	0x80374040,
	0x80372040,
	0x80371040,
	0x80370840,
	0x80370440,
	0x80370240,
	0x80370140,

	/* all page size values */

	0x80301240,
	0x80311240,
	0x80321240,
	0x80331240,
	0x80341240,
	0x80351240,
	0x80361240,
	0x80371240,
	0x80381240,
	0x80391240,
	0x803a1240,
	0x803b1240,
	0x803c1240,
	0x803d1240,
	0x803e1240,
	0x803f1240,

	/* all values of tR */

	0x80071240,
	0x80171240,
	0x80271240,

	0,
    };

    int		i, j;
    u32		b32;
    int		tL, tP, tR;
    u32		PGS;
    TYPE_PIDMA	*iotp;	/* dma/pio IO test pointer */

    /* loop thru all of the timing */

    for (i=0; TimingTable[i]; i++) {

	/* setup both domain 1 and domain 2 timings */

	PI_UseDomain(0x10000000, TimingTable[i]);
	PI_UseDomain(0x05000000, TimingTable[i]);

	PI_ExtractSpeedParam(TimingTable[i], &tL, &tP, &tR, (int *)&PGS);
	PGS = PI_PGSTable[PGS];

	/* disable osPi DMA routines domain base address translation */

	osRomBase = (void *)0;

	/* loop thru all IO tests */

	iotp = IOTests;
	for (j = 0; iotp->nbytes; j++) {

#ifdef SKIP_ZARU
	    /* do DMA reads */
	    if (i < NUM_TIMING_ZARUCHECK && j < NUM_DMATEST_ZARUCHECK) {
		ZaruSetADBusCheck(ZARU_ON, 1);
		DO_DMA(iotp->romaddr, iotp->dramaddr, iotp->nbytes, OS_READ);
		if (PI_CheckIO(iotp->romaddr, iotp->nbytes, OS_READ, PGS) == PI_FAIL)
		    return PI_FAIL;
		ZaruSetADBusCheck(ZARU_OFF, 1);
	    }
	    else {
#endif
		DO_DMA(iotp->romaddr, iotp->dramaddr, iotp->nbytes, OS_READ);
#ifdef SKIP_ZARU
	    }
#endif

	    /* do DMA writes, but only if running from ROM. */
	    if (runningFromRom) {
		DO_DMA(iotp->romaddr, iotp->dramaddr, iotp->nbytes, OS_WRITE);
	    }

	    /* do PIO reads and check address + len */
#ifdef SKIP_ZARU
	    if (i < NUM_TIMING_ZARUCHECK && j < NUM_IOTEST_ZARUCHECK) {
		ZaruSetADBusCheck(ZARU_ON, 1);
		osPiReadIo(iotp->romaddr, &b32);
		if (PI_CheckIO(iotp->romaddr, sizeof(u32), OS_READ, PGS) == PI_FAIL)
		    return PI_FAIL;
		ZaruSetADBusCheck(ZARU_OFF, 1);
	    }
	    else {
#endif
		osPiReadIo(iotp->romaddr, &b32);
#ifdef SKIP_ZARU
	    }
#endif

	    /* do PIO writes, but only if running from ROM. */
	    if (runningFromRom) {
		osPiWriteIo(iotp->romaddr, b32);
	    }
	    iotp++;
	}
    }

    return PI_PASS;
}

int piAllTest()
{
    int	error=0;

    /* initialization prior to test */

    PI_TestInit();

    /*
     * Just try the full range of addresses and timing without regard for
     * ROM data correctness.
     *
     * This section include
     *		- full timing test
     *		- full ROM address test
     *
     * This section does not include
     *		- data correctness test
     */

    /* full timing and ROM address test */

    if (PI_TimingAddrTests() == PI_FAIL) error++;
    PI_UseDomain(PI_DEF_DOMAIN, PI_DEF_TIMING);

    /*
     * Tests after this point all check for data correctness. Therefore
     * we must limit the test conditions to ROM capability (timing, address)
     *
     * This section include
     *		- domain tests
     *		- limited ROM address read test
     *		- limited timing test
     *
     * This section does not include
     *		- full timing test
     *		- full ROM address test
     */

#define	PI_DATATEST(domain, speed)		\
	PI_UseDomain(domain, speed);	\
	if (PI_DataTests(speed) == PI_FAIL) error++;

    /* Domain Test */

    PI_DATATEST(PI_DEF_DOMAIN, PI_DEF_TIMING);

/*
 * The current GO/NOGO debug ROM do not have the other address
 * domains mapped correctly so we don't test for now.
 */

#ifdef _GONOGOROM
    PI_DATATEST(0x05000000, PI_DEF_TIMING);

    PI_DATATEST(0x06000000, PI_DEF_TIMING);

    PI_DATATEST(0x08000000, PI_DEF_TIMING);

    PI_DATATEST(0x1fd00000, PI_DEF_TIMING);
#endif

    /*
     * Timing Test, since we maybe in a mask rom, can only go slower than
     * 5.34 MB/s and smaller page sizes.
     *
     * Since we don't have HW for faster timing, we can not test PI's
     * full timing capabilities
     */

    /* slower tP */
    PI_DATATEST(PI_DEF_DOMAIN, 0x80372240);

    /* slower tL */
    PI_DATATEST(PI_DEF_DOMAIN, 0x803712ff);

    /* can't make slower tR */

    /* smaller page size */
    PI_DATATEST(PI_DEF_DOMAIN, 0x80351240);
    PI_DATATEST(PI_DEF_DOMAIN, 0x80331240);

    /* Reset back to original for future tests */
    PI_UseDomain(PI_DEF_DOMAIN, PI_DEF_TIMING);

    return error;
}
