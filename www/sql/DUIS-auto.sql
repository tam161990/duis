ALTER TABLE `kl_mms_darbi` RENAME `kl_mms_darbi_old`;

CREATE TABLE `kl_mms_darbi` (
	`KMSD_ID` INT(11) NOT NULL AUTO_INCREMENT,
	`KMSD_KODS` VARCHAR(20) NOT NULL COLLATE 'utf8_latvian_ci',
    `KMSD_OPERATIVAS_APZIM` VARCHAR(255) NULL  COLLATE 'utf8_latvian_ci',
    `KMSD_WORK_TITLE` VARCHAR(2550) NULL  COLLATE 'utf8_latvian_ci',
    `KMSD_IZPILDES_DATUMS` DATETIME NOT NULL,
    `KMSD_NOSACIJUMA_KODS` INT NULL,
    `KMSD_NOSACIJUMS` VARCHAR(2550) NULL  COLLATE 'utf8_latvian_ci',
    `KMSD_IZPILDITAJA_KODS` VARCHAR(20) NULL COLLATE 'utf8_latvian_ci',
    `KMSD_VV_NUMURS` VARCHAR(20) NULL COLLATE 'utf8_latvian_ci',
    `KMSD_KEDI_KODS` INT(5) NOT NULL,
    `KMSD_PRIORITATE` SMALLINT(1) NOT NULL DEFAULT 0,
    `KMSD_IR_EPLA` SMALLINT(1) NOT NULL DEFAULT 0,
    `KMSD_TO_ID` VARCHAR(10) NULL  COLLATE 'utf8_latvian_ci',
    `KMSD_TEH_OBJEKTS` VARCHAR(50) NULL  COLLATE 'utf8_latvian_ci',
    `KMSD_TIKLA_ELEMENTS` VARCHAR(255) NULL  COLLATE 'utf8_latvian_ci',
    `KMSD_TIKLA_ELEMENTA_KLASE` VARCHAR(255) NULL  COLLATE 'utf8_latvian_ci',
    `KMSD_DAUDZUMS` FLOAT(8,2)   NULL,
    `KMSD_VADU_SKAITS` INT NULL,
    `KMSD_X` FLOAT(12,6)   NULL,
    `KMSD_Y` FLOAT(12,6)   NULL,
    `KMSD_KSRG_KODS` VARCHAR(10) NULL  COLLATE 'utf8_latvian_ci',
    `KMSD_KOBJ_KODS` VARCHAR(10) NULL  COLLATE 'utf8_latvian_ci',
    `KMSD_KFNA_KODS` VARCHAR(10) NULL  COLLATE 'utf8_latvian_ci',
	`KMSD_EXPORT_DATUMS` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,	
	PRIMARY KEY (`KMSD_ID`),
	INDEX `KMSD_NOSACIJUMA_KODS` (`KMSD_NOSACIJUMA_KODS`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM
AUTO_INCREMENT=1
;

ALTER TABLE `kl_mms_darbi` ADD `KMSD_CREATOR` INT NULL;
ALTER TABLE `kl_mms_darbi` ADD `KMSD_CREATED` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `kl_mms_darbi` ADD `KMSD_EDITOR` INT NULL;
ALTER TABLE `kl_mms_darbi` ADD `KMSD_EDITED` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP;

DELETE FROM `kl_ref_kolonnas` WHERE klkl_catalog = 'KL_MMS_DARBI' AND klkl_column = 'KMSD_CILVEKSTUNDAS';
DELETE FROM `kl_ref_kolonnas` WHERE klkl_catalog = 'KL_MMS_DARBI' AND klkl_column = 'KMSD_IR_PABEIGTS';
DELETE FROM `kl_ref_kolonnas` WHERE klkl_catalog = 'KL_MMS_DARBI' AND klkl_column = 'KMSD_MATR_IZMAKSAS';
DELETE FROM `kl_ref_kolonnas` WHERE klkl_catalog = 'KL_MMS_DARBI' AND klkl_column = 'KMSD_CETUKSNIS';
DELETE FROM `kl_ref_kolonnas` WHERE klkl_catalog = 'KL_MMS_DARBI' AND klkl_column = 'KMSD_GADS';

INSERT INTO `kl_ref_kolonnas`(KLKL_COLUMN,KLKL_TITLE,KLKL_CATALOG,KLKL_IS_DEFAULT) VALUES 
('KMSD_IZPILDES_DATUMS', 'Plānotais beigu datums', 'KL_MMS_DARBI', 0),
('KMSD_OPERATIVAS_APZIM', 'Operatīvais apzīmējums', 'KL_MMS_DARBI', 0),
('KMSD_WORK_TITLE', 'Darba apraksts', 'KL_MMS_DARBI', 0),
('KMSD_NOSACIJUMA_KODS', 'Nosacījuma ID', 'KL_MMS_DARBI', 0);

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('PROCESS_DATE', 'Plānotais beigu datums'),
('TECHNIC_OBJECT', 'Tehniskais objekts'),
('REQUIREMENT_CODE', 'Nosacījuma ID'),
('REQUIREMENT_TITLE', 'Nosacījums'),
('NETWORK_ELEMENT','Tīkla elementa iezīme'),
('NETWORK_EL_CODE', 'Tīkla elementa klase'),
('MMS_QUANTITY', 'Daudzums'),
('MMS_LINE_COUNT', 'Vadu skaits'),
('MMS_X', 'X'),
('MMS_Y', 'Y'),
('EXPORT_DATE','Eksporta datums, laiks');

ALTER TABLE `kl_objekti` ADD `KOBJ_KODS` CHAR(5);

INSERT INTO `kl_ref_kolonnas`(KLKL_COLUMN,KLKL_TITLE,KLKL_CATALOG,KLKL_IS_DEFAULT) VALUES 
('KOBJ_KODS', 'Objekta kods', 'KL_OBJEKTI', 0);

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES ('ERROR_EXISTS_OBJECT_CODE', 'Jau eksistē cits objekts ar šādu kodu.');

UPDATE `kl_objekti` SET `KOBJ_KODS` = '4'  WHERE `KOBJ_NOSAUKUMS` = '0,4 kV gaisvadu līnija';
UPDATE `kl_objekti` SET `KOBJ_KODS` = '5'  WHERE `KOBJ_NOSAUKUMS` = '0,4 kV kabeļi';
UPDATE `kl_objekti` SET `KOBJ_KODS` = '10'  WHERE `KOBJ_NOSAUKUMS` = '10 kV kabeļi';
UPDATE `kl_objekti` SET `KOBJ_KODS` = '20'  WHERE `KOBJ_NOSAUKUMS` = '20 kV gaisvadu līnija';
UPDATE `kl_objekti` SET `KOBJ_KODS` = '7'  WHERE `KOBJ_NOSAUKUMS` = 'CK (cilpu kastes)';
UPDATE `kl_objekti` SET `KOBJ_KODS` = '35'  WHERE `KOBJ_NOSAUKUMS` = 'KP (komutāc. punkts)';
UPDATE `kl_objekti` SET `KOBJ_KODS` = '30'  WHERE `KOBJ_NOSAUKUMS` = 'TP (transformat. punkti)';

UPDATE `FMK_MESSAGES` SET TEXT = '<table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr>        
        <tr><td>Darba kods</td><td>+</td><td>Maksimāli 20 simboli.</td></tr>
        <tr><td>Operatīvais apzīmējums</td><td>-</td><td>Maksimāli 255 simboli.</td></tr>
        <tr><td>Darba apraksts</td><td>-</td><td>Maksimāli 255 simboli.</td></tr>
        <tr><td>Plānotais izpildes datums</td><td>-</td><td>Datums formatā [YYYY-MM-DD].</td></tr>
        <tr><td>MMS nosacījuma kods</td><td>-</td><td>Cipars formatā [xxxxxxxxxx].</td></tr>
        <tr><td>MMS nosacījums</td><td>-</td><td>Maksimāli 255 simboli.</td></tr>
        <tr><td>Izpildītāja kods</td><td>-</td><td>Maksimāli 20 simboli.</td></tr>
        <tr><td>VV.Nr.</td><td>-</td><td>Maksimāli 20 simboli.</td></tr>
        <tr><td>Iecirkņa kods</td><td>+</td><td>Maksimāli 10 simboli.</td></tr>
        <tr><td>Steidzamības kods</td><td>-</td><td>Atļautas vērtības: 0, 1 </td></tr>
        <tr><td>Trašu darba pazīme</td><td>-</td><td>Atļautas vērtības: 0, 1 </td></tr>
        <tr><td>TO_ID</td><td>-</td><td>Maksimāli 10 simboli.</td></tr>
        <tr><td>Tehniskais objekts</td><td>-</td><td>Maksimāli 50 simboli.</td></tr>
        <tr><td>Tīkla elementa iezīme</td><td>-</td><td>Maksimāli 255 simboli.</td></tr>
        <tr><td>Tīkla elementa klase</td><td>-</td><td>Maksimāli 255 simboli.</td></tr>
        <tr><td>Daudzums</td><td>-</td><td>Cipars formatā [xxxxxxx.xx].</td></tr>
        <tr><td>vadu skaits</td><td>-</td><td>Cipars formatā [xxxxxxxxxx].</td></tr>
        <tr><td>X</td><td>-</td><td>Cipars formatā [xxxxxx.xxxxxx].</td></tr>
        <tr><td>Y</td><td>-</td><td>Cipars formatā [xxxxxx.xxxxxx].</td></tr>
        <tr><td>Spriegums, kods</td><td>-</td><td>Maksimāli 10 simboli.</td></tr>        
       </table>'
WHERE code = 'REQUIREMENTS_MMS_WORKS';

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('CREATED', 'Importa daums'),
('CREATOR', 'Importa veiceis'),
('EDITED', 'Labošanas datums'),
('EDITOR', 'Laboja lietotājs');

DELETE FROM `kl_ref_kolonnas` WHERE klkl_catalog = 'KL_MMS_DARBI' AND klkl_column = 'KMSD_TRASE';
INSERT INTO `kl_ref_kolonnas`(KLKL_COLUMN,KLKL_TITLE,KLKL_CATALOG,KLKL_IS_DEFAULT) VALUES 
('KMSD_IR_EPLA', 'DU trases (1/0)', 'KL_MMS_DARBI', 0);

--ALTER TABLE `kl_materiali` DROP `KMAT_IR_AKTIVS`;
ALTER TABLE `kl_materiali` ADD `KMAT_GRUPAS_KODS` INT  NULL;
ALTER TABLE `kl_materiali` ADD `KMAT_GRUPAS_NOSAUKUNS` VARCHAR(250)  NULL  COLLATE 'utf8_latvian_ci';
ALTER TABLE `kl_materiali` ADD `KMAT_APAKSGRUPAS_KODS` INT  NULL;
ALTER TABLE `kl_materiali` ADD `KMAT_APAKSGRUPAS_NOSAUKUNS` VARCHAR(250) NULL  COLLATE 'utf8_latvian_ci';
ALTER TABLE `kl_materiali` ADD `KMAT_KATEGORIJAS_KODS` INT NOT NULL;
ALTER TABLE `kl_materiali` ADD `KMAT_KATEGORIJAS_NOSAUKUNS` VARCHAR(250) NOT NULL  COLLATE 'utf8_latvian_ci';
ALTER TABLE `kl_materiali` ADD `KMAT_KATEGORIJAS_KLASE` VARCHAR(250) NULL COLLATE 'utf8_latvian_ci';
ALTER TABLE `kl_materiali` ADD `KMAT_KATEGORIJAS_MERVIENIBA` VARCHAR(15) NOT NULL  COLLATE 'utf8_latvian_ci';
ALTER TABLE `kl_materiali` ADD `KMAT_PRECIZEJUMS` INT NOT NULL DEFAULT 1;
ALTER TABLE `kl_materiali` ADD `KMAT_NOKLUSETAIS` INT NOT NULL DEFAULT 0;

UPDATE `FMK_MESSAGES` SET TEXT = '<table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr> 
        <tr><td>Grupas kods</td><td>+</td><td>Cipars formatā [xxxxxxxxxx].</td></tr>
        <tr><td>Grupa</td><td>+</td><td>Maksimāli 255 simboli.</td></tr>
        <tr><td>Apakšgrupas kods</td><td>+</td><td>Cipars formatā [xxxxxxxxxx].</td></tr>
        <tr><td>Apakšgrupa</td><td>+</td><td>Maksimāli 255 simboli.</td></tr>
        <tr><td>Nomenklatūras kategorijas kods</td><td>+</td><td>Cipars formatā [xxxxxxxxxx].</td></tr>
        <tr><td>Nomenklatūras kategorijas nosaukums</td><td>+</td><td>Maksimāli 255 simboli.</td></tr>
        <tr><td>Nomenklatūras kods</td><td>+</td><td>Materiāla oracla kods. Unikāls. Var saturēt tikai sekojošus simbolus `a`-`z`, `A`-`Z`, `0`-`9`. Maksimāli 7 simboli. </td></tr>
        <tr><td>Nomenklatūras apraksts</td><td>+</td><td>Materiāla nosaukums. Maksimāli 160 simboli. </td></tr>
        <tr><td>Mērvienība</td><td>+</td><td>Materiāla mērvienība. Maksimāli 15 simboli. </td></tr>
        <tr><td>Daudzums noliktavā</td><td>+</td><td>Cipars formatā [xxxxxxx.xx].</td></tr>
        <tr><td>Nomenklatūras vidējā cena</td><td>+</td><td>Cipars formatā [xxxxxxx.xx]. </td></tr>
        <tr><td>Kategorijas klase</td><td>-</td><td>Maksimāli 255 simboli. </td></tr>
        <tr><td>Kategorijas mērvienība</td><td>+</td><td>Maksimāli 15 simboli. </td></tr>
        <tr><td>Kategorijas precizējums</td><td>+</td><td>Cipars formatā [xxx].</td></tr>
        <tr><td>Noklusētais materiāls</td><td>-</td><td>Atļautas vērtības: 0, 1 </td></tr>
       </table>'
WHERE code = 'REQUIREMENTS_MATERIAL';

ALTER TABLE `kl_materiali` ADD `KMAT_CREATOR` INT NULL;
ALTER TABLE `kl_materiali` ADD `KMAT_CREATED` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `kl_materiali` ADD `KMAT_EDITOR` INT NULL;
ALTER TABLE `kl_materiali` ADD `KMAT_EDITED` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP;

DELETE FROM `kl_ref_kolonnas` WHERE klkl_catalog = 'KL_MATERIALI' AND klkl_column = 'KMAT_IR_AKTIVS';

INSERT INTO `kl_ref_kolonnas`(KLKL_COLUMN,KLKL_TITLE,KLKL_CATALOG,KLKL_IS_DEFAULT) VALUES 
('KMAT_KATEGORIJAS_KODS', 'Kategorijas kods', 'KL_MATERIALI', 0),
('KMAT_KATEGORIJAS_NOSAUKUNS', 'Kategorijas nosaukums', 'KL_MATERIALI', 0);

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('MATERIAL_CATEGORY', 'Nomenklatūras kategorija'),
('MATERIAL_CATEGORY_CLAS', 'Kategorijas klase'),
('MATERIAL_CATEGORY_MEASURE', 'Kategorijas mērvienība'),
('MATERIAL_CATEGORY_DESCR', 'Kategorijas precizējums'),
('MATERIAL_BY_DEFAULT', 'Noklusētais materiāls');

ALTER TABLE `kl_kalkulacija` RENAME `kl_kalkulacija_old`;
CREATE TABLE `kl_kalkulacija` (
	`KKAL_ID` INT(11) NOT NULL AUTO_INCREMENT,
	`KKAL_GRUPAS_KODS` CHAR(5) NOT NULL COLLATE 'utf8_latvian_ci',
	`KKAL_SHIFRS` CHAR(5) NOT NULL COLLATE 'utf8_latvian_ci',
	`KKAL_NOSAUKUMS` VARCHAR(150) NOT NULL COLLATE 'utf8_latvian_ci',
    `KKAL_MERVIENIBA` VARCHAR(15) NOT NULL COLLATE 'utf8_latvian_ci',
	`KKAL_APRAKSTS` TEXT NULL DEFAULT NULL COLLATE 'utf8_latvian_ci',
    `KKAL_FIZ_RADIJUMS` VARCHAR(4) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci',
    `KKAL_KWOI_KODS` VARCHAR(13) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci',
    `KKAL_VV_NUMBER` VARCHAR(20) NOT NULL COLLATE 'utf8_latvian_ci',
    `KKAL_KEDI_SECTION` VARCHAR(250) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci',
	`KKAL_PLANA` FLOAT(5,2) NOT NULL,
	`KKAL_NEPLANA` FLOAT(5,2) NOT NULL,
	`KKAL_KOEFICENT` FLOAT(5,3) NOT NULL DEFAULT 1.000,
    `KKAL_IS_ELEMENT` TINYINT(1) NOT NULL DEFAULT 0,
    `KKAL_TRASE` TINYINT(1) NOT NULL DEFAULT 0,
	`KKAL_IR_AKTIVS` TINYINT(1) NOT NULL DEFAULT 1,
    `KKAL_CREATOR` INT NULL,
    `KKAL_CREATED` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `KKAL_EDITOR` INT NULL,
    `KKAL_EDITED` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
	PRIMARY KEY (`KKAL_ID`),
	UNIQUE INDEX `U_KKAL_SHIFRS` (`KKAL_SHIFRS`),
	INDEX `KKAL_GRUPAS_KODS` (`KKAL_GRUPAS_KODS`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM
AUTO_INCREMENT=1
;
UPDATE `FMK_MESSAGES` SET TEXT = '<table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr> 
        <tr><td>Grupas kods</td><td>+</td><td>Kalkulācijas grupas kods. Var saturēt tikai sekojošus simbolus `a`-`z`, `A`-`Z`, `0`-`9`. Maksimāli 5 simboli.</td></tr>
        <tr><td>Kalkulācijas šifrs</td><td>+</td><td>Kalkulācijas šifrs. Unikāls. Var saturēt tikai sekojošus simbolus `0`-`9`. Maksimāli 5 simboli.</td></tr>
        <tr><td>Kalkulācijas nosaukums</td><td>+</td><td>Kalkulācijas nosaukums. Maksimāli 150 simboli.</td></tr>
        <tr><td>Mērvienība</td><td>+</td><td>Kalkulācijas mērvienība. Maksimāli 15 simboli.</td></tr>
        <tr><td>Apraksts</td><td>+</td><td>Kalkulācijas apraksts. Maksimāli 2000 simboli.</td></tr>
        <tr><td>Fiziskais rādītājs</td><td>+</td><td>Fiziska rādītāja pazime. Var saturēt tikai sekojošus simbolus [`2`-`9`]`z` vai [`2`-`11`]`v`. Maksimāli 3 simboli.</td></tr>
        <tr><td>Darbuzņēmējs</td><td>+</td><td>Darbuzņēmēja identifikators. Cipars.</td></tr>
        <tr><td>Līguma Nr.</td><td>+</td><td>Vispārīgās vienošanās nr. Maksimāli 20 simboli.</td></tr>
        <tr><td>ED nodaļa</td><td>+</td><td>ED nodaļas nosaukums. Maksimāli 250 simboli.</td></tr>
        <tr><td>Plāna cena</td><td>+</td><td>Cipars formātā [xxxxx.xx].</td></tr>
        <tr><td>Neplāna cena</td><td>+</td><td>Cipars formātā [xxxxx.xx].</td></tr>
        <tr><td>Fiz.rād. koefic.</td><td>+</td><td>Cipars formātā [xxxxx.xx].</td></tr>
        <tr><td>Stihijas kalkul.</td><td>+</td><td>Stihijas kalkul. Cipars formātā [0/1]</td></tr>
        <tr><td>Trašu kalkulācija</td><td>+</td><td>Kalkulācija tiek izmantota trašu tīrīšanas darbiem. Cipars formātā [0/1]</td></tr>
        <tr><td>Ir aktīvs</td><td>+</td><td>Kalkulācija ir aktuāla. Cipars formātā [0/1]</td></tr>
       </table>'
WHERE code = 'REQUIREMENTS_CALCULATION';

DELETE FROM `kl_ref_kolonnas` WHERE klkl_catalog = 'KL_KALKULACIJA' AND klkl_column = 'KKAL_PLAN_PRICE';
DELETE FROM `kl_ref_kolonnas` WHERE klkl_catalog = 'KL_KALKULACIJA' AND klkl_column = 'KKAL_NOT_PLAN_PRICE';

INSERT INTO `kl_ref_kolonnas`(KLKL_COLUMN,KLKL_TITLE,KLKL_CATALOG,KLKL_IS_DEFAULT) VALUES 
('KKAL_PLANA', 'Plāna cena', 'KL_KALKULACIJA', 0),
('KKAL_NEPLANA', 'Neplāna cena', 'KL_KALKULACIJA', 0);

CREATE TABLE `kl_mms_kalkulacija` (
	`KMKL_ID` INT(11) NOT NULL AUTO_INCREMENT,
	`KMKL_KMSD_NOSACIJUMA_KODS` INT(11) NOT NULL,
	`KMKL_KKAL_SHIFRS` CHAR(5) NOT NULL COLLATE 'utf8_latvian_ci',
    `KMKL_NOKL_SPRIEGUMS_10` TINYINT(1) NOT NULL DEFAULT 1,
    `KMKL_NOKL_SPRIEGUMS_NE_10` TINYINT(1) NOT NULL DEFAULT 1,
    `KMKL_DAUDZUMS` FLOAT(7,3) NOT NULL DEFAULT 1.000,
    `KMKL_IZMANTOT_LINIJU` TINYINT(1) NOT NULL DEFAULT 0,
    `KMKL_KOEFICENTS` FLOAT(7,3) NOT NULL DEFAULT 1.000,
    `KMKL_IZMANTOT_VADU` TINYINT(1) NOT NULL DEFAULT 0,
    `KMKL_IR_AKTIVS` TINYINT(1) NOT NULL DEFAULT 1,
    `KMKL_TRASE` TINYINT(1) NOT NULL DEFAULT 0,
    `KMKL_CREATOR` INT NULL,
    `KMKL_CREATED` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `KMKL_EDITOR` INT NULL,
    `KMKL_EDITED` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
	PRIMARY KEY `PK_KMKL_ID` (`KMKL_ID`),
	UNIQUE INDEX `U_KMKL_NOS_KALK` (`KMKL_KMSD_NOSACIJUMA_KODS`, `KMKL_KKAL_SHIFRS`, `KMKL_TRASE`),
	INDEX `IDX_KMKL_KMSD_NOSACIJUMA_KODS` (`KMKL_KMSD_NOSACIJUMA_KODS`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM
AUTO_INCREMENT=1
;

INSERT INTO `kl_ref_kolonnas`(KLKL_COLUMN,KLKL_TITLE,KLKL_CATALOG,KLKL_IS_DEFAULT) VALUES 
('KMKL_KMSD_NOSACIJUMA_KODS', 'MMS nosacījuma kods', 'KL_MMS_KALKULACIJA', 1),
('KMKL_KKAL_SHIFRS', 'Kalkulācijas kods', 'KL_MMS_KALKULACIJA', 0),
('KMKL_NOKL_SPRIEGUMS_10', 'Noklus.kalk. spriegums 10(1/0)', 'KL_MMS_KALKULACIJA', 0),
('KMKL_NOKL_SPRIEGUMS_NE_10', 'Noklus.kalk. spriegums<>10(1/0)', 'KL_MMS_KALKULACIJA', 0),
('KMKL_DAUDZUMS', 'Daudzums', 'KL_MMS_KALKULACIJA', 0),
('KMKL_IZMANTOT_LINIJU', 'Izmantot līnijas garumu(1/0)', 'KL_MMS_KALKULACIJA', 0),
('KMKL_KOEFICENTS', 'Koeficents', 'KL_MMS_KALKULACIJA', 0),
('KMKL_IZMANTOT_VADU', 'Izmantot vadu skaitu(1/0)', 'KL_MMS_KALKULACIJA', 0),
('KMKL_IR_AKTIVS', 'Aktīvs (1/0)', 'KL_MMS_KALKULACIJA', 0),
('KMKL_TRASE', 'Trases (0/1)', 'KL_MMS_KALKULACIJA', 0)
;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('MMS_REQUIREMENT_CODE', 'MMS nosacījuma kods'),
('CALCULATION_CODE', 'Kalkulācijas kods'),
('DEFAULT_VOLTAGE_10', 'Noklusētā kalk. sprieguma kodam 10'),
('DEFAULT_VOLTAGE_NOT_10', 'Noklusētā kalk. sprieguma kodam <> 10'),
('USE_LINE', 'Izmantot līnijas garumu'),
('USE_CORD', 'Izmantot vadu skaitu');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES ('REQUIREMENTS_MMS_CALCULATION',
       '<table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr> 
        <tr><td>MMS nosacījuma kods</td><td>+</td><td>Var saturēt tikai sekojošus simbolus `0`-`9`. Maksimāli 11 simboli.</td></tr>
        <tr><td>Kalkulācijas šifrs</td><td>+</td><td>Var saturēt tikai sekojošus simbolus `0`-`9`. Maksimāli 5 simboli.</td></tr>
        <tr><td>Noklusētā kalk. sprieguma kodam 10</td><td>+</td><td>Cipars formātā [0/1]</td></tr>
        <tr><td>Noklusētā kalk. sprieguma kodam <> 10</td><td>+</td><td>Cipars formātā [0/1]</td></tr>
        <tr><td>Daudzums</td><td>+</td><td>Cipars formātā [xxxxx.xxx].</td></tr>
        <tr><td>Izmantot līnijas garumu</td><td>+</td><td>Cipars formātā [0/1]</td></tr>
        <tr><td>Koeficents</td><td>+</td><td>Cipars formātā [xxxxx.xxx].</td></tr>
        <tr><td>Izmantot vadu skaitu</td><td>+</td><td>Stihijas kalkul. Cipars formātā [0/1]</td></tr>
        <tr><td>Ir aktīvs</td><td>+</td><td>Kalkulācija ir aktuāla. Cipars formātā [0/1]</td></tr>
        <tr><td>Trašu kalkulācija</td><td>+</td><td>Kalkulācija tiek izmantota trašu tīrīšanas darbiem. Cipars formātā [0/1]</td></tr>        
       </table>'    
);

INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`)
VALUES ('IMPORTS', 'MMS_KALKULATION', 'MMS-kalkulācijas');

UPDATE `FMK_MESSAGES` SET TEXT = '
        <ul>
            <li>Importējamais fails jābūt CSV formātā ar standarta specifikāciju: atdalītājs komats, ja teksta lauks satur komatu, tad teksta lauks ir "pēdiņās", kodējums UTF-8. </li>
            <li>Kolonnas virsraksti netiek importēti. </li>
            <li>Kolonas secība ir obligāta. </li>
            <li>Failā jābūt tikai predefinētas kolonnas. </li>
        </ul>
        Importējama faila kolonas saturs:'
WHERE code = 'TOTAL_REQUIREMENTS';

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('MMS_CALCULATION', 'MMS-kalkulācijas'),
('MMS_CALCULATION_INFO', 'MMS-kalkulācijas informācija'),
('ERROR_EXISTS_MMS_CALCULATION_CODE', 'Jau eksistē cita MMS-kalkulācija ar šādu kodu un nosacījumu.');

CREATE TABLE `kl_kalkulacija_materiali` (
	`KKMT_ID` INT(11) NOT NULL AUTO_INCREMENT,
	`KKMT_KKAL_SHIFRS` CHAR(5) NOT NULL COLLATE 'utf8_latvian_ci',
    `KKMT_KMAT_GRUPA` CHAR(4) NOT NULL COLLATE 'utf8_latvian_ci',
    `KKMT_KMAT_APAKSGRUPA` CHAR(3) NOT NULL COLLATE 'utf8_latvian_ci',
    `KKMT_KMAT_KODS` CHAR(7) NOT NULL COLLATE 'utf8_latvian_ci',
    `KKMT_IZMANTOT_NOMENKLATURU` TINYINT(1) NOT NULL DEFAULT 1,
    `KKMT_NOKLUSETAIS` TINYINT(1) NOT NULL DEFAULT 1,
    `KKMT_DAUDZUMS` FLOAT(7,3) NOT NULL DEFAULT 1.000,
    `KKMT_IZMANTOT_LINIJU` TINYINT(1) NOT NULL DEFAULT 0,
    `KKMT_KOEFICENTS` FLOAT(7,3) NOT NULL DEFAULT 1.000,
    `KKMT_IZMANTOT_VADU` TINYINT(1) NOT NULL DEFAULT 0,
    `KKMT_IR_AKTIVS` TINYINT(1) NOT NULL DEFAULT 1,
    `KKMT_CREATOR` INT NULL,
    `KKMT_CREATED` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `KKMT_EDITOR` INT NULL,
    `KKMT_EDITED` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
	PRIMARY KEY `PK_KKMT_ID` (`KKMT_ID`),
	UNIQUE INDEX `U_KKMT_GROUP_MATERI` (`KKMT_KKAL_SHIFRS`, `KKMT_KMAT_GRUPA`, `KKMT_KMAT_APAKSGRUPA`, `KKMT_KMAT_KODS`),
	INDEX `IDX_KKMT_KKAL_SHIFRS` (`KKMT_KKAL_SHIFRS`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM
AUTO_INCREMENT=1
;

INSERT INTO `kl_ref_kolonnas`(KLKL_COLUMN,KLKL_TITLE,KLKL_CATALOG,KLKL_IS_DEFAULT) VALUES 
('KKMT_KKAL_SHIFRS', 'Kalkulācijas kods', 'KL_KALKULACIJA_MATERIALI', 1),
('KMAT_GRUPA', 'Materiālu kategorija', 'KL_KALKULACIJA_MATERIALI', 0),
('KKMT_KMAT_KODS', 'Materiālu nomenklatūra', 'KL_KALKULACIJA_MATERIALI', 0),
('KKMT_IZMANTOT_NOMENKLATURU', 'Izmantot nomenklatūru(1/0)', 'KL_KALKULACIJA_MATERIALI', 0),
('KKMT_NOKLUSETAIS', 'Noklusētais materiāls(1/0)', 'KL_KALKULACIJA_MATERIALI', 0),
('KKMT_DAUDZUMS', 'Daudzums', 'KL_KALKULACIJA_MATERIALI', 0),
('KKMT_IZMANTOT_LINIJU', 'Izmantot līnijas garumu(1/0)', 'KL_KALKULACIJA_MATERIALI', 0),
('KKMT_KOEFICENTS', 'Koeficents', 'KL_KALKULACIJA_MATERIALI', 0),
('KKMT_IZMANTOT_VADU', 'Izmantot vadu skaitu(1/0)', 'KL_KALKULACIJA_MATERIALI', 0),
('KKMT_IR_AKTIVS', 'Aktīvs (1/0)', 'KL_KALKULACIJA_MATERIALI', 0)
;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('MATERIAL_GROUP_CODE', 'Materiālu kategorija'),
('MATERIAL_SUBGROUP_CODE', 'Materiālu apakškategorija'),
('JUSE_MATERIAL', 'Izmantot nomenklatūru'),
('DEFAULT_MATERIAL', 'Noklusētais materiāls'),
('CALCULATION_MATERIAL', 'Kalkulācijas-materiāli'),
('CALCULATION_MATERIAL_INFO', 'Kalkulācijas-materiālu informācija'),
('ERROR_EXISTS_CALC_MATERIAL_CODE', 'Jau eksistē cits Kalkulācijas-materiāls ar šādu kodu un kategoriju.');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES ('REQUIREMENTS_CALCULATION_MATERIAL',
       '<table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr>         
        <tr><td>Kalkulācijas šifrs</td><td>+</td><td>Var saturēt tikai sekojošus simbolus `0`-`9`. Maksimāli 5 simboli.</td></tr>
        <tr><td>Materiālu kategorija</td><td>+</td><td>Var saturēt tikai sekojošus simbolus `0`-`9`, `.`. Formāts [xxxx.xxx]. Maksimāli 8 simboli.</td></tr>
        <tr><td>Materiālu nomenklatūra</td><td>+</td><td>Var saturēt tikai sekojošus simbolus `0`-`9`. Maksimāli 7 simboli.</td></tr>
        <tr><td>Izmantot nomenklatūru</td><td>+</td><td>Cipars formātā [0/1]</td></tr>
        <tr><td>Noklusētais materiāls</td><td>+</td><td>Cipars formātā [0/1]</td></tr>
        <tr><td>Daudzums</td><td>+</td><td>Cipars formātā [xxxxx.xxx].</td></tr>
        <tr><td>Izmantot līnijas garumu</td><td>+</td><td>Cipars formātā [0/1]</td></tr>
        <tr><td>Koeficents</td><td>+</td><td>Cipars formātā [xxxxx.xxx].</td></tr>
        <tr><td>Izmantot vadu skaitu</td><td>+</td><td>Stihijas kalkul. Cipars formātā [0/1]</td></tr>
        <tr><td>Ir aktīvs</td><td>+</td><td>Kalkulācija ir aktuāla. Cipars formātā [0/1]</td></tr>        
       </table>'    
);

INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`)
VALUES ('IMPORTS', 'KALKULATION_MATERIAL', 'Kalkulācijas-materiāli');

UPDATE `FMK_MESSAGES` SET TEXT = 'Importējamais fails jābūt CSV formātā.' WHERE code = 'ERROR_NOT_CORRECT_TYPE_OF_FILE';

ALTER TABLE `kl_ed_iecirkni` ADD UNIQUE INDEX `U_KEDI_KODS` (`KEDI_KODS`);
ALTER TABLE `kl_ed_iecirkni` ADD `KEDI_CREATOR` INT NULL;
ALTER TABLE `kl_ed_iecirkni` ADD `KEDI_CREATED` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `kl_ed_iecirkni` ADD `KEDI_EDITOR` INT NULL;
ALTER TABLE `kl_ed_iecirkni` ADD `KEDI_EDITED` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP;

ALTER TABLE `kl_saskanotaji` ADD `SLTT_CREATOR` INT NULL;
ALTER TABLE `kl_saskanotaji` ADD `SLTT_CREATED` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP;
ALTER TABLE `kl_saskanotaji` ADD `SLTT_EDITOR` INT NULL;
ALTER TABLE `kl_saskanotaji` ADD `SLTT_EDITED` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP;

ALTER TABLE `kl_materiali` CHANGE `KMAT_NOSAUKUMS` `KMAT_NOSAUKUMS` VARCHAR( 250 ) CHARACTER SET utf8 COLLATE utf8_latvian_ci NOT NULL;
ALTER TABLE `kl_materiali` CHANGE `KMAT_CENA` `KMAT_CENA` FLOAT( 8, 2 ) NOT NULL;
ALTER TABLE `kl_materiali` CHANGE `KMAT_DAUDZUMS` `KMAT_DAUDZUMS` FLOAT( 9, 3 ) NULL DEFAULT NULL;