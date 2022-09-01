<script type="text/javascript">
  function doSearch()
  {
    eval(xmlHttpGetValue('<?= $searchLink; ?>&xml=1&search_q=' + urlencode(document.all['Search'].value) + '&search_c=' + document.all['Columns'].value));
    reloadFrame(1, '<?= $searchLink; ?>&search=' + q + '&column=' + c);
  }
  function doSearchOnlyText()
  {
    eval(xmlHttpGetValue('<?= $searchLink; ?>&xml=1&search_q=' + urlencode(document.all['Search'].value) ));
    reloadFrame(1, '<?= $searchLink; ?>&search=' + q );
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
                 <? if(isset($searchTitle)) { ?>
                  <td nowrap ><?= $searchTitle; ?></td>
                  <? } ?>
                  <td nowrap ><input type="text" id="Search" maxlength="50" value="<?=isset($_GET['search'])?$_GET['search']:''; ?>">&nbsp;</td>
                  <td nowrap >                       
                  <?
                    if (!isset($searchTitle))
                    {
                      ?>
                      <select id="Columns">
                      <?
                       foreach ($columns as $col)
                       {
                            ?>
                            <option value="<?= $col['kolonna']; ?>"  <?= ( (isset($_GET['column']) && $_GET['column'] == $col['kolonna'])? "selected" : (!isset($_GET['column']) && $col['def']==1)? "selected" : "");?> ><?= $col['nosaukums']; ?></option>
                            <?
                           }
                      ?>
                      <select id="Columns">
                      <?
                      }
                      ?>
                      </select>&nbsp;
                  </td>
        <? if(isset($searchTitle)) { ?>
          <td nowrap ><a href="#" onclick="doSearchOnlyText()">
        <? } else { ?>
           <td nowrap ><a href="#" onclick="doSearch()">
        <? } ?>
          <span id="loading" style="position:absolute; width:32; height:32; margin-left:30px; display: none; ">
          <img src="./img/loading.gif" widht="32" height="32" border="0" />
          </span>
          <img src="img/btn_meklet.gif" alt="<?= text::get('SEARCH'); ?>"  onClick="setPosition1('loading'); return true;" width="70" height="20" border="0" class="block">
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
    $style = 'table_cell_3';  
    if (isset($searchTitle) && is_array($columns)){
      foreach ($columns as $col){
        if( ($col['kolonna'] == 'transactionQty'  || $col['kolonna'] == 'quantity') && $row[$col['kolonna']] < 0 ) {
          $style = 'table_cell_7'; 
        }
      }
    }
  ?>
    <? if(isset($searchTitle)) { ?>
		<tr id="recordRow<?=$i;?>" class="<?=$style;?>" >
	<? } else { ?>
	    <tr id="recordRow<?=$i;?>" class="<?=$style;?>"  onClick="makeActiveRow(this, '<?=$row['URL'];?>');">
	<? } ?>
      <td><?=$number;?></td>
            <?
            if (is_array($columns))
            {
              $colCount = 0;
              foreach ($columns as $col)
              {
                if((substr($col['kolonna'], -9) == 'IR_AKTIVS') || substr($col['kolonna'], -9) == 'IR_ADMINS' || 
                substr($col['kolonna'], -8) == 'IR_PLANS' || substr($col['kolonna'], -11) == 'IR_PABEIGTS' || 
                substr($col['kolonna'], -10) == 'PRIORITATE' ||  substr($col['kolonna'], -8) == 'IR_TRASE' ||  
                substr($col['kolonna'], -9) == 'IR_LIGUMS' || substr($col['kolonna'], -9) == 'PROJECTOR' ||
                substr($col['kolonna'], -7) == 'IR_EPLA' || substr($col['kolonna'], -7) == 'IR_AUTO' || 
                substr($col['kolonna'], -12) == 'APJOMS_ROUND' || substr($col['kolonna'], -3) == 'DVD')
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
                $colCount ++;
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
<? if(isset($searchTitle) ) { ?>
  <tr><td colspan="<?= $colCount; ?>" align="right"><b><?= text::get('TOTAL'); ?></b></td>
      <td align="right"><b><?= $subtotal; ?></b></td>
  </tr>
<? } ?>

</table>

<table cellpadding="0" cellspacing="0" border="0" width="100%">
<tr>
  <td align="right"><?=$listingHtml;?></td>
</tr>
</table>

</body>
