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