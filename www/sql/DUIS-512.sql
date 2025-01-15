CREATE TABLE `kl_writeoff_code_new` (
	`KWRC_ID` INT(11) NOT NULL AUTO_INCREMENT,	
	`KWRC_KKAL_SHIFRS` CHAR(5) NOT NULL COLLATE 'utf8_latvian_ci',
	`KWRC_KKAL_NOSAUKUMS` VARCHAR(150) NOT NULL COLLATE 'utf8_latvian_ci',
    `KWRC_KODS` INT(7) NOT NULL,
    `KWRC_NOSAUKUMS` VARCHAR(150) NOT NULL COLLATE 'utf8_latvian_ci',
    `KWRC_CREATOR` INT(11),
    `KWRC_CREATED` DATETIME,
    `KWRC_EDITOR` INT(11),
    `KWRC_EDITED` DATETIME,
	PRIMARY KEY (`KWRC_ID`)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM
AUTO_INCREMENT=1
;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES ('REQUIREMENTS_WRITE_OFF_CODE',
       '<h3>Izmaksu konta importam lūdzam izmantot daus Excel 97-2003 formātā</h3>
        <table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr> 
        <tr><td>Kalkulācijas šifrs</td><td>+</td><td>Maksimāli 5 simboli.</td></tr>
        <tr><td>Kalkulācijas nosaukums</td><td>+</td><td>Maksimāli 150 simboli.</td></tr>
        <tr><td>Darba izmaksu veida kods</td><td>+</td><td>Cipars formatā [xxxxxxx].</td></tr>
        <tr><td>Darba izmaksu veida nosaukums</td><td>+</td><td>Maksimāli 150 simboli.</td></tr>
       </table>'    
);

INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`)
VALUES ('IMPORTS', 'WRITE_OFF_CODES', 'Izmaksu konti');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('WRITE_OFF_CODES','Izmaksu konti' ),
('WRITE_OFF_CODE','Darba izmaksu veida kods' ),
('WRITE_OFF_TITLE', 'Darba izmaksu veida nosaukums'),
('WRITE_OFF_CODES_INFO', 'Izmaksu konta informācija'),
('ERROR_EXISTS_WRITE_OFF_CODE', 'Izmaksu konts ar šādu kodu jau ir definēts.');

INSERT INTO `kl_ref_kolonnas` (`KLKL_COLUMN`, `KLKL_TITLE`, `KLKL_CATALOG`, `KLKL_IS_DEFAULT`)
VALUES 
('KWRC_KKAL_SHIFRS', 'Kalkulācijas šifrs', 'KL_IZMAKSU_KONTI', 0),
('KWRC_KKAL_NOSAUKUMS', 'Kalkulācijas nosaukums', 'KL_IZMAKSU_KONTI', 0),
('KWRC_KODS', 'Darba izmaksu veida kods', 'KL_IZMAKSU_KONTI', 1),
('KWRC_NOSAUKUMS', 'Darba izmaksu veida nosaukums', 'KL_IZMAKSU_KONTI', 0);

INSERT INTO  `kl_akta_veids` (`KAKV_KODS`,`KAKV_NOSAUKUMS`,`KAKV_IR_AKTIVS`)
VALUES(90, 'Pers', 0);

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('PERS','Pers' );

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('WRITE_OFF_CODE_ELEMENT','71882 Dabas stihiju radīto avārijas bojājumu novēršana / Objekta kods K00' ),
('WRITE_OFF_CODE_PERS','71889 Trešo personu radīto zaudējumu bojājumu novēršana' );