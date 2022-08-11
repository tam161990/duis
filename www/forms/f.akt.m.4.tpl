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
		<td class="table_cell_2" width="25%"><?= $oForm -> getElementHtml('year'); ?></td>
        
        <td class="table_cell_c" width="10%"><?= $oForm -> getElementLabel('worker'); ?>:</td>
		<td class="table_cell_2" width="25%"><?= $oForm -> getElementHtml('worker'); ?></td>

        <td class="table_cell_c" width="10%">&nbsp;</td>
		<td class="table_cell_2" width="20%">&nbsp;</td>
   </tr>
   <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('month'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('month'); ?></td>
        
        <td class="table_cell_c"><?= $oForm -> getElementLabel('contract'); ?>:</td>
        <td class="table_cell_2"><?= $oForm -> getElementHtml('contract'); ?></td>
        
        <td class="table_cell_c"><?= $oForm -> getElementLabel('one_contract'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('one_contract'); ?></td>
   	</tr>


	<tr>
        
		<td colspan="2" align="right">
        <span id="loading" style="position:absolute; width:32; height:32; margin-left:30px; display: none; ">
        <img src="./img/loading.gif" widht="32" height="32" border="0" />
        </span><?=$oForm->getElementHtml('search');?></td>
        <td colspan="2"><a href="#" onClick="reloadFrame(1,'<?= $criteriaLink; ?>');reloadFrame(23,'');"><?=text::get('RETURN_TO_SEARCH_CRRITERIA');?></a></td>
    </tr>
</table>

<?= $oForm -> getFormBottom(); ?>
</body>
