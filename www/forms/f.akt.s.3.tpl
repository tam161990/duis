<h1><?=text::toUpper(text::get(TAB_MATERIAL));?></h1>
<?= $oFormMaterialTab -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="2"><?= $oFormMaterialTab -> getMessage(); ?></td>
	</tr>
    <tr>
		<td valign="top">
        <?
        $x = 0;
        foreach ($aMaterials as $d => $aDayMaterial)
        {
        ?>
        <table cellpadding="5" cellspacing="1" border="0" width="100%">
		   <tr class="table_head_2">

				<th width="12%"><?=text::get('CODE');?></th>
				<th width="37%"><?=text::get('NAME');?></th>
				<th  width="12%"><?=text::get('UNIT_OF_MEASURE');?></th>
                <th  width="12%"><?=text::get('PRICE');?></th>
                <th  width="12%"><?=text::get('AMOUNT');?></th>
                <? if($tame) { ?>
                    <th  width="12%"><?=text::get('AMOUNT_KOR');?></th>
                <? } ?>
				<th  width="12%"><?=text::get('PRICE_TOTAL');?></th>
			 	<th width="3%">&nbsp;</th>
			</tr>

	  <?
        foreach ($aDayMaterial as $j => $actMaterial)
		{
           if($tameMaterial && $actMaterial['MATR_DAUDZUMS'] != $actMaterial['MATR_DAUDZUMS_KOR']) {
                $changestyle = "font-weight:bold;"   ;
            } else {
                $changestyle = "font-weight:normal;"   ;
            }
           if($actMaterial['MATR_IS_WORKER'] != 1)
           {
                $pricestyle = "color:#e4edd8;  font-size:1px;"   ;
           ?>
            <tr class="table_cell_3" style="<?=$changestyle;?>" id="blank_mat<?= $x; ?>">

           <?}
           else
           {
                $pricestyle = "color:#ffffff;  font-size:11px;"   ;
           ?>
            <tr class="table_cell_4" style="<?=$changestyle;?>" id="blank_mat<?= $x; ?>">
           <?
             }
		    ?>
				<td>
                    <?= $oFormMaterialTab->getElementHtml('id['.$x.']'); ?>
                    <?= $oFormMaterialTab->getElementHtml('code['.$x.']'); ?>
                </td>
				<td><?= $oFormMaterialTab->getElementHtml('title['.$x.']'); ?></td>
				<td><?= $oFormMaterialTab->getElementHtml('unit['.$x.']'); ?></td>
                <?if($isEDUser || $isAdmin){ ?>
                <td><?= $oFormMaterialTab->getElementHtml('price['.$x.']'); ?></td>
                <?}else{ ?>
                <td style="<?=$pricestyle;?>"><?= $oFormMaterialTab->getElementHtml('price['.$x.']'); ?></td>
                <?}?>
                <? if($tameMaterial) { ?>
					<td><?= $oFormMaterialTab->getElementHtml('amount_km['.$x.']'); ?></td>
					<td><?= $oFormMaterialTab->getElementHtml('amount_kor_mat['.$x.']'); ?></td>
				<? } else { ?>
					<td><?= $oFormMaterialTab->getElementHtml('amount_mat['.$x.']'); ?></td>
                <? } ?> 
                <?if($isEDUser || $isAdmin ){ ?>
                    <td><?= $oFormMaterialTab->getElementHtml('total_mat['.$x.']'); ?></td>
                    <?}else{ ?>
                    <td  style="<?=$pricestyle;?>"><?= $oFormMaterialTab->getElementHtml('total_mat['.$x.']'); ?></td>
                <?}?>
				
             	<td>
                    <? if(!$isReadonly && ( empty($actMaterial['MATR_APPROVE_DATE'])  || $tameMaterial ))  {?>
                    <?= $oFormMaterialTab->getElementHtml('mat_del['.$x.']'); ?>
                    <? } else{ ?>
                    &nbsp;
                    <? } ?>
                </td>
			</tr>

        <?
        $x++;
        }
        
        ?>
        <tr>
            <td align="right" colspan="2"><b><?=text::get('WORK_APPROVE_DATE');?>:</b></td>
            <td align="left" colspan="2"><b><?= isset($workApproveDate[$d])?$workApproveDate[$d]:''; ?></b></td>
            <? if($tameMaterial) { ?>
                <td align="right" colspan="3"><b><?=text::get('TOTAL');?>:</b></td>
                <td align="center"><b><?= isset($totalTime[$d])?$totalTime[$d]:''; ?></b></td>
            <? } else { ?>
                <td align="right" colspan="3">&nbsp;</td>
                <td align="center">&nbsp;</td>
            <? }  ?>    
       </tr>
        
       <?  
        }
         ?>
	    </table>
        </td>
        <td width="20%"  valign="top">
            <table cellpadding="5" cellspacing="1" border="0" align="center" width="100%">
            <? if(!$isReadonly)  {
	      
              foreach($favorit as $i=>$val){?>
             <tr>
                <td bgcolor="white"><?= $oFormMaterialTab->getElementHtml('group['.$i.']'); ?></td>
             </tr>
            <? }} ?>
            </table>
            <br />
            <table cellpadding="5" cellspacing="0" border="0" align="center">
            <tr>
             <? if(!$isReadonly)  {?>
            	<td><?= $oFormMaterialTab -> getElementHtml('save'); ?></td>
             <? } ?>

             </tr>
             <tr>
                <? if( $tameMaterial)  {?>
                   <td><?= $oFormMaterialTab -> getElementHtml('export'); ?></td>
                <? } ?>
   
                </tr>
            </table>
        </td>
	</tr>

</table>
<?= $oFormMaterialTab -> getFormBottom(); ?>

