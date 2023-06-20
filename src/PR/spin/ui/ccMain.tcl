##################### Color Combiner #######################################
toplevel .cc

frame .cc.topF
frame .cc.stateF
frame .cc.muxesF
frame .cc.cyc0ColorF -relief ridge -borderwidth 2
frame .cc.cyc1ColorF -relief ridge -borderwidth 2
frame .cc.cyc0AlphaF -relief ridge -borderwidth 2
frame .cc.cyc1AlphaF -relief ridge -borderwidth 2

frame .cc.colorF -relief ridge -borderwidth 4
frame .cc.primColorF
frame .cc.primRedF 
frame .cc.primGreenF 
frame .cc.primBlueF 
frame .cc.primAlphaF

frame .cc.envColorF
frame .cc.envRedF 
frame .cc.envGreenF 
frame .cc.envBlueF 
frame .cc.envAlphaF

frame .cc.keyF -relief ridge -borderwidth 4
frame .cc.keyWidthF 
frame .cc.keyWidthRedF 
frame .cc.keyWidthGreenF 
frame .cc.keyWidthBlueF 

frame .cc.keyCenterF 
frame .cc.keyCenterRedF 
frame .cc.keyCenterGreenF 
frame .cc.keyCenterBlueF 

frame .cc.keyScaleF 
frame .cc.keyScaleRedF 
frame .cc.keyScaleGreenF 
frame .cc.keyScaleBlueF 

frame .cc.convertF -relief ridge -borderwidth 4
frame .cc.convertK4K5F
frame .cc.convertK4F
frame .cc.convertK5F

frame .cc.primLODF -relief ridge -borderwidth 4
frame .cc.primLODfracminF
frame .cc.primLODfracF
frame .cc.primLODminF

frame .cc.presetF -relief ridge -borderwidth 2
frame .cc.cycle0cycle1presetF
#--------------------------- cc State ------------------------------------

#--------------------------- Convert  ------------------------------------
label .cc.convertL -width 11 -text "Convert"

scale .cc.convertK4S -label K4 -from 0 -to 255 -length 277 -orient horizontal -command CccConvertK4

entry .cc.convertK4E -width 3 -relief sunken -textvariable setConvertK4
bind .cc.convertK4E <Return> {
	if {$setConvertK4 > 255} {set setConvertK4 255}
	if {$setConvertK4 < 0} {set setConvertK4 0}
	.cc.convertK4S set $setConvertK4
	.setConvertS4 set $setConvertK4
	focus none
}

#.cc.convertK4S set 128

proc CccConvertK4 value {
	global ccConvertK4 setConvertK4
	global fptr record
	set setConvertK4 $value
	.setConvertS4 set $setConvertK4
        if {$record == 1} {
                puts $fptr ".cc.convertK4S set $setConvertK4"
        }
	callback_setConvert
	callback_send_dl
}

scale .cc.convertK5S -label K5 -from 0 -to 255 -length 277 -orient horizontal -command CccConvertK5

entry .cc.convertK5E -width 3 -relief sunken -textvariable setConvertK5
bind .cc.convertK5E <Return> {
	if {$setConvertK5 > 255} {set setConvertK5 255}
	if {$setConvertK5 < 0} {set setConvertK5 0}
	.cc.convertK5S set $setConvertK5
	.setConvertS5 set $setConvertK5
	focus none
}
#.cc.convertK5S set 128

proc CccConvertK5 value {
	global ccConvertK5 setConvertK5
	global fptr record
	set setConvertK5 $value
	.setConvertS5 set $setConvertK5
        if {$record == 1} {
                puts $fptr ".cc.convertK5S set $setConvertK5"
        }
	callback_setConvert
	callback_send_dl
}

#--------------------------- Key Scale ------------------------------------
label .cc.keyScaleL -width 11 -text "Key Scale"

scale .cc.keyScaleRedS -label Red -from 0 -to 255 -length 165 -orient horizontal -command CccKeyScaleRed

entry .cc.keyScaleRedE -width 3 -relief sunken -textvariable ccKeyScaleRed
bind .cc.keyScaleRedE <Return> {
	if {$ccKeyScaleRed > 255} {set ccKeyScaleRed 255}
	if {$ccKeyScaleRed < 0} {set ccKeyScaleRed 0}
	.cc.keyScaleRedS set $ccKeyScaleRed
	focus none
}

#.cc.keyScaleRedS set 128

proc CccKeyScaleRed value {
	global ccKeyScaleRed
	global fptr record
	set ccKeyScaleRed $value
	if {$record == 1} {
		puts $fptr ".cc.keyScaleRedS set $ccKeyScaleRed"
	}
	callback_ccKey
	callback_send_dl
}

scale .cc.keyScaleBlueS -label Blue -from 0 -to 255 -length 165 -orient horizontal -command CccKeyScaleBlue

entry .cc.keyScaleBlueE -width 3 -relief sunken -textvariable ccKeyScaleBlue
bind .cc.keyScaleBlueE <Return> {
	if {$ccKeyScaleBlue > 255} {set ccKeyScaleBlue 255}
	if {$ccKeyScaleBlue < 0} {set ccKeyScaleBlue 0}
	.cc.keyScaleBlueS set $ccKeyScaleBlue
	focus none
}
#.cc.keyScaleBlueS set 128

proc CccKeyScaleBlue value {
	global ccKeyScaleBlue
	global fptr record
	set ccKeyScaleBlue $value
	if {$record == 1} {
		puts $fptr ".cc.keyScaleBlueS set $ccKeyScaleBlue"
	}
	callback_ccKey
	callback_send_dl
}

scale .cc.keyScaleGreenS -label Green -from 0 -to 255 -length 165 -orient horizontal -command CccKeyScaleGreen

entry .cc.keyScaleGreenE -width 3 -relief sunken -textvariable ccKeyScaleGreen
bind .cc.keyScaleGreenE <Return> {
	if {$ccKeyScaleGreen > 255} {set ccKeyScaleGreen 255}
	if {$ccKeyScaleGreen < 0} {set ccKeyScaleGreen 0}
	.cc.keyScaleGreenS set $ccKeyScaleGreen
	focus none
}
#.cc.keyScaleGreenS set 128

proc CccKeyScaleGreen value {
	global ccKeyScaleGreen
	global fptr record
	set ccKeyScaleGreen $value
	if {$record == 1} {
		puts $fptr ".cc.keyScaleGreenS set $ccKeyScaleGreen"
	}
	callback_ccKey
	callback_send_dl
}
#--------------------------Key Center--------------------------------------

label .cc.keyCenterL -width 11 -text "Key Center"

scale .cc.keyCenterRedS -label Red -from 0 -to 255 -length 165 -orient horizontal -command CccKeyCenterRed

entry .cc.keyCenterRedE -width 3 -relief sunken -textvariable ccKeyCenterRed
bind .cc.keyCenterRedE <Return> {
	if {$ccKeyCenterRed > 255} {set ccKeyCenterRed 255}
	if {$ccKeyCenterRed < 0} {set ccKeyCenterRed 0}
	.cc.keyCenterRedS set $ccKeyCenterRed
	focus none
}

#.cc.keyCenterRedS set 128

proc CccKeyCenterRed value {
	global ccKeyCenterRed
	global fptr record
	set ccKeyCenterRed $value
	if {$record == 1} {
		puts $fptr ".cc.keyCenterRedS set $ccKeyCenterRed"
	}
	callback_ccKey
	callback_send_dl
}

scale .cc.keyCenterBlueS -label Blue -from 0 -to 255 -length 165 -orient horizontal -command CccKeyCenterBlue

entry .cc.keyCenterBlueE -width 3 -relief sunken -textvariable ccKeyCenterBlue
bind .cc.keyCenterBlueE <Return> {
	if {$ccKeyCenterBlue > 255} {set ccKeyCenterBlue 255}
	if {$ccKeyCenterBlue < 0} {set ccKeyCenterBlue 0}
	.cc.keyCenterBlueS set $ccKeyCenterBlue
	focus none
}
#.cc.keyCenterBlueS set 128

proc CccKeyCenterBlue value {
	global ccKeyCenterBlue
	global fptr record
	set ccKeyCenterBlue $value
	if {$record == 1} {
		puts $fptr ".cc.keyCenterBlueS set $ccKeyCenterBlue"
	}
	callback_ccKey
	callback_send_dl
}

scale .cc.keyCenterGreenS -label Green -from 0 -to 255 -length 165 -orient horizontal -command CccKeyCenterGreen

entry .cc.keyCenterGreenE -width 3 -relief sunken -textvariable ccKeyCenterGreen
bind .cc.keyCenterGreenE <Return> {
	if {$ccKeyCenterGreen > 255} {set ccKeyCenterGreen 255}
	if {$ccKeyCenterGreen < 0} {set ccKeyCenterGreen 0}
	.cc.keyCenterGreenS set $ccKeyCenterGreen
	focus none
}
#.cc.keyCenterGreenS set 128

proc CccKeyCenterGreen value {
	global ccKeyCenterGreen
	global fptr record
	set ccKeyCenterGreen $value
	if {$record == 1} {
		puts $fptr ".cc.keyCenterGreenS set $ccKeyCenterGreen"
	}
	callback_ccKey
	callback_send_dl
}
#--------------------------Key Width--------------------------------------

label .cc.keyWidthL -width 11 -text "Key Width"

scale .cc.keyWidthRedS -label Red -from 0 -to 4095 -length 159 -orient horizontal -command CccKeyWidthRed

entry .cc.keyWidthRedE -width 4 -relief sunken -textvariable ccKeyWidthRed
bind .cc.keyWidthRedE <Return> {
	if {$ccKeyWidthRed > 4095} {set ccKeyWidthRed 4095}
	if {$ccKeyWidthRed < 0} {set ccKeyWidthRed 0}
	.cc.keyWidthRedS set $ccKeyWidthRed
	focus none
}

#.cc.keyWidthRedS set 2047

proc CccKeyWidthRed value {
	global ccKeyWidthRed
	global fptr record
	set ccKeyWidthRed $value
	if {$record == 1} {
		puts $fptr ".cc.keyWidthRedS set $ccKeyWidthRed"
	}
	callback_ccKey
	callback_send_dl
}

scale .cc.keyWidthBlueS -label Blue -from 0 -to 4095 -length 159 -orient horizontal -command CccKeyWidthBlue

entry .cc.keyWidthBlueE -width 4 -relief sunken -textvariable ccKeyWidthBlue
bind .cc.keyWidthBlueE <Return> {
	if {$ccKeyWidthBlue > 4095} {set ccKeyWidthBlue 4095}
	if {$ccKeyWidthBlue < 0} {set ccKeyWidthBlue 0}
	.cc.keyWidthBlueS set $ccKeyWidthBlue
	focus none
}
#.cc.keyWidthBlueS set 2047

proc CccKeyWidthBlue value {
	global ccKeyWidthBlue
	global fptr record
	set ccKeyWidthBlue $value
	if {$record == 1} {
		puts $fptr ".cc.keyWidthBlueS set $ccKeyWidthBlue"
	}
	callback_ccKey
	callback_send_dl
}

