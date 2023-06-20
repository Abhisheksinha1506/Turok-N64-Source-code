  #------------------ Set Tile --------------------------------------------------
set numTiles 8

set setTileOptions { .setTileTileNoL .setTileFormatL .setTileTexelSizeL .setTileLineL .setTileAddrsL .setTileWrapMirsL .setTileClampsL .setTileMasksL .setTileShiftsL .setTileWrapMirtL .setTileClamptL .setTileMasktL .setTileShifttL .setTilePalttL .setTileSizeSlL .setTileSizeShL .setTileSizeTlL .setTileSizeThL}

set setTileEntries {.setTileTileNo .setTileFormatMB .setTileTexelSizeMB .setTileLineE .setTileAddrsE .setTileWrapMirsMB .setTileClampsCB .setTileMasksE .setTileShiftsE .setTileWrapMirtMB .setTileClamptCB .setTileMasktE .setTileShifttE .setTilePalttE .setTileSizeSlE .setTileSizeShE .setTileSizeTlE .setTileSizeThE }

for {set i 0} {$i < [llength $setTileOptions]} {incr i 1} {
   frame .setTileFrame$i
}
   frame .setTileFrame$i


label .setTileL -text "setTile" -relief groove

label .setTileTileNoL -text "tile" -width 10 -relief groove
for {set tile 0} {$tile < $numTiles} {incr tile 1} {
 label .setTileTileNo$tile -text $tile -width 4  -relief groove
}

label .setTileFormatL -text "texFmt" -width 10 -relief raised -bg LightGray

for {set tile 0} {$tile < $numTiles} {incr tile 1} {
 menubutton .setTileFormatMB$tile -textvariable LsetTileFormat$tile -width 4 -relief raised \
 -menu .setTileFormatMB$tile.menu -bg LightGray -activebackground LightGray
 menu .setTileFormatMB$tile.menu
 .setTileFormatMB$tile.menu add radiobutton -label RGBA -command CsetTileFormat -variable setTileFormat$tile -value 0
 .setTileFormatMB$tile.menu add radiobutton -label YUV -command CsetTileFormat -variable setTileFormat$tile -value 1
 .setTileFormatMB$tile.menu add radiobutton -label CI -command CsetTileFormat -variable setTileFormat$tile -value 2
 .setTileFormatMB$tile.menu add radiobutton -label IA -command CsetTileFormat -variable setTileFormat$tile -value 3
 .setTileFormatMB$tile.menu add radiobutton -label I -command CsetTileFormat -variable setTileFormat$tile -value 4
 #set setTileFormat$tile 0
 #set LsetTileFormat$tile rgba
}

proc CsetTileFormat {} {
  global numTiles
  for {set tile 0} {$tile < $numTiles} {incr tile 1} {
   global setTileFormat$tile
   global LsetTileFormat$tile
  }

  for {set tile 0} {$tile < $numTiles} {incr tile 1} {
  set first setTileFormat
  set next  $tile
  upvar #0 $first$next x
    switch $x {
	0 {set LsetTileFormat$tile rgba}
	1 {set LsetTileFormat$tile yuv}
	2 {set LsetTileFormat$tile ci}
	3 {set LsetTileFormat$tile ia}
	4 {set LsetTileFormat$tile i}
    }
  }
}
      
    

label .setTileTexelSizeL   -text "texSiz" -width 10 -relief raised -bg LightGray

for {set tile  0} {$tile < $numTiles } {incr tile 1} {
 menubutton .setTileTexelSizeMB$tile   -textvariable LsetTileTexelSize$tile -width 4 -relief raised -menu \
 .setTileTexelSizeMB$tile.menu -bg LightGray -activebackground LightGray
 menu .setTileTexelSizeMB$tile.menu
 .setTileTexelSizeMB$tile.menu add radiobutton -command CsetTileTexelSize -label 4 -variable setTileTexelSize$tile -value 0
 .setTileTexelSizeMB$tile.menu add radiobutton -command CsetTileTexelSize -label 8 -variable setTileTexelSize$tile -value 1 
 .setTileTexelSizeMB$tile.menu add radiobutton -command CsetTileTexelSize -label 16  -variable setTileTexelSize$tile -value 2
 .setTileTexelSizeMB$tile.menu add radiobutton -command CsetTileTexelSize -label 32  -variable setTileTexelSize$tile -value 3
 #set setTileTexelSize$tile 2
 #set LsetTileTexelSize$tile 16
}

