-- ED iecirkni
CREATE TABLE kl_ed_iecirkni_hist LIKE kl_ed_iecirkni;
INSERT INTO kl_ed_iecirkni_hist SELECT * FROM kl_ed_iecirkni;

DELEte from kl_ref_kolonnas where klkl_catalog = 'KL_ED_IECIRKNI' and klkl_column = 'KEDI_REGIONS';
UPDATE kl_ref_kolonnas SET klkl_is_default = 1 WHERE klkl_catalog = 'KL_ED_IECIRKNI' and klkl_column = 'KEDI_KODS';

UPDATE fmk_messages
set text = '<table cellpadding="3" cellspacing="0" border="1" width="100%">	
            <tr>	
            <th>Kolonas dati</th>	
            <th>Obligāts</th>	
            <th>Kolonas datu apraksts</th>	
            </tr>	
            <tr>	
                <td>Kods</td>	
                <td>+</td>	
                <td>ED iecirkņa kods. Unikāls. Var saturēt tikai sekojošus simbolus  `0`-`9`. Maksimāli 5 simboli. </td>	
            </tr>		       
            <tr>	
                <td>Nosaukums.</td>	
                <td>+</td>	
                <td>ED iecirkņa nosaukums. Maksimāli 30 simboli. </td>	
            </tr>	
            <tr>	
                <td>ED nodaļa</td>	
                <td>+</td>	
                <td>Maksimāli 30 simboli.</td>	
            </tr>	
            <td>Stihija</td>	
            <td>+</td>	
            <td>Cipars 0/1.</td>	
            </tr>	
        </table>'
where code = 'REQUIREMENTS_EDAREA';

-- ED contracts
CREATE TABLE kl_contract_hist LIKE kl_contract;
INSERT INTO kl_contract_hist SELECT * FROM kl_contract;

alter table kl_contract add column KONT_KEDI_KODS CHAR(5);

-- Kalkulacija
CREATE TABLE kl_kalkulacija_hist LIKE kl_kalkulacija;
INSERT INTO kl_kalkulacija_hist SELECT * FROM kl_kalkulacija;

alter table kl_kalkulacija add column KKAL_KEDI_KODS CHAR(5);

UPDATE kl_ref_kolonnas SET klkl_column = 'KKAL_KEDI_KODS' WHERE klkl_catalog = 'KL_KALKULACIJA' and klkl_column = 'KKAL_KEDI_SECTION';
UPDATE kl_ref_kolonnas SET klkl_title = 'ED iecirkņis' WHERE klkl_catalog = 'KL_KALKULACIJA' and klkl_column = 'KKAL_KEDI_KODS';

UPDATE fmk_messages
set text = '<h3>Kalkulācijas importal lūdzam izmantot daus Excel 97-2003 formātā</h3>
        <table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr> 
        <tr><td>Grupas kods</td><td>+</td><td>Kalkulācijas grupas kods. Var saturēt tikai sekojošus simbolus `a`-`z`, `A`-`Z`, `0`-`9`. Maksimāli 5 simboli.</td></tr>
        <tr><td>Kalkulācijas šifrs</td><td>+</td><td>Kalkulācijas šifrs. Unikāls. Var saturēt tikai sekojošus simbolus `0`-`9`. Maksimāli 5 simboli.</td></tr>
        <tr><td>Kalkulācijas nosaukums</td><td>+</td><td>Kalkulācijas nosaukums. Maksimāli 150 simboli.</td></tr>
        <tr><td>Mērvienība</td><td>+</td><td>Kalkulācijas mērvienība. Maksimāli 15 simboli.</td></tr>
        <tr><td>Apraksts</td><td>+</td><td>Kalkulācijas apraksts. Maksimāli 2000 simboli.</td></tr>
        <tr><td>Fiziskais rādītājs</td><td>+</td><td>Fiziska rādītāja pazime. Var saturēt tikai sekojošus simbolus [`2`-`9`]`z` vai [`2`-`11`]`v`. Maksimāli 3 simboli.</td></tr>
        <tr><td>Darbuzņēmējs</td><td>+</td><td>Darbuzņēmēja identifikators. Cipars.</td></tr>
        <tr><td>Līguma Nr.</td><td>+</td><td>Vispārīgās vienošanās nr. Maksimāli 20 simboli.</td></tr>
        <tr><td>ED iecirkņis</td><td>+</td><td>ED iecirkņa kods. Cipars formātā [xxxxx].</td></tr>
        <tr><td>Plāna cena</td><td>+</td><td>Cipars formātā [xxxxx.xx].</td></tr>
        <tr><td>Neplāna cena</td><td>+</td><td>Cipars formātā [xxxxx.xx].</td></tr>
        <tr><td>Fiz.rād. koefic.</td><td>+</td><td>Cipars formātā [xxxxx.xx].</td></tr>
        <tr><td>Stihijas kalkul.</td><td>+</td><td>Stihijas kalkul. Cipars formātā [0/1]</td></tr>
        <tr><td>Trašu kalkulācija</td><td>+</td><td>Kalkulācija tiek izmantota trašu tīrīšanas darbiem. Cipars formātā [0/1]</td></tr>
        <tr><td>Ir aktīvs</td><td>+</td><td>Kalkulācija ir aktuāla. Cipars formātā [0/1]</td></tr>
       </table>'
where code = 'REQUIREMENTS_CALCULATION';

-- ST users
DELEte from kl_ref_kolonnas where klkl_catalog = 'KL_LIETOTAJI' and klkl_column = 'RLTT_REGIONS';

-- saskaņotāji
DELEte from kl_ref_kolonnas where klkl_catalog = 'KL_SASKANOTAJI' and klkl_column = 'SLTT_REGIONS';

-- act search
UPDATE search_criteria SET edRegion = NULL ;
ALTER TABLE search_criteria MODIFY edRegion CHAR(5);
ALTER TABLE search_criteria RENAME COLUMN edRegion TO edCode; -- in case of error rename manually

-- ED iecirkņi - manuāla labošna
-- Līgumi - labošana ar skriptu (excel)
-- Kalkulācija - enpty table -> full inport
DELETE FROM kl_kalkulacija;
-- akti - labošana ar skriptu no MMS un Contract