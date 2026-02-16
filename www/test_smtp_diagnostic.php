<?php
/**
 * SMTP Diagnostic Test Script
 * Provides detailed information about SMTP connection and delivery
 */

// Load configuration
$configFile = dirname(__FILE__).'/config/main.conf.php';
if (!file_exists($configFile)) {
    die("ERROR: Config file not found at: $configFile\n");
}
require_once($configFile);

// Check which constants are missing
$missingConstants = array();
$requiredConstants = array(
    'EMAIL_FROM',
    'SMTP_HOST',
    'SMTP_PORT',
    'SMTP_ENCRYPTION',
    'SMTP_AUTH',
    'SMTP_USERNAME',
    'SMTP_PASSWORD',
    'SMTP_FROM_NAME'
);

foreach ($requiredConstants as $const) {
    if (!defined($const)) {
        $missingConstants[] = $const;
    }
}

if (!empty($missingConstants)) {
    echo "ERROR: Missing SMTP configuration constants in config/main.conf.php\n\n";
    echo "Missing constants:\n";
    foreach ($missingConstants as $const) {
        echo "  - $const\n";
    }
    echo "\nPlease add the following to your config/main.conf.php file:\n";
    echo "---------------------------------------------------------------\n";
    echo "# SMTP Email configuration\n";
    echo "define('EMAIL_FROM', 'softex@softex.lv');\n";
    echo "define('SMTP_HOST', 'mail.energo.lv');\n";
    echo "define('SMTP_PORT', 25);\n";
    echo "define('SMTP_ENCRYPTION', '');\n";
    echo "define('SMTP_AUTH', false);\n";
    echo "define('SMTP_USERNAME', '');\n";
    echo "define('SMTP_PASSWORD', '');\n";
    echo "define('SMTP_FROM_NAME', 'DUIS System');\n";
    echo "---------------------------------------------------------------\n\n";
    echo "Or copy the entire SMTP section from:\n";
    echo "  sql/SMTP_CONFIG_UPDATE.sql\n";
    die("\n");
}

require_once(dirname(__FILE__).'/libs/email/SmtpMailer.class');

echo "=========================================\n";
echo "SMTP DIAGNOSTIC TEST\n";
echo "=========================================\n\n";

// Get recipient email from command line or use default
$recipientEmail = isset($argv[1]) ? $argv[1] : 'tatjana.fedorkova@gmail.com';

echo "CONFIGURATION:\n";
echo "  SMTP Host: " . SMTP_HOST . "\n";
echo "  SMTP Port: " . SMTP_PORT . "\n";
echo "  SMTP Encryption: " . (SMTP_ENCRYPTION ? SMTP_ENCRYPTION : 'None') . "\n";
echo "  SMTP Auth: " . (SMTP_AUTH ? 'Enabled' : 'Disabled') . "\n";
echo "  From Email: " . EMAIL_FROM . "\n";
echo "  From Name: " . SMTP_FROM_NAME . "\n";
echo "  To Email: " . $recipientEmail . "\n\n";

// Test 1: Check SMTP server connectivity
echo "TEST 1: SMTP Server Connectivity\n";
echo "-----------------------------------\n";
$socket = @fsockopen(SMTP_HOST, SMTP_PORT, $errno, $errstr, 10);
if ($socket) {
    echo "✓ SUCCESS: Connected to " . SMTP_HOST . ":" . SMTP_PORT . "\n";
    $welcome = fgets($socket, 515);
    echo "  Server says: " . trim($welcome) . "\n";
    fclose($socket);
} else {
    echo "✗ FAILED: Cannot connect to " . SMTP_HOST . ":" . SMTP_PORT . "\n";
    echo "  Error: $errstr ($errno)\n";
    echo "\n  Possible issues:\n";
    echo "  - Firewall blocking port " . SMTP_PORT . "\n";
    echo "  - SMTP server is down\n";
    echo "  - Wrong hostname/IP\n";
    exit(1);
}

echo "\nTEST 2: DNS Resolution\n";
echo "-----------------------------------\n";
$ip = gethostbyname(SMTP_HOST);
if ($ip != SMTP_HOST) {
    echo "✓ SUCCESS: " . SMTP_HOST . " resolves to " . $ip . "\n";
} else {
    echo "⚠ WARNING: Could not resolve " . SMTP_HOST . "\n";
}

