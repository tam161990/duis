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
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $actTotalReportLinkP; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_ACT_TOTAL_P'); ?></td>
	</tr>
	<tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $actTotalReportLinkE; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_ACT_TOTAL_E'); ?></td>
	</tr>
    <tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $workTotalReportLinkP; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_WORK_TOTAL_P'); ?></td>
	</tr>
	<tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $workTotalReportLinkE; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_WORK_TOTAL_E'); ?></td>
	</tr>
    <tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $materialTotalReportLinkP; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_MATERIAL_TOTAL_P'); ?> ST</td>
	</tr>
	<tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $materialTotalReportLinkE; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_MATERIAL_TOTAL_E'); ?> ST</td>
	</tr>

	<tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $materialTotalReportLinkPDU; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_MATERIAL_TOTAL_P'); ?> DU</td>
	</tr>
	<tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $materialTotalReportLinkEDU; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_MATERIAL_TOTAL_E'); ?> DU</td>
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
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $actTrTotalReportLinkP; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_ACT_TOTAL_P'); ?></td>
	</tr>
	<tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $actTrTotalReportLinkE; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_ACT_TOTAL_E'); ?></td>
	</tr>
    <tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $workTrTotalReportLinkP; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_WORK_TOTAL_P'); ?></td>
	</tr>
	<tr onmouseover="makeActiveRow2(this,'x');"
	onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $workTrTotalReportLinkE; ?>');reloadFrame(23,'');">
	<td><?= text::get('REPORT_WORK_TOTAL_E'); ?></td>
	</tr>
    <tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $materialTrTotalReportLinkP; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_MATERIAL_TOTAL_P'); ?></td>
	</tr>
	<tr onmouseover="makeActiveRow2(this,'x');"
		onClick="parent['frameTop'].enableFrameControl();window.top.normal();reloadFrame(1,'<?= $materialTrTotalReportLinkE; ?>');reloadFrame(23,'');">
		<td><?= text::get('REPORT_MATERIAL_TOTAL_E'); ?></td>
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