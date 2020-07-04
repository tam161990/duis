<body class="frame_1">
<?= $oFormPop -> getFormHeader(); ?>
<h1><?=$title;?></h1>
<div align=center><?= $oFormPop -> getMessage(); ?></div>
<?  if($catalog == KL_CALCULALATION ) { ?>

<table cellpadding="5" cellspacing="1" border="0" width="100%">
<tr>
    <td class="table_cell_c" width="40%"><?= $oFormPop -> getElementLabel('calc_group'); ?></td>
    <td class="table_cell_2" width="60%"><?= $oFormPop -> getElementHtml('calc_group'); ?></td>    
</tr>
</table>
<? } ?>

<?  if($catalog == KL_MATERIALS ) { ?>

    <table cellpadding="5" cellspacing="1" border="0" width="100%">
    <tr>
        <td class="table_cell_c" width="40%"><?= $oFormPop -> getElementLabel('mat_group'); ?></td>
        <td class="table_cell_2" width="60%"><?= $oFormPop -> getElementHtml('mat_group'); ?></td>    
    </tr>
    <tr>
        <td class="table_cell_c" width="40%"><?= $oFormPop -> getElementLabel('mat_sub_group'); ?></td>
        <td class="table_cell_2" width="60%"><?= $oFormPop -> getElementHtml('mat_sub_group'); ?></td>    
    </tr>
    </table>
    <? } ?>

<table cellpadding="5" cellspacing="1" border="0" width="100%">
<tr>
    <td><?= $oFormPop -> getElementHtml('scope'); ?></td>
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