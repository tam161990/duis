# Production Setup Instructions

## SMTP Configuration Missing Error

If you get this error on production:
```
ERROR: Required constants not defined in config/main.conf.php
```

This means the production `config/main.conf.php` doesn't have the SMTP configuration yet.

---

## Quick Fix

### Option 1: Check What's Missing (Safe)

```bash
cd /u01/duis-prod  # or your production path
php add_smtp_config.php
```

This will show you exactly which constants are missing and provide copy-paste instructions.

### Option 2: Manual Update (Recommended)

1. **Edit the production config file:**
   ```bash
   cd /u01/duis-prod
   nano config/main.conf.php
   ```

2. **Find this line:**
   ```php
   define('EMAIL_FROM', 'softex@softex.lv');
   ```

3. **Add these lines after it:**
   ```php
   # =============================================================================
   # SMTP Email configuration
   # =============================================================================

   // SMTP server hostname
   define('SMTP_HOST', 'mail.energo.lv');

   // SMTP server port (25 for no encryption, 587 for TLS, 465 for SSL)
   define('SMTP_PORT', 25);

   // SMTP encryption type: '', 'tls', or 'ssl'
   define('SMTP_ENCRYPTION', '');

   // SMTP authentication enabled (false = no auth, true = use username/password)
   define('SMTP_AUTH', false);

   // SMTP username (leave empty if SMTP_AUTH is false)
   define('SMTP_USERNAME', '');

   // SMTP password (leave empty if SMTP_AUTH is false)
   define('SMTP_PASSWORD', '');

   // SMTP sender name
   define('SMTP_FROM_NAME', 'DUIS System');
   ```

4. **Save and exit** (Ctrl+X, Y, Enter in nano)

5. **Verify:**
   ```bash
   php add_smtp_config.php
   ```
   Should show: ✓ All SMTP constants are already defined!

---

## After Configuration is Added

### Test SMTP:

```bash
cd /u01/duis-prod

# Check configuration
php add_smtp_config.php

# Run diagnostic test
php test_smtp_diagnostic.php tatjana.fedorkova@latvenergo.lv

# Or quick test
php test_smtp_standalone.php tatjana.fedorkova@latvenergo.lv
```

---

## If You Don't Have Access to Edit Config

Contact your system administrator and ask them to add the SMTP configuration to:
```
/u01/duis-prod/config/main.conf.php
```

Provide them with this file: `sql/SMTP_CONFIG_UPDATE.sql` which contains the full configuration.

---

## Alternative: Copy from Test

If test environment already has the configuration:

```bash
# Backup production config first
cp /u01/duis-prod/config/main.conf.php /u01/duis-prod/config/main.conf.php.backup

# Compare with test config
diff /u01/duis-test/config/main.conf.php /u01/duis-prod/config/main.conf.php

# Manually copy the SMTP section
```

⚠️ **Warning:** Don't just copy the entire config file - database settings and other configs may differ between test and prod!

---

## Quick Verification

After adding the configuration, verify it works:

```bash
cd /u01/duis-prod

# This should show your SMTP config (not error)
php -r "require_once('config/main.conf.php'); echo 'SMTP_HOST: '.SMTP_HOST.PHP_EOL;"
```

Expected output:
```
SMTP_HOST: mail.energo.lv
```

---

## Next Steps

Once configuration is added:

1. ✅ **Verify config:** `php add_smtp_config.php`
2. ✅ **Test connectivity:** `php test_smtp_diagnostic.php`
3. ✅ **Send test email:** `php test_smtp_standalone.php your.email@example.com`
4. ✅ **Check results:** Look for email in inbox/spam

---

## Troubleshooting

### Still Getting "Constants Not Defined" Error

1. Check if you're in the right directory:
   ```bash
   pwd
   # Should show: /u01/duis-prod (or similar)
   ```

2. Check if config file exists:
   ```bash
   ls -la config/main.conf.php
   ```

3. Check file permissions:
   ```bash
   # Should be readable
   cat config/main.conf.php | grep SMTP_HOST
   ```

### Config Added But Still Not Working

1. Check PHP syntax:
   ```bash
   php -l config/main.conf.php
   ```

2. Check if constants actually defined:
   ```bash
   php -r "require_once('config/main.conf.php'); var_dump(defined('SMTP_HOST'));"
   ```
   Should output: `bool(true)`

---

## Files Reference

- **Helper script:** `add_smtp_config.php` - Checks configuration status
- **Test scripts:** 
  - `test_smtp.php` - Full test with DUIS initialization
  - `test_smtp_standalone.php` - Quick standalone test
  - `test_smtp_diagnostic.php` - Detailed diagnostic
- **Documentation:**
  - `SMTP_TROUBLESHOOTING.md` - Troubleshooting guide
  - `libs/email/README_SMTP_CONFIG.md` - Configuration guide
  - `sql/SMTP_CONFIG_UPDATE.sql` - SQL documentation

---

**Updated:** 2026-02-16  
**For:** Production deployment of DUIS-549 SMTP changes

