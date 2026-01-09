<?php
/**
 * Automatic RBF Acts and Works Processing Script
 * 
 * This script performs two main operations:
 * 
 * PART 1: Process Acts
 * - Reads pending records from rbf_akti table (FAKT_PROCESSED = 0)
 * - Validates all required data (employee, VV, territory, author, act type)
 * - Creates automatic RBF acts in AKTI table (RAKT_IS_AUTO = 1, RAKT_IS_RBF = 1)
 * - Marks processed acts as FAKT_PROCESSED = 1
 * 
 * PART 2: Process Works
 * - Reads all work records from rbf_akta_darbi_tmp table
 * - Groups works by Order ID (act number)
 * - For each work:
 *   - Validates calculation code in kl_rbf_kalkulacija
 *   - Finds related act in AKTI by RAKT_NUM_POSTFIX
 *   - Checks if work exists in rbf_akta_darbi:
 *     * If exists AND processed (RADR_IS_PROCESSED=1) → Skip
 *     * If exists AND not processed → Update status & plan_date only
 *     * If not exists → Insert new work record
 * - Logs all operations grouped by act for easy tracking
 * 
 * Usage: php autoProc/createRBFacts.php
 * 
 * Future: Will be scheduled to run automatically at night
 */

// Include necessary files
require_once(dirname(__FILE__).'/../config/main.conf.php');
require_once(dirname(__FILE__).'/../libs/requestHandler/requestHandler.class');
require_once(dirname(__FILE__).'/../libs/dbLayer/dbLayer.class');
require_once(dirname(__FILE__).'/../libs/dbProc/dbProc.class');
require_once(dirname(__FILE__).'/../libs/files/files.class');


// Log start
$startTime = date('Y-m-d H:i:s');
files::wh_log("========================================");
files::wh_log("[START] RBF Automatic Act Creation - $startTime");
files::wh_log("========================================");

// Get pending acts
$pendingActs = dbProc::getPendingRbfAkts();

// Process statistics
$successCount = 0;
$errorCount = 0;
$errors = array();

