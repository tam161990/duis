-- DUIS-549: Add RBF menu structure with submenus
-- This script adds Latvian text translations for the new RBF catalog menu items and creates RBF Territories table

-- ============================================================================
-- Text translations for menu items
-- ============================================================================

-- Insert text code for main RBF menu item
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF', 'RBF');

-- Insert text code for RBF Territories submenu
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_TERRITORIES', 'RBF teritorijas');

-- Insert text code for RBF Employees submenu
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_EMPLOYEES', 'Darbuzņēmēji');

-- Insert text code for RBF Calculations submenu
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_CALCULATIONS', 'Kalkulācijas');

-- Insert text code for error when RBF territory code already exists
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ERROR_EXISTS_RBF_TERRITORY_CODE', 'RBF teritorija ar šādu kodu jau eksistē!');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('DID_NAME', 'DID nosaukums');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_DID_NAME', 'DID nosaukums');

-- Insert text code for error when RBF employee code already exists
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ERROR_EXISTS_RBF_EMPLOYEE_CODE', 'Darbuzņēmējs ar šādu kodu jau eksistē!');

-- Insert text code for error when RBF employee agreement number already exists
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ERROR_EXISTS_RBF_EMPLOYEE_VV_NUMBER', 'Šis vispārīgās vienošanās numurs jau eksistē!');

-- Insert text codes for RBF Employee form fields
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_VV_TYPE', 'Vispārīgās vienošanās veids');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_VV_NUMBER', 'Vispārīgās vienošanās nr.');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_CONTACTS', 'Kontakti');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_SERVICE_TERRITORY', 'Apkalpes teritorija');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_VV_TYPE_MAINTENANCE', 'Uzturēšana');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_VV_TYPE_ROAD_SURFACE', 'Ceļa segumi');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_MULTISELECT_HELP', 'Ctrl+klikšķis lai izvēlētos vairākus');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_ADD_VV', 'Pievienot VV');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_VV_ENTRIES', 'VV numuri un teritorijas');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_TERRITORY', 'Teritorija');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_DID_NAME', 'DID nosaukums');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_REMOVE', 'Dzēst');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ERROR_MIN_ONE_VV', 'Jāpievieno vismaz viens VV numurs!');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_CONTACTS_HELP', 'Vairākus kontaktus atdalīt ar ";"');

-- RBF Kalkulācija text codes
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_CALCULATION_INFO', 'RBF kalkulācijas informācija');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_SHIFRS', 'Šifrs');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_UNIT_OF_MEASURE', 'Mērvienība');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_DESCRIPTION', 'Apraksts');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_EMPLOYEE_CODE', 'Darbuzņēmējs');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_SECTION', 'Nodaļa');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_PRICE', 'Cena');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ERROR_EXISTS_RBF_CALCULATION', 'Kalkulācija ar šādu kombināciju (VV numurs, Šifrs, Nodaļa) jau eksistē!');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_CALC_IMPORT', 'RBF Kalkulācijas');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('REQUIREMENTS_RBF_KALKULATION', '<h3>Kalkulācijas importal lūdzam izmantot daus Excel 97-2003 formātā</h3>
        <table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr> 
        <tr><td>Kalkulācijas šifrs</td><td>+</td><td>Kalkulācijas šifrs. Unikāls. Var saturēt tikai sekojošus simbolus `0`-`9`. Maksimāli 5 simboli.</td></tr>
        <tr><td>Kalkulācijas nosaukums</td><td>+</td><td>Kalkulācijas nosaukums. Maksimāli 150 simboli.</td></tr>
		<tr><td>Cena</td><td>+</td><td>Cipars formātā [xxxxx.xx].</td></tr>
        <tr><td>Mērvienība</td><td>+</td><td>Kalkulācijas mērvienība. Maksimāli 15 simboli.</td></tr>
        <tr><td>Apraksts</td><td>+</td><td>Kalkulācijas apraksts. Maksimāli 2000 simboli.</td></tr>
        <tr><td>Darbuzņēmējs</td><td>+</td><td>Darbuzņēmēja identifikators. Cipars.</td></tr>
        <tr><td>Līguma Nr.</td><td>+</td><td>Vispārīgās vienošanās nr. Maksimāli 20 simboli.</td></tr>
        <tr><td>Nodaļ</td><td>+</td><td>Teritorijas kods. Cipars formātā [xxxxx].</td></tr>        
       </table>');

