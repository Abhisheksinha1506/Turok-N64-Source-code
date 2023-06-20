/*
 *  Test texture lookup table, TLUT is 48 entries RGBA
 *  5-bit ramp in R/G/B
 */

#ifndef TLUT2_INCLD
#define TLUT2_INCLD

unsigned short Tlut2[] = {
	0x0001,
	(1 << 11)  | 1,
	(2 << 11)  | 1,
	(3 << 11)  | 1,
	(4 << 11)  | 1,
	(5 << 11)  | 1,
	(6 << 11)  | 1,
	(7 << 11)  | 1,
	(8 << 11)  | 1,
	(9 << 11)  | 1,
	(10 << 11) | 1,
	(11 << 11) | 1,
	(12 << 11) | 1,
	(13 << 11) | 1,
	(14 << 11) | 1,
	(15 << 11) | 1,
	0x0001,
	(1 << 6)  | 1,
	(2 << 6)  | 1,
	(3 << 6)  | 1,
	(4 << 6)  | 1,
	(5 << 6)  | 1,
	(6 << 6)  | 1,
	(7 << 6)  | 1,
	(8 << 6)  | 1,
	(9 << 6)  | 1,
	(10 << 6) | 1,
	(11 << 6) | 1,
	(12 << 6) | 1,
	(13 << 6) | 1,
	(14 << 6) | 1,
	(15 << 6) | 1,
	0x0001,
	(1 << 1)  | 1,
	(2 << 1)  | 1,
	(3 << 1)  | 1,
	(4 << 1)  | 1,
	(5 << 1)  | 1,
	(6 << 1)  | 1,
	(7 << 1)  | 1,
	(8 << 1)  | 1,
	(9 << 1)  | 1,
	(10 << 1) | 1,
	(11 << 1) | 1,
	(12 << 1) | 1,
	(13 << 1) | 1,
	(14 << 1) | 1,
	(15 << 1) | 1,
};

#endif /* TLUT2_INCLD */
