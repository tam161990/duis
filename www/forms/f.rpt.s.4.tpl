<script type="text/javascript">
    function doSort(column, order)
	{
    	eval(xmlHttpGetValue('<?= $searchLink; ?>&xml=1&sort_k=' + column + '&sort_o=' + order));
	    reloadFrame(2, '<?= $searchLink; ?>&order=' + o + '&kol=' + k);
    }
</script>

<body class="frame_2">

<table cellpadding="0" cellspacing="0" border="0" width="100%">
	<tr>
		<td><h1><?= text::toUpper(text::get('REPORT_MAIN_ACT').(($trase == 1) ? ' ('.text::get('TRASE').')' : '' )); ?></h1></td>
		<td align="right">
            <img src="img/ico_print.gif" alt="" width="16" height="16" border="0">&nbsp;
            <a href="<?= $printUrl; ?>" target="new"><?=text::get('PRINT');?></a>&nbsp;&nbsp;
            <img src="img/ico_excel.gif" alt="" width="16" height="16">&nbsp;
            <a href="<?= $exportUrl; ?>" ><?=text::get('EXPORT_TO_EXCEL');?></a>&nbsp;
        </td>
	</tr>
</table>

<table cellpadding="5" cellspacing="1" border="0" width="100%" >
	<thead>
		<tr class="table_head_2">
            <td width="17%"><?= text::get('SINGL_WORK_OWNER'); ?></td>
			<td width="8%"><?= text::get('ACT_NUMBER'); ?></td>
			<td width="5%"><?= text::get('SINGLE_ACT_TYPE'); ?></td>
            <td width="5%"><?=text::get('STATUS');?></td>
            <td width="5%"><?=text::get('DATE');?></td>
            <td width="10%">
                <?=text::get('SINGLE_VOLTAGE');?><br />
                <a href="#" onclick="doSort('<?= COLUMN_VOLTAGE;?>', 'ASC')">
						<img src="img/sort_asc.gif" alt="A-Z" width="11" height="6" border="0"></a>
                <a href="#" onclick="doSort('<?= COLUMN_VOLTAGE;?>', 'DESC')">
						<img src="img/sort_desc.gif" alt="Z-A" width="11" height="6" border="0"></a>
            </td>

            <td width="10%"><?= text::get('SINGLE_OBJECT'); ?></td>
			<td width="10%"><?= text::get('MAIN_DESIGNATION'); ?></td>

            <td width="10%"><?= text::get('ACT_TOTAL_WORK_PRICE').', EUR'; ?></td>
            <td width="10%"><?=text::get('ST_TOTAL_MATER_PRICE').', EUR';?></td>
            <td width="10%"><?=text::get('ACT_TOTAL_MATER_PRICE').', EUR';?></td>
 		</tr>
	</thead>
	<tbody>
<?
	if (is_array($res) && count($res) > 0)
	{
		foreach ($res as $row)
		{
?>
			<tr class="table_cell_3" >
                <td align="center"><?= $row['WORKER']; ?></td>
			   	<td align="center"><?= $row['NUMURS']; ?></td>
                <td align="left"><?= $row['TYPE']; ?></td>
                <td align="left"><?= $row['STATUS_NAME']; ?></td>
                <td align="left"><?= $row['AAUD_DATUMS']; ?></td>
                <td align="left"><?= $row['KSRG_NOSAUKUMS']; ?></td>

                <td align="left"><?= $row['KOBJ_NOSAUKUMS']; ?></td>
                <td align="left"><?= $row['RAKT_OPERATIVAS_APZIM']; ?></td>

                <td align="center"><?= $row['WORK_TOTAL']; ?></td>
                <td align="center"><?= $row['ST_MATER_TOTAL']; ?></td>
                <td align="center"><?= $row['DU_MATER_TOTAL']; ?></td>
			</tr>
<?
		}
?>
        <tr>
             <td align="right" colspan="8"><b><?=text::get('TOTAL');?>:</b></td>
             <td align="center"><b><?= $work; ?></b></td>
             <td align="center"><b><?= $st_material; ?></b></td>
             <td align="center"><b><?= $du_material; ?></b></td>
        </tr>
<?
	}
?>
	</tbody>
</table>

</body>