<script language="JavaScript">
    <!--
    javascript:window.history.forward(1);
    //-->
    </script>
    <body class="frame_1">
    <?=$oForm->getElementHtml('jsRefresh2');?>
    <?=$oForm->getElementHtml('jsRefresh3');?>
    <h1><?=$searchTitle;?></h1>
    <?= $oForm -> getFormHeader(); ?>
    <table cellpadding="3" cellspacing="1" border="0" width="100%" >
    
       <tr>
            <td align=center colspan="6"><?= $oForm -> getMessage(); ?></td>
       </tr>
       <tr>
            <td class="table_cell_c" width="15%"><?= $oForm -> getElementLabel('type'); ?>:</td>
            <td class="table_cell_2" width="15%"><?= $oForm -> getElementHtml('type'); ?></td>
            <td class="table_cell_c"  width="15%"><?= $oForm -> getElementLabel('section'); ?>:</td>
            <td class="table_cell_2" width="15%"><?= $oForm -> getElementHtml('section'); ?></td>
            <td class="table_cell_c" width="15%"><?= $oForm -> getElementLabel('ouner'); ?>:</td>
            <td class="table_cell_2" width="15%"><?= $oForm -> getElementHtml('ouner'); ?></td>    
       </tr>
       
        <tr>
            <td align="right">
                <?=$oForm->getElementHtml('delete');?>
            </td>
            <td><?=text::get('EVENT_LOG_DELETE_INFO');?></td>
            <td colspan="2" align="right">
            <span id="loading" style="position:absolute; width:32; height:32; margin-left:30px; display: none; ">
            <img src="./img/loading.gif" widht="32" height="32" border="0" />
            </span><?=$oForm->getElementHtml('search');?></td>
            <td colspan="2"><a href="#" onClick="reloadFrame(1,'<?= $criteriaLink; ?>');reloadFrame(23,'');"><?=text::get('RETURN_TO_SEARCH_CRRITERIA');?></a></td>
        </tr>
      
    </table>
    
    <?= $oForm -> getFormBottom(); ?>
    </body>
    