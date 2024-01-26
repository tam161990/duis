INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`)
VALUES ('REQUIREMENTS_VV_DELETE',
       '<h3>Masveida kalkulācijas dzēšanai lūdzam izmantot daus Excel 97-2003 formātā</h3>
       <table cellpadding="3" cellspacing="0" border="1" width="100%">
        <tr><th>Kolonas dati</th><th>Obligāts</th><th>Kolonas datu apraksts</th></tr>         
        <tr><td>VV numurs</td><td>+</td><td>Visparīgas vienošanas numurs. Maksimāli 20 simboli.</td></tr>
        <tr><td>Iecirkņa kods</td><td>-</td><td>Iecirkņa kods (piemēram, 36034). Var saturēt tikai sekojošus simbolus `0`-`9`. Maksimāli 5 simboli.</td></tr>
        </table>'    
);

INSERT INTO `FMK_MESSAGES` (`CODE`, `TEXT`) VALUES 
('VV_DELETE', 'Masveida kalkulācijas dzēšana');

INSERT INTO `kl_ref_kodi` (`KRFK_NOSAUKUMS`, `KRFK_VERTIBA`, `KRFK_NOZIME`)
VALUES ('IMPORTS', 'VV_DELETE', 'Masveida kalkulācijas dzēšana');