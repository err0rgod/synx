
$argsStr = $args -join " "

Write-Host "🚀 Syncing and building on flexurl-dev..." -ForegroundColor Cyan

# Package all .cpp, .hpp, and Makefile automatically
cmd.exe /c "tar -cf - *.cpp *.hpp Makefile | ssh flexurl-dev ""tar -xf - -C ~/synx && cd ~/synx && make"""

if ($LASTEXITCODE -eq 0) {
    Write-Host "✅ Running ./synx $argsStr" -ForegroundColor Green
    ssh -t flexurl-dev "cd ~/synx && ./synx $argsStr"
} else {
    Write-Host "❌ Compilation failed!" -ForegroundColor Red
}