scale .cc.keyWidthGreenS -label Green -from 0 -to 4095 -length 159 -orient horizontal -command CccKeyWidthGreen

entry .cc.keyWidthGreenE -width 4 -relief sunken -textvariable ccKeyWidthGreen
bind .cc.keyWidthGreenE <Return> {
	if {$ccKeyWidthGreen > 4095} {set ccKeyWidthGreen 4095}
	if {$ccKeyWidthGreen < 0} {set ccKeyWidthGreen 0}
	.cc.keyWidthGreenS set $ccKeyWidthGreen
	focus none
}
#.cc.keyWidthGreenS set 2047

proc CccKeyWidthGreen value {
	global ccKeyWidthGreen
	global fptr record
	set ccKeyWidthGreen $value
	if {$record == 1} {
		puts $fptr ".cc.keyWidthGreenS set $ccKeyWidthGreen"
	}
	callback_ccKey
	callback_send_dl
}

#--------------------------Prim Color--------------------------------------

label .cc.primColorL -width 11 -text "Prim Color"

scale .cc.primColorRedS -label Red -from 0 -to 255 -length 110 -orient horizontal -command CccPrimColorRed

entry .cc.primColorRedE -width 3 -relief sunken -textvariable ccPrimColorRed
bind .cc.primColorRedE <Return> {
	if {$ccPrimColorRed > 255} {set ccPrimColorRed 255}
	if {$ccPrimColorRed < 0} {set ccPrimColorRed 0}
	.cc.primColorRedS set $ccPrimColorRed
	focus none
}

#.cc.primColorRedS set 128

proc CccPrimColorRed value {
	global ccPrimColorRed
	global fptr record
	set ccPrimColorRed $value
	if {$record == 1} {
		puts $fptr ".cc.primColorRedS set $ccPrimColorRed"
	}
	callback_ccPrim
	callback_send_dl
}

scale .cc.primColorBlueS -label Blue -from 0 -to 255 -length 110 -orient horizontal -command CccPrimColorBlue

entry .cc.primColorBlueE -width 3 -relief sunken -textvariable ccPrimColorBlue
bind .cc.primColorBlueE <Return> {
	if {$ccPrimColorBlue > 255} {set ccPrimColorBlue 255}
	if {$ccPrimColorBlue < 0} {set ccPrimColorBlue 0}
	.cc.primColorBlueS set $ccPrimColorBlue
	focus none
}
#.cc.primColorBlueS set 128

proc CccPrimColorBlue value {
	global ccPrimColorBlue
	global fptr record
	set ccPrimColorBlue $value
	if {$record == 1} {
		puts $fptr ".cc.primColorBlueS set $ccPrimColorBlue"
	}
	callback_ccPrim
	callback_send_dl
}

scale .cc.primColorAlphaS -label Alpha -from 0 -to 255 -length 110 -orient horizontal -command CccPrimColorAlpha

entry .cc.primColorAlphaE -width 3 -relief sunken -textvariable ccPrimColorAlpha
bind .cc.primColorAlphaE <Return> {
	if {$ccPrimColorAlpha > 255} {set ccPrimColorAlpha 255}
	if {$ccPrimColorAlpha < 0} {set ccPrimColorAlpha 0}
	.cc.primColorAlphaS set $ccPrimColorAlpha
	focus none
}
#.cc.primColorAlphaS set 128

proc CccPrimColorAlpha value {
	global ccPrimColorAlpha
	global fptr record
	set ccPrimColorAlpha $value
	if {$record == 1} {
		puts $fptr ".cc.primColorAlphaS set $ccPrimColorAlpha"
	}
	callback_ccPrim
	callback_send_dl
}

scale .cc.primColorGreenS -label Green -from 0 -to 255 -length 110 -orient horizontal -command CccPrimColorGreen

entry .cc.primColorGreenE -width 3 -relief sunken -textvariable ccPrimColorGreen
bind .cc.primColorGreenE <Return> {
	if {$ccPrimColorGreen > 255} {set ccPrimColorGreen 255}
	if {$ccPrimColorGreen < 0} {set ccPrimColorGreen 0}
	.cc.primColorGreenS set $ccPrimColorGreen
	focus none
}
#.cc.primColorGreenS set 128

proc CccPrimColorGreen value {
	global ccPrimColorGreen
	global fptr record
	set ccPrimColorGreen $value
	if {$record == 1} {
		puts $fptr ".cc.primColorGreenS set $ccPrimColorGreen"
	}
	callback_ccPrim
	callback_send_dl
}
#--------------------------- Prim LOD  ------------------------------------
label .cc.primLODL -width 11 -text "Prim LOD"

scale .cc.primLODfracS -label Frac -from 0 -to 255 -length 277 -orient horizontal -command CccPrimLODfrac

entry .cc.primLODfracE -width 3 -relief sunken -textvariable ccPrimLODfrac
bind .cc.primLODfracE <Return> {
	if {$ccPrimLODfrac > 255} {set ccPrimLODfrac 255}
	if {$ccPrimLODfrac < 0} {set ccPrimLODfrac 0}
	.cc.primLODfracS set $ccPrimLODfrac
	focus none
}

#.cc.primLODfracS set 128

proc CccPrimLODfrac value {
	global ccPrimLODfrac
	global fptr record
	set ccPrimLODfrac $value
	if {$record == 1} {
		puts $fptr ".cc.primLODfracS set $ccPrimLODfrac"
	}
	callback_ccPrim
	callback_send_dl
}

scale .cc.primLODminS -label Min -from 0 -to 255 -length 277 -orient horizontal -command CccPrimLODmin

entry .cc.primLODminE -width 3 -relief sunken -textvariable ccPrimLODmin
bind .cc.primLODminE <Return> {
	if {$ccPrimLODmin > 255} {set ccPrimLODmin 255}
	if {$ccPrimLODmin < 0} {set ccPrimLODmin 0}
	.cc.primLODminS set $ccPrimLODmin
	focus none
}
#.cc.primLODminS set 128

proc CccPrimLODmin value {
	global ccPrimLODmin
	global fptr record
	set ccPrimLODmin $value
	if {$record == 1} {
		puts $fptr ".cc.primLODminS set $ccPrimLODmin"
	}
	callback_ccPrim
	callback_send_dl
}
#---------------------------Env Color------------------------------------
label .cc.envColorL -width 11 -text "Env Color"

scale .cc.envColorRedS -label Red -from 0 -to 255 -length 110 -orient horizontal -command CccEnvColorRed

entry .cc.envColorRedE -width 3 -relief sunken -textvariable ccEnvColorRed
bind .cc.envColorRedE <Return> {
	if {$ccEnvColorRed > 255} {set ccEnvColorRed 255}
	if {$ccEnvColorRed < 0} {set ccEnvColorRed 0}
	.cc.envColorRedS set $ccEnvColorRed
	focus none
}

#.cc.envColorRedS set 128

proc CccEnvColorRed value {
	global ccEnvColorRed
	global fptr record
	set ccEnvColorRed $value
	if {$record == 1} {
		puts $fptr ".cc.envColorRedS set $ccEnvColorRed"
	}
	callback_ccEnv
	callback_send_dl
}

scale .cc.envColorBlueS -label Blue -from 0 -to 255 -length 110 -orient horizontal -command CccEnvColorBlue

entry .cc.envColorBlueE -width 3 -relief sunken -textvariable ccEnvColorBlue
bind .cc.envColorBlueE <Return> {
	if {$ccEnvColorBlue > 255} {set ccEnvColorBlue 255}
	if {$ccEnvColorBlue < 0} {set ccEnvColorBlue 0}
	.cc.envColorBlueS set $ccEnvColorBlue
	focus none
}
#.cc.envColorBlueS set 128

proc CccEnvColorBlue value {
	global ccEnvColorBlue
	global fptr record
	set ccEnvColorBlue $value
	if {$record == 1} {
		puts $fptr ".cc.envColorBlueS set $ccEnvColorBlue"
	}
	callback_ccEnv
	callback_send_dl
}

scale .cc.envColorAlphaS -label Alpha -from 0 -to 255 -length 110 -orient horizontal -command CccEnvColorAlpha

entry .cc.envColorAlphaE -width 3 -relief sunken -textvariable ccEnvColorAlpha
bind .cc.envColorAlphaE <Return> {
	if {$ccEnvColorAlpha > 255} {set ccEnvColorAlpha 255}
	if {$ccEnvColorAlpha < 0} {set ccEnvColorAlpha 0}
	.cc.envColorAlphaS set $ccEnvColorAlpha
	focus none
}
#.cc.envColorAlphaS set 128

proc CccEnvColorAlpha value {
	global ccEnvColorAlpha
	global fptr record
	set ccEnvColorAlpha $value
	if {$record == 1} {
		puts $fptr ".cc.envColorAlphaS set $ccEnvColorAlpha"
	}
	callback_ccEnv
	callback_send_dl
}

scale .cc.envColorGreenS -label Green -from 0 -to 255 -length 110 -orient horizontal -command CccEnvColorGreen

entry .cc.envColorGreenE -width 3 -relief sunken -textvariable ccEnvColorGreen
bind .cc.envColorGreenE <Return> {
	if {$ccEnvColorGreen > 255} {set ccEnvColorGreen 255}
	if {$ccEnvColorGreen < 0} {set ccEnvColorGreen 0}
	.cc.envColorGreenS set $ccEnvColorGreen
	focus none
}
#.cc.envColorGreenS set 128

proc CccEnvColorGreen value {
	global ccEnvColorGreen
	global fptr record
	set ccEnvColorGreen $value
	if {$record == 1} {
		puts $fptr ".cc.envColorGreenS set $ccEnvColorGreen"
	}
	callback_ccEnv
	callback_send_dl
}
#---------------------------CC Muxes--------------------------------------
#---------------------------Utility functions-----------------------------
proc getCCcolorLabelA val {
  switch $val {
	0 {return "Comb Color"}
	1 {return "Tex0 Color"}
	2 {return "Tex1 Color"}
	3 {return "Prim Color"}
	4 {return "Shade Color"}
	5 {return "Env Color"}
	6 {return "1.0"}
	7 {return "Noise"}
 	31 {return "0.0"}
  }
}

proc getCCcolorLabelB val {
  switch $val {
	0 {return "Comb Color"}
	1 {return "Tex0 Color"}
	2 {return "Tex1 Color"}
	3 {return "Prim Color"}
	4 {return "Shade Color"}
	5 {return "Env Color"}
	6 {return "Key:Center"}
	7 {return "Convert:K4"}
 	31 {return "0.0"}
  }
}

proc getCCcolorLabelC val {
  switch $val {
	0 {return "Comb Color"}
	1 {return "Tex0 Color"}
	2 {return "Tex1 Color"}
	3 {return "Prim Color"}
	4 {return "Shade Color"}
	5 {return "Env Color"}
	6 {return "Key:Scale"}
	7 {return "Comb Alpha"}
	8 {return "Tex0 Alpha"}
	9 {return "Tex1 Alpha"}
	10 {return "Prim Alpha"}
	11 {return "Shade Alpha"}
	12 {return "Env Alpha"}
	13 {return "LOD frac"}
	14 {return "Prim LOD frac"}
	15 {return "Convert:K5"}
 	31 {return "0.0"}
  }
}

