   #------------------ Set Convert --------------------------------------------------
frame .setConvertFrame0 -relief ridge -borderwidth 2
frame .setConvertFrame1 -relief ridge -borderwidth 2
frame .setConvertFrame2 -relief ridge -borderwidth 2
frame .setConvertFrame3 -relief ridge -borderwidth 2
frame .setConvertFrame4 -relief ridge -borderwidth 2
frame .setConvertFrame5 -relief ridge -borderwidth 2

frame .setConvertPair0
frame .setConvertPair1
frame .setConvertPair2
frame .setConvertPair3
frame .setConvertPair4
frame .setConvertPair5

   
   label .setConvertL -text "setConvert" -relief groove

   scale .setConvertS0 -label K0 -from 0 -to 255 -length 130 -orient vertical \
   -command CsetConvertK0

   entry .setConvertE0 -width 3 -relief sunken -textvariable setConvertK0
   #set setConvertK0 128
   #.setConvertS0 set 128

   bind .setConvertE0 <Return> {
        if {$setConvertK0 > 255} {set setConvertK0 255}
        if {$setConvertK0 < 0} {set setConvertK0 0}
        .setConvertS0 set $setConvertK0
        focus none
	if {$record == 1} {
		puts $fptr "set setConvertK0 $setConvertK0"
		puts $fptr ".setConvertS0 set $setConvertK0"
	}
   }

   proc CsetConvertK0 value {
	global setConvertK0
	global fptr record
	set setConvertK0 $value
	if {$record == 1} {
		puts $fptr "set setConvertK0 $setConvertK0"
		puts $fptr ".setConvertS0 set $setConvertK0"
	}
	callback_setConvert
	callback_send_dl
   }


   scale .setConvertS1 -label K1 -from 0 -to 255 -length 130 -orient vertical \
   -command CsetConvertK1

   entry .setConvertE1 -width 3 -relief sunken -textvariable setConvertK1
   #set setConvertK1 128
   #.setConvertS1 set 128

   bind .setConvertE1 <Return> {
        if {$setConvertK1 > 255} {set setConvertK1 255}
        if {$setConvertK1 < 0} {set setConvertK1 0}
        .setConvertS1 set $setConvertK1
        focus none
	if {$record == 1} {
		puts $fptr "set setConvertK1 $setConvertK1"
		puts $fptr ".setConvertS1 set $setConvertK1"
	}
   }

   proc CsetConvertK1 value {
	global setConvertK1
	global fptr record
	set setConvertK1 $value
	if {$record == 1} {
		puts $fptr "set setConvertK1 $setConvertK1"
		puts $fptr ".setConvertS1 set $setConvertK1"
	}
	callback_setConvert
	callback_send_dl
   }

   scale .setConvertS2 -label K2 -from 0 -to 255 -length 130 -orient vertical \
   -command CsetConvertK2

   entry .setConvertE2 -width 3 -relief sunken -textvariable setConvertK2
   #set setConvertK2 128
   #.setConvertS2 set 128

   bind .setConvertE2 <Return> {
        if {$setConvertK2 > 255} {set setConvertK2 255}
        if {$setConvertK2 < 0} {set setConvertK2 0}
        .setConvertS2 set $setConvertK2
        focus none
	if {$record == 1} {
		puts $fptr "set setConvertK2 $setConvertK2"
		puts $fptr ".setConvertS2 set $setConvertK2"
	}
   }

   proc CsetConvertK2 value {
	global setConvertK2
	global fptr record
	set setConvertK2 $value
	if {$record == 1} {
		puts $fptr "set setConvertK2 $setConvertK2"
		puts $fptr ".setConvertS2 set $setConvertK2"
	}
	callback_setConvert
	callback_send_dl
   }

   scale .setConvertS3 -label K3 -from 0 -to 255 -length 130 -orient vertical \
   -command CsetConvertK3

   entry .setConvertE3 -width 3 -relief sunken -textvariable setConvertK3
   #set setConvertK3 128
   #.setConvertS3 set 128

   bind .setConvertE3 <Return> {
        if {$setConvertK3 > 255} {set setConvertK3 255}
        if {$setConvertK3 < 0} {set setConvertK3 0}
        .setConvertS3 set $setConvertK3
        focus none
	if {$record == 1} {
		puts $fptr "set setConvertK3 $setConvertK3"
		puts $fptr ".setConvertS3 set $setConvertK3"
	}
   }

   proc CsetConvertK3 value {
	global setConvertK3
	global fptr record
	set setConvertK3 $value
	if {$record == 1} {
		puts $fptr "set setConvertK3 $setConvertK3"
		puts $fptr ".setConvertS3 set $setConvertK3"
	}
	callback_setConvert
	callback_send_dl
   }

   scale .setConvertS4 -label K4 -from 0 -to 255 -length 130 -orient vertical \
   -command CsetConvertK4

   entry .setConvertE4 -width 3 -relief sunken -textvariable setConvertK4
   #set setConvertK4 128
   #.setConvertS4 set 128

   bind .setConvertE4 <Return> {
        if {$setConvertK4 > 255} {set setConvertK4 255}
        if {$setConvertK4 < 0} {set setConvertK4 0}
        .setConvertS4 set $setConvertK4
	.cc.convertK4S set $setConvertK4
   	focus none
	if {$record == 1} {
		puts $fptr "set setConvertK4 $setConvertK4"
		puts $fptr ".setConvertS4 set $setConvertK4"
		puts $fptr ".cc.convertK4S set $setConvertK4"
	}
	callback_setConvert
	callback_send_dl
   }

   proc CsetConvertK4 value {
	global setConvertK4 ccConvertK4
	global fptr record
	set setConvertK4 $value
	.cc.convertK4S set $setConvertK4
	if {$record == 1} {
		puts $fptr "set setConvertK4 $setConvertK4"
		puts $fptr ".setConvertS4 set $setConvertK4"
		puts $fptr ".cc.convertK4S set $setConvertK4"
	}
	callback_setConvert
	callback_send_dl
   }

   scale .setConvertS5 -label K5 -from 0 -to 255 -length 130 -orient vertical \
   -command CsetConvertK5

   entry .setConvertE5 -width 3 -relief sunken -textvariable setConvertK5
   #set setConvertK5 128
   #.setConvertS5 set 128

   bind .setConvertE5 <Return> {
        if {$setConvertK5 > 255} {set setConvertK5 255}
        if {$setConvertK5 < 0} {set setConvertK5 0}
        .setConvertS5 set $setConvertK5
	.cc.convertK5S set $setConvertK5
        focus none
	if {$record == 1} {
		puts $fptr "set setConvertK5 $setConvertK5"
		puts $fptr "CsetConvertK5 $setConvertK5"
		puts $fptr ".setConvertS5 set $setConvertK5"
		puts $fptr ".cc.convertK5S set $setConvertK5"
	}
   }

   proc CsetConvertK5 value {
	global setConvertK5 ccConvertK4
	global fptr record
	set setConvertK5 $value
	.cc.convertK5S set $setConvertK5
	if {$record == 1} {
		puts $fptr "set setConvertK5 $setConvertK5"
		puts $fptr "CsetConvertK5 $setConvertK5"
		puts $fptr ".setConvertS5 set $setConvertK5"
		puts $fptr ".cc.convertK5S set $setConvertK5"
	}

	callback_setConvert
	callback_send_dl
   }
   set setConvertK1 128
