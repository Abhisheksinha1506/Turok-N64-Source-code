 ##################### Load TLUT ###################################################
set loadTlutOptions {.loadTlutOffsetL .loadTlutCountL .loadTlutDoneB}

set loadTlutEntries {.loadTlutOffsetE .loadTlutCountE }

for {set i 0} {$i < [llength $loadTlutOptions]} {incr i 1} {
   frame .loadTlutFrame$i
}
 #----------------------------------------------------------------------------------------------

label .loadTlutLoadTlutL -text "loadTLUT" -relief groove

label .loadTlutOffsetL  -width 10 -text "tmemAddr" -relief groove
entry .loadTlutOffsetE  -width 8 -relief sunken -textvariable loadTlutOffset
#set loadTlutOffset 1

label .loadTlutCountL  -width 10 -text "count" -relief groove
entry .loadTlutCountE  -width 8 -relief sunken -textvariable loadTlutCount
#set loadTlutCount 1

label .loadTlutAddrL  -width 10 -text "dramAddr" -relief groove
entry .loadTlutAddrE  -width 8 -relief sunken -textvariable loadTlutAddr
#set loadTlutAddr 256

button .loadTlutDoneB -text "done" -command CloadTlut

proc CloadTlut {} {
	global fptr record
	global loadTlutOffset
	global loadTlutCount loadTlutAddr
	global loadTlut_dirty

 	set loadTlut_dirty 1

	callback_loadTlut
	callback_send_dl

    	if {$record == 1} {
	  puts $fptr "set loadTlutOffset $loadTlutOffset"
	  puts $fptr "set loadTlutCount $loadTlutCount"
	  puts $fptr "set loadTlutAddr $loadTlutAddr"
	  puts $fptr "CloadTlut"
    	}
}
