<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <title>DUIS - PHP 8.3 Status</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; background: #f5f5f5; }
        .container { max-width: 1200px; margin: 0 auto; background: white; padding: 30px; border-radius: 10px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }
        h1 { color: #2c3e50; border-bottom: 3px solid #3498db; padding-bottom: 10px; }
        h2 { color: #34495e; margin-top: 30px; }
        .success { color: #27ae60; font-weight: bold; }
        .error { color: #e74c3c; font-weight: bold; }
        .warning { color: #f39c12; font-weight: bold; }
        table { width: 100%; border-collapse: collapse; margin: 20px 0; }
        th, td { padding: 12px; text-align: left; border-bottom: 1px solid #ddd; }
        th { background-color: #3498db; color: white; }
        tr:hover { background-color: #f5f5f5; }
        .status-ok { color: #27ae60; font-weight: bold; }
        .status-fail { color: #e74c3c; font-weight: bold; }
        .code { background: #ecf0f1; padding: 10px; border-left: 4px solid #3498db; margin: 10px 0; font-family: monospace; }
        .next-steps { background: #e8f8f5; padding: 20px; border-radius: 5px; margin: 20px 0; }
        .next-steps h3 { color: #16a085; margin-top: 0; }
        .next-steps ol { line-height: 1.8; }
    </style>
</head>
<body>
    <div class="container">
        <h1>🚀 DUIS - PHP 8.3.36 Migration Status</h1>
        
        <h2>📊 PHP Environment</h2>
        <table>
            <tr>
                <th>Parameter</th>
                <th>Value</th>
                <th>Status</th>
            </tr>
            <tr>
                <td><strong>PHP Version</strong></td>
                <td><?php echo phpversion(); ?></td>
                <td class="<?php echo version_compare(phpversion(), '8.3.0', '>=') ? 'status-ok' : 'status-fail'; ?>">
                    <?php echo version_compare(phpversion(), '8.3.0', '>=') ? '✓ OK' : '✗ FAIL'; ?>
                </td>
            </tr>
            <tr>
                <td><strong>Thread Safety</strong></td>
                <td><?php echo ZEND_THREAD_SAFE ? 'Enabled (Thread Safe)' : 'Disabled (Non-Thread Safe)'; ?></td>
                <td class="<?php echo ZEND_THREAD_SAFE ? 'status-ok' : 'status-fail'; ?>">
                    <?php echo ZEND_THREAD_SAFE ? '✓ OK for Apache' : '✗ Not suitable for Apache'; ?>
                </td>
            </tr>
            <tr>
                <td><strong>Configuration File</strong></td>
                <td><?php echo php_ini_loaded_file(); ?></td>
                <td class="status-ok">✓ Loaded</td>
            </tr>
            <tr>
                <td><strong>Memory Limit</strong></td>
                <td><?php echo ini_get('memory_limit'); ?></td>
                <td class="status-ok">✓ OK</td>
            </tr>
            <tr>
                <td><strong>Max Execution Time</strong></td>
                <td><?php echo ini_get('max_execution_time'); ?> seconds</td>
                <td class="status-ok">✓ OK</td>
            </tr>
            <tr>
                <td><strong>Upload Max Filesize</strong></td>
                <td><?php echo ini_get('upload_max_filesize'); ?></td>
                <td class="status-ok">✓ OK</td>
            </tr>
        </table>

        <h2>🔌 Critical Extensions</h2>
        <table>
            <tr>
                <th>Extension</th>
                <th>Required For</th>
                <th>Status</th>
            </tr>
            <?php
            $required_extensions = [
                'mysqli' => 'Database (MySQL)',
                'pdo_mysql' => 'Database (PDO)',
                'mbstring' => 'Multibyte strings',
                'openssl' => 'Encryption/SSL',
                'curl' => 'HTTP requests',
                'gd' => 'Image processing',
                'fileinfo' => 'File type detection',
                'session' => 'Sessions',
                'json' => 'JSON processing'
            ];
            
            foreach ($required_extensions as $ext => $purpose) {
                $loaded = extension_loaded($ext);
                $status_class = $loaded ? 'status-ok' : 'status-fail';
                $status_text = $loaded ? '✓ Loaded' : '✗ Missing';
                echo "<tr>";
                echo "<td><strong>$ext</strong></td>";
                echo "<td>$purpose</td>";
                echo "<td class='$status_class'>$status_text</td>";
                echo "</tr>";
            }
            ?>
        </table>

        <h2>⚠️ Removed Functions Check</h2>
        <table>
            <tr>
                <th>Function</th>
                <th>Removed In</th>
                <th>Status</th>
            </tr>
            <?php
            $removed_functions = [
                'each' => 'PHP 8.0',
                'create_function' => 'PHP 8.0',
                'split' => 'PHP 7.0',
                'ereg' => 'PHP 7.0'
            ];
            
            foreach ($removed_functions as $func => $version) {
                $exists = function_exists($func);
                $status_class = $exists ? 'status-fail' : 'status-ok';
                $status_text = $exists ? '✗ Still exists (unexpected)' : '✓ Removed (expected)';
                echo "<tr>";
                echo "<td><code>$func()</code></td>";
                echo "<td>$version</td>";
                echo "<td class='$status_class'>$status_text</td>";
                echo "</tr>";
            }
            ?>
        </table>

        <h2>🔗 Database Connection Test</h2>
        <?php
        $db_test_result = '';
        $config_file = dirname(__FILE__) . '/config/main.conf.php';
        
        if (file_exists($config_file)) {
            require_once($config_file);
            
            if (defined('DB_HOST') && defined('DB_USER') && defined('DB_PASSWORD') && defined('DB_NAME')) {
                try {
                    $mysqli = new mysqli(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
                    
                    if ($mysqli->connect_error) {
                        echo "<div class='code error'>✗ Connection failed: " . htmlspecialchars($mysqli->connect_error) . "</div>";
                    } else {
                        echo "<div class='code success'>✓ Database connected successfully!</div>";
                        echo "<div class='code'>";
                        echo "<strong>Server:</strong> " . htmlspecialchars($mysqli->server_info) . "<br>";
                        echo "<strong>Client:</strong> " . htmlspecialchars($mysqli->client_info) . "<br>";
                        echo "<strong>Database:</strong> " . htmlspecialchars(DB_NAME);
                        echo "</div>";
                        $mysqli->close();
                    }
                } catch (Exception $e) {
                    echo "<div class='code error'>✗ Exception: " . htmlspecialchars($e->getMessage()) . "</div>";
                }
            } else {
                echo "<div class='code warning'>⚠ Database constants not defined in config</div>";
            }
        } else {
            echo "<div class='code error'>✗ Config file not found: " . htmlspecialchars($config_file) . "</div>";
        }
        ?>

        <div class="next-steps">
            <h3>📋 Next Steps</h3>
            <ol>
                <li><strong>Test Main Page:</strong> <a href="/" target="_blank">Open DUIS Main Page</a></li>
                <li><strong>Test Login:</strong> Try to log in to the system</li>
                <li><strong>Test RBF Module:</strong> Open RBF acts if possible</li>
                <li><strong>Check for Errors:</strong> Look for any PHP errors or warnings</li>
                <li><strong>If Everything Works:</strong> Proceed to configure Apache for PHP 8.3</li>
                <li><strong>If Issues Found:</strong> Document errors and revert to PHP 7.3</li>
            </ol>
        </div>

        <div class="code">
            <strong>To stop this server:</strong> Close the PHP console window or press Ctrl+C<br>
            <strong>To switch back to PHP 7.3:</strong> Use switch-php73.bat<br>
            <strong>Current URL:</strong> http://localhost:8083/
        </div>

        <hr style="margin: 30px 0;">
        <p style="color: #7f8c8d; text-align: center;">
            Generated: <?php echo date('Y-m-d H:i:s'); ?> | 
            Server: <?php echo php_sapi_name(); ?> | 
            OS: <?php echo PHP_OS; ?>
        </p>
    </div>
</body>
</html>
