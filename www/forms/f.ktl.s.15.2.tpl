
<body class="frame_1">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::toUpper(text::get('KWOI_VV_NUMBER')));?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="6"><?= $oForm -> getMessage(); ?></td>
	</tr>
	<tr>
		<td colspan="6" class="table_separator">&nbsp;</td>
	</tr>
	<tr>
     	<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('contractNo'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('contractNo'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('edArea'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="26%"><?= $oForm -> getElementHtml('edArea'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('signatory'); ?>:</td>
		<td class="table_cell_2" width="6%"><?= $oForm -> getElementHtml('signatory'); ?></td>
	</tr>
    <tr>
     	<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('isTrase'); ?>:</td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('isTrase'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('isActive'); ?>:</td>
		<td class="table_cell_2" width="6%"><?= $oForm -> getElementHtml('isActive'); ?></td>
        <td class="table_cell_c">&nbsp;</td>
		<td class="table_cell_2">&nbsp;</td>
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
