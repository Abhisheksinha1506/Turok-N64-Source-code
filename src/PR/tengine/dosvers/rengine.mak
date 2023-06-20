# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

!IF "$(CFG)" == ""
CFG=rengine - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to rengine - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "rengine - Win32 Release" && "$(CFG)" !=\
 "rengine - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "rengine.mak" CFG="rengine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rengine - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "rengine - Win32 Debug" (based on "Win32 (x86) External Target")
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

!IF  "$(CFG)" == "rengine - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f rengine.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "rengine.exe"
# PROP BASE Bsc_Name "rengine.bsc"
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f rengine.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "rengine.exe"
# PROP Bsc_Name "rengine.bsc"
OUTDIR=.\Release
INTDIR=.\Release

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ELSEIF  "$(CFG)" == "rengine - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f rengine.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "rengine.exe"
# PROP BASE Bsc_Name "rengine.bsc"
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f rengine.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "rengine.exe"
# PROP Bsc_Name "rengine.bsc"
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

# Name "rengine - Win32 Release"
# Name "rengine - Win32 Debug"

!IF  "$(CFG)" == "rengine - Win32 Release"

".\rengine.exe" : 
   CD M:\src\PR\tengine\dosvers
   NMAKE /f rengine.mak

!ELSEIF  "$(CFG)" == "rengine - Win32 Debug"

".\rengine.exe" : 
   CD M:\src\PR\tengine\dosvers
   NMAKE /f rengine.mak

!ENDIF 

# End Target
# End Project
################################################################################
