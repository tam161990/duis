# SMTP Email Configuration Guide

## Pārskats (Overview)

DUIS sistēma tagad atbalsta SMTP e-pasta sūtīšanu ar elastīgu konfigurāciju, kas atbilst pašreizējām un nākotnes prasībām.

The DUIS system now supports SMTP email sending with flexible configuration that meets current and future requirements.

---

## Pašreizējā Konfigurācija (Current Configuration)

**Aktīvie iestatījumi failā `config/main.conf.php`:**

```php
// SMTP serveris
define('SMTP_HOST', 'mail.energo.lv');

// SMTP ports
define('SMTP_PORT', 25);

// Šifrēšana (tukša vērtība = bez šifrēšanas)
define('SMTP_ENCRYPTION', '');

// Autentifikācija (false = nav nepieciešama)
define('SMTP_AUTH', false);

// Lietotājvārds (tukšs, ja autentifikācija izslēgta)
define('SMTP_USERNAME', '');

// Parole (tukša, ja autentifikācija izslēgta)
define('SMTP_PASSWORD', '');

// Sūtītāja vārds
define('SMTP_FROM_NAME', 'DUIS System');

// Sūtītāja e-pasts
define('EMAIL_FROM', 'softex@softex.lv');
```

---

## Nākotnes Konfigurācija MS Outlook (Future MS Outlook Configuration)

Kad notiek pāreja uz MS Outlook infrastruktūru, mainiet sekojošos parametrus:

### Ar TLS šifrēšanu (Recommended):
```php
define('SMTP_PORT', 587);
define('SMTP_ENCRYPTION', 'tls');
define('SMTP_AUTH', true);
define('SMTP_USERNAME', 'your-email@energo.lv');
define('SMTP_PASSWORD', 'your-password');
```

### Ar SSL šifrēšanu (Alternative):
```php
define('SMTP_PORT', 465);
define('SMTP_ENCRYPTION', 'ssl');
define('SMTP_AUTH', true);
define('SMTP_USERNAME', 'your-email@energo.lv');
define('SMTP_PASSWORD', 'your-password');
```

---

## Tehniskā Informācija (Technical Information)

### Klases un Faili (Classes and Files)

1. **`SmtpMailer.class`** - Galvenā SMTP klase (Main SMTP class)
   - Atbalsta SMTP autentifikāciju (Supports SMTP authentication)
   - Atbalsta TLS/SSL šifrēšanu (Supports TLS/SSL encryption)
   - UTF-8 atbalsts latviešu valodas rakstzīmēm (UTF-8 support for Latvian characters)
   - Automātiska atgriešanās pie PHP `mail()` funkcijas, ja SMTP neizdodas (Automatic fallback to PHP mail() if SMTP fails)

2. **`email.class`** - E-pasta servisa klase (Email service class)
   - Izmanto `SmtpMailer` e-pastu sūtīšanai (Uses SmtpMailer for sending emails)
   - Automātiski apstrādā saņēmēju sarakstus (Automatically processes recipient lists)
   - Logu vešanu RBF aktu statusa izmaiņām (Logging for RBF act status changes)

### Funkcionalitāte (Functionality)

#### 1. Savienojums (Connection)
- Izveido socket savienojumu ar SMTP serveri (Establishes socket connection to SMTP server)
- Atbalsta STARTTLS komandu TLS šifrēšanai (Supports STARTTLS command for TLS encryption)
- Automātiska EHLO/HELO protokola vadība (Automatic EHLO/HELO protocol handling)

#### 2. Autentifikācija (Authentication)
- AUTH LOGIN metode (AUTH LOGIN method)
- Base64 kodēti akreditācijas dati (Base64 encoded credentials)
- Automātiska kļūdu apstrāde (Automatic error handling)

#### 3. E-pasta sūtīšana (Email Sending)
- MAIL FROM, RCPT TO, DATA SMTP komandas (MAIL FROM, RCPT TO, DATA SMTP commands)
- UTF-8 kodēts saturs un temati (UTF-8 encoded content and subjects)
- Atbalsts vairākiem saņēmējiem (Support for multiple recipients)

