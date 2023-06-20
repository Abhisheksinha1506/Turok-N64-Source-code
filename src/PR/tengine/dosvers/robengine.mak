# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

!IF "$(CFG)" == ""
CFG=robengine - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to robengine - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "robengine - Win32 Release" && "$(CFG)" !=\
 "robengine - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "robengine.mak" CFG="robengine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "robengine - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "robengine - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project

!IF  "$(CFG)" == "robengine - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f robengine.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "robengine.exe"
# PROP BASE Bsc_Name "robengine.bsc"
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f robengine.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "robengine.exe"
# PROP Bsc_Name "robengine.bsc"
OUTDIR=.\Release
INTDIR=.\Release

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f robengine.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "robengine.exe"
# PROP BASE Bsc_Name "robengine.bsc"
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f robengine.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "robengine.exe"
# PROP Bsc_Name "robengine.bsc"
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ENDIF 

################################################################################
# Begin Target

# Name "robengine - Win32 Release"
# Name "robengine - Win32 Debug"

!IF  "$(CFG)" == "robengine - Win32 Release"

".\robengine.exe" : 
   CD M:\src\PR\tengine\dosvers
   NMAKE /f robengine.mak

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

".\robengine.exe" : 
   CD M:\src\PR\tengine\dosvers
   NMAKE /f robengine.mak

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\mattable.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ai.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ai.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\aidoor.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\aidoor.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\aistand.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\aistand.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\aistruc.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\aistruc.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\aiweap.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\aiweap.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\anim.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\anim.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\arrow.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\attract.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\attract.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\audheap.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\audio.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\audio.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\audiocfx.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\audiocfx.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\audiomgr.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\behavior.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\boot.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\boss.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\boss.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\bossflgs.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\camera.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\camera.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cammodes.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\campaign.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\campaign.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cart.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cart.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cartdir.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cfb.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cheats.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cheats.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cinecam.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cinecam.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\collinfo.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\collinfo.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\control.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\control.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cppu64.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\crdcam.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\crdcam.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\debug.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\defs.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\defs.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlists.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlists.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fifo.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\frontend.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\frontend.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fx.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fx.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\galrecam.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\galrecam.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\gdl.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\geometry.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\geometry.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\gfx16bit.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\gfx16bit.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\gfxyield.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\graphu64.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\graphu64.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\hash.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\hash.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\hedtrack.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\hedtrack.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\hsb.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\hsb.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\huffman.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\humvee.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\humvee.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\instcol.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\instcol.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\introcam.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\introcam.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lists.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lists.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\loadsave.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\loadsave.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\longhunt.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\longhunt.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mantis.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mantis.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\map.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\map.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\matdefs.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mattable.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\adpcm2.h

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tcontrol.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mempool.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\onscrn.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\options.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\particle.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pause.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\persist.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pickup.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\prfault.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\qsort.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\regicol.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\romstruc.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\scene.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\sched.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\simppool.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\stacks.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\sun.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\memory.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\zbuffer.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\textload.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tmove.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\train.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\trex.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\turret.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\unicol.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\unpack.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\volume.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\wallcoll.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\warp.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\wradcol.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tengine.cpp

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\spec

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\makefile

!IF  "$(CFG)" == "robengine - Win32 Release"

!ELSEIF  "$(CFG)" == "robengine - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