proc getCCcolorLabelD val {
  switch $val {
	0 {return "Comb Color"}
	1 {return "Tex0 Color"}
	2 {return "Tex1 Color"}
	3 {return "Prim Color"}
	4 {return "Shade Color"}
	5 {return "Env Color"}
 	6 {return "1.0"}
 	31 {return "0.0"}
  }
}

proc getCCalphaLabelA val {
  switch $val {
	0 {return "Comb Alpha"}
	1 {return "Tex0 Alpha"}
	2 {return "Tex1 Alpha"}
	3 {return "Prim Alpha"}
	4 {return "Shade Alpha"}
	5 {return "Env Alpha"}
	6 {return "1.0"}
 	7 {return "0.0"}
  }
}

proc getCCalphaLabelB val {
  switch $val {
	0 {return "Comb Alpha"}
	1 {return "Tex0 Alpha"}
	2 {return "Tex1 Alpha"}
	3 {return "Prim Alpha"}
	4 {return "Shade Alpha"}
	5 {return "Env Alpha"}
	6 {return "1.0"}
 	7 {return "0.0"}
  }
}

proc getCCalphaLabelC val {
  switch $val {
	0 {return "LOD frac"}
	1 {return "Tex0 Alpha"}
	2 {return "Tex1 Alpha"}
	3 {return "Prim Alpha"}
	4 {return "Shade Alpha"}
	5 {return "Env Alpha"}
	6 {return "Prim LOD Frac"}
 	7 {return "0.0"}
  }
}

proc getCCalphaLabelD val {
  switch $val {
	0 {return "Comb Alpha"}
	1 {return "Tex0 Alpha"}
	2 {return "Tex1 Alpha"}
	3 {return "Prim Alpha"}
	4 {return "Shade Alpha"}
	5 {return "Env Alpha"}
	6 {return "1.0"}
 	7 {return "0.0"}
  }
}
#-------------------------- cycle1 color -----------------------------------#

label .cc.cycle1ColorL -width 11 -text "cycle1 Color"

label .cc.cycle1ColorL( -width 5 -text "=   ("

menubutton .cc.cycle1ColorAMB -textvariable LccCycle1ColorA -width 12 \
-relief  raised -menu .cc.cycle1ColorAMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle1ColorAMB.menu
.cc.cycle1ColorAMB.menu add radiobutton -label "Comb Color" -command CccCycle1ColorA -variable ccCycle1ColorA -value 0
.cc.cycle1ColorAMB.menu add radiobutton -label "Tex0 Color" -command CccCycle1ColorA -variable ccCycle1ColorA -value 1
.cc.cycle1ColorAMB.menu add radiobutton -label "Tex1 Color" -command CccCycle1ColorA -variable ccCycle1ColorA -value 2
.cc.cycle1ColorAMB.menu add radiobutton -label "Prim Color" -command CccCycle1ColorA -variable ccCycle1ColorA -value 3
.cc.cycle1ColorAMB.menu add radiobutton -label "Shade Color" -command CccCycle1ColorA -variable ccCycle1ColorA -value 4
.cc.cycle1ColorAMB.menu add radiobutton -label "Env Color" -command CccCycle1ColorA -variable ccCycle1ColorA -value 5
.cc.cycle1ColorAMB.menu add radiobutton -label "Noise" -command CccCycle1ColorA -variable ccCycle1ColorA -value 7
.cc.cycle1ColorAMB.menu add radiobutton -label "1.0" -command CccCycle1ColorA -variable ccCycle1ColorA -value 6
.cc.cycle1ColorAMB.menu add radiobutton -label "0.0" -command CccCycle1ColorA -variable ccCycle1ColorA -value 31

#set ccCycle1ColorA 2
#set LccCycle1ColorA "Tex1 Color"

proc CccCycle1ColorA {} {
     global LccCycle1ColorA ccCycle1ColorA
     global fptr record
     set LccCycle1ColorA  [getCCcolorLabelA $ccCycle1ColorA]

     if {$record == 1} {
	puts $fptr "set ccCycle1ColorA $ccCycle1ColorA"
	puts $fptr "CccCycle1ColorA"
     }
	callback_ccCycle
	callback_send_dl
}


label .cc.cycle1ColorL- -width 1 -text "-"

menubutton .cc.cycle1ColorBMB -textvariable LccCycle1ColorB -width 12 \
-relief  raised -menu .cc.cycle1ColorBMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle1ColorBMB.menu
.cc.cycle1ColorBMB.menu add radiobutton -label "Comb Color" -command CccCycle1ColorB -variable ccCycle1ColorB -value 0
.cc.cycle1ColorBMB.menu add radiobutton -label "Tex0 Color" -command CccCycle1ColorB -variable ccCycle1ColorB -value 1
.cc.cycle1ColorBMB.menu add radiobutton -label "Tex1 Color" -command CccCycle1ColorB -variable ccCycle1ColorB -value 2
.cc.cycle1ColorBMB.menu add radiobutton -label "Prim Color" -command CccCycle1ColorB -variable ccCycle1ColorB -value 3
.cc.cycle1ColorBMB.menu add radiobutton -label "Shade Color" -command CccCycle1ColorB -variable ccCycle1ColorB -value 4
.cc.cycle1ColorBMB.menu add radiobutton -label "Env Color" -command CccCycle1ColorB -variable ccCycle1ColorB -value 5
.cc.cycle1ColorBMB.menu add radiobutton -label "Key:Center" -command CccCycle1ColorB -variable ccCycle1ColorB -value 6
.cc.cycle1ColorBMB.menu add radiobutton -label "Convert:K4" -command CccCycle1ColorB -variable ccCycle1ColorB -value 7
.cc.cycle1ColorBMB.menu add radiobutton -label "0.0" -command CccCycle1ColorB -variable ccCycle1ColorB -value 31

#set ccCycle1ColorB 1
#set LccCycle1ColorB "Tex0 Color"

proc CccCycle1ColorB {} {
     global LccCycle1ColorB ccCycle1ColorB
     global fptr record
     set LccCycle1ColorB  [getCCcolorLabelB $ccCycle1ColorB]
     if {$record == 1} {
	puts $fptr "set ccCycle1ColorB $ccCycle1ColorB"
	puts $fptr "CccCycle1ColorB"
     }
	callback_ccCycle
	callback_send_dl
}


label .cc.cycle1ColorL) -width 5 -text ")   X"

menubutton .cc.cycle1ColorCMB -textvariable LccCycle1ColorC -width 12 \
-relief  raised -menu .cc.cycle1ColorCMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle1ColorCMB.menu
.cc.cycle1ColorCMB.menu add radiobutton -label "Comb Color" -command CccCycle1ColorC -variable ccCycle1ColorC -value 0
.cc.cycle1ColorCMB.menu add radiobutton -label "Tex0 Color" -command CccCycle1ColorC -variable ccCycle1ColorC -value 1
.cc.cycle1ColorCMB.menu add radiobutton -label "Tex1 Color" -command CccCycle1ColorC -variable ccCycle1ColorC -value 2
.cc.cycle1ColorCMB.menu add radiobutton -label "Prim Color" -command CccCycle1ColorC -variable ccCycle1ColorC -value 3
.cc.cycle1ColorCMB.menu add radiobutton -label "Shade Color" -command CccCycle1ColorC -variable ccCycle1ColorC -value 4
.cc.cycle1ColorCMB.menu add radiobutton -label "Env Color" -command CccCycle1ColorC -variable ccCycle1ColorC -value 5
.cc.cycle1ColorCMB.menu add radiobutton -label "Key:Scale" -command CccCycle1ColorC -variable ccCycle1ColorC -value 6
.cc.cycle1ColorCMB.menu add radiobutton -label "Comb Alpha" -command CccCycle1ColorC -variable ccCycle1ColorC -value 7
.cc.cycle1ColorCMB.menu add radiobutton -label "Tex0 Alpha" -command CccCycle1ColorC -variable ccCycle1ColorC -value 8
.cc.cycle1ColorCMB.menu add radiobutton -label "Tex1 Alpha" -command CccCycle1ColorC -variable ccCycle1ColorC -value 9
.cc.cycle1ColorCMB.menu add radiobutton -label "Prim Alpha" -command CccCycle1ColorC -variable ccCycle1ColorC -value 10
.cc.cycle1ColorCMB.menu add radiobutton -label "Shade Alpha" -command CccCycle1ColorC -variable ccCycle1ColorC -value 11
.cc.cycle1ColorCMB.menu add radiobutton -label "Env Alpha" -command CccCycle1ColorC -variable ccCycle1ColorC -value 12
.cc.cycle1ColorCMB.menu add radiobutton -label "LOD Frac" -command CccCycle1ColorC -variable ccCycle1ColorC -value 13
.cc.cycle1ColorCMB.menu add radiobutton -label "Prim LOD Frac" -command CccCycle1ColorC -variable ccCycle1ColorC -value 14
.cc.cycle1ColorCMB.menu add radiobutton -label "Convert:K5" -command CccCycle1ColorC -variable ccCycle1ColorC -value 15
.cc.cycle1ColorCMB.menu add radiobutton -label "0.0" -command CccCycle1ColorC -variable ccCycle1ColorC -value 31

#set ccCycle1ColorC "LOD Frac"
#set LccCycle1ColorC "LOD Frac"

proc CccCycle1ColorC {} {
     global LccCycle1ColorC ccCycle1ColorC
     global fptr record
     set LccCycle1ColorC  [getCCcolorLabelC $ccCycle1ColorC]
     if {$record == 1} {
	puts $fptr "set ccCycle1ColorC $ccCycle1ColorC"
	puts $fptr "CccCycle1ColorC"
     }
	callback_ccCycle
	callback_send_dl
}


label .cc.cycle1ColorL+ -width 1 -text "+"

menubutton .cc.cycle1ColorDMB -textvariable LccCycle1ColorD -width 12 \
-relief  raised -menu .cc.cycle1ColorDMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle1ColorDMB.menu
.cc.cycle1ColorDMB.menu add radiobutton -label "Comb Color" -command CccCycle1ColorD -variable ccCycle1ColorD -value 0
.cc.cycle1ColorDMB.menu add radiobutton -label "Tex0 Color" -command CccCycle1ColorD -variable ccCycle1ColorD -value 1
.cc.cycle1ColorDMB.menu add radiobutton -label "Tex1 Color" -command CccCycle1ColorD -variable ccCycle1ColorD -value 2
.cc.cycle1ColorDMB.menu add radiobutton -label "Prim Color" -command CccCycle1ColorD -variable ccCycle1ColorD -value 3
.cc.cycle1ColorDMB.menu add radiobutton -label "Shade Color" -command CccCycle1ColorD -variable ccCycle1ColorD -value 4
.cc.cycle1ColorDMB.menu add radiobutton -label "Env Color" -command CccCycle1ColorD -variable ccCycle1ColorD -value 5
.cc.cycle1ColorDMB.menu add radiobutton -label "1.0" -command CccCycle1ColorD -variable ccCycle1ColorD -value 6
.cc.cycle1ColorDMB.menu add radiobutton -label "0.0" -command CccCycle1ColorD -variable ccCycle1ColorD -value 31

