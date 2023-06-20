# REMEMBER TO CONVERT VALUES TO gbi.h MACROS AND RUN THRU CPP
# setTile parameters 

set RGBA   0
set YUV    1
set CI     2
set IA     3
set I      4

set 4b     0
set 8b     1
set 16b    2
set 32b    3

set blank  9999
#												  	MM  	MM	MM			MM 	MM
#---------------------------------------------------------------------------------------------------------------------------------------------------------
#		0	1	2	3	4	5	6	7	8	9	10	11	12 	13	14	15	16	17
#---------------------------------------------------------------------------------------------------------------------------------------------------------
set formatA0	{0	0  	4	4	4 	3	3	3	4	2	2	0	0	0	0	0	0	4}
set formatA1	{0 	0  	4	4	4 	3	3	3	4	2	2	0	0	0	0	0	0	4}
set formatA2	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	4}
set formatA3	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	4}
set formatA4	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	4}
set formatA5	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	4}
set formatA6	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	4}
set formatA7	{0 	0  	4	4	4 	3	3	3	4	2	2	0	0	0	0	0	0	4}

set sizeA0     	{2	2 	1	1	0 	2	1	0	1	1	0	2	2	2	2	3	2	1}
set sizeA1     	{2	2 	1	1	0 	2	1	0	1	1	0	2	2	2	2	3	2	1}
set sizeA2     	{0	0	0	0	0	0	0	0	0	0	0	2	2	2	0	0	2	1}
set sizeA3     	{0	0	0	0	0	0	0	0	0	0	0	2	2	2	0	0	2	1}
set sizeA4     	{0	0	0	0	0	0	0	0	0	0	0	2	2	2	0	0	2	1}
set sizeA5     	{0	0	0	0	0	0	0	0	0	0	0	2	2	2	0	0	2	1}
set sizeA6     	{0	0	0	0	0	0	0	0	0	0	0	2	2	2	0	0	2	1}
set sizeA7     	{2 	2 	1	1	0 	2	1	0	1	1	0	2	2	2	2	3	2	1}

set lineSizeA0 	{8 	8 	8	4	4 	8	4	2	4	4	2	8	8	8	16	8	8	0}
set lineSizeA1 	{8 	8 	8	4	4 	8	4	2	4	4	2	8	8	8	16	8	8	4}
set lineSizeA2 	{0	0	0	0	0	0	0	0	0	0	0	4	4	4	0	0	4	2}
set lineSizeA3 	{0	0	0	0	0	0	0	0	0	0	0	2	2	2	0	0	2	1}
set lineSizeA4 	{0	0	0	0	0	0	0	0	0	0	0	1	1	1	0	0	1	1}
set lineSizeA5 	{0	0	0	0	0	0	0	0	0	0	0	1	1	1	0	0	1	1}
set lineSizeA6 	{0	0	0	0	0	0	0	0	0	0	0	1	1	1	0	0	1	1}
set lineSizeA7 	{8 	8 	8	4	4 	8	4	2	4	4	2	0	0	0	16	8	0	0}

set tmemAddrA0 	{0 	0  	0	0	0  	0	0	0	0	0	0	0	0	0	0	0	0	0}
set tmemAddrA1 	{0 	0  	0	0	0  	0	0	0	0	0	0	0	0	0	0	0	0	0}
set tmemAddrA2 	{0	0	0	0	0	0	0	0	0	0	0	256	256	256	0	0	256	128}
set tmemAddrA3 	{0	0	0	0	0	0	0	0	0	0	0	320	320	320	0	0	320	160}
set tmemAddrA4 	{0	0	0	0	0	0	0	0	0	0	0	336	336	336	0	0	336	168}
set tmemAddrA5 	{0	0	0	0	0	0	0	0	0	0	0	340	340	340	0	0	340	172}
set tmemAddrA6 	{0	0	0	0	0	0	0	0	0	0	0	342	342	342	0	0	342	174}
set tmemAddrA7 	{0   	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}

