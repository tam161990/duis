<body class="frame_1">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::get('DATA_IMPORT'));?></h1>
<?= $oForm -> getFormHeader(); ?>
<script type="text/javascript">
var importCatalogs = ['MATERIAL',
                     'EDAREA',
                     'KALKULATION',
                     'KALKULATION_TR',
                     'KALKULATION_STATUSS',
                     'MMS_WORKS',
                     'HARMONIZED',
                     'MMS_KALKULATION',
                     'KALKULATION_MATERIAL',
                     'DUUSERS',
                     'MATERIAL_CATEGORY',
                     'MATERIAL_COMPLECTATION',
                     'COMPLECTATION',
                     'ACT_DELETE',
                     'CALC_NORMAS',
                     'VV_DELETE',
                     'WRITE_OFF_CODES'
                     ];

function setImportColumnVisibility()
{
	var selectedReport=optionValue('catalog');
       importCatalogs.forEach(element => {
              if( document.all[element] != 'undefined') {
                     document.all[element].style.display='none';
                     if(selectedReport == element) {
                            document.all[element].style.display='block';
                     } 
              }
       });
       document.all['options'].disabled=true;
       document.all['options'].selectedIndex=0;

}
add2onload('setImportColumnVisibility()');
</script>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<tr>
		<td align=center colspan="6"><?= $oForm -> getMessage(); ?></td>
	</tr>
	<tr>
		<td colspan="6" class="table_head">&nbsp;</td>
	</tr>
	<tr>
		<td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('catalog'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" width="16%"><?= $oForm -> getElementHtml('catalog'); ?></td>
        	<td class="table_cell_2" colspan="2"><?= $oForm -> getElementHtml('options'); ?></td>
        	<td class="table_cell_2" colspan="2">&nbsp;</td>
	</tr>
    <tr>
        <td class="table_cell_c" width="16%"><img src="img/ico_excel.gif" alt="" width="16" height="16">&nbsp;<?= $oForm -> getElementLabel('fileName'); ?>:<font color="red">*</font></td>
		<td class="table_cell_2" colspan="3"><?= $oForm -> getElementHtml('fileName'); ?></td>
        <td class="table_cell_2" width="32%" colspan="2">&nbsp;</td>
	</tr>

</table>
<br />
<table cellpadding="5" cellspacing="1" border="0" width="100%">

	<tr>
		<td colspan="2" class="table_head"><?=text::get('REQUIREMENTS');?></td>
	</tr>
	<tr>
		<td class="table_cell_c" width="50" rowspan="2"><img src="img/ico_attention.gif" alt="" width="41" height="37" class="block"></td>
		<td class="table_cell_2" ><?=text::get('TOTAL_REQUIREMENTS');?></td>
    </tr>
    <tr>
	<td class="table_cell_2" >
       <div id="MATERIAL" style="display:none"><?=text::get('REQUIREMENTS_MATERIAL');?></div>
       <div id="EDAREA" style="display:none"><?=text::get('REQUIREMENTS_EDAREA');?></div>
       <div id="KALKULATION" style="display:none"><?=text::get('REQUIREMENTS_CALCULATION');?></div>
       <div id="KALKULATION_TR" style="display:none"><?=text::get('REQUIREMENTS_CALCULATION_TR');?></div>
       <div id="KALKULATION_STATUSS" style="display:none"><?=text::get('REQUIREMENTS_CALCULATION_STATUSS');?></div>
       <div id="MMS_WORKS" style="display:none"><?=text::get('REQUIREMENTS_MMS_WORKS');?></div>
       <div id="HARMONIZED" style="display:none"><?=text::get('REQUIREMENTS_HARMONIZED');?></div>
       <div id="MMS_KALKULATION" style="display:none"><?=text::get('REQUIREMENTS_MMS_CALCULATION');?></div>
       <div id="KALKULATION_MATERIAL" style="display:none"><?=text::get('REQUIREMENTS_CALCULATION_MATERIAL');?></div>
       <div id="DUUSERS" style="display:none"><?=text::get('REQUIREMENTS_DU_USERS');?></div>
       <div id="MATERIAL_CATEGORY" style="display:none"><?=text::get('REQUIREMENTS_MATERIAL_CATEGORY');?></div>
       <div id="COMPLECTATION" style="display:none"><?=text::get('REQUIREMENTS_COMPLECTATION');?></div>
       <div id="MATERIAL_COMPLECTATION" style="display:none"><?=text::get('REQUIREMENTS_MATERIAL_COMPLECTATION');?></div>
       <div id="ACT_DELETE" style="display:none"><?=text::get('REQUIREMENTS_ACT_DELETE');?></div>
       <div id="CALC_NORMAS" style="display:none"><?=text::get('REQUIREMENTS_CALC_NORMAS');?></div>
       <div id="VV_DELETE" style="display:none"><?=text::get('REQUIREMENTS_VV_DELETE');?></div>
       <div id="WRITE_OFF_CODES" style="display:none"><?=text::get('REQUIREMENTS_WRITE_OFF_CODE');?></div>
       </td>
    </tr>
</table>

<table cellpadding="5" cellspacing="0" border="0" align="center">
	<tr>
		<td>
                     <span id="loading" style="position:absolute; width:32; height:32; margin-left:30px; display: none; ">
                         <img src="./img/loading.gif" widht="32" height="32" border="0" />
                         </span><?= $oForm -> getElementHtml('submit'); ?>
              </td>
       </tr>
</table>
<?= $oForm -> getFormBottom(); ?>
</body>
       