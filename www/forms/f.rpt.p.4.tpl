<body class="print">
<div class="print_header"><?= text::get('REPORT_MAIN_ACT').(($trase == 1) ? ' ('.text::get('TRASE').')' : '' ); ?></div>
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


            <td width="17%" class="print_table_header"><?= text::get('SINGL_WORK_OWNER'); ?></td>
			<td width="8%" class="print_table_header"><?= text::get('ACT_NUMBER'); ?></td>
			<td width="5%" class="print_table_header"><?= text::get('SINGLE_ACT_TYPE'); ?></td>
            <td width="5%" class="print_table_header"><?=text::get('STATUS');?></td>
            <td width="5%" class="print_table_header"><?=text::get('DATE');?></td>
            <td width="10%" class="print_table_header"><?=text::get('SINGLE_VOLTAGE');?><br /></td>
            <td width="10%" class="print_table_header"><?= text::get('SINGLE_OBJECT'); ?></td>
			<td width="10%" class="print_table_header"><?= text::get('MAIN_DESIGNATION'); ?></td>

            <td width="10%" class="print_table_header"><?= text::get('ACT_TOTAL_WORK_PRICE').', EUR'; ?></td>
            <td width="10%" class="print_table_header"><?=text::get('ST_TOTAL_MATER_PRICE').', EUR';?></td>
            <td width="10%" class="print_table_header"><?=text::get('ACT_TOTAL_MATER_PRICE').', EUR';?></td>
 		</tr>

<?
	if (is_array($res) && count($res) > 0)
	{
		foreach ($res as $row)
		{
?>
			<tr >


                <td align="center" class="print_table_data">&nbsp;<?= $row['WORKER']; ?></td>
			   	<td align="center" class="print_table_data">&nbsp;<?= $row['NUMURS']; ?></td>
                <td align="left" class="print_table_data">&nbsp;<?= $row['TYPE']; ?></td>
                <td align="left" class="print_table_data">&nbsp;<?= $row['STATUS_NAME']; ?></td>
                <td align="left" class="print_table_data">&nbsp;<?= $row['AAUD_DATUMS']; ?></td>
                <td align="left" class="print_table_data">&nbsp;<?= $row['KSRG_NOSAUKUMS']; ?></td>
                <td align="left" class="print_table_data">&nbsp;<?= $row['KOBJ_NOSAUKUMS']; ?></td>
                <td align="left" class="print_table_data">&nbsp;<?= $row['RAKT_OPERATIVAS_APZIM']; ?></td>

                <td align="center" class="print_table_data">&nbsp;<?= $row['WORK_TOTAL']; ?></td>
                <td align="center" class="print_table_data">&nbsp;<?= $row['ST_MATER_TOTAL']; ?></td>
                <td align="center" class="print_table_data">&nbsp;<?= $row['DU_MATER_TOTAL']; ?></td>
			</tr>
<?
		}
?>
        <tr>
             <td align="right" class="print_table_total" colspan="8"><?=text::get('TOTAL');?>:</td>
             <td align="center" class="print_table_total"><?= $work; ?></td>
             <td align="center" class="print_table_total"><?= $st_material; ?></td>
             <td align="center" class="print_table_total"><?= $du_material; ?></td>
        </tr>
<?
	}
?>

</table>

</body>