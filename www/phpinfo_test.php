<?php
header('Content-Type: text/plain; charset=UTF-8');
echo "PHP Version: " . phpversion() . "\n";
echo "Thread Safe: " . (ZEND_THREAD_SAFE ? "Yes" : "No") . "\n";
echo "Config File: " . php_ini_loaded_file() . "\n";
echo "\nExtensions:\n";
echo "- mysqli: " . (extension_loaded('mysqli') ? 'Loaded' : 'Missing') . "\n";
echo "- mbstring: " . (extension_loaded('mbstring') ? 'Loaded' : 'Missing') . "\n";
echo "- gd: " . (extension_loaded('gd') ? 'Loaded' : 'Missing') . "\n";
echo "- openssl: " . (extension_loaded('openssl') ? 'Loaded' : 'Missing') . "\n";
?>