proc CsetTileTexelSize {} {
  global numTiles
  for {set tile 0} {$tile < $numTiles} {incr tile 1} {
   global setTileTexelSize$tile
   global LsetTileTexelSize$tile
  }

  for {set tile 0} {$tile < $numTiles} {incr tile 1} {
  set first setTileTexelSize
  set next  $tile
  upvar #0 $first$next x
    switch $x {
	0 {set LsetTileTexelSize$tile   4}
	1 {set LsetTileTexelSize$tile   8}
	2 {set LsetTileTexelSize$tile 16}
	3 {set LsetTileTexelSize$tile 32}
    }
  }
}

label .setTileLineL  -width 10 -text "lineSiz" -relief groove
for {set tile  0} {$tile < $numTiles} {incr tile 1} {
 entry .setTileLineE$tile -width 4 -relief sunken -bd 3 -textvariable setTileLine$tile
 #set setTileLine$tile 32
}

label .setTileAddrsL  -width 10 -text "tmemAddr" -relief groove
for {set tile  0} {$tile < $numTiles} {incr tile 1} {
 entry .setTileAddrsE$tile  -width 4 -relief sunken -bd 3 -text setTileAddrs$tile
 #set setTileAddrs$tile 256
}

label .setTileWrapMirsL  -width 10 -text "wrapMirrS" -relief raised -bg LightGray

for {set tile  0} {$tile < $numTiles} {incr tile 1} {
 menubutton .setTileWrapMirsMB$tile  -width 4 -textvariable LsetTileWrapMirs$tile -relief raised -menu \
 .setTileWrapMirsMB$tile.menu -bg LightGray -activebackground LightGray
 menu .setTileWrapMirsMB$tile.menu 
 .setTileWrapMirsMB$tile.menu add radiobutton -command CsetTileWrapMirs -label WrapS  -variable setTileWrapMirs$tile -value 0
 .setTileWrapMirsMB$tile.menu add radiobutton -command CsetTileWrapMirs -label MirrorS -variable setTileWrapMirs$tile -value 1
 #set LsetTileWrapMirs$tile wrS
 #set setTileWrapMirs$tile 0
}

proc CsetTileWrapMirs {} {
  global numTiles
  for {set tile 0} {$tile < $numTiles} {incr tile 1} {
   global setTileWrapMirs$tile
   global LsetTileWrapMirs$tile
  }

  for {set tile 0} {$tile < $numTiles} {incr tile 1} {
  set first setTileWrapMirs
  set next  $tile
  upvar #0 $first$next x
    switch $x {
	0   {set LsetTileWrapMirs$tile   wrS}
	1 {set LsetTileWrapMirs$tile   miS}
    }
  }
}


label .setTileClampsL  -width 10 -text "clampS" -relief raised -bg LightGray

for {set tile  0} {$tile < $numTiles} {incr tile 1} {
  checkbutton .setTileClampsCB$tile -width 1 -padx 2p -variable setTileClamps$tile
 # set setTileClamps$tile 1
}

label .setTileMasksL  -width 10 -text "maskS" -relief groove
for {set tile 0} {$tile < $numTiles} {incr tile 1} {
 entry .setTileMasksE$tile -width 4 -relief sunken -bd 3 -textvariable setTileMaskS$tile
 #set setTileMaskS$tile 5
}

label .setTileShiftsL  -width 10 -text "shiftS" -relief groove
for {set tile 0} {$tile < $numTiles} {incr tile 1} {
 entry .setTileShiftsE$tile -width 4 -relief sunken -bd 3 -textvariable setTileShiftS$tile
 #set setTileShiftS$tile 5
}

label .setTileWrapMirtL  -width 10 -text "wrapMirrT" -relief raised -bg LightGray

