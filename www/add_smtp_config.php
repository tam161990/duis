<?php
/**
 * Helper script to add SMTP configuration to config/main.conf.php
 * This script checks if SMTP constants exist and helps add them if missing
 */

echo "=========================================\n";
echo "SMTP Configuration Helper\n";
echo "=========================================\n\n";

$configFile = dirname(__FILE__).'/config/main.conf.php';

if (!file_exists($configFile)) {
    die("ERROR: Config file not found at: $configFile\n");
}

echo "Config file found: $configFile\n\n";

// Load the config file
require_once($configFile);

// Check which constants are defined
$constants = array(
    'EMAIL_FROM' => 'softex@softex.lv',
    'SMTP_HOST' => 'mail.energo.lv',
    'SMTP_PORT' => 25,
    'SMTP_ENCRYPTION' => '',
    'SMTP_AUTH' => false,
    'SMTP_USERNAME' => '',
    'SMTP_PASSWORD' => '',
    'SMTP_FROM_NAME' => 'DUIS System'
);

$missing = array();
$existing = array();

foreach ($constants as $name => $defaultValue) {
    if (defined($name)) {
        $existing[] = $name;
    } else {
        $missing[] = $name;
    }
}

echo "Status Check:\n";
echo "-------------\n";

if (empty($missing)) {
    echo "✓ All SMTP constants are already defined!\n\n";
    echo "Current configuration:\n";
    foreach ($constants as $name => $defaultValue) {
        $value = constant($name);
        if ($name == 'SMTP_PASSWORD' && !empty($value)) {
            $value = '***hidden***';
        }
        if (is_bool($value)) {
            $value = $value ? 'true' : 'false';
        }
        echo "  $name = " . var_export($value, true) . "\n";
    }
    echo "\n✓ SMTP configuration is complete!\n";
    exit(0);
}

echo "✗ Missing SMTP constants: " . count($missing) . "\n\n";

echo "Missing constants:\n";
foreach ($missing as $const) {
    echo "  - $const\n";
}

echo "\n=========================================\n";
echo "TO FIX: Add the following to config/main.conf.php\n";
echo "=========================================\n\n";

echo "Add this after the line:\n";
echo "  define('EMAIL_FROM', 'softex@softex.lv');\n\n";

echo "# =============================================================================\n";
echo "# SMTP Email configuration\n";
echo "# =============================================================================\n\n";

echo "// SMTP server hostname\n";
echo "define('SMTP_HOST', 'mail.energo.lv');\n\n";

echo "// SMTP server port (25 for no encryption, 587 for TLS, 465 for SSL)\n";
echo "define('SMTP_PORT', 25);\n\n";

echo "// SMTP encryption type: '', 'tls', or 'ssl'\n";
echo "// Current: no encryption (empty string)\n";
echo "// Future (MS Outlook): will need 'tls' or 'ssl'\n";
echo "define('SMTP_ENCRYPTION', '');\n\n";

echo "// SMTP authentication enabled (false = no auth, true = use username/password)\n";
echo "// Current: false (no authentication required)\n";
echo "// Future (MS Outlook): set to true\n";
echo "define('SMTP_AUTH', false);\n\n";

echo "// SMTP username (leave empty if SMTP_AUTH is false)\n";
echo "define('SMTP_USERNAME', '');\n\n";

echo "// SMTP password (leave empty if SMTP_AUTH is false)\n";
echo "define('SMTP_PASSWORD', '');\n\n";

echo "// SMTP sender name\n";
echo "define('SMTP_FROM_NAME', 'DUIS System');\n\n";

echo "=========================================\n\n";

echo "INSTRUCTIONS:\n";
echo "1. Open config/main.conf.php in editor\n";
echo "2. Find the line: define('EMAIL_FROM', ...);\n";
echo "3. Add the SMTP configuration section after it\n";
echo "4. Save the file\n";
echo "5. Run this script again to verify\n\n";

echo "Or use this command to edit:\n";
echo "  nano $configFile\n\n";

echo "After adding the configuration, you can test with:\n";
echo "  php test_smtp_diagnostic.php\n\n";
?>

