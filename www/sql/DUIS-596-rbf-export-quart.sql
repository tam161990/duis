-- Starpakt period for each exported rbf_akta_darbi row (used on economist RETURN)
ALTER TABLE `rbf_akta_darbi`
	ADD COLUMN `RADR_ACT_QUART` TINYINT(1) NULL DEFAULT NULL COMMENT 'Starpakta periods (1-3) when exported' AFTER `RADR_IS_PROCESSED`;
