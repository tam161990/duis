<body class="print">
<div class="print_header"><?= text::get('REPORT_MMS_CALC'); ?></div>
<table cellpadding="0" cellspacing="0" class="print_table_landscape" >
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
<table cellpadding="0" cellspacing="0" class="print_table_landscape" >

		<tr>
            <td width="17%" class="print_table_header"><?= text::get('SINGLE_MMS'); ?> <?= text::get('CODE'); ?></td>
			<td width="13%" class="print_table_header"><?= text::get('MAIN_DESIGNATION'); ?></td>
			<td width="5%" class="print_table_header"><?= text::get('PLAN_CODE'); ?></td>
            <td width="20%" class="print_table_header"><?=text::get('TOTAL_WORK_NAME');?></td>
            <td width="10%" class="print_table_header"><?=text::get('PLAN_AMOUNT');?></td>
            <td width="5%" class="print_table_header"><?= text::get('UNIT_OF_MEASURE'); ?></td>
			<td width="10%" class="print_table_header"><?= text::get('PLAN_PRICES').', EUR'; ?></td>
            <td width="10%" class="print_table_header"><?= text::get('DONE_AMOUNT'); ?></td>
            <td width="10%" class="print_table_header"><?=text::get('PAYMENT_AMOUNT').', EUR';?></td>


 		</tr>

<?
	if (is_array($res) && count($res) > 0)
	{
		foreach ($res as $row)
		{
		   if($row['planAmount'] == -1) continue;
?>
			<tr >
                <td align="center" class="print_table_data"><?= $row['KMSD_KODS']; ?></td>
			   	<td align="center" class="print_table_data"><?= $row['RAKT_OPERATIVAS_APZIM']; ?></td>
                <td align="left" class="print_table_data"><?= $row['KKAL_FIZ_RADIJUMS']; ?></td>
                <td align="left" class="print_table_data"><?= $row['DRBI_KKAL_NOSAUKUMS']; ?></td>
                <td align="left" class="print_table_data"><?= $row['planAmount']; ?></td>
                <td align="left" class="print_table_data"><?= $row['DRBI_MERVIENIBA']; ?></td>
                <td align="left" class="print_table_data"><?= $row['planPrice']; ?></td>
                <td align="left" class="print_table_data"><?= $row['DRBI_DAUDZUMS']; ?></td>
                <td align="center" class="print_table_data"><?= $row['DRBI_CILVEKSTUNDAS']; ?></td>


			</tr>
<?
		}
?>
        <tr>
             <td align="right" class="print_table_total" colspan="6"><?=text::get('TOTAL');?>:</td>
             <td align="center" class="print_table_total"><?= $planPrice; ?></td>
             <td align="center" class="print_table_total">&nbsp;</td>
             <td align="center" class="print_table_total"><?= $realPrice; ?></td>
        </tr>
<?
	}
?>

</table>

</body>