-- Add RBF Kalkulācija to import catalog options
INSERT INTO `KL_REF_KODI` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`)
VALUES
('IMPORTS', 'RBF_KALKULATION', 'RBF Kalkulācijas');

-- Add RBF access field to user table
ALTER TABLE `lietotaji` ADD COLUMN `RLTT_IR_RBF` INT(1) DEFAULT 0 AFTER `RLTT_IR_PPA`;

-- Add text for RBF access checkbox
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_ACCESS', 'Piekļūve RBF aktiem');

-- ============================================================================
-- RBF Acts - Add new fields to AKTI table
-- ============================================================================

-- Add field to mark if expenses should be capitalized
ALTER TABLE `AKTI` ADD COLUMN `RAKT_CAPITALIZED` TINYINT(1) NULL DEFAULT NULL AFTER `RAKT_IS_AUTO`;

-- Add field to mark RBF acts
ALTER TABLE `AKTI` ADD COLUMN `RAKT_IS_RBF` TINYINT(1) NOT NULL DEFAULT 0 AFTER `RAKT_CAPITALIZED`;

-- ============================================================================
-- Text translations for RBF Acts
-- ============================================================================

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_ACT', 'RBF Akts');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_ACT_INFO', 'RBF akta informācija');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_EMPLOYEE', 'Darbuzņēmējs');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_AUTHOR', 'Autors');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_ACT_TYPE', 'Akta veids');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_DEPARTMENT', 'RBF nodaļa');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_ORDER_ID', 'Pasūtījuma ID');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_SIGNING_METHOD', 'Parakstīšanas veids');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORK_TITLE', 'Darba nosaukums (izdrukām)');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_NOTES', 'Piezīmes');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_CAPITALIZE', 'Izmaksas kapitalizē');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_STATUS', 'Statuss');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORKS', 'Darbi');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_ATTACHMENTS', 'Pielikumi');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_STATUS_HISTORY', 'Statusa vēsture');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORKS_EMPTY', 'Saglabājiet aktu, lai pievienotu darbus');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_ATTACHMENTS_EMPTY', 'Saglabājiet aktu, lai pievienotu pielikumus');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_STATUS_HISTORY_EMPTY', 'Nav statusa vēstures');
--
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_AUTO_WORKS_INFO', 'Automātiski importēti darbi');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_AUTO_WORKS_INFO_DESC', 'Šie darbi tika automātiski importēti no Excel faila un ir tikai skatāmi. Lai veiktu izmaiņas, lūdzu, augšupielādējiet jaunu Excel failu ar atjauninātiem datiem.');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_AUTO_WORKS_EMPTY', 'Nav importētu darbu');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORK_NO', 'Nr.');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORK_ORDER_NUMBER', 'Uzturēšanas darba numurs');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORK_CALC_CODE', 'Kalkulāciju kategorijas šifrs');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORK_MMS_CODE', 'MMS nosacījums');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORK_MMS_TITLE', 'MMS Darbība/Nosacījums');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORK_STATUS', 'Darbības statuss');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORK_NORMA', 'C.st.');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORK_PLAN_DATE', 'Izpildes datums');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORK_APPROVE_DATE', 'Apstiprināšanas datums');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORK_TOTAL', 'Kopā');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORK_RECORDS', 'ieraksti');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_WORK_PROCESS_ERROR', 'Darbs statusā "Novēršana" nevar tikt iekļauts Starpaktā');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('NO_FILES', 'Nav pielikumu');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_SUBMIT_FOR_APPROVAL', 'Nodot saskaņošanai');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_APPROVE', 'Apstiprināt');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_RETURN', 'Atgriezt');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('RBF_ACT_NUMBER', 'Akta numurs');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('STATUS_INSERT', 'Ievads');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('CONFIRM_EXPORT', 'Vai tiešām vēlaties nodot aktu saskaņošanai?');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('CONFIRM_ACCEPT', 'Vai tiešām vēlaties apstiprināt aktu?');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('CONFIRM_RETURN', 'Vai tiešām vēlaties atgriezt aktu?');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('ACT_SUBMITTED_FOR_APPROVAL', 'Akts nodots saskaņošanai');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('ACT_APPROVED', 'Akts apstiprināts');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('ACT_RETURNED', 'Akts atgriezts');
 
 
  
CREATE TABLE `kl_rbf_teritorijas` (
	`RBTR_ID` INT(11) NOT NULL AUTO_INCREMENT,
    `RBTR_KODS` VARCHAR(10) NOT NULL COLLATE 'utf8_latvian_ci', -- Kods
	`RBTR_NOSAUKUMS` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci', -- Nosaukums
	`RBTR_DID_NOSAUKUMS` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci', -- DID nosaukums
	`RBTR_IR_AKTIVS` TINYINT(1) NOT NULL DEFAULT 1, -- Aktīvs (1/0)
	PRIMARY KEY (`RBTR_ID`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM;


CREATE TABLE `kl_rbf_darbuznemeji` (
	`RBDU_ID` INT(11) NOT NULL AUTO_INCREMENT,
    `RBDU_KODS` VARCHAR(11) NOT NULL COLLATE 'utf8_latvian_ci', -- Kods
	`RBDU_NOSAUKUMS` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci', -- Nosaukums
    `RBDU_VV_VEIDS` CHAR(1) NOT NULL COLLATE 'utf8_latvian_ci', -- Vispārīgās vienošanās veids (U=Uzturēšana, C=Ceļa segumi)
    `RBDU_KONTAKTI` VARCHAR(500) NULL COLLATE 'utf8_latvian_ci', -- Kontakti
    `RBDU_IR_AKTIVS` TINYINT(1) NOT NULL DEFAULT 1, -- Aktīvs (1/0)
	PRIMARY KEY (`RBDU_ID`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM;

CREATE TABLE `kl_rbf_du_vv` (    
	`RBDV_ID` INT(11) NOT NULL AUTO_INCREMENT,
	`RBDV_RBDU_ID` INT(11) NOT NULL, -- Darbuzņēmēja ID
	`RBDV_VV_NUMURS` VARCHAR(15) NOT NULL COLLATE 'utf8_latvian_ci', -- Vispārīgās vienošanās nr.
	`RBDV_RBTR_ID` INT(11) NOT NULL, -- Teritorijas ID
	PRIMARY KEY (`RBDV_ID`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM;

CREATE TABLE `kl_rbf_kalkulacija` (
	`RBKL_ID` INT(11) NOT NULL AUTO_INCREMENT, 
	`RBKL_SHIFRS` CHAR(5) NOT NULL COLLATE 'utf8_latvian_ci', -- Šifrs
	`RBKL_NOSAUKUMS` VARCHAR(150) NOT NULL COLLATE 'utf8_latvian_ci', -- Nosaukums
	`RBKL_MERVIENIBA` VARCHAR(15) NOT NULL COLLATE 'utf8_latvian_ci', -- Mērvienība
	`RBKL_APRAKSTS` TEXT NULL DEFAULT NULL COLLATE 'utf8_latvian_ci', -- Apraksts
	`RBKL_RBDU_KODS` VARCHAR(13) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci', -- Darbuzņēmējs
	`RBKL_VV_NUMBER` VARCHAR(20) NOT NULL COLLATE 'utf8_latvian_ci', -- Vispārīgās vienošanās nr.
	`RBKL_RBTR_CODE` VARCHAR(10) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci', -- Teritorijas kods (Nodaļa)
	`RBKL_CENA` FLOAT(7,2) NOT NULL,	-- Cena
	`RBKL_IR_AKTIVS` TINYINT(1) NOT NULL DEFAULT 1, -- Ir aktīvs
	`RBKL_CREATOR` INT(11) NULL DEFAULT NULL, -- Importa veiceis
	`RBKL_CREATED` DATETIME NOT NULL DEFAULT current_timestamp(), -- Importa daums
	`RBKL_EDITOR` INT(11) NULL DEFAULT NULL, -- Laboja lietotājs
	`RBKL_EDITED` DATETIME NOT NULL DEFAULT current_timestamp(), -- Labošanas datums
	PRIMARY KEY (`RBKL_ID`),
	UNIQUE INDEX `U_KKAL_SHIFRS` (`RBKL_VV_NUMBER`, `RBKL_SHIFRS`, `RBKL_RBTR_CODE`),
	INDEX `IX_RBKL_SHIFRS` (`RBKL_SHIFRS`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM;

-- Sample data for testing RBF functionality
-- Insert sample territories
INSERT INTO `kl_rbf_teritorijas` (`RBTR_KODS`, `RBTR_NOSAUKUMS`, `RBTR_DID_NOSAUKUMS`, `RBTR_IR_AKTIVS`) VALUES
('11223', 'Rīgas nodaļa', 'Vidzeme DID', 1),
('308313', 'Balvu nodaļa', 'Austrumu DID', 1),
('308314', 'Daugavpils nodaļa', 'Austrumu DID', 1);

-- Insert sample employees
INSERT INTO `kl_rbf_darbuznemeji` (`RBDU_KODS`, `RBDU_NOSAUKUMS`, `RBDU_VV_VEIDS`, `RBDU_KONTAKTI`, `RBDU_IR_AKTIVS`) VALUES
('40003524433', 'Delta EM SIA', 'U', 'info@deltaem.lv; +371 29123456', 1),
('41503087204', 'Ceļu būvnieks SIA', 'C', 'info@celubuvnieks.lv', 1);

-- Insert sample VV entries for employees
-- For Delta EM SIA (ID will be 1 if this is first insert)
INSERT INTO `kl_rbf_du_vv` (`RBDV_RBDU_ID`, `RBDV_VV_NUMURS`, `RBDV_RBTR_ID`) VALUES
(1, '300000/23-112', 1),
(1, '300000/24-113', 2);

-- For Ceļu būvnieks SIA (ID will be 2)
INSERT INTO `kl_rbf_du_vv` (`RBDV_RBDU_ID`, `RBDV_VV_NUMURS`, `RBDV_RBTR_ID`) VALUES
(2, '300000/25-113', 3),
(2, '300000/26-114', 1);

-- ============================================================================
-- Text translations for RBF Works Tab
-- ============================================================================

-- Insert text code for RBF Works Tab title
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_WORKS_TAB', 'Darbi');

-- Insert text code for Add Work button
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ADD_WORK', 'Pievienot darbu');

-- Insert text code for error when no calculation is selected
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ERROR_SELECT_CALCULATION', 'Lūdzu, izvēlieties vismaz vienu kalkulāciju!');

-- Insert text code for search code field
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('SEARCH_CODE', 'Meklēt pēc šifra');

-- Insert text code for calculations list
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('CALCULATIONS', 'Kalkulācijas');

-- Insert text code for Add to Act button
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ADD_TO_ACT', 'Pievienot aktam');

-- Insert text code for PDF generation error
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ERROR_GENERATING_PDF', 'Kļūda PDF faila izveidošanā');

-- Add text translations for file upload functionality
INSERT INTO `FMK_MESSAGES` (`code`, `text`) VALUES 
('FILE_SELECT', 'Izvēlieties failu')
ON DUPLICATE KEY UPDATE `text` = VALUES(`text`);

INSERT INTO `FMK_MESSAGES` (`code`, `text`) VALUES 
('FILE_DESCRIPTION', 'Apraksts')
ON DUPLICATE KEY UPDATE `text` = VALUES(`text`);

INSERT INTO `FMK_MESSAGES` (`code`, `text`) VALUES 
('FILE_ALLOWED_TYPES', 'Atļautie failu tipi')
ON DUPLICATE KEY UPDATE `text` = VALUES(`text`);

INSERT INTO `FMK_MESSAGES` (`code`, `text`) VALUES 
('BTN_UPLOAD', 'Augšupielādēt')
ON DUPLICATE KEY UPDATE `text` = VALUES(`text`);

INSERT INTO `FMK_MESSAGES` (`code`, `text`) VALUES 
('FILE_NAME', 'Faila nosaukums')
ON DUPLICATE KEY UPDATE `text` = VALUES(`text`);

INSERT INTO `FMK_MESSAGES` (`code`, `text`) VALUES 
('ACTIONS', 'Darbības')
ON DUPLICATE KEY UPDATE `text` = VALUES(`text`);

INSERT INTO `FMK_MESSAGES` (`code`, `text`) VALUES 
('FILE_OPERATION_SUCCESS', 'Faila operācija veiksmīgi izpildīta!')
ON DUPLICATE KEY UPDATE `text` = VALUES(`text`);

INSERT INTO `FMK_MESSAGES` (`code`, `text`) VALUES 
('FILE_UPLOAD_FAILED', 'Kļūda, augšupielādējot failu!')
ON DUPLICATE KEY UPDATE `text` = VALUES(`text`);

INSERT INTO `FMK_MESSAGES` (`code`, `text`) VALUES 
('FILE_INVALID_TYPE', 'Nederīgs faila tips! Atļautie tipi: docx, pdf, excel, gif, jpeg, png')
ON DUPLICATE KEY UPDATE `text` = VALUES(`text`);

INSERT INTO `FMK_MESSAGES` (`code`, `text`) VALUES 
('FILE_NOT_SELECTED', 'Lūdzu, izvēlieties failu!')
ON DUPLICATE KEY UPDATE `text` = VALUES(`text`);

INSERT INTO `FMK_MESSAGES` (`code`, `text`) VALUES 
('FILE_DELETE_FAILED', 'Kļūda, dzēšot failu!')
ON DUPLICATE KEY UPDATE `text` = VALUES(`text`);

INSERT INTO `FMK_MESSAGES` (`code`, `text`) VALUES 
('CONFIRM_DELETE_FILE', 'Vai tiešām vēlaties dzēst šo failu?')
ON DUPLICATE KEY UPDATE `text` = VALUES(`text`);

-- ============================================================================
-- RBF Akts Upload - Menu and Text Translations
-- ============================================================================

-- Add text code for RBF Export menu item
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_EXPORT', 'Upload RBF akti');

-- Add text code for file upload field
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_AKTS_FILE', 'Excel fails');

-- Add text codes for import messages
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_IMPORT_SUCCESS', 'Veiksmīgi importēti ieraksti:');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_IMPORT_SKIPPED', 'Izlaisti jau eksistējoši ieraksti:');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('RBF_IMPORT_ERRORS', 'Kļūdas importējot:');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ERROR_INVALID_FILE_TYPE', 'Nederīgs faila tips! Atļautie tipi: .xls, .xlsx');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ERROR_FILE_UPLOAD', 'Kļūda augšupielādējot failu!');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ERROR_PROCESSING_FILE', 'Kļūda apstrādājot failu');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ERROR_SAVING_FILE', 'Kļūda saglabājot failu!');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ERROR_SAVING_FILE_INFO', 'Kļūda saglabājot faila informāciju!');

-- Add requirements text for RBF Akts import
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('REQUIREMENTS_RBF_AKTS', '<h3 align="left">RBF aktu importam lūdzam izmantot Excel 97-2003 vai Excel 2007+ formātā (.xls vai .xlsx)</h3>
        <p align="left" style="color: #ff6600;"><strong>SVARĪGI: Excel failam jābūt ar 2 lapām (sheets):</strong></p>
        <ul style="margin-left: 20px;" align="left">
            <li><strong>1. lapa (Sheet1):</strong> Aktu dati</li>
            <li><strong>2. lapa (Sheet2):</strong> Darbu dati</li>
        </ul>
        
        <h4 align="left">1. LAPA (SHEET1): AKTU DATI</h4>
        <p align="left"><strong>Kolonnu secība un nosaukumi:</strong></p>
        <table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas nr.</th><th>Kolonas nosaukums Excel</th><th>Obligāts</th><th>Datu tips</th><th>Maksimālais garums</th><th>Apraksts</th></tr>
        <tr><td>A</td><td>Darbuzņēmēja kods</td><td>+</td><td>VARCHAR</td><td>11</td><td>Darbuzņēmēja identifikācijas kods</td></tr>
        <tr><td>B</td><td>VV numurs</td><td>+</td><td>VARCHAR</td><td>20</td><td>Vispārīgās vienošanās numurs</td></tr>
        <tr><td>C</td><td>RBF nodaļa</td><td>+</td><td>VARCHAR</td><td>10</td><td>RBF teritorijas/nodaļas kods</td></tr>
        <tr><td>D</td><td>Autors</td><td>+</td><td>VARCHAR</td><td>200</td><td>Akta autora vārds un uzvārds</td></tr>
        <tr><td>E</td><td>Akta veids</td><td>+</td><td>CHAR</td><td>3</td><td>Akta veida kods no akta veidi kataloga (piemēram, "10", "20", "30")</td></tr>
        <tr><td>F</td><td>Pasūtījuma ID</td><td>+</td><td>VARCHAR</td><td>20</td><td>Unikāls pasūtījuma identifikators. Sistēma neimportēs ierakstus ar jau eksistējošu Pasūtījuma ID.</td></tr>
        <tr><td>G</td><td>Darba nosaukums</td><td>+</td><td>VARCHAR</td><td>500</td><td>Darba nosaukums izdrukām</td></tr>
        <tr><td>H</td><td>Parakstīšanas veids</td><td>-</td><td>CHAR</td><td>1</td><td>E - ar eparakstu, P - ar fizisko parakstu, K - KVIKSTEPS (nav obligāts)</td></tr>
        <tr style="background-color: #f0f0f0;"><td>I</td><td>Piezīmes</td><td>-</td><td>VARCHAR</td><td>150</td><td>Papildus piezīmes par aktu (nav obligāts)</td></tr>
        </table>
        
        <h4 align="left">2. LAPA (SHEET2): DARBU DATI</h4>
        <p align="left"><strong>Kolonnu secība un nosaukumi:</strong></p>
        <table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas nr.</th><th>Kolonas nosaukums Excel</th><th>Obligāts</th><th>Datu tips</th><th>Maksimālais garums</th><th>Apraksts</th></tr>
        <tr><td>A</td><td>Uzturēšanas darba numurs</td><td>+</td><td>VARCHAR</td><td>20</td><td>Pasūtījuma ID no 1. lapas (Sheet1 kolona F)</td></tr>
        <tr><td>B</td><td>Kalkulāciju kategorijas šifrs</td><td>+</td><td>CHAR</td><td>5</td><td>Kalkulācijas šifrs no kalkulāciju kataloga</td></tr>
        <tr><td>C</td><td>MMS nosacījums ID</td><td>+</td><td>VARCHAR</td><td>10</td><td>MMS sistēmas nosacījuma identifikators</td></tr>
        <tr><td>D</td><td>MMS darbība/Nosacījums</td><td>+</td><td>VARCHAR</td><td>250</td><td>MMS darbības vai nosacījuma nosaukums</td></tr>
        <tr><td>E</td><td>Darbības statusa kods</td><td>+</td><td>VARCHAR</td><td>20</td><td>Darba izpildes statuss (piemēram: "Iesākts" - PROCESS, "Novēršana" - COMPLETED)</td></tr>
        <tr><td>F</td><td>Normatīvais koeficients (C.st.)</td><td>+</td><td>FLOAT</td><td>7,2</td><td>Normatīvais koeficients (c.st. vienībās)</td></tr>
        <tr style="background-color: #f0f0f0;"><td>G</td><td>Izpildes datums</td><td>-</td><td>DATE/DATETIME</td><td>-</td><td>Plānotais vai faktiskais izpildes datums (nav obligāts)</td></tr>
		</table>
        
        <p align="left"><strong>Piezīmes:</strong></p>
        <ul style="margin-left: 20px;" align="left">
            <li><strong>1. lapa:</strong> Pirmā rinda (galvene) tiek izlaista importēšanas procesā</li>
            <li><strong>1. lapa:</strong> Ja ieraksts ar tādu pašu Pasūtījuma ID jau eksistē tabulā, tas netiks importēts atkārtoti</li>
            <li><strong>2. lapa:</strong> Pirmā rinda (galvene) tiek izlaista importēšanas procesā</li>
            <li><strong>2. lapa:</strong> Pirms jauno datu importēšanas, vecā darbu tabula (rbf_akta_darbi_tmp) tiek pilnībā iztīrīta</li>
            <li><strong>2. lapa:</strong> Kolona A (Uzturēšanas darba numurs) jāsasaista ar 1. lapas kolonu F (Pasūtījuma ID)</li>
            <li>Tukšas rindas abās lapās tiek automātiski izlaistas</li>
            <li>Ja 2. lapa (Sheet2) neeksistē, tiek importēta tikai 1. lapa</li>
        </ul>');

-- ============================================================================
-- RBF Akti Tables
-- ============================================================================

CREATE TABLE `rbf_akti` (
	`FAKT_ID` INT(11) NOT NULL AUTO_INCREMENT,
    `FAKT_KWOI_KODS` VARCHAR(11) NOT NULL COLLATE 'utf8_latvian_ci', -- Darbuzņēmēja kods
	`FAKT_VV_NUMBER` VARCHAR(20) NOT NULL COLLATE 'utf8_latvian_ci', -- Vispārīgās vienošanās nr.
    `FAKT_RBTR_KODS` VARCHAR(10) NOT NULL COLLATE 'utf8_latvian_ci', -- RBF nodaļa
    `FAKT_RLTT_TEXT` VARCHAR(200) NOT NULL COLLATE 'utf8_latvian_ci', -- Autors
	`FAKT_KAKV_KODS` CHAR(3) NOT NULL COLLATE 'utf8_latvian_ci', -- Akta veids
	`FAKT_SIGNATURE` CHAR(1) NULL COLLATE 'utf8_latvian_ci', -- Paraksts (E/P/K)
    `FAKT_NUM_POSTFIX` VARCHAR(20) NOT NULL COLLATE 'utf8_latvian_ci', -- Pasūtījuma ID (unikāls)
	`FAKT_WORK_TITLE` VARCHAR(500) NOT NULL COLLATE 'utf8_latvian_ci', -- Darba nosaukums
	`FAKT_PIEZIMES` VARCHAR(150) NULL COLLATE 'utf8_latvian_ci', -- Piezīmes
	`FAKT_FFLS_ID` INT(11) NULL, -- Reference to uploaded file
	`FAKT_PROCESSED_DATE` DATETIME NULL, -- Processing date
	`FAKT_PROCESSED` CHAR(1) NOT NULL DEFAULT '0', -- Is processed (0 - no, 1 - yes)
	PRIMARY KEY (`FAKT_ID`),
	UNIQUE INDEX `U_FAKT_NUM_POSTFIX` (`FAKT_NUM_POSTFIX`),
	INDEX `IDX_FAKT_FFLS_ID` (`FAKT_FFLS_ID`),
	INDEX `IDX_FAKT_PROCESSED` (`FAKT_PROCESSED`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM;

CREATE TABLE `rbf_akta_files` (
	`FFLS_ID` INT(11) NOT NULL AUTO_INCREMENT,
    `FFLS_NAME_ORIGINAL` VARCHAR(200) NOT NULL COLLATE 'utf8_latvian_ci', -- Faila originālais nosaukums
	`FFLS_NAME_GENERATED` VARCHAR(200) NOT NULL COLLATE 'utf8_latvian_ci', -- Faila sistēmas nosaukums
    `FFLS_UPLOADED_DATE` DATETIME NOT NULL DEFAULT current_timestamp(), -- Importa datums
	PRIMARY KEY (`FFLS_ID`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM;

-- ============================================================================
-- ALTER TABLE for existing databases
-- ============================================================================

-- Add FAKT_SIGNATURE column if it doesn't exist
ALTER TABLE `rbf_akti` 
ADD COLUMN `FAKT_SIGNATURE` CHAR(1) NULL COLLATE 'utf8_latvian_ci' COMMENT 'Paraksts (E/P/K)' AFTER `FAKT_KAKV_KODS`;

CREATE TABLE `rbf_akta_darbi_tmp` (
	`FADR_ID` INT(11) NOT NULL AUTO_INCREMENT,
    `FADR_NUM_POSTFIX` VARCHAR(20) NOT NULL COLLATE 'utf8_latvian_ci', -- Uzturēšanas darba numurs
	`FADR_RBKL_SHIFRS` CHAR(5) NOT NULL COLLATE 'utf8_latvian_ci', -- Kalkulāciju kategorijas šifrs
    `FADR_MMS_KODS` VARCHAR(10) NOT NULL COLLATE 'utf8_latvian_ci', -- MMS nosacījums ID
    `FADR_MMS_TITLE` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci', -- MMS darbība/Nosacījums
	`FADR_STATUS` VARCHAR(20) NOT NULL COLLATE 'utf8_latvian_ci', -- Darbības status
	`FADR_PLAN_DATE` DATETIME NULL, -- Izpildes datums
    `FADR_NORMA` FLOAT(7,2) NOT NULL,	-- C.st.
	PRIMARY KEY (`FADR_ID`),
	INDEX `IDX_FADR_AKT` (`FADR_NUM_POSTFIX`),
	INDEX `IDX_FADR_PROCESSED` (`FADR_RBKL_SHIFRS`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM;

CREATE TABLE `rbf_akta_darbi` (
	`RADR_ID` INT(11) NOT NULL AUTO_INCREMENT,
    `RADR_FAKT_ID` INT(11) NOT NULL, -- Act ID
	`RADR_RBKL_SHIFRS` CHAR(5) NOT NULL COLLATE 'utf8_latvian_ci', -- Kalkulāciju kategorijas šifrs
    `RADR_MMS_KODS` VARCHAR(10) NOT NULL COLLATE 'utf8_latvian_ci', -- MMS nosacījums ID
    `RADR_MMS_TITLE` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci', -- MMS darbība/Nosacījums
	`RADR_STATUS` VARCHAR(20) NOT NULL COLLATE 'utf8_latvian_ci', -- Darbības status
	`RADR_PLAN_DATE` DATETIME NULL, -- Izpildes datums
    `RADR_NORMA` FLOAT(7,2) NOT NULL,	-- C.st.
	`RADR_APPROVE_DATE` DATETIME NULL, -- Apstiprināšanas datums
	`RADR_IS_PROCESSED` TINYINT(1) NOT NULL DEFAULT 0, -- Is processed (0 - no, 1 - yes)
	PRIMARY KEY (`RADR_ID`),
	INDEX `IDX_RADR_FAKT_ID` (`RADR_FAKT_ID`),
	INDEX `IDX_RADR_RBKL_SHIFRS` (`RADR_RBKL_SHIFRS`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM;

INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`) VALUES 
('WORK_STATUS', 'PROCESS', 'Novēršana'),
('WORK_STATUS', 'COMPLETED', 'Pabeigts');
INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`) VALUES 
('WORK_STATUS', 'NOTHING_TO_DO', 'Nav darāmā'),
('WORK_STATUS', 'CANT_DO', 'Nevarēja izpildīt');