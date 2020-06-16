<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);
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



// tikai  sist?mas lietotajam vai administr?toram ir pieeja!
if ( $isAdmin || $isSystemUser)
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
  	}
  }
  else
  {
    // get default statuss
    $statusInfo = dbProc::getKrfkInfoByName(STAT_INSERT);
    $status = $statusInfo['KRFK_VERTIBA'];
    $statusLabel = $statusInfo['KRFK_NOZIME'];    
    $worker = userAuthorization::getWorker();

  }

 
  $ouner = array();
  if($worker !== false) {
    $res = dbProc::getUserWorkerList($worker);
  } else {
    $res = dbProc::getActiveUserList();
  }
  
  if (is_array($res))
  {
    foreach ($res as $row)
    {
      $ouner[$row['RLTT_ID']]=$row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS'];
    }
  }
  unset($res);
  

  $isReadonly   = true;
  $isReadonly1   = true;
  $isReadonlyExceptAdmin   = true;
  $isReadonlyExceptEconomist   = true;

  if($actId != false)
  {
    // Ir pieejams main??anai, ja  AKTS:LIETOT?JS = �Teko?ais lietot?js� un lietot?ja loma ir �Ievad?tais� un AKTS:STATUS = �Izveide� vai �Atgriezts� vai �T?me�.
    if(($act['RAKT_RLTT_ID'] == $userId && ($isEditor || $isAdmin) && ($status == STAT_INSERT || $status == STAT_RETURN )) )
    {
      $isReadonly   = false;
    }
    // labo autors, inženieris, administrators
    if(($act['RAKT_RLTT_ID'] == $userId || $isAdmin) && ($status == STAT_INSERT || $status == STAT_RETURN ) )
    {
      
      $isReadonly1   = false;
    }
    // Ir pieejams main??anai, ja  �Teko?ais lietot?js� ir Sist?mas administrators un AKTS:STATUS = �Izveide� vai �Atgriezts� vai �T?me�.
    if($isAdmin && ($status == STAT_INSERT || $status == STAT_RETURN ))
    {	
      $isReadonlyExceptAdmin   = false;
    }
	
    //Ir pieejams main??anai, ja   Teko?a lietot?ja loma = �Ekonomists�  un AKTS:STATUS = �Saska?o?ana�.
    if($isEconomist && $status == STAT_ACCEPT )
    {
      $isReadonlyExceptEconomist   = false;
    }

    
  }
  else
  {
     if(($isEditor || $isAdmin) && $status == STAT_INSERT)
     {
        $isReadonly   = false;
        $isReadonly1   = false;
     }
	 if($isAdmin && ($status == STAT_INSERT || $status == STAT_RETURN ))
	 {	
		$isReadonlyExceptAdmin   = false;
		
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
    $actNumber = (isset($act['KEDI_KODS'])?$act['KEDI_KODS']:'') .
                (isset($act['RAKT_NUMURS'])?$act['RAKT_NUMURS']:'').
                (isset($act['RAKT_NUMURS_OBJEKTA'])?$act['RAKT_NUMURS_OBJEKTA']:'0').
                ((true)? "/":"");
    /*$oForm -> addElement('label', 'eDcode',  text::get('ACT_NUMBER'), isset($act['ED_KODS'])?$act['ED_KODS']:'');
    $oForm -> addElement('label', 'typeCode',  '', isset($act['TYPE_CODE'])?$act['TYPE_CODE']:'');
    $oForm -> addElement('label', 'actNumber',  text::get('ACT_NUMBER'), isset($act['RAKT_NUMURS'])?$act['RAKT_NUMURS']:'');
    $oForm -> addElement('label', 'objNumber',  '', isset($act['RAKT_NUMURS_OBJEKTA'])?$act['RAKT_NUMURS_OBJEKTA']:'0');*/
    /* $oForm -> addElement('label', 'actFullNumber',  text::get('ACT_NUMBER'), isset($act['RAKT_FULL_NUMBER'])?$act['RAKT_FULL_NUMBER']:'');  */
    $oForm -> addElement('label', 'actFullNumber',  text::get('ACT_NUMBER'), $actNumber);
   
  }
  

  $oForm -> addElement('select', 'EDarea',  text::get('ED_AREA'), isset($act['RAKT_KEDI_ID'])?$act['RAKT_KEDI_ID']:'', ''.(($isReadonlyExceptAdmin || ($actId != false))?' disabled':'').'', '', '', $edarea);
  if (!$isReadonly1)
  {
    $oForm -> addRule('EDarea', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }
 
  
  $oForm -> addElement('select', 'ouner',  text::get('ACT_OUNER'), isset($act['RAKT_RLTT_ID'])?$act['RAKT_RLTT_ID']:$userId, ''.(($isReadonlyExceptAdmin || !$isEconomist)?' disabled':'').'', '', '', $ouner);
  
  if (!$isReadonlyExceptAdmin)
  {
    $oForm -> addRule('ouner', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

  $oForm -> addElement('kls', 'worker',  text::get('SINGL_WORK_OWNER'), array('classifName'=>KL_WORK_OWNERS,'value'=>isset($act['RAKT_KWOI_KODS'])?$act['RAKT_KWOI_KODS']:(($isReadonlyExceptAdmin)?userAuthorization::getWorker(): ''),'readonly'=>false), (($isReadonlyExceptAdmin) ? ' disabled' : ' ') . ' maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&worker=\'+this.value))"');

  if (!$isReadonlyExceptAdmin)
  {
    $oForm -> addRule('worker', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

  $oForm -> addElement('text', 'numPostfix',  text::get('ACT_NUM_POSTFIX'), isset($act['RAKT_NUM_POSTFIX'])?$act['RAKT_NUM_POSTFIX']:'', 'maxlength="16" disabled');

  $oForm -> addElement('text', 'worktitle',  text::get('PRINT_WORK_TITLE'), isset($act['RAKT_WORK_TITLE'])?$act['RAKT_WORK_TITLE']:'', 
                        'tabindex=6 maxlength="250"'.(($isReadonly1)?' disabled':''));
  if (!$isReadonly)
  {        
        $oForm -> addRule('worktitle', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

  $oForm -> addElement('text', 'year',  text::get('YEAR'), isset($act['RAKT_GADS'])?$act['RAKT_GADS']:'', 
                        'tabindex=6 maxlength="4"'.(($isReadonly1)?' disabled':''));
  if (!$isReadonly)
  {        
        $oForm -> addRule('year', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }
  
  

  // form buttons
  if (!$isReadonly || !$isReadonlyExceptAdmin)
  {
    $oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat_g.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {setValue(\'action\',\''.OP_INSERT.'\');}"');

  }
  if (!$isReadonly)
  {

    $oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshField();'));
    $oForm -> addElement('static', 'jsButtonsControl', '', '
			<script>
				function refreshField()
				{

                    document.all["status"].value = "'.$status.'";
				}
				refreshField();

			</script>
		');

  }
  if (!$isReadonly1 && ($actId != false))
  {
    $oForm -> addElement('submitImg', 'export', text::get('EXPORT'), 'img/btn_nodot_saskanosanai.gif', ' height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\') && isDeleteWithMessage(\''.text::get('WARNING_EXPORT').'\')) {setValue(\'action\',\''.OP_EXPORT.'\');} else {return false;}"');
  }
  
  if (!$isReadonlyExceptEconomist)
  {
    $oForm -> addElement('submitImg', 'return', text::get('RETURN'), 'img/btn_atgriezt.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_RETURN').'\')) {setValue(\'action\',\''.OP_RETURN.'\');} else {return false;}"');
    $oForm -> addElement('submitImg', 'accept', text::get('ACCEPT'), 'img/btn_apstiprinat.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_ACCEPT').'\')) {setValue(\'action\',\''.OP_ACCEPT.'\');} else {return false;}"');
  }

  if ($isAdmin && ($actId != false) && ($status == STAT_DELETE || $status == STAT_CLOSE))
  {
    $oForm -> addElement('submitImg', 'return', text::get('RETURN'), 'img/btn_atgriezt.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_RETURN').'\')) {setValue(\'action\',\''.OP_RETURN_CONFIRMED.'\');} else {return false;}"');
  }
  if($actId != false)
  {
      // back button
      // act advanced search form
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', $isSearch);
        $oLink->addPrm('selectedId', ($isSearch == 1)?$actId : $searchNum);
    	$oLink->addPrm(FORM_ID, 'f.akt.s.9');
    	$actSearchLink=$oLink ->getQuery();
    	unset($oLink);
        // list of acts
    	$oLink=new urlQuery();
        $oLink->addPrm('isNumber', ($isSearch == 1)?0 : $searchNum);
        $oLink->addPrm('selectedId', $actId);
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
  

  if ($oForm -> isFormSubmitted())
  {
    if ($oForm->getValue('action')==OP_INSERT ||
        ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('actId'))) ||
        ($oForm->getValue('action')==OP_EXPORT && is_numeric($oForm->getValue('actId'))) 
        )
	  {
         $check = true;
    	  $r = false;
          $r1 = true;
          $r2 = true;
          $checkRequiredFields = false;
         
         $actNumber = false;
         if (($isEditor ||$isAdmin) && $oForm -> getValue('status') && $oForm -> getValue('EDarea') &&
             $oForm -> getValue('year')  &&  $oForm -> getValue('worker') &&  $oForm -> getValue('numPostfix') 
            )
    	{
          $checkRequiredFields = true;
    	}

        if ($isAdmin  && !$oForm -> getValue('ouner')  )
        {
              $checkRequiredFields = false;
        }

        // if all is ok, do operation
		  if($check)
		  {
		    // save
            if($oForm->getValue('action')==OP_INSERT || $oForm->getValue('action')==OP_UPDATE)
            {
      
    		}
            // export
            if($oForm->getValue('action')==OP_EXPORT )
            {

            }

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
                        $oLink->addPrm('tab', TAB_ESTIMATE);
              break;
           
              }
            RequestHandler::makeRedirect($oLink->getQuery());
        }
    }
	 else
	 {
	  	$oForm->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
	 }
  }
  if (($oForm->getValue('action')==OP_RETURN && is_numeric($oForm->getValue('actId'))) ||
          ($oForm->getValue('action')==OP_ACCEPT && is_numeric($oForm->getValue('actId'))) )
	{
       	 $r = false;
         $r1 = true;
       	 $checkRequiredFields = false;
  
    }



  $oForm -> makeHtml();
  include('f.akt.s.20.tpl');

}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>