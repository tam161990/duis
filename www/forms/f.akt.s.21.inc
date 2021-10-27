<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isProjector = dbProc::isExistsUserRoleWithProject($userId) ;
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);
$projectApprover = dbProc::isUserInRole($userId, ROLE_PROJ_APPROVER);
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
	    document.all['frmWorkTab'].submit();      
	<?
    }

    // if operation is SAVE , save daudzumu in DB
    if (reqVar::get('saveId')!='' )
	  {
      if (reqVar::get('amount')!='')
      {
        dbProc::updateWorkDaudzums(reqVar::get('saveId'), reqVar::get('amount'));
      }
	    if (reqVar::get('notes')!='')
      {
        $note = ((reqVar::get('notes') == 'D') ? '' : reqVar::get('notes'));
        dbProc::updateWorkComment(reqVar::get('saveId'), $note);
      }
      if (reqVar::get('work_type_text')!='')
      {
        dbProc::updateWorkTypeText(reqVar::get('saveId'), reqVar::get('work_type_text'));
      }
      if (reqVar::get('work_type')!='')
      {
        dbProc::updateWorkType(reqVar::get('saveId'), reqVar::get('work_type'));
      }
    }

    // masveida dzešana
    if (reqVar::get('issue') && reqVar::get('op'))
    {
      ob_clean();
      $o = reqVar::get('op');
      $a = reqVar::get('issue');
      if (isset($o) && $o == OP_INSERT)
      {
      	session::set('DRBI_FOR_DELETE_'.$a,$a);
      }
      else
      {
         session::del('DRBI_FOR_DELETE_'.$a);
      }
    }
    exit();
}


