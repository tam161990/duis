<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isSuperAdmin=userAuthorization::isSuperAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isProjector = dbProc::isExistsUserRoleWithProject($userId)  ;
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);
$projectApprover = dbProc::isUserInRole($userId, ROLE_PROJ_APPROVER);

// act ID
$actId  = reqVar::get('actId');
// tab name
$tab  = reqVar::get('tab');
// search form
$isSearch  = reqVar::get('isSearch');
// search act by number
$searchNum  = reqVar::get('searchNum');
if($tab === false)
{
  $tab = TAB_WORKS;
}
$isNew  = reqVar::get('isNew');
$isProject = 1;

// Main form with XMLHTTP method load this code:
  if (reqVar::get('xmlHttp') == 1)
  {    
    
    if(reqVar::get('worker'))
      {
          $res=dbProc::getProjectorWorkerList(reqVar::get('worker'));
          if (is_array($res))
          {
          ?>
            document.all['ouner'].disabled = false;
            for(i=document.all["ouner"].length; i>=0; i--)
            {
              document.all["ouner"].options[i] = null;
            }
            <?
              $i = 1;
              foreach ($res as $row)
              {					 
                  ?>
                  document.all["ouner"].options[<?=$i;?>] = new Option( '<?=$row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS'];?>', '<?=$row['RLTT_ID'];?>');
                  
                  <?
                  $i++;
              }	
          }
          unset($res);
    }
 
    exit;
      
  }



