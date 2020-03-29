<body class="print">

<table cellpadding="0" cellspacing="0" class="print_table_portrait" >
  <tr>
    <td  colspan="2" align="right"><h4><?= text::toUpper(text::get('PROJECT')); ?></h4></td>
  </tr>
  <tr>
    <td  colspan="2" class="print_header_centered" align="center"><?= text::get('TRASE_ACT_HEADER1'); ?></td>
  </tr>
  <tr>
     <td colspan="2">&nbsp;</td>
  </tr>
  <tr>
    <td><?= dtime::dateToLvStringEmpty(date('d.m.Y')); ?></td>
    <td align="right"><b><?=text::get('NUMBER_SIMBOL').'. '.$act['NUMURS']; ?></b></td>
  </tr>
  <tr>
     <td colspan="2">&nbsp;</td>
  </tr>
  <tr>
     <td colspan="2"><?= text::get('TRASE_ACT_HEADER5'); ?></td>
  </tr>
  <tr>
     <td colspan="2">&nbsp;</td>
  </tr>
  <tr>
    <td><?= text::get('REPORT_WORK_OFFER').':'; ?></td>
    <td><?= text::get('REPORT_WORK_DONE'); ?></td>
  </tr>
  <tr>
    <td><b><?= text::get('ST_COMPANY_NAME').', '.text::get('REGISTRATION_SIMBOL').'. '.text::get('NUMBER_SIMBOL').': '.text::get('ST_REG_NR'); ?></b></td>
    <td><b><?= $act['WORKER'].', '.text::get('REGISTRATION_SIMBOL').'. '.text::get('NUMBER_SIMBOL').': '.$act['KWOI_KODS']; ?></b></td>
  </tr>
  <tr>
    <td><?= text::get('ED_IECIKNIS').':'; ?></td>
    <td><?= text::get('WORK_DONE_AGREEMENT_NO').': '.$act['RAKT_VV_NUMBER']; ?></td>
  </tr>

  <tr>
    <td><b><?= $regionName .' '. text::get('REPORT_DEPARTMENT'); ?></b></td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td><b><?= $act['KEDI_SECTION']; ?></b></td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td><?= text::get('WORKS_AND_TERITORY'); ?></td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td><b><?= $regionName .' '. text::get('REPORT_REGION'); ?></b></td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td><b><?= $act['KEDI_NOSAUKUMS']; ?></b></td>
    <td>&nbsp;</td>
  </tr>
  <tr>
     <td colspan="2">&nbsp;</td>
  </tr>
  <tr>
     <td colspan="2"><?= $act['WORK_TITLE']; ?></td>
  </tr>
  <tr>
     <td colspan="2">&nbsp;</td>
  </tr>
</table>
<table cellpadding="0" cellspacing="0" class="print_table_portrait">

    <tr>
        <td width="15%" ><b><i><?= text::get('SINGLE_ACT_TYPE').': '; ?></i></b></td>
        <td width="35%" ><?= ' '.$act['TYPE']; ?></td>
        <td width="15%" ><b><i><?= text::get('SINGLE_OBJECT').': '; ?></i></b></td>
        <td width="35%" ><?= ' '.$act['OBJECT']; ?></td>

    </tr>
    <tr>
        <td ><b><i><?= text::get('SINGLE_VOLTAGE').': '; ?></i></b></td>
        <td><?= ' '.$act['SPRIEGUMS']; ?></td>
        <td><b><i><?= text::get('EXPORT_MAIN_DESIGNATION').': '; ?></i></b></td>
        <td ><?= ' '.$act['RAKT_OPERATIVAS_APZIM']; ?></td>
    </tr>


    <tr>
        <td><b><i><?= text::get('COMMENT').': '; ?></i></b></td>
        <td colspan="3"><?= ' '.$act['RAKT_PIEZIMES']; ?></td>

    </tr>
