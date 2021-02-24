
<body class="frame_2">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::toUpper(text::get('MMS_CALCULATION_INFO')));?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="6"><?= $oForm -> getMessage(); ?></td>
	</tr>
	<tr>
		<td colspan="6" class="table_separator">&nbsp;</td>
	</tr>
	<tr>
     	<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('requirement'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('requirement'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('chipher'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('chipher'); ?></td>
		<td class="table_cell_c"  width="16%"><?= $oForm -> getElementLabel('title'); ?>:</td>
		<td class="table_cell_2"  width="16%"><?= $oForm -> getElementHtml('title'); ?></td>       
	</tr>
    <tr>
		<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('isDefault10'); ?>:</td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('isDefault10'); ?></td>
     	<td class="table_cell_c"><?= $oForm -> getElementLabel('isDefaultNot10'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('isDefaultNot10'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('amount'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('amount'); ?></td>
        
	</tr>
    
    <tr>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('useLine'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('useLine'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('koeficent'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('koeficent'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('useCord'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('useCord'); ?></td>
		
	</tr>
	<tr>
	   <td class="table_cell_c"><?= $oForm -> getElementLabel('isEpla'); ?>:</td>
	   <td class="table_cell_2"><?= $oForm -> getElementHtml('isEpla'); ?></td>
	   <td class="table_cell_c"><?= $oForm -> getElementLabel('created'); ?>:</td>
	   <td class="table_cell_2"><?= $oForm -> getElementHtml('created'); ?></td>
	   <td class="table_cell_c"><?= $oForm -> getElementLabel('creator'); ?>:</td>
	   <td class="table_cell_2"><?= $oForm -> getElementHtml('creator'); ?></td>
   </tr>
   <tr>
	
	<td class="table_cell_c"><?= $oForm -> getElementLabel('isActive'); ?>:</td>
	<td class="table_cell_2"><?= $oForm -> getElementHtml('isActive'); ?></td>	
	<td class="table_cell_c"><?= $oForm -> getElementLabel('edited'); ?>:</td>
	<td class="table_cell_2"><?= $oForm -> getElementHtml('edited'); ?></td>
	<td class="table_cell_c"><?= $oForm -> getElementLabel('editor'); ?>:</td>
	<td class="table_cell_2"><?= $oForm -> getElementHtml('editor'); ?></td>
</tr>
</table>

<table cellpadding="5" cellspacing="0" border="0" align="center">
	<tr>
		<td><?=$oForm->getElementHtml('add');?></td>
		<td><?=$oForm->getElementHtml('save');?></td>
		<td><?=$oForm->getElementHtml('clear');?></td>
        <td><?=$oForm->getElementHtml('delete');?></td>
	</tr>
</table>
<?= $oForm -> getFormBottom(); ?>
<?=$oForm->getElementHtml('jsButtonsControl');?>
</body>
