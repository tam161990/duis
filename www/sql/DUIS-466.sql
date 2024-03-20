ALTER TABLE `lietotaji` ADD `RLTT_IR_PPA` INT(1) NOT NULL DEFAULT 0;

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('PPA_ACCESS', 'Piekļūve PPA'),
('PPA', 'Provizoriskai plānotais atslēgums');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('PROJRCT_NUMBER', 'PPA kods');

INSERT INTO `kl_ref_kolonnas` (`KLKL_COLUMN`, `KLKL_TITLE`, `KLKL_CATALOG`, `KLKL_IS_DEFAULT`)
VALUES 
('PPACode', 'PPA kods', 'PPA', 0),
('IssueStatus', 'PPA pieteikums statuss', 'PPA', 0),
('Precinct', 'Iecirknis (Atbildības teritorija)', 'PPA', 0),
('DPNEngineer', 'DPN plānošanas inženieris', 'PPA', 0),
('JobCode', 'Darba pieteikuma kods', 'PPA', 1),
('JobType', 'Darba pieteikuma tips', 'PPA', 0),
('JobStatus', 'Darba pieteikums statuss', 'PPA', 0),
('JobDescription', 'Darba apraksts', 'PPA', 0),
('TechObjType', 'Tehniskā objekta veids', 'PPA', 0),
('TechObj', 'Tehniskais objekts', 'PPA', 0),
('PersonInCharge', 'Atbildīgais', 'PPA', 0),
('ConstructionMerchant', 'Būvkomersants', 'PPA', 0),
('ExpectedExecutionDate', 'Paradzemais izpildes datums', 'PPA', 0);


