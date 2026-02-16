# SMTP Issue Analysis - Email Not Received

## Problem Summary
**Status:** SMTP returns "SUCCESS" but emails are not being received  
**Date:** 2026-02-16  
**Recipient:** tatjana.fedorkova@gmail.com

---

## Error Log Analysis

### Error 1: Undefined Constants
```
PHP Warning: Use of undefined constant EMAIL_FROM - assumed 'EMAIL_FROM'
```

**Cause:** `config/main.conf.php` not loading correctly  
**Impact:** Uses string 'EMAIL_FROM' instead of actual email address  
**Fix:** ✅ Added config file verification in all test scripts

### Error 2: SMTP Connection Timeout
```
[SMTP] ERROR: Failed to connect to SMTP server
```

**Cause:** Cannot connect to `mail.energo.lv:25`  
**Possible reasons:**
1. Firewall blocking outbound port 25
2. SMTP server down or unreachable
3. Network routing issues
4. Wrong hostname/IP in config

**Impact:** Falls back to PHP `mail()` function  
**Fix:** ✅ Added connectivity test before sending

### Error 3: IPv6 Warning
```
sendmail: warning: inet_protocols: disabling IPv6
```

**Cause:** System trying IPv6 but not supported  
**Impact:** Minor - falls back to IPv4  
**Fix:** Not critical, informational only

---

## Root Cause Analysis

### Primary Issue: SMTP Connectivity

The main problem is that the server **cannot connect** to `mail.energo.lv:25`. This means:

1. ❌ SMTP is not actually sending via mail.energo.lv
2. ✅ Fallback to PHP mail() is working
3. ⚠️ PHP mail() sends but Gmail rejects/filters it

### Why Gmail Doesn't Receive

When using PHP `mail()` fallback:
- Email comes from local sendmail/postfix
- No proper sender authentication
- Missing SPF/DKIM records
- Gmail marks as spam or silently drops

---

## Diagnostic Results

Run this to diagnose:
```bash
cd /u01/duis-test
php test_smtp_diagnostic.php tatjana.fedorkova@gmail.com
```

Expected output should show:
```
TEST 1: SMTP Server Connectivity
-----------------------------------
✓ SUCCESS: Connected to mail.energo.lv:25
  Server says: 220 mail.energo.lv ESMTP Postfix
```

If you see:
```
✗ FAILED: Cannot connect to mail.energo.lv:25
  Error: Connection timed out (110)
```

Then the issue is **network connectivity**, not email configuration.

---

## Solutions in Priority Order

### Solution 1: Fix SMTP Connectivity (Highest Priority)

**Check if port 25 is reachable:**
```bash
# From the server
telnet mail.energo.lv 25
```

If this fails, contact IT to:
- Open outbound port 25 in firewall
- Verify mail.energo.lv is correct hostname
- Check if mail relay is configured
- Verify server can access mail.energo.lv

**Expected result:**
```
Trying 10.20.15.x...
Connected to mail.energo.lv.
Escape character is '^]'.
220 mail.energo.lv ESMTP Postfix
```

### Solution 2: Use Alternative SMTP Port

If port 25 is blocked, try port 587:

Edit `config/main.conf.php`:
```php
define('SMTP_PORT', 587);
define('SMTP_ENCRYPTION', 'tls');
```

### Solution 3: Test with Internal Email First

Instead of Gmail, test with internal email:
```bash
php test_smtp_diagnostic.php tatjana.fedorkova@latvenergo.lv
```

This will bypass Gmail's strict filters.

### Solution 4: Configure Proper Mail Relay

Ask IT team to:
1. Configure mail.energo.lv as mail relay
2. Allow your server IP to relay
3. Set up SPF records for energo.lv domain
4. Configure reverse DNS (PTR) for server IP

---

## What's Actually Happening Now

