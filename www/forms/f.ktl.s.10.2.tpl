
<body class="frame_2">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::toUpper(text::get('CALCULATION_INFO')));?></h1>
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
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('chipher'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('chipher'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('nosaukums'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('nosaukums'); ?></td>
	</tr>
    <tr>
         <td class="table_cell_c"><?= $oForm -> getElementLabel('edArea'); ?>:<?= (($trase == 1)? "<font color=red>*</font>" : "" ) ?>    </td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('edArea'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('measure'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('measure'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('isActive'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('isActive'); ?></td>
	</tr>
     <tr>
     	<td class="table_cell_c"><?= $oForm -> getElementLabel('worker'); ?>:<?= (($trase == 1)? "<font color=red>*</font>" : "" ) ?> </td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('worker'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('planPrice'); ?>:<?= (($trase == 1)? "<font color=red>*</font>" : "" ) ?> </td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('planPrice'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('notPlanPrice'); ?>:<?= (($trase == 1)? "<font color=red>*</font>" : "" ) ?> </td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('notPlanPrice'); ?></td>
	</tr>
    <tr>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('contract'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('contract'); ?></td>
        <td class="table_cell_c">&nbsp;</td>
		<td class="table_cell_2">&nbsp;</td>
        <td class="table_cell_c">&nbsp;</td>
		<td class="table_cell_2">&nbsp;</td>
	</tr>
    <tr>
		<td class="table_cell_c"><?= $oForm -> getElementLabel('fizRadijums'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('fizRadijums'); ?></td>

        <td class="table_cell_c"><?= $oForm -> getElementLabel('element'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('element'); ?></td>

        <? if($trase == 1)  { ?>
        <td class="table_cell_c"></td>
		<td class="table_cell_2"></td>
        <? } else { ?>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('koeficent'); ?>:</td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('koeficent'); ?></td>

        <? } ?>
	</tr>
    
    <tr>
		<td class="table_cell"><?= $oForm -> getElementLabel('description'); ?>:</td>
		<td class="table_cell_2" colspan="5"><?= $oForm -> getElementHtml('description'); ?></td>

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
