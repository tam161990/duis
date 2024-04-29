<script type="text/javascript">
function doSort(column, order)
{
    eval(xmlHttpGetValue('<?= $searchLink; ?>&xmlHttp=1&sort_k=' + column + '&sort_o=' + order));
    reloadFrame(1, '<?= $orderLink; ?>&order=' + o + '&kol=' + k);
}
function savedField (el, color) { 
    el.style.borderColor = color; 
    parent = el.parentNode;
    if(parent.firstChild.nodeName == 'SPAN') {
        parent.removeChild(sp1);
    }
    //parent.removeChild(parent.childNodes[0]); 
}
// succsess
var sp1 = document.createElement('span');
sp1.append('Saglabāts');
sp1.style.color = 'green';
// error
var sp2 = document.createElement('span');
sp2.append('<?=text::get('ERROR_DOUBLE_VALUE');?>');
sp2.style.color = 'red';
</script>

<h1><?=text::toUpper(text::get(TAB_MATERIAL));?></h1>
<?= $oFormMaterialTab -> getFormHeader(); ?>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="2"><?= $oFormMaterialTab -> getMessage(); ?></td>
    </tr>
    <tr>
        <td>
            <table cellpadding="0" cellspacing="0" border="0" width="100%">
                <tr>
                    <td width="50"></td>
                    <td><span class="error" name="error_span" id="error_span"><?= $oFormMaterialTab->getElementHtml('error_msg'); ?></span></td>
                </tr>
            </table>
        </td>
        <td></td>
	</tr>    
    <tr>
	<td valign="top">        
        <table cellpadding="5" cellspacing="1" border="0" width="100%">
            <tr>
                <td colspan="6"><?= $oFormMaterialTab -> getElementLabel('work_types'); ?>: <?= $oFormMaterialTab->getElementHtml('work_types'); ?></td>
                <td align="right" colspan="6"><?=$listingHtml;?></td>
           </tr>
		   <tr class="table_head_2">
                <th width="5%"><?=text::get('CODE');?>
                    <a href="#" onclick="doSort('MATR_KODS', 'ASC')">
                        <img src="img/sort_asc.gif" alt="A-Z" width="11" height="6" border="0"></a>
                    <a href="#" onclick="doSort('MATR_KODS', 'DESC')">
                        <img src="img/sort_desc.gif" alt="Z-A" width="11" height="6" border="0"></a>
                </th>
                <th width="30%"><?=text::get('SINGLE_WORK_TYPE');?></th>
                <th width="20%"><?=text::get('NAME');?>
                    <a href="#" onclick="doSort('MATR_NOSAUKUMS', 'ASC')">
                        <img src="img/sort_asc.gif" alt="A-Z" width="11" height="6" border="0"></a>
                    <a href="#" onclick="doSort('MATR_NOSAUKUMS', 'DESC')">
                        <img src="img/sort_desc.gif" alt="Z-A" width="11" height="6" border="0"></a>
                </th>
                <th  width="5%"><?=text::get('UNIT_OF_MEASURE');?>
                    <a href="#" onclick="doSort('MATR_MERVIENIBA', 'ASC')">
                        <img src="img/sort_asc.gif" alt="A-Z" width="11" height="6" border="0"></a>
                    <a href="#" onclick="doSort('MATR_MERVIENIBA', 'DESC')">
                        <img src="img/sort_desc.gif" alt="Z-A" width="11" height="6" border="0"></a>
                </th>
                <th  width="5%"><?=text::get('AMOUNT');?>
                    <a href="#" onclick="doSort('MATR_DAUDZUMS', 'ASC')">
                        <img src="img/sort_asc.gif" alt="A-Z" width="11" height="6" border="0"></a>
                    <a href="#" onclick="doSort('MATR_DAUDZUMS', 'DESC')">
                        <img src="img/sort_desc.gif" alt="Z-A" width="11" height="6" border="0"></a>
                </th>
                <th  width="10%"><?=text::get('COMPLECTATION');?>
                    <a href="#" onclick="doSort('MATR_COMPLECTATION', 'ASC')">
                        <img src="img/sort_asc.gif" alt="A-Z" width="11" height="6" border="0"></a>
                    <a href="#" onclick="doSort('MATR_COMPLECTATION', 'DESC')">
                        <img src="img/sort_desc.gif" alt="Z-A" width="11" height="6" border="0"></a>
                </th>
                <th  width="10%"><?=text::get('CROSSECTION');?>
                    <a href="#" onclick="doSort('MATR_CROSSECTION', 'ASC')">
                        <img src="img/sort_asc.gif" alt="A-Z" width="11" height="6" border="0"></a>
                    <a href="#" onclick="doSort('MATR_CROSSECTION', 'DESC')">
                        <img src="img/sort_desc.gif" alt="Z-A" width="11" height="6" border="0"></a>
                </th>
                <th  width="15%"><?=text::get('COMMENT');?>
                    <a href="#" onclick="doSort('MATR_PIEZIMES', 'ASC')">
                        <img src="img/sort_asc.gif" alt="A-Z" width="11" height="6" border="0"></a>
                    <a href="#" onclick="doSort('MATR_PIEZIMES', 'DESC')">
                        <img src="img/sort_desc.gif" alt="Z-A" width="11" height="6" border="0"></a>
                </th>
                <? if( ($status == STAT_CLOSE && ($isAdmin || $isEconomist || $projectApprover)))  {?>
                <th  width="3%" colspan=2><?=text::get('PROJECT_EXPORT_TYPE');?>
                    <a href="#" onclick="doSort('MATR_PROJECT_EXPORT', 'ASC')">
                        <img src="img/sort_asc.gif" alt="A-Z" width="11" height="6" border="0"></a>
                    <a href="#" onclick="doSort('MATR_PROJECT_EXPORT', 'DESC')">
                        <img src="img/sort_desc.gif" alt="Z-A" width="11" height="6" border="0"></a>
                </th>
                <? } else {?>
                    <th width="3%">&nbsp;</th>
                    <th width="3%">&nbsp;</th>
                <? } ?>
			</tr>

	  <?
      $x = 0;
      foreach ($aGroupMaterials as $j => $actMaterial)
	  {
           $changestyle = "font-weight:normal;"   ;
           if($actMaterial['MATR_IS_WORKER'] == 1)
           {
                $pricestyle = "color:#e4edd8;  font-size:1px;"   ;
           ?>
            <tr class="table_cell_4" style="<?=$changestyle;?>" id="blank_mat<?= $i; ?>">

           <?}
           else
           {
                $pricestyle = "color:#ffffff;  font-size:11px;"   ;
           ?>
            <tr class="table_cell_3" style="<?=$changestyle;?>" id="blank_mat<?= $i; ?>">
           <?}
		?>


				<td>
                    <?= $oFormMaterialTab->getElementHtml('id['.$x.']'); ?>
                    <?= $oFormMaterialTab->getElementHtml('code['.$x.']'); ?>
                </td>
                <td><?= $oFormMaterialTab->getElementHtml('work_type['.$x.']'); ?> </td>   
				<td><?= $oFormMaterialTab->getElementHtml('title['.$x.']'); ?></td>
				<td><?= $oFormMaterialTab->getElementHtml('unit['.$x.']'); ?></td>                
                <td><?= $oFormMaterialTab->getElementHtml('amount_mat['.$x.']'); ?></td>
                <td><?= $oFormMaterialTab->getElementHtml('complectation['.$x.']'); ?></td>
                <td><?= $oFormMaterialTab->getElementHtml('crossection['.$x.']'); ?></td>
                <td><?= $oFormMaterialTab->getElementHtml('notes['.$x.']'); ?></td>                
                <? if( $status == STAT_CLOSE )  {
                    if ($isAdmin || $isEconomist || $projectApprover) { ?>
                        <td><?= $oFormMaterialTab->getElementHtml('export_type['.$x.']'); ?></td>
                    <? } ?>
                    <td style="background-color:<?=$actMaterial['color'];?>"><?= $oFormMaterialTab->getElementHtml('nomenklatura['.$x.']'); ?></td>
                <? } else {?>
                    <td>
                        <? if(!$isReadonly)  {?>
                        <?= $oFormMaterialTab->getElementHtml('mat_del['.$x.']'); ?>
                        <? } else{ ?>
                        &nbsp;
                        <? } ?>
                    </td>
                    <td>
                        <? if(!$isReadonly)  {?>
                        <input type="checkbox" onclick="eval(xmlHttpGetValue('<?= $searchLink; ?>&issue=<?=$actMaterial['MATR_ID'];?>&op=' + ((this.checked)?'<?=OP_INSERT;?>':'<?=OP_DELETE;?>'))); "  /></td>
                        <? } else{ ?>
                        &nbsp;
                        <? } ?>
                    </td>
                <? } ?>
			</tr>
            
            <?
            $x++;
            }
            ?>
            <tr>
                 <td align="right" colspan="12"><?=$listingHtml;?></td>
            </tr>
           
	    </table>
        </td>
        <td width="20%" valign="top">
            &nbsp;
        </td>
	</tr>
    <tr>
        <td>&nbsp;</td>
        <td align="right"></td>
    </tr>