#### 4. Kļūdu apstrāde (Error Handling)
- Detalizēta kļūdu logošana (Detailed error logging)
- Automātiska atgriešanās pie PHP mail() (Automatic fallback to PHP mail())
- SMTP atbilžu kodu validācija (SMTP response code validation)

---

## Testēšana (Testing)

### 1. Pārbaudiet pašreizējo konfigurāciju (Test current configuration):

```php
// Test script: test_email.php
require_once('config/main.conf.php');
require_once('libs/email/SmtpMailer.class');

$mailer = new SmtpMailer();
$mailer->setDebug(true);

$result = $mailer->send(
    'test@example.com',
    'Test Email',
    'This is a test message',
    EMAIL_FROM,
    SMTP_FROM_NAME
);

echo $result ? "SUCCESS" : "FAILED: " . $mailer->getLastError();
```

### 2. Pārbaudiet logus (Check logs):
```bash
tail -f logs/wh.log
```

---

## Konfigurācijas Maiņa (Configuration Changes)

### Solis 1: Atveriet konfigurācijas failu (Step 1: Open configuration file)
```bash
nano config/main.conf.php
```

### Solis 2: Mainiet nepieciešamos parametrus (Step 2: Change required parameters)
Skatīties "Nākotnes Konfigurācija MS Outlook" sadaļu augstāk (See "Future MS Outlook Configuration" section above)

### Solis 3: Saglabājiet un pārstartējiet sistēmu (Step 3: Save and restart system)
```bash
# Pārlādējiet web serveri
sudo service apache2 restart
# vai
sudo systemctl restart apache2
```

---

## Atbalstītās Konfigurācijas (Supported Configurations)

| Konfigurācija | Ports | Šifrēšana | Autentifikācija | Izmantošana |
|--------------|-------|-----------|----------------|-------------|
| Pašreizējā   | 25    | Nav       | Nav            | mail.energo.lv (local relay) |
| MS Outlook (TLS) | 587 | TLS     | Jā             | Office 365 / Exchange |
| MS Outlook (SSL) | 465 | SSL     | Jā             | Office 365 / Exchange |

---

## Bieži Uzdotie Jautājumi (FAQ)

### J: Vai vecā konfigurācija joprojām darbosies?
**A:** Jā, sistēma automātiski izmanto SMTP, bet ja tas neizdodas, atgriežas pie PHP `mail()` funkcijas.

### Q: Will the old configuration still work?
**A:** Yes, the system automatically uses SMTP, but falls back to PHP `mail()` function if SMTP fails.

---

### J: Kā es zinu, vai e-pasts tika nosūtīts veiksmīgi?
**A:** Pārbaudiet logu failu `logs/wh.log`, kur tiek reģistrētas visas SMTP operācijas.

### Q: How do I know if an email was sent successfully?
**A:** Check the log file `logs/wh.log` where all SMTP operations are logged.

---

### J: Vai es varu izmantot citu SMTP serveri?
**A:** Jā, vienkārši mainiet `SMTP_HOST` konstanti `config/main.conf.php` failā.

### Q: Can I use a different SMTP server?
**A:** Yes, simply change the `SMTP_HOST` constant in `config/main.conf.php` file.

---

### J: Kas notiek, ja SMTP serveris nav pieejams?
**A:** Sistēma automātiski izmanto PHP `mail()` funkciju kā rezerves risinājumu.

### Q: What happens if the SMTP server is unavailable?
**A:** The system automatically uses PHP `mail()` function as a fallback solution.

---

## Kontakti (Support)

Ja rodas problēmas ar e-pasta sūtīšanu, pārbaudiet:
If you experience issues with email sending, check:

1. SMTP servera pieejamību (SMTP server availability)
2. Ugunsmūra iestatījumus (Firewall settings)
3. Logu failus `/logs/wh.log` (Log files)
4. PHP konfigurāciju `php.ini` (PHP configuration)

---

## Izmaiņu Vēsture (Change History)

**2026-02-16** - DUIS-549
- Pievienota SMTP atbalsts (Added SMTP support)
- Pievienota elastīga konfigurācija (Added flexible configuration)
- Pievienots TLS/SSL šifrēšanas atbalsts (Added TLS/SSL encryption support)
- Pievienota autentifikācijas atbalsts (Added authentication support)
- Pievienota automātiska atgriešanās mehānisms (Added automatic fallback mechanism)

