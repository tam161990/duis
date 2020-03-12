<h1><?=text::toUpper(text::get(TAB_TRANSPORT));?></h1>
<?= $oFormTransportTab -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="2"><?= $oFormTransportTab -> getMessage(); ?></td>
	</tr>
    <tr>
		<td valign="top">
        <table cellpadding="5" cellspacing="1" border="0" width="100%">
		   <tr class="table_head_2">

				<th width="12%"><?=text::get('NATION_NUMBER');?></th>
				<th width="37%"><?=text::get('GROUP_TITLE');?></th>
				<th  width="12%"><?=text::get('SUBGROUP_TITLE');?></th>
                <th  width="12%"><?=text::get('TRANSPORT_KM');?></th>
				<th  width="12%"><?=text::get('TRANSPORT_AVTO_TIME');?></th>
				<th  width="12%"><?=text::get('TRANSPORT_WORK_TIME');?></th>
			 	<th width="3%">&nbsp;</th>
			</tr>

	  <?
	   	foreach($aTransports as $i=>$val)
		{
		?>
			<tr class="table_cell_3"  id="blank_mat<?= $i; ?>">

				<td>
                    <?= $oFormTransportTab->getElementHtml('id['.$i.']'); ?>
                    <?= $oFormTransportTab->getElementHtml('code['.$i.']'); ?>
                </td>
				<td><?= $oFormTransportTab->getElementHtml('group['.$i.']'); ?></td>
				<td>
                    <?= $oFormTransportTab->getElementHtml('apGroup['.$i.']'); ?>
                    <?= $oFormTransportTab->getElementHtml('apGroupCode['.$i.']'); ?>
                    <?= $oFormTransportTab->getElementHtml('ouner['.$i.']'); ?>
                </td>
                <td><?= $oFormTransportTab->getElementHtml('km['.$i.']'); ?></td>
				<td><?= $oFormTransportTab->getElementHtml('stundas['.$i.']'); ?></td>
				<td><?= $oFormTransportTab->getElementHtml('total2['.$i.']'); ?></td>
             	<td>
                    <? if(!$isReadonly)  {?>
                    <?= $oFormTransportTab->getElementHtml('trans_del['.$i.']'); ?>
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
             <td align="center"><b><?= $totalKm; ?></b></td>
             <td align="center"><b><?= $totalTime; ?></b></td>
             <td align="center"><b><?= $totalWorkTime; ?></b></td>
        </tr>
	    </table>
        </td>
        <td width="20%"  valign="top">
            <table cellpadding="5" cellspacing="1" border="0" align="center" width="100%">
            <? if(!$isReadonly)  {
              foreach($favorit as $i=>$val){?>
             <tr>
                <td bgcolor="white" colspan="3"><?= $oFormTransportTab->getElementHtml('favorit['.$i.']'); ?></td>
             </tr>
            <? } ?>
             <tr>
             <?
                for($i = 0; $i < 3; $i++)
                {
                   ?>
                   <td bgcolor="white"><?= $oFormTransportTab->getElementHtml('region['.$i.']'); ?></td>
                   <?
                }
             ?>
             </tr>
             <tr>
             <?
                for($i = 3; $i < 6; $i++)
                {
                   ?>
                   <td bgcolor="white"><?= $oFormTransportTab->getElementHtml('region['.$i.']'); ?></td>
                   <?
                }
             ?>
             </tr>
            <?} ?>
            </table>
            <br />
            <table cellpadding="5" cellspacing="0" border="0" align="center">
            <tr>
             <? if(!$isReadonly)  {?>
            	<td><?= $oFormTransportTab -> getElementHtml('save'); ?></td>
             <? } ?>

             </tr>
            </table>
        </td>
	</tr>

</table>
<?= $oFormTransportTab -> getFormBottom(); ?>

