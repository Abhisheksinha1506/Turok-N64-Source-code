  #-------------------------Set Other Mode-------------------------------------------

set G_TT_NONE       0
set G_TT_RGBA16     2
set G_TT_IA16       3


set setTotherOptions {.setTotherDetailMB .setTotherTlutMB .setTotherTexFiltMB .setTotherConvertMB .setTotherPerspCB .setTotherLodCB .setTotherDoneB}
set setTotherEntries {.setTotherDetailL .setTotherTlutL .setTotherTexFiltL .setTotherConvertL}

for {set i 0} {$i < [llength $setTotherOptions]} {incr i 1} {
   frame .setTotherFrame$i
}

label .setTotherL  -text "setTother" -relief groove

checkbutton .setTotherPerspCB  -text "texPersp" -variable setTotherPersp
set setTotherPersp 1

menubutton .setTotherDetailMB  -width 10 -text "texCSD" -relief raised -menu .setTotherDetailMB.menu -bg LightGray -activebackground LightGray
menu .setTotherDetailMB.menu
.setTotherDetailMB.menu add radiobutton -label Clamp -command CsetTotherDetail -variable setTotherDetail -value 0
.setTotherDetailMB.menu add radiobutton -label Sharpen -command CsetTotherDetail -variable setTotherDetail -value 1
.setTotherDetailMB.menu add radiobutton -label Detail -command CsetTotherDetail -variable setTotherDetail -value 2

#set setTotherDetail 0
#set LsetTotherDetail Clamp

label .setTotherDetailL -width 9 -relief sunken -textvariable LsetTotherDetail


proc CsetTotherDetail {} {
   global setTotherDetail
   global LsetTotherDetail

    switch $setTotherDetail {
	0	{set LsetTotherDetail   Clamp}
	1	{set LsetTotherDetail   Sharpen}
	2	{set LsetTotherDetail   Detail}
    }
}

checkbutton .setTotherLodCB  -text "texLOD" -variable setTotherLOD
set setTotherLOD 0

menubutton .setTotherTlutMB  -width 10 -text "texTLUT" -relief raised -menu .setTotherTlutMB.menu -bg LightGray -activebackground LightGray
menu .setTotherTlutMB.menu
.setTotherTlutMB.menu add radiobutton -label None  -command CsetTotherTlut -variable setTotherTlut -value 0
.setTotherTlutMB.menu add radiobutton -label RGBA16  -command CsetTotherTlut -variable setTotherTlut -value 2
.setTotherTlutMB.menu add radiobutton -label IA16 -command CsetTotherTlut -variable setTotherTlut -value 3

#set setTotherTlut $G_TT_NONE
#set LsetTotherTlut None

label .setTotherTlutL -width 9 -relief sunken -textvariable LsetTotherTlut

proc CsetTotherTlut {} {
   global setTotherTlut
   global LsetTotherTlut

    switch $setTotherTlut {
        0	{set LsetTotherTlut None  }
        2	{set LsetTotherTlut RGBA16  }
        3	{set LsetTotherTlut IA16  }
    }
}

menubutton .setTotherTexFiltMB  -width 10 -text "texFilt" -relief raised -menu .setTotherTexFiltMB.menu -bg LightGray -activebackground LightGray
menu .setTotherTexFiltMB.menu
.setTotherTexFiltMB.menu add radiobutton -label Bilerp -command CsetTotherTexFilt -variable setTotherTexFilt -value 2
.setTotherTexFiltMB.menu add radiobutton -label Average  -command CsetTotherTexFilt -variable setTotherTexFilt -value 3
.setTotherTexFiltMB.menu add radiobutton -label Point  -command CsetTotherTexFilt -variable setTotherTexFilt -value 0

#set setTotherTexFilt 2
#set LsetTotherTexFilt Bilerp

label .setTotherTexFiltL -width 9 -relief sunken -textvariable LsetTotherTexFilt

proc CsetTotherTexFilt {} {
   global setTotherTexFilt
   global LsetTotherTexFilt

    switch $setTotherTexFilt {
        2	{set LsetTotherTexFilt Bilerp}
        3	{set LsetTotherTexFilt Average}
        0	{set LsetTotherTexFilt Point }
    }
}


menubutton .setTotherConvertMB  -width 10 -text "texConvert" -relief raised -menu .setTotherConvertMB.menu -bg LightGray -activebackground LightGray
menu .setTotherConvertMB.menu
.setTotherConvertMB.menu add radiobutton -label Filt -command CsetTotherConvert -variable setTotherConvert -value 6
.setTotherConvertMB.menu add radiobutton -label FiltConv  -command CsetTotherConvert -variable setTotherConvert -value 5
.setTotherConvertMB.menu add radiobutton -label Conv  -command CsetTotherConvert -variable setTotherConvert -value 0

#set setTotherConvert 6
#set LsetTotherConvert Filt

label .setTotherConvertL -width 9 -relief sunken -textvariable LsetTotherConvert

proc CsetTotherConvert {} {
   global setTotherConvert
   global LsetTotherConvert

    switch $setTotherConvert {
        6	{set LsetTotherConvert Filt}
        5	{set LsetTotherConvert FiltConv}
        0	{set LsetTotherConvert Conv}
    }
}

button .setTotherDoneB -command setTother  -text "done"
