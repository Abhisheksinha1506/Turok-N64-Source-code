##################### Blender #######################################
toplevel .bl

frame .bl.topF
frame .bl.stateF
frame .bl.muxesF
frame .bl.cyc0ColorF -relief ridge -borderwidth 2
frame .bl.cyc1ColorF -relief ridge -borderwidth 2

frame .bl.modeBitsF -relief ridge -borderwidth 2
frame .bl.modeBitsF1 
frame .bl.modeBitsF2

frame .bl.ditherF -relief ridge -borderwidth 4

frame .bl.colorF -relief ridge -borderwidth 4
frame .bl.blendColorF
frame .bl.blendRedF 
frame .bl.blendGreenF 
frame .bl.blendBlueF 
frame .bl.blendAlphaF

frame .bl.fogColorF
frame .bl.fogRedF 
frame .bl.fogGreenF 
frame .bl.fogBlueF 
frame .bl.fogAlphaF

frame .bl.primDepthF -relief ridge -borderwidth 4
frame .bl.primZF
frame .bl.primDeltaZF

frame .bl.presetF -relief ridge -borderwidth 2
frame .bl.cycle0cycle1presetF
#--------------------------- bl Modes ------------------------------------

######### IMP NOTE about the bl mode bits #######################################
# the procs associated with these buttons are also called from the preset mode	#
# buttons. When they're called from there, the lines that clear and then set	#
# that particular bit in the modeword are redundant since the bit has already	#
# been set in the modeWord. This clearing and setting is only useful when the	#
# proc is called by its respective button. Any additions to this proc should	#
# be done keeping this in mind otherwise weird interactions can occur. e.g.	#
# clearing and setting the bit in both modewords can play havoc since then	#
# if we're in two cycle mode, modeword 0 should be able to have all its		#
# mode bits (except those that set muxes) to be not set. What happens in 	#
# this case is that if the modeword1 has a bit say aaEn set it propagates that 	#
# bit to modeword 0.								#
#################################################################################

checkbutton .bl.aaEnCB -width 13 -text "aaEn" -variable blAaEn -command CblAaEn
set blAaEn 0

proc CblAaEn {} {
	global fptr record blAaEn
	global blCycle0ModeWord blCycle1ModeWord AA_EN

	# set modeword based on CB selection
	set blCycle1ModeWord [expr $blCycle1ModeWord & ~($AA_EN)]
	set blCycle0ModeWord [expr $blCycle0ModeWord & ~($AA_EN)]

        if {$blAaEn == 1} {
		set blCycle1ModeWord [expr $blCycle1ModeWord | $AA_EN]
		set blCycle0ModeWord [expr $blCycle0ModeWord | $AA_EN]
	}

	if {$record == 1} {
                puts $fptr "set blAaEn $blAaEn"
		puts $fptr "CblAaEn"
        }
	callback_blCycle
	callback_send_dl
}


checkbutton .bl.zCmpEnCB -width 13 -text "zCmpEn" -variable blZcmpEn -command CblZcmpEn
#set blZcmpEn 0

proc CblZcmpEn {} {
	global fptr record blZcmpEn
	global blCycle0ModeWord blCycle1ModeWord Z_CMP

	# set modeword based on CB selection
	set blCycle1ModeWord [expr $blCycle1ModeWord & ~($Z_CMP)]
	set blCycle0ModeWord [expr $blCycle0ModeWord & ~($Z_CMP)]

        if {$blZcmpEn == 1} {
		set blCycle1ModeWord [expr $blCycle1ModeWord | $Z_CMP]
		set blCycle0ModeWord [expr $blCycle0ModeWord | $Z_CMP]
	}

	if {$record == 1} {
		puts $fptr "set blZcmpEn $blZcmpEn"
		puts $fptr "CblZcmpEn"
	}
	callback_blCycle
	callback_send_dl
}
		
checkbutton .bl.zUpdEnCB -width 13 -text "zUpdEn" -variable blZupdEn -command CblZupdEn
#set blZupdEn 0

proc CblZupdEn {} {
	global fptr record blZupdEn
	global blCycle0ModeWord blCycle1ModeWord Z_UPD

	# set modeword based on CB selection
	set blCycle1ModeWord [expr $blCycle1ModeWord & ~($Z_UPD)]
	set blCycle0ModeWord [expr $blCycle0ModeWord & ~($Z_UPD)]

        if {$blZupdEn == 1} {
		set blCycle1ModeWord [expr $blCycle1ModeWord | $Z_UPD]
		set blCycle0ModeWord [expr $blCycle0ModeWord | $Z_UPD]
	}

	if {$record == 1} {
                puts $fptr "set blZupdEn $blZupdEn"
		puts $fptr "CblZupdEn"
        }
	callback_blCycle
	callback_send_dl
}


checkbutton .bl.imRdEnCB -width 13 -text "imRdEn" -variable blImRdEn -command CblImRdEn
#set blImRdEn 0

proc CblImRdEn {} {
	global fptr record blImRdEn
	global blCycle0ModeWord blCycle1ModeWord IM_RD

	# set modeword based on CB selection
	set blCycle1ModeWord [expr $blCycle1ModeWord & ~($IM_RD)]
	set blCycle0ModeWord [expr $blCycle0ModeWord & ~($IM_RD)]

        if {$blImRdEn == 1} {
		set blCycle1ModeWord [expr $blCycle1ModeWord | $IM_RD]
		set blCycle0ModeWord [expr $blCycle0ModeWord | $IM_RD]
	}

        if {$record == 1} {
                puts $fptr "set blImRdEn $blImRdEn"
		puts $fptr "CblImRdEn"
        }
	callback_blCycle
	callback_send_dl
}


menubutton .bl.cvgDestMB -width 15 -textvariable LblCvgDest -relief  raised  \
-menu .bl.cvgDestMB.menu -bg LightGray -activebackground LightGray

menu .bl.cvgDestMB.menu 
.bl.cvgDestMB.menu add radiobutton -label "clamp" -command CblCvgDest -variable blCvgDest -value 0
.bl.cvgDestMB.menu add radiobutton -label "wrap" -command CblCvgDest -variable blCvgDest -value 1
.bl.cvgDestMB.menu add radiobutton -label "full" -command CblCvgDest -variable blCvgDest -value 2
.bl.cvgDestMB.menu add radiobutton -label "save" -command CblCvgDest -variable blCvgDest -value 3

set blCvgDest 0
set LblCvgDest clamp

proc CblCvgDest {} {
	global LblCvgDest blCvgDest
	global fptr record
	global blCycle0ModeWord blCycle1ModeWord
	global CVG_DST_MASK CVG_DST_WRAP CVG_DST_FULL CVG_DST_SAVE

	# set modeword based on CB selection
	set blCycle1ModeWord [expr $blCycle1ModeWord & ~($CVG_DST_MASK)]
	set blCycle0ModeWord [expr $blCycle0ModeWord & ~($CVG_DST_MASK)]

        switch $blCvgDest {
		1 {set blCycle1ModeWord [expr $blCycle1ModeWord | $CVG_DST_WRAP] 
		   set blCycle0ModeWord [expr $blCycle0ModeWord | $CVG_DST_WRAP] }
		2 {set blCycle1ModeWord [expr $blCycle1ModeWord | $CVG_DST_FULL]
		   set blCycle0ModeWord [expr $blCycle0ModeWord | $CVG_DST_FULL] }
		3 {set blCycle1ModeWord [expr $blCycle1ModeWord | $CVG_DST_SAVE]
		   set blCycle0ModeWord [expr $blCycle0ModeWord | $CVG_DST_SAVE] }
	}

  	switch $blCvgDest {
		0 {set LblCvgDest clamp}
		1 {set LblCvgDest wrap}
		2 {set LblCvgDest full}
		3 {set LblCvgDest save}
  	}

  	if {$record == 1} {
		puts $fptr "set blCvgDest $blCvgDest"
		puts $fptr "CblCvgDest"
  	}
	callback_blCycle
	callback_send_dl
}


checkbutton .bl.colOnCvgCB -width 13 -text "colOnCvg" -variable blColOnCvg -command CblColOnCvg

proc CblColOnCvg {} {
	global fptr record blColOnCvg
	global blCycle0ModeWord blCycle1ModeWord CLR_ON_CVG

	# set modeword based on CB selection
	set blCycle1ModeWord [expr $blCycle1ModeWord & ~($CLR_ON_CVG)]
	set blCycle0ModeWord [expr $blCycle0ModeWord & ~($CLR_ON_CVG)]

        if {$blColOnCvg == 1} {
		set blCycle1ModeWord [expr $blCycle1ModeWord | $CLR_ON_CVG]
		set blCycle0ModeWord [expr $blCycle0ModeWord | $CLR_ON_CVG]
	}

        if {$record == 1} {
                puts $fptr "set blColOnCvg $blColOnCvg"
		puts $fptr "CblColOnCvg"
        }
	callback_blCycle
	callback_send_dl
}

checkbutton .bl.cvgXalphaCB -width 13 -text "cvgXalpha" -variable blCvgXalpha -command CblCvgXalpha

proc CblCvgXalpha {} {
	global fptr record blCvgXalpha
	global blCycle0ModeWord blCycle1ModeWord CVG_X_ALPHA

	# set modeword based on CB selection
	set blCycle1ModeWord [expr $blCycle1ModeWord & ~($CVG_X_ALPHA)]
	set blCycle0ModeWord [expr $blCycle0ModeWord & ~($CVG_X_ALPHA)]

        if {$blCvgXalpha == 1} {
		set blCycle1ModeWord [expr $blCycle1ModeWord | $CVG_X_ALPHA]
		set blCycle0ModeWord [expr $blCycle0ModeWord | $CVG_X_ALPHA]
	}

	if {$record == 1} {
                puts $fptr "set blCvgXalpha $blCvgXalpha"
		puts $fptr "CblCvgXalpha"
        }
	callback_blCycle
	callback_send_dl
}

