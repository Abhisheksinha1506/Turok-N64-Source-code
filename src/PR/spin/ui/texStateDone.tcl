button .doneAllB -text "done" -command CsetTexStateAll

# This loop needed solely for create_callback.tcl to 
# be able to pick up these variables.
for {set tile 0} {$tile < $numTiles} {incr tile 1} {
  set setTileSizeSl$tile 0
  set setTileSizeTl$tile 0
  set setTileSizeSh$tile 0
  set setTileSizeTh$tile 0
}

proc CshiftTileSize {} {
	global fptr record numTiles

	for {set tile 0} {$tile < $numTiles} {incr tile 1} {
	  global setTileFormat$tile setTileTexelSize$tile
	  global setTileLine$tile setTileWrapMirs$tile
	  global setTileClamps$tile setTileMaskS$tile
	  global setTileShiftS$tile setTileWrapMirt$tile
	  global setTileClampt$tile setTileMaskT$tile
	  global setTileShiftT$tile setTilePalette$tile
	  global setTileSizeSlFloat$tile setTileSizeTlFloat$tile
	  global setTileSizeSl$tile setTileSizeTl$tile
	  global setTileSizeShFloat$tile setTileSizeThFloat$tile
	  global setTileSizeSh$tile setTileSizeTh$tile
	  global setTileAddrs$tile

	  # multiply x 4 to account for 2 frac bits

	  set first setTileSizeSlFloat
	  set next $tile
	  upvar #0 $first$next x
 	  set setTileSizeSl$tile [expr int($x * 4)]

	  set first setTileSizeShFloat
	  set next $tile
	  upvar #0 $first$next x
 	  set setTileSizeSh$tile [expr int($x * 4)]

	  set first setTileSizeTlFloat
	  set next $tile
	  upvar #0 $first$next x
 	  set setTileSizeTl$tile [expr int($x * 4)]

	  set first setTileSizeThFloat
	  set next $tile
	  upvar #0 $first$next x
 	  set setTileSizeTh$tile [expr int($x * 4)]

	}


}

proc CsetTexStateAll {} {
	global fptr record numTiles

	for {set tile 0} {$tile < $numTiles} {incr tile 1} {
	  global setTileFormat$tile setTileTexelSize$tile
	  global setTileLine$tile setTileWrapMirs$tile
	  global setTileClamps$tile setTileMaskS$tile
	  global setTileShiftS$tile setTileWrapMirt$tile
	  global setTileClampt$tile setTileMaskT$tile
	  global setTileShiftT$tile setTilePalette$tile
	  global setTileSizeSlFloat$tile setTileSizeTlFloat$tile
	  global setTileSizeSl$tile setTileSizeTl$tile
	  global setTileSizeShFloat$tile setTileSizeThFloat$tile
	  global setTileSizeSh$tile setTileSizeTh$tile
	  global setTileAddrs$tile
	}

	CshiftTileSize

	global spTexEnable spTexScaleS spTexScaleT
	global spTexPrimTile spTexMaxLevel
	global setTimgFmt setTimgSize setTimgwidth setTimgDramAddr
	global setTotherPersp setTotherDetail setTotherLOD setTotherTlut
	global setTotherTexFilt setTotherConvert


#Note: Remember to add proc names in the recording process if such procs
#are added to the appropriate buttons e.g. clamp has no procs attached

	if {$record == 1} {
		for {set tile 0} {$tile < $numTiles} {incr tile 1} {
		  set first setTileFormat
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileFormat$tile $x"
		  puts $fptr "CsetTileFormat"

		  set first setTileTexelSize
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileTexelSize$tile $x"
		  puts $fptr "CsetTileTexelSize"

		  set first setTileLine
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileLine$tile $x"

		  set first setTileAddrs
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileAddrs$tile $x"

		  set first setTileWrapMirs
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileWrapMirs$tile $x"
		  puts $fptr "CsetTileWrapMirs"

		  set first setTileClamps
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileClamps$tile $x"

		  set first setTileMaskS
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileMaskS$tile $x"

		  set first setTileShiftS
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileShiftS$tile $x"

		  set first setTileWrapMirt
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileWrapMirt$tile $x"
		  puts $fptr "CsetTileWrapMirt"

		  set first setTileClampt
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileClampt$tile $x"

		  set first setTileMaskT
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileMaskT$tile $x"

		  set first setTileShiftT
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileShiftT$tile $x"

		  set first setTilePalette
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTilePalette$tile $x"

		  set first setTileSizeSlFloat
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileSizeSlFloat$tile $x"
		  puts $fptr "CshiftTileSize"

		  set first setTileSizeShFloat
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileSizeShFloat$tile $x"
		  puts $fptr "CshiftTileSize"

		  set first setTileSizeTlFloat
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileSizeTlFloat$tile $x"
		  puts $fptr "CshiftTileSize"

		  set first setTileSizeThFloat
		  set next $tile
		  upvar #0 $first$next x
		  puts $fptr "set setTileSizeThFloat$tile $x"
		  puts $fptr "CshiftTileSize"

		}
		
	#--------------- spTex buttons --------------------------
		puts $fptr "set spTexEnable $spTexEnable"
		puts $fptr "set spTexScaleS $spTexScaleS"
		puts $fptr "set spTexScaleT $spTexScaleT"
		puts $fptr "set spTexPrimTile $spTexPrimTile"
		puts $fptr "set spTexMaxLevel $spTexMaxLevel"

	#--------------- setTimg buttons --------------------------
		puts $fptr "set setTimgFmt $setTimgFmt"
		puts $fptr "CsetTimgFmt"
		puts $fptr "set setTimgSize $setTimgSize"
		puts $fptr "CsetTimgSize"
		puts $fptr "set setTimgwidth $setTimgwidth"
		puts $fptr "set setTimgDramAddr $setTimgDramAddr"

	#--------------- setTother buttons --------------------------
		puts $fptr "set setTotherTexFilt $setTotherTexFilt"
		puts $fptr "CsetTotherTexFilt"
		puts $fptr "set setTotherPersp $setTotherPersp"
		puts $fptr "set setTotherDetail $setTotherDetail"
		puts $fptr "CsetTotherDetail"
		puts $fptr "set setTotherLOD $setTotherLOD"
		puts $fptr "set setTotherTlut $setTotherTlut"
		puts $fptr "CsetTotherTlut"
		puts $fptr "set setTotherConvert $setTotherConvert"
		puts $fptr "CsetTotherConvert"
		puts $fptr "CsetTexStateAll"
	}

	callback_spTex
	callback_setTimg
	callback_setTile
	callback_setTileSize
	callback_setTother
	callback_send_dl

}

#CsetTexStateAll
