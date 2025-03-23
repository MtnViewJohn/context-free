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
!include "FileFunc.nsh"

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

  ${If} ${IsNativeAMD64}
    File "..\\..\\Release\\x64\\ContextFreeCLI.exe"
    File "..\\..\\src-mfc\\x64\\Release\\ContextFree.exe" 
    File "..\\..\\src-mfc\\x64\\Release\\ffplay.exe"
    File "..\\..\\src-mfc\\x64\\Release\\avcodec-59.dll"
    File "..\\..\\src-mfc\\x64\\Release\\avformat-59.dll"
    File "..\\..\\src-mfc\\x64\\Release\\avutil-57.dll"
    File "..\\..\\src-mfc\\x64\\Release\\avfilter-8.dll"
    File "..\\..\\src-mfc\\x64\\Release\\avdevice-59.dll"
    File "..\\..\\src-mfc\\x64\\Release\\swresample-4.dll"
    File "..\\..\\src-mfc\\x64\\Release\\swscale-6.dll"
    File "..\\..\\src-mfc\\x64\\Release\\SDL2.dll"
    File "..\\..\\src-mfc\\x64\\Release\\postproc-56.dll"
    File "..\\..\\src-mfc\\x64\\Release\\libpng16.dll"
    File "..\\..\\src-mfc\\x64\\Release\\Lexilla.dll"
    File "..\\..\\src-mfc\\x64\\Release\\Scintilla.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Redist\MSVC\14.42.34433\x64\Microsoft.VC143.CRT\vcruntime140.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Redist\MSVC\14.42.34433\x64\Microsoft.VC143.CRT\vcruntime140_1.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Redist\MSVC\14.42.34433\x64\Microsoft.VC143.CRT\msvcp140.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Redist\MSVC\14.42.34433\x64\Microsoft.VC143.MFC\mfc140u.dll"
  ${ElseIf} ${IsNativeARM64}
    File "..\\..\\Release\\ARM64\\ContextFreeCLI.exe"
    File "..\\..\\src-mfc\\ARM64\\Release\\ContextFree.exe" 
    File "..\\..\\src-mfc\\ARM64\\Release\\ffplay.exe"
    File "..\\..\\src-mfc\\ARM64\\Release\\avcodec-59.dll"
    File "..\\..\\src-mfc\\ARM64\\Release\\avformat-59.dll"
    File "..\\..\\src-mfc\\ARM64\\Release\\avutil-57.dll"
    File "..\\..\\src-mfc\\ARM64\\Release\\avfilter-8.dll"
    File "..\\..\\src-mfc\\ARM64\\Release\\avdevice-59.dll"
    File "..\\..\\src-mfc\\ARM64\\Release\\swresample-4.dll"
    File "..\\..\\src-mfc\\ARM64\\Release\\swscale-6.dll"
    File "..\\..\\src-mfc\\ARM64\\Release\\SDL2.dll"
    File "..\\..\\src-mfc\\ARM64\\Release\\postproc-56.dll"
    File "..\\..\\src-mfc\\ARM64\\Release\\libpng16.dll"
    File "..\\..\\src-mfc\\ARM64\\Release\\Lexilla.dll"
    File "..\\..\\src-mfc\\ARM64\\Release\\Scintilla.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Redist\MSVC\14.42.34433\arm64\Microsoft.VC143.CRT\vcruntime140.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Redist\MSVC\14.42.34433\arm64\Microsoft.VC143.CRT\vcruntime140_1.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Redist\MSVC\14.42.34433\arm64\Microsoft.VC143.CRT\msvcp140.dll"
    File "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Redist\MSVC\14.42.34433\arm64\Microsoft.VC143.MFC\mfc140u.dll"
  ${Else}
    Abort "Unsupported CPU architecture!"
  ${EndIf}

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
    
    ;Create shortcut
    RMDir /r "$SMPROGRAMS\ContextFree"
    CreateShortCut "$SMPROGRAMS\Context Free.lnk" "$INSTDIR\ContextFree.exe"
  
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

  Delete "$SMPROGRAMS\Context Free.lnk"
  SetShellVarContext all
  Delete "$SMPROGRAMS\Context Free.lnk"
  

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
