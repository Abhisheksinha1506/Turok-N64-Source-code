### loadBlock  #######
#puts "onee"
set loadBlockTile 0
set loadBlockTl 0
set loadBlockSh 0
set loadBlockDxt 0
#CloadBlock

#puts "twoo"
### loadTex  #######
set loadTexFile 0
CloadTexFile
#puts "threee"
#CloadTex

### loadTile ######
# set to 1 since loadTile requires line Size to
# be set unlike loadBlock where lineSize = 0
set loadTileTile 1
set loadTileSl 0
set loadTileTl 0
set loadTileSh 0
set loadTileTh 0
#CloadTile

#### loadTlut.tcl #####

set loadTlutOffset 1
set loadTlutCount 1
set loadTlutAddr 256
#CloadTlut

#### set Conv ###########
    set setConvertK0 128
   .setConvertS0 set 128
CsetConvertK0 128
    set setConvertK1 128
   .setConvertS1 set 128
CsetConvertK1 128
    set setConvertK2 128
   .setConvertS2 set 128
CsetConvertK2 128
    set setConvertK3 128
   .setConvertS3 set 128
CsetConvertK3 128
    set setConvertK4 128
   .setConvertS4 set 128
CsetConvertK4 128
    set setConvertK5 128
   .setConvertS5 set 128
CsetConvertK5 128

#puts "fourr"
#### set Other ########
set setTotherDetail 0
CsetTotherDetail
set setTotherTlut 0
CsetTotherTlut
set setTotherTexFilt 2
CsetTotherTexFilt
set setTotherConvert 6
CsetTotherConvert
set setTotherLOD 0
set setTotherPersp 1
CsetTexStateAll

####### sp Tex ######
set spTexEnable 1
set spTexScaleS 0xffff
set spTexScaleT 0xffff
set spTexPrimTile 1
set spTexMaxLevel 5

###### tex state all ####
CsetTexStateAll
#puts "fivee"
