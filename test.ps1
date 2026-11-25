$cfdgs = Get-ChildItem -Path '.\input\tests\*.cfdg'
$cfdgs += Get-ChildItem -Path '.\input\*.cfdg'

if ( -Not (Test-Path "output"))
{
 New-Item -Path "output" -ItemType Directory
}

foreach ($cfdg in $cfdgs) {
  Write-Host -NoNewLine -foregroundcolor white $cfdg.Name

  .\Release\ARM64\ContextFreeCLI.exe /q /P $cfdg .\output\test.png
  if ($LastExitCode) {
    Write-Host -foregroundcolor red "   fail: execution"
    exit 1
  }

  .\Release\ARM64\ContextFreeCLI.exe /q //jsonredacted $cfdg .\output\test.json
  if ($LastExitCode) {
    Write-Host -foregroundcolor red "   fail: json create"
    exit 2
  }

  $json = $cfdg -replace '\.cfdg$', '.json'
  fc.exe $json .\output\test.json | out-null
  if ($LastExitCode) {
    Write-Host -foregroundcolor red "   fail: json compare"
    exit 3
  }

  Write-Host -foregroundcolor green "   pass"
}

Write-Host -NoNewLine -foregroundcolor white "mtree.cfdg movie"
.\Release\ARM64\ContextFreeCLI.exe /a150 /s640x480 //quicktime /vffgh input\mtree.cfdg output\mtree.mov
if ($LastExitCode) {
  Write-Host -foregroundcolor red "   fail"
  exit 4
} else {
  Write-Host -foregroundcolor green "   pass"
}

