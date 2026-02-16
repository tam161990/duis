# SMTP Email Troubleshooting Guide

## Problem: "SUCCESS" But No Email Received

This is a common issue where the SMTP server accepts the email (returns 250 OK), but the email never arrives in the inbox.

---

## Why This Happens

### 1. **Gmail/Google Mail Specific Issues** ⚠️

Gmail has very strict spam filters and sender validation:

- **No Authentication**: Gmail prefers authenticated SMTP connections
- **Sender Reputation**: Unknown sender domains are often rejected
- **Missing SPF/DKIM**: Emails without proper DNS records are flagged
- **Content Filtering**: Certain keywords or patterns trigger spam filters

### 2. **General Email Delivery Issues**

- Email goes to SPAM/Junk folder
- Recipient mail server rejects after SMTP transaction
- Sender domain has no MX records
- Reverse DNS (PTR) not configured
- IP address blacklisted

---

## Diagnostic Steps

### Step 1: Run Diagnostic Test

```bash
cd /u01/duis-test
php test_smtp_diagnostic.php tatjana.fedorkova@gmail.com
```

This will show:
- SMTP server connectivity
- DNS resolution
- MX records
- Detailed SMTP conversation
- Gmail-specific warnings

### Step 2: Check SPAM Folder

**For Gmail:**
1. Go to https://mail.google.com
2. Check "Spam" folder
3. Search for subject: "DUIS SMTP"

**For Other Providers:**
- Check Junk/Spam folder
- Check quarantine (if corporate email)

### Step 3: Review SMTP Conversation

Look for these responses in the diagnostic output:

```
✓ Good: 250 2.0.0 OK
✗ Bad:  550 5.7.1 Rejected
⚠ Warning: 554 Transaction failed
```

---

## Solutions

### Solution 1: Enable SMTP Authentication (Recommended)

Edit `config/main.conf.php`:

```php
// Change from:
define('SMTP_AUTH', false);
define('SMTP_USERNAME', '');
define('SMTP_PASSWORD', '');

// To:
define('SMTP_AUTH', true);
define('SMTP_USERNAME', 'your-email@energo.lv');
define('SMTP_PASSWORD', 'your-password');
```

**Note:** This requires credentials from your IT team.

### Solution 2: Use Verified Sender Email

Instead of `softex@softex.lv`, use an email from your actual domain:

```php
define('EMAIL_FROM', 'noreply@energo.lv');
```

### Solution 3: Test with Different Email Provider

Gmail is very strict. Try testing with:

```bash
# Test with Outlook
php test_smtp_diagnostic.php tatjana.fedorkova@outlook.com

# Test with Yahoo
php test_smtp_diagnostic.php tatjana.fedorkova@yahoo.com

# Test with corporate email
php test_smtp_diagnostic.php tatjana.fedorkova@latvenergo.lv
```

### Solution 4: Configure DNS Records (IT Team Task)

Ask IT team to configure:

**SPF Record:**
```
v=spf1 ip4:YOUR_SERVER_IP include:mail.energo.lv ~all
```

**DKIM Record:**
```
(Requires mail server configuration)
```

**Reverse DNS (PTR):**
```
YOUR_SERVER_IP → your-server.energo.lv
```

### Solution 5: Use Different SMTP Port

Some networks block port 25. Try:

```php
// Try port 587 (submission)
define('SMTP_PORT', 587);
```

---

## Gmail-Specific Solutions

### Option A: Use Gmail SMTP Server

```php
define('SMTP_HOST', 'smtp.gmail.com');
define('SMTP_PORT', 587);
define('SMTP_ENCRYPTION', 'tls');
define('SMTP_AUTH', true);
define('SMTP_USERNAME', 'your-gmail@gmail.com');
define('SMTP_PASSWORD', 'app-specific-password'); // Not regular password!
```

**Note:** Gmail requires "App Password" (not regular password):
1. Go to https://myaccount.google.com/security
2. Enable 2-Step Verification
3. Generate App Password

### Option B: Whitelist Sender IP

Ask recipient to:
1. Create filter in Gmail for sender email
2. Mark as "Not Spam"
3. Move to "Important"

