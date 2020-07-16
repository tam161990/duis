<h1><?=text::toUpper(text::get(TAB_EXPORT));?></h1>
<table cellpadding="5" cellspacing="1" border="0" width="100%">

	<?
	if ($isProject && isset($excelInfo) && is_array($excelInfo))
	{
		for($i=0; $i<count($excelInfo); $i++)
		{
		?>
			<tr>
				<td class="table_cell" width="14%"><img src="img/ico_excel.gif" alt="" width="16" height="16">&nbsp;</td>
				<td class="table_cell_2" width="30%"><a href="<?=$excelInfo[$i]['getFileURL'];?>" ><?=$excelInfo[$i]['EFLS_NOSAUKUMS'];?></a></td>
                <td class="table_cell" width="14%"><?=text::get('DATE');?>:</td>
				<td class="table_cell_2" width="14%"><?=$excelInfo[$i]['EFLS_DATUMS'];?></td>
				<td class="table_cell" width="14%"><?=text::get('EXPORT_ACT_APOVE');?>:</td>
				<td class="table_cell_2" width="14%"><?=$excelInfo[$i]['AUTORS'];?></td>

			</tr>

		<?
         break;
		}
	}
	if (isset($fileInfo) && is_array($fileInfo))
	{
		for($i=0; $i<count($fileInfo); $i++)
		{
		?>
			<tr>
				<td class="table_cell" width="14%"><img src="img/ico_pdf.gif" alt="" width="16" height="16">&nbsp;</td>
				<td class="table_cell_2" width="30%"><a href="<?=$fileInfo[$i]['getFileURL'];?>" ><?=$fileInfo[$i]['RFLS_NOSAUKUMS'];?></a></td>
                <td class="table_cell" width="14%"><?=text::get('DATE');?>:</td>
				<td class="table_cell_2" width="14%"><?=$fileInfo[$i]['RFLS_DATUMS'];?></td>
				<td class="table_cell" width="14%"><?=text::get('EXPORT_ACT_APOVE');?>:</td>
				<td class="table_cell_2" width="14%"><?=$fileInfo[$i]['AUTORS'];?></td>

			</tr>

		<?
        if($isEditor && $isProject == 0) break;
		}
	}
	?>
</table>


