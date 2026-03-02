<?
// Created by 
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isProjector = dbProc::isExistsUserRoleWithProject($userId) ;
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;

// act ID
$actId  = reqVar::get('actId');

$parsedData = array();
$parseErrors = array();
$hasFile = false;
$savedEstimateId = false;
$processResults = array(
    'totalRows' => 0,
    'workRows' => 0,
    'materialRows' => 0,
    'workSaved' => 0,
    'workExists' => 0,
    'workNotFound' => 0,
    'workAmountNotSet' => 0,
    'materialSaved' => 0,
    'materialExists' => 0,
    'materialNotFound' => 0,
    'materialAmountNotSet' => 0,
    'skipped' => 0
);

// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isProjector)
{
    $oLink=new urlQuery();
    $oLink->addPrm(FORM_ID, 'f.akt.s.26');
    $oLink->addPrm('actId', $actId);
    $oFormPop = new Form('frmMainTab','post',$oLink->getQuery());
    unset($oLink);

    if($actId !== false )
    {
      // get info about act
      $actInfo = dbProc::getActInfo($actId);
      if(count($actInfo)>0)
      {
      	$act = $actInfo[0];
        $status = $act['RAKT_STATUS'];
      }

      // Form elements
      $oFormPop -> addElement('uploadfile', 'fileName', text::get('FILE'), '', 'class="flex" accept=".xlsx,.xls,.csv" onchange="enableUploadButton();"');
      $oFormPop -> addElement('hidden', 'action', '');
      
      // Form buttons
      $isUploadDisabled = ($hasFile) ? ' disabled' : '';
      $oFormPop -> addElement('submitImg', 'upload', text::get('UPLOAD'), 'img/btn_import.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_UPDATE.'\');"'.$isUploadDisabled);
      $oFormPop -> addElement('button', 'close', '', text::get('CLOSE'), 'class="btn70" onclick="javascript:window.close();return false;"; ');
      
      // JavaScript for button control
      $oFormPop -> addElement('static', 'jsButtonsControl', '', '
        <script>
          function enableUploadButton()
          {
            var fileInput = document.forms["frmMainTab"]["fileName"];
            var uploadButton = document.all["upload"];
            
            if (uploadButton) {
              if (fileInput && fileInput.value) {
                uploadButton.disabled = false;
                uploadButton.src = "img/btn_import.gif";
                uploadButton.style.opacity = "1";
                uploadButton.style.cursor = "pointer";
              } else {
                uploadButton.disabled = true;
                uploadButton.src = "img/btn_import.gif";
                uploadButton.style.opacity = "0.4";
                uploadButton.style.cursor = "not-allowed";
              }
            }
          }
          
          // Disable button on page load or after data is loaded
          if (typeof window.onload == "function") {
            var existingOnload = window.onload;
            window.onload = function() {
              existingOnload();
              enableUploadButton();
            };
          } else {
            window.onload = function() {
              enableUploadButton();
            };
          }
        </script>
      ');

      // Handle form submission
      if ($oFormPop -> isFormSubmitted() && $oFormPop->getValue('action') == OP_UPDATE)
      {
          if (files::isUploadFile('fileName'))
          {
              // Check file extension
              $uploadedFile = $_FILES['fileName'];
              $fileExtension = strtolower(pathinfo($uploadedFile['name'], PATHINFO_EXTENSION));
              
              if ($fileExtension == 'xlsx' || $fileExtension == 'xls' || $fileExtension == 'csv')
              {
                  // Parse the Excel file directly from uploaded temporary file
                  // Pass original filename so parser can detect file type correctly
                  $parser = new ioExcelParser($uploadedFile['tmp_name'], $uploadedFile['name']);
                  $result = $parser->parse();
                  
                  if ($parser->isValid() && $result !== false)
                  {
                      $parsedData = $parser->getParsedData();
                      
                      // Insert estimate file record to database
                      $estimateId = dbProc::insertEstimateFile($uploadedFile['name'], $actId, $userId, count($parsedData));
                      
                      if ($estimateId !== false)
                      {
                          // Create estimate_files directory if it doesn't exist
                          if (!file_exists(ESTIMATE_FILES_STORE_PATH))
                          {
                              @mkdir(ESTIMATE_FILES_STORE_PATH, 0777, true);
                          }
                          
                          // Use DB PK as filename
                          $savedFileName = $estimateId;
                          $savedFilePath = ESTIMATE_FILES_STORE_PATH . '/' . $savedFileName;
                          
                          // Save the uploaded file to estimate_files directory
                          if (@move_uploaded_file($uploadedFile['tmp_name'], $savedFilePath))
                              {
                                  $hasFile = true;
                                  $savedEstimateId = $estimateId;
                                  
                                  // Process parsed data - classify and save to estimate_files_detales
                                  $processResults['totalRows'] = count($parsedData);
                                  
                                  // Create log prefix with act info for easier debugging
                                  $actNumber = isset($act['RAKT_NUM_POSTFIX']) ? $act['RAKT_NUM_POSTFIX'] : 'N/A';
                                  $logPrefix = "[Act: $actNumber | ActID: $actId | EstimateID: $estimateId]";
                                  
                                  files::wh_log("$logPrefix ===== ESTIMATE IMPORT STARTED =====");
                                  files::wh_log("$logPrefix File: {$uploadedFile['name']}, Rows: {$processResults['totalRows']}");
                                  
                                  // Track status for each row (for popup display)
                                  $rowStatuses = array();
                                  
                                  foreach ($parsedData as $rowIndex => $row)
                                  {
                                      // row[0] = Section Type (1=WORK, 2=MATERIAL), row[1] = Group Type, row[2] = Column A (code), row[3-6] = other columns
                                      $sectionType = isset($row[0]) ? $row[0] : null;
                                      $groupName = isset($row[1]) ? trim($row[1]) : '';
                                      $code = isset($row[2]) ? trim($row[2]) : '';
                                      $codeLength = strlen($code);
                                      $amount = isset($row[5]) ? trim($row[5]) : null;
                                      
                                      
                                      
                                      // Skip rows without a valid group name (empty or "Bez darba veida")
                                      if (empty($groupName) || stripos($groupName, 'Bez darba veida') !== false) {
                                          if (empty($code)) {
                                              files::wh_log("$logPrefix SKIPPED - Invalid group: Row $rowIndex - GroupName: '$groupName'");
                                          }
                                          continue;
                                      }
                                      
                                      // Check if amount is not set (for all rows including worker rows without code)
                                      $amountNotSet = (empty($amount) || $amount === '0' || $amount === 0);
                                      
                                      // LOG: Amount check for worker rows
                                      if (empty($code) && $amountNotSet) {
                                          files::wh_log("$logPrefix SKIPPED - No amount: Row $rowIndex - Amount: '$amount'");
                                      }
                                      
                                      // Classify based on section type (if available) or code length
                                      // Use section type from parser if available, otherwise fall back to code length
                                      if ($sectionType == 1 || ($sectionType === null && ($codeLength == 5 || empty($code))))
                                      {
                                          // WORK (section type 1, or 5 digits, or null/empty when section unknown)
                                          $processResults['workRows']++;
                                          $type = 1; // WORK
                                          
                                          // If amount not set, record it and skip processing
                                          if ($amountNotSet) {
                                              if (!empty($code)) {
                                                  $title = isset($row[3]) ? $row[3] : '';
                                                  dbProc::insertEstimateFileDetail($estimateId, $type, $code, 4, 0, $title, $groupName);
                                              }
                                              $processResults['workAmountNotSet']++;
                                              $rowStatuses[$rowIndex] = 4; // Amount not set
                                              continue;
                                          }
                                          
                                          // Get work type ID from kl_darba_veidi
                                          $workTypeId = false;
                                          if (!empty($row[1]))
                                          {
                                              $workTypeId = dbProc::getWorkTypeIdByName($row[1]);
                                              
                                              // Requirement #1: If work type doesn't exist, create it
                                              if ($workTypeId === false) {
                                                  $workTypeId = dbProc::insertWorkType($row[1], $userId);
                                              }
                                          }
                                          
                                          // Get work info from kl_kalkulacija (if code is not empty)
                                          $workInfo = false;
                                          $codeExistsInKalkulacija = false;
                                          
                                          if (!empty($code))
                                          {
                                              $workInfo = dbProc::getWorkInfoByCode($code);
                                              $codeExistsInKalkulacija = ($workInfo !== false);
                                          }
                                          
                                          // Check if work already exists in darbi for this act AND work type (BEFORE this import)
                                          $existsInDarbi = false;
                                          if (!empty($code))
                                          {
                                              $existsInDarbi = dbProc::workExistsInDarbi($actId, $code, $workTypeId);
                                          }
                                          
                                          // If code exists in catalog (or is empty for worker rows)
                                          if ($codeExistsInKalkulacija || empty($code))
                                          {
                                              // If already exists, mark as exists and skip
                                              if (!empty($code) && $existsInDarbi)
                                              {
                                                  $title = isset($row[3]) ? $row[3] : '';
                                                  if (empty($title) && $workInfo !== false) {
                                                      $title = $workInfo['KKAL_NOSAUKUMS'];
                                                  }
                                                  dbProc::insertEstimateFileDetail($estimateId, $type, $code, 2, 0, $title, $groupName);
                                                  $processResults['workExists']++;
                                                  $rowStatuses[$rowIndex] = 2; // Already exists
                                              }
                                              // If doesn't exist, insert it
                                              else
                                              {
                                                  // Prepare values for insert
                                                  $title = isset($row[3]) ? $row[3] : '';
                                                  $normativ = ($workInfo !== false) ? $workInfo['KKAL_PLANA'] : null;
                                                  $amount = isset($row[5]) ? $row[5] : null;
                                                  $measure = isset($row[4]) ? $row[4] : '';
                                                  $kkalId = ($workInfo !== false) ? $workInfo['KKAL_ID'] : null;
                                                  $isWorker = empty($code) ? 1 : 0;
                                                  $notes = isset($row[6]) ? $row[6] : '';
                                                  
                                                  // For worker rows, ensure we have at least a title
                                                  if (empty($code) && empty($title)) {
                                                      $title = 'Strādnieks'; // Default worker title
                                                  }
                                                  
                                                  // LOG: Worker row debug
                                                  if (empty($code)) {
                                                      files::wh_log("$logPrefix WORK: Row $rowIndex - Title: $title, Amount: $amount, WorkTypeId: $workTypeId, isWorker: $isWorker");
                                                  }
                                                  
                                                  // Insert into DARBI
                                                  $darbiId = dbProc::insertWorkToDarbiFromEstimate(
                                                      $actId, $code, $title, $normativ, $amount, 
                                                      $measure, $kkalId, $isWorker, $workTypeId, $notes
                                                  );
                                                  
                                                  
                                                  
                                                  if ($darbiId !== false)
                                                  {
                                                      // Successfully inserted - save to statistics
                                                      // For worker rows without code, use work type ID as identifier
                                                      $statCode = !empty($code) ? $code : ('WORKER_' . $workTypeId . '_' . $darbiId);                                                      
                                                     
                                                      
                                                      dbProc::insertEstimateFileDetail($estimateId, $type, $statCode, 1, 1, $title, $groupName);
                                                      $processResults['workSaved']++;
                                                      $rowStatuses[$rowIndex] = 1; // Saved successfully
                                                  }
                                                  else
                                                  {
                                                      // Insert failed - mark as error
                                                      if (!empty($code))
                                                      {
                                                          dbProc::insertEstimateFileDetail($estimateId, $type, $code, 3, 0, $title, $groupName);
                                                      }
                                                      else
                                                      {
                                                          files::wh_log("$logPrefix WORK INSERT FAILED: Row $rowIndex - Cannot save to statistics (no code, insert failed)");
                                                      }
                                                      $rowStatuses[$rowIndex] = 3; // Error during insert
                                                  }
                                              }
                                          }
                                          // Code doesn't exist in kl_kalkulacija
                                          elseif (!empty($code))
                                          {
                                              $title = isset($row[3]) ? $row[3] : '';
                                              dbProc::insertEstimateFileDetail($estimateId, $type, $code, 3, 0, $title, $groupName);
                                              $processResults['workNotFound']++;
                                              $rowStatuses[$rowIndex] = 3; // Not found in catalog
                                          }
                                      }
                                      elseif ($sectionType == 2 || ($sectionType === null && $codeLength == 8))
                                      {
                                          // MATERIAL (section type 2, or 8 symbols when section unknown)
                                          $processResults['materialRows']++;
                                          $type = 2; // MATERIAL
                                          
                                          // If amount not set, record it and skip processing
                                          if ($amountNotSet) {
                                              if (!empty($code)) {
                                                  $title = isset($row[3]) ? $row[3] : '';
                                                  dbProc::insertEstimateFileDetail($estimateId, $type, $code, 4, 0, $title, $groupName);
                                              }
                                              $processResults['materialAmountNotSet']++;
                                              $rowStatuses[$rowIndex] = 4; // Amount not set
                                              continue;
                                          }
                                          
                                          // Get work type ID from kl_darba_veidi
                                          $workTypeId = false;
                                          if (!empty($row[1]))
                                          {
                                              $workTypeId = dbProc::getWorkTypeIdByName($row[1]);
                                              
                                              // Requirement #1: If work type doesn't exist, create it
                                              if ($workTypeId === false) {
                                                  $workTypeId = dbProc::insertWorkType($row[1], $userId);
                                              }
                                          }
                                          
                                          // Get material info from kl_materiali by category code
                                          $materialInfoList = dbProc::getMaterialInfoByCode($code);
                                          $codeExistsInKlMateriali = ($materialInfoList !== false);
                                          
                                          // Use first material from the list (if multiple exist with same category code)
                                          $materialInfo = ($materialInfoList !== false) ? $materialInfoList[0] : false;
                                          
                                          // Check if material already exists in materiali for this act AND work type (BEFORE this import)
                                          // Check using category code from Excel
                                          $existsInMateriali = dbProc::materialExistsInMateriali($actId, $code, $workTypeId);
                                          
                                          // If code exists in catalog (or is empty for worker rows)
                                          if ($codeExistsInKlMateriali || empty($code))
                                          {
                                              // If already exists, mark as exists and skip
                                              if (!empty($code) && $existsInMateriali)
                                              {
                                                  $title = isset($row[3]) ? $row[3] : '';
                                                  if (empty($title) && $materialInfo !== false) {
                                                      $title = $materialInfo['KMAT_NOSAUKUMS'];
                                                  }
                                                  dbProc::insertEstimateFileDetail($estimateId, $type, $code, 2, 0, $title, $groupName);
                                                  $processResults['materialExists']++;
                                                  $rowStatuses[$rowIndex] = 2; // Already exists
                                              }
                                              // If doesn't exist, insert it
                                              else
                                              {
                                                  // Prepare values for insert - use title from Excel
                                                  $title = isset($row[3]) ? $row[3] : '';
                                                  $amount = isset($row[5]) ? $row[5] : null;
                                                  $measure = isset($row[4]) ? $row[4] : '';
                                                  if ($materialInfo !== false && !empty($materialInfo['KMAT_MERVIENIBA']))
                                                  {
                                                      $measure = $materialInfo['KMAT_MERVIENIBA'];
                                                  }
                                                  $isWorker = empty($code) ? 1 : 0;
                                                  $notes = isset($row[6]) ? $row[6] : '';
                                                  
                                                  // For worker rows, ensure we have at least a title
                                                  if (empty($code) && empty($title)) {
                                                      $title = 'Strādnieks'; // Default worker title
                                                  }
                                                  
                                                  // LOG: Worker row debug
                                                  if (empty($code)) {
                                                      files::wh_log("$logPrefix MATERIAL: Row $rowIndex - Title: $title, Amount: $amount, WorkTypeId: $workTypeId, isWorker: $isWorker");
                                                  }
                                                  
                                                  // Insert into MATERIALI using category code from Excel
                                                  $materialiId = dbProc::insertMaterialToMaterialiFromEstimate(
                                                      $actId, $code, $title, $amount, 
                                                      $measure, $isWorker, $workTypeId, $notes
                                                  );
                                                  
                                                 
                                                  if ($materialiId !== false)
                                                  {
                                                      // Successfully inserted - save to statistics
                                                      // For worker rows without code, use work type ID as identifier
                                                      $statCode = !empty($code) ? $code : ('WORKER_' . $workTypeId . '_' . $materialiId);
                                                     
                                                      dbProc::insertEstimateFileDetail($estimateId, $type, $statCode, 1, 1, $title, $groupName);
                                                      $processResults['materialSaved']++;
                                                      $rowStatuses[$rowIndex] = 1; // Saved successfully
                                                  }
                                                  else
                                                  {
                                                      // Insert failed - mark as error
                                                      if (!empty($code))
                                                      {
                                                          dbProc::insertEstimateFileDetail($estimateId, $type, $code, 3, 0, $title, $groupName);
                                                      }
                                                      else
                                                      {
                                                          files::wh_log("$logPrefix MATERIAL INSERT FAILED: Row $rowIndex - Cannot save to statistics (no code, insert failed)");
                                                      }
                                                      $rowStatuses[$rowIndex] = 3; // Error during insert
                                                  }
                                              }
                                          }
                                          // Code doesn't exist in kl_materiali
                                          elseif (!empty($code))
                                          {
                                              $title = isset($row[3]) ? $row[3] : '';
                                              dbProc::insertEstimateFileDetail($estimateId, $type, $code, 3, 0, $title, $groupName);
                                              $processResults['materialNotFound']++;
                                              $rowStatuses[$rowIndex] = 3; // Not found in catalog
                                          }
                                      }
                                      else
                                      {
                                          // Unknown format
                                          $processResults['skipped']++;
                                      }
                                  }
                                  
                                  // Build success message
                                  $message = text::get('FILE_UPLOADED_SUCCESSFULLY') . ' ' . $estimateId . '<br>';
                                  $message .= text::get('TOTAL_ROWS_COUNT') . ' ' . $processResults['totalRows'] . '<br><br>';
                                  
                                  $message .= '<b>' . text::get('WORK_ROWS_LABEL') . ' ' . $processResults['workRows'] . '</b><br>';
                                  $message .= '&nbsp;&nbsp;- ' . text::get('SAVED_TO_WORKS') . ' <span style="color:green;">' . $processResults['workSaved'] . '</span><br>';
                                  if ($processResults['workExists'] > 0)
                                  {
                                      $message .= '&nbsp;&nbsp;- ' . text::get('STATUS_WORK_EXISTS') . ' <span style="color:orange;">' . $processResults['workExists'] . '</span><br>';
                                  }
                                  if ($processResults['workNotFound'] > 0)
                                  {
                                      $message .= '&nbsp;&nbsp;- ' . text::get('STATUS_WORK_NOT_FOUND') . ' <span style="color:red;">' . $processResults['workNotFound'] . '</span><br>';
                                  }
                                  if ($processResults['workAmountNotSet'] > 0)
                                  {
                                      $message .= '&nbsp;&nbsp;- ' . text::get('STATUS_AMOUNT_NOT_SET') . ' <span style="color:red;">' . $processResults['workAmountNotSet'] . '</span><br>';
                                  }
                                  
                                  $message .= '<br><b>' . text::get('MATERIAL_ROWS_LABEL') . ' ' . $processResults['materialRows'] . '</b><br>';
                                  $message .= '&nbsp;&nbsp;- ' . text::get('SAVED_TO_MATERIALS') . ' <span style="color:green;">' . $processResults['materialSaved'] . '</span><br>';
                                  if ($processResults['materialExists'] > 0)
                                  {
                                      $message .= '&nbsp;&nbsp;- ' . text::get('STATUS_MATERIAL_EXISTS') . ' <span style="color:orange;">' . $processResults['materialExists'] . '</span><br>';
                                  }
                                  if ($processResults['materialNotFound'] > 0)
                                  {
                                      $message .= '&nbsp;&nbsp;- ' . text::get('STATUS_MATERIAL_NOT_FOUND') . ' <span style="color:red;">' . $processResults['materialNotFound'] . '</span><br>';
                                  }
                                  if ($processResults['materialAmountNotSet'] > 0)
                                  {
                                      $message .= '&nbsp;&nbsp;- ' . text::get('STATUS_AMOUNT_NOT_SET') . ' <span style="color:red;">' . $processResults['materialAmountNotSet'] . '</span><br>';
                                  }
                                  
                                  if ($processResults['skipped'] > 0)
                                  {
                                      $message .= '<br>' . text::get('SKIPPED_ROWS_LABEL') . ' ' . $processResults['skipped'];
                                  }
                                  
                                  $oFormPop->addSuccess($message);
                                  
                                  // LOG: Import summary
                                  files::wh_log("$logPrefix ===== IMPORT COMPLETED =====");
                                  files::wh_log("$logPrefix Work: Saved={$processResults['workSaved']}, Exists={$processResults['workExists']}, NotFound={$processResults['workNotFound']}, NoAmount={$processResults['workAmountNotSet']}");
                                  files::wh_log("$logPrefix Material: Saved={$processResults['materialSaved']}, Exists={$processResults['materialExists']}, NotFound={$processResults['materialNotFound']}, NoAmount={$processResults['materialAmountNotSet']}");
                                  
                                  // Generate Excel file with statistics
                                  $excelFileId = toExcel::exportEstimateStatistics($estimateId, $userId, $actId);
                                  
                                  // Save Excel file ID to estimate_files table for future use
                                  dbProc::updateEstimateFileExcelId($estimateId, $excelFileId);

                                  // Refresh parent window tabs to show inserted rows
                                  $oRedirectLink = new urlQuery();
                                  $oRedirectLink->addPrm(FORM_ID, 'f.akt.s.20');
                                  $oRedirectLink->addPrm('actId', $actId);
                                  $oRedirectLink->addPrm('tab', TAB_WORKS);
                                  $oRedirectLink->addPrm('isNew', RequestHandler::getMicroTime());
                                  requestHandler::makeParentReplaceWithoutClosure($oRedirectLink->getQuery().'#tab');
                                  unset($oRedirectLink);
                              }
                              else
                              {
                                  // If file save failed, delete the database record
                                  dbProc::deleteEstimateFile($estimateId);
                                  $oFormPop->addError('Kļūda saglabājot failu estimate_files direktorijā.');
                              }
                          }
                          else
                          {
                              $oFormPop->addError('Kļūda izveidojot datubāzes ierakstu tāmes failam.');
                          }
                      }
                      else
                      {
                          $parseErrors = $parser->getErrors();
                          foreach ($parseErrors as $error)
                          {
                              $oFormPop->addError($error);
                          }
                      }
              }
              else
              {
                  $oFormPop->addError('Nederīgs faila formāts. Lūdzu augšupielādējiet Excel vai CSV failu (.xlsx, .xls, .csv).');
              }
          }
          else
          {
              $oFormPop->addError('Lūdzu izvēlieties failu augšupielādei.');
          }
      }

      $oFormPop -> makeHtml();
      include('f.akt.s.26.tpl');
    }
    else
    {
        RequestHandler::showErrorAndDie(text::get('ERROR_NOT_FOUND_FORM_FILE'));
    }
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
