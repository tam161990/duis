
<body class="frame_2">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::toUpper(text::get('HARMONIZED_INFO')));?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">

   	<tr>

    		<td align=center colspan="6"><?= $oForm -> getMessage(); ?></td>
    </tr>
    <tr>
		<td colspan="6" class="table_separator">
           &nbsp;
        </td>
	</tr>
	<tr>
		<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('name'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('name'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('surname'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('surname'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('position'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('position'); ?></td>

	</tr>
	<tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('section'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('section'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('edArea'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('edArea'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('isActive'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('isActive'); ?></td>
	</tr>
	<tr>        
        <td class="table_cell_c"><?= $oForm -> getElementLabel('department'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('department'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('created'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('created'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('creator'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('creator'); ?></td>
	</tr>
	
	<tr>
		<td class="table_cell_c">&nbsp;</td>
		<td class="table_cell_2">&nbsp;</td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('edited'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('edited'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('editor'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('editor'); ?></td>
	</tr>

</table>

<table cellpadding="5" cellspacing="0" border="0" align="center">
	<tr>
		<td><?=$oForm->getElementHtml('add');?></td>
		<td><?=$oForm->getElementHtml('save');?></td>
		<td><?=$oForm->getElementHtml('clear');?></td>

	</tr>
</table>
<?= $oForm -> getFormBottom(); ?>
<?=$oForm->getElementHtml('jsButtonsControl');?>
</body>
