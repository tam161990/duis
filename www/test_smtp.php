<?php
/**
 * SMTP Email Test Script
 * Tests the SMTP email configuration
 */

// Include initialization file (loads all config and classes)
require_once(dirname(__FILE__).'/libs/init.inc');

echo "=========================================\n";
echo "SMTP EMAIL TEST\n";
echo "=========================================\n\n";

echo "Configuration:\n";
echo "  SMTP Host: " . SMTP_HOST . "\n";
echo "  SMTP Port: " . SMTP_PORT . "\n";
echo "  SMTP Encryption: " . (SMTP_ENCRYPTION ? SMTP_ENCRYPTION : 'None') . "\n";
echo "  SMTP Auth: " . (SMTP_AUTH ? 'Enabled' : 'Disabled') . "\n";
echo "  From Email: " . EMAIL_FROM . "\n";
echo "  From Name: " . SMTP_FROM_NAME . "\n\n";

// Get recipient email from command line or use default
$recipientEmail = isset($argv[1]) ? $argv[1] : 'tatjana.fedorkova@latvenergo.lv';

echo "Sending test email to: $recipientEmail\n\n";

// Create mailer instance
$mailer = new SmtpMailer();
$mailer->setDebug(true);

// Send test email
$subject = 'DUIS SMTP Test Email - ' . date('Y-m-d H:i:s');
$message = "This is a test email from DUIS SMTP implementation.\n\n";
$message .= "Configuration details:\n";
$message .= "- SMTP Host: " . SMTP_HOST . "\n";
$message .= "- SMTP Port: " . SMTP_PORT . "\n";
$message .= "- Encryption: " . (SMTP_ENCRYPTION ? SMTP_ENCRYPTION : 'None') . "\n";
$message .= "- Authentication: " . (SMTP_AUTH ? 'Enabled' : 'Disabled') . "\n\n";
$message .= "Sent at: " . date('Y-m-d H:i:s') . "\n";
$message .= "Server: " . (isset($_SERVER['SERVER_NAME']) ? $_SERVER['SERVER_NAME'] : php_uname('n')) . "\n";

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
    echo "4. Log file: logs/wh.log for detailed error messages\n";
}

echo "=========================================\n";
?>

