<body class="frame_1">
<h1><?=text::toUpper(text::get('CHANGE_USER_PASSWORD'));?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="3"><?= $oForm -> getMessage(); ?></td>
	</tr>
	<tr>
		<td colspan="3" class="table_head"><?=text::get('NEW_PASSWORD');?>:</td>
	</tr>
    <tr>
		<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('oldPassword'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('oldPassword'); ?></td>
		<td class="table_cell_c">&nbsp;</td>
	</tr>
	<tr>
		<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('password'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('password'); ?></td>
		<td class="table_cell_c">&nbsp;</td>
	</tr>
	<tr>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('password2'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('password2'); ?></td>
		<td class="table_cell_c">&nbsp;</td>
	</tr>
</table>

<table cellpadding="5" cellspacing="0" border="0" align="center">
	<tr>
		<td><?= $oForm -> getElementHtml('submit'); ?></td>
	</tr>
</table>
<?= $oForm -> getFormBottom(); ?>
</body>
