# Find and fix non-static methods called statically

$baseDir = "C:\xampp\WORKS\duis-dev\www"
$methods = @(
    @{Class='RequestHandler'; Method='run'},
    @{Class='RequestHandler'; Method='getMicroTime'},
    @{Class='dbProc'; Method='saveEvent'},
    @{Class='dbProc'; Method='isModuleExist'}
)

Write-Host "========================================" 
Write-Host "PHP 8 Static Methods Fixer"
Write-Host "========================================" 
Write-Host ""

foreach ($item in $methods) {
    $class = $item.Class
    $method = $item.Method
    
    Write-Host "Searching for: $class::$method()" -ForegroundColor Cyan
    
    # Find the file containing the class
    $pattern = "function\s+$method\s*\("
    $files = Get-ChildItem -Path $baseDir -Include *.php,*.inc,*.class -Recurse -File
    
    foreach ($file in $files) {
        $content = Get-Content $file.FullName -Raw -ErrorAction SilentlyContinue
        if (-not $content) { continue }
        
        if ($content -match $pattern -and $content -notmatch "static\s+function\s+$method") {
            # Add static keyword
            $newContent = $content -replace "(\s+)function\s+$method\s*\(", '$1static function ' + $method + '('
            
            if ($newContent -ne $content) {
                $newContent | Out-File $file.FullName -Encoding UTF8 -NoNewline
                Write-Host "  [+] Fixed in: $($file.Name)" -ForegroundColor Green
            }
        }
    }
}

Write-Host ""
Write-Host "========================================" 
Write-Host "Complete!"
Write-Host "========================================" 
