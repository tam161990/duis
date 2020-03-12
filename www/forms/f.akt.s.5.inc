<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isSystemUser = dbProc::isExistsUserRole($userId);
$isEditor = ( dbProc::isUserInRole($userId, ROLE_EDITOR) ||  dbProc::isUserInRole($userId, ROLE_EDITOR_VIEWER));

// act ID
$actId  = reqVar::get('actId');
// search form
$isSearch  = reqVar::get('isSearch');
// search act by number
$searchNum  = reqVar::get('searchNum');

// Main form with XMLHTTP method load this code:
if (reqVar::get('xmlHttp') == 1)
{
    // if operation is DELETE , delete record from DB
    if (reqVar::get('deleteId')!='')
	{
         dbProc::deleteActPersonalRecord(reqVar::get('deleteId'));
         ?>
           rowNode = this.parentNode.parentNode;
           rowNode.parentNode.removeChild(rowNode);
         <?
        // get act works total time
        $totalTime = dbProc::getActTotalWorkTime($actId);
        // get act virsstundu koef
        $actInfo = dbProc::getActInfo($actId);
        if(count($actInfo)>0)
        {
            $koef = $actInfo[0]['RAKT_VIRSSTUNDU_KOEF'];
        }
        $totalTimeWithKoef = round(($totalTime*($koef-1)), 2);

        //Ja eksistee akta materiāli, tad nolasaam taas darbus no datu baazes
  	    $aCustomerDb=dbProc::getActPersonalList($actId);
        $totalProportion = dbProc::getActPersonalProportion($actId);

        $totalUnPropBaseTime = 0;
        $totalUnPropOverTime = 0;
        foreach($aCustomerDb as $i => $row)
        {
          if($row['PRSN_IS_PROPORTIONAL'] == 1)
          {
              $totalUnPropBaseTime = ($totalUnPropBaseTime + $row['PRSN_PAMATSTUNDAS']);
              $totalUnPropOverTime = ($totalUnPropOverTime + $row['PRSN_VIRSSTUNDAS']);
          }
        }
        $totalTime = ($totalTime - $totalUnPropBaseTime);
        $totalTimeWithKoef = ($totalTimeWithKoef - $totalUnPropOverTime);

        if($totalProportion > 0)
        {
          ?>
          var rowCount = getFormValue("frmPersonalTab", "rowCount") ;
          var index = <?=reqVar::get('index');?>;

          var totalTimeTmp = <?=$totalTime;?> ;
          var totalTimeWithKoefTmp = <?=$totalTimeWithKoef;?>;

          var proportion;
          var baseTime;
          var overTime;

          var baseTime0;
          var overTime0;
          var j = -1;
          for(i=0; i < rowCount; i++)
          {  if(getFormValue("frmPersonalTab", "isProportional["+i+"]") != 1)
             if(isSetFormField("frmPersonalTab", "code["+i+"]"))
             {
               if(i != index)
               {
                 proportion = 1*(getFormValue("frmPersonalTab", "proportion["+i+"]"));
                 baseTime = Math.round(((<?=round($totalTime/$totalProportion, 2);?>)*proportion)*Math.pow(10,2))/Math.pow(10,2);
                 overTime = Math.round(((<?=round($totalTimeWithKoef/$totalProportion, 2);?>)*proportion)*Math.pow(10,2))/Math.pow(10,2);
                 setFormValue("frmPersonalTab","baseTime["+i+"]", ((baseTime == 0)? '0.00' : baseTime));
                 setFormValue("frmPersonalTab","overTime["+i+"]", ((overTime == 0)? '0.00' : overTime));

                 j = i;
                 baseTime0 = baseTime;
                 overTime0 = overTime;

                 totalTimeTmp = Math.round( (totalTimeTmp - baseTime)*Math.pow(10,2))/Math.pow(10,2);
                 totalTimeWithKoefTmp = Math.round( (totalTimeWithKoefTmp - overTime)*Math.pow(10,2))/Math.pow(10,2);

               }
             }
          }
          if( totalTimeTmp != 0)
          {
             baseTime0 = Math.round((baseTime0 + totalTimeTmp)*Math.pow(10,2))/Math.pow(10,2);
             setFormValue("frmPersonalTab","baseTime["+j+"]", ((baseTime0 == 0)? '0.00' : baseTime0));
          }

          if( totalTimeWithKoefTmp != 0)
          {
             overTime0 = Math.round((overTime0 + totalTimeWithKoefTmp)*Math.pow(10,2))/Math.pow(10,2);
             setFormValue("frmPersonalTab","overTime["+j+"]", ((overTime0 == 0)? '0.00' : overTime0));
          }

          <?
        }
    }
    exit();
}

// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
    if($actId !== false )
    {
      $oLink=new urlQuery();
      $oLink->addPrm(FORM_ID, 'f.akt.s.1');
      $oLink->addPrm('actId', $actId);
      $oLink->addPrm('isSearch', $isSearch);
      $oLink->addPrm('searchNum', $searchNum);
      $oLink->addPrm('tab', TAB_PERONAL);
      $oFormPersonalTab = new Form('frmPersonalTab','post',$oLink->getQuery().'#tab');
      unset($oLink);

      // if operation is success, show success message and redirect top frame
      if (reqVar::get('successMessageTab') && $isNew === false)
      {
      	$oFormPersonalTab->addSuccess(reqVar::get('successMessageTab'));
      }

      $isReadonly   = true;
      // Ir pieejams mainīšanai, ja  AKTS:LIETOTĀJS = ’Tekošais lietotājs’ un lietotāja loma ir ‘Ievadītais’ un AKTS:STATUS = ‘Izveide’ vai ‘Atgriezts’ vai ‘Tāme’.
      if(($act['RAKT_RLTT_ID'] == $userId && ($isEditor || $isAdmin) && ($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ESTIMATE)) )
      {
        $isReadonly   = false;
      }

      //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.8');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('catalog',KL_CUSTOMERS);
      $oPopLink->addPrm('isSearch', $isSearch);
      $oPopLink->addPrm('searchNum', $searchNum);

      // get favorit
      $favorit=array();
      $krfk = dbProc::getKrfkInfo(KRFK_CUSTOMER_ID);
      if($krfk !== false)
      {

        $res=dbProc::getFavoritTypeDefinitionList($userId, $krfk['KRFK_VERTIBA']);
        if (is_array($res))
        {
         	foreach ($res as $i => $row)
         	{
              $favorit[$i]['TITLE'] = $row['LTFV_NOSAUKUMS'];
          	  $favorit[$i]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery().'&favoritId='.$row['LTFV_ID']);
            }
        }
        unset($res);
      }

      $next =  count($favorit);
      $favorit[$next]['TITLE'] = text::get('ALL_VALUES');   ;
      $favorit[$next]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery().'&all=1');
       // get region list
       $region=array();
       $res=dbProc::getKrfkName(KRFK_REGION);
       if (is_array($res))
       {
       	foreach ($res as $i => $row)
       	{
       		$region[$i]['TITLE'] = $row['nosaukums'];
          	$region[$i]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery().'&region='.$row['nosaukums']);
       	}
       }
       unset($res);
       unset($oPopLink);

      // get act works total time
      $totalTimeFixed = number_format(dbProc::getActTotalWorkTime($actId), 2, '.', '');
      $totalTimeWithKoefFixed = number_format(($totalTimeFixed*($koef-1)), 2, '.', '');
      

      $aCustomers = array();
      if ($oFormPersonalTab -> isFormSubmitted() && $isNew === false)
      {
          $isRowValid = true;
          $isError = false;
          $aCodes =  $oFormPersonalTab->getValue('code');
          if(is_array($aCodes) )
          {

            $tProp = 0;
            $tPamat = 0;
            $tVirs = 0;

            foreach ($aCodes as $i => $val)
            {
                 $aCustomers[$i]['PRSN_ID'] = $oFormPersonalTab->getValue('id['.$i.']');
                 $aCustomers[$i]['PRSN_RCD_KODS'] = $oFormPersonalTab->getValue('code['.$i.']');
                 $aCustomers[$i]['PRSN_VARDS_UZVARDS'] = $oFormPersonalTab->getValue('nameSurname['.$i.']');
                 $aCustomers[$i]['PRSN_DARBA_VIETA'] = $oFormPersonalTab->getValue('place['.$i.']');
                 $aCustomers[$i]['PRSN_REGION'] = $oFormPersonalTab->getValue('region['.$i.']');
                 $aCustomers[$i]['PRSN_PROPORCIJA'] = $oFormPersonalTab->getValue('proportion['.$i.']');
                 $aCustomers[$i]['PRSN_PAMATSTUNDAS'] = $oFormPersonalTab->getValue('baseTime['.$i.']');
                 $aCustomers[$i]['PRSN_VIRSSTUNDAS'] = $oFormPersonalTab->getValue('overTime['.$i.']');
                 $aCustomers[$i]['PRSN_IS_PROPORTIONAL'] = $oFormPersonalTab->getValue('isProportional['.$i.']');

                 // validate proportion value
    			 if (!empty($aCustomers[$i]['PRSN_PROPORCIJA']))
    			 {
    			    // assign error message
    				//$oFormPersonalTab->addErrorPerElem('proportion['.$i.']', text::get('ERROR_REQUIRED_FIELD'));
    				//$isRowValid = false;

                     if (!is_numeric($aCustomers[$i]['PRSN_PROPORCIJA']))
        			 {
        				 // assign error message
        				 $oFormPersonalTab->addErrorPerElem('proportion['.$i.']', text::get('ERROR_DOUBLE_VALUE'));
        				 $isRowValid = false;
        			 }
                     elseif ($aCustomers[$i]['PRSN_PROPORCIJA'] >= 100)
        			 {
        			 	// assign error message
        			 	$oFormPersonalTab->addErrorPerElem('proportion['.$i.']', text::get('ERROR_AMOUNT_VALUE'));
        			 	$isRowValid = false;
        			 }
                     else
                     {
                       $tProp = round(($tProp + $aCustomers[$i]['PRSN_PROPORCIJA']), 2);
                     }
                 }


                 // validate baseTime value
    			 if (empty($aCustomers[$i]['PRSN_PAMATSTUNDAS']))
    			 {
    			    // assign error message
    				$oFormPersonalTab->addErrorPerElem('baseTime['.$i.']', text::get('ERROR_REQUIRED_FIELD'));
    				$isRowValid = false;
    			 }
                 elseif (!is_numeric($aCustomers[$i]['PRSN_PAMATSTUNDAS']))
    			 {
    				 // assign error message
    				 $oFormPersonalTab->addErrorPerElem('baseTime['.$i.']', text::get('ERROR_DOUBLE_VALUE'));
    				 $isRowValid = false;
    			 }
                 elseif ($aCustomers[$i]['PRSN_PAMATSTUNDAS'] >= 100000000)
    			 {
    			 	// assign error message
    			 	$oFormPersonalTab->addErrorPerElem('baseTime['.$i.']', text::get('ERROR_AMOUNT_VALUE_100000'));
    			 	$isRowValid = false;
    			 }
                 else
                 {
                   $tPamat = round(($tPamat + $aCustomers[$i]['PRSN_PAMATSTUNDAS']), 2);
                 }


                 // validate overTime value
    			 if (empty($aCustomers[$i]['PRSN_VIRSSTUNDAS']))
    			 {
    			    // assign error message
    				//$oFormPersonalTab->addErrorPerElem('overTime['.$i.']', text::get('ERROR_REQUIRED_FIELD'));
    				//$isRowValid = false;
    			 }
                 elseif (!is_numeric($aCustomers[$i]['PRSN_VIRSSTUNDAS']))
    			 {
    				 // assign error message
    				 $oFormPersonalTab->addErrorPerElem('overTime['.$i.']', text::get('ERROR_DOUBLE_VALUE_100000'));
    				 $isRowValid = false;
    			 }
                 elseif ($aCustomers[$i]['PRSN_VIRSSTUNDAS'] >= 100000000)
    			 {
    			 	// assign error message
    			 	$oFormPersonalTab->addErrorPerElem('overTime['.$i.']', text::get('ERROR_AMOUNT_VALUE'));
    			 	$isRowValid = false;
    			 }
                 else
                 {
                   $tVirs = round(($tVirs + $aCustomers[$i]['PRSN_VIRSSTUNDAS']), 2);
                 }

                // prepare database record data
  			    $aValidRows[] = array(
      				'code' => $aCustomers[$i]['PRSN_RCD_KODS'],
      				'nameSurname' => $aCustomers[$i]['PRSN_VARDS_UZVARDS'],
      				'place' => $aCustomers[$i]['PRSN_DARBA_VIETA'],
                    'region' => $aCustomers[$i]['PRSN_REGION'],
      				'proportion' => $aCustomers[$i]['PRSN_PROPORCIJA'],
                    'baseTime' => number_format($aCustomers[$i]['PRSN_PAMATSTUNDAS'],2,'.',''),
                    'overTime' => number_format($aCustomers[$i]['PRSN_VIRSSTUNDAS'],2,'.',''),
                    'isProportional' => $aCustomers[$i]['PRSN_IS_PROPORTIONAL'],
                    'rowNum' => $i
  			    );
             }



            /* if($totalTimeWithKoef != $tVirs || $totalTime != $tPamat)
             {
                $oFormPersonalTab->addError(text::get('ERROR_CUSTOMER_SUMM_CHECK'));
                $isError = true;
             }*/
           }
      }
      else
      {
        //Ja eksistee akta materiāli, tad nolasaam taas darbus no datu baazes
  	    $aCustomerDb=dbProc::getActPersonalList($actId);

        foreach ($aCustomerDb as $i => $customer)
        {
           $aCustomers[$i]['PRSN_ID'] = $customer['PRSN_ID'];
           $aCustomers[$i]['PRSN_RCD_KODS'] = $customer['PRSN_RCD_KODS'];
           $aCustomers[$i]['PRSN_VARDS_UZVARDS'] = $customer['PRSN_VARDS_UZVARDS'];
           $aCustomers[$i]['PRSN_DARBA_VIETA'] = $customer['PRSN_DARBA_VIETA'];
           $aCustomers[$i]['PRSN_REGION'] = $customer['PRSN_REGION'];
           $aCustomers[$i]['PRSN_PROPORCIJA'] = $customer['PRSN_PROPORCIJA'];
           $aCustomers[$i]['PRSN_PAMATSTUNDAS'] = number_format($customer['PRSN_PAMATSTUNDAS'],2,'.','');
           $aCustomers[$i]['PRSN_VIRSSTUNDAS'] = number_format($customer['PRSN_VIRSSTUNDAS'],2,'.','');
           $aCustomers[$i]['PRSN_IS_PROPORTIONAL'] = $customer['PRSN_IS_PROPORTIONAL'];

        }
      }
      $oFormPersonalTab -> addElement('hidden', 'isSearch', '', $isSearch);
      $oFormPersonalTab -> addElement('hidden', 'searchNum', '', $searchNum);
      $oFormPersonalTab->addElement('hidden','actId','',$actId);
      $oFormPersonalTab->addElement('hidden','maxAmaunt','','1000.00');
      $oFormPersonalTab->addElement('hidden','maxAmaunt1','','100.00');
      $oFormPersonalTab->addElement('hidden','maxAmaunt2','','100000000.00');
      $oFormPersonalTab->addElement('hidden','minAmaunt','','0.00');
      $oFormPersonalTab->addElement('label','totalOverTime','','');
      $rowCount = 0;
      $totalWorkTime = 0;
      $totalOverTime = 0;
      // form elements
      foreach ($aCustomers as $i => $actCustomer)
      {
        $oFormPersonalTab->addElement('hidden', 'id['.$i.']', '', $actCustomer['PRSN_ID']);
        $oFormPersonalTab->addElement('label', 'code['.$i.']', '', $actCustomer['PRSN_RCD_KODS']);
        $oFormPersonalTab->addElement('label', 'nameSurname['.$i.']', '', $actCustomer['PRSN_VARDS_UZVARDS']);
        $oFormPersonalTab->addElement('hidden', 'place['.$i.']', '', $actCustomer['PRSN_DARBA_VIETA']);
        $oFormPersonalTab->addElement('hidden', 'region['.$i.']', '', $actCustomer['PRSN_REGION']);

        $oFormPersonalTab->addElement('text', 'proportion['.$i.']', '', $actCustomer['PRSN_PROPORCIJA'], (($isReadonly)?' disabled ':'').'maxlength="6"');
        //$oFormPersonalTab -> addRule('proportion['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oFormPersonalTab -> addRule('proportion['.$i.']', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);
        // check Amaunt field
        $v1=&$oFormPersonalTab->createValidation('proportionValidation_'.$i, array('proportion['.$i.']'), 'ifonefilled');
        // ja Amount ir definēts un > 1000
        $r1=&$oFormPersonalTab->createRule(array('proportion['.$i.']', 'maxAmaunt1'), text::get('ERROR_AMOUNT_VALUE_100'), 'comparedouble','<');
        // ja Amount ir definēts un < 0
        $r2=&$oFormPersonalTab->createRule(array('proportion['.$i.']', 'minAmaunt'), text::get('ERROR_AMOUNT_VALUE_100'), 'comparedouble','>');
        $oFormPersonalTab->addRule(array($r1, $r2), 'groupRuleProportion_'.$i, 'group', $v1);

        $oFormPersonalTab->addElement('text', 'baseTime['.$i.']', '', $actCustomer['PRSN_PAMATSTUNDAS'], (($isReadonly)?' disabled ':'').'maxlength="11"');
        $oFormPersonalTab -> addRule('baseTime['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oFormPersonalTab -> addRule('baseTime['.$i.']', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);
        // check Amaunt field
        $v2=&$oFormPersonalTab->createValidation('baseTimeValidation_'.$i, array('baseTime['.$i.']'), 'ifonefilled');
        // ja Amount ir definēts un > 100000
        $r1=&$oFormPersonalTab->createRule(array('baseTime['.$i.']', 'maxAmaunt2'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','<');
        // ja Amount ir definēts un < 0
        //$r2=&$oFormPersonalTab->createRule(array('baseTime['.$i.']', 'minAmaunt'), text::get('ERROR_AMOUNT_VALUE'), 'comparedouble','>');
        $oFormPersonalTab->addRule(array($r1), 'groupRuleBaseTime_'.$i, 'group', $v2);

        $oFormPersonalTab->addElement('text', 'overTime['.$i.']', '', $actCustomer['PRSN_VIRSSTUNDAS'], (($isReadonly)?' disabled ':'').'maxlength="11"');
        //$oFormPersonalTab -> addRule('overTime['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oFormPersonalTab -> addRule('overTime['.$i.']', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);
        // check Amaunt field
        $v3=&$oFormPersonalTab->createValidation('overTimeValidation_'.$i, array('overTime['.$i.']'), 'ifonefilled');
        // ja Amount ir definēts un > 1000
        $r1=&$oFormPersonalTab->createRule(array('overTime['.$i.']', 'maxAmaunt2'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','<');
        // ja Amount ir definēts un < 0
        //$r2=&$oFormPersonalTab->createRule(array('overTime['.$i.']', 'minAmaunt'), text::get('ERROR_AMOUNT_VALUE'), 'comparedouble','>');
        $oFormPersonalTab->addRule(array($r1), 'groupRuleOverTime_'.$i, 'group', $v3);

        $totalWorkTime += $actCustomer['PRSN_PAMATSTUNDAS'];
        $totalOverTime += $actCustomer['PRSN_VIRSSTUNDAS'];
        // checkbox
        $checkboxJs = "	var index=" . $i . ";
                        if(this.checked) {
						    document.forms['frmPersonalTab']['proportion['+index+']'].value = '';
                            document.forms['frmPersonalTab']['proportion['+index+']'].disabled = true;
                        }else{
                            document.forms['frmPersonalTab']['proportion['+index+']'].value = '1.00';
                            document.forms['frmPersonalTab']['proportion['+index+']'].disabled = false;
                        }";
        $oFormPersonalTab -> addElement('checkbox', 'isProportional['.$i.']',  '', $actCustomer['PRSN_IS_PROPORTIONAL'], 'onclick="' . $checkboxJs . '"'.(($isReadonly)?' disabled ':''));

        // ajax handler link for delete
	    $delLink = new urlQuery();
	    $delLink->addPrm(FORM_ID, 'f.akt.s.5');
	    $delLink->addPrm(DONT_USE_GLB_TPL, '1');
        $delLink->addPrm('actId', $actId);
        $delLink->addPrm('xmlHttp', '1');
	   	// delete button
        $delButtonJs = "if(isDelete()) {
							var index=" . $i . ";
							var rowId = document.forms['frmPersonalTab']['id['+index+']'];
							rowId = rowId ? rowId.value : '';
							eval(xmlHttpGetValue('" .$delLink -> getQuery() ."&deleteId='+rowId+'&index='+index));
						}";
		$oFormPersonalTab->addElement('button', 'cust_del['.$i.']', '', '', 'onclick="' . $delButtonJs . ';return false;" style="background: url(img/ico_del.gif); cursor:hand; border:0px; width: 20px; height: 20px;" title="' . text::get('DELETE') . '"');
        unset($delLink);

        $rowCount++;
      }
      $totalWorkTime = number_format($totalWorkTime, 2);
      $totalOverTime = number_format($totalOverTime, 2);

      $oFormPersonalTab->addElement('hidden','rowCount','',$rowCount);

      // form buttons
      if (!$isReadonly)
      {
        foreach ($favorit as $i => $group)
        {
           $oFormPersonalTab->addElement('link', 'favorit['.$i.']', $group['TITLE'], '#', 'onClick="'.$group['URL'].'"', '');
        }
        foreach ($region as $i => $r)
        {
           $oFormPersonalTab->addElement('link', 'regions['.$i.']', $r['TITLE'], '#', 'onClick="'.$r['URL'].'"', '');
        }
        $oFormPersonalTab -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_save_personal.gif', 'width="120" height="20" ');
        //$oFormPersonalTab -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"');
      }

      // if form iz submit (save button was pressed)
	  if ($oFormPersonalTab -> isFormSubmitted()&& $isNew === false)
	  {
		if($oFormPersonalTab ->isValid() && $isRowValid && !$isError )
		{
		   $r=dbProc::deleteActPersonals($actId);
		   if ($r === false)
		   {
		   	$oFormPersonalTab->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
		   }
		   else
		   {    /*echo "<pre>";
		        print_r($aValidRows);
                echo "</pre>";*/
		        if(isset($aValidRows) && is_array($aValidRows))
                {
                    $totalWorkTime = 0;
                    $totalOverTime = 0;
                    $totalTime = 0;
                    $totalTimeWithKoef = 0;
                    $totalProportion = $tProp;
                    $totalUnPropBaseTime = 0;
                    $totalUnPropOverTime = 0;
                    $n = 0;
                    foreach($aValidRows as $i => $row)
        			{
                       if($row['isProportional']==1)
                       {
                          $totalUnPropBaseTime = ($totalUnPropBaseTime + $row['baseTime']);
                          $totalUnPropOverTime = ($totalUnPropOverTime + $row['overTime']);
                          $n++;

                       }
                    }
                    $totalTime = ($totalTimeFixed - $totalUnPropBaseTime);
                    $totalTimeWithKoef = ($totalTimeWithKoefFixed - $totalUnPropOverTime);

                    if(($totalTime < 0 || $totalTimeWithKoef < 0) ||
                        (count($aValidRows) == $n && ($totalTime != 0 || $totalTimeWithKoef != 0)))
                    {
                      $oFormPersonalTab->addError(text::get('WORK_TIME_NOT_EQUAL_PERSONAL_TIME'));
                    }
                    else
                    {
                        $totalTimeTmp = $totalTime;
                        $totalTimeWithKoefTmp = $totalTimeWithKoef;

            	    	foreach($aValidRows as $i => $row)
            			{
                          if(!$row['isProportional'])
                          {
                              $baseTime = round(($totalTime/$totalProportion)*$row['proportion'], 2);
                              $overTime = round(($totalTimeWithKoef/$totalProportion)*$row['proportion'], 2);

                              $baseTime0 = $baseTime;
                              $overTime0 = $overTime;
                              $proportion0 = $row['proportion'];
                              $rowNum0 = $row['rowNum'];
                          }
                          $r=dbProc::writeActPersonal($actId,
                                                    $row['code'],
                                                    $row['nameSurname'],
                                                    $row['place'],
                                                    $row['region'],
                                                    $row['proportion'],
                                                    ((!$row['isProportional'])?$baseTime:$row['baseTime']),
                                                    ((!$row['isProportional'])?$overTime:$row['overTime']),
                                                    (($row['isProportional'])?$row['isProportional']:0));

                             // if work not inserted in to the DB
                             $totalWorkTime += ((!$row['isProportional'])?$baseTime:$row['baseTime']);
                             $totalOverTime += ((!$row['isProportional'])?$overTime:$row['overTime']);
        					 // delete  task record and show error message
        					 if($r === false)
        					 {
        					 	dbProc::deleteActPersonals($actId);
        					 	$oFormPersonalTab->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
        				        break;
        					 }
                             else
                             {
                               $Id=dbLayer::getInsertId();
                               if(!$row['isProportional'])
                               {
                                 $Id0 = $Id;
                               }

                               $oFormPersonalTab -> setNewValue('id['.$row['rowNum'].']', $Id);

                               if(!$row['isProportional'])
                               {
                                   $oFormPersonalTab -> setNewValue('baseTime['.$row['rowNum'].']', number_format($baseTime,2,'.',''));
                                   $oFormPersonalTab -> setNewValue('overTime['.$row['rowNum'].']', number_format($overTime,2,'.',''));

                                   $totalTimeTmp = round(($totalTimeTmp -  $baseTime), 2);
                                   $totalTimeWithKoefTmp = round(($totalTimeWithKoefTmp -  $overTime), 2);
                               }
                             }
                        }

                        if(isset($baseTime0) && isset($overTime0) && isset($proportion0) && isset($rowNum0))
                        {
                            if( $totalTimeTmp != 0)
                            {
                               $baseTime0 = round(($baseTime0 + $totalTimeTmp), 2);
                               $totalWorkTime += $totalTimeTmp;
                            }
                            if( $totalTimeWithKoefTmp != 0)
                            {
                               $overTime0 = round(($overTime0 + $totalTimeWithKoefTmp), 2);
                               $totalWorkTime += $totalTimeWithKoefTmp;
                            }
                            $r = dbProc::updatePersonalTime($Id0,
                                                                $proportion0,
                                                                $baseTime0,
                                                                $overTime0);
                            if(!$r)
                            {
                               $oFormPop->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                            }
                            else
                            {
                               $oFormPersonalTab -> setNewValue('baseTime['.$rowNum0.']', number_format($baseTime0,2,'.',''));
                               $oFormPersonalTab -> setNewValue('overTime['.$rowNum0.']', number_format($overTime0,2,'.',''));

                               $oFormPersonalTab->addSuccess(text::get('RECORD_WAS_SAVED'));
                            }
                        }
                        $totalWorkTime = number_format($totalWorkTime, 2);
                        $totalOverTime = number_format($totalOverTime, 2);
                    }
                    // saglaba lietotaja darbiibu
                    dbProc::setUserActionDate($userId, ACT_UPDATE);
                }
           }
        }
      }
       $oFormPersonalTab -> makeHtml();
       include('f.akt.s.5.tpl');
    }



}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>