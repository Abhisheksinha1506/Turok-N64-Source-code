  #--------------------------- spTex --------------------------------------------
set spTexOptions {.spTexScaleSL .spTexScaleTL .spTexPrimTileL .spTexMaxLevelL .spTexEnableCB .spTexDoneB}
set spTexEntries {.spTexScaleSE .spTexScaleTE .spTexPrimTileE .spTexMaxLevelE}

for {set i 0} {$i < [llength $spTexOptions]} {incr i 1} {
   frame .spTexFrame$i
}
label .state -text "state" -bg mintCream
label .spTexL  -text "spTex" -relief groove

checkbutton .spTexEnableCB -text "spTexEnable"  -variable spTexEnable
#set spTexEnable 1

label .spTexScaleSL  -width 10 -text "scaleS" -relief groove
entry .spTexScaleSE  -width 9 -relief sunken -textvariable spTexScaleS
#set spTexScaleS 0xffff

label .spTexScaleTL  -width 10 -text "scaleT" -relief groove
entry .spTexScaleTE  -width 9 -relief sunken -textvariable spTexScaleT
#set spTexScaleT 0xffff

label .spTexPrimTileL  -width 10 -text "PrimTile" -relief groove
entry .spTexPrimTileE  -width 9 -relief sunken -textvariable spTexPrimTile
#set spTexPrimTile 1

label .spTexMaxLevelL  -width 10 -text "MaxLevel" -relief groove
entry .spTexMaxLevelE  -width 9 -relief sunken -textvariable spTexMaxLevel
#set spTexMaxLevel 5
