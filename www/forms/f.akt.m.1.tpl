<script language="JavaScript">
<!--
javascript:window.history.forward(1);
//-->
</script>
<body class="frame_1">
<?=$oForm->getElementHtml('jsRefresh2');?>
<?=$oForm->getElementHtml('jsRefresh3');?>
<h1><?=$searchTitle;?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="3" cellspacing="1" border="0" width="100%" >

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
        <? if($isSearchForm) { ?>
            <td class="table_cell_c" width="10%"><?= $oForm -> getElementLabel('designation'); ?>:</td>
		    <td class="table_cell_2" width="23%"><?= $oForm -> getElementHtml('designation'); ?></td>
        <? } else { ?>
            <td class="table_cell_c" width="10%">&nbsp;</td>
    		<td class="table_cell_2" width="23%">&nbsp;</td>
        <? } ?>
        <td class="table_cell_c" width="10%"><?= $oForm -> getElementLabel('ouner'); ?>:</td>
		<td class="table_cell_2" width="27%"><?= $oForm -> getElementHtml('ouner'); ?></td>
   </tr>
   <tr>
        <td class="table_cell_c" ><?= $oForm -> getElementLabel('month'); ?>:</td>
		<td class="table_cell_2" >
            <?= $oForm -> getElementLabel('monthFrom'); ?>
            <?= $oForm -> getElementHtml('monthFrom'); ?>&nbsp;
            <?= $oForm -> getElementLabel('monthUntil'); ?>
            <?= $oForm -> getElementHtml('monthUntil'); ?>
        </td>

        <td class="table_cell_c"><?= $oForm -> getElementLabel('edRegion'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('edRegion'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('worker'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('worker'); ?></td>
   	</tr>

    <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('voltage'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('voltage'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('section'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('section'); ?></td>        <td class="table_cell_c" rowspan="3"><?= $oForm -> getElementLabel('status'); ?>:</td>
		<td class="table_cell_2" rowspan="3"><?= $oForm -> getElementHtml('status'); ?></td>
   	</tr>

    <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('type'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('type'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('object'); ?></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('object'); ?></td>
    </tr>
    <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('contract'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('contract'); ?></td>
        <td class="table_cell_c">&nbsp;</td>
		<td class="table_cell_2">&nbsp;</td>
    </tr>
	<tr>
        <td colspan="2">&nbsp;</td>
		<td colspan="2" align="right">
        <span id="loading" style="position:absolute; width:32; height:32; margin-left:30px; display: none; ">
        <img src="./img/loading.gif" widht="32" height="32" border="0" />
        </span><?=$oForm->getElementHtml('search');?></td>
        <td colspan="2"><a href="#" onClick="reloadFrame(1,'<?= $criteriaLink; ?>');reloadFrame(23,'');"><?=text::get('RETURN_TO_SEARCH_CRRITERIA');?></a></td>
    </tr>
</table>

<?= $oForm -> getFormBottom(); ?>
</body>
