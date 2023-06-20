############### rsp/setup #####################
toplevel .rsp

frame .rsp.mainF
frame .rsp.1F
frame .rsp.2F
frame .rsp.projBF
frame .rsp.projF

frame .rsp.rightF -relief ridge -borderwidth 2
frame .rsp.leftF -relief ridge -borderwidth 2
frame .rsp.bottomF -relief ridge -borderwidth 2
frame .rsp.topF -relief ridge -borderwidth 2
frame .rsp.mousehF
frame .rsp.mouseF -relief ridge -borderwidth 2

frame .rsp.cycleTypeF -relief ridge -borderwidth 2
frame .rsp.geomF 
frame .rsp.lightingF
frame .rsp.recordPlayF

frame .rsp.recFileF -relief ridge -borderwidth 2
frame .rsp.playFileF -relief ridge -borderwidth 2

frame .rsp.projFovF -relief ridge -borderwidth 2
frame .rsp.projAspectF -relief ridge -borderwidth 2
frame .rsp.projNearF -relief ridge -borderwidth 2
frame .rsp.projFarF -relief ridge -borderwidth 2
frame .rsp.spTexXparmF -relief ridge -borderwidth 2
frame .rsp.otherF -relief ridge -borderwidth 2

frame .rsp.zbufFogF -relief ridge -borderwidth 2
frame .rsp.shadeSmoothF -relief ridge -borderwidth 2
frame .rsp.cullF -relief ridge -borderwidth 2
frame .rsp.texLodF -relief ridge -borderwidth 2

frame .rsp.topLabelF -relief ridge -borderwidth 2
frame .rsp.ambF -relief ridge -borderwidth 2
frame .rsp.l1F -relief ridge -borderwidth 2
frame .rsp.l2F -relief ridge -borderwidth 2
frame .rsp.diffSpecF -relief ridge -borderwidth 2

frame .rsp.lightsF

frame .rsp.modelCtrlF 
frame .rsp.initCtrlF 
frame .rsp.trapCtrlF
frame .rsp.ctrlF


set record 0
####################### dummy sync variables to keep create_callback happy ######
set loadSyncDummy 0
set tileSyncDummy 0
set fullSyncDummy 0
############ Mouse Window ######################
canvas .rsp.canvas -relief ridge -borderwidth 4 -width 320 -height 240

set mouseX 0
set mouseY 0
set buttons 0

bind .rsp.canvas <Any-ButtonPress-1> {
	global mouseX mouseY buttons spindso
	set mouseX %x
	set mouseY %y
	set buttons [expr $buttons | 4]
  	if {$record == 1} {
		puts $fptr "set mouseX $mouseX"
		puts $fptr "set mouseY $mouseY"
	 	puts $fptr "set buttons $buttons"
		puts $fptr "\$spindso call SpinTclMouse \$mouseX \$mouseY \$buttons"
	}
	$spindso call SpinTclMouse $mouseX $mouseY $buttons
}

bind .rsp.canvas <Any-ButtonRelease-1> {
	global mouseX mouseY buttons spindso
	set mouseX %x
	set mouseY %y
	set buttons [expr $buttons & ~4]
  	if {$record == 1} {
		puts $fptr "set mouseX $mouseX"
		puts $fptr "set mouseY $mouseY"
	 	puts $fptr "set buttons $buttons"
		puts $fptr "\$spindso call SpinTclMouse \$mouseX \$mouseY \$buttons"
	}
	$spindso call SpinTclMouse $mouseX $mouseY $buttons
}

bind .rsp.canvas <Any-ButtonPress-2> {
	global mouseX mouseY buttons spindso
	set mouseX %x
	set mouseY %y
	set buttons [expr $buttons | 2]
  	if {$record == 1} {
		puts $fptr "set mouseX $mouseX"
		puts $fptr "set mouseY $mouseY"
	 	puts $fptr "set buttons $buttons"
		puts $fptr "\$spindso call SpinTclMouse \$mouseX \$mouseY \$buttons"
	}
	$spindso call SpinTclMouse $mouseX $mouseY $buttons
}


bind .rsp.canvas <Any-ButtonRelease-2> {
	global mouseX mouseY buttons spindso
	set mouseX %x
	set mouseY %y
	set buttons [expr $buttons & ~2]
  	if {$record == 1} {
		puts $fptr "set mouseX $mouseX"
		puts $fptr "set mouseY $mouseY"
	 	puts $fptr "set buttons $buttons"
		puts $fptr "\$spindso call SpinTclMouse \$mouseX \$mouseY \$buttons"
	}
	$spindso call SpinTclMouse $mouseX $mouseY $buttons
}

# B-3 is being overloaded here. Upon 

bind .rsp.canvas <Any-ButtonPress-3> {
	global mouseX mouseY buttons spindso
	set mouseX %x
	set mouseY %y
	
  	if {$record == 1} {
		puts $fptr "set mouseX $mouseX"
		puts $fptr "set mouseY $mouseY"
	 	puts $fptr "set buttons $buttons"
		puts $fptr "\$spindso call SpinTclMouse \$mouseX \$mouseY \$buttons"
	}
	# mark location for scissoring rectangle
	itemMark .rsp.canvas %x %y 
}

bind .rsp.canvas <Any-ButtonRelease-3> {
	global mouseX mouseY buttons spindso
	
	if { ($mouseX == %x) && ($mouseY == %y) } {
		.rsp.trackBallFlyCB invoke
	}

	set mouseX %x
	set mouseY %y

  	if {$record == 1} {
		puts $fptr "set mouseX $mouseX"
		puts $fptr "set mouseY $mouseY"
	 	puts $fptr "set buttons $buttons"
		puts $fptr "\$spindso call SpinTclMouse \$mouseX \$mouseY \$buttons"
	}
	$spindso call SpinTclMouse $mouseX $mouseY $buttons
}

