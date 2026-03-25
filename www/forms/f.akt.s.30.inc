<?php
// RBF Act Form (f.akt.s.30.inc)
// Created for DUIS-549

$userId = userAuthorization::getUserId();
$isAdmin = userAuthorization::isAdmin();
$isRbfUser = userAuthorization::isRbfUser();
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);

// search form
$isSearch  = reqVar::get('isSearch');
// search act by number
$searchNum  = reqVar::get('searchNum');
$isNew  = reqVar::get('isNew');
$isAuto  = reqVar::get('isAuto');
// act ID
$actId  = reqVar::get('actId');
// tab name
$tab  = reqVar::get('tab');

// Check if user has access
if (!$isAdmin && !$isRbfUser && !$isEconomist)
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

// XMLHTTP request handlers for dynamic dropdowns
if (reqVar::get('xmlHttp') == 1)
{
    // Load VV numbers based on selected employee
    if (reqVar::get('employeeCode') !== false)
    {
        ?>
        for(i=document.all["vvNumber"].length; i>=0; i--)
        {
            document.all["vvNumber"].options[i] = null;
        }
        for(i=document.all["department"].length; i>=0; i--)
        {
            document.all["department"].options[i] = null;
        }
        <?
        $res = dbProc::getRbfEmployeeVVList(reqVar::get('employeeCode'));
        if (is_array($res) && count($res)>0)
        {
            ?>
            document.all["vvNumber"].options[0] = new Option('<?=addslashes(text::get('EMPTY_SELECT_OPTION'));?>', '');
            document.all["department"].options[0] = new Option('<?=addslashes(text::get('EMPTY_SELECT_OPTION'));?>', '');
            <?
            $i = 1;
            foreach ($res as $row)
            {
                ?>
                document.all["vvNumber"].options[<?=$i;?>] = new Option('<?=addslashes($row['RBDV_VV_NUMURS']);?>', '<?=addslashes($row['RBDV_VV_NUMURS']);?>');
                <?
                $i++;
            }
        }
    }
    
    // Load departments based on selected VV number
    if (reqVar::get('vvNumber') !== false)
    {
        ?>
        for(i=document.all["department"].length; i>=0; i--)
        {
            document.all["department"].options[i] = null;
        }
        <?
        $res = dbProc::getRbfVVTerritories(reqVar::get('vvNumber'));
        if (is_array($res) && count($res)>0)
        {
            // For C type, group by DID code to show only one option per code
            $deptOptionsTemp = array();
            foreach ($res as $row)
            {
                // Use RBTR_KODS for U type, RBTR_DID_KODS for C type
                $territoryCode = ($row['RBDU_VV_VEIDS'] == 'U') ? $row['RBTR_KODS'] : $row['RBTR_DID_KODS'];
                if (!isset($deptOptionsTemp[$territoryCode])) {
                    $deptOptionsTemp[$territoryCode] = $row['RBTR_NOSAUKUMS'];
                }
            }
            
            ?>
            document.all["department"].options[0] = new Option('<?=addslashes(text::get('EMPTY_SELECT_OPTION'));?>', '');
            <?
            $i = 1;
            foreach ($deptOptionsTemp as $code => $name)
            {
                ?>
                document.all["department"].options[<?=$i;?>] = new Option('<?=addslashes($name);?>', '<?=addslashes($code);?>');
                <?
                $i++;
            }
        }
    }
    
    // Load authors (users) based on selected employee
    if (reqVar::get('loadAuthors') !== false)
    {
        ?>
        for(i=document.all["author"].length; i>=0; i--)
        {
            document.all["author"].options[i] = null;
        }
        <?
        $employeeCode = reqVar::get('loadAuthors');
        $res = dbProc::getUsersList(false, false, false, false, false, false, 'ASC', false);
        if (is_array($res) && count($res)>0)
        {
            ?>
            document.all["author"].options[0] = new Option('<?=addslashes(text::get('EMPTY_SELECT_OPTION'));?>', '');
            <?
            $i = 1;
            foreach ($res as $row)
            {
                // Show only active RBF users with matching employee code
                if($row['RLTT_IR_AKTIVS'] == 1 && $row['RLTT_KWOI_KODS'] == $employeeCode && $row['RLTT_IR_RBF'] == 1)
                {
                    ?>
                    document.all["author"].options[<?=$i;?>] = new Option('<?=addslashes($row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS']);?>', '<?=$row['RLTT_ID'];?>');
                    <?
                    $i++;
                }
            }
        }
    }
    
    exit;
}

