INSERT INTO `kl_ref_kolonnas` (`KLKL_COLUMN`, `KLKL_TITLE`, `KLKL_CATALOG`, `KLKL_IS_DEFAULT`)
VALUES 
('ExecutorResponsiblePerson', 'Izpildītāja atbildīgā persona', 'PPA', 0),
('ExecutorResponsiblePersonPhone', 'Mobilais t.nr.', 'PPA', 0);

UPDATE `kl_ref_kolonnas` SET `KLKL_TITLE` = 'Pieteikuma atbildīgais' WHERE `KLKL_COLUMN` = 'PersonInCharge';