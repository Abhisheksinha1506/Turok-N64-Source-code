 #--------------------------- setTimg --------------------------------------------
set setTimgOptions {.setTimgFmtMB .setTimgSizeMB .setTimgwidthL .setTimgDoneB}
set setTimgEntries {.setTimgFmtE .setTimgSizeE .setTimgwidthE }

for {set i 0} {$i < [llength $setTimgOptions]} {incr i 1} {
   frame .setTimgFrame$i
}

label .setTimgL  -text "setTextureImg" -relief groove

menubutton .setTimgFmtMB -text "timgFmt" -width 10 -relief raised -menu .setTimgFmtMB.menu -bg LightGray -activebackground LightGray
menu .setTimgFmtMB.menu
.setTimgFmtMB.menu add radiobutton -label RGBA -command CsetTimgFmt -variable setTimgFmt -value 0
.setTimgFmtMB.menu add radiobutton -label YUV -command CsetTimgFmt -variable setTimgFmt -value 1
.setTimgFmtMB.menu add radiobutton -label CI -command CsetTimgFmt -variable setTimgFmt -value 2
.setTimgFmtMB.menu add radiobutton -label IA -command CsetTimgFmt -variable setTimgFmt -value 3
.setTimgFmtMB.menu add radiobutton -label I -command CsetTimgFmt -variable setTimgFmt -value 4

#set setTimgFmt 0
#set LsetTimgFmt RGBA

label .setTimgFmtE -width 9 -relief sunken -textvariable LsetTimgFmt

proc CsetTimgFmt {} {
   global setTimgFmt
   global LsetTimgFmt

    switch $setTimgFmt {
	0 {set LsetTimgFmt RGBA}
	1 {set LsetTimgFmt YUV}
	2 {set LsetTimgFmt CI}
	3 {set LsetTimgFmt IA}
	4 {set LsetTimgFmt I}
    }
}

menubutton .setTimgSizeMB   -text "timgSiz" -width 10 -relief raised -menu .setTimgSizeMB.menu -bg LightGray -activebackground LightGray
menu .setTimgSizeMB.menu
.setTimgSizeMB.menu add radiobutton -label 4 -command CsetTimgSize -variable setTimgSize -value 0
.setTimgSizeMB.menu add radiobutton -label 8 -command CsetTimgSize -variable setTimgSize -value 1
.setTimgSizeMB.menu add radiobutton -label 16 -command CsetTimgSize -variable setTimgSize -value 2
.setTimgSizeMB.menu add radiobutton -label 32 -command CsetTimgSize -variable setTimgSize -value 3

#set setTimgSize 2
#set LsetTimgSize 16

label .setTimgSizeE -width 9 -relief sunken -textvariable LsetTimgSize

proc CsetTimgSize {} {
   global setTimgSize
   global LsetTimgSize

    switch $setTimgSize {
	0 {set LsetTimgSize   4}
	1 {set LsetTimgSize   8}
	2 {set LsetTimgSize 16}
	3 {set LsetTimgSize 32}
    }
}

label .setTimgwidthL  -width 10 -text "texWidth" -relief groove
entry .setTimgwidthE  -width 9 -relief sunken -textvariable setTimgwidth
#set setTimgwidth 32

 #Allow symbolic addresses?
label .setTimgDramAddrL  -width 10 -text "dramAddr" -relief groove
entry .setTimgDramAddrE  -width 9 -relief sunken -textvariable setTimgDramAddr
#set setTimgDramAddr 0
