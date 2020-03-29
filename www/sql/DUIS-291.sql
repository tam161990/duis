INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`) VALUES 
('SIGNATURE', 'E', 'ar eparakstu'),
('SIGNATURE', 'P', 'ar fizisko parakstu');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('SIGNATURE_TYPE', 'Parakstīšanas veids'),
('ELRCTRONIC_SIGNATURE', 'Šis dokuments ir parakstīts ar drošu elektronisko parakstu un satur laika zīmogu.');

ALTER TABLE `AKTI` ADD COLUMN  `RAKT_SIGNATURE` VARCHAR(1) NOT NULL DEFAULT 'P';