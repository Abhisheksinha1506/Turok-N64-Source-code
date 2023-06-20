 #-----------------------------loadBlock--------------------------------------------
set loadBlockOptions {.loadBlockTileL .loadBlockSlTlL .loadBlockShL .loadBlockDxtL .loadBlockDone}
set loadBlockEntries {.loadBlockTileE .loadBlockSlE .loadBlockTlE .loadBlockShE .loadBlockDxtE}

for {set i 0} {$i < [llength $loadBlockOptions]} {incr i 1} {
   frame .loadBlockFrame$i
}
 #------------------------------------------------------------------------------------

label .loadBlockL  -text "loadBlock" -relief groove

label .loadBlockTileL  -width 10 -text "tile" -relief groove
entry .loadBlockTileE  -width 9 -relief sunken -textvariable loadBlockTile
#set loadBlockTile 0

label .loadBlockSlTlL  -width 10 -text "Slo:Tlo" -relief groove
entry .loadBlockSlE  -width 4 -relief sunken -textvariable loadBlockSl
set loadBlockSl 0
entry .loadBlockTlE  -width 4 -relief sunken -textvariable loadBlockTl
#set loadBlockTl 0

label .loadBlockShL  -width 10 -text "Shi" -relief groove
entry .loadBlockShE  -width 9 -relief sunken -textvariable loadBlockSh
#set loadBlockSh 0

label .loadBlockDxtL  -width 10 -text "DxT" -relief groove
entry .loadBlockDxtE  -width 9 -relief sunken -textvariable loadBlockDxt
#set loadBlockDxt 0

button .loadBlockDone -text "done" -command CloadBlock

proc CloadBlock {} {
	global record fptr
	global loadBlockTile loadBlockSl loadBlockTl 
	global loadBlockSh loadBlockDxt
	global loadBlock_dirty 

	set loadBlock_dirty 1

	callback_loadBlock
	callback_send_dl

    	if {$record == 1} {
	  puts $fptr "set loadBlockTile $loadBlockTile"
	  puts $fptr "set loadBlockSl $loadBlockSl"
	  puts $fptr "set loadBlockTl $loadBlockTl"
	  puts $fptr "set loadBlockSh $loadBlockSh"
	  puts $fptr "set loadBlockDxt $loadBlockDxt"
	  puts $fptr "CloadBlock"
    	}
}
