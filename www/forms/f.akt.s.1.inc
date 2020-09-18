<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;
$isEdUser = dbProc::isExistsUserRole($userId);
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);
$isTraseUser = userAuthorization::isTrase();
$isNew  = reqVar::get('isNew');
// act ID
$actId  = reqVar::get('actId');
// tab name
$tab  = reqVar::get('tab');
// tab tame name
$tametab  = reqVar::get('tametab');
// search form
$isSearch  = reqVar::get('isSearch');
// search act by number
$searchNum  = reqVar::get('searchNum');
// paz?me vai ir akta turpin?jums
$isCopy  = reqVar::get('isCopy');
// TRASE act
$trase =  reqVar::get('isTrase');
if($trase === false) $trase = 0;
if($tab === false)
{
  $tab = TAB_WORKS;
}
if($tametab === false)
{
  $tametab = TAB_WORKS_T;
}
// auto akts
$isAuto = reqVar::get('isAuto');
$tame = false;
$isProject = 0;

// Main form with XMLHTTP method load this code:
if (reqVar::get('xmlHttp') == 1)
{    
  
  if(reqVar::get('type') )
  {
      if(dbProc::isActTypePlan(reqVar::get('type')))
      {
        ?>
          //document.all['toid'].disabled = true;
          document.all["toid"].value = '';
        <?
      }
      else
      {
        ?>
          document.all["toid"].value = '';
          //document.all['toid'].disabled = false;
        <?
        if(  reqVar::get('type') == ACT_TYPE_STIHIJA_ID )
        {
          ?>
            document.all["toid"].value = '---';
          <?
        }	 
      }

    }     
	/*
	if(reqVar::get('worker'))
    {
        $res=dbProc::getDuContractNo(reqVar::get('worker'), $trase, true);
        if (is_array($res))
        {
			 ?>
			  document.all['contract'].disabled = false;
			  for(i=document.all["contract"].length; i>=0; i--)
			  {
				document.all["contract"].options[i] = null;
			  }
			  <?
			    $i = 1;
				foreach ($res as $row)
				{					 
					  ?>
					  document.all["contract"].options[<?=$i;?>] = new Option( '<?=$row['KCNT_VV_NUMBER'];?>', '<?=$row['KCNT_VV_NUMBER'];?>');
					  <?
					  $i++;
				}	
        }
        unset($res);

	}
	*/
    
    if(reqVar::get('type') && reqVar::get('contract'))
    {
     
      $PlanKvikStep = dbProc::getActTypePostfix(reqVar::get('type'));
      
      ?>
      document.all['EDarea'].disabled = false;
      for(i=document.all["EDarea"].length; i>=0; i--)
      {
        document.all["EDarea"].options[i] = null;
      }
      <?
      // check is this type set as PLANS
      if(dbProc::isActTypePlan(reqVar::get('type')))
      {
          
           if($trase == 1)
           {
             // define quickStep code
             //
             //$quickStep = dbProc::getMMSWorkCode(reqVar::get('mms'));
             ?>
                 //document.all["numPostfix"].value = suda v php tegah podstavit quickStep;
             <?
             /*
             // define spriegums && objekts value
             $res = dbProc::getMmsVZSum(reqVar::get('mms'));
             if (is_array($res) && count($res) > 0)
             {
                //sum(v) > 0
                if($res[0]['SUM_V'] > 0 && $res[0]['SUM_Z'] == 0)
                { ?>
                     document.all["voltage"].value = '<?=VOLTAGE20KV?>';
                     document.all["object"].value = '<?=OBJECT20KV?>';
                 <?
                }
                //sum(z) > 0
                if($res[0]['SUM_Z'] > 0 && $res[0]['SUM_V'] == 0)
                { ?>
                     document.all["voltage"].value = '<?=VOLTAGE04KV?>';
                     document.all["object"].value = '<?=OBJECT04KV?>';
                 <?
                }
                 //(sum(z) > 0 &  sum(v) > 0) OR   (sum(z) = 0 &  sum(v) = 0)
                if(($res[0]['SUM_Z'] > 0 && $res[0]['SUM_V'] > 0) OR ($res[0]['SUM_Z'] ==0  && $res[0]['SUM_V'] == 0))
                { ?>
                     document.all["voltage"].value = '<?=VOLTAGE20KV?>';
                     document.all["object"].value = '<?=OBJECT20KV?>';
                 <?
                }
             }*/
           }   
            $res=dbProc::getEDAreaNotElementActivList($trase);
            
      }
      elseif((reqVar::get('type') == ACT_TYPE_DAMAGE_ID) || (reqVar::get('type') == ACT_TYPE_DEFECT_ID ) || (reqVar::get('type') == ACT_TYPE_DAMAGE_TR_ID) || (reqVar::get('type') == ACT_TYPE_DEFECT_TR_ID ))
      {
          $res=dbProc::getEDSectionListForWorker(reqVar::get('worker'), reqVar::get('contract'), $trase);
      }
      elseif((reqVar::get('type') == ACT_TYPE_STIHIJA_ID) || (reqVar::get('type') == ACT_TYPE_STIHIJA_TR_ID))
      {
          $res=dbProc::getEDElementSectionList($trase);
      }
      else
      {
        //$res=dbProc::getEDAreaActivList();
        $res=dbProc::getEDAreaNotElementActivList($trase);
      }
      if (is_array($res) && count($res) > 0)
      {
           ?>
            document.all["EDarea"].options[0] = new Option('<?=text::get('EMPTY_SELECT_OPTION');?>', '');
          <?
             $i = 1;
            foreach ($res as $row)
            {
              // feel options array
              ?>
              document.all["EDarea"].options[<?=$i;?>] = new Option( '<?=$row['KEDI_NOSAUKUMS'];?>', '<?=$row['KEDI_ID'];?>');
              <?
               $i++;
            }
      }
      
    }
    exit;
    
}

// tikai  sist?mas lietotajam vai administr?toram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
  $oLink=new urlQuery();
  $oLink->addPrm(FORM_ID, 'f.akt.s.1');
  $oLink->addPrm('isSearch', $isSearch);
  $oLink->addPrm('isTrase', $trase );
  $oLink->addPrm('isAuto', $isAuto);
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

  $contract = array();
  $contract['']=text::get('EMPTY_SELECT_OPTION');

  $signature = array();
  $signature['']=text::get('EMPTY_SELECT_OPTION');

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

  // inicial state: actId=0;
  $isPlan = false;

  // get info about system
  $systemInfo = dbProc::getSystemInfo();
  if(count($systemInfo)>0)
  {
  	$info = $systemInfo[0];
  }

  $res=dbProc::getKrfkName('SIGNATURE');
  if (is_array($res))
  {
  foreach ($res as $row)
  {
    $signature[$row['nosaukums']]=$row['nozime'];
  }
  }

  // get act type
  $acttype=array();
  $acttype['']=text::get('EMPTY_SELECT_OPTION');
	if($trase == 1) {
		$res=dbProc::getActTraseTypeActivList();
	} else {
  		$res=dbProc::getActTypeActivList();
	}
	if (is_array($res))
	{
		foreach ($res as $row)
		{
        		if($row['KAKV_ID'] == ACT_TYPE_PLAN_ID || $row['KAKV_ID'] == ACT_TYPE_PLAN_TR_ID) continue;
        		$acttype[$row['KAKV_ID']]=$row['KAKV_NOSAUKUMS'];
		}
	}