checkbutton .bl.alphaCvgSelCB -width 13 -text "alphaCvgSel" -variable blAlphaCvgSel -command CblAlphaCvgSel

proc CblAlphaCvgSel {} {
	global fptr record blAlphaCvgSel
	global blCycle0ModeWord blCycle1ModeWord ALPHA_CVG_SEL

	# set modeword based on CB selection
	set blCycle1ModeWord [expr $blCycle1ModeWord & ~($ALPHA_CVG_SEL)]
	set blCycle0ModeWord [expr $blCycle0ModeWord & ~($ALPHA_CVG_SEL)]

        if {$blAlphaCvgSel == 1} {
		set blCycle1ModeWord [expr $blCycle1ModeWord | $ALPHA_CVG_SEL]
		set blCycle0ModeWord [expr $blCycle0ModeWord | $ALPHA_CVG_SEL]
	}

	if {$record == 1} {
                puts $fptr "set blAlphaCvgSel $blAlphaCvgSel"
		puts $fptr "CblAlphaCvgSel"
        }
	callback_blCycle
	callback_send_dl
}

checkbutton .bl.forceBlendCB -width 13 -text "forceBlend" -variable blForceBlend -command CblForceBlend

proc CblForceBlend {} {
	global fptr record blForceBlend
	global blCycle0ModeWord blCycle1ModeWord FORCE_BL

	# set modeword based on CB selection
	set blCycle1ModeWord [expr $blCycle1ModeWord & ~($FORCE_BL)]
	set blCycle0ModeWord [expr $blCycle0ModeWord & ~($FORCE_BL)]

        if {$blForceBlend == 1} {
		set blCycle1ModeWord [expr $blCycle1ModeWord | $FORCE_BL]
		set blCycle0ModeWord [expr $blCycle0ModeWord | $FORCE_BL]
	}

	if {$record == 1} {
                puts $fptr "set blForceBlend $blForceBlend"
		puts $fptr "CblForceBlend"
        }
	callback_blCycle
	callback_send_dl
}

#checkbutton .bl.zModeCB -width 13 -text "zMode" -variable blZmode -command CblZmode
#
#proc CblZmode {} {
#	global fptr record blZmode
#
#	if {$record == 1} {
#                puts $fptr "set blZmode $blZmode"
#		puts $fptr "CblZmode"
#        }
#}

	

menubutton .bl.zModeMB -width 15 -textvariable LblZmode -relief  raised  \
-menu .bl.zModeMB.menu -bg LightGray -activebackground LightGray

menu .bl.zModeMB.menu 
.bl.zModeMB.menu add radiobutton -label "opaque" -command CblZmode -variable blZmode -value 0
.bl.zModeMB.menu add radiobutton -label "inter" -command CblZmode -variable blZmode -value 1
.bl.zModeMB.menu add radiobutton -label "trans" -command CblZmode -variable blZmode -value 2
.bl.zModeMB.menu add radiobutton -label "decal" -command CblZmode -variable blZmode -value 3

#set blZmode 0
#set LblZmode clamp

proc CblZmode {} {
	global LblZmode blZmode
	global fptr record
	global blCycle0ModeWord blCycle1ModeWord
	global ZMODE_MASK ZMODE_INTER ZMODE_XLU ZMODE_DEC

	# set modeword based on CB selection
	set blCycle1ModeWord [expr $blCycle1ModeWord & ~($ZMODE_MASK)]
	set blCycle0ModeWord [expr $blCycle0ModeWord & ~($ZMODE_MASK)]

        switch $blZmode {
		1 {set blCycle1ModeWord [expr $blCycle1ModeWord | $ZMODE_INTER]
		   set blCycle0ModeWord [expr $blCycle0ModeWord | $ZMODE_INTER] }
		2 {set blCycle1ModeWord [expr $blCycle1ModeWord | $ZMODE_XLU]
		   set blCycle0ModeWord [expr $blCycle0ModeWord | $ZMODE_XLU] }
		3 {set blCycle1ModeWord [expr $blCycle1ModeWord | $ZMODE_DEC]
		   set blCycle0ModeWord [expr $blCycle0ModeWord | $ZMODE_DEC] }
	}

  switch $blZmode {
	0 {set LblZmode opaque}
	1 {set LblZmode inter}
	2 {set LblZmode trans}
	3 {set LblZmode decal}
  }

  if {$record == 1} {
	puts $fptr "set blZmode $blZmode"
	puts $fptr "CblZmode"
  }
	callback_blCycle
	callback_send_dl
}


checkbutton .bl.texEdgeModeCB -width 13 -text "texEdgeMode" -variable blTexEdgeMode -command CblTexEdgeMode

proc CblTexEdgeMode {} {
	global fptr record blTexEdgeMode
	global blCycle0ModeWord blCycle1ModeWord TEX_EDGE

#        puts "Inside CblTexEdgeMode : blTexEdgeMode = $blTexEdgeMode"
	# set modeword based on CB selection
	set blCycle1ModeWord [expr $blCycle1ModeWord & ~($TEX_EDGE)]
	set blCycle0ModeWord [expr $blCycle0ModeWord & ~($TEX_EDGE)]

        if {$blTexEdgeMode == 1} {
		set blCycle1ModeWord [expr $blCycle1ModeWord | $TEX_EDGE]
		set blCycle0ModeWord [expr $blCycle0ModeWord | $TEX_EDGE]
	}
	
	if {$record == 1} {
                puts $fptr "set blTexEdgeMode $blTexEdgeMode"
		puts $fptr "CblTexEdgeMode"
        }
	callback_blCycle
	callback_send_dl
}

checkbutton .bl.alphaCompEnCB -width 13 -text "alphaCompEn" -variable blAlphaCompEn -command CblAlphaCompEn

proc CblAlphaCompEn {} {
	global fptr record blAlphaCompEn
	global blCycle0ModeWord blCycle1ModeWord A_CMP_EN

	# set modeword based on CB selection
	set blCycle1ModeWord [expr $blCycle1ModeWord & ~($A_CMP_EN)]
	set blCycle0ModeWord [expr $blCycle0ModeWord & ~($A_CMP_EN)]

        if {$blAlphaCompEn == 1} {
		set blCycle1ModeWord [expr $blCycle1ModeWord | $A_CMP_EN]
		set blCycle0ModeWord [expr $blCycle0ModeWord | $A_CMP_EN]
	}
	
	 if {$record == 1} {
                puts $fptr "set blAlphaCompEn $blAlphaCompEn"
		puts $fptr "CblAlphaCompEn"
        }
	callback_blCycle
	callback_send_dl
}

checkbutton .bl.dithAlphaEnCB -width 13 -text "dithAlphaEn" -variable blDithAlphaEn -command CblDithAlphaEn

proc CblDithAlphaEn {} {
	global fptr record blDithAlphaEn
	global blCycle0ModeWord blCycle1ModeWord A_DITH_EN

	# set modeword based on CB selection
	set blCycle1ModeWord [expr $blCycle1ModeWord & ~($A_DITH_EN)]
	set blCycle0ModeWord [expr $blCycle0ModeWord & ~($A_DITH_EN)]

        if {$blDithAlphaEn == 1} {
		set blCycle1ModeWord [expr $blCycle1ModeWord | $A_DITH_EN]
		set blCycle0ModeWord [expr $blCycle0ModeWord | $A_DITH_EN]
	}
	
	if {$record == 1} {
                puts $fptr "set blDithAlphaEn $blDithAlphaEn"
		puts $fptr "CblDithAlphaEn"
        }
	callback_blCycle
	callback_send_dl
}

checkbutton .bl.zSrcSelCB -width 13 -textvariable LzSrcSel -variable blZsrcSel -command CblZsrcSel

proc CblZsrcSel {} {
	global fptr record blZsrcSel LzSrcSel
	global blCycle0ModeWord blCycle1ModeWord Z_SRC_SEL

	# set modeword based on CB selection
	set blCycle1ModeWord [expr $blCycle1ModeWord & ~($Z_SRC_SEL)]
	set blCycle0ModeWord [expr $blCycle0ModeWord & ~($Z_SRC_SEL)]

        if {$blZsrcSel == 1} {
		set blCycle1ModeWord [expr $blCycle1ModeWord | $Z_SRC_SEL]
		set blCycle0ModeWord [expr $blCycle0ModeWord | $Z_SRC_SEL]
	}
	
        if {$blZsrcSel == 1} {
		set LzSrcSel "zSrcPrim"
	} else {
		set LzSrcSel "zSrcPixel"
	}

	if {$record == 1} {
                puts $fptr "set blZsrcSel $blZsrcSel"
		puts $fptr "CblZsrcSel"
        }
	callback_blCycle
	callback_send_dl
}
#--------------------------dither Modes--------------------------------------
label .bl.alphaDitherL -text "alphaDither"
menubutton .bl.alphaDitherMB -textvariable LblAlphaDither -width 9 -relief raised -menu .bl.alphaDitherMB.menu -bg LightGray -activebackground LightGray
menu .bl.alphaDitherMB.menu
.bl.alphaDitherMB.menu add radiobutton -label "pattern" -command CalphaDither -variable blAlphaDither -value 0
.bl.alphaDitherMB.menu add radiobutton -label "~pattern" -command CalphaDither -variable blAlphaDither -value 1
.bl.alphaDitherMB.menu add radiobutton -label "Noise" -command CalphaDither -variable blAlphaDither -value 2
.bl.alphaDitherMB.menu add radiobutton -label "Off" -command CalphaDither -variable blAlphaDither -value 3

proc CalphaDither {} {
	global fptr record
	global LblAlphaDither dPattern
	global blAlphaDither

	switch $blAlphaDither {
		0 {set LblAlphaDither $dPattern }
		1 {set LblAlphaDither "~ $dPattern" }
		2 {set LblAlphaDither "noise" }
		3 {set LblAlphaDither "Off" }
	}

	if {$record == 1} {
                puts $fptr "set blAlphaDither $blAlphaDither"
                puts $fptr "CalphaDither"
        }

	callback_blAlphaDither
	callback_send_dl
}



