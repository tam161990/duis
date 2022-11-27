<h1><?=text::toUpper(text::get(TAB_ESTIMATE));?></h1>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<?
		
	if (isset($fileInfo) && is_array($fileInfo))
	{
		for($i=0; $i<count($fileInfo); $i++)
		{
		?>
			<tr>
				<td class="table_cell" width="5%"><img src="img/<?=$fileInfo[$i]['ico'];?>" alt="" width="16" height="16">&nbsp;</td>
				<td class="table_cell_2" width="20%"><a href="<?=$fileInfo[$i]['getFileURL'];?>" ><?=$fileInfo[$i]['RFLS_NOSAUKUMS'];?></a></td>
                <td class="table_cell" ><?=text::get('DATE');?>:</td>
				<td class="table_cell_2" ><?=$fileInfo[$i]['RFLS_DATUMS'];?></td>
				<td class="table_cell" ><?=text::get('EXPORT_ACT_APOVE');?>:</td>
				<td class="table_cell_2" ><?=$fileInfo[$i]['AUTORS'];?></td>
				<? if($isProject == 1) { ?>
					<? if(isset($fileInfo[$i]['STATUS'])) { ?>
						<td class="table_cell" ><?=text::get('STATUS');?>:</td>
					<? } else {  ?>
						<td class="table_cell" >&nbsp;</td>
					<? } ?>
					<td class="table_cell_2" ><?=$fileInfo[$i]['STATUS'];?></td>
					<? if(isset($fileInfo[$i]['project_no'])) { ?>
						<td class="table_cell" ><?=text::get('PROJECT_NO');?>:</td>
					<? } else {  ?>
						<td class="table_cell" >&nbsp;</td>
					<? } ?>
				    <td class="table_cell_2" ><?=$fileInfo[$i]['project_no'];?></td>
				<? } ?>
			</tr>

		<?
        if($isEditor && $isProject == 0) break;
		}
	}
	?>
</table>