#set ccCycle1ColorD 1
#set LccCycle1ColorD "Tex0 Color"

proc CccCycle1ColorD {} {
     global LccCycle1ColorD ccCycle1ColorD
     global fptr record
     set LccCycle1ColorD  [getCCcolorLabelD $ccCycle1ColorD]
     if {$record == 1} {
	puts $fptr "set ccCycle1ColorD $ccCycle1ColorD"
	puts $fptr "CccCycle1ColorD"
     }
	callback_ccCycle
	callback_send_dl
}

#----------------------------- cycle 0 color ------------------------------
label .cc.cycle0ColorL -width 11 -text "cycle0 Color"

label .cc.cycle0ColorL( -width 5 -text "=   ("

menubutton .cc.cycle0ColorAMB -textvariable LccCycle0ColorA -width 12 \
-relief  raised -menu .cc.cycle0ColorAMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle0ColorAMB.menu
.cc.cycle0ColorAMB.menu add radiobutton -label "Comb Color" -command CccCycle0ColorA  -variable ccCycle0ColorA -value 0
.cc.cycle0ColorAMB.menu add radiobutton -label "Tex0 Color" -command CccCycle0ColorA -variable ccCycle0ColorA -value 1
.cc.cycle0ColorAMB.menu add radiobutton -label "Tex1 Color" -command CccCycle0ColorA -variable ccCycle0ColorA -value 2
.cc.cycle0ColorAMB.menu add radiobutton -label "Prim Color" -command CccCycle0ColorA -variable ccCycle0ColorA -value 3
.cc.cycle0ColorAMB.menu add radiobutton -label "Shade Color" -command CccCycle0ColorA -variable ccCycle0ColorA -value 4
.cc.cycle0ColorAMB.menu add radiobutton -label "Env Color" -command CccCycle0ColorA -variable ccCycle0ColorA -value 5
.cc.cycle0ColorAMB.menu add radiobutton -label "Noise" -command CccCycle0ColorA -variable ccCycle0ColorA -value 7
.cc.cycle0ColorAMB.menu add radiobutton -label "1.0" -command CccCycle0ColorA -variable ccCycle0ColorA -value 6
.cc.cycle0ColorAMB.menu add radiobutton -label "0.0" -command CccCycle0ColorA -variable ccCycle0ColorA -value 31

#set ccCycle0ColorA 2
#set LccCycle0ColorA "Tex1 Color"

proc CccCycle0ColorA {} {
     global LccCycle0ColorA ccCycle0ColorA
     global fptr record
     global rspCycleType ccCycle1ColorA
     set LccCycle0ColorA  [getCCcolorLabelA $ccCycle0ColorA]
     if {$record == 1} {
	puts $fptr "set ccCycle0ColorA $ccCycle0ColorA"
	puts $fptr "CccCycle0ColorA"
     }
	if {$rspCycleType  == 0} {
		set ccCycle1ColorA $ccCycle0ColorA
		CccCycle1ColorA
	}
	callback_ccCycle
	callback_send_dl
}


label .cc.cycle0ColorL- -width 1 -text "-"

menubutton .cc.cycle0ColorBMB -textvariable LccCycle0ColorB -width 12 \
-relief  raised -menu .cc.cycle0ColorBMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle0ColorBMB.menu
.cc.cycle0ColorBMB.menu add radiobutton -label "Comb Color" -command CccCycle0ColorB -variable ccCycle0ColorB -value 0
.cc.cycle0ColorBMB.menu add radiobutton -label "Tex0 Color" -command CccCycle0ColorB -variable ccCycle0ColorB -value 1
.cc.cycle0ColorBMB.menu add radiobutton -label "Tex1 Color" -command CccCycle0ColorB -variable ccCycle0ColorB -value 2
.cc.cycle0ColorBMB.menu add radiobutton -label "Prim Color" -command CccCycle0ColorB -variable ccCycle0ColorB -value 3
.cc.cycle0ColorBMB.menu add radiobutton -label "Shade Color" -command CccCycle0ColorB -variable ccCycle0ColorB -value 4
.cc.cycle0ColorBMB.menu add radiobutton -label "Env Color" -command CccCycle0ColorB -variable ccCycle0ColorB -value 5
.cc.cycle0ColorBMB.menu add radiobutton -label "Key:Center" -command CccCycle0ColorB -variable ccCycle0ColorB -value 6
.cc.cycle0ColorBMB.menu add radiobutton -label "Convert:K4" -command CccCycle0ColorB -variable ccCycle0ColorB -value 7
.cc.cycle0ColorBMB.menu add radiobutton -label "0.0" -command CccCycle0ColorB -variable ccCycle0ColorB -value 31

#set ccCycle0ColorB "Tex0 Color"
#set LccCycle0ColorB "Tex0 Color"

proc CccCycle0ColorB {} {
     global LccCycle0ColorB ccCycle0ColorB
     global fptr record
     global rspCycleType ccCycle1ColorB
     set LccCycle0ColorB  [getCCcolorLabelB $ccCycle0ColorB]
     if {$record == 1} {
	puts $fptr "set ccCycle0ColorB $ccCycle0ColorB"
	puts $fptr "CccCycle0ColorB"
     }

	if {$rspCycleType  == 0} {
		set ccCycle1ColorB $ccCycle0ColorB
		CccCycle1ColorB
	}
	callback_ccCycle
	callback_send_dl

}

label .cc.cycle0ColorL) -width 5 -text ")   X"

menubutton .cc.cycle0ColorCMB -textvariable LccCycle0ColorC -width 12 \
-relief  raised -menu .cc.cycle0ColorCMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle0ColorCMB.menu
.cc.cycle0ColorCMB.menu add radiobutton -label "Comb Color" -command CccCycle0ColorC -variable ccCycle0ColorC -value 0
.cc.cycle0ColorCMB.menu add radiobutton -label "Tex0 Color" -command CccCycle0ColorC -variable ccCycle0ColorC -value 1
.cc.cycle0ColorCMB.menu add radiobutton -label "Tex1 Color" -command CccCycle0ColorC -variable ccCycle0ColorC -value 2
.cc.cycle0ColorCMB.menu add radiobutton -label "Prim Color" -command CccCycle0ColorC -variable ccCycle0ColorC -value 3
.cc.cycle0ColorCMB.menu add radiobutton -label "Shade Color" -command CccCycle0ColorC -variable ccCycle0ColorC -value 4
.cc.cycle0ColorCMB.menu add radiobutton -label "Env Color" -command CccCycle0ColorC -variable ccCycle0ColorC -value 5
.cc.cycle0ColorCMB.menu add radiobutton -label "Key:Scale" -command CccCycle0ColorC -variable ccCycle0ColorC -value 6
.cc.cycle0ColorCMB.menu add radiobutton -label "Comb Alpha" -command CccCycle0ColorC -variable ccCycle0ColorC -value 7
.cc.cycle0ColorCMB.menu add radiobutton -label "Tex0 Alpha" -command CccCycle0ColorC -variable ccCycle0ColorC -value 8
.cc.cycle0ColorCMB.menu add radiobutton -label "Tex1 Alpha" -command CccCycle0ColorC -variable ccCycle0ColorC -value 9
.cc.cycle0ColorCMB.menu add radiobutton -label "Prim Alpha" -command CccCycle0ColorC -variable ccCycle0ColorC -value 10
.cc.cycle0ColorCMB.menu add radiobutton -label "Shade Alpha" -command CccCycle0ColorC  -variable ccCycle0ColorC -value 11
.cc.cycle0ColorCMB.menu add radiobutton -label "Env Alpha" -command CccCycle0ColorC -variable ccCycle0ColorC -value 12
.cc.cycle0ColorCMB.menu add radiobutton -label "LOD Frac" -command CccCycle0ColorC -variable ccCycle0ColorC -value 13
.cc.cycle0ColorCMB.menu add radiobutton -label "Prim LOD Frac" -command CccCycle0ColorC -variable ccCycle0ColorC -value 14
.cc.cycle0ColorCMB.menu add radiobutton -label "Convert:K5" -command CccCycle0ColorC -variable ccCycle0ColorC -value 15
.cc.cycle0ColorCMB.menu add radiobutton -label "0.0" -command CccCycle0ColorC -variable ccCycle0ColorC -value 31

#set ccCycle0ColorC 13
#set LccCycle0ColorC "LOD Frac"

proc CccCycle0ColorC {} {
     global LccCycle0ColorC ccCycle0ColorC
     global fptr record
     global rspCycleType ccCycle1ColorC
     set LccCycle0ColorC  [getCCcolorLabelC $ccCycle0ColorC]
     if {$record == 1} {
	puts $fptr "set ccCycle0ColorC $ccCycle0ColorC"
	puts $fptr "CccCycle0ColorC"
     }
	if {$rspCycleType  == 0} {
		set ccCycle1ColorC $ccCycle0ColorC
		CccCycle1ColorC
	}
	callback_ccCycle
	callback_send_dl
}

label .cc.cycle0ColorL+ -width 1 -text "+"

menubutton .cc.cycle0ColorDMB -textvariable LccCycle0ColorD -width 12 \
-relief  raised -menu .cc.cycle0ColorDMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle0ColorDMB.menu
.cc.cycle0ColorDMB.menu add radiobutton -label "Comb Color" -command CccCycle0ColorD -variable ccCycle0ColorD -value 0
.cc.cycle0ColorDMB.menu add radiobutton -label "Tex0 Color" -command CccCycle0ColorD -variable ccCycle0ColorD -value 1
.cc.cycle0ColorDMB.menu add radiobutton -label "Tex1 Color" -command CccCycle0ColorD -variable ccCycle0ColorD -value 2
.cc.cycle0ColorDMB.menu add radiobutton -label "Prim Color" -command CccCycle0ColorD -variable ccCycle0ColorD -value 3
.cc.cycle0ColorDMB.menu add radiobutton -label "Shade Color" -command CccCycle0ColorD -variable ccCycle0ColorD -value 4
.cc.cycle0ColorDMB.menu add radiobutton -label "Env Color" -command CccCycle0ColorD -variable ccCycle0ColorD -value 5
.cc.cycle0ColorDMB.menu add radiobutton -label "1.0" -command CccCycle0ColorD -variable ccCycle0ColorD -value 6
.cc.cycle0ColorDMB.menu add radiobutton -label "0.0" -command CccCycle0ColorD -variable ccCycle0ColorD -value 31

#set ccCycle0ColorD 1
#set LccCycle0ColorD "Tex0 Color"

