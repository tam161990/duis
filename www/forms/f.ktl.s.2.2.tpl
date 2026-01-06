
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
         <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('worker'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('worker'); ?></td>

	</tr>
	<tr>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('surname'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('surname'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('password'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('password'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('isActive'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('isActive'); ?></td>

	</tr>
	<tr>
         <td class="table_cell_c"><?= $oForm -> getElementLabel('trase'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('trase'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('password2'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('password2'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('projector'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('projector'); ?></td>

	</tr>
    <tr>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('contract'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('contract'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('changePass'); ?></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('changePass'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('limitCard'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('limitCard'); ?></td>

	</tr>
	<tr>
        <td class="table_cell_c">&nbsp;</td>
		<td class="table_cell_2">&nbsp;</td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('ppaReport'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('ppaReport'); ?></td>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('rbfAccess'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('rbfAccess'); ?></td>

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
