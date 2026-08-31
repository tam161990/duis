<?php
/**
 * Quick SMTP Connection Test
 * Tests if we can connect to the SMTP server
 */

require_once(dirname(__FILE__).'/config/main.conf.php');

echo "=========================================\n";
echo "SMTP CONNECTION TEST\n";
echo "=========================================\n\n";

echo "Configuration:\n";
echo "  SMTP_HOST: " . SMTP_HOST . "\n";
echo "  SMTP_PORT: " . SMTP_PORT . "\n\n";

// Test 1: DNS Resolution
echo "TEST 1: DNS Resolution\n";
echo "-----------------------------------\n";
$hostname = 'mail.energo.lv';
$ip = gethostbyname($hostname);
echo "  $hostname resolves to: $ip\n";
echo "  Current config uses: " . SMTP_HOST . "\n\n";

// Test 2: Direct IP Connection
echo "TEST 2: Direct Connection to " . SMTP_HOST . ":" . SMTP_PORT . "\n";
echo "-----------------------------------\n";
$socket = @fsockopen(SMTP_HOST, SMTP_PORT, $errno, $errstr, 10);
if ($socket) {
    echo "✓ SUCCESS: Connected to " . SMTP_HOST . ":" . SMTP_PORT . "\n";
    $welcome = fgets($socket, 515);
    echo "  Server says: " . trim($welcome) . "\n";
    fclose($socket);
    echo "\n✓ SMTP server is accessible!\n";
    echo "\nNext step: Try sending a test email with test_smtp_diagnostic.php\n";
} else {
    echo "✗ FAILED: Cannot connect to " . SMTP_HOST . ":" . SMTP_PORT . "\n";
    echo "  Error: $errstr ($errno)\n";
    echo "\n  Possible issues:\n";
    echo "  - Firewall blocking connection\n";
    echo "  - SMTP server is down\n";
    echo "  - Wrong IP address\n";
    exit(1);
}

echo "=========================================\n";
?>