// tikai  sist?mas lietotajam vai administr?toram ir pieeja!
if ( $isAdmin || $isProjector ||  $projectApprover)
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

      $oLink=new urlQuery();
      $oLink->addPrm(FORM_ID, 'f.akt.s.21');
      $oLink->addPrm(DONT_USE_GLB_TPL, '1');
      $oLink->addPrm('xmlHttp', '1');
      $searchLink = $oLink -> getQuery();
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
      $oPopLink->addPrm('st',1);
      $oPopLink->addPrm('catalog',KL_CALCULALATION);      

      $calcGroups=array();
      $j = 0;

      $calcGroups[$j]['TITLE'] = text::get('ST_WORK');
      $calcGroups[$j]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery(), false, 500, 500, true, false, true);

      unset($oPopLink);
      $j ++;
      //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.13');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('catalog',KL_CALCULALATION);
      $oPopLink->addPrm('isSearch', $isSearch);
      $oPopLink->addPrm('searchNum', $searchNum);
      $oPopLink->addPrm('isProject',1);
      $oPopLink->addPrm('st',0);
      $calcGroups[$j]['TITLE'] = text::get('SEARCH_NEW');   ;
      $calcGroups[$j]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery(), false, 500, 500, true, false, true);
      unset($oPopLink);
      $j ++;
      //Popup import no cita projekta
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.24');
      $oPopLink->addPrm('actId',$actId);
 
      $calcGroups[$j]['TITLE'] = text::get('IMPORT_NO_PROJECT');
      $calcGroups[$j]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery(), false, 500, 500, true, false, true);
 
       unset($oPopLink);
       unset($res);

      // get grupas list
      $workType=array();
      $workType['']=text::get('EMPTY_SELECT_OPTION');		
      $res=dbProc::getWorkTypeList();
      if (is_array($res))
      {
        foreach ($res as $row)
        {
          $workType[$row['KLDV_ID']]=$row['KLDV_NOSAUKUMS'];
        }
      }
      unset($res);
      
      $type=array();
      $type_code = array();
      $res = dbProc::getKrfkName('PROJECT_EXPORT');
      $type['']=text::get('EMPTY_SELECT_OPTION');		
      if (is_array($res))
      {
            foreach ($res as $row)
            {
                $type[$row['nosaukums']]=$row['nozime'];
                $type_code[] = $row['nosaukums'];
            }
      }
      unset($res);

      $aWorks = array();
      $aWorkExist = false;

      if ($oFormWorkTab -> isFormSubmitted() && $oFormWorkTab->getValue('action_t')== OP_DELETE)  {

        // get issue array
        $issues = array();
        $r = false;
        foreach ($_SESSION as $key => $val)
        {
          if(substr($key, 0, 16) == 'DRBI_FOR_DELETE_' && !empty($val))
          {
            $issues[] = $val;            
          }
        }
        //print_r($issues);
        if(count($issues) > 0)
        {
          foreach($issues as $a)
          {
            $r = dbProc::deleteActWorkRecord($a);
            if($r !== false) {
              session::del('DRBI_FOR_DELETE_'.$a);
            }
          }          
        }
        else {
          $oFormWorkTab->addError(text::get('ERROR_NOT_CHECKED'));
        }
  
      }
     /* if ($oFormWorkTab -> isFormSubmitted() && $isNew === false)
      {
          $isRowValid = true;
          $aKids =  $oFormWorkTab->getValue('chipher');
          //print_r($aKids);
          if(is_array($aKids) )
          {
            $aWorkFr = array();
            $j = 0;
            foreach ($aKids as $i => $val)
            {
                
                 $aWorkFr[$j]['DRBI_ID'] = $oFormWorkTab->getValue('id['.$i.']');
                 $aWorkFr[$j]['DRBI_KKAL_ID'] = $oFormWorkTab->getValue('kid['.$i.']');
                 $aWorkFr[$j]['DRBI_KKAL_SHIFRS'] = $oFormWorkTab->getValue('chipher['.$i.']');
                 $aWorkFr[$j]['DRBI_KKAL_NOSAUKUMS'] = $oFormWorkTab->getValue('title['.$i.']');
                 $aWorkFr[$j]['DRBI_DAUDZUMS'] = $oFormWorkTab->getValue('amount['.$i.']');
                 $aWorkFr[$j]['DRBI_MERVIENIBA'] = $oFormWorkTab->getValue('measure['.$i.']');
                 $aWorkFr[$j]['KKAL_APRAKSTS'] = $oFormWorkTab->getValue('description['.$i.']');
                 $aWorkFr[$j]['DRBI_PIEZIMES'] = $oFormWorkTab->getValue('notes['.$i.']');
                 $aWorkFr[$j]['DRBI_IS_WORKER'] = $oFormWorkTab->getValue('st['.$i.']');
                 $aWorkFr[$j]['DRBI_WORK_TYPE_TEXT'] = $oFormWorkTab->getValue('work_type_text['.$i.']');
                 $aWorkFr[$j]['DRBI_IMPORT_NO'] = $oFormWorkTab->getValue('import_no['.$i.']');
                 
                if(($status == STAT_CLOSE && ($isAdmin ||  $projectApprover))) {
                  $isRowValid = true;
                  $aWorkFr[$j]['DRBI_WORK_TYPE_ID'] = $oFormWorkTab->getValue('work_type_id['.$i.']');                  
                  $aWorkFr[$j]['KLDV_NOSAUKUMS'] = $oFormWorkTab->getValue('work_type['.$i.']');
                  $aWorkFr[$j]['DRBI_PROJECT_EXPORT'] = $oFormWorkTab->getValue('export_type['.$i.']');
                } else {
                  $aWorkFr[$j]['DRBI_WORK_TYPE_ID'] = $oFormWorkTab->getValue('work_type['.$i.']');
                  // validate work progress value
                  if (empty($aWorkFr[$j]['DRBI_DAUDZUMS']))
                  {
                    // assign error message
                   // $oFormWorkTab->addErrorPerElem('amount['.$i.']', text::get('ERROR_REQUIRED_FIELD'));
                   // $isRowValid = false;
                  }
                          // validate work progress value
                  elseif (!is_numeric($aWorkFr[$j]['DRBI_DAUDZUMS']))
                  {
                    // assign error message
                    $oFormWorkTab->addErrorPerElem('amount['.$i.']', text::get('ERROR_DOUBLE_VALUE'));
                    $isRowValid = false;
                  }
                          // validate work progress value
                  elseif ($aWorkFr[$j]['DRBI_DAUDZUMS'] >= 100000)
                  {
                    // assign error message
                    $oFormWorkTab->addErrorPerElem('amount['.$i.']', text::get('ERROR_AMOUNT_VALUE_100000'));
                    $isRowValid = false;
                  }
                }
                  // prepare database record data
  			          $aValidRows[] = array(
                    'kid' => $aWorkFr[$j]['DRBI_KKAL_ID'],
                    'chipher' => $aWorkFr[$j]['DRBI_KKAL_SHIFRS'],
                    'title' => $aWorkFr[$j]['DRBI_KKAL_NOSAUKUMS'],
                    'amount' => $aWorkFr[$j]['DRBI_DAUDZUMS'],
                    'measure' => $aWorkFr[$j]['DRBI_MERVIENIBA'],
                    'description' => $aWorkFr[$j]['KKAL_APRAKSTS'],
                    'notes' => $aWorkFr[$j]['DRBI_PIEZIMES'],
                    'st' => $aWorkFr[$j]['DRBI_IS_WORKER'],
                    'work_type' => $aWorkFr[$j]['DRBI_WORK_TYPE_ID'],
                    'work_type_text' => $aWorkFr[$j]['DRBI_WORK_TYPE_TEXT'],    
                    'import_no' => $aWorkFr[$j]['DRBI_IMPORT_NO'],                    
                    'export_type' => ($status == STAT_CLOSE && ($isAdmin ||  $projectApprover)) ? $aWorkFr[$j]['DRBI_PROJECT_EXPORT'] : '',
                    'rowNum' => $j
                  );
                  $j++;
                }

                //print_r($aValidRows)."<hr>";
                //print_r($aWorkFr);

            foreach ($aWorkFr as $i=>$work)
            {
              $aWorks[$work['DRBI_WORK_TYPE_ID'].'^'.$work['DRBI_WORK_TYPE_TEXT']][] = $work;              
            }
           }
      }
      else
      { */
      //Ja eksistee akta darbi, tad nolasaam taas darbus no datu baazes
      $aWorkDb=dbProc::getActWorkList($actId, false, false, false, true);      	
      
      $aWorkExist = false;
      foreach ($aWorkDb as $work)
      {
        $work['DRBI_PIEZIMES'] = ($work['DRBI_PIEZIMES'] == 'NULL') ? '' : $work['DRBI_PIEZIMES'];
        $aWorks[$work['DRBI_WORK_TYPE_ID'].'^'.$work['DRBI_WORK_TYPE_TEXT']][] = $work;     
        $aWorkExist = true;     
      }

      if(!$aWorkExist) {
        $aWorks[0] = array();          
      }        
      //}
      $oFormWorkTab -> addElement('hidden', 'isSearch', '', $isSearch);
      $oFormWorkTab -> addElement('hidden', 'searchNum', '', $searchNum);
      $oFormWorkTab->addElement('hidden','actId','',$actId);      
      $oFormWorkTab->addElement('hidden','maxAmaunt','','100000.00');
      $oFormWorkTab->addElement('hidden','minAmaunt','','0.00');     
      $oFormWorkTab -> addElement('hidden', 'action_t', '');
      $i = 0;
      // form elements
      foreach ($aWorks as $d => $aGroupWorks)
      {
        foreach ($aGroupWorks as $j => $actWork)
        {       
          $export_type_string = false;
          if (!empty($actWork['DRBI_PROJECT_EXPORT']) && !in_array( $actWork['DRBI_PROJECT_EXPORT'],  $type_code))
          {
            $export_type_string = true;
          }

          $oFormWorkTab->addElement('hidden', 'id['.$i.']', '', $actWork['DRBI_ID']);
          $oFormWorkTab->addElement('hidden', 'description['.$i.']', '', $actWork['KKAL_APRAKSTS']);
          $oFormWorkTab->addElement('hidden', 'kid['.$i.']', '', $actWork['DRBI_KKAL_ID']);
          $oFormWorkTab->addElement('label', 'chipher['.$i.']', '', $actWork['DRBI_KKAL_SHIFRS']);
          $oFormWorkTab->addElement('label', 'title['.$i.']', '', $actWork['DRBI_KKAL_NOSAUKUMS']);
          $oFormWorkTab->addElement('label', 'measure['.$i.']', '', $actWork['DRBI_MERVIENIBA']);
          $oFormWorkTab->addElement('hidden', 'st['.$i.']', '', $actWork['DRBI_IS_WORKER']);
          $oFormWorkTab->addElement('hidden', 'import_no['.$i.']', '', $actWork['DRBI_IMPORT_NO']);
          
           // ajax handler link for delete
           $saveLink = new urlQuery();
           $saveLink->addPrm(FORM_ID, 'f.akt.s.21');
           $saveLink->addPrm(DONT_USE_GLB_TPL, '1');
           $saveLink->addPrm('xmlHttp', '1');    

          if($status == STAT_CLOSE && ($isAdmin ||  $projectApprover)){
              $oFormWorkTab->addElement('label', 'notes['.$i.']', '', $actWork['DRBI_PIEZIMES'], ' maxlength="250"');
              $oFormWorkTab->addElement('label', 'amount['.$i.']', '', $actWork['DRBI_DAUDZUMS']); 
              $oFormWorkTab->addElement('label', 'work_type['.$i.']', '', $actWork['KLDV_NOSAUKUMS']); 
              $oFormWorkTab->addElement('hidden', 'work_type_id['.$i.']', '', $actWork['DRBI_WORK_TYPE_ID']);
              $oFormWorkTab->addElement('label', 'work_type_text['.$i.']', '', $actWork['DRBI_WORK_TYPE_TEXT']);
              if($export_type_string) {
                $oFormWorkTab->addElement('label', 'export_type['.$i.']', '', $actWork['DRBI_PROJECT_EXPORT']); 
              } else {
              $oFormWorkTab -> addElement('select', 'export_type['.$i.']',  '', $actWork['DRBI_PROJECT_EXPORT'], 'maxlength="10"', '', '', $type);
              }
          } else {
            // save work_type_text
            $saveJs = "if(this.value != '') { 
              var rowId = document.forms['frmWorkTab']['id[" .$i. "]'];
              eval(xmlHttpGetValue('" .$saveLink -> getQuery() ."&work_type='+this.value+'&saveId='+rowId.value));
              this.style.borderColor = '#16bb24cc'; 
              this.parentNode.prepend(sp1);
              setTimeout(savedField, 3000, this, '#8c8c8c'); 
            }";
            $oFormWorkTab -> addElement('select', 'work_type['.$i.']',  '', $actWork['DRBI_WORK_TYPE_ID'], (($isReadonly)?' disabled ':''). '
            onchange="' . $saveJs . ';return false;" onkeypress = "this.onchange();" onpaste = "this.onchange();"', '', '', $workType);
            
            $oFormWorkTab -> addRule('work_type['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required'); 
             // save work_type_text
             $saveJs = "if(this.value != '') { 
              var rowId = document.forms['frmWorkTab']['id[" .$i. "]'];
              eval(xmlHttpGetValue('" .$saveLink -> getQuery() ."&work_type_text='+this.value+'&saveId='+rowId.value));
              this.style.borderColor = '#16bb24cc'; 
              this.parentNode.prepend(sp1);
              setTimeout(savedField, 3000, this, '#8c8c8c'); 
            }";
            $oFormWorkTab->addElement('text', 'work_type_text['.$i.']', '', $actWork['DRBI_WORK_TYPE_TEXT'], (($isReadonly)?' disabled ':'').'maxlength="50"'.'
            onchange="' . $saveJs . ';return false;" onkeypress = "this.onchange();" onpaste = "this.onchange();"');
            
              // save button
             $saveJs = "var amount = isDoubleAuto(this.value,3);               
             if(amount != '') { 
               if(this.parentNode.firstChild.nodeName == 'SPAN') {
                this.parentNode.removeChild(sp2);
               }
               this.value = amount;
               var rowId = document.forms['frmWorkTab']['id[" .$i. "]'];
               eval(xmlHttpGetValue('" .$saveLink -> getQuery() ."&amount='+this.value+'&saveId='+rowId.value));
                this.style.background = '#ffffff'; this.style.borderColor = '#16bb24cc';                 
                this.parentNode.prepend(sp1);
                setTimeout(savedField, 3000, this, '#8c8c8c'); 
             } else { 
               this.parentNode.prepend(sp2);
             }";
            $oFormWorkTab->addElement('text', 'amount['.$i.']', '', $actWork['DRBI_DAUDZUMS'], (($isReadonly)?' disabled ':'').'maxlength="9"'.
            ((isset($actWork['DRBI_DAUDZUMS'])) ? '' : ' style="background:#fda8a5;border: 1px solid #f80f07;" ') .'
            onchange="' . $saveJs . ';return false;" onkeypress = "this.onchange();" onpaste = "this.onchange();"' );
           
            if(!empty($actWork['DRBI_KKAL_SHIFRS']))            {   
                
                    //$oFormWorkTab -> addRule('amount['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
                    $oFormWorkTab -> addRule('amount['.$i.']', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);
                    // check Amaunt field
                    $v1=&$oFormWorkTab->createValidation('amauntValidation_'.$i, array('amount['.$i.']'), 'ifonefilled');
                    // ja Cilv?kstundas normat?vs ir defin?ts un > 100000
                    $r1=&$oFormWorkTab->createRule(array('amount['.$i.']', 'maxAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','<');
                    // ja koeficent ir defin?ts un < 0
                    $r2=&$oFormWorkTab->createRule(array('amount['.$i.']', 'minAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','>');
                    $oFormWorkTab->addRule(array($r1, $r2), 'groupRuleAmaunt_'.$i, 'group', $v1);
                
            }  
            // save notes
            $saveJs = " 
              var rowId = document.forms['frmWorkTab']['id[" .$i. "]'];
              var val = ((this.value != '') ? this.value : 'D');
              eval(xmlHttpGetValue('" .$saveLink -> getQuery() ."&notes='+val+'&saveId='+rowId.value));
              this.style.borderColor = '#16bb24cc'; 
              this.parentNode.prepend(sp1);
              setTimeout(savedField, 3000, this, '#8c8c8c'); 
            ";
            $oFormWorkTab->addElement('text', 'notes['.$i.']', '', $actWork['DRBI_PIEZIMES'], (($isReadonly)?' disabled ':'').'maxlength="250"'.'
            onchange="' . $saveJs . ';return false;" onkeypress = "this.onchange();" onpaste = "this.onchange();"');
            
            unset($saveLink);
            
            if ($oFormWorkTab -> isFormSubmitted()){
              $oFormWorkTab->setNewValue('chipher['.$i.']',$actWork['DRBI_KKAL_SHIFRS']);
              $oFormWorkTab->setNewValue('title['.$i.']',$actWork['DRBI_KKAL_NOSAUKUMS']);
              $oFormWorkTab->setNewValue('measure['.$i.']',$actWork['DRBI_MERVIENIBA']);
              $oFormWorkTab->setNewValue('import_no['.$i.']',$actWork['DRBI_IMPORT_NO']);        
              $oFormWorkTab->setNewValue('notes['.$i.']',$actWork['DRBI_PIEZIMES']);        
              $oFormWorkTab->setNewValue('amount['.$i.']',$actWork['DRBI_DAUDZUMS']);        
              $oFormWorkTab->setNewValue('work_type['.$i.']',$actWork['DRBI_WORK_TYPE_ID']);  
              $oFormWorkTab->setNewValue('work_type_text['.$i.']',$actWork['DRBI_WORK_TYPE_TEXT']);        
              $oFormWorkTab->setNewValue('id['.$i.']',$actWork['DRBI_ID']);
            }
          }

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
          $i++;
        }
      }
      // form buttons
      if (!$isReadonly || ($status == STAT_CLOSE && ($isAdmin )))
      {
        if(!$isReadonly ) {
          foreach ($calcGroups as $i => $group)
          {
            $oFormWorkTab->addElement('link', 'group['.$i.']', $group['TITLE'], '#', 'onClick="'.$group['URL'].'"', '');
          }
        }
        $oFormWorkTab -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_save_work.gif', 'width="120" height="20" ');
        $oFormWorkTab -> addElement('submitImg', 'delete_all', text::get('DELETE'), 'img/btn_delete_all_120.gif', 'width="120" height="20" onclick="if (isDeleteWithMessage(\''.text::get('WARNING_DELETE_ROW').'\')) {setValue(\'action_t\',\''.OP_DELETE.'\');} else {return false;}"');
      }
      

      // if form iz submit (save button was pressed)
	  if ($oFormWorkTab -> isFormSubmitted() && $isNew === false)
	  {
		/*if($oFormWorkTab ->isValid()  && $isRowValid)
		{
		   $r=dbProc::deleteActWorks($actId);
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
                        $r=dbProc::writeActWork($actId,
                        $row['kid'],
                        isset($row['chipher'])?$row['chipher']:' ',
                        $row['title'],
                        false,
                        $row['amount'],
                        false,
                        $row['measure'],
                        false,
                        false,
                        false,
                        false,
                        $row['notes'],
                        $row['st'],
                        $row['work_type'],
                        $row['work_type_text'],
                        $row['export_type'],
                        false,
                        $row['import_no'],
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
        } */
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