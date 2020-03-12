<body class="frame_1">
<?= $oFormPop -> getFormHeader(); ?>

<h1><?=$title;?></h1>
<div align=center><?= $oFormPop -> getMessage(); ?></div>

<table cellpadding="5" cellspacing="1" border="0" width="100%">
   <tr>
	   <th width="20%" class="table_head_2"><?=text::get('NAME');?></th>
       <td class="table_cell_3"><?= $oFormPop->getElementHtml('title'); ?> </td>
   </tr>
   <tr>
	   <th class="table_head_2"><?=text::get('UNIT_OF_MEASURE');?></th>
       <td class="table_cell_3"><?= $oFormPop->getElementHtml('mervieniba'); ?> </td>
   </tr>
   <tr>
	   <th class="table_head_2"><?=text::get('AMOUNT');?></th>
       <td class="table_cell_3"><?= $oFormPop->getElementHtml('amount'); ?></td>
   </tr>
   <tr>
	    <th class="table_head_2"><?=text::get('PRICE');?></th>
       <td class="table_cell_3"><?= $oFormPop->getElementHtml('price'); ?></td>
   </tr>


</table>

<table cellpadding="5" cellspacing="0" border="0" align="center">
    <tr>
      <td>
        <? if(!$isReadonly)  {?>
            <?= $oFormPop->getElementHtml('save'); ?>
        <?}?>
       </td>
      <td><?=$oFormPop->getElementHtml('close');?></td>
    </tr>
</table>
<?= $oFormPop->getFormBottom(); ?>
<?=$oFormPop->getElementHtml('jsRefresh2');?>
</body>