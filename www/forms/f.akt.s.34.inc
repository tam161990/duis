<?
// RBF Acts - Works Tab for Automatic Acts (RAKT_IS_AUTO = 1)
// This tab displays works imported from rbf_akta_darbi table

$userId = userAuthorization::getUserId();
$isAdmin = userAuthorization::isAdmin();
$isRbfUser = userAuthorization::isRbfUser();
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);

// act ID
$actId = reqVar::get('actId');

// Initialize variables
$works = false;
$worksFormatted = array();
$hasAccess = false;

// Check access permissions
if ($isAdmin || $isRbfUser || $isEconomist)
{
    $hasAccess = true;
    
    if($actId !== false)
    {
        // Get works from rbf_akta_darbi table with act number
        $works = dbProc::getRbfActWorks($actId);
        
        // Get reference codes for work statuses
        $workStatusCodes = dbProc::getKrfkName('WORK_STATUS');
        
        // Get act status from parent scope (set in f.akt.s.30.inc)
        $actStatus = isset($status) ? $status : '';
        
        // Process and format work data
        if ($works && count($works) > 0)
        {
            foreach ($works as $work)
            {
                $workFormatted = array();
                
                // Checkbox state logic:
                // - Checked if work is processed (RADR_IS_PROCESSED = 1)
                // - Disabled if:
                //   * Act status is not INSERT or RETURN
                //   * OR work has approve date
                //   * OR work status is NOTHING_TO_DO or CANT_DO
                // - Special handling for PROCESS status (show error on click)
                $isProcessed = ($work['RADR_IS_PROCESSED'] == 1);
                $isApproved = !empty($work['RADR_APPROVE_DATE']);
                $actStatusAllowsEdit = ($actStatus == STAT_INSERT || $actStatus == STAT_RETURN);
                $workStatus = $work['RADR_STATUS'];
                
                // Check if work status prevents selection
                $statusDisablesCheckbox = ($workStatus == 'NOTHING_TO_DO' || $workStatus == 'CANT_DO' || $workStatus == 'PROCESS');
                $statusIsProcess = ($workStatus == 'PROCESS');
                
                $workFormatted['checkbox_checked'] = $isProcessed ? 'checked="checked"' : '';
                $workFormatted['checkbox_disabled'] = (!$actStatusAllowsEdit || $isApproved || $statusDisablesCheckbox) ? 'disabled="disabled"' : '';
                $workFormatted['work_status_code'] = $workStatus;
                $workFormatted['is_process_status'] = $statusIsProcess;
                
                // Get status name from reference codes
                $workFormatted['status_name'] = isset($workStatusCodes[$work['RADR_STATUS']]) ? $workStatusCodes[$work['RADR_STATUS']] : $work['RADR_STATUS'];
                
                // Format plan date
                $workFormatted['plan_date'] = '';
                if (!empty($work['RADR_PLAN_DATE']))
                {
                    $workFormatted['plan_date'] = date('d.m.Y', strtotime($work['RADR_PLAN_DATE']));
                }
                
                // Format approve date
                $workFormatted['approve_date'] = '';
                if (!empty($work['RADR_APPROVE_DATE']))
                {
                    $workFormatted['approve_date'] = date('d.m.Y', strtotime($work['RADR_APPROVE_DATE']));
                }
                
                // Format norma
                $workFormatted['norma'] = number_format($work['RADR_NORMA'], 2, '.', '');
                
                // Copy raw data
                $workFormatted['order_number'] = htmlspecialchars($work['RAKT_NUM_POSTFIX']);
                $workFormatted['calc_code'] = htmlspecialchars($work['RADR_RBKL_SHIFRS']);
                $workFormatted['mms_code'] = htmlspecialchars($work['RADR_MMS_KODS']);
                $workFormatted['mms_title'] = htmlspecialchars($work['RADR_MMS_TITLE']);
                
                $worksFormatted[] = $workFormatted;
            }
        }
    }
}

// Include the template
include('f.akt.s.34.tpl');
?>
