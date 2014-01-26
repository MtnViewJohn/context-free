$cfdgs = Get-ChildItem -Path '.\input\tests\*.cfdg'

foreach ($cfdg in $cfdgs) {
  Write-Host -NoNewLine -foregroundcolor white $cfdg.Name
  .\Release64\ContextFreeCLI.exe /q /P $cfdg .\output\test.png

  if ($LastExitCode) {
    Write-Host -foregroundcolor red "   fail"
  } else {
    Write-Host -foregroundcolor green "   pass"
  }
}
