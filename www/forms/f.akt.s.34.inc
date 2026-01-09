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
$showExportButton = false;
$exportMessage = '';

// Check access permissions
if ($isAdmin || $isRbfUser || $isEconomist)
{
    $hasAccess = true;
    
    if($actId !== false)
    {
        // Handle export button submissions
        $exportAction = reqVar::get('export_action'); // 'final' or 'middle'
        
        if (!empty($exportAction))
        {
            $checkedWorks = reqVar::get('checked_works');
            
            // Validation: Check if works are selected
            if (empty($checkedWorks) || !is_array($checkedWorks) || count($checkedWorks) == 0)
            {
                $exportMessage = text::get('ERROR') . ': ' . text::get('NO_WORKS_SELECTED');
            }
            else
            {
                $isFinalExport = ($exportAction == 'final');
                $validationPassed = true;
                
                // Calculate act life period for validation
                $actLifePeriod = dbProc::getActLifePeriod($actId);
                if ($actLifePeriod === false)
                {
                    $actLifePeriod = 0;
                }
                
                // Validation based on export type
                if ($isFinalExport)
                {
                    // Final export validation: Check for PROCESS works
                    $processCount = dbProc::countWorksByStatus($actId, 'PROCESS');
                    if ($processCount > 0)
                    {
                        $exportMessage = text::get('RBF_ERROR_NEED_MIDDLE_EXPORT');
                        $validationPassed = false;
                    }
                    // Check if all works are COMPLETED
                    else
                    {
                        $notCompletedCount = dbProc::countWorksNotCompleted($actId);
                        if ($notCompletedCount > 0)
                        {
                            $exportMessage = text::get('RBF_ERROR_NOT_ALL_WORKS_COMPLETED');
                            $validationPassed = false;
                        }
                    }
                }
                else
                {
                    // Middle export validation: NOT allowed in period 3
                    if ($actLifePeriod == 3)
                    {
                        $exportMessage = text::get('RBF_ERROR_USE_FINAL_APPROVE');
                        $validationPassed = false;
                    }
                }
                
                // If validation passed, perform export
                if ($validationPassed)
                {
                    $result = dbProc::exportAutoActWorksToDarbi($actId, $checkedWorks, $userId, $isFinalExport, $actLifePeriod);
                    
                    if ($result['success'])
                    {
                        // Build success message
                        $insertedCount = $result['inserted_count'];
                        $successMessage = text::get('RBF_WORKS_EXPORTED_SUCCESS') . " ($insertedCount " . text::get('RBF_CALC_GROUPS') . ")";
                        
                        // Redirect back to act form with success message
                        $oLink = new urlQuery();
                        $oLink->addPrm(FORM_ID, 'f.akt.s.30');
                        $oLink->addPrm('actId', $actId);
                        $oLink->addPrm('tab', 'RBF_WORKS');
                        $oLink->addPrm('successMessage', $successMessage);
                        RequestHandler::makeRedirect($oLink->getQuery() . '#tab');
                    }
                    else
                    {
                        $exportMessage = text::get('ERROR') . ': ' . $result['message'];
                    }
                }
            }
        }
        
        // Get DARBI records for this act (exported works)
        $darbiRecords = dbProc::getDarbiByActId($actId);
        $darbiFormatted = array();
        
        if ($darbiRecords && count($darbiRecords) > 0)
        {
            foreach ($darbiRecords as $darbi)
            {
                $darbiFormatted[] = array(
                    'calc_code' => htmlspecialchars($darbi['DRBI_KKAL_SHIFRS']),
                    'calc_name' => htmlspecialchars($darbi['DRBI_KKAL_NOSAUKUMS']),
                    'writeoff_code' => htmlspecialchars($darbi['KWRC_KODS']),
                    'period_1' => number_format($darbi['PERIOD_1'], 2, '.', ''),
                    'period_2' => number_format($darbi['PERIOD_2'], 2, '.', ''),
                    'period_3' => number_format($darbi['PERIOD_3'], 2, '.', '')
                );
            }
        }
        
        // Get works from rbf_akta_darbi table with act number
        $works = dbProc::getRbfActWorks($actId);
        
        // Get act status from parent scope (set in f.akt.s.30.inc)
        $actStatus = isset($status) ? $status : '';
        
        // Calculate act life period
        $actLifePeriod = dbProc::getActLifePeriod($actId);
        
        // Show export buttons based on act status
        // Middle Export: periods 1-2 only
        // Final Export: any period (1, 2, or 3) - validates all works COMPLETED
        $actStatusAllowsExport = ($actStatus == STAT_INSERT || $actStatus == STAT_RETURN);
        $showMiddleExportButton = $actStatusAllowsExport && ($actLifePeriod < 3);
        $showFinalExportButton = $actStatusAllowsExport; // Always show if status allows
        
        // Count works by status for validation
        $processWorkCount = 0;
        $notCompletedWorkCount = 0;
        if ($works && count($works) > 0)
        {
            foreach ($works as $work)
            {
                if ($work['RADR_STATUS'] == 'PROCESS')
                {
                    $processWorkCount++;
                }
                if ($work['RADR_STATUS'] != 'COMPLETED')
                {
                    $notCompletedWorkCount++;
                }
            }
        }
        
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
                
                // Get status name using getKrfkInfoByName
                $statusInfo = dbProc::getKrfkInfoByName($work['RADR_STATUS']);
                $workFormatted['status_name'] = $statusInfo ? $statusInfo['KRFK_NOZIME'] : $work['RADR_STATUS'];
                
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
                $workFormatted['work_id'] = $work['RADR_ID'];
                $workFormatted['order_number'] = htmlspecialchars($work['RAKT_NUM_POSTFIX']);
                $workFormatted['calc_code'] = htmlspecialchars($work['RADR_RBKL_SHIFRS']);
                $workFormatted['mms_code'] = htmlspecialchars($work['RADR_MMS_KODS']);
                $workFormatted['mms_title'] = htmlspecialchars($work['RADR_MMS_TITLE']);
                $workFormatted['plan_date_raw'] = $work['RADR_PLAN_DATE'];
                $workFormatted['norma_raw'] = $work['RADR_NORMA'];
                
                $worksFormatted[] = $workFormatted;
            }
        }
    }
}

