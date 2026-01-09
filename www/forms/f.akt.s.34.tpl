<?
// RBF Acts - Works Tab for Automatic Acts - Template

if (!$hasAccess)
{
    ?>
    <table cellpadding="5" cellspacing="1" border="0" width="100%">
        <tr>
            <td align="center">
                <table width="100%">
                    <tr>
                        <td><h1><?= text::toUpper(text::get('RBF_WORKS_TAB')); ?></h1></td>
                    </tr>
                </table>
            </td>
        </tr>
        <tr>
            <td class="table_cell_3" align="center">
                <i><?= text::get('ERROR_NO_ACCESS') ?></i>
            </td>
        </tr>
    </table>
    <?
}
elseif ($actId === false)
{
    ?>
    <table cellpadding="5" cellspacing="1" border="0" width="100%">
        <tr>
            <td align="center">
                <table width="100%">
                    <tr>
                        <td><h1><?= text::toUpper(text::get('RBF_WORKS_TAB')); ?></h1></td>
                    </tr>
                </table>
            </td>
        </tr>
        <tr>
            <td class="table_cell_3" align="center">
                <i><?= text::get('RBF_WORKS_EMPTY') ?></i>
            </td>
        </tr>
    </table>
    <?
}
elseif ($worksFormatted && count($worksFormatted) > 0)
{
    ?>
    <form method="post" name="rbf_auto_works_form">
    <input type="hidden" name="export_action" value="" />
    
    <? if (!empty($exportMessage)) { ?>
        <div style="padding: 10px; margin: 10px 0; background-color: #ffebee; border-left: 4px solid #f44336; color: #c62828;">
            <?= $exportMessage ?>
        </div>
    <? } ?>
    
    <table cellpadding="5" cellspacing="1" border="0" width="100%">
        <tr>
            <td align="center">
                <table width="100%">
                    <tr>
                        <td><h1><?= text::toUpper(text::get('RBF_WORKS_TAB')); ?></h1></td>
                    </tr>
                </table>
            </td>
        </tr>
        
        <? if ($darbiFormatted && count($darbiFormatted) > 0) { ?>
        <tr>
            <td valign="top" style="padding-bottom: 20px;">
                <table cellpadding="5" cellspacing="1" border="0" width="100%" class="table_form">
                    <tr class="table_head_2">
                        <th rowspan="2" align="center"><?= text::get('RBF_CALC_GROUP') ?></th>
                        <th rowspan="2"><?= text::get('RBF_PRICE') ?></th>
                        <th colspan="2">1</th>
                        <th colspan="2">2</th>
                        <th colspan="2">3</th>
                        <th rowspan="2"><?= text::get('RBF_COST_ACCOUNT') ?></th>
                    </tr>
                    <tr class="table_head_2">
                        <th><?= text::get('RBF_HOURS_TOTAL') ?></th>
                        <th><?= text::get('RBF_TOTAL_COST') ?></th>
                        <th><?= text::get('RBF_HOURS_TOTAL') ?></th>
                        <th><?= text::get('RBF_TOTAL_COST') ?></th>
                        <th><?= text::get('RBF_HOURS_TOTAL') ?></th>
                        <th><?= text::get('RBF_TOTAL_COST') ?></th>
                    </tr>
                    <?
                    foreach ($darbiFormatted as $item)
                    {
                        ?>
                        <tr class="table_cell_3">
                            <td align="left"><?= $item['calc_code'] ?> <?= $item['calc_name'] ?></td>
                            <td align="right"><?= $item['price'] ?></td>
                            <td align="right"><?= $item['hours_1'] != '0.00' ? $item['hours_1'] : '0' ?></td>
                            <td align="right"><?= $item['cost_1'] != '0.00' ? $item['cost_1'] : '0' ?></td>
                            <td align="right"><?= $item['hours_2'] != '0.00' ? $item['hours_2'] : '0' ?></td>
                            <td align="right"><?= $item['cost_2'] != '0.00' ? $item['cost_2'] : '0' ?></td>
                            <td align="right"><?= $item['hours_3'] != '0.00' ? $item['hours_3'] : '0' ?></td>
                            <td align="right"><?= $item['cost_3'] != '0.00' ? $item['cost_3'] : '0' ?></td>
                            <td align="center"><?= $item['account_code'] ?></td>
                        </tr>
                        <?
                    }
                    ?>
                    <!-- Total Row -->
                    <tr class="table_head_2" style="font-weight: bold; background-color: #cbeaa0;">
                        <td colspan="2" align="right"><?= text::get('RBF_TOTAL') ?></td>
                        <td align="right"><?= $totalsFormatted['hours_1'] ?></td>
                        <td align="right"><?= $totalsFormatted['cost_1'] ?></td>
                        <td align="right"><?= $totalsFormatted['hours_2'] ?></td>
                        <td align="right"><?= $totalsFormatted['cost_2'] ?></td>
                        <td align="right"><?= $totalsFormatted['hours_3'] ?></td>
                        <td align="right"><?= $totalsFormatted['cost_3'] ?></td>
                        <td>&nbsp;</td>
                    </tr>
                    <!-- VAT Row -->
                    <tr class="table_head_2" style="font-weight: bold; background-color: #cbeaa0;">
                        <td colspan="2" align="right"><?= text::get('RBF_VAT_21') ?></td>
                        <td>&nbsp;</td>
                        <td align="right"><?= $totalsFormatted['vat_1'] ?></td>
                        <td>&nbsp;</td>
                        <td align="right"><?= $totalsFormatted['vat_2'] ?></td>
                        <td>&nbsp;</td>
                        <td align="right"><?= $totalsFormatted['vat_3'] ?></td>
                        <td>&nbsp;</td>
                    </tr>
                    <!-- Total with VAT Row -->
                    <tr class="table_head_2" style="font-weight: bold; background-color: #cbeaa0;">
                        <td colspan="2" align="right"><?= text::get('RBF_TOTAL_WITH_VAT') ?></td>
                        <td>&nbsp;</td>
                        <td align="right"><?= $totalsFormatted['total_with_vat_1'] ?></td>
                        <td>&nbsp;</td>
                        <td align="right"><?= $totalsFormatted['total_with_vat_2'] ?></td>
                        <td>&nbsp;</td>
                        <td align="right"><?= $totalsFormatted['total_with_vat_3'] ?></td>
                        <td>&nbsp;</td>
                    </tr>
                </table>
            </td>
        </tr>
        <? } ?>
        
        <tr>
            <td valign="top">
                
                <table cellpadding="0" cellspacing="0" border="0" width="100%">
                    <tr>
                        <td valign="top" style="padding-right: 10px;">
                            <table cellpadding="5" cellspacing="1" border="0" width="100%">
                                <tr class="table_head_2">
                                    <th width="3%" align="center">&nbsp;</th>
                                    <th width="12%"><?= text::get('RBF_WORK_ORDER_NUMBER') ?></th>
                                    <th width="8%"><?= text::get('RBF_WORK_CALC_CODE') ?></th>
                                    <th width="8%"><?= text::get('RBF_WORK_MMS_CODE') ?></th>
                                    <th width="25%"><?= text::get('RBF_WORK_MMS_TITLE') ?></th>
                                    <th width="12%"><?= text::get('RBF_WORK_STATUS') ?></th>
                                    <th width="10%"><?= text::get('RBF_WORK_PLAN_DATE') ?></th>
                                    <th width="8%"><?= text::get('RBF_WORK_NORMA') ?></th>
                                    <th width="10%"><?= text::get('RBF_WORK_APPROVE_DATE') ?></th>
                                </tr>
                                <?
                                foreach ($worksFormatted as $work)
                                {
                                    ?>
                                    <tr class="table_cell_3">
                                        <td align="center">
                                            <input type="checkbox" 
                                                   name="checked_works[]"
                                                   value="<?= $work['work_id'] ?>"
                                                   class="rbf-work-checkbox" 
                                                   data-work-status="<?= $work['work_status_code'] ?>" 
                                                   <?= $work['checkbox_checked'] ?> 
                                                   <?= $work['checkbox_disabled'] ?> />
                                        </td>
                                        <td><?= $work['order_number'] ?></td>
                                        <td><?= $work['calc_code'] ?></td>
                                        <td><?= $work['mms_code'] ?></td>
                                        <td align="left"><?= $work['mms_title'] ?></td>
                                        <td><?= $work['status_name'] ?></td>
                                        <td align="center"><?= $work['plan_date'] ?></td>
                                        <td align="right"><?= $work['norma'] ?></td>
                                        <td align="center"><?= $work['approve_date'] ?></td>
                                    </tr>
                                    <?
                                }
                                ?>
                            </table>
                        </td>
                        <? if ($showMiddleExportButton || $showFinalExportButton) { ?>
                        <td valign="top" align="right" width="160">
                            <table cellpadding="5" cellspacing="0" border="0">
                                <? if ($showMiddleExportButton) { ?>
                                <tr>
                                    <td>
                                        <input type="image" 
                                               src="img/btn_nodot_saskanosanai.gif" 
                                               onclick="if(confirm('<?= addslashes(text::get('RBF_CONFIRM_MIDDLE_EXPORT')) ?>')) { document.getElementsByName('export_action')[0].value='middle'; document.rbf_auto_works_form.submit(); return false; } return false;" 
                                               title="<?= text::get('RBF_MIDDLE_EXPORT_TOOLTIP') ?>" 
                                               style="cursor: pointer;" />
                                    </td>
                                </tr>
                                <? } ?>
                                
                                <? if ($showFinalExportButton) { ?>
                                <tr>
                                    <td>
                                        <input type="image" 
                                               src="img/btn_120_nodosana.gif" 
                                               onclick="return handleFinalExport();" 
                                               title="<?= text::get('RBF_FINAL_EXPORT_TOOLTIP') ?>" 
                                               style="cursor: pointer;" />
                                    </td>
                                </tr>
                                <? } ?>
                            </table>
                        </td>
                        <? } ?>
                    </tr>
                </table>
            </td>
        </tr>
    </table>
    </form>
    <?
}
else
{
    ?>
    <table cellpadding="5" cellspacing="1" border="0" width="100%">
        <tr>
            <td align="center">
                <table width="100%">
                    <tr>
                        <td><h1><?= text::toUpper(text::get('RBF_WORKS_TAB')); ?></h1></td>
                    </tr>
                </table>
            </td>
        </tr>
        <tr>
            <td class="table_cell_3" align="center">
                <i><?= text::get('RBF_AUTO_WORKS_EMPTY') ?></i>
            </td>
        </tr>
    </table>
    <?
}
?>

