<body class="frame_1">
<?= $oFormPop -> getFormHeader(); ?>

<h1><?=$title;?></h1>
<div align=center><?= $oFormPop -> getMessage(); ?></div>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
<tr>
    <td class="table_cell_c" width="30%"><?= $oFormPop -> getElementLabel('searchCode'); ?></td>
    <td class="table_cell_2" width="40%"><?= $oFormPop -> getElementHtml('searchCode'); ?></td>
    <td class="table_cell_2" width="30%"></td>
</tr>
<tr>
    <td class="table_cell_c" width="30%"><?= $oFormPop -> getElementLabel('searchTitle'); ?></td>
    <td class="table_cell_2" width="40%"><?= $oFormPop -> getElementHtml('searchTitle'); ?></td>
    <td class="table_cell_2" width="30%">
    <? if(!$isReadonly)  {?>
        <?= $oFormPop -> getElementHtml('search'); ?>
    <?}?>
    </td>
</tr>

</table>
<br />
<? if($showResults) { ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
   <tr class="table_head_2">
	   <th width="55%"><?=text::get('NAME');?></th>
       <th  width="15%"><?=text::get('AMOUNT');?></th>
       <th  width="15%"><?=text::get('PRICE');?></th>
	   <th width="150%">&nbsp;</th>
   </tr>
   <?
   for ($j = 0; $j < count($resMater); $j++)    {
     $idName = "id_".$j;
     $idTitle = "title_".$j;
     $idAmount = "amount_".$j;
     $idSave = "save_".$j;
     $idPrice = "price_".$j;
   ?>
   <tr class="table_cell_3">
       <td>
            <?= $oFormPop->getElementHtml($idName); ?>
            <?= $oFormPop->getElementHtml($idTitle); ?>
       </td>
       <td><?= $oFormPop->getElementHtml($idAmount); ?></td>
       <td><?= $oFormPop->getElementHtml($idPrice); ?></td>
       <td>
        <? if(!$isReadonly)  {?>
            <?= $oFormPop->getElementHtml($idSave); ?>
        <?}?>
       </td>
   </tr>
   <?}?>
</table>
<? } ?>
<table cellpadding="5" cellspacing="0" border="0" align="center">
    <tr>
      <td><?=$oFormPop->getElementHtml('close');?></td>
    </tr>
</table>
<?= $oFormPop->getFormBottom(); ?>
<?=$oFormPop->getElementHtml('jsRefresh2');?>
</body>