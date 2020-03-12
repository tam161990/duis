<body class="print">
<div class="print_header">
<?= text::get('WRITE_OFF_ACT'); ?><br />
</div>
<table cellpadding="0" cellspacing="0" class="print_table_portrait" >
<?
	if (is_array($acts) && count($acts) > 0)
	{
	    $i = 0;
		foreach ($acts as $act => $code)
		{
		  if( $i == 0)
          {
?>
    <tr>
        <td width="15%" ><b><i><?= text::get('ACT_NUMBER').': '; ?></i></b></td>
        <td width="35%" ><?= ''.$code['NUMURS']; ?></td>
        <td width="15%" ><b><i><?= text::get('WRITE_OFF_ACCOUNT').': '; ?></i></b></td>
        <td width="35%" ><?= ''.$code['WRITE_OFF_ACCOUNT']; ?></td>
    </tr>
<?
            }
            else
            {
?>
               <tr>
                  <td width="15%" >&nbsp;</td>
                  <td width="35%" ><?= ''.$code['NUMURS']; ?></td>
                  <td width="15%" >&nbsp;</td>
                  <td width="35%" ><?= ''.$code['WRITE_OFF_ACCOUNT']; ?></td>
              </tr>
<?
            }
            $i ++;
        }
    }
?>
</table>

<br />
<div class="print_header"><?= text::get(TAB_MATERIAL); ?></div>
<table cellpadding="0" cellspacing="0" class="print_table_portrait" >

		<tr>
            <td width="12%" class="print_table_header"><?= text::get('CODE'); ?></td>
			<td width="40%" class="print_table_header"><?= text::get('NAME'); ?></td>
            <td width="12%" class="print_table_header"><?=text::get('UNIT_OF_MEASURE');?></td>
            <td width="12%" class="print_table_header"><?=text::get('PRICE');?></td>
            <td width="12%" class="print_table_header"><?=text::get('AMOUNT');?></td>
            <td width="12%" class="print_table_header"><?= text::get('PRICE_TOTAL'); ?></td>
 		</tr>

<?
	if (is_array($aMaterialDb) && count($aMaterialDb) > 0)
	{
		foreach ($aMaterialDb as $i => $material)
		{
?>
			<tr >
                <td align="center" class="print_table_data">&nbsp;<?= $material['MATR_KODS']; ?></td>
                <td align="left" class="print_table_data">&nbsp;<?= $material['MATR_NOSAUKUMS']; ?></td>
                <td align="center" class="print_table_data">&nbsp;<?= $material['MATR_MERVIENIBA']; ?></td>
                <td align="center" class="print_table_data">&nbsp;<?= $material['MATR_CENA']; ?></td>
                <td align="center" class="print_table_data">&nbsp;<?= $material['MATR_DAUDZUMS']; ?></td>
                <td align="center" class="print_table_data">&nbsp;<?= $material['MATR_CENA_KOPA']; ?></td>
			</tr>
<?
		}
?>
     <tr>
             <td align="right" class="print_table_total" colspan="5"><?=text::get('TOTAL');?>:</td>
             <td align="center" class="print_table_total"><?= number_format($Totalsumma,2); ?></td>
        </tr>
<?
	}
?>
</table>
<br />

<table cellpadding="0" cellspacing="0" class="print_table_portrait" >

    <tr>
        <td><b><i><?= text::get('DATE').': '.date('d.m.Y H:i:s'); ?></i></b></td>
    </tr>

</table>
</body>