// Get act ID if editing
$actId = reqVar::get('actId');
$tab = reqVar::get('tab');
if(!$tab) $tab = 'RBF_WORKS';

// Success message handling - check for flash message first, then URL param (for backwards compatibility)
$successMessage = false;
if (session::hasFlash('successMessage'))
{
    $successMessage = session::getFlash('successMessage');
}
else if (reqVar::get('successMessage'))
{
    $successMessage = reqVar::get('successMessage');
}

// Get user's employee code
$userEmployeeCode = false;
$userInfo = dbProc::getUserInfo($userId);
if(count($userInfo) > 0)
{
    $userEmployeeCode = $userInfo[0]['RLTT_KWOI_KODS'];
}

// Load act data if editing
if($actId != false)
{
    $actInfo = dbProc::getRbfActInfo($actId);
    
    if(!$actInfo)
    {
        RequestHandler::showErrorAndDie(text::get('ERROR_ACT_NOT_FOUND'));
    }
    
    $act = $actInfo;
    $status = $act['RAKT_STATUS'];
}
else
{
    $status = STAT_INSERT;
    $act = array();
}

// Determine field editability
$isReadonly = ($status != STAT_INSERT && $status != STAT_RETURN);
$isReadonlyExceptAdmin = $isReadonly && !$isAdmin;

// Capitalize field can be edited by economist in ACCEPT status
$isCapitalizeDisabled = !($status == STAT_ACCEPT && ($isEconomist || $isAdmin));

// Create form
$oLink = new urlQuery();
$oLink->addPrm(FORM_ID, 'f.akt.s.30');
if($actId) $oLink->addPrm('actId', $actId);

$oForm = new Form('frmMain', 'post', $oLink->getQuery());
unset($oLink);

// Display success message (only if not empty)
if (!empty($successMessage))
{
    $oForm->addSuccess($successMessage);
}

// Hidden fields
$oForm->addElement('hidden', 'action', '');
$oForm->addElement('hidden', 'actId', '', $actId);
$oForm->addElement('hidden', 'status', '', $status);

// Act number display
if($actId != false)
{
    $oForm->addElement('label', 'actFullNumber', '', 
        isset($act['RAKT_FULL_NUMBER']) ? $act['RAKT_FULL_NUMBER'] : '');
}

// Status display - get status text from database or use act's status text
if(isset($act['STATUS_TEXT']) && !empty($act['STATUS_TEXT'])) {
    $statusText = $act['STATUS_TEXT'];
} else {
    // For new acts or when status text is not available, get it from KRFK table
    $statusInfo = dbProc::getKrfkInfoByName($status);
    $statusText = $statusInfo ? $statusInfo['KRFK_NOZIME'] : '';
}

$oForm->addElement('label', 'statusTxt', text::get('RBF_STATUS'), $statusText);

// Employee dropdown (from kl_rbf_darbuznemeji)
$employeeOptions = array();
$employeeOptions[''] = text::get('EMPTY_SELECT_OPTION');
$empList = dbProc::getRbfEmployeeActiveList();
if(is_array($empList))
{
    foreach($empList as $emp)
    {
        // For non-admin RBF users, show only their own employee
        if(!$isAdmin && $userEmployeeCode && $emp['RBDU_KODS'] != $userEmployeeCode)
        {
            continue;
        }
        $employeeOptions[$emp['RBDU_KODS']] = $emp['RBDU_KODS'] . ' - ' . $emp['RBDU_NOSAUKUMS'];
    }
}

// Employee dropdown is disabled for non-admin RBF users and when in readonly status
$employeeDisabled = '';
if($isReadonlyExceptAdmin)
{
    $employeeDisabled = ' disabled';
}
elseif(!$isAdmin && $userEmployeeCode)
{
    $employeeDisabled = ' disabled';
}

// Create xmlHttp link for AJAX dropdowns
$oLink = new urlQuery();
$oLink->addPrm(DONT_USE_GLB_TPL, 1);
$oLink->addPrm(FORM_ID, 'f.akt.s.30');

$oForm->addElement('select', 'employeeCode', text::get('RBF_EMPLOYEE'), 
    isset($act['RAKT_KWOI_KODS']) ? $act['RAKT_KWOI_KODS'] : ($userEmployeeCode ? $userEmployeeCode : ''),
    $employeeDisabled . ' onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&employeeCode=\'+this.value+\'\')); eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&loadAuthors=\'+this.value+\'\'))"',
    '', '', $employeeOptions);

