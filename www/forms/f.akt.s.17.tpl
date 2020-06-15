<body class="frame_1">
<?= $oFormPop -> getFormHeader(); ?>
<h1><?= text::get('SIGN_HEADER'); ?></h1>
<div align=center><?= $oFormPop -> getMessage(); ?></div>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
<tr>
		<td class="table_cell_c" width="40%"><?= $oFormPop -> getElementLabel('master'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="60%"><?= $oFormPop -> getElementHtml('master'); ?></td>
</tr>
<tr>
       <td class="table_cell_c" width="40%"><?= $oFormPop -> getElementLabel('engineer'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="60%"><?= $oFormPop -> getElementHtml('engineer'); ?></td>
</tr>
<tr>
       <td class="table_cell_c" width="40%"><?= $oFormPop -> getElementLabel('start_date'); ?>:</td>
		<td class="table_cell_2" width="60%"><?= $oFormPop -> getElementHtml('start_date'); ?></td>
</tr>
</table>

<table cellpadding="5" cellspacing="0" border="0" align="center">
    <tr>
      <? if(!$isReadonly)  {?>
        <td><?= $oFormPop -> getElementHtml('save'); ?></td>
      <? } ?>
        <td><?=$oFormPop->getElementHtml('close');?></td>
    </tr>
</table>
<?= $oFormPop->getFormBottom(); ?>
</body>