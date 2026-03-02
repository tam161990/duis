-- Add new status text keys for estimate file import
-- These need to be added to KL_TEKSTI table

-- Work not found in catalog
INSERT INTO `KL_TEKSTI` (`KTXT_ATSLEGA`, `KTXT_VERTIBA`, `KTXT_VALODA`) 
VALUES ('STATUS_WORK_NOT_FOUND', 'Darbs nav atrasts DUIS katalogā Kalkulācija', 'lv')
ON DUPLICATE KEY UPDATE `KTXT_VERTIBA` = 'Darbs nav atrasts DUIS katalogā Kalkulācija';

-- Material not found in catalog  
INSERT INTO `KL_TEKSTI` (`KTXT_ATSLEGA`, `KTXT_VERTIBA`, `KTXT_VALODA`) 
VALUES ('STATUS_MATERIAL_NOT_FOUND', 'Materiāls nav atrasts DUIS katalogā Kalkulācija', 'lv')
ON DUPLICATE KEY UPDATE `KTXT_VERTIBA` = 'Materiāls nav atrasts DUIS katalogā Kalkulācija';

-- Work already exists in project
INSERT INTO `KL_TEKSTI` (`KTXT_ATSLEGA`, `KTXT_VERTIBA`, `KTXT_VALODA`) 
VALUES ('STATUS_WORK_EXISTS', 'Darbs jau pievienots projektam', 'lv')
ON DUPLICATE KEY UPDATE `KTXT_VERTIBA` = 'Darbs jau pievienots projektam';

-- Material already exists in project
INSERT INTO `KL_TEKSTI` (`KTXT_ATSLEGA`, `KTXT_VERTIBA`, `KTXT_VALODA`) 
VALUES ('STATUS_MATERIAL_EXISTS', 'Materiāls jau pievienots projektam', 'lv')
ON DUPLICATE KEY UPDATE `KTXT_VERTIBA` = 'Materiāls jau pievienots projektam';

-- Amount not set
INSERT INTO `KL_TEKSTI` (`KTXT_ATSLEGA`, `KTXT_VERTIBA`, `KTXT_VALODA`) 
VALUES ('STATUS_AMOUNT_NOT_SET', 'Darba vai materiāla apjoms nav norādīts', 'lv')
ON DUPLICATE KEY UPDATE `KTXT_VERTIBA` = 'Darba vai materiāla apjoms nav norādīts';
