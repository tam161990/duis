@echo off
echo ========================================
echo Switch to PHP 8.3.36
echo ========================================
echo.

REM Stop Apache if running
echo Stopping Apache...
net stop Apache2.4 2>nul
if %errorlevel% == 0 (
    echo Apache stopped successfully
) else (
    echo Apache was not running
)
echo.

REM Run PowerShell script
echo Configuring Apache for PHP 8.3...
powershell.exe -ExecutionPolicy Bypass -File "%~dp0configure-apache-php8.ps1"

if %errorlevel% == 0 (
    echo.
    echo ========================================
    echo SUCCESS! Apache configured for PHP 8.3
    echo ========================================
    echo.
    echo Starting Apache...
    net start Apache2.4
    echo.
    echo Done! Apache is now running with PHP 8.3.36
) else (
    echo.
    echo ========================================
    echo FAILED! Configuration was not applied
    echo ========================================
    echo.
    echo Apache remains with previous configuration
)

echo.
pause
