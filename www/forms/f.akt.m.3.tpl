<body class="frame_1">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=$searchTitle;?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="4"><?= $oForm -> getMessage(); ?></td>
	</tr>

    <tr>
        <td class="table_cell_c" width="20%"><?= $oForm -> getElementLabel('number'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('number'); ?></td>

   	</tr>

</table>

<table cellpadding="5" cellspacing="0" border="0" align="center">
	<tr>
		<td><?=$oForm->getElementHtml('search');?></td>

	</tr>
</table>
<?= $oForm -> getFormBottom(); ?>
<script language="JavaScript">
document.all['number'].focus();
</script>
</body>
