@echo off
echo ========================================
echo Rollback to PHP 7.3.8
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

REM Find latest backup
echo Looking for backup...
for /f "delims=" %%i in ('dir /b /o-d "C:\xampp\apache\conf\httpd.conf.backup.php73.*" 2^>nul') do (
    set "LATEST_BACKUP=%%i"
    goto :found
)

:found
if defined LATEST_BACKUP (
    echo Found backup: %LATEST_BACKUP%
    echo.
    echo Restoring configuration...
    copy /Y "C:\xampp\apache\conf\%LATEST_BACKUP%" "C:\xampp\apache\conf\httpd.conf"
    
    if %errorlevel% == 0 (
        echo.
        echo ========================================
        echo SUCCESS! Restored to PHP 7.3
        echo ========================================
        echo.
        echo Starting Apache...
        net start Apache2.4
        echo.
        echo Done! Apache is now running with PHP 7.3.8
    ) else (
        echo.
        echo ERROR: Failed to restore configuration
    )
) else (
    echo ERROR: No backup file found!
    echo Please manually edit C:\xampp\apache\conf\httpd.conf
    echo.
    echo Required lines:
    echo   LoadModule php7_module "C:/xampp/php/php7apache2_4.dll"
    echo   PHPIniDir "C:/xampp/php"
)

echo.
pause
