<body class="frame_2">

<table cellpadding="0" cellspacing="0" border="0" width="100%">
	<tr>
		<td><h1><?= text::toUpper(text::get('REPORT_PHISICAL_SHOWING')); ?></h1></td>
		<td align="right">
            <img src="img/ico_print.gif" alt="" width="16" height="16" border="0">&nbsp;
            <a href="<?= $printUrl; ?>" target="new"><?=text::get('PRINT');?></a>&nbsp;&nbsp;
            <img src="img/ico_excel.gif" alt="" width="16" height="16">&nbsp;
            <a href="<?= $exportUrl; ?>" ><?=text::get('EXPORT');?></a>&nbsp;
        </td>
	</tr>
</table>

<table cellpadding="5" cellspacing="1" border="0" width="100%" >
<?

	if (is_array($area) && count($area) > 0)
	{
		foreach ($area as $row)
		{
		  if(count($row['dataRow']) > 0)
          {
?>
            <!--tr class="table_head_2">
                <td align="left" colspan="5"><b><?= (($row['code'] == '999999') ? '' : text::get('ED_IECIKNIS').': ');?> <?= $row['name']; ?></b></td>
                <td align="left" colspan="12"><b><?= (($row['code'] == '999999') ? '' : $row['code']);?></b></td>

            </tr-->

            <tr class="table_head_2">

                <td width="20%" rowspan="2"><?=text::get('WORK_TITLE');?></td>
                <td width="5%" rowspan="2"><?=text::get('UNIT_OF_MEASURE');?></td>
                <td width="5%" rowspan="2"><?=text::get('REPORT_PHISICAL_SHOWING_PLAN');?></td>
                <td width="5%" rowspan="2"><?= text::get('REPORT_PHISICAL_SHOWING_DONE'); ?></td>
                <td width="5%" rowspan="2"><?=text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN');?></td>
                <td width="15%" colspan="3">I</td>
                <td width="15%" colspan="3">II</td>
                <td width="15%" colspan="3">III</td>
                <td width="15%" colspan="3">IV</td>
            </tr>
            <tr class="table_head_2">
                <td width="5%"><?=text::get('REPORT_PHISICAL_SHOWING_PLAN');?></td>
                <td width="5%"><?= text::get('REPORT_PHISICAL_SHOWING_DONE'); ?></td>
                <td width="5%"><?= text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN'); ?></td>
                <td width="5%"><?=text::get('REPORT_PHISICAL_SHOWING_PLAN');?></td>
                <td width="5%"><?= text::get('REPORT_PHISICAL_SHOWING_DONE'); ?></td>
                <td width="5%"><?= text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN'); ?></td>
                <td width="5%"><?=text::get('REPORT_PHISICAL_SHOWING_PLAN');?></td>
                <td width="5%"><?= text::get('REPORT_PHISICAL_SHOWING_DONE'); ?></td>
                <td width="5%"><?= text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN'); ?></td>
                <td width="5%"><?=text::get('REPORT_PHISICAL_SHOWING_PLAN');?></td>
                <td width="5%"><?= text::get('REPORT_PHISICAL_SHOWING_DONE'); ?></td>
                <td width="5%"><?= text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN'); ?></td>

            </tr>

          <?
          foreach ($row['dataRow'] as $i=>$arow)
		  {
            //if($arow['calcMms'] != 0 || $arow['calcPlan'] !=0 || $arow['calcNotPlan'] != 0)
            //{
            ?>
            <tr class="table_cell_3" >

                 <td align="left"><?=(($sCr[8] == 1) ? $rowName['low'][$i] : $rowName['middle'][$i]);?></td>
                 <td align="center"><?= $arow['calcMeasure'];?></td>
                 <td align="center"><?= $arow['calcMms']; ?></td>
                 <td align="center"><?= $arow['calcPlan']; ?></td>
                 <td align="center"><?= $arow['calcNotPlan']; ?></td>

                 <td align="center"><?= $arow['calcMms1']; ?></td>
                 <td align="center"><?= $arow['calcPlan1']; ?></td>
                 <td align="center"><?= $arow['calcNotPlan1']; ?></td>
                 <td align="center"><?= $arow['calcMms2']; ?></td>
                 <td align="center"><?= $arow['calcPlan2']; ?></td>
                 <td align="center"><?= $arow['calcNotPlan2']; ?></td>
                 <td align="center"><?= $arow['calcMms3']; ?></td>
                 <td align="center"><?= $arow['calcPlan3']; ?></td>
                 <td align="center"><?= $arow['calcNotPlan3']; ?></td>
                 <td align="center"><?= $arow['calcMms4']; ?></td>
                 <td align="center"><?= $arow['calcPlan4']; ?></td>
                 <td align="center"><?= $arow['calcNotPlan4']; ?></td>
            </tr>
          <?
          //}
        }
        ?>
        <tr><td colspan="17">&nbsp;</td></tr>
        <?

		}
    }
}
?>

</table>

</body>