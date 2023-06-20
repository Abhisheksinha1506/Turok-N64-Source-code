
/**************************************************************************
 *									  *
 *		 Copyright (C) 1996, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#include "gbi.h"

void guSprite2DInit(uSprite *SpritePointer,   
		    void *SourceImagePointer,
		    void *TlutPointer,
		    short Stride,
		    short SubImageWidth,
		    short SubImageHeight,
		    char  SourceImageType,
		    char  SourceImageBitSize,
		    short ScaleX,
		    short ScaleY,
		    char  FlipTextureX,
		    char  FlipTextureY,
		    short SourceImageOffsetS,
		    short SourceImageOffsetT,
		    short PScreenX,
		    short PScreenY)
{
  SpritePointer->s.SourceImagePointer = SourceImagePointer;
  SpritePointer->s.TlutPointer        = TlutPointer;
  SpritePointer->s.Stride             = Stride;
  SpritePointer->s.SubImageWidth      = SubImageWidth;
  SpritePointer->s.SubImageHeight     = SubImageHeight;
  SpritePointer->s.SourceImageType    = SourceImageType;
  SpritePointer->s.SourceImageBitSize = SourceImageBitSize;
  SpritePointer->s.ScaleX             = ScaleX;
  SpritePointer->s.ScaleY             = ScaleY;
  SpritePointer->s.FlipTextureX       = FlipTextureX;
  SpritePointer->s.FlipTextureY       = FlipTextureY;
  SpritePointer->s.SourceImageOffsetS = SourceImageOffsetS;
  SpritePointer->s.SourceImageOffsetT = SourceImageOffsetT;
  SpritePointer->s.PScreenX           = PScreenX;
  SpritePointer->s.PScreenY           = PScreenY;
}		 
		 
		 
		
