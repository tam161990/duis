<h1><?=text::toUpper(text::get(TAB_MATERIAL));?></h1>
<?= $oFormMaterialTab -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="2"><?= $oFormMaterialTab -> getMessage(); ?></td>
	</tr>
    <tr>
		<td valign="top">
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
	   	foreach($aMaterials as $i=>$val)
		{
           if($tameMaterial && $val['MATR_DAUDZUMS'] != $val['MATR_DAUDZUMS_KOR']) {
                $changestyle = "font-weight:bold;"   ;
            } else {
                $changestyle = "font-weight:normal;"   ;
            }
           if($aMaterials[$i]['MATR_IS_WORKER'] == 1)
           {
                $pricestyle = "color:#e4edd8;  font-size:1px;"   ;
           ?>
            <tr class="table_cell_3" style="<?=$changestyle;?>" id="blank_mat<?= $i; ?>">

           <?}
           else
           {
                $pricestyle = "color:#ffffff;  font-size:11px;"   ;
           ?>
            <tr class="table_cell_4" style="<?=$changestyle;?>" id="blank_mat<?= $i; ?>">
           <?}
		?>


				<td>
                    <?= $oFormMaterialTab->getElementHtml('id['.$i.']'); ?>
                    <?= $oFormMaterialTab->getElementHtml('code['.$i.']'); ?>
                </td>
				<td><?= $oFormMaterialTab->getElementHtml('title['.$i.']'); ?></td>
				<td><?= $oFormMaterialTab->getElementHtml('unit['.$i.']'); ?></td>
                <?if($isEDUser || $isAdmin){ ?>
                <td><?= $oFormMaterialTab->getElementHtml('price['.$i.']'); ?></td>
                <?}else{ ?>
                <td style="<?=$pricestyle;?>"><?= $oFormMaterialTab->getElementHtml('price['.$i.']'); ?></td>
                <?}?>
                <? if($tameMaterial) { ?>
					<td><?= $oFormMaterialTab->getElementHtml('amount_km['.$i.']'); ?></td>
					<td><?= $oFormMaterialTab->getElementHtml('amount_kor_mat['.$i.']'); ?></td>
				<? } else { ?>
					<td><?= $oFormMaterialTab->getElementHtml('amount_mat['.$i.']'); ?></td>
                <? } ?> 
                <?if($isEDUser || $isAdmin ){ ?>
                    <td><?= $oFormMaterialTab->getElementHtml('total_mat['.$i.']'); ?></td>
                    <?}else{ ?>
                    <td  style="<?=$pricestyle;?>"><?= $oFormMaterialTab->getElementHtml('total_mat['.$i.']'); ?></td>
                <?}?>
				
             	<td>
                    <? if(!$isReadonly)  {?>
                    <?= $oFormMaterialTab->getElementHtml('mat_del['.$i.']'); ?>
                    <? } else{ ?>
                    &nbsp;
                    <? } ?>
                </td>
			</tr>

		<?
		}
        ?>
        <? if($tameMaterial) { ?>
        <tr>
            <td align="right"  colspan="6"><b><?=text::get('TOTAL');?>:</b></td>
            <td align="center"><b><?= $totalPrice; ?></b></td>
       </tr>
       <? } ?>
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

