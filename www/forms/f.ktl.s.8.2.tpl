
<body class="frame_2">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::toUpper(text::get('WORK_OWNERS_INFO')));?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="6"><?= $oForm -> getMessage(); ?></td>
	</tr>
	<tr>
		<td colspan="6" class="table_separator">&nbsp;</td>
	</tr>
	<tr>

        <td class="table_cell_c" width="15%"><?= $oForm -> getElementLabel('nosaukums'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="25%"><?= $oForm -> getElementHtml('nosaukums'); ?></td>
        <td class="table_cell_c" width="15%"><?= $oForm -> getElementLabel('kods'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="25%"><?= $oForm -> getElementHtml('kods'); ?></td>
        <td class="table_cell_c" width="15%"><?= $oForm -> getElementLabel('isActive'); ?>:</td>
		<td class="table_cell_2" width="5%"><?= $oForm -> getElementHtml('isActive'); ?></td>
	</tr>
	<tr>

        <td class="table_cell_c" width="15%"><?= $oForm -> getElementLabel('nosaukums2'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="25%"><?= $oForm -> getElementHtml('nosaukums2'); ?></td>
        <td class="table_cell_c" width="15%">&nbsp;</td>
		<td class="table_cell_2" width="25%">&nbsp;</td>
        <td class="table_cell_c" width="15%">&nbsp;</td>
		<td class="table_cell_2" width="5%">&nbsp;</td>
	</tr>
       <tr>
     	<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('number'); ?>:</td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('number'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('trase_number'); ?>:</td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('trase_number'); ?></td>
        <td class="table_cell_2" width="16%" ><?=$oForm->getElementHtml('view');?></td>
		<td class="table_cell_2" width="6%">&nbsp;</td>
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