label .bl.rgbDitherL -text "rgbDither"
menubutton .bl.rgbDitherMB -textvariable LblRgbDither -width 9 -relief raised -menu .bl.rgbDitherMB.menu -bg LightGray -activebackground LightGray
menu .bl.rgbDitherMB.menu
.bl.rgbDitherMB.menu add radiobutton -label "MagicSq" -command CrgbDither -variable blRgbDither -value 0
.bl.rgbDitherMB.menu add radiobutton -label "Bayer" -command CrgbDither -variable blRgbDither -value 1
.bl.rgbDitherMB.menu add radiobutton -label "Noise" -command CrgbDither -variable blRgbDither -value 2
.bl.rgbDitherMB.menu add radiobutton -label "Off" -command CrgbDither -variable blRgbDither -value 3

proc CrgbDither {} {
	global fptr record
	global LblRgbDither LblAlphaDither
	global blRgbDither blAlphaDither dPattern

	switch $blRgbDither {
		0 {set LblRgbDither "MagicSq" 
		   set dPattern "MagicSq" }

		1 {set LblRgbDither "Bayer" 
		   set dPattern "Bayer" }

		2 {set LblRgbDither "Noise"
		   set dPattern "MagicSq" }

		3 {set LblRgbDither "Off"
		   set dPattern "Bayer" }
	}

	CalphaDither

	if {$record == 1} {
                puts $fptr "set blRgbDither $blRgbDither"
                puts $fptr "set blAlphaDither $blAlphaDither"
                puts $fptr "CrgbDither"
        }

	callback_blRgbDither
	callback_send_dl
}



label .bl.videoAAFilterL -text "vidDithFilt"
checkbutton .bl.videoAAFilterCB -width 9 -text "vidAAFilt" -variable blVideoAAFilter -command CblVideoAAFilter

proc CblVideoAAFilter {} {
  global blVideoAAFilter
  global spindso fptr record

  if {$blVideoAAFilter == 0}  {
	$spindso call SpinTclModel 104
  } else { 
    if {$blVideoAAFilter == 1}  {
	$spindso call SpinTclModel 105
    }
  }
  if {$record == 1} {
	if {$blVideoAAFilter == 0} {
	  puts $fptr "$spindso call SpinTclModel 104"
	  puts $fptr "set blVideoAAFilter 0"
	} else {
	  if {$blVideoAAFilter == 1} {
	    puts $fptr "$spindso call SpinTclModel 105"
	    puts $fptr "set blVideoAAFilter 1"
          }
	}
  }
}

label .bl.videoDitherFilterL -text "vidDithFilt"
checkbutton .bl.videoDitherFilterCB -width 10 -text "vidDithFilt" -variable blVideoDitherFilter -command CblVideoDitherFilter

proc CblVideoDitherFilter {} {
  global blVideoDitherFilter
  global spindso fptr record

  if {$blVideoDitherFilter == 0}  {
	$spindso call SpinTclModel 100
  } else { 
    if {$blVideoDitherFilter == 1}  {
	$spindso call SpinTclModel 101
    }
  }

  if {$record == 1} {
	if {$blVideoDitherFilter == 0} {
	  puts $fptr "$spindso call SpinTclModel 100"
	  puts $fptr "set blVideoDitherFilter 0"
	} else {
	  if {$blVideoDitherFilter == 1} {
	    puts $fptr "$spindso call SpinTclModel 101"
	    puts $fptr "set blVideoDitherFilter 1"
          }
	}
  }
}


label .bl.frameBufferSizeL -text "cfbSize"
checkbutton .bl.frameBufferSizeCB -width 9 -text "cfbSize32" -variable blFrameBufferSize -command CblFrameBufferSize

proc CblFrameBufferSize {} {
  global blFrameBufferSize
  global blRgbDither blAlphaDither blVideoDitherFilter
  global spindso fptr record

  if {$blFrameBufferSize == 0}  {
	set blRgbDither 1
	CrgbDither
	set blAlphaDither 1
	CalphaDither
	set blVideoDitherFilter 1
	CblVideoDitherFilter
	$spindso call SpinTclModel 102
	if {$record == 1} {
		puts $fptr "set blRgbDither 1"
		puts $fptr "CrgbDither"
		puts $fptr "set blAlphaDither 1"
		puts $fptr "CalphaDither"
		puts $fptr "set blVideoDitherFilter 1"
		puts $fptr "CblVideoDitherFilter"
		puts $fptr "$spindso call SpinTclModel 102"
		puts $fptr "set blFrameBufferSize 0"
	}
	
  } else { 
    if {$blFrameBufferSize == 1}  {
	set blRgbDither 3
	CrgbDither
	set blAlphaDither 3
	CalphaDither
	set blVideoDitherFilter 0
	CblVideoDitherFilter
	$spindso call SpinTclModel 103
	if {$record == 1} {
		puts $fptr "set blRgbDither 3"
		puts $fptr "CrgbDither"
		puts $fptr "set blAlphaDither 3"
		puts $fptr "CalphaDither"
		puts $fptr "set blVideoDitherFilter 0"
		puts $fptr "CblVideoDitherFilter"
		puts $fptr "$spindso call SpinTclModel 103"
		puts $fptr "set blFrameBufferSize 1"
	}
    }
  }
}

set blFrameBufferSize 0
CblFrameBufferSize
#--------------------------Blend Color--------------------------------------

checkbutton .bl.fbShiftL -width 15 -text "frameBuf shift " -variable fbShiftEnable -command fbShiftEnableProc
entry .bl.fbShiftE -width 3 -relief sunken -textvariable fbShift

proc fbShiftEnableProc {} {
    global fbShiftEnable
    global spindso fptr record

  if {$fbShiftEnable == 0}  {
	$spindso call SpinTclModel 118
  } else { 
    if {$fbShiftEnable == 1}  {
	$spindso call SpinTclModel 119
    }
  }
  if {$record == 1} {
	if {$fbShiftEnable == 0} {
	  puts $fptr "$spindso call SpinTclModel 118"
	  puts $fptr "set fbShiftEnable 0"
	} else {
	  if {$fbShiftEnable == 1} {
	    puts $fptr "$spindso call SpinTclModel 119"
	    puts $fptr "set fbShiftEnable 1"
          }
	}
  }

}

set fbShift 0

proc CblfbShift value {
	global fbShift fptr
	set blBlendColorRed $value
	if {$record == 1} {
		puts $fptr ".bl.blendColorRedS set $blBlendColorRed"
	}

	callback_blBlendColor
	callback_send_dl
}

bind .bl.fbShiftE <Return> {
 if {$fbShift > 255} {set fbShift 255}
 if {$fbShift < 0} {set fbShift 0}
	if {$record == 1} {
                puts $fptr "set fbShift $fbShift"
		puts $fptr "$spindso call SpinTclModel [expr $fbShift + 110]"
        }
	$spindso call SpinTclModel [expr $fbShift + 110]
	focus none
}



label .bl.blendColorL -width 11 -text "Blend Color"

scale .bl.blendColorRedS -label Red -from 0 -to 255 -length 181 -orient horizontal -command CblBlendColorRed

entry .bl.blendColorRedE -width 3 -relief sunken -textvariable blBlendColorRed
bind .bl.blendColorRedE <Return> {
	if {$blBlendColorRed > 255} {set blBlendColorRed 255}
	if {$blBlendColorRed < 0} {set blBlendColorRed 0}
	.bl.blendColorRedS set $blBlendColorRed
	focus none
}

#.bl.blendColorRedS set 128

proc CblBlendColorRed value {
	global blBlendColorRed
	global fptr record
	set blBlendColorRed $value
	if {$record == 1} {
		puts $fptr ".bl.blendColorRedS set $blBlendColorRed"
	}
	callback_blBlendColor
	callback_send_dl
}

scale .bl.blendColorBlueS -label Blue -from 0 -to 255 -length 181 -orient horizontal -command CblBlendColorBlue

entry .bl.blendColorBlueE -width 3 -relief sunken -textvariable blBlendColorBlue
bind .bl.blendColorBlueE <Return> {
	if {$blBlendColorBlue > 255} {set blBlendColorBlue 255}
	if {$blBlendColorBlue < 0} {set blBlendColorBlue 0}
	.bl.blendColorBlueS set $blBlendColorBlue
	focus none
}
#.bl.blendColorBlueS set 128

proc CblBlendColorBlue value {
	global blBlendColorBlue
	global fptr record
	set blBlendColorBlue $value
	if {$record == 1} {
		puts $fptr ".bl.blendColorBlueS set $blBlendColorBlue"
	}
	callback_blBlendColor
	callback_send_dl
}

scale .bl.blendColorAlphaS -label Alpha -from 0 -to 255 -length 181 -orient horizontal -command CblBlendColorAlpha

entry .bl.blendColorAlphaE -width 3 -relief sunken -textvariable blBlendColorAlpha
bind .bl.blendColorAlphaE <Return> {
	if {$blBlendColorAlpha > 255} {set blBlendColorAlpha 255}
	if {$blBlendColorAlpha < 0} {set blBlendColorAlpha 0}
	.bl.blendColorAlphaS set $blBlendColorAlpha
	focus none
}
#.bl.blendColorAlphaS set 128

proc CblBlendColorAlpha value {
	global blBlendColorAlpha
	global fptr record
	set blBlendColorAlpha $value
	if {$record == 1} {
		puts $fptr ".bl.blendColorAlphaS set $blBlendColorAlpha"
	}
	callback_blBlendColor
	callback_send_dl
}

scale .bl.blendColorGreenS -label Green -from 0 -to 255 -length 181 -orient horizontal -command CblBlendColorGreen

entry .bl.blendColorGreenE -width 3 -relief sunken -textvariable blBlendColorGreen
bind .bl.blendColorGreenE <Return> {
	if {$blBlendColorGreen > 255} {set blBlendColorGreen 255}
	if {$blBlendColorGreen < 0} {set blBlendColorGreen 0}
	.bl.blendColorGreenS set $blBlendColorGreen
	focus none
}
#.bl.blendColorGreenS set 128

