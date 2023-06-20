# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=SndComp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to SndComp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SndComp - Win32 Release" && "$(CFG)" !=\
 "SndComp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "SndComp.mak" CFG="SndComp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SndComp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SndComp - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "SndComp - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "SndComp - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\SndComp.exe" "$(OUTDIR)\SndComp.bsc"

CLEAN : 
	-@erase "$(INTDIR)\makeinst.obj"
	-@erase "$(INTDIR)\makeinst.sbr"
	-@erase "$(INTDIR)\SndComp.obj"
	-@erase "$(INTDIR)\SndComp.pch"
	-@erase "$(INTDIR)\SndComp.res"
	-@erase "$(INTDIR)\SndComp.sbr"
	-@erase "$(INTDIR)\SndCompDlg.obj"
	-@erase "$(INTDIR)\SndCompDlg.sbr"
	-@erase "$(INTDIR)\statusdlg.obj"
	-@erase "$(INTDIR)\statusdlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(OUTDIR)\SndComp.bsc"
	-@erase "$(OUTDIR)\SndComp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/SndComp.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SndComp.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SndComp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\makeinst.sbr" \
	"$(INTDIR)\SndComp.sbr" \
	"$(INTDIR)\SndCompDlg.sbr" \
	"$(INTDIR)\statusdlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\SndComp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/SndComp.pdb" /machine:I386 /out:"$(OUTDIR)/SndComp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\makeinst.obj" \
	"$(INTDIR)\SndComp.obj" \
	"$(INTDIR)\SndComp.res" \
	"$(INTDIR)\SndCompDlg.obj" \
	"$(INTDIR)\statusdlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SndComp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SndComp - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\SndComp.exe" "$(OUTDIR)\SndComp.bsc"

CLEAN : 
	-@erase "$(INTDIR)\makeinst.obj"
	-@erase "$(INTDIR)\makeinst.sbr"
	-@erase "$(INTDIR)\SndComp.obj"
	-@erase "$(INTDIR)\SndComp.pch"
	-@erase "$(INTDIR)\SndComp.res"
	-@erase "$(INTDIR)\SndComp.sbr"
	-@erase "$(INTDIR)\SndCompDlg.obj"
	-@erase "$(INTDIR)\SndCompDlg.sbr"
	-@erase "$(INTDIR)\statusdlg.obj"
	-@erase "$(INTDIR)\statusdlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\SndComp.bsc"
	-@erase "$(OUTDIR)\SndComp.exe"
	-@erase "$(OUTDIR)\SndComp.ilk"
	-@erase "$(OUTDIR)\SndComp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/SndComp.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SndComp.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SndComp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\makeinst.sbr" \
	"$(INTDIR)\SndComp.sbr" \
	"$(INTDIR)\SndCompDlg.sbr" \
	"$(INTDIR)\statusdlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\SndComp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/SndComp.pdb" /debug /machine:I386 /out:"$(OUTDIR)/SndComp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\makeinst.obj" \
	"$(INTDIR)\SndComp.obj" \
	"$(INTDIR)\SndComp.res" \
	"$(INTDIR)\SndCompDlg.obj" \
	"$(INTDIR)\statusdlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\SndComp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "SndComp - Win32 Release"
# Name "SndComp - Win32 Debug"

!IF  "$(CFG)" == "SndComp - Win32 Release"

!ELSEIF  "$(CFG)" == "SndComp - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\SndComp.cpp
DEP_CPP_SNDCO=\
	".\SndComp.h"\
	".\SndCompDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SndComp.obj" : $(SOURCE) $(DEP_CPP_SNDCO) "$(INTDIR)"\
 "$(INTDIR)\SndComp.pch"

"$(INTDIR)\SndComp.sbr" : $(SOURCE) $(DEP_CPP_SNDCO) "$(INTDIR)"\
 "$(INTDIR)\SndComp.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SndCompDlg.cpp

!IF  "$(CFG)" == "SndComp - Win32 Release"

DEP_CPP_SNDCOM=\
	".\defines.h"\
	".\makeinst.h"\
	".\SndComp.h"\
	".\SndCompDlg.h"\
	".\statusdlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SndCompDlg.obj" : $(SOURCE) $(DEP_CPP_SNDCOM) "$(INTDIR)"\
 "$(INTDIR)\SndComp.pch"

"$(INTDIR)\SndCompDlg.sbr" : $(SOURCE) $(DEP_CPP_SNDCOM) "$(INTDIR)"\
 "$(INTDIR)\SndComp.pch"


!ELSEIF  "$(CFG)" == "SndComp - Win32 Debug"

DEP_CPP_SNDCOM=\
	".\defines.h"\
	".\makeinst.h"\
	".\SndComp.h"\
	".\SndCompDlg.h"\
	".\statusdlg.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SNDCOM=\
	".\sgiName"\
	

"$(INTDIR)\SndCompDlg.obj" : $(SOURCE) $(DEP_CPP_SNDCOM) "$(INTDIR)"\
 "$(INTDIR)\SndComp.pch"

"$(INTDIR)\SndCompDlg.sbr" : $(SOURCE) $(DEP_CPP_SNDCOM) "$(INTDIR)"\
 "$(INTDIR)\SndComp.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "SndComp - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/SndComp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SndComp.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "SndComp - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/SndComp.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\SndComp.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SndComp.rc
DEP_RSC_SNDCOMP=\
	".\res\SndComp.ico"\
	".\res\SndComp.rc2"\
	

"$(INTDIR)\SndComp.res" : $(SOURCE) $(DEP_RSC_SNDCOMP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\makeinst.cpp
DEP_CPP_MAKEI=\
	".\Sfhdr.h"\
	".\SndComp.h"\
	".\SndCompDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\makeinst.obj" : $(SOURCE) $(DEP_CPP_MAKEI) "$(INTDIR)"\
 "$(INTDIR)\SndComp.pch"

"$(INTDIR)\makeinst.sbr" : $(SOURCE) $(DEP_CPP_MAKEI) "$(INTDIR)"\
 "$(INTDIR)\SndComp.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sfhdr.h

!IF  "$(CFG)" == "SndComp - Win32 Release"

!ELSEIF  "$(CFG)" == "SndComp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\statusdlg.cpp
DEP_CPP_STATU=\
	".\defines.h"\
	".\SndComp.h"\
	".\statusdlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\statusdlg.obj" : $(SOURCE) $(DEP_CPP_STATU) "$(INTDIR)"\
 "$(INTDIR)\SndComp.pch"

"$(INTDIR)\statusdlg.sbr" : $(SOURCE) $(DEP_CPP_STATU) "$(INTDIR)"\
 "$(INTDIR)\SndComp.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\defines.h

!IF  "$(CFG)" == "SndComp - Win32 Release"

!ELSEIF  "$(CFG)" == "SndComp - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
