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
	   dbProc::deleteActTransportRecord(reqVar::get('deleteId'));
       ?>
	    rowNode = this.parentNode.parentNode;
		rowNode.parentNode.removeChild(rowNode);
		<?
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
      $oLink->addPrm('tab', TAB_TRANSPORT);
      $oFormTransportTab = new Form('frmTransportTab','post',$oLink->getQuery().'#tab');
      unset($oLink);

      // if operation is success, show success message and redirect top frame
      if (reqVar::get('successMessageTab') && $isNew === false)
      {
      	$oFormTransportTab->addSuccess(reqVar::get('successMessageTab'));
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
      $oPopLink->addPrm('catalog',KL_TRANSPORT);
      $oPopLink->addPrm('isSearch', $isSearch);
      $oPopLink->addPrm('searchNum', $searchNum);

      // get favorit
      $favorit=array();
      $krfk = dbProc::getKrfkInfo(KRFK_TRANSPORT_ID);
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
       $next =  count($region);
       $region[$next]['TITLE'] = text::get('TRANSPORT_DEPARTMENT');   ;
       $region[$next]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery().'&region='.text::get('TRANSPORT_DEPARTMENT'));
       unset($res);
       unset($oPopLink);

      $aTransports = array();
      if ($oFormTransportTab -> isFormSubmitted() && $isNew === false)
      {
          $isRowValid = true;
          $aCodes =  $oFormTransportTab->getValue('code');
          if(is_array($aCodes) )
          {
            foreach ($aCodes as $i => $val)
            {
                 $aTransports[$i]['TRNS_ID'] = $oFormTransportTab->getValue('id['.$i.']');
                 $aTransports[$i]['TRNS_VALSTS_NUMURS'] = $oFormTransportTab->getValue('code['.$i.']');
                 $aTransports[$i]['TRNS_GRUPAS_NOSAUKUMS'] = $oFormTransportTab->getValue('group['.$i.']');
                 $aTransports[$i]['TRNS_APAKSGRUPAS_KODS'] = $oFormTransportTab->getValue('apGroupCode['.$i.']');
                 $aTransports[$i]['TRNS_APAKSGRUPAS_NOSAUKUMS'] = $oFormTransportTab->getValue('apGroup['.$i.']');
                 $aTransports[$i]['TRNS_PIEDERIBA'] = $oFormTransportTab->getValue('ouner['.$i.']');
                 $aTransports[$i]['TRNS_KM'] = $oFormTransportTab->getValue('km['.$i.']');
                 $aTransports[$i]['TRNS_STUNDAS'] = $oFormTransportTab->getValue('stundas['.$i.']');
                 $aTransports[$i]['TRNS_DARBA_STUNDAS'] = $oFormTransportTab->getValue('total2['.$i.']');

                // validate km
  			   if (!empty($aTransports[$i]['TRNS_KM']) && !is_numeric($aTransports[$i]['TRNS_KM']))
  			   {
  					// assign error message
  					$oFormTransportTab->addErrorPerElem('km['.$i.']', text::get('ERROR_NUMERIC_VALUE'));
  					$isRowValid = false;
  			   }
               // validate stundas
  			   if (!empty($aTransports[$i]['TRNS_STUNDAS']) && !is_numeric($aTransports[$i]['TRNS_STUNDAS']))
  			   {
  					// assign error message
  					$oFormTransportTab->addErrorPerElem('stundas['.$i.']', text::get('ERROR_DOUBLE_VALUE'));
  					$isRowValid = false;
  			   }
               // validate darba stundas
  			    if (empty($aTransports[$i]['TRNS_DARBA_STUNDAS']))
  				{
  					// assign error message
  					$oFormTransportTab->addErrorPerElem('total2['.$i.']', text::get('ERROR_REQUIRED_FIELD'));
  					$isRowValid = false;
  				}
                  // validate work progress value
  			   elseif (!is_numeric($aTransports[$i]['TRNS_DARBA_STUNDAS']))
  				{
  					// assign error message
  					$oFormTransportTab->addErrorPerElem('total2['.$i.']', text::get('ERROR_DOUBLE_VALUE'));
  					$isRowValid = false;
  				}
                  // validate work progress value
  			   elseif ($aTransports[$i]['TRNS_DARBA_STUNDAS'] >= 1000)
  				{
  					// assign error message
  					$oFormTransportTab->addErrorPerElem('total2['.$i.']', text::get('ERROR_AMOUNT_VALUE'));
  					$isRowValid = false;
  				}


                  // prepare database record data
  			    $aValidRows[] = array(
      				'code' => $aTransports[$i]['TRNS_VALSTS_NUMURS'],
      				'group' => $aTransports[$i]['TRNS_GRUPAS_NOSAUKUMS'],
      				'apGroupCode' => $aTransports[$i]['TRNS_APAKSGRUPAS_KODS'],
                    'apGroup' => $aTransports[$i]['TRNS_APAKSGRUPAS_NOSAUKUMS'],
      				'ouner' => $aTransports[$i]['TRNS_PIEDERIBA'],
                    'km' => $aTransports[$i]['TRNS_KM'],
                    'stundas' => $aTransports[$i]['TRNS_STUNDAS'],
      				'total2' => $aTransports[$i]['TRNS_DARBA_STUNDAS'],
                    'rowNum' => $i
  			    );
             }
           }
      }
      else
      {
        //Ja eksistee akta materiāli, tad nolasaam taas darbus no datu baazes
  	    $aTransportDb=dbProc::getActTransportList($actId);

        foreach ($aTransportDb as $i => $transport)
        {
           $aTransports[$i]['TRNS_ID'] = $transport['TRNS_ID'];
           $aTransports[$i]['TRNS_VALSTS_NUMURS'] = $transport['TRNS_VALSTS_NUMURS'];
           $aTransports[$i]['TRNS_GRUPAS_NOSAUKUMS'] = $transport['TRNS_GRUPAS_NOSAUKUMS'];
           $aTransports[$i]['TRNS_APAKSGRUPAS_KODS'] = $transport['TRNS_APAKSGRUPAS_KODS'];
           $aTransports[$i]['TRNS_APAKSGRUPAS_NOSAUKUMS'] = $transport['TRNS_APAKSGRUPAS_NOSAUKUMS'];
           $aTransports[$i]['TRNS_PIEDERIBA'] = $transport['TRNS_PIEDERIBA'];
           $aTransports[$i]['TRNS_KM'] = $transport['TRNS_KM'];
           $aTransports[$i]['TRNS_STUNDAS'] = $transport['TRNS_STUNDAS'];
           $aTransports[$i]['TRNS_DARBA_STUNDAS'] = $transport['TRNS_DARBA_STUNDAS'];
        }
      }
      $oFormTransportTab -> addElement('hidden', 'isSearch', '', $isSearch);
      $oFormTransportTab -> addElement('hidden', 'searchNum', '', $searchNum);
      $oFormTransportTab->addElement('hidden','actId','',$actId);
      $oFormTransportTab->addElement('hidden','maxAmaunt','','1000.00');
      $oFormTransportTab->addElement('hidden','minAmaunt','','0.00');

      $totalKm = 0;
      $totalTime = 0;
      $totalWorkTime = 0;
      // form elements
      foreach ($aTransports as $i => $actTransport)
      {
        $oFormTransportTab->addElement('hidden', 'id['.$i.']', '', $actTransport['TRNS_ID']);
        $oFormTransportTab->addElement('label', 'code['.$i.']', '', $actTransport['TRNS_VALSTS_NUMURS']);
        $oFormTransportTab->addElement('label', 'group['.$i.']', '', $actTransport['TRNS_GRUPAS_NOSAUKUMS']);
        $oFormTransportTab->addElement('hidden', 'apGroupCode['.$i.']', '', $actTransport['TRNS_APAKSGRUPAS_KODS']);
        $oFormTransportTab->addElement('label', 'apGroup['.$i.']', '', $actTransport['TRNS_APAKSGRUPAS_NOSAUKUMS']);
        $oFormTransportTab->addElement('hidden', 'ouner['.$i.']', '', $actTransport['TRNS_PIEDERIBA']);

        $oFormTransportTab->addElement('text', 'km['.$i.']', '', $actTransport['TRNS_KM'], (($isReadonly)?' disabled ':'').'maxlength="4"');
        $oFormTransportTab -> addRule('km['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oFormTransportTab -> addRule('km['.$i.']', text::get('ERROR_NUMERIC_VALUE'), 'numeric');

        $oFormTransportTab->addElement('text', 'stundas['.$i.']', '', $actTransport['TRNS_STUNDAS'], (($isReadonly)?' disabled ':'').'maxlength="6"');
        $oFormTransportTab -> addRule('stundas['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oFormTransportTab -> addRule('stundas['.$i.']', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);
        // check Amaunt field
        $v1=&$oFormTransportTab->createValidation('stundasValidation_'.$i, array('stundas['.$i.']'), 'ifonefilled');
        // ja Amount ir definēts un > 1000
        $r1=&$oFormTransportTab->createRule(array('stundas['.$i.']', 'maxAmaunt'), text::get('ERROR_AMOUNT_VALUE'), 'comparedouble','<');
        $oFormTransportTab->addRule(array($r1), 'groupRuleStundas_'.$i, 'group', $v1);

        $oFormTransportTab->addElement('text', 'total2['.$i.']', '', $actTransport['TRNS_DARBA_STUNDAS'], (($isReadonly)?' disabled ':'').'maxlength="6"');
        $oFormTransportTab -> addRule('total2['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oFormTransportTab -> addRule('total2['.$i.']', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);
        // check Amaunt field
        $v2=&$oFormTransportTab->createValidation('total2Validation_'.$i, array('total2['.$i.']'), 'ifonefilled');
        // ja Amount ir definēts un > 1000
        $r1=&$oFormTransportTab->createRule(array('total2['.$i.']', 'maxAmaunt'), text::get('ERROR_AMOUNT_VALUE'), 'comparedouble','<');
        // ja Amount ir definēts un < 0
        $r2=&$oFormTransportTab->createRule(array('total2['.$i.']', 'minAmaunt'), text::get('ERROR_AMOUNT_VALUE'), 'comparedouble','>');
        $oFormTransportTab->addRule(array($r1, $r2), 'groupRuleTotal2_'.$i, 'group', $v2);

        $totalKm += $actTransport['TRNS_KM'];
        $totalTime += $actTransport['TRNS_STUNDAS'];
        $totalWorkTime += $actTransport['TRNS_DARBA_STUNDAS'];

        // ajax handler link for delete
	    $delLink = new urlQuery();
	    $delLink->addPrm(FORM_ID, 'f.akt.s.4');
	    $delLink->addPrm(DONT_USE_GLB_TPL, '1');
        $delLink->addPrm('xmlHttp', '1');
	   	// delete button
        $delButtonJs = "if(isDelete()) {
							var index=" . $i . ";
							var rowId = document.forms['frmTransportTab']['id['+index+']'];
							rowId = rowId ? rowId.value : '';
							eval(xmlHttpGetValue('" .$delLink -> getQuery() ."&deleteId='+rowId));
						}";
		$oFormTransportTab->addElement('button', 'trans_del['.$i.']', '', '', 'onclick="' . $delButtonJs . ';return false;" style="background: url(img/ico_del.gif); cursor:hand; border:0px; width: 20px; height: 20px;" title="' . text::get('DELETE') . '"');
        unset($delLink);
      }

      $totalKm = number_format($totalKm, 2, '.', '');
      $totalTime = number_format($totalTime, 2, '.', '');
      $totalWorkTime = number_format($totalWorkTime, 2, '.', '');

      // form buttons
      if (!$isReadonly)
      {
        foreach ($favorit as $i => $group)
        {
           $oFormTransportTab->addElement('link', 'favorit['.$i.']', $group['TITLE'], '#', 'onClick="'.$group['URL'].'"', '');
        }
        foreach ($region as $i => $r)
        {
           $oFormTransportTab->addElement('link', 'region['.$i.']', $r['TITLE'], '#', 'onClick="'.$r['URL'].'"', '');
        }
        $oFormTransportTab -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_save_transport.gif', 'width="120" height="20" ');
        //$oFormTransportTab -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"');
      }

      // if form iz submit (save button was pressed)
	  if ($oFormTransportTab -> isFormSubmitted()&& $isNew === false)
	  {
		if($oFormTransportTab ->isValid() && $isRowValid)
		{
		   $r=dbProc::deleteActTransports($actId);
		   if ($r === false)
		   {
		   	$oFormTransportTab->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
		   }
		   else
		   {
		        if(is_array($aValidRows))
                {
        	    	foreach($aValidRows as $i => $row)
        			{
                         $r=dbProc::writeActTransport($actId,
                                                $row['code'],
                                                $row['group'],
                                                $row['apGroupCode'],
                                                $row['apGroup'],
                                                $row['ouner'],
                                                $row['km'],
                                                $row['stundas'],
                                                $row['total2']);
                         // if work not inserted in to the DB
    					 // delete  task record and show error message
    					 if($r === false)
    					 {
    					 	dbProc::deleteActTransports($actId);
    					 	$oFormTransportTab->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
    				        break;
    					 }
                         else
                         {
                           $Id=dbLayer::getInsertId();
                           $oFormTransportTab -> setNewValue('id['.$row['rowNum'].']', $Id);
                           $oFormTransportTab->addSuccess(text::get('RECORD_WAS_SAVED'));

                         }
                    }
                    // saglaba lietotaja darbiibu
                    dbProc::setUserActionDate($userId, ACT_UPDATE);
                }
           }
        }
      }
       $oFormTransportTab -> makeHtml();
       include('f.akt.s.4.tpl');
    }



}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>