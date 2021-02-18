ALTER TABLE `lietotaji`
	CHANGE COLUMN `RLTT_ID` `RLTT_ID` INT(11) UNSIGNED NOT NULL AUTO_INCREMENT FIRST;

CREATE TABLE `event_log` (
	`EVNT_ID` INT(11) NOT NULL AUTO_INCREMENT COMMENT 'Ieraksta identifikātors',
	`EVNT_TYPE` CHAR(1) NOT NULL DEFAULT 'A' COMMENT 'Notikuma tips (A, W, C) (Activity, Warning, Critical)' COLLATE 'utf8_latvian_ci',
	`EVNT_FORM_ID` VARCHAR(50) NULL DEFAULT NULL COMMENT 'Formas unikalais identifikātors' COLLATE 'utf8_latvian_ci',
	`EVNT_OP_ID` CHAR(1) NULL DEFAULT NULL COMMENT 'Operacijas identifikātors' COLLATE 'utf8_latvian_ci',
	`EVNT_IS_EPLA` SMALLINT(1) NOT NULL DEFAULT 0 COMMENT 'Pazīme norada uz EPLA aktu',
	`EVNT_USER` INT(11) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Atsauce uz lietotāja ID',
	`EVNT_DESCRIPTION` VARCHAR(4000) NULL DEFAULT '0' COMMENT 'Notikuma apraksts' COLLATE 'utf8_latvian_ci',
	`EVNT_SECTION` VARCHAR(100) NULL DEFAULT '0' COMMENT 'Moduļa apakšsadaļa' COLLATE 'utf8_latvian_ci',
	`EVNT_TIMESTAMP` DATETIME NOT NULL DEFAULT current_timestamp() COMMENT 'Notikuma datums',
	`EVNT_REQUEST` VARCHAR(4000) NULL DEFAULT NULL COMMENT 'Requesta dati' COLLATE 'utf8_latvian_ci',
	PRIMARY KEY (`EVNT_ID`)
)
COMMENT='Kritisko kļūdu un darbību reģistrācijas žurnāls'
COLLATE='utf8_latvian_ci'
ENGINE=InnoDB
AUTO_INCREMENT=1147
;

CREATE TABLE `event_modules` (
    `EVMD_MODULE` VARCHAR(50) NOT NULL  COMMENT 'Sistēmas daļa' COLLATE 'utf8_latvian_ci',
    `EVMD_FORM_ID` VARCHAR(50) NOT NULL  COMMENT 'Formas unikalais identifikātors' COLLATE 'utf8_latvian_ci',
    `EVMD_FORM_NAME` VARCHAR(250) NOT NULL COMMENT 'Formas nosaukums' COLLATE 'utf8_latvian_ci',
    PRIMARY KEY (`EVMD_FORM_ID`)
)
COMMENT='Kritisko kļūdu un darbību reģistrācijas žurnāla sadaļas'
COLLATE='utf8_latvian_ci'
AUTO_INCREMENT=1
;

INSERT INTO  `event_modules` (`EVMD_MODULE`,`EVMD_FORM_NAME`,`EVMD_FORM_ID`) VALUES
('CATALOG', 'MATERIALS', 'f.ktl.s.1'),
('CATALOG', 'REGIONS', 'f.ktl.s.3'),
('CATALOG', 'ED_AREA', 'f.ktl.s.5'),
('CATALOG', 'VOLTAGE', 'f.ktl.s.6'),
('CATALOG', 'OBJECTS', 'f.ktl.s.7'),
('CATALOG', 'WORK_OUNERS', 'f.ktl.s.8'),
('CATALOG', 'CALCULATION_GROUP', 'f.ktl.s.9'),
('CATALOG', 'CALCULATION', 'f.ktl.s.10'),
('CATALOG', 'ACT_TYPE', 'f.ktl.s.11'),
('CATALOG', 'USERS', 'f.ktl.s.12'),
('CATALOG', 'USERS_DU', 'f.ktl.s.2'),
('CATALOG', 'HARMONIZED', 'f.ktl.s.4'),
('CATALOG', 'SINGLE_MMS', 'f.ktl.s.14'),
('CATALOG', 'MMS_CALCULATION', 'f.ktl.s.20'),
('CATALOG', 'CALCULATION_MATERIAL', 'f.ktl.s.21'),
('CATALOG', 'WORK_TYPES', 'f.ktl.s.22'),
('CATALOG', 'DATA_IMPORT', 'f.ktl.s.13'),
('USER', 'AUTENTIFICATION', 'f.lgn.s.1'), 
('REPORT', 'REPORT', 'f.rpt.s.0'),
('REPORT', 'REPORT_ACT_TOTAL', 'f.rpt.s.1'),
('REPORT', 'REPORT_WORK_TOTAL', 'f.rpt.s.2'),
('REPORT', 'REPORT_MATERIAL_TOTAL', 'f.rpt.s.3'),
('REPORT', 'REPORT_ACT_TOTAL', 'f.rpt.e.1'),
('REPORT', 'REPORT_WORK_TOTAL', 'f.rpt.e.2'),
('REPORT', 'REPORT_MATERIAL_TOTAL', 'f.rpt.e.3'),
('OPTIONS', 'WARNING', 'f.adm.s.1'),
('OPTIONS', 'ACT_NUMBER_TEMPLATE', 'f.adm.s.3'),
('OPTIONS', 'SUPERADMIN', 'f.adm.s.5'),
('OPTIONS', 'SYSTEM_PROCESS', 'f.adm.s.4'),
('ACT', 'SINGLE_ACT', 'f.akt.s.1'),
('ACT', 'SEARCH', 'f.akt.s.9'),
('ACT', 'WRITE_OFF_ACT', 'f.akt.s.14'),
('ACT', 'WRITE_OFF_ACT', 'f.akt.s.15'),
('ACT', 'MAMUAL_WORK_ADD', 'f.akt.s.8'),  
('ACT', 'MAMUAL_MATERIAL_ADD', 'f.akt.s.11'), 
('ACT', 'WORKER_MATERIAL', 'f.akt.s.13'),
('ACT', 'VIEW_ACT', 'f.akt.s.12'),
('ACT', 'VIEW_ACT', 'f.akt.s.16'),
('ACT', 'ACCEPT', 'f.akt.s.17'),
('PROJECT', 'PROJECTS', 'f.akt.s.20'),
('PROJECT', 'WORK_MATERIAL_ADD', 'f.akt.s.23'),
('PROJECT', 'IMPORT_NO_PROJECT', 'f.akt.s.24'),
('SYSTEM', 'CORE', 'class'), 
('SYSTEM', 'CORE', 'php');

