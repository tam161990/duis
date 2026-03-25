<script language="JavaScript">
<!--
javascript:window.history.forward(1);
//-->
</script>
<body class="frame_1">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=$searchTitle;?></h1>
<?= $oForm->getFormHeader(); ?>
<table cellpadding="3" cellspacing="1" border="0" width="100%">
	<tr>
		<td align="center" colspan="6"><?= $oForm->getMessage(); ?></td>
	</tr>
	<tr>
		<td class="table_cell_c" width="16%"><?= $oForm->getElementLabel('employeeCode'); ?>:</td>
		<td class="table_cell_2" width="34%"><?= $oForm->getElementHtml('employeeCode'); ?></td>
		<td class="table_cell_c" width="16%"><?= $oForm->getElementLabel('vvNumber'); ?>:</td>
		<td class="table_cell_2" width="34%"><?= $oForm->getElementHtml('vvNumber'); ?></td>
	</tr>
	<tr>
		<td class="table_cell_c"><?= $oForm->getElementLabel('territoryCode'); ?>:</td>
		<td class="table_cell_2"><?= $oForm->getElementHtml('territoryCode'); ?></td>
		<td class="table_cell_c"><?= $oForm->getElementLabel('actType'); ?>:</td>
		<td class="table_cell_2"><?= $oForm->getElementHtml('actType'); ?></td>
	</tr>
	<tr>
		<td class="table_cell_c"><?= $oForm->getElementLabel('status'); ?>:</td>
		<td class="table_cell_2"><?= $oForm->getElementHtml('status'); ?></td>
		<td class="table_cell_c"><?= $oForm->getElementLabel('authorId'); ?>:</td>
		<td class="table_cell_2"><?= $oForm->getElementHtml('authorId'); ?></td>
	</tr>
	<tr>
		<td colspan="2">&nbsp;</td>
		<td colspan="2" align="right">
			<span id="loading" style="position:absolute; width:32; height:32; margin-left:30px; display:none;">
				<img src="./img/loading.gif" widht="32" height="32" border="0" />
			</span>
			<?=$oForm->getElementHtml('search');?>
		</td>
	</tr>
</table>
<?= $oForm->getFormBottom(); ?>
</body>
