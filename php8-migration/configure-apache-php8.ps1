# ============================================
# Apache Configuration for PHP 8.3.36
# ============================================

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Apache Configuration for PHP 8.3.36" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

$apacheConfPath = "C:\xampp\apache\conf\httpd.conf"
$backupPath = "C:\xampp\apache\conf\httpd.conf.backup.php73." + (Get-Date -Format "yyyyMMdd_HHmmss")

# Check if httpd.conf exists
if (-not (Test-Path $apacheConfPath)) {
    Write-Host "ERROR: Apache config not found at: $apacheConfPath" -ForegroundColor Red
    exit 1
}

# Create backup
Write-Host "Creating backup..." -ForegroundColor Yellow
Copy-Item $apacheConfPath $backupPath
Write-Host "✓ Backup created: $backupPath" -ForegroundColor Green
Write-Host ""

# Read current configuration
$content = Get-Content $apacheConfPath -Encoding UTF8
$newContent = @()
$changes = 0

Write-Host "Updating configuration..." -ForegroundColor Yellow
Write-Host ""

foreach ($line in $content) {
    # Update LoadModule php7_module
    if ($line -match '^\s*LoadModule\s+php7_module\s+"([^"]+)"') {
        $oldModule = $matches[1]
        $newContent += 'LoadModule php_module "C:/php-8.3.36/php8apache2_4.dll"'
        Write-Host "✓ Updated LoadModule:" -ForegroundColor Green
        Write-Host "  OLD: $line" -ForegroundColor Gray
        Write-Host "  NEW: LoadModule php_module `"C:/php-8.3.36/php8apache2_4.dll`"" -ForegroundColor Green
        $changes++
    }
    # Update PHPIniDir for PHP 7.3
    elseif ($line -match '^\s*PHPIniDir\s+"?C:\\xampp\\php"?') {
        $newContent += 'PHPIniDir "C:/php-8.3.36"'
        Write-Host "✓ Updated PHPIniDir:" -ForegroundColor Green
        Write-Host "  OLD: $line" -ForegroundColor Gray
        Write-Host "  NEW: PHPIniDir `"C:/php-8.3.36`"" -ForegroundColor Green
        $changes++
    }
    # Keep all other lines
    else {
        $newContent += $line
    }
}

if ($changes -eq 0) {
    Write-Host ""
    Write-Host "WARNING: No PHP configuration found in httpd.conf" -ForegroundColor Yellow
    Write-Host "Please add manually:" -ForegroundColor Yellow
    Write-Host "  LoadModule php_module `"C:/php-8.3.36/php8apache2_4.dll`"" -ForegroundColor Cyan
    Write-Host "  PHPIniDir `"C:/php-8.3.36`"" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Backup restored." -ForegroundColor Yellow
    Copy-Item $backupPath $apacheConfPath -Force
    exit 1
}

# Write new configuration
$newContent | Out-File $apacheConfPath -Encoding UTF8
Write-Host ""
Write-Host "========================================" -ForegroundColor Green
Write-Host "Configuration updated successfully!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host ""
Write-Host "Changes made: $changes" -ForegroundColor Cyan
Write-Host "Backup: $backupPath" -ForegroundColor Cyan
Write-Host ""

# Test Apache configuration
Write-Host "Testing Apache configuration..." -ForegroundColor Yellow
$apacheExe = "C:\xampp\apache\bin\httpd.exe"

if (Test-Path $apacheExe) {
    $testResult = & $apacheExe -t 2>&1
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✓ Apache configuration is valid!" -ForegroundColor Green
    } else {
        Write-Host "✗ Apache configuration test failed:" -ForegroundColor Red
        Write-Host $testResult -ForegroundColor Red
        Write-Host ""
        Write-Host "Restoring backup..." -ForegroundColor Yellow
        Copy-Item $backupPath $apacheConfPath -Force
        Write-Host "✓ Backup restored" -ForegroundColor Green
        exit 1
    }
} else {
    Write-Host "⚠ Apache executable not found, skipping config test" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Next Steps:" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "1. Stop Apache if running" -ForegroundColor White
Write-Host "2. Start Apache with new configuration" -ForegroundColor White
Write-Host "3. Check Apache error log for issues" -ForegroundColor White
Write-Host "4. Test DUIS application" -ForegroundColor White
Write-Host ""
Write-Host "To rollback: Copy backup file back to httpd.conf" -ForegroundColor Yellow
Write-Host ""
