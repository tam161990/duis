INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'GPS', 'GPS');

INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'ADDING_FILES', 'Piesaistîtie faili');

--
-- Table structure for table `gps_faili`
--

CREATE TABLE IF NOT EXISTS `GPS_FAILI` (
  `GFLS_ID` int(11) NOT NULL auto_increment,
  `GFLS_NOSAUKUMS` varchar(30) collate utf8_latvian_ci NOT NULL,
  `GFLS_REGION` varchar(3) NOT NULL,
  `GFLS_DATUMS` datetime NOT NULL default '0000-00-00 00:00:00',
  `GFLS_META_INFO` varchar(50) collate utf8_latvian_ci NOT NULL default 'application/octet-stream',
  PRIMARY KEY  (`GFLS_ID`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_latvian_ci AUTO_INCREMENT=1 ;
