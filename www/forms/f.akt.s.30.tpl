<script language="javascript">
function loadVVNumbers(employeeCode) {
	if(employeeCode != "")
	{
		var url = "?formId=f.akt.s.30&xmlHttp=1&employeeCode=" + employeeCode;
		eval(xmlHttpGetValue(url));
	}
	else
	{
		document.all["vvNumber"].options.length = 1;
		document.all["department"].options.length = 1;
	}
}

function loadDepartments(vvNumber) {
	if(vvNumber != "")
	{
		var url = "?formId=f.akt.s.30&xmlHttp=1&vvNumber=" + vvNumber;
		eval(xmlHttpGetValue(url));
	}
	else
	{
		document.all["department"].options.length = 1;
	}
}

function loadAuthors(employeeCode) {
	if(employeeCode != "")
	{
		var url = "?formId=f.akt.s.30&xmlHttp=1&loadAuthors=" + employeeCode;
		eval(xmlHttpGetValue(url));
	}
	else
	{
		document.all["author"].options.length = 1;
	}
}

// Trigger initial load if employee is pre-selected
window.onload = function() {
	var employeeSelect = document.all["employeeCode"];
	if(employeeSelect && employeeSelect.value) {
		loadVVNumbers(employeeSelect.value);
		loadAuthors(employeeSelect.value);
		
		// If VV number is already set (editing), load departments after a short delay
		setTimeout(function() {
			var vvSelect = document.all["vvNumber"];
			if(vvSelect && vvSelect.value) {
				loadDepartments(vvSelect.value);
			}
		}, 500);
	}
};
</script>

<body class="frame_1">
	
	<?= $oForm -> getFormHeader(); ?>
	<table cellpadding="0" cellspacing="0" border="0" width="100%">
		<tr>
			<td><h1><?=text::toUpper(text::get('RBF_ACT'));?></h1></td>
			<td align="right">&nbsp;</td>
		</tr>
	</table>
	
	<table cellpadding="5" cellspacing="1" border="0" width="100%">
		<tr>
			<td align=center colspan="5"><?= $oForm -> getMessage(); ?></td>
		</tr>
		<tr>
			<td colspan="2" class="table_head" align="right">
			<? if($actId != false)  {?>
				<?= $oForm -> getElementHtml('actFullNumber'); ?>
			<? } ?>
			</td>
			<td colspan="2" class="table_head" align="right">
				<?= $oForm -> getElementLabel('statusTxt'); ?>:
				<font color="red"><?=text::toUpper($oForm -> getElementHtml('statusTxt'));?></font>
			</td>
			<td width="20%" rowspan="11" valign="bottom">
				<table cellpadding="5" cellspacing="0" border="0" align="center">
				<? if(!$isReadonly || !$isReadonlyExceptAdmin)  {?>
					<tr><td><?= $oForm -> getElementHtml('save'); ?></td></tr>
				<? } ?>
				
				<? if($actId != false && ($status == STAT_INSERT || $status == STAT_RETURN))  {?>
					<tr><td><?=$oForm->getElementHtml('export');?></td></tr>
				<? } ?>
				
				<? if($actId != false && $status == STAT_ACCEPT && ($isEconomist || $isAdmin))  {?>
					<tr><td><?=$oForm->getElementHtml('accept');?></td></tr>
					<tr><td><?=$oForm->getElementHtml('return');?></td></tr>
				<? } ?>
				
				<? if($actId != false)  {?>
					<tr><td><?=$oForm->getElementHtml('back');?></td></tr>
				<? } ?>
				</table>
			</td>
		</tr>
		
		<tr>
			<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('employeeCode'); ?>:<font color="red">*</font></td>
			<td class="table_cell_2"  width="24%"><?= $oForm -> getElementHtml('employeeCode'); ?></td>
			<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('author'); ?>:<font color="red">*</font></td>
			<td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('author'); ?></td>
		</tr>
		
		<tr>
			<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('vvNumber'); ?>:<font color="red">*</font></td>
			<td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('vvNumber'); ?></td>
			<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('actType'); ?>:<font color="red">*</font></td>
			<td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('actType'); ?></td>
		</tr>
		
		<tr>
			<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('department'); ?>:<font color="red">*</font></td>
			<td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('department'); ?></td>
			<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('orderId'); ?>:<font color="red">*</font></td>
			<td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('orderId'); ?></td>
		</tr>
		
		<tr>
			<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('signature'); ?>:<font color="red">*</font></td>
			<td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('signature'); ?></td>
			<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('capitalize'); ?>:</td>
			<td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('capitalize'); ?></td>
		</tr>
		
		<tr>
			<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('workTitle'); ?>:<font color="red">*</font></td>
			<td class="table_cell_2" colspan="3"><?= $oForm -> getElementHtml('workTitle'); ?></td>
		</tr>
		
		<tr>
			<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('notes'); ?>:</td>
			<td class="table_cell_2" colspan="3"><?= $oForm -> getElementHtml('notes'); ?></td>
		</tr>
	</table>
	
	<a name="tab"></a>
	<?= $oForm -> getFormBottom(); ?>
	<?= $oForm -> getElementHtml('jsBackButtons'); ?>
	
</body>

