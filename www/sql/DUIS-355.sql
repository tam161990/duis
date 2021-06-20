INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`)
VALUES ('IMPORTS', 'ACT_DELETE', 'Aktu dzēšana');

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES ('REQUIREMENTS_ACT_DELETE',
       '<table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr>         
        <tr><td>Kvikstep kods</td><td>+</td><td>Kvikstep kods dzēšamajam aktam. Maksimāli 20 simboli.</td></tr>
       </table>'    
);