<body class="print">
<div class="print_header"><?= text::get('REPORT_PHISICAL_SHOWING'); ?></div>
<table cellpadding="0" cellspacing="0" class="print_table_portrait" >
<?
  foreach($searchCr as $i=>$s)
  {
    if($i%3 == 0)
    {
      ?>
        <tr>
      <?
    }
    ?>
      <td align="right" class="print_table_total" width="13%"><?=$s['label'];?>:</td>
      <td align="left" class="print_table_data" width="20%"><?=$s['value'];?></td>
    <?
  }
?>
</table>

<br />
<table cellpadding="0" cellspacing="0" class="print_table_portrait" >
<?

	if (is_array($area) && count($area) > 0)
	{
		foreach ($area as $row)
		{
          if(count($row['dataRow']) > 0)
          {
?>
           <!--tr>
                <td align="left" colspan="5" class="print_table_header2"><b><?= (($row['code'] == '999999') ? '' : text::get('ED_IECIKNIS').': ');?> <?= $row['name']; ?></b></td>
                <td align="left" colspan="12" class="print_table_header2"><b><?= (($row['code'] == '999999') ? '' : $row['code']);?></b></td>
            </tr-->

            <tr >

                <td width="20%" rowspan="2" class="print_table_header2"><?=text::get('WORK_TITLE');?></td>
                <td width="5%" rowspan="2" class="print_table_header2"><?=text::get('UNIT_OF_MEASURE');?></td>
                <td width="5%" rowspan="2" class="print_table_header2"><?=text::get('REPORT_PHISICAL_SHOWING_PLAN');?></td>
                <td width="5%" rowspan="2" class="print_table_header2"><?= text::get('REPORT_PHISICAL_SHOWING_DONE'); ?></td>
                <td width="5%" rowspan="2" class="print_table_header2"><?=text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN');?></td>
                <td width="15%" colspan="3" class="print_table_header2">I</td>
                <td width="15%" colspan="3" class="print_table_header2">II</td>
                <td width="15%" colspan="3" class="print_table_header2">III</td>
                <td width="15%" colspan="3" class="print_table_header2">IV</td>
            </tr>
            <tr>
                <td width="5%" class="print_table_header2"><?=text::get('REPORT_PHISICAL_SHOWING_PLAN');?></td>
                <td width="5%" class="print_table_header2"><?= text::get('REPORT_PHISICAL_SHOWING_DONE'); ?></td>
                <td width="5%" class="print_table_header2"><?= text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN'); ?></td>
                <td width="5%" class="print_table_header2"><?=text::get('REPORT_PHISICAL_SHOWING_PLAN');?></td>
                <td width="5%" class="print_table_header2"><?= text::get('REPORT_PHISICAL_SHOWING_DONE'); ?></td>
                <td width="5%" class="print_table_header2"><?= text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN'); ?></td>
                <td width="5%" class="print_table_header2"><?=text::get('REPORT_PHISICAL_SHOWING_PLAN');?></td>
                <td width="5%" class="print_table_header2"><?= text::get('REPORT_PHISICAL_SHOWING_DONE'); ?></td>
                <td width="5%" class="print_table_header2"><?= text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN'); ?></td>
                <td width="5%" class="print_table_header2"><?=text::get('REPORT_PHISICAL_SHOWING_PLAN');?></td>
                <td width="5%" class="print_table_header2"><?= text::get('REPORT_PHISICAL_SHOWING_DONE'); ?></td>
                <td width="5%" class="print_table_header2"><?= text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN'); ?></td>

            </tr>
           <?
          foreach ($row['dataRow'] as $i=>$arow)
		  {
            //if($arow['calcMms'] != 0 || $arow['calcPlan'] !=0 || $arow['calcNotPlan'] != 0)
            //{
            ?>
            <tr>

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
         // }
        }
        ?>
        <tr><td colspan="17"  class="print_table_data2">&nbsp;</td></tr>
        <?

		}
    }
}
?>

</table>

</body>