// Author dropdown (users with same employee code as selected employee)
$selectedEmployeeCode = isset($act['RAKT_KWOI_KODS']) ? $act['RAKT_KWOI_KODS'] : ($userEmployeeCode ? $userEmployeeCode : '');
$authorOptions = array();
$authorOptions[''] = text::get('EMPTY_SELECT_OPTION');
$authorsList = dbProc::getUsersList(false, false, false, false, false, false, 'ASC', false);
if(is_array($authorsList) && $selectedEmployeeCode)
{
    foreach($authorsList as $author)
    {
        // Show only active RBF users with the same employee code as selected employee
        if($author['RLTT_IR_AKTIVS'] == 1 && $author['RLTT_KWOI_KODS'] == $selectedEmployeeCode && $author['RLTT_IR_RBF'] == 1)
        {
            $authorOptions[$author['RLTT_ID']] = $author['RLTT_VARDS'] . ' ' . $author['RLTT_UZVARDS'];
        }
    }
}

// Author dropdown is disabled for non-admin RBF users and when in readonly status
$authorDisabled = '';
if($isReadonlyExceptAdmin)
{
    $authorDisabled = ' disabled';
}
elseif(!$isAdmin && $userEmployeeCode)
{
    $authorDisabled = ' disabled';
}

$oForm->addElement('select', 'author', text::get('RBF_AUTHOR'), 
    isset($act['RAKT_RLTT_ID']) ? $act['RAKT_RLTT_ID'] : $userId,
    $authorDisabled . ' id="author"',
    '', '', $authorOptions);

// VV Number dropdown (populated via AJAX based on employee)
$vvOptions = array();
$vvOptions[''] = text::get('EMPTY_SELECT_OPTION');

// Pre-populate VV numbers if employee is already selected
if($selectedEmployeeCode)
{
    $vvList = dbProc::getRbfEmployeeVVList($selectedEmployeeCode);
    if(is_array($vvList))
    {
        foreach($vvList as $vv)
        {
            $vvOptions[$vv['RBDV_VV_NUMURS']] = $vv['RBDV_VV_NUMURS'];
        }
    }
}

$oForm->addElement('select', 'vvNumber', text::get('RBF_VV_NUMBER'), 
    isset($act['RAKT_VV_NUMBER']) ? $act['RAKT_VV_NUMBER'] : '',
    ($isReadonlyExceptAdmin ? ' disabled' : '') . ' onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&vvNumber=\'+this.value+\'\'))"',
    '', '', $vvOptions);

// Act Type dropdown - different types based on RAKT_IS_AUTO
// Manual acts (RAKT_IS_AUTO = 0): NĪAD (50) and Ceļu remonts (100)
// Automatic acts (RAKT_IS_AUTO = 1): Bojājums (20), Stihija(40), Pers(90), Plāns(10), Defekts (30)
$isAuto = isset($act['RAKT_IS_AUTO']) ? $act['RAKT_IS_AUTO'] : 0;
$actTypeOptions = array();
$actTypeOptions[''] = text::get('EMPTY_SELECT_OPTION');
$actTypesList = dbProc::getRbfActTypes($isAuto);
if(is_array($actTypesList))
{
    foreach($actTypesList as $type)
    {
        $actTypeOptions[$type['KAKV_ID']] = $type['KAKV_NOSAUKUMS'];
    }
}

$oForm->addElement('select', 'actType', text::get('RBF_ACT_TYPE'), 
    isset($act['RAKT_KAKV_ID']) ? $act['RAKT_KAKV_ID'] : '',
    ($isReadonlyExceptAdmin ? ' disabled' : '') . ' id="actType"',
    '', '', $actTypeOptions);

// Department dropdown (populated via AJAX based on VV number)
$deptOptions = array();
$deptOptions[''] = text::get('EMPTY_SELECT_OPTION');

// Pre-populate departments if VV number is already selected or if editing
$selectedVVNumber = isset($act['RAKT_VV_NUMBER']) ? $act['RAKT_VV_NUMBER'] : '';
if($selectedVVNumber)
{
    $deptList = dbProc::getRbfVVTerritories($selectedVVNumber);
    if(is_array($deptList))
    {
        foreach($deptList as $dept)
        {
            // Use territory code as key (RBTR_KODS for U, RBTR_DID_KODS for C)
            $territoryCode = ($dept['RBDU_VV_VEIDS'] == 'U') ? $dept['RBTR_KODS'] : $dept['RBTR_DID_KODS'];
            // For C type, only add if not already present (group by DID code)
            if (!isset($deptOptions[$territoryCode])) {
                $deptOptions[$territoryCode] = $dept['RBTR_NOSAUKUMS'];
            }
        }
    }
}

