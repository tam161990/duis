
<body class="frame_2">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::get('RBF_EMPLOYEES'));?></h1>
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
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('nosaukums'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="26%"><?= $oForm -> getElementHtml('nosaukums'); ?></td>
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('isActive'); ?>:</td>
		<td class="table_cell_2" width="6%"><?= $oForm -> getElementHtml('isActive'); ?></td>
	</tr>
	<tr>
     	<td class="table_cell_c"><?= $oForm -> getElementLabel('vvType'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('vvType'); ?></td>
        <td class="table_cell_c"><?= $oForm -> getElementLabel('vvNumber'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('vvNumber'); ?></td>
		<td class="table_cell_c">&nbsp;</td>
		<td class="table_cell_2">&nbsp;</td>
	</tr>
	<tr>
     	<td class="table_cell_c" valign="top"><?= $oForm -> getElementLabel('territories'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2"><?= $oForm -> getElementHtml('territories'); ?><br><small><?=text::get('RBF_MULTISELECT_HELP');?></small></td>
        <td class="table_cell_c" valign="top"><?= $oForm -> getElementLabel('kontakti'); ?>:</td>
		<td class="table_cell_2" valign="top" colspan="3"><?= $oForm -> getElementHtml('kontakti'); ?></td>
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

<script type="text/javascript">
var territoriesNosaukums = <?=$territoriesNosaukumsJSON;?>;
var territoriesDID = <?=$territoriesDIDJSON;?>;

function updateTerritories() {
	try {
		var vvTypeElem = document.all["vvType"];
		var territoriesElem = document.all["territories[]"];
		
		if (!vvTypeElem || !territoriesElem) {
			return;
		}
		
		var vvType = vvTypeElem.value;
		var territoriesSelect = territoriesElem;
		var selectedValues = [];
		
		// Save currently selected values
		if (territoriesSelect.options) {
			for (var i = 0; i < territoriesSelect.options.length; i++) {
				if (territoriesSelect.options[i] && territoriesSelect.options[i].selected) {
					selectedValues.push(territoriesSelect.options[i].value);
				}
			}
		}
		
		// Clear existing options
		territoriesSelect.options.length = 0;
		
		// Get the appropriate territory list
		var territoryList = (vvType == "U") ? territoriesNosaukums : territoriesDID;
		
		// Add new options
		var optIndex = 0;
		for (var id in territoryList) {
			if (territoryList.hasOwnProperty(id)) {
				var isSelected = false;
				for (var j = 0; j < selectedValues.length; j++) {
					if (selectedValues[j] == id) {
						isSelected = true;
						break;
					}
				}
				territoriesSelect.options[optIndex] = new Option(territoryList[id], id, false, isSelected);
				optIndex++;
			}
		}
	} catch(e) {
		// Silent fail
	}
}
</script>

</body>
