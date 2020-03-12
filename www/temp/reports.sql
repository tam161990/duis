INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'REPORT_ACT_TOTAL', 'Darbu izpildes aktu kopsavilkums');
INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'REPORT_WORK_TOTAL', ' Darba pozîciju kopsavilkums');
INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'REPORT_MATERIAL_TOTAL', 'Akts par izlietotiem materiâliem');

INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'PCT', 'PVN');
INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'TOTAL_WITH_PCT', 'Kopâ ar PVN');
INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'EXPORT_TO_PDF', 'Eksportçt uz PDF');

INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'UNIT_PRICE', 'Vienîbas cena');

INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'STOCK_NUMBER', 'Nomenklatûras nr.');

INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'ST_COMPANY_NAME', 'AS "Sadales tîkls"');

INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'TOATAL_MATERIAL_NAME', 'Nomenklatûras nosaukums');
INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'TOTAL_WORK_NAME', 'Kalkulâcijas nosaukums');

INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'ACT_ACCEPT_TIME', 'Saskaòoðanas datums');
INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'ACT_TOTAL_WORK_PRICE', 'Darbaspçka izmaksas');
INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'ACT_TOTAL_MATER_PRICE', 'DU materiâlu izmaksas');
INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'ACT_TOTAL_PRICE', 'Kopçjâs izmaksas');

INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'REPORT_WORK_OFFER', 'Pasûtîtâjs');
INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'REPORT_WORKER', 'Izpildîtâjs');
INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'REPORT_AGREEMENT_NO', 'Vispârîgâ vienoðanâs Nr.___________');
INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'REPORT_HEADER_1', 'Uzturçðanas remonta darbi');

INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'REPORT_REGION', 'reìions');
INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)
VALUES (NULL, 'REPORT_SECTION', 'nodaïa');

ALTER TABLE `search_criteria` ADD `SERCH_ID` INT( 11 ) NOT NULL AUTO_INCREMENT ,
ADD PRIMARY KEY ( `SERCH_ID` ) ;