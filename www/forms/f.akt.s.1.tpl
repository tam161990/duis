
<body class="frame_1">
    
    <?= $oForm -> getFormHeader(); ?>
    <table cellpadding="0" cellspacing="0" border="0" width="100%">
        <tr>
            <td><h1><?=text::toUpper(text::get('SINGLE_ACT'));?></h1></td>
            <td align="right">
            <? if($actId == false)  {?>
                <img src="img/ico_pdf.gif" alt="" width="16" height="16">&nbsp;
                <?= $oForm -> getElementHtml('actHelp'); ?>
            <? } else {?>
                       &nbsp;
            <? } ?>
            </td>
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
            <td width="20%" rowspan="<?=(($actId === false)?'14':'15');?>" valign="bottom">
                <table cellpadding="5" cellspacing="0" border="0" align="center">
                 <? if(!$isReadonly1 && ($actId != false))  {?>
                    <? if(!$trase || $isAdmin)  {?>
                        <tr><td><?=$oForm->getElementHtml('export_part');?></td></tr>
                    <? } ?>
                    <tr><td><?=$oForm->getElementHtml('export');?></td></tr>
                    <tr><td><img src="img/0.gif" alt="" width="1" height="100" class="block"></td></tr>
                 <? } ?>
    
                 <? if(!$isReadonly2 || !$isReadonlyExceptAdmin)  {?>
                    <tr><td><?= $oForm -> getElementHtml('save'); ?></td> </tr>
                 <? } ?>
    
                 <? if(!$isReadonlyExceptEconomist)  {?>
                    <tr><td><?=$oForm->getElementHtml('return');?></td></tr>
                 <? } ?>
                 <? if($isAdmin && ($actId != false) && ($status == STAT_DELETE || $status == STAT_CLOSE))  {?>
                    <tr><td><?=$oForm->getElementHtml('return');?></td></tr>
                 <? } ?>
                 <?if (($isAuto && ($isAdmin || $isSuperAdmin)) || (!$isAuto && !$isReadonlyExceptEconomist))  {?>
                    <tr><td><?=$oForm->getElementHtml('accept');?></td></tr>
                 <? } ?>
                
                 <? if(false/*!$isReadonly*/)  {?>
                    <tr><td><?=$oForm->getElementHtml('clear');?></td></tr>
                 <? } ?>
                 <? if($isAllowEstimate)  {?>
                    <tr><td><?=$oForm->getElementHtml('view');?></td></tr>
                 <? } ?>
                 <? if($isAllowPrintActcalc)  {?>
                      <tr><td><?=$oForm->getElementHtml('print');?></td></tr>
                 <? } ?>
    
                 <? if($isDelete)  {?>
                    <tr><td><?=$oForm->getElementHtml('delete');?></td></tr>
                 <? } ?>
                 <? if($isAllowToPay)  {?>
                    <tr><td><?=$oForm->getElementHtml('topay');?></td></tr>
                 <? } ?>
                 <? if($actId != false)  {?>
                    <tr><td><?=$oForm->getElementHtml('back');?></td></tr>
                 <? } ?>
                 <? if($isAdmin && ($actId != false) && ($status == STAT_AUTO) )  {?>
                    <tr><td><?=$oForm->getElementHtml('to_insert');?></td></tr>
                 <? } ?>
                 <? if($isAdmin && ($actId != false) && ($status == STAT_INSERT) )  {?>
                    <tr><td><?=$oForm->getElementHtml('to_return');?></td></tr>
                 <? } ?>
                </table>
            </td>
        </tr>
        <tr>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('worker'); ?>:<font color="red">*</font></td>
            <td class="table_cell_2"  width="24%"><?= $oForm -> getElementHtml('worker'); ?></td>
             <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('ouner'); ?>:<font color="red">*</font></td>
            <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('ouner'); ?></td>
           </tr>
        <tr>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('type'); ?>:<font color="red">*</font></td>
            <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('type'); ?></td>
    
        <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('contract'); ?>:<font color="red">*</font></td>
        <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('contract'); ?></td>
    
           </tr>
        <tr>        
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('object'); ?>:<font color="red">*</font></td>
            <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('object'); ?></td>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('EDarea'); ?>:<font color="red">*</font></td>
            <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('EDarea'); ?></td>
    
           </tr>
           <tr>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('designation'); ?>:<font color="red">*</font></td>
            <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('designation'); ?></td>
            <?  if(true)  {?>
                <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('numPostfix'); ?><font color="red">*</font>:</td>
                <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('numPostfix'); ?></td>
            <? } else { ?>
                <td class="table_cell_c" width="16%">&nbsp;</td>
                <td class="table_cell_2" width="24%">&nbsp;</td>
            <? } ?>
           </tr>
           <?  if(!$trase && ($type == ACT_TYPE_DAMAGE_ID || $type == ACT_TYPE_DEFECT_ID 
                    || $type == ACT_TYPE_STIHIJA_ID))  {?>
            <tr>        
                <td class="table_cell_c" width="16%">&nbsp;</td>
                <td class="table_cell_2" width="24%">&nbsp;</td>
                <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('pers_number'); ?>:</td>
                <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('pers_number'); ?></td>
               </tr>
            <? } ?>
        <tr>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('voltage'); ?>:<font color="red">*</font></td>
            <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('voltage'); ?></td>
            <td class="table_cell_c" width="16%">&nbsp;</td>
            <td class="table_cell_2" width="24%">&nbsp;</td>
           </tr>
        
        <tr>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('proces_date'); ?>:<font color="red">*</font></td>
            <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('proces_date'); ?></td>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('isFinished'); ?>:</td>
            <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('isFinished'); ?></td>
           </tr>
        <tr>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('signature'); ?>:<font color="red">*</font></td>
            <td class="table_cell_2" width="24%"><?= $oForm -> getElementHtml('signature'); ?></td>
            <td class="table_cell_c"><?= $oForm -> getElementLabel('toid'); ?>:<font color="red">*</font></td>
            <td class="table_cell_2"><?= $oForm -> getElementHtml('toid'); ?></td>
           </tr>
      <?  if(true)  {?>
        <tr>
             <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('worktitle'); ?>:<font color="red">*</font></td>
            <td class="table_cell_2" colspan="3"><?= $oForm -> getElementHtml('worktitle'); ?></td>
            
         </tr>
            <? } ?>
        <tr>
            <td class="table_cell_c" width="16%"><?= $oForm -> getElementLabel('description'); ?>:</td>
            <td class="table_cell_2" colspan="3"><?= $oForm -> getElementHtml('description'); ?></td>
           </tr>
    </table>
      
    <a name="tab"></a>
    <?= $oForm -> getFormBottom(); ?>
    <?=$oForm->getElementHtml('jsButtonsControl');?>
    <?=$oForm->getElementHtml('jsBackButtons');?>
    <?=$oForm->getElementHtml('jsRefresh2');?>
    </body>
    