</table>
<br />
<div class="print_header"><?= text::get('TAB_WORKS'); ?></div>
<table cellpadding="0" cellspacing="0" class="print_table_portrait" >

		<tr>
            <td width="12%" class="print_table_header"><?= text::get('CHIPHER'); ?></td>
			<td width="50%" class="print_table_header"><?= text::get('EXPORT_CALCULATION_NAME'); ?></td>
            <td width="12%" class="print_table_header"><?=text::get('UNIT_OF_MEASURE');?></td>
            <td width="12%" class="print_table_header"><?=text::get('PRICE');?></td>
            <td width="12%" class="print_table_header"><?=text::get('AMOUNT');?></td>
            <td width="12%" class="print_table_header"><?= text::get('PRICE_TOTAL'); ?></td>
 		</tr>

<?
	if (is_array($aWorkDb) && count($aWorkDb) > 0)
	{
		foreach ($aWorkDb as $i => $work)
		{
?>
			<tr >
                <td align="center" class="print_table_data">&nbsp;<?= $work['DRBI_KKAL_SHIFRS']; ?></td>
                <td align="left" class="print_table_data">&nbsp;<?= $work['DRBI_KKAL_NOSAUKUMS']; ?></td>
                <td align="center" class="print_table_data">&nbsp;<?= $work['DRBI_MERVIENIBA']; ?></td>
                <td align="center" class="print_table_data">&nbsp;<?= $work['DRBI_KKAL_NORMATIVS']; ?></td>
                <td align="center" class="print_table_data">&nbsp;<?= $work['DRBI_DAUDZUMS']; ?></td>
                <td align="center" class="print_table_data">&nbsp;<?= $work['DRBI_CILVEKSTUNDAS']; ?></td>
			</tr>
<?
		}
    }
?>
        <tr>
             <td align="right" class="print_table_total" colspan="5"><?=text::get('TOTAL');?>:</td>
             <td align="center" class="print_table_total"><?= number_format($workTotal,2,'.',''); ?></td>
        </tr>
        <tr>
             <td align="right" class="print_table_total" colspan="5"><?=text::get('PCT').' '. $pvn . '%';?>:</td>
             <td align="center" class="print_table_total"><?= number_format($pct,2,'.',''); ?></td>
        </tr>
        <tr>
             <td align="right" class="print_table_total" colspan="5"><?=text::get('TOTAL_WITH_PCT');?>:</td>
             <td align="center" class="print_table_total"><?= number_format($summa,2,'.',''); ?></td>
        </tr>

</table>

<br />

<table cellpadding="0" cellspacing="0" class="print_table_portrait" >
  <tr>
    <td width="30%"><?= text::get('ACT_CREATER').': '.$act['AUTORS']; ?></td>
    <td width="30%"></td>
    <td width="30%"></td>
  </tr>
  <tr>
    <td width="30%"><?= text::get('DATE').': '.date('d.m.Y'); ?></td>
    <td width="30%"></td>
    <td width="30%"><?= text::get('IS_NOT_ENDORSED'); ?></td>
  </tr>
   <tr>
    <td width="30%">&nbsp;</td>
    <td width="30%">&nbsp;</td>
    <td width="30%">&nbsp;</td>
  </tr>
  <tr>
    <td width="30%"><?= text::get('REPORT_WORKER_FINISHED').':'; ?></td>
    <td width="30%"></td>
    <td width="30%"></td>
  </tr>
  <tr>
    <td width="30%"><?= $act['WORKER']; ?></td>
    <td width="30%"></td>
    <td width="30%" ></td>
  </tr>
  <tr>
    <td width="30%"><?= $act['AUTORS']; ?></td>
    <td width="30%"></td>
    <td width="30%" class="print_table_data"></td>
  </tr>
   <tr>
    <td width="30%">&nbsp;</td>
    <td width="30%"></td>
    <td width="30%" >&nbsp;</td>
  </tr>
  <tr>
    <td width="30%">&nbsp;</td>
    <td width="30%">&nbsp;</td>
    <td width="30%" ></td>
  </tr>
  <tr>
    <td width="30%">&nbsp;</td>
    <td width="30%">&nbsp;</td>
    <td width="30%"></td>
  </tr>
   <tr>
    <td width="30%">&nbsp;</td>
    <td width="30%"></td>
    <td width="30%">&nbsp;</td>
  </tr>
  <tr>
    <? if($act['RAKT_SIGNATURE'] == 'E') { ?>
    <td  colspan="3" style="text-align: center;"><?= text::get('ELRCTRONIC_SIGNATURE'); ?></td>
    <? } ?>
  </tr>
</table>
</body>