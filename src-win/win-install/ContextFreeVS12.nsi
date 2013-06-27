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
!define VER_MINOR 0

SetCompressor lzma
RequestExecutionLevel user

!define PRODUCT "ContextFree"
!define VERSION "${VER_MAJOR}.${VER_MINOR}"

!include "MUI.nsh"
!include WordFunc.nsh
!include "x64.nsh"
!include WinVer.nsh

;--------------------------------
;Variables

  Var MUI_TEMP
  Var STARTMENU_FOLDER
  
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

  ${If} ${RunningX64}
    File "..\\..\\src-net\\Release64\\ContextFree.exe" 
    File "..\\..\\Release64\\ContextFreeCLI.exe" 
    File "..\\..\\src-net\\Release64\\CFControlsVS11.dll" 
    File "..\\..\\src-net\\Release64\\Controls.dll" 
    File "..\\..\\src-net\\Release64\\FileDlgExtenders.dll" 
    File "..\\..\\src-net\\Release64\\WeifenLuo.WinFormsUI.Docking.dll" 
    File "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\x64\Microsoft.VC120.CRT\msvcr120.dll"
    File "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\x64\Microsoft.VC120.CRT\msvcp120.dll"
  ${Else}
    File "..\\..\\src-net\\release\\ContextFree.exe" 
    File "..\\..\\Release\\ContextFreeCLI.exe" 
    File "..\\..\\src-net\\release\\CFControlsVS11.dll" 
    File "..\\..\\src-net\\release\\Controls.dll" 
    File "..\\..\\src-net\\release\\FileDlgExtenders.dll" 
    File "..\\..\\src-net\\release\\WeifenLuo.WinFormsUI.Docking.dll" 
    File "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\x86\Microsoft.VC120.CRT\msvcr120.dll"
    File "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\x86\Microsoft.VC120.CRT\msvcp120.dll"
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
  
  ReadRegStr $0 HKLM "SOFTWARE\Microsoft\NET Framework Setup\NDP\v4\Client" "Version"
  ${If} $0 == ""
    MessageBox \
      MB_YESNO|MB_ICONSTOP \
      ".Net framework v4.0 is required. Install Context Free anyway?" \
      IDYES okgo
    Abort
  ${EndIf}

okgo:
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
  Delete '$INSTDIR\CFControls.dll' 
  Delete '$INSTDIR\Controls.dll'
  Delete '$INSTDIR\FileDlgExtenders.dll'
  Delete '$INSTDIR\WeifenLuo.WinFormsUI.Docking.dll'
  Delete '$INSTDIR\msvcr100.dll'
  Delete '$INSTDIR\msvcp100.dll'
  Delete '$INSTDIR\license.txt'
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
