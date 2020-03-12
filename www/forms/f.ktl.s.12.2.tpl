
<body class="frame_2">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::toUpper(text::get('USER_INFO')));?></h1>
<?= $oForm -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="6"><?= $oForm -> getMessage(); ?>
         <b> <?= $oForm -> getElementLabel('darbiba'); ?>:</b>
           <?= $oForm -> getElementHtml('darbiba'); ?>
        </td>
	</tr>
   	<tr>
		<td colspan="6" class="table_separator">
           &nbsp;
        </td>
	</tr>
	<tr>
		<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('name'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('name'); ?></td>
		<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('login'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('login'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('role'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('role'); ?></td>

	</tr>
	<tr>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('surname'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('surname'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('password'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('password'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('region'); ?>:</td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('region'); ?></td>

	</tr>
	<tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('isActive'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('isActive'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('password2'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('password2'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('section'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('section'); ?></td>


	</tr>
	<tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('irAdmin'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('irAdmin'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('changePass'); ?></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('changePass'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('edArea'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('edArea'); ?></td>
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
