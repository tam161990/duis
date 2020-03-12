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

// Main form with XMLHTTP method load this code:
if (reqVar::get('xmlHttp') == 1)
{
    if(reqVar::get('middlact') !== false && reqVar::get('typet') !== false)
    {
	  if(dbProc::isActTypePlan(reqVar::get('typet')))
	  {
       if(reqVar::get('middlact') == 1 )
       {
         ?>
           document.all["numPostfix"].value = '';
         <?
       }
             else
       {
         ?>
             document.all["numPostfix"].value = document.all['mmsWork'].options[document.all['mmsWork'].selectedIndex].text;
         <?
       }
	  }
	  else
	  {

	  }
       exit;
    }
    
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
       


    if(reqVar::get('type') && reqVar::get('contract'))
    {
      $PlanKvikStep = dbProc::getActTypePostfix(reqVar::get('type'));
     
      ?>
      document.all['EDarea'].disabled = false;
      <?
      // check is this type set as PLANS
      if(dbProc::isActTypePlan(reqVar::get('type')))
      {
	
        if(reqVar::get('mms') !== false )
        {
           ?>
            for(i=document.all["EDarea"].length; i>=0; i--)
            {
            	document.all["EDarea"].options[i] = null;
            }
           <?
           $res=dbProc::getEDSectionForMMS(reqVar::get('mms'), reqVar::get('contract'), $trase);
           if (is_array($res) && count($res) > 0)
           {

             	?>
  		    document.all["EDarea"].options[0] = new Option( '<?=$res[0]['KEDI_NOSAUKUMS'];?>', '<?=$res[0]['KEDI_ID'];?>');
                         document.all['EDarea'].disabled = true;
  	    	<?
	   	// get & set designation & work title values
             	$res = dbProc::getMMSWorkList(reqVar::get('mms'));
	   	if (is_array($res) && count($res) > 0)
	   	{
			?>
          		document.all["designation"].value = '<?=$res[0]['KMSD_OPERATIVAS_APZIM'];?>';
          		document.all["worktitle"].value = '<?=$res[0]['KMSD_WORK_TITLE'];?>';
              document.all["toidn"].value = '<?=$res[0]['KMSD_TO_IDN'];?>';
              document.all["toid"].value = '<?=$res[0]['KMSD_TO_ID'];?>';
			<?
        		if(reqVar::get('middlact') !== false)
        		{
    				if(reqVar::get('middlact') == 1 )
           			{
    					?>
    		    			document.all["numPostfix"].value = '';
    					<?
    				} 
				else 
				{
    					?>
    		    			document.all["numPostfix"].value = '<?=$res[0]['KMSD_KODS'];?>';
    					<?
    				}
        		}
        		else
        		{
            			?>
    		    		document.all["numPostfix"].value = '<?=$res[0]['KMSD_KODS'];?>';
    				<?
        		}
	   	}

           }
           if($trase == 1)
           {
             // define quickStep code
             //
             //$quickStep = dbProc::getMMSWorkCode(reqVar::get('mms'));
             ?>
                 //document.all["numPostfix"].value = suda v php tegah podstavit quickStep;
             <?
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
             }
           }
        }
        else
        {
            	// unset previouse values of edArea
          		?>
      		for(i=document.all["mmsWork"].length; i>=0; i--)
  		{
  			document.all["mmsWork"].options[i] = null;
  		}
  		<?
          $res=dbProc::getMMSWorkListByWorker(reqVar::get('worker'),  $trase, reqVar::get('contract'));

          if (is_array($res) && count($res) > 0)
          {
             	?>
  		document.all["mmsWork"].options[0] = new Option('<?=text::get('EMPTY_SELECT_OPTION');?>', '');
  		<?
                  $i = 1;
  		foreach ($res as $row)
  		{
  			// feel options array
  			?>
  		   	document.all["mmsWork"].options[<?=$i;?>] = new Option( '<?=$row['KMSD_KODS'];?>', '<?=$row['KMSD_ID'];?>');
                  	<?
                  	$i++;
  		}
          }
  	  ?>
          document.all['mmsWork'].disabled = false;
          document.all['mmsWorkStar'].style.display = 'inline';


          for(i=document.all["EDarea"].length; i>=0; i--)
          {
              document.all["EDarea"].options[i] = null;
          }
          <?
          $res=dbProc::getMMSEDListByWorker(reqVar::get('worker'), reqVar::get('contract'), $trase);


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

      }
      else
      {
	
          ?>
         document.all['mmsWork'].value = '';
         document.all['mmsWork'].disabled = true;
         document.all['mmsWorkStar'].style.display = 'none';


         for(i=document.all["EDarea"].length; i>=0; i--)
          {
          	document.all["EDarea"].options[i] = null;
          }
  	   <?
          if((reqVar::get('type') == ACT_TYPE_DAMAGE_ID) || (reqVar::get('type') == ACT_TYPE_DEFECT_ID ) || (reqVar::get('type') == ACT_TYPE_DAMAGE_TR_ID) || (reqVar::get('type') == ACT_TYPE_DEFECT_TR_ID ))
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
  $oLink->addPrm('searchNum', $searchNum);
  $oForm = new Form('frmMain','post',$oLink->getQuery());
  unset($oLink);

  // get user info
  $userInfo = dbProc::getUserInfo($userId);
  if(count($userInfo) >0 )
  {
  	$user = $userInfo[0];
  }


  unset($res);

  // get MMS work list
  $mmswork=array();
  $mmswork['']=text::get('EMPTY_SELECT_OPTION');

  $edarea=array();
  $edarea['']=text::get('EMPTY_SELECT_OPTION');

  $contract = array();
  $contract['']=text::get('EMPTY_SELECT_OPTION');

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

  if ($oForm -> isFormSubmitted() && $oForm -> getValue('worker') && dbProc::isActTypePlan($oForm -> getValue('type')) )
  {

        // get MMS work list
        $res=dbProc::getMMSWorkListByWorker($oForm -> getValue('worker'), $trase, $oForm -> getValue('contract'));
         if (is_array($res))
        {
         	foreach ($res as $row)
         	{
          	    $mmswork[$row['KMSD_ID']] = $row['KMSD_KODS'];
            }
        }
        unset($res);

        // get ED area list
        $res=dbProc::getEDSectionForMMS($oForm -> getValue('mmsWork'),$oForm -> getValue('contract'), $trase);
        if (is_array($res))
        {
         	foreach ($res as $row)
         	{
         	   $edarea[$row['KEDI_ID']]=$row['KEDI_NOSAUKUMS'];
            }
        }
        unset($res);


  }
  if ($oForm -> isFormSubmitted() && $oForm -> getValue('worker') && !dbProc::isActTypePlan($oForm -> getValue('type')) )
  {

        // get ED area list
        $res=dbProc::getMMSEDListByWorker($oForm -> getValue('worker'),$oForm -> getValue('contract'), $trase);
         if(($oForm -> getValue('type') == ACT_TYPE_DAMAGE_ID) || ($oForm -> getValue('type') == ACT_TYPE_DEFECT_ID ) || ($oForm -> getValue('type') == ACT_TYPE_DAMAGE_TR_ID) || (reqVar::get('type') == ACT_TYPE_DEFECT_TR_ID ))
          {
              $res=dbProc::getEDSectionListForWorker($oForm -> getValue('worker'), $oForm -> getValue('contract'), $trase);
          }
          elseif(($oForm -> getValue('type') == ACT_TYPE_STIHIJA_ID) || ($oForm -> getValue('type') == ACT_TYPE_STIHIJA_TR_ID))
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

        // get MMS work list
        $res=dbProc::getMMSWorkListByEd($act['RAKT_KEDI_ID'], $trase, $act['RAKT_VV_NUMBER']);
        if (is_array($res))
        {
         	foreach ($res as $row)
         	{
          	    $mmswork[$row['KMSD_ID']] = $row['KMSD_KODS'];
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

        // get ED area list
        // plan
        if(dbProc::isActTypePlan($act['RAKT_KAKV_ID']))
        {
            $res=dbProc::getEDSectionForMMS($act['RAKT_MMS_KODS'], $act['RAKT_VV_NUMBER'], $trase);
            $rs = dbProc::getMmsData($act['RAKT_MMS_KODS'])  ;
             if (is_array($rs) && count($rs) > 0)
            {
              $oForm -> addElement('label', 'koknese',  text::get('MMS_KOKNESE'), isset($rs[0]['KMSD_CILVEKSTUNDAS'])?$rs[0]['KMSD_CILVEKSTUNDAS']:'');
              $oForm -> addElement('label', 'plpayment',  text::get('MMS_PLAN_PAYMENT'), isset($rs[0]['KMSD_MATR_IZMAKSAS'])?$rs[0]['KMSD_MATR_IZMAKSAS']:'');
            }
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


  	}
  }
  else
  {
    // get default statuss
    $statusInfo = dbProc::getKrfkInfoByName(STAT_INSERT);
    $status = $statusInfo['KRFK_VERTIBA'];
    $statusLabel = $statusInfo['KRFK_NOZIME'];
    $actMonth =  dtime::getCurrentMonth();
    $actYear =  dtime::getCurrentYear();
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

  }

  $isReadonly   = true;
  $isReadonly1   = true;
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
    // Ir pieejams main??anai, ja  AKTS:LIETOT?JS = ’Teko?ais lietot?js’ un lietot?ja loma ir ‘Ievad?tais’ un AKTS:STATUS = ‘Izveide’ vai ‘Atgriezts’ vai ‘T?me’.
    if(($act['RAKT_RLTT_ID'] == $userId && ($isEditor || $isAdmin) && ($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ESTIMATE)) )
    {
      $isReadonly   = false;
    }
    // Ir pieejams main??anai, ja  AKTS:LIETOT?JS = administrators un lietot?ja loma ir ‘Ievad?tais’ un AKTS:STATUS = ‘Izveide’ vai ‘Atgriezts’ vai ‘T?me’.
    if($act['RAKT_RLTT_ID'] == $userId && $isAdmin && ($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ESTIMATE))
    {
      $isReadonly1   = false;
    }
    // Ir pieejams main??anai, ja  ’Teko?ais lietot?js’ ir Sist?mas administrators un AKTS:STATUS = ‘Izveide’ vai ‘Atgriezts’ vai ‘T?me’.
    if($isAdmin && ($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ESTIMATE))
    {
      $isReadonlyExceptAdmin   = false;
    }
    //Ir pieejams main??anai, ja   Teko?a lietot?ja loma = ‘Ekonomists’  un AKTS:STATUS = ‘Saska?o?ana’.
    if($isEconomist && $status == STAT_ACCEPT )
    {
      $isReadonlyExceptEconomist   = false;
    }

    //Ir pieejams main??anai, ja  AKTS:LIETOT?JS = ’Teko?ais lietot?js’ un objekts nav pabeigts
    if((($act['RAKT_RLTT_ID'] == $userId && $isEditor) || $isAdmin || $isEdUser) && ($status == STAT_INSERT || $status == STAT_RETURN ))
    {
       $isAllowEstimate = true;
    }

         // Ir pieejams, ja  lietotaja loma ir ‘ED budþeta inþenieris’ un AKTS:STATUS != ‘Izveide’ 
         if(( $isEconomist || $isAdmin ) && ($status != STAT_INSERT ))
         {
	$isAllowPrintActcalc = true;
         }

    // atïauts labot gan autoram, gan apstiprinâtâjam, gan administratoram lîdz pilnîgai akta noslçgðanai
     if((($act['RAKT_RLTT_ID'] == $userId && $isEditor) || $isAdmin || $isEconomist ) && ($status != STAT_WRETEDOFF ))
    {
      $isActNumPrefix   = true;
    }
    // Ir pieejams main??anai, ja  AKTS:LIETOT?JS = ’Teko?ais lietot?js’ un lietot?ja loma ir ‘Ievad?tais’ un AKTS:STATUS = ‘Izveide’ vai ‘Atgriezts’ vai ‘T?me’.
    if((($act['RAKT_RLTT_ID'] == $userId && $isEditor) || $isAdmin) && ($status == STAT_ACCEPT || $status == STAT_CLOSE || $status == STAT_WRETEDOFF ))
    {
      $isAllowContinue   = true;
    }

    if(($act['RAKT_RLTT_ID'] == $userId && $isEditor && ($status == STAT_INSERT || $status == STAT_RETURN ) ) ||
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
     }
  }
  // form elements
  $oForm -> addElement('hidden', 'isTrase', null, $trase);
  $oForm -> addElement('hidden', 'isSearch', '', $isSearch);
  $oForm -> addElement('hidden', 'searchNum', '', $searchNum);
  $oForm -> addElement('hidden', 'action', '');
  $oForm -> addElement('hidden', 'actId', null, isset($act['RAKT_ID'])? $act['RAKT_ID']:'');
  $oForm -> addElement('hidden', 'status', null, $status);
  $oForm -> addElement('hidden', 'isCopy', null, $isCopy);
  $oForm -> addElement('label', 'statusTxt',  text::get('STATUS'), $statusLabel);
  $oForm -> addElement('hidden', 'actNumber',  '', isset($act['RAKT_NUMURS'])?$act['RAKT_NUMURS']:'');

  $oLink=new urlQuery();
  $oLink->addPrm(DONT_USE_GLB_TPL, 1);
  $oLink->addPrm(FORM_ID, 'f.akt.s.1');
  $oLink->addPrm('actId', $actId);
  $oLink->addPrm('isTrase', $trase );
  $oLink->addPrm('worker', userAuthorization::getWorker() );

$oForm -> addElement('kls', 'type',  text::get('SINGLE_ACT_TYPE'), array('classifName'=> (($trase== 1) ? KL_ACT_TYPE_TRASE : KL_ACT_TYPE),'value'=>isset($act['RAKT_KAKV_ID'])?$act['RAKT_KAKV_ID']:'','readonly'=>false), (($isReadonly1 || $isCopy)?' disabled ':'').'maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&type=\'+this.value+\'&contract=\'+document.all[\'contract\'].options[document.all[\'contract\'].selectedIndex].value))"');

  if (!$isReadonly1 && !$isCopy)
  {
    $oForm -> addRule('type', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

   // check is mmsWork field disabled
  $isMmsWorkDisabled = true;
  if(!$isReadonly1)
  {

      if((isset($act['PLAN']) && $act['PLAN'] == 1) || dbProc::isActTypePlan($oForm -> getValue('type')))
      {
        if( (isset($act['RAKT_MMS_KODS']) ) && $status != STAT_RETURN)
        {
            $isMmsWorkDisabled = true;
        }
        elseif (dbProc::isActTypePlan($oForm -> getValue('type')))
        {
            $isMmsWorkDisabled = false;
        }
        else
        {
            $isMmsWorkDisabled = false;
        }
      }
    }

  $isEdDisabled = true;
  if(!$isReadonly1)
  {
      if(isset($act['RAKT_VV_NUMBER'])|| dbProc::isActTypePlan($oForm -> getValue('type')))
      {
        $isEdDisabled = false;
      }
  }


  $oForm -> addElement('select', 'mmsWork',  text::get('SINGLE_MMS'), isset($act['RAKT_MMS_KODS'])?$act['RAKT_MMS_KODS']:'', (($isMmsWorkDisabled || $isCopy)? ' disabled ':''). ' onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&type=\'+document.all[\'type\'].options[document.all[\'type\'].selectedIndex].value+\'&contract=\'+document.all[\'contract\'].options[document.all[\'contract\'].selectedIndex].value+\'&middlact=\'+((document.all[\'middlact\'].checked)?1:0)+\'&mms=\'+this.value))"', '', '', $mmswork);

  $oForm -> addElement('select', 'EDarea',  text::get('ED_AREA'), isset($act['RAKT_KEDI_ID'])?$act['RAKT_KEDI_ID']:'', ''.(($isEdDisabled || ($actId != false))?' disabled':'').'', '', '', $edarea);


  if (!$isReadonly1)
  {
    $oForm -> addRule('EDarea', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

   $oForm -> addElement('select', 'contract',  text::get('KWOI_VV_NUMBER'), isset($act['RAKT_VV_NUMBER'])?$act['RAKT_VV_NUMBER']:'', (($isReadonly1 || $isCopy)? ' disabled ':''). '  onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&type=\'+document.all[\'type\'].options[document.all[\'type\'].selectedIndex].value+\'&contract=\'+this.value))"', '', '', $contract);
 
  if (!$isReadonly1 && !$isCopy)
  {
    $oForm -> addRule('contract', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

  $oForm -> addElement('kls', 'ouner',  text::get('ACT_OUNER'), array('classifName'=>KL_USERS,'value'=>isset($act['RAKT_RLTT_ID'])?$act['RAKT_RLTT_ID']:$userId,'readonly'=>false), (($isReadonlyExceptAdmin)?' disabled ':'').'maxlength="2000"');
  if (!$isReadonlyExceptAdmin)
  {
    $oForm -> addRule('ouner', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }


  $oForm -> addElement('hidden', 'toidn', '', isset($act['RAKT_TO_IDN'])?$act['RAKT_TO_IDN']:'0', ' tabindex=13  maxlength="12"'.((!$isReadonlyExceptAdmin && $status != STAT_DELETE)?'' : ' disabled'));
  /*
  if( (isset($act['PLAN']) && $act['PLAN'] == 1) || dbProc::isActTypePlan($oForm -> getValue('type')))
  {
        $oForm -> addElement('text', 'toid',  text::get('TO_ID'), isset($act['RAKT_TO_ID'])?$act['RAKT_TO_ID']:'', ' tabindex=14  maxlength="6"'.((!$isReadonlyExceptAdmin && $status != STAT_DELETE)?'' : ' disabled'));
  }
  else
  {
         $oForm -> addElement('text', 'toid',  text::get('TO_ID'), isset($act['RAKT_TO_ID'])? $act['RAKT_TO_ID']:(( isset($act['RAKT_KAKV_ID']) &&  $act['RAKT_KAKV_ID'] == ACT_TYPE_STIHIJA_ID)? '---' : ''), ' tabindex=14  maxlength="6"'.(($isReadonly)?' disabled':''));      
  }
  */
  $oForm -> addElement('text', 'toid',  text::get('TO_ID'), isset($act['RAKT_TO_ID'])? $act['RAKT_TO_ID']:(( isset($act['RAKT_KAKV_ID']) &&  $act['RAKT_KAKV_ID'] == ACT_TYPE_STIHIJA_ID)? '---' : ''), ' tabindex=14  maxlength="6"'.(($isReadonly &&  $isReadonlyExceptEconomist )?' disabled':''));      
  //$oForm -> addElement('text', 'toid',  text::get('TO_ID'), isset($act['RAKT_TO_ID'])?$act['RAKT_TO_ID']:'', ' tabindex=14  maxlength="6"'.(($isReadonly &&  $isReadonlyExceptEconomist )? 'disabled' : ' '));
  $oForm -> addRule('toid', text::get('ERROR_REQUIRED_FIELD'), 'required');
  $oForm -> addRule('toid', text::get('ERROR_TOID_KODS'), 'toid', 'type');

  // akta instrukcija
    $oForm -> addElement('link', 'actHelp', text::get('ACT_HELP'), './img/instrukcija.pdf', ' target=new');

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

  $oForm -> addElement('kls', 'worker',  text::get('SINGL_WORK_OWNER'), array('classifName'=>KL_WORK_OWNERS,'value'=>isset($act['RAKT_KWOI_KODS'])?$act['RAKT_KWOI_KODS']:(($isReadonlyExceptAdmin)?userAuthorization::getWorker(): ''),'readonly'=>false), (($isReadonlyExceptAdmin)?' disabled ':'').'maxlength="2000"');

  if (!$isReadonlyExceptAdmin)
  {
    $oForm -> addRule('worker', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

   $oForm -> addElement('checkbox', 'middlact',  text::get('STARPAKTS'), isset($act['RAKT_STARPAKTS'])?$act['RAKT_STARPAKTS']:0, ' onClick="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&middlact=\'+((this.checked)?1:0)+\'&typet=\'+document.all[\'type\'].options[document.all[\'type\'].selectedIndex].value))" '.(($isReadonly)?' disabled' : ''));
  //$oForm -> addElement('checkbox', 'middlact',  text::get('STARPAKTS'), isset($act['RAKT_STARPAKTS'])?$act['RAKT_STARPAKTS']:0, ' onClick="if(this.checked){document.all[\'numPostfix\'].value=\'\';} else {document.all[\'numPostfix\'].value=document.all[\'mmsWork\'].options[document.all[\'mmsWork\'].selectedIndex].text;} " '.(($isReadonly)?' disabled' : ''));
unset($oLink);
  $oForm -> addElement('text', 'designation',  text::get('MAIN_DESIGNATION'), isset($act['RAKT_OPERATIVAS_APZIM'])?$act['RAKT_OPERATIVAS_APZIM']:'', 'maxlength="250"'.(($isReadonly1 || $isCopy)?' disabled':''));
  if (!$isReadonly1 && !$isCopy)
  {
    $oForm -> addRule('designation', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

  $oForm -> addElement('kls', 'voltage',  text::get('SINGLE_VOLTAGE'), array('classifName'=>(($trase== 1) ? KL_VOLTAGE_TRASE : KL_VOLTAGE),'value'=>isset($act['RAKT_KSRG_ID'])?$act['RAKT_KSRG_ID']:'','readonly'=>false), 'maxlength="2000"'.(($isReadonly1 || $isCopy)?' disabled':''));
  if (!$isReadonly1 && !$isCopy)
  {
    $oForm -> addRule('voltage', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }
  $oForm -> addElement('kls', 'object',  text::get('SINGLE_OBJECT'), array('classifName'=>(($trase== 1) ? KL_OBJECTS_TRASE : KL_OBJECTS),'value'=>isset($act['RAKT_KOBJ_ID'])?$act['RAKT_KOBJ_ID']:'','readonly'=>false), 'maxlength="2000"'.(( ($trase== 1 && $isReadonly1 ) || ($trase== 0 && $isReadonly1 && !$isCopy) )?' disabled':''));
  if (!$isReadonly1 || ($isCopy && $trase == 0))
  {
    $oForm -> addRule('object', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

  $oForm -> addElement('select', 'month',  text::get('MONTH'), isset($act['RAKT_MENESIS'])?$act['RAKT_MENESIS']:$actMonth, ''.(($isReadonly && $isReadonlyExceptEconomist)?' disabled ':''), '', '', dtime::getMonthArray());
  if (!$isReadonly || !$isReadonlyExceptEconomist)
  {
    $oForm -> addRule('month', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }
  $oForm -> addElement('select', 'year',  text::get('YEAR'), isset($act['RAKT_GADS'])?$act['RAKT_GADS']:$actYear, ''.(($isReadonly && $isReadonlyExceptEconomist)?' disabled ':''), '', '', (($isReadonly && $isReadonlyExceptEconomist)?dtime::getYearArray():dtime::getCurYearArray()));
  if (!$isReadonly || !$isReadonlyExceptEconomist)
  {
    $oForm -> addRule('year', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }


  $oForm -> addElement('text', 'description',  text::get('COMMENT'), isset($act['RAKT_PIEZIMES'])?$act['RAKT_PIEZIMES']:'', 'maxlength="150"'.(($isReadonly)?' disabled':''));

if(true)
{ // !$isReadonly || $isActNumPrefix
  $oForm -> addElement('text', 'numPostfix',  text::get('ACT_NUM_POSTFIX'), isset($act['RAKT_NUM_POSTFIX'])?$act['RAKT_NUM_POSTFIX']:'', 'maxlength="16"'.(($isReadonly && !$isCopy)?' disabled':''));

  $oForm -> addElement('text', 'worktitle',  text::get('PRINT_WORK_TITLE'), isset($act['RAKT_WORK_TITLE'])?$act['RAKT_WORK_TITLE']:'', 'tabindex=6 maxlength="250"'.(($isReadonly)?' disabled':''));
   if (!$isReadonly)
    {
        $oForm -> addRule('numPostfix', text::get('ERROR_REQUIRED_FIELD'), 'required');
       // IF($trase == 1)
       // {
       //	 $oForm -> addRule('numPostfix', text::getAndReplace('ERROR_ACT_NUM_POSTFIX', $info['SNFO_TEXT_TMPL']), 'kvikstep', $info['SNFO_TEXT_TMPL']);
       // }
       // else
       // {
	//  if( isset($act['TEXT_TMPL']))
	//  {
	//		$oForm -> addRule('numPostfix', text::getAndReplace('ERROR_ACT_NUM_POSTFIX', str_replace(';', ' vai ', $act['TEXT_TMPL'])), 'kvikstep', $act['TEXT_TMPL']);
	//
	//  }

        $oForm -> addRule('worktitle', text::get('ERROR_REQUIRED_FIELD'), 'required');
    }



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
  if (!$isReadonly && ($actId != false))
  {
    $oForm -> addElement('submitImg', 'export', text::get('EXPORT'), 'img/btn_nodot_saskanosanai.gif', ' height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\') && isDeleteWithMessage(\''.text::get('WARNING_EXPORT').'\')) {setValue(\'action\',\''.OP_EXPORT.'\');} else {return false;}"');
  }
  if ($isAllowContinue)
  {
    $oForm -> addElement('submitImg', 'continue', text::get('CONTINUE'), 'img/btn_turpinat.gif', 'width="140" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')) {setValue(\'action\',\''.OP_COPY.'\');} else {return false;}"');
  }
  if (!$isReadonlyExceptEconomist)
  {
    $oForm -> addElement('submitImg', 'return', text::get('RETURN'), 'img/btn_atgriezt.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_RETURN').'\')) {setValue(\'action\',\''.OP_RETURN.'\');} else {return false;}"');
    if($trase == 1)
    {
       //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.17');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('isTrase', $trase );

      $oForm -> addElement('submitImg', 'accept', text::get('ACCEPT'), 'img/btn_apstiprinat.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_ACCEPT').'\')) {'.RequestHandler::popupHref($oPopLink -> getQuery().'&year=\'+document.all[\'year\'].value+\'&month=\'+document.all[\'month\'].value+\'&toid=\'+document.all[\'toid\'].value+\'&numPostfix=\'+document.all[\'numPostfix\'].value+\'').' } return false;"');
      unset($oPopLink);
    }
    else
    {
         // '&year=\'+document.all[\'year\'].value+\'&month=\'+document.all[\'month\'].value+\'&numPostfix=\'+document.all[\'numPostfix\'].value+\''
      $oForm -> addElement('submitImg', 'accept', text::get('ACCEPT'), 'img/btn_apstiprinat.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_ACCEPT').'\')) {setValue(\'action\',\''.OP_ACCEPT.'\');} else {return false;}"');
    }

  }
  if ($isAdmin && ($actId != false) && ($status == STAT_DELETE || $status == STAT_CLOSE))
  {
    $oForm -> addElement('submitImg', 'return', text::get('RETURN'), 'img/btn_atgriezt.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_RETURN').'\')) {setValue(\'action\',\''.OP_RETURN.'\');} else {return false;}"');
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
  if($isAllowEstimate)
  {
      $oForm -> addElement('submitImg', 'estimate', text::get('ESTIMATE'), 'img/btn_tame.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')) {setValue(\'action\',\''.OP_ESTIMATE.'\');} else {return false;}"');
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
    $oForm -> addElement('submitImg', 'delete', text::get('DELETE'), 'img/btn_dzest_r.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\') && isDeleteWithMessage(\''.text::get('WARNING_DELETE').'\')) {setValue(\'action\',\''.OP_DELETE.'\');} else {return false;}"');
  }
  if($isAllowToPay)
  {
      $oForm -> addElement('submitImg', 'topay', text::get('TO_PAY'), 'img/Nodot-apmaksai2.gif', 'width="90" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\') && isDeleteWithMessage(\''.text::get('WARNING_TOPAY').'\')) {setValue(\'action\',\''.OP_PAY.'\');} else {return false;}"');
  }

  if ($oForm -> isFormSubmitted())
  {
    if ($oForm->getValue('action')==OP_INSERT ||
        ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('actId'))) ||
        ($oForm->getValue('action')==OP_EXPORT && is_numeric($oForm->getValue('actId'))) ||
        ($oForm->getValue('action')==OP_ESTIMATE && is_numeric($oForm->getValue('actId'))) )
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
            $oForm -> getValue('object') && $oForm -> getValue('toid') && 
            $oForm -> getValue('month') && $oForm -> getValue('year') )
    	 {

            if(dbProc::isActTypePlan($oForm -> getValue('type')))
            {
                   if($oForm -> getValue('mmsWork'))
                   {
                     $checkRequiredFields = true;
                   }
                   else
                   {
                      $checkRequiredFields = false;
                      $oForm -> setDeisabled('mmsWork', 'false');
                   }
            }
            else
            {
                 $checkRequiredFields = true;
            }

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
             // Sâkas ar angïu alfabçta lielajiem burtiem, parasti 3-4 (ne vairâk par 8)
             // salîdzinâts ievadîtais teksta lauks ar teksta ðablonu no admin daïas
             // - Tâlâk seko simbols „-”
             // - Pçc tâ seko skaitïi no 1 lîdz 9999999
             $actNumPostfix = $oForm->getValue('numPostfix');
             $defis_pos = stripos($actNumPostfix, '-');

             $text_tpl = substr($actNumPostfix, 0, $defis_pos);

             $num_tpl = substr($actNumPostfix, $defis_pos+1);

         //   if($trase == 1)
         //   {
         //    	if($defis_pos == true && $text_tpl == $info['SNFO_TEXT_TMPL'] && preg_match('([0-9]{1,7})', $num_tpl))
         //     		$check = true;
         //    	else
         //   	  	$oForm->addError( text::getAndReplace('ERROR_ACT_NUM_POSTFIX', $info['SNFO_TEXT_TMPL']) );
         //     }
         //     else
         //     {
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
           //   }
           }
           else
           {
            	if(dbProc::isActTypePlan($oForm -> getValue('type')) )
            	{
            		$actNumPostfix = $oForm->getValue('numPostfix');
            	}
                $check = true;
           }

		   /*
		    ja Akta veids=Plâns un Starpakts Checkbox=false, tad MMS kods ir jâbût = ar Kvikstep kods - citâdi kïûdas paziòojums 
 ja Akta veids=Plâns un Starpakts Checkbox=true, tad MMS kods<>Kviksteps kods un neviens no viòiem nav tukðs - citâdi kïûdas paziòojums 
 ja Akta veids<>Plâns, tad papildus neko nepârbauda 
			*/
			if(dbProc::isActTypePlan($oForm -> getValue('type')) )
			{
				if($oForm -> getValue('middlact', 0) == 0)
				{
					if($actNumPostfix != dbProc::getMMSWorkCode($oForm ->getValue('mmsWork')))
					{
						$oForm->addError(text::get('STARPAKTS_KLUDA_1'));
						$check = false;
					}
				}
				else
				{
					if($actNumPostfix == dbProc::getMMSWorkCode($oForm ->getValue('mmsWork')))
					{
						$oForm->addError(text::get('STARPAKTS_KLUDA_2'));
						$check = false;
					}
				}
			}

          // if all is ok, do operation
		  if($check)
		  {
		    // save
            if($oForm->getValue('action')==OP_INSERT || $oForm->getValue('action')==OP_UPDATE)
            {
    		    // get next act number
                /*if($oForm->getValue('action')==OP_INSERT)
                {
                  $actNumber =  dbProc::getNextActNumber($oForm->getValue('dvArea'));
                }*/

    		  	$r=dbProc::saveAct(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('actId'):false),
    		    			false,
                            ($oForm->getValue('action')==OP_INSERT)?0:false,
                            $oForm->getValue('month'),
                            $oForm->getValue('year'),
                            $oForm->getValue('description'),
                            $oForm->getValue('mmsWork'),
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
	                          $oForm->getValue('middlact', 0) ,
                            $oForm->getValue('toidn') ,
                            $oForm->getValue('toid')
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

                // update mms state
                if(dbProc::isActTypePlan($oForm -> getValue('type')))
                {
                     $r2 = dbProc::updateMMSWorkActive($oForm->getValue('mmsWork'), '1');
                }


                // save status changed time
                if($oForm->getValue('action')==OP_INSERT)
                {
                   $r1 = dbProc::saveAuditRecord($actId, $userId, $oForm->getValue('status'));
                }
    			if (!$r || !$r1 || !$r2)
    			{
    				$oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
    			}


    		}
            // export
            if($oForm->getValue('action')==OP_EXPORT || $oForm->getValue('action')==OP_ESTIMATE)
            {

                $r=dbProc::saveAct($oForm->getValue('actId'),
    		    			false,
                            false,
                            $oForm->getValue('month'),
                            $oForm->getValue('year'),
                            $oForm->getValue('description'),
                            $oForm->getValue('mmsWork'),
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
	                        $oForm->getValue('middlact', 0),
                            $oForm->getValue('toidn') ,
                            $oForm->getValue('toid')
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
                if($trase == 1 && $oForm->getValue('action')==OP_EXPORT)
                {
                  // akta sagatavi (tab tamme)
                  $pdf=new FPDF();
                  $pdf->AddFont('Arial','','arial.php');
                  $pdf->AddFont('Arial','BI','arialbi.php');
                  $pdf->AddFont('Arial','I','ariali.php');
                  $pdf->AddFont('Arial','B','arialbd.php');
                  $pdf->SetDisplayMode('real');
                  $pdf->SetAutoPageBreak(true,20);
                  $pdf->AliasNbPages();
                  $pdf->SetTitle(iconv('UTF-8', 'windows-1257',text::get('TRASE_ACT_HEADER4').' '.$act['NUMURS']));
                  $pdf->SetLeftMargin(20);
                  $pdf->AddPage();
                  $pdf->SetFont('Arial','B',10);
                  $pdf->Cell(0,0,iconv('UTF-8', 'windows-1257',text::get('TRASE_ACT_HEADER4')), 0,1,'C');


                  // Create new PHPExcel object
                  $objPHPExcel = new PHPExcel();

                  // create act header
                  $actHeader= array(
                     array(
                       array('', 'L', '', 8),
                       array('', 'L', '', 8)
                          ) ,
                     array(
                       array('', 'L', '', 8),
                       array('', 'L', '', 8)
                          ) ,
                    array(

                       array(iconv('UTF-8', 'windows-1257',dtime::dateToLvStringEmpty(date('d.m.Y'))), 'L', '', 8),
                       array(iconv('UTF-8', 'windows-1257',text::get('NUMBER_SIMBOL').'. '.$act['NUMURS']), 'R', 'B', 10)
                          ),
                    array(
                       array('', 'L', '', 8),
                       array('', 'L', '', 8)
                          ) ,
                    array(
                       array(iconv('UTF-8', 'windows-1257',text::get('TRASE_ACT_HEADER5')), 'L', '', 8),
                       array('', 'L', '', 8)
                          ),
                    array(
                       array('', 'L', '', 8),
                       array('', 'L', '', 8)
                          ) ,
                    array(
                       array(iconv('UTF-8', 'windows-1257',text::get('REPORT_WORK_OFFER').':'), 'L', '', 8),
                       array(iconv('UTF-8', 'windows-1257',text::get('REPORT_WORK_DONE').':'), 'L', '', 8)
                          ) ,
                    array(
                       array(iconv('UTF-8', 'windows-1257',text::get('ST_COMPANY_NAME').', '.text::get('REGISTRATION_SIMBOL').'. '.text::get('NUMBER_SIMBOL').': '.text::get('ST_REG_NR')), 'L', 'B', 8),
                       array(iconv('UTF-8', 'windows-1257',$act['WORKER'].', '.text::get('REGISTRATION_SIMBOL').'. '.text::get('NUMBER_SIMBOL').': '.$act['KWOI_KODS']), 'L', 'B', 8)
                          ),
                    array(
                       array(iconv('UTF-8', 'windows-1257',text::get('ED_IECIKNIS').':'), 'L', '', 8),
                       array(iconv('UTF-8', 'windows-1257',text::get('WORK_DONE_AGREEMENT_NO').': '.$act['RAKT_VV_NUMBER']), 'L', '', 8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257', $regionName.' '.text::get('REPORT_DEPARTMENT')), 'L', 'B', 8),
                       array('', 'L', '', 8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257',$act['KEDI_SECTION']), 'L', 'B', 8),
                       array('', 'L', '', 8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257',text::get('WORKS_AND_TERITORY').':'), 'L', '', 8),
                       array('', 'L', '',8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257', $regionName.' '.text::get('REPORT_REGION')), 'L', 'B', 8),
                       array('', 'L', '', 8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257',$act['KEDI_NOSAUKUMS'] ), 'L', 'B', 8),
                       array('', 'L', '', 8)
                          ) ,
                  ) ;
                  $pdf->HeaderStyledTable($actHeader);

                   $pdf->SetFont('Arial','BI',8);
                   $pdf->Cell(0,8,iconv('UTF-8', 'windows-1257', $act['WORK_TITLE']),0,1);

                  $actDescription = array(

                      array(
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_ACT_TYPE')).':',
                      iconv('UTF-8', 'windows-1257',$act['TYPE']),
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_OBJECT')).':',
                      iconv('UTF-8', 'windows-1257',$act['OBJECT'])
                          ),
                      array(
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_VOLTAGE')).':',
                      iconv('UTF-8', 'windows-1257',$act['SPRIEGUMS']),
                      iconv('UTF-8', 'windows-1257',text::get('EXPORT_MAIN_DESIGNATION')).':',
                      iconv('UTF-8', 'windows-1257',$act['RAKT_OPERATIVAS_APZIM'])
                          ),
	      array(
                      iconv('UTF-8', 'windows-1257',text::get('COMMENT')).':',
                      iconv('UTF-8', 'windows-1257',$act['RAKT_PIEZIMES']),
                      iconv('UTF-8', 'windows-1257',text::get('TO_ID')).':',
                      iconv('UTF-8', 'windows-1257',$act['RAKT_TO_ID'])
                          )

                      );
                  $pdf->DescriptionTableTrase($actDescription);
	  /*
                  $actDetales= array(


                     array(
                       array(iconv('UTF-8', 'windows-1257',text::get('COMMENT')).':',  'L', 'B', 8),
                       array(iconv('UTF-8', 'windows-1257',$act['RAKT_PIEZIMES']), 'L', '', 8)
                          ),
                  );
                  $pdf->DescriptionAsimetricalTable($actDetales);
	  */
                  // darbi
                  $pdf->SetFont('Arial','BI',10);
                  $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',text::get(TAB_WORKS)), 0,1);

                  $width=array(20,80,20,20,20,20);
                  $alignHeader=array('R','C','R','R','R','R');
                  $align=array('R','L','R','R','R','R');

                  $headers = array(
                      'DRBI_KKAL_SHIFRS' => iconv('UTF-8', 'windows-1257',text::get('CHIPHER')),
                      'DRBI_KKAL_NOSAUKUMS' => iconv('UTF-8', 'windows-1257',text::get('EXPORT_CALCULATION_NAME')),
                      'DRBI_MERVIENIBA' => iconv('UTF-8', 'windows-1257',text::get('UNIT_OF_MEASURE')),
                      'DRBI_KKAL_NORMATIVS' => iconv('UTF-8', 'windows-1257',text::get('PRICE')),
                      'DRBI_DAUDZUMS' => iconv('UTF-8', 'windows-1257',text::get('AMOUNT')),

                      'DRBI_CILVEKSTUNDAS' => iconv('UTF-8', 'windows-1257',text::get('PRICE_TOTAL'))
                      );

                  $aWorkDb=dbProc::getActWorkList($actId);
                  $data = array();
                  $totalD = 0;
                  foreach ($aWorkDb as $i => $work)
                  {
                    $data[$i] = array(
                      'DRBI_KKAL_SHIFRS' => $work['DRBI_KKAL_SHIFRS'],
                      'DRBI_KKAL_NOSAUKUMS' => text::returnsplit(iconv('UTF-8', 'windows-1257',$work['DRBI_KKAL_NOSAUKUMS']),  2, "\n", 60),
                      'DRBI_MERVIENIBA' => iconv('UTF-8', 'windows-1257',$work['DRBI_MERVIENIBA']),
                      'DRBI_KKAL_NORMATIVS' => $work['DRBI_KKAL_NORMATIVS'],
                      'DRBI_DAUDZUMS' => $work['DRBI_DAUDZUMS'],

                      'DRBI_CILVEKSTUNDAS' => $work['DRBI_CILVEKSTUNDAS']
                      );

                    $totalD +=  $work['DRBI_CILVEKSTUNDAS'];
                  }
                  $pdf->FancyTableTrase($headers,$data, $width, $align, $alignHeader);

                  $pct =  ($totalD*(100+ $pvn )/ 100 ) - $totalD;
                  $summa = ($totalD*(100+ $pvn )/ 100 );

                  $pdf->SetFont('Arial','',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('TOTAL')).":",0,0,'R');
                  $pdf->SetFont('Arial','B',8);
                  $pdf->Cell(20,6,number_format($totalD, 2), 0,1,'R');
                   $pdf->SetFont('Arial','',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('PCT').' '. $pvn . '%').":",0,0,'R');
                  $pdf->Cell(20,6,number_format(number_format($pct,2,'.',''), 2),0,1,'R');
                  $pdf->SetFont('Arial','B',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('TOTAL_WITH_PCT')).":", 0,0,'R');
                  $pdf->Cell(20,6,number_format(number_format($summa,2,'.',''), 2), 0,1,'R');
/*                  $pdf->SetTitle(iconv('UTF-8', 'windows-1257',text::get('TRASE_ACT_HEADER4').' '.$act['NUMURS']));
                  $pdf->SetLeftMargin(20);
                  $pdf->AddPage();
                  $pdf->SetFont('Arial','B',10);
                  $pdf->Cell(0,0,iconv('UTF-8', 'windows-1257',text::get('TRASE_ACT_HEADER4')), 0,1,'C');
                  $pdf->Cell(0,8,iconv('UTF-8', 'windows-1257',text::get('NUMBER_SIMBOL').'. '.$act['NUMURS']), 0,1,'C');
                  $pdf->Cell(0,0,iconv('UTF-8', 'windows-1257',text::get('TRASE_ACT_HEADER2')), 0,1,'C');

                  // ///////////////
                  $pdf->SetFont('Arial','',9);
                  $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',date('d.m.Y')), 0, 1);
                  $pdf->Cell(0,8,iconv('UTF-8', 'windows-1257',text::get('REPORT_WORK_OFFER').':'),0,1);
                  $pdf->SetFont('Arial','B',9);
                  $pdf->Cell(0,4,iconv('UTF-8', 'windows-1257',text::get('ST_COMPANY_NAME').' '.$act['KEDI_SECTION'] . ' '.text::get('IN_REPORT_SECTION').', '.text::get('MASTER_SECTION').' '.text::get('NUMBER_SIMBOL').'. '.$act['KEDI_NOSAUKUMS']), 0,1);
                  $pdf->SetFont('Arial','',9);
                  $pdf->Cell(0,8,iconv('UTF-8', 'windows-1257',text::get('REPORT_WORK_DONE').':'),0,1);
                  $pdf->Cell(0,4,iconv('UTF-8', 'windows-1257',$act['WORKER'].', '.text::get('REGISTRATION_SIMBOL').'. '.text::get('NUMBER_SIMBOL').'.: '.$act['KWOI_KODS']),0,1);
                  $pdf->Cell(0,4,iconv('UTF-8', 'windows-1257',text::get('WORK_DONE_AGREEMENT_NO').': '.$act['KWOI_TRASE_VV_NUMBER']),0,1);
                  $pdf->SetFont('Arial','B',9);
                   $pdf->Cell(0,8,iconv('UTF-8', 'windows-1257',text::get('TRASE_ACT_HEADER3').' '.$act['RAKT_GADS'].'. '.text::get('IN_YEAR').' '.dtime::getMonthNameInTime($act['RAKT_MENESIS'])),0,1);

                  // Create new PHPExcel object
                  $objPHPExcel = new PHPExcel();

                  $actDescription = array(

                      array(
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_ACT_TYPE')).':',
                      iconv('UTF-8', 'windows-1257',$act['TYPE']),
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_OBJECT')).':',
                      iconv('UTF-8', 'windows-1257',$act['OBJECT'])
                          ),
                      array(
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_VOLTAGE')).':',
                      iconv('UTF-8', 'windows-1257',$act['SPRIEGUMS']),
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_MMS')).':',
                      iconv('UTF-8', 'windows-1257',$act['MMS'])
                          )

                      );
                  $pdf->DescriptionTable($actDescription);
                  $actDetales= array(

                    array(
                       array(iconv('UTF-8', 'windows-1257',text::get('EXPORT_MAIN_DESIGNATION')), 'L', 'B', 8),
                       array(iconv('UTF-8', 'windows-1257',$act['RAKT_OPERATIVAS_APZIM']), 'L', '', 8)
                          ),
                     array(
                       array(iconv('UTF-8', 'windows-1257',text::get('COMMENT')), 'L', 'B', 8),
                       array(iconv('UTF-8', 'windows-1257',$act['RAKT_PIEZIMES']), 'L', '', 8)
                          ),
                  );
                  $pdf->DescriptionAsimetricalTable($actDetales);

                  // darbi
                  $pdf->SetFont('Arial','BI',10);
                  $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',text::get(TAB_WORKS)), 0,1);

                  $width=array(20,80,20,20,20,20);
                  $align=array('R','L','R','R','R','R');

                  $headers = array(
                      'DRBI_KKAL_SHIFRS' => iconv('UTF-8', 'windows-1257',text::get('CHIPHER')),
                      'DRBI_KKAL_NOSAUKUMS' => iconv('UTF-8', 'windows-1257',text::get('EXPORT_CALCULATION_NAME')),
                      'DRBI_MERVIENIBA' => iconv('UTF-8', 'windows-1257',text::get('UNIT_OF_MEASURE')),
                      'DRBI_KKAL_NORMATIVS' => iconv('UTF-8', 'windows-1257',text::get('PRICE')),
                      'DRBI_DAUDZUMS' => iconv('UTF-8', 'windows-1257',text::get('AMOUNT')),

                      'DRBI_CILVEKSTUNDAS' => iconv('UTF-8', 'windows-1257',text::get('PRICE_TOTAL'))
                      );

                  $aWorkDb=dbProc::getActWorkList($actId);
                  $data = array();
                  $totalD = 0;
                  foreach ($aWorkDb as $i => $work)
                  {
                    $data[$i] = array(
                      'DRBI_KKAL_SHIFRS' => $work['DRBI_KKAL_SHIFRS'],
                      'DRBI_KKAL_NOSAUKUMS' => text::returnsplit(iconv('UTF-8', 'windows-1257',$work['DRBI_KKAL_NOSAUKUMS']),  2, "\n", 40),
                      'DRBI_MERVIENIBA' => iconv('UTF-8', 'windows-1257',$work['DRBI_MERVIENIBA']),
                      'DRBI_KKAL_NORMATIVS' => $work['DRBI_KKAL_NORMATIVS'],
                      'DRBI_DAUDZUMS' => $work['DRBI_DAUDZUMS'],

                      'DRBI_CILVEKSTUNDAS' => $work['DRBI_CILVEKSTUNDAS']
                      );

                    $totalD +=  $work['DRBI_CILVEKSTUNDAS'];
                  }
                  $pdf->FancyTable($headers,$data, $width, $align);

                  $pdf->SetFont('Arial','B',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('TOTAL')).":",0,0,'R');
                  $pdf->Cell(20,6,number_format($totalD, 2),0,1,'C');     */

                  $rows=dbProc::getUserInfo($userId);
                  if (count($rows)==1)
                  {
                    $actAutorName =  $rows[0]['RLTT_VARDS'].' '.$rows[0]['RLTT_UZVARDS'];
                  }


                   $actFooter = array(
                   array(
                    iconv('UTF-8', 'windows-1257',text::get('ACT_CREATER').': '.$act['AUTORS']),
                    ''
                       ),
                    array(
                    iconv('UTF-8', 'windows-1257',text::get('DATE').': '.date('d.m.Y')),
                    iconv('UTF-8', 'windows-1257',text::get('IS_NOT_ENDORSED'))
                       ),
                    array(
                    iconv('UTF-8', 'windows-1257',''),
                    iconv('UTF-8', 'windows-1257','')
                        ),
                    array(
                    iconv('UTF-8', 'windows-1257',text::get('REPORT_WORKER_FINISHED').': '),
                    ''
                       ),
                    array(
                    iconv('UTF-8', 'windows-1257',$act['WORKER']),
                   ''
                       ),
                    array(
                    iconv('UTF-8', 'windows-1257',$act['AUTORS']),
                    ''
                       )
                    );
                  $pdf->FooterTablePortraitAsimetrikal($actFooter);

                }

                else
                { // tab exports
                /*
                 $pdf=new FPDF();
                  $pdf->AddFont('Arial','','arial.php');
                  $pdf->AddFont('Arial','BI','arialbi.php');
                  $pdf->AddFont('Arial','I','ariali.php');
                  $pdf->AddFont('Arial','B','arialbd.php');
                  $pdf->SetDisplayMode('real');
                  $pdf->SetAutoPageBreak(true,20);
                  $pdf->AliasNbPages();
                  $pdf->SetTitle(iconv('UTF-8', 'windows-1257',text::get('EXPORT_TITLE').' '.$act['NUMURS']));
                  $pdf->SetLeftMargin(20);
                  $pdf->AddPage();
                  $pdf->SetFont('Arial','BI',10);
                  $pdf->Cell(0,0,iconv('UTF-8', 'windows-1257',text::get('SINGL_WORK_OWNER').' '.$act['WORKER']), 0,1);
                  $pdf->Cell(0,8,iconv('UTF-8', 'windows-1257',text::get('WORK_DONE_AGREEMENT_NO').' '.$act['RAKT_VV_NUMBER']), 0,1);
                  $pdf->Cell(0,8,iconv('UTF-8', 'windows-1257',text::get('EXPORT_TITLE').' '.$act['NUMURS'].' '.(isset($act['MMS'])? text::get('SINGLE_MMS').': '.$act['MMS'] : '')), 0,1);
                  $pdf->Cell(0,8,iconv('UTF-8', 'windows-1257',text::get('EXPORT_ED_IECIRKNIS').' '.$act['STRUKTURVIENIBA']), 0,1);

                 // Create new PHPExcel object
                  $objPHPExcel = new PHPExcel();

                  $actDescription = array(
                      array(
                      iconv('UTF-8', 'windows-1257',text::get('ACT_NUMBER')).':',
                      iconv('UTF-8', 'windows-1257',$act['NUMURS']),
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_OBJECT')).':',
                      iconv('UTF-8', 'windows-1257',$act['OBJECT'])
                          ),
                      array(
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_ACT_TYPE')).':',
                      iconv('UTF-8', 'windows-1257',$act['TYPE']),
                      iconv('UTF-8', 'windows-1257',text::get('MONTH')).':',
                      iconv('UTF-8', 'windows-1257',dtime::getMonthName($act['RAKT_MENESIS']))
                          ),
                      array(
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_VOLTAGE')).':',
                      iconv('UTF-8', 'windows-1257',$act['SPRIEGUMS']),
                      iconv('UTF-8', 'windows-1257',text::get('YEAR')).':',
                      iconv('UTF-8', 'windows-1257',$act['RAKT_GADS'])
                          )

                      );
                  $pdf->DescriptionTable($actDescription);

                  $actDetales= array(

                    array(
                       array(iconv('UTF-8', 'windows-1257',text::get('EXPORT_MAIN_DESIGNATION')), 'L', 'B', 8),
                       array(iconv('UTF-8', 'windows-1257',$act['RAKT_OPERATIVAS_APZIM']), 'L', '', 8)
                          ),
                     array(
                       array(iconv('UTF-8', 'windows-1257',text::get('COMMENT')), 'L', 'B', 8),
                       array(iconv('UTF-8', 'windows-1257',$act['RAKT_PIEZIMES']), 'L', '', 8)
                          ),
                  );
                  $pdf->DescriptionAsimetricalTable($actDetales);

                  // darbi
                  $pdf->SetFont('Arial','BI',10);
                  $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',text::get(TAB_WORKS)), 0,1);

                  $width=array(20,80,20,20,20,20);
                  $align=array('C','L','C','C','C','C');

                  $headers = array(
                      'DRBI_KKAL_SHIFRS' => iconv('UTF-8', 'windows-1257',text::get('CHIPHER')),
                      'DRBI_KKAL_NOSAUKUMS' => iconv('UTF-8', 'windows-1257',text::get('EXPORT_CALCULATION_NAME')),
                      'DRBI_MERVIENIBA' => iconv('UTF-8', 'windows-1257',text::get('UNIT_OF_MEASURE')),
                      'DRBI_KKAL_NORMATIVS' => iconv('UTF-8', 'windows-1257',text::get('PRICE')),
                      'DRBI_DAUDZUMS' => iconv('UTF-8', 'windows-1257',text::get('AMOUNT')),

                      'DRBI_CILVEKSTUNDAS' => iconv('UTF-8', 'windows-1257',text::get('PRICE_TOTAL'))
                      );

                  $aWorkDb=dbProc::getActWorkList($actId);
                  $data = array();
                  $totalD = 0;
                  foreach ($aWorkDb as $i => $work)
                  {
                    $data[$i] = array(
                      'DRBI_KKAL_SHIFRS' => $work['DRBI_KKAL_SHIFRS'],
                      'DRBI_KKAL_NOSAUKUMS' => text::returnsplit(iconv('UTF-8', 'windows-1257',$work['DRBI_KKAL_NOSAUKUMS']),  2, "\n", 40),
                      'DRBI_MERVIENIBA' => iconv('UTF-8', 'windows-1257',$work['DRBI_MERVIENIBA']),
                      'DRBI_KKAL_NORMATIVS' => $work['DRBI_KKAL_NORMATIVS'],
                      'DRBI_DAUDZUMS' => $work['DRBI_DAUDZUMS'],

                      'DRBI_CILVEKSTUNDAS' => $work['DRBI_CILVEKSTUNDAS']
                      );

                    $totalD +=  $work['DRBI_CILVEKSTUNDAS'];
                  }
                  $pdf->FancyTable($headers,$data, $width, $align);

                  $pdf->SetFont('Arial','B',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('STARPTOTAL')).":",0,0,'R');
                  $pdf->Cell(20,6,number_format($totalD, 2),0,1,'C');

                  // materiali
                  $pdf->SetFont('Arial','BI',10);
                  $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',text::get(TAB_MATERIAL)), 0,1);

                  $width=array(20,80,20,20,20,20);
                  $align=array('C','L','C','C','C','C');

                  $headers = array(
                      'MATR_KODS' => iconv('UTF-8', 'windows-1257',text::get('CODE')),
                      'MATR_NOSAUKUMS' => iconv('UTF-8', 'windows-1257',text::get('NAME')),
                      'MATR_MERVIENIBA' => iconv('UTF-8', 'windows-1257',text::get('UNIT_OF_MEASURE')),
                      'MATR_CENA' => iconv('UTF-8', 'windows-1257',text::get('PRICE')),
                      'MATR_DAUDZUMS' => iconv('UTF-8', 'windows-1257',text::get('AMOUNT')),
                      'MATR_CENA_KOPA' => iconv('UTF-8', 'windows-1257',text::get('PRICE_TOTAL'))
                      );

                  $aMaterialDb=dbProc::getActMaterialList($actId);
                  $data = array();
                  $totalM = 0;
                  $mat_cena_kopa = 0;
                  foreach ($aMaterialDb as $i => $material)
                  {
                    if (isset($material['MATR_CENA_KOPA']))
                    {
                       $mat_cena_kopa = $material['MATR_CENA_KOPA'];
                    }
                    else
                    {
                      $mat_cena_kopa = $material['MATR_CENA'] *  $material['MATR_DAUDZUMS'];
                    }
                    $data[$i] = array(
                      'MATR_KODS' => (($material['MATR_IS_WORKER'] == '1')? $material['MATR_KODS'] : ''),
                      'MATR_NOSAUKUMS' => text::returnsplit(iconv('UTF-8', 'windows-1257',$material['MATR_NOSAUKUMS']),  2, "\n", 60),
                      'MATR_MERVIENIBA' => iconv('UTF-8', 'windows-1257',$material['MATR_MERVIENIBA']),
                      'MATR_CENA' => (($material['MATR_IS_WORKER'] == '1')? '' : $material['MATR_CENA']),
                      'MATR_DAUDZUMS' => $material['MATR_DAUDZUMS'],
                      'MATR_CENA_KOPA' => (($material['MATR_IS_WORKER'] == '1')? '' : $mat_cena_kopa)
                      );
                    if($material['MATR_IS_WORKER'] != '1')
                       $totalM +=  $mat_cena_kopa;
                  }
                  $pdf->FancyTable($headers,$data, $width, $align);

                  $pdf->SetFont('Arial','B',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('STARPTOTAL')).":",0,0,'R');
                  $pdf->Cell(20,6,number_format($totalM, 2),0,1,'C');

                  $pdf->SetFont('Arial','B',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('TOTAL')).":",0,0,'R');
                  $pdf->Cell(20,6,number_format($totalD+$totalM, 2),0,1,'C');
                  */
                               $pdf=new FPDF();
                  $pdf->AddFont('Arial','','arial.php');
                  $pdf->AddFont('Arial','BI','arialbi.php');
                  $pdf->AddFont('Arial','I','ariali.php');
                  $pdf->AddFont('Arial','B','arialbd.php');
                  $pdf->SetDisplayMode('real');
                  $pdf->SetAutoPageBreak(true,20);
                  $pdf->AliasNbPages();
                  $pdf->SetTitle(iconv('UTF-8', 'windows-1257',text::get('TRASE_ACT_HEADER1').' '.$act['NUMURS']));
                  $pdf->SetLeftMargin(20);
                  $pdf->AddPage();
                  $pdf->SetFont('Arial','B',10);
                  $pdf->Cell(0,0,iconv('UTF-8', 'windows-1257',text::get('TRASE_ACT_HEADER1')), 0,1,'C');


                  // Create new PHPExcel object
                  $objPHPExcel = new PHPExcel();

                  // create act header
                  $actHeader= array(
                     array(
                       array('', 'L', '', 8),
                       array('', 'L', '', 8)
                          ) ,
                     array(
                       array('', 'L', '', 8),
                       array('', 'L', '', 8)
                          ) ,
                    array(

                       array(iconv('UTF-8', 'windows-1257',dtime::dateToLvStringEmpty(date('d.m.Y'))), 'L', '', 8),
                       array(iconv('UTF-8', 'windows-1257',text::get('NUMBER_SIMBOL').'. '.$act['NUMURS']), 'R', 'B', 10)
                          ),
                    array(
                       array('', 'L', '', 8),
                       array('', 'L', '', 8)
                          ) ,
                    array(
                       array(iconv('UTF-8', 'windows-1257',text::get('SUPORT_ACT_HEADER5')), 'L', '', 8),
                       array(iconv('UTF-8', 'windows-1257',((isset($act['RAKT_STARPAKTS']) && $act['RAKT_STARPAKTS'] == 1) ? 
																	((isset($act['PLAN']) && $act['PLAN'] == 1) ?  $act['MMS'].' / '.text::get('STARPAKTS') : text::get('STARPAKTS')) : 
																	'')), 'R', 'B', 10)
                          ),
                    array(
                       array('', 'L', '', 8),
                       array('', 'L', '', 8)
                          ) ,
                    array(
                       array(iconv('UTF-8', 'windows-1257',text::get('REPORT_WORK_OFFER').':'), 'L', '', 8),
                       array(iconv('UTF-8', 'windows-1257',text::get('SINGLE_SOURCE_OF_FOUNDS').':'), 'L', '', 8)
                          ) ,
                    array(
                       array(iconv('UTF-8', 'windows-1257',text::get('ST_COMPANY_NAME').', '.text::get('REGISTRATION_SIMBOL').'. '.text::get('NUMBER_SIMBOL').': '.text::get('ST_REG_NR')), 'L', 'B', 8),
                       array(iconv('UTF-8', 'windows-1257',$act['WRITE_OFF_ACCOUNT']), 'L', '', 8)
                          ),
                    array(
                       array(iconv('UTF-8', 'windows-1257',text::get('ED_IECIKNIS').':'), 'L', '', 8),
                       array('', 'L', '', 8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257', $regionName.' '.text::get('REPORT_DEPARTMENT')), 'L', 'B', 8),
                       array(iconv('UTF-8', 'windows-1257',text::get('REPORT_WORK_DONE').':'), 'L', '', 8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257',$act['KEDI_SECTION']), 'L', 'B', 8),
                       array(iconv('UTF-8', 'windows-1257',$act['WORKER'].', '.text::get('REGISTRATION_SIMBOL').'. '.text::get('NUMBER_SIMBOL').': '.$act['KWOI_KODS']), 'L', 'B', 8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257',text::get('WORKS_AND_TERITORY').':'), 'L', '', 8),
                       array(iconv('UTF-8', 'windows-1257',text::get('WORK_DONE_AGREEMENT_NO').': '.$act['RAKT_VV_NUMBER']), 'L', '', 8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257', $regionName.' '.text::get('REPORT_REGION')), 'L', 'B', 8),
                       array('', 'L', '', 8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257',$act['KEDI_NOSAUKUMS'] ), 'L', 'B', 8),
                       array('', 'L', '', 8)
                          ) ,
                  ) ;
                  $pdf->HeaderStyledTable($actHeader);


                  $pdf->SetFont('Arial','BI',8);
                  $pdf->Cell(0,8,iconv('UTF-8', 'windows-1257', $act['WORK_TITLE']),0,1);


                  $actDescription = array(

                      array(
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_ACT_TYPE')).':',
                      iconv('UTF-8', 'windows-1257',$act['TYPE']),
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_OBJECT')).':',
                      iconv('UTF-8', 'windows-1257',$act['OBJECT'])
                          ),
                      array(
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_VOLTAGE')).':',
                      iconv('UTF-8', 'windows-1257',$act['SPRIEGUMS']),
                      iconv('UTF-8', 'windows-1257',text::get('EXPORT_MAIN_DESIGNATION')).':',
                      iconv('UTF-8', 'windows-1257',$act['RAKT_OPERATIVAS_APZIM'])
                          ),
                                            array(
                      		iconv('UTF-8', 'windows-1257',text::get('COMMENT')).':',
                      		iconv('UTF-8', 'windows-1257',$act['RAKT_PIEZIMES']),
                      		iconv('UTF-8', 'windows-1257',text::get('TO_ID')).':',
                      		iconv('UTF-8', 'windows-1257',$act['RAKT_TO_ID'])
                          		)

                      );
                  $pdf->DescriptionTableTrase($actDescription);
		    /*
                  $actDetales= array(


                     array(
                       array(iconv('UTF-8', 'windows-1257',text::get('COMMENT')).':',  'L', 'B', 8),
                       array(iconv('UTF-8', 'windows-1257',$act['RAKT_PIEZIMES']), 'L', '', 8)
                          ),
                  );
                  $pdf->DescriptionAsimetricalTable($actDetales);
		    */

                  // darbi
                  $pdf->SetFont('Arial','BI',10);
                  $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',text::get(TAB_WORKS)), 0,1);

                  $width=array(20,80,20,20,20,20);
                  $alignHeader=array('R','C','R','R','R','R');
                  $align=array('R','L','R','R','R','R');

                  $headers = array(
                      'DRBI_KKAL_SHIFRS' => iconv('UTF-8', 'windows-1257',text::get('CHIPHER')),
                      'DRBI_KKAL_NOSAUKUMS' => iconv('UTF-8', 'windows-1257',text::get('EXPORT_CALCULATION_NAME')),
                      'DRBI_MERVIENIBA' => iconv('UTF-8', 'windows-1257',text::get('UNIT_OF_MEASURE')),
                      'DRBI_KKAL_NORMATIVS' => iconv('UTF-8', 'windows-1257',text::get('PRICE')),
                      'DRBI_DAUDZUMS' => iconv('UTF-8', 'windows-1257',text::get('AMOUNT')),

                      'DRBI_CILVEKSTUNDAS' => iconv('UTF-8', 'windows-1257',text::get('PRICE_TOTAL'))
                      );

                  $aWorkDb=dbProc::getActWorkList($actId);
                  $data = array();
                  $totalD = 0;
                  foreach ($aWorkDb as $i => $work)
                  {
                    $data[$i] = array(
                      'DRBI_KKAL_SHIFRS' => $work['DRBI_KKAL_SHIFRS'],
                      'DRBI_KKAL_NOSAUKUMS' => text::returnsplit(iconv('UTF-8', 'windows-1257',$work['DRBI_KKAL_NOSAUKUMS']),  2, "\n", 60),
                      'DRBI_MERVIENIBA' => iconv('UTF-8', 'windows-1257',$work['DRBI_MERVIENIBA']),
                      'DRBI_KKAL_NORMATIVS' => $work['DRBI_KKAL_NORMATIVS'],
                      'DRBI_DAUDZUMS' => $work['DRBI_DAUDZUMS'],

                      'DRBI_CILVEKSTUNDAS' => $work['DRBI_CILVEKSTUNDAS']
                      );

                    $totalD +=  $work['DRBI_CILVEKSTUNDAS'];
                  }
                  $pdf->FancyTableTrase($headers,$data, $width, $align, $alignHeader);

                  //$pct =  ($totalD*(100+ $pvn )/ 100 ) - $totalD;
                  //$summa = ($totalD*(100+ $pvn )/ 100 );

                  $pdf->SetFont('Arial','',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('STARPTOTAL')).":",0,0,'R');
                  $pdf->SetFont('Arial','B',8);
                  $pdf->Cell(20,6,number_format($totalD, 2), 0,1,'R');
                  // $pdf->SetFont('Arial','',8);
//                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('PCT').' '. $pvn . '%').":",0,0,'R');
//                  $pdf->Cell(20,6,number_format(number_format($pct,2,'.',''), 2),0,1,'R');
//                  $pdf->SetFont('Arial','B',8);
//                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('TOTAL_WITH_PCT')).":", 0,0,'R');
//                  $pdf->Cell(20,6,number_format(number_format($summa,2,'.',''), 2), 0,1,'R');

                  // materiali
                  $pdf->SetFont('Arial','BI',10);
                  $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',text::get(TAB_MATERIAL)), 0,1);

                  $width=array(20,80,20,20,20,20);
                  $alignHeader=array('R','C','R','R','R','R');
                  $align=array('R','L','R','R','R','R');

                  $headers = array(
                      'MATR_KODS' => iconv('UTF-8', 'windows-1257',text::get('CODE')),
                      'MATR_NOSAUKUMS' => iconv('UTF-8', 'windows-1257',text::get('NAME')),
                      'MATR_MERVIENIBA' => iconv('UTF-8', 'windows-1257',text::get('UNIT_OF_MEASURE')),
                      'MATR_CENA' => iconv('UTF-8', 'windows-1257',text::get('PRICE')),
                      'MATR_DAUDZUMS' => iconv('UTF-8', 'windows-1257',text::get('AMOUNT')),
                      'MATR_CENA_KOPA' => iconv('UTF-8', 'windows-1257',text::get('PRICE_TOTAL'))
                      );

                  $aMaterialDb=dbProc::getActMaterialList($actId);
                  $data = array();
                  $totalM = 0;
                  $mat_cena_kopa = 0;
                  foreach ($aMaterialDb as $i => $material)
                  {
                    if (isset($material['MATR_CENA_KOPA']))
                    {
                       $mat_cena_kopa = $material['MATR_CENA_KOPA'];
                    }
                    else
                    {
                      $mat_cena_kopa = $material['MATR_CENA'] *  $material['MATR_DAUDZUMS'];
                    }
                    $data[$i] = array(
                      'MATR_KODS' => (($material['MATR_IS_WORKER'] == '1')? $material['MATR_KODS'] : ''),
                      'MATR_NOSAUKUMS' => text::returnsplit(iconv('UTF-8', 'windows-1257',$material['MATR_NOSAUKUMS']),  2, "\n", 60),
                      'MATR_MERVIENIBA' => iconv('UTF-8', 'windows-1257',$material['MATR_MERVIENIBA']),
                      'MATR_CENA' => (($material['MATR_IS_WORKER'] == '1')? '' : $material['MATR_CENA']),
                      'MATR_DAUDZUMS' => $material['MATR_DAUDZUMS'],
                      'MATR_CENA_KOPA' => (($material['MATR_IS_WORKER'] == '1')? '' : $mat_cena_kopa)
                      );
                    if($material['MATR_IS_WORKER'] != '1')
                       $totalM +=  $mat_cena_kopa;
                  }
                  $pdf->FancyTableTrase($headers,$data, $width, $align, $alignHeader);

                  //$pct =  ($totalM*(100+ $pvn )/ 100 ) - $totalM;
                  //$summa = ($totalM*(100+ $pvn )/ 100 );

                  $pdf->SetFont('Arial','',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('STARPTOTAL')).":",0,0,'R');
                  $pdf->SetFont('Arial','B',8);
                  $pdf->Cell(20,6,number_format($totalM, 2), 0,1,'R');
                /*   $pdf->SetFont('Arial','',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('PCT').' '. $pvn . '%').":",0,0,'R');
                  $pdf->Cell(20,6,number_format(number_format($pct,2,'.',''), 2),0,1,'R');
                  $pdf->SetFont('Arial','B',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('TOTAL_WITH_PCT')).":", 0,0,'R');
                  $pdf->Cell(20,6,number_format(number_format($summa,2,'.',''), 2), 0,1,'R');*/
                  $pdf->SetFont('Arial','',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('TOTAL')).":",0,0,'R');
                  $pdf->SetFont('Arial','B',8);
                  $pdf->Cell(20,6,number_format($totalD + $totalM, 2), 0,1,'R');



                   $actFooter = array(
                   array(
                    iconv('UTF-8', 'windows-1257',text::get('ACT_CREATER').': '.$act['AUTORS']),
                    ''
                       ),
                    array(
                    iconv('UTF-8', 'windows-1257',text::get('DATE').': '.date('d.m.Y')),
                    ''
                       ),
                    array(
                    iconv('UTF-8', 'windows-1257',''),
                    iconv('UTF-8', 'windows-1257','')
                        ) ,
                     array(
                    iconv('UTF-8', 'windows-1257',text::get('EXPORT_FOOTER')),
                    iconv('UTF-8', 'windows-1257','')
                        )

                    );
                  $pdf->FooterTablePortraitAsimetrikal($actFooter);

                }
                // saglaba faila datus

                $res=dbProc::replaceFile(
                    (($trase == 1) ? (($oForm->getValue('action')==OP_EXPORT) ? 'S':'A') : '').
                    $act['NUMURS'].'_'.dtime::now().'.'.EXPORT_FILE_EXTENTION,
                    $userId, $actId,
                    (($oForm->getValue('action')==OP_EXPORT)? FILE_EXPORT : FILE_ESTIMATE),
                    EXPORT_FILE_TYPE);
		        if ($res)
		        {
		        	$idFile=dbLayer::getInsertId();
		        }
		        else
		        {
		        	$oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
		        }
		        if ($idFile!==false)
		        {
                    $pdf->Output(FILES_STORE_PATH."/".$idFile, 'F');

                   // update act status
                    $r=dbProc::saveAct($oForm->getValue('actId'),
    		    			false,false,false,false,false,false,false,
                            ($oForm->getValue('action')==OP_EXPORT)? true : false,
                            ($oForm->getValue('action')==OP_EXPORT)? STAT_ACCEPT : STAT_ESTIMATE,
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
	                        		$oForm->getValue('middlact', 0),
                            			$oForm->getValue('toidn') ,
                            			$oForm->getValue('toid')

				);
                    // save status changed time
                    $r1 = dbProc::saveAuditRecord($actId, $userId, ($oForm->getValue('action')==OP_EXPORT)? STAT_ACCEPT : STAT_ESTIMATE);
                    // saglaba lietotaja darbiibu
                    dbProc::setUserActionDate($userId, ($oForm->getValue('action')==OP_EXPORT)? ACT_EXPORT : ACT_ESTIMATE);

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
                    $oLink->addPrm('tab', TAB_ESTIMATE);
					break;
                case OP_ESTIMATE:
					$oLink->addPrm('successMessage', text::get('INFO_WAS_ESTIMATED'));
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
        ($oForm->getValue('action')==OP_RETURN_CONFIRMED && is_numeric($oForm->getValue('actId'))) ||
        ($oForm->getValue('action')==OP_ACCEPT && is_numeric($oForm->getValue('actId'))) )
	{
       	 $r = false;
         $r1 = true;
       	 $checkRequiredFields = false;
         if ($isEconomist && $oForm -> getValue('month') && $oForm -> getValue('year') )
    	 {
    	    $checkRequiredFields = true;
            $_month = $oForm->getValue('month');
            $_year =  $oForm->getValue('year');
            $returnStatus  = STAT_RETURN;
            $returnAction =  STAT_RETURN;
         }
         if ($isAdmin && ($oForm -> getValue('status') == STAT_DELETE || $oForm -> getValue('status') == STAT_CLOSE) )
    	 {
    	    $checkRequiredFields = true;
            $_month = false;
            $_year =  false;
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

			  //  ja Starpakts checkbox = true un KL_MMS_DARBI.KMSD_NOSLEGUMA_AKTS=true, tad nenotiek atgrieðana, bet parâdâs kïûdas paziòojums, ka ir pieòemts noslçguma akts un starpaktu atgriezt nevar
			  if($oForm->getValue('action')==OP_RETURN && $oForm -> getValue('middlact', 0) == 1 && dbProc::getFinalizeMMS($actId) == 1)
			  {
                  if($isAdmin)
                {  // document.all[\'frmMain\'].submit();
                    $oForm->addError(text::get('STARPAKTS_KLUDA_6').'&nbsp;<a href="javascript: setValue(\'action\',\''.OP_RETURN_CONFIRMED.'\');  document.all[\'frmMain\'].submit(); "><img src=\'img/btn_turpinat1.gif\' border=0></a>');
                }
                else
                {
				    $oForm->addError(text::get('STARPAKTS_KLUDA_4'));
                }
			  }
			  else
			  {

				$r=dbProc::saveAct($oForm->getValue('actId'),
    		    			false,
                            false,
                            $_month,
                            $_year,
                            false,
                            false,
                            false,
                            false,
                            ( ($oForm->getValue('action')==OP_RETURN || $oForm->getValue('action')==OP_RETURN_CONFIRMED)? $returnStatus : STAT_CLOSE),
                            false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false  ,
                            false,
                            false,
                            false,
                            false,
							false,
                            $oForm->getValue('toidn') ,
                            $oForm->getValue('toid')
    						);
               // Ja akts tiek atgriezts nepilnîbu novçrðanai vai dzçsts, tad PDF ar amatpersonu vîzâm jâkïûst nepieejamam.
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
					// Saskaòoðanas statusâ -> Poga Saskaòots :ja Starpakts checkbox = false, tad tabulâ KL_MMS_DARBI laukam KMSD_NOSLEGUMA_AKTS vçrtîba ierakstâs =true attiecîgajam MMS darbam
					 if($oForm->getValue('action')==OP_ACCEPT)
					 {
						if($oForm -> getValue('middlact', 0) == 0) 
						{	
							$r1 = dbProc::finalizeMMS($actId, 1);
						}
						else
						{
							$r1 = dbProc::finalizeMMS($actId, 0);
						}

						if (!$r1)
        				{
        					$oForm->addError(text::get('ERROR_IN_DB_QUERY').'!!!'.dbProc::getError());
        				}
					 }

					//  ja Starpakts checkbox = false un KL_MMS_DARBI.KMSD_NOSLEGUMA_AKTS=true, tad saglabâjas funkcionalitâte un ierakstâm KL_MMS_DARBI.KMSD_NOSLEGUMA_AKTS=false
					 if($oForm->getValue('action')==OP_RETURN)
					 {
						if($oForm -> getValue('middlact', 0) == 0 && dbProc::getFinalizeMMS($actId) == 1)
						{
							$r1 = dbProc::finalizeMMS($actId, 0);
							if (!$r1)
        					{
        						$oForm->addError(text::get('ERROR_IN_DB_QUERY').'!!!'.dbProc::getError());
        					}
						}
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
              $r=dbProc::saveAct($oForm->getValue('actId'),
    		    			false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            STAT_TOPAY,
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
                            $oForm->getValue('toidn') ,
                            $oForm->getValue('toid')
    						);

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
	    //  ja Starpakts checkbox = true un KL_MMS_DARBI.KMSD_NOSLEGUMA_AKTS=true, tad nenotiek atgrieðana, bet parâdâs kïûdas paziòojums, ka ir pieòemts noslçguma akts un starpaktu dzçst nevar
		if($oForm -> getValue('middlact', 0) == 1  && dbProc::getFinalizeMMS($actId) == 1)
		{
           if($isAdmin)
          {  // document.all[\'frmMain\'].submit();
              $oForm->addError(text::get('STARPAKTS_KLUDA_7').'&nbsp;<a href="javascript: setValue(\'action\',\''.OP_DELETE_CONFIRMED.'\');  document.all[\'frmMain\'].submit(); "><img src=\'img/btn_turpinat1.gif\' border=0></a>');
          }
          else
          {
		    $oForm->addError(text::get('STARPAKTS_KLUDA_5'));
          }
		}
		else
		{
			if(($act['RAKT_RLTT_ID'] == $userId && $isEditor && ($status == STAT_INSERT || $status == STAT_RETURN) ) || ($isAdmin && ($status != STAT_DELETE))  )
			{
				
				  $r=dbProc::saveAct($oForm->getValue('actId'),
    		    			false,
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
                            $oForm->getValue('toidn') ,
                            $oForm->getValue('toid')
    						);
                // Ja akts tiek atgriezts nepilnîbu novçrðanai vai dzçsts, tad PDF ar amatpersonu vîzâm jâkïûst nepieejamam.
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

					//  ja Starpakts checkbox = false un KL_MMS_DARBI.KMSD_NOSLEGUMA_AKTS=true, tad saglabâjas funkcionalitâte un ierakstâm KL_MMS_DARBI.KMSD_NOSLEGUMA_AKTS=false
					if($oForm->getValue('action')==OP_DELETE && $oForm -> getValue('middlact', 0) == 0 && dbProc::getFinalizeMMS($actId) == 1)
				    {
						$r1 = dbProc::finalizeMMS($actId, 0);
						if (!$r1)
        				{
        					$oForm->addError(text::get('ERROR_IN_DB_QUERY').'!!!'.dbProc::getError());
        				}
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
    }

    if ($oForm->getValue('action')==OP_COPY && is_numeric($oForm->getValue('actId')))
	{
	     //aktam, kurð nav starpakts turpinâjumu izveidot nevar
		 if($oForm -> getValue('middlact', 0) == 0)
		 {
			if($oForm->getValue('numPostfix') != $oForm->getValue('mmsWork'))
			{
				$oForm->addError(text::get('STARPAKTS_KLUDA_3'));
				$check = false;
			}
		}
		else
		{
			
       	 $r = false;
         $objNumber =  dbProc::getNextObjNumber($oForm->getValue('actId'));
         $r=dbProc::saveAct(false,
    		    			$oForm->getValue('actNumber'),
                            $objNumber,
                            $oForm->getValue('month'),
                            $oForm->getValue('year'),
                            $oForm->getValue('description'),
                            $oForm->getValue('mmsWork'),
                            $oForm->getValue('designation'),
                            false,
                            STAT_INSERT,
                            ($oForm->getValue('ouner'))? $oForm->getValue('ouner'):$userId,
                            $oForm->getValue('object'),
                            $oForm->getValue('voltage'),
                            $oForm->getValue('type'),
                            ($oForm->getValue('worker'))? $oForm->getValue('worker') : false,
                            $oForm->getValue('EDarea'),
                            1,/*$oForm->getValue('koeficent')*/
                            $oForm->getValue('isTrase'),
                            /*(($trase == 1) ? dbProc::getMMSWorkCode($oForm->getValue('mmsWork')) : $actNumPostfix  )*/
	            (($oForm -> getValue('middlact', 0) == 0) ? $oForm->getValue('numPostfix') : ''),
                            $oForm->getValue('worktitle'),
                            $oForm->getValue('contract') ,
                            false,
                            false,
                            $oForm->getValue('toidn'),
                            $oForm->getValue('toid')
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

  }

    $oForm -> makeHtml();
    include('f.akt.s.1.tpl');

  $tabs = new tabs("example1");

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
    include('f.akt.s.6.inc');
   	$tabs->end();

    if($trase == 1)
    {
  	  $tabs->start(text::get(TAB_EXPORT));
      include('f.akt.s.10.inc');
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