<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isProjector = dbProc::isExistsUserRoleWithProject($userId) ;
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);

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
	   	   dbProc::deleteActWorkRecord(reqVar::get('deleteId'));
       ?>
	    rowNode = this.parentNode.parentNode;
		  rowNode.parentNode.removeChild(rowNode);
	<?
    }
    exit();
}


// tikai  sist?mas lietotajam vai administr?toram ir pieeja!
if ( $isAdmin || $isProjector || $isEconomist)
{
    if($actId !== false )
    {
      $oLink=new urlQuery();
      $oLink->addPrm(FORM_ID, 'f.akt.s.20');
      $oLink->addPrm('actId', $actId);
      $oLink->addPrm('tab', TAB_WORKS);
      $oLink->addPrm('isSearch', $isSearch);
      $oLink->addPrm('searchNum', $searchNum);
      $oFormWorkTab = new Form('frmWorkTab', 'post', $oLink->getQuery() . '#tab');

      unset($oLink);

      // if operation is success, show success message and redirect top frame
      if (reqVar::get('successMessageTab') && $isNew === false)
      {
      	$oFormWorkTab->addSuccess(reqVar::get('successMessageTab'));

      }

      $isReadonly   = true;
      // Ir pieejams main��anai, ja  AKTS:LIETOT�JS = �Teko�ais lietot�js� un lietot�ja loma ir �Ievad�tais� un AKTS:STATUS = �Izveide� vai �Atgriezts� vai �T�me�.
      if(($act['RAKT_RLTT_ID'] == $userId && $isProjector || $isAdmin) && ($status == STAT_INSERT || $status == STAT_RETURN ) )
      {
        $isReadonly   = false;
      }
      

      //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.23');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('catalog',KL_CALCULALATION);      

      $calcGroups=array();
      $j = 0;

      $calcGroups[$j]['TITLE'] = text::get('ST_WORK');
      $calcGroups[$j]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery(), false, 500, 500, true, false, true);

      unset($oPopLink);
      unset($res);

      $aWorks = array();
      if ($oFormWorkTab -> isFormSubmitted() && $isNew === false)
      {
          $isRowValid = true;
          $aKids =  $oFormWorkTab->getValue('kid');
          if(is_array($aKids) )
          {
            $total = 0;
            foreach ($aKids as $i => $val)
            {
                if($oFormWorkTab->getValue('chipher['.$i.']') == '') continue;

                 $aWorks[$i]['DRBI_ID'] = $oFormWorkTab->getValue('id['.$i.']');
                 $aWorks[$i]['DRBI_KKAL_ID'] = $oFormWorkTab->getValue('kid['.$i.']');
                 $aWorks[$i]['DRBI_KKAL_SHIFRS'] = $oFormWorkTab->getValue('chipher['.$i.']');
                 $aWorks[$i]['DRBI_KKAL_NOSAUKUMS'] = $oFormWorkTab->getValue('title['.$i.']');
                 $aWorks[$i]['DRBI_DAUDZUMS'] = $oFormWorkTab->getValue('amount['.$i.']');
                 $aWorks[$i]['DRBI_MERVIENIBA'] = $oFormWorkTab->getValue('measure['.$i.']');
                 $aWorks[$i]['KKAL_APRAKSTS'] = $oFormWorkTab->getValue('description['.$i.']');
                 $aWorks[$i]['DRBI_PIEZIMES'] = $oFormWorkTab->getValue('notes['.$i.']');
                 
                 // validate work progress value
                if (empty($aWorks[$i]['DRBI_DAUDZUMS']))
                {
                  // assign error message
                  $oFormWorkTab->addErrorPerElem('amount['.$i.']', text::get('ERROR_REQUIRED_FIELD'));
                  $isRowValid = false;
                }
                        // validate work progress value
                elseif (!is_numeric($aWorks[$i]['DRBI_DAUDZUMS']))
                {
                  // assign error message
                  $oFormWorkTab->addErrorPerElem('amount['.$i.']', text::get('ERROR_DOUBLE_VALUE'));
                  $isRowValid = false;
                }
                        // validate work progress value
                elseif ($aWorks[$i]['DRBI_DAUDZUMS'] >= 100000)
                {
                  // assign error message
                  $oFormWorkTab->addErrorPerElem('amount['.$i.']', text::get('ERROR_AMOUNT_VALUE_100000'));
                  $isRowValid = false;
                }
                  // prepare database record data
  			          $aValidRows[] = array(
                    'kid' => $aWorks[$i]['DRBI_KKAL_ID'],
                    'chipher' => $aWorks[$i]['DRBI_KKAL_SHIFRS'],
                    'title' => $aWorks[$i]['DRBI_KKAL_NOSAUKUMS'],
                    'amount' => $aWorks[$i]['DRBI_DAUDZUMS'],
                    'measure' => $aWorks[$i]['DRBI_MERVIENIBA'],
                    'description' => $aWorks[$i]['KKAL_APRAKSTS'],
                    'notes' => $aWorks[$i]['DRBI_PIEZIMES'],
                    'rowNum' => $i
  			          );
                }
           }
      }
      else
      {
        //Ja eksistee akta darbi, tad nolasaam taas darbus no datu baazes
  	    $aWorkDb=dbProc::getActWorkList($actId);      	

        foreach ($aWorkDb as $i => $work)
        {
           $aWorks[$i]['DRBI_ID'] = $work['DRBI_ID'];
           $aWorks[$i]['DRBI_KKAL_ID'] = $work['DRBI_KKAL_ID'];
           $aWorks[$i]['DRBI_KKAL_SHIFRS'] = $work['DRBI_KKAL_SHIFRS'];
           $aWorks[$i]['DRBI_KKAL_NOSAUKUMS'] = $work['DRBI_KKAL_NOSAUKUMS'];
           $aWorks[$i]['DRBI_DAUDZUMS'] = $work['DRBI_DAUDZUMS'];
           $aWorks[$i]['DRBI_MERVIENIBA'] = $work['DRBI_MERVIENIBA'];
           $aWorks[$i]['KKAL_APRAKSTS'] = str_replace('"', '`', $work['KKAL_APRAKSTS']);
           $aWorks[$i]['DRBI_PIEZIMES'] = $work['DRBI_PIEZIMES'];
          
        }
      }
      $oFormWorkTab -> addElement('hidden', 'isSearch', '', $isSearch);
      $oFormWorkTab -> addElement('hidden', 'searchNum', '', $searchNum);
      $oFormWorkTab->addElement('hidden','actId','',$actId);      
      $oFormWorkTab->addElement('hidden','maxAmaunt','','100000.00');
      $oFormWorkTab->addElement('hidden','minAmaunt','','0.00');     

      $totalTime = 0;
      // form elements
      foreach ($aWorks as $i => $actWork)
      {

        $oFormWorkTab->addElement('hidden', 'id['.$i.']', '', $actWork['DRBI_ID']);
        $oFormWorkTab->addElement('hidden', 'description['.$i.']', '', $actWork['KKAL_APRAKSTS']);
        $oFormWorkTab->addElement('hidden', 'kid['.$i.']', '', $actWork['DRBI_KKAL_ID']);
        $oFormWorkTab->addElement('label', 'chipher['.$i.']', '', $actWork['DRBI_KKAL_SHIFRS']);
        $oFormWorkTab->addElement('label', 'title['.$i.']', '', $actWork['DRBI_KKAL_NOSAUKUMS']);
        $oFormWorkTab->addElement('label', 'measure['.$i.']', '', $actWork['DRBI_MERVIENIBA']);
        
        $oFormWorkTab->addElement('text', 'amount['.$i.']', '', $actWork['DRBI_DAUDZUMS'], (($isReadonly)?' disabled ':'').'maxlength="9"');
        
        if(!empty($actWork['DRBI_KKAL_SHIFRS']))
        {
            
                $oFormWorkTab -> addRule('amount['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
                $oFormWorkTab -> addRule('amount['.$i.']', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);
                // check Amaunt field
                $v1=&$oFormWorkTab->createValidation('amauntValidation_'.$i, array('amount['.$i.']'), 'ifonefilled');
                // ja Cilv?kstundas normat?vs ir defin?ts un > 100000
                $r1=&$oFormWorkTab->createRule(array('amount['.$i.']', 'maxAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','<');
                // ja koeficent ir defin?ts un < 0
                $r2=&$oFormWorkTab->createRule(array('amount['.$i.']', 'minAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','>');
                $oFormWorkTab->addRule(array($r1, $r2), 'groupRuleAmaunt_'.$i, 'group', $v1);
            
        }       
        $oFormWorkTab->addElement('text', 'notes['.$i.']', '', $actWork['DRBI_PIEZIMES'], (($isReadonly)?' disabled ':'').'maxlength="250"');
        

        // ajax handler link for delete
        $delLink = new urlQuery();
        $delLink->addPrm(FORM_ID, 'f.akt.s.21');        
        $delLink->addPrm(DONT_USE_GLB_TPL, '1');
        $delLink->addPrm('xmlHttp', '1');
        // delete button
        $delButtonJs = "if(isDelete()) { 
							var rowId = document.forms['frmWorkTab']['id[" .$i. "]'];
							eval(xmlHttpGetValue('" .$delLink -> getQuery() ."&deleteId='+rowId.value));
						}";

		    $oFormWorkTab->addElement('button', 'work_del['.$i.']', '', '', 'onclick="' . $delButtonJs . ';return false;" style="background: url(img/ico_del.gif); cursor:hand; border:0px; width: 20px; height: 20px;" title="' . text::get('DELETE') . '"');
        unset($delLink);
      }
      $totalTime = number_format($totalTime, 2, '.', '');
      // form buttons
      if (!$isReadonly)
      {
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
		   $r=dbProc::deleteActWorks($actId);

		   if ($r === false)
		   {
		   	$oFormWorkTab->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
		   }
		   else
		   {
		        if(is_array($aValidRows))
                {
        	    	foreach($aValidRows as $i => $row)
                {
                    if($row['chipher'] == '') continue;
                            $r=dbProc::writeActWork($actId,
                                                    $row['kid'],
                                                    $row['chipher'],
                                                    $row['title'],
                                                    false,
                                                    $row['amount'],
                                                    false,
                                                    $row['measure'],
                                                    false,
                                                    false,
                                                    false,
                                                    false,
                                                    $row['notes']
                                                    );
                            // if work not inserted in to the DB
                        // delete  task record and show error message
                        if($r === false)
                        {
                            dbProc::deleteActWorks($actId);
                            $oFormWorkTab->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                              break;
                        }
                         else
                         {
                            $Id=dbLayer::getInsertId();
                            $oFormWorkTab -> setNewValue('id['.$row['rowNum'].']', $Id);
                            
                            $oFormWorkTab->addSuccess(text::get('RECORD_WAS_SAVED'));
                            
                            $oLink=new urlQuery();
                            $oLink->addPrm(FORM_ID, 'f.akt.s.20');
                            $oLink->addPrm('actId', $actId);                          
                            $oLink->addPrm('tab', TAB_WORKS);
                            $oLink->addPrm('isNew', RequestHandler::getMicroTime());
                            $oLink->addPrm('successMessageTab', text::get('RECORD_WAS_SAVED'));
                            //RequestHandler::makeRedirect($oLink->getQuery());
                         }
                    }
                    // saglaba lietotaja darbiibu
                    dbProc::setUserActionDate($userId, ACT_UPDATE);

                }
           }
        }
      }
       $oFormWorkTab -> makeHtml();
       include('f.akt.s.21.tpl');
    }



}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>