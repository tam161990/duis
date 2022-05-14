CREATE TABLE `kl_kalkulacijas_normas` (
        KKNO_ID INT(11) NOT NULL AUTO_INCREMENT COMMENT 'Ieraksta identifikātors',
        KKNO_KKAL_SHIFRS CHAR(5) NOT NULL COMMENT 'kalkulācijas šifrs',
        KKNO_KKAL_NOSAUKUMS VARCHAR(150) NOT NULL COMMENT 'kalkulācijas nosaukums',
        KKNO_NORM FLOAT(7,2) COMMENT 'kalkulācijas c.st. norma',
    PRIMARY KEY (`KKNO_ID`),
	UNIQUE INDEX `U_KKNO_KKAL_SHIFRS` (KKNO_KKAL_SHIFRS)
)
COLLATE='utf8_latvian_ci'
ENGINE=MyISAM
AUTO_INCREMENT=1
;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('CALC_WORK_H_NORM', 'c.st. norma');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('CALC_WORK_H_NORM_SUM', 'c.st. summa');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES ('REQUIREMENTS_CALC_NORMAS',
       '<h3>Kalkulācijas c.st. normas importam lūdzam izmantot daus Excel 97-2003 formātā</h3>
        <table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr> 
        <tr><td>Kalkulācijas šifrs</td><td>+</td><td>Maksimāli 5 simboli.</td></tr>
        <tr><td>Kalkulācijas nosaukums</td><td>+</td><td>Maksimāli 150 simboli.</td></tr>
        <tr><td>Kalkulācijas c.st. norma</td><td>+</td><td>Maksimāli 7 simboli formatā [xxxx.xx]</td></tr>
       </table>'    
);

INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`)
VALUES ('IMPORTS', 'CALC_NORMAS', 'Kalkulācijas c.st. normas');

INSERT INTO `kl_ref_kolonnas`(KLKL_COLUMN,KLKL_TITLE,KLKL_CATALOG,KLKL_IS_DEFAULT) VALUES 
('KKNO_KKAL_SHIFRS', 'Kalkulācijas šifrs', 'KL_KALKULACIJAS_NORMAS', 1),
('KKNO_KKAL_NOSAUKUMS', 'Kalkulācijas nosaukums', 'KL_KALKULACIJAS_NORMAS', 0),
('KKNO_NORM', 'c.st. norma', 'KL_KALKULACIJAS_NORMAS', 0);

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('CALC_WORK_H_NORMS', 'c.st. normas');