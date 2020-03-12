<body class="frame_1">
<h1><?=text::toUpper(text::get('ACT_NUMBER_TEMPLATE'));?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="3"><?= $oForm -> getMessage(); ?></td>
	</tr>
	<tr>
		<td colspan="3" class="table_separator">&nbsp;</td>
	</tr>
    
    <tr>
		<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('link_tpl'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"  colspan="2"><?= $oForm -> getElementHtml('link_tpl'); ?></td>

	</tr>

</table>

<table cellpadding="5" cellspacing="0" border="0" align="center">
	<tr>
		<td><?= $oForm -> getElementHtml('submit'); ?></td>
	</tr>
</table>
<?= $oForm -> getFormBottom(); ?>
</body>
