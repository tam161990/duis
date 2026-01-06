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
            <td valign="top">
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
                                       class="rbf-work-checkbox" 
                                       data-work-status="<?= $work['work_status_code'] ?>" 
                                       <?= $work['checkbox_checked'] ?> 
                                       <?= $work['checkbox_disabled'] ?> />
                            </td>
                            <td><?= $work['order_number'] ?></td>
                            <td><?= $work['calc_code'] ?></td>
                            <td><?= $work['mms_code'] ?></td>
                            <td><?= $work['mms_title'] ?></td>
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
        </tr>
    </table>
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

