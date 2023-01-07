; Context Free
; ---------------------
; Copyright (C) 2005 John Horigan
;
; This program is free software; you can redistribute it and/or
; modify it under the terms of the GNU General Public License
; as published by the Free Software Foundation; either version 2
; of the License, or (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program; if not, write to the Free Software
; Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
; 
; John Horigan can be contacted at john@glyphic.com or at
; John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
;

!define VER_MAJOR 3
!define VER_MINOR 4

;SetCompressor bzip2
RequestExecutionLevel user

!define PRODUCT "Context Free"
!define VERSION "${VER_MAJOR}.${VER_MINOR}"

!include "MUI2.nsh"
!include WordFunc.nsh
!include "x64.nsh"
!include WinVer.nsh
!include "dotnetcore.nsh"
!include "FileFunc.nsh"

;--------------------------------
;Variables

  Var MUI_TEMP
  Var STARTMENU_FOLDER
  Var X86_OVERRIDE

;--------------------------------
;Configuration

  !define MUI_ICON "ContextFree.ico"
  !define MUI_UNICON "ContextFree.ico"
  
  !define MUI_WELCOMEFINISHPAGE_BITMAP "sidebar.bmp"
  !define MUI_UNWELCOMEFINISHPAGE_BITMAP "sidebar.bmp"


  !define MUI_WELCOMEPAGE_TITLE "Context Free"
    
  
  !define MUI_FINISHPAGE_NOAUTOCLOSE
  !define MUI_UNFINISHPAGE_NOAUTOCLOSE

ShowInstDetails show
ShowUninstDetails show

  
;General
  OutFile "ContextFreeInstall.exe"
  
  ;License page
  LicenseData "license.txt"

  Name "${PRODUCT}"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "license.txt"
!insertmacro MUI_PAGE_DIRECTORY

  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\OzoneSoft\ContextFree" 
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  
  !insertmacro MUI_PAGE_STARTMENU Application $STARTMENU_FOLDER

!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

  ;Language
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Context Free (required)" 
SectionIn RO
  SetOutPath "$INSTDIR"
  ClearErrors
  
  File 'license.txt'

  ${If} ${IsNativeIA32}
  ${OrIf} $X86_OVERRIDE = 1
    File "..\\..\\Release\\Win32\\ContextFreeCLI.exe"
    File /oname=ContextFree.exe "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x86\\CFForm.exe" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x86\\CFForm.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x86\\CppWrapper.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x86\\CFForm.dll.config" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x86\\FileDlgExtenders.dll.config" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x86\\CFForm.deps.json" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x86\\CFForm.runtimeconfig.json" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x86\\FileDlgExtenders.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x86\\OpenMRU.Core.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x86\\OpenMRU.WinForm.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x86\\WeifenLuo.WinFormsUI.Docking.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x86\\WeifenLuo.WinFormsUI.Docking.ThemeVS2015.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x86\\ScintillaNET.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-i686-libx264\\ffplay.exe"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-i686-libx264\\avcodec-59.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-i686-libx264\\avformat-59.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-i686-libx264\\avutil-57.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-i686-libx264\\avfilter-8.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-i686-libx264\\avdevice-59.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-i686-libx264\\swresample-4.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-i686-libx264\\swscale-6.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-i686-libx264\\SDL2.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-i686-libx264\\postproc-56.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Redist\MSVC\14.34.31931\x86\Microsoft.VC143.CRT\\vcruntime140.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Redist\MSVC\14.34.31931\x86\Microsoft.VC143.CRT\\concrt140.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Redist\MSVC\14.34.31931\x86\Microsoft.VC143.CRT\\msvcp140.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x86\\ucrtbase.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x86\\api-ms-win-crt-stdio-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x86\\api-ms-win-crt-heap-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x86\\api-ms-win-crt-string-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x86\\api-ms-win-crt-convert-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x86\\api-ms-win-crt-runtime-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x86\\api-ms-win-crt-locale-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x86\\api-ms-win-crt-math-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x86\\api-ms-win-crt-time-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x86\\api-ms-win-crt-filesystem-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x86\\api-ms-win-crt-environment-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x86\\api-ms-win-crt-private-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x86\\api-ms-win-crt-utility-l1-1-0.dll"
  ${ElseIf} ${IsNativeAMD64}
    File "..\\..\\Release\\x64\\ContextFreeCLI.exe"
    File /oname=ContextFree.exe "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x64\\CFForm.exe" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x64\\CFForm.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x64\\CppWrapper.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x64\\CFForm.dll.config" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x64\\FileDlgExtenders.dll.config" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x64\\CFForm.deps.json" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x64\\CFForm.runtimeconfig.json" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x64\\FileDlgExtenders.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x64\\OpenMRU.Core.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x64\\OpenMRU.WinForm.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x64\\WeifenLuo.WinFormsUI.Docking.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x64\\WeifenLuo.WinFormsUI.Docking.ThemeVS2015.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\x64\\ScintillaNET.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-x86_64-libx264\\ffplay.exe"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-x86_64-libx264\\avcodec-59.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-x86_64-libx264\\avformat-59.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-x86_64-libx264\\avutil-57.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-x86_64-libx264\\avfilter-8.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-x86_64-libx264\\avdevice-59.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-x86_64-libx264\\swresample-4.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-x86_64-libx264\\swscale-6.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-x86_64-libx264\\SDL2.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-x86_64-libx264\\postproc-56.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Redist\MSVC\14.34.31931\x64\Microsoft.VC143.CRT\\vcruntime140.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Redist\MSVC\14.34.31931\x64\Microsoft.VC143.CRT\\vcruntime140_1.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Redist\MSVC\14.34.31931\x64\Microsoft.VC143.CRT\\concrt140.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Redist\MSVC\14.34.31931\x64\Microsoft.VC143.CRT\\msvcp140.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x64\\ucrtbase.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x64\\api-ms-win-crt-stdio-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x64\\api-ms-win-crt-heap-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x64\\api-ms-win-crt-string-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x64\\api-ms-win-crt-convert-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x64\\api-ms-win-crt-runtime-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x64\\api-ms-win-crt-locale-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x64\\api-ms-win-crt-math-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x64\\api-ms-win-crt-time-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x64\\api-ms-win-crt-filesystem-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x64\\api-ms-win-crt-environment-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x64\\api-ms-win-crt-private-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\x64\\api-ms-win-crt-utility-l1-1-0.dll"
  ${ElseIf} ${IsNativeARM64}
    File "..\\..\\Release\\ARM64\\ContextFreeCLI.exe"
    File /oname=ContextFree.exe "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\arm64\\CFForm.exe" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\arm64\\CFForm.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\arm64\\CppWrapper.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\arm64\\CFForm.dll.config" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\arm64\\FileDlgExtenders.dll.config" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\arm64\\CFForm.deps.json" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\arm64\\CFForm.runtimeconfig.json" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\arm64\\FileDlgExtenders.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\arm64\\OpenMRU.Core.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\arm64\\OpenMRU.WinForm.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\arm64\\WeifenLuo.WinFormsUI.Docking.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\arm64\\WeifenLuo.WinFormsUI.Docking.ThemeVS2015.dll" 
    File "..\\..\\src-cs\\CFForm\\bin\\Release\\net6.0-windows\\publish\\arm64\\ScintillaNET.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-aarch64-libx264\\ffplay.exe"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-aarch64-libx264\\avcodec-59.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-aarch64-libx264\\avformat-59.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-aarch64-libx264\\avutil-57.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-aarch64-libx264\\avfilter-8.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-aarch64-libx264\\avdevice-59.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-aarch64-libx264\\swresample-4.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-aarch64-libx264\\swscale-6.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-aarch64-libx264\\SDL2.dll"
    File "..\\..\\src-ffmpeg\\lib\\ffmpeg-aarch64-libx264\\postproc-56.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Redist\MSVC\14.34.31931\arm64\Microsoft.VC143.CRT\\vcruntime140.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Redist\MSVC\14.34.31931\arm64\Microsoft.VC143.CRT\\concrt140.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Redist\MSVC\14.34.31931\arm64\Microsoft.VC143.CRT\\msvcp140.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\arm\\ucrtbase.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\arm\\api-ms-win-crt-stdio-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\arm\\api-ms-win-crt-heap-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\arm\\api-ms-win-crt-string-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\arm\\api-ms-win-crt-convert-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\arm\\api-ms-win-crt-runtime-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\arm\\api-ms-win-crt-locale-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\arm\\api-ms-win-crt-math-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\arm\\api-ms-win-crt-time-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\arm\\api-ms-win-crt-filesystem-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\arm\\api-ms-win-crt-environment-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\arm\\api-ms-win-crt-private-l1-1-0.dll"
    File "C:\Program Files (x86)\Windows Kits\10\Redist\10.0.22621.0\ucrt\DLLs\arm\\api-ms-win-crt-utility-l1-1-0.dll"
  ${Else}
  ${EndIf}

  !insertmacro CheckDotNetCore 6.0

SectionEnd


Section -post

  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\{DD0B06AD-5E55-41be-88E5-E9D13BAF06F4}" \
                   "DisplayName" "Context Free"
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\{DD0B06AD-5E55-41be-88E5-E9D13BAF06F4}" \
                   "UninstallString" '"$INSTDIR\uninst-contextfree.exe"'
  WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\{DD0B06AD-5E55-41be-88E5-E9D13BAF06F4}" \
                   "NoModify" 1
  WriteRegDWORD HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\{DD0B06AD-5E55-41be-88E5-E9D13BAF06F4}" \
                   "NoRepair" 1
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\{DD0B06AD-5E55-41be-88E5-E9D13BAF06F4}" \
                   "InstallDir" '$INSTDIR'

  SetOutPath $INSTDIR



  ; since the installer is now created last (in 1.2+), this makes sure 
  ; that any old installer that is readonly is overwritten.
  Delete $INSTDIR\uninst-contextfree.exe 
  WriteUninstaller $INSTDIR\uninst-contextfree.exe

  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    
    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
    CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Context Free.lnk" "$INSTDIR\ContextFree.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_END

SectionEnd

Function .onInstSuccess
  Exec '"$INSTDIR\ContextFree.exe"'
FunctionEnd

Function .onInit
  ;Folder-selection page
  ${If} ${AtLeastWin2000}
    StrCpy $INSTDIR "$LOCALAPPDATA\OzoneSoft\${PRODUCT}"
  ${Else}
    StrCpy $INSTDIR "$PROGRAMFILES\OzoneSoft\${PRODUCT}"
  ${EndIf}

  ${GetParameters} $R0
  ${GetOptions} $R0 "/x86"  $R1
  IfErrors +3 0
  IntOp $X86_OVERRIDE 0 + 1
  Goto +2
  IntOp $X86_OVERRIDE 0 + 0

  SetOutPath $TEMP
  File /oname=spltmp.bmp "splash.bmp"

  splash::show 4000 $TEMP\spltmp
  
  Pop $0 ; $0 has '1' if the user closed the splash screen early,
         ; '0' if everything closed normal, and '-1' if some error occured.

  Delete $TEMP\spltmp.bmp
FunctionEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"
  Delete '$INSTDIR\ContextFree.exe'
  Delete '$INSTDIR\ContextFreeCLI.exe'
  Delete '$INSTDIR\ffplay.exe'
  Delete '$INSTDIR\*.dll'
  Delete '$INSTDIR\*.config'
  Delete '$INSTDIR\*.json'
  Delete '$INSTDIR\license.txt'
  Delete '$INSTDIR\COPYING.GPLv2.txt'
  Delete '$INSTDIR\uninst-contextfree.exe' 
  RMDir  '$INSTDIR'

  !insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP

  RMDir /r "$SMPROGRAMS\$MUI_TEMP"
  SetShellVarContext all
  RMDir /r "$SMPROGRAMS\$MUI_TEMP"
  

  SetRegView 32
  DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\{DD0B06AD-5E55-41be-88E5-E9D13BAF06F4}"
  DeleteRegKey HKCU "Software\OzoneSoft\ContextFree" 
  DeleteRegKey HKCU "Software\Classes\.cfdg"
  DeleteRegKey HKCU "Software\Classes\ContextFree.Document"
  SetRegView 64
  DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\{DD0B06AD-5E55-41be-88E5-E9D13BAF06F4}"
  DeleteRegKey HKCU "Software\OzoneSoft\ContextFree" 
  DeleteRegKey HKCU "Software\Classes\.cfdg"
  DeleteRegKey HKCU "Software\Classes\ContextFree.Document"


SectionEnd

;eof