</table>
<div class="navbar">
    <table cellpadding="5" cellspacing="1" border="0" align="left" width="100">
    <? if(!$isReadonly)  {
      foreach($favorit as $i=>$val){?>
     <tr>
        <td bgcolor="white"><?= $oFormMaterialTab->getElementHtml('group['.$i.']'); ?></td>
     </tr>
    <? }} ?>
    <tr>
        <? if(!$isReadonly || ($status == STAT_CLOSE && ($isAdmin || $isEconomist || $projectApprover)))  {?>
            <td><?= $oFormMaterialTab -> getElementHtml('save'); ?></td>
         <? } ?>

     </tr>
     <tr>
        <? if(!$isReadonly || ($status == STAT_CLOSE && ($isAdmin || $isEconomist || $projectApprover)))  {?>
           <td><?= $oFormMaterialTab -> getElementHtml('delete_all'); ?></td>
        <? } ?>        
        </tr>
      <tr>
        <td><?= $oFormMaterialTab -> getElementHtml('all'); ?></td>
      </tr>
      <tr>
        <td><?= $oFormMaterialTab -> getElementHtml('default_order'); ?></td>
      </tr>
    </table>   
</div>
<?=$oFormMaterialTab->getElementHtml('jsRefresh2');?>

<?= $oFormMaterialTab -> getFormBottom(); ?>