unset($res);

  
  if ($oForm -> isFormSubmitted() && $oForm -> getValue('worker') && dbProc::isActTypePlan($oForm -> getValue('type')) )
  {
           // get ED area list
        $res=dbProc::getEDElementSectionList($trase);
        if (is_array($res))
        {
         	foreach ($res as $row)
         	{
         	   $edarea[$row['KEDI_ID']]=$row['KEDI_NOSAUKUMS'];
          }
        }
        unset($res);

  }
  

		// URL  acta help
	  $oLink = new urlQuery;
	  $oLink -> addPrm(FORM_ID, 'f.rpt.e.1');
		$oLink->addPrm('isTrase', $trase );
		$oLink->addPrm(DONT_USE_GLB_TPL, '1');
		$actHelpUrl =  $oLink ->getQuery();
		unset($oLink);

  

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
        $trase = $act['RAKT_TRASE'];
        $isPlan = dbProc::isActTypePlan($act['RAKT_KAKV_ID']);
        $isAuto = $act['RAKT_IS_AUTO'];
        $actNumPostfix = $act['RAKT_NUM_POSTFIX'];
        $sign = $act['RAKT_SIGNATURE'];

        // get act type
        $acttype=array();
        $acttype['']=text::get('EMPTY_SELECT_OPTION');
        if($trase == 1) {
          $res=dbProc::getActTraseTypeActivList();
        } else {
          $res=dbProc::getActTypeActivList();
        }
        if (is_array($res))
        {
          foreach ($res as $row)
          {
              if(($row['KAKV_ID'] == ACT_TYPE_PLAN_ID || $row['KAKV_ID'] == ACT_TYPE_PLAN_TR_ID) &&  !$isPlan) continue;
              $acttype[$row['KAKV_ID']]=$row['KAKV_NOSAUKUMS'];
          }
        }
        unset($res);
        
        // get contract list
        $res=dbProc::getDuContractNo($act['RAKT_KWOI_KODS'], $trase, true);
        if (is_array($res))
        {
         	foreach ($res as $row)
         	{
          	    $contract[$row['KCNT_VV_NUMBER']] = $row['KCNT_VV_NUMBER'];
          }
          if (!array_key_exists($act['RAKT_VV_NUMBER'],$contract)) 
          {
                $contract[$act['RAKT_VV_NUMBER']] = $act['RAKT_VV_NUMBER'];		
          }

        }
        unset($res);
        if ($oForm -> isFormSubmitted() && $oForm -> getValue('worker') && !dbProc::isActTypePlan($oForm -> getValue('type')) )
        {

                // get ED area list
              // bojanums, defekts
                if(($oForm -> getValue('type') == ACT_TYPE_DAMAGE_ID) || ($oForm -> getValue('type') == ACT_TYPE_DEFECT_ID ) )
                {
                    $res=dbProc::getEDSectionListForWorker($act['RAKT_KWOI_KODS'], $act['RAKT_VV_NUMBER'], $trase);
                }
              if(($oForm -> getValue('type') == ACT_TYPE_STIHIJA_ID) || ($oForm -> getValue('type') == ACT_TYPE_STIHIJA_TR_ID))
                {
                    $res=dbProc::getEDElementSectionList($trase);
                }
                else
                {
                  //$res=dbProc::getEDAreaActivList();
                  $res=dbProc::getEDAreaNotElementActivList($trase);
                }

              if (is_array($res))
              {
                foreach ($res as $row)
                {
                  $edarea[$row['KEDI_ID']]=$row['KEDI_NOSAUKUMS'];
                  }
              }
              unset($res);

        }

        // get ED area list
        // plan        
        if(dbProc::isActTypePlan($act['RAKT_KAKV_ID']))
        {
            $res=dbProc::getEDAreaNotElementActivList($trase);           
        }
        // bojanums, defekts
        elseif(($act['RAKT_KAKV_ID'] == ACT_TYPE_DAMAGE_ID) || ($act['RAKT_KAKV_ID'] == ACT_TYPE_DEFECT_ID ) || ($act['RAKT_KAKV_ID'] == ACT_TYPE_DAMAGE_TR_ID) || ($act['RAKT_KAKV_ID'] == ACT_TYPE_DEFECT_TR_ID ))
        {
            $res=dbProc::getEDSectionListForWorker($act['RAKT_KWOI_KODS'], $act['RAKT_VV_NUMBER'], $trase);
        }
        // stihija
        elseif(($act['RAKT_KAKV_ID'] == ACT_TYPE_STIHIJA_ID) || ($act['RAKT_KAKV_ID'] == ACT_TYPE_STIHIJA_TR_ID))
        {
            $res=dbProc::getEDElementSectionList($trase);
        }
        else
        {
           //$res=dbProc::getEDAreaActivList();
           $res=dbProc::getEDAreaNotElementActivList($trase);
        }

        if (is_array($res))
        {
         	foreach ($res as $row)
         	{
          	$edarea[$row['KEDI_ID']]=$row['KEDI_NOSAUKUMS'];
          }
        }
        unset($res);
      
        $worker = $act['RAKT_KWOI_KODS'];

  	}
  }
  else
  {
    // get default statuss
    $statusInfo = dbProc::getKrfkInfoByName(STAT_INSERT);
    $status = $statusInfo['KRFK_VERTIBA'];
    $statusLabel = $statusInfo['KRFK_NOZIME'];
    $isAuto = 0;
    $worker = userAuthorization::getWorker();
 // get contract list
    $res=dbProc::getDuContractNo(userAuthorization::getWorker(), $trase, true);
    if (is_array($res))
    {
     	foreach ($res as $row)
     	{
      	    $contract[$row['KCNT_VV_NUMBER']] = $row['KCNT_VV_NUMBER'];
        }
    }
    unset($res);
  if($trase == 1) {
	    $sign = 'E';
    } else {
	    $sign = '';
    } 
  }

 
  $ouner = array();
  $ouner['']=text::get('EMPTY_SELECT_OPTION');
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
  $isReadonly2   = true;
  $isReadonlyExceptAdmin   = true;
  $isReadonlyExceptEconomist   = true;
  $isAllowEstimate = false;
  $isAllowContinue = false;
  $isDelete   = false;
  $isActNumPrefix = false;
  $isAllowToPay = false;
  $isAllowPrintActcalc = false;
  if($actId != false)
  {
	
    // Ir pieejams main??anai, ja  AKTS:LIETOT?JS = �Teko?ais lietot?js� un lietot?ja loma ir �Ievad?tais� un AKTS:STATUS = �Izveide� vai �Atgriezts� vai �T?me�.
    if(($act['RAKT_RLTT_ID'] == $userId && ($isEditor || $isAdmin) && ($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ESTIMATE)) )
    {
      $isReadonly   = false;
    }
    // labo autors, inženieris, administrators
    if((( $act['RAKT_RLTT_ID'] == $userId && $isEditor) || $isAdmin || $isEconomist) && ($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ESTIMATE))
    {
      
      $isReadonly1   = false;
    }
    // labo autors,  administrators
    if((( $act['RAKT_RLTT_ID'] == $userId && $isEditor) || $isAdmin || $isEconomist) && ($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_AUTO))
    {
      
      $isReadonly2   = false;
    }
    // Ir pieejams main??anai, ja  �Teko?ais lietot?js� ir Sist?mas administrators un AKTS:STATUS = �Izveide� vai �Atgriezts� vai �T?me�.
    if($isAdmin && ($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ESTIMATE))
    {	
      $isReadonlyExceptAdmin   = false;
    }
	
    //Ir pieejams main??anai, ja   Teko?a lietot?ja loma = �Ekonomists�  un AKTS:STATUS = �Saska?o?ana�.
    if($isEconomist && $status == STAT_ACCEPT )
    {
      $isReadonlyExceptEconomist   = false;
    }

    //Ir pieejams main??anai, ja  AKTS:LIETOT?JS = �Teko?ais lietot?js� un objekts nav pabeigts
    if((($act['RAKT_RLTT_ID'] == $userId && $isEditor) || $isAdmin || $isEdUser) && ($status == STAT_INSERT || $status == STAT_RETURN ))
    {
       $isAllowEstimate = true;
    }

    // Ir pieejams, ja  lietotaja loma ir �ED bud�eta in�enieris� un AKTS:STATUS != �Izveide� 
    if(( $isEconomist || $isAdmin ) && ($status != STAT_INSERT ))
    {
      $isAllowPrintActcalc = true;
    }

    // at�auts labot gan autoram, gan apstiprin�t�jam, gan administratoram l�dz piln�gai akta nosl�g�anai
     if((($act['RAKT_RLTT_ID'] == $userId && $isEditor) || $isAdmin || $isEconomist ) && ($status != STAT_WRETEDOFF ))
    {
      $isActNumPrefix   = true;
    }
    
    if(($act['RAKT_RLTT_ID'] == $userId && $isEditor && ($status == STAT_INSERT || $status == STAT_RETURN ) && $isAuto == 0 ) ||
        ($isAdmin && ($status != STAT_DELETE))  )
    {
      $isDelete   = true;
    }

    // nodot apmaksai
    if($trase == 1 && ($isAdmin || $isEconomist) && $status == STAT_CLOSE)
    {
         $isAllowToPay = true;
    }
  }
  else
  {
     if(($isEditor || $isAdmin) && $status == STAT_INSERT)
     {
        $isReadonly   = false;
        $isReadonly1   = false;
        $isReadonly2   = false;
     }
	 if($isAdmin && ($status == STAT_INSERT || $status == STAT_RETURN ))
	 {	
		$isReadonlyExceptAdmin   = false;
		//echo "$isReadonlyExceptAdmin   = false";
     }
	 //echo "$isReadonlyExceptAdmin   = true";
  }
  

  // form elements
  $oForm -> addElement('hidden', 'isTrase', null, $trase);
  $oForm -> addElement('hidden', 'isSearch', '', $isSearch);
  $oForm -> addElement('hidden', 'searchNum', '', $searchNum);
  $oForm -> addElement('hidden', 'action', '');
  $oForm -> addElement('hidden', 'actId', null, isset($act['RAKT_ID'])? $act['RAKT_ID']:'');
  $oForm -> addElement('hidden', 'status', null, $status);
  $oForm -> addElement('hidden', 'isCopy', null, $isCopy);
  $oForm -> addElement('hidden', 'isAuto', '', $isAuto);
  $oForm -> addElement('label', 'statusTxt',  text::get('STATUS'), $statusLabel);
  $oForm -> addElement('hidden', 'actNumber',  '', isset($act['RAKT_NUMURS'])?$act['RAKT_NUMURS']:'');

  $oLink=new urlQuery();
  $oLink->addPrm(DONT_USE_GLB_TPL, 1);
  $oLink->addPrm(FORM_ID, 'f.akt.s.1');
  $oLink->addPrm('actId', $actId);
  $oLink->addPrm('isTrase', $trase );
  $oLink->addPrm('isAuto', $isAuto);
  $oLink->addPrm('worker', userAuthorization::getWorker() );

 
  if($actId != false)
  {
    $actNumber = (($trase == 1)? "2":"").
                (isset($act['KEDI_KODS'])?$act['KEDI_KODS']:'') .
                (isset($act['RAKT_NUMURS'])?$act['RAKT_NUMURS']:'').
                (isset($act['RAKT_NUMURS_OBJEKTA'])?$act['RAKT_NUMURS_OBJEKTA']:'0').
                ((true)? "/":"");
    /*$oForm -> addElement('label', 'eDcode',  text::get('ACT_NUMBER'), isset($act['ED_KODS'])?$act['ED_KODS']:'');
    $oForm -> addElement('label', 'typeCode',  '', isset($act['TYPE_CODE'])?$act['TYPE_CODE']:'');
    $oForm -> addElement('label', 'actNumber',  text::get('ACT_NUMBER'), isset($act['RAKT_NUMURS'])?$act['RAKT_NUMURS']:'');
    $oForm -> addElement('label', 'objNumber',  '', isset($act['RAKT_NUMURS_OBJEKTA'])?$act['RAKT_NUMURS_OBJEKTA']:'0');*/
    /* $oForm -> addElement('label', 'actFullNumber',  text::get('ACT_NUMBER'), isset($act['RAKT_FULL_NUMBER'])?$act['RAKT_FULL_NUMBER']:'');  */
    $oForm -> addElement('label', 'actFullNumber',  text::get('ACT_NUMBER'), $actNumber);
    if(true)
    {
      $actUrl = $info['SNFO_LINK_TMPL'].'/'.$act['RAKT_NUM_POSTFIX'];

      $oForm -> addElement('link', 'actNumPostfixLink', isset($act['RAKT_NUM_POSTFIX'])?$act['RAKT_NUM_POSTFIX']:'', $actUrl, ' target=new');
    }


    $oForm -> addElement('label', 'writeoffAccount',  text::get('WRITE_OFF_ACCOUNT'), isset($act['WRITE_OFF_ACCOUNT'])?$act['WRITE_OFF_ACCOUNT']:'');
  }
  
  $oForm -> addElement('select', 'type',  text::get('SINGLE_ACT_TYPE'), isset($act['RAKT_KAKV_ID'])?$act['RAKT_KAKV_ID']:'', ''.(($isReadonly1 || $isCopy || $isAuto == 1)?' disabled':'').' onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&type=\'+this.value+\'&contract=\'+document.all[\'contract\'].options[document.all[\'contract\'].selectedIndex].value))"', '', '', $acttype);
  //$oForm -> addElement('kls', 'type',  text::get('SINGLE_ACT_TYPE'), array('classifName'=> (($trase== 1) ? KL_ACT_TYPE_TRASE : KL_ACT_TYPE),'value'=>isset($act['RAKT_KAKV_ID'])?$act['RAKT_KAKV_ID']:'','readonly'=>false), (($isReadonly1 || $isCopy || $isAuto == 1)?' disabled ':'').'maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&type=\'+this.value+\'&contract=\'+document.all[\'contract\'].options[document.all[\'contract\'].selectedIndex].value))"');
  if (!$isReadonly1 && !$isCopy)
  {
     $oForm -> addRule('type', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

  $isEdDisabled = true;
  if(!$isReadonly1)
  {
      if(isset($act['RAKT_VV_NUMBER'])|| dbProc::isActTypePlan($oForm -> getValue('type')) || $isAuto == 1 || $isAdmin)
      {
        $isEdDisabled = false;
      }
  }

  $oForm -> addElement('select', 'EDarea',  text::get('ED_AREA'), isset($act['RAKT_KEDI_ID'])?$act['RAKT_KEDI_ID']:'', ''.(($isReadonly1 || $isCopy || $isAuto == 1)?' disabled':'').'', '', '', $edarea);
  if (!$isReadonly1)
  {
    $oForm -> addRule('EDarea', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }
 
  $oForm -> addElement('select', 'contract',  text::get('KWOI_VV_NUMBER'), isset($act['RAKT_VV_NUMBER'])?$act['RAKT_VV_NUMBER']:'', (($isReadonly1 || $isCopy || $isAuto == 1)? ' disabled ':''). '  onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&type=\'+document.all[\'type\'].options[document.all[\'type\'].selectedIndex].value+\'&contract=\'+this.value))"', '', '', $contract);
  if (!$isReadonly1 && !$isCopy)
  {
    $oForm -> addRule('contract', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

  $oForm -> addElement('select', 'ouner',  text::get('ACT_OUNER'), isset($act['RAKT_RLTT_ID'])?$act['RAKT_RLTT_ID']:$userId, ''.((!$isReadonly2 || !$isReadonlyExceptAdmin)?' ':'disabled').'', '', '', $ouner);
  //$oForm -> addElement('kls', 'ouner',  text::get('ACT_OUNER'), array('classifName'=>KL_USERS,'value'=>isset($act['RAKT_RLTT_ID'])?$act['RAKT_RLTT_ID']:$userId,'readonly'=>false), (($isReadonlyExceptAdmin || !$isEconomist)?' disabled ':'').'maxlength="2000"');
  if (!$isReadonlyExceptAdmin)
  {
    $oForm -> addRule('ouner', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

  $oForm -> addElement('kls', 'worker',  text::get('SINGL_WORK_OWNER'), array('classifName'=>KL_WORK_OWNERS,'value'=>isset($act['RAKT_KWOI_KODS'])?$act['RAKT_KWOI_KODS']:(($isReadonlyExceptAdmin)?userAuthorization::getWorker(): ''),'readonly'=>false), (($isReadonlyExceptAdmin) ? ' disabled' : ' ') . ' maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&worker=\'+this.value))"');

  if (!$isReadonlyExceptAdmin)
  {
    $oForm -> addRule('worker', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

  $oForm -> addElement('text', 'designation',  text::get('MAIN_DESIGNATION'), isset($act['RAKT_OPERATIVAS_APZIM'])?$act['RAKT_OPERATIVAS_APZIM']:'', 'maxlength="250"'.(($isReadonly1 || $isCopy)?' disabled':''));
  if (!$isReadonly1 && !$isCopy)
  {
    $oForm -> addRule('designation', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

  
  $oForm -> addElement('kls', 'object',  text::get('SINGLE_OBJECT'), array('classifName'=>(($trase== 1) ? KL_OBJECTS_TRASE : KL_OBJECTS),'value'=>isset($act['RAKT_KOBJ_ID'])?$act['RAKT_KOBJ_ID']:'','readonly'=>false), 'maxlength="2000"'.(( ($trase== 1 && $isReadonly2 ) || ($trase== 0 && $isReadonly2 && !$isCopy) )?' disabled':''));
  if (!$isReadonly1 || ($isCopy && $trase == 0))
  {
    $oForm -> addRule('object', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

  $oForm -> addElement('kls', 'voltage',  text::get('SINGLE_VOLTAGE'), array('classifName'=>(($trase== 1) ? KL_VOLTAGE_TRASE : KL_VOLTAGE),'value'=>isset($act['RAKT_KSRG_ID'])?$act['RAKT_KSRG_ID']:'','readonly'=>false), 'maxlength="2000"'.(($isReadonly2 || $isCopy)?' disabled':''));
  
  $oForm -> addElement('select', 'signature',  text::get('SIGNATURE_TYPE'), isset($act['RAKT_SIGNATURE'])?$act['RAKT_SIGNATURE']:$sign, ''.(($isReadonly1 || $isCopy)?' disabled':'').'', '', '', $signature);
  if (!$isReadonly1 && !$isCopy)
  {
    $oForm -> addRule('voltage', text::get('ERROR_REQUIRED_FIELD'), 'required');
    $oForm -> addRule('signature', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }
  
  
  if( (isset($act['PLAN']) && $act['PLAN'] == 1) || dbProc::isActTypePlan($oForm -> getValue('type')))
  {
        $oForm -> addElement('text', 'toid',  text::get('TO_ID'), isset($act['RAKT_TO_ID'])?$act['RAKT_TO_ID']:'', ' tabindex=14  maxlength="6"'.(($isReadonly1 )?' disabled ' : ' '));
  }
  else
  {
         $oForm -> addElement('text', 'toid',  text::get('TO_ID'), isset($act['RAKT_TO_ID'])? $act['RAKT_TO_ID']:(( isset($act['RAKT_KAKV_ID']) &&  $act['RAKT_KAKV_ID'] == ACT_TYPE_STIHIJA_ID)? '---' : ''), ' tabindex=14  maxlength="6"'.(($isReadonly1)?' disabled':''));      
  }

  // akta instrukcija
  $oForm -> addElement('link', 'actHelp', text::get('ACT_HELP'), './img/instrukcija.pdf', ' target=new');

  //datums
  $oForm -> addElement('date', 'proces_date',  text::get('DATE'), isset($act['RAKT_IZPILDES_DATUMS'])?$act['RAKT_IZPILDES_DATUMS']:dtime::now(), 'tabindex=4 maxlength="10"'.((($isReadonly1 && $isReadonlyExceptEconomist) || $isAuto == 1)?' disabled ':''));
  if (!$isReadonly || !$isReadonlyExceptEconomist)
  {
    $oForm -> addRule('proces_date', text::get('ERROR_REQUIRED_FIELD'), 'required');
    $oForm -> addRule('proces_date', text::get('ERROR_INCORRECT_DATE'),'validatedate');
  }

  $oForm -> addElement('checkbox', 'isFinished',  text::get('OBJECT_IS_FINISHED'), ((isset($act['RAKT_IR_OBJEKTS_PABEIGTS'] ) && $act['RAKT_IR_OBJEKTS_PABEIGTS'] == 1)?'1':0), ' disabled');
  $oForm -> addElement('text', 'description',  text::get('COMMENT'), isset($act['RAKT_PIEZIMES'])?$act['RAKT_PIEZIMES']:'', 'maxlength="150"'.(($isReadonly1 )?' disabled':''));

if(true)
{ // !$isReadonly || $isActNumPrefix
  $oForm -> addElement('text', 'numPostfix',  text::get('ACT_NUM_POSTFIX'), isset($act['RAKT_NUM_POSTFIX'])?$act['RAKT_NUM_POSTFIX']:'', 'maxlength="16"'.((($isReadonly1 && !$isCopy ) || $isAuto == 1)?' disabled':''));

  $oForm -> addElement('text', 'worktitle',  text::get('PRINT_WORK_TITLE'), isset($act['RAKT_WORK_TITLE'])?$act['RAKT_WORK_TITLE']:'', 'tabindex=6 maxlength="250"'.(($isReadonly1)?' disabled':''));
   if (!$isReadonly)
    {
        $oForm -> addRule('numPostfix', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('worktitle', text::get('ERROR_REQUIRED_FIELD'), 'required');
    }
}

  // form buttons
  if (!$isReadonly2 || !$isReadonlyExceptAdmin)
  {
    $oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat_g.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')) {setFormValue(\'frmMain\',\'action\',\''.OP_UPDATE.'\');} else {setFormValue(\'frmMain\',\'action\',\''.OP_INSERT.'\');}"');

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
    if($trase == 1) {
      $oForm -> addElement('submitImg', 'export', text::get('EXPORT'), 'img/btn_120_nodosana.gif', ' height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\') && isDeleteWithMessage(\''.text::get('WARNING_EXPORT').'\')) {setFormValue(\'frmMain\',\'action\',\''.OP_EXPORT.'\');} else {return false;}"');
    } else {
      $oForm -> addElement('submitImg', 'export', text::get('EXPORT'), 'img/btn_120_nodosana.gif', ' height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\') && isDeleteWithMessage(\''.text::get('WARNING_EXPORT').'\')) {setFormValue(\'frmMain\',\'action\',\''.OP_EXPORT.'\');} else {return false;}"');
    
      if($act['RAKT_IS_AUTO'] == 1) {
        $oForm -> addElement('submitImg', 'export_part', text::get('ACT_MIDDLE_RESULT'), 'img/btn_nodot_saskanosanai.gif', 'height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')) {setFormValue(\'frmMain\',\'action\',\''.OP_MIDLE_EXPORT.'\');} else {return false;}"');
      }
    }
    
  }
  
  if (!$isReadonlyExceptEconomist)
  {
    $oForm -> addElement('submitImg', 'return', text::get('RETURN'), 'img/btn_atgriezt.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_RETURN').'\')) {setFormValue(\'frmMain\',\'action\',\''.OP_RETURN.'\');} else {return false;}"');
    if($trase == 1)
    {
       //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.17');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('isTrase', $trase );

      $oForm -> addElement('submitImg', 'accept', text::get('ACCEPT'), 'img/btn_apstiprinat.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_ACCEPT').'\')) {'.RequestHandler::popupHref($oPopLink -> getQuery().'&toid=\'+document.all[\'toid\'].value+\'&numPostfix=\'+document.all[\'numPostfix\'].value+\'').' } return false;"');
      unset($oPopLink);
    }
    else
    {         
      $oForm -> addElement('submitImg', 'accept', text::get('ACCEPT'), 'img/btn_apstiprinat.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_ACCEPT').'\')) {setFormValue(\'frmMain\',\'action\',\''.OP_ACCEPT.'\');} else {return false;}"');
    }

  }
  if ($isAdmin && ($actId != false) && ($status == STAT_DELETE || $status == STAT_CLOSE))
  {
    $oForm -> addElement('submitImg', 'return', text::get('RETURN'), 'img/btn_atgriezt.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_RETURN').'\')) {setFormValue(\'frmMain\',\'action\',\''.OP_RETURN_CONFIRMED.'\');} else {return false;}"');
  }
  if ($isAdmin && ($actId != false) && ($status == STAT_AUTO))
  {
    $oForm -> addElement('submitImg', 'to_insert', text::get('TO_INSERT'), 'img/btn_auto_to_insert_120.gif', 'width="120" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')) {setFormValue(\'frmMain\',\'action\',\''.OP_CH_TO_INSERT.'\');} else {return false;}"');
  }
  if ($isAdmin && ($actId != false) && ($status == STAT_INSERT))
  {
    $oForm -> addElement('submitImg', 'to_return', text::get('TO_RETURN'), 'img/btn_insert_to_return_120.gif', 'width="120" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')) {setFormValue(\'frmMain\',\'action\',\''.OP_CH_TO_INSERT.'\');} else {return false;}"');
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
      $oLink->addPrm('isNumber', ($isSearch == 1 || $isSearch == 3)?0 : $searchNum);
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
  if($isAllowEstimate)
  {
      //$oForm -> addElement('submitImg', 'estimate', text::get('ESTIMATE'), 'img/btn_tame.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')) {setFormValue(\'frmMain\',\'action\',\''.OP_ESTIMATE.'\');} else {return false;}"');
      //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, (($trase == 1) ? 'f.akt.s.16': 'f.akt.s.12'));
      //$oPopLink->addPrm(FORM_ID,  'f.akt.s.12');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('isTrase',$trase);
      $oPopLink->addPrm('isMaterialPrice',0);
      $oForm -> addElement('buttonImg', 'view', text::get('VIEW_ACT'), 'img/btn_aplukot.gif', 'width="79" height="20" onclick="window.open(\''.$oPopLink ->getQuery().'\', \'frmMain\',\'\')"');
      unset($oPopLink);

  }
    if($isAllowPrintActcalc)
   {
      //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.12');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('isTrase',$trase);
      $oPopLink->addPrm('isMaterialPrice',1);
      $oForm -> addElement('buttonImg', 'print', text::get('VIEW_ACT'), 'img/btn_act_calc.gif', 'width="140" height="20" onclick="window.open(\''.$oPopLink ->getQuery().'\', \'frmMain\',\'\')"');
      unset($oPopLink);
   }

  if ($isDelete)
  {
    $oForm -> addElement('submitImg', 'delete', text::get('DELETE'), 'img/btn_dzest_r.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\') && isDeleteWithMessage(\''.text::get('WARNING_DELETE').'\')) {setFormValue(\'frmMain\',\'action\',\''.OP_DELETE.'\');} else {return false;}"');
  }
  if($isAllowToPay)
  {
      $oForm -> addElement('submitImg', 'topay', text::get('TO_PAY'), 'img/Nodot-apmaksai2.gif', 'width="90" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\') && isDeleteWithMessage(\''.text::get('WARNING_TOPAY').'\')) {setFormValue(\'frmMain\',\'action\',\''.OP_PAY.'\');} else {return false;}"');
  }

  if ($oForm -> isFormSubmitted())
  { 

    if ($oForm->getValue('action')==OP_INSERT ||
        ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('actId'))) ||
        ($oForm->getValue('action')==OP_EXPORT && is_numeric($oForm->getValue('actId'))) ||
        ($oForm->getValue('action')==OP_MIDLE_EXPORT && is_numeric($oForm->getValue('actId')))
        )
	  {
         $check = false;
    	    $r = false;
          $r1 = true;
          $r2 = true;
          $checkRequiredFields = false;

         $actNumber = false;
         if (($isEditor ||$isAdmin) && $oForm -> getValue('status') && $oForm -> getValue('EDarea') &&
            $oForm -> getValue('type') && $oForm -> getValue('contract') &&
            $oForm -> getValue('designation') && $oForm -> getValue('voltage') &&
            $oForm -> getValue('object') && //$oForm -> getValue('toid') && 
            $oForm -> getValue('proces_date')  && $oForm -> getValue('signature') 
            )
    	  {

          $checkRequiredFields = true;

    	  }

         if ($isAdmin  && !$oForm -> getValue('ouner')  )
        {
              $checkRequiredFields = false;
        }

    	 if ($checkRequiredFields)
    	 {
           $actNumPostfix = false;
           if($trase == 1 || !dbProc::isActTypePlan($oForm -> getValue('type')) )
           {
      	     // check act postfix
             // S�kas ar ang�u alfab�ta lielajiem burtiem, parasti 3-4 (ne vair�k par 8)
             // sal�dzin�ts ievad�tais teksta lauks ar teksta �ablonu no admin da�as
             // - T�l�k seko simbols �-�
             // - P�c t� seko skait�i no 1 l�dz 9999999
             $actNumPostfix = $oForm->getValue('numPostfix');
             $defis_pos = stripos($actNumPostfix, '-');

             $text_tpl = substr($actNumPostfix, 0, $defis_pos);

             $num_tpl = substr($actNumPostfix, $defis_pos+1);

        
              $PlanKvikStep = dbProc::getActTypePostfix( $oForm -> getValue('type') );
              $KvikStepCodes = explode(";", $PlanKvikStep);
              $check = false;
              foreach($KvikStepCodes as $key => $val)
              {
                if($defis_pos == true && $text_tpl ==$val && preg_match('([0-9]{1,7})', $num_tpl))
                {
                    $check = true;
                    break;
                }
	            }
              if(!$check)
              {
                      $oForm->addError( text::getAndReplace('ERROR_ACT_NUM_POSTFIX', str_replace(';', ' vai ', $PlanKvikStep)) );
                    $check = false;
              }

           }
           else
           {
            	if(dbProc::isActTypePlan($oForm -> getValue('type')) )
            	{
            		$actNumPostfix = $oForm->getValue('numPostfix');
            	}
                $check = true;
           }
           
           // check quistep ir umikāls
           if($oForm->getValue('action')==OP_INSERT && !dbProc::CheckQuiqStepUnique( $actNumPostfix ))
           {
               $oForm -> addError(text::get('ERROR_ACT_NUM_POSTFIX_NOT_UNOQUE'));
                $check = false;

           }

      // if all is ok, do operation
		  if($check)
		  {
		    // save
            if($oForm->getValue('action')==OP_INSERT || $oForm->getValue('action')==OP_UPDATE)
            {
              // get next act number
              $r=dbProc::saveAct(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('actId'):false),
                            false,
                            ($oForm->getValue('action')==OP_INSERT)?0:false,
                            $oForm->getValue('proces_date'),
                            $oForm->getValue('isFinished', 0) ,
                            $oForm->getValue('description'),
                            $oForm->getValue('designation'),
                            false,
                            $oForm->getValue('status'),
                            ($oForm->getValue('ouner'))? $oForm->getValue('ouner'):$userId,
                            $oForm->getValue('object'),
                            $oForm->getValue('voltage'),
                            $oForm->getValue('type'),
                            $oForm->getValue('worker'),
                            $oForm->getValue('EDarea'),
                            1/*$oForm->getValue('koeficent')*/ ,
                            $oForm->getValue('isTrase') ,
                            $actNumPostfix,
                            $oForm->getValue('worktitle'),
                            $oForm->getValue('contract'),
                            false,
                            $oForm->getValue('toid'),
                            $oForm->getValue('signature'),
							            (dbProc::isActTypePlan($oForm -> getValue('type')))?1:0
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

            // estimate
            if($oForm->getValue('action')==OP_EXPORT || $oForm->getValue('action')==OP_MIDLE_EXPORT)
            {

                $r=dbProc::saveAct($oForm->getValue('actId'),
    		    			          false,
                            false,
                            $oForm->getValue('proces_date'),
                            (($oForm->getValue('action')==OP_EXPORT)? 1: 0),
                            $oForm->getValue('description'),
                            $oForm->getValue('designation'),
                            false,
                            $oForm->getValue('status'),
                            ($oForm->getValue('ouner'))? $oForm->getValue('ouner'):$userId,
                            $oForm->getValue('object'),
                            $oForm->getValue('voltage'),
                            $oForm->getValue('type'),
                            ($oForm->getValue('worker'))? $oForm->getValue('worker') : false,
                            $oForm->getValue('EDarea'),
                            1,/*$oForm->getValue('koeficent')*/
                            $oForm->getValue('isTrase'),
                            $actNumPostfix,
                            $oForm->getValue('worktitle'),
                            $oForm->getValue('contract'),
		                        false,
                            $oForm->getValue('toid'),
                            $oForm->getValue('signature')
    						);

              if ($r )
              {

                
             
                if($trase == 1 && $oForm->getValue('action')==OP_EXPORT)
                {
                  // akta sagatavi (tab tamme)
                  $idFile = toPdf::estimateTrasePdf($actId, $userId, FILE_ESTIMATE);

                }
                else if($trase == 0 &&  ($oForm->getValue('action')==OP_EXPORT || $oForm->getValue('action')==OP_MIDLE_EXPORT) )
                {

                  // akta sagatavi (tab export)
                  $idFile = toPdf::exportActPdf($actId, $userId, $oForm->getValue('action')) ;
                }

                if ($idFile!==false)
                {
                    
                   // update act status
                    $r=dbProc::saveAct($oForm->getValue('actId'),
                                  false,false,false,false,false,false,
                                  true,
                                  STAT_ACCEPT,
                                  ($oForm->getValue('ouner'))? $oForm->getValue('ouner'):$userId,
                           			  $oForm->getValue('object'),
                            			$oForm->getValue('voltage'),
                            			$oForm->getValue('type'),
                            			($oForm->getValue('worker'))? $oForm->getValue('worker') : false,
                           			  $oForm->getValue('EDarea'),
                            			1,/*$oForm->getValue('koeficent')*/
                            			$oForm->getValue('isTrase'),
                            			$actNumPostfix,
                            			$oForm->getValue('worktitle'),
                            			$oForm->getValue('contract'),
		                   	          false,	                        		
                            			$oForm->getValue('toid'),
                                  $oForm->getValue('signature')
                                 );

                      if($isAuto){
                      // set darba, transporta un personala nodošanas datumu
                      dbProc::setUnsetActItemsDate(addslashes($actId), true);                  
                    }

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
              else
              {
                $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
              }
            }

      }
      // if operation was compleated succefully, show success mesage and redirect current frame
		  if ($r)
		  {
          $oLink=new urlQuery();
          $oLink->addPrm(FORM_ID, 'f.akt.s.1');
          $oLink->addPrm('actId', $actId);
          $oLink->addPrm('isTrase', $trase);
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
            case OP_MIDLE_EXPORT:
                $oLink->addPrm('successMessage', text::get('INFO_WAS_EXPORTED'));
                $oLink->addPrm('tab', TAB_EXPORT);
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
  // nomainīt akta statusu to INSERT
  if ($oForm->getValue('action')==OP_CH_TO_INSERT && is_numeric($oForm->getValue('actId')))
  {
      $r = false;
      $r1 = false;
      $r2 = false;  
      if($oForm->getValue('status') == STAT_AUTO) {
        $r=dbProc::updateActStatus($oForm->getValue('actId'), STAT_INSERT);
        $r2 = true;
      }
      if($oForm->getValue('status') == STAT_INSERT) {
        $r=dbProc::updateActStatus($oForm->getValue('actId'), STAT_RETURN);
        $r2 = dbProc::setUnsetActItemsDate($actId, false);
      }
      if($r && $r2)
      {
          // save status changed time
          $r1 = dbProc::saveAuditRecord($actId, $userId, STAT_INSERT);
          dbProc::setUserActionDate($userId, STAT_INSERT);

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
            $oLink->addPrm(FORM_ID, 'f.akt.s.1');
            $oLink->addPrm('actId', $actId);
            $oLink->addPrm('isTrase', $trase);
            $oLink->addPrm('isSearch', $isSearch);
            $oLink->addPrm('searchNum', $searchNum);
            $oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));

            RequestHandler::makeRedirect($oLink->getQuery());
      }
  }
  if (($oForm->getValue('action')==OP_RETURN && is_numeric($oForm->getValue('actId'))) ||
        ($oForm->getValue('action')==OP_RETURN_CONFIRMED && is_numeric($oForm->getValue('actId'))) ||
        ($oForm->getValue('action')==OP_ACCEPT && is_numeric($oForm->getValue('actId'))) )
	{
       	 $r = false;
         $r1 = true;
       	 $checkRequiredFields = false;
         if ($isEconomist && $oForm -> getValue('proces_date')  )
    	 {
    	    $checkRequiredFields = true;
            $_proces_date = $oForm->getValue('proces_date');
            $returnStatus  = STAT_RETURN;
            $returnAction =  STAT_RETURN;
         }
         if ($isAdmin && ($oForm -> getValue('status') == STAT_DELETE || $oForm -> getValue('status') == STAT_CLOSE) )
    	 {
    	      $checkRequiredFields = true;
            $_proces_date = false;

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
                  ( ($oForm->getValue('action')==OP_RETURN || $oForm->getValue('action')==OP_RETURN_CONFIRMED)? $returnStatus : STAT_CLOSE)
                );
               
               // Ja akts tiek atgriezts nepiln�bu nov�r�anai vai dz�sts, tad PDF ar amatpersonu v�z�m j�k��st nepieejamam.
                if($trase && $oForm->getValue('action')==OP_RETURN)
                {
                    $fileInfo=dbProc::getFilesInfo($actId, FILE_ESTIMATE);
                    if(count($fileInfo) > 0)
                        dbProc::deleteFile($fileInfo[0]['RFLS_ID']);
                }
                if($r)
                {
                    // save status changed time
                    $r1 = dbProc::saveAuditRecord($actId, $userId, ($oForm->getValue('action')==OP_RETURN)? $returnStatus : STAT_CLOSE);
                    dbProc::setUserActionDate($userId, ($oForm->getValue('action')=='OP_RETURN')? $returnAction : STAT_CLOSE);

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
                      $oLink->addPrm(FORM_ID, 'f.akt.s.1');
                      $oLink->addPrm('actId', $actId);
                      $oLink->addPrm('isTrase', $trase);
                      $oLink->addPrm('isSearch', $isSearch);
                      $oLink->addPrm('searchNum', $searchNum);
                      $oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));

                      //RequestHandler::makeRedirect($oLink->getQuery());
                }
            
            }
         }
         else
         {
            $oForm->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
         }
    }

    // nodot apmaksai
    if (($oForm->getValue('action')==OP_PAY && is_numeric($oForm->getValue('actId'))))
	{
         if($trase == 1 && ($isAdmin || $isEconomist) && $status == STAT_CLOSE)
         {
            // nomainit akta statusu uz  apmaksu
            if($oForm->getValue('action')==OP_PAY)
            {
                $r=dbProc::updateActStatus($oForm->getValue('actId'), STAT_TOPAY);

                if($r)
                {
                    // save status changed time
                    $r1 = dbProc::saveAuditRecord($actId, $userId, STAT_TOPAY);
                    dbProc::setUserActionDate($userId, ACT_TOPAY);

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
                      $oLink->addPrm(FORM_ID, 'f.akt.s.1');
                      $oLink->addPrm('actId', $actId);
                      $oLink->addPrm('isTrase', $trase);
                      $oLink->addPrm('isSearch', $isSearch);
                      $oLink->addPrm('searchNum', $searchNum);
                      $oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));

                      RequestHandler::makeRedirect($oLink->getQuery());
                }
            }
         }
         else
         {
            $oForm->addError(text::get('ERROR_NOT_PERMISSION'));
         }
    }
	// nomainit akta statusu uz dz?sts
    if (($oForm->getValue('action')==OP_DELETE && is_numeric($oForm->getValue('actId'))) ||
        ($oForm->getValue('action')==OP_DELETE_CONFIRMED && is_numeric($oForm->getValue('actId'))))
	  {
	  
			if(($act['RAKT_RLTT_ID'] == $userId && $isEditor && ($status == STAT_INSERT || $status == STAT_RETURN) ) || ($isAdmin && ($status != STAT_DELETE))  )
			{

            $r=dbProc::updateActStatus($oForm->getValue('actId'), STAT_DELETE);

                // Ja akts tiek atgriezts nepiln�bu nov�r�anai vai dz�sts, tad PDF ar amatpersonu v�z�m j�k��st nepieejamam.
                if($trase && $oForm->getValue('action')==OP_RETURN)
                {
                    $fileInfo=dbProc::getFilesInfo($actId, FILE_ESTIMATE);
                    if(count($fileInfo) > 0)
                        dbProc::deleteFile($fileInfo[0]['RFLS_ID']);
                }
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
                  $oLink->addPrm(FORM_ID, 'f.akt.s.1');
                  $oLink->addPrm('actId', $actId);
                  $oLink->addPrm('isTrase', $trase);
                  $oLink->addPrm('isSearch', $isSearch);
                  $oLink->addPrm('searchNum', $searchNum);
                  $oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));

                  RequestHandler::makeRedirect($oLink->getQuery());
                }
            }         
			else
			{
				$oForm->addError(text::get('ERROR_NOT_PERMISSION'));
			}
		
  }

    if ($oForm->getValue('action')==OP_COPY && is_numeric($oForm->getValue('actId')))
	{
	  
       	 $r = false;
         $objNumber =  dbProc::getNextObjNumber($oForm->getValue('actId'));
         $r=dbProc::saveAct(false,
    		    			$oForm->getValue('actNumber'),
                          $objNumber,
                          $oForm->getValue('proces_date'),
                          $oForm->getValue('isFinished', 0) ,
                          $oForm->getValue('description'),
                          $oForm->getValue('designation'),
                          STAT_INSERT,
                          ($oForm->getValue('ouner'))? $oForm->getValue('ouner'):$userId,
                          $oForm->getValue('object'),
                          $oForm->getValue('voltage'),
                          $oForm->getValue('type'),
                          ($oForm->getValue('worker'))? $oForm->getValue('worker') : false,
                          $oForm->getValue('EDarea'),
                          1,/*$oForm->getValue('koeficent')*/
                          $oForm->getValue('isTrase'),
                          $oForm->getValue('numPostfix'),
                          $oForm->getValue('worktitle'),
                          $oForm->getValue('contract') ,
                          false,                            
                          $oForm->getValue('toid'),
                          $oForm->getValue('signature')
    			);

          // save status changed time
          if ($r)
          {
              $newActId =  dbLayer::getInsertId();
              $r1 = dbProc::saveAuditRecord($newActId, $userId, STAT_INSERT);
              dbProc::setUserActionDate($userId, ACT_COPY);

              // if operation was compleated succefully, show success mesage and redirect current frame
              if ($r1)
              {
                $oLink=new urlQuery();
                $oLink->addPrm(FORM_ID, 'f.akt.s.1');
                $oLink->addPrm('actId', $newActId);
                $oLink->addPrm('isTrase', $trase);
                $oLink->addPrm('successMessage', text::get('RECORD_WAS_ADDED'));
                $oLink->addPrm('isSearch', $isSearch);
                $oLink->addPrm('searchNum', $searchNum);
                $oLink->addPrm('isCopy', 1);
                RequestHandler::makeRedirect($oLink->getQuery());
              }
              else
              {
                   $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
              }
          }
          else
          {
               $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
          }

	   }
    }

  

    $oForm -> makeHtml();
    include('f.akt.s.1.tpl');

    if ($isAuto == 1) {
      $tame = true;
      //$tameWork = $tame || (reqVar::get('tameWork') == 1);
      $tabs = new tabs("tame", "", true);

      $tabs->start(strtoupper(text::get(TAB_ESTIMATE)). ' ' .text::get(TAB_WORKS_T));
      
      include('f.akt.s.2.inc');
      $tabs->end();

      if($trase != 1)
      {

      $tabs->start(strtoupper(text::get(TAB_ESTIMATE)). ' ' .text::get(TAB_MATERIAL_T));
      include('f.akt.s.3.inc');
      $tabs->end();
     }

      //  $tabs->active = strtoupper(text::get(TAB_ESTIMATE)). ' ' .text::get($tametab);

      $tabs->run();
      $tame = false;        

  }


  $tabs = new tabs("akts", "");

    $tabs->start(text::get(TAB_WORKS));
    include('f.akt.s.2.inc');
    $tabs->end();
    if($trase != 1)
    {
  	  $tabs->start(text::get(TAB_MATERIAL));
      	include('f.akt.s.3.inc');
      	$tabs->end();
    }
    
    $tabs->start(text::get(TAB_ESTIMATE));
    include('f.akt.s.10.inc');
    $tabs->end();
    	
    if($trase == 1)
    {	
    	$tabs->start(text::get(TAB_EXPORT));
    	include('f.akt.s.6.inc');
    	$tabs->end();
    }     
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