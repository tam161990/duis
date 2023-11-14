
    
    <body class="frame_1">
  
    <h1><?=text::toUpper(text::get(ALL_MATERIAL));?></h1>
    <table cellpadding="5" cellspacing="1" border="0" width="100%">
        <tr><td align="right"><a href="javascript:close();">
            <img src="img/ico_end.gif" alt="<?= text::get('CLOSE'); ?>" border="0">
            </a></td></tr>
        <tr>
            <td valign="top">
            <?
            $x = 0;
            foreach ($aMaterials as $d => $aGroupMaterials)
            {
            ?>
            <table cellpadding="5" cellspacing="1" border="0" width="100%">
               <tr class="table_head_2">
                    <th width="5%"><?=text::get('CODE');?></th>
                    <th width="30%"><?=text::get('SINGLE_WORK_TYPE');?></th>
                    <th width="20%"><?=text::get('NAME');?></th>
                    <th  width="5%"><?=text::get('UNIT_OF_MEASURE');?></th>
                    <th  width="5%"><?=text::get('AMOUNT');?></th>
                    <th  width="10%"><?=text::get('COMPLECTATION');?></th>
                    <th  width="10%"><?=text::get('CROSSECTION');?></th>
                    <th  width="15%"><?=text::get('COMMENT');?></th>
                </tr>    
          <?
          foreach ($aGroupMaterials as $j => $actMaterial)
          {
               $changestyle = "font-weight:normal;";
               if($actMaterial['MATR_IS_WORKER'] == 1)
               {
                    $pricestyle = "color:#e4edd8;  font-size:1px;"   ;
               ?>
                <tr class="table_cell_4" style="<?=$changestyle;?>" id="blank_mat<?= $i; ?>">
    
               <?}
               else
               {
                    $pricestyle = "color:#ffffff;  font-size:11px;"   ;
               ?>
                <tr class="table_cell_3" style="<?=$changestyle;?>" id="blank_mat<?= $i; ?>">
               <?}?>
    
    
                    <td><?= $actMaterial['MATR_KODS'] ; ?></td>
                    <td><?= $workType[$actMaterial['MATR_WORK_TYPE']] ; ?></td>   
                    <td><?= $actMaterial['MATR_NOSAUKUMS'] ; ?></td>
                    <td><?= $actMaterial['MATR_MERVIENIBA'] ; ?></td>                
                    <td><?= $actMaterial['MATR_DAUDZUMS'] ; ?></td>
                    <td><?= $actMaterial['MATR_COMPLECTATION'] ; ?></td>
                    <td><?= $actMaterial['MATR_CROSSECTION'] ; ?></td>
                    <td><?= $actMaterial['MATR_PIEZIMES'] ; ?></td>
                    
                </tr>
                
                <?
                $x++;
                }        
            }
            ?>
            
            </table>
            </td>            
        </tr>
        <tr><td align="right"><a href="javascript:close();">
            <img src="img/ico_end.gif" alt="<?= text::get('CLOSE'); ?>" border="0">
            </a></td></tr>
    </table>
   
    </body>
    
    