ALTER TABLE `event_modules` ADD COLUMN `EVMD_CHECK_SECTION` SMALLINT NOT NULL DEFAULT 0 COMMENT 'Pārbaudīt saturu event_log.evnt_section kolonnā';
ALTER TABLE `event_modules` ADD COLUMN `EVMD_CHECK_OP_ID` SMALLINT NOT NULL DEFAULT 0 COMMENT 'Pārbaudīt saturu event_log.evnt_op_id kolonnā';
ALTER TABLE `event_modules` ADD COLUMN `EVMD_CHECK_IS_EPLA` SMALLINT NOT NULL DEFAULT 0 COMMENT 'Pārbaudīt saturu event_log.evnt_is_epla kolonnā';

UPDATE `event_modules` SET `EVMD_CHECK_SECTION` = 1 WHERE `EVMD_FORM_ID` IN ('f.ktl.s.13', 'f.akt.s.1', 'f.akt.s.20');
UPDATE `event_modules` SET `EVMD_CHECK_OP_ID` = 1 WHERE `EVMD_FORM_ID` IN ('f.akt.s.1', 'f.akt.s.20', 'f.adm.s.4');
UPDATE `event_modules` SET `EVMD_CHECK_OP_ID` = 1 WHERE `EVMD_FORM_ID` LIKE 'f.ktl.s.%';
UPDATE `event_modules` SET `EVMD_CHECK_IS_EPLA` = 1 WHERE `EVMD_FORM_ID` IN ('f.akt.s.1','f.akt.s.8','f.akt.s.12','f.akt.s.16','f.akt.s.17');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('ACT', 'Akts'),
('SYSTEM', 'Sistēma'),
('AUTENTIFICATION', 'Autentifikācija'),
('MAMUAL_WORK_ADD', 'Darbu/materiālu pievienošana'),
('MAMUAL_MATERIAL_ADD', 'Materiālu pievienošana'),
('CORE', 'Iekšējais process');

INSERT INTO  `event_modules` (`EVMD_MODULE`,`EVMD_FORM_NAME`,`EVMD_FORM_ID`) VALUES
('AUTOPROC', 'SYSTEM_PROCESS_INFO', 'ActStatus'),
('AUTOPROC', 'SYSTEM_PROCESS_INFO', 'ProjectInput'),
('AUTOPROC', 'SYSTEM_PROCESS_INFO', 'updateActStatus');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('AUTOPROC', 'Fona process'),
('INPUT_ACT_STATUS', 'Akta status no KS'),
('INPUT_PROJECT_INFO', 'Project info no KS'),
('SET_ACT_STATUS', 'Akta statusa atjaunošana');

INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`) VALUES 
('OP', 'I', 'Ievadīt'),
('OP', 'D', 'Dzēst'),
('OP', 'U', 'Atjaunot'),
('OP', 'E', 'Eksportēt'),
('OP', 'T', 'Eksportēt tame'),
('OP', 'R', 'Atgriezt'),
('OP', 'A', 'Apstiprināt'),
('OP', 'C', 'Kopēt'),
('OP', 'S', 'Meklēt'),
('OP', 'P', 'Nodot apmaksai'),
('OP', 'X', 'Atgriezts ar administrātoru'),
('OP', 'Y', 'Dzēsts ar administrātoru'),
('OP', 'J', 'Palaist process'),
('OP', 'K', 'Pabeigt process'),
('OP', 'M', 'Eksportēt staraktu'),
('OP', 'L', 'Dzēst rindu'),
('OP', 'N', 'Noraidīt projektu')
;
CREATE OR REPLACE VIEW v_event_log
AS
SELECT * FROM (
SELECT 	
   l.`EVNT_ID`,
	l.`EVNT_TYPE`
	,l.`EVNT_FORM_ID`
	,l.`EVNT_OP_ID`
	,l.`EVNT_IS_EPLA`
	,l.`EVNT_USER`
	,NVL(CASE WHEN l.`EVNT_OP_ID` IS NOT NULL AND l.`EVNT_DESCRIPTION` = '' THEN
		(SELECT `EVNT_DESCRIPTION`
					FROM `event_log`  l1
					WHERE l1.`EVNT_OP_ID` = ''
					AND l1.`EVNT_DESCRIPTION` IS NOT NULL
					AND l1.EVNT_ID = l.EVNT_ID + 1
					AND l.EVNT_USER = l1.EVNT_USER 
					AND l.EVNT_FORM_ID = l1.EVNT_FORM_ID
		)
	ELSE l.`EVNT_DESCRIPTION` END, '') AS `DESCRIPTION`
	,CASE WHEN 1=1 THEN
		(SELECT l1.`EVNT_ID`
					FROM `event_log`  l1
					WHERE l1.`EVNT_OP_ID` IS NOT NULL
					AND l1.`EVNT_DESCRIPTION` = ''
					AND l1.EVNT_ID = l.EVNT_ID - 1
					AND l.EVNT_USER = l1.EVNT_USER 
					AND l.EVNT_FORM_ID = l1.EVNT_FORM_ID
		)
	 END AS `SECOND_EVNT_ID`
	,l.`EVNT_SECTION`
	,l.`EVNT_TIMESTAMP`
	,l.`EVNT_REQUEST`
	,m.`EVMD_MODULE`
	,msg1.text AS `MODULE_TITLE`
	,m.`EVMD_FORM_ID`
	,m.`EVMD_FORM_NAME`
	,CONCAT(msg2.text, ' ', NVL(msg4.text, ''),' ', NVL(k1.KRFK_NOZIME, ''), ' ', NVL(msg3.text, ''), ' ', NVL(k.KRFK_NOZIME, '')) AS `FORM_NAME`
	,CONCAT(u.RLTT_VARDS, ' ', u.RLTT_UZVARDS) AS `USER_NAME`
	FROM `event_log` l
	INNER JOIN `event_modules` m ON l.EVNT_FORM_ID = m.EVMD_FORM_ID
	INNER JOIN `lietotaji` u ON l.EVNT_USER = u.RLTT_ID
	INNER JOIN `fmk_messages` msg1 ON m.EVMD_MODULE = msg1.code
	INNER JOIN `fmk_messages` msg2 ON m.EVMD_FORM_NAME = msg2.code
	LEFT JOIN `fmk_messages` msg3 ON m.EVMD_CHECK_SECTION = 1 AND l.EVNT_SECTION= msg3.code 
	LEFT JOIN `fmk_messages` msg4 ON m.EVMD_CHECK_IS_EPLA = 1 AND 'TRASES' = msg4.code 
	LEFT JOIN `kl_ref_kodi` k ON m.EVMD_CHECK_OP_ID = 1 AND k.KRFK_NOSAUKUMS = 'OP' AND l.EVNT_OP_ID = k.KRFK_VERTIBA
	LEFT JOIN `kl_ref_kodi` k1 ON m.EVMD_CHECK_SECTION = 1 AND k1.KRFK_NOSAUKUMS = 'IMPORTS' AND l.EVNT_SECTION = k1.KRFK_VERTIBA
) X
 WHERE 
 x.`SECOND_EVNT_ID` IS NULL OR 
 (x.`EVNT_OP_ID` !='' AND x.`EVNT_ID` = x.`SECOND_EVNT_ID`+1) ;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('EVENT_LOG', 'Notikumu žurnāls'),
('EVENT_SECTION', 'Sadaļa'),
('EVENT_MODULE', 'Modulis'),
('EVENT_TYPE_ACTIVITY', 'Activity'),
('EVENT_TYPE_WARNING', 'Warning'),
('EVENT_TYPE_CRITICAL', 'Critical');

INSERT INTO  `event_modules` (`EVMD_MODULE`,`EVMD_FORM_NAME`,`EVMD_FORM_ID`) VALUES
('OPTIONS', 'EVENT_LOG', 'f.adm.s.6');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('EVENT_LOG_DELETE_INFO', 'Dzēst notikumus vecākus par šodienu.');