set wrapMirrSA0	{0   	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set wrapMirrSA1	{0   	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set wrapMirrSA2	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set wrapMirrSA3	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set wrapMirrSA4	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set wrapMirrSA5	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set wrapMirrSA6	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set wrapMirrSA7	{0   	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}

set clampSA0   	{0   	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set clampSA1   	{0   	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set clampSA2	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set clampSA3	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set clampSA4	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set clampSA5	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set clampSA6	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set clampSA7   	{0   	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}

set maskSA0    	{5   	5   	6	5	6   	5	5	5	5	5	5	5	5	5	6	5	5	5}
set maskSA1    	{5  	5   	6	5	6   	5	5	5	5	5	5	5	5	5	6	5	5	5}
set maskSA2	{0	0	0	0	0	0	0	0	0	0	0	4	4	4	0	0	4	4}
set maskSA3	{0	0	0	0	0	0	0	0	0	0	0	3	3	3	0	0	3	3}
set maskSA4	{0	0	0	0	0	0	0	0	0	0	0	2	2	2	0	0	2	2}
set maskSA5	{0	0	0	0	0	0	0	0	0	0	0	1	1	1	0	0	1	1}
set maskSA6	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set maskSA7    	{5  	5   	6	5	6   	5	5	5	5	5	5	0	0	0	6	5	0	5}
	
set shiftSA0   	{0  	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set shiftSA1   	{0  	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set shiftSA2	{0	0	0	0	0	0	0	0	0	0	0	1	1	1	0	0	1	1}
set shiftSA3	{0	0	0	0	0	0	0	0	0	0	0	2	2	2	0	0	2	2}
set shiftSA4	{0	0	0	0	0	0	0	0	0	0	0	3	3	3	0	0	3	3}
set shiftSA5	{0	0	0	0	0	0	0	0	0	0	0	4	4	4	0	0	4	4}
set shiftSA6	{0	0	0	0	0	0	0	0	0	0	0	5	5	5	0	0	5	5}
set shiftSA7   	{0  	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}

set wrapMirrTA0	{0  	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set wrapMirrTA1	{0  	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set wrapMirrTA2	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set wrapMirrTA3	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set wrapMirrTA4	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set wrapMirrTA5	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set wrapMirrTA6	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set wrapMirrTA7	{0  	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}

set clampTA0   	{0  	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set clampTA1   	{0  	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set clampTA2	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set clampTA3	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set clampTA4	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set clampTA5	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set clampTA6	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set clampTA7   	{0  	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}

set maskTA0    	{5  	5   	6	5	6   	5	5	5	5	5	5	5	5	5	5	5	5	5}
set maskTA1    	{5   	5   	6	5	6   	5	5	5	5	5	5	5	5	5	5	5	5	5}
set maskTA2	{0	0	0	0	0	0	0	0	0	0	0	4	4	4	0	0	4	4}
set maskTA3	{0	0	0	0	0	0	0	0	0	0	0	3	3	3	0	0	3	3}
set maskTA4	{0	0	0	0	0	0	0	0	0	0	0	2	2	2	0	0	2	2}
set maskTA5	{0	0	0	0	0	0	0	0	0	0	0	1	1	1	0	0	1	1}
set maskTA6	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set maskTA7    	{5   	5   	6	5	6   	5	5	5	5	5	5	0	0	0	5	5	0	0}

set shiftTA0   	{0   	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set shiftTA1   	{0   	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set shiftTA2	{0	0	0	0	0	0	0	0	0	0	0	1	1	1	0	0	1	1}
set shiftTA3	{0	0	0	0	0	0	0	0	0	0	0	2	2	2	0	0	2	2}
set shiftTA4	{0	0	0	0	0	0	0	0	0	0	0	3	3	3	0	0	3	3}
set shiftTA5	{0	0	0	0	0	0	0	0	0	0	0	4	4	4	0	0	4	4}
set shiftTA6	{0	0	0	0	0	0	0	0	0	0	0	5	5	5	0	0	5	5}
set shiftTA7   	{0   	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}

set paletteA0	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set paletteA1  	{0   	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set paletteA2	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set paletteA3	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set paletteA4	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set paletteA5	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set paletteA6	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set paletteA7  	{0   	0   	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}

set widthA0    	{32  	32 	64	32	64  	32	32	32	32	32	32	32	32	32	64	32	32	32}
set widthA1    	{32  	32 	64	32	64  	32	32	32	32	32	32	32	32	32	64	32	32	32}
set widthA2  	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set widthA3  	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set widthA4  	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set widthA5  	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set widthA6  	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set widthA7    	{32  	32 	64	32	64  	32	32	32	32	32	32	32	32	32	64	32	32	32}

set heightA0    {32  	32 	60	32	64  	32	32	32	32	32	32	32	32	32	32	32	32	32}
set heightA1    {32  	32 	60	32	64  	32	32	32	32	32	32	32	32	32	32	32	32	32}
set heightA2  	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set heightA3  	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set heightA4  	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set heightA5  	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set heightA6  	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set heightA7    {32  	32 	60	32	64  	32	32	32	32	32	32	32	32	32	32	32	32	32}

set mipmapA0   	{0   	0   	0	0	0   	0	0	0	0	0	0	1	1	1	0	0	1	1}


# setTileSize parameters
set tileA0	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set tileA1     	{0   	0    	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set tileA2	{0	0	0	0	0	0	0	0	0	0	0	1	1	1	0	0	1	1}
set tileA3	{0	0	0	0	0	0	0	0	0	0	0	2	2	2	0	0	2	2}
set tileA4	{0	0	0	0	0	0	0	0	0	0	0	3	3	3	0	0	3	3}
set tileA5	{0	0	0	0	0	0	0	0	0	0	0	4	4	4	0	0	4	4}
set tileA6	{0	0	0	0	0	0	0	0	0	0	0	5	5	5	0	0	5	5}
set tileA7     	{0   	0    	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}

set sLowA0	{0	0	0	0	0	0	0	0	0	0	0	0 	0 	0 	0	0	0	0}
set sLowA1     	{0   	0   	0	0	0   	0	0	0	0	0	0	0.5 	0 	0 	0	0	0.5	0.5}
set sLowA2	{0	0	0	0	0	0	0	0	0	0	0	0.5 	0 	0 	0	0	0.5	0.5}
set sLowA3	{0	0	0	0	0	0	0	0	0	0	0	0.5 	0 	0 	0	0	0.5	0.5}
set sLowA4	{0	0	0	0	0	0	0	0	0	0	0	0.5 	0 	0 	0	0	0.5	0.5}
set sLowA5	{0	0	0	0	0	0	0	0	0	0	0	0.5 	0 	0 	0	0	0.5	0.5}
set sLowA6	{0	0	0	0	0	0	0	0	0	0	0	0.5 	0 	0 	0	0	0.5	0.5}
set sLowA7     	{0   	0   	0	0	0   	0	0	0	0	0	0	0 	0 	0 	0	0	0	0}

set sHiA0      	{31  	31  	63	31	63  	31	31	31	31	31	31	31	31	31	63	31	31	31}
set sHiA1      	{31  	31  	63	31	63  	31	31	31	31	31	31	31	31	31	63	31	31	31}
set sHiA2	{0	0	0	0	0	0	0	0	0	0	0	15	15	15	0	0	0	15}
set sHiA3	{0	0	0	0	0	0	0	0	0	0	0	7	7	7	0	0	0	7}
set sHiA4	{0	0	0	0	0	0	0	0	0	0	0	3	3	3	0	0	0	3}
set sHiA5	{0	0	0	0	0	0	0	0	0	0	0	1	1	1	0	0	0	1}
set sHiA6	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set sHiA7      	{31  	31  	63	31	63  	31	31	31	31	31	31	0	0	0	63	31	31	31}

set tLowA0	{0	0	0	0	0	0	0	0	0	0	0	0 	0 	0 	0	0	0	0}
set tLowA1     	{0   	0    	0	0	0   	0	0	0	0	0	0	0.5 	0 	0 	0	0	0.5	0.5}
set tLowA2	{0	0	0	0	0	0	0	0	0	0	0	0.5 	0 	0 	0	0	0.5	0.5}
set tLowA3	{0	0	0	0	0	0	0	0	0	0	0	0.5 	0 	0 	0	0	0.5	0.5}
set tLowA4	{0	0	0	0	0	0	0	0	0	0	0	0.5 	0 	0 	0	0	0.5	0.5}
set tLowA5	{0	0	0	0	0	0	0	0	0	0	0	0.5 	0 	0 	0	0	0.5	0.5}
set tLowA6	{0	0	0	0	0	0	0	0	0	0	0	0.5 	0 	0 	0	0	0.5	0.5}
set tLowA7     	{0   	0   	0	0	0   	0	0	0	0	0	0	0 	0 	0 	0	0	0	0}

set tHiA0      	{31  	31 	59	31	63  	31	31	31	31	31	31	31	31	31	31	31	31	31}
set tHiA1      	{31  	31  	59	31	63  	31	31	31	31	31	31	31	31	31	31	31	31	31}
set tHiA2	{0	0	0	0	0	0	0	0	0	0	0	15	15	15	0	0	15	15}
set tHiA3	{0	0	0	0	0	0	0	0	0	0	0	7	7	7	0	0	7	7}
set tHiA4	{0	0	0	0	0	0	0	0	0	0	0	3	3	3	0	0	3	3}
set tHiA5	{0	0	0	0	0	0	0	0	0	0	0	1	1	1	0	0	1	1}
set tHiA6	{0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0}
set tHiA7      	{31  	31  	59	31	63  	31	31	31	31	31	31	0	0	0	31	31	0	31}

#loadBlock parameters 
# note that sH is set for 4-bit textures as if they were 8-bit textures
set lbTileA    	{7   	7     	7	7	7   	7	7	7	7	7	7	7	7	7	7	7	7	0}
set lbSlowA    	{0   	0     	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set lbTlowA    	{0   	0     	0	0	0   	0	0	0	0	0	0	0	0	0	0	0	0	0}
set lbShiA     	{1023	1023  	3839	1023	2047 	1023	1023	511	1023	1023	511	1372	1372	1372	2047	1023	1372	1400}
set lbDxtA     	{0x100 	0x100 	0x100	0x200	0x200 	0x100	0x200	0x400	0x200	0x200	0x400	0x0	0x0	0x0	0x80	0x80	0x0	0x0}

#loadTlut parameters
set loadTlutCountA \
		{0	0	0	0	0	0	0	0	0	256	16	0	0	0	0	0	0	0}
set loadTlutOffsetA \
		{0	0	0	0	0	0	0	0	0	256	256	0	0	0	0	0	0	0}
set loadTlutAddrA  \
		{0	0	0	0	0	0	0	0	0	108	109	0	0	0	0	0	0	0}


 ######################### loadTextureMap Frames ###################################
#set loadTexOptions {.loadTexFileMB .loadTexFormatMB .loadTexTexelsizeMB .loadTexWidthL .loadTexHeightL .loadTexAddrsL .loadTexWrapMirsMB .loadTexClampsCB .loadTexMasksL .loadTexWrapMirtMB .loadTexClamptCB .loadTexMasktL .loadTexPalttL .loadTexMipmapCB .loadTexDoneB }

set loadTexOptions {.loadTexFileMB .loadTexFormatL .loadTexTexelSizeL .loadTexWidthL .loadTexHeightL .loadTexDoneB }

#set loadTexEntries { .loadTexFileL .loadTexFormatE .loadTexTexelSizeL .loadTexWidthE .loadTexHeightE .loadTexAddrsE .loadTexWrapMirsL .loadTexClampsL .loadTexMaskE .loadWrapMirtL .loadTexClamptL .loadTexMasktE .loadTexPalttE }

set loadTexEntries { .loadTexFileL .loadTexFormatE .loadTexTexelSizeE .loadTexWidthE .loadTexHeightE }

for {set i 0} {$i < [llength $loadTexOptions]} {incr i 1} {
   frame .loadTexFrame$i
}

label .loadTmL -text "selectTextureMap" -relief groove

menubutton .loadTexFileMB -text "texFile" -width 10 -relief raised -menu .loadTexFileMB.menu -bg LightGray -activebackground LightGray
menu .loadTexFileMB.menu
.loadTexFileMB.menu add radiobutton -label RGBA16molecule -command CloadTexFile -variable loadTexFile -value 0
.loadTexFileMB.menu add radiobutton -label RGBA16grid -command CloadTexFile -variable loadTexFile -value 1
#.loadTexFileMB.menu add radiobutton -label I8mand -command CloadTexFile -variable loadTexFile -value 2
.loadTexFileMB.menu add radiobutton -label I8cloud -command CloadTexFile -variable loadTexFile -value 3
.loadTexFileMB.menu add radiobutton -label I4granite -command CloadTexFile -variable loadTexFile -value 4
.loadTexFileMB.menu add radiobutton -label 1A16tree -command CloadTexFile -variable loadTexFile -value 5
.loadTexFileMB.menu add radiobutton -label IA8tree -command CloadTexFile -variable loadTexFile -value 6
.loadTexFileMB.menu add radiobutton -label IA4tree -command CloadTexFile -variable loadTexFile -value 7
.loadTexFileMB.menu add radiobutton -label I8grid -command CloadTexFile -variable loadTexFile -value 8
.loadTexFileMB.menu add radiobutton -label CI8mario -command CloadTexFile -variable loadTexFile -value 9
.loadTexFileMB.menu add radiobutton -label CI4mario -command CloadTexFile -variable loadTexFile -value 10
.loadTexFileMB.menu add radiobutton -label RGBA16checkMM -command CloadTexFile -variable loadTexFile -value 11
.loadTexFileMB.menu add radiobutton -label RGBA16treeMM -command CloadTexFile -variable loadTexFile -value 12
.loadTexFileMB.menu add radiobutton -label RGBA16foliageMM -command CloadTexFile -variable loadTexFile -value 13
.loadTexFileMB.menu add radiobutton -label RGBA16mario -command CloadTexFile -variable loadTexFile -value 14
.loadTexFileMB.menu add radiobutton -label RGBA32mario -command CloadTexFile -variable loadTexFile -value 15
.loadTexFileMB.menu add radiobutton -label RGBA16check1 -command CloadTexFile -variable loadTexFile -value 16
.loadTexFileMB.menu add radiobutton -label I8check -command CloadTexFile -variable loadTexFile -value 17

#set loadTexFile 0
#set LloadTexFile texFile0

label .loadTexFileL -width 8 -relief sunken -textvariable LloadTexFile

proc CloadTexFile {} {
  global fptr record
  global loadTexFile
  global LloadTexFile
  global setTimgFmt setTimgSize setTimgwidth setTimgDramAddr
  global lbTileA lbSlowA lbTlowA lbShiA lbDxtA
  global fptr record
  global setTotherTlut G_TT_RGBA16 G_TT_IA16 G_TT_NONE

  for {set i 0} {$i <= 7} {incr i 1} {
	global formatA$i sizeA$i widthA$i lineSizeA$i
	global heightA$i tmemAddrA$i wrapMirrSA$i clampSA$i maskSA$i shiftSA$i
	global wrapMirrTA$i clampTA$i maskTA$i shiftTA$i paletteA$i mipmapA$i
	global tileA$i sLowA$i sHiA$i tlowA$i tHiA$i
  }

  if {$record == 1} {
	puts $fptr "set loadTexFile $loadTexFile"
	puts $fptr "CloadTexFile"
  }

   switch $loadTexFile {
	0 {
		set LloadTexFile molecule
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }

	1 {
		set LloadTexFile grid
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }
	
	2 {	
		set LloadTexFile mand
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }
	
	3 {	
		set LloadTexFile cloud
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }
	
	4 {
		set LloadTexFile granite
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }

	5 {	
		set LloadTexFile tree
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }

	6 {
		set LloadTexFile tree
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }

	7 {
		set LloadTexFile tree
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }

	8 {	
		set LloadTexFile grid
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }

	9 {
		set LloadTexFile mario
		set setTotherTlut $G_TT_RGBA16
		CsetTotherTlut
	  }

	10 {
		set LloadTexFile mario
		set setTotherTlut $G_TT_RGBA16
		CsetTotherTlut
	  }

	11 {
		set LloadTexFile check
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }

	12 {
		set LloadTexFile tree
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }

	13 {
		set LloadTexFile foliage
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }

	14 {
		set LloadTexFile mario
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }

	15 {
		set LloadTexFile mario
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }

	16 {
		set LloadTexFile check1
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }

	17 {
		set LloadTexFile check1
		set setTotherTlut $G_TT_NONE
		CsetTotherTlut
	  }


   }

   #################### loadTextureMap ###################

   global loadTexFormat loadTexTexelSize loadTexWidth loadTexHeight
   global loadTexTmemAddr loadTexWrapMirS loadTexClampS loadTexMaskS
   global loadTexWrapMirT loadTexClampT loadTexMaskT loadTexPalette 
   global loadTexMipmap

   set loadTexFormat 		[lindex $formatA0	$loadTexFile ]
   CloadTexFormat
   set loadTexTexelSize		[lindex $sizeA0		$loadTexFile ]
   CloadTexTexelSize
   set loadTexWidth		[lindex $widthA0	$loadTexFile ]
   set loadTexHeight		[lindex $heightA0	$loadTexFile ]
   set loadTexTmemAddr		[lindex $tmemAddrA0	$loadTexFile ]
   set loadTexWrapMirS 		[lindex $wrapMirrSA0     $loadTexFile ]
   CloadTexWrapMirS
   set loadTexClampS		[lindex $clampSA0        $loadTexFile ]
   clampSsetLabel
   set loadTexMaskS		[lindex $maskSA0         $loadTexFile ]
   set loadTexWrapMirT 		[lindex $wrapMirrTA0     $loadTexFile ]
   CloadTexWrapMirT
   set loadTexClampT		[lindex $clampTA0        $loadTexFile ]
   clampTsetLabel
   set loadTexMaskT		[lindex $maskTA0         $loadTexFile ]
   set loadTexPalette 		[lindex $paletteA0       $loadTexFile ]
   set loadTexMipmap		[lindex $mipmapA0	$loadTexFile ]
    
   ############### set setTimg parameters #############################

   global setTimgFmt setTimgSize setTimgwidth

   set setTimgFmt [lindex $formatA0 $loadTexFile ]
   CsetTimgFmt
   set setTimgSize [lindex $sizeA0 $loadTexFile ] 
   if {$setTimgSize == 0} {
	set setTimgSize 1   
	# 4-bit textures to be loaded as 8-bit
   }
   CsetTimgSize
   set setTimgwidth [lindex $widthA0 $loadTexFile ] 
   set setTimgDramAddr $loadTexFile

   ############## setTile parameters ##################################

   set LOADTILE 7
   set RENDERTILE 1
   set tileList {0 1 2 3 4 5 6 7}
   
   # set both LOADTILE and RENDERTILE parameters in this loop
   foreach tile $tileList {

     global setTileFormat$tile setTileTexelSize$tile setTileWrapMirs$tile
     global setTileLine$tile setTileAddrs$tile
     global setTileClamps$tile setTileMaskS$tile setTileShiftS$tile
     global setTileWrapMirt$tile setTileClampt$tile setTileMaskT$tile
     global setTileShiftT$tile setTilePalette$tile
     global setTileSizeSlFloat$tile setTileSizeTlFloat$tile 
     global setTileSizeShFloat$tile setTileSizeThFloat$tile

     set first formatA
     set next $tile
     upvar #0 $first$next x

     set setTileFormat$tile	[lindex $x    	$loadTexFile ]
     CsetTileFormat

     set first sizeA
     set next $tile
     upvar #0 $first$next x

     set setTileTexelSize$tile 	[lindex $x     	$loadTexFile ]
     CsetTileTexelSize

     set first lineSizeA
     set next $tile
     upvar #0 $first$next x

     set setTileLine$tile	[lindex $x 	$loadTexFile ]

     set first tmemAddrA
     set next $tile
     upvar #0 $first$next x

     set setTileAddrs$tile	[lindex $x	$loadTexFile ]

     set first wrapMirrSA
     set next $tile
     upvar #0 $first$next x

     set setTileWrapMirs$tile	[lindex $x 	$loadTexFile ]

     set first clampSA
     set next $tile
     upvar #0 $first$next x

     CsetTileWrapMirs
     set setTileClamps$tile	[lindex $x    	$loadTexFile ]

     set first maskSA
     set next $tile
     upvar #0 $first$next x

     set setTileMaskS$tile	[lindex $x     	$loadTexFile ]

     set first shiftSA
     set next $tile
     upvar #0 $first$next x

     set setTileShiftS$tile	[lindex $x    	$loadTexFile ]

     set first wrapMirrTA
     set next $tile
     upvar #0 $first$next x

     set setTileWrapMirt$tile	[lindex $x 	$loadTexFile ]

     set first clampTA
     set next $tile
     upvar #0 $first$next x

     CsetTileWrapMirt
     set setTileClampt$tile	[lindex $x	$loadTexFile ]

     set first maskTA
     set next $tile
     upvar #0 $first$next x

     set setTileMaskT$tile	[lindex $x	$loadTexFile ]

     set first shiftTA
     set next $tile
     upvar #0 $first$next x
     set setTileShiftT$tile   [lindex $x      $loadTexFile ]


     set first paletteA
     set next $tile
     upvar #0 $first$next x
     set setTilePalette$tile	[lindex $x   	$loadTexFile ]


     ####################### setTileSize parameters ###########################


     set first sLowA
     set next $tile
     upvar #0 $first$next x

     set setTileSizeSlFloat$tile	[lindex $x      	$loadTexFile ]

     set first sHiA
     set next $tile
     upvar #0 $first$next x

     set setTileSizeShFloat$tile	[lindex $x 		$loadTexFile ]

     set first tLowA
     set next $tile
     upvar #0 $first$next x

     set setTileSizeTlFloat$tile	[lindex $x 		$loadTexFile ]

     set first tHiA
     set next $tile
     upvar #0 $first$next x

     set setTileSizeThFloat$tile	[lindex $x 		$loadTexFile ]
   }

   ############## modifications to parameters for tile 7  ###################
   #for loadBlock, linesize must be set to zero.
   set setTileLine7 0    
   if {$setTileTexelSize7 == 0} {
	set setTileTexelSize7 1
        CsetTileTexelSize
   }


   ###################  loadBlock parameters ###############################

   global lbTileA lbSlowA lbTlowA lbShiA lbDxtA
   global loadBlockTile loadBlockSl loadBlockTl
   global loadBlockSh loadBlockDxt

   set loadBlockTile 		[lindex $lbTileA	$loadTexFile ]
   set loadBlockSl		[lindex $lbSlowA	$loadTexFile ]
   set loadBlockTl		[lindex $lbTlowA	$loadTexFile ]
   set loadBlockSh		[lindex $lbShiA		$loadTexFile ]
   set loadBlockDxt		[lindex $lbDxtA		$loadTexFile ]

   ###################### loadTlut parameters ############################

   global loadTlutOffsetA loadTlutCountA loadTlutAddrA
   global loadTlutOffset loadTlutCount loadTlutAddr loadTlutTLUT

   set loadTlutCount		[lindex $loadTlutCountA  $loadTexFile ]
   set loadTlutOffset		[lindex $loadTlutOffsetA $loadTexFile ]
   set loadTlutAddr		[lindex $loadTlutAddrA   $loadTexFile ]
   set loadTlutTLUT		[lindex $LloadTexFile    $loadTexFile ]
}


label .loadTexFormatL  -width 10 -text "texelFmt" -relief groove
label .loadTexFormatE -width 8 -relief sunken -textvariable LloadTexFormat
#set loadTexFormat 0
#set LloadTexFormat RGBA

proc CloadTexFormat {} {
   global loadTexFormat
   global LloadTexFormat

    switch $loadTexFormat {
	0 {set LloadTexFormat RGBA}
	1 {set LloadTexFormat YUV}
	2 {set LloadTexFormat CI}
	3 {set LloadTexFormat IA}
	4 {set LloadTexFormat I}
    }

}

label .loadTexTexelSizeL  -width 10 -text "texelSiz" -relief groove
label .loadTexTexelSizeE -width 8 -relief sunken -textvariable LloadTexTexelSize
#set loadTexTexelSize 2
#set LloadTexTexelSize 16

proc CloadTexTexelSize {} {
   global loadTexTexelSize
   global LloadTexTexelSize

    switch $loadTexTexelSize {
	0 {set LloadTexTexelSize   4}
	1 {set LloadTexTexelSize   8}
	2 {set LloadTexTexelSize 16}
	3 {set LloadTexTexelSize 32}
    }

}


label .loadTexWidthL  -width 10 -text "width" -relief groove
label .loadTexWidthE -width 8 -relief sunken -textvariable loadTexWidth
#set loadTexWidth 32

label .loadTexHeightL -width 10 -text "height" -relief groove
label .loadTexHeightE -width 8 -relief sunken -textvariable loadTexHeight
#set loadTexHeight 32

label .loadTexAddrsL  -width 10 -text "tmemAddr" -relief groove
entry .loadTexAddrsE -width 8 -relief sunken -textvariable loadTexTmemAddr
#set loadTexTmemAddr 0

menubutton .loadTexWrapMirsMB  -width 10 -text "wrapMirS" -relief raised -menu .loadTexWrapMirsMB.menu -bg LightGray -activebackground LightGray
menu .loadTexWrapMirsMB.menu 
.loadTexWrapMirsMB.menu add radiobutton -label wrapS  -command CloadTexWrapMirS -variable loadTexWrapMirS -value 0
.loadTexWrapMirsMB.menu add radiobutton -label mirrorS  -command CloadTexWrapMirS -variable loadTexWrapMirS -value 1

#set LloadTexWrapMirS wrapS
#set loadTexWrapMirS 0

label .loadTexWrapMirsL -width 8 -relief sunken -textvariable LloadTexWrapMirS

proc CloadTexWrapMirS {} {
   global loadTexWrapMirS
   global LloadTexWrapMirS
   global fptr record

    switch $loadTexWrapMirS {
	0   {set LloadTexWrapMirS   wrS}
	1 {set LloadTexWrapMirS   miS}
    }
}

checkbutton .loadTexClampsCB -width 7 -command clampSsetLabel -padx 3 -text "clampS" -variable loadTexClampS
#set loadTexClampS 1

label .loadTexClampsL -width 8 -relief sunken -textvariable loadTexClampsLabel
#set loadTexClampsLabel On

proc clampSsetLabel {} {
  global loadTexClampS
  global loadTexClampsLabel
   global fptr record
  if {$loadTexClampS == 1} {
       set loadTexClampsLabel "On" 
  } else {
      set loadTexClampsLabel "Off"
  }
}

label .loadTexMasksL  -width 10 -text "maskS" -relief groove
entry .loadTexMaskE -width 8 -relief sunken -textvariable loadTexMaskS
#set loadTexMaskS 5

menubutton .loadTexWrapMirtMB   -width 10 -text "wrapMirT" -relief raised -menu .loadTexWrapMirtMB.menu -bg LightGray -activebackground LightGray
menu .loadTexWrapMirtMB.menu 
.loadTexWrapMirtMB.menu add radiobutton -label WrapT  -command CloadTexWrapMirT -variable loadTexWrapMirT -value 0
.loadTexWrapMirtMB.menu add radiobutton -label MirrorT -command CloadTexWrapMirT -variable loadTexWrapMirT -value 1

#set LloadTexWrapMirT wrapT
#set loadTexWrapMirT 0

label .loadWrapMirtL -width 8 -relief sunken -textvariable LloadTexWrapMirT

proc CloadTexWrapMirT {} {
   global loadTexWrapMirT
   global LloadTexWrapMirT
   global fptr record

    switch $loadTexWrapMirT {
	0   {set LloadTexWrapMirT   wrT}
	1 {set LloadTexWrapMirT   miT}
    }
}

checkbutton .loadTexClamptCB -width 7 -command clampTsetLabel -padx 3 -text "clampT" -variable loadTexClampT
#set loadTexClampT 1

label .loadTexClamptL -width 8 -relief sunken -textvariable loadTexClamptLabel
set loadTexClamptLabel On

proc clampTsetLabel {} {
  global loadTexClampT
  global loadTexClamptLabel
   global fptr record
  if {$loadTexClampT == 1} {
       set loadTexClamptLabel "On" 
  } else {
      set loadTexClamptLabel "Off"
  }
}

label .loadTexMasktL  -width 10 -text "maskT" -relief groove
entry .loadTexMasktE -width 8 -relief sunken -textvariable loadTexMaskT
#set loadTexMaskT 4

label .loadTexPalttL  -width 10 -text "paltt No" -relief groove
entry .loadTexPalttE -width 8 -relief sunken -textvariable loadTexPalette
#set loadTexPalette 0

checkbutton .loadTexDetailCB -text "detailmap" -variable loadTexDetail -command CloadTexDetail

#set loadTexDetail 0

proc CloadTexDetail {} {
	global record fptr
	global loadTexDetail
	
    if {$record == 1} {
	puts $fptr "set loadTexDetail $loadTexDetail"
	puts $fptr "CloadTexDetail"
    }
}
	

checkbutton .loadTexMipmapCB -text "mipmap" -variable loadTexMipmap -command CloadTexMipmap
#set loadTexMipmap 0
#
proc CloadTexMipmap {} {
	global record fptr
	global loadTexMipmap

	if {$record == 1} {
           puts $fptr "set loadTexMipmap $loadTexMipmap"
           puts $fptr "CloadTexMipmap"
    	}
}


button .loadTexDoneB -command CloadTex  -text "done"

proc CloadTex {} {
	global fptr record loadTex_dirty 
	global loadTexFile loadTlut_dirty

	set loadTex_dirty 1

 	switch $loadTexFile {
		9 {
			set loadTlut_dirty 1
			callback_setTother
			callback_loadTlut
		  }

		10 {
			set loadTlut_dirty 1
			callback_setTother
			callback_loadTlut
		  }
	}

	CshiftTileSize

	callback_spTex
	callback_setTimg
	callback_setTile
	callback_setTileSize
	callback_loadBlock
	callback_setTother
	callback_send_dl

    if {$record == 1} {
	puts $fptr "CloadTex"
    }
}
