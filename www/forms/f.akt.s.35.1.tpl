<script type="text/javascript">
    function setRowStyle(row)
    {
      var rowName =  'recordRow' + row;
      var row = document.getElementById(rowName);
      row.style.color = '#999999';
    }
</script>
<body class="frame_2">
<table cellpadding="0" cellspacing="0" border="0" width="100%">
	<tr>
		<td><h1><?= text::toUpper(text::get('LIST_OF_ACTS')); ?></h1></td>
		<td align="right"><?= $listingHtml; ?></td>
	</tr>
</table>

<table cellpadding="5" cellspacing="1" border="0" width="100%" >
	<thead>
		<tr class="table_head_2">
			<td width="5%"><?= text::get('CURRENT_NUMBER'); ?></td>
			<td align="left"><?= text::get('ACT_NUMBER'); ?></td>
            <td align="left"><?= text::get('SINGLE_ACT_TYPE'); ?></td>
            <td align="left"><?= text::get('STATUS'); ?></td>
            <td align="left"><?= text::get('PRINT_WORK_TITLE'); ?></td>
            <td align="left">RBF Nodaļa/RBF Daļa</td>
            <td align="left"><?= text::get('SINGL_WORK_OWNER'); ?></td>
            <td align="left"><?= text::get('USER'); ?></td>
		</tr>
	</thead>
	<tbody>
<?
	if (is_array($res))
	{
        $i = 0;
        foreach ($res as $row)
		{
?>
			<tr id="recordRow<?=$i;?>" class="<?=(($row['selected'] == 1) ? 'table_cell_4': 'table_cell_3')?>"
                onMouseOver="this.className='table_cell_4'"
                onMouseOut="this.className='table_cell_3'"
                onClick="parent['frameTop'].disableFrameControl();window.top.min(1);reloadFrame(1,'<?= $row['URL']; ?>');reloadFrame(23,'');">
                <?
                if(substr($row['RAKT_STATUS'], -6) == STAT_DELETE)
                {
                ?>
                    <script>setRowStyle(<?=$i;?>);</script>
                <?
                }
                ?>
                <td><?= $number++; ?></td>
				<td align="left"><?= $row['NUMURS']; ?></td>
                <td align="left"><?= $row['TYPE']; ?></td>
                <td align="left"><?= $row['STATUS_NAME']; ?></td>
                <td align="left"><?= $row['RAKT_WORK_TITLE']; ?></td>
                <td align="left"><?= $row['ED']; ?></td>
                <td align="left"><?= $row['WORKER']; ?></td>
                <td align="left"><?= $row['AUTORS']; ?></td>
			</tr>
<?
            $i ++;
		}
	}
?>
	</tbody>
</table>

<table cellpadding="0" cellspacing="0" border="0" width="100%">
	<tr>
		<td align=right><?= $listingHtml; ?></td>
	</tr>
</table>

</body>
