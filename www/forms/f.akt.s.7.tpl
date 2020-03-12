<h1><?=text::toUpper(text::get(TAB_AUDIT));?></h1>
<table cellpadding="5" cellspacing="1" border="0" width="100%">

	<?
	if (isset($auditInfo) && is_array($auditInfo))
	{
		for($i=0; $i<count($auditInfo); $i++)
		{
		?>
			<tr>
				<td class="table_cell" width="14%"><?=text::get('STATUS');?>:</td>
				<td class="table_cell_2" width="30%"><?=$auditInfo[$i]['STATUS'];?></td>
                <td class="table_cell" width="14%"><?=text::get('DATE');?>:</td>
				<td class="table_cell_2" width="14%"><?=$auditInfo[$i]['AAUD_DATUMS'];?></td>
				<td class="table_cell" width="14%"><?=text::get('USER');?>:</td>
				<td class="table_cell_2" width="14%"><?=$auditInfo[$i]['AUTORS'];?></td>

			</tr>

		<?
		}
	}
	?>
</table>