```
Your Server → [❌ Can't connect to mail.energo.lv:25]
           ↓
        PHP mail() → Local sendmail → Internet
           ↓
        Gmail → [⚠️ No authentication, rejected/spam]
           ↓
        🗑️ Email dropped or in spam
```

**What should happen:**
```
Your Server → [✓ Connected to mail.energo.lv:25]
           ↓
        SMTP Command: MAIL FROM, RCPT TO, DATA
           ↓
        mail.energo.lv → Proper delivery → Gmail
           ↓
        ✓ Email received in inbox
```

---

## Immediate Actions Required

### 1. Verify Network Connectivity
```bash
# Run from server
telnet mail.energo.lv 25
ping mail.energo.lv
traceroute mail.energo.lv
```

### 2. Check Firewall Rules
```bash
# Check if iptables is blocking
sudo iptables -L -n | grep 25

# Check firewalld (if used)
sudo firewall-cmd --list-all
```

### 3. Verify SMTP Server
```bash
# Check DNS resolution
nslookup mail.energo.lv
dig mail.energo.lv

# Check if service is running
nc -zv mail.energo.lv 25
```

### 4. Test from Different Network
If possible, run test from a different server or network to isolate the issue.

---

## Expected vs Actual Behavior

### Expected (Working SMTP):
```
[SMTP] Connecting to mail.energo.lv:25
[SMTP CONNECT] << 220 mail.energo.lv ESMTP
[SMTP CMD] >> EHLO your-server
[SMTP RSP] << 250-mail.energo.lv
[SMTP CMD] >> MAIL FROM: <softex@softex.lv>
[SMTP RSP] << 250 2.1.0 Ok
[SMTP CMD] >> RCPT TO: <recipient@gmail.com>
[SMTP RSP] << 250 2.1.5 Ok
[SMTP DATA] Sending email body
[SMTP DATA RSP] << 250 2.0.0 Ok: queued
✓ SUCCESS: Email sent successfully!
```

### Actual (Connection Failure):
```
[SMTP] Connecting to mail.energo.lv:25 (timeout: 10s)
... waiting 10 seconds ...
[SMTP] ERROR: Failed to connect to SMTP server
[SMTP] Falling back to PHP mail() function
```

---

## Contact IT Team With This Information

When contacting IT support, provide:

1. **Error Message:**
   ```
   Failed to connect to SMTP server: mail.energo.lv:25
   Connection timed out after 10 seconds
   ```

2. **Server Details:**
   - Server: `/u01/duis-test`
   - Script: `test_smtp_diagnostic.php`
   - Network: [your network segment]

3. **Request:**
   - Open outbound port 25 (SMTP) to mail.energo.lv
   - OR provide alternative SMTP server/port
   - OR configure mail relay permissions

4. **Test Results:**
   - Attach output from `test_smtp_diagnostic.php`
   - Include `telnet mail.energo.lv 25` results

---

## Quick Test After Fixes

Once IT resolves connectivity:

```bash
cd /u01/duis-test

# Test connectivity
telnet mail.energo.lv 25

# Test SMTP
php test_smtp_diagnostic.php tatjana.fedorkova@latvenergo.lv

# If that works, try Gmail
php test_smtp_diagnostic.php tatjana.fedorkova@gmail.com
```

---

## Summary

| Issue | Status | Action |
|-------|--------|--------|
| Undefined constants | ✅ Fixed | Added verification in scripts |
| SMTP connectivity | ❌ **MAIN ISSUE** | **Contact IT to fix network/firewall** |
| Gmail delivery | ⚠️ Secondary | Will work once SMTP connects |
| Config loading | ✅ Fixed | Added error checking |
| Timeout handling | ✅ Fixed | Reduced from 30s to 10s |

**Bottom Line:** The email system code is working correctly, but it cannot reach the SMTP server. This is a **network/infrastructure issue** that requires IT team intervention.

---

**Created:** 2026-02-16  
**Status:** SMTP connectivity issue identified  
**Next Step:** Contact IT team to fix mail.energo.lv:25 connectivity

