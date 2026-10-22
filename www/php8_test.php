<?php
header('Content-Type: text/html; charset=UTF-8');
?>
<!DOCTYPE html>
<html>
<head>
    <title>PHP 8.3 Test</title>
    <style>
        body { font-family: Arial; padding: 20px; background: #f0f0f0; }
        .success { color: green; font-weight: bold; font-size: 24px; }
        .info { background: white; padding: 20px; border-radius: 5px; margin: 10px 0; }
    </style>
</head>
<body>
    <div class="success">✓ PHP 8.3.36 is working!</div>
    <div class="info">
        <strong>PHP Version:</strong> <?php echo phpversion(); ?><br>
        <strong>Thread Safe:</strong> <?php echo ZEND_THREAD_SAFE ? 'Yes' : 'No'; ?><br>
        <strong>Config File:</strong> <?php echo php_ini_loaded_file(); ?><br>
        <br>
        <strong>Extensions:</strong><br>
        <?php
        $exts = ['mysqli', 'mbstring', 'gd', 'openssl', 'curl', 'pdo_mysql'];
        foreach ($exts as $ext) {
            $loaded = extension_loaded($ext);
            echo "- $ext: " . ($loaded ? '✓ Loaded' : '✗ Missing') . "<br>";
        }
        ?>
    </div>
    <a href="/">← Back to DUIS</a>
</body>
</html>
