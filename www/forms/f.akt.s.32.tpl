<h1><?=text::toUpper(text::get('RBF_ATTACHMENTS'));?></h1>
<table cellpadding="5" cellspacing="1" border="0" width="100%">

	<?
	if (isset($fileInfo) && is_array($fileInfo) && count($fileInfo) > 0)
	{
		for($i=0; $i<count($fileInfo); $i++)
		{
		?>
			<tr>
				<td class="table_cell" width="5%"><img src="img/ico_pdf.gif" alt="" width="16" height="16">&nbsp;</td>
				<td class="table_cell_2" width="35%"><a href="<?=$fileInfo[$i]['getFileURL'];?>" ><?=$fileInfo[$i]['RFLS_NOSAUKUMS'];?></a></td>
                <td class="table_cell" width="10%"><?=text::get('DATE');?>:</td>
				<td class="table_cell_2" width="20%"><?=$fileInfo[$i]['RFLS_DATUMS'];?></td>
				<td class="table_cell" width="10%"><?=text::get('EXPORT_ACT_AUTHOR');?>:</td>
				<td class="table_cell_2" width="20%"><?=$fileInfo[$i]['AUTORS'];?></td>
			</tr>
		<?
		}
	}
	else
	{
	?>
		<tr>
			<td class="table_cell_2" colspan="6" style="text-align: center; padding: 20px; color: #666;">
				<?=text::get('NO_FILES');?>
			</td>
		</tr>
	<?
	}
	?>
</table>

