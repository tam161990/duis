ALTER TABLE `system_info`
	ADD COLUMN `SNFO_SUPERADMIN` VARCHAR(50) NULL DEFAULT NULL;
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('SUPERADMIN_NAME', '"SuperADMIN" sistēmas lietotāja vārds');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('SUPERADMIN_TITLE', 'Lietotājam ar lomu "SuperADMIN" ir atļauts:
<li>Labot visus laukus Akta galviņā</li>
<li>Labot un/vai dzēst arī reģistrētas pozīcijas statusos ĢENERĒETS, IEVADS, ATGRIEZTS</li>');
INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES ('SUPERADMIN', '"SuperADMIN"');