bind .rsp.canvas <Any-Motion> {
	global mouseX mouseY buttons spindso
	set mouseX %x
	set mouseY %y
 	if {$record == 1} {
		puts $fptr "set mouseX $mouseX"
		puts $fptr "set mouseY $mouseY"
	 	puts $fptr "set buttons $buttons"
		puts $fptr "\$spindso call SpinTclMouse \$mouseX \$mouseY \$buttons"
	}
	$spindso call SpinTclMouse $mouseX $mouseY $buttons
}

bind .rsp.canvas <B3-Motion> "itemStroke .rsp.canvas %x %y"

proc itemMark {c x y} {
#    global areaX1 areaY1
#    set areaX1 [$c canvasx $x]
#    set areaY1 [$c canvasy $y]
}

proc itemStroke {c x y} {
#    global areaX1 areaY1 areaX2 areaY2
#    set x [$c canvasx $x]
#    set y [$c canvasy $y]

#        set areaX2 $x
#        set areaY2 $y
#	if {$areaX2 > $areaX1} {
#        	.rsp.leftS set [expr int($areaX1*4)]
#        	.rsp.rightS set [expr int($areaX2*4)]
#	} else {
#		.rsp.leftS set [expr int($areaX2*4)]
#                .rsp.rightS set [expr int($areaX1*4)]
#	}
#	if {$areaY2 > $areaY1} {
#        	.rsp.topS set [expr int($areaY1*4)]
#        	.rsp.bottomS set [expr int($areaY2*4)]
#	} else {
#		.rsp.topS set [expr int($areaY2*4)]
#                .rsp.bottomS set [expr int($areaY1*4)]
#	}
}

proc drawRect {} {
#	global rspSCissLeft rspSCissTop rspSCissRight rspSCissBottom
#
#	set x0 $rspSCissLeft
#	set y0 $rspSCissTop
#	set x1 $rspSCissRight
#	set y1 $rspSCissBottom
#
#	.rsp.canvas delete area
#	if {($x0 == $x1) || ($y0 == $y1)} {
#		.rsp.canvas addtag area withtag [.rsp.canvas create rect \
#		$x0 $y0 [expr $x1 + 1] [expr $y1 + 1] -outline black]
#	} else {
#		.rsp.canvas addtag area withtag [.rsp.canvas create rect \
#		$x0 $y0 $x1 $y1 -outline black]
#	}
#		
}

.rsp.canvas addtag area withtag [.rsp.canvas create rect 160 0 160 239 -outline black]

.rsp.canvas addtag area withtag [.rsp.canvas create rect 0 120 319 120 -outline black]
set canvasHeight [winfo height .rsp.canvas]
set canvasWidth [winfo width .rsp.canvas]

scale .rsp.bottomS -label bot -from 0 -to 960 -length 215 -orient vertical -command CrspScissBottom -relief ridge -borderwidth 2
entry .rsp.bottomE -width 6 -relief sunken -textvariable rspSCissBottom

bind .rsp.bottomE <Return> {

	if {$rspScissBottom > 960} {
		set rspScissBottom 960
		set rspSCissBottom [expr $rspScissBottom/4.0]
	}
	if {$rspScissBottom < $rspScissTop} {
		set rspScissTop $rspScissBottom
		set rspSCissTop [expr $rspScissTop/4.0]
		.rsp.topS set $rspScissBottom
	}

	.rsp.bottomS set [expr int($rspSCissBottom*4.0)]

	drawRect
	focus none
}

proc CrspScissBottom value {
	global rspScissBottom rspScissTop rspScissLeft rspScissRight
	global rspSCissBottom rspSCissTop rspSCissLeft rspSCissRight
	global fptr record

	set rspScissBottom [expr $value]
	set rspSCissBottom [expr $rspScissBottom/4.0]

	if {$rspScissBottom < $rspScissTop} {
		set rspScissTop $rspScissBottom
		set rspSCissTop [expr $rspScissTop/4.0]
		.rsp.topS set $rspScissBottom
	}
	drawRect

	if {$record == 1} {
		puts $fptr "set rspScissBottom $rspScissBottom"
		puts $fptr "set rspSCissBottom $rspSCissBottom"
		puts $fptr ".rsp.bottomS set $value"
	}
	callback_rspSciss
	callback_send_dl
}


scale .rsp.topS -label top -from 0 -to 960 -length 215 -orient vertical -command CrspScissTop -relief ridge -borderwidth 2
entry .rsp.topE -width 6 -relief sunken -textvariable rspSCissTop

bind .rsp.topE <Return> {
	if {$rspScissTop > 960} {
		set rspScissTop 960
		set rspSCissTop [expr $rspScissTop/4.0]
	}

        if {$rspScissBottom < $rspScissTop} {
                set rspScissBottom $rspScissTop
                set rspSCissBottom [expr $rspScissBottom/4.0]
                .rsp.bottomS set $rspScissTop
        }

	.rsp.topS set [expr int($rspSCissTop*4.0)]

	drawRect
	focus none
}

proc CrspScissTop value {
	global rspScissTop rspScissBottom
	global rspSCissBottom rspSCissTop rspSCissLeft rspSCissRight
	global fptr record

	set rspScissTop $value
	set rspSCissTop [expr $rspScissTop/4.0]

	if {$rspScissBottom < $rspScissTop} {
                set rspScissBottom $rspScissTop
                set rspSCissBottom [expr $rspScissBottom/4.0]
                .rsp.bottomS set $rspScissTop

        }
	drawRect
	if {$record == 1} {
		puts $fptr "set rspScissTop $rspScissTop"
		puts $fptr "set rspSCissTop $rspSCissTop"
		puts $fptr ".rsp.topS set $value"
	}
	callback_rspSciss
	callback_send_dl
}

scale .rsp.leftS -label left -from 0 -to 1280 -length 252 -orient horizontal -command CrspScissLeft -relief ridge -borderwidth 2
entry .rsp.leftE -width 6 -relief sunken -textvariable rspSCissLeft

