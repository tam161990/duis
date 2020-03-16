
<body class="frame_2">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::toUpper(text::get('OBJECT_INFO')));?></h1>
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
		<td class="table_cell_2" width="35%"><?= $oForm -> getElementHtml('nosaukums'); ?></td>
        <td class="table_cell_c" width="15%"><?= $oForm -> getElementLabel('isActive'); ?>:</td>
		<td class="table_cell_2" width="10%"><?= $oForm -> getElementHtml('isActive'); ?></td>
        <td class="table_cell_c" width="15%"><?= $oForm -> getElementLabel('trase'); ?>:</td>
		<td class="table_cell_2" width="10%"><?= $oForm -> getElementHtml('trase'); ?></td>
    </tr>
	<tr>
        <td class="table_cell_c" width="15%"><?= $oForm -> getElementLabel('kods'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="35%"><?= $oForm -> getElementHtml('kods'); ?></td>
        <td class="table_cell_c" width="15%">&nbsp;</td>
		<td class="table_cell_2" width="10%">&nbsp;</td>
        <td class="table_cell_c" width="15%">&nbsp;</td>
		<td class="table_cell_2" width="10%">&nbsp;</td>
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
