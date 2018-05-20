# Microsoft Developer Studio Project File - Name="VirtuaNES" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VirtuaNES - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VirtuaNES.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VirtuaNES.mak" CFG="VirtuaNES - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VirtuaNES - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /I "Zlib" /I "." /I "NES" /I "NES\Mapper" /I "NES\ApuEx" /I "NES\ApuEx\emu2413" /I "NES\PadEx" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# SUBTRACT CPP /O<none>
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib comctl32.lib imm32.lib dinput.lib shlwapi.lib /nologo /subsystem:windows /machine:I386 /out:"Release\◊Ó÷’ª√œÎ3.exe"
# SUBTRACT LINK32 /map /nodefaultlib
# Begin Target

# Name "VirtuaNES - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\App.cpp
# End Source File
# Begin Source File

SOURCE=.\CheatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Com.cpp
# End Source File
# Begin Source File

SOURCE=.\Config.cpp
# End Source File
# Begin Source File

SOURCE=.\ControllerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Crclib.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectInput.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectSound.cpp
# End Source File
# Begin Source File

SOURCE=.\EmulatorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EmuThread.cpp
# End Source File
# Begin Source File

SOURCE=.\GameOptionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphicsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MMTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\MovieDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MovieInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NetPlay.cpp
# End Source File
# Begin Source File

SOURCE=.\NetPlayDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Pathlib.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\ShortcutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VirtuaNES.rc
# End Source File
# Begin Source File

SOURCE=.\WinMain.cpp
# End Source File
# Begin Source File

SOURCE=.\Wnd.cpp
# End Source File
# Begin Source File

SOURCE=.\WndHook.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\App.h
# End Source File
# Begin Source File

SOURCE=.\CheatDlg.h
# End Source File
# Begin Source File

SOURCE=.\Com.h
# End Source File
# Begin Source File

SOURCE=.\Config.h
# End Source File
# Begin Source File

SOURCE=.\ControllerDlg.h
# End Source File
# Begin Source File

SOURCE=.\Crclib.h
# End Source File
# Begin Source File

SOURCE=.\DirectDraw.h
# End Source File
# Begin Source File

SOURCE=.\DirectInput.h
# End Source File
# Begin Source File

SOURCE=.\DirectSound.h
# End Source File
# Begin Source File

SOURCE=.\EmulatorDlg.h
# End Source File
# Begin Source File

SOURCE=.\EmuThread.h
# End Source File
# Begin Source File

SOURCE=.\GameOptionDlg.h
# End Source File
# Begin Source File

SOURCE=.\GraphicsDlg.h
# End Source File
# Begin Source File

SOURCE=.\lzAscii.h
# End Source File
# Begin Source File

SOURCE=.\lzSight.h
# End Source File
# Begin Source File

SOURCE=.\lzTVlayer.h
# End Source File
# Begin Source File

SOURCE=.\Macro.h
# End Source File
# Begin Source File

SOURCE=.\MainFrame.h
# End Source File
# Begin Source File

SOURCE=.\MMTimer.h
# End Source File
# Begin Source File

SOURCE=.\MovieDlg.h
# End Source File
# Begin Source File

SOURCE=.\MovieInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\NetPlay.h
# End Source File
# Begin Source File

SOURCE=.\NetPlayDlg.h
# End Source File
# Begin Source File

SOURCE=.\Pathlib.h
# End Source File
# Begin Source File

SOURCE=.\Registry.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ShortcutDlg.h
# End Source File
# Begin Source File

SOURCE=.\SoundDlg.h
# End Source File
# Begin Source File

SOURCE=.\Typedef.h
# End Source File
# Begin Source File

SOURCE=.\VirtuaNESres.h
# End Source File
# Begin Source File

SOURCE=.\Wnd.h
# End Source File
# Begin Source File

SOURCE=.\WndHook.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\CheatImageList.bmp
# End Source File
# Begin Source File

SOURCE=.\harrow.cur
# End Source File
# Begin Source File

SOURCE=.\KF.ico
# End Source File
# Begin Source File

SOURCE=.\PP.ico
# End Source File
# Begin Source File

SOURCE=.\VirtuaNES.ico
# End Source File
# Begin Source File

SOURCE=.\Wolf.ico
# End Source File
# End Group
# Begin Group "NES"

# PROP Default_Filter ""
# Begin Group "Mapper"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NES\Mapper\Mapper.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\Mapper\Mapper.h
# End Source File
# Begin Source File

SOURCE=.\NES\Mapper\MapperNSF.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\Mapper\MapperNSF.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "ApuEx"

# PROP Default_Filter ""
# Begin Group "emu2413"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NES\ApuEX\2413tone.h
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\emu2413\2413tone.h
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\emu2413.c
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\emu2413.h
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\emu2413\vrc7tone.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\NES\ApuEX\APU_FDS.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\APU_FDS.h
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\APU_FME7.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\APU_FME7.h
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\APU_INTERFACE.h
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\APU_INTERNAL.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\APU_INTERNAL.h
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\APU_MMC5.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\APU_MMC5.h
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\APU_N106.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\APU_N106.h
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\APU_VRC6.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\APU_VRC6.h
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\APU_VRC7.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\APU_VRC7.h
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\FDSplugin.h
# End Source File
# Begin Source File

SOURCE=.\NES\ApuEX\vrc7tone.h
# End Source File
# End Group
# Begin Group "PadEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD_CrazyClimber.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD_CrazyClimber.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD_HyperShot.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD_HyperShot.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD_Keyboard.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD_Keyboard.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD_Paddle.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD_Paddle.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD_SpaceShadowGun.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD_SpaceShadowGun.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD_Toprider.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD_Toprider.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD_Zapper.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NES\PadEX\EXPAD_Zapper.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=.\NES\APU.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\APU.h
# End Source File
# Begin Source File

SOURCE=.\NES\Cheat.h
# End Source File
# Begin Source File

SOURCE=.\NES\Cpu.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\CPU.h
# End Source File
# Begin Source File

SOURCE=.\NES\MMU.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\MMU.h
# End Source File
# Begin Source File

SOURCE=.\NES\Nes.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\Nes.h
# End Source File
# Begin Source File

SOURCE=.\NES\PAD.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\PAD.h
# End Source File
# Begin Source File

SOURCE=.\NES\PPU.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\PPU.h
# End Source File
# Begin Source File

SOURCE=.\NES\ROM.cpp
# End Source File
# Begin Source File

SOURCE=.\NES\ROM.h
# End Source File
# Begin Source File

SOURCE=.\NES\State.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CHN.NES
# End Source File
# Begin Source File

SOURCE=.\CHN.ZHI
# End Source File
# Begin Source File

SOURCE=.\FF3.zhi
# End Source File
# Begin Source File

SOURCE=.\Ff3chn.nes
# End Source File
# End Target
# End Project
