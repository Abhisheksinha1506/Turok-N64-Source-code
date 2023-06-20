####### ucode related parameters #######
set rspGeomZbuf 1
set rspGeomFog 0
set rspGeomShade 1
set rspGeomSmooth 1
set rspGeomCullFront 0
set rspGeomCullBack 1
set rspGeomTexture 1
set rspGeomLod 0
#need all these calls for proper recording
#even though one call will send all the
#geom modes down
CrspGeomZbuf
CrspGeomFog
CrspGeomShade
CrspGeomSmooth
CrspGeomCullFront
CrspGeomCullBack
CrspGeomTexture
CrspGeomLod
#-----------------------
.rsp.bottomS set 960
set rspScissBottom 960
set rspSCissBottom 240.0
CrspScissBottom 960

.rsp.topS set 0
set rspScissTop 0
set rspSCissTop 0
CrspScissTop 0

.rsp.leftS set 0
set rspScissLeft 0
set rspSCissLeft 0
CrspScissLeft 0

.rsp.rightS set 1280
set rspScissRight 1280
set rspSCissRight 1280.0
CrspScissRight 1280

#-------------------------
.rsp.projFovS set 30
.rsp.projAspectS set 1333
.rsp.projNearS set 50
.rsp.projFarS set 10000
set rspProjFar 10000
set rspProjNear 50
#.rsp.perspNormS set [expr 10*$rspProjNear]
CrspProjFov 30
CrspProjAspect 1333
CrspProjNear 50
CrspProjFar 5000
#CrspPerspNorm [expr 10*$rspProjNear]
#----------------------
set rspAmbR 128
set rspAmbG 128
set rspAmbB 128
set rspl1R 128
set rspl1G 0
set rspl1B 0

set rspl1X 1
set rspl1Y 1
set rspl1Z 1

set rspl2R 0
set rspl2G 0
set rspl2B 128

set rspl2X -1
set rspl2Y 1
set rspl2Z 1

set rspL1 0
CrspL1
set rspL2 0
CrspL2
set rspDiffuse 0
set rspSpecular 0
CrspDiffuse
CrspSpecular
#----------------------------
set rspTrackBallFly 1
set LrspTrackBallFly "trackball"
set buttons [expr $buttons | 1]
#-------------------------
set rspTrap 0
#CrspTrap
set rspTrapCount 1
set rspTrapType 0
CrspTrapType
#-------------------------
set rspModels 15
CrspModels
#---------------------
# shouldnt set this since recording 
# will be inhibited on hitting the init button
#set LrspRecord "record"
#set rspRecord 0
#set LrspPlay "play"
#set rspPlay 0
#------------------
# only needed for trapping frames
#sendState   

#---------------------
# This is set in fineGrain after the function is defined
set rspCycleType 0
CrspCycleType
#---------------------
set rspPipeLineMode 0
CrspPipeLineMode