proc CccCycle0ColorD {} {
     global LccCycle0ColorD ccCycle0ColorD
     global fptr record
     global  rspCycleType ccCycle1ColorD
     set LccCycle0ColorD  [getCCcolorLabelD $ccCycle0ColorD]
     if {$record == 1} {
	puts $fptr "set ccCycle0ColorD $ccCycle0ColorD"
	puts $fptr "CccCycle0ColorD"
     }
	if {$rspCycleType  == 0} {
		set ccCycle1ColorD $ccCycle0ColorD
		CccCycle1ColorD
	}
	callback_ccCycle
	callback_send_dl
}


#---------------------------------------------------------------------------#
label .cc.cycle1AlphaL -width 11 -text "cycle1 Alpha"

label .cc.cycle1AlphaL( -width 5 -text "=   ("

menubutton .cc.cycle1AlphaAMB -textvariable LccCycle1AlphaA -width 12 \
-relief  raised -menu .cc.cycle1AlphaAMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle1AlphaAMB.menu
.cc.cycle1AlphaAMB.menu add radiobutton -label "Comb Alpha" -command CccCycle1AlphaA -variable ccCycle1AlphaA -value 0
.cc.cycle1AlphaAMB.menu add radiobutton -label "Tex0 Alpha" -command CccCycle1AlphaA -variable ccCycle1AlphaA -value 1
.cc.cycle1AlphaAMB.menu add radiobutton -label "Tex1 Alpha" -command CccCycle1AlphaA -variable ccCycle1AlphaA -value 2
.cc.cycle1AlphaAMB.menu add radiobutton -label "Prim Alpha" -command CccCycle1AlphaA -variable ccCycle1AlphaA -value 3
.cc.cycle1AlphaAMB.menu add radiobutton -label "Shade Alpha" -command CccCycle1AlphaA -variable ccCycle1AlphaA -value 4
.cc.cycle1AlphaAMB.menu add radiobutton -label "Env Alpha" -command CccCycle1AlphaA -variable ccCycle1AlphaA -value 5
.cc.cycle1AlphaAMB.menu add radiobutton -label "1.0" -command CccCycle1AlphaA -variable ccCycle1AlphaA -value 6
.cc.cycle1AlphaAMB.menu add radiobutton -label "0.0" -command CccCycle1AlphaA -variable ccCycle1AlphaA -value 7

#set ccCycle1AlphaA 2
#set LccCycle1AlphaA "Tex1 Alpha"

proc CccCycle1AlphaA {} {
     global LccCycle1AlphaA ccCycle1AlphaA
     global fptr record
     set LccCycle1AlphaA  [getCCalphaLabelA $ccCycle1AlphaA]
     if {$record == 1} {
	puts $fptr "set ccCycle1AlphaA $ccCycle1AlphaA"
	puts $fptr "CccCycle1AlphaA"
     }
	callback_ccCycle
	callback_send_dl
}


label .cc.cycle1AlphaL- -width 1 -text "-"

menubutton .cc.cycle1AlphaBMB -textvariable LccCycle1AlphaB -width 12 \
-relief  raised -menu .cc.cycle1AlphaBMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle1AlphaBMB.menu
.cc.cycle1AlphaBMB.menu add radiobutton -label "Comb Alpha" -command CccCycle1AlphaB -variable ccCycle1AlphaB -value 0
.cc.cycle1AlphaBMB.menu add radiobutton -label "Tex0 Alpha" -command CccCycle1AlphaB -variable ccCycle1AlphaB -value 1
.cc.cycle1AlphaBMB.menu add radiobutton -label "Tex1 Alpha" -command CccCycle1AlphaB -variable ccCycle1AlphaB -value 2
.cc.cycle1AlphaBMB.menu add radiobutton -label "Prim Alpha" -command CccCycle1AlphaB -variable ccCycle1AlphaB -value 3
.cc.cycle1AlphaBMB.menu add radiobutton -label "Shade Alpha" -command CccCycle1AlphaB -variable ccCycle1AlphaB -value 4
.cc.cycle1AlphaBMB.menu add radiobutton -label "Env Alpha" -command CccCycle1AlphaB -variable ccCycle1AlphaB -value 5
.cc.cycle1AlphaBMB.menu add radiobutton -label "1.0" -command CccCycle1AlphaB -variable ccCycle1AlphaB -value 6
.cc.cycle1AlphaBMB.menu add radiobutton -label "0.0" -command CccCycle1AlphaB -variable ccCycle1AlphaB -value 7

#set ccCycle1AlphaB 1
#set LccCycle1AlphaB "Tex0 Alpha"

proc CccCycle1AlphaB {} {
     global LccCycle1AlphaB ccCycle1AlphaB
     global fptr record
     set LccCycle1AlphaB  [getCCalphaLabelB $ccCycle1AlphaB]
     if {$record == 1} {
	puts $fptr "set ccCycle1AlphaB $ccCycle1AlphaB"
	puts $fptr "CccCycle1AlphaB"
     }
	callback_ccCycle
	callback_send_dl
}


label .cc.cycle1AlphaL) -width 5 -text ")   X"

menubutton .cc.cycle1AlphaCMB -textvariable LccCycle1AlphaC -width 12 \
-relief  raised -menu .cc.cycle1AlphaCMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle1AlphaCMB.menu
.cc.cycle1AlphaCMB.menu add radiobutton -label "Tex0 Alpha" -command CccCycle1AlphaC -variable ccCycle1AlphaC -value 1
.cc.cycle1AlphaCMB.menu add radiobutton -label "Tex1 Alpha" -command CccCycle1AlphaC -variable ccCycle1AlphaC -value 2
.cc.cycle1AlphaCMB.menu add radiobutton -label "Prim Alpha" -command CccCycle1AlphaC -variable ccCycle1AlphaC -value 3
.cc.cycle1AlphaCMB.menu add radiobutton -label "Shade Alpha" -command CccCycle1AlphaC -variable ccCycle1AlphaC -value 4
.cc.cycle1AlphaCMB.menu add radiobutton -label "Env Alpha" -command CccCycle1AlphaC -variable ccCycle1AlphaC -value 5
.cc.cycle1AlphaCMB.menu add radiobutton -label "LOD Frac" -command CccCycle1AlphaC -variable ccCycle1AlphaC -value 0
.cc.cycle1AlphaCMB.menu add radiobutton -label "Prim LOD Frac" -command CccCycle1AlphaC -variable ccCycle1AlphaC -value 6
.cc.cycle1AlphaCMB.menu add radiobutton -label "0.0" -command CccCycle1AlphaC -variable ccCycle1AlphaC -value 7

#set ccCycle1AlphaC 0
#set LccCycle1AlphaC "LOD Frac"

proc CccCycle1AlphaC {} {
     global LccCycle1AlphaC ccCycle1AlphaC
     global fptr record
     set LccCycle1AlphaC  [getCCalphaLabelC $ccCycle1AlphaC]
     if {$record == 1} {
	puts $fptr "set ccCycle1AlphaC $ccCycle1AlphaC"
	puts $fptr "CccCycle1AlphaC"
     }
	callback_ccCycle
	callback_send_dl
}


label .cc.cycle1AlphaL+ -width 1 -text "+"

menubutton .cc.cycle1AlphaDMB -textvariable LccCycle1AlphaD -width 12 \
-relief  raised -menu .cc.cycle1AlphaDMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle1AlphaDMB.menu
.cc.cycle1AlphaDMB.menu add radiobutton -label "Comb Alpha" -command CccCycle1AlphaD -variable ccCycle1AlphaD -value 0
.cc.cycle1AlphaDMB.menu add radiobutton -label "Tex0 Alpha" -command CccCycle1AlphaD -variable ccCycle1AlphaD -value 1
.cc.cycle1AlphaDMB.menu add radiobutton -label "Tex1 Alpha" -command CccCycle1AlphaD -variable ccCycle1AlphaD -value 2
.cc.cycle1AlphaDMB.menu add radiobutton -label "Prim Alpha" -command CccCycle1AlphaD -variable ccCycle1AlphaD -value 3
.cc.cycle1AlphaDMB.menu add radiobutton -label "Shade Alpha" -command CccCycle1AlphaD -variable ccCycle1AlphaD -value 4
.cc.cycle1AlphaDMB.menu add radiobutton -label "Env Alpha" -command CccCycle1AlphaD -variable ccCycle1AlphaD -value 5
.cc.cycle1AlphaDMB.menu add radiobutton -label "1.0" -command CccCycle1AlphaD -variable ccCycle1AlphaD -value 6
.cc.cycle1AlphaDMB.menu add radiobutton -label "0.0" -command CccCycle1AlphaD -variable ccCycle1AlphaD -value 7

#set ccCycle1AlphaD 1
#set LccCycle1AlphaD "Tex0 Alpha"

proc CccCycle1AlphaD {} {
     global LccCycle1AlphaD ccCycle1AlphaD
     global fptr record
     set LccCycle1AlphaD  [getCCalphaLabelD $ccCycle1AlphaD]
     if {$record == 1} {
	puts $fptr "set ccCycle1AlphaD $ccCycle1AlphaD"
	puts $fptr "CccCycle1AlphaD"
     }
	callback_ccCycle
	callback_send_dl
}

#---------------------------------------------------------------------------#
label .cc.cycle0AlphaL -width 11 -text "cycle0 Alpha"

