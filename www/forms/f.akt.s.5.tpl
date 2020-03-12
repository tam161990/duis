<h1><?=text::toUpper(text::get(TAB_PERONAL));?></h1>
<?= $oFormPersonalTab -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="2"><?= $oFormPersonalTab -> getMessage(); ?></td>
	</tr>
    <tr>
		<td valign="top">
        <table cellpadding="5" cellspacing="1" border="0" width="100%">
		   <tr class="table_head_2">

				<th width="12%"><?=text::get('RCD_KODS');?></th>
				<th width="40%"><?=text::get('USER_NAME');?> <?=text::get('USER_SURNAME');?></th>
				<th  width="15%"><?=text::get('PROPORTION');?></th>
                <th  width="15%"><?=text::get('BASE_TIME');?><br />(<?=$totalTimeFixed;?>)</th>
				<th  width="15%"><?=text::get('OVER_TIME');?><br />(<?=$totalTimeWithKoefFixed;?>)</th>
                <th width="3%">&nbsp;</th>
                <th width="3%">&nbsp;</th>
			</tr>

	  <?
	   	foreach($aCustomers as $i=>$val)
		{
		?>
			<tr class="table_cell_3"  id="blank_mat<?= $i; ?>">

				<td>
                    <?= $oFormPersonalTab->getElementHtml('id['.$i.']'); ?>
                    <?= $oFormPersonalTab->getElementHtml('code['.$i.']'); ?>
                </td>
				<td><?= $oFormPersonalTab->getElementHtml('nameSurname['.$i.']'); ?>
                    <?= $oFormPersonalTab->getElementHtml('place['.$i.']'); ?>
                    <?= $oFormPersonalTab->getElementHtml('region['.$i.']'); ?>
                </td>
                <td><?= $oFormPersonalTab->getElementHtml('proportion['.$i.']'); ?></td>
				<td><?= $oFormPersonalTab->getElementHtml('baseTime['.$i.']'); ?></td>
				<td><?= $oFormPersonalTab->getElementHtml('overTime['.$i.']'); ?></td>
                <td><?= $oFormPersonalTab->getElementHtml('isProportional['.$i.']'); ?></td>
             	<td>
                    <? if(!$isReadonly)  {?>
                    <?= $oFormPersonalTab->getElementHtml('cust_del['.$i.']'); ?>
                    <? } else{ ?>
                    &nbsp;
                    <? } ?>
                </td>
			</tr>

		<?
		}
		?>
        <tr>
             <td align="right" colspan="3"><b><?=text::get('TOTAL');?>:</b></td>
             <td align="center"><b><?= $totalWorkTime; ?></b></td>
             <td align="center"><b><?= $totalOverTime; ?></b></td>
        </tr>
	    </table>
        </td>
        <td width="20%"  valign="top">
            <table cellpadding="5" cellspacing="1" border="0" align="center" width="100%">
            <? if(!$isReadonly)  {
              foreach($favorit as $i=>$val){?>
             <tr>
                <td bgcolor="white" colspan="5"><?= $oFormPersonalTab->getElementHtml('favorit['.$i.']'); ?></td>
             </tr>
            <? } ?>
             <tr>
             <?
                for($i = 0; $i < 5; $i++)
                {
                   ?>
                   <td bgcolor="white"><?= $oFormPersonalTab->getElementHtml('regions['.$i.']'); ?></td>
                   <?
                }
             ?>
             </tr>

            <?} ?>
            </table>
            <br />
            <table cellpadding="5" cellspacing="0" border="0" align="center" >
            <tr>
             <? if(!$isReadonly)  {?>
            	<td><?= $oFormPersonalTab -> getElementHtml('save'); ?></td>
             <? } ?>

             </tr>
            </table>
        </td>
	</tr>

</table>
<?= $oFormPersonalTab -> getFormBottom(); ?>

