/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1995, 1996 Silicon Graphics, Inc.          *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

/*
 * File:	texture.c
 * Creator:	hal@sgi.com
 * Create Date:	Wed Sep 27 17:40:23 PDT 1995
 * Purpose:
 *
 * This file holds texture data chunks that are 'static' data; at one point
 * we loaded them in at a fixed, known location by makerom, so that we would 
 * know where to load this data when generating .rdram files, BUT since the gng
 * app no longer supports .rdram file generation, we just load these textures
 * into the codesegment at whatever address makerom assigns for us.
 */

#include <ultra64.h>

#include "RGBA16data.h"
#include "RGBA16checkerMM.h"
#include "spacer.h"
#include "RGBA16longspan.h"
#include "loadTlut.h"
#include "RGBA16data_bar.h"

#include "map.h"

#include "map_a5.h"
#include "map_5a.h"
#include "map_rand.h"
#include "map_rand_comp.h"
#include "map_rand32.h"
#include "map_cs16_rand.h"
#include "RGBA16powersOfTwoMM.h"

#include "cc_tex.h"

#include "YUVbars.h"
#include "RGBA32pattern.h"
#include "RGBA16dana.h"
#include "tf_tex.h"

#include "bl_tex1.h"