proc CblBlendColorGreen value {
	global blBlendColorGreen
	global fptr record
	set blBlendColorGreen $value
	if {$record == 1} {
		puts $fptr ".bl.blendColorGreenS set $blBlendColorGreen"
	}
	callback_blBlendColor
	callback_send_dl
}
#---------------------------Fog Color------------------------------------
label .bl.fogColorL -width 11 -text "Fog Color"

scale .bl.fogColorRedS -label Red -from 0 -to 255 -length 181 -orient horizontal -command CblFogColorRed

entry .bl.fogColorRedE -width 3 -relief sunken -textvariable blFogColorRed
bind .bl.fogColorRedE <Return> {
	if {$blFogColorRed > 255} {set blFogColorRed 255}
	if {$blFogColorRed < 0} {set blFogColorRed 0}
	.bl.fogColorRedS set $blFogColorRed
	focus none
}

#.bl.fogColorRedS set 128

proc CblFogColorRed value {
	global blFogColorRed
	global fptr record
	set blFogColorRed $value
	if {$record == 1} {
		puts $fptr ".bl.fogColorRedS set $blFogColorRed"
	}
	callback_blFogColor
	callback_send_dl
}

scale .bl.fogColorBlueS -label Blue -from 0 -to 255 -length 181 -orient horizontal -command CblFogColorBlue

entry .bl.fogColorBlueE -width 3 -relief sunken -textvariable blFogColorBlue
bind .bl.fogColorBlueE <Return> {
	if {$blFogColorBlue > 255} {set blFogColorBlue 255}
	if {$blFogColorBlue < 0} {set blFogColorBlue 0}
	.bl.fogColorBlueS set $blFogColorBlue
	focus none
}
#.bl.fogColorBlueS set 128

proc CblFogColorBlue value {
	global blFogColorBlue
	global fptr record
	set blFogColorBlue $value
	if {$record == 1} {
		puts $fptr ".bl.fogColorBlueS set $blFogColorBlue"
	}
	callback_blFogColor
	callback_send_dl
}

scale .bl.fogColorAlphaS -label Alpha -from 0 -to 255 -length 181 -orient horizontal -command CblFogColorAlpha

entry .bl.fogColorAlphaE -width 3 -relief sunken -textvariable blFogColorAlpha
bind .bl.fogColorAlphaE <Return> {
	if {$blFogColorAlpha > 255} {set blFogColorAlpha 255}
	if {$blFogColorAlpha < 0} {set blFogColorAlpha 0}
	.bl.fogColorAlphaS set $blFogColorAlpha
	focus none
}
#.bl.fogColorAlphaS set 128

proc CblFogColorAlpha value {
	global blFogColorAlpha
	global fptr record
	set blFogColorAlpha $value
	if {$record == 1} {
		puts $fptr ".bl.fogColorAlphaS set $blFogColorAlpha"
	}
	callback_blFogColor
	callback_send_dl
}

scale .bl.fogColorGreenS -label Green -from 0 -to 255 -length 181 -orient horizontal -command CblFogColorGreen

entry .bl.fogColorGreenE -width 3 -relief sunken -textvariable blFogColorGreen
bind .bl.fogColorGreenE <Return> {
	if {$blFogColorGreen > 255} {set blFogColorGreen 255}
	if {$blFogColorGreen < 0} {set blFogColorGreen 0}
	.bl.fogColorGreenS set $blFogColorGreen
	focus none
}
#.bl.fogColorGreenS set 128

proc CblFogColorGreen value {
	global blFogColorGreen
	global fptr record
	set blFogColorGreen $value
	if {$record == 1} {
		puts $fptr ".bl.fogColorGreenS set $blFogColorGreen"
	}
	callback_blFogColor
	callback_send_dl
}

#---------------------------Z delta Z ----------------------------------------
label .bl.primZL -width 11 -text "Prim Depth"

scale .bl.primZS -label Z -from 0 -to 65535 -length 393 -orient horizontal -command CblPrimZ

entry .bl.primZE -width 6 -relief sunken -textvariable blPrimZ
bind .bl.primZE <Return> {
        if {$blPrimZ > 65535} {set blPrimZ 65535}
        if {$blPrimZ < 0} {set blPrimZ 0}
        .bl.primZS set $blPrimZ
        focus none
}

proc CblPrimZ value {
        global blPrimZ
        global fptr record
        set blPrimZ $value
        if {$record == 1} {
                puts $fptr ".bl.primZS set $blPrimZ"
        }
        callback_blPrim
        callback_send_dl
}

label .bl.primDeltaZL -width 11 -text "Prim Depth"

scale .bl.primDeltaZS -label "delta Z" -from 0 -to 65535 -length 393 -orient horizontal -command CblPrimDeltaZ

entry .bl.primDeltaZE -width 6 -relief sunken -textvariable blPrimDeltaZ
bind .bl.primDeltaZE <Return> {
        if {$blPrimDeltaZ > 65535} {set blPrimDeltaZ 65535}
        if {$blPrimDeltaZ < 0} {set blPrimDeltaZ 0}
        .bl.primDeltaZS set $blPrimDeltaZ
        focus none
}

proc CblPrimDeltaZ value {
        global blPrimDeltaZ
        global fptr record
        set blPrimDeltaZ $value
        if {$record == 1} {
                puts $fptr ".bl.primDeltaZS set $blPrimDeltaZ"
        }
        callback_blPrim
        callback_send_dl
}



#---------------------------BL Muxes--------------------------------------
#---------------------------Utility functions-----------------------------
set M1A1_SH 30
set M1B1_SH 26 
set M2A1_SH 22
set M2B1_SH 18

set M1A2_SH 28
set M1B2_SH 24 
set M2A2_SH 20
set M2B2_SH 16

set AA_EN           0x8
set Z_CMP           0x10
set Z_UPD           0x20
set IM_RD           0x40
set CLR_ON_CVG      0x80
set CVG_DST_CLAMP   0
set CVG_DST_WRAP    0x100
set CVG_DST_FULL    0x200
set CVG_DST_SAVE    0x300
set CVG_DST_MASK    0x300
set CVG_DST_SH      8
set ZMODE_OPA       0
set ZMODE_INTER     0x400
set ZMODE_XLU       0x800
set ZMODE_DEC       0xc00
set ZMODE_MASK      0xc00
set ZMODE_SH	    10
set CVG_X_ALPHA     0x1000
set ALPHA_CVG_SEL   0x2000
set FORCE_BL        0x4000
set TEX_EDGE        0x8000
set A_CMP_EN	    0x0001
set A_DITH_EN 	    0x0002
set Z_SRC_SEL 	    0x0004


proc getBLcolorLabelA val {
  switch $val {
	0 {return "Bl/Pix Color"}
	1 {return "Mem Color"}
	2 {return "Blend Color"}
	3 {return "Fog Color"}
  }
}

proc getBLcolorLabelB val {
  switch $val {
	0 {return "Pixel Alpha"}
	1 {return "Prim Alpha"}
	2 {return "Shade Alpha"}
 	3 {return "0.0"}
  }
}

proc getBLcolorLabelC val {
  switch $val {
	0 {return "Bl/Pix Color"}
	1 {return "Mem Color"}
	2 {return "Blend Color"}
	3 {return "Fog Color"}
  }
}

proc getBLcolorLabelD val {
  switch $val {
	0 {return "1.0 - A"}
	1 {return "Mem Alpha"}
 	2 {return "1.0"}
 	3 {return "0.0"}
  }
}

label .bl.cycle0ColorL -width 11 -text "Cycle0 Blend"

