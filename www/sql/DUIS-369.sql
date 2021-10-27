alter table `AUTO_ACT_STATUS` add `AAST_PROJECT_NO` VARCHAR(250);
alter table `AUTO_ACT_STATUS_LOG` add `AAST_PROJECT_NO` VARCHAR(250);
alter table `AKTI` add `RAKT_PROJECT_NO` VARCHAR(250);

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('ORDER_MATERIAL', 'Izveidot Materiālu pieprasījumu'),
('MATEREIAL_CODE', 'Nomenklatūraa kods');

alter table `materiali` add `MATR_NOM_KODS` CHAR(7);
alter table `materiali` add `MATR_NOM_STATUS` CHAR(1); -- 1 - ok, 2-check; 3-error

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
('XML_EXPIDENTURE_ORG', '3 AS Sadals tīkls EUR'),
('XML_BUDZET_TYPE', 'Kapitālieguldījumu budžets');

alter table `AKTI` add `RAKT_KEY_OBJECT` CHAR(1) DEFAULT '0';
alter table `AKTI` add `RAKT_CONSTRUCT_COMPANY` VARCHAR(250);

INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`) VALUES 
('PROJECT_EXPORT_DEFAULT', 'DU_DELIVER', 'DU piegāde');