// tikai  sist?mas lietotajam vai administr?toram ir pieeja!
if ( $isAdmin || $isProjector || $projectApprover )
{
  $oLink=new urlQuery();
  $oLink->addPrm(FORM_ID, 'f.akt.s.20');
  $oLink->addPrm('isSearch', $isSearch);
  $oLink->addPrm('searchNum', $searchNum);
  $oForm = new Form('frmMain','post',$oLink->getQuery());
  unset($oLink);

  // get user info
  $userInfo = dbProc::getUserInfo($userId);
  if(count($userInfo) >0 )
  {
  	$user = $userInfo[0];
  }

  $edarea=array();
  $edarea['']=text::get('EMPTY_SELECT_OPTION');

  $ouner = array();
  $ouner['']=text::get('EMPTY_SELECT_OPTION');

  $type = array();
  $type['']=text::get('EMPTY_SELECT_OPTION');


  // if operation is success, show success message and redirect top frame
  if (reqVar::get('successMessage'))
  {
  	$oForm->addSuccess(reqVar::get('successMessage'));
  	//$oForm->addElement('static','jsRefresh2','','<script>refreshFrame(1);</script>');
  }

  if (reqVar::get('errorMessage'))
  {
  	$oForm->addError(reqVar::get('errorMessage'));
  }

  // get info about system
  $systemInfo = dbProc::getSystemInfo();
  if(count($systemInfo)>0)
  {
  	$info = $systemInfo[0];
  }

  $res=dbProc::getEDAreaActivList();
  if (is_array($res))
  {
        foreach ($res as $row)
        {
            $edarea[$row['KEDI_ID']]=$row['KEDI_NOSAUKUMS'];
        }
  }
  unset($res);

  $res = dbProc::getKrfkName('PROJECT_TYPE');
  if (is_array($res))
  {
        foreach ($res as $row)
        {
            $type[$row['nosaukums']]=$row['nozime'];
        }
  }
  unset($res);

  
  if($actId != false)
  {
  	// get info about voltage
  	$actInfo = dbProc::getActInfo($actId);
  	//print_r($actInfo);
  	if(count($actInfo)>0)
  	{
  		  $act = $actInfo[0];
        $status = $act['RAKT_STATUS'];
        $statusLabel =  $act['STATUS_NAME'];
        $worker = $act['RAKT_KWOI_KODS'];

        if($worker !== false && !empty($worker)) 
        {
          if( !$isEditor && !$isAdmin  && !$projectApprover) { 
            $res = dbProc::getUserInfo($userId);
          } 
          else { 
            $res = dbProc::getProjectorWorkerList($worker);
          }
        } 
        else {
          $res = dbProc::getProjectorWorkerList(-1);       
        }  	
  	}
  }
  else
  {
    // get default statuss
    $statusInfo = dbProc::getKrfkInfoByName(STAT_INSERT);
    $status = $statusInfo['KRFK_VERTIBA'];
    $statusLabel = $statusInfo['KRFK_NOZIME'];    
    $worker = userAuthorization::getWorker();

    if( !$isEditor) {        
      $res = dbProc::getUserInfo($userId);
      $worker = dbProc::getWorkOwnerCode(ST);
    }
    if($isAdmin) {
      $res = dbProc::getProjectorWorkerList();
    }
  }

  if (is_array($res))
  {
    foreach ($res as $row)
    {
      $ouner[$row['RLTT_ID']]=$row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS'];
    }
    unset($res);
  }
  
  

  $isReadonly   = true;
  $isReadonly1   = true;
  $isReadonlyExceptAdmin   = true;
  $isReadonlyExceptEconomist   = true;
  $isDelete   = false;

  if($actId != false)
  {

    // Ir pieejams main??anai, ja  AKTS:LIETOT?JS = �Teko?ais lietot?js� un lietot?ja loma ir �Ievad?tais� un AKTS:STATUS = �Izveide� vai �Atgriezts� vai �T?me�.
    if(($isProjector || $isAdmin) && ($status == STAT_AUTO) )
    {
      $isReadonly   = false;
    }
    // labo autors, inženieris, administrators
    if( ($isProjector || $isAdmin) && !$projectApprover  && ($status == STAT_INSERT || $status == STAT_RETURN ) )
    {      
      $isReadonly1   = false;
    }
    // Ir pieejams main??anai, ja  �Teko?ais lietot?js� ir Sist?mas administrators 
    if($isAdmin && ($status == STAT_AUTO  || $status == STAT_INSERT || $status == STAT_RETURN ) )
    {	
      $isReadonlyExceptAdmin   = false;
    }
	
    //Ir pieejams main??anai, ja   Teko?a lietot?ja loma = �Ekonomists�  un AKTS:STATUS = �Saska?o?ana�.
    if((($projectApprover && (!$isProjector || ($isProjector && $act['RAKT_RLTT_ID'] <> $userId) )) || 
          $isAdmin
        ) && 
        ( $status == STAT_ACCEPT  || $status == STAT_CLOSE)
      )
    {
      $isReadonlyExceptEconomist   = false;
    }

    //if(($act['RAKT_RLTT_ID'] == $userId && $isProjector && ($status == STAT_INSERT || $status == STAT_RETURN ) ) ||
    if ($isAdmin && $status != STAT_DELETE)
    {
      $isDelete   = true;
    }
  }
  else
  {
    if($isAdmin){
      $isReadonly   = false;	 
      $isReadonlyExceptAdmin = false; 
    }  
  }

  // form elements  
  $oForm -> addElement('hidden', 'isSearch', '', $isSearch);
  $oForm -> addElement('hidden', 'searchNum', '', $searchNum);
  $oForm -> addElement('hidden', 'action', '');
  $oForm -> addElement('hidden', 'actId', null, isset($act['RAKT_ID'])? $act['RAKT_ID']:'');
  $oForm -> addElement('hidden', 'status', null, $status);
  $oForm -> addElement('label', 'statusTxt',  text::get('STATUS'), $statusLabel);  
  $oForm -> addElement('hidden', 'actNumber',  '', isset($act['RAKT_NUMURS'])?$act['RAKT_NUMURS']:'');

  $oLink=new urlQuery();
  $oLink->addPrm(DONT_USE_GLB_TPL, 1);
  $oLink->addPrm(FORM_ID, 'f.akt.s.20');
  $oLink->addPrm('actId', $actId);
  $oLink->addPrm('worker', userAuthorization::getWorker() );
 
  if($actId != false)
  {
      $oForm -> addElement('label', 'actFullNumber',  text::get('ACT_NUMBER'), isset($act['RAKT_FULL_NUMBER'])?$act['RAKT_FULL_NUMBER']:'', 'width="70" '); 
  }   
  
  $oForm -> addElement('text', 'CODEVAL',  text::get('CODE'), isset($act['RAKT_PROJECT_NO'])?$act['RAKT_PROJECT_NO']:'', 'maxlength="16" '.(($isAdmin || $isSuperAdmin)? '' : ' disabled').'');
  
  $oForm -> addElement('date', 'construction_date',  text::get('PLAN_CONSTRACTION_DATE'), isset($act['RAKT_CONSTRACTION_DATE'])?$act['RAKT_CONSTRACTION_DATE']:'', 'tabindex=4 maxlength="10"'.(($isAdmin || $isSuperAdmin)? '' : ' disabled'));
  
  $oForm -> addElement('select', 'EDarea',  text::get('ED_AREA'), isset($act['RAKT_KEDI_ID'])?$act['RAKT_KEDI_ID']:'', ''.(($isReadonlyExceptAdmin )?' disabled':'').'', '', '', $edarea);
    
  $oForm -> addElement('select', 'ouner',  text::get('ACT_OUNER'), isset($act['RAKT_RLTT_ID'])?$act['RAKT_RLTT_ID']:(($isEditor) ? '' : $userId), ''.((!$isReadonlyExceptAdmin || !$isReadonly )? '' :' disabled').'', '', '', $ouner);
  
  $oForm -> addElement('select', 'type',  text::get('SINGLE_ACT_TYPE'), isset($act['RAKT_PROJECT_TYPE'])?$act['RAKT_PROJECT_TYPE']:'', ''.(($isReadonlyExceptAdmin )?' disabled':'').'', '', '', $type);
  
  if ($isReadonlyExceptAdmin)
  {
    $oForm -> addRule('ouner', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }
  if($act['RAKT_KEY_OBJECT'] == '1') {
    $oForm -> addElement('text', 'constract_company',  text::get('SINGL_WORK_OWNER'), isset($act['RAKT_CONSTRUCT_COMPANY'])?$act['RAKT_CONSTRUCT_COMPANY']:'', 'maxlength="250" '.((!$isReadonlyExceptAdmin || !$isReadonly )? '' : ' disabled'));
  } else {
  $oForm -> addElement('kls', 'worker',  text::get('SINGL_WORK_OWNER'), 
  array('classifName'=>KL_WORK_OWNERS,
        'value'=>isset($act['RAKT_KWOI_KODS'])?$act['RAKT_KWOI_KODS']: (($isEditor) ? '' : $worker),
        'readonly'=>false), 
        ((!$isReadonlyExceptAdmin || !$isReadonly )? '' : ' disabled') . ' maxlength="2000" '.
        ((!$isEditor) ? '' : 'onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&worker=\'+this.value))"'));
  }
  $oForm -> addElement('text', 'numPostfix',  text::get('ACT_NUM_POSTFIX'), isset($act['RAKT_NUM_POSTFIX'])?$act['RAKT_NUM_POSTFIX']:'', 'maxlength="16" '.(($isReadonlyExceptAdmin )?' disabled':''));

  $oForm -> addElement('text', 'worktitle',  text::get('PRINT_WORK_TITLE'), isset($act['RAKT_WORK_TITLE'])?$act['RAKT_WORK_TITLE']:'', 
                        'tabindex=6 maxlength="250"'.(($isReadonlyExceptAdmin)?' disabled':''));
  
  $oForm -> addElement('text', 'year',  text::get('INVESTICION_DATE'), isset($act['RAKT_IZPILDES_DATUMS'])?substr($act['RAKT_IZPILDES_DATUMS'],6,4):'', 
                        'tabindex=6 maxlength="10"'.(($isReadonlyExceptAdmin)?' disabled':''));
  if (!$isReadonlyExceptAdmin)
  { 
        $oForm -> addRule('EDarea', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('worker', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('numPostfix', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('worktitle', text::get('ERROR_REQUIRED_FIELD'), 'required');       
        $oForm -> addRule('year', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('type', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }
  
  // form buttons
  if (!$isReadonlyExceptAdmin || !$isReadonly)
  {
    $oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat_g.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {setValue(\'action\',\''.OP_INSERT.'\');}"');
  }
  
  if (!$isReadonly1 && ($actId != false))
  {
    $oForm -> addElement('submitImg', 'export', text::get('EXPORT'), 'img/btn20_120_nodot_saskanosanai.gif', ' height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\') && isDeleteWithMessage(\''.text::get('WARNING_EXPORT').'\')) {setValue(\'action\',\''.OP_EXPORT.'\');} else {return false;}"');
  }
  
  if (!$isReadonlyExceptEconomist)
  {
    if($status == STAT_ACCEPT) {
      $oForm -> addElement('submitImg', 'decline', text::get('RETURN'), 'img/btn_decline.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_RETURN').'\')) {setValue(\'action\',\''.OP_DECLINE.'\');} else {return false;}"');
      $oForm -> addElement('submitImg', 'accept', text::get('ACCEPT'), 'img/btn_apstiprinat.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_ACCEPT').'\')) {setValue(\'action\',\''.OP_ACCEPT.'\');} else {return false;}"');
      
    }
  }

  if($status == STAT_CLOSE) {
    $oForm -> addElement('submitImg', 'order_material', text::get('ORDER_MATERIAL'), 'img/btn_order_material_120.gif', 'width="120" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')) {setValue(\'action\',\''.OP_ORDER_MATERIAL.'\');setPosition1(\'loading\');} else {return false;}"');
  }

  if (!$isReadonlyExceptEconomist && ($status == STAT_DELETE || $status == STAT_CLOSE))
  {
    $oForm -> addElement('submitImg', 'return', text::get('RETURN'), 'img/btn_atgriezt.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_RETURN').'\')) {setValue(\'action\',\''.OP_RETURN.'\');} else {return false;}"');
  }
  if($actId != false)
  {
      // back button
      // act advanced search form
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', $isSearch);
      $oLink->addPrm('selectedId', ($isSearch == 1 || $isSearch == 3)?$actId : $searchNum);
    	$oLink->addPrm(FORM_ID, 'f.akt.s.9');
    	$actSearchLink=$oLink ->getQuery();
    	unset($oLink);
        // list of acts
    	$oLink=new urlQuery();
      $oLink->addPrm('isNumber', ($isSearch == 1 || $isSearch == 3)? 0 : $searchNum);
      $oLink->addPrm('selectedId', $actId);
      $oLink->addPrm('isProject', 1);
    	$oLink->addPrm(FORM_ID, 'f.akt.s.9');
    	$actListLink=$oLink ->getQuery();
    	unset($oLink);
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
  
  if ($isDelete)
  {
    $oForm -> addElement('submitImg', 'delete', text::get('DELETE'), 'img/btn_dzest_r.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\') && isDeleteWithMessage(\''.text::get('WARNING_DELETE').'\')) {setValue(\'action\',\''.OP_DELETE.'\');} else {return false;}"');
  }
  if($status == STAT_CLOSE && ($isAdmin || $projectApprover || $projectApprover))
  {
    $oForm -> addElement('submitImg', 'make_excel', text::get('EXPORT'), 'img/btn_make_excel.gif', 'width="90" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\') ) {setValue(\'action\',\''.OP_MIDLE_EXPORT.'\');} else {return false;}"');
  }
  if(($status == STAT_INSERT || $status == STAT_RETURN ) && !$isReadonly1 && $actId != false)
  {
    $oForm -> addElement('submitImg', 'make_excel2', text::get('EXPORT'), 'img/export_to_excel.gif', 'width="90" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\') ) {setValue(\'action\',\''.OP_ESTIMATE.'\');} else {return false;}"');
  }

  if ($oForm -> isFormSubmitted())
  {
    if ($oForm->getValue('action')==OP_INSERT ||
        ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('actId'))) ||
        ($oForm->getValue('action')==OP_EXPORT && is_numeric($oForm->getValue('actId')))  ||
        ($oForm->getValue('action')==OP_ESTIMATE && is_numeric($oForm->getValue('actId')))  ||
        ($oForm->getValue('action')==OP_MIDLE_EXPORT && is_numeric($oForm->getValue('actId'))) 
        )
	  {
         
    	    $r = false;
          $r1 = true;
          $r2 = true;
          $checkRequiredFields = false;
         
         $actNumber = false;
         if ( $oForm -> getValue('status') && $oForm -> getValue('EDarea') &&
             $oForm -> getValue('year')  &&  $oForm -> getValue('worker') &&  
             $oForm -> getValue('numPostfix')  && $oForm -> getValue('type') 
            )
        {
            $checkRequiredFields = true;
        }

        if (!$isAdmin  && !$oForm -> getValue('ouner')  )
        {
              $checkRequiredFields = false;
        }

        // if all is ok, do operation
		  if($checkRequiredFields)
		  { 
		        // save
            if($oForm->getValue('action')==OP_INSERT || $oForm->getValue('action')==OP_UPDATE)
            {
                $r=dbProc::saveAct(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('actId'):false),
                false,
                ($oForm->getValue('action')==OP_INSERT)?0:false,
                date_create($oForm->getValue('year').'-01-01')->format('d.m.Y'), 
                0,
                false,
                false,
                false,
                (($oForm->getValue('status') == STAT_AUTO ) ? STAT_INSERT : $oForm->getValue('status')),
                ($oForm->getValue('ouner'))? $oForm->getValue('ouner'):$userId,
                false,
                false,
                false,
                $oForm->getValue('worker'),
                $oForm->getValue('EDarea'),
                1 ,
                0,
                $oForm->getValue('numPostfix'),
                $oForm->getValue('worktitle'),
                false,
                false,
                false,
                false,
                1,
                1,
                $oForm->getValue('type'),
                $oForm->getValue(strtoupper('codeval')),
                $oForm->getValue('constract_company'),
                false,
                false,
                $oForm->getValue('construction_date')
              );

              // get inserted record ID
              if($oForm->getValue('action')==OP_INSERT)
              {
                  $actId=dbLayer::getInsertId();
                  // saglaba lietotaja darbiibu
                  dbProc::setUserActionDate($userId, ACT_INSERT);
              }
              else
              {
                  $actId =  $oForm->getValue('actId');
                  // saglaba lietotaja darbiibu
                  dbProc::setUserActionDate($userId, ACT_UPDATE);
              }

              // save status changed time
              if($oForm->getValue('action')==OP_INSERT)
              {
                $r1 = dbProc::saveAuditRecord($actId, $userId, $oForm->getValue('status'));
              }
              if (!$r || !$r1 )
              {
                $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
              }
            }
            
            // export
            if($oForm->getValue('action')==OP_EXPORT || $oForm->getValue('action')==OP_ESTIMATE)
            {
              
              if($oForm->getValue('action')==OP_EXPORT && dbProc::checkAllInputFields($oForm->getValue('actId')) == false )
              {
                  $oForm->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
              }
              else 
              {
                  $r=dbProc::saveAct($oForm->getValue('actId'),
                              false,
                              false,
                              false,
                              0,
                              false,
                              false,
                              false,
                              $oForm->getValue('status'),
                              ($oForm->getValue('ouner'))? $oForm->getValue('ouner'):$userId,
                              false,
                              false,
                              false,
                              $oForm->getValue('worker'),
                              $oForm->getValue('EDarea'),
                              1,
                              0,
                              $oForm->getValue('numPostfix'),
                              $oForm->getValue('worktitle'),
                              false,
                              false,
                              false,
                              false,
                              1,
                              1,
                              $oForm->getValue('type'),
                              $oForm->getValue(strtoupper('codeval')),
                              $oForm->getValue('constract_company'),
                              false,
                              false,
                              $oForm->getValue('construction_date')
                  );

                  if ($r )
                  {
                    // get info about voltage
                    $actInfo = dbProc::getActInfo($oForm->getValue('actId'));
                    if(count($actInfo)>0)
                    {
                        $act = $actInfo[0];
                        $regionName = dbProc::GetRefionName($act['RAKT_KEDI_ID']);
                        $departmentName = dbProc::GetDepartmentName($act['RAKT_KEDI_ID']);
                    }
                    // akta sagatavi (tab tamme)
                    $fileId = toPdf::projectTammePdf($actId, $userId, $oForm->getValue('action')==OP_ESTIMATE);
                    if( $fileId === false){
                      $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                    }
                    else {
                      $fileId = toExcel::projectTammeExcel($actId, $userId, $oForm->getValue('action'));
                    }
                    if( $fileId === false){
                        $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                    } else 
                    {
                      if($oForm->getValue('action')==OP_EXPORT) {
                        // update act status
                        $r=dbProc::saveAct($oForm->getValue('actId'),
                                      false,false,false,false,false,false,
                                      true,
                                      STAT_ACCEPT,
                                      ($oForm->getValue('ouner'))? $oForm->getValue('ouner'):$userId,
                                      false,
                                      false,
                                      false,
                                      $oForm->getValue('worker'),
                                      $oForm->getValue('EDarea'),
                                      1,
                                      0,
                                      $oForm->getValue('numPostfix'),
                                      $oForm->getValue('worktitle'),
                                      false,
                                      false,
                                      false,
                                      false,
                                      1,
                                      1
                                    );
                        // save status changed time
                        $r1 = dbProc::saveAuditRecord($actId, $userId, STAT_ACCEPT);
                        // saglaba lietotaja darbiibu
                        dbProc::setUserActionDate($userId, ACT_EXPORT);
    
                        if (!$r || !$r1)
                        {
                          $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                        }
                      }
                    }                
                }
                else
                {
                  $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                }
              }
            }

            // izveidot excel tikai ST darbiniekam
            if($oForm->getValue('action')==OP_MIDLE_EXPORT )
            {
              $fileId = toExcel::projectExportExcel($actId, $userId);
            
              if( $fileId === false){
                  $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
              } else {
                $r = ture;
              }
            }
      }
      else
      {
          $oForm->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
      }
      // if operation was compleated succefully, show success mesage and redirect current frame
		  if ($r)
		  {
          $oLink=new urlQuery();
          $oLink->addPrm(FORM_ID, 'f.akt.s.20');
          $oLink->addPrm('actId', $actId);
          $oLink->addPrm('isSearch', $isSearch);
          $oLink->addPrm('searchNum', $searchNum);
          switch($oForm->getValue('action'))
          {
            case OP_INSERT:
              $oLink->addPrm('successMessage', text::get('RECORD_WAS_ADDED'));
              break;
            case OP_UPDATE:
              $oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));
              break;
            case OP_EXPORT:
              $oLink->addPrm('successMessage', text::get('INFO_WAS_EXPORTED'));
              $oLink->addPrm('tab', TAB_EXPORT);
              break;
            case OP_ESTIMATE:
              $oLink->addPrm('successMessage', text::get('INFO_WAS_EXPORTED'));
              $oLink->addPrm('tab', TAB_EXPORT);
              break;
           
            }
            RequestHandler::makeRedirect($oLink->getQuery());
          }
          unset($oLink);
      }      
    }
    if (($oForm->getValue('action')==OP_RETURN && is_numeric($oForm->getValue('actId'))) ||
        ($oForm->getValue('action')==OP_RETURN_CONFIRMED && is_numeric($oForm->getValue('actId'))) ||
        ($oForm->getValue('action')==OP_ACCEPT && is_numeric($oForm->getValue('actId'))) )
    {
          $r = false;
          $r1 = true;
          $checkRequiredFields = true;
          if ($projectApprover )
          {
                $returnStatus  = STAT_RETURN;
                $returnAction =  STAT_RETURN;
          }
          if ($isAdmin && ($oForm -> getValue('status') == STAT_DELETE || $oForm -> getValue('status') == STAT_CLOSE) )
          {
                if($oForm -> getValue('status') == STAT_DELETE)
                {
                  $returnStatus  = STAT_INSERT;
                  $returnAction =  ACT_RETURN_INSERT;
                }
                if($oForm -> getValue('status') == STAT_CLOSE)
                {
                  $returnStatus  = STAT_ACCEPT;
                  $returnAction =  ACT_RETURN_ACCEPT;
                }
          }
          if($checkRequiredFields)
          {
              // atgriezt vai apstiprin?t
              if($oForm->getValue('action')==OP_RETURN || $oForm->getValue('action')==OP_ACCEPT || $oForm->getValue('action')==OP_RETURN_CONFIRMED)
              {
                $r=dbProc::updateActStatus($oForm->getValue('actId'), 
                ( ($oForm->getValue('action')==OP_RETURN || $oForm->getValue('action')==OP_RETURN_CONFIRMED)? $returnStatus : STAT_CLOSE));  
                 
                if($r)
                {
                    // save status changed time
                    $r1 = dbProc::saveAuditRecord($actId, $userId, 
                      ($oForm->getValue('action')==OP_RETURN || $oForm->getValue('action')==OP_RETURN_CONFIRMED)? 
                      $returnStatus : STAT_CLOSE);
                    dbProc::setUserActionDate($userId, 
                    ($oForm->getValue('action')==OP_RETURN || $oForm->getValue('action')==OP_RETURN_CONFIRMED)? 
                    $returnAction : STAT_CLOSE);

                    if (!$r1)
                    {
                      $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                    }  
                }
                else
                {
                   $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                }

                // sūtit excel link to KS
                if($oForm->getValue('action')==OP_ACCEPT)
                {
                    $fileId = dbProc::getExcelId($actId);
                    if($fileId !== false) {
                        // sūta file link uz KvikStep                            
                        //RequestHandler::sentExcelToKvikStep($oForm->getValue('numPostfix'), $fileId);
                    }
                }
                // if operation was compleated succefully, show success mesage and redirect current frame
                if ($r && $r1)
                {
                      $oLink=new urlQuery();
                      $oLink->addPrm(FORM_ID, 'f.akt.s.20');
                      $oLink->addPrm('actId', $actId);
                      $oLink->addPrm('isSearch', $isSearch);
                      $oLink->addPrm('searchNum', $searchNum);
                      $oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));

                      RequestHandler::makeRedirect($oLink->getQuery());
                      unset($oLink);
                }
            
            }
         }
         else
         {
            $oForm->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
         }
    }

        	// nomainit akta statusu uz dz?sts
          if (($oForm->getValue('action')==OP_DECLINE && is_numeric($oForm->getValue('actId'))) )
          {      
            if(($projectApprover ||  $isAdmin ) && $status = STAT_ACCEPT )
             {       
                  $r=dbProc::updateActStatus($oForm->getValue('actId'), STAT_RETURN);  
                  if($r)
                  {
                      // save status changed time
                      $r1 = dbProc::saveAuditRecord($actId, $userId, STAT_RETURN);
                      dbProc::setUserActionDate($userId, STAT_RETURN);

                      if (!$r1)
                      {
                        $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                      }                    
                  }
                  else
                  {
                    $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                  }
                  // if operation was compleated succefully, show success mesage and redirect current frame
                  if ($r && $r1)
                  {
                        $oLink=new urlQuery();
                        $oLink->addPrm(FORM_ID, 'f.akt.s.20');
                        $oLink->addPrm('actId', $actId);                        
                        $oLink->addPrm('isSearch', $isSearch);
                        $oLink->addPrm('searchNum', $searchNum);
                        $oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));

                        RequestHandler::makeRedirect($oLink->getQuery());
                        unset($oLink);
                  }
              }         
             else
             {
               $oForm->addError(text::get('ERROR_NOT_PERMISSION'));
             }      
         }
    	// nomainit akta statusu uz dz?sts
     if (($oForm->getValue('action')==OP_DELETE && is_numeric($oForm->getValue('actId'))) )
     {      
        if(($act['RAKT_RLTT_ID'] == $userId && $isProjector && ($status == STAT_INSERT || $status == STAT_RETURN) ) ||
           ($isAdmin && ($status != STAT_DELETE))  )
        {          
              $r=dbProc::saveAct($oForm->getValue('actId'),
                      false,
                      false,
                      false,
                      false,
                      false,
                      false,
                      false,
                      STAT_DELETE,
                      false,
                      false,
                      false,
                      false,
                      false,
                      false,
                      false,
                      false,
                      false ,
                      false,
                      false,
                      false,
                      false,
                      false,
                      1,
                      1
                  );
                  
                  if($r)
                  {
                      // save status changed time
                      $r1 = dbProc::saveAuditRecord($actId, $userId, STAT_DELETE);
                      dbProc::setUserActionDate($userId, ACT_DELETE);

                      if (!$r1)
                      {
                        $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                      }                    
                  }
                  else
                  {
                    $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                  }
                  // if operation was compleated succefully, show success mesage and redirect current frame
                  if ($r && $r1)
                  {
                        $oLink=new urlQuery();
                        $oLink->addPrm(FORM_ID, 'f.akt.s.20');
                        $oLink->addPrm('actId', $actId);                        
                        $oLink->addPrm('isSearch', $isSearch);
                        $oLink->addPrm('searchNum', $searchNum);
                        $oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));

                        RequestHandler::makeRedirect($oLink->getQuery());
                        unset($oLink);
                  }
              }         
        else
        {
          $oForm->addError(text::get('ERROR_NOT_PERMISSION'));
        }      
    }
    // 
    // pieprasīt materiālus
    if (($oForm->getValue('action')==OP_ORDER_MATERIAL && is_numeric($oForm->getValue('actId'))) )
    {    

      $fileId = toJson::projectOrderMaterial($actId, $userId);
      $r = false;
      if( $fileId === false){
         $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
      } else {
          // saglaba lietotaja darbiibu
          $r = dbProc::setUserActionDate($userId, OP_ORDER_MATERIAL);
      } 
      // if operation was compleated succefully, show success mesage and redirect current frame
      if ($r)
      {
            $oLink=new urlQuery();
            $oLink->addPrm(FORM_ID, 'f.akt.s.20');
            $oLink->addPrm('actId', $actId);                        
            $oLink->addPrm('isSearch', $isSearch);
            $oLink->addPrm('searchNum', $searchNum);
            $oLink->addPrm('successMessage', text::get('INFO_WAS_EXPORTED'));
            $oLink->addPrm('tab', TAB_EXPORT);

            RequestHandler::makeRedirect($oLink->getQuery());
            unset($oLink);
      }
          
        
    }

    $oForm -> makeHtml();
    include('f.akt.s.20.tpl');

    $tabs = new tabs("akts", "");

    $tabs->start(text::get(TAB_WORKS));
    include('f.akt.s.21.inc');
    $tabs->end();
   
  	$tabs->start(text::get(TAB_MATERIAL));
    include('f.akt.s.22.inc');
    $tabs->end();  
  
    $tabs->start(text::get(TAB_EXPORT));
    include('f.akt.s.10.inc');
    $tabs->end();

    $tabs->start(text::get(TAB_AUDIT));
    include('f.akt.s.7.inc');
    $tabs->end();
    
    $tabs->active = text::get($tab);

    $tabs->run();

}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>