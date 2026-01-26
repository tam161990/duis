<body class="frame_1">
<h1><?=text::toUpper(text::get('RBF_EXPORT'));?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="2"><?= $oForm -> getMessage(); ?></td>
	</tr>
	<tr>
		<td colspan="2" class="table_separator">&nbsp;</td>
	</tr>	
	<tr>
		<td class="table_cell_c" width="20%"><?= $oForm -> getElementLabel('upload_type'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('upload_type'); ?></td>
	</tr>
	<tr>
		<td colspan="2" class="table_separator">&nbsp;</td>
	</tr>	
	<tr>
		<td class="table_cell_c" width="20%"><?= $oForm -> getElementLabel('rbf_akts_file'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('rbf_akts_file'); ?></td>
	</tr>
	<tr>
		<td colspan="2" class="table_separator">&nbsp;</td>
	</tr>
	<tr>
		<td colspan="2" class="table_cell_c">
			<?= text::get('REQUIREMENTS_RBF_AKTS'); ?>
		</td>
	</tr>
	
</table>

<table cellpadding="5" cellspacing="0" border="0" align="center">
	<tr>
		<td><?= $oForm -> getElementHtml('submit'); ?></td>
	</tr>
</table>
<?= $oForm -> getFormBottom(); ?>
</body>

