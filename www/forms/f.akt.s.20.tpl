
<body class="frame_1">
    <?=$oForm->getElementHtml('jsRefresh2');?>
    <?= $oForm -> getFormHeader(); ?>
    <table cellpadding="0" cellspacing="0" border="0" width="100%">
        <tr>
            <td><h1><?=text::toUpper(text::get('PROJECT'));?></h1></td>           
        </tr>
    </table>
    
    <table cellpadding="5" cellspacing="1" border="0" width="100%">
        <tr>
            <td align=center colspan="5"><?= $oForm -> getMessage(); ?></td>
        </tr>
        <tr>
            <td colspan="2" class="table_head" align="right">
            <? if($actId != false)  {?>
                <?= $oForm -> getElementHtml('actFullNumber'); ?>
            <? } ?>
            <? if(true)    {?>
                <?= $oForm -> getElementHtml('actNumPostfixLink'); ?>
            <? } ?>
            </td>
            <td colspan="2" class="table_head" align="right">
                <?= $oForm -> getElementLabel('statusTxt'); ?>:
                <font color="red"><?=text::toUpper($oForm -> getElementHtml('statusTxt'));?></font></td>
            <td width="20%" rowspan="<?=(($actId === false)?'4':'5');?>" valign="bottom">
                <table cellpadding="5" cellspacing="0" border="0" align="center">
                 <? if(!$isReadonly1 && ($actId != false))  {?>                    
                    <tr><td><?=$oForm->getElementHtml('export');?></td></tr>
                    <tr><td><img src="img/0.gif" alt="" width="1" height="10" class="block"></td></tr>
                 <? } ?>
    
                 <? if(!$isReadonly || !$isReadonlyExceptAdmin)  {?>
                    <tr><td><?= $oForm -> getElementHtml('save'); ?></td> </tr>
                 <? } ?>
    
                 <? if(!$isReadonlyExceptEconomist)  {?>
                    <tr><td><?=$oForm->getElementHtml('return');?></td></tr>
                 <? } ?>
                 <? if($isAdmin && ($actId != false) && ($status == STAT_DELETE || $status == STAT_CLOSE))  {?>
                    <tr><td><?=$oForm->getElementHtml('return');?></td></tr>
                 <? } ?>
                 <? if(!$isReadonlyExceptEconomist)  {?>
                    <tr><td><?=$oForm->getElementHtml('accept');?></td></tr>
                 <? } ?>
                 <? if($projectApprover && $status == STAT_ACCEPT) {?>
                    <tr><td><?=$oForm->getElementHtml('decline');?></td></tr>
                 <? } ?>
                 
                 <? if($isDelete)  {?>
                    <tr><td><?=$oForm->getElementHtml('delete');?></td></tr>
                 <? } ?>
                 <? if($actId != false)  {?>
                    <tr><td><?=$oForm->getElementHtml('back');?></td></tr>
                 <? } ?>
                 <? if($status == STAT_CLOSE && ($isAdmin || $isEconomist || $projectApprover))  {?>
                    <tr><td><?=$oForm->getElementHtml('make_excel');?></td></tr>
                 <? } ?>
                </table>
            </td>
        </tr>
        <tr>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('worker'); ?>:<?=(($isReadonly)?'':'<font color="red">*</font>');?></td>
            <td class="table_cell_2"  width="24%"><?= $oForm -> getElementHtml('worker'); ?></td>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('ouner'); ?>:<?=((!$isReadonly1 || !$isReadonly)?'<font color="red">*</font>':'');?></td>
            <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('ouner'); ?></td>
        </tr>
        
        <tr>        
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('numPostfix'); ?><font color="red">*</font>:</td>
            <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('numPostfix'); ?></td>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('EDarea'); ?>:<?=(($isReadonly)?'':'<font color="red">*</font>');?></td>
            <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('EDarea'); ?></td>
    
        </tr>
    
        
        <tr>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('year'); ?>:<?=(($isReadonly)?'':'<font color="red">*</font>');?></td>
            <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('year'); ?></td>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('type'); ?>:<?=(($isReadonly)?'':'<font color="red">*</font>');?></td>
            <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('type'); ?></td>
        </tr>
        
        <tr>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('worktitle'); ?>:<?=(($isReadonly)?'':'<font color="red">*</font>');?></td>
            <td class="table_cell_2" colspan="3"><?= $oForm -> getElementHtml('worktitle'); ?></td>            
         </tr>
      
       
    </table>
      
    <a name="tab"></a>
    <?= $oForm -> getFormBottom(); ?>
    <?=$oForm->getElementHtml('jsButtonsControl');?>
    <?=$oForm->getElementHtml('jsBackButtons');?>
    </body>
    