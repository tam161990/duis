-- ============================================================================
-- RBF Email Configuration Checker
-- ============================================================================
-- This script helps verify that contractor email addresses are configured
-- correctly for RBF act notifications
-- ============================================================================

-- 1. Check all contractors and their email addresses
SELECT 
    '=== CONTRACTORS WITH EMAIL ADDRESSES ===' AS info;

SELECT 
    RBDU_ID AS 'ID',
    RBDU_KODS AS 'Code',
    RBDU_NOSAUKUMS AS 'Name',
    RBDU_VV_VEIDS AS 'Type (U/C)',
    RBDU_KONTAKTI AS 'Email Addresses',
    RBDU_IR_AKTIVS AS 'Active (1/0)',
    CASE 
        WHEN RBDU_KONTAKTI IS NULL OR RBDU_KONTAKTI = '' THEN '⚠ NO EMAIL'
        WHEN RBDU_KONTAKTI LIKE '%@%' THEN '✓ Has Email'
        ELSE '⚠ Invalid Format'
    END AS 'Status'
FROM kl_rbf_darbuznemeji
ORDER BY RBDU_IR_AKTIVS DESC, RBDU_ID;

-- 2. Check contractors WITHOUT email addresses (these won't receive notifications)
SELECT 
    '=== CONTRACTORS WITHOUT EMAIL (WILL NOT RECEIVE NOTIFICATIONS) ===' AS warning;

SELECT 
    RBDU_KODS AS 'Code',
    RBDU_NOSAUKUMS AS 'Name',
    RBDU_IR_AKTIVS AS 'Active'
FROM kl_rbf_darbuznemeji
WHERE (RBDU_KONTAKTI IS NULL OR RBDU_KONTAKTI = '')
  AND RBDU_IR_AKTIVS = 1;

-- 3. Check recent RBF acts and their associated contractors
SELECT 
    '=== RECENT RBF ACTS AND THEIR CONTRACTORS ===' AS info;

SELECT 
    a.RAKT_ID AS 'Act ID',
    a.RAKT_NUM_PILNS AS 'Act Number',
    a.RAKT_KWOI_KODS AS 'Contractor Code',
    d.RBDU_NOSAUKUMS AS 'Contractor Name',
    d.RBDU_KONTAKTI AS 'Email Addresses',
    a.RAKT_STATUS AS 'Status',
    a.RAKT_CREATED AS 'Created',
    CASE 
        WHEN d.RBDU_KONTAKTI IS NULL OR d.RBDU_KONTAKTI = '' THEN '⚠ NO EMAIL CONFIGURED'
        WHEN d.RBDU_KONTAKTI LIKE '%@%' THEN '✓ Email OK'
        ELSE '⚠ Check Format'
    END AS 'Email Status'
FROM AKTI a
LEFT JOIN kl_rbf_darbuznemeji d ON a.RAKT_KWOI_KODS = d.RBDU_KODS
WHERE a.RAKT_IS_RBF = 1
ORDER BY a.RAKT_ID DESC
LIMIT 10;

-- 4. Sample email format examples
SELECT 
    '=== EMAIL FORMAT EXAMPLES ===' AS info;

SELECT 
    'Single email' AS 'Format',
    'info@example.com' AS 'Example',
    'Correct format for one email address' AS 'Note'
UNION ALL
SELECT 
    'Multiple emails',
    'email1@example.com; email2@example.lv; email3@test.com',
    'Multiple emails separated by semicolon (;)'
UNION ALL
SELECT 
    'With spaces',
    'email1@example.com ; email2@example.lv',
    'Spaces around semicolons are OK (trimmed automatically)';

-- 5. Check RBF audit records for email-related status changes
SELECT 
    '=== RECENT STATUS CHANGES (SHOULD TRIGGER EMAILS) ===' AS info;

SELECT 
    h.RAKH_RAKT_ID AS 'Act ID',
    a.RAKT_NUM_PILNS AS 'Act Number',
    h.RAKH_OLD_STATUS AS 'Old Status',
    h.RAKH_NEW_STATUS AS 'New Status',
    h.RAKH_DATE AS 'Change Date',
    h.RAKH_RLTT_ID AS 'User ID',
    CONCAT(u.RLTT_VARDS, ' ', u.RLTT_UZVARDS) AS 'Changed By'
FROM aktu_status_history h
LEFT JOIN AKTI a ON h.RAKH_RAKT_ID = a.RAKT_ID
LEFT JOIN lietotaji u ON h.RAKH_RLTT_ID = u.RLTT_ID
WHERE a.RAKT_IS_RBF = 1
ORDER BY h.RAKH_DATE DESC
LIMIT 10;

-- ============================================================================
-- INSTRUCTIONS FOR FIXING EMAIL ISSUES
-- ============================================================================
-- 
-- If a contractor has no email configured:
-- 
-- UPDATE kl_rbf_darbuznemeji 
-- SET RBDU_KONTAKTI = 'email@example.com'
-- WHERE RBDU_KODS = 'contractor_code';
--
-- For multiple emails:
--
-- UPDATE kl_rbf_darbuznemeji 
-- SET RBDU_KONTAKTI = 'email1@example.com; email2@example.com; email3@example.com'
-- WHERE RBDU_KODS = 'contractor_code';
--
-- ============================================================================