for {set tile  0} {$tile < $numTiles} {incr tile 1} {
 menubutton .setTileWrapMirtMB$tile  -width 4 -textvariable LsetTileWrapMirt$tile -relief raised -menu \
 .setTileWrapMirtMB$tile.menu -bg LightGray -activebackground LightGray
 menu .setTileWrapMirtMB$tile.menu 
 .setTileWrapMirtMB$tile.menu add radiobutton -label WrapT  -command CsetTileWrapMirt -variable setTileWrapMirt$tile -value 0
 .setTileWrapMirtMB$tile.menu add radiobutton -label MirrorT -command CsetTileWrapMirt -variable setTileWrapMirt$tile -value 1

 #set LsetTileWrapMirt$tile wrT
 #set setTileWrapMirt$tile 0
}

proc CsetTileWrapMirt {} {
  global numTiles
  for {set tile 0} {$tile < $numTiles} {incr tile 1} {
   global setTileWrapMirt$tile
   global LsetTileWrapMirt$tile
  }

  for {set tile 0} {$tile < $numTiles} {incr tile 1} {
  set first setTileWrapMirt
  set next  $tile
  upvar #0 $first$next x
    switch $x {
	0   {set LsetTileWrapMirt$tile   wrT}
	1 {set LsetTileWrapMirt$tile   miT}
    }
  }
}


label .setTileClamptL  -width 10 -text "clampT" -relief raised -bg LightGray

for {set tile  0} {$tile < $numTiles} {incr tile 1} {
  checkbutton .setTileClamptCB$tile -width 1 -padx 2p -variable setTileClampt$tile
  #set setTileClampt$tile 1
}

label .setTileMasktL  -width 10 -text "maskT" -relief groove
for {set tile 0} {$tile < $numTiles} {incr tile 1} {
 entry .setTileMasktE$tile -width 4 -relief sunken -bd 3 -textvariable setTileMaskT$tile
 #set setTileMaskT$tile 4
}

label .setTileShifttL  -width 10 -text "shiftT" -relief groove
for {set tile 0} {$tile < $numTiles} {incr tile 1} {
 entry .setTileShifttE$tile -width 4 -relief sunken -bd 3 -textvariable setTileShiftT$tile
 #set setTileShiftT$tile 5
}

label .setTilePalttL  -width 10 -text "palette" -relief groove
for {set tile 0} {$tile < $numTiles} {incr tile 1} {
 entry .setTilePalttE$tile -width 4 -relief sunken -bd 3 -textvariable setTilePalette$tile
 #set setTilePalette$tile 0
}

 ############################### Set Tile Size portion ####################################

label .setTileSizeL  -text "setTileSize" -relief groove

label .setTileSizeTileL  -width 10 -text "tile" -relief groove
for {set tile 0} {$tile < $numTiles} {incr tile 1} {
 label .setTileSizeTileL$tile  -width 4 -relief groove -text $tile
}

# Note: The tileSize parameters are multiplied by 4 before being passed
# to the 'c' code to account for 2 fractional bits

label .setTileSizeSlL  -width 10 -text "sLow" -relief groove
for {set tile 0} {$tile < $numTiles} {incr tile 1} {
 entry .setTileSizeSlE$tile  -width 4 -bd 3 -relief sunken -textvariable setTileSizeSlFloat$tile
}


label .setTileSizeTlL  -width 10 -text "tLow" -relief groove
for {set tile 0} {$tile < $numTiles} {incr tile 1} {
 entry .setTileSizeTlE$tile  -width 4 -bd 3 -relief sunken -textvariable setTileSizeTlFloat$tile
 #set setTileSizeTl$tile 0
}

label .setTileSizeShL  -width 10 -text "sHi" -relief groove
for {set tile 0} {$tile < $numTiles} {incr tile 1} {
 entry .setTileSizeShE$tile  -width 4 -bd 3 -relief sunken -textvariable setTileSizeShFloat$tile
 #set setTileSizeSh$tile 0
}


label .setTileSizeThL  -width 10 -text "tHi" -relief groove
for {set tile 0} {$tile < $numTiles} {incr tile 1} {
 entry .setTileSizeThE$tile  -width 4 -bd 3 -relief sunken -textvariable setTileSizeThFloat$tile
 #set setTileSizeTh$tile 0
}
 ###########################################################################################

 button .setTileDoneB -command CsetTileAndTileSize  -text "done"