bind .rsp.leftE <Return> {
	if {$rspScissLeft > 1280} {
		set rspScissLeft 1280
		set rspSCissLeft [expr $rspScissLeft/4.0]
	}
	
       if {$rspScissRight < $rspScissLeft} {
                set rspScissRight $rspScissLeft
                set rspSCissRight [expr $rspScissRight/4.0]
                .rsp.rightS set $rspScissLeft
        }

	.rsp.leftS set [expr int($rspSCissLeft*4.0)]

	drawRect
	focus none
}

proc CrspScissLeft value {
	global rspScissLeft rspScissRight
	global rspSCissBottom rspSCissTop rspSCissLeft rspSCissRight
	global fptr record

	set rspScissLeft $value
	set rspSCissLeft [expr $rspScissLeft/4.0]

       if {$rspScissRight < $rspScissLeft} {
                set rspScissRight $rspScissLeft
		set rspSCissRight [expr $rspScissRight/4.0]
                .rsp.rightS set $rspScissLeft
        }
	drawRect
	if {$record == 1} {
		puts $fptr "set rspScissLeft $rspScissLeft"
		puts $fptr "set rspSCissLeft $rspSCissLeft"
		puts $fptr ".rsp.leftS set $value"
	}
	callback_rspSciss
	callback_send_dl
}

scale .rsp.rightS -label right -from 0 -to 1280 -length 252 -orient horizontal -command CrspScissRight -relief ridge -borderwidth 2
entry .rsp.rightE -width 6 -relief sunken -textvariable rspSCissRight

bind .rsp.rightE <Return> {
	if {$rspScissRight > 1280} {
		set rspScissRight 1280
		set rspSCissRight 320
	}

	if {$rspScissRight < $rspScissLeft} {
                set rspScissLeft $rspScissRight
                set rspSCissLeft [expr $rspScissLeft/4.0]
                .rsp.leftS set $rspScissRight
        }

	.rsp.rightS set [expr int($rspSCissRight*4.0)]

	drawRect
	focus none
}

proc CrspScissRight value {
	global rspScissRight rspScissLeft
	global rspSCissBottom rspSCissTop rspSCissLeft rspSCissRight
	global fptr record

	set rspScissRight $value
	set rspSCissRight [expr $rspScissRight/4.0]

        if {$rspScissRight < $rspScissLeft} {
                set rspScissLeft $rspScissRight
                set rspSCissLeft [expr $rspScissLeft/4.0]
                .rsp.leftS set $rspScissRight
        }
	drawRect
	if {$record == 1} {
		puts $fptr "set rspScissRight $rspScissRight"
		puts $fptr "set rspSCissRight $rspSCissRight"
		puts $fptr ".rsp.rightS set $value"
	}
	callback_rspSciss
	callback_send_dl
}

#--------------------------initialization---------------------
.rsp.bottomS set 960
set rspScissBottom 960
set rspSCissBottom 240.0

.rsp.topS set 0
set rspScissTop 0
set rspSCissTop 0

.rsp.leftS set 0
set rspScissLeft 0
set rspSCissLeft 0

.rsp.rightS set 1280
set rspScissRight 1280
set rspSCissRight 320.0

#bind .cc.leftE <Return> {
#        if {$ccPrimLODfrac > 255} {set ccPrimLODfrac 255}
#        if {$ccPrimLODfrac < 0} {set ccPrimLODfrac 0}
#        .cc.leftS set $ccPrimLODfrac
#        focus none
#        if {$record == 1} {
#                puts $fptr "set ccPrimLODfrac $ccPrimLODfrac"
#                puts $fptr ".cc.leftS set $ccPrimLODfrac"
#        }
#}

############ Proj ##########################
label .rsp.projL -text "projection xform" -relief ridge -borderwidth 2

scale .rsp.projFovS -label fov -from 1 -to 180 -length 200 -orient horizontal -command CrspProjFov

entry .rsp.projFovE -width 3 -relief sunken -textvariable rspProjFov
bind .rsp.projFovE <Return> {
        if {$rspProjFov > 180} {set rspProjFov 180}
        if {$rspProjFov < 1} {set rspProjFov 1}
        .rsp.projFovS set $rspProjFov
        focus none
        }

.rsp.projFovS set 30

set rspProjFovFlag 1

proc CrspProjFov value {
        global rspProjFov
	global fptr record
	global rspProjFovFlag

        set rspProjFov $value
	if {$record == 1} {
		puts $fptr "set rspProjFov $rspProjFov"
		puts $fptr "sendProj"
		puts $fptr ".rsp.projFovS set $rspProjFov"
	}
	sendProj
}

scale .rsp.projAspectS -label aspect -from 500 -to 2000 -length 200 -orient horizontal -command CrspProjAspect

entry .rsp.projAspectE -width 5 -relief sunken -textvariable rspProjAspect
bind .rsp.projAspectE <Return> {
        if {$rspProjAspect > 2.0} {set rspProjAspect 2.0}
        if {$rspProjAspect < 0.0} {set rspProjAspect 0.0}
        .rsp.projAspectS set [expr int($rspProjAspect*1000)]
        focus none
        }

#.rsp.projAspectS set 1333

set rspProjAspectFlag 1

proc CrspProjAspect value {
        global rspProjAspect
	global fptr record
	global rspProjAspectFlag

        set rspProjAspect [expr $value/1000.0]
	if {$record == 1} {
		puts $fptr "set rspProjAspect $rspProjAspect"
		puts $fptr "sendProj"
		puts $fptr ".rsp.projAspectS set $value"
	}
	sendProj
}

scale .rsp.projNearS -label near -from 1 -to 5000 -length 200 -orient horizontal -command CrspProjNear

entry .rsp.projNearE -width 4 -relief sunken -textvariable rspProjNear
bind .rsp.projNearE <Return> {
        if {$rspProjNear > 5000} {set rspProjNear 5000}
        if {$rspProjNear < 1} {set rspProjNear 1}
        .rsp.projNearS set $rspProjNear
        focus none
        }

#.rsp.projNearS set 50
#set rspProjNear 50


