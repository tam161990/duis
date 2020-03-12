<body class="frame_1">
<?=$oForm->getElementHtml('jsRefresh2');?>
<h1><?=text::get('GPS');?></h1>

<?= $oForm -> getFormHeader(); ?>
<script>
//f-ja nodzest bloku fail pievienoshanaj
function removeFileBlock(id)
{
	var filelist=getElement("filelist");
	var filerow=getElement("filerow_"+id);
	if (filelist && filerow)
	{
		filelist.removeChild(filerow);
	}
}
//f-ja uztaisit tabulu vienam faila blokam
function drowFileBlock(filelist, filerow, id, description, readonly)
{
	filerow.id="filerow_"+id;

	filecell = filerow.insertCell();
	filecell.width="100%";
	filecell.innerHTML="<table cellpadding='5' cellspacing='1' border='0' width='100%' id='filetable_"+id+"'></table>";

	fileblock=filecell.firstChild;

	row = fileblock.insertRow();
	cell = row.insertCell();
	cell.className="table_cell_c";
	cell.width="16%";
	cell.innerHTML="";

    cell = row.insertCell();
	cell.className="table_cell_2";
    cell.width="16%";
	cell.innerHTML="<select class=\"flex\" id=\"edRegion_"+id+"\" name=\"edRegion_"+id+"\" \""+((readonly)?"disabled": "")+"\"><?= $rgionOptions; ?></select>";


	cell = row.insertCell();
	cell.className="table_cell_2";
	cell.innerHTML="<input id=\"fileName_"+id+"\" type=\"file\" name=\"fileName_"+id+"\" class=\"flex\"/>";

	cell = row.insertCell();
	cell.className="table_cell_c";
	cell.width="16%";
   	cell.innerHTML="<input type='image' src='img/btn_dzest.gif' alt='<?=text::get('DELETE');?>' width='70' height='20' onclick='removeFileBlock("+id+");return false;' name='delete_'"+id+"' id='delete_'"+id+"' border=0/>";


}
//f-ja atjaunot fail bloku pec submita
function restoreFileBlock(id, region)
{
	var filelist=getElement("filelist");
	if (filelist)
	{
		var filerow = filelist.insertRow();
		if (filerow)
		{
			drowFileBlock(filelist, filerow, id, region);
		}
	}
}
//f-ja pievienot bloku fail pievienoshanaj
function addFileBlock()
{

	var filelist=getElement("filelist");

	if (filelist)
	{
		var newid;
		newid = parseInt(document.all["fileFieldId"].value)+1;
		document.all["fileFieldId"].value = newid;

		var filerow = filelist.insertRow(1);

		if (filerow)
		{
			drowFileBlock(filelist, filerow, newid, "-1");
		}
	}
}
</script>
<? if($isEdUser || $isAdmin || $isEditor){ ?>
<table cellpadding="0" cellspacing="0" border="0" width="100%">
<tr>
		<td align=center colspan="2"><?= $oForm -> getMessage(); ?></td>
</tr>
<tbody id="filelist">

	<tr>
		<td>
			<table cellpadding="0" cellspacing="1" border="0" width="100%">
				<tr>
					<td class="table_head"><?=text::get('ADDING_FILES');?>:</td>
                    <? if($isEdUser || $isAdmin){  ?>
					<td class="table_head" align="right" width="16%"><?=$oForm->getElementHtml('addFile');?></td>
                    <? } ?>
                </tr>
			</table>
		</td>
	</tr>
    <?
	if($fileRowsCount >0)
	{
		foreach ($savedFilesArray as $key => $value)
		{
		?>
			<script language="JavaScript">
			<?
			echo ($fileDescription[$key] !== false)? 'restoreFileBlock('.$key.',"'.$fileDescription[$key].'");':'';
			?>
			</script>
		<?
		}
	}
	?>

    <?
	if (isset($fileInfo) && is_array($fileInfo))
	{
	  ?>
      <table cellpadding='5' cellspacing='1' border='0' width='100%' >
      <?
		for($i=0; $i<count($fileInfo); $i++)
		{
		?>
			<tr>
				<td class="table_cell_c" width="16%"><?=$fileInfo[$i]['GFLS_DATUMS'];?></td>
                <td class="table_cell_2" width="16%"><?=$fileInfo[$i]['GFLS_REGION'];?></td>
				<td class="table_cell_2" ><a href="<?=$fileInfo[$i]['getFileURL'];?>"><?=$fileInfo[$i]['GFLS_NOSAUKUMS'];?></a></td>
				<td width="16%" class="table_cell_c">
				<?
				if($fileInfo[$i]['deleteURL'] !== false)
				{
				?>
					<a href="<?=$fileInfo[$i]['deleteURL'];?>" onClick="if (isDelete()) {return true;} else {return false;}"><?=text::get('DELETE');?></a>
				<?
				}

				?>
				</td>
			</tr>

			<tr>
				<td colspan="4" class="table_separator"><img src="img/0.gif" alt="" width="1" height="1" class="block"></td>

			</tr>
		<?
		}
        ?>
        </table>
    <?
	}
	?>
</tbody>
</table>
<? if($isEdUser || $isAdmin){  ?>
<table cellpadding="5" cellspacing="0" border="0" align="center">
	<tr>
		<td><?=$oForm->getElementHtml('add');?></td>

	</tr>
</table>
<? } ?>
<? } ?>

<?= $oForm -> getFormBottom(); ?>

</body>