ALTER TABLE `lietotaji` ADD `RLTT_IR_LIMITCARD` INT(1) NOT NULL DEFAULT 0;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('LIMITCARD_ACCESS', 'Piekļūve Limitkarte'),
('LIMITCARD', 'LIMITKARTE');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('PROJRCT_MATERIAL_REPORT', 'Materiālu izdevumu karte projektam'),
('UNCOMPLETED_PROJECT_REPORT', 'AS Sadales tīkls Neizpildītie PR, ieskaitot Expense');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('PROJRCT_NUMBER', 'Projekt Nr. (No Kvikstepa)');

INSERT INTO `kl_ref_kolonnas` (`KLKL_COLUMN`, `KLKL_TITLE`, `KLKL_CATALOG`, `KLKL_IS_DEFAULT`)
VALUES 
('projectNr', 'Projekta Nr.', 'LIMITCARD_PROJRCT_MATERIAL', 0),
('projectTaskNr', 'Projekta daļas Nr.', 'LIMITCARD_PROJRCT_MATERIAL', 0),
('projectName', 'Projekta nosaukums', 'LIMITCARD_PROJRCT_MATERIAL', 0),
('projectTaskName', 'Projekta daļas nosaukums', 'LIMITCARD_PROJRCT_MATERIAL', 0),
('prNr', 'PR Nr.', 'LIMITCARD_PROJRCT_MATERIAL', 0),
('documentNr', 'Dokumenta Nr.', 'LIMITCARD_PROJRCT_MATERIAL', 0),
('transactionDate', 'Tranzakcijas datums', 'LIMITCARD_PROJRCT_MATERIAL', 0),
('period', 'Periods', 'LIMITCARD_PROJRCT_MATERIAL', 0),
('itemNumber', 'Nomenklatūras kods', 'LIMITCARD_PROJRCT_MATERIAL', 1),
('itemName', 'Nomenklatūras nosaukums', 'LIMITCARD_PROJRCT_MATERIAL', 0),
('itemUnitPrice', 'Darījuma vienības cena', 'LIMITCARD_PROJRCT_MATERIAL', 0),
('uom', 'Mērvienība', 'LIMITCARD_PROJRCT_MATERIAL', 0),
('transactionQty', 'Tranzakcijas daudzums', 'LIMITCARD_PROJRCT_MATERIAL', 0),
('transactionAmount', 'Tranzakcijas summa koncerna valūtā EUR', 'LIMITCARD_PROJRCT_MATERIAL', 0);

INSERT INTO `kl_ref_kolonnas` (`KLKL_COLUMN`, `KLKL_TITLE`, `KLKL_CATALOG`, `KLKL_IS_DEFAULT`)
VALUES 
('projectNr', 'Projekta Nr.', 'UNCOMPLETED_PROJECT_REPORT', 0),
('projectTaskNr', 'Projekta daļas Nr.', 'UNCOMPLETED_PROJECT_REPORT', 0),
('prDescr', 'Projekta apraksts', 'UNCOMPLETED_PROJECT_REPORT', 0),
('prNr', 'PR Nr.', 'UNCOMPLETED_PROJECT_REPORT', 0),
('prType', 'PR veids', 'UNCOMPLETED_PROJECT_REPORT', 0),
('prStatus', 'PR statuss', 'UNCOMPLETED_PROJECT_REPORT', 0),
('creationDate', 'Izveidošanas datums', 'UNCOMPLETED_PROJECT_REPORT', 0),
('approvedDate', 'Apstiprināšanas datums', 'UNCOMPLETED_PROJECT_REPORT', 0),
('projectTaskName', 'PR apraksts', 'UNCOMPLETED_PROJECT_REPORT', 0),
('itemNumber', 'Nomenklatūras kods', 'UNCOMPLETED_PROJECT_REPORT', 1),
('itemName', 'Nomenklatūras apraksts', 'UNCOMPLETED_PROJECT_REPORT', 0),
('prLineNum', 'PR rindas Nr.', 'UNCOMPLETED_PROJECT_REPORT', 0),
('poNum', 'PO sistemas Nr.', 'UNCOMPLETED_PROJECT_REPORT', 0),
('itemUnitPrice', 'Vienības cena', 'UNCOMPLETED_PROJECT_REPORT', 0),
('amtReq', 'Pieprasījuma summa funkcionālajā valūtā', 'UNCOMPLETED_PROJECT_REPORT', 0),
('uom', 'Mērvienība', 'UNCOMPLETED_PROJECT_REPORT', 0),
('quantity', 'Pieprasītais daudzums', 'UNCOMPLETED_PROJECT_REPORT', 0),
('quantityDelivered', 'Faktiski izsniegtais daudzums', 'UNCOMPLETED_PROJECT_REPORT', 0),
('quantityLeft', 'Nepieciešamais izpildāmais daudzums', 'UNCOMPLETED_PROJECT_REPORT', 0),
('isCompleted', 'Ir izpildīts', 'UNCOMPLETED_PROJECT_REPORT', 0);








