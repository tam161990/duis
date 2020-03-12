<body class="frame_1">
<h1><?=text::get('REPORT');?></h1>


<? if(true/*$isEdUser || $isAdmin*/){ ?>
<table class="list" width="90%">
	<thead>
		<tr>
			<th><?= text::get('ED_REPORTS'); ?></th>
		</tr>
	</thead>
	<tbody>
    <tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $actTotalReportLink; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_ACT_TOTAL'); ?></td>
	</tr>
    <tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $workTotalReportLink; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_WORK_TOTAL'); ?></td>
	</tr>
    <tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $materialTotalReportLink; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_MATERIAL_TOTAL'); ?></td>
	</tr>
    <!--tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $actMainReportLink; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_MAIN_ACT'); ?></td>
	</tr-->
    <!--tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $actMainReportStstusLink; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_MAIN_ACT_STAUSI'); ?></td>
	</tr-->
     <!--tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $workPhisicalShowingReportLink; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_PHISICAL_SHOWING'); ?></td>
	</tr-->
	</tbody>
</table>
<br /><br />
<table class="list" width="90%">
	<thead>
		<tr>
			<th><?= text::get('TRASE'); ?></th>
		</tr>
	</thead>
	<tbody>
    <tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $actTrTotalReportLink; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_ACT_TOTAL'); ?></td>
	</tr>
    <tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $workTrTotalReportLink; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_WORK_TOTAL'); ?></td>
	</tr>
    <tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $materialTrTotalReportLink; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_MATERIAL_TOTAL'); ?></td>
	</tr>
    <!--tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $actTrMainReportLink; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_MAIN_ACT'); ?></td>
	</tr-->
     <!--tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $actTrMmsCalc; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_MMS_CALC'); ?></td>
	</tr-->

	</tbody>
</table>
<? } ?>
</body>