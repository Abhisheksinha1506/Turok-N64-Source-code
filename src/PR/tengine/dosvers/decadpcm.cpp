//*****************************************************************************
//	ADPCM Decompression Functions
//*****************************************************************************

#include "stdafx.h"

//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <string.h>

#include "adpcm2.h"

//---	1 = Fixed Point, 0 = Floating Point
#define	COEF_FIXED		1

//---	Filter Ceofficients
#if	COEF_FIXED
#define	FIXED_SCALE		16
#define	COEF	s32
static s32		FCA[MAX_FILTERS] = {F0CA*(1<<FIXED_SCALE), F1CA*(1<<FIXED_SCALE), F2CA*(1<<FIXED_SCALE), F3CA*(1<<FIXED_SCALE)} ;
static s32		FCB[MAX_FILTERS] = {F0CB*(1<<FIXED_SCALE), F1CB*(1<<FIXED_SCALE), F2CB*(1<<FIXED_SCALE), F3CB*(1<<FIXED_SCALE)} ;
#else
#define	COEF	float
static float	FCA[MAX_FILTERS] = {F0CA, F1CA, F2CA, F3CA} ;
static float	FCB[MAX_FILTERS] = {F0CB, F1CB, F2CB, F3CB} ;
#endif

//*****************************************************************************
//	Module Scoped Variables
//*****************************************************************************

//---	Bitstream Manipulation Variables
static u32		rdh_BitBuffer ;							// Read Headers Bitstream
static s32		rdh_BitsInBuffer ;
static u8		*rdh_BitPtr ;
static u32		rdd_BitBuffer ;							// Read Data Bitstream
static s32		rdd_BitsInBuffer ;
static u8		*rdd_BitPtr ;

/*****************************************************************************
*
*		Function Title: adpcmDecode ()
*
******************************************************************************
*
*		Synopsis:		void adpcmDecode ( RawBuffer, ADPCMBuffer, NumSignals )
*
*		Description:	Convert the ADPCM Data into 16Bit Sample Data
*
*		Inputs:			s16	*RawBuffer		- Buffer to put Raw Data in
*						u8	*ADPCMBuffer	- Buffer to get ADPCM Data from
*						s32	NumSignals		- Number of Signals in ADPCM Data
*
*		Outputs:		RawBuffer Filled
*
*****************************************************************************/

static void adpcmReadBitsInitH (u8 *Data)
{
	rdh_BitBuffer = *Data++ ;
	rdh_BitBuffer |= *Data++ << 8 ;
	rdh_BitBuffer |= *Data++ << 16 ;
	rdh_BitBuffer |= *Data++ << 24 ;
	rdh_BitsInBuffer = 32 ;
	rdh_BitPtr = Data ;
}

static s32 adpcmReadBitsH (s32 n)
{
	s32		v ;

	v = rdh_BitBuffer & ~(-1<<n) ;
	rdh_BitBuffer >>= n ;
	rdh_BitsInBuffer -= n ;
	if (rdh_BitsInBuffer <= 24)
	{
		rdh_BitBuffer |= (u32)(*rdh_BitPtr++) << rdh_BitsInBuffer ;
		rdh_BitsInBuffer += 8 ;
	}
	return v ;
}

static void adpcmReadBitsInitD (u8 *Data, u32 Bit)
{
	rdd_BitBuffer = *Data++ ;
	rdd_BitBuffer |= *Data++ << 8 ;
	rdd_BitBuffer |= *Data++ << 16 ;
	rdd_BitBuffer |= *Data++ << 24 ;
	rdd_BitBuffer >>= Bit ;
	rdd_BitsInBuffer = 32 - Bit ;
	rdd_BitPtr = Data ;
}

static u16 adpcmReadBitsD (s32 n)
{
	s16		v ;

	v = rdd_BitBuffer & ~(-1<<n) ;
	rdd_BitBuffer >>= n ;
	rdd_BitsInBuffer -= n ;
	if (rdd_BitsInBuffer <= 24)
	{
		rdd_BitBuffer |= (u32)(*rdd_BitPtr++) << rdd_BitsInBuffer ;
		rdd_BitsInBuffer += 8 ;
	}
	return v ;
}

static void adpcmDecodeSignal (s16 *RawBuffer, s32 SampleLen)
{
	s32		x1 = 0 ;
	s32		x2 = 0 ;
	s32		ps ;
	s32		v ;
	s16		s ;
	s16		Shift ;
	s16		Type ;
	s32		BlockPos = 0 ;
	u8		BlockHeader ;
	s32		t ;
	COEF	fca ;
	COEF	fcb ;

	//---	Get Initial Prediction from the Buffer
	ps = (s16)(adpcmReadBitsD (8) << 8) ;

	//---	Loop while Data Left
	while (SampleLen-- > 0)
	{
		//---	If first sample in New Block then read Block Header Details
		if (BlockPos-- == 0)
		{
			BlockPos = (BLOCK-1) ;
			BlockHeader = adpcmReadBitsH (6) ;
			Shift = (BlockHeader) & 0x0F ;
			Type = (BlockHeader >> 4) & 0x03 ;
			fca = FCA[Type] ; fcb = FCB[Type] ;
		}

		//---	Get Next Sample & Apply Filter to decode it
		s = adpcmReadBitsD (BITS) ;
		if (s & BIT_SIGN)
			t = ((s|~BITM) << Shift) ;
		else
			t = (s << Shift) ;
#if COEF_FIXED
		t += (x1*fca + x2*fcb) >> FIXED_SCALE ;
#else
		t += (x1*fca + x2*fcb) ;
#endif
		x2 = x1 ;
		x1 = t ;
		v = ps + t ;
		ps = v ;

		//---	Limit to Range of 16Bit Values & Save out
		v = min (32767, v) ;
		v = max (-32768, v) ;
		*RawBuffer++ = v ;
	}
}

s32	adpcmDecode (s16 **RawBuffers, u8 *ADPCMBuffer, s32 NumSignals)
{
	s32		SampleLen ;						// Sample Length to Decompress
	s32		NumBlocks ;						// Number of Blocks Encoded
	u8		*adpcm_Hdr ;					// Header Pointer
	//u8		*adpcm_Src ;					// Source Data Streams
	s32		i ;
	s32		BitPos ;

	//---	Initialize Pointer to ADPCM data
	adpcm_Hdr = ADPCMBuffer ;

	//---	Get Header Info from stream
	SampleLen = *adpcm_Hdr++ << 8 ;
	SampleLen |= *adpcm_Hdr++ ;

	//---	Determine Number of Blocks which were encoded
	NumBlocks = (SampleLen + BLOCK-1) / BLOCK ;

	//---	Setup BitStream to Read Data
	BitPos = NumBlocks * 6 ;
	adpcmReadBitsInitD (adpcm_Hdr + (BitPos / 8), BitPos & 7) ;

	//---	Setup Pointer to ADPCM Stream Data, after Header Data
	//adpcm_Src = adpcm_Hdr + NumBlocks ;

	//---	Decompress each signal in turn
	for (i = 0 ; i < NumSignals ; i++)
	{
		adpcmReadBitsInitH (adpcm_Hdr) ;
		adpcmDecodeSignal (RawBuffers[i], SampleLen) ;
	}

	//---	Return Number of Samples in Decoded Data
	return SampleLen ;
}
