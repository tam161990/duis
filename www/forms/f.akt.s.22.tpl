<script type="text/javascript">
function savedField (el, color) { 
    el.style.borderColor = color; 
    parent = el.parentNode;
    if(parent.firstChild.nodeName == 'SPAN') {
        parent.removeChild(sp1);
    }
    //parent.removeChild(parent.childNodes[0]); 
}
// succsess
var sp1 = document.createElement('span');
sp1.append('Saglabāts');
sp1.style.color = 'green';
// error
var sp2 = document.createElement('span');
sp2.append('<?=text::get('ERROR_DOUBLE_VALUE');?>');
sp2.style.color = 'red';
</script>
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
                <? if( ($status == STAT_CLOSE && ($isAdmin || $isEconomist || $projectApprover)))  {?>
                <th  width="3%"><?=text::get('PROJECT_EXPORT_TYPE');?></th>
                <? } else {?>
                    <th width="3%">&nbsp;</th>
                <? } ?>
			</tr>

	  <?
      foreach ($aGroupMaterials as $j => $actMaterial)
	  {
           $changestyle = "font-weight:normal;"   ;
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
           <?}
		?>


				<td>
                    <?= $oFormMaterialTab->getElementHtml('id['.$x.']'); ?>
                    <?= $oFormMaterialTab->getElementHtml('code['.$x.']'); ?>
                </td>
                <td><?= $oFormMaterialTab->getElementHtml('work_type['.$x.']'); ?> </td>   
				<td><?= $oFormMaterialTab->getElementHtml('title['.$x.']'); ?></td>
				<td><?= $oFormMaterialTab->getElementHtml('unit['.$x.']'); ?></td>                
                <td><?= $oFormMaterialTab->getElementHtml('amount_mat['.$x.']'); ?></td>
                <td><?= $oFormMaterialTab->getElementHtml('complectation['.$x.']'); ?></td>
                <td><?= $oFormMaterialTab->getElementHtml('crossection['.$x.']'); ?></td>
				<td><?= $oFormMaterialTab->getElementHtml('notes['.$x.']'); ?></td>
                <? if( ($status == STAT_CLOSE && ($isAdmin || $isEconomist || $projectApprover)))  {?>
                    <td><?= $oFormMaterialTab->getElementHtml('export_type['.$x.']'); ?></td>
                <? } else {?>
                    <td>
                        <? if(!$isReadonly)  {?>
                        <?= $oFormMaterialTab->getElementHtml('mat_del['.$x.']'); ?>
                        <? } else{ ?>
                        &nbsp;
                        <? } ?>
                    </td>
                <? } ?>
			</tr>

            <?
            $x++;
            }
            ?>
            <tr>
                 <td align="right" colspan="7">&nbsp;</td>
            </tr>
            <?
           
		}
		?>
        
	    </table>
        </td>
        <td width="20%" valign="top">
            &nbsp;
        </td>
	</tr>
</table>
<div class="navbar">
    <table cellpadding="5" cellspacing="1" border="0" align="left" width="100">
    <? if(!$isReadonly)  {
      foreach($favorit as $i=>$val){?>
     <tr>
        <td bgcolor="white"><?= $oFormMaterialTab->getElementHtml('group['.$i.']'); ?></td>
     </tr>
    <? }} ?>
    <tr>
        <? if(!$isReadonly || ($status == STAT_CLOSE && ($isAdmin || $isEconomist || $projectApprover)))  {?>
            <td><?= $oFormMaterialTab -> getElementHtml('save'); ?></td>
         <? } ?>

     </tr>
    </table>   
</div>
<?= $oFormMaterialTab -> getFormBottom(); ?>

