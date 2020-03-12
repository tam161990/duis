
<body class="frame_2">

<table cellpadding="0" cellspacing="0" border="0" width="100%">
	<tr>
		<td><h1><?= text::toUpper(text::get('REPORT_MMS_CALC')); ?></h1></td>
		<td align="right">
            <img src="img/ico_print.gif" alt="" width="16" height="16" border="0">&nbsp;
            <a href="<?= $printUrl; ?>" target="new"><?=text::get('PRINT');?></a>&nbsp;&nbsp;

        </td>
	</tr>
</table>

<table cellpadding="5" cellspacing="1" border="0" width="100%" >
	<thead>
		<tr class="table_head_2">
            <td width="17%"><?= text::get('SINGLE_MMS'); ?> <?= text::get('CODE'); ?></td>
			<td width="13%"><?= text::get('MAIN_DESIGNATION'); ?></td>
			<td width="5%"><?= text::get('PLAN_CODE'); ?></td>
            <td width="20%"><?=text::get('TOTAL_WORK_NAME');?></td>
            <td width="10%"><?=text::get('PLAN_AMOUNT');?></td>
            <td width="5%"><?= text::get('UNIT_OF_MEASURE'); ?></td>
			<td width="10%"><?= text::get('PLAN_PRICES').', EUR'; ?></td>
            <td width="10%"><?= text::get('DONE_AMOUNT'); ?></td>
            <td width="10%"><?=text::get('PAYMENT_AMOUNT').', EUR';?></td>

 		</tr>
	</thead>
	<tbody>
<?
	if (is_array($res) && count($res) > 0)
	{
		foreach ($res as $row)
		{
           if($row['planAmount'] == -1) continue;
?>
			<tr class="table_cell_3" >
                <td align="center"><?= $row['KMSD_KODS']; ?></td>
			   	<td align="center"><?= $row['RAKT_OPERATIVAS_APZIM']; ?></td>
                <td align="left"><?= $row['KKAL_FIZ_RADIJUMS']; ?></td>
                <td align="left"><?= $row['DRBI_KKAL_NOSAUKUMS']; ?></td>
                <td align="left"><?= $row['planAmount']; ?></td>
                <td align="left"><?= $row['DRBI_MERVIENIBA']; ?></td>
                <td align="left"><?= $row['planPrice']; ?></td>
                <td align="left"><?= $row['DRBI_DAUDZUMS']; ?></td>
                <td align="center"><?= $row['DRBI_CILVEKSTUNDAS']; ?></td>

			</tr>
<?
		}
?>
        <tr>
             <td align="right" colspan="6"><b><?=text::get('TOTAL');?>:</b></td>
             <td align="center"><b><?= $planPrice; ?></b></td>
             <td align="center"><b>&nbsp;</b></td>
             <td align="center"><b><?= $realPrice; ?></b></td>
        </tr>
<?
	}
?>
	</tbody>
</table>

</body>