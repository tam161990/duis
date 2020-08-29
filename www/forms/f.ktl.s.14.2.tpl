
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
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('designation'); ?></td>
        <td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('designation'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('worktitle'); ?>:</td>
        <td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('worktitle'); ?></td>
	</tr>
    <tr>        
        <td class="table_cell_c"><?= $oForm -> getElementLabel('proces_date'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('proces_date'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('requirement_code'); ?>:</td>
        <td class="table_cell_2"><?= $oForm -> getElementHtml('requirement_code'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('requirement'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('requirement'); ?></td>
	</tr>
    <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('edAreaCode'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('edAreaCode'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('worker'); ?>:</td>
        <td class="table_cell_2"><?= $oForm -> getElementHtml('worker'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('contract'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('contract'); ?></td>
	</tr>
    <tr>        
        <td class="table_cell_c"><?= $oForm -> getElementLabel('toid'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('toid'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('technic_object'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('technic_object'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('network_element'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('network_element'); ?></td>
    </tr>
    <tr>        
        <td class="table_cell_c"><?= $oForm -> getElementLabel('network_element_code'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('network_element_code'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('quantity'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('quantity'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('line_count'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('line_count'); ?></td>
    </tr>
    <tr>        
        <td class="table_cell_c"><?= $oForm -> getElementLabel('mms_x'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('mms_x'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('mms_y'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('mms_y'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('voltage'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('voltage'); ?></td>
    </tr>
    <tr>        
        <td class="table_cell_c"><?= $oForm -> getElementLabel('object'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('object'); ?></td>
        <td class="table_cell_c">&nbsp;</td>
		<td class="table_cell_2">&nbsp;</td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('export_date'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('export_date'); ?></td>
    </tr>
    <tr>        
        <td class="table_cell_c"><?= $oForm -> getElementLabel('priority'); ?>:</td>
        <td class="table_cell_2"><?= $oForm -> getElementHtml('priority'); ?></td>        
        <td class="table_cell_c"><?= $oForm -> getElementLabel('created'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('created'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('creator'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('creator'); ?></td>
    </tr>
    <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('isEpla'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('isEpla'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('edited'); ?>:</td>
        <td class="table_cell_2"><?= $oForm -> getElementHtml('edited'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('editor'); ?>:</td>
        <td class="table_cell_2"><?= $oForm -> getElementHtml('editor'); ?></td>
    </tr>
</table>


<table cellpadding="5" cellspacing="0" border="0" align="center">
	<tr>
		<td><?=$oForm->getElementHtml('add');?></td>
        <? if ($isEdit)   { ?>
            <td><?=$oForm->getElementHtml('save');?></td>
            <td><?=$oForm->getElementHtml('delete_row');?></td>
        <? } ?>
		<td><?=$oForm->getElementHtml('clear');?></td>

        <? if ($isDelete)   { ?>
            <td><?=$oForm->getElementHtml('delete_work');?></td>
        <? } ?>
        <!--td><?=$oForm->getElementHtml('deleteFavorit');?></td-->  
	</tr>
</table>
<?= $oForm -> getFormBottom(); ?>
<?=$oForm->getElementHtml('jsButtonsControl');?>
</body>


