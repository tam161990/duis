<body class="frame_1">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::toUpper(text::get('DATA_IMPORT'));?></h1>
<?= $oForm -> getFormHeader(); ?>
<script type="text/javascript">
function setImportColumnVisibility()
{
	var selectedReport=optionValue('catalog');
	if (selectedReport=='EDAREA')
	{
       document.all['MATERIALS'].style.display='none';
       document.all['EDAREA'].style.display='block';
       document.all['KALKULATIONS'].style.display='none';
       document.all['KALKULATION_TR'].style.display='none';
              document.all['KALKULATION_STATUSS'].style.display='none';
       document.all['MMS_WORKS'].style.display='none';
       document.all['HARMONIZED'].style.display='none';
       document.all['options'].disabled=true;
       document.all['options'].selectedIndex=0;
	}
	else if (selectedReport=='MATERIAL')
	{
       document.all['MATERIALS'].style.display='block';
       document.all['EDAREA'].style.display='none';
       document.all['KALKULATIONS'].style.display='none';
       document.all['KALKULATION_TR'].style.display='none';
             document.all['KALKULATION_STATUSS'].style.display='none';
       document.all['MMS_WORKS'].style.display='none';
       document.all['HARMONIZED'].style.display='none';
       document.all['options'].disabled=true;
       document.all['options'].selectedIndex=0;
	}

    else if (selectedReport=='KALKULATION')
	{
       document.all['MATERIALS'].style.display='none';
       document.all['EDAREA'].style.display='none';
       document.all['KALKULATIONS'].style.display='block';
       document.all['KALKULATION_TR'].style.display='none';
              document.all['KALKULATION_STATUSS'].style.display='none';
       document.all['MMS_WORKS'].style.display='none';
       document.all['HARMONIZED'].style.display='none';
       document.all['options'].disabled=false;
       document.all['options'].selectedIndex=2;

	}
     else if (selectedReport=='KALKULATION_TR')
	{
       document.all['MATERIALS'].style.display='none';
       document.all['EDAREA'].style.display='none';
       document.all['KALKULATIONS'].style.display='none';
       document.all['KALKULATION_TR'].style.display='block';
              document.all['KALKULATION_STATUSS'].style.display='none';
       document.all['MMS_WORKS'].style.display='none';
       document.all['HARMONIZED'].style.display='none';
       document.all['options'].disabled=false;
       document.all['options'].selectedIndex=2;

	}
     else if (selectedReport=='KALKULATION_STATUSS')
	{
       document.all['MATERIALS'].style.display='none';
       document.all['EDAREA'].style.display='none';
       document.all['KALKULATIONS'].style.display='none';
       document.all['KALKULATION_TR'].style.display='none';
              document.all['KALKULATION_STATUSS'].style.display='block';
       document.all['MMS_WORKS'].style.display='none';
       document.all['HARMONIZED'].style.display='none';
       document.all['options'].disabled=true;
              document.all['options'].selectedIndex=0;

	}

    else if (selectedReport=='HARMONIZED')
	{
       document.all['MATERIALS'].style.display='none';
       document.all['EDAREA'].style.display='none';
       document.all['KALKULATIONS'].style.display='none';
       document.all['KALKULATION_TR'].style.display='none';
              document.all['KALKULATION_STATUSS'].style.display='none';
       document.all['MMS_WORKS'].style.display='none';
       document.all['HARMONIZED'].style.display='block';
       document.all['options'].disabled=true;
       document.all['options'].selectedIndex=0;
	}
    else if (selectedReport=='MMS_WORKS')
	{
       document.all['MATERIALS'].style.display='none';
       document.all['EDAREA'].style.display='none';
       document.all['KALKULATIONS'].style.display='none';
       document.all['KALKULATION_TR'].style.display='none';
             document.all['KALKULATION_STATUSS'].style.display='none';
       document.all['MMS_WORKS'].style.display='block';
       document.all['HARMONIZED'].style.display='none';
       document.all['options'].disabled=true;
       document.all['options'].selectedIndex=0;
	}
    else
	{
       document.all['MATERIALS'].style.display='none';
       document.all['EDAREA'].style.display='none';
       document.all['KALKULATIONS'].style.display='none';
       document.all['KALKULATION_TR'].style.display='none';
              document.all['KALKULATION_STATUSS'].style.display='none';
       document.all['MMS_WORKS'].style.display='none';
       document.all['HARMONIZED'].style.display='none';
       document.all['options'].disabled=true;
       document.all['options'].selectedIndex=0;
	}
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
       <div id="MATERIALS" style="display:none"><?=text::get('REQUIREMENTS_MATERIAL');?></div>
       <div id="EDAREA" style="display:none"><?=text::get('REQUIREMENTS_EDAREA');?></div>
       <div id="KALKULATIONS" style="display:none"><?=text::get('REQUIREMENTS_CALCULATION');?></div>
       <div id="KALKULATION_TR" style="display:none"><?=text::get('REQUIREMENTS_CALCULATION_TR');?></div>
              <div id="KALKULATION_STATUSS" style="display:none"><?=text::get('REQUIREMENTS_CALCULATION_STATUSS');?></div>
       <div id="MMS_WORKS" style="display:none"><?=text::get('REQUIREMENTS_MMS_WORKS');?></div>
       <div id="HARMONIZED" style="display:none"><?=text::get('REQUIREMENTS_HARMONIZED');?></div>
       </td>
    </tr>
</table>

<table cellpadding="5" cellspacing="0" border="0" align="center">
	<tr>
		<td><?= $oForm -> getElementHtml('submit'); ?></td>
	</tr>
</table>
<?= $oForm -> getFormBottom(); ?>
</body>
