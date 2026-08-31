<?
// RBF Acts - Works Tab for Automatic Acts (RAKT_IS_AUTO = 1)
// This tab displays works imported from rbf_akta_darbi table

$userId = userAuthorization::getUserId();
$isAdmin = userAuthorization::isAdmin();
$isRbfUser = userAuthorization::isRbfUser();
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);

// act ID
$actId = reqVar::get('actId');
// search form
$isSearch = reqVar::get('isSearch');
// search act by number
$searchNum = reqVar::get('searchNum');

// Main form with XMLHTTP method load this code:
if (reqVar::get('xmlHttp') == 1)
{
    // if operation is DELETE, delete record from DB
    if (reqVar::get('deleteId') != '')
    {
       dbProc::deleteActWorkRecord(reqVar::get('deleteId'), 0); // tame=0 for RBF acts
    ?>
        rowNode = this.parentNode.parentNode;
        rowNode.parentNode.removeChild(rowNode);
    <?
    }
    exit();
}

// Helper: calculate period number based on custom month boundaries (27th to 26th)
if (!function_exists('rbfCalculatePeriodNumber')) {
    function rbfCalculatePeriodNumber($dateString)
    {
        $date = new DateTime($dateString);
        $year = (int)$date->format('Y');
        $month = (int)$date->format('m');
        $day = (int)$date->format('d');

        if ($day >= 27) {
            $periodYear = $year;
            $periodMonth = $month;
        } else {
            if ($month == 1) {
                $periodYear = $year - 1;
                $periodMonth = 12;
            } else {
                $periodYear = $year;
                $periodMonth = $month - 1;
            }
        }

        return ($periodYear * 12) + $periodMonth;
    }
}

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
        // Get act info for permission checks
        $act = array();
        $status = false;
        $actInfo = dbProc::getRbfActInfo($actId);
        if(count($actInfo) > 0)
        {
            $act = $actInfo;
            $status = $act['RAKT_STATUS'];
        }

        $isReadonly = true;
        // Edit access: if act is in "Ievads" (INSERT) or "Atgriezts" (RETURN) status and user is the author or admin
        if((($act['RAKT_RLTT_ID'] == $userId && $isRbfUser) || $isAdmin) && 
          ($status == STAT_INSERT || $status == STAT_RETURN))
        {
          $isReadonly = false;
        }
        
        // Create form for manual works section
        $oLink = new urlQuery();
        $oLink->addPrm(FORM_ID, 'f.akt.s.30');
        $oLink->addPrm('actId', $actId);
        $oLink->addPrm('tab', 'RBF_WORKS');
        $oLink->addPrm('isSearch', $isSearch);
        $oLink->addPrm('searchNum', $searchNum);
        $oFormManualWorks = new Form('frmRbfManualWorkTab', 'post', $oLink->getQuery() . '#tab');
        unset($oLink);

        // if operation is success, show success message
        if (reqVar::get('successMessageTab'))
        {
            $oFormManualWorks->addSuccess(reqVar::get('successMessageTab'));
        }

        $aManualWorks = array();
        $aManualWorkExist = false;
        
        // Handle manual works save
        if ($oFormManualWorks->isFormSubmitted() && $oFormManualWorks->getValue('action') == 'save_manual_works')
        {
            $isRowValid = true;
            $aChiphers = $oFormManualWorks->getValue('chipher');
            
            if(is_array($aChiphers))
            {
              $aWorkFr = array();
              foreach ($aChiphers as $i => $val)
              {
                   $aWorkFr[$i]['DRBI_ID'] = $oFormManualWorks->getValue('id['.$i.']');
                   $aWorkFr[$i]['DRBI_KKAL_ID'] = $oFormManualWorks->getValue('kid['.$i.']');
                   $aWorkFr[$i]['DRBI_KKAL_SHIFRS'] = $oFormManualWorks->getValue('chipher['.$i.']');
                   $aWorkFr[$i]['DRBI_KKAL_NOSAUKUMS'] = $oFormManualWorks->getValue('title['.$i.']');
                   $aWorkFr[$i]['DRBI_KKAL_NORMATIVS'] = $oFormManualWorks->getValue('standart['.$i.']');
                   $aWorkFr[$i]['DRBI_MERVIENIBA'] = $oFormManualWorks->getValue('measure['.$i.']');
                   $aWorkFr[$i]['DRBI_PLAN_DATE'] = $oFormManualWorks->getValue('plan_date['.$i.']');
                   $aWorkFr[$i]['KKAL_APRAKSTS'] = $oFormManualWorks->getValue('description['.$i.']');
                   $aWorkFr[$i]['DRBI_DAUDZUMS'] = $oFormManualWorks->getValue('amount['.$i.']');
                   // Calculate total as price * amount
                   $aWorkFr[$i]['DRBI_CILVEKSTUNDAS'] = $aWorkFr[$i]['DRBI_KKAL_NORMATIVS'] * $aWorkFr[$i]['DRBI_DAUDZUMS'];

                   // Validate amount
                   if (empty($aWorkFr[$i]['DRBI_DAUDZUMS']) || $aWorkFr[$i]['DRBI_DAUDZUMS'] <= 0)
                   {
                       $oFormManualWorks->addErrorPerElem('amount['.$i.']', text::get('ERROR_REQUIRED_FIELD'));
                       $isRowValid = false;
                   }

                   // Validate plan date
                   if (empty($aWorkFr[$i]['DRBI_PLAN_DATE']))
                   {
                       $oFormManualWorks->addErrorPerElem('plan_date['.$i.']', text::get('ERROR_REQUIRED_FIELD'));
                       $isRowValid = false;
                   }
              }

              // Save if valid
              if ($isRowValid)
              {
                  // Delete all existing manual work records (DRBI_IS_WORKER = 1)
                  $r = dbProc::deleteManualActWorks($actId, 0); // tame=0 for RBF acts
                  
                  if ($r === false)
                  {
                      $oFormManualWorks->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                  }
                  else
                  {
                      // Pre-calculate act period values for DRBI_ACT_QUART
                      $actLifePeriod = dbProc::getActLifePeriod($actId);
                      if ($actLifePeriod === false) {
                          $actLifePeriod = 1;
                      }
                      $actDate = isset($act['RAKT_DATUMS']) ? $act['RAKT_DATUMS'] : false;
                      $actPeriod = $actDate ? rbfCalculatePeriodNumber($actDate) : false;

                      // Re-insert all manual work records
                      foreach($aWorkFr as $i => $work)
                      {
                          $actQuart = $actLifePeriod;
                          if ($actPeriod !== false && !empty($work['DRBI_PLAN_DATE'])) {
                              $planDate = dbLayer::parseDate($work['DRBI_PLAN_DATE']);
                              $planPeriod = rbfCalculatePeriodNumber($planDate . ' 00:00:00');
                              $calculatedQuart = ($planPeriod - $actPeriod) + 1;
                              if ($calculatedQuart >= 1 && $calculatedQuart <= $actLifePeriod) {
                                  $actQuart = $calculatedQuart;
                              }
                          }
                          
                          $r = dbProc::writeActWork(
                              $actId,
                              $work['DRBI_KKAL_ID'],
                              $work['DRBI_KKAL_SHIFRS'],
                              $work['DRBI_KKAL_NOSAUKUMS'],
                              $work['DRBI_KKAL_NORMATIVS'],
                              $work['DRBI_DAUDZUMS'],
                              $work['DRBI_CILVEKSTUNDAS'], // total
                              $work['DRBI_MERVIENIBA'],
                              false, // amount_kor (not used for RBF)
                              false, // edited
                              $work['DRBI_PLAN_DATE'],
                              false, // day_total (not used for RBF)
                              false, // notes
                              1,     // st (is_worker) = 1 for manual works
                              false, // work_type
                              false, // work_type_text
                              false, // export_type
                              false, // work_approve_date
                              false, // import_no
                              $actQuart
                          );
                          
                          if($r === false)
                          {
                              $oFormManualWorks->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                              break;
                          }
                      }
                      
                      if($r !== false)
                      {
                          $oLink = new urlQuery();
                          $oLink->addPrm(FORM_ID, 'f.akt.s.30');
                          $oLink->addPrm('actId', $actId);
                          $oLink->addPrm('tab', 'RBF_WORKS');
                          $oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));
                          RequestHandler::makeRedirect($oLink->getQuery() . '#tab');
                      }
                  }
              }
            }
        }

        // Get manual work list from DB (DRBI_IS_WORKER = 1)
        // Parameters: $ID, $tame, $onlyNotApproved, $group_id, $project, $work_type_text, $sortOrder, $orderColumn, $manualOnly
        $aManualWorkDb = dbProc::getActWorkList($actId, 0, false, false, false, false, false, false, true);

        if (is_array($aManualWorkDb) && count($aManualWorkDb) > 0)
        {
            $aManualWorkExist = true;
            $k = 0;
            
            foreach ($aManualWorkDb as $i => $row)
            {
                $aManualWorks[$i] = $row;

                // ID
                $oFormManualWorks->addElement('hidden', 'id['.$k.']', '', $row['DRBI_ID']);
                $oFormManualWorks->addElement('hidden', 'kid['.$k.']', '', $row['DRBI_KKAL_ID']);
                $oFormManualWorks->addElement('hidden', 'description['.$k.']', '', $row['KKAL_APRAKSTS']);

                // Chipher (Šifrs) - always readonly
                $oFormManualWorks->addElement('label', 'chipher['.$k.']', '', $row['DRBI_KKAL_SHIFRS']);

                // Plan date (Izpildes datums) - editable when not readonly
                if(!$isReadonly)
                {
                    $oFormManualWorks->addElement('date', 'plan_date['.$k.']', '', $row['DRBI_PLAN_DATE'], (($isReadonly)?' disabled ':''));
                    $oFormManualWorks->addRule('plan_date['.$k.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
                    $oFormManualWorks->addRule('plan_date['.$k.']', text::get('ERROR_INCORRECT_DATE'),'validatedate');
                }
                else
                {
                    $oFormManualWorks->addElement('label', 'plan_date['.$k.']', '', $row['DRBI_PLAN_DATE']);
                }

                // Title (Nosaukums) - always readonly
                $oFormManualWorks->addElement('label', 'title['.$k.']', '', $row['DRBI_KKAL_NOSAUKUMS']);

                // Price (Cena) - always readonly
                $oFormManualWorks->addElement('hidden', 'standart['.$k.']', '', $row['DRBI_KKAL_NORMATIVS']);
                $oFormManualWorks->addElement('label', 'standart_display['.$k.']', '', number_format($row['DRBI_KKAL_NORMATIVS'], 2, '.', ' '));

                // Unit of measure (Mērvienība) - always readonly
                $oFormManualWorks->addElement('label', 'measure['.$k.']', '', $row['DRBI_MERVIENIBA']);

                // Total (Summa) - calculate BEFORE formatting amount
                $total = $row['DRBI_KKAL_NORMATIVS'] * $row['DRBI_DAUDZUMS'];
                
                // Amount (Daudzums) - editable when not readonly
                $amountFormatted = number_format($row['DRBI_DAUDZUMS'], 3, '.', '');
                $oFormManualWorks->addElement('text', 'amount['.$k.']', '', $amountFormatted, (($isReadonly)?' disabled ':'').'maxlength="9"');
                $oFormManualWorks->addRule('amount['.$k.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
                $oFormManualWorks->addRule('amount['.$k.']', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);

                // Total (Summa) - always readonly, display calculated value
                $oFormManualWorks->addElement('label', 'total['.$k.']', '', number_format($total, 2, '.', ' '));

                // Work norm (c.st. norma) - for admins only, always readonly
                if($isAdmin)
                {
                    $workNorm = isset($row['KKNO_NORM']) ? $row['KKNO_NORM'] : '';
                    $oFormManualWorks->addElement('label', 'work_norm['.$k.']', '', $workNorm);

                    // Work norm sum (c.st. summa)
                    $workNormSum = isset($row['WORK_NORM_SUM']) ? $row['WORK_NORM_SUM'] : 0;
                    $oFormManualWorks->addElement('label', 'work_norm_sum['.$k.']', '', number_format($workNormSum, 2, '.', ''));
                }

                // Write off account (Izmaksu konts) - always readonly                '
                $kwrcCode = (($act['RAKT_KAKV_ID'] == ACT_TYPE_STIHIJA_ID) ?
                    '71882' :
                        (($act['RAKT_KAKV_ID'] == ACT_TYPE_PERS_ID)? 
                            '71889' : $row['KWRC_KODS']));
                $oFormManualWorks->addElement('label', 'write_off_code['.$k.']', '', $kwrcCode);

                // Element (Stihija) - always readonly label showing YES/NO
                $elementText = ($act['RAKT_KAKV_ID'] == ACT_TYPE_STIHIJA_ID) ? text::get('YES'): text::get('NO');                
                $oFormManualWorks->addElement('label', 'act_element['.$k.']', '', $elementText);

                // Pers - always readonly label showing YES/NO
                $persText = ($act['RAKT_KAKV_ID'] == ACT_TYPE_PERS_ID) ? text::get('YES'): text::get('NO');
                $oFormManualWorks->addElement('label', 'act_pers['.$k.']', '', $persText);

                // Delete button
                if(!$isReadonly)
                {
                    $delLink = new urlQuery();
                    $delLink->addPrm(FORM_ID, 'f.akt.s.34');
                    $delLink->addPrm(DONT_USE_GLB_TPL, '1');
                    $delLink->addPrm('actId', $actId);
                    $delLink->addPrm('xmlHttp', '1');
                    $delLink->addPrm('isSearch', $isSearch);
                    $delLink->addPrm('searchNum', $searchNum);

                    $delButtonJs = "if(isDelete()) { 
                        var rowId = document.forms['frmRbfManualWorkTab']['id[" .$k. "]'];
                        eval(xmlHttpGetValue('" .$delLink->getQuery() ."&deleteId='+rowId.value));
                      }";
                
                    $oFormManualWorks->addElement('button', 'work_del['.$k.']', '', '', 'onclick="' . $delButtonJs . ';return false;" style="background: url(img/ico_del.gif); cursor:hand; border:0px; width: 20px; height: 20px;" title="' . text::get('DELETE') . '"');
                    unset($delLink);
                }

                $k++;
            }
        }

        // Add hidden action field
        $oFormManualWorks->addElement('hidden', 'action', '');

        // Save button - for manual works
        if(!$isReadonly && $aManualWorkExist)
        {
            $oFormManualWorks->addElement('submitImg', 'save_manual', text::get('SAVE'), 'img/btn_save_work.gif', 'width="120" height="20" onclick="document.forms[\'frmRbfManualWorkTab\'][\'action\'].value=\'save_manual_works\';return true;"');
        }

        // Add ALL_WORK link for manual works section and calculate totals
        $manualWorksTotal = 0; // Total of all manual works (for manual works table)
        $manualWorksApprovedTotal = 0; // Total of only approved manual works (for summary table - all quarters)
        $manualWorksApprovedByQuarter = array(1 => 0, 2 => 0, 3 => 0); // Approved manual works by quarter
        $actLifePeriod = dbProc::getActLifePeriod($actId);
        if ($actLifePeriod === false) {
            $actLifePeriod = 0;
        }
        $isFinalExportAct = !empty($act['RAKT_IR_OBJEKTS_PABEIGTS']);
        $forceManualWorksToPeriod = ($isFinalExportAct || $actLifePeriod == 3) ? $actLifePeriod : false;
        
       
            $oPopLinkManual = new urlQuery;
            $oPopLinkManual->addPrm(FORM_ID, 'f.akt.s.33');
            $oPopLinkManual->addPrm('actId', $actId);
            
            $allWorkLinkManual = array();
            $allWorkLinkManual['TITLE'] = text::get('ALL_WORK');
            $allWorkLinkManual['URL'] = RequestHandler::popupHref($oPopLinkManual->getQuery().'&all=1', false, 700, 450, true, false, true);
            
            unset($oPopLinkManual);
            if($aManualWorkExist)
            {    
            // Calculate manual works totals
            foreach ($aManualWorks as $work) {
                $workTotal = $work['DRBI_KKAL_NORMATIVS'] * $work['DRBI_DAUDZUMS'];
                $manualWorksTotal += $workTotal;
                
                // Only add to approved total if work has approve date
                if (!empty($work['DRBI_WORK_APROVE_DATE'])) {
                    $manualWorksApprovedTotal += $workTotal;
                    
                    // Add to appropriate quarter total
                    if ($forceManualWorksToPeriod !== false) {
                        if ($forceManualWorksToPeriod >= 1 && $forceManualWorksToPeriod <= 3) {
                            $manualWorksApprovedByQuarter[$forceManualWorksToPeriod] += $workTotal;
                        }
                    } else {
                        $quarter = isset($work['DRBI_ACT_QUART']) ? intval($work['DRBI_ACT_QUART']) : 1;
                        if ($quarter >= 1 && $quarter <= 3) {
                            $manualWorksApprovedByQuarter[$quarter] += $workTotal;
                        }
                    }
                }
            }
        }
        
        // Fallback for period 3: if works should be approved but totals are empty, show total in period 3
        if ($forceManualWorksToPeriod !== false
            && $manualWorksApprovedTotal == 0
            && $manualWorksTotal > 0
            && $actLifePeriod == 3
            && $status != STAT_INSERT
            && $status != STAT_RETURN) {
            $manualWorksApprovedByQuarter[$forceManualWorksToPeriod] = $manualWorksTotal;
        }
        
        // Render the manual works form
        $oFormManualWorks->makeHtml();
        
        // Handle export button submissions
        $exportAction = reqVar::get('export_action'); // 'final' or 'middle'
        
        if (!empty($exportAction))
        {
            $checkedWorks = reqVar::get('checked_works');
            
            // Check if we have manual works to export (they don't require checkboxes)
            $hasManualWorksToExport = ($aManualWorkExist && count($aManualWorks) > 0);
            
            // Validation: Check if works are selected OR if we have manual works
            if ((empty($checkedWorks) || !is_array($checkedWorks) || count($checkedWorks) == 0) && !$hasManualWorksToExport)
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
                    // Export auto works if any are selected
                    if (!empty($checkedWorks) && is_array($checkedWorks) && count($checkedWorks) > 0)
                    {
                        $result = dbProc::exportAutoActWorksToDarbi($actId, $checkedWorks, $userId, $isFinalExport, $actLifePeriod);
                        
                        if (!$result['success'])
                        {
                            $exportMessage = text::get('ERROR') . ': ' . $result['message'];
                            $validationPassed = false;
                        }
                    }
                    
                    // If auto works export succeeded (or there were no auto works to export), change act status
                    if ($validationPassed)
                    {
                        // Update act status to ACCEPT
                        $r = dbProc::updateRbfActStatus($actId, STAT_ACCEPT, $userId);
                        
                        // Save user action
                        dbProc::setUserActionDate($userId, ACT_EXPORT);
                        
                        // Finalize the object
                        dbProc::closeObject($actId, 1);
                        
                        if ($r !== false)
                        {
                            $oldStatus = STAT_INSERT;
                            // Send email notification about status change
                            email::sendRbfActStatusChangeNotification($actId, $oldStatus, STAT_ACCEPT, $userId);
                    
                            // Build and set flash message (will show once after redirect)
                            $successMessage = text::get('ACT_SUBMITTED_FOR_APPROVAL');
                            session::setFlash('successMessage', $successMessage);
                            
                            // Redirect back to act form
                            $oLink = new urlQuery();
                            $oLink->addPrm(FORM_ID, 'f.akt.s.30');
                            $oLink->addPrm('actId', $actId);
                            $oLink->addPrm('tab', 'RBF_WORKS');
                            RequestHandler::makeRedirect($oLink->getQuery() . '#tab');
                        }
                        else
                        {
                            $exportMessage = text::get('ERROR_IN_DB_QUERY') . dbProc::getError();
                        }
                    }
                }
            }
        }
        
        // Popup link preparation for ALL_WORK
        $oPopLink = new urlQuery;
        $oPopLink->addPrm(FORM_ID, 'f.akt.s.33');
        $oPopLink->addPrm('actId', $actId);
        
        // Single link - ALL_WORK
        $allWorkLink = array();
        $allWorkLink['TITLE'] = text::get('ALL_WORK');
        $allWorkLink['URL'] = RequestHandler::popupHref($oPopLink->getQuery().'&all=1', false, 700, 450, true, false, true);
        
        unset($oPopLink);
        
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
        
        // Calculate act life period (already set for manual works totals if available)
        if (!isset($actLifePeriod) || $actLifePeriod === null) {
            $actLifePeriod = dbProc::getActLifePeriod($actId);
        }
        
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
                
                // Format new columns (Mērvienība, Apjoms, C.st. norma)
                $workFormatted['mervieniba'] = !empty($work['RADR_MERVIENIBA']) ? htmlspecialchars($work['RADR_MERVIENIBA']) : '';
                $workFormatted['apjoms'] = !empty($work['RADR_APJOMS']) ? number_format($work['RADR_APJOMS'], 2, '.', '') : '';
                $workFormatted['cst_norma'] = !empty($work['RADR_CST_NORMA']) ? number_format($work['RADR_CST_NORMA'], 2, '.', '') : '';
                
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
                $workFormatted['mervieniba_raw'] = $work['RADR_MERVIENIBA'];
                $workFormatted['apjoms_raw'] = $work['RADR_APJOMS'];
                $workFormatted['cst_norma_raw'] = $work['RADR_CST_NORMA'];
                
                $worksFormatted[] = $workFormatted;
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

        
        // Element (Stihija) - always readonly label showing YES/NO
        $elementText = ($act['RAKT_KAKV_ID'] == ACT_TYPE_STIHIJA_ID) ? text::get('YES'): text::get('NO'); 
        // Pers - always readonly label showing YES/NO
        $persText = ($act['RAKT_KAKV_ID'] == ACT_TYPE_PERS_ID) ? text::get('YES'): text::get('NO');

        if ($darbiSummary && is_array($darbiSummary)) {
            foreach ($darbiSummary as $item) {
                $price = floatval($item['DRBI_KKAL_NORMATIVS']);
                $hours1 = floatval($item['PERIOD_1_HOURS']);
                $hours2 = floatval($item['PERIOD_2_HOURS']);
                $hours3 = floatval($item['PERIOD_3_HOURS']);
                
                $cost1 = $price * $hours1;
                $cost2 = $price * $hours2;
                $cost3 = $price * $hours3;

                // Write off account (Izmaksu konts) - always readonly                '
                $kwrcCode = (($act['RAKT_KAKV_ID'] == ACT_TYPE_STIHIJA_ID) ?
                '71882' :
                    (($act['RAKT_KAKV_ID'] == ACT_TYPE_PERS_ID)? 
                        '71889' : $item['KWRC_KODS']));
                
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
                    'account_code' => htmlspecialchars($kwrcCode ? $kwrcCode : ''),
                    'act_element' => htmlspecialchars($elementText),
                    'act_pers' => htmlspecialchars($persText)
                );
                
                $totals['hours_1'] += $hours1;
                $totals['cost_1'] += $cost1;
                $totals['hours_2'] += $hours2;
                $totals['cost_2'] += $cost2;
                $totals['hours_3'] += $hours3;
                $totals['cost_3'] += $cost3;
            }
        }

        // Calculate VAT (21%) on auto works + manual works (approved)
        $manualCost1 = isset($manualWorksApprovedByQuarter[1]) ? $manualWorksApprovedByQuarter[1] : 0;
        $manualCost2 = isset($manualWorksApprovedByQuarter[2]) ? $manualWorksApprovedByQuarter[2] : 0;
        $manualCost3 = isset($manualWorksApprovedByQuarter[3]) ? $manualWorksApprovedByQuarter[3] : 0;

        $vatBase1 = $totals['cost_1'] + $manualCost1;
        $vatBase2 = $totals['cost_2'] + $manualCost2;
        $vatBase3 = $totals['cost_3'] + $manualCost3;

        $vat1 = $vatBase1 * 0.21;
        $vat2 = $vatBase2 * 0.21;
        $vat3 = $vatBase3 * 0.21;

        // Calculate total with VAT (auto + manual)
        $totalWithVat1 = $vatBase1 + $vat1;
        $totalWithVat2 = $vatBase2 + $vat2;
        $totalWithVat3 = $vatBase3 + $vat3;

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
    }
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>
