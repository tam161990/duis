<h1><?=text::toUpper(text::get('TAB_UPLOAD_STAT'));?></h1>
<table cellpadding="5" cellspacing="1" border="0" width="100%">
    <thead>
        <tr class="table_head_2">
            <th width="15%"><?=text::get('DATE');?></th>
            <th width="35%"><?=text::get('FILE');?></th>
            <th width="25%"><?=text::get('USER');?></th>
            <th width="15%"><?=text::get('ROWS');?></th>
            <th width="10%">&nbsp;</th>
        </tr>
    </thead>
    <tbody>
    <?
    if (isset($estimateFilesInfo) && is_array($estimateFilesInfo) && count($estimateFilesInfo) > 0)
    {
        foreach($estimateFilesInfo as $fileInfo)
        {
        ?>
            <tr>
                <td class="table_cell_2"><?=$fileInfo['ESTM_DATE'];?></td>
                <td class="table_cell_2"><?=htmlspecialchars($fileInfo['ESTM_NAME']);?></td>
                <td class="table_cell_2"><?=$fileInfo['AUTORS'];?></td>
                <td class="table_cell_2" align="center"><?=$fileInfo['ESTM_ROWS'];?></td>
                <td class="table_cell_2" align="center"><a href="<?=$fileInfo['getFileURL'];?>"><img src="img/ico_excel.gif" alt="<?=text::get('VIEW_DETAILS');?>" width="16" height="16"></a></td>
            </tr>
        <?
        }
    }
    else
    {
        ?>
        <tr>
            <td class="table_cell_2" colspan="5" align="center">
                <i><?=text::get('NO_DATA');?></i>
            </td>
        </tr>
        <?
    }
    ?>
    </tbody>
</table>

