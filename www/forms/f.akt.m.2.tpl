<body class="frame_1">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=$searchTitle;?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="3" cellspacing="1" border="0" width="100%">

	<tr>
		<td align=center colspan="6"><?= $oForm -> getMessage(); ?></td>
    </tr>

   <tr>
		<td class="table_cell_c" width="10%"><?= $oForm -> getElementLabel('year'); ?>:</td>
		<td class="table_cell_2" width="20%">
            <?= $oForm -> getElementLabel('yearFrom'); ?>&nbsp;
            <?= $oForm -> getElementHtml('yearFrom'); ?>&nbsp;&nbsp;
            <?= $oForm -> getElementLabel('yearUntil'); ?>&nbsp;
            <?= $oForm -> getElementHtml('yearUntil'); ?>
        </td>
        <td class="table_cell_c" width="10%"><?= $oForm -> getElementLabel('month'); ?>:</td>
		<td class="table_cell_2" width="20%">
            <?= $oForm -> getElementLabel('monthFrom'); ?>
            <?= $oForm -> getElementHtml('monthFrom'); ?>&nbsp;
            <?= $oForm -> getElementLabel('monthUntil'); ?>
            <?= $oForm -> getElementHtml('monthUntil'); ?>
        </td>
        <td class="table_cell_c" width="10%"><?= $oForm -> getElementLabel('worker'); ?>:</td>
		<td class="table_cell_2" width="30%"><?= $oForm -> getElementHtml('worker'); ?></td>
   </tr>
   <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('edRegion'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('edRegion'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('section'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('section'); ?></td>
        <td class="table_cell_c" ><?= $oForm -> getElementLabel('writeoff'); ?>:</td>
		<td class="table_cell_2" ><?= $oForm -> getElementHtml('writeoff'); ?></td>
   </tr>
	<tr>

		<td colspan="6" align="center">
        <span id="loading" style="position:absolute; width:32; height:32; margin-left:30px; display: none; ">
        <img src="./img/loading.gif" widht="32" height="32" border="0" />
        </span><?=$oForm->getElementHtml('search');?></td>

    </tr>
</table>

<?= $oForm -> getFormBottom(); ?>
</body>