$oForm->addElement('select', 'department', text::get('RBF_DEPARTMENT'), 
    isset($act['RAKT_KEDI_ID']) ? $act['RAKT_KEDI_ID'] : '',
    ($isReadonlyExceptAdmin ? ' disabled' : '') . ' id="department"',
    '', '', $deptOptions);

unset($oLink);

// Order ID
$oForm->addElement('text', 'orderId', text::get('RBF_ORDER_ID'), 
    isset($act['RAKT_NUM_POSTFIX']) ? $act['RAKT_NUM_POSTFIX'] : '',
    'maxlength="20"' . ($isReadonlyExceptAdmin ? ' disabled' : ''));

// Signature dropdown
$signatureOptions = array();
$signatureOptions[''] = text::get('EMPTY_SELECT_OPTION');
$res=dbProc::getKrfkName('SIGNATURE');
if (is_array($res))  {
  foreach ($res as $row)
  {
    $signatureOptions[$row['nosaukums']]=$row['nozime'];
  }
} 


$oForm->addElement('select', 'signature', text::get('RBF_SIGNING_METHOD'), 
    isset($act['RAKT_SIGNATURE']) ? $act['RAKT_SIGNATURE'] : '',
    ($isReadonlyExceptAdmin ? ' disabled' : '') . ' id="signature"',
    '', '', $signatureOptions);

// Work Title
$oForm->addElement('text', 'workTitle', text::get('RBF_WORK_TITLE'), 
    isset($act['RAKT_WORK_TITLE']) ? $act['RAKT_WORK_TITLE'] : '',
    'maxlength="250"' . ($isReadonlyExceptAdmin ? ' disabled' : ''));

// Notes
$oForm->addElement('textarea', 'notes', text::get('RBF_NOTES'), 
    isset($act['RAKT_PIEZIMES']) ? $act['RAKT_PIEZIMES'] : '',
    'rows="3" cols="50"' . ($isReadonlyExceptAdmin ? ' disabled' : ''));

// Capitalize expenses checkbox - only checked if explicitly set to 1 in database
$capitalizeValue = ($actId != false && isset($act['RAKT_CAPITALIZED']) && $act['RAKT_CAPITALIZED'] == 1) ? 1 : 0;
$capitalizeDisabledAttr = ($isCapitalizeDisabled && !$isAdmin) ? ' disabled' : '';
$oForm->addElement('checkbox', 'capitalize', text::get('RBF_CAPITALIZE'), $capitalizeValue, $capitalizeDisabledAttr);

// Buttons
if(!$isReadonly || !$isReadonlyExceptAdmin)
{
    $oForm->addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 
        'width="70" height="20" onclick="document.forms[\'frmMain\'][\'action\'].value=\''.OP_UPDATE.'\';"');
}

if($actId != false && $isAuto == 0 && ($status == STAT_INSERT || $status == STAT_RETURN))
{
    $oForm->addElement('submitImg', 'export', text::get('RBF_SUBMIT_FOR_APPROVAL'), 'img/btn_120_nodosana.gif', 
        ' height="20" onclick="if(confirm(\''.text::get('CONFIRM_EXPORT').'\')){document.forms[\'frmMain\'][\'action\'].value=\''.OP_EXPORT.'\';} else {return false;}"');
}   
if($actId != false && $status == STAT_ACCEPT && ($isEconomist || $isAdmin))
{
    $oForm->addElement('submitImg', 'accept', text::get('RBF_APPROVE'), 'img/btn_apstiprinat.gif', 
        'width="70" height="20" onclick="if(confirm(\''.text::get('CONFIRM_ACCEPT').'\')){document.forms[\'frmMain\'][\'action\'].value=\''.OP_ACCEPT.'\';} else {return false;}"');
    
    $oForm->addElement('submitImg', 'return', text::get('RBF_RETURN'), 'img/btn_atgriezt.gif', 
        'width="70" height="20" onclick="if(confirm(\''.text::get('CONFIRM_RETURN').'\')){document.forms[\'frmMain\'][\'action\'].value=\''.OP_RETURN.'\';} else {return false;}"');
}

