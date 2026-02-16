-- ============================================================================
-- SMTP Email Configuration Update
-- Date: 2026-02-16
-- Task: Update email system to support SMTP with flexible configuration
-- ============================================================================

-- This file documents the SMTP configuration changes made to the system.
-- No database changes are required - all configuration is in config/main.conf.php

-- ============================================================================
-- Summary of Changes
-- ============================================================================

-- 1. Added SMTP configuration constants to config/main.conf.php:
--    - SMTP_HOST: SMTP server hostname (current: mail.energo.lv)
--    - SMTP_PORT: SMTP server port (current: 25)
--    - SMTP_ENCRYPTION: Encryption type (current: none, future: tls/ssl)
--    - SMTP_AUTH: Authentication enabled (current: false, future: true)
--    - SMTP_USERNAME: SMTP username (for future use)
--    - SMTP_PASSWORD: SMTP password (for future use)
--    - SMTP_FROM_NAME: Sender name (DUIS System)

-- 2. Created new SmtpMailer.class:
--    - Full SMTP protocol implementation
--    - Support for TLS/SSL encryption
--    - Support for SMTP authentication
--    - Automatic fallback to PHP mail() on failure
--    - UTF-8 support for Latvian characters
--    - Detailed logging for debugging

-- 3. Updated email.class:
--    - Now uses SmtpMailer instead of mail()
--    - sendMsgStatusChangeNotification() updated
--    - sendRbfActStatusChangeNotification() updated
--    - Better error handling and logging

-- 4. Created documentation:
--    - libs/email/README_SMTP_CONFIG.md
--    - Configuration guide in Latvian and English
--    - Testing procedures
--    - FAQ section

-- ============================================================================
-- Current Configuration (IT Team Requirements)
-- ============================================================================

-- SMTP Server: mail.energo.lv
-- Port: 25
-- Encryption: None
-- Authentication: Not required

-- ============================================================================
-- Future Configuration (MS Outlook)
-- ============================================================================

-- When migrating to MS Outlook, update config/main.conf.php:
-- 
-- For TLS (Recommended):
--   SMTP_PORT: 587
--   SMTP_ENCRYPTION: 'tls'
--   SMTP_AUTH: true
--   SMTP_USERNAME: 'your-email@energo.lv'
--   SMTP_PASSWORD: 'your-password'
--
-- For SSL (Alternative):
--   SMTP_PORT: 465
--   SMTP_ENCRYPTION: 'ssl'
--   SMTP_AUTH: true
--   SMTP_USERNAME: 'your-email@energo.lv'
--   SMTP_PASSWORD: 'your-password'

-- ============================================================================
-- Testing
-- ============================================================================

-- To test SMTP configuration, create a test script:
-- 
-- <?php
-- require_once('config/main.conf.php');
-- require_once('libs/email/SmtpMailer.class');
-- 
-- $mailer = new SmtpMailer();
-- $mailer->setDebug(true);
-- 
-- $result = $mailer->send(
--     'test@example.com',
--     'Test Subject',
--     'Test Message Body',
--     EMAIL_FROM,
--     SMTP_FROM_NAME
-- );
-- 
-- echo $result ? "SUCCESS\n" : "FAILED: " . $mailer->getLastError() . "\n";
-- ?>

-- ============================================================================
-- Files Modified
-- ============================================================================

-- 1. config/main.conf.php (added SMTP configuration)
-- 2. libs/email/email.class (updated to use SMTP)
-- 3. libs/email/SmtpMailer.class (NEW - SMTP implementation)
-- 4. libs/email/README_SMTP_CONFIG.md (NEW - documentation)
-- 5. sql/SMTP_CONFIG_UPDATE.sql (NEW - this file)

-- ============================================================================
-- Compatibility
-- ============================================================================

-- The system is backward compatible:
-- - If SMTP fails, it automatically falls back to PHP mail()
-- - Existing email functionality continues to work
-- - No changes required to calling code
-- - Configuration can be updated without code changes

-- ============================================================================
-- Logging
-- ============================================================================

-- All SMTP operations are logged to: logs/wh.log
-- Log entries include:
-- - Connection attempts
-- - Authentication results
-- - Send status for each email
-- - Error messages with details
-- - Fallback operations

-- ============================================================================
-- End of SMTP Configuration Update
-- ============================================================================

