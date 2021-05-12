CREATE TABLE `kl_materialu_grupas` (
	`KMTG_ID` INT(11) NOT NULL AUTO_INCREMENT,	
	`KMTG_GRUPAS_KODS` CHAR(2) NOT NULL COLLATE 'utf8_latvian_ci',
	`KMTG_GRUPAS_NOSAUKUNS` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci',
	`KMTG_APAKSGRUPAS_KODS` CHAR(4) NOT NULL COLLATE 'utf8_latvian_ci',
	`KMTG_APAKSGRUPAS_NOSAUKUNS` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci',
	`KMTG_KATEGORIJAS_KODS` CHAR(8) NOT NULL COLLATE 'utf8_latvian_ci',
	`KMTG_KATEGORIJAS_NOSAUKUNS` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci',
    `KMTG_KATEGORIJAS_MERVIENIBA` VARCHAR(15) NOT NULL COLLATE 'utf8_latvian_ci',
	`KMTG_PIEGADES_VEIDS` VARCHAR(50) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci',
	`KMTG_TS_NUMURS` VARCHAR(50) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci',
    `KMTG_KATEGORIJAS_IZMAINAS` VARCHAR(50) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci',
    `KMTG_IZMAINU_PIEZIMES` VARCHAR(250) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci',
	`KMTG_TS_ID` INT(3) NULL ,
    `KMTG_TS_STATUS` VARCHAR(50) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci',
    `KMTG_MR_STATUS` VARCHAR(50) NULL DEFAULT NULL COLLATE 'utf8_latvian_ci',
    `KMTG_KATEGORIJAS_PIELIETOJUMS` VARCHAR(50) NOT NULL COLLATE 'utf8_latvian_ci',
    `KMTG_KATEGORIJAS_NOZIMIGUMS` VARCHAR(50) NOT NULL COLLATE 'utf8_latvian_ci',
    `KMTG_KATEGORIJAS_UZTUR` VARCHAR(50) NOT NULL COLLATE 'utf8_latvian_ci',
    `KMTG_AIZVIETOJAMA_NOMENKLATURA` VARCHAR(50) NOT NULL,
    `KMTG_VIENUMA_TIPS` VARCHAR(50) NOT NULL,
    `KMTG_CELS` VARCHAR(50) NOT NULL,
	PRIMARY KEY (`KMTG_ID`),
	UNIQUE INDEX `KMTG_KATEGORIJAS_KODS` (`KMTG_KATEGORIJAS_KODS`),
    INDEX `KMTG_GRUPAS_KODS` (`KMTG_GRUPAS_KODS`),
    INDEX `KMTG_APAKSGRUPAS_KODS` (`KMTG_APAKSGRUPAS_KODS`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM
AUTO_INCREMENT=1
;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES ('REQUIREMENTS_MATERIAL_CATEGORY',
       '<h3>Materiālu kategorijas importam lūdzam izmantot daus Excel 97-2003 formātā</h3>
        <table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr> 
        <tr><td>Grupa</td><td>+</td><td>Maksimāli 255 simboli.</td></tr>
        <tr><td>Apakšgrupa</td><td>+</td><td>Maksimāli 255 simboli.</td></tr>
        <tr><td>Nomenklatūras kategorijas kods</td><td>+</td><td>Maksimāli 8 simboli formatā [xxxx.xxx].</td></tr>
        <tr><td>Nomenklatūras kategorijas nosaukums</td><td>+</td><td>Maksimāli 255 simboli.</td></tr>
        <tr><td>Kategorijas mērvienība</td><td>+</td><td>Materiāla mērvienība. Maksimāli 15 simboli. </td></tr>
        <tr><td>Piegādesveids</td><td>-</td><td>Maksimāli 50 simboli. </td></tr>
        <tr><td>TS Numurs</td><td>-</td><td>Maksimāli 50 simboli. </td></tr>
        <tr><td>Kategorijas izmaiņas</td><td>-</td><td>Maksimāli 50 simboli. </td></tr>
        <tr><td>Izmaiņu piezīmes</td><td>-</td><td>Maksimāli 250 simboli. </td></tr>        
        <tr><td>TS_ID</td><td>-</td><td>Cipars formatā [xxx].</td></tr>
        <tr><td>TS_Statuss_prim.</td><td>-</td><td>Maksimāli 50 simboli. </td></tr>
        <tr><td>MR statuss</td><td>-</td><td>Maksimāli 50 simboli. </td></tr>
        <tr><td>Kat.pielietojums</td><td>+</td><td>Maksimāli 50 simboli. </td></tr>
        <tr><td>Kat.nozīmīgums</td><td>+</td><td>Maksimāli 50 simboli. </td></tr>
        <tr><td>TS uztur.</td><td>+</td><td>Maksimāli 50 simboli. </td></tr>
        <tr><td>Aizvietojamas nomenklatūras</td><td>+</td><td>Maksimāli 50 simboli. </td></tr>
        <tr><td>Vienuma tips</td><td>+</td><td>Maksimāli 50 simboli. </td></tr>
        <tr><td>Ceļš</td><td>+</td><td>Maksimāli 50 simboli. </td></tr>
       </table>'    
);

INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`)
VALUES ('IMPORTS', 'MATERIAL_CATEGORY', 'Materiālu kategorijas');

CREATE TABLE `kl_komplektacijas` (
	`KMTK_ID` INT(11) NOT NULL AUTO_INCREMENT,	
	`KMTK_KATEGORIJAS_KODS` CHAR(8) NOT NULL COLLATE 'utf8_latvian_ci',
	`KMTK_KATEGORIJAS_NOSAUKUNS` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci',
    `KMTK_KOMPLEKTACIJA` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci',
	PRIMARY KEY (`KMTK_ID`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM
AUTO_INCREMENT=1
;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES ('REQUIREMENTS_COMPLECTATION',
       '<h3>Komplektacijas importam lūdzam izmantot daus Excel 97-2003 formātā</h3>
        <table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr> 
        <tr><td>Nomenklatūras kategorijas kods</td><td>+</td><td>Maksimāli 8 simboli formatā [xxxx.xxx].</td></tr>
        <tr><td>Nomenklatūras kategorijas nosaukums</td><td>+</td><td>Maksimāli 255 simboli.</td></tr>
        <tr><td>Komplektācija</td><td>+</td><td>Maksimāli 250 simboli. </td></tr>
       </table>'    
);

INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`)
VALUES ('IMPORTS', 'COMPLECTATION', 'Materiālu komplektacija');

CREATE TABLE `kl_materialu_komplekt` (
	`KTMK_ID` INT(11) NOT NULL AUTO_INCREMENT,	
	`KTMK_KATEGORIJAS_KODS` CHAR(8) NOT NULL COLLATE 'utf8_latvian_ci',
	`KTMK_KATEGORIJAS_NOSAUKUNS` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci',
    `KTMK_MATERIAL_KODS` CHAR(7) NOT NULL COLLATE 'utf8_latvian_ci',
	`KTMK_MATERIAL_NOSAUKUNS` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci',
    `KTMK_KOMPLEKTACIJA` VARCHAR(250) NOT NULL COLLATE 'utf8_latvian_ci',
	PRIMARY KEY (`KTMK_ID`),
    INDEX `KTMK_MATERIAL_KODS` (`KTMK_MATERIAL_KODS`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM
AUTO_INCREMENT=1
;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES ('REQUIREMENTS_MATERIAL_COMPLECTATION',
       '<h3>Materiālu komplektacijas importam lūdzam izmantot daus Excel 97-2003 formātā</h3>
        <table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr> 
        <tr><td>Nomenklatūras kategorijas kods</td><td>+</td><td>Maksimāli 8 simboli formatā [xxxx.xxx].</td></tr>
        <tr><td>Nomenklatūras kategorijas nosaukums</td><td>+</td><td>Maksimāli 255 simboli.</td></tr>
        <tr><td>Nomenklatūras kods</td><td>+</td><td>Maksimāli 8 simboli formatā [xxxx.xxx].</td></tr>
        <tr><td>Nomenklatūras nosaukums</td><td>+</td><td>Maksimāli 255 simboli.</td></tr>
        <tr><td>Komplektācija</td><td>+</td><td>Maksimāli 250 simboli. </td></tr>
       </table>'    
);

INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`)
VALUES ('IMPORTS', 'MATERIAL_COMPLECTATION', 'Materiālu komplektacija');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('COMPLECTATION','Komplektācija' ),
('CROSSECTION','Šķērsgriezums' );

ALTER TABLE `materiali` ADD COLUMN `MATR_CROSSECTION` VARCHAR(20) NULL;
ALTER TABLE `materiali` ADD COLUMN `MATR_COMPLECTATION` VARCHAR(50) NULL;