proc CrspProjNear value {
        global rspProjNear
        global rspProjFar
	global fptr record
	global rspProjNearFlag

        set rspProjNear $value
	if {$rspProjFar < $rspProjNear} {
	  set rspProjFar $rspProjNear
	  .rsp.projFarS set $rspProjFar
	}
	if {$record == 1} {
		puts $fptr "set rspProjNear $rspProjNear"
		puts $fptr "sendProj"
		puts $fptr ".rsp.projNearS set $value"
	}
	sendProj
}

scale .rsp.projFarS -label far -from 1 -to 9999 -length 200 -orient horizontal -command CrspProjFar

entry .rsp.projFarE -width 4 -relief sunken -textvariable rspProjFar
bind .rsp.projFarE <Return> {
        if {$rspProjFar > 9999} {set rspProjFar 9999}
        if {$rspProjFar < 1} {set rspProjFar 1}
        .rsp.projFarS set $rspProjFar
        focus none
        }

#.rsp.projFarS set 5000
#set rspProjFar 5000

set rspProjFarFlag 1

proc CrspProjFar value {
        global rspProjFar
        global rspProjNear
	global fptr record
	global rspProjFarFlag

        set rspProjFar $value
	if {$rspProjFar < $rspProjNear} {
	  set rspProjNear $rspProjFar
	  .rsp.projNearS set $rspProjNear
	}
	if {$record == 1} {
		puts $fptr "set rspProjFar $rspProjFar"
		puts $fptr "sendProj"
		puts $fptr ".rsp.projFarS set $value"
	}
	sendProj
}

set rspProjFov 33
set rspProjAspect 1.3
set rspProjNear 50
set rspProjFar 9999

proc sendProj {} {
	global rspProjFov rspProjAspect 
	global rspProjNear rspProjFar spindso

	$spindso call SpinTclProj $rspProjFov $rspProjAspect $rspProjNear $rspProjFar
}


scale .rsp.spTexXparmS -label spTexXparm -from 0 -to 255 -length 200 -orient horizontal -command CspTexXparm

entry .rsp.spTexXparmE -width 5 -relief sunken -textvariable spTexXparm
bind .rsp.spTexXparmE <Return> {
        if {$spTexXparm > 255} {set spTexXparm 255}
        if {$spTexXparm < 0} {set spTexXparm 0}
        .rsp.spTexXparmS set $spTexXparm
        focus none
        }

#.rsp.spTexXparmS set [expr 10*$rspProjNear]

set spTexXparm 1

proc CspTexXparm value {
        global spTexXparm
	global fptr record

        set spTexXparm $value
	if {$record == 1} {
		puts $fptr "set spTexXparm $spTexXparm"
	#	puts $fptr ".rsp.spTexXparmS set $value"
	}
	callback_spTex
	callback_send_dl
}

############ geometry modes #####################
label .rsp.geomL -text "geometry modes" -relief ridge -borderwidth 2

checkbutton .rsp.zbufCB -width 14 -text "zbuf       " -variable rspGeomZbuf -command CrspGeomZbuf

proc CrspGeomZbuf {} {
	global record fptr rspGeomZbuf
	if {$record == 1} {
	 	puts $fptr "set rspGeomZbuf $rspGeomZbuf"
		puts $fptr "CrspGeomZbuf"
	}
	callback_rspGeom
	callback_send_dl
} 


checkbutton .rsp.fogCB -width 14 -text "fog         " -variable rspGeomFog -command CrspGeomFog

proc CrspGeomFog {} {
	global record fptr rspGeomFog
	if {$record == 1} {
	 	puts $fptr "set rspGeomFog $rspGeomFog"
		puts $fptr "CrspGeomFog"
	}
	callback_rspGeom
	callback_send_dl
} 


checkbutton .rsp.shadeCB -width 14 -text "shade     " -variable rspGeomShade -command CrspGeomShade

proc CrspGeomShade {} {
	global record fptr rspGeomShade
	if {$record == 1} {
	 	puts $fptr "set rspGeomShade $rspGeomShade"
		puts $fptr "CrspGeomShade"
	}
	callback_rspGeom
	callback_send_dl
} 


checkbutton .rsp.smoothCB -width 14 -text "smooth    " -variable rspGeomSmooth -command CrspGeomSmooth

proc CrspGeomSmooth {} {
	global record fptr rspGeomSmooth
	if {$record == 1} {
	 	puts $fptr "set rspGeomSmooth $rspGeomSmooth"
		puts $fptr "CrspGeomSmooth"
	}
	callback_rspGeom
	callback_send_dl
} 


checkbutton .rsp.cullFrontCB -width 14 -text "cull Front" -variable rspGeomCullFront -command CrspGeomCullFront

proc CrspGeomCullFront {} {
	global record fptr rspGeomCullFront
	if {$record == 1} {
	 	puts $fptr "set rspGeomCullFront $rspGeomCullFront"
		puts $fptr "CrspGeomCullFront"
	}
	callback_rspGeom
	callback_send_dl
} 


checkbutton .rsp.cullBackCB -width 14 -text "cull Back " -variable rspGeomCullBack -command CrspGeomCullBack

proc CrspGeomCullBack {} {
	global record fptr rspGeomCullBack
	if {$record == 1} {
	 	puts $fptr "set rspGeomCullBack $rspGeomCullBack"
		puts $fptr "CrspGeomCullBack"
	}
	callback_rspGeom
	callback_send_dl
} 


checkbutton .rsp.textureCB -width 14 -text "texture    " -variable rspGeomTexture -command CrspGeomTexture

proc CrspGeomTexture {} {
	global record fptr rspGeomTexture
	if {$record == 1} {
	 	puts $fptr "set rspGeomTexture $rspGeomTexture"
		puts $fptr "CrspGeomTexture"
	}
	callback_rspGeom
	callback_send_dl
} 


checkbutton .rsp.lodCB -width 14 -text "LOD       " -variable rspGeomLod -command CrspGeomLod

proc CrspGeomLod {} {
	global record fptr rspGeomLod
	if {$record == 1} {
	 	puts $fptr "set rspGeomLod $rspGeomLod"
		puts $fptr "CrspGeomLod"
	}
	callback_rspGeom
	callback_send_dl
} 

