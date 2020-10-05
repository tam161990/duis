INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`)
VALUES ('IMPORTS', 'DUUSERS', 'DU lietotāji');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES ('REQUIREMENTS_DU_USERS',
       '<table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr>         
        <tr><td>Lietotāja vārds</td><td>+</td><td>Lietotāja sistēmas vārds. Maksimāli 30 simboli.</td></tr>
        <tr><td>Vārds</td><td>+</td><td>DU lietotāja vārds. Maksimāli 30 simboli.</td></tr>
        <tr><td>Uzvārds</td><td>+</td><td>DU lietotāja uzvārds. Maksimāli 30 simboli.</td></tr>
        <tr><td>Darbuzņēmēja kods</td><td>+</td><td>Var saturēt tikai sekojošus simbolus `0`-`9`. Maksimāli 11 simboli.</td></tr>
        <tr><td>Trašu tīrītājs</td><td>+</td><td>Cipars formātā [0/1]</td></tr>
        <tr><td>Pēc līguma</td><td>+</td><td>Cipars formātā [0/1]</td></tr>
        <tr><td>Projektētajs</td><td>+</td><td>Cipars formātā [0/1]</td></tr>
       </table>'    
);