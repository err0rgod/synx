# dev.ps1 - Fast sync, build, and test on flexurl-dev without git push/pull
param(
    [Parameter(ValueFromRemainingArguments = $true)]
    [string[]]$SynxArgs
)

$argsStr = $SynxArgs -join " "

Write-Host "🚀 Syncing and building on flexurl-dev..." -ForegroundColor Cyan

cmd.exe /c "tar -cf - main.cpp Makefile ps.cpp CLI11.hpp | ssh flexurl-dev ""tar -xf - -C ~/synx && cd ~/synx && make"""

if ($LASTEXITCODE -eq 0) {
    Write-Host "✅ Running ./synx $argsStr" -ForegroundColor Green
    ssh -t flexurl-dev "cd ~/synx && ./synx $argsStr"
} else {
    Write-Host "❌ Compilation failed!" -ForegroundColor Red
}