####################### init all the above #################
#set rspGeomZbuf 1
#set rspGeomFog 0
#set rspGeomShade 1
#set rspGeomSmooth 1
#set rspGeomCullFront 0
#set rspGeomCullBack 1
#set rspGeomTexture 0
#set rspGeomLod 0
#callback_rspGeom
#callback_send_dl

############ Light ##########################
label .rsp.lightingL -width 4 -text "Light"
label .rsp.redL -width 3 -text "Red"
label .rsp.greenL -width 3 -text "Grn"
label .rsp.blueL -width 3 -text "Blue"
label .rsp.xL -width 3 -text "X"
label .rsp.yL -width 3 -text "Y"
label .rsp.zL -width 3 -text "Z"

label .rsp.ambL -width 4 -text Amb
label .rsp.ambR -width 3 -relief sunken -textvariable rspAmbR
label .rsp.ambG -width 3 -relief sunken -textvariable rspAmbG
label .rsp.ambB -width 3 -relief sunken -textvariable rspAmbB

#set rspAmbR 128
#set rspAmbG 128
#set rspAmbB 128


label .rsp.l1L -width 4 -text "L1"
label .rsp.l1R -width 3 -relief sunken -textvariable rspl1R
label .rsp.l1G -width 3 -relief sunken -textvariable rspl1G
label .rsp.l1B -width 3 -relief sunken -textvariable rspl1B
label .rsp.l1X -width 3 -relief sunken -textvariable rspl1X
label .rsp.l1Y -width 3 -relief sunken -textvariable rspl1Y
label .rsp.l1Z -width 3 -relief sunken -textvariable rspl1Z

#set rspl1R 128
#set rspl1G 0
#set rspl1B 0

#set rspl1X 1
#set rspl1Y 1
#set rspl1Z 1

label .rsp.l2L -width 4 -text "L2"
label .rsp.l2R -width 3 -relief sunken -textvariable rspl2R
label .rsp.l2G -width 3 -relief sunken -textvariable rspl2G
label .rsp.l2B -width 3 -relief sunken -textvariable rspl2B
label .rsp.l2X -width 3 -relief sunken -textvariable rspl2X
label .rsp.l2Y -width 3 -relief sunken -textvariable rspl2Y
label .rsp.l2Z -width 3 -relief sunken -textvariable rspl2Z

#set rspl2R 0
#set rspl2G 0
#set rspl2B 128

#set rspl2X -1
#set rspl2Y 1
#set rspl2Z 1

checkbutton .rsp.l1CB -width 3 -text L1 -variable rspL1 -command CrspL1

proc CrspL1 {} {
	global rspL1
	global record fptr

	if {$rspL1 == 1} {
	  .rsp.l1L configure -background AntiqueWhite1
	  .rsp.l1R configure -background AntiqueWhite1
	  .rsp.l1G configure -background AntiqueWhite1
	  .rsp.l1B configure -background AntiqueWhite1
	  .rsp.l1X configure -background AntiqueWhite1
	  .rsp.l1Y configure -background AntiqueWhite1
	  .rsp.l1Z configure -background AntiqueWhite1
	} else {
	  .rsp.l1L configure -background AntiqueWhite2
	  .rsp.l1R configure -background AntiqueWhite2
	  .rsp.l1G configure -background AntiqueWhite2
	  .rsp.l1B configure -background AntiqueWhite2
	  .rsp.l1X configure -background AntiqueWhite2
	  .rsp.l1Y configure -background AntiqueWhite2
	  .rsp.l1Z configure -background AntiqueWhite2
	}

	if {$record == 1} {
		puts $fptr "set rspL1 $rspL1"
		puts $fptr "CrspL1"
	}
}

#set rspL1 0
#CrspL1

checkbutton .rsp.l2CB -width 3 -text L2 -variable rspL2 -command CrspL2

proc CrspL2 {} {
	global rspL2
	global fptr record

	if {$rspL2 == 1} {
	  .rsp.l2L configure -background AntiqueWhite1
	  .rsp.l2R configure -background AntiqueWhite1
	  .rsp.l2G configure -background AntiqueWhite1
	  .rsp.l2B configure -background AntiqueWhite1
	  .rsp.l2X configure -background AntiqueWhite1
	  .rsp.l2Y configure -background AntiqueWhite1
	  .rsp.l2Z configure -background AntiqueWhite1
	} else {
	  .rsp.l2L configure -background AntiqueWhite2
	  .rsp.l2R configure -background AntiqueWhite2
	  .rsp.l2G configure -background AntiqueWhite2
	  .rsp.l2B configure -background AntiqueWhite2
	  .rsp.l2X configure -background AntiqueWhite2
	  .rsp.l2Y configure -background AntiqueWhite2
	  .rsp.l2Z configure -background AntiqueWhite2
	}

	if {$record == 1} {
		puts $fptr "set rspL2 $rspL2"
		puts $fptr "CrspL2"
	}
}

#set rspL2 0
#CrspL2

label .rsp.diffSpecL -width 4 -text "type"

checkbutton .rsp.diffuseCB -width 10 -text "diffuse" -variable rspDiffuse -command CrspDiffuse
set rspDiffuse 0

proc CrspDiffuse {} {
 	global rspDiffuse rspSpecular
	global fptr record

	if {$rspDiffuse == 0} {set rspSpecular 0}
	if {$record == 1} {
		puts $fptr "set rspDiffuse $rspDiffuse"
		puts $fptr "CrspDiffuse"
	}
}

checkbutton .rsp.specularCB -width 10 -text "specular" -variable rspSpecular -command CrspSpecular
set rspSpecular 0

proc CrspSpecular {} {
	global fptr record rspSpecular
	
	if {$record == 1} {
		puts $fptr "set rspSpecular $rspSpecular"
		puts $fptr "CrspSpecular"
	}
}

############ Model Control #######################
#send the complete state for trapping purposes
#send Actions only if the action had been invoked