if (!$pendingActs || count($pendingActs) == 0) {
    files::wh_log("[INFO] No pending acts to process");
} else {
    files::wh_log("[INFO] Found " . count($pendingActs) . " pending act(s) to process");
    
    // Process each pending act
    foreach ($pendingActs as $faktAct) {
    $faktId = $faktAct['FAKT_ID'];
    $faktNumPostfix = $faktAct['FAKT_NUM_POSTFIX'];
    
    files::wh_log("");
    files::wh_log("--- Processing FAKT_ID: $faktId (Pasūtījuma ID: $faktNumPostfix) ---");
    
    $hasErrors = false;
    $actErrors = array();
    
    // 1. Validate required fields
    if (empty($faktAct['FAKT_NUM_POSTFIX'])) {
        $error = "[ERROR] FAKT_ID $faktId: FAKT_NUM_POSTFIX is empty";
        files::wh_log($error);
        $actErrors[] = $error;
        $hasErrors = true;
    }
    
    if (empty($faktAct['FAKT_WORK_TITLE'])) {
        $error = "[ERROR] FAKT_ID $faktId: FAKT_WORK_TITLE is empty";
        files::wh_log($error);
        $actErrors[] = $error;
        $hasErrors = true;
    }
    
    // 2. Validate employee code
    if (!dbProc::validateRbfEmployeeCode($faktAct['FAKT_KWOI_KODS'])) {
        $error = "[ERROR] FAKT_ID $faktId: FAKT_KWOI_KODS '{$faktAct['FAKT_KWOI_KODS']}' not found in kl_rbf_darbuznemeji.RBDU_KODS";
        files::wh_log($error);
        $actErrors[] = $error;
        $hasErrors = true;
    }
    
    // 3. Validate VV number for employee
    if (!dbProc::validateVVNumberForEmployee($faktAct['FAKT_VV_NUMBER'], $faktAct['FAKT_KWOI_KODS'])) {
        $error = "[ERROR] FAKT_ID $faktId: FAKT_VV_NUMBER '{$faktAct['FAKT_VV_NUMBER']}' not found for employee '{$faktAct['FAKT_KWOI_KODS']}' in kl_rbf_du_vv";
        files::wh_log($error);
        $actErrors[] = $error;
        $hasErrors = true;
    }
    
    // 4. Validate territory code for VV
    if (!dbProc::validateTerritoryForVV($faktAct['FAKT_RBTR_KODS'], $faktAct['FAKT_VV_NUMBER'])) {
        $error = "[ERROR] FAKT_ID $faktId: FAKT_RBTR_KODS '{$faktAct['FAKT_RBTR_KODS']}' not found for VV '{$faktAct['FAKT_VV_NUMBER']}' in kl_rbf_teritorijas";
        files::wh_log($error);
        $actErrors[] = $error;
        $hasErrors = true;
    }
    
    // 5. Find user ID by name and validate relationship to employee
    $userInfo = dbProc::findUserByNameForEmployee($faktAct['FAKT_RLTT_TEXT'], $faktAct['FAKT_KWOI_KODS']);
    $authorId = 0;
    
    if ($userInfo === false) {
        $error = "[ERROR] FAKT_ID $faktId: User '{$faktAct['FAKT_RLTT_TEXT']}' not found in LIETOTAJI. Setting RAKT_RLTT_ID = 0";
        files::wh_log($error);
        $actErrors[] = $error;
    } else {
        $authorId = $userInfo['RLTT_ID'];
        
        // Check if user belongs to the employee
        if (!$userInfo['belongs_to_employee']) {
            $error = "[ERROR] FAKT_ID $faktId: User '{$faktAct['FAKT_RLTT_TEXT']}' (ID: {$authorId}, KWOI: {$userInfo['RLTT_KWOI_KODS']}) is not related to employee '{$faktAct['FAKT_KWOI_KODS']}'. Setting RAKT_RLTT_ID = 0";
            files::wh_log($error);
            $actErrors[] = $error;
            $authorId = 0;
        } else {
            files::wh_log("[INFO] Found user ID: $authorId for '{$faktAct['FAKT_RLTT_TEXT']}' (belongs to employee {$faktAct['FAKT_KWOI_KODS']})");
        }
    }
    
    // 6. Find act type ID by code
    $actTypeId = dbProc::findActTypeIdByCode($faktAct['FAKT_KAKV_KODS']);
    if ($actTypeId === false) {
        $error = "[ERROR] FAKT_ID $faktId: Act type code '{$faktAct['FAKT_KAKV_KODS']}' not found in kl_akta_veids. Setting RAKT_KAKV_ID = 0";
        files::wh_log($error);
        $actErrors[] = $error;
        $actTypeId = 0;
        // This is not a blocking error, we set it to 0 and continue
    } else {
        files::wh_log("[INFO] Found act type ID: $actTypeId for code '{$faktAct['FAKT_KAKV_KODS']}'");
    }
    
    // 7. Find territory ID by code
    $departmentId = dbProc::findRbfTerritoryIdByCode($faktAct['FAKT_RBTR_KODS']);
    if ($departmentId === false) {
        $error = "[ERROR] FAKT_ID $faktId: Territory code '{$faktAct['FAKT_RBTR_KODS']}' not found in kl_rbf_teritorijas";
        files::wh_log($error);
        $actErrors[] = $error;
        $hasErrors = true;
    } else {
        files::wh_log("[INFO] Found department ID: $departmentId for code '{$faktAct['FAKT_RBTR_KODS']}'");
    }
    
    // If we have blocking errors, skip this record
    if ($hasErrors) {
        files::wh_log("[FAILED] FAKT_ID $faktId: Skipped due to validation errors");
        $errorCount++;
        $errors = array_merge($errors, $actErrors);
        continue;
    }
    
    // 8. Create automatic RBF act in AKTI table
    files::wh_log("[INFO] Creating automatic act in AKTI table...");
    
    $createdActId = dbProc::createAutomaticRbfAct(
        $faktAct['FAKT_KWOI_KODS'],      // employeeCode
        $authorId,                         // authorId (0 if not found)
        $faktAct['FAKT_VV_NUMBER'],       // vvNumber
        $actTypeId,                        // actTypeId (0 if not found)
        $departmentId,                     // departmentId
        $faktAct['FAKT_NUM_POSTFIX'],     // orderId
        $faktAct['FAKT_WORK_TITLE'],      // workTitle
        $faktAct['FAKT_PIEZIMES'],        // notes
        $faktAct['FAKT_SIGNATURE'],       // signature (E/P/K) - optional
        STAT_INSERT                        // status (INSERT)
    );
    
    if ($createdActId === false) {
        $error = "[ERROR] FAKT_ID $faktId: Failed to create act in AKTI table";
        files::wh_log($error);
        $actErrors[] = $error;
        $errorCount++;
        $errors = array_merge($errors, $actErrors);
        continue;
    }
    
    files::wh_log("[SUCCESS] Created RAKT_ID: $createdActId (RAKT_IS_AUTO=1, RAKT_IS_RBF=1)");
    
    // 9. Save audit records (user action and status change)
    $systemUserId = 197; // System user ID for automatic processes
    dbProc::setUserActionDate($systemUserId, ACT_INSERT);
    dbProc::updateRbfActStatus($createdActId, STAT_INSERT, $systemUserId);
    files::wh_log("[INFO] Audit records saved for RAKT_ID: $createdActId (User: $systemUserId, Status: INSERT)");
    
    // Send email notification about new act creation
    email::sendRbfActStatusChangeNotification($createdActId, null, STAT_INSERT, $systemUserId);
    files::wh_log("[INFO] Email notification sent for new act RAKT_ID: $createdActId");
    
    // 10. Mark as processed
    $marked = dbProc::markRbfAktProcessed($faktId);
    if (!$marked) {
        files::wh_log("[WARNING] Failed to mark FAKT_ID $faktId as processed in rbf_akti table");
    } else {
        files::wh_log("[INFO] Marked FAKT_ID $faktId as processed (FAKT_PROCESSED=1)");
    }
    
    $successCount++;
    
    // Log any non-blocking errors (like user not found, act type not found)
    if (count($actErrors) > 0) {
        files::wh_log("[NOTE] Act created with warnings:");
        foreach ($actErrors as $actError) {
            files::wh_log("  " . $actError);
        }
        $errors = array_merge($errors, $actErrors);
    }
} // End foreach ($pendingActs as $faktAct)
} // End else (pending acts found)