label .cc.cycle0AlphaL( -width 5 -text "=   ("

menubutton .cc.cycle0AlphaAMB -textvariable LccCycle0AlphaA -width 12 \
-relief  raised -menu .cc.cycle0AlphaAMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle0AlphaAMB.menu
.cc.cycle0AlphaAMB.menu add radiobutton -label "Comb Alpha" -command CccCycle0AlphaA -variable ccCycle0AlphaA -value 0
.cc.cycle0AlphaAMB.menu add radiobutton -label "Tex0 Alpha" -command CccCycle0AlphaA -variable ccCycle0AlphaA -value 1
.cc.cycle0AlphaAMB.menu add radiobutton -label "Tex1 Alpha" -command CccCycle0AlphaA -variable ccCycle0AlphaA -value 2
.cc.cycle0AlphaAMB.menu add radiobutton -label "Prim Alpha" -command CccCycle0AlphaA -variable ccCycle0AlphaA -value 3
.cc.cycle0AlphaAMB.menu add radiobutton -label "Shade Alpha" -command CccCycle0AlphaA -variable ccCycle0AlphaA -value 4
.cc.cycle0AlphaAMB.menu add radiobutton -label "Env Alpha" -command CccCycle0AlphaA -variable ccCycle0AlphaA -value 5
.cc.cycle0AlphaAMB.menu add radiobutton -label "1.0" -command CccCycle0AlphaA -variable ccCycle0AlphaA -value 6
.cc.cycle0AlphaAMB.menu add radiobutton -label "0.0" -command CccCycle0AlphaA -variable ccCycle0AlphaA -value 7

#set ccCycle0AlphaA 2
#set LccCycle0AlphaA "Tex1 Alpha"

proc CccCycle0AlphaA {} {
     global LccCycle0AlphaA ccCycle0AlphaA
     global fptr record
     global rspCycleType ccCycle1AlphaA
     set LccCycle0AlphaA  [getCCalphaLabelA $ccCycle0AlphaA]
     if {$record == 1} {
	puts $fptr "set ccCycle0AlphaA $ccCycle0AlphaA"
	puts $fptr "CccCycle0AlphaA"
     }
	if {$rspCycleType  == 0} {
		set ccCycle1AlphaA $ccCycle0AlphaA
		CccCycle1AlphaA
	}
	callback_ccCycle
	callback_send_dl
}



label .cc.cycle0AlphaL- -width 1 -text "-"

menubutton .cc.cycle0AlphaBMB -textvariable LccCycle0AlphaB -width 12 \
-relief  raised -menu .cc.cycle0AlphaBMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle0AlphaBMB.menu
.cc.cycle0AlphaBMB.menu add radiobutton -label "Comb Alpha" -command CccCycle0AlphaB -variable ccCycle0AlphaB -value 0
.cc.cycle0AlphaBMB.menu add radiobutton -label "Tex0 Alpha" -command CccCycle0AlphaB -variable ccCycle0AlphaB -value 1
.cc.cycle0AlphaBMB.menu add radiobutton -label "Tex1 Alpha" -command CccCycle0AlphaB -variable ccCycle0AlphaB -value 2
.cc.cycle0AlphaBMB.menu add radiobutton -label "Prim Alpha" -command CccCycle0AlphaB -variable ccCycle0AlphaB -value 3
.cc.cycle0AlphaBMB.menu add radiobutton -label "Shade Alpha" -command CccCycle0AlphaB -variable ccCycle0AlphaB -value 4
.cc.cycle0AlphaBMB.menu add radiobutton -label "Env Alpha" -command CccCycle0AlphaB -variable ccCycle0AlphaB -value 5
.cc.cycle0AlphaBMB.menu add radiobutton -label "1.0" -command CccCycle0AlphaB -variable ccCycle0AlphaB -value 6
.cc.cycle0AlphaBMB.menu add radiobutton -label "0.0" -command CccCycle0AlphaB -variable ccCycle0AlphaB -value 7

#set ccCycle0AlphaB 1
#set LccCycle0AlphaB "Tex0 Alpha"

proc CccCycle0AlphaB {} {
     global LccCycle0AlphaB ccCycle0AlphaB
     global fptr record
     global rspCycleType ccCycle1AlphaB
     set LccCycle0AlphaB  [getCCalphaLabelB $ccCycle0AlphaB]
     if {$record == 1} {
	puts $fptr "set ccCycle0AlphaB $ccCycle0AlphaB"
	puts $fptr "CccCycle0AlphaB"
     }
	if {$rspCycleType  == 0} {
		set ccCycle1AlphaB $ccCycle0AlphaB
		CccCycle1AlphaB
	}
	callback_ccCycle
	callback_send_dl
}



label .cc.cycle0AlphaL) -width 5 -text ")   X"

menubutton .cc.cycle0AlphaCMB -textvariable LccCycle0AlphaC -width 12 \
-relief  raised -menu .cc.cycle0AlphaCMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle0AlphaCMB.menu
.cc.cycle0AlphaCMB.menu add radiobutton -label "Tex0 Alpha" -command CccCycle0AlphaC -variable ccCycle0AlphaC -value 1
.cc.cycle0AlphaCMB.menu add radiobutton -label "Tex1 Alpha" -command CccCycle0AlphaC -variable ccCycle0AlphaC -value 2
.cc.cycle0AlphaCMB.menu add radiobutton -label "Prim Alpha" -command CccCycle0AlphaC -variable ccCycle0AlphaC -value 3
.cc.cycle0AlphaCMB.menu add radiobutton -label "Shade Alpha" -command CccCycle0AlphaC -variable ccCycle0AlphaC -value 4
.cc.cycle0AlphaCMB.menu add radiobutton -label "Env Alpha" -command CccCycle0AlphaC -variable ccCycle0AlphaC -value 5
.cc.cycle0AlphaCMB.menu add radiobutton -label "LOD Frac" -command CccCycle0AlphaC -variable ccCycle0AlphaC -value  0
.cc.cycle0AlphaCMB.menu add radiobutton -label "Prim LOD Frac" -command CccCycle0AlphaC -variable ccCycle0AlphaC -value 6
.cc.cycle0AlphaCMB.menu add radiobutton -label "0.0" -command CccCycle0AlphaC -variable ccCycle0AlphaC -value 7

#set ccCycle0AlphaC 0
#set LccCycle0AlphaC "LOD Frac"

proc CccCycle0AlphaC {} {
     global LccCycle0AlphaC ccCycle0AlphaC
     global fptr record
     global rspCycleType ccCycle1AlphaC
     set LccCycle0AlphaC  [getCCalphaLabelC $ccCycle0AlphaC]
     if {$record == 1} {
	puts $fptr "set ccCycle0AlphaC $ccCycle0AlphaC"
	puts $fptr "CccCycle0AlphaC"
     }
	if {$rspCycleType  == 0} {
		set ccCycle1AlphaC $ccCycle0AlphaC
		CccCycle1AlphaC
	}
	callback_ccCycle
	callback_send_dl
}

label .cc.cycle0AlphaL+ -width 1 -text "+"

menubutton .cc.cycle0AlphaDMB -textvariable LccCycle0AlphaD -width 12 \
-relief  raised -menu .cc.cycle0AlphaDMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle0AlphaDMB.menu
.cc.cycle0AlphaDMB.menu add radiobutton -label "Comb Alpha" -command CccCycle0AlphaD -variable ccCycle0AlphaD -value 0
.cc.cycle0AlphaDMB.menu add radiobutton -label "Tex0 Alpha" -command CccCycle0AlphaD -variable ccCycle0AlphaD -value 1
.cc.cycle0AlphaDMB.menu add radiobutton -label "Tex1 Alpha" -command CccCycle0AlphaD -variable ccCycle0AlphaD -value 2
.cc.cycle0AlphaDMB.menu add radiobutton -label "Prim Alpha" -command CccCycle0AlphaD -variable ccCycle0AlphaD -value 3
.cc.cycle0AlphaDMB.menu add radiobutton -label "Shade Alpha" -command CccCycle0AlphaD -variable ccCycle0AlphaD -value 4
.cc.cycle0AlphaDMB.menu add radiobutton -label "Env Alpha" -command CccCycle0AlphaD -variable ccCycle0AlphaD -value 5
.cc.cycle0AlphaDMB.menu add radiobutton -label "1.0" -command CccCycle0AlphaD -variable ccCycle0AlphaD -value 6
.cc.cycle0AlphaDMB.menu add radiobutton -label "0.0" -command CccCycle0AlphaD -variable ccCycle0AlphaD -value 7

#set ccCycle0AlphaD 1
#set LccCycle0AlphaD "Tex0 Alpha"

proc CccCycle0AlphaD {} {
     global LccCycle0AlphaD ccCycle0AlphaD
     global fptr record
     global rspCycleType ccCycle1AlphaD
     set LccCycle0AlphaD  [getCCalphaLabelD $ccCycle0AlphaD]
     if {$record == 1} {
	puts $fptr "set ccCycle0AlphaD $ccCycle0AlphaD"
	puts $fptr "CccCycle0AlphaD"
     }
	if {$rspCycleType  == 0} {
		set ccCycle1AlphaD $ccCycle0AlphaD
		CccCycle1AlphaD
	}
	callback_ccCycle
	callback_send_dl
}

#--------------------preset modes-------------------------------------------------

# 			  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 
set ccCycle0presetColorA {31 31  1  1  1  1  1  1  1  1  1  1  1  1 31 31  5  5  5  1  1  6  6  5  5  3  3  3 31  5  5  2  1  1  2}
set ccCycle0presetColorB {31 31 31 31 31 31 31 31 31 31 31 31 31 31 31 31  4  4  4  4  4 31 31 31 31  4  4  4
31  3  3  1 31  7  7}
set ccCycle0presetColorC {31 31  4  4  4  4  4  4  3  3  3  3  3  3 31 31  1  1  1  8  8  1  1  1  1  1  1  1 31  1  1 13  2 15 15}
set ccCycle0presetColorD {3  4 31 31 31 31 31 31 31 31 31 31 31 31  1  1  4  4  4  4  4  4  4  4  4  4  4  4 4  3  3  1 31  1  2}

set ccCycle0presetAlphaA {7  7  7  1  7  7  1  7  7  1  7  7  1  1  7  7  7  1  7  7  7  7  7  7  7  7  3  7 7  1  7  2  1  7  7}
set ccCycle0presetAlphaB {7  7  7  7  7  7  7  7  7  7  7  7  7  7  7  7  7  7  7  7  7  7  7  7  7  7  4  7 7  7  7  1  7  7  7}
set ccCycle0presetAlphaC {7  7  7  4  7  7  4  7  7  3  7  7  3  3  7  7  7  4  7  7  7  7  7  7  7  7  1  7 7  4  7  0  2  7  7}
set ccCycle0presetAlphaD {3  4  4  7  1  4  7  1  3  7  1  3  7  7  4  1  4  7  1  4  1  4  1  4  1  4  4  1 1  7  1  1  7  4  7}
 
set ccCycle1presetColorA {31  0  0  0  0  0  0  0  0 31  5  5  1  5  5  5  5}
set ccCycle1presetColorB {31 31 31 31 31 31 31 31 31 31  4  4  6  0  0  0  0}
set ccCycle1presetColorC {31  4  4  4  4  3  3  3  3 31  0  0  6  1  1  1  1}
set ccCycle1presetColorD { 0 31 31 31 31 31 31 31 31  0  4  4 31  0  0  0  0}
 
set ccCycle1presetAlphaA { 7  7  0  7  0  7  0  7  0  7  7  0  7  7  5  7  7}
set ccCycle1presetAlphaB { 7  7  7  7  7  7  7  7  7  7  7  7  7  7  0  7  7}
set ccCycle1presetAlphaC { 7  7  4  7  4  7  3  7  3  7  7  4  7  7  1  7  7}
set ccCycle1presetAlphaD { 0  4  7  4  7  3  7  3  7  4  4  7  7  4  0  1  0}

proc get_ccCycle0presetLabel val {
  switch $val {
	0 {return PRIM}
	1 {return SHADE}
	2 {return MOD_I}
	3 {return MOD_IA}
	4 {return MOD_I_DEC_A}
	5 {return MOD_RGB}
	6 {return MOD_RGBA}
	7 {return MOD_RGB_DEC_A}
	8 {return MOD_I_PRIM}
	9 {return MOD_IA_PRIM}
	10 {return MOD_I_DEC_A_PRIM}
	11 {return MOD_RGB_PRIM}
	12 {return MOD_RGBA_PRIM}
	13 {return MOD_RGB_DEC_A_PRIM}
	14 {return DEC_RGB}
	15 {return DEC_RGBA}
	16 {return BLEND_I}
	17 {return BLEND_IA}
	18 {return BLEND_I_DEC_A}
	19 {return BLEND_RGBA}
	20 {return BLEND_RGB_DECL_A}
	21 {return ADD_RGB}
	22 {return ADD_RGB_DEC_A}
	23 {return REFLECT_RGB}
	24 {return REFLECT_RGB_DEC_A}
	25 {return HILITE_RGB}
	26 {return HILITE_RGBA}
	27 {return HILITE_RGB_DEC_A}
	28 {return SHADE_DEC_A}
	29 {return BLEND_PE}
	30 {return BLEND_PE_DEC_A}
	31 {return TRILERP}
	32 {return INTERFERENCE}
	33 {return 1CY_YUV2RGB}
	34 {return YUV2RGB}
  }
}

