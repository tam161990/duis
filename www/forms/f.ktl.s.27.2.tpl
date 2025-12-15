
<body class="frame_2">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::get('RBF_CALCULATION_INFO'));?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="6"><?= $oForm -> getMessage(); ?></td>
	</tr>
	<tr>
		<td colspan="6" class="table_separator">&nbsp;</td>
	</tr>
	<tr>
     	<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('shifrs'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('shifrs'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('nosaukums'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="18%"><?= $oForm -> getElementHtml('nosaukums'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('mervieniba'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="18%"><?= $oForm -> getElementHtml('mervieniba'); ?></td>
	</tr>
	<tr>
     	<td class="table_cell_c"><?= $oForm -> getElementLabel('employeeCode'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('employeeCode'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('vvNumber'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('vvNumber'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('cena'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('cena'); ?></td>
	</tr>
	<tr>
     	<td class="table_cell_c" valign="top"><?= $oForm -> getElementLabel('section'); ?>:</td>
		<td class="table_cell_2" colspan="5"><?= $oForm -> getElementHtml('section'); ?></td>
	</tr>
	<tr>
     	<td class="table_cell_c" valign="top"><?= $oForm -> getElementLabel('apraksts'); ?>:</td>
		<td class="table_cell_2" colspan="5"><?= $oForm -> getElementHtml('apraksts'); ?></td>
	</tr>
	<tr>
		<td colspan="6" class="table_separator">&nbsp;</td>
	</tr>
	<tr>
     	<td class="table_cell_c"><?= $oForm -> getElementLabel('created'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('created'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('creator'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('creator'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('isActive'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('isActive'); ?></td>
	</tr>
	<tr>
     	<td class="table_cell_c"><?= $oForm -> getElementLabel('edited'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('edited'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('editor'); ?>:</td>
		<td class="table_cell_2" colspan="3"><?= $oForm -> getElementHtml('editor'); ?></td>
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
