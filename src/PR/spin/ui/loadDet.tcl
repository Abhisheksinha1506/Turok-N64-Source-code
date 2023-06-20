set loadDetailOptions {.loadDetailTfileL .loadDetailFormatMB .loadDetailTexelSizeMB .loadDetailWidthL .loadDetailHeightL .loadDetailAddrsL .loadDetailWrapMirsMB .loadDetailClampsCB .loadDetailMasksL .loadDetailShiftsL .loadDetailWrapMirtMB .loadDetailClamptCB .loadDetailMasktL .loadDetailShifttL .loadDetailPalttL .loadDetailDoneB }

set loadDetailEntries { .loadDetailTfileE .loadDetailFormatE .loadDetailTexelSizeL .loadDetailWidthE .loadDetailHeightE .loadDetailAddrsE .loadDetailWrapMirsL .loadDetailClampsL .loadDetailMasksE .loadDetailShiftsE .loadDetailWrapMirtL .loadDetailClamptL .loadDetailMasktE .loadDetailShifttE .loadDetailPalttE }

for {set i 0} {$i < [llength $loadDetailOptions]} {incr i 1} {
   frame .loadDetailFrame$i
}
label .loadDetailLoadDetL -text "LoadDetailMap" -relief groove

label .loadDetailTfileL  -width 10 -text "detFile" -relief groove
entry  .loadDetailTfileE -width 8 -relief sunken -textvariable loadDetailTfile
set loadDetailTfile \$ROOT/PR/apps/rdptex/RGBA16grid.h

menubutton .loadDetailFormatMB -text "texFmt" -width 10 -relief raised -menu .loadDetailFormatMB.menu -bg LightGray -activebackground LightGray
menu .loadDetailFormatMB.menu
.loadDetailFormatMB.menu add radiobutton -label RGBA -command CloadDetailFormat -variable loadDetailFormat -value 0
.loadDetailFormatMB.menu add radiobutton -label YUV -command CloadDetailFormat -variable loadDetailFormat -value 1
.loadDetailFormatMB.menu add radiobutton -label CI -command CloadDetailFormat -variable loadDetailFormat -value 2
.loadDetailFormatMB.menu add radiobutton -label IA -command CloadDetailFormat -variable loadDetailFormat -value 3
.loadDetailFormatMB.menu add radiobutton -label I -command CloadDetailFormat -variable loadDetailFormat -value 4

set loadDetailFormat 0
set LloadDetailFormat RGBA

label .loadDetailFormatE -width 8 -relief sunken -textvariable LloadDetailFormat

proc CloadDetailFormat {} {
   global loadDetailFormat
   global LloadDetailFormat

    switch $loadDetailFormat {
	0 {set LloadDetailFormat RGBA}
	1 {set LloadDetailFormat YUV}
	2 {set LloadDetailFormat CI}
	3 {set LloadDetailFormat IA}
	4 {set LloadDetailFormat I}
    }
}

menubutton .loadDetailTexelSizeMB   -text "texSiz" -width 10 -relief raised -menu .loadDetailTexelSizeMB.menu -bg LightGray -activebackground LightGray
menu .loadDetailTexelSizeMB.menu
.loadDetailTexelSizeMB.menu add radiobutton -label 4 -command CloadDetailTexelSize -variable loadDetailTexelSize -value 0
.loadDetailTexelSizeMB.menu add radiobutton -label 8 -command CloadDetailTexelSize -variable loadDetailTexelSize -value 1
.loadDetailTexelSizeMB.menu add radiobutton -label 16 -command CloadDetailTexelSize -variable loadDetailTexelSize -value 2
.loadDetailTexelSizeMB.menu add radiobutton -label 32 -command CloadDetailTexelSize -variable loadDetailTexelSize -value 3

set LloadDetailTexelSize 16
set loadDetailTexelSize 2

label .loadDetailTexelSizeL -width 8 -relief sunken -textvariable LloadDetailTexelSize


proc CloadDetailTexelSize {} {
   global loadDetailTexelSize
   global LloadDetailTexelSize

    switch $loadDetailTexelSize {
	0 {set LloadDetailTexelSize   4}
	1 {set LloadDetailTexelSize   8}
	2 {set LloadDetailTexelSize 16}
	3 {set LloadDetailTexelSize 32}
    }
}

label .loadDetailWidthL  -width 10 -text "width" -relief groove
entry .loadDetailWidthE -width 8 -relief sunken -textvariable loadDetailWidth
set loadDetailWidth 32

label .loadDetailHeightL -width 10 -text "height" -relief groove
entry .loadDetailHeightE -width 8 -relief sunken -textvariable loadDetailHeight
set loadDetailHeight 32

set loadDetailTmemaddr 256
label .loadDetailAddrsL  -width 10 -text "tmemAddr" -relief groove
label .loadDetailAddrsE  -width 8 -relief sunken -text $loadDetailTmemaddr

