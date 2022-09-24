<body class="frame_1">
  
  <table cellpadding="0" cellspacing="0" border="0" width="100%">
	<tr>
		<h1><?= $title; ?></h1>
		<td align="right"><a href="javascript:parent.close();">
		<img src="img/ico_end.gif" alt="<?= text::get('CLOSE'); ?>" border="0">
		</a></td>
	  </tr>
  <tr>
	<td colspan="2" align="right"><?=$listingHtml;?></td>
  </tr>
  </table>
  <table cellpadding="5" cellspacing="1" border="0" width="100%">
  <tr class="table_head_2">
	<th><?=text::get('CURRENT_NUMBER');?></th>	
	<th><?=text::get('KWOI_VV_NUMBER');?></th>
	<th><?=text::get('SIGNATORY');?></th>
	<th><?=text::get('SINGL_ED_AREA') ;?> </th>
	<th><?=text::get('TRASE');?></th>
	<th><?=text::get('IS_ACTIVE');?></th>	 
   </tr>
  <?
  if (is_array($res))
  {
	$i = 0;
	 
	foreach ($res as $row)
	{
	?>
	  <tr id="recordRow<?=$i;?>" class="table_cell_3"  onClick="makeActiveRow(this, '<?=$row['URL'];?>');">
	  <td><?=$number;?></td>
	  <td><?=$row['KCNT_VV_NUMBER'];?></td>	 
	  <td><?=$row['KCNT_SIGNATORY'];?></td> 
	  <td><?=$row['KONT_KEDI_KODS'];?></td> 
	  <td><?=$row['KCNT_IR_TRASE'];?></td>
	  <td><?=$row['KCNT_IR_AKTIVS'];?></td>
	  </tr>
	<?
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
  