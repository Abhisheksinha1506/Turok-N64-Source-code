 #--------------------------- loadTile --------------------------------------------
set loadTileOptions {.loadTileTileL .loadTileSlTlL .loadTileShThL .loadTileDoneB}
set loadTileEntries {.loadTileTileE .loadTileSlE .loadTileTlE .loadTileShE .loadTileThE}

for {set i 0} {$i < [llength $loadTileOptions]} {incr i 1} {
   frame .loadTileFrame$i
}
 #----------------------------------------------------------------------------------

label .loadTileL  -text "loadTile" -relief groove

label .loadTileTileL  -width 10 -text "tile" -relief groove
entry .loadTileTileE  -width 9 -relief sunken -textvariable loadTileTile
#set loadTileTile 0

label .loadTileSlTlL  -width 10 -text "Slo:Tlo" -relief groove
entry .loadTileSlE  -width 4 -relief sunken -textvariable loadTileSl
#set loadTileSl 0
entry .loadTileTlE  -width 4 -relief sunken -textvariable loadTileTl
#set loadTileTl 0

label .loadTileShThL  -width 10 -text "Shi:Thi" -relief groove
entry .loadTileShE  -width 4 -relief sunken -textvariable loadTileSh
#set loadTileSh 0
entry .loadTileThE  -width 4 -relief sunken -textvariable loadTileTh
#set loadTileTh 0

button .loadTileDoneB -command CloadTile  -text "done"

proc CloadTile {} {
	global fptr record
	global loadTileTile loadTileSl loadTileTl
	global loadTileSh loadTileTh
        global loadTile_dirty

        set loadTile_dirty 1
	callback_loadTile
	callback_send_dl

    	if {$record == 1} {
	  puts $fptr "set loadTileTile $loadTileTile"
	  puts $fptr "set loadTileSl $loadTileSl"
	  puts $fptr "set loadTileTl $loadTileTl"
	  puts $fptr "set loadTileSh $loadTileSh"
	  puts $fptr "set loadTileTh $loadTileTh"
	  puts $fptr "CloadTile"
    	}
}
