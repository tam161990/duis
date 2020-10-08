<body class="frame_1">
    <script type="text/javascript">

        function setAct(act, op)
        {            
            eval(xmlHttpGetValue('<?= $searchLink; ?>&xml=1&act=' + act + '&op=' + op));
        }
    
        function imports()
        {
            eval(xmlHttpGetValue('<?= $searchLink; ?>&xml=1&import=1&act=<?= $actId; ?>'));
            
        }
    </script>
<?= $oFormPop -> getFormHeader(); ?>
<h1><?=$title;?></h1>
<div align=center><?= $oFormPop -> getMessage(); ?></div>

<table cellpadding="5" cellspacing="1" border="0" width="100%" >
	<thead>
		<tr class="table_head_2">			
			<td align="left"><?= text::get('SINGL_WORK_OWNER'); ?></td>
            <td align="left"><?= text::get('ACT_NUM_POSTFIX'); ?></td>
            <td align="left"><?= text::get('WORK_TITLE'); ?></td>
            <td width="5%">&nbsp;</td>
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
				<td align="left"><?= $row['KWOI_NOSAUKUMS']; ?></td>
                <td align="left"><?= $row['RAKT_NUM_POSTFIX']; ?></td>
                <td align="left"><?= $row['RAKT_WORK_TITLE']; ?></td>
                <td align="center"><input type="checkbox" onclick="setAct('<?=$row['RAKT_ID'];?>', (this.checked)?'<?=OP_INSERT;?>':'<?=OP_DELETE;?>')"  /></td>
                
			</tr>
<?
            $i ++;
		}
        ?>
          <tr>
              <td>&nbsp;</td>
              <td align="right">
                  <input type="image" src="img/btn_saglabat.gif" alt="<?= text::get('SAVE'); ?>" width="70" height="20" onClick="imports(); window.opener.location.replace( '<?= $redirectUrl; ?>' ); window.close();" name="save" border=0/>
              </td>
              <td align="left">
                  <input type="button" class="btn70" value="<?= text::get('CLOSE'); ?>" alt="<?= text::get('CLOSE'); ?>" onClick="javascript:window.close();return false;" name="close" border=0/>
            </td>
            <td>&nbsp;</td>
          </tr>
        <?
	}
?>
	</tbody>
</table>


<?= $oFormPop->getFormBottom(); ?>
</body>