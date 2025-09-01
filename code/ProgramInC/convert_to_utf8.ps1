# Convert all C files from GB2312 to UTF-8 encoding
# Usage: .\convert_to_utf8.ps1

$ErrorActionPreference = "Continue"

$currentDir = Get-Location
Write-Host "Starting conversion in directory: $currentDir" -ForegroundColor Green

$cFiles = Get-ChildItem -Path $currentDir -Recurse -Include "*.c", "*.h" | Where-Object { !$_.PSIsContainer }

Write-Host "Found $($cFiles.Count) C/header files" -ForegroundColor Yellow

$convertedCount = 0
$skippedCount = 0
$errorCount = 0

foreach ($file in $cFiles) {
    Write-Host "Processing file: $($file.FullName)" -ForegroundColor Cyan
    
    try {
        $bytes = [System.IO.File]::ReadAllBytes($file.FullName)
        
        $gb2312 = [System.Text.Encoding]::GetEncoding("GB2312")
        $gb2312Content = $gb2312.GetString($bytes)
        
        $utf8 = [System.Text.Encoding]::UTF8
        $utf8Content = $utf8.GetString($bytes)
        
        $hasChinese = $gb2312Content -match '[\u4e00-\u9fff]'
        
        if (-not $hasChinese) {
            Write-Host "  No Chinese characters found, skipping" -ForegroundColor Gray
            $skippedCount++
            continue
        }
        
        if ($utf8Content -notmatch '\uFFFD') {
            Write-Host "  File may already be UTF-8, skipping" -ForegroundColor Gray
            $skippedCount++
            continue
        }
        
        $backupPath = $file.FullName + ".gb2312.bak"
        Copy-Item -Path $file.FullName -Destination $backupPath -Force
        Write-Host "  Backup created: $backupPath" -ForegroundColor Green
        
        $utf8NoBom = New-Object System.Text.UTF8Encoding $false
        [System.IO.File]::WriteAllText($file.FullName, $gb2312Content, $utf8NoBom)
        
        Write-Host "  Conversion completed: GB2312 -> UTF-8" -ForegroundColor Green
        $convertedCount++
    }
    catch {
        Write-Host "  Conversion failed: $($_.Exception.Message)" -ForegroundColor Red
        $errorCount++
    }
}

Write-Host "`nConversion completed!" -ForegroundColor Green
Write-Host "Statistics:" -ForegroundColor Yellow
Write-Host "  Successfully converted: $convertedCount files" -ForegroundColor Green
Write-Host "  Skipped files: $skippedCount files" -ForegroundColor Gray
Write-Host "  Error files: $errorCount files" -ForegroundColor Red
Write-Host "  Total files: $($cFiles.Count) files" -ForegroundColor Yellow

if ($convertedCount -gt 0) {
    Write-Host "`nNote: Backup files with .gb2312.bak extension have been created" -ForegroundColor Cyan
    Write-Host "You can delete these backup files if conversion is successful" -ForegroundColor Cyan
}

Write-Host "`nPress Enter to exit..." -ForegroundColor Yellow
$null = Read-Host