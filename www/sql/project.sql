ALTER TABLE `lietotaji` ADD `RLTT_PROJECTOR` INT(1) NOT NULL DEFAULT 0;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('PROJECTOR', 'Projektētajs');

ALTER TABLE `akti` ADD `RAKT_PROJECT` INT(1) NOT NULL DEFAULT 0;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('PROJECT', 'Projekts');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('ADVANCED_PROJECT_SEARCH', 'Izvērsta projektu meklēšana');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('ST_WORK', 'ST darbi');

ALTER TABLE `darbi` ADD `DRBI_PIEZIMES` VARCHAR(250) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci';
ALTER TABLE `tame_darbi` ADD `DRBI_PIEZIMES` VARCHAR(250) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci';
ALTER TABLE `materiali` ADD `MATR_PIEZIMES` VARCHAR(250) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci';
ALTER TABLE `tame_materiali` ADD `MATR_PIEZIMES` VARCHAR(250) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci';
ALTER TABLE `darbi` CHANGE COLUMN `DRBI_KKAL_NORMATIVS` `DRBI_KKAL_NORMATIVS` FLOAT(8,2) NULL;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('PROJECT_HEADER', 'SAGATAVE');

ALTER TABLE `kl_work_owners` ADD `KWOI_NOSAUKUMS2` VARCHAR(250) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci';
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('NAME2', 'Nosaukums2');
INSERT INTO `kl_ref_kolonnas`(KLKL_COLUMN,KLKL_TITLE,KLKL_CATALOG,KLKL_IS_DEFAULT) VALUES 
('KWOI_NOSAUKUMS2', 'Nosaukums2', 'KL_DARBA_UZNEMEJI', 0);
UPDATE `kl_work_owners` SET `KWOI_NOSAUKUMS2` = `KWOI_NOSAUKUMS`; 

