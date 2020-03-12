<script type="text/javascript">
    function doSearch()
	{
    	eval(xmlHttpGetValue('<?= $searchLink; ?>&xml=1&search_q=' + urlencode(document.all['Search'].value) + '&search_c=' + document.all['Columns'].value));
	    reloadFrame(1, '<?= $searchLink; ?>&search=' + q + '&column=' + c);
    }
    function doSort(column, order)
	{
    	eval(xmlHttpGetValue('<?= $searchLink; ?>&xml=1&sort_k=' + column + '&sort_o=' + order));
	    reloadFrame(1, '<?= $searchLink; ?>&order=' + o + '&kol=' + k);
    }
    function setRowStyle(row)
    {
      var rowName =  'recordRow' + row;
      var row = document.getElementById(rowName);
      row.style.color = '#999999';
    }
</script>
<body class="frame_1">
<h1><?= $title; ?></h1>
<table cellpadding="0" cellspacing="0" border="0" width="100%">
	<tr>
		<td>
            <table cellpadding="0" cellspacing="0" border="0" >
				<tr>
                    <td nowrap ><input type="text" id="Search" maxlength="11" value="<?= (isset($_GET['search']) ? $_GET['search']: ''); ?>">&nbsp;</td>
                    <td nowrap >
                        <select id="Columns">
                        <?
	                    if (is_array($columns))
	                    {
		                     foreach ($columns as $col)
		                     {
                              ?>
                              <option value="<?= $col['kolonna']; ?>"  <?= ( (isset($_GET['column']) && $_GET['column'] == $col['kolonna'])? "selected" : (!isset($_GET['column']) && $col['def']==1)? "selected" : "");?> ><?= $col['nosaukums']; ?></option>
                              <?
                             }
                        }
                        ?>
                        </select>&nbsp;
                    </td>
					<td nowrap ><a href="#" onclick="doSearch()">
						<img src="img/btn_meklet.gif" alt="<?= text::get('SEARCH'); ?>" width="70" height="20" border="0" class="block">
					</a></td>
                </tr>
			</table>
        </td>
		<td align="right"><?=$listingHtml;?></td>
	</tr>
</table>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr class="table_head_2">
		<td><?=text::get('CURRENT_NUMBER');?></td>
         <?
	     if (is_array($columns))
	     {
		    foreach ($columns as $col)
            {
            ?>
                <td class="block"><?=$col['nosaukums'];?>
                <a href="#" onclick="doSort('<?= $col['kolonna'];?>', 'ASC')">
						<img src="img/sort_asc.gif" alt="A-Z" width="11" height="6" border="0"></a>
                <a href="#" onclick="doSort('<?= $col['kolonna'];?>', 'DESC')">
						<img src="img/sort_desc.gif" alt="Z-A" width="11" height="6" border="0"></a>
                </td>
            <?
            }
         }
        ?>
 	</tr>
	<?
	if (is_array($res))
	{
        $i = 0;
		foreach ($res as $row)
		{
		?>
			<tr id="recordRow<?=$i;?>" class="table_cell_3" >
				<td><?=$number;?></td>
                <?
                if (is_array($columns))
	            {
		            foreach ($columns as $col)
		            {
		              if((substr($col['kolonna'], -9) == 'IR_AKTIVS') || substr($col['kolonna'], -9) == 'IR_ADMINS' || substr($col['kolonna'], -8) == 'IR_PLANS')
                      {
                        if((substr($col['kolonna'], -9) == 'IR_AKTIVS') && ($row[$col['kolonna']] == 0))
                        {
                          ?>
                             <script>setRowStyle(<?=$i;?>);</script>
                          <?
                        }
                        ?>
                           <td>
                            <?=($row[$col['kolonna']])?text::get('YES'):text::get('NO');?>
                           </td>
                        <?
                      }
                      else
                      {
                        ?>
				        <td><?=$row[$col['kolonna']];?></td>
                        <?
                       }
                    }
                }
                ?>

			</tr>
		<?
            $i ++;
			$number++;
		}
	}
	?>

</table>

<table cellpadding="0" cellspacing="0" border="0" width="100%">
	<tr>
		<td align="right"><?=$listingHtml;?></td>
	</tr>
</table>

</body>