menubutton .loadDetailWrapMirsMB  -width 10 -text "wrapMirrS" -relief raised -menu .loadDetailWrapMirsMB.menu -bg LightGray -activebackground LightGray
menu .loadDetailWrapMirsMB.menu 
.loadDetailWrapMirsMB.menu add radiobutton -label wrapS  -command CloadDetailWrapMirS -variable loadDetailWrapMirS -value 0
.loadDetailWrapMirsMB.menu add radiobutton -label mirrorS  -command CloadDetailWrapMirS -variable loadDetailWrapMirS -value 1

set loadDetailWrapMirS 0
set LloadDetailWrapMirS wrapS

label .loadDetailWrapMirsL -width 8 -relief sunken -textvariable LloadDetailWrapMirS


proc CloadDetailWrapMirS {} {
   global loadDetailWrapMirS
   global LloadDetailWrapMirS

    switch $loadDetailWrapMirS {
	0   {set LloadDetailWrapMirS   wrS}
	1 {set LloadDetailWrapMirS   miS}
    }
}

checkbutton .loadDetailClampsCB -width 7 -command loadDetailClampSsetLabel -padx 3 -text "clampS" -variable loadDetailClampS
set loadDetailClampS 1

label .loadDetailClampsL -width 8 -relief sunken -textvariable loadDetailClampsLabel
set loadDetailClampsLabel On

proc loadDetailClampSsetLabel {} {
  global loadDetailClampS
  global loadDetailClampsLabel
  if {$loadDetailClampS == 1} {
       set loadDetailClampsLabel "On" 
  } else {
      set loadDetailClampsLabel "Off"
  }
}

label .loadDetailMasksL  -width 10 -text "maskS" -relief groove
entry .loadDetailMasksE -width 8 -relief sunken -textvariable loadDetailMaskS
set loadDetailMaskS 5

label .loadDetailShiftsL  -width 10 -text "shiftS" -relief groove
entry .loadDetailShiftsE -width 8 -relief sunken -textvariable loadDetailShiftS
set loadDetailShiftS 5

menubutton .loadDetailWrapMirtMB  -width 10 -text "wrapMirrT" -relief raised -menu .loadDetailWrapMirtMB.menu -bg LightGray -activebackground LightGray
menu .loadDetailWrapMirtMB.menu 
.loadDetailWrapMirtMB.menu add radiobutton -label wrapT  -command CloadDetailWrapMirT -variable loadDetailWrapMirT -value 0
.loadDetailWrapMirtMB.menu add radiobutton -label mirrorT  -command CloadDetailWrapMirT -variable loadDetailWrapMirT -value 1

set loadDetailWrapMirT 0
set LloadDetailWrapMirT wrapT

label .loadDetailWrapMirtL -width 8 -relief sunken -textvariable LloadDetailWrapMirT


proc CloadDetailWrapMirT {} {
   global loadDetailWrapMirT
   global LloadDetailWrapMirT

    switch $loadDetailWrapMirT {
	0   {set LloadDetailWrapMirT   wrT}
	1 {set LloadDetailWrapMirT   miT}
    }
}




checkbutton .loadDetailClamptCB -width 7 -command loadDetailClampTsetLabel -padx 3 -text "clampT" -variable loadDetailClampT
set loadDetailClampT 1

label .loadDetailClamptL -width 8 -relief sunken -textvariable loadDetailClamptLabel
set loadDetailClamptLabel On

proc loadDetailClampTsetLabel {} {
  global loadDetailClampT
  global loadDetailClamptLabel
  if {$loadDetailClampT == 1} {
       set loadDetailClamptLabel "On" 
  } else {
      set loadDetailClamptLabel "Off"
  }
}

menubutton .loadDetailWcmtMB   -width 10 -text "wcmT" -relief raised -menu .loadDetailWcmtMB.menu -bg LightGray -activebackground LightGray
menu .loadDetailWcmtMB.menu 
.loadDetailWcmtMB.menu add radiobutton -label WrapT  -variable loadDetailWcmt -value wrapT
.loadDetailWcmtMB.menu add radiobutton -label ClampT  -variable loadDetailWcmt -value clampT
.loadDetailWcmtMB.menu add radiobutton -label MirrorT -variable loadDetailWcmt -value mirrorT
set loadDetailWcmt wrapT
label .loadDetailWcmtL -width 8 -relief sunken -textvariable loadDetailWcmt

label .loadDetailMasktL  -width 10 -text "maskT" -relief groove
entry .loadDetailMasktE -width 8 -relief sunken -textvariable loadDetailMaskt
set loadDetailMaskt 4

label .loadDetailShifttL  -width 10 -text "shiftT" -relief groove
entry .loadDetailShifttE -width 8 -relief sunken -textvariable loadDetailShiftT
set loadDetailShiftT 5

label .loadDetailPalttL  -width 10 -text "palette" -relief groove
entry .loadDetailPalttE -width 8 -relief sunken -textvariable loadDetailPalette
set loadDetailPalette 0

checkbutton .loadDetailMipmapCB -text "mipmap" -variable loadDetailMipmap
set loadDetailMipmap 0

button .loadDetailDoneB -command loadDet  -text "done"
