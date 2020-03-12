<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isEDUser = dbProc::isExistsUserRole($userId);
$isSystemUser = $isEDUser || $isEditor;

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
      $oFormMaterialTab = new Form('frmMaterialTab','post',$oLink->getQuery().'#tab');
      unset($oLink);

      // if operation is success, show success message and redirect top frame
      if (reqVar::get('successMessageTab') && $isNew === false)
      {
      	$oFormMaterialTab->addSuccess(reqVar::get('successMessageTab'));
      }

      $isReadonly   = true;
      // Ir pieejams mainīšanai, ja  AKTS:LIETOTĀJS = ’Tekošais lietotājs’ un lietotāja loma ir ‘Ievadītais’ un AKTS:STATUS = ‘Izveide’ vai ‘Atgriezts’ vai ‘Tāme’.
      if(($act['RAKT_RLTT_ID'] == $userId && ($isEditor || $isAdmin) && ($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ESTIMATE)) )
      {
        $isReadonly   = false;
      }


      //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.11');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('catalog',KL_MATERIALS);
      $oPopLink->addPrm('isSearch', $isSearch);
      $oPopLink->addPrm('searchNum', $searchNum);
      $oPopLink->addPrm('st',1);
      //$next =  count($favorit);
      $favorit[0]['TITLE'] = text::get('SEARCH_ST_MATERIAL');   ;
      $favorit[0]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery());
      unset($oPopLink);

      //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.11');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('catalog',KL_MATERIALS);
      $oPopLink->addPrm('isSearch', $isSearch);
      $oPopLink->addPrm('searchNum', $searchNum);
      $oPopLink->addPrm('st',0);
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
      $favorit[1]['TITLE'] = text::get('SEARCH_NEW');   ;
      $favorit[1]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery());
      unset($oPopLink);

      $aMaterials = array();
      if ($oFormMaterialTab -> isFormSubmitted() && $isNew === false)
      {
          $isRowValid = true;
          $aCodes =  $oFormMaterialTab->getValue('code');
          if(is_array($aCodes) )
          {
            foreach ($aCodes as $i => $val)
            {
                 $aMaterials[$i]['MATR_ID'] = $oFormMaterialTab->getValue('id['.$i.']');
                 $aMaterials[$i]['MATR_KODS'] = $oFormMaterialTab->getValue('code['.$i.']');
                 $aMaterials[$i]['MATR_NOSAUKUMS'] = $oFormMaterialTab->getValue('title['.$i.']');
                 $aMaterials[$i]['MATR_MERVIENIBA'] = $oFormMaterialTab->getValue('unit['.$i.']');
                 $aMaterials[$i]['MATR_CENA'] = $oFormMaterialTab->getValue('price['.$i.']');
                 $aMaterials[$i]['MATR_DAUDZUMS'] = $oFormMaterialTab->getValue('amount1['.$i.']');
                 $aMaterials[$i]['MATR_IS_WORKER'] = $oFormMaterialTab->getValue('st['.$i.']');
                 // validate work progress value
  			   if (empty($aMaterials[$i]['MATR_DAUDZUMS']))
  				{
  					// assign error message
  					$oFormMaterialTab->addErrorPerElem('amount1['.$i.']', text::get('ERROR_REQUIRED_FIELD'));
  					$isRowValid = false;
  				}
                  // validate work progress value
  			   elseif (!is_numeric($aMaterials[$i]['MATR_DAUDZUMS']))
  				{
  					// assign error message
  					$oFormMaterialTab->addErrorPerElem('amount1['.$i.']', text::get('ERROR_DOUBLE_VALUE'));
  					$isRowValid = false;
  				}
                  // validate work progress value
  			   elseif ($aMaterials[$i]['MATR_DAUDZUMS'] >= 100000)
  				{
  					// assign error message
  					$oFormMaterialTab->addErrorPerElem('amount1['.$i.']', text::get('ERROR_AMOUNT_VALUE_100000'));
  					$isRowValid = false;
  				}
                else
                {
                  $aMaterials[$i]['MATR_CENA_KOPA'] = number_format(($aMaterials[$i]['MATR_CENA']*$aMaterials[$i]['MATR_DAUDZUMS']), 2, '.', '');
                }
                  // prepare database record data
  			    $aValidRows[] = array(
      				'code' => $aMaterials[$i]['MATR_KODS'],
      				'title' => $aMaterials[$i]['MATR_NOSAUKUMS'],
      				'unit' => $aMaterials[$i]['MATR_MERVIENIBA'],
                    'price' => $aMaterials[$i]['MATR_CENA'],
      				'amount1' => $aMaterials[$i]['MATR_DAUDZUMS'],
      				'total1' => $aMaterials[$i]['MATR_CENA_KOPA'],
                    'st' => $aMaterials[$i]['MATR_IS_WORKER'],
                    'rowNum' => $i
  			    );
             }
           }
      }
      else
      {

        //Ja eksistee akta materiāli, tad nolasaam taas darbus no datu baazes
        $aMaterialDb=dbProc::getActMaterialList($actId);

        foreach ($aMaterialDb as $i => $material)
        {
           if (isset($material['MATR_CENA_KOPA']))
           {
                $mat_cena_kopa = $material['MATR_CENA_KOPA'];
           }
           else
           {
                $mat_cena_kopa = number_format($material['MATR_CENA'] *  $material['MATR_DAUDZUMS'], 2, '.', '');
           }

           $aMaterials[$i]['MATR_ID'] = $material['MATR_ID'];
           $aMaterials[$i]['MATR_KODS'] = $material['MATR_KODS'];
           $aMaterials[$i]['MATR_NOSAUKUMS'] = $material['MATR_NOSAUKUMS'];
           $aMaterials[$i]['MATR_MERVIENIBA'] = $material['MATR_MERVIENIBA'];
           $aMaterials[$i]['MATR_CENA'] = $material['MATR_CENA'];
           $aMaterials[$i]['MATR_DAUDZUMS'] = $material['MATR_DAUDZUMS'];
           $aMaterials[$i]['MATR_CENA_KOPA'] = $mat_cena_kopa; 	//$material['MATR_CENA_KOPA'];
           $aMaterials[$i]['MATR_IS_WORKER'] = $material['MATR_IS_WORKER'];

        }
      }
      $oFormMaterialTab -> addElement('hidden', 'isSearch', '', $isSearch);
      $oFormMaterialTab -> addElement('hidden', 'searchNum', '', $searchNum);
      $oFormMaterialTab->addElement('hidden','actId','',$actId);
      $oFormMaterialTab->addElement('hidden','maxAmaunt','','100000.00');
      $oFormMaterialTab->addElement('hidden','minAmaunt','','0.00');
      // form elements
      $totalPrice = 0;
      foreach ($aMaterials as $i => $actMaterial)
      {
        $oFormMaterialTab->addElement('hidden', 'id['.$i.']', '', $actMaterial['MATR_ID']);
        $oFormMaterialTab->addElement('hidden', 'st['.$i.']', '', $actMaterial['MATR_IS_WORKER']);
        $oFormMaterialTab->addElement('label', 'code['.$i.']', '', $actMaterial['MATR_KODS']);
        $oFormMaterialTab->addElement('label', 'title['.$i.']', '', $actMaterial['MATR_NOSAUKUMS']);
        $oFormMaterialTab->addElement('label', 'unit['.$i.']', '', $actMaterial['MATR_MERVIENIBA']);
        $oFormMaterialTab->addElement('label', 'price['.$i.']', '', $actMaterial['MATR_CENA']);

        $oFormMaterialTab->addElement('text', 'amount1['.$i.']', '', $actMaterial['MATR_DAUDZUMS'], (($isReadonly)?' disabled ':'').'maxlength="9"');
        $oFormMaterialTab -> addRule('amount1['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oFormMaterialTab -> addRule('amount1['.$i.']', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);
        // check Amaunt field
        $v1=&$oFormMaterialTab->createValidation('amaunt1Validation_'.$i, array('amount1['.$i.']'), 'ifonefilled');
        // ja Amount ir definēts un > 100000
        $r1=&$oFormMaterialTab->createRule(array('amount1['.$i.']', 'maxAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','<');
        // ja Amount ir definēts un < 0
        $r2=&$oFormMaterialTab->createRule(array('amount1['.$i.']', 'minAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','>');
        $oFormMaterialTab->addRule(array($r1, $r2), 'groupRuleAmaunt1_'.$i, 'group', $v1);

        $oFormMaterialTab->addElement('label', 'total1['.$i.']', '', $actMaterial['MATR_CENA_KOPA'], ' disabled maxlength="13"');

        $totalPrice += $actMaterial['MATR_CENA_KOPA'];

        // ajax handler link for delete
        $delLink = new urlQuery();
       $delLink->addPrm(FORM_ID, 'f.akt.s.3');
       $delLink->addPrm(DONT_USE_GLB_TPL, '1');
        $delLink->addPrm('xmlHttp', '1');
      //$delLink->addPrm('deleteId', $actWork['DRBI_ID']);
     // delete button
        $delButtonJs = "if(isDelete()) {
							var index=" . $i . ";
							var rowId = document.forms['frmMaterialTab']['id['+index+']'];
							rowId = rowId ? rowId.value : '';
							eval(xmlHttpGetValue('" .$delLink -> getQuery() ."&deleteId='+rowId));
						}";
        $oFormMaterialTab->addElement('button', 'mat_del['.$i.']', '', '', 'onclick="' . $delButtonJs . ';return false;" style="background: url(img/ico_del.gif); cursor:hand; border:0px; width: 20px; height: 20px;" title="' . text::get('DELETE') . '"');
        unset($delLink);
      }
      $totalPrice = number_format($totalPrice, 2, '.', '');

      // form buttons
      if (!$isReadonly)
      {
        foreach ($favorit as $i => $group)
        {
           $oFormMaterialTab->addElement('link', 'group['.$i.']', $group['TITLE'], '#', 'onClick="'.$group['URL'].'"', '');
        }
        $oFormMaterialTab -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_save_material.gif', 'width="120" height="20" ');
        //$oFormMaterialTab -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"');
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
                                                $row['price'],
                                                $row['amount1'],
                                                $row['total1'],
                                                $row['st']);
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
                           $oFormMaterialTab -> setNewValue('total1['.$row['rowNum'].']', $row['total1']);
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
       include('f.akt.s.3.tpl');
    }



}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>