// Back button - show for existing acts or when coming from search
if($actId != false || $isSearch !== false || $searchNum !== false)
{
    $fromRbfSearch = reqVar::get('fromRbfSearch');
    // back button
    if($fromRbfSearch == 1)
    {
      $employeeCodeSearch = reqVar::get('employeeCode');
      $vvNumberSearch = reqVar::get('vvNumber');
      $territoryCodeSearch = reqVar::get('territoryCode');
      $actTypeSearch = reqVar::get('actType');
      $authorIdSearch = reqVar::get('authorId');
      $statusSearch = reqVar::get('status');

      // RBF advanced search form (frame_1) with selected criteria restored
      $oLink=new urlQuery();
      $oLink->addPrm('isSearch', 1);
      $oLink->addPrm('isReturn', 1);
      $oLink->addPrm('selectedId', $actId);
      $oLink->addPrm('employeeCode', $employeeCodeSearch);
      $oLink->addPrm('vvNumber', $vvNumberSearch);
      $oLink->addPrm('territoryCode', $territoryCodeSearch);
      $oLink->addPrm('actType', $actTypeSearch);
      $oLink->addPrm('authorId', $authorIdSearch);
      $oLink->addPrm('status', $statusSearch);
      $oLink->addPrm(FORM_ID, 'f.akt.s.35');
      $actSearchLink=$oLink ->getQuery();
      unset($oLink);

      // RBF acts list (frame_2) with the same criteria
      $oLink=new urlQuery();
      $oLink->addPrm('selectedId', $actId);
      $oLink->addPrm('employeeCode', $employeeCodeSearch);
      $oLink->addPrm('vvNumber', $vvNumberSearch);
      $oLink->addPrm('territoryCode', $territoryCodeSearch);
      $oLink->addPrm('actType', $actTypeSearch);
      $oLink->addPrm('authorId', $authorIdSearch);
      $oLink->addPrm('status', $statusSearch);
      $oLink->addPrm(FORM_ID, 'f.akt.s.35');
      $actListLink=$oLink ->getQuery();
      unset($oLink);
    }
    else
    {
      // legacy search back flow
      $oLink=new urlQuery();
      $oLink->addPrm('isSearch', $isSearch);
      $oLink->addPrm('selectedId', ($isSearch == 1 || $isSearch == 3)?$actId : $searchNum);
      $oLink->addPrm(FORM_ID, 'f.akt.s.9');
      $actSearchLink=$oLink ->getQuery();
      unset($oLink);

      $oLink=new urlQuery();
      $oLink->addPrm('isNumber', ($isSearch == 1 || $isSearch == 3)?0 : $searchNum);
      $oLink->addPrm('selectedId', $actId);
      $oLink->addPrm(FORM_ID, 'f.akt.s.9');
      $actListLink=$oLink ->getQuery();
      unset($oLink);
    }
      $oForm -> addElement('static', 'jsBackButtons', '', '
    			<script>
    			    function reloadBack()
                    {
                        parent["frameTop"].enableFrameControl();
                        window.top.enableResize();
                        window.top.normal();
                        reloadFrame(1,"'.$actSearchLink.'");
                        reloadFrame(2,"'.$actListLink.'");
                        reloadFrame(3,"");
                    }
    			</script>
    		');
      $oForm -> addElement('buttonImg', 'back', text::get('BACK'), 'img/btn_atpakal.gif', 'width="70" height="20" onClick="reloadBack();"');
}

// Handle form submission
if($oForm->getValue('action'))
{
    $action = $oForm->getValue('action');
    
    if($action == OP_UPDATE)
    {
        // Manual validation of required fields
        $employeeCode = $oForm->getValue('employeeCode');
        $author = $oForm->getValue('author');
        $vvNumber = $oForm->getValue('vvNumber');
        $actType = $oForm->getValue('actType');
        $department = $oForm->getValue('department');
        $orderId = $oForm->getValue('orderId');
        $signature = $oForm->getValue('signature');
        $workTitle = $oForm->getValue('workTitle');
        
        if(empty($employeeCode) || empty($author) || empty($vvNumber) || empty($actType) || 
           empty($department) || empty($orderId) || empty($signature) || empty($workTitle))
        {
            $oForm->addError(text::get('ERROR_REQUIRED_FIELD'));
        }
        else
        {
            $notes = $oForm->getValue('notes');
            $capitalize = ($oForm->getValue('capitalize') == 1) ? 1 : 0;
            
            $r = dbProc::saveRbfAct(
                $actId,
                $employeeCode,
                $author,
                $vvNumber,
                $actType,
                $department,
                $orderId,
                $signature,
                $workTitle,
                $notes,
                $capitalize,
                $status
            );
            
            if($r !== false)
            {
                // get inserted record ID
                $r1 = true;
                if($oForm->getValue('action')==OP_INSERT || $actId == false)
                {
                    $actId=dbLayer::getInsertId();
                    // saglaba lietotaja darbiibu
                    dbProc::setUserActionDate($userId, ACT_INSERT);
                    
                    // save status changed time
                    $r1 = dbProc::updateRbfActStatus($actId, $status, $userId);
                }
                else
                {
                    $actId =  $oForm->getValue('actId');
                    // saglaba lietotaja darbiibu
                    dbProc::setUserActionDate($userId, ACT_UPDATE);
                }

                if (!$r || !$r1 )
                {
                    $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                }
                // if operation was compleated succefully, show success mesage and redirect current frame
                if ($r && $r1)
                {
                    $oLink=new urlQuery();
                    $oLink->addPrm(FORM_ID, 'f.akt.s.30');
                    $oLink->addPrm('actId', $actId);
                    $oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));
                    RequestHandler::makeRedirect($oLink->getQuery());
                }
            }
            else
            {
                $oForm->addError(text::get('ERROR_IN_DB_QUERY'));
            }
        }
    }
    else if($oForm->getValue('action') == OP_EXPORT)
    {
            // Get old status before update
            $oldStatus = STAT_INSERT;
            
            // Update act status (INSERT → ACCEPT) - also saves audit record automatically
            $r = dbProc::updateRbfActStatus($actId, STAT_ACCEPT, $userId);
            
            // Save user action
            dbProc::setUserActionDate($userId, ACT_EXPORT);
            // finilize the object
            dbProc::closeObject($actId, 1);
            
            if($r)
            {
                // Send email notification about status change
                email::sendRbfActStatusChangeNotification($actId, $oldStatus, STAT_ACCEPT, $userId);
                
                // Set flash message (will show once after redirect)
                session::setFlash('successMessage', text::get('ACT_SUBMITTED_FOR_APPROVAL'));
                
                $oLink=new urlQuery();
                $oLink->addPrm(FORM_ID, 'f.akt.s.30');
                $oLink->addPrm('actId', $actId);
                RequestHandler::makeRedirect($oLink->getQuery());
            }
            else
            {
                $oForm->addError(text::get('ERROR_IN_DB_QUERY') . dbProc::getError());
            }
       
    }
    else if($oForm->getValue('action') == OP_ACCEPT)
    {
        // Set approve date for works and materials
        if($isAuto == 1) {
            // For automatic acts, only approve works for the current period
            $actLifePeriod = dbProc::getActLifePeriod($actId);
            dbProc::setApproveDate($actId, dbLayer::parseDate(dtime::now()), $actLifePeriod);
            
            // Set approve date for processed RBF works
            dbProc::setRbfWorksApproveDate($actId, dbLayer::parseDate(dtime::now()));
            
            // Set approve date for manual works (DRBI_IS_WORKER = 1)
            // If final export or actLifePeriod = 3, approve all remaining manual works
            // Otherwise, only approve manual works for the current period
            $isFinalExport = !empty($act['RAKT_IR_OBJEKTS_PABEIGTS']);
            $approveAllManual = ($isFinalExport || $actLifePeriod == 3);
            dbProc::setManualWorksApproveDate(
                $actId,
                dbLayer::parseDate(dtime::now()),
                $actLifePeriod,
                $approveAllManual
            );
        } else {
            // For manual acts, approve all works
            dbProc::setApproveDate($actId, dbLayer::parseDate(dtime::now()));
        }

        // Generate PDF
        $idFile = toPdf::exportRbfActPdf($actId, $userId);
        
        if ($idFile !== false)
        {
            // Determine target status for automatic acts
            $targetStatus = STAT_CLOSE;
            $actionType = ACT_CLOSE;
            
            if($isAuto == 1) {
                // Check if period < 3 and there are remaining unapproved works
                $actLifePeriod = dbProc::getActLifePeriod($actId);
                $hasRemainingWorks = dbProc::hasRemainingUnapprovedWorks($actId);
                
                if ($actLifePeriod < 3 && $hasRemainingWorks) {
                    // Set status back to INSERT if there are more works to process
                    $targetStatus = STAT_INSERT;
                    $actionType = ACT_INSERT;
                }
            }
            
            // Save capitalize checkbox value
            $capitalizeValue = $oForm->getValue('capitalize') ? 1 : 0;
            $r = dbProc::updateRbfActCapitalize($actId, $capitalizeValue);  

            // Get old status before update
            $oldStatus = STAT_ACCEPT;
            
            // Update act status - also saves audit record automatically
            $r3 = dbProc::updateRbfActStatus($actId, $targetStatus, $userId);
            
            // Save user action
            dbProc::setUserActionDate($userId, $actionType);
            
            // Send email notification about status change
            if($r3 !== false) {
                email::sendRbfActStatusChangeNotification($actId, $oldStatus, $targetStatus, $userId);
            }
            
            // Debug logging
            if($r === false) error_log("RBF Act Approve - Step 1 updateRbfActCapitalize failed: " . dbProc::getError());
            if($r3 === false) error_log("RBF Act Approve - Step 3 updateRbfActStatus failed: " . dbProc::getError());
            
            // Check critical operations only (setApproveDate is optional for RBF acts)
            if($r !== false && $r3 !== false)
            {
                // Set flash message (will show once after redirect)
                if($targetStatus == STAT_INSERT) {
                    session::setFlash('successMessage', text::get('RBF_PERIOD_APPROVED_REMAINING'));
                } else {
                    session::setFlash('successMessage', text::get('ACT_APPROVED'));
                }
                
                $oLink=new urlQuery();
                $oLink->addPrm(FORM_ID, 'f.akt.s.30');
                $oLink->addPrm('actId', $actId);
                RequestHandler::makeRedirect($oLink->getQuery());
            }
            else
            {
                $errorDetails = dbProc::getError();
                $oForm->addError(text::get('ERROR_IN_DB_QUERY') . ($errorDetails ? ' - ' . $errorDetails : ''));
            }
        }
        else
        {
            $oForm->addError(text::get('ERROR_GENERATING_PDF'));
        }
    }
    else if($oForm->getValue('action') == OP_RETURN)
    {
        if($isAuto == 1) {
            // Reset processed flag for unapproved works
            dbProc::resetUnprocessedRbfWorks($actId);
            
            // Delete unapproved DARBI records for current period
            dbProc::deleteUnapprovedDarbiForCurrentPeriod($actId);
        }

        // open the object
        dbProc::closeObject($actId, 0);

        // Get old status before update
        $oldStatus = STAT_ACCEPT;

        // Return (ACCEPT → RETURN) - also saves audit record automatically
        $r = dbProc::updateRbfActStatus($actId, STAT_RETURN, $userId);
        
        // Save user action
        dbProc::setUserActionDate($userId, ACT_RETURN_ACCEPT);
        
        // Send email notification about status change
        if($r !== false) {
            email::sendRbfActStatusChangeNotification($actId, $oldStatus, STAT_RETURN, $userId);
        }
        
        if($r)
        {
            // Set flash message (will show once after redirect)
            session::setFlash('successMessage', text::get('ACT_RETURNED'));
            
            $oLink=new urlQuery();
            $oLink->addPrm(FORM_ID, 'f.akt.s.30');
            $oLink->addPrm('actId', $actId);
            RequestHandler::makeRedirect($oLink->getQuery());
        }
        else
        {
            $oForm->addError(text::get('ERROR_IN_DB_QUERY') . dbProc::getError());
        }
    }
}

