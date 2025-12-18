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