label .bl.cycle0ColorL( -width 5 -text "=   ("

menubutton .bl.cycle0ColorAMB -textvariable LblCycle0ColorA -width 12 \
-relief  raised -menu .bl.cycle0ColorAMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .bl.cycle0ColorAMB.menu
.bl.cycle0ColorAMB.menu add radiobutton -label "Blend/Pix Color" -command CblCycle0ColorA  -variable blCycle0ColorA -value 0
.bl.cycle0ColorAMB.menu add radiobutton -label "Mem Color" -command CblCycle0ColorA -variable blCycle0ColorA -value 1
.bl.cycle0ColorAMB.menu add radiobutton -label "Blend Color" -command CblCycle0ColorA -variable blCycle0ColorA -value 2
.bl.cycle0ColorAMB.menu add radiobutton -label "Fog Color" -command CblCycle0ColorA -variable blCycle0ColorA -value 3

#set blCycle0ColorA 2
#set LblCycle0ColorA "Tex1 Color"

proc CblCycle0ColorA {} {
     global LblCycle0ColorA blCycle0ColorA
     global fptr record
     global blCycle0ModeWord
     global M1A1_SH
     global rspCycleType blCycle1ColorA

     set blCycle0ModeWord [expr $blCycle0ModeWord & ~(3 << $M1A1_SH)]
     set blCycle0ModeWord [expr $blCycle0ModeWord | ($blCycle0ColorA << $M1A1_SH)]

     set LblCycle0ColorA  [getBLcolorLabelA $blCycle0ColorA]

     if {$record == 1} {
	puts $fptr "set blCycle0ColorA $blCycle0ColorA"
	puts $fptr "CblCycle0ColorA"
     }
    
     if {$rspCycleType == 0} {
	set blCycle1ColorA $blCycle0ColorA
	CblCycle1ColorA
     }
	
	callback_blCycle
	callback_send_dl
}


label .bl.cycle0ColorLX1 -width 1 -text "X"
label .bl.cycle0ColorLX2 -width 1 -text "X"

menubutton .bl.cycle0ColorBMB -textvariable LblCycle0ColorB -width 12 \
-relief  raised -menu .bl.cycle0ColorBMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .bl.cycle0ColorBMB.menu
.bl.cycle0ColorBMB.menu add radiobutton -label "Pixel Alpha" -command CblCycle0ColorB -variable blCycle0ColorB -value 0
.bl.cycle0ColorBMB.menu add radiobutton -label "Prim Alpha" -command CblCycle0ColorB -variable blCycle0ColorB -value 1
.bl.cycle0ColorBMB.menu add radiobutton -label "Shade Alpha" -command CblCycle0ColorB -variable blCycle0ColorB -value 2
.bl.cycle0ColorBMB.menu add radiobutton -label "0.0" -command CblCycle0ColorB -variable blCycle0ColorB -value 3

#set blCycle0ColorB "Tex0 Color"
#set LblCycle0ColorB "Tex0 Color"

proc CblCycle0ColorB {} {
     global LblCycle0ColorB blCycle0ColorB
     global fptr record
     global blCycle0ModeWord M1B1_SH
     global rspCycleType blCycle1ColorB

     set blCycle0ModeWord [expr $blCycle0ModeWord & ~(3 << $M1B1_SH)]
     set blCycle0ModeWord [expr $blCycle0ModeWord | ($blCycle0ColorB << $M1B1_SH)]

     set LblCycle0ColorB  [getBLcolorLabelB $blCycle0ColorB]

     if {$record == 1} {
	puts $fptr "set blCycle0ColorB $blCycle0ColorB"
	puts $fptr "CblCycle0ColorB"
     }
     if {$rspCycleType == 0} {
	set blCycle1ColorB $blCycle0ColorB
	CblCycle1ColorB
     }
	callback_blCycle
	callback_send_dl
}

label .bl.cycle0ColorL+ -width 1 -text "+"

menubutton .bl.cycle0ColorCMB -textvariable LblCycle0ColorC -width 12 \
-relief  raised -menu .bl.cycle0ColorCMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .bl.cycle0ColorCMB.menu
.bl.cycle0ColorCMB.menu add radiobutton -label "Blend/Pix Color" -command CblCycle0ColorC -variable blCycle0ColorC -value 0
.bl.cycle0ColorCMB.menu add radiobutton -label "Mem Color" -command CblCycle0ColorC -variable blCycle0ColorC -value 1
.bl.cycle0ColorCMB.menu add radiobutton -label "Blend Color" -command CblCycle0ColorC -variable blCycle0ColorC -value 2
.bl.cycle0ColorCMB.menu add radiobutton -label "Fog Color" -command CblCycle0ColorC -variable blCycle0ColorC -value 3

#set blCycle0ColorC 13
#set LblCycle0ColorC "LOD Frac"

proc CblCycle0ColorC {} {
     global LblCycle0ColorC blCycle0ColorC
     global fptr record
     global blCycle0ModeWord M2A1_SH
     global rspCycleType blCycle1ColorC

     set blCycle0ModeWord [expr $blCycle0ModeWord & ~(3 << $M2A1_SH)]
     set blCycle0ModeWord [expr $blCycle0ModeWord | ($blCycle0ColorC << $M2A1_SH)]

     set LblCycle0ColorC  [getBLcolorLabelC $blCycle0ColorC]

     if {$record == 1} {
	puts $fptr "set blCycle0ColorC $blCycle0ColorC"
	puts $fptr "CblCycle0ColorC"
     }

     if {$rspCycleType == 0} {
	set blCycle1ColorC $blCycle0ColorC
	CblCycle1ColorC
     }

	callback_blCycle
	callback_send_dl
}

label .bl.cycle0ColorL) -width 5 -text ") / ("

menubutton .bl.cycle0ColorDMB -textvariable LblCycle0ColorD -width 12 \
-relief  raised -menu .bl.cycle0ColorDMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .bl.cycle0ColorDMB.menu
.bl.cycle0ColorDMB.menu add radiobutton -label "1.0 - A" -command CblCycle0ColorD -variable blCycle0ColorD -value 0
.bl.cycle0ColorDMB.menu add radiobutton -label "Mem Alpha" -command CblCycle0ColorD -variable blCycle0ColorD -value 1
.bl.cycle0ColorDMB.menu add radiobutton -label "1.0" -command CblCycle0ColorD -variable blCycle0ColorD -value 2
.bl.cycle0ColorDMB.menu add radiobutton -label "0.0" -command CblCycle0ColorD -variable blCycle0ColorD -value 3

#set blCycle0ColorD 1
#set LblCycle0ColorD "Tex0 Color"

proc CblCycle0ColorD {} {
     global LblCycle0ColorD blCycle0ColorD
     global fptr record
     global blCycle0ModeWord M2B1_SH
     global rspCycleType blCycle1ColorD

     set blCycle0ModeWord [expr $blCycle0ModeWord & ~(3 << $M2B1_SH)]
     set blCycle0ModeWord [expr $blCycle0ModeWord | ($blCycle0ColorD << $M2B1_SH)]

     set LblCycle0ColorD  [getBLcolorLabelD $blCycle0ColorD]

     if {$record == 1} {
	puts $fptr "set blCycle0ColorD $blCycle0ColorD"
	puts $fptr "CblCycle0ColorD"
     }

     if {$rspCycleType == 0} {
	set blCycle1ColorD $blCycle0ColorD
	CblCycle1ColorD
     }
	callback_blCycle
	callback_send_dl
}

label .bl.cycle0ColorL1+ -width 1 -text "+"
label .bl.cycle0ColorL1) -width 1 -text ")"

label .bl.cycle0ColorBL -width 11 -textvariable LblCycle0ColorB
label .bl.cycle0ColorDL -width 11 -textvariable LblCycle0ColorD

#---------------------------------------------------------------------------#
label .bl.cycle1ColorL -width 11 -text "Cycle1 Blend"

label .bl.cycle1ColorL( -width 5 -text "=   ("

menubutton .bl.cycle1ColorAMB -textvariable LblCycle1ColorA -width 12 \
-relief  raised -menu .bl.cycle1ColorAMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .bl.cycle1ColorAMB.menu
.bl.cycle1ColorAMB.menu add radiobutton -label "Blend/Pix Color" -command CblCycle1ColorA  -variable blCycle1ColorA -value 0
.bl.cycle1ColorAMB.menu add radiobutton -label "Mem Color" -command CblCycle1ColorA -variable blCycle1ColorA -value 1
.bl.cycle1ColorAMB.menu add radiobutton -label "Blend Color" -command CblCycle1ColorA -variable blCycle1ColorA -value 2
.bl.cycle1ColorAMB.menu add radiobutton -label "Fog Color" -command CblCycle1ColorA -variable blCycle1ColorA -value 3

#set blCycle1ColorA 2
#set LblCycle1ColorA "Tex1 Color"

proc CblCycle1ColorA {} {
     global LblCycle1ColorA blCycle1ColorA
     global fptr record
     global blCycle1ModeWord M1A2_SH

     set blCycle1ModeWord [expr $blCycle1ModeWord & ~(3 << $M1A2_SH)]
     set blCycle1ModeWord [expr $blCycle1ModeWord | ($blCycle1ColorA << $M1A2_SH)]

     set LblCycle1ColorA  [getBLcolorLabelA $blCycle1ColorA]

     if {$record == 1} {
	puts $fptr "set blCycle1ColorA $blCycle1ColorA"
	puts $fptr "CblCycle1ColorA"
     }
	callback_blCycle
	callback_send_dl
}


label .bl.cycle1ColorLX1 -width 1 -text "X"
label .bl.cycle1ColorLX2 -width 1 -text "X"

menubutton .bl.cycle1ColorBMB -textvariable LblCycle1ColorB -width 12 \
-relief  raised -menu .bl.cycle1ColorBMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .bl.cycle1ColorBMB.menu
.bl.cycle1ColorBMB.menu add radiobutton -label "Pixel Alpha" -command CblCycle1ColorB -variable blCycle1ColorB -value 0
.bl.cycle1ColorBMB.menu add radiobutton -label "Prim Alpha" -command CblCycle1ColorB -variable blCycle1ColorB -value 1
.bl.cycle1ColorBMB.menu add radiobutton -label "Shade Alpha" -command CblCycle1ColorB -variable blCycle1ColorB -value 2
.bl.cycle1ColorBMB.menu add radiobutton -label "0.0" -command CblCycle1ColorB -variable blCycle1ColorB -value 3

#set blCycle1ColorB "Tex0 Color"
#set LblCycle1ColorB "Tex0 Color"

proc CblCycle1ColorB {} {
     global LblCycle1ColorB blCycle1ColorB
     global fptr record
     global blCycle1ModeWord M1B2_SH

     set blCycle1ModeWord [expr $blCycle1ModeWord & ~(3 << $M1B2_SH)]
     set blCycle1ModeWord [expr $blCycle1ModeWord | ($blCycle1ColorB << $M1B2_SH)]
     set LblCycle1ColorB  [getBLcolorLabelB $blCycle1ColorB]
     if {$record == 1} {
	puts $fptr "set blCycle1ColorB $blCycle1ColorB"
	puts $fptr "CblCycle1ColorB"
     }
	callback_blCycle
	callback_send_dl
}

label .bl.cycle1ColorL+ -width 1 -text "+"

menubutton .bl.cycle1ColorCMB -textvariable LblCycle1ColorC -width 12 \
-relief  raised -menu .bl.cycle1ColorCMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .bl.cycle1ColorCMB.menu
.bl.cycle1ColorCMB.menu add radiobutton -label "Blend/Pix Color" -command CblCycle1ColorC -variable blCycle1ColorC -value 0
.bl.cycle1ColorCMB.menu add radiobutton -label "Mem Color" -command CblCycle1ColorC -variable blCycle1ColorC -value 1
.bl.cycle1ColorCMB.menu add radiobutton -label "Blend Color" -command CblCycle1ColorC -variable blCycle1ColorC -value 2
.bl.cycle1ColorCMB.menu add radiobutton -label "Fog Color" -command CblCycle1ColorC -variable blCycle1ColorC -value 3

#set blCycle1ColorC 13
#set LblCycle1ColorC "LOD Frac"

proc CblCycle1ColorC {} {
     global LblCycle1ColorC blCycle1ColorC
     global fptr record
     global blCycle1ModeWord M2A2_SH

     set blCycle1ModeWord [expr $blCycle1ModeWord & ~(3 << $M2A2_SH)]
     set blCycle1ModeWord [expr $blCycle1ModeWord | ($blCycle1ColorC << $M2A2_SH)]

     set LblCycle1ColorC  [getBLcolorLabelC $blCycle1ColorC]

     if {$record == 1} {
	puts $fptr "set blCycle1ColorC $blCycle1ColorC"
	puts $fptr "CblCycle1ColorC"
     }
	callback_blCycle
	callback_send_dl
}

label .bl.cycle1ColorL) -width 5 -text ") / ("

