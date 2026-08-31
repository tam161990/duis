-- ============================================================================
-- RBF Email Configuration Checker
-- ============================================================================
-- This script helps verify that contractor email addresses are configured
-- correctly for RBF act notifications
-- Note: After DUIS-593, emails are stored in kl_rbf_du_vv (VV-level)
-- ============================================================================

-- 1. Check all contractors and their email addresses (NEW LOCATION - VV-level)
SELECT 
    '=== VV ENTRIES WITH EMAIL ADDRESSES (NEW LOCATION) ===' AS info;

SELECT 
    d.RBDU_ID AS 'Contractor ID',
    d.RBDU_KODS AS 'Code',
    d.RBDU_NOSAUKUMS AS 'Name',
    vv.RBDV_VV_NUMURS AS 'VV Number',
    vv.RBDV_KONTAKTI AS 'Email Addresses (VV-level)',
    d.RBDU_IR_AKTIVS AS 'Active (1/0)',
    CASE 
        WHEN vv.RBDV_KONTAKTI IS NULL OR vv.RBDV_KONTAKTI = '' THEN '⚠ NO EMAIL'
        WHEN vv.RBDV_KONTAKTI LIKE '%@%' THEN '✓ Has Email'
        ELSE '⚠ Invalid Format'
    END AS 'Status'
FROM kl_rbf_darbuznemeji d
LEFT JOIN kl_rbf_du_vv vv ON d.RBDU_ID = vv.RBDV_RBDU_ID
ORDER BY d.RBDU_IR_AKTIVS DESC, d.RBDU_ID, vv.RBDV_VV_NUMURS;

-- 2. Check contractors with OLD email configuration (backward compatibility)
SELECT 
    '=== CONTRACTORS WITH OLD EMAIL CONFIGURATION (SHOULD BE MIGRATED) ===' AS info;

SELECT 
    RBDU_ID AS 'ID',
    RBDU_KODS AS 'Code',
    RBDU_NOSAUKUMS AS 'Name',
    RBDU_KONTAKTI AS 'Email Addresses (OLD LOCATION)',
    RBDU_IR_AKTIVS AS 'Active (1/0)',
    CASE 
        WHEN RBDU_KONTAKTI IS NULL OR RBDU_KONTAKTI = '' THEN 'OK - No old emails'
        WHEN RBDU_KONTAKTI LIKE '%@%' THEN '⚠ NEEDS MIGRATION TO VV-LEVEL'
        ELSE '⚠ Invalid Format'
    END AS 'Status'
FROM kl_rbf_darbuznemeji
WHERE RBDU_KONTAKTI IS NOT NULL AND RBDU_KONTAKTI != ''
ORDER BY RBDU_IR_AKTIVS DESC, RBDU_ID;

-- 3. Check VV entries WITHOUT email addresses (these won't receive notifications)
SELECT 
    '=== VV ENTRIES WITHOUT EMAIL (WILL NOT RECEIVE NOTIFICATIONS) ===' AS warning;

SELECT 
    d.RBDU_KODS AS 'Code',
    d.RBDU_NOSAUKUMS AS 'Name',
    vv.RBDV_VV_NUMURS AS 'VV Number',
    d.RBDU_IR_AKTIVS AS 'Active',
    CASE 
        WHEN d.RBDU_KONTAKTI IS NOT NULL AND d.RBDU_KONTAKTI != '' THEN '✓ Has old email (fallback)'
        ELSE '⚠ NO EMAILS AT ALL'
    END AS 'Fallback Status'
FROM kl_rbf_darbuznemeji d
INNER JOIN kl_rbf_du_vv vv ON d.RBDU_ID = vv.RBDV_RBDU_ID
WHERE (vv.RBDV_KONTAKTI IS NULL OR vv.RBDV_KONTAKTI = '')
  AND d.RBDU_IR_AKTIVS = 1
ORDER BY d.RBDU_KODS, vv.RBDV_VV_NUMURS;

-- 4. Check recent RBF acts and their associated contractors
SELECT 
    '=== RECENT RBF ACTS AND THEIR CONTRACTORS ===' AS info;

SELECT 
    a.RAKT_ID AS 'Act ID',
    a.RAKT_NUM_PILNS AS 'Act Number',
    a.RAKT_KWOI_KODS AS 'Contractor Code',
    d.RBDU_NOSAUKUMS AS 'Contractor Name',
    GROUP_CONCAT(DISTINCT vv.RBDV_KONTAKTI SEPARATOR '; ') AS 'VV Emails (NEW)',
    d.RBDU_KONTAKTI AS 'Old Emails',
    a.RAKT_STATUS AS 'Status',
    a.RAKT_CREATED AS 'Created',
    CASE 
        WHEN GROUP_CONCAT(DISTINCT vv.RBDV_KONTAKTI) IS NOT NULL THEN '✓ VV-level email configured'
        WHEN d.RBDU_KONTAKTI IS NOT NULL AND d.RBDU_KONTAKTI != '' THEN '⚠ Using old email (fallback)'
        ELSE '⚠ NO EMAIL CONFIGURED'
    END AS 'Email Status'
FROM AKTI a
LEFT JOIN kl_rbf_darbuznemeji d ON a.RAKT_KWOI_KODS = d.RBDU_KODS
LEFT JOIN kl_rbf_du_vv vv ON d.RBDU_ID = vv.RBDV_RBDU_ID
WHERE a.RAKT_IS_RBF = 1
GROUP BY a.RAKT_ID
ORDER BY a.RAKT_ID DESC
LIMIT 10;

-- 5. Sample email format examples
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

-- 6. Check RBF audit records for email-related status changes
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
-- INSTRUCTIONS FOR CONFIGURING EMAIL ADDRESSES
-- ============================================================================
-- 
-- NEW LOCATION (DUIS-593): Emails are now stored at VV-level in kl_rbf_du_vv
-- 
-- To add email to a VV entry:
-- 
-- UPDATE kl_rbf_du_vv 
-- SET RBDV_KONTAKTI = 'email@example.com'
-- WHERE RBDV_VV_NUMURS = 'VV_NUMBER_HERE';
--
-- For multiple emails:
--
-- UPDATE kl_rbf_du_vv 
-- SET RBDV_KONTAKTI = 'email1@example.com; email2@example.com; email3@example.com'
-- WHERE RBDV_VV_NUMURS = 'VV_NUMBER_HERE';
--
-- OLD LOCATION (backward compatibility): kl_rbf_darbuznemeji.RBDU_KONTAKTI
-- This is used as fallback if VV-level emails are not configured
--
-- ============================================================================