// Check recipient domain MX records
$recipientDomain = substr(strrchr($recipientEmail, "@"), 1);
echo "\nTEST 3: Recipient Domain MX Records\n";
echo "-----------------------------------\n";
echo "Checking MX records for: " . $recipientDomain . "\n";
if (function_exists('getmxrr')) {
    $mxHosts = array();
    if (getmxrr($recipientDomain, $mxHosts)) {
        echo "✓ SUCCESS: Found " . count($mxHosts) . " MX record(s)\n";
        foreach ($mxHosts as $i => $mx) {
            echo "  MX " . ($i+1) . ": " . $mx . "\n";
        }
    } else {
        echo "⚠ WARNING: No MX records found for " . $recipientDomain . "\n";
    }
} else {
    echo "⚠ SKIPPED: getmxrr() function not available\n";
}

echo "\nTEST 4: Sender Email Validation\n";
echo "-----------------------------------\n";
$senderDomain = substr(strrchr(EMAIL_FROM, "@"), 1);
echo "Sender domain: " . $senderDomain . "\n";

// Check if sender domain has MX records
if (function_exists('getmxrr')) {
    $senderMX = array();
    if (getmxrr($senderDomain, $senderMX)) {
        echo "✓ SUCCESS: Sender domain has MX records\n";
    } else {
        echo "⚠ WARNING: Sender domain has no MX records\n";
        echo "  This may cause the email to be rejected or marked as spam\n";
    }
}

// Common Gmail rejection reasons
if (strpos($recipientEmail, '@gmail.com') !== false || strpos($recipientEmail, '@googlemail.com') !== false) {
    echo "\n⚠ IMPORTANT: Gmail Delivery Notes\n";
    echo "-----------------------------------\n";
    echo "Gmail has strict spam filters. Your email may be rejected because:\n";
    echo "1. No SMTP authentication (SMTP_AUTH = false)\n";
    echo "2. Sender email '" . EMAIL_FROM . "' may not be verified\n";
    echo "3. Missing SPF/DKIM records for sender domain\n";
    echo "4. Mail server reputation issues\n\n";
    echo "RECOMMENDATIONS:\n";
    echo "- Enable SMTP authentication\n";
    echo "- Use a verified sender email address\n";
    echo "- Configure SPF and DKIM for sender domain\n";
    echo "- Try sending to a different email provider first\n";
}

echo "\nTEST 5: Send Test Email with Detailed Logging\n";
echo "-----------------------------------\n";

// Create mailer instance with debug enabled
$mailer = new SmtpMailer();
$mailer->setDebug(true);

// Send test email
$subject = 'DUIS SMTP Diagnostic Test - ' . date('Y-m-d H:i:s');
$message = "This is a diagnostic test email from DUIS SMTP implementation.\n\n";
$message .= "If you receive this email, the SMTP configuration is working correctly.\n\n";
$message .= "Test details:\n";
$message .= "- Sent at: " . date('Y-m-d H:i:s') . "\n";
$message .= "- From: " . EMAIL_FROM . "\n";
$message .= "- SMTP Server: " . SMTP_HOST . ":" . SMTP_PORT . "\n";
$message .= "- Server: " . php_uname('n') . "\n";

echo "\nSending email...\n\n";

$result = $mailer->send(
    $recipientEmail,
    $subject,
    $message,
    EMAIL_FROM,
    SMTP_FROM_NAME
);

echo "\n=========================================\n";
echo "FINAL RESULT\n";
echo "=========================================\n";

if ($result) {
    echo "✓ SMTP Transaction: SUCCESS\n";
    echo "  The email was accepted by the SMTP server.\n\n";
    echo "NEXT STEPS:\n";
    echo "1. Check your inbox: $recipientEmail\n";
    echo "2. Check your SPAM/Junk folder\n";
    echo "3. Wait a few minutes (delivery can be delayed)\n\n";
    
    if (strpos($recipientEmail, '@gmail.com') !== false) {
        echo "GMAIL SPECIFIC:\n";
        echo "- Gmail may silently reject emails from unauthenticated sources\n";
        echo "- Try checking: https://mail.google.com/mail/u/0/#spam\n";
        echo "- Consider enabling SMTP authentication\n";
    }
} else {
    echo "✗ SMTP Transaction: FAILED\n";
    echo "  Error: " . $mailer->getLastError() . "\n\n";
    echo "TROUBLESHOOTING:\n";
    echo "1. Review the SMTP conversation above\n";
    echo "2. Check server logs\n";
    echo "3. Verify SMTP configuration\n";
}

echo "=========================================\n";
?>

