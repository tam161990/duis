
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
		<td class="table_cell_2" ><?= $oForm -> getElementHtml('vvType'); ?></td>
		<td class="table_cell_c" valign="top"><?= $oForm -> getElementLabel('kontakti'); ?>:</td>
		<td class="table_cell_2" colspan="3"><?= $oForm -> getElementHtml('kontakti'); ?>
		<i><?=text::get('RBF_CONTACTS_HELP');?></i></td>
	</tr>

	<tr>
		<td colspan="6" align="center"><b><?=text::get('RBF_VV_ENTRIES');?>:</b> <font color="red">*</font></td>
	</tr>
</table>

<table cellpadding="3" cellspacing="1" border="0" width="100%" id="vvEntriesTable">
	<tr class="table_head_2">
		<td width="4%">#</td>
		<td width="28%"><?=text::get('RBF_VV_NUMBER');?> <font color="red">*</font></td>
		<td width="28%"><?=text::get('RBF_TERRITORY');?> <font color="red">*</font></td>
		<td width="36%"><?=text::get('RBF_VV_CONTACTS');?></td>
		<td width="4%">&nbsp;</td>
	</tr>
	<tbody id="vvEntriesBody">
		<!-- Dynamic rows will be added here -->
	</tbody>
	<tr>
		<td colspan="4" class="table_cell_2">
			<a href="#" onclick="addVVRow(); return false;" class="link">
				<img src="img/btn_pievienot.gif" width="70" height="20" border="0" style="vertical-align:middle;"> 
				<?=text::get('RBF_ADD_VV');?>
			</a>
		</td>
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
var existingVVEntries = <?=$existingVVEntriesJSON;?>;
var rowCounter = 0;

function getTerritoryOptions(selectedId) {
	var vvType = document.all['vvType'].value;
	var territoryList = (vvType == "U") ? territoriesNosaukums : territoriesDID;
	var html = '';
	for (var id in territoryList) {
		if (territoryList.hasOwnProperty(id)) {
			html += '<option value="' + id + '"' + (id == selectedId ? ' selected' : '') + '>' + territoryList[id] + '</option>';
		}
	}
	return html;
}

function addVVRow(vvNumber, territoryId, contacts) {
	vvNumber = vvNumber || '';
	territoryId = territoryId || '';
	contacts = contacts || '';
	
	var tbody = document.getElementById('vvEntriesBody');
	var tr = document.createElement('tr');
	tr.id = 'vvRow_' + rowCounter;
	tr.className = 'table_cell_2';
	
	// Escape HTML in contacts value
	var escapedContacts = contacts.replace(/"/g, '&quot;').replace(/'/g, '&#39;');
	
	tr.innerHTML = '<td>' + (rowCounter + 1) + '</td>' +
		'<td><input type="text" name="vvNumber_' + rowCounter + '" maxlength="15" value="' + vvNumber + '" style="width:100%;"></td>' +
		'<td><select name="territory_' + rowCounter + '" id="territory_' + rowCounter + '" style="width:100%;">' +
		getTerritoryOptions(territoryId) +
		'</select></td>' +
		'<td><input type="text" name="contacts_' + rowCounter + '" maxlength="500" value="' + escapedContacts + '" style="width:100%;" placeholder="<?=text::get('RBF_CONTACTS_HELP');?>"></td>' +
		'<td><a href="#" onclick="removeVVRow(' + rowCounter + '); return false;">' +
		'<img src="img/btn_dzest.gif" width="70" height="20" border="0" title="<?=text::get('RBF_REMOVE');?>"></a>' +
		'<input type="hidden" name="deleted_' + rowCounter + '" id="deleted_' + rowCounter + '" value="0"></td>';
	
	tbody.appendChild(tr);
	rowCounter++;
	document.all['vvRowCount'].value = rowCounter;
	updateRowNumbers();
}

function removeVVRow(rowId) {
	document.all['deleted_' + rowId].value = '1';
	var row = document.getElementById('vvRow_' + rowId);
	if (row) {
		row.style.display = 'none';
	}
	updateRowNumbers();
}

function updateAllTerritories() {
	// Update all territory dropdowns when VV Type changes
	for (var i = 0; i < rowCounter; i++) {
		var territorySelect = document.all['territory_' + i];
		if (territorySelect && document.all['deleted_' + i].value != '1') {
			var selectedValue = territorySelect.value;
			territorySelect.innerHTML = getTerritoryOptions(selectedValue);
		}
	}
}

function updateRowNumbers() {
	var tbody = document.getElementById('vvEntriesBody');
	var visibleRows = 0;
	for (var i = 0; i < tbody.rows.length; i++) {
		var row = tbody.rows[i];
		if (row.style.display != 'none') {
			visibleRows++;
			row.cells[0].innerHTML = visibleRows;
		}
	}
}

function validateVVEntries() {
	var vvRowCount = parseInt(document.all['vvRowCount'].value);
	var hasValidEntry = false;
	
	for (var i = 0; i < vvRowCount; i++) {
		var deleted = document.all['deleted_' + i] ? document.all['deleted_' + i].value : '0';
		var vvNumber = document.all['vvNumber_' + i] ? document.all['vvNumber_' + i].value : '';
		var territory = document.all['territory_' + i] ? document.all['territory_' + i].value : '';
		
		if (deleted != '1' && vvNumber && territory) {
			hasValidEntry = true;
			break;
		}
	}
	
	if (!hasValidEntry) {
		alert('<?=text::get('ERROR_MIN_ONE_VV');?>');
		return false;
	}
	
	return true;
}

// Initialize with existing entries or add one empty row
if (existingVVEntries && existingVVEntries.length > 0) {
	for (var i = 0; i < existingVVEntries.length; i++) {
		addVVRow(
			existingVVEntries[i].RBDV_VV_NUMURS,
			existingVVEntries[i].RBDV_RBTR_KODS,
			existingVVEntries[i].RBDV_KONTAKTI || ''
		);
	}
} else {
	addVVRow(); // Add one empty row
}
</script>

</body>