menubutton .bl.cycle1ColorDMB -textvariable LblCycle1ColorD -width 12 \
-relief  raised -menu .bl.cycle1ColorDMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .bl.cycle1ColorDMB.menu
.bl.cycle1ColorDMB.menu add radiobutton -label "1.0 - A" -command CblCycle1ColorD -variable blCycle1ColorD -value 0
.bl.cycle1ColorDMB.menu add radiobutton -label "Mem Alpha" -command CblCycle1ColorD -variable blCycle1ColorD -value 1
.bl.cycle1ColorDMB.menu add radiobutton -label "1.0" -command CblCycle1ColorD -variable blCycle1ColorD -value 2
.bl.cycle1ColorDMB.menu add radiobutton -label "0.0" -command CblCycle1ColorD -variable blCycle1ColorD -value 3

#set blCycle1ColorD 1
#set LblCycle1ColorD "Tex0 Color"

proc CblCycle1ColorD {} {
     global LblCycle1ColorD blCycle1ColorD
     global fptr record
     global blCycle1ModeWord M2B2_SH

     set blCycle1ModeWord [expr $blCycle1ModeWord & ~(3 << $M2B2_SH)]
     set blCycle1ModeWord [expr $blCycle1ModeWord | ($blCycle1ColorD << $M2B2_SH)]

     set LblCycle1ColorD  [getBLcolorLabelD $blCycle1ColorD]

     if {$record == 1} {
	puts $fptr "set blCycle1ColorD $blCycle1ColorD"
	puts $fptr "CblCycle1ColorD"
     }
	callback_blCycle
	callback_send_dl
}

label .bl.cycle1ColorL1+ -width 1 -text "+"
label .bl.cycle1ColorL1) -width 1 -text ")"

label .bl.cycle1ColorBL -width 11 -textvariable LblCycle1ColorB
label .bl.cycle1ColorDL -width 11 -textvariable LblCycle1ColorD

#--------------------preset modes-------------------------------------------------

set file blModes0
set fptr [open $file r]

while  {[gets $fptr line] >= 0} {
	lappend blCycle0ModeList [expr $line]
}

set file blModes1
set fptr [open $file r]

while  {[gets $fptr line] >= 0} {
	lappend blCycle1ModeList [expr $line]
}

set blCycle0presetColorA {0 1 2 3 4 5}
set blCycle0presetColorB {0 1 2 3 4 5}
set blCycle0presetColorC {0 1 2 3 4 5}
set blCycle0presetColorD {0 1 2 3 4 5}

set blCycle1presetColorA {0 1 2 3 4 5}
set blCycle1presetColorB {0 1 2 3 4 5}
set blCycle1presetColorC {0 1 2 3 4 5}
set blCycle1presetColorD {0 1 2 3 4 5}

proc get_blCycle0presetLabel val {
  switch $val {
	0 {return AA_ZB_OPA_SURF}
	1 {return AA_ZB_XLU_SURF}
	2 {return AA_ZB_OPA_DECAL}
	3 {return AA_ZB_XLU_DECAL}
	4 {return AA_ZB_OPA_INTER}
	5 {return AA_ZB_XLU_INTER}
	6 {return AA_ZB_XLU_LINE}
	7 {return AA_ZB_DEC_LINE}
	8 {return AA_ZB_TEX_EDGE}
	9 {return AA_ZB_TEX_INTER}
	10 {return AA_ZB_SUB_SURF}
	11 {return AA_ZB_PCL_SURF}
	12 {return AA_ZB_OPA_TERR}
	13 {return AA_ZB_TEX_TERR}
	14 {return AA_ZB_SUB_TERR}
	15 {return AA_OPA_SURF}
	16 {return AA_XLU_SURF}
	17 {return AA_XLU_LINE}
	18 {return AA_DEC_LINE}
	19 {return AA_TEX_EDGE}
	20 {return AA_SUB_SURF}
	21 {return AA_PCL_SURF}
	22 {return AA_OPA_TERR}
	23 {return AA_TEX_TERR}
	24 {return AA_SUB_TERR}
	25 {return ZB_OPA_SURF}
	26 {return ZB_XLU_SURF}
	27 {return ZB_OPA_DECAL}
	28 {return ZB_XLU_DECAL}
	29 {return ZB_CLD_SURF}
	30 {return ZB_OVL_SURF}
	31 {return ZB_PCL_SURF}
	32 {return OPA_SURF}
	33 {return XLU_SURF}
	34 {return CLD_SURF}
	35 {return PCL_SURF}
	36 {return FOG_SHADE_A}
	37 {return FOG_PRIM_A}
	38 {return PASS}
  }
}


proc get_blCycle1presetLabel val {
  switch $val {
	0 {return AA_ZB_OPA_SURF2}
	1 {return AA_ZB_XLU_SURF2}
	2 {return AA_ZB_OPA_DECAL2}
	3 {return AA_ZB_XLU_DECAL2}
	4 {return AA_ZB_OPA_INTER2}
	5 {return AA_ZB_XLU_INTER2}
	6 {return AA_ZB_XLU_LINE2}
	7 {return AA_ZB_DEC_LINE2}
	8 {return AA_ZB_TEX_EDGE2}
	9 {return AA_ZB_TEX_INTER2}
	10 {return AA_ZB_SUB_SURF2}
	11 {return AA_ZB_PCL_SURF2}
	12 {return ZB_OPA_TERR2}
	13 {return ZB_TEX_TERR2}
	14 {return ZB_SUB_TERR2}
	15 {return AA_OPA_SURF2}
	16 {return AA_XLU_SURF2}
	17 {return AA_XLU_LINE2}
	18 {return AA_DEC_LINE2}
	19 {return AA_TEX_EDGE2}
	20 {return AA_SUB_SURF2}
	21 {return AA_PCL_SURF2}
	22 {return AA_OPA_TERR2}
	23 {return AA_TEX_TERR2}
	24 {return AA_SUB_TERR2}
	25 {return ZB_OPA_SURF2}
	26 {return ZB_XLU_SURF2}
	27 {return ZB_OPA_DECAL2}
	28 {return ZB_XLU_DECAL2}
	29 {return ZB_CLD_SURF2}
	30 {return ZB_OVL_SURF2}
	31 {return ZB_PCL_SURF2}
	32 {return OPA_SURF2}
	33 {return XLU_SURF2}
	34 {return CLD_SURF2}
	35 {return PCL_SURF2}
  }
}


label .bl.cycle0presetL -width 11 -text "Cycle0 Modes"

menubutton .bl.cycle0presetMB -textvariable LblCycle0preset -width 22 \
-relief  raised -menu .bl.cycle0presetMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .bl.cycle0presetMB.menu
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_OPA_SURF" -command CblCycle0preset -variable blCycle0preset -value 0
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_XLU_SURF" -command CblCycle0preset -variable blCycle0preset -value 1
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_OPA_DECAL" -command CblCycle0preset -variable blCycle0preset -value 2
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_XLU_DECAL" -command CblCycle0preset -variable blCycle0preset -value 3
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_OPA_INTER" -command CblCycle0preset -variable blCycle0preset -value 4
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_XLU_INTER" -command CblCycle0preset -variable blCycle0preset -value 5
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_XLU_LINE" -command CblCycle0preset -variable blCycle0preset -value 6
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_DEC_LINE" -command CblCycle0preset -variable blCycle0preset -value 7
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_TEX_EDGE" -command CblCycle0preset -variable blCycle0preset -value 8
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_TEX_INTER" -command CblCycle0preset -variable blCycle0preset -value 9
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_SUB_SURF" -command CblCycle0preset -variable blCycle0preset -value 10
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_PCL_SURF" -command CblCycle0preset -variable blCycle0preset -value 11
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_OPA_TERR" -command CblCycle0preset -variable blCycle0preset -value 12
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_TEX_TERR" -command CblCycle0preset -variable blCycle0preset -value 13
.bl.cycle0presetMB.menu add radiobutton -label "AA_ZB_SUB_TERR" -command CblCycle0preset -variable blCycle0preset -value 14
.bl.cycle0presetMB.menu add radiobutton -label "AA_OPA_SURF" -command CblCycle0preset -variable blCycle0preset -value 15
.bl.cycle0presetMB.menu add radiobutton -label "AA_XLU_SURF" -command CblCycle0preset -variable blCycle0preset -value 16
.bl.cycle0presetMB.menu add radiobutton -label "AA_XLU_LINE" -command CblCycle0preset -variable blCycle0preset -value 17
.bl.cycle0presetMB.menu add radiobutton -label "AA_DEC_LINE" -command CblCycle0preset -variable blCycle0preset -value 18
.bl.cycle0presetMB.menu add radiobutton -label "AA_TEX_EDGE" -command CblCycle0preset -variable blCycle0preset -value 19
.bl.cycle0presetMB.menu add radiobutton -label "AA_SUB_SURF" -command CblCycle0preset -variable blCycle0preset -value 20
.bl.cycle0presetMB.menu add radiobutton -label "AA_PCL_SURF" -command CblCycle0preset -variable blCycle0preset -value 21
.bl.cycle0presetMB.menu add radiobutton -label "AA_OPA_TERR" -command CblCycle0preset -variable blCycle0preset -value 22
.bl.cycle0presetMB.menu add radiobutton -label "AA_TEX_TERR" -command CblCycle0preset -variable blCycle0preset -value 23
.bl.cycle0presetMB.menu add radiobutton -label "AA_SUB_TERR" -command CblCycle0preset -variable blCycle0preset -value 24
.bl.cycle0presetMB.menu add radiobutton -label "ZB_OPA_SURF" -command CblCycle0preset -variable blCycle0preset -value 25
.bl.cycle0presetMB.menu add radiobutton -label "ZB_XLU_SURF" -command CblCycle0preset -variable blCycle0preset -value 26
.bl.cycle0presetMB.menu add radiobutton -label "ZB_OPA_DECAL" -command CblCycle0preset -variable blCycle0preset -value 27
.bl.cycle0presetMB.menu add radiobutton -label "ZB_XLU_DECAL" -command CblCycle0preset -variable blCycle0preset -value 28
.bl.cycle0presetMB.menu add radiobutton -label "ZB_CLD_SURF" -command CblCycle0preset -variable blCycle0preset -value 29
.bl.cycle0presetMB.menu add radiobutton -label "ZB_OVL_SURF" -command CblCycle0preset -variable blCycle0preset -value 30
.bl.cycle0presetMB.menu add radiobutton -label "ZB_PCL_SURF" -command CblCycle0preset -variable blCycle0preset -value 31
.bl.cycle0presetMB.menu add radiobutton -label "OPA_SURF" -command CblCycle0preset -variable blCycle0preset -value 32
.bl.cycle0presetMB.menu add radiobutton -label "XLU_SURF" -command CblCycle0preset -variable blCycle0preset -value 33
.bl.cycle0presetMB.menu add radiobutton -label "CLD_SURF" -command CblCycle0preset -variable blCycle0preset -value 34
.bl.cycle0presetMB.menu add radiobutton -label "PCL_SURF" -command CblCycle0preset -variable blCycle0preset -value 35
.bl.cycle0presetMB.menu add radiobutton -label "FOG_SHADE_A" -command CblCycle0preset -variable blCycle0preset -value 36
.bl.cycle0presetMB.menu add radiobutton -label "FOG_PRIM_A" -command CblCycle0preset -variable blCycle0preset -value 37
.bl.cycle0presetMB.menu add radiobutton -label "PASS" -command CblCycle0preset -variable blCycle0preset -value 38