// XMLHTTP handling for dynamic dropdowns
if(isset($_GET['xmlHttp']) && $_GET['xmlHttp'] == 1)
{
    ob_clean();
    
    // Load VV numbers based on employee
    if(isset($_GET['employeeCode']) && !empty($_GET['employeeCode']))
    {
        $employeeCode = $_GET['employeeCode'];
        $vvList = dbProc::getRbfEmployeeVVList($employeeCode);
        
        echo 'console.log("Loading VV for employee: '.$employeeCode.'");';
        echo 'vvNumbers = [];';
        echo 'vvNumbers[0] = ["", "'.addslashes(text::get('EMPTY_SELECT_OPTION')).'"];';
        
        if(is_array($vvList) && count($vvList) > 0)
        {
            echo 'console.log("Found '.count($vvList).' VV numbers");';
            $i = 1;
            foreach($vvList as $vv)
            {
                echo 'vvNumbers['.$i.'] = ["'.$vv['RBDV_VV_NUMURS'].'", "'.$vv['RBDV_VV_NUMURS'].'"];';
                echo 'console.log("VV: '.$vv['RBDV_VV_NUMURS'].'");';
                $i++;
            }
        }
        else
        {
            echo 'console.log("No VV numbers found for employee '.$employeeCode.'");';
        }
        
        echo 'updateVVDropdown();';
        echo 'console.log("VV dropdown updated, count: " + vvNumbers.length);';
    }
    
    // Load departments based on VV number
    if(isset($_GET['vvNumber']) && !empty($_GET['vvNumber']))
    {
        $vvNumber = $_GET['vvNumber'];
        $territories = dbProc::getRbfVVTerritories($vvNumber);
        
        echo 'console.log("Loading departments for VV: '.$vvNumber.'");';
        echo 'departments = [];';
        echo 'departments[0] = ["", "'.addslashes(text::get('EMPTY_SELECT_OPTION')).'"];';
        
        if(is_array($territories) && count($territories) > 0)
        {
            echo 'console.log("Found '.count($territories).' territories");';
            $i = 1;
            foreach($territories as $terr)
            {
                echo 'departments['.$i.'] = ["'.$terr['RBTR_ID'].'", "'.$terr['RBTR_NOSAUKUMS'].'"];';
                echo 'console.log("Territory: '.$terr['RBTR_NOSAUKUMS'].'");';
                $i++;
            }
        }
        else
        {
            echo 'console.log("No territories found for VV '.$vvNumber.'");';
        }
        
        echo 'updateDepartmentDropdown();';
        echo 'console.log("Department dropdown updated, count: " + departments.length);';
    }
    
    // Load authors based on employee code
    if(isset($_GET['loadAuthors']) && !empty($_GET['loadAuthors']))
    {
        $employeeCode = $_GET['loadAuthors'];
        $authors = dbProc::getUsersList(false, false, false, false, false, false, 'ASC', false);
        
        echo 'authors = [];';
        echo 'authors[0] = ["", "'.addslashes(text::get('EMPTY_SELECT_OPTION')).'"];';
        
        if(is_array($authors) && count($authors) > 0)
        {
            $i = 1;
            foreach($authors as $author)
            {
                if($author['RLTT_IR_AKTIVS'] == 1 && $author['RLTT_KWOI_KODS'] == $employeeCode)
                {
                    echo 'authors['.$i.'] = ["'.$author['RLTT_ID'].'", "'.addslashes($author['RLTT_VARDS'].' '.$author['RLTT_UZVARDS']).'"];';
                    $i++;
                }
            }
        }
        
        echo 'updateAuthorDropdown();';
    }
    
    exit;
}

