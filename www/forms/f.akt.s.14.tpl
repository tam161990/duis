<script type="text/javascript">

    function setAct(act, op)
	{
        eval(xmlHttpGetValue('<?= $searchLink; ?>&xml=1&act=' + act + '&op=' + op));
    }

    function writeOff()
    {
      reloadFrame(2, '<?= $searchResultLink; ?>&xml=1&writeoff=1');
    }
</script>

<body class="frame_2">
<table cellpadding="0" cellspacing="0" border="0" width="100%">
	<tr>
		<td><h1><?= text::toUpper(text::get('LIST_OF_ACTS')); ?></h1></td>
		<td align="right">&nbsp;</td>
	</tr>
</table>

<table cellpadding="5" cellspacing="1" border="0" width="100%" >
	<thead>
		<tr class="table_head_2">
			<td width="5%">&nbsp;</td>
			<td align="left"><?= text::get('ACT_NUMBER'); ?></td>
            <td align="left"><?= text::get('MONTH'); ?></td>
            <td align="left"><?= text::get('YEAR'); ?></td>
            <td align="left"><?= text::get('STATUS'); ?></td>
            <td align="left"><?= text::get('SINGLE_ACT_TYPE'); ?></td>
            <td align="left"><?= text::get('ED_SECTION'); ?></td>
            <td align="left"><?= text::get('SINGL_WORK_OWNER'); ?></td>
            <td align="left"><?= text::get('MAIN_DESIGNATION'); ?></td>
            <td align="left"><?= text::get('WRITE_OFF_ACCOUNT'); ?></td>
		</tr>
	</thead>
	<tbody>
<?
	if (is_array($res) && count($res) > 0)
	{
        $i = 0;
        foreach ($res as $row)
		{
?>
			<tr id="recordRow<?=$i;?>" class="<?=(($row['selected'] == 1) ? 'table_cell_4': 'table_cell_3')?>"
                onMouseOver="this.className='table_cell_4'"
                onMouseOut="this.className='table_cell_3'"               >

                <td><input type="checkbox" onclick="setAct('<?=$row['RAKT_ID'];?>', (this.checked)?'<?=OP_INSERT;?>':'<?=OP_DELETE;?>')"  /></td>
				<td align="left"><?= $row['NUMURS']; ?></td>
                <td align="left"><?= dtime::getMonthName($row['RAKT_MENESIS']); ?></td>
                <td align="left"><?= $row['RAKT_GADS']; ?></td>
                <td align="left"><?= $row['STATUS_NAME']; ?></td>
                <td align="left"><?= $row['TYPE']; ?></td>
                <td align="left"><?= $row['ED']; ?></td>
                <td align="left"><?= $row['WORKER']; ?></td>
                <td align="left"><?= $row['RAKT_OPERATIVAS_APZIM']; ?></td>
                <td align="left"><?= $row['WRITE_OFF_ACCOUNT']; ?></td>
			</tr>
<?
            $i ++;
		}
        ?>
          <tr>
              <td colspan="10">
                  <input type="image" src="img/btn_view.gif" alt="<?= text::get('VIEW_ACT'); ?>" width="70" height="20" onClick="window.open('<?= $oPopLink ->getQuery(); ?>', 'frmMain',''); return true;" name="wiew" border=0/>  &nbsp;
              <input type="image" src="img/btn_writeoff.gif" alt="<?= text::get('VIEW_ACT'); ?>" width="70" height="20" onClick="writeOff(); return true;" name="wiew" border=0/>
              </td>
          </tr>
        <?
	}
?>
	</tbody>
</table>


</body>