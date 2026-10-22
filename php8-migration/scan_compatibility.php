<?php
/**
 * PHP 8 Compatibility Scanner
 * Scans DUIS codebase for removed/deprecated functions
 */

error_reporting(E_ALL);
ini_set('display_errors', 1);

$baseDir = 'C:/xampp/WORKS/duis-dev/www';
$excludeDirs = ['vendor', 'node_modules', '.git', 'cache', 'temp', 'tmp'];

// Functions removed in PHP 8.0
$removedFunctions = [
    'each' => [
        'removed_in' => 'PHP 8.0',
        'alternative' => 'Use foreach or array functions',
        'pattern' => '/\beach\s*\(/',
    ],
    'create_function' => [
        'removed_in' => 'PHP 8.0',
        'alternative' => 'Use anonymous functions or closures',
        'pattern' => '/\bcreate_function\s*\(/',
    ],
    'split' => [
        'removed_in' => 'PHP 7.0 (also not in PHP 8)',
        'alternative' => 'Use explode() or preg_split()',
        'pattern' => '/\bsplit\s*\(/',
    ],
    'ereg' => [
        'removed_in' => 'PHP 7.0 (also not in PHP 8)',
        'alternative' => 'Use preg_match()',
        'pattern' => '/\bereg\s*\(/',
    ],
    'eregi' => [
        'removed_in' => 'PHP 7.0 (also not in PHP 8)',
        'alternative' => 'Use preg_match() with /i flag',
        'pattern' => '/\beregi\s*\(/',
    ],
    'ereg_replace' => [
        'removed_in' => 'PHP 7.0 (also not in PHP 8)',
        'alternative' => 'Use preg_replace()',
        'pattern' => '/\bereg_replace\s*\(/',
    ],
    'mysql_connect' => [
        'removed_in' => 'PHP 7.0 (also not in PHP 8)',
        'alternative' => 'Use mysqli or PDO',
        'pattern' => '/\bmysql_connect\s*\(/',
    ],
    'mysql_query' => [
        'removed_in' => 'PHP 7.0 (also not in PHP 8)',
        'alternative' => 'Use mysqli or PDO',
        'pattern' => '/\bmysql_query\s*\(/',
    ],
];

$issues = [];
$filesScanned = 0;
$totalIssues = 0;

function scanDirectory($dir, &$files, $excludeDirs) {
    $items = @scandir($dir);
    if (!$items) return;
    
    foreach ($items as $item) {
        if ($item === '.' || $item === '..') continue;
        
        $path = $dir . '/' . $item;
        
        if (is_dir($path)) {
            $dirName = basename($path);
            if (!in_array($dirName, $excludeDirs)) {
                scanDirectory($path, $files, $excludeDirs);
            }
        } elseif (is_file($path) && preg_match('/\.(php|inc)$/i', $path)) {
            $files[] = $path;
        }
    }
}

function scanFile($file, $removedFunctions) {
    $content = @file_get_contents($file);
    if ($content === false) return [];
    
    $lines = explode("\n", $content);
    $fileIssues = [];
    
    foreach ($removedFunctions as $funcName => $info) {
        $pattern = $info['pattern'];
        
        foreach ($lines as $lineNum => $lineContent) {
            // Skip comments
            if (preg_match('/^\s*\/\//', $lineContent) || preg_match('/^\s*\*/', $lineContent)) {
                continue;
            }
            
            if (preg_match($pattern, $lineContent)) {
                $fileIssues[] = [
                    'function' => $funcName,
                    'line' => $lineNum + 1,
                    'content' => trim($lineContent),
                    'removed_in' => $info['removed_in'],
                    'alternative' => $info['alternative'],
                ];
            }
        }
    }
    
    return $fileIssues;
}

// Start scanning
echo "PHP 8 Compatibility Scanner\n";
echo str_repeat("=", 80) . "\n";
echo "Scanning directory: $baseDir\n";
echo "Excluded directories: " . implode(', ', $excludeDirs) . "\n";
echo str_repeat("=", 80) . "\n\n";

$files = [];
scanDirectory($baseDir, $files, $excludeDirs);

$filesScanned = count($files);
echo "Found $filesScanned PHP files to scan\n";
echo "Scanning for removed functions...\n\n";

foreach ($files as $file) {
    $fileIssues = scanFile($file, $removedFunctions);
    
    if (!empty($fileIssues)) {
        $issues[$file] = $fileIssues;
        $totalIssues += count($fileIssues);
    }
}

// Report results
if (empty($issues)) {
    echo str_repeat("=", 80) . "\n";
    echo "✓ GREAT NEWS! No removed functions found!\n";
    echo str_repeat("=", 80) . "\n";
    echo "\nYour codebase appears to be compatible with PHP 8.3!\n";
    echo "Files scanned: $filesScanned\n";
} else {
    echo str_repeat("=", 80) . "\n";
    echo "⚠ WARNING: Found $totalIssues potential compatibility issues\n";
    echo str_repeat("=", 80) . "\n\n";
    
    $functionCount = [];
    
    foreach ($issues as $file => $fileIssues) {
        $relPath = str_replace($baseDir . '/', '', $file);
        echo "FILE: $relPath\n";
        echo str_repeat("-", 80) . "\n";
        
        foreach ($fileIssues as $issue) {
            echo sprintf(
                "  Line %4d: %s()\n",
                $issue['line'],
                $issue['function']
            );
            echo "            " . substr($issue['content'], 0, 70) . "\n";
            echo "            Removed in: {$issue['removed_in']}\n";
            echo "            Alternative: {$issue['alternative']}\n";
            echo "\n";
            
            if (!isset($functionCount[$issue['function']])) {
                $functionCount[$issue['function']] = 0;
            }
            $functionCount[$issue['function']]++;
        }
        echo "\n";
    }
    
    // Summary
    echo str_repeat("=", 80) . "\n";
    echo "SUMMARY\n";
    echo str_repeat("=", 80) . "\n";
    echo "Files with issues: " . count($issues) . " / $filesScanned\n";
    echo "Total issues: $totalIssues\n";
    echo "\nIssues by function:\n";
    arsort($functionCount);
    foreach ($functionCount as $func => $count) {
        echo sprintf("  %-20s: %3d occurrences\n", $func . "()", $count);
    }
    echo "\n";
    
    echo "NEXT STEPS:\n";
    echo "1. Review each occurrence in context\n";
    echo "2. Replace with suggested alternatives\n";
    echo "3. Test thoroughly after changes\n";
    echo "4. Re-run this scanner to verify\n";
}

echo "\n";
echo "Scan completed: " . date('Y-m-d H:i:s') . "\n";
echo "PHP Version: " . phpversion() . "\n";