// JavaScript for AJAX is now in the template file f.akt.s.30.tpl

$oForm->makeHtml();
include('f.akt.s.30.tpl');

// Add tabs (show for both new and existing acts) - rendered AFTER the form
$tabs = new tabs("rbfAct", "");
$tabs->active = text::get($tab);

$tabs->start(text::get('RBF_WORKS'));
if($actId != false)
{
    // Use different work management based on act type
    // Automatic acts (RAKT_IS_AUTO = 1) use f.akt.s.34.inc
    // Manual acts (RAKT_IS_AUTO = 0) use f.akt.s.31.inc
    if($isAuto == 1)
    {
        include('f.akt.s.34.inc');
    }
    else
    {
        include('f.akt.s.31.inc');
    }
}
else
{
    echo '<div style="padding: 20px; text-align: center; color: #666;">'.text::get('RBF_WORKS_EMPTY').'</div>';
}
$tabs->end();

$tabs->start(text::get('RBF_ATTACHMENTS'));
if($actId != false)
{
    include('f.akt.s.32.inc');
}
else
{
    echo '<div style="padding: 20px; text-align: center; color: #666;">'.text::get('RBF_ATTACHMENTS_EMPTY').'</div>';
}
$tabs->end();

$tabs->start(text::get('RBF_STATUS_HISTORY'));
if($actId != false)
{
    include('f.akt.s.7.inc');
}
else
{
    echo '<div style="padding: 20px; text-align: center; color: #666;">'.text::get('RBF_STATUS_HISTORY_EMPTY').'</div>';
}
$tabs->end();

$tabs->run();
?>

