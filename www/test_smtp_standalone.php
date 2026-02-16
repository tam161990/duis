<?php
/**
 * Standalone SMTP Email Test Script
 * This script can run without full DUIS initialization
 * Use this for quick testing
 */

// Load configuration
$configFile = dirname(__FILE__).'/config/main.conf.php';
if (!file_exists($configFile)) {
    die("ERROR: Config file not found at: $configFile\n");
}
require_once($configFile);

// Verify constants are loaded
if (!defined('EMAIL_FROM')) {
    die("ERROR: EMAIL_FROM constant not defined. Check config/main.conf.php\n");
}
if (!defined('SMTP_HOST')) {
    die("ERROR: SMTP_HOST constant not defined. Check config/main.conf.php\n");
}

// Load SmtpMailer class
require_once(dirname(__FILE__).'/libs/email/SmtpMailer.class');

echo "=========================================\n";
echo "SMTP STANDALONE TEST\n";
echo "=========================================\n\n";

echo "Configuration:\n";
echo "  SMTP Host: " . SMTP_HOST . "\n";
echo "  SMTP Port: " . SMTP_PORT . "\n";
echo "  SMTP Encryption: " . (SMTP_ENCRYPTION ? SMTP_ENCRYPTION : 'None') . "\n";
echo "  SMTP Auth: " . (SMTP_AUTH ? 'Enabled' : 'Disabled') . "\n";
echo "  From Email: " . EMAIL_FROM . "\n";
echo "  From Name: " . SMTP_FROM_NAME . "\n\n";

// Test SMTP connectivity first
echo "Testing SMTP connectivity...\n";
$testSocket = @fsockopen(SMTP_HOST, SMTP_PORT, $errno, $errstr, 5);
if (!$testSocket) {
    echo "✗ ERROR: Cannot connect to " . SMTP_HOST . ":" . SMTP_PORT . "\n";
    echo "  Error: $errstr ($errno)\n";
    echo "  This means:\n";
    echo "  - SMTP server may be down\n";
    echo "  - Firewall is blocking the connection\n";
    echo "  - Wrong hostname/port\n\n";
    die("Please fix connectivity issues before proceeding.\n");
}
echo "✓ SMTP server is reachable\n";
fclose($testSocket);
echo "\n";

// Get recipient email from command line or use default
$recipientEmail = isset($argv[1]) ? $argv[1] : 'tatjana.fedorkova@gmail.com';

echo "Sending test email to: $recipientEmail\n\n";

// Create mailer instance
$mailer = new SmtpMailer();
$mailer->setDebug(true);

// Send test email
$subject = 'DUIS SMTP Standalone Test - ' . date('Y-m-d H:i:s');
$message = "This is a standalone test email from DUIS SMTP implementation.\n\n";
$message .= "Configuration details:\n";
$message .= "- SMTP Host: " . SMTP_HOST . "\n";
$message .= "- SMTP Port: " . SMTP_PORT . "\n";
$message .= "- Encryption: " . (SMTP_ENCRYPTION ? SMTP_ENCRYPTION : 'None') . "\n";
$message .= "- Authentication: " . (SMTP_AUTH ? 'Enabled' : 'Disabled') . "\n\n";
$message .= "Sent at: " . date('Y-m-d H:i:s') . "\n";
$message .= "Server: " . php_uname('n') . "\n";

echo "Attempting to send email...\n";
echo "=========================================\n\n";

$result = $mailer->send(
    $recipientEmail,
    $subject,
    $message,
    EMAIL_FROM,
    SMTP_FROM_NAME
);

echo "\n=========================================\n";

if ($result) {
    echo "✓ SUCCESS: Email sent successfully!\n";
    echo "Check your inbox at: $recipientEmail\n";
} else {
    echo "✗ FAILED: Could not send email\n";
    echo "Error: " . $mailer->getLastError() . "\n";
    echo "\nPlease check:\n";
    echo "1. SMTP server is accessible: " . SMTP_HOST . ":" . SMTP_PORT . "\n";
    echo "2. Firewall allows outgoing connections on port " . SMTP_PORT . "\n";
    echo "3. Configuration in config/main.conf.php is correct\n";
}

echo "=========================================\n";

echo "\nNote: This is a standalone test. For full system test with logging,\n";
echo "      use: php test_smtp.php\n";
?>

