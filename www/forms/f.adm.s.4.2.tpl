
<body class="frame_2">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::toUpper(text::get('SYSTEM_PROCESS_INFO')));?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="6"><?= $oForm -> getMessage(); ?></td>
	</tr>
	<tr>
		<td colspan="6" class="table_separator">&nbsp;</td>
	</tr>
	<tr>
     	<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('nosaukums'); ?>:</td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('nosaukums'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('comand'); ?>:</td>
		<td class="table_cell_2" width="26%"><?= $oForm -> getElementHtml('comand'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('pid'); ?>:</td>
		<td class="table_cell_2" width="6%"><?= $oForm -> getElementHtml('pid'); ?></td>
	</tr>
    <tr>
     	<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('start'); ?>:</td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('start'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('end'); ?>:</td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('end'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('isActive'); ?>:</td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('isActive'); ?></td>
	</tr>
	<tr>
	   <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('interval'); ?>:</td>
	   <td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('interval'); ?></td>
	   <td class="table_cell_c" width="16%">&nbsp;</td>
	   <td class="table_cell_2" width="16%">&nbsp;</td>
	   <td class="table_cell_c" width="16%">&nbsp;</td>
	   <td class="table_cell_2" width="16%">&nbsp;</td>
   </tr>

</table>

<table cellpadding="5" cellspacing="0" border="0" align="center">
	<tr>
		<td><?=$oForm->getElementHtml('run');?></td>
		<td><?=$oForm->getElementHtml('stop');?></td>
		<td><?=$oForm->getElementHtml('delete');?></td>
	</tr>
</table>
<?= $oForm -> getFormBottom(); ?>
<?=$oForm->getElementHtml('jsButtonsControl');?>
</body>
