<h1><?=text::toUpper(text::get('RBF_ATTACHMENTS'));?></h1>



<? if (isset($canEdit) && $canEdit): ?>
<!-- File Upload Form -->
<form method="post" enctype="multipart/form-data">
	<table cellpadding="5" cellspacing="0" border="0" width="100%">
		<tr>
			<td class="table_cell" width="15%">
				<strong><?=text::get('FILE_SELECT');?>:</strong>
				<font color="red">*</font>
			</td>
			<td class="table_cell_2" width="35%">
				<input type="file" name="file_upload" id="file_upload" required />
				<br />
				<small style="color: #666;"><?=text::get('FILE_ALLOWED_TYPES');?>: docx, pdf, excel, gif, jpeg, png</small>
			</td>
			<td class="table_cell" width="15%">
				<strong><?=text::get('FILE_DESCRIPTION');?>:</strong>
			</td>
			<td class="table_cell_2" width="25%">
				<textarea name="file_description" id="file_description" rows="2" style="width: 100%;"></textarea>
			</td>
			<td class="table_cell_2" width="10%" style="text-align: center;">
				<input type="submit" name="upload_file" value="<?=text::get('BTN_UPLOAD');?>" class="btn" />
			</td>
		</tr>
	</table>
</form>
<? endif; ?>

<!-- Files List -->
<table cellpadding="5" cellspacing="1" border="0" width="100%">
	<thead>
		<tr>
			<th class="table_head" width="5%">&nbsp;</th>
			<th class="table_head" width="30%"><?=text::get('FILE_NAME');?></th>
			<th class="table_head" width="25%"><?=text::get('FILE_DESCRIPTION');?></th>
			<th class="table_head" width="15%"><?=text::get('DATE');?></th>
			<th class="table_head" width="15%"><?=text::get('EXPORT_ACT_AUTHOR');?></th>
			<? if (isset($canEdit) && $canEdit): ?>
			<th class="table_head" width="10%"><?=text::get('ACTIONS');?></th>
			<? endif; ?>
		</tr>
	</thead>
	<tbody>
	<?
	if (isset($fileInfo) && is_array($fileInfo) && count($fileInfo) > 0)
	{
		for($i=0; $i<count($fileInfo); $i++)
		{
		?>
			<tr>
				<td class="table_cell" style="text-align: center;">
					<img src="img/<?=isset($fileInfo[$i]['icon'])?$fileInfo[$i]['icon']:'ico_file.gif';?>" alt="" width="16" height="16">
				</td>
				<td class="table_cell_2">
					<a href="<?=$fileInfo[$i]['getFileURL'];?>" target="_blank"><?=$fileInfo[$i]['RFLS_NOSAUKUMS'];?></a>
				</td>
				<td class="table_cell_2">
					<?=isset($fileInfo[$i]['RFLS_DESCRIPTION']) ? htmlspecialchars($fileInfo[$i]['RFLS_DESCRIPTION']) : '&nbsp;';?>
				</td>
				<td class="table_cell"><?=$fileInfo[$i]['RFLS_DATUMS'];?></td>
				<td class="table_cell"><?=$fileInfo[$i]['AUTORS'];?></td>
				<? if (isset($canEdit) && $canEdit): ?>
				<td class="table_cell" style="text-align: center;">
					<? 
					// Only show delete button for user-uploaded files (RBF type), not exported PDFs
					if (isset($fileInfo[$i]['fileType']) && $fileInfo[$i]['fileType'] == 'RBF'): 
					?>
					<a href="?formId=f.akt.s.30&actId=<?=$actId;?>&tab=RBF_ATTACHMENTS&delete_file=<?=$fileInfo[$i]['RFLS_ID'];?>" 
					   onclick="return confirm('<?=addslashes(text::get('CONFIRM_DELETE_FILE'));?>');">
						<img src="img/btn_delete.gif" alt="<?=text::get('BTN_DELETE');?>" border="0">
					</a>
					<? else: ?>
						&nbsp;
					<? endif; ?>
				</td>
				<? endif; ?>
			</tr>
		<?
		}
	}
	else
	{
	?>
		<tr>
			<td class="table_cell_2" colspan="<?=(isset($canEdit) && $canEdit) ? '6' : '5';?>" style="text-align: center; padding: 20px; color: #666;">
				<?=text::get('NO_FILES');?>
			</td>
		</tr>
	<?
	}
	?>
	</tbody>
</table>

