-- DUIS-593: Move email addresses from kl_rbf_darbuznemeji to kl_rbf_du_vv
-- This allows emails to be linked to specific VV numbers

-- Add email field to kl_rbf_du_vv table
ALTER TABLE `kl_rbf_du_vv` 
ADD COLUMN `RBDV_KONTAKTI` VARCHAR(500) NULL DEFAULT NULL COMMENT 'Email addresses (semicolon separated)' AFTER `RBDV_RBTR_KODS`;

-- Add text constants for UI
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
(
	'RBF_VV_CONTACTS',
	'Kontakti (e-pasts)'
)
ON DUPLICATE KEY UPDATE `TEXT` = VALUES(`TEXT`);

