<?php
/**
 * Test connection to tmail:25
 */

require_once(dirname(__FILE__).'/config/main.conf.php');

echo "=========================================\n";
echo "TMAIL CONNECTION TEST\n";
echo "=========================================\n\n";

echo "Configuration:\n";
echo "  SMTP_HOST: " . SMTP_HOST . "\n";
echo "  SMTP_PORT: " . SMTP_PORT . "\n\n";

// Test connection to tmail:25
echo "TEST: Connecting to " . SMTP_HOST . ":" . SMTP_PORT . "\n";
echo "-----------------------------------\n";

$socket = @fsockopen(SMTP_HOST, SMTP_PORT, $errno, $errstr, 10);

if ($socket) {
    echo "✓ SUCCESS: Connected to " . SMTP_HOST . ":" . SMTP_PORT . "\n";
    
    // Read welcome message
    $welcome = fgets($socket, 515);
    echo "  Server says: " . trim($welcome) . "\n";
    
    // Try EHLO command
    fwrite($socket, "EHLO test\r\n");
    $response = fgets($socket, 515);
    echo "  EHLO response: " . trim($response) . "\n";
    
    // Close connection
    fwrite($socket, "QUIT\r\n");
    fclose($socket);
    
    echo "\n✓ Connection successful!\n";
    echo "\nNext step: Try sending a test email with test_smtp_diagnostic.php\n";
} else {
    echo "✗ FAILED: Cannot connect to " . SMTP_HOST . ":" . SMTP_PORT . "\n";
    echo "  Error: $errstr ($errno)\n";
    echo "\n  Possible issues:\n";
    echo "  - Server 'tmail' not accessible from this server\n";
    echo "  - Firewall blocking connection\n";
    echo "  - SMTP server is down\n";
    echo "  - Wrong hostname\n";
    exit(1);
}

echo "=========================================\n";
?>
