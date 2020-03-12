INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)  VALUES (NULL, 'TO_IDN', 'TO_IDN');
INSERT INTO `FMK_MESSAGES` (`id`, `code`, `text`)  VALUES (NULL, 'TO_ID', 'TO_ID');

ALTER TABLE `AKTI` ADD `RAKT_TO_IDN` INT(12) DEFAULT 0 NULL;
ALTER TABLE `AKTI` ADD `RAKT_TO_ID` varchar(4)  NULL;

ALTER TABLE `KL_MMS_DARBI` ADD `KMSD_TO_IDN` INT(12) DEFAULT 0 NULL;
ALTER TABLE `KL_MMS_DARBI` ADD `KMSD_TO_ID` varchar(4)  NULL;

UPDATE `FMK_MESSAGES` SET `text` = '<table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr>
           <th>Kolonas dati</th>
           <th>Obligâts</th>
           <th>Kolonas datu apraksts</th>
        </tr>
        <tr>
            <td>Kods</td>
            <td>+</td>
            <td>MMS darba kods. Maksimâli 150 simboli. </td>
        </tr>
        <tr>
            <td>Cilvekstundas</td>
            <td>+</td>
            <td>Cipars formatâ [xxxxx.xx]. </td>
        </tr>
        <tr>
            <td>Materiâla izmaksas</td>
            <td>+</td>
            <td>Cipars formatâ [xxxxx.xx]. </td>
        </tr>
        <tr>
            <td>Ceturksnis</td>
            <td>+</td>
            <td>Atïautas vçrtîbas: 1, 2, 3, 4. </td>
        </tr>
        <tr>
            <td>Gads</td>
            <td>+</td>
            <td>Cipars formatâ [xxxx]. </td>
        </tr>
        <tr>
            <td>Problemobjekts</td>
            <td>+</td>
            <td>Atïautas vçrtîbas: 0, 1 </td>
        </tr>
        <tr>
            <td>Struktûrvienîbas kods</td>
            <td>+</td>
            <td>Cipars formatâ [xxxx]. </td>
        </tr>
<tr>
            <td>Darbuzòçmçjs</td>
            <td>-</td>
            <td>Darbuzòçmçja identifikators. Cipars.</td>
        </tr>
        <tr>
            <td>Lîguma Nr.</td>
            <td>+</td>
            <td>Vispârîgâs vienoðanâs nr. Maksimâli 20 simboli.</td>
        </tr>
<tr>
            <td>DU trases</td>
            <td>+</td>
            <td>Atïautas vçrtîbas: 0, 1 </td>
        </tr>
        <tr><td>1z</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>2z</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>3z</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>4z</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>5z</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>6z</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>7z</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>8z</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>9z</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>1v</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>2v</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>3v</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>4v</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>5v</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>6v</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>7v</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>8v</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>9v</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>10v</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr><td>11v</td><td>+</td><td>Cipars formatâ [xxxxx.xx].</td></tr>
        <tr>
            <td>Operatîvais apzîmçjums</td>
            <td>-</td>
            <td>Operatîvais apzîmçjums. Maksimâli 250 simboli. </td>
        </tr>
        <tr>
            <td>Darba nosaukums (izdrukâm)</td>
            <td>-</td>
            <td>Darba nosaukums (izdrukâm). Maksimâli 250 simboli. </td>
        </tr>
        <tr>
            <td>TO_IDN</td>
            <td>+</td>
            <td>Cipars formatâ [xxxxxxxxxxxx]. </td>
        </tr>
        <tr>
            <td>TO_ID</td>
            <td>-</td>
            <td> Maksimâli 4 simboli. </td>
        </tr>
       </table>'
WHERE `code` = 'REQUIREMENTS_MMS_WORKS';

ktl.14.inc
ktl.14.2.tpl
ktl.13.inc
dbProc.class
act.s.1.inc
act.s.2.tpl