proc get_ccCycle1presetLabel val {
  switch $val {
	0 {return "PASS2"}
	1 {return "MOD_I2"}
	2 {return "MOD_IA2"}
	3 {return "MOD_RGB2"}
	4 {return "MOD_RGBA2"}
	5 {return "MOD_I_PRIM2"}
	6 {return "MOD_IA_PRIM2"}
	7 {return "MOD_RGB_PRIM2"}
	8 {return "MOD_RGBA_PRIM2"}
	9 {return "DEC_RGB2"}
	10 {return "BLEND_I2"}
	11 {return "BLEND_IA2"}
	12 {return "CHROMA_KEY2"}
	13 {return "HILITE_RGB2"}
	14 {return "HILITE_RGBA2"}
	15 {return "HILITE_RGBA_DEC_A2"}
	16 {return "HILITE_RGB_PASS_A2"}
  }
}

label .cc.cycle1presetL -width 11 -text "cycle1 Modes"

menubutton .cc.cycle1presetMB -textvariable LccCycle1preset -width 22 \
-relief  raised -menu .cc.cycle1presetMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle1presetMB.menu
.cc.cycle1presetMB.menu add radiobutton -label "PASS2" -command CccCycle1preset -variable ccCycle1preset -value 0
.cc.cycle1presetMB.menu add radiobutton -label "MODULATEI2" -command CccCycle1preset -variable ccCycle1preset -value 1
.cc.cycle1presetMB.menu add radiobutton -label "MODULATEIA2" -command CccCycle1preset -variable ccCycle1preset -value 2
.cc.cycle1presetMB.menu add radiobutton -label "MODULATERGB2" -command CccCycle1preset -variable ccCycle1preset -value 3
.cc.cycle1presetMB.menu add radiobutton -label "MODULATERGBA2" -command CccCycle1preset -variable ccCycle1preset -value 4
.cc.cycle1presetMB.menu add radiobutton -label "MODULATEI_PRIM2" -command CccCycle1preset -variable ccCycle1preset -value 5
.cc.cycle1presetMB.menu add radiobutton -label "MODULATEIA_PRIM2" -command CccCycle1preset -variable ccCycle1preset -value 6
.cc.cycle1presetMB.menu add radiobutton -label "MODULATERGB_PRIM2" -command CccCycle1preset -variable ccCycle1preset -value 7
.cc.cycle1presetMB.menu add radiobutton -label "MODULATERGBA_PRIM2" -command CccCycle1preset -variable ccCycle1preset -value 8
.cc.cycle1presetMB.menu add radiobutton -label "DECALRGB2" -command CccCycle1preset -variable ccCycle1preset -value 9
.cc.cycle1presetMB.menu add radiobutton -label "BLENDI2" -command CccCycle1preset -variable ccCycle1preset -value 10
.cc.cycle1presetMB.menu add radiobutton -label "BLENDIA2" -command CccCycle1preset -variable ccCycle1preset -value 11
.cc.cycle1presetMB.menu add radiobutton -label "CHROMA_KEY2" -command CccCycle1preset -variable ccCycle1preset -value 12
.cc.cycle1presetMB.menu add radiobutton -label "HILITERGB2" -command CccCycle1preset -variable ccCycle1preset -value 13
.cc.cycle1presetMB.menu add radiobutton -label "HILITERGBA2" -command CccCycle1preset -variable ccCycle1preset -value 14
.cc.cycle1presetMB.menu add radiobutton -label "HILITERGBDECALA2" -command CccCycle1preset -variable ccCycle1preset -value 15
.cc.cycle1presetMB.menu add radiobutton -label "HILITERGBPASSA2" -command CccCycle1preset -variable ccCycle1preset -value 16

proc CccCycle1preset {} {
     global ccCycle1preset LccCycle1preset	
     global fptr record
     global ccCycle1presetColorA ccCycle1presetColorB ccCycle1presetColorC ccCycle1presetColorD
     global ccCycle1presetAlphaA ccCycle1presetAlphaB ccCycle1presetAlphaC ccCycle1presetAlphaD
     global ccCycle1ColorA ccCycle1ColorB ccCycle1ColorC ccCycle1ColorD
     global ccCycle1AlphaA ccCycle1AlphaB ccCycle1AlphaC ccCycle1AlphaD

     global rspCycleType ccCycle0preset
     global ccCycle0presetColorA ccCycle0presetAlphaA ccCycle0presetColorB
     global ccCycle0presetAlphaB ccCycle0presetColorC ccCycle0presetAlphaC
     global ccCycle0presetColorD ccCycle0presetAlphaD

     if {$rspCycleType == 1} {

     	set LccCycle1preset [get_ccCycle1presetLabel $ccCycle1preset]

     	set ccCycle1ColorA  [lindex $ccCycle1presetColorA $ccCycle1preset]
     	set ccCycle1AlphaA  [lindex $ccCycle1presetAlphaA $ccCycle1preset]
 		CccCycle1ColorA
 		CccCycle1AlphaA
     	set ccCycle1ColorB  [lindex $ccCycle1presetColorB $ccCycle1preset]
     	set ccCycle1AlphaB  [lindex $ccCycle1presetAlphaB $ccCycle1preset]
 		CccCycle1ColorB
 		CccCycle1AlphaB
     	set ccCycle1ColorC  [lindex $ccCycle1presetColorC $ccCycle1preset]
     	set ccCycle1AlphaC  [lindex $ccCycle1presetAlphaC $ccCycle1preset]
 		CccCycle1ColorC
 		CccCycle1AlphaC
     	set ccCycle1ColorD  [lindex $ccCycle1presetColorD $ccCycle1preset]
     	set ccCycle1AlphaD  [lindex $ccCycle1presetAlphaD $ccCycle1preset]
 		CccCycle1ColorD
 		CccCycle1AlphaD

	if {$record == 1} {
		puts $fptr "set ccCycle1preset $ccCycle1preset"
		puts $fptr "set LccCycle1preset $LccCycle1preset"
	}

     } else {

     	set LccCycle1preset [get_ccCycle0presetLabel $ccCycle0preset]

     	set ccCycle1ColorA  [lindex $ccCycle0presetColorA $ccCycle0preset]
     	set ccCycle1AlphaA  [lindex $ccCycle0presetAlphaA $ccCycle0preset]
     	set ccCycle1ColorB  [lindex $ccCycle0presetColorB $ccCycle0preset]
     	set ccCycle1AlphaB  [lindex $ccCycle0presetAlphaB $ccCycle0preset]
     	set ccCycle1ColorC  [lindex $ccCycle0presetColorC $ccCycle0preset]
     	set ccCycle1AlphaC  [lindex $ccCycle0presetAlphaC $ccCycle0preset]
     	set ccCycle1ColorD  [lindex $ccCycle0presetColorD $ccCycle0preset]
     	set ccCycle1AlphaD  [lindex $ccCycle0presetAlphaD $ccCycle0preset]

	if {$record == 1} {
		puts $fptr "set ccCycle1preset $ccCycle1preset"
		puts $fptr "set LccCycle1preset $LccCycle1preset"
	}

     }
}

label .cc.cycle0presetL -width 11 -text "cycle0 Modes"

menubutton .cc.cycle0presetMB -textvariable LccCycle0preset -width 22 \
-relief  raised -menu .cc.cycle0presetMB.menu -bg LightGray \
-activebackground LightGray -disabledforeground DarkGray

menu .cc.cycle0presetMB.menu
.cc.cycle0presetMB.menu add radiobutton -label "PRIMITIVE" -command CccCycle0preset -variable ccCycle0preset -value 0
.cc.cycle0presetMB.menu add radiobutton -label "SHADE" -command CccCycle0preset -variable ccCycle0preset -value 1
.cc.cycle0presetMB.menu add radiobutton -label "MODULATEI" -command CccCycle0preset -variable ccCycle0preset -value 2
.cc.cycle0presetMB.menu add radiobutton -label "MODULATEIA" -command CccCycle0preset -variable ccCycle0preset -value 3
.cc.cycle0presetMB.menu add radiobutton -label "MODULATEIDECALA" -command CccCycle0preset -variable ccCycle0preset -value 4
.cc.cycle0presetMB.menu add radiobutton -label "MODULATERGB" -command CccCycle0preset -variable ccCycle0preset -value 5
.cc.cycle0presetMB.menu add radiobutton -label "MODULATERGBA" -command CccCycle0preset -variable ccCycle0preset -value 6
.cc.cycle0presetMB.menu add radiobutton -label "MODULATERGBDECALA" -command CccCycle0preset -variable ccCycle0preset -value 7
.cc.cycle0presetMB.menu add radiobutton -label "MODULATEI_PRIM" -command CccCycle0preset -variable ccCycle0preset -value 8
.cc.cycle0presetMB.menu add radiobutton -label "MODULATEIA_PRIM" -command CccCycle0preset -variable ccCycle0preset -value 9
.cc.cycle0presetMB.menu add radiobutton -label "MODULATEIDECALA_PRIM" -command CccCycle0preset -variable ccCycle0preset -value 10
.cc.cycle0presetMB.menu add radiobutton -label "MODULATERGB_PRIM" -command CccCycle0preset -variable ccCycle0preset -value 11
.cc.cycle0presetMB.menu add radiobutton -label "MODULATERGBA_PRIM" -command CccCycle0preset -variable ccCycle0preset -value 12
.cc.cycle0presetMB.menu add radiobutton -label "MODULATERGBDECALA_PRIM" -command CccCycle0preset -variable ccCycle0preset -value 13
.cc.cycle0presetMB.menu add radiobutton -label "DECALRGB" -command CccCycle0preset -variable ccCycle0preset -value 14
.cc.cycle0presetMB.menu add radiobutton -label "DECALRGBA" -command CccCycle0preset -variable ccCycle0preset -value 15
.cc.cycle0presetMB.menu add radiobutton -label "BLENDI" -command CccCycle0preset -variable ccCycle0preset -value 16
.cc.cycle0presetMB.menu add radiobutton -label "BLENDIA" -command CccCycle0preset -variable ccCycle0preset -value 17
.cc.cycle0presetMB.menu add radiobutton -label "BLENDIDECALA" -command CccCycle0preset -variable ccCycle0preset -value 18
.cc.cycle0presetMB.menu add radiobutton -label "BLENDRGBA" -command CccCycle0preset -variable ccCycle0preset -value 19
.cc.cycle0presetMB.menu add radiobutton -label "BLENDRGBDECALA" -command CccCycle0preset -variable ccCycle0preset -value 20
.cc.cycle0presetMB.menu add radiobutton -label "ADDRGB" -command CccCycle0preset -variable ccCycle0preset -value 21
.cc.cycle0presetMB.menu add radiobutton -label "ADDRGBDECALA" -command CccCycle0preset -variable ccCycle0preset -value 22
.cc.cycle0presetMB.menu add radiobutton -label "REFLECTRGB" -command CccCycle0preset -variable ccCycle0preset -value 23
.cc.cycle0presetMB.menu add radiobutton -label "REFLECTRGBDECALA" -command CccCycle0preset -variable ccCycle0preset -value 24
.cc.cycle0presetMB.menu add radiobutton -label "HILITERGB " -command CccCycle0preset -variable ccCycle0preset -value 25
.cc.cycle0presetMB.menu add radiobutton -label "HILITERGBA" -command CccCycle0preset -variable ccCycle0preset -value 26
.cc.cycle0presetMB.menu add radiobutton -label "HILITERGBDECALA" -command CccCycle0preset -variable ccCycle0preset -value 27
.cc.cycle0presetMB.menu add radiobutton -label "SHADEDECALA" -command CccCycle0preset -variable ccCycle0preset -value 28
.cc.cycle0presetMB.menu add radiobutton -label "BLENDPE" -command CccCycle0preset -variable ccCycle0preset -value 29
.cc.cycle0presetMB.menu add radiobutton -label "BLENDPEDECALA" -command CccCycle0preset -variable ccCycle0preset -value 30

