<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isEDUser = dbProc::isExistsUserRole($userId);
$isSystemUser = $isEDUser || $isEditor;
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
	   dbProc::deleteActMaterialRecord(reqVar::get('deleteId'));
       ?>
	    rowNode = this.parentNode.parentNode;
		  rowNode.parentNode.removeChild(rowNode);
		<?
    }
    exit();
}


// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isProjector || $isEconomist)
{
    if($actId !== false )
    {
      $oLink=new urlQuery();
      $oLink->addPrm(FORM_ID, 'f.akt.s.20');
      $oLink->addPrm('actId', $actId);
      $oLink->addPrm('isSearch', $isSearch);
      $oLink->addPrm('searchNum', $searchNum);
      $oLink->addPrm('tab', TAB_MATERIAL);
      $oFormMaterialTab = new Form('frmMaterialTab', 'post', $oLink->getQuery() . '#tab');
      unset($oLink);

      // if operation is success, show success message and redirect top frame
      if (reqVar::get('successMessageTab') && $isNew === false)
      {
      	$oFormMaterialTab->addSuccess(reqVar::get('successMessageTab'));
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
      $oPopLink->addPrm('catalog',KL_MATERIALS);     
      $oPopLink->addPrm('st',1); 
      $favorit[0]['TITLE'] = text::get('SEARCH_NEW_FROM_LIST');   ;
      $favorit[0]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery(), false, 500, 500, true, false, true);
      unset($oPopLink);

      //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.13');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('catalog',KL_MATERIALS);
      $oPopLink->addPrm('isSearch', $isSearch);
      $oPopLink->addPrm('searchNum', $searchNum);
      $oPopLink->addPrm('isProject',1);
      $oPopLink->addPrm('st',0);
      $favorit[1]['TITLE'] = text::get('SEARCH_NEW');   ;
      $favorit[1]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery(), false, 500, 500, true, false, true);
      unset($oPopLink);

      // get grupas list
      $workType=array();
      $workType['']=text::get('EMPTY_SELECT_OPTION');		
      $res=dbProc::getWorkTypeListByWork($actId);
      if (is_array($res))
      {
        foreach ($res as $row)
        {
          $workType[$row['KLDV_ID']]=$row['KLDV_NOSAUKUMS'];
        }
      }
      unset($res);

      $aMaterials = array();
      $aMaterialExist = false;
      if ($oFormMaterialTab -> isFormSubmitted() && $isNew === false)
      {
          $isRowValid = true;
          $aCodes =  $oFormMaterialTab->getValue('code');
          if(is_array($aCodes) )
          {
            $aMaterialsFr = array();
            foreach ($aCodes as $i => $val)
            {
                 $aMaterialsFr[$i]['MATR_ID'] = $oFormMaterialTab->getValue('id['.$i.']');
                 $aMaterialsFr[$i]['MATR_KODS'] = $oFormMaterialTab->getValue('code['.$i.']');
                 $aMaterialsFr[$i]['MATR_NOSAUKUMS'] = $oFormMaterialTab->getValue('title['.$i.']');
                 $aMaterialsFr[$i]['MATR_MERVIENIBA'] = $oFormMaterialTab->getValue('unit['.$i.']');        
                 $aMaterialsFr[$i]['MATR_IS_WORKER'] = $oFormMaterialTab->getValue('st['.$i.']');
                 $aMaterialsFr[$i]['MATR_PIEZIMES'] = $oFormMaterialTab->getValue('notes['.$i.']');
                 $aMaterialsFr[$i]['MATR_WORK_TYPE_ID'] = $oFormMaterialTab->getValue('work_type['.$i.']');
                 // validate work progress value
                 
                  $aMaterialsFr[$i]['MATR_DAUDZUMS'] = $oFormMaterialTab->getValue('amount_mat['.$i.']');
                  if (empty($aMaterialsFr[$i]['MATR_DAUDZUMS']))
                  {
                      // assign error message
                      $oFormMaterialTab->addErrorPerElem('amount_mat['.$i.']', text::get('ERROR_REQUIRED_FIELD'));
                      $isRowValid = false;
                  }
                  // validate work progress value
                  elseif (!is_numeric($aMaterialsFr[$i]['MATR_DAUDZUMS']))
                  {
                      // assign error message
                      $oFormMaterialTab->addErrorPerElem('amount_mat['.$i.']', text::get('ERROR_DOUBLE_VALUE'));
                      $isRowValid = false;
                  }
                  // validate work progress value
                  elseif ($aMaterialsFr[$i]['MATR_DAUDZUMS'] >= 100000)
                  {
                      // assign error message
                      $oFormMaterialTab->addErrorPerElem('amount_mat['.$i.']', text::get('ERROR_AMOUNT_VALUE_100000'));
                      $isRowValid = false;
                  }
                  
              
                  // prepare database record data
                  $aValidRows[] = array(
                        'code' => $aMaterialsFr[$i]['MATR_KODS'],
                        'title' => $aMaterialsFr[$i]['MATR_NOSAUKUMS'],
                        'unit' => $aMaterialsFr[$i]['MATR_MERVIENIBA'],
                        'amount_mat' => $aMaterialsFr[$i]['MATR_DAUDZUMS'],                        
                        'st' => $aMaterialsFr[$i]['MATR_IS_WORKER'],
                        'notes' => $aMaterialsFr[$i]['MATR_PIEZIMES'],
                        'work_type' => $aMaterialsFr[$i]['MATR_WORK_TYPE_ID'],
                        'rowNum' => $i
                      );
                }
                foreach ($aMaterialsFr as $i=>$material)
                {
                  $aMaterials[$material['MATR_WORK_TYPE_ID']][] = $material;              
                }
           }
      }
      else
      {

        //Ja eksistee akta materiāli, tad nolasaam taas darbus no datu baazes
        $aMaterialDb=dbProc::getActMaterialList($actId);

        $aMaterialExist = false;
        foreach ($aMaterialDb as $material)
        {
          $aMaterials[$material['MATR_WORK_TYPE_ID']][] = $material;     
          $aMaterialExist = true;     
        }

        if(!$aMaterialExist) {
          $aMaterials[0] = array();          
        }    
      }
      $oFormMaterialTab -> addElement('hidden', 'isSearch', '', $isSearch);
      $oFormMaterialTab -> addElement('hidden', 'searchNum', '', $searchNum);
      $oFormMaterialTab->addElement('hidden','actId','',$actId);
      $oFormMaterialTab->addElement('hidden','maxAmaunt','','100000.00');
      $oFormMaterialTab->addElement('hidden','minAmaunt','','0.00');
      
      $i = 0;
      // form elements
      foreach ($aMaterials as $d => $aGroupMaterials)
      {
        foreach ($aGroupMaterials as $j => $actMaterial)
        {          
      
          $oFormMaterialTab->addElement('hidden', 'id['.$i.']', '', $actMaterial['MATR_ID']);
          $oFormMaterialTab->addElement('hidden', 'st['.$i.']', '', $actMaterial['MATR_IS_WORKER']);
          $oFormMaterialTab->addElement('label', 'code['.$i.']', '', $actMaterial['MATR_KODS']);
          $oFormMaterialTab->addElement('label', 'title['.$i.']', '', $actMaterial['MATR_NOSAUKUMS']);
          $oFormMaterialTab->addElement('label', 'unit['.$i.']', '', $actMaterial['MATR_MERVIENIBA']);
                  
          $oFormMaterialTab->addElement('text', 'amount_mat['.$i.']', '', $actMaterial['MATR_DAUDZUMS'], (($isReadonly)?' disabled ':'').'maxlength="9"');
          $oFormMaterialTab -> addRule('amount_mat['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
          $oFormMaterialTab -> addRule('amount_mat['.$i.']', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);
          // check Amaunt field
          $v1=&$oFormMaterialTab->createValidation('amaunt1Validation_'.$i, array('amount_mat['.$i.']'), 'ifonefilled');
          // ja Amount ir definēts un > 100000
          $r1=&$oFormMaterialTab->createRule(array('amount_mat['.$i.']', 'maxAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','<');
          // ja Amount ir definēts un < 0
          $r2=&$oFormMaterialTab->createRule(array('amount_mat['.$i.']', 'minAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','>');
          $oFormMaterialTab->addRule(array($r1, $r2), 'groupRuleAmaunt1_'.$i, 'group', $v1);
      
          $oFormMaterialTab->addElement('text', 'notes['.$i.']', '', $actMaterial['MATR_PIEZIMES'], (($isReadonly)?' disabled ':'').'maxlength="250"');

          $oFormMaterialTab -> addElement('select', 'work_type['.$i.']',  '', $actMaterial['MATR_WORK_TYPE_ID'], (($isReadonly)?' disabled ':'').'maxlength="9"', '', '', $workType);
          $oFormMaterialTab -> addRule('work_type['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
        

          // ajax handler link for delete
          $delLink = new urlQuery();
          $delLink->addPrm(FORM_ID, 'f.akt.s.22');
          $delLink->addPrm(DONT_USE_GLB_TPL, '1');
          $delLink->addPrm('xmlHttp', '1');
          // delete button
          $delButtonJs = "if(isDelete()) {
                var rowId = document.forms['frmMaterialTab']['id[" .$i. "]'];
                eval(xmlHttpGetValue('" .$delLink -> getQuery() ."&deleteId='+rowId.value));
              }";
              $oFormMaterialTab->addElement('button', 'mat_del['.$i.']', '', '', 'onclick="' . $delButtonJs . ';return false;" style="background: url(img/ico_del.gif); cursor:hand; border:0px; width: 20px; height: 20px;" title="' . text::get('DELETE') . '"');
              unset($delLink);
            
            $i++;
        }
      }
      // form buttons
      if (!$isReadonly)
      {
        foreach ($favorit as $i => $group)
        {
           $oFormMaterialTab->addElement('link', 'group['.$i.']', $group['TITLE'], '#', 'onClick="'.$group['URL'].'"', '');
        }
        $oFormMaterialTab -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_save_material.gif', 'width="120" height="20" ');
        
      }

      // if form iz submit (save button was pressed)
	  if ($oFormMaterialTab -> isFormSubmitted()&& $isNew === false)
	  { 
      if($oFormMaterialTab ->isValid()  && $isRowValid)
      {
          $r=dbProc::deleteActMaterials($actId);
          if ($r === false)
          {
            $oFormMaterialTab->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
          }
          else
          {
              if(is_array($aValidRows))
              { 
                    foreach($aValidRows as $i => $row)
                    {                         
                          $r=dbProc::writeActMaterial($actId,
                                                $row['code'],
                                                $row['title'],
                                                $row['unit'],
                                                false,
                                                $row['amount_mat'],
                                                false,
                                                $row['st'],
                                                false,
                                                $row['notes'],
                                                $row['work_type']
                                              );
                          // if work not inserted in to the DB
                          // delete  task record and show error message
                          if($r === false)
                          {
                                dbProc::deleteActMaterials($actId);
                                $oFormMaterialTab->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                                break;
                          }
                          else
                          {
                            $Id=dbLayer::getInsertId();
                            $oFormMaterialTab -> setNewValue('id['.$row['rowNum'].']', $Id);
                            $oFormMaterialTab->addSuccess(text::get('RECORD_WAS_SAVED'));
                          }
                    }
                    // saglaba lietotaja darbiibu
                    dbProc::setUserActionDate($userId, ACT_UPDATE);
                }
           }
        }
      }
       $oFormMaterialTab -> makeHtml();
       include('f.akt.s.22.tpl');
    }



}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>