proc CblCycle0preset {} {
     global blCycle0preset LblCycle0preset	
     global blCycle1preset LblCycle1preset	
     global fptr record
     global blCycle0ModeList blCycle1ModeList blCycle0ModeWord blCycle1ModeWord
     global blCycle0presetColorA blCycle0presetColorB blCycle0presetColorC blCycle0presetColorD
     global blCycle0ColorA blCycle0ColorB blCycle0ColorC blCycle0ColorD
     global M1A1_SH M1B1_SH M2A1_SH M2B1_SH
     global AA_EN Z_CMP Z_UPD IM_RD CLR_ON_CVG CVG_X_ALPHA ALPHA_CVG_SEL FORCE_BL ZMODE_MASK ZMODE_SH TEX_EDGE CVG_DST_MASK CVG_DST_SH A_CMP_EN A_DITH_EN Z_SRC_SEL
     global blAaEn blZcmpEn blZupdEn blImRdEn blCvgDest blColOnCvg blCvgXalpha blAlphaCvgSel blForceBlend blZmode blTexEdgeMode blAlphaCompEn blDithAlphaEn blZsrcSel
     global rspCycleType blCycle1preset

     set LblCycle0preset [get_blCycle0presetLabel $blCycle0preset]

     set blCycle0ModeWord [lindex $blCycle0ModeList $blCycle0preset]
     set blCycle1ModeWord [lindex $blCycle1ModeList $blCycle1preset]


     if {$rspCycleType == 0} {
	set blCycle1preset $blCycle0preset
	CblCycle1preset
     }

     # shift and AND instead of ANDing and then shifting since all shifts
     # in TCL are arithmetic shifts and a set MSB can screw up results
     set blCycle0ColorA [expr (($blCycle0ModeWord >> $M1A1_SH) & 3) ]
     set blCycle0ColorB [expr (($blCycle0ModeWord >> $M1B1_SH) & 3) ]
     set blCycle0ColorC [expr (($blCycle0ModeWord >> $M2A1_SH) & 3) ]
     set blCycle0ColorD [expr (($blCycle0ModeWord >> $M2B1_SH) & 3) ]

     set blAaEn [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $AA_EN) && 1)]
     set blZcmpEn [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $Z_CMP) && 1)]
     set blZupdEn [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $Z_UPD) && 1)]
     set blImRdEn [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $IM_RD) && 1)]
     set blColOnCvg [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $CLR_ON_CVG) && 1)]
     set blCvgDest [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $CVG_DST_MASK)>>  $CVG_DST_SH)]
     set blCvgXalpha [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $CVG_X_ALPHA) && 1)]
     set blAlphaCvgSel [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $ALPHA_CVG_SEL) && 1)]
     set blForceBlend [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $FORCE_BL) && 1)]
     set blZmode [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $ZMODE_MASK) >> $ZMODE_SH)]
     set blTexEdgeMode [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $TEX_EDGE) && 1)]
     set blAlphaCompEn [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $A_CMP_EN) && 1)]
     set blDithAlphaEn [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $A_DITH_EN) && 1)]
     set blZsrcSel [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $Z_SRC_SEL) && 1)]

     # call the corresponding procs mainly for recording functionality
     CblAaEn
     CblZcmpEn
     CblZupdEn
     CblImRdEn
     CblCvgDest
     CblColOnCvg
     CblCvgXalpha
     CblAlphaCvgSel
     CblForceBlend
     CblZmode
     CblTexEdgeMode
     CblAlphaCompEn
     CblDithAlphaEn
     CblZsrcSel

     CblCycle0ColorA
     CblCycle0ColorB
     CblCycle0ColorC
     CblCycle0ColorD


     if {$record == 1} {
	puts $fptr "set blCycle0preset $blCycle0preset"
	puts $fptr "set LblCycle0preset $LblCycle0preset"
     }
}


label .bl.cycle1presetL -width 11 -text "Cycle1 Modes"

menubutton .bl.cycle1presetMB -textvariable LblCycle1preset -width 22 \
-relief  raised -menu .bl.cycle1presetMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .bl.cycle1presetMB.menu
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_OPA_SURF2" -command CblCycle1preset -variable blCycle1preset -value 0
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_XLU_SURF2" -command CblCycle1preset -variable blCycle1preset -value 1
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_OPA_DECAL2" -command CblCycle1preset -variable blCycle1preset -value 2
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_XLU_DECAL2" -command CblCycle1preset -variable blCycle1preset -value 3
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_OPA_INTER2" -command CblCycle1preset -variable blCycle1preset -value 4
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_XLU_INTER2" -command CblCycle1preset -variable blCycle1preset -value 5
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_XLU_LINE2" -command CblCycle1preset -variable blCycle1preset -value 6
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_DEC_LINE2" -command CblCycle1preset -variable blCycle1preset -value 7
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_TEX_EDGE2" -command CblCycle1preset -variable blCycle1preset -value 8
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_TEX_INTER2" -command CblCycle1preset -variable blCycle1preset -value 9
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_SUB_SURF2" -command CblCycle1preset -variable blCycle1preset -value 10
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_PCL_SURF2" -command CblCycle1preset -variable blCycle1preset -value 11
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_OPA_TERR2" -command CblCycle1preset -variable blCycle1preset -value 12
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_TEX_TERR2" -command CblCycle1preset -variable blCycle1preset -value 13
.bl.cycle1presetMB.menu add radiobutton -label "AA_ZB_SUB_TERR2" -command CblCycle1preset -variable blCycle1preset -value 14
.bl.cycle1presetMB.menu add radiobutton -label "AA_OPA_SURF2" -command CblCycle1preset -variable blCycle1preset -value 15
.bl.cycle1presetMB.menu add radiobutton -label "AA_XLU_SURF2" -command CblCycle1preset -variable blCycle1preset -value 16
.bl.cycle1presetMB.menu add radiobutton -label "AA_XLU_LINE2" -command CblCycle1preset -variable blCycle1preset -value 17
.bl.cycle1presetMB.menu add radiobutton -label "AA_DEC_LINE2" -command CblCycle1preset -variable blCycle1preset -value 18
.bl.cycle1presetMB.menu add radiobutton -label "AA_TEX_EDGE2" -command CblCycle1preset -variable blCycle1preset -value 19
.bl.cycle1presetMB.menu add radiobutton -label "AA_SUB_SURF2" -command CblCycle1preset -variable blCycle1preset -value 20
.bl.cycle1presetMB.menu add radiobutton -label "AA_PCL_SURF2" -command CblCycle1preset -variable blCycle1preset -value 21
.bl.cycle1presetMB.menu add radiobutton -label "AA_OPA_TERR2" -command CblCycle1preset -variable blCycle1preset -value 22
.bl.cycle1presetMB.menu add radiobutton -label "AA_TEX_TERR2" -command CblCycle1preset -variable blCycle1preset -value 23
.bl.cycle1presetMB.menu add radiobutton -label "AA_SUB_TERR2" -command CblCycle1preset -variable blCycle1preset -value 24
.bl.cycle1presetMB.menu add radiobutton -label "ZB_OPA_SURF2" -command CblCycle1preset -variable blCycle1preset -value 25
.bl.cycle1presetMB.menu add radiobutton -label "ZB_XLU_SURF2" -command CblCycle1preset -variable blCycle1preset -value 26
.bl.cycle1presetMB.menu add radiobutton -label "ZB_OPA_DECAL2" -command CblCycle1preset -variable blCycle1preset -value 27
.bl.cycle1presetMB.menu add radiobutton -label "ZB_XLU_DECAL2" -command CblCycle1preset -variable blCycle1preset -value 28
.bl.cycle1presetMB.menu add radiobutton -label "ZB_CLD_SURF2" -command CblCycle1preset -variable blCycle1preset -value 29
.bl.cycle1presetMB.menu add radiobutton -label "ZB_OVL_SURF2" -command CblCycle1preset -variable blCycle1preset -value 30
.bl.cycle1presetMB.menu add radiobutton -label "ZB_PCL_SURF2" -command CblCycle1preset -variable blCycle1preset -value 31
.bl.cycle1presetMB.menu add radiobutton -label "OPA_SURF2" -command CblCycle1preset -variable blCycle1preset -value 32
.bl.cycle1presetMB.menu add radiobutton -label "XLU_SURF2" -command CblCycle1preset -variable blCycle1preset -value 33
.bl.cycle1presetMB.menu add radiobutton -label "CLD_SURF2" -command CblCycle1preset -variable blCycle1preset -value 34
.bl.cycle1presetMB.menu add radiobutton -label "PCL_SURF2" -command CblCycle1preset -variable blCycle1preset -value 35

