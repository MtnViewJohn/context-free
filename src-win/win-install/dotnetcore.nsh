; A set of NSIS macros to check whether a dotnet core runtime is installed and, if not, offer to
; download and install it. Currently only supports dotnet 6.
;
; Inspired by & initially based on NsisDotNetChecker, which does the same thing for .NET framework
; https://github.com/alex-sitnikov/NsisDotNetChecker

!include "WordFunc.nsh"
!include "TextFunc.nsh"
!include "X64.nsh"

!ifndef DOTNETCORE_INCLUDED
!define DOTNETCORE_INCLUDED

; Check that a specific version of the dotnet core runtime is installed and, if not, attempts to
; install it
;
; \param Version The desired dotnet core runtime version as a 2 digit version. e.g. 3.1, 5.0, 6.0
!macro CheckDotNetCore Version

	; Save registers
	Push $R0
	Push $R1
	Push $R2

	; Push and pop parameters so we don't have conflicts if parameters are $R#
	Push ${Version}
	Pop $R0 ; Version

	!define ID ${__LINE__}

	; Check current installed version
	!insertmacro DotNetCoreGetInstalledVersion $R0 $R1

	; If $R1 is blank then there is no version installed, otherwise it is installed
	; todo in future we might want to support "must be at least 6.0.7", for now we only deal with "yes/no" for a major version (e.g. 6.0)
	StrCmp $R1 "" notinstalled_${ID}
	DetailPrint "dotnet version $R1 already installed"
	Goto end_${ID}

	notinstalled_${ID}:
	DetailPrint "dotnet $R0 is not installed"

	!insertmacro DotNetCoreGetLatestVersion $R0 $R1
	DetailPrint "Latest Version of $R0 is $R1"


	; Get number of input digits
	; ${WordFind} $R1 "." "#" $R2
	; DetailPrint "version parts count is $R2"

	; ${WordFind} $R1 "." "+1" $R2
	; DetailPrint "version part 1 is $R2"

	; ${WordFind} $R1 "." "+2" $R2
	; DetailPrint "version part 2 is $R2"

	; ${WordFind} $R1 "." "+3" $R2
	; DetailPrint "version part 3 is $R2"

	!insertmacro DotNetCoreInstallVersion $R1

	end_${ID}:
	!undef ID

	; Restore registers
	Pop $R2
	Pop $R1
	Pop $R0

!macroend



; Gets the latest version of the runtime for a specified dotnet version. This uses the same endpoint
; as the dotnet-install scripts to determine the latest full version of a dotnet version
;
; \param[in] Version The desired dotnet core runtime version as a 2 digit version. e.g. 3.1, 5.0, 6.0
; \param[out] Result The full version number of the latest version - e.g. 6.0.7
!macro DotNetCoreGetLatestVersion Version Result

	; Save registers
	Push $R0
	Push $R1
	Push $R2

	; Push and pop parameters so we don't have conflicts if parameters are $R#
	Push ${Version}
	Pop $R0 ; Version

	StrCpy $R1 https://dotnetcli.azureedge.net/dotnet/WindowsDesktop/$R0/latest.version
	DetailPrint "Querying latest version of dotnet $R0 from $R1"

	; Fetch latest version of the desired dotnet version
	; todo error handling in the PS script? so we can check for errors here
	StrCpy $R2 "Write-Host (Invoke-WebRequest -UseBasicParsing -URI $\"$R1$\").Content;"
	!insertmacro DotNetCorePSExec $R2 $R2
	; $R2 contains latest version, e.g. 6.0.7

	; todo error handling here

	; Push the result onto the stack
	${TrimNewLines} $R2 $R2
	Push $R2

	; Restore registers
	Exch
	Pop $R2
	Exch
	Pop $R1
	Exch
	Pop $R0

	; Set result
	Pop ${Result}

!macroend

!macro DotNetCoreGetInstalledVersion Version Result
	!define DNC_INS_ID ${__LINE__}

	; Save registers
	Push $R0
	Push $R1
	Push $R2

	; Push and pop parameters so we don't have conflicts if parameters are $R#
	Push ${Version}
	Pop $R0 ; Version

	DetailPrint "Checking installed version of dotnet $R0"

	StrCpy $R1 "dotnet --list-runtimes | % { if($$_ -match $\".*WindowsDesktop.*($R0.\d+).*$\") { $$matches[1] } } | Sort-Object {[int]($$_ -replace '\d.\d.(\d+)', '$$1')} -Descending | Select-Object -first 1"
	!insertmacro DotNetCorePSExec $R1 $R1
	; $R1 contains highest installed version, e.g. 6.0.7

	${TrimNewLines} $R1 $R1

	; If there is an installed version it should start with the same two "words" as the input version,
	; otherwise assume we got an error response

	; todo improve this simple test which checks there are at least 3 "words" separated by periods
	${WordFind} $R1 "." "E#" $R2
	IfErrors error_${DNC_INS_ID}
	; $R2 contains number of version parts in R1 (dot separated words = version parts)

	; If less than 3 parts, or more than 4 parts, error
	IntCmp $R2 3 0 error_${DNC_INS_ID}
	IntCmp $R2 4 0 0 error_${DNC_INS_ID}

	; todo more error handling here / validation

	; Seems to be OK, skip the "set to blank string" error handler
	Goto end_${DNC_INS_ID}

	error_${DNC_INS_ID}:
	StrCpy $R1 "" ; Set result to blank string if any error occurs (means not installed)

	end_${DNC_INS_ID}:
	!undef DNC_INS_ID

	; Push the result onto the stack
	Push $R1

	; Restore registers
	Exch
	Pop $R2
	Exch
	Pop $R1
	Exch
	Pop $R0

	; Set result
	Pop ${Result}