CREATE TABLE `excel_faili` (
	`EFLS_ID` INT(11) NOT NULL AUTO_INCREMENT,
	`EFLS_NOSAUKUMS` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci',
	`EFLS_DATUMS` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,	
	`EFLS_META_INFO` VARCHAR(250) NOT NULL DEFAULT 'application/vnd.ms-excel' COLLATE 'utf8_latvian_ci',
	`EFLS_RLTT_ID` INT(11) NOT NULL,
	`EFLS_RAKT_ID` INT(11) NOT NULL,
	PRIMARY KEY (`EFLS_ID`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM
AUTO_INCREMENT=1
;

-- 
ALTER TABLE `darbi`
	ADD COLUMN `DRBI_IS_WORKER` TINYINT(1) NOT NULL DEFAULT 0 AFTER `DRBI_KKAL_ID`;
ALTER TABLE `tame_darbi`
	ADD COLUMN `DRBI_IS_WORKER` TINYINT(1) NOT NULL DEFAULT 0 AFTER `DRBI_KKAL_ID`;

ALTER TABLE `darbi`
	CHANGE COLUMN `DRBI_KKAL_SHIFRS` `DRBI_KKAL_SHIFRS` CHAR(5) NULL COLLATE 'utf8_latvian_ci' ;
ALTER TABLE `tame_darbi`
	CHANGE COLUMN `DRBI_KKAL_SHIFRS` `DRBI_KKAL_SHIFRS` CHAR(5) NULL COLLATE 'utf8_latvian_ci' ;

ALTER TABLE `darbi` CHANGE COLUMN `DRBI_KKAL_ID` `DRBI_KKAL_ID` INT(11) NULL;
ALTER TABLE `tame_darbi` CHANGE COLUMN `DRBI_KKAL_ID` `DRBI_KKAL_ID` INT(11) NULL;

--
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('WORK_COAST', 'Darbu izmaksas'),
('MATERIAL_COAST', 'Materiālu izmaksas');

ALTER TABLE `darbi` CHANGE COLUMN `DRBI_KKAL_ID` `DRBI_KKAL_ID` INT(11) NULL;
ALTER TABLE `tame_darbi` CHANGE COLUMN `DRBI_KKAL_ID` `DRBI_KKAL_ID` INT(11) NULL;

INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`) VALUES 
('PROJECT_TYPE', 'PT_EE', 'Elektroenerģijas ražotāji (>1MW)'),
('PROJECT_TYPE', 'PT_EL', 'Elektrolīniju un TP rekonstrukcijas'),
('PROJECT_TYPE', 'PT_ET', 'Elektrotīkla pārvietošana'),
('PROJECT_TYPE', 'PT_OP', 'Objekta pieņemšana'),
('PROJECT_TYPE', 'PT_RS', 'Rekonstrukcijas shēma');

ALTER TABLE `AKTI` ADD COLUMN `RAKT_PROJECT_TYPE` CHAR(5) NULL;

CREATE TABLE `kl_darba_veidi` (
	`KLDV_ID` INT(11) NOT NULL AUTO_INCREMENT,
	`KLDV_NOSAUKUMS` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci',
	`KLDV_VEIDS` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci',
	`KLDV_IR_AKTIVS` TINYINT(1) NOT NULL DEFAULT '1',
	PRIMARY KEY (`KLDV_ID`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM
AUTO_INCREMENT=1
;
INSERT INTO `kl_ref_kolonnas`(KLKL_COLUMN,KLKL_TITLE,KLKL_CATALOG,KLKL_IS_DEFAULT) VALUES 
('KLDV_NOSAUKUMS', 'Darba nosaukums', 'KL_DARBA_VEIDI', 0),
('KLDV_VEIDS', 'Darba veids', 'KL_DARBA_VEIDI', 1),
('KLDV_IR_AKTIVS', 'Aktīvs (1/0)', 'KL_DARBA_VEIDI', 0)
;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('WORK_TYPES', 'Darba veidi'),
('SINGLE_WORK_TYPE', 'Darba veids'),
('TYPE', 'Veids'),
('WORK_TYPE_INFO', 'Darba veida informācija');


INSERT INTO `kl_darba_veidi` (`KLDV_NOSAUKUMS`,`KLDV_VEIDS`,`KLDV_IR_AKTIVS`) VALUES
('VS GVL (vidējā sprieguma gaisvadu līniju) izbūve, t. sk. digitālā nospraušana un uzmērīšana', 'Ierīkošanas/ pārbūves darbi', '1'),
('VS IVL (vidējā sprieguma izolētu vadu līniju) izbūve, t. sk. digitālā nospraušana un uzmērīšana', 'Ierīkošanas/ pārbūves darbi', '1'),
('VS KL (vidējā sprieguma kabeļu līniju) izbūve, t. sk. digitālā nospraušana un uzmērīšana', 'Ierīkošanas/ pārbūves darbi', '1'),
('Brīvgaisa komutācijas punkta izbūve / pārbūve, t. sk. digitālā nospraušana un uzmērīšana', 'Ierīkošanas/ pārbūves darbi', '1'),
('Slēgtā komutācijas punkta izbūve / pārbūve, t. sk. digitālā nospraušana un uzmērīšana', 'Ierīkošanas/ pārbūves darbi', '1'),
('Transformatora apakšstacijas izbūve / pārbūve, t. sk. digitālā nospraušana un uzmērīšana', 'Ierīkošanas/ pārbūves darbi', '1'),
('ZS GVL/PKL (zemsprieguma gaisvadu līniju/piekarkabeļu līniju) izbūve, t. sk. digitālā nospraušana un uzmērīšana', 'Ierīkošanas/ pārbūves darbi', '1'),
('Pirmsuzskaites ZS KL (zemsprieguma kabeļu līniju) izbūve, t. sk. digitālā nospraušana un uzmērīšana', 'Ierīkošanas/ pārbūves darbi', '1'),
('Pēcuzskaites ZS KL (zemsprieguma kabeļu līniju) izbūve, t. sk. digitālā nospraušana un uzmērīšana', 'Ierīkošanas/ pārbūves darbi', '1'),
('Automatizēta/ neautomatizēta jaudas slēdža iekārtas un materiālu izbūve, t. sk. digitālā nospraušana un uzmērīšana', 'Ierīkošanas/ pārbūves darbi', '1'),
('VS GVL (vidējā sprieguma gaisvadu līniju) demontāžas darbi', 'Demontāžas (nojaukšanas) darbi', '1'),
('VS IVL (vidējā sprieguma izolētu vadu līniju) demontāžas darbi', 'Demontāžas (nojaukšanas) darbi', '1'),
('VS KL (vidējā sprieguma kabeļlīniju) demontāžas darbi', 'Demontāžas (nojaukšanas) darbi', '1'),
('Brīvgaisa komutācijas punkta demontāžas darbi', 'Demontāžas (nojaukšanas) darbi', '1'),
('Slēgtā komutācijas punkta demontāžas darbi', 'Demontāžas (nojaukšanas) darbi', '1'),
('Transformatora apakšstacijas demontāžas darbi', 'Demontāžas (nojaukšanas) darbi', '1'),
('ZS GVL/PKL (zemsprieguma gaisvadu līniju/piekarkabeļu līniju) demontāžas darbi', 'Demontāžas (nojaukšanas) darbi', '1'),
('ZS GVL/PKL (zemsprieguma gaisvadu līniju/piekarkabeļu līniju) demontāžas darbi', 'Demontāžas (nojaukšanas) darbi', '1'),
('Pirmsuzskaites ZS KL (zemsprieguma pirmsuzskaites kabeļu līniju) demontāžas darbi', 'Demontāžas (nojaukšanas) darbi', '1'),
('Pēcuzskaites ZS KL (zemsprieguma pēcuzskaites kabeļu līniju) demontāžas darbi', 'Demontāžas (nojaukšanas) darbi', '1'),
('Automatizēta/ neautomatizēta jaudas slēdža iekārtas un materiālu demontāžas darbi', 'Demontāžas (nojaukšanas) darbi', '1');

ALTER TABLE `darbi` ADD COLUMN `DRBI_WORK_TYPE_ID` INT(11) NULL;
ALTER TABLE `materiali` ADD COLUMN `MATR_WORK_TYPE_ID` INT(11) NULL;
ALTER TABLE `tame_darbi` ADD COLUMN `DRBI_WORK_TYPE_ID` INT(11) NULL;
ALTER TABLE `tame_materiali` ADD COLUMN `MATR_WORK_TYPE_ID` INT(11) NULL;
--
ALTER TABLE `kl_materiali` CHANGE `KMAT_GRUPAS_KODS` `KMAT_GRUPAS_KODS` CHAR( 2 ) NULL DEFAULT NULL;
ALTER TABLE `kl_materiali` CHANGE `KMAT_APAKSGRUPAS_KODS` `KMAT_APAKSGRUPAS_KODS` CHAR( 4 ) NULL DEFAULT NULL;

INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`) VALUES 
('ROLE', 'PROJ_APPROVER', 'Projekta saskaņotājs');
--
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('PROJECTS', 'Projekti');
UPDATE `FMK_MESSAGES` SET `TEXT` = 'Meklēšanas rezultāti' WHERE `CODE` = 'LIST_OF_ACTS';

ALTER TABLE `materiali` CHANGE COLUMN `MATR_KODS` `MATR_KODS` CHAR(8) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci';

UPDATE `FMK_MESSAGES` SET `TEXT` = 'Darbu apjomi' WHERE `CODE` = 'WORK_COAST';
UPDATE `FMK_MESSAGES` SET `TEXT` = 'Materiālu saraksts' WHERE `CODE` = 'MATERIAL_COAST';

ALTER TABLE `darbi` ADD COLUMN `DRBI_WORK_TYPE_TEXT` VARCHAR(50) NULL;
ALTER TABLE `materiali` ADD COLUMN `MATR_WORK_TYPE_TEXT` VARCHAR(50) NULL;
ALTER TABLE `tame_darbi` ADD COLUMN `DRBI_WORK_TYPE_TEXT` VARCHAR(50) NULL;
ALTER TABLE `tame_materiali` ADD COLUMN `MATR_WORK_TYPE_TEXT` VARCHAR(50) NULL;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('PROJECT_OBJECT_TITLE', 'Objekta nosaukumu');
--
INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`) VALUES 
('PROJECT_EXPORT', 'MAN', 'MAN'),
('PROJECT_EXPORT', 'ST_DELIVER', 'ST piegāde');

ALTER TABLE `darbi` ADD COLUMN `DRBI_PROJECT_EXPORT` VARCHAR(10) NULL;
ALTER TABLE `materiali` ADD COLUMN `MATR_PROJECT_EXPORT` VARCHAR(10) NULL;
ALTER TABLE `tame_darbi` ADD COLUMN `DRBI_PROJECT_EXPORT` VARCHAR(10) NULL;
ALTER TABLE `tame_materiali` ADD COLUMN `MATR_PROJECT_EXPORT` VARCHAR(10) NULL;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('PROJECT_EXPORT_TYPE', 'Piegādes veids');