$cfdgs = Get-ChildItem -Path '.\input\tests\*.cfdg'
$cfdgs += Get-ChildItem -Path '.\input\*.cfdg'

if ( -Not (Test-Path "output"))
{
 New-Item -Path "output" -ItemType Directory
}

foreach ($cfdg in $cfdgs) {
  Write-Host -NoNewLine -foregroundcolor white $cfdg.Name
  .\Release64\ContextFreeCLI.exe /q /P $cfdg .\output\test.png

  if ($LastExitCode) {
    Write-Host -foregroundcolor red "   fail"
  } else {
    Write-Host -foregroundcolor green "   pass"
  }
}