// ============================================================================
// STEP 2: Process Work Records from rbf_akta_darbi_tmp
// ============================================================================

files::wh_log("");
files::wh_log("========================================");
files::wh_log("[START] Processing Work Records from rbf_akta_darbi_tmp");
files::wh_log("========================================");

$workRecords = dbProc::getWorkRecordsFromTemp();

if (!$workRecords || count($workRecords) == 0) {
    files::wh_log("[INFO] No work records to process in rbf_akta_darbi_tmp");
} else {
    files::wh_log("[INFO] Found " . count($workRecords) . " work record(s) to process");
    
    // Work statistics
    $workInsertCount = 0;
    $workUpdateCount = 0;
    $workSkipCount = 0;
    $workErrorCount = 0;
    $workErrors = array();
    
    // Group works by act (Order ID)
    $worksByAct = array();
    foreach ($workRecords as $work) {
        $orderId = $work['FADR_NUM_POSTFIX'];
        if (!isset($worksByAct[$orderId])) {
            $worksByAct[$orderId] = array();
        }
        $worksByAct[$orderId][] = $work;
    }
    
    // Process works grouped by act
    foreach ($worksByAct as $orderId => $works) {
        files::wh_log("");
        files::wh_log("--- Processing Works for Order ID: $orderId ---");
        
        // Get act ID by Order ID
        $actInfo = dbProc::getActIdByPostfix($orderId);
        
        if ($actInfo === false) {
            $error = "[ERROR] Order ID '$orderId': Act not found in AKTI table (RAKT_NUM_POSTFIX). Skipping " . count($works) . " work(s).";
            files::wh_log($error);
            $workErrors[] = $error;
            $workErrorCount += count($works);
            continue;
        }
        
        $raktId = $actInfo['RAKT_ID'];
        $raktFullNumber = $actInfo['RAKT_FULL_NUMBER'];
        files::wh_log("[INFO] Found Act: $raktFullNumber (RAKT_ID: $raktId)");
        
        // Process each work for this act
        foreach ($works as $work) {
            $rbklShifrs = $work['FADR_RBKL_SHIFRS'];
            $mmsKods = $work['FADR_MMS_KODS'];
            $mmsTitle = $work['FADR_MMS_TITLE'];
            $status = $work['FADR_STATUS'];
            $planDate = $work['FADR_PLAN_DATE'];
            $norma = $work['FADR_NORMA'];
            
            // Validate calculation code exists
            if (!dbProc::validateRbfCalculationCode($rbklShifrs)) {
                $error = "[ERROR] Act $raktFullNumber: Calculation code '$rbklShifrs' not found in kl_rbf_kalkulacija. Skipping work.";
                files::wh_log($error);
                $workErrors[] = $error;
                $workErrorCount++;
                continue;
            }
            
            // Check if work already exists
            $existingWork = dbProc::getExistingWork($raktId, $rbklShifrs, $mmsKods);
            
            if ($existingWork) {
                // Work exists - check if processed
                if ($existingWork['RADR_IS_PROCESSED'] == 1) {
                    // Already processed - skip
                    files::wh_log("[SKIP] Act $raktFullNumber: Work (Calc: $rbklShifrs, MMS: $mmsKods) already processed (RADR_IS_PROCESSED=1)");
                    $workSkipCount++;
                } else {
                    // Not processed - update status and plan_date only
                    $updated = dbProc::updateRbfWorkStatus($existingWork['RADR_ID'], $status, $planDate);
                    if ($updated) {
                        files::wh_log("[UPDATE] Act $raktFullNumber: Work (Calc: $rbklShifrs, MMS: $mmsKods) - Updated status to '$status'");
                        $workUpdateCount++;
                    } else {
                        $error = "[ERROR] Act $raktFullNumber: Failed to update work (RADR_ID: {$existingWork['RADR_ID']})";
                        files::wh_log($error);
                        $workErrors[] = $error;
                        $workErrorCount++;
                    }
                }
            } else {
                // Work doesn't exist - insert new
                $insertedId = dbProc::insertRbfWork($raktId, $rbklShifrs, $mmsKods, $mmsTitle, $status, $planDate, $norma);
                if ($insertedId) {
                    files::wh_log("[INSERT] Act $raktFullNumber: New work added (RADR_ID: $insertedId, Calc: $rbklShifrs, MMS: $mmsKods, Norma: $norma)");
                    $workInsertCount++;
                } else {
                    $error = "[ERROR] Act $raktFullNumber: Failed to insert work (Calc: $rbklShifrs, MMS: $mmsKods)";
                    files::wh_log($error);
                    $workErrors[] = $error;
                    $workErrorCount++;
                }
            }
        }
    }
    
    // Work summary
    files::wh_log("");
    files::wh_log("========================================");
    files::wh_log("[SUMMARY] Work Records Processing");
    files::wh_log("========================================");
    files::wh_log("[INFO] Total work records: " . count($workRecords));
    files::wh_log("[SUCCESS] Inserted: $workInsertCount work(s)");
    files::wh_log("[SUCCESS] Updated: $workUpdateCount work(s)");
    files::wh_log("[INFO] Skipped (already processed): $workSkipCount work(s)");
    files::wh_log("[ERROR] Failed: $workErrorCount work(s)");
    
    if (count($workErrors) > 0) {
        files::wh_log("");
        files::wh_log("[WORK ERRORS] Details:");
        foreach ($workErrors as $error) {
            files::wh_log("  " . $error);
        }
    }
}

