# Mass Fix: Replace curly braces with square brackets in PHP files
# Fixes PHP 8 compatibility issue with array/string offset access

$baseDir = "C:\xampp\WORKS\duis-dev\www"
$excludeDirs = @('.git', 'cache', 'temp', 'tmp', 'vendor', 'node_modules')
$filesFixed = 0
$totalReplacements = 0

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "PHP 8 Curly Braces Fixer" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Scanning directory: $baseDir" -ForegroundColor Yellow
Write-Host ""

# Get all PHP files
$files = Get-ChildItem -Path $baseDir -Include *.php,*.inc,*.class -Recurse -File | Where-Object {
    $exclude = $false
    foreach ($dir in $excludeDirs) {
        if ($_.FullName -like "*\$dir\*") {
            $exclude = $true
            break
        }
    }
    -not $exclude
}

Write-Host "Found $($files.Count) PHP files to process" -ForegroundColor Cyan
Write-Host ""

foreach ($file in $files) {
    $content = Get-Content $file.FullName -Raw -ErrorAction SilentlyContinue
    if (-not $content) { continue }
    
    $originalContent = $content
    $fileChanges = 0
    
    # Pattern 1: $var{number} -> $var[number]
    # Matches: $str{0}, $array{1}, etc.
    if ($content -match '\$\w+\s*\{\s*\d+\s*\}') {
        $content = $content -replace '(\$\w+)\s*\{(\s*\d+\s*)\}', '$1[$2]'
        $fileChanges++
    }
    
    # Pattern 2: $var[expr]{number} -> $var[expr][number]
    # Matches: $arr[$i]{0}, etc.
    if ($content -match '\$\w+\[.+?\]\s*\{') {
        $content = $content -replace '(\$\w+\[.+?\])\s*\{([^}]+)\}', '$1[$2]'
        $fileChanges++
    }
    
    # Pattern 3: function_call(){number} -> function_call()[number]
    if ($content -match '\)\s*\{') {
        $content = $content -replace '(\))\s*\{(\s*\d+\s*)\}', '$1[$2]'
        $fileChanges++
    }
    
    # Pattern 4: Complex expressions with {}
    # Example: $arr[$i%3] {rand()} -> $arr[$i%3][rand()]
    if ($content -match '\]\s*\{[^}]*\(') {
        $content = $content -replace '(\])\s*\{([^}]+)\}', '$1[$2]'
        $fileChanges++
    }
    
    if ($content -ne $originalContent) {
        $content | Out-File $file.FullName -Encoding UTF8 -NoNewline
        $filesFixed++
        $totalReplacements += $fileChanges
        
        $relPath = $file.FullName.Replace($baseDir, "").TrimStart('\')
        Write-Host "✓ Fixed: $relPath ($fileChanges change(s))" -ForegroundColor Green
    }
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Green
Write-Host "Fixing Complete!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host "Files processed: $($files.Count)" -ForegroundColor Cyan
Write-Host "Files fixed: $filesFixed" -ForegroundColor Green
Write-Host "Total replacements: $totalReplacements" -ForegroundColor Yellow
Write-Host ""

if ($filesFixed -gt 0) {
    Write-Host "✓ Curly braces replaced with square brackets" -ForegroundColor Green
    Write-Host "  Your code is now PHP 8 compatible!" -ForegroundColor Cyan
} else {
    Write-Host "No changes needed - all files are already compatible" -ForegroundColor Green
}
