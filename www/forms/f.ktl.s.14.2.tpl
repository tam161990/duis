
<body class="frame_2">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::toUpper(text::get('MMS_INFO')));?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="6"><?= $oForm -> getMessage(); ?></td>
	</tr>
	<tr>
		<td colspan="6" class="table_separator">&nbsp;</td>
	</tr>
	<tr>
     	<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('kods'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('kods'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('edAreaCode'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('edAreaCode'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('isFinished'); ?>:</td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('isFinished'); ?></td>
	</tr>
    <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('workTime'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('workTime'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('price'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('price'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('priority'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('priority'); ?></td>
	</tr>
    <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('year'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('year'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('quarter'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('quarter'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('trase'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('trase'); ?></td>
	</tr>
    <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('worker'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('worker'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('contract'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('contract'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('finalize'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('finalize'); ?></td>

	</tr>
    <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('toidn'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('toidn'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('toid'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('toid'); ?></td>
        <td class="table_cell_c">&nbsp;</td>
		<td class="table_cell_2">&nbsp;</td>

	</tr>
</table>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
     <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('designation'); ?></td>
        <td class="table_cell_2" colspan="4"><?= $oForm -> getElementHtml('designation'); ?></td>
        <td class="table_cell_2">&nbsp;</td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('worktitle'); ?></td>
        <td class="table_cell_2" colspan="4"><?= $oForm -> getElementHtml('worktitle'); ?></td>

	</tr>
    
    <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('1z'); ?>&nbsp;<?= $oForm -> getElementHtml('1z'); ?></td>
		<td class="table_cell_2"><?= $oForm -> getElementLabel('2z'); ?>&nbsp;<?= $oForm -> getElementHtml('2z'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('3z'); ?>&nbsp;<?= $oForm -> getElementHtml('3z'); ?></td>
		<td class="table_cell_2"><?= $oForm -> getElementLabel('4z'); ?>&nbsp;<?= $oForm -> getElementHtml('4z'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('5z'); ?>&nbsp;<?= $oForm -> getElementHtml('5z'); ?></td>
		<td class="table_cell_2"><?= $oForm -> getElementLabel('6z'); ?>&nbsp;<?= $oForm -> getElementHtml('6z'); ?></td>

        <td class="table_cell_c"><?= $oForm -> getElementLabel('7z'); ?>&nbsp;<?= $oForm -> getElementHtml('7z'); ?></td>
		<td class="table_cell_2"><?= $oForm -> getElementLabel('8z'); ?>&nbsp;<?= $oForm -> getElementHtml('8z'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('9z'); ?>&nbsp;<?= $oForm -> getElementHtml('9z'); ?></td>
        <td class="table_cell_2">&nbsp;</td>
        <td class="table_cell_c">&nbsp;</td>


	</tr>

    <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('1v'); ?>&nbsp;<?= $oForm -> getElementHtml('1v'); ?></td>
		<td class="table_cell_2"><?= $oForm -> getElementLabel('2v'); ?>&nbsp;<?= $oForm -> getElementHtml('2v'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('3v'); ?>&nbsp;<?= $oForm -> getElementHtml('3v'); ?></td>
		<td class="table_cell_2"><?= $oForm -> getElementLabel('4v'); ?>&nbsp;<?= $oForm -> getElementHtml('4v'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('5v'); ?>&nbsp;<?= $oForm -> getElementHtml('5v'); ?></td>
		<td class="table_cell_2"><?= $oForm -> getElementLabel('6v'); ?>&nbsp;<?= $oForm -> getElementHtml('6v'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('7v'); ?>&nbsp;<?= $oForm -> getElementHtml('7v'); ?></td>
		<td class="table_cell_2"><?= $oForm -> getElementLabel('8v'); ?>&nbsp;<?= $oForm -> getElementHtml('8v'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('9v'); ?>&nbsp;<?= $oForm -> getElementHtml('9v'); ?></td>
        <td class="table_cell_2"><?= $oForm -> getElementLabel('10v'); ?>&nbsp;<?= $oForm -> getElementHtml('10v'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('11v'); ?>&nbsp;<?= $oForm -> getElementHtml('11v'); ?></td>

	</tr>

</table>

<table cellpadding="5" cellspacing="0" border="0" align="center">
	<tr>
		<td><?=$oForm->getElementHtml('add');?></td>
		<td><?=$oForm->getElementHtml('save');?></td>
		<td><?=$oForm->getElementHtml('clear');?></td>
        <? if ($isDelete)   { ?>
        <td><?=$oForm->getElementHtml('delete');?></td>
        <? } ?>
	</tr>
</table>
<?= $oForm -> getFormBottom(); ?>
<?=$oForm->getElementHtml('jsButtonsControl');?>
</body>