!macroend

!macro DotNetCoreInstallVersion Version

	; Save registers
	Push $R0
	Push $R1
	Push $R2
	Push $R3

	; Push and pop parameters so we don't have conflicts if parameters are $R#
	Push ${Version}
	Pop $R0 ; Version

	${If} ${IsNativeAMD64}
		StrCpy $R3 "x64"
	${ElseIf} ${IsNativeARM64}
		StrCpy $R3 "arm64"
	${ElseIf} ${IsNativeIA32}
		StrCpy $R3 "x86"
	${Else}
		StrCpy $R3 "unknown"
	${EndIf}

	; todo can download as a .zip, which is smaller, then we'd need to unzip it before running it...
	StrCpy $R1 https://dotnetcli.azureedge.net/dotnet/WindowsDesktop/$R0/windowsdesktop-runtime-$R0-win-$R3.exe

	; For dotnet versions less than 5 the WindowsDesktop runtime has a different path
	${WordFind} $R0 "." "+1" $R2
	IntCmp $R2 5 +2 0 +2
	StrCpy $R1 https://dotnetcli.azureedge.net/dotnet/Runtime/$R0/windowsdesktop-runtime-$R0-win-$R3.exe

	DetailPrint "Downloading dotnet $R0 from $R1"

	; Create destination file
	GetTempFileName $R2
	nsExec::Exec 'cmd.exe /c rename "$R2" "$R2.exe"'	; Not using Rename to avoid spam in details log
	Pop $R3 ; Pop exit code
	StrCpy $R2 "$R2.exe"
	
	; Fetch runtime installer
	; todo error handling in the PS script? so we can check for errors here
	StrCpy $R1 "Invoke-WebRequest -UseBasicParsing -URI $\"$R1$\" -OutFile $\"$R2$\""
	!insertmacro DotNetCorePSExec $R1 $R1
	; $R1 contains powershell script result

	${WordFind} $R1 "BlobNotFound" "E+1{" $R3
	ifErrors +3 0
	DetailPrint "Dotnet installer $R0 not found."
	Goto +10

	; todo error handling for PS result, verify download result

	
	IfFileExists $R2 +3, 0
	DetailPrint "Dotnet installer did not download."
	Goto +7

	DetailPrint "Download complete"

	DetailPrint "Installing dotnet $R0"
	ExecWait "$\"$R2$\" /install /quiet /norestart" $R1
	DetailPrint "Installer completed (Result: $R1)"

	nsExec::Exec 'cmd.exe /c del "$R2"'	; Not using Delete to avoid spam in details log
	Pop $R3 ; Pop exit code

	; Error checking? Verify install result?

	; Restore registers
	Pop $R3
	Pop $R2
	Pop $R1
	Pop $R0

!macroend

; below is adapted from https://nsis.sourceforge.io/PowerShell_support but avoids using the plugin
; directory in favour of a temp file and providing a return variable rather than returning on the
; stack. Methods renamed to avoid conflicting with use of the original macros

; DotNetCorePSExec
; Executes a powershell script
;
; \param[in] PSCommand The powershell command or script to execute
; \param[out] Result The output from the powershell script
!macro DotNetCorePSExec PSCommand Result

	Push ${PSCommand}
	Call DotNetCorePSExecFn
	Pop ${Result}

!macroend

; DotNetCorePSExecFile
; Executes a powershell file
;
; \param[in] FilePath The path to the powershell script file to execute
; \param[out] Result The output from the powershell script
!macro DotNetCorePSExecFile FilePath Result

	Push ${FilePath}
	Call DotNetCorePSExecFileFn
	Pop ${Result}

!macroend

Function DotNetCorePSExecFn

	; Read parameters and save registers
	Exch $R0	; Script
	Push $R1
	Push $R2

	; Write the command into a temp file
	; Note: Using GetTempFileName to get a temp file name, but since we need to have a .ps1 extension
	; on the end we rename it with an extra file extension
	GetTempFileName $R1
	nsExec::Exec 'cmd.exe /c rename "$R1" "$R1.ps1"'	; Not using Rename to avoid spam in details log
	Pop $R2 ; Pop exit code
	StrCpy $R1 "$R1.ps1"

	FileOpen $R2 $R1 w
	FileWrite $R2 $R0
	FileClose $R2

	; Execute the powershell script and delete the temp file
	Push $R1
	Call DotNetCorePSExecFileFn
	nsExec::Exec 'cmd.exe /c del "$R1"'	; Not using Delete to avoid spam in details log
	Pop $R0 ; Pop exit code

	; Restore registers
	Exch
	Pop $R2
	Exch
	Pop $R1
	Exch
	Pop $R0

	; Stack contains script output only, which we leave as the function result

FunctionEnd

Function DotNetCorePSExecFileFn

	; Read parameters and save registers
	Exch $R0	; FilePath
	Push $R1

	nsExec::ExecToStack 'powershell -inputformat none -ExecutionPolicy RemoteSigned -File "$R0"  '
	; Stack contain exitCode, scriptOutput, registers

	; Pop exit code & validate
	Pop $R1
	IntCmp $R1 0 +2
	SetErrorLevel 2

	; Restore registers
	Exch
	Pop $R1
	Exch
	Pop $R0

	; Stack contains script output only, which we leave as the function result

FunctionEnd

!endif