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
    'materialSaved' => 0,
    'materialExists' => 0,
    'materialNotFound' => 0,
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
                                  
                                  foreach ($parsedData as $row)
                                  {
                                      // row[0] = Group Type, row[1] = Column A (code), row[2-5] = other columns
                                      $code = isset($row[1]) ? trim($row[1]) : '';
                                      $codeLength = strlen($code);
                                      $amount = isset($row[4]) ? trim($row[4]) : null;
                                      
                                      // Requirement #2: Skip rows without amount (unless code is empty - worker rows)
                                      if (!empty($code) && (empty($amount) || $amount === '0' || $amount === 0)) {
                                          $processResults['skipped']++;
                                          continue;
                                      }
                                      
                                      // Classify: 5 digits = WORK (type 1), 8 symbols = MATERIAL (type 2)
                                      if ($codeLength == 5 || empty($code))
                                      {
                                          // WORK (5 digits or null/empty)
                                          $processResults['workRows']++;
                                          $type = 1; // WORK
                                          
                                          // Get work type ID from kl_darba_veidi
                                          $workTypeId = false;
                                          if (!empty($row[0]))
                                          {
                                              $workTypeId = dbProc::getWorkTypeIdByName($row[0]);
                                              
                                              // Requirement #1: If work type doesn't exist, create it
                                              if ($workTypeId === false) {
                                                  $workTypeId = dbProc::insertWorkType($row[0], $userId);
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
                                          
                                          // Check if work already exists in darbi for this act AND work type
                                          $existsInDarbi = false;
                                          if (!empty($code))
                                          {
                                              $existsInDarbi = dbProc::workExistsInDarbi($actId, $code, $workTypeId);
                                          }
                                          
                                          // Scenario 1: Code exists in kl_kalkulacija (or is null) AND doesn't exist in darbi
                                          if (($codeExistsInKalkulacija || empty($code)) && !$existsInDarbi)
                                          {
                                              
                                              // Prepare values for insert
                                              $title = isset($row[2]) ? $row[2] : '';
                                              $normativ = ($workInfo !== false) ? $workInfo['KKAL_PLANA'] : null;
                                              $amount = isset($row[4]) ? $row[4] : null;
                                              $measure = isset($row[3]) ? $row[3] : '';
                                              $kkalId = ($workInfo !== false) ? $workInfo['KKAL_ID'] : null;
                                              $isWorker = empty($code) ? 1 : 0;
                                              $notes = isset($row[5]) ? $row[5] : '';
                                              
                                              // Insert into DARBI
                                              $darbiId = dbProc::insertWorkToDarbiFromEstimate(
                                                  $actId, $code, $title, $normativ, $amount, 
                                                  $measure, $kkalId, $isWorker, $workTypeId, $notes
                                              );
                                              
                                              if ($darbiId !== false)
                                              {
                                                  // Successfully inserted into darbi
                                                  // Now insert into estimate_files_detales if code is not null
                                                  if (!empty($code))
                                                  {
                                                      dbProc::insertEstimateFileDetail($estimateId, $type, $code, 1, 1);
                                                      $processResults['workSaved']++;
                                                  }
                                                  else
                                                  {
                                                      // Code is null - work row inserted successfully
                                                      $processResults['workSaved']++;
                                                  }
                                              }
                                          }
                                          // Scenario 2: Code doesn't exist in kl_kalkulacija
                                          elseif (!empty($code) && !$codeExistsInKalkulacija)
                                          {
                                              dbProc::insertEstimateFileDetail($estimateId, $type, $code, 3, 0);
                                              $processResults['workNotFound']++;
                                          }
                                          // Scenario 3: Code already exists in darbi for this act
                                          elseif (!empty($code) && $existsInDarbi)
                                          {
                                              dbProc::insertEstimateFileDetail($estimateId, $type, $code, 2, 0);
                                              $processResults['workExists']++;
                                          }
                                      }
                                      elseif ($codeLength == 8)
                                      {
                                          // MATERIAL (8 symbols)
                                          $processResults['materialRows']++;
                                          $type = 2; // MATERIAL
                                          
                                          // Get work type ID from kl_darba_veidi
                                          $workTypeId = false;
                                          if (!empty($row[0]))
                                          {
                                              $workTypeId = dbProc::getWorkTypeIdByName($row[0]);
                                              
                                              // Requirement #1: If work type doesn't exist, create it
                                              if ($workTypeId === false) {
                                                  $workTypeId = dbProc::insertWorkType($row[0], $userId);
                                              }
                                          }
                                          
                                          // Get material info from kl_materiali by category code
                                          $materialInfoList = dbProc::getMaterialInfoByCode($code);
                                          $codeExistsInKlMateriali = ($materialInfoList !== false);
                                          
                                          // Use first material from the list (if multiple exist with same category code)
                                          $materialInfo = ($materialInfoList !== false) ? $materialInfoList[0] : false;
                                          
                                          // Check if material already exists in materiali for this act AND work type
                                          $existsInMateriali = dbProc::materialExistsInMateriali($actId, $code, $workTypeId);
                                          
                                          // Scenario 1: Code exists in kl_materiali (or is null) AND doesn't exist in materiali
                                          if (($codeExistsInKlMateriali || empty($code)) && !$existsInMateriali)
                                          {
                                              
                                              // Prepare values for insert - use title from Excel
                                              $title = isset($row[2]) ? $row[2] : '';
                                              $amount = isset($row[4]) ? $row[4] : null;
                                              $measure = isset($row[3]) ? $row[3] : '';
                                              if ($materialInfo !== false && !empty($materialInfo['KMAT_MERVIENIBA']))
                                              {
                                                  $measure = $materialInfo['KMAT_MERVIENIBA'];
                                              }
                                              $isWorker = empty($code) ? 1 : 0;
                                              $notes = isset($row[5]) ? $row[5] : '';
                                              
                                              // Insert into MATERIALI using actual material code from catalog
                                              $materialCode = ($materialInfo !== false && !empty($materialInfo['KMAT_KODS'])) ? $materialInfo['KMAT_KODS'] : $code;
                                              
                                              // Insert into MATERIALI
                                              $materialiId = dbProc::insertMaterialToMaterialiFromEstimate(
                                                  $actId, $materialCode, $title, $amount, 
                                                  $measure, $isWorker, $workTypeId, $notes
                                              );
                                              
                                              if ($materialiId !== false)
                                              {
                                                  // Successfully inserted into materiali
                                                  // Now insert into estimate_files_detales if code is not null
                                                  if (!empty($code))
                                                  {
                                                      dbProc::insertEstimateFileDetail($estimateId, $type, $code, 1, 1);
                                                      $processResults['materialSaved']++;
                                                  }
                                                  else
                                                  {
                                                      // Code is null - material row inserted successfully
                                                      $processResults['materialSaved']++;
                                                  }
                                              }
                                          }
                                          // Scenario 2: Code doesn't exist in kl_materiali
                                          elseif (!empty($code) && !$codeExistsInKlMateriali)
                                          {
                                              dbProc::insertEstimateFileDetail($estimateId, $type, $code, 3, 0);
                                              $processResults['materialNotFound']++;
                                          }
                                          // Scenario 3: Code already exists in materiali for this act
                                          elseif (!empty($code) && $existsInMateriali)
                                          {
                                              dbProc::insertEstimateFileDetail($estimateId, $type, $code, 2, 0);
                                              $processResults['materialExists']++;
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
                                      $message .= '&nbsp;&nbsp;- ' . text::get('ALREADY_EXISTS_LABEL') . ' <span style="color:orange;">' . $processResults['workExists'] . '</span><br>';
                                  }
                                  if ($processResults['workNotFound'] > 0)
                                  {
                                      $message .= '&nbsp;&nbsp;- ' . text::get('NOT_FOUND_IN_CATALOG_LABEL') . ' <span style="color:red;">' . $processResults['workNotFound'] . '</span><br>';
                                  }
                                  
                                  $message .= '<br><b>' . text::get('MATERIAL_ROWS_LABEL') . ' ' . $processResults['materialRows'] . '</b><br>';
                                  $message .= '&nbsp;&nbsp;- ' . text::get('SAVED_TO_MATERIALS') . ' <span style="color:green;">' . $processResults['materialSaved'] . '</span><br>';
                                  if ($processResults['materialExists'] > 0)
                                  {
                                      $message .= '&nbsp;&nbsp;- ' . text::get('ALREADY_EXISTS_LABEL') . ' <span style="color:orange;">' . $processResults['materialExists'] . '</span><br>';
                                  }
                                  if ($processResults['materialNotFound'] > 0)
                                  {
                                      $message .= '&nbsp;&nbsp;- ' . text::get('NOT_FOUND_IN_CATALOG_LABEL') . ' <span style="color:red;">' . $processResults['materialNotFound'] . '</span><br>';
                                  }
                                  
                                  if ($processResults['skipped'] > 0)
                                  {
                                      $message .= '<br>' . text::get('SKIPPED_ROWS_LABEL') . ' ' . $processResults['skipped'];
                                  }
                                  
                                  $oFormPop->addSuccess($message);
                                  
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
