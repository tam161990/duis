<body class="frame_1">
<?=$oForm->getElementHtml('jsRefresh2');?>
<?= $oForm -> getFormHeader(); ?>
<h1><?= text::get('KWOI_VV_NUMBER'); ?></h1>
<span><?= $oForm -> getMessage(); ?></span>
<table class="list" width="90%">
    
		<tr>
			<th width="10%"><?=text::get('TRASE');?></th>
			<th width="40%"><?=text::get('KWOI_VV_NUMBER');?></th>
           	<th width="30%"><?=text::get('SINGL_ED_AREA') ;?> </th>
            <th width="10%"><?=text::get('IS_ACTIVE');?></th>
			<th width="10">
				<a href="#" onclick="javascript:openNewBlock('empty_node'); return false;" title="<?= text::get('INSERT_NEW_ROW'); ?>">
					<img src="img/ico_new_row.gif" border="0"/>
				</a>
			</th>
		</tr>

<?
	for ($i=0; $i < CONTRACT_MAX_COUNT; $i++)
	{
?>
	     <tr id="empty_node<?=$i;?>" <?=(($oForm->getValue('contractId_'.$i)=='')? ' style="display:none;"' : 'style=""'); ?>  >
			<td width="10%"><?= $oForm -> getElementHtml('contractId_'.$i); ?><?= $oForm -> getElementHtml('isTrase_'.$i); ?></td>
			<td width="40%"><?= $oForm -> getElementHtml('contractNo_'.$i); ?></td>
            <td><?= $oForm -> getElementHtml('edArea_'.$i); ?></td>
            <td width="10%"><?= $oForm -> getElementHtml('isActive_'.$i); ?></td>
		   	<td width="10">
				<a href="#" onclick="javascript:if(confirm('<?=$warningMsgDelete;?>')) {
						eval(xmlHttpGetValue('<?=$oxmlHttpLinkD -> getQuery();?>&itemId='+document.all['contractId_<?=$i;?>'].value));
				} return false;" title="<?= text::get('DELETE'); ?>">
					<img src="img/ico_del.gif" border="0" />
				</a>
			</td>
		</tr>
<?
	}
?>
		<tr>
			<td colspan="5" class="controls">
				<?= ($oForm -> getElementHtml('save'))?$oForm -> getElementHtml('save'):''; ?>
				<?= $oForm -> getElementHtml('close'); ?>
			</td>
		</tr>

</table>
<?= $oForm -> getFormBottom(); ?>
</body>

