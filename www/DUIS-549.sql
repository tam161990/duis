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

-- Insert text code for error when RBF employee code already exists
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ERROR_EXISTS_RBF_EMPLOYEE_CODE', 'Darbuzņēmējs ar šādu kodu jau eksistē!');

-- Insert text code for error when RBF employee agreement number already exists
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ERROR_EXISTS_RBF_EMPLOYEE_VV_NUMBER', 'Darbuzņēmējs ar šādu vispārīgās vienošanās numuru jau eksistē!');

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
	`RBDU_VV_VEIDS` CHAR(1) NOT NULL COLLATE 'utf8_latvian_ci', -- Vispārīgās vienošanās veids (only 2 options available: "Uzturēšana", "Ceļa segumi")
	`RBDU_VV_NUMURS` VARCHAR(15) NOT NULL COLLATE 'utf8_latvian_ci', -- Vispārīgās vienošanās nr.
    `RBDU_KONTAKTI` VARCHAR(500) NULL COLLATE 'utf8_latvian_ci', -- Kontakti
    `RBDU_IR_AKTIVS` TINYINT(1) NOT NULL DEFAULT 1, -- Aktīvs (1/0)
	PRIMARY KEY (`RBDU_ID`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM;

CREATE TABLE `kl_rbf_du_teritorijas` (    
	`RBDT_RBTR_ID` INT(11) NOT NULL,
    `RBDT_RBDU_ID` INT(11) NOT NULL
)
ENGINE=MyISAM;