<body class="frame_2">

<table cellpadding="0" cellspacing="0" border="0" width="100%">
	<tr>
		<td><h1><?= text::toUpper(text::get('REPORT_WORK_TOTAL').(($trase == 1) ? ' ('.text::get('TRASE').')' : '' )); ?></h1></td>
		<td align="right">

            <img src="img/ico_pdf.gif" alt="" width="16" height="16">&nbsp;
            <a href="<?= $exportUrl; ?>" ><?=text::get('EXPORT_TO_PDF');?></a>&nbsp;
        </td>
	</tr>
</table>

<table cellpadding="5" cellspacing="1" border="0" width="100%" >
<?
	if (is_array($area) && count($area) > 0)
	{
		foreach ($area as $row)
		{
?>
            <tr class="table_cell_3">

                <td colspan="2" align="right"><b><?=text::get('WRITE_OFF_ACCOUNT');?>:</b></td>
                <td colspan="4" align="left"><?= $row['writeoftitle']; ?></td>
            </tr>
            <tr class="table_head_2">
    			<td width="10%"><?= text::get('CHIPHER'); ?></td>
                <td width="30%"><?=text::get('TOTAL_WORK_NAME');?></td>
                <td width="15%"><?= text::get('UNIT_OF_MEASURE'); ?></td>
                <td width="15%"><?= text::get('AMOUNT'); ?></td>
                <td width="15%"><?=text::get('UNIT_PRICE').', EUR';?></td>
                <td width="15%"><?=text::get('PRICE').', EUR';?></td>
            </tr>
             <?
                if (is_array($row['work']) && count($row['work']) > 0)
                {
                   foreach ($row['work'] as $r)
                   {
                     ?>
                   <tr class="table_cell_3" >
      			      <td align="center"><?= $r['code']; ?></td>
                      <td align="left"><?= $r['name']; ?></td>
                      <td align="center"><?= $r['miasure']; ?></td>
                      <td align="center"><?= $r['quantity']; ?></td>
                      <td align="center"><?= $r['cena']; ?></td>
                      <td align="center"><?= $r['total']; ?></td>
                  </tr>
                     <?

                   }
                }
            ?>
            <tr class="table_head_2">
             <td colspan="5" align="right"><b><?=text::get('TOTAL');?>: </b></td>
             <td align="center"><b><?=number_format($row['Cena'],2,'.','');?></b></td>
            </tr>
            <tr class="table_head_2">
             <td colspan="5" align="right"><b><?=text::get('PCT').' '. $pvn . '%';?>: </b></td>
             <td align="center"><b><?=number_format($row['Pct'],2,'.','');?></b></td>
            </tr>
            <tr class="table_head_2">
             <td colspan="5" align="right"><b><?=text::get('TOTAL_WITH_PCT');?>: </b></td>
             <td align="center"><b><?=number_format($row['Total'],2,'.','');?></b></td>
            </tr>
            <tr><td colspan="6">&nbsp;</td></tr>
<? }}?>
<tr class="table_head_2">
             <td colspan="5" align="right"><b><?=text::get('TOTAL');?>: </b></td>
             <td align="center"><b><?=number_format($Totalsumma,2,'.','');?></b></td>
            </tr>
            <tr class="table_head_2">
             <td colspan="5" align="right"><b><?=text::get('PCT').' '. $pvn . '%';?>: </b></td>
             <td align="center"><b><?=number_format($Totalpct,2,'.','');?></b></td>
            </tr>
            <tr class="table_head_2">
             <td colspan="5" align="right"><b><?=text::get('TOTAL_WITH_PCT');?>: </b></td>
             <td align="center"><b><?=number_format($Totaltotal,2,'.','');?></b></td>
            </tr>
            <tr><td colspan="6">&nbsp;</td></tr>
</table>

</body>