// ============================================================================
// Final Summary
// ============================================================================

files::wh_log("");
files::wh_log("========================================");
files::wh_log("[FINAL SUMMARY] RBF Automatic Processing");
files::wh_log("========================================");
$totalPendingActs = ($pendingActs && is_array($pendingActs)) ? count($pendingActs) : 0;
files::wh_log("[ACTS] Total pending: $totalPendingActs");
files::wh_log("[ACTS] Successfully created: $successCount act(s)");
files::wh_log("[ACTS] Failed: $errorCount act(s)");

if ($workRecords) {
    files::wh_log("[WORKS] Total records: " . count($workRecords));
    files::wh_log("[WORKS] Inserted: $workInsertCount work(s)");
    files::wh_log("[WORKS] Updated: $workUpdateCount work(s)");
    files::wh_log("[WORKS] Skipped: $workSkipCount work(s)");
    files::wh_log("[WORKS] Failed: $workErrorCount work(s)");
}

if (count($errors) > 0 || (isset($workErrors) && count($workErrors) > 0)) {
    files::wh_log("");
    files::wh_log("[ALL ERRORS/WARNINGS] Details:");
    
    if (count($errors) > 0) {
        files::wh_log("  [ACT ERRORS]:");
        foreach ($errors as $error) {
            files::wh_log("    " . $error);
        }
    }
    
    if (isset($workErrors) && count($workErrors) > 0) {
        files::wh_log("  [WORK ERRORS]:");
        foreach ($workErrors as $error) {
            files::wh_log("    " . $error);
        }
    }
}

$endTime = date('Y-m-d H:i:s');
files::wh_log("");
files::wh_log("[END] Process completed at $endTime");
files::wh_log("========================================");

// Close database connection
mysqli_close($GLOBALS['sql_connect']);

// Exit with appropriate code
exit($errorCount > 0 ? 1 : 0);

?>