---

## Testing Strategy

### Test 1: Internal Email (Most Reliable)

```bash
# Test with internal company email
php test_smtp_diagnostic.php tatjana.fedorkova@latvenergo.lv
```

✅ **Should work** if mail.energo.lv is configured correctly

### Test 2: Corporate Email (Usually Works)

```bash
# Test with corporate Outlook
php test_smtp_diagnostic.php someone@company.lv
```

✅ **Usually works** with basic SMTP

### Test 3: Gmail (Strictest)

```bash
# Test with Gmail (hardest to deliver)
php test_smtp_diagnostic.php tatjana.fedorkova@gmail.com
```

⚠️ **Often fails** without authentication

---

## Common Error Messages

### "550 5.7.1 Relaying denied"
**Cause:** SMTP server doesn't allow relaying
**Solution:** Enable SMTP authentication

### "554 5.7.1 Rejected"
**Cause:** Spam filter rejection
**Solution:** Fix sender domain, add SPF/DKIM

### "Connection timeout"
**Cause:** Firewall blocking port
**Solution:** Open port 25/587 in firewall

### "550 Mailbox not found"
**Cause:** Invalid recipient email
**Solution:** Check email address spelling

---

## Verification Checklist

Before contacting IT support, verify:

- [ ] SMTP server connectivity (telnet mail.energo.lv 25)
- [ ] Firewall allows outgoing connections on port 25
- [ ] Sender email domain exists and has MX records
- [ ] Recipient email address is valid
- [ ] Checked SPAM/Junk folder
- [ ] Waited 5-10 minutes for delivery
- [ ] Ran diagnostic test script
- [ ] Reviewed detailed SMTP conversation logs

---

## Understanding SMTP Response Codes

### Success Codes (2xx)
- `220` - Service ready
- `250` - Requested action okay, completed
- `251` - User not local; will forward

### Temporary Failure (4xx)
- `421` - Service not available
- `450` - Mailbox unavailable
- `451` - Aborted: error in processing

### Permanent Failure (5xx)
- `550` - Mailbox unavailable / Rejected
- `551` - User not local
- `552` - Exceeded storage allocation
- `553` - Mailbox name not allowed
- `554` - Transaction failed

---

## Server-Side Checks (IT Team)

Ask IT to verify:

### 1. Check Mail Server Logs
```bash
# On mail.energo.lv
tail -f /var/log/mail.log
grep "from=<softex@softex.lv>" /var/log/mail.log
```

### 2. Check if Outbound Email is Allowed
```bash
# Test from server
telnet mail.energo.lv 25
```

### 3. Check IP Blacklists
Visit: https://mxtoolbox.com/blacklists.aspx
Enter: Your server IP

### 4. Check SPF Records
```bash
dig txt softex.lv
dig txt energo.lv
```

---

## Alternative: Use PHP mail() Fallback

If SMTP consistently fails, the system automatically falls back to PHP `mail()` function.

To force using PHP mail():

```php
// In email.class, comment out SMTP usage
// $mailer->send(...);

// Use directly:
mail($recipient, $subject, $body, $headers);
```

---

## Contact Information

**For SMTP Issues:**
- Check: `logs/wh.log` for detailed logs
- Run: `php test_smtp_diagnostic.php`
- Contact: IT Support with diagnostic output

**For Gmail Delivery:**
- Documentation: https://support.google.com/mail/answer/81126
- SPF/DKIM: https://support.google.com/a/answer/33786

---

## Quick Fix Summary

### Immediate (No IT Required):
1. ✅ Check SPAM folder
2. ✅ Test with different email provider
3. ✅ Run diagnostic script
4. ✅ Try different recipient email

### Short-term (Requires Config Change):
1. Change sender email to @energo.lv domain
2. Try different SMTP port (587)
3. Add authentication credentials (if available)

### Long-term (Requires IT Team):
1. Configure SPF/DKIM records
2. Set up reverse DNS
3. Get proper SMTP credentials
4. Whitelist server IP on recipient side

---

**Last Updated:** 2026-02-16  
**Version:** 1.0

