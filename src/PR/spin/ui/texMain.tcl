##################### Frame Declarations #########################################
frame .textureF
frame .actionsF
frame .actionsF0
frame .actionsF1
frame .actionsF2
frame .actionsF3
frame .stateF
frame .stateF0
frame .stateF1
frame .stateF2
frame .stateF3

frame .setTileF
frame .setTileOptionsF
frame .setTileEntriesF

frame .loadTexF
frame .loadTexOptionsF
frame .loadTexEntriesF

frame .loadDetailF
frame .loadDetailOptionsF
frame .loadDetailEntriesF

frame .loadTlutF
frame .loadTlutOptionsF
frame .loadTlutEntriesF

frame .loadBlockF

frame .loadTileF

frame .spTexF
frame .setTimgF
frame .setTotherModeF
frame .setTilesF
frame .setTotherF
frame .setConvertF -relief ridge -borderwidth 2
frame .setTileSizeF
##################### Texture Actions #########################################
source loadTex.tcl
source loadDet.tcl
source loadTlut.tcl
source loadTile.tcl
source loadBlock.tcl
############################ Texture State ########################################
source spTex.tcl
source setTimg.tcl
source setTother.tcl
source setConv.tcl
source setTileAndTileSize.tcl
############################### State Done Button #################################
source texStateDone.tcl

################################ Pack Frames ######################################
pack .loadTmL -in .loadTexF -side top -fill x
for {set i 0} {$i < [llength $loadTexEntries]} {incr i 1} {
     pack [lindex $loadTexOptions $i]  [lindex $loadTexEntries $i] -in .loadTexFrame$i -side left -fill x -expand 1
     pack .loadTexFrame$i -in .loadTexF -side top -fill x
}
pack [lindex $loadTexOptions $i] -in .loadTexF -side top -fill x
#pack [lindex $loadTexOptions [expr $i+1]] -in .loadTexF -side top -fill x
#pack [lindex $loadTexOptions [expr $i+2]] -in .loadTexF -side top -fill x
#-----------------------------------------------------------------------------------

pack .loadDetailLoadDetL -in .loadDetailF -side top -fill x
for {set i 0} {$i < [llength $loadDetailEntries]} {incr i 1} {
   pack [lindex $loadDetailOptions $i]  [lindex $loadDetailEntries $i] -in .loadDetailFrame$i -side left -fill x -expand 1
   pack .loadDetailFrame$i -in .loadDetailF -side top -fill x
}
pack [lindex $loadDetailOptions $i] -in .loadDetailF -side top -fill x
#-----------------------------------------------------------------------------------

pack .loadTlutLoadTlutL -in .loadTlutF -side top -fill x
for {set i 0} {$i < [llength $loadTlutEntries]} {incr i 1} {
   pack [lindex $loadTlutOptions $i]  [lindex $loadTlutEntries $i] -in .loadTlutFrame$i -side left -fill x -expand 1
   pack .loadTlutFrame$i -in .loadTlutF -side top -fill x
}
pack [lindex $loadTlutOptions $i] -in .loadTlutF -side top -fill x
#-----------------------------------------------------------------------------------

pack .spTexL -in .spTexF -side top -fill x
for {set i 0} {$i < [expr [llength $spTexEntries] ]} {incr i 1} {
     pack [lindex $spTexOptions $i]  [lindex $spTexEntries $i] -in .spTexFrame$i -side left -fill x \
     -expand 1
   pack .spTexFrame$i -in .spTexF -side top -fill x
}
pack [lindex $spTexOptions $i] -in .spTexF -side top -fill x
#pack [lindex $spTexOptions [expr $i+1]] -in .spTexF -side top -fill x
#-----------------------------------------------------------------------------------

pack .setTimgL -in .setTimgF -side top -fill x
for {set i 0} {$i < [llength $setTimgEntries]} {incr i 1} {
   pack [lindex $setTimgOptions $i]  [lindex $setTimgEntries $i] -in .setTimgFrame$i -side left -fill x -expand 1
   pack .setTimgFrame$i -in .setTimgF -side top -fill x
}
#pack [lindex $setTimgOptions $i] -in .setTimgF -side top -fill x
#-----------------------------------------------------------------------------------

pack .loadTileL -in .loadTileF -side top -fill x -expand 1
pack .loadTileTileL .loadTileTileE -in .loadTileFrame0 -side left -fill x -expand 1
pack .loadTileSlTlL .loadTileSlE .loadTileTlE -in .loadTileFrame1 -side left -fill x -expand 1
pack .loadTileShThL .loadTileShE .loadTileThE -in .loadTileFrame2 -side left -fill x -expand 1
pack .loadTileDoneB -in .loadTileFrame3 -side left -fill x -expand 1
pack .loadTileFrame0 .loadTileFrame1 .loadTileFrame2 .loadTileFrame3  -in .loadTileF -side top -fill x
#-----------------------------------------------------------------------------------

