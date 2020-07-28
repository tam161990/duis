<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);

// act ID
$actId  = reqVar::get('actId');
// search form
$isSearch  = reqVar::get('isSearch');
// search act by number
$searchNum  = reqVar::get('searchNum');
// TRASE act
$trase =  reqVar::get('isTrase');
if($trase === false) $trase = 0;
// Auto
if(isset($tame))
  $tameWork  = $tame;
else 
  $tameWork   = reqVar::get('tame');
if(isset($actNumPostfix))
  $kvikstep  = $actNumPostfix;
else 
  $kvikstep =  reqVar::get('kvikstep');


// Main form with XMLHTTP method load this code:
if (reqVar::get('xmlHttp') == 1)
{
    // if operation is DELETE , delete record from DB
    if (reqVar::get('deleteId')!='')
	{
	   dbProc::deleteActWorkRecord(reqVar::get('deleteId'), reqVar::get('tame'));
    ?>
	    rowNode = this.parentNode.parentNode;
		  rowNode.parentNode.removeChild(rowNode);
		<?
    }
    exit();
}

// tikai  sistï¿½mas lietotajam vai administrï¿½toram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
    if($actId !== false )
    {
      $oLink=new urlQuery();
      $oLink->addPrm(FORM_ID, 'f.akt.s.1');
      $oLink->addPrm('actId', $actId);
      $oLink->addPrm('tab', TAB_WORKS);
      $oLink->addPrm('tametab', strtoupper(text::get(TAB_ESTIMATE)). ' ' .TAB_WORKS_T);
      $oLink->addPrm('isSearch', $isSearch);
      $oLink->addPrm('searchNum', $searchNum);
      $oLink->addPrm('trase', $trase);
      $oLink->addPrm('kvikstep ', $kvikstep);
      $oFormWorkTab = new Form('frmWorkTab'.(($tameWork==1) ? 'T' : ''), 'post', $oLink->getQuery() . '#tab');

      unset($oLink);
      

      // if operation is success, show success message and redirect top frame
      if (reqVar::get('successMessageTab') && $isNew === false)
      {
      	$oFormWorkTab->addSuccess(reqVar::get('successMessageTab'));

      }

      $isReadonly   = true;
      // Ir pieejams mainï¿½ï¿½anai, ja  AKTS:LIETOTï¿½JS = ï¿½Tekoï¿½ais lietotï¿½jsï¿½ un lietotï¿½ja loma ir ï¿½Ievadï¿½taisï¿½ un AKTS:STATUS = ï¿½Izveideï¿½ vai ï¿½Atgrieztsï¿½ vai ï¿½Tï¿½meï¿½.
      if((( $act['RAKT_RLTT_ID'] == $userId && $isEditor) || $isAdmin || $isEconomist) && 
        ((($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ESTIMATE) && $tameWork==0 )|| 
        ($status == STAT_AUTO && $tameWork==1 ))
      )
      {
        $isReadonly   = false;
      }

      //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.8');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('catalog',KL_CALCULALATION);
      $oPopLink->addPrm('isSearch', $isSearch);
      $oPopLink->addPrm('searchNum', $searchNum);
      $oPopLink->addPrm('isTrase', $trase);
      $oPopLink->addPrm('tame', $tameWork ?'1':'0');
     
      $tameGroup['TITLE'] = text::get('TAB_ESTIMATE');   ;
      $tameGroup['URL'] = RequestHandler::popupHref($oPopLink -> getQuery().'&estimate=1', false, 700, 450);

      // get calgulation group
      $calcGroups=array();
      $j = 0;
      if(  $trase == 1)
      {
         $calcGroups[$j]['TITLE'] = text::get('TRASE_WORK');
         $calcGroups[$j]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery(), false, 700, 450, true, false, true);
      }
      else
      {
        
        $res=dbProc::getCalculationGroupActivList();

        if (is_array($res))
        {
         	foreach ($res as $i => $row)
         	{
              $calcGroups[$i]['TITLE'] = $row['KKLG_NOSAUKUMS'];
          	  $calcGroups[$i]['URL'] =  RequestHandler::popupHref($oPopLink -> getQuery().'&calcGroup='.$row['KKLG_KODS'], false, 700, 450);
              $j++;
          }
        }
         $calcGroups[$j]['TITLE'] = text::get('ALL_WORK');
         $calcGroups[$j]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery().'&all=1', false, 700, 450, true, false, true);

      }
      unset($oPopLink);
      unset($res);


      $aWorks = array();
      $aWorkExist = false;
      if ($oFormWorkTab -> isFormSubmitted() && $isNew === false)
      {
          
          $isRowValid = true;
          $aChiphers =  $oFormWorkTab->getValue('chipher');
          if(is_array($aChiphers) )
          {
            $aWorkFr = array();
            foreach ($aChiphers as $i => $val)
            {
                 
				         $aWorkFr[$i]['DRBI_KKAL_ID'] = $oFormWorkTab->getValue('kid['.$i.']');
                 $aWorkFr[$i]['DRBI_KKAL_SHIFRS'] = $oFormWorkTab->getValue('chipher['.$i.']');
                 $aWorkFr[$i]['DRBI_KKAL_NOSAUKUMS'] = $oFormWorkTab->getValue('title['.$i.']');
                 $aWorkFr[$i]['DRBI_KKAL_NORMATIVS'] = $oFormWorkTab->getValue('standart['.$i.']');                 
                 $aWorkFr[$i]['DRBI_MERVIENIBA'] = $oFormWorkTab->getValue('measure['.$i.']');
                 $aWorkFr[$i]['DRBI_ID'] = $oFormWorkTab->getValue('id['.$i.']');
                 $aWorkFr[$i]['DRBI_APPROVE_DATE'] = $oFormWorkTab->getValue('edited['.$i.']');
                 $aWorkFr[$i]['DRBI_PLAN_DATE'] = $oFormWorkTab->getValue('plan_date['.$i.']');
                 $aWorkFr[$i]['KKAL_APRAKSTS'] = $oFormWorkTab->getValue('description['.$i.']');
                 
                 if($tameWork ){
                   
                    $aWorkFr[$i]['DRBI_DAUDZUMS_KOR'] = $oFormWorkTab->getValue('amount_kor['.$i.']');
                    // validate work progress value
                    if (empty($aWorkFr[$i]['DRBI_DAUDZUMS_KOR']))
                    {
                        // assign error message
                        $oFormWorkTab->addErrorPerElem('amount_kor['.$i.']', text::get('ERROR_REQUIRED_FIELD'));
                        $isRowValid = false;
                    }
                    // validate work progress value
                    elseif (!is_numeric($aWorkFr[$i]['DRBI_DAUDZUMS_KOR']))
                    {
                        // assign error message
                        $oFormWorkTab->addErrorPerElem('amount_kor['.$i.']', text::get('ERROR_DOUBLE_VALUE'));
                        $isRowValid = false;
                    }
                    // validate work progress value
                    elseif ($aWorkFr[$i]['DRBI_DAUDZUMS_KOR'] >= 100000)
                    {
                        // assign error message
                        $oFormWorkTab->addErrorPerElem('amount_kor['.$i.']', text::get('ERROR_AMOUNT_VALUE_100000'));
                        $isRowValid = false;
                    }
                    else
                    {
                        $aWorkFr[$i]['DRBI_CILVEKSTUNDAS'] = number_format(($aWorkFr[$i]['DRBI_KKAL_NORMATIVS']*$aWorkFr[$i]['DRBI_DAUDZUMS_KOR']), 2, '.', '');
                    }
                    $aWorkFr[$i]['DRBI_DAUDZUMS'] = $oFormWorkTab->getValue('amount_k['.$i.']');
                    
                } else {
                  
                    $aWorkFr[$i]['DRBI_DAUDZUMS'] = $oFormWorkTab->getValue('amount['.$i.']');
                    // validate work progress value
                    if (empty($aWorkFr[$i]['DRBI_DAUDZUMS'])) {
                        // assign error message
                        $oFormWorkTab->addErrorPerElem('amount[' . $i . ']', text::get('ERROR_REQUIRED_FIELD'));
                        $isRowValid = false;
                    } // validate work progress value
                    elseif (!is_numeric($aWorkFr[$i]['DRBI_DAUDZUMS'])) {
                        // assign error message
                        $oFormWorkTab->addErrorPerElem('amount[' . $i . ']', text::get('ERROR_DOUBLE_VALUE'));
                        $isRowValid = false;
                    } // validate work progress value
                    elseif ($aWorkFr[$i]['DRBI_DAUDZUMS'] >= 100000) {
                        // assign error message
                        $oFormWorkTab->addErrorPerElem('amount[' . $i . ']', text::get('ERROR_AMOUNT_VALUE_100000'));
                        $isRowValid = false;
                    } else {
                        $aWorkFr[$i]['DRBI_CILVEKSTUNDAS'] = number_format(($aWorkFr[$i]['DRBI_KKAL_NORMATIVS'] * $aWorkFr[$i]['DRBI_DAUDZUMS']), 2, '.', '');

                    }
                }

                  // prepare database record data
                  $aAllRows[] = array(
                    'kid' => $aWorkFr[$i]['DRBI_KKAL_ID'],
                    'chipher' => $aWorkFr[$i]['DRBI_KKAL_SHIFRS'],
                    'title' => $aWorkFr[$i]['DRBI_KKAL_NOSAUKUMS'],
                    'standart' => $aWorkFr[$i]['DRBI_KKAL_NORMATIVS'],
                    'amount' => $aWorkFr[$i]['DRBI_DAUDZUMS'],
                    'amount_kor' => ($oFormWorkTab->getValue('tame') == 1) ? $aWorkFr[$i]['DRBI_DAUDZUMS_KOR'] :'',
                    'total' => $aWorkFr[$i]['DRBI_CILVEKSTUNDAS'],
                    'measure' => $aWorkFr[$i]['DRBI_MERVIENIBA'],
                    'edited' => $aWorkFr[$i]['DRBI_APPROVE_DATE'],
                    'plan_date' => $aWorkFr[$i]['DRBI_PLAN_DATE'],
                    'description' => $aWorkFr[$i]['KKAL_APRAKSTS'],
                    'rowNum' => $i
                  );   
                  
                  
             }
            // transform for calculate tota summ for the date
            $aSumms = array();
            foreach ($aAllRows as $i => $row){
              if(isset($aSumms[$row['plan_date']])) {
                $aSumms[$row['plan_date']] += $row['total'];
              } else {
                $aSumms[$row['plan_date']] = $row['total'];
              }              
            }
            foreach ($aAllRows as $i => $row){
              $aValidRows[$i] = $row;
              $aValidRows[$i]['day_total'] = $aSumms[$row['plan_date']];
            }

            foreach ($aWorkFr as $i=>$work)
            {
              $aWorks[$work['DRBI_PLAN_DATE']][] = $work;
              //$aWorks[$work['DRBI_PLAN_DATE']][$i]['DRBI_DAY_TOTAL'] = $aSumms[$work['DRBI_PLAN_DATE']];
            }
            foreach ($aWorks as $d => $aDayWorks)
            {
              foreach ($aDayWorks as $i => $actWork)
              {
                $aWorks[$actWork['DRBI_PLAN_DATE']][$i]['DRBI_DAY_TOTAL'] = $aSumms[$actWork['DRBI_PLAN_DATE']];
              }
            }

            //echo '<pre>',print_r($aWorkFr,true),'</pre>';
            //echo '<pre>',print_r($aWorks,true),'</pre>';
           }
      }
      else
      {
        //Ja eksistee akta darbi, tad nolasaam taas darbus no datu baazes
  	$aWorkDb=dbProc::getActWorkList($actId, $tameWork);
        $aWorkExist = false;
        foreach ($aWorkDb as $work)
        {
          $aWorks[$work['DRBI_PLAN_DATE']][] = $work;     
          $aWorkExist = true;     
        }
	if($trase == 1) {
		$aWorkSums = dbProc::getActWorkSumms($actId, $tameWork);
 		foreach ($aWorkSums as $d => $aSum)
      		{
			$oFormWorkTab->addElement('label', 'sum_m3', 'M3', $aSum['m3']);
			$oFormWorkTab->addElement('label', 'sum_ha', 'HA', $aSum['ha']);
			$oFormWorkTab->addElement('label', 'sum_km', 'KM', $aSum['km']);
			$oFormWorkTab->addElement('label', 'sum_gab', 'GAB', $aSum['gab']);
			break;
      		}
	   }
	
      }

     
      if(!$aWorkExist) {
        $aWorks[0] = array();          
      }
      
     

      //echo '<pre>',print_r($aWorks,true),'</pre>';

      $oFormWorkTab -> addElement('hidden', 'isSearch', '', $isSearch);
      $oFormWorkTab -> addElement('hidden', 'searchNum', '', $searchNum);
      $oFormWorkTab->addElement('hidden','actId','',$actId);
      $oFormWorkTab->addElement('hidden','isTrase','',$trase);
      $oFormWorkTab->addElement('hidden','maxAmaunt','','100000.00');
      $oFormWorkTab->addElement('hidden','minAmaunt','','0.00');
      $oFormWorkTab->addElement('hidden','tame','',($tameWork) ? 1 : 0);
      
      $totalTime = array();
      $i = 0;
      // form elements
      foreach ($aWorks as $d => $aDayWorks)
      {
        foreach ($aDayWorks as $j => $actWork)
        {          
          $oFormWorkTab->addElement('hidden', 'id['.$i.']', '', $actWork['DRBI_ID']);
          $oFormWorkTab->addElement('hidden', 'kid['.$i.']', '', $actWork['DRBI_KKAL_ID']);
          $oFormWorkTab->addElement('hidden', 'edited['.$i.']', '', $actWork['DRBI_APPROVE_DATE']);
          $oFormWorkTab->addElement('hidden', 'description['.$i.']', '', $actWork['KKAL_APRAKSTS']);
          $oFormWorkTab->addElement('label', 'chipher['.$i.']', '', $actWork['DRBI_KKAL_SHIFRS']);
          $oFormWorkTab->addElement('label', 'title['.$i.']', '', $actWork['DRBI_KKAL_NOSAUKUMS']);
          $oFormWorkTab->addElement('label', 'standart['.$i.']', '', $actWork['DRBI_KKAL_NORMATIVS']);
          $oFormWorkTab->addElement('label', 'measure['.$i.']', '', $actWork['DRBI_MERVIENIBA']);   
          if ($oFormWorkTab -> isFormSubmitted()){
            $oFormWorkTab->setNewValue('chipher['.$i.']',$actWork['DRBI_KKAL_SHIFRS']);
            $oFormWorkTab->setNewValue('title['.$i.']',$actWork['DRBI_KKAL_NOSAUKUMS']);
            $oFormWorkTab->setNewValue('standart['.$i.']',$actWork['DRBI_KKAL_NORMATIVS']);
            $oFormWorkTab->setNewValue('measure['.$i.']',$actWork['DRBI_MERVIENIBA']);        
          }

          $actWork['DRBI_DAUDZUMS'] = number_format($actWork['DRBI_DAUDZUMS'], 3, '.', '');         


          if($tameWork || $oFormWorkTab->getValue('tame') == 1){
              
              $actWork['DRBI_DAUDZUMS_KOR'] = number_format($actWork['DRBI_DAUDZUMS_KOR'], 3, '.', '');
              $oFormWorkTab->addElement('label', 'amount_k['.$i.']', '', $actWork['DRBI_DAUDZUMS']);  
              
              if(empty($actWork['DRBI_APPROVE_DATE']) ) {
                $oFormWorkTab->setNewValue('amount_k['.$i.']', $actWork['DRBI_DAUDZUMS']); 
                $oFormWorkTab->addElement('text', 'amount_kor['.$i.']', '', $actWork['DRBI_DAUDZUMS_KOR'], (($isReadonly)?' disabled ':'').'maxlength="9"');

                $oFormWorkTab -> addRule('amount_kor['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
                $oFormWorkTab -> addRule('amount_kor['.$i.']', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);
                // check Amaunt field
                $v1=&$oFormWorkTab->createValidation('amauntKOrValidation_'.$i, array('amount_kor['.$i.']'), 'ifonefilled');
                // ja Cilvï¿½kstundas normatï¿½vs ir definï¿½ts un > 100000
                $r1=&$oFormWorkTab->createRule(array('amount_kor['.$i.']', 'maxAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','<');
                // ja koeficent ir definï¿½ts un < 0
                $r2=&$oFormWorkTab->createRule(array('amount_kor['.$i.']', 'minAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','>');
                $oFormWorkTab->addRule(array($r1, $r2), 'groupRuleAmauntKor_'.$i, 'group', $v1);
              }
              else {
                $oFormWorkTab->addElement('label', 'amount_kor['.$i.']', '', $actWork['DRBI_DAUDZUMS_KOR']);                 
              }
              if ($oFormWorkTab -> isFormSubmitted()){
                $oFormWorkTab->setNewValue('amount_kor['.$i.']', $actWork['DRBI_DAUDZUMS_KOR']);
              }
              
          } else {
            if( empty($actWork['DRBI_APPROVE_DATE'])  ) {
                $oFormWorkTab->addElement('text', 'amount['.$i.']', '', $actWork['DRBI_DAUDZUMS'], (($isReadonly)?' disabled ':'').'maxlength="9"');
                $oFormWorkTab -> addRule('amount['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
                $oFormWorkTab -> addRule('amount['.$i.']', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);
                // check Amaunt field
                $v1=&$oFormWorkTab->createValidation('amauntValidation_'.$i, array('amount['.$i.']'), 'ifonefilled');
                // ja Cilvï¿½kstundas normatï¿½vs ir definï¿½ts un > 100000
                $r1=&$oFormWorkTab->createRule(array('amount['.$i.']', 'maxAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','<');
                // ja koeficent ir definï¿½ts un < 0
                $r2=&$oFormWorkTab->createRule(array('amount['.$i.']', 'minAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','>');
                $oFormWorkTab->addRule(array($r1, $r2), 'groupRuleAmaunt_'.$i, 'group', $v1);

                //datums
                $oFormWorkTab -> addElement('date', 'plan_date['.$i.']',  '', $actWork['DRBI_PLAN_DATE'], (($isReadonly)?' disabled ':''));
                $oFormWorkTab -> addRule('plan_date['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
                $oFormWorkTab -> addRule('plan_date['.$i.']', text::get('ERROR_INCORRECT_DATE'),'validatedate');
            } 
            else {
                $oFormWorkTab->addElement('label', 'amount['.$i.']', '', $actWork['DRBI_DAUDZUMS']); 
                $oFormWorkTab->addElement('label', 'plan_date['.$i.']', '', $actWork['DRBI_PLAN_DATE']);                
                
            }
            if ($oFormWorkTab -> isFormSubmitted()){
              $oFormWorkTab->setNewValue('amount['.$i.']', $actWork['DRBI_DAUDZUMS']);
              $oFormWorkTab->setNewValue('plan_date['.$i.']', $actWork['DRBI_PLAN_DATE']); 
            }
          }
          

          $oFormWorkTab->addElement('label', 'total['.$i.']', '', $actWork['DRBI_CILVEKSTUNDAS'], ' disabled maxlength="10"');

          $totalTime[$d] = number_format($actWork['DRBI_DAY_TOTAL'], 2, '.', '');

          
        
          // delete button
          if( empty($aWorks[$i]['DRBI_APPROVE_DATE']) || $tameWork  ) {
            // ajax handler link for delete
            $delLink = new urlQuery();
            $delLink->addPrm(FORM_ID, 'f.akt.s.2');
            $delLink->addPrm(DONT_USE_GLB_TPL, '1');
            $delLink->addPrm('tame', $tameWork ?'1':'0');
            $delLink->addPrm('isTrase', $trase );
            $delLink->addPrm('xmlHttp', '1');

            $delButtonJs = "if(isDelete()) { 
                var rowId = document.forms['frmWorkTab".(($tameWork ) ? 'T' : '')."']['id[" .$i. "]'];
                eval(xmlHttpGetValue('" .$delLink -> getQuery() ."&deleteId='+rowId.value));
              }";
          
              $oFormWorkTab->addElement('button', 'work_del['.$i.']', '', '', 'onclick="' . $delButtonJs . ';return false;" style="background: url(img/ico_del.gif); cursor:hand; border:0px; width: 20px; height: 20px;" title="' . text::get('DELETE') . '"');
              unset($delLink);
          }
          $i++;
          
        }
        
      }
      // form buttons
      if (!$isReadonly)
      {
        $oFormWorkTab->addElement('link', 'tameLink', $tameGroup['TITLE'], '#', 'onClick="'.$tameGroup['URL'].'"', '');
        foreach ($calcGroups as $i => $group)
        {
           $oFormWorkTab->addElement('link', 'group['.$i.']', $group['TITLE'], '#', 'onClick="'.$group['URL'].'"', '');
        }
        $oFormWorkTab -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_save_work.gif', 'width="120" height="20" ');
        //$oFormWorkTab -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"');
      }

      // if form iz submit (save button was pressed)
      if ($oFormWorkTab -> isFormSubmitted()&& $isNew === false)
      { 
		if($oFormWorkTab ->isValid()  && $isRowValid)
		{ 
      
		   $r=dbProc::deleteActWorks($actId, $tameWork);
		   if ($r === false)
		   {
		   	$oFormWorkTab->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
		   }
		   else
		   {
		        if(isset($aValidRows) && is_array($aValidRows))
            		{
              
                  		foreach($aValidRows as $i => $row)
                  		{
                    
                      			//if(!empty($row['edited'])) continue;
                      
                      			$r=dbProc::writeActWork($actId,
                                                    $row['kid'],
                                                    $row['chipher'],
                                                    $row['title'],
                                                    $row['standart'],
                                                    $row['amount'],
                                                    $row['total'],
                                                    $row['measure'],
                                                    ($tameWork) ? $row['amount_kor']:false,
                                                    $row['edited'],
                                                    ($tameWork) ? false : $row['plan_date'],
                                                    $row['day_total']
                                                    );
                            		// if work not inserted in to the DB
                      			// delete  task record and show error message
                      			if($r === false)
                      			{
                        			//dbProc::deleteActWorks($actId, $tameWork);
                        			$oFormWorkTab->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                        			break;
                      			}
                      			else
                      			{
                           			$Id=dbLayer::getInsertId();
                           			$oFormWorkTab -> setNewValue('id['.$row['rowNum'].']', $Id);
                           			$oFormWorkTab -> setNewValue('total['.$row['rowNum'].']', $row['total']);
                           			$oFormWorkTab->addSuccess(text::get('RECORD_WAS_SAVED'));
                           
                           			$oLink=new urlQuery();
                		       		  $oLink->addPrm(FORM_ID, 'f.akt.s.1');
                		       		  $oLink->addPrm('actId', $actId);
                          			$oLink->addPrm('tab', TAB_WORKS.(($tameWork==1) ? '_T' : ''));
                           			$oLink->addPrm('isNew', RequestHandler::getMicroTime());
                           			$oLink->addPrm('successMessageTab', text::get('RECORD_WAS_SAVED'));
                           			$oLink->addPrm('isTrase', $trase );
               		   			//RequestHandler::makeRedirect($oLink->getQuery());
                      			}
                    	}
                    	//pie saglabâðanas fonâ pârrçíina kopsummas un materiâlu apjomus
                    	dbProc::updateWorkSumms($actId, $tameWork);
	
			if($tameWork == 1) {
                            // iztirit matçriâla tame
                            dbProc::deleteAutoActMaterial($actId);
			    // pârrçíinat materiâla tame
			    dbProc::processAutoActMaterial($actId, $kvikstep, $trase);			    
		      	}
                   	
			// ìenerçta akta laboðanas gadîjumâ summas katru reizi tiek pârsûtîtas uz kvikstepu.
			dbProc::sentDataToKvikStep($actId, $kvikstep, $trase);
                    	// saglaba lietotaja darbiibu
                    	dbProc::setUserActionDate($userId, ACT_UPDATE);

                    if($trase == 1) {
		      
                      $aWorkSums = dbProc::getActWorkSumms($actId, $tameWork);
                      foreach ($aWorkSums as $d => $aSum)
                      {
                        
                            $oFormWorkTab->setNewValue('sum_m3', 'M3', $aSum['m3']);
                            $oFormWorkTab->setNewValue('sum_ha', 'HA', $aSum['ha']);
                            $oFormWorkTab->setNewValue('sum_km', 'KM', $aSum['km']);
                            $oFormWorkTab->setNewValue('sum_gab', 'GAB', $aSum['gab']);
                            //break;
                      }
		      
		    }

                    $tameWork = 0;
                }
             }
          }
      }
       $oFormWorkTab -> makeHtml();
       include('f.akt.s.2.tpl');
    }



}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>