proc CblCycle1preset {} {
     global blCycle1preset LblCycle1preset
     global blCycle0preset LblCycle0preset
     global fptr record
     global blCycle0ModeList blCycle1ModeList blCycle1ModeWord blCycle0ModeWord
     global blCycle1presetColorA blCycle1presetColorB blCycle1presetColorC blCycle1presetColorD
     global blCycle1ColorA blCycle1ColorB blCycle1ColorC blCycle1ColorD
     global M1A2_SH M1B2_SH M2A2_SH M2B2_SH
     global AA_EN Z_CMP Z_UPD IM_RD CLR_ON_CVG CVG_X_ALPHA ALPHA_CVG_SEL FORCE_BL ZMODE_MASK ZMODE_SH TEX_EDGE CVG_DST_MASK CVG_DST_SH A_CMP_EN A_DITH_EN Z_SRC_SEL
     global blAaEn blZcmpEn blZupdEn blImRdEn blCvgDest blColOnCvg blCvgXalpha blAlphaCvgSel blForceBlend blZmode blTexEdgeMode blAlphaCompEn blDithAlphaEn blZsrcSel

     set LblCycle1preset [get_blCycle1presetLabel $blCycle1preset]

     set blCycle1ModeWord [lindex $blCycle1ModeList $blCycle1preset]
     set blCycle0ModeWord [lindex $blCycle0ModeList $blCycle0preset]

     # shift and AND instead of ANDing and then shifting since all shifts
     # in TCL are arithmetic shifts and a set MSB can screw up results
     set blCycle1ColorA [expr (($blCycle1ModeWord >> $M1A2_SH) & 3) ]
     set blCycle1ColorB [expr (($blCycle1ModeWord >> $M1B2_SH) & 3) ]
     set blCycle1ColorC [expr (($blCycle1ModeWord >> $M2A2_SH) & 3) ]
     set blCycle1ColorD [expr (($blCycle1ModeWord >> $M2B2_SH) & 3) ]

#    set blCycle1ColorA [expr ($blCycle1ModeWord & (3 << $M1A2_SH)) >> $M1A2_SH ]
#    set blCycle1ColorB [expr ($blCycle1ModeWord & (3 << $M1B2_SH)) >> $M1B2_SH ]
#    set blCycle1ColorC [expr ($blCycle1ModeWord & (3 << $M2A2_SH)) >> $M2A2_SH ]
#    set blCycle1ColorD [expr ($blCycle1ModeWord & (3 << $M2B2_SH)) >> $M2B2_SH ]

     set blAaEn [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $AA_EN) && 1)]
     set blZcmpEn [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $Z_CMP) && 1)]
     set blZupdEn [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $Z_UPD) && 1)]
     set blImRdEn [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $IM_RD) && 1)]
     set blColOnCvg [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $CLR_ON_CVG) && 1)]
     set blCvgDest [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $CVG_DST_MASK)>>  $CVG_DST_SH)]
     set blCvgXalpha [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $CVG_X_ALPHA) && 1)]
     set blAlphaCvgSel [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $ALPHA_CVG_SEL) && 1)]
     set blForceBlend [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $FORCE_BL) && 1)]
     set blZmode [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $ZMODE_MASK) >> $ZMODE_SH)]
     set blTexEdgeMode [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $TEX_EDGE) && 1)]
     set blAlphaCompEn [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $A_CMP_EN) && 1)]
     set blDithAlphaEn [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $A_DITH_EN) && 1)]
     set blZsrcSel [expr ((($blCycle0ModeWord | $blCycle1ModeWord) & $Z_SRC_SEL) && 1)]

     #puts "blTexEdgeMode = $blTexEdgeMode"

     CblAaEn
     CblZcmpEn
     CblZupdEn
     CblImRdEn
     CblCvgDest
     CblColOnCvg
     CblCvgXalpha
     CblAlphaCvgSel
     CblForceBlend
     CblZmode
     CblTexEdgeMode
     CblAlphaCompEn
     CblDithAlphaEn
     CblZsrcSel

     CblCycle1ColorA
     CblCycle1ColorB
     CblCycle1ColorC
     CblCycle1ColorD
     
     if {$record == 1} {
	puts $fptr "set blCycle1preset $blCycle1preset"
	puts $fptr "set LblCycle1preset $LblCycle1preset"
     }
}

set blCycle0ModeWord 0
set blCycle1ModeWord 0
#
set blCycle0preset 0
#    CblCycle0preset
#
set blCycle1preset 0
#    CblCycle1preset

#----------------------------------------------------------------------------

pack .bl.aaEnCB .bl.zCmpEnCB .bl.zUpdEnCB .bl.imRdEnCB .bl.cvgDestMB .bl.colOnCvgCB .bl.cvgXalphaCB -in .bl.modeBitsF1 -side left -fill y -padx 1m -pady 1m

pack .bl.alphaCvgSelCB .bl.forceBlendCB .bl.zModeMB .bl.texEdgeModeCB .bl.alphaCompEnCB .bl.dithAlphaEnCB .bl.zSrcSelCB -in .bl.modeBitsF2 -side left -fill y -padx 1m -pady 1m

pack .bl.modeBitsF1 .bl.modeBitsF2  -in .bl.modeBitsF -side top -fill x -padx 1m -pady 1m

pack .bl.cycle0ColorL .bl.cycle0ColorL( .bl.cycle0ColorAMB .bl.cycle0ColorLX1 .bl.cycle0ColorBMB .bl.cycle0ColorL+ .bl.cycle0ColorCMB .bl.cycle0ColorLX2 .bl.cycle0ColorDMB .bl.cycle0ColorL) .bl.cycle0ColorBL .bl.cycle0ColorL1+ .bl.cycle0ColorDL .bl.cycle0ColorL1)  -in .bl.cyc0ColorF -side left -fill y -padx 1m -pady 1m

pack .bl.cycle1ColorL .bl.cycle1ColorL( .bl.cycle1ColorAMB .bl.cycle1ColorLX1 .bl.cycle1ColorBMB .bl.cycle1ColorL+ .bl.cycle1ColorCMB .bl.cycle1ColorLX2 .bl.cycle1ColorDMB  .bl.cycle1ColorL) .bl.cycle1ColorBL .bl.cycle1ColorL1+ .bl.cycle1ColorDL .bl.cycle1ColorL1) -in .bl.cyc1ColorF -side left -fill y -padx 1m -pady 1m

pack .bl.cyc0ColorF .bl.cyc1ColorF -in .bl.muxesF -side top -fill x -pady 1m

pack .bl.blendColorRedS .bl.blendColorRedE -in .bl.blendRedF -side left -padx 1m
pack .bl.blendColorGreenS .bl.blendColorGreenE -in .bl.blendGreenF -side left -padx 1m
pack .bl.blendColorBlueS .bl.blendColorBlueE -in .bl.blendBlueF -side left -padx 1m
pack .bl.blendColorAlphaS .bl.blendColorAlphaE -in .bl.blendAlphaF -side left -padx 1m
pack .bl.blendColorL .bl.blendRedF .bl.blendGreenF .bl.blendBlueF .bl.blendAlphaF -in .bl.blendColorF -side left -fill y -padx 1m

pack .bl.fogColorRedS .bl.fogColorRedE -in .bl.fogRedF -side left -padx 1m
pack .bl.fogColorGreenS .bl.fogColorGreenE -in .bl.fogGreenF -side left -padx 1m
pack .bl.fogColorBlueS .bl.fogColorBlueE -in .bl.fogBlueF -side left -padx 1m
pack .bl.fogColorAlphaS .bl.fogColorAlphaE -in .bl.fogAlphaF -side left -padx 1m
pack .bl.fogColorL .bl.fogRedF .bl.fogGreenF .bl.fogBlueF .bl.fogAlphaF -in .bl.fogColorF -side left -fill y -padx 1m

pack .bl.primZS .bl.primZE -in .bl.primZF -side left -padx 1m
pack .bl.primDeltaZS .bl.primDeltaZE -in .bl.primDeltaZF -side left -padx 1m
pack .bl.primZL .bl.primZF .bl.primDeltaZF -in .bl.primDepthF -side left -fill y -padx 1m

pack .bl.rgbDitherL .bl.rgbDitherMB .bl.alphaDitherL .bl.alphaDitherMB .bl.videoAAFilterL .bl.videoAAFilterCB .bl.videoDitherFilterL .bl.videoDitherFilterCB .bl.frameBufferSizeL .bl.frameBufferSizeCB -in .bl.ditherF -side left -fill y -padx 2m

pack .bl.blendColorF .bl.fogColorF -in .bl.colorF -side top -fill x -pady 1m


pack .bl.cycle0presetL .bl.cycle0presetMB .bl.cycle1presetL .bl.cycle1presetMB .bl.fbShiftL .bl.fbShiftE -in .bl.cycle0cycle1presetF -side left -fill y -padx 5m
pack .bl.cycle0cycle1presetF -in .bl.presetF -side top -fill x -pady 1m

pack .bl.ditherF .bl.colorF .bl.primDepthF -in .bl.stateF -side top -fill x -pady 1m

pack .bl.stateF .bl.modeBitsF .bl.muxesF .bl.presetF -in .bl.topF -side top -fill x -pady 1m
pack .bl.topF
