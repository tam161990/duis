<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isEDUser = dbProc::isExistsUserRole($userId);
$isSystemUser = $isEDUser || $isEditor;
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);
$isSuperAdmin=userAuthorization::isSuperAdmin();

// act ID
$actId  = reqVar::get('actId');
// search form
$isSearch  = reqVar::get('isSearch');
// search act by number
$searchNum  = reqVar::get('searchNum');
// Auto
if(isset($tame))
  $tameMaterial  = $tame;
else 
  $tameMaterial   = reqVar::get('tame_mat');

// Main form with XMLHTTP method load this code:
if (reqVar::get('xmlHttp') == 1)
{
    // if operation is DELETE , delete record from DB
    if (reqVar::get('deleteId')!='')
	{
	   dbProc::deleteActMaterialRecord(reqVar::get('deleteId'), reqVar::get('tame_mat'));
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
      $oLink->addPrm('tab', TAB_MATERIAL);
      $oLink->addPrm('tametab', TAB_MATERIAL_T);
      $oFormMaterialTab = new Form('frmMaterialTab'.(($tameMaterial==1) ? 'T' : ''), 'post', $oLink->getQuery() . '#tab');
      unset($oLink);

      // if operation is success, show success message and redirect top frame
      if (reqVar::get('successMessageTab') && $isNew === false)
      {
      	$oFormMaterialTab->addSuccess(reqVar::get('successMessageTab'));
      }

      $isReadonly   = true;
      // Ir pieejams mainīšanai, ja  AKTS:LIETOTĀJS = ’Tekošais lietotājs’ un lietotāja loma ir ‘Ievadītais’ un AKTS:STATUS = ‘Izveide’ vai ‘Atgriezts’ vai ‘Tāme’.
      if((( $act['RAKT_RLTT_ID'] == $userId && $isEditor) || $isAdmin || $isEconomist || $isSuperAdmin) && 
      ((($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ESTIMATE) && $tameMaterial==0 )|| 
      ($status == STAT_AUTO && $tameMaterial==1 ))
      )
      {
        $isReadonly   = false;
      }


       if($tameMaterial== false) {

        //Popup saites sagatave
        $oPopLink=new urlQuery;
        $oPopLink->addPrm(FORM_ID, 'f.akt.s.8');
        $oPopLink->addPrm('actId',$actId);
        $oPopLink->addPrm('catalog',KL_MATERIALS);
        $oPopLink->addPrm('isSearch', $isSearch);
        $oPopLink->addPrm('searchNum', $searchNum);


        $favorit[0]['TITLE'] = text::get('TAB_ESTIMATE');  
        $favorit[0]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery().'&estimate=1', false, 700, 450);
      } else {
        $favorit[0]['TITLE'] ='';
              $favorit[0]['URL'] = '';
      }

      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.11');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('catalog',KL_MATERIALS);
      $oPopLink->addPrm('isSearch', $isSearch);
      $oPopLink->addPrm('searchNum', $searchNum);
      $oPopLink->addPrm('st',1);
      $oPopLink->addPrm('tame', $tameMaterial ?'1':'0');      

      //$next =  count($favorit);
      $favorit[1]['TITLE'] = text::get('SEARCH_ST_MATERIAL');   ;
      $favorit[1]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery());
      unset($oPopLink);

      //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.11');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('catalog',KL_MATERIALS);
      $oPopLink->addPrm('isSearch', $isSearch);
      $oPopLink->addPrm('searchNum', $searchNum);
      $oPopLink->addPrm('st',1);
      $oPopLink->addPrm('tame', $tameMaterial ?'1':'0');
     // $favorit[1]['TITLE'] = text::get('SEARCH_NEW_FROM_LIST');   ;
     // $favorit[1]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery());
      unset($oPopLink);

      //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.13');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('catalog',KL_MATERIALS);
      $oPopLink->addPrm('isSearch', $isSearch);
      $oPopLink->addPrm('searchNum', $searchNum);
      $oPopLink->addPrm('st',0);
      $oPopLink->addPrm('tame', $tameMaterial ?'1':'0');
      $favorit[2]['TITLE'] = text::get('WORKER_MATERIAL');   ;
      $favorit[2]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery());
      unset($oPopLink);

      $aMaterials = array();
      $aMaterialkExist = false;
      if ($oFormMaterialTab -> isFormSubmitted() && $isNew === false && $oFormMaterialTab->getValue('action')!=OP_EXPORT)
      {
        
          $isRowValid = true;
          $aCodes =  $oFormMaterialTab->getValue('code');
          if(is_array($aCodes) )
          {
            $aMaterialFr = array();
            foreach ($aCodes as $i => $val)
            {
                 $aMaterialFr[$i]['MATR_ID'] = $oFormMaterialTab->getValue('id['.$i.']');
                 $aMaterialFr[$i]['MATR_KODS'] = $oFormMaterialTab->getValue('code['.$i.']');
                 $aMaterialFr[$i]['MATR_NOSAUKUMS'] = $oFormMaterialTab->getValue('title['.$i.']');
                 $aMaterialFr[$i]['MATR_MERVIENIBA'] = $oFormMaterialTab->getValue('unit['.$i.']');
                 $aMaterialFr[$i]['MATR_CENA'] = $oFormMaterialTab->getValue('price['.$i.']');                 
                 $aMaterialFr[$i]['MATR_IS_WORKER'] = $oFormMaterialTab->getValue('st['.$i.']');
                 $aMaterialFr[$i]['MATR_APPROVE_DATE'] = $oFormMaterialTab->getValue('edited['.$i.']');
                 $aMaterialFr[$i]['MATR_WORK_APROVE_DATE'] = $oFormMaterialTab->getValue('work_aprove_date['.$i.']');
                 // validate work progress value
                 if($tameMaterial ){

                    $aMaterialFr[$i]['MATR_DAUDZUMS_KOR'] = $oFormMaterialTab->getValue('amount_kor_mat['.$i.']');

                    // validate work progress value
                    if (empty($aMaterialFr[$i]['MATR_DAUDZUMS_KOR'])) {
                        // assign error message
                        $oFormMaterialTab->addErrorPerElem('amount_kor_mat[' . $i . ']', text::get('ERROR_REQUIRED_FIELD'));
                        $isRowValid = false;
                    } // validate work progress value
                    elseif (!is_numeric($aMaterialFr[$i]['MATR_DAUDZUMS_KOR'])) {
                        // assign error message
                        $oFormMaterialTab->addErrorPerElem('amount_kor_mat[' . $i . ']', text::get('ERROR_DOUBLE_VALUE'));
                        $isRowValid = false;
                    } // validate work progress value
                    elseif ($aMaterialFr[$i]['MATR_DAUDZUMS_KOR'] >= 100000) {
                        // assign error message
                        $oFormMaterialTab->addErrorPerElem('amount_kor_mat[' . $i . ']', text::get('ERROR_AMOUNT_VALUE_100000'));
                        $isRowValid = false;
                    } else {
                        $aMaterialFr[$i]['MATR_CENA_KOPA'] = number_format(($aMaterialFr[$i]['MATR_CENA'] * $aMaterialFr[$i]['MATR_DAUDZUMS_KOR']), 2, '.', '');
                    }
                    $aMaterialFr[$i]['MATR_DAUDZUMS'] = $oFormMaterialTab->getValue('amount_km['.$i.']');
                } else {
                  $aMaterialFr[$i]['MATR_DAUDZUMS'] = $oFormMaterialTab->getValue('amount_mat['.$i.']');
                    if (empty($aMaterialFr[$i]['MATR_DAUDZUMS']))
                    {
                        // assign error message
                        $oFormMaterialTab->addErrorPerElem('amount_mat['.$i.']', text::get('ERROR_REQUIRED_FIELD'));
                        $isRowValid = false;
                    }
                    // validate work progress value
                    elseif (!is_numeric($aMaterialFr[$i]['MATR_DAUDZUMS']))
                    {
                        // assign error message
                        $oFormMaterialTab->addErrorPerElem('amount_mat['.$i.']', text::get('ERROR_DOUBLE_VALUE'));
                        $isRowValid = false;
                    }
                    // validate work progress value
                    elseif ($aMaterialFr[$i]['MATR_DAUDZUMS'] >= 100000)
                    {
                        // assign error message
                        $oFormMaterialTab->addErrorPerElem('amount_mat['.$i.']', text::get('ERROR_AMOUNT_VALUE_100000'));
                        $isRowValid = false;
                    }
                    else
                    {
                        $aMaterialFr[$i]['MATR_CENA_KOPA'] = number_format(($aMaterialFr[$i]['MATR_CENA']*$aMaterialFr[$i]['MATR_DAUDZUMS']), 2, '.', '');
                    }
              }
              // prepare database record data
  			      $aAllRows[] = array(
                    'code' => $aMaterialFr[$i]['MATR_KODS'],
                    'title' => $aMaterialFr[$i]['MATR_NOSAUKUMS'],
                    'unit' => $aMaterialFr[$i]['MATR_MERVIENIBA'],
                    'price' => $aMaterialFr[$i]['MATR_CENA'],
                    'amount_mat' => $aMaterialFr[$i]['MATR_DAUDZUMS'],
                    'amount_kor_mat' => ($oFormMaterialTab->getValue('tame_mat') == 1) ? $aMaterialFr[$i]['MATR_DAUDZUMS_KOR'] :'',
                    'total_mat' => $aMaterialFr[$i]['MATR_CENA_KOPA'],
                    'st' => $aMaterialFr[$i]['MATR_IS_WORKER'],
                    'edited' => $aMaterialFr[$i]['MATR_APPROVE_DATE'],
                    'work_aprove_date' => $aMaterialFr[$i]['MATR_WORK_APROVE_DATE'],
                    'rowNum' => $i
                  );
             }

             foreach ($aAllRows as $i => $row){
              $aValidRows[$i] = $row;
            }

            foreach ($aMaterialFr as $i=>$material)
            {
              $aMaterials[$material['MATR_WORK_APROVE_DATE']][] = $material;
            }
           }
      }
      else
      {

        //Ja eksistee akta materiāli, tad nolasaam taas darbus no datu baazes
        $aMaterialDb=dbProc::getActMaterialList($actId,  $tameMaterial );

        
        $aMaterialkExist = false;
        foreach ($aMaterialDb as $i => $material)
        {
            if(empty($material['MATR_WORK_APROVE_DATE'])) {
              $material['MATR_WORK_APROVE_DATE'] = DEFAULT_DATE;
            }
            if (empty($material['MATR_CENA_KOPA']))
            {
                $material['MATR_CENA_KOPA'] = number_format($material['MATR_CENA'] *  $material['MATR_DAUDZUMS'], 2, '.', '');
            }
            
            $aMaterials[$material['MATR_WORK_APROVE_DATE']][$i] = $material;  
            if($tameMaterial){
                $aMaterials[$material['MATR_WORK_APROVE_DATE']][$i]['MATR_DAUDZUMS_KOR'] = $material['MATR_DAUDZUMS_KOR'];
            }   
            $aMaterialkExist = true;     
          }
      }

      if(!$aMaterialkExist) {
        $aMaterials[0] = array();          
      }
      

      $oFormMaterialTab -> addElement('hidden', 'isSearch', '', $isSearch);
      $oFormMaterialTab -> addElement('hidden', 'searchNum', '', $searchNum);
      $oFormMaterialTab->addElement('hidden','actId','',$actId);
      $oFormMaterialTab->addElement('hidden','action','','');
      $oFormMaterialTab->addElement('hidden','maxAmaunt','','100000.00');
      $oFormMaterialTab->addElement('hidden','minAmaunt','','0.00');
      $oFormMaterialTab->addElement('hidden','tame_mat','',($tameMaterial) ? 1 : 0);

      // form elements
      $totalTime = array();
      $totalPrice = 0;
      $workApproveDate = array();

      $i = 0;
      foreach ($aMaterials as $d => $aDayMaterial)
      {
        foreach ($aDayMaterial as $j => $actMaterial)
        {      
          
            $oFormMaterialTab->addElement('hidden', 'id['.$i.']', '', $actMaterial['MATR_ID']);
            $oFormMaterialTab->addElement('hidden', 'st['.$i.']', '', $actMaterial['MATR_IS_WORKER']);
            $oFormMaterialTab->addElement('label', 'code['.$i.']', '', $actMaterial['MATR_KODS']);
            $oFormMaterialTab->addElement('label', 'title['.$i.']', '', $actMaterial['MATR_NOSAUKUMS']);
            $oFormMaterialTab->addElement('label', 'unit['.$i.']', '', $actMaterial['MATR_MERVIENIBA']);
            $oFormMaterialTab->addElement('label', 'price['.$i.']', '', $actMaterial['MATR_CENA']);
            $oFormMaterialTab->addElement('hidden', 'edited['.$i.']', '', $actMaterial['MATR_APPROVE_DATE']);
            $oFormMaterialTab->addElement('hidden', 'work_aprove_date['.$i.']', '', $actMaterial['MATR_WORK_APROVE_DATE']);

            if($tameMaterial || $oFormMaterialTab->getValue('tame_mat') == 1) {

              $oFormMaterialTab->addElement('label', 'amount_km['.$i.']', '', $actMaterial['MATR_DAUDZUMS']);  
              $oFormMaterialTab->setNewValue('amount_km['.$i.']', number_format($actMaterial['MATR_DAUDZUMS'], 3, '.', '')); 
              
              $oFormMaterialTab->addElement('text', 'amount_kor_mat['.$i.']', '', $actMaterial['MATR_DAUDZUMS_KOR'], (($isReadonly)?' disabled ':'').'maxlength="9"');

              $oFormMaterialTab->addRule('amount_kor_mat[' . $i . ']', text::get('ERROR_REQUIRED_FIELD'), 'required');
              $oFormMaterialTab->addRule('amount_kor_mat[' . $i . ']', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);
              // check Amaunt field
              $v1 =& $oFormMaterialTab->createValidation('amauntKorValidation_' . $i, array('amount_kor_mat[' . $i . ']'), 'ifonefilled');
              // ja Amount ir definēts un > 100000
              $r1 =& $oFormMaterialTab->createRule(array('amount_kor_mat[' . $i . ']', 'maxAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble', '<');
              // ja Amount ir definēts un < 0
              $r2 =& $oFormMaterialTab->createRule(array('amount_kor_mat[' . $i . ']', 'minAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble', '>');
              $oFormMaterialTab->addRule(array($r1, $r2), 'groupRuleAmauntKor_' . $i, 'group', $v1);
          } else {
              if( empty($actMaterial['MATR_APPROVE_DATE']) ) {
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
              } else {
                  $oFormMaterialTab->addElement('label', 'amount_mat['.$i.']', '', $actMaterial['MATR_DAUDZUMS']); 
              }
          }

          $oFormMaterialTab->addElement('label', 'total_mat['.$i.']', '', $actMaterial['MATR_CENA_KOPA'], ' disabled maxlength="13"');

          $totalPrice += $actMaterial['MATR_CENA_KOPA'];          
	        $workApproveDate[$d] =  (($actMaterial['MATR_WORK_APROVE_DATE'] == DEFAULT_DATE) ? "" : $actMaterial['MATR_WORK_APROVE_DATE']);

          if( !$isReadonly && (empty($actMaterial['MATR_APPROVE_DATE'])  || $tameMaterial) ) {
              // ajax handler link for delete
              $delLink = new urlQuery();
              $delLink->addPrm(FORM_ID, 'f.akt.s.3');
              $delLink->addPrm(DONT_USE_GLB_TPL, '1');
              $delLink->addPrm('xmlHttp', '1');
              $delLink->addPrm('tame_mat', $tameMaterial ?'1':'0');
              //$delLink->addPrm('deleteId', $actWork['DRBI_ID']);
              // delete button
              $delButtonJs = "if(isDelete()) {
                    var rowId = document.forms['frmMaterialTab".(($tameMaterial ) ? 'T' : '')."']['id[" .$i. "]'];
                    eval(xmlHttpGetValue('" .$delLink -> getQuery() ."&deleteId='+rowId.value));
                  }";
                  $oFormMaterialTab->addElement('button', 'mat_del['.$i.']', '', '', 'onclick="' . $delButtonJs . ';return false;" style="background: url(img/ico_del.gif); cursor:hand; border:0px; width: 20px; height: 20px;" title="' . text::get('DELETE') . '"');
                  unset($delLink);
          }
          $i++;
        }
        
        $totalTime[$d] = number_format($totalPrice, 2, '.', '');
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
      if($tameMaterial) {
        $oFormMaterialTab -> addElement('submitImg', 'export', text::get('EXPORT'), 'img/export_to_excel.gif', ' height="20" onclick="if (!isEmptyFormField(\'frmMaterialTabT\',\'actId\') ) {setFormValue(\'frmMaterialTabT\',\'action\',\''.OP_EXPORT.'\');} else {return false;}"');
     }

      // if form iz submit (save button was pressed)
	  if ($oFormMaterialTab -> isFormSubmitted()&& $isNew === false)
	  {
      if($tameMaterial && $oFormMaterialTab->getValue('action')==OP_EXPORT)
      {
          // akta sagatavi (tab tamme)
          $idFile = toExcel::exportTameMaterial($actId, $userId, FILE_ESTIMATE);
          if($idFile !== false) {
            $oLink=new urlQuery();
            $oLink->addPrm(FORM_ID, 'f.akt.s.1');
            $oLink->addPrm('actId', $actId);
            $oLink->addPrm('tab', TAB_ESTIMATE);
            RequestHandler::makeRedirect($oLink->getQuery());
        }
        else {
          $oFormMaterialTab->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
        }
      } 
      else 
      {
        if($oFormMaterialTab ->isValid()  && $isRowValid)
        {
      
          $r=dbProc::deleteActMaterials($actId, $tameMaterial);
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
                              $row['price'],
                              $row['amount_mat'],
                              $row['total_mat'],
                              $row['st'],
                              ($tameMaterial) ? $row['amount_kor_mat']:false,
                              false,
                              false,
                              $row['work_aprove_date'],
                              $row['edited']
                        );
                          // if work not inserted in to the DB
                          // delete  task record and show error message
                          if($r === false)
                          {
                                dbProc::deleteActMaterials($actId, $tameMaterial);
                                $oFormMaterialTab->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                                break;
                          }
                          else
                          {
                            $Id=dbLayer::getInsertId();
                            $oFormMaterialTab -> setNewValue('id['.$row['rowNum'].']', $Id);
                            $oFormMaterialTab -> setNewValue('total_mat['.$row['rowNum'].']', $row['total_mat']);
                            $oFormMaterialTab->addSuccess(text::get('RECORD_WAS_SAVED'));

                          }
                      }
                      // saglaba lietotaja darbiibu
                      dbProc::setUserActionDate($userId, ACT_UPDATE);
                  }
            }
          }
        }
      }
       $oFormMaterialTab -> makeHtml();
       include('f.akt.s.3.tpl');
    }



}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>