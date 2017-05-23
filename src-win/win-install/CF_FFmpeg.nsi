; Context Free FFmpeg
; ---------------------
; Copyright (C) 2017 John Horigan
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
!define VER_MINOR 24

SetCompressor bzip2
RequestExecutionLevel user

!define PRODUCT "ContextFree FFmpeg"
!define VERSION "${VER_MAJOR}.${VER_MINOR}"

!include "MUI.nsh"
!include WordFunc.nsh
!include "x64.nsh"
!include WinVer.nsh

;--------------------------------
;Variables

  
;--------------------------------
;Configuration

  !define MUI_ICON "FFmpeg.ico"
  !define MUI_UNICON "FFmpeg.ico"
  
  !define MUI_WELCOMEFINISHPAGE_BITMAP "sidebar.bmp"


  !define MUI_WELCOMEPAGE_TITLE "FFmpeg for Context Free"
    
  
  !define MUI_FINISHPAGE_NOAUTOCLOSE

ShowInstDetails show

  
;General
  OutFile "CF_FFmpegInstall.exe"
  
  ;License page
  LicenseData "COPYING.GPLv2.txt"

  Name "${PRODUCT}"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "COPYING.GPLv2.txt"


!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH


  ;Language
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Context Free FFmpeg (required)" 
SectionIn RO
  SetOutPath "$INSTDIR"
  ClearErrors
  
  File 'COPYING.GPLv2.txt'

  ${If} ${RunningX64}
    File "..\\..\\src-net\\Release64\\avcodec-57.dll" 
    File "..\\..\\src-net\\Release64\\avdevice-57.dll" 
    File "..\\..\\src-net\\Release64\\avfilter-6.dll" 
    File "..\\..\\src-net\\Release64\\avformat-57.dll"
    File "..\\..\\src-net\\Release64\\avutil-55.dll"
    File "..\\..\\src-net\\Release64\\ffplay.exe" 
    File "..\\..\\src-net\\Release64\\postproc-54.dll" 
    File "..\\..\\src-net\\Release64\\swresample-2.dll" 
    File "..\\..\\src-net\\Release64\\swscale-4.dll" 
  ${Else}
    File "..\\..\\src-net\\Release\\avcodec-57.dll" 
    File "..\\..\\src-net\\Release\\avdevice-57.dll" 
    File "..\\..\\src-net\\Release\\avfilter-6.dll" 
    File "..\\..\\src-net\\Release\\avformat-57.dll"
    File "..\\..\\src-net\\Release\\avutil-55.dll"
    File "..\\..\\src-net\\Release\\ffplay.exe" 
    File "..\\..\\src-net\\Release\\postproc-54.dll" 
    File "..\\..\\src-net\\Release\\swresample-2.dll" 
    File "..\\..\\src-net\\Release\\swscale-4.dll" 
  ${EndIf}

SectionEnd



Function .onInit
  ReadRegStr $INSTDIR HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\{DD0B06AD-5E55-41be-88E5-E9D13BAF06F4}" "InstallDir"
  
  ${If} $INSTDIR == ""
    MessageBox \
      MB_OK|MB_ICONSTOP "Cannot find installation location for Context Free."
    Abort
  ${EndIf}

FunctionEnd

;--------------------------------

;eof
