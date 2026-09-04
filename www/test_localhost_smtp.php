<?php
/**
 * Test Local SMTP (localhost/127.0.0.1)
 * Check if we should use local Postfix as relay
 */

echo "=========================================\n";
echo "LOCAL SMTP TEST\n";
echo "=========================================\n\n";

// Test localhost:25
echo "TEST: Connecting to localhost:25\n";
echo "-----------------------------------\n";
$socket = @fsockopen('localhost', 25, $errno, $errstr, 5);
if ($socket) {
    echo "✓ SUCCESS: Connected to localhost:25\n";
    $response = fgets($socket, 515);
    echo "  Server says: " . trim($response) . "\n\n";
    fclose($socket);
    
    echo "✓ Local Postfix is available!\n\n";
    echo "RECOMMENDATION:\n";
    echo "  Use 'localhost' or '127.0.0.1' as SMTP_HOST\n";
    echo "  This will use the local Postfix server as a relay,\n";
    echo "  which knows how to route mail through allowed channels.\n";
} else {
    echo "✗ FAILED: Cannot connect to localhost:25\n";
    echo "  Error: $errstr ($errno)\n\n";
    
    echo "This means:\n";
    echo "  - Local Postfix is not running, OR\n";
    echo "  - It's not listening on port 25, OR\n";
    echo "  - It's only listening on external interfaces\n";
}

echo "\n=========================================\n";
?>