proc sendState {} {
	global loadTile_dirty loadTlut_dirty loadBlock_dirty loadTex_dirty


puts "TRAPPING ALL"


#-------Cycle Type------------
	callback_rspCycleType

#-------Actions------------
if {$loadTile_dirty == 1} {
	callback_loadTile
}

if {$loadTlut_dirty == 1} {
	puts "trapping loadTlut"
	callback_loadTlut
}

if {$loadBlock_dirty == 1} {
	callback_loadBlock
}

	callback_tileSync
	callback_setTile
	callback_setTileSize

if {$loadTex_dirty == 1} {
	puts "dumping loadTex actions"
	callback_setTimg
	callback_loadBlock
}

#-------RSP State--------------
	callback_rspProj
	callback_spTex
	callback_rspGeom
#-------RDP State--------------
	callback_setConvert
	callback_setTother
	callback_ccKey
	callback_ccPrim
	callback_ccEnv
	callback_blFogColor
	callback_blBlendColor
	callback_ccCycle
	callback_blCycle
	callback_rspSciss
	callback_send_dl
#	callback_fullSync
}

checkbutton .rsp.initModelCB -width 14 -text "init model pos" -variable rspInitModel -command {
	if {$rspInitModel == 1} {
                set rspInitModel 0
                .rsp.initModelCB flash
        }
# we're using the model control path to init the model position
	$spindso call SpinTclModel 99
}

checkbutton .rsp.initStateCB -width 14 -text "init state" -variable rspInitState -command {
	source defRSP.tcl
	source defCc.tcl
	source defBl.tcl
	source defTex.tcl
	if {$rspInitState == 1} {
                set rspInitState 0
                .rsp.initStateCB flash
        }
}

checkbutton .rsp.dumpFrameCB -width 14 -text "dump frame" -variable rspdumpFrame -command {
	if {$rspdumpFrame == 1} {
                set rspdumpFrame 0
                .rsp.dumpFrameCB flash
        }

	$spindso call SpinTclModel 120
}

checkbutton .rsp.trapCB -width 12 -textvariable LrspTrapModule -variable rspTrap -command CrspTrap

proc CrspTrap {} {
	global rspTrap LrspTrap
	global fptr record spindso
	global rspTrapCount rspTrapType

	if {$record == 1} {
		puts $fptr "set rspTrap $rspTrap"
		puts $fptr "CrspTrap"
	}

	if {$rspTrap == 1} {
		set rspTrap 0
		.rsp.trapCB flash
	}

	sendState	
	$spindso  call SpinTclTrap $rspTrapCount $rspTrapType
}

entry .rsp.trapCountE -width 3 -relief sunken -textvariable rspTrapCount

bind .rsp.trapCountE <Return> {
        if {$rspTrapCount < 0.0} {set rspTrapCount 0.0}
        focus none
        }

#checkbutton .rsp.trapTypeCB -width 12 -textvariable "LrspTrapType" -variable rspTrapType -command CrspTrapType

menubutton .rsp.trapTypeMB -textvariable LrspTrapType -width 15 \
-relief  raised -menu .rsp.trapTypeMB.menu -bg LightGray \
-activebackground LightGray

menu .rsp.trapTypeMB.menu
.rsp.trapTypeMB.menu add radiobutton -label "Parsed RSP" -command CrspTrapType -variable rspTrapType -value 0
.rsp.trapTypeMB.menu add radiobutton -label "Raw RSP" -command CrspTrapType -variable rspTrapType -value 1
.rsp.trapTypeMB.menu add radiobutton -label "Parsed RDP" -command CrspTrapType -variable rspTrapType -value 2
.rsp.trapTypeMB.menu add radiobutton -label "Raw RDP" -command CrspTrapType -variable rspTrapType -value 3



proc CrspTrapType {} {
	global rspTrapType LrspTrapType LrspTrapModule
	global fptr record spindso rspTrapCount


	switch $rspTrapType {
		0 {set LrspTrapType "ParseRSP"
                   set LrspTrapModule "dump"}
	 	1 {set LrspTrapType "RawRSP"
                   set LrspTrapModule "dump"}
		2 {set LrspTrapType "ParseRDP"
                   set LrspTrapModule "dump"}
		3 {set LrspTrapType "RawRDP"
                   set LrspTrapModule "dump"}
	}

	if {$record == 1} {
		puts $fptr "set rspTrapType $rspTrapType"
		puts $fptr "CrspTrapType"
	}

	$spindso  call SpinTclTrap 0 $rspTrapType
}

checkbutton .rsp.trackBallFlyCB -width 15 -textvariable LrspTrackBallFly -variable rspTrackBallFly -command CrspTrackBallFly

#set rspTrackBallFly 1
#set LrspTrackBallFly "trackball"
#set buttons [expr $buttons | 1]

# the trackball/fly bit is sent thru the mouse button interface

proc CrspTrackBallFly {} {
	global rspTrackBallFly LrspTrackBallFly
	global fptr record
  	global buttons 


	if {$rspTrackBallFly == 1} {
		set buttons [expr $buttons | 1]
	} else {
		set buttons [expr $buttons & ~1]
	}

	if {$rspTrackBallFly == 0} {set LrspTrackBallFly "fly"} \
	else {set LrspTrackBallFly "trackball"}

	if {$record == 1} {
		puts $fptr "set rspTrackBallFly $rspTrackBallFly"
		puts $fptr "CrspTrackBallFly"
	}
}

menubutton .rsp.modelsMB -textvariable LrspModels -width 15 \
-relief  raised -menu .rsp.modelsMB.menu -bg LightGray \
-activebackground LightGray