#pack .setTileSizeL -in .setTileSizeF -side top -fill x -expand 1
#pack .setTileSizeTileL .setTileSizeTileE -in .setTileSizeFrame0 -side left -fill x -expand 1
#pack .setTileSizeSlTlL .setTileSizeSlE .setTileSizeTlE -in .setTileSizeFrame1 -side left -fill x -expand 1
#pack .setTileSizeShThL .setTileSizeShE .setTileSizeThE -in .setTileSizeFrame2 -side left -fill x -expand 1
#pack .setTileSizeDoneB -in .setTileSizeFrame3 -side left -fill x -expand 1
#pack .setTileSizeFrame0 .setTileSizeFrame1 .setTileSizeFrame2 .setTileSizeFrame3  -in .setTileSizeF -side top -fill x
#-----------------------------------------------------------------------------------

pack .loadBlockL -in .loadBlockF -side top -fill x -expand 1
pack .loadBlockTileL .loadBlockTileE -in .loadBlockFrame0 -side left -fill x -expand 1
pack .loadBlockSlTlL .loadBlockSlE .loadBlockTlE -in .loadBlockFrame1 -side left -fill x -expand 1
pack .loadBlockShL .loadBlockShE -in .loadBlockFrame2 -side left -fill x -expand 1
pack .loadBlockDxtL .loadBlockDxtE -in .loadBlockFrame3 -side left -fill x -expand 1
pack .loadBlockDone -in .loadBlockFrame4 -side left -fill x -expand 1
pack .loadBlockFrame0 .loadBlockFrame1 .loadBlockFrame2 .loadBlockFrame3 .loadBlockFrame4  -in .loadBlockF -side top -fill x 
#-----------------------------------------------------------------------------------

pack .setTotherL -in .setTotherF -side top -fill x -expand 1
for {set i 0} {$i < [llength $setTotherEntries]} {incr i 1} {
   pack [lindex $setTotherOptions $i]  [lindex $setTotherEntries $i] -in .setTotherFrame$i -side left -fill x -expand 1
   pack .setTotherFrame$i -in .setTotherF -side top -fill x
}
pack [lindex $setTotherOptions $i] -in .setTotherF -side top -fill x -expand 1
pack [lindex $setTotherOptions [expr $i+1]] -in .setTotherF -side top -fill x -expand 1
#pack [lindex $setTotherOptions [expr $i+2]] -in .setTotherF -side top -fill x -expand 1
#-----------------------------------------------------------------------------------

pack .setConvertL -in .setConvertF -side top -fill x
for {set i 0} {$i < 6} {incr i 2} {
   set j [expr $i +1]

   pack .setConvertS$i  .setConvertE$i -in .setConvertFrame$i -side top -fill y -expand 1
   pack .setConvertS$j  .setConvertE$j -in .setConvertFrame$j -side top -fill y -expand 1
   pack .setConvertFrame$i .setConvertFrame$j -in .setConvertPair$i -side left -fill x -expand 1
   pack .setConvertPair$i -in .setConvertF -side top -fill x
}
#pack .setConvertDoneB -in .setConvertF -side top -fill x
#-----------------------------------------------------------------------------------

pack .setTileL -in .setTileF -side top -fill x
for {set i 0} {$i < [llength $setTileOptions]} {incr i 1} {
   pack [lindex $setTileOptions $i]  -in .setTileFrame$i -side left -fill x -expand 1
   for {set tile 0} {$tile < $numTiles} {incr tile 1} {
     pack [lindex $setTileEntries $i]$tile  -in .setTileFrame$i -side left -fill x -expand 1
   }
   pack .setTileFrame$i -in .setTileF -side top -fill x
}
pack .setTileDoneB -in .setTileFrame$i -side left -fill x -expand 1
#pack .setTileFrame$i -in .setTileF -side top -fill x 
#-----------------------------------------------------------------------------------

pack .setTileF -in .stateF0 -side top -fill x -pady 1m
pack .spTexF .setTimgF .setTotherF -in .stateF1 -side top -fill x -expand 1
pack .setConvertF -in .stateF2 -side top -fill x -pady 1m
#-----------------------------------------------------------------------------------

#pack .loadTexF .loadDetailF -in .actionsF0 -side left -fill y -padx 2m
pack .loadTexF -in .actionsF0 -side left -fill y -padx 2m
pack .loadBlockF -in .actionsF1 -side top -pady 2m
pack .loadTileF -in .actionsF2 -side top -pady 2m
pack .loadTlutF -in .actionsF3 -side top -pady 2m
#-----------------------------------------------------------------------------------

pack .actionsF0 .actionsF1 .actionsF2 .actionsF3 -in .actionsF -side left -fill y -padx 2m
pack .stateF0 .stateF1 .stateF2 -in .stateF3 -side left -fill y -padx 2m
pack .stateF3 .doneAllB -in .stateF -side top -fill x -pady 0.5m
#---------------------------------------------------------------------------------
pack .actionsF .stateF -in .textureF -side top -fill x -pady 0.5m
#---------------------------------------------------------------------------------
pack .textureF
#---------------------------------------------------------------------------------

#dlopen ../spintcl.so init callback_init
#../spintcl.so call SpinTclConnect [lindex $argv 0] [lindex $argv 1]
