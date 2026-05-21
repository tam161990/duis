-- DUIS-576: RBF aktu importa validācijas ziņojumi (Excel 1. lapa vs darbu veidne)

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES
(
	'RBF_IMPORT_ACTS_SHEET_LOOKS_LIKE_WORKS',
	'Excel faila 1. lapa neatbilst aktu veidnei — tā izskatās kā darbu lapa (piemēram, kolonnā A ir „Uzturēšanas darba numurs” vai kolonnā B — kalkulācijas šifrs). Ja augšupielādējat tikai darbus, izvēlieties „Tikai darbi”. Ja fails satur abas lapas, pārliecinieties, ka pirmā lapa ir akti un lapu secība kā instrukcijā.'
),
(
	'RBF_IMPORT_ACT_AUTHOR_WORK_STATUS_ROW',
	'1. lapas rinda %s: kolonna „Autors” satur darba statusu (%s). Augšupielādes tips vai lapas secība, visticamāk, ir nepareiza — izmantojiet „Tikai darbi”, ja augšupielādējat tikai darbus.'
)
ON DUPLICATE KEY UPDATE `TEXT` = VALUES(`TEXT`);