<script type="text/javascript">
// Validation for Final Export button
function handleFinalExport() {
    var processWorkCount = <?= isset($processWorkCount) ? $processWorkCount : 0 ?>;
    var notCompletedWorkCount = <?= isset($notCompletedWorkCount) ? $notCompletedWorkCount : 0 ?>;
    
    // Check if there are PROCESS works - must use Middle Export first
    if (processWorkCount > 0) {
        alert('<?= addslashes(text::get('RBF_ERROR_NEED_MIDDLE_EXPORT')) ?>');
        return false;
    }
    
    // Check if all works are COMPLETED
    if (notCompletedWorkCount > 0) {
        alert('<?= addslashes(text::get('RBF_ERROR_NOT_ALL_WORKS_COMPLETED')) ?>');
        return false;
    }
    
    // All validations passed - show confirmation
    if (confirm('<?= addslashes(text::get('RBF_CONFIRM_FINAL_EXPORT')) ?>')) {
        document.getElementsByName('export_action')[0].value='final';
        document.rbf_auto_works_form.submit();
        return false;
    }
    
    return false;
}

// Handle checkbox clicks for works with PROCESS status
document.addEventListener('DOMContentLoaded', function() {
    var checkboxes = document.querySelectorAll('.rbf-work-checkbox');
    
    checkboxes.forEach(function(checkbox) {
        checkbox.addEventListener('click', function(e) {
            var workStatus = this.getAttribute('data-work-status');
            
            // If work status is PROCESS and user tries to check, prevent and show error
            if (workStatus === 'PROCESS' && this.checked) {
                e.preventDefault();
                this.checked = false;
                alert('<?= addslashes(text::get('RBF_WORK_PROCESS_ERROR')) ?>');
                return false;
            }
        });
    });
});
</script>

