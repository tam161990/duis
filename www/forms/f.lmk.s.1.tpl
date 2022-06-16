<?
if($searchMode)
{
?>
    <script language="JavaScript">
   
    javascript:window.history.forward(1);
   
    </script>
    <body class="frame_1">
    <?=$oForm->getElementHtml('jsRefresh2');?>
    <?=$oForm->getElementHtml('jsRefresh3');?>
    <h1><?= text::toUpper(text::get('PROJRCT_MATERIAL_REPORT')); ?></h1>
    <?= $oForm -> getFormHeader(); ?>
    <table cellpadding="3" cellspacing="1" border="0" width="100%" >
    
       <tr>
            <td align=center colspan="6"><?= $oForm -> getMessage(); ?></td>
       </tr>
       <tr>
            <td class="table_cell_c" width="40%"><?= $oForm -> getElementLabel('project_code'); ?>:</td>
            <td class="table_cell_2" width="10%"><?= $oForm -> getElementHtml('project_code'); ?></td>
            <td class="table_cell_c" width="40%">&nbsp;</td>
            
        </tr>
        <tr>   
            <td>&nbsp;</td>        
            <td>
            <span id="loading" style="position:absolute; width:32; height:32; margin-left:30px; display: none; ">
            <img src="./img/loading.gif" widht="32" height="32" border="0" />
            </span><?=$oForm->getElementHtml('search');?></td>
            <td>&nbsp;</td>
        </tr>
        </table>

    <?= $oForm -> getFormBottom(); ?>
    </body>
<?
} else {
?>
<body class="frame_2"></body>
<table cellpadding="0" cellspacing="0" border="0" width="100%">
	<tr>
		<td><h1><?= text::toUpper(text::get('PROJRCT_MATERIAL_REPORT')); ?></h1></td>
		
	</tr>
</table>

<table cellpadding="5" cellspacing="1" border="0" width="100%" >
<?
	if (is_array($area) && count($area) > 0)
	{
		foreach ($area as $row)
		{
?>
            
           
<? }}?>

</body>
<? } ?>