.cc.cycle0presetMB.menu add radiobutton -label "TRILERP" -command CccCycle0preset -variable ccCycle0preset -value 31
.cc.cycle0presetMB.menu add radiobutton -label "INTERFERENCE" -command CccCycle0preset -variable ccCycle0preset -value 32
.cc.cycle0presetMB.menu add radiobutton -label "1CYUV2RGB" -command CccCycle0preset -variable ccCycle0preset -value 33
.cc.cycle0presetMB.menu add radiobutton -label "YUV2RGB" -command CccCycle0preset -variable ccCycle0preset -value 34

proc CccCycle0preset {} {
     global ccCycle0preset LccCycle0preset	
     global fptr record
     global rspCycleType ccCycle1preset

     global ccCycle0presetColorA ccCycle0presetColorB ccCycle0presetColorC ccCycle0presetColorD
     global ccCycle0presetAlphaA ccCycle0presetAlphaB ccCycle0presetAlphaC ccCycle0presetAlphaD

     global ccCycle0ColorA ccCycle0ColorB ccCycle0ColorC ccCycle0ColorD
     global ccCycle0AlphaA ccCycle0AlphaB ccCycle0AlphaC ccCycle0AlphaD

     set LccCycle0preset [get_ccCycle0presetLabel $ccCycle0preset]

     set ccCycle0ColorA  [lindex $ccCycle0presetColorA $ccCycle0preset]
     set ccCycle0AlphaA  [lindex $ccCycle0presetAlphaA $ccCycle0preset]
 	CccCycle0ColorA
 	CccCycle0AlphaA
     set ccCycle0ColorB  [lindex $ccCycle0presetColorB $ccCycle0preset]
     set ccCycle0AlphaB  [lindex $ccCycle0presetAlphaB $ccCycle0preset]
 	CccCycle0ColorB
 	CccCycle0AlphaB
     set ccCycle0ColorC  [lindex $ccCycle0presetColorC $ccCycle0preset]
     set ccCycle0AlphaC  [lindex $ccCycle0presetAlphaC $ccCycle0preset]
 	CccCycle0ColorC
 	CccCycle0AlphaC
     set ccCycle0ColorD  [lindex $ccCycle0presetColorD $ccCycle0preset]
     set ccCycle0AlphaD  [lindex $ccCycle0presetAlphaD $ccCycle0preset]
 	CccCycle0ColorD
 	CccCycle0AlphaD

	if {$record == 1} {
		puts $fptr "set ccCycle0preset $ccCycle0preset"
		puts $fptr "set LccCycle0preset $LccCycle0preset"
	}

	if {$rspCycleType == 0} {
		set ccCycle1preset $ccCycle0preset
	        CccCycle1preset
	}
}



#set ccCycle0preset 1
###    CccCycle0preset

#set ccCycle1preset 0
#    CccCycle1preset

#----------------------------------------------------------------------------

pack .cc.cycle0ColorL .cc.cycle0ColorL( .cc.cycle0ColorAMB .cc.cycle0ColorL- .cc.cycle0ColorBMB .cc.cycle0ColorL) .cc.cycle0ColorCMB .cc.cycle0ColorL+ .cc.cycle0ColorDMB  -in .cc.cyc0ColorF -side left -fill y -padx 1m -pady 1m

pack .cc.cycle1ColorL .cc.cycle1ColorL( .cc.cycle1ColorAMB .cc.cycle1ColorL- .cc.cycle1ColorBMB .cc.cycle1ColorL) .cc.cycle1ColorCMB .cc.cycle1ColorL+ .cc.cycle1ColorDMB  -in .cc.cyc1ColorF -side left -fill y -padx 1m -pady 1m

pack .cc.cycle0AlphaL .cc.cycle0AlphaL( .cc.cycle0AlphaAMB .cc.cycle0AlphaL- .cc.cycle0AlphaBMB .cc.cycle0AlphaL) .cc.cycle0AlphaCMB .cc.cycle0AlphaL+ .cc.cycle0AlphaDMB  -in .cc.cyc0AlphaF -side left -fill y -padx 1m -pady 1m

pack .cc.cycle1AlphaL .cc.cycle1AlphaL( .cc.cycle1AlphaAMB .cc.cycle1AlphaL- .cc.cycle1AlphaBMB .cc.cycle1AlphaL) .cc.cycle1AlphaCMB .cc.cycle1AlphaL+ .cc.cycle1AlphaDMB  -in .cc.cyc1AlphaF -side left -fill y -padx 1m -pady 1m

pack .cc.cyc0ColorF .cc.cyc1ColorF .cc.cyc0AlphaF .cc.cyc1AlphaF -in .cc.muxesF -side top -fill x -pady 1m

pack .cc.primLODfracS .cc.primLODfracE -in .cc.primLODfracF -side left -padx 1m
pack .cc.primLODminS .cc.primLODminE -in .cc.primLODminF -side left -padx 1m
pack .cc.primLODL .cc.primLODfracF .cc.primLODminF -in .cc.primLODfracminF -side left -fill y -padx 1m
pack .cc.primLODfracminF -in .cc.primLODF -side top -fill x -pady 1m

pack .cc.convertK4S .cc.convertK4E -in .cc.convertK4F -side left -padx 1m
pack .cc.convertK5S .cc.convertK5E -in .cc.convertK5F -side left -padx 1m
pack .cc.convertL .cc.convertK4F .cc.convertK5F -in .cc.convertK4K5F -side left -fill y -padx 1m
pack .cc.convertK4K5F -in .cc.convertF -side top -fill x -pady 1m

pack .cc.keyWidthRedS .cc.keyWidthRedE -in .cc.keyWidthRedF -side left -padx 1m
pack .cc.keyWidthGreenS .cc.keyWidthGreenE -in .cc.keyWidthGreenF -side left -padx 1m
pack .cc.keyWidthBlueS .cc.keyWidthBlueE -in .cc.keyWidthBlueF -side left -padx 1m
pack .cc.keyWidthL .cc.keyWidthRedF .cc.keyWidthGreenF .cc.keyWidthBlueF -in .cc.keyWidthF -side left -fill y -padx 1m
pack .cc.keyWidthF -in .cc.keyF -side top -fill x -pady 1m

pack .cc.keyCenterRedS .cc.keyCenterRedE -in .cc.keyCenterRedF -side left -padx 1m
pack .cc.keyCenterGreenS .cc.keyCenterGreenE -in .cc.keyCenterGreenF -side left -padx 1m
pack .cc.keyCenterBlueS .cc.keyCenterBlueE -in .cc.keyCenterBlueF -side left -padx 1m
pack .cc.keyCenterL .cc.keyCenterRedF .cc.keyCenterGreenF .cc.keyCenterBlueF -in .cc.keyCenterF -side left -fill y -padx 1m
pack .cc.keyCenterF -in .cc.keyF -side top -fill x -pady 1m

pack .cc.keyScaleRedS .cc.keyScaleRedE -in .cc.keyScaleRedF -side left -padx 1m
pack .cc.keyScaleGreenS .cc.keyScaleGreenE -in .cc.keyScaleGreenF -side left -padx 1m
pack .cc.keyScaleBlueS .cc.keyScaleBlueE -in .cc.keyScaleBlueF -side left -padx 1m
pack .cc.keyScaleL .cc.keyScaleRedF .cc.keyScaleGreenF .cc.keyScaleBlueF -in .cc.keyScaleF -side left -fill y -padx 1m
pack .cc.keyScaleF -in .cc.keyF -side top -fill x -pady 1m

pack .cc.primColorRedS .cc.primColorRedE -in .cc.primRedF -side left -padx 1m
pack .cc.primColorGreenS .cc.primColorGreenE -in .cc.primGreenF -side left -padx 1m
pack .cc.primColorBlueS .cc.primColorBlueE -in .cc.primBlueF -side left -padx 1m
pack .cc.primColorAlphaS .cc.primColorAlphaE -in .cc.primAlphaF -side left -padx 1m
pack .cc.primColorL .cc.primRedF .cc.primGreenF .cc.primBlueF .cc.primAlphaF -in .cc.primColorF -side left -fill y -padx 1m

pack .cc.envColorRedS .cc.envColorRedE -in .cc.envRedF -side left -padx 1m
pack .cc.envColorGreenS .cc.envColorGreenE -in .cc.envGreenF -side left -padx 1m
pack .cc.envColorBlueS .cc.envColorBlueE -in .cc.envBlueF -side left -padx 1m
pack .cc.envColorAlphaS .cc.envColorAlphaE -in .cc.envAlphaF -side left -padx 1m
pack .cc.envColorL .cc.envRedF .cc.envGreenF .cc.envBlueF .cc.envAlphaF -in .cc.envColorF -side left -fill y -padx 1m
pack .cc.primColorF .cc.envColorF -in .cc.colorF -side top -fill x -pady 1m

pack .cc.cycle0presetL .cc.cycle0presetMB .cc.cycle1presetL .cc.cycle1presetMB -in .cc.cycle0cycle1presetF -side left -fill y -padx 5m
pack .cc.cycle0cycle1presetF -in .cc.presetF -side top -fill x -pady 1m

pack .cc.convertF .cc.keyF .cc.primLODF .cc.colorF -in .cc.stateF -side top -fill x -pady 1m

pack .cc.stateF .cc.muxesF .cc.presetF -in .cc.topF -side top -fill x -pady 1m
pack .cc.topF
