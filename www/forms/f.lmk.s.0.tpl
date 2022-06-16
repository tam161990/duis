<body class="frame_1">
<h1><?=text::get('REPORT');?></h1>


<? if($isLimitCardUser || $isAdmin){ ?>
<table class="list" width="90%">
	<tbody>
    <tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].disableFrameControl();window.top.normal();reloadFrame(1,'<?= $projectMaterialReport; ?>');reloadFrame(23,'');">
		<td><?= text::get('PROJRCT_MATERIAL_REPORT'); ?></td>
	</tr>
	<tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $uncompletedPrReport; ?>');reloadFrame(23,'');">
		<td><?= text::get('UNCOMPLETED_PROJECT_REPORT'); ?></td>
	</tr>    
	</tbody>
</table>
<? } ?>
</body>