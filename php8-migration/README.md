# PHP 8.3.36 Migration Guide for DUIS

## 📋 Migration Status

### ✅ Completed Steps
1. **PHP 8.3.36 Installation Verified**
   - Location: `C:\php-8.3.36\`
   - Version: PHP 8.3.36 (ZTS, Thread Safe)
   - Apache Module: `php8apache2_4.dll` ✓

2. **Configuration Migrated**
   - php.ini migrated from PHP 7.3.8
   - All critical directives copied:
     - memory_limit: 512M
     - max_execution_time: 30
     - upload_max_filesize: 2M
     - date.timezone: Europe/Berlin
   - Extensions migrated and fixed:
     - gd2 → gd (renamed in PHP 8)
     - php_openssl.dll → openssl
     - php_ftp.dll → ftp

3. **Test Server Running**
   - Built-in PHP server: `http://localhost:8083/`
   - Status page: `http://localhost:8083/php8_status.php`

---

## 🚀 Current Testing Phase

### Test Using Built-in PHP Server

The PHP 8.3 built-in web server is currently running on port 8083.

**Test URLs:**
- Status check: http://localhost:8083/php8_status.php
- Main application: http://localhost:8083/

**What to test:**
1. ✅ PHP version and configuration
2. ✅ Database connection
3. ✅ Login functionality
4. ✅ RBF module (acts, works)
5. ✅ Excel import/export
6. ✅ Reports generation

**Stop the test server:**
- Close the PHP console window
- Or press Ctrl+C in the terminal

---

## 📝 Next Step: Configure Apache

Once you've verified the application works with the built-in server, configure Apache:

### Switch Apache to PHP 8.3

```cmd
cd C:\xampp\WORKS\duis-dev\php8-migration
switch-to-php8.bat
```

This will:
1. Stop Apache
2. Backup current httpd.conf
3. Update LoadModule to use PHP 8.3
4. Update PHPIniDir to C:/php-8.3.36
5. Test configuration
6. Start Apache with PHP 8.3

### Rollback to PHP 7.3 (if needed)

```cmd
cd C:\xampp\WORKS\duis-dev\php8-migration
rollback-to-php73.bat
```

This will:
1. Stop Apache
2. Restore httpd.conf from backup
3. Start Apache with PHP 7.3.8

---

## ⚠️ Known PHP 8 Breaking Changes

### Functions Removed in PHP 8.0
- `each()` - use `foreach` or array functions
- `create_function()` - use anonymous functions or closures
- `split()` - use `explode()` or `preg_split()`
- `ereg()` / `eregi()` - use `preg_match()`

### Changes That May Affect Code
1. **Stricter type checking** - less implicit type juggling
2. **Named arguments** - parameter order matters less
3. **Nullsafe operator** - `$obj?->method()`
4. **Match expression** - stricter alternative to switch
5. **Constructor property promotion** - shorter syntax

### Common Issues to Watch For
- Fatal errors on undefined variables (previously warnings)
- Fatal errors on undefined array keys (previously notices)
- Type mismatches in function calls
- Changes to string/number comparison

---

## 📊 Migration Scripts

### Directory Structure
```
C:\xampp\WORKS\duis-dev\php8-migration\
│
├── configure-apache-php8.ps1     # Apache configuration script
├── switch-to-php8.bat             # Switch to PHP 8.3
└── rollback-to-php73.bat          # Rollback to PHP 7.3
```

### PHP Installation
```
C:\php-8.3.36\
├── php.exe
├── php8apache2_4.dll
├── php.ini
└── ext\                           # Extensions directory
```

---

## 🐛 Troubleshooting

### Apache won't start with PHP 8.3

**Check 1: Verify PHP module**
```cmd
dir C:\php-8.3.36\php8apache2_4.dll
```

**Check 2: Test Apache config**
```cmd
C:\xampp\apache\bin\httpd.exe -t
```

**Check 3: Check Apache error log**
```
C:\xampp\apache\logs\error.log
```

**Check 4: Verify php.ini exists**
```cmd
dir C:\php-8.3.36\php.ini
```

### Application shows errors

**Check PHP error log:**
```
C:\php-8.3.36\error.log
```

**Check Apache error log:**
```
C:\xampp\apache\logs\error.log
```

**Common fixes:**
1. Check extension_dir in php.ini
2. Verify all required extensions are loaded: `php -m`
3. Check file permissions
4. Review deprecated function usage

---

## 📞 Quick Commands

### Check PHP Version (CLI)
```cmd
C:\php-8.3.36\php.exe -v
```

### List Loaded Extensions
```cmd
C:\php-8.3.36\php.exe -m
```

### Test PHP Script
```cmd
C:\php-8.3.36\php.exe -f test_php8_compatibility.php
```

### View php.ini Location
```cmd
C:\php-8.3.36\php.exe --ini
```

---

## 📈 Migration Timeline

1. **✅ Installation Verified** - PHP 8.3.36 installed
2. **✅ Configuration Migrated** - php.ini ready
3. **🔄 Testing Phase** - Currently testing with built-in server
4. **⏳ Apache Configuration** - Pending user approval
5. **⏳ Production Testing** - After Apache is configured
6. **⏳ Code Fixes** - If incompatibilities found
7. **⏳ Final Verification** - Complete system test

---

## 📝 Notes

- **Backup Strategy:** All configurations are backed up with timestamps
- **Rollback:** Can switch back to PHP 7.3 at any time
- **Zero Downtime:** Test with built-in server before switching Apache
- **Data Safety:** No database changes required for PHP upgrade

---

Generated: <?php echo date('Y-m-d H:i:s'); ?>
PHP Version: <?php echo phpversion(); ?>