menu .rsp.modelsMB.menu
#.rsp.modelsMB.menu add radiobutton -label "square" -command CrspModels -variable rspModels -value 0
.rsp.modelsMB.menu add radiobutton -label "square" -command CrspModels -variable rspModels -value 1
.rsp.modelsMB.menu add radiobutton -label "box" -command CrspModels -variable rspModels -value 2
.rsp.modelsMB.menu add radiobutton -label "rect_box" -command CrspModels -variable rspModels -value 3
.rsp.modelsMB.menu add radiobutton -label "cone" -command CrspModels -variable rspModels -value 4
.rsp.modelsMB.menu add radiobutton -label "cylinder" -command CrspModels -variable rspModels -value 5
.rsp.modelsMB.menu add radiobutton -label "frustum" -command CrspModels -variable rspModels -value 6
.rsp.modelsMB.menu add radiobutton -label "bumble" -command CrspModels -variable rspModels -value 7
.rsp.modelsMB.menu add radiobutton -label "icosa" -command CrspModels -variable rspModels -value 8
.rsp.modelsMB.menu add radiobutton -label "torii" -command CrspModels -variable rspModels -value 9
.rsp.modelsMB.menu add radiobutton -label "ground" -command CrspModels -variable rspModels -value 10
.rsp.modelsMB.menu add radiobutton -label "A" -command CrspModels -variable rspModels -value 11
.rsp.modelsMB.menu add radiobutton -label "cross" -command CrspModels -variable rspModels -value 12
.rsp.modelsMB.menu add radiobutton -label "sphere" -command CrspModels -variable rspModels -value 13
.rsp.modelsMB.menu add radiobutton -label "pipe" -command CrspModels -variable rspModels -value 14
.rsp.modelsMB.menu add radiobutton -label "twist" -command CrspModels -variable rspModels -value 15
.rsp.modelsMB.menu add radiobutton -label "twist1" -command CrspModels -variable rspModels -value 16
.rsp.modelsMB.menu add radiobutton -label "sector" -command CrspModels -variable rspModels -value 17
.rsp.modelsMB.menu add radiobutton -label "frac_island" -command CrspModels -variable rspModels -value 18
.rsp.modelsMB.menu add radiobutton -label "triangle" -command CrspModels -variable rspModels -value 19
#.rsp.modelsMB.menu add radiobutton -label "runway" -command CrspModels -variable rspModels -value 20
#.rsp.modelsMB.menu add radiobutton -label "blend_test" -command CrspModels -variable rspModels -value 21 
#.rsp.modelsMB.menu add radiobutton -label "big_tex" -command CrspModels -variable rspModels -value 22 
#.rsp.modelsMB.menu add radiobutton -label "bigger_tex" -command CrspModels -variable rspModels -value 23 
.rsp.modelsMB.menu add radiobutton -label "gorge" -command CrspModels -variable rspModels -value 24 
#.rsp.modelsMB.menu add radiobutton -label "airport" -command CrspModels -variable rspModels -value 25 
.rsp.modelsMB.menu add radiobutton -label "xluramp" -command CrspModels -variable rspModels -value 26
.rsp.modelsMB.menu add radiobutton -label "tex_fill_rect" -command CrspModels -variable rspModels -value 27

proc CrspModels {} {
	global rspModels LrspModels
	global fptr record spindso
	
	switch $rspModels {
		0 {set LrspModels square}
		1 {set LrspModels square2}
		2 {set LrspModels box}
		3 {set LrspModels rect_box}
		4 {set LrspModels cone}
		5 {set LrspModels cylinder}
		6 {set LrspModels frustum}
		7 {set LrspModels bumble}
		8 {set LrspModels icosa}
		9 {set LrspModels torii}
		10 {set LrspModels ground}
		11 {set LrspModels u64}
		12 {set LrspModels cross}
		13 {set LrspModels sphere}
		14 {set LrspModels pipe}
		15 {set LrspModels twist}
		16 {set LrspModels twist1}
		17 {set LrspModels sector}
		18 {set LrspModels frac_island}
		19 {set LrspModels triangle}
		20 {set LrspModels runway}
		21 {set LrspModels blend_test}
		22 {set LrspModels big_tex}
		23 {set LrspModels bigger_tex}
		24 {set LrspModels gorge}
		25 {set LrspModels airport}
		26 {set LrspModels xluramp}
		27 {set LrspModels tex_fill_rect}
	}

	$spindso call SpinTclModel $rspModels

	if {$record == 1} {
		puts $fptr "set rspModels $rspModels"
		puts $fptr "CrspModels"
	}
}

#set rspModels 15
#CrspModels


############ cycleType ########################
checkbutton .rsp.cycleTypeCB -width 13 -textvariable LrspCycleType -variable rspCycleType -command CrspCycleType

########### pipeLine Mode ######################
checkbutton .rsp.pipeLineModeCB -width 13 -textvariable LrspPipeLineMode -variable rspPipeLineMode -command CrspPipeLineMode

proc CrspPipeLineMode {} {

	global rspPipeLineMode LrspPipeLineMode
	global record fptr

	if {$rspPipeLineMode == 0} {
		set LrspPipeLineMode "normal pipeline mode"
	} else {
		set LrspPipeLineMode "atomic primitive"
	}
		
	if {$record == 1} {
		puts $fptr "set rspPipeLineMode $rspPipeLineMode"
                puts $fptr "CrspPipeLineMode"
        }

	callback_rspPipe
	callback_send_dl
}

############ record Playback  #####################
label .rsp.recPlayL -text "Record/Play" -relief ridge -borderwidth 2

checkbutton .rsp.recordCB -width 14 -textvariable LrspRecord -variable rspRecord -command CrspRecord

set LrspRecord "record"
set rspRecord 0

set testList {}

proc CrspRecord {} {
	global LrspRecord rspRecord rspTestFile
	global testList fptr record

	if {$rspRecord == 1} {
	  set rspRecord 0
	  .rsp.recFileE configure -state normal
	  .rsp.recFileE configure -background AntiqueWhite1
	  .rsp.recordCB configure -state disabled
#	  .rsp.playCB configure -state disabled
	} else {
	  if {$rspRecord == 1} {set LrspRecord "Stop"} \
          else {set LrspRecord "Record"}
	  close $fptr
	  set record 0
	  .rsp.recFileE configure -state disabled
	  .rsp.recFileE configure -background AntiqueWhite2
#	  .rsp.playCB configure -state normal
	}
}

