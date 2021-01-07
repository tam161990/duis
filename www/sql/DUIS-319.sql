ALTER TABLE `lietotaji`
	CHANGE COLUMN `RLTT_ID` `RLTT_ID` INT(11) UNSIGNED NOT NULL AUTO_INCREMENT FIRST;

CREATE TABLE `event_log` (
	`EVNT_ID` INT(11) NOT NULL AUTO_INCREMENT COMMENT 'Ieraksta identifikātors',
	`EVNT_TYPE` CHAR(1) NOT NULL DEFAULT 'A' COMMENT 'Notikuma tips (A, W, C) (Activity, Warning, Critical)',
	`EVNT_FORM_ID` VARCHAR(50) NULL DEFAULT NULL COMMENT 'Formas unikalais identifikātors',
	`EVNT_OP_ID` CHAR(1) NULL DEFAULT NULL COMMENT 'Operacijas identifikātors',
	`EVNT_IS_EPLA` SMALLINT(1) NOT NULL DEFAULT 0 COMMENT 'Pazīme norada uz EPLA aktu',
	`EVNT_USER` INT(11) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Atsauce uz lietotāja ID',
	`EVNT_REQUEST_URI` VARCHAR(500) NULL DEFAULT '0' COMMENT 'Pilna pieprasīta lapas adrese',
	`EVNT_DESCRIPTION` VARCHAR(4000) NULL DEFAULT '0' COMMENT 'Notikuma apraksts',
	`EVNT_TIMESTAMP` DATETIME NOT NULL DEFAULT current_timestamp() COMMENT 'Notikuma datums',
	`EVNT_REQUEST` VARCHAR(4000) NULL DEFAULT NULL COMMENT 'Requesta dati',
	PRIMARY KEY (`EVNT_ID`)
)
COMMENT='Kritisko kļūdu un darbību reģistrācijas žurnāls'
COLLATE='utf8_general_ci'
ENGINE=InnoDB
AUTO_INCREMENT=121
;
ALTER TABLE `   FOREIGN KEY (`async_task_id`) REFERENCES `async_task`(`idasync_task`);