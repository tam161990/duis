
<body class="frame_2">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::toUpper(text::get('CALCULATION_MATERIAL_INFO')));?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="6"><?= $oForm -> getMessage(); ?></td>
	</tr>
	<tr>
		<td colspan="6" class="table_separator">&nbsp;</td>
	</tr>
	<tr>
		<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('chipher'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('chipher'); ?></td>
     	<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('calc_title'); ?>:</td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('calc_title'); ?></td>        
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('matr_code'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('matr_code'); ?></td>
	</tr>
	<tr>		
     	<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('group'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('group'); ?></td>        
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('subgroup'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('subgroup'); ?></td>
		<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('group_title'); ?>:</td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('group_title'); ?></td>
	</tr>
	
    <tr>
     	<td class="table_cell_c"><?= $oForm -> getElementLabel('amount'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('amount'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('useMaterial'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('useMaterial'); ?></td>        
        <td class="table_cell_c"><?= $oForm -> getElementLabel('isDefault'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('isDefault'); ?></td>
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
	<td class="table_cell_c"><?= $oForm -> getElementLabel('isActive'); ?>:</td>
	<td class="table_cell_2"><?= $oForm -> getElementHtml('isActive'); ?></td>	
   <td class="table_cell_c"><?= $oForm -> getElementLabel('round_amount'); ?>:</td>
   <td class="table_cell_2"><?= $oForm -> getElementHtml('round_amount'); ?></td>
   <td class="table_cell_c"><?= $oForm -> getElementLabel('dvd'); ?>:</td>
   <td class="table_cell_2"><?= $oForm -> getElementHtml('dvd'); ?></td>
</tr>
<tr>
	<td class="table_cell_c">&nbsp;</td>
	<td class="table_cell_2">&nbsp;</td>
	
   <td class="table_cell_c"><?= $oForm -> getElementLabel('created'); ?>:</td>
   <td class="table_cell_2"><?= $oForm -> getElementHtml('created'); ?></td>
   <td class="table_cell_c"><?= $oForm -> getElementLabel('creator'); ?>:</td>
   <td class="table_cell_2"><?= $oForm -> getElementHtml('creator'); ?></td>
</tr>

<tr>
	<td class="table_cell_c">&nbsp;</td>
	<td class="table_cell_2">&nbsp;</td>
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
       
	</tr>
</table>
<?= $oForm -> getFormBottom(); ?>
<?=$oForm->getElementHtml('jsButtonsControl');?>
</body>