entry .rsp.recFileE -width 17 -state disabled -relief sunken -textvariable rspTestFile -background AntiqueWhite2
set rspTestFile "fileName <Enter>"

bind .rsp.recFileE <Return> {
	global LrspRecord rspRecord fptr record

	if {$rspRecord == 0} {
		set rspRecord 1
		set fptr [open $rspTestFile w]
		set record 1
	}
        if {$rspRecord == 1} {
		set LrspRecord "Stop"
	        .rsp.recordCB configure -state normal
	} else {set LrspRecord "Record"}
	.rsp.recFileE configure -state disabled
	.rsp.recFileE configure -background AntiqueWhite2
	focus none
}

checkbutton .rsp.playCB -width 14 -textvariable LrspPlay -variable rspPlay -command CrspPlay

set LrspPlay "play"
set rspPlay 0

entry .rsp.playFileE -width 17 -state disabled -relief sunken -textvariable rspPlayFile -background AntiqueWhite2
set rspPlayFile "fileName <Enter>"

proc CrspPlay {} {
	global rspPlay LrspPlay

	if {$rspPlay == 1} {
          set rspPlay 0
          .rsp.playFileE configure -state normal
          .rsp.playFileE configure -background AntiqueWhite1
        }
}

bind .rsp.playFileE <Return> {
        global LrspPlay rspPlay
	global rspPlayFile

        if {$rspPlay == 0} {set rspPlay 1}
        .rsp.playFileE configure -state disabled
        .rsp.playFileE configure -background AntiqueWhite2
	source $rspPlayFile
	set rspPlay 0
	focus none
}

############  ##########################


############ Pack ##########################
pack .rsp.projFovS .rsp.projFovE -in .rsp.projFovF -side left -padx 1m
pack .rsp.projAspectS .rsp.projAspectE -in .rsp.projAspectF -side left -padx 1m
pack .rsp.projNearS .rsp.projNearE -in .rsp.projNearF -side left -padx 1m
pack .rsp.projFarS .rsp.projFarE -in .rsp.projFarF -side left -padx 1m
pack .rsp.spTexXparmS .rsp.spTexXparmE -in .rsp.spTexXparmF -side left -padx 1m
pack .rsp.projL .rsp.projFovF .rsp.projAspectF .rsp.projNearF .rsp.projFarF -in .rsp.projF -side top -fill x


pack .rsp.rightS .rsp.rightE -in .rsp.rightF -side left
pack .rsp.leftS .rsp.leftE -in .rsp.leftF -side left
pack .rsp.topS .rsp.topE -in .rsp.topF -side top
pack .rsp.bottomS .rsp.bottomE -in .rsp.bottomF -side top

pack .rsp.trackBallFlyCB .rsp.modelsMB .rsp.trapTypeMB .rsp.trapCB .rsp.trapCountE -in .rsp.modelCtrlF -side left
pack .rsp.trapTypeMB .rsp.trapCB .rsp.trapCountE  -in .rsp.trapCtrlF -side left

pack .rsp.initStateCB .rsp.initModelCB .rsp.dumpFrameCB -in .rsp.initCtrlF -side left
# pack .rsp.modelCtrlF .rsp.initCtrlF -in .rsp.ctrlF -side top
pack .rsp.modelCtrlF .rsp.trapCtrlF .rsp.initCtrlF -in .rsp.ctrlF -side top


pack .rsp.topF .rsp.canvas .rsp.bottomF -in .rsp.mousehF -side left
pack .rsp.leftF .rsp.mousehF .rsp.rightF .rsp.ctrlF -in .rsp.mouseF -side top

pack .rsp.cycleTypeCB .rsp.pipeLineModeCB -in .rsp.cycleTypeF -side top -fill x

pack .rsp.zbufCB .rsp.textureCB -in .rsp.zbufFogF -side left
pack .rsp.shadeCB .rsp.smoothCB -in .rsp.shadeSmoothF -side left
pack .rsp.cullFrontCB .rsp.cullBackCB -in .rsp.cullF -side left

pack .rsp.geomL .rsp.zbufFogF .rsp.shadeSmoothF .rsp.cullF -in .rsp.geomF -side top -fill x

pack .rsp.lightingL .rsp.redL .rsp.greenL .rsp.blueL .rsp.xL .rsp.yL .rsp.zL -in .rsp.topLabelF -side left -fill y -padx 1m
pack .rsp.ambL .rsp.ambR .rsp.ambG .rsp.ambB .rsp.l1CB .rsp.l2CB -in .rsp.ambF -side left -fill y -padx 1m
pack .rsp.l1L .rsp.l1R .rsp.l1G .rsp.l1B .rsp.l1X .rsp.l1Y .rsp.l1Z -in .rsp.l1F -side left -fill y -padx 1m
pack .rsp.l2L .rsp.l2R .rsp.l2G .rsp.l2B .rsp.l2X .rsp.l2Y .rsp.l2Z -in .rsp.l2F -side left -fill y -padx 1m
pack .rsp.diffSpecL .rsp.diffuseCB .rsp.specularCB -in .rsp.diffSpecF -side left -padx 1m

pack .rsp.topLabelF .rsp.l1F .rsp.l2F .rsp.ambF .rsp.diffSpecF -in .rsp.lightingF -side top -fill x

pack .rsp.recordCB .rsp.recFileE -in .rsp.recFileF -side left
pack .rsp.playCB .rsp.playFileE -in .rsp.playFileF -side left
pack .rsp.recPlayL .rsp.recFileF .rsp.playFileF -in .rsp.recordPlayF -side top -fill x

pack .rsp.cycleTypeF .rsp.geomF  .rsp.recordPlayF -in .rsp.otherF -side top -fill x -pady 1m

pack .rsp.projF .rsp.mouseF .rsp.otherF -in .rsp.1F -side left -padx 1m


pack .rsp.1F .rsp.2F -in .rsp.mainF -side top -fill x -pady 1m

pack .rsp.mainF
