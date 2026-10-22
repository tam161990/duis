$baseDir = "C:\xampp\WORKS\duis-dev\www"
$excludeDirs = @('.git', 'cache', 'temp', 'tmp', 'vendor', 'node_modules')
$filesFixed = 0
$totalReplacements = 0

Write-Host "========================================"
Write-Host "PHP 8 Curly Braces Fixer"
Write-Host "========================================"
Write-Host ""
Write-Host "Scanning: $baseDir"
Write-Host ""

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

Write-Host "Found $($files.Count) PHP files"
Write-Host ""

foreach ($file in $files) {
    $content = Get-Content $file.FullName -Raw -ErrorAction SilentlyContinue
    if (-not $content) { continue }
    
    $originalContent = $content
    $replacements = 0
    
    # Replace all patterns of {digit} with [digit]
    while ($content -match '(\$\w+(?:\[[^\]]+\])*)\s*\{(\d+)\}') {
        $content = $content -replace '(\$\w+(?:\[[^\]]+\])*)\s*\{(\d+)\}', '$1[$2]'
        $replacements++
        if ($replacements -gt 100) { break }
    }
    
    # Replace patterns like: $var{expr} where expr contains function calls
    while ($content -match '(\$\w+(?:\[[^\]]+\])*)\s*\{([^}]+)\}' -and $replacements -lt 100) {
        $oldContent = $content
        $content = $content -replace '(\$\w+(?:\[[^\]]+\])*)\s*\{([^}]+)\}', '$1[$2]'
        if ($content -eq $oldContent) { break }
        $replacements++
    }
    
    if ($content -ne $originalContent) {
        $content | Out-File $file.FullName -Encoding UTF8 -NoNewline
        $filesFixed++
        
        $relPath = $file.FullName.Replace($baseDir, "").TrimStart('\')
        Write-Host "[+] Fixed: $relPath"
    }
}

Write-Host ""
Write-Host "========================================"
Write-Host "Complete!"
Write-Host "========================================"
Write-Host "Files processed: $($files.Count)"
Write-Host "Files fixed: $filesFixed"
Write-Host ""
