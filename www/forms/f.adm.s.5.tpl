<body class="frame_1">
<h1><?=text::toUpper(text::get('SUPERADMIN'));?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td  width="36%" >&nbsp;</td>
		<td  colspan="2"><?=text::get('SUPERADMIN_TITLE'); ?></td>
	</tr>
	<tr>
		<td align=center colspan="3"><?= $oForm -> getMessage(); ?></td>
	</tr>
	<tr>
		<td colspan="3" class="table_separator">&nbsp;</td>
	</tr>
    
    <tr>
		<td class="table_cell_c" width="36%"><?= $oForm -> getElementLabel('superadmin_name'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="36%"><?= $oForm -> getElementHtml('superadmin_name'); ?></td>
		<td class="table_cell_c" >&nbsp;</td>
	</tr>

</table>

<table cellpadding="5" cellspacing="0" border="0" align="center">
	<tr>
		<td><?= $oForm -> getElementHtml('submit'); ?></td>
	</tr>
</table>
<?= $oForm -> getFormBottom(); ?>
</body>