// ============================================================================
// Fetch DARBI summary for the summary table
// ============================================================================

$darbiSummary = dbProc::getDarbiSummaryByActId($actId);

// Calculate costs and totals for each period
$darbiFormatted = array();
$totals = array(
    'hours_1' => 0,
    'cost_1' => 0,
    'hours_2' => 0,
    'cost_2' => 0,
    'hours_3' => 0,
    'cost_3' => 0
);

if ($darbiSummary && is_array($darbiSummary)) {
    foreach ($darbiSummary as $item) {
        $price = floatval($item['DRBI_KKAL_NORMATIVS']);
        $hours1 = floatval($item['PERIOD_1_HOURS']);
        $hours2 = floatval($item['PERIOD_2_HOURS']);
        $hours3 = floatval($item['PERIOD_3_HOURS']);
        
        $cost1 = $price * $hours1;
        $cost2 = $price * $hours2;
        $cost3 = $price * $hours3;
        
        $darbiFormatted[] = array(
            'calc_code' => htmlspecialchars($item['DRBI_KKAL_SHIFRS']),
            'calc_name' => htmlspecialchars($item['DRBI_KKAL_NOSAUKUMS']),
            'price' => number_format($price, 2, '.', ''),
            'hours_1' => number_format($hours1, 2, '.', ''),
            'cost_1' => number_format($cost1, 2, '.', ''),
            'hours_2' => number_format($hours2, 2, '.', ''),
            'cost_2' => number_format($cost2, 2, '.', ''),
            'hours_3' => number_format($hours3, 2, '.', ''),
            'cost_3' => number_format($cost3, 2, '.', ''),
            'account_code' => htmlspecialchars($item['KWRC_KODS'] ? $item['KWRC_KODS'] : '')
        );
        
        $totals['hours_1'] += $hours1;
        $totals['cost_1'] += $cost1;
        $totals['hours_2'] += $hours2;
        $totals['cost_2'] += $cost2;
        $totals['hours_3'] += $hours3;
        $totals['cost_3'] += $cost3;
    }
}

// Calculate VAT (21%)
$vat1 = $totals['cost_1'] * 0.21;
$vat2 = $totals['cost_2'] * 0.21;
$vat3 = $totals['cost_3'] * 0.21;

// Calculate total with VAT
$totalWithVat1 = $totals['cost_1'] + $vat1;
$totalWithVat2 = $totals['cost_2'] + $vat2;
$totalWithVat3 = $totals['cost_3'] + $vat3;

// Format totals for display
$totalsFormatted = array(
    'hours_1' => number_format($totals['hours_1'], 2, '.', ''),
    'cost_1' => number_format($totals['cost_1'], 2, '.', ''),
    'hours_2' => number_format($totals['hours_2'], 2, '.', ''),
    'cost_2' => number_format($totals['cost_2'], 2, '.', ''),
    'hours_3' => number_format($totals['hours_3'], 2, '.', ''),
    'cost_3' => number_format($totals['cost_3'], 2, '.', ''),
    'vat_1' => number_format($vat1, 2, '.', ''),
    'vat_2' => number_format($vat2, 2, '.', ''),
    'vat_3' => number_format($vat3, 2, '.', ''),
    'total_with_vat_1' => number_format($totalWithVat1, 2, '.', ''),
    'total_with_vat_2' => number_format($totalWithVat2, 2, '.', ''),
    'total_with_vat_3' => number_format($totalWithVat3, 2, '.', '')
);

// Include the template
include('f.akt.s.34.tpl');
?>
