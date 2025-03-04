<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isEDUser = dbProc::isExistsUserRole($userId);
$isSystemUser = $isEDUser || $isEditor;
$isProjector = dbProc::isExistsUserRoleWithProject($userId) ;
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);
$projectApprover = dbProc::isUserInRole($userId, ROLE_PROJ_APPROVER);
// act ID
$actId  = reqVar::get('actId');
// search form
$isSearch  = reqVar::get('isSearch');
// search act by number
$searchNum  = reqVar::get('searchNum');
// work type from popup
$work_types = reqVar::get('work_types');

function getErrorMesaageString( $actId, $bullet, $newLine )
{
	    $error_messages = array();
      $empty_material = array();
      $result = '';
      $res = dbProc::getAllEmptyInputFields($actId);
      if (is_array($res))
      {
            foreach ($res as $row)
            {
              $error_messages[$row['MATR_WORK_TYPE']] = $bullet . ' ' . text::get('MATERIAL_ERROR_1'). '"'.
              $row['KLDV_NOSAUKUMS'] . '" ' . text::get('MATERIAL_ERROR_2').' '.
              str_replace('X', '', $row['MATR_WORK_TYPE_TEXT']).' ';
              $empty_material[$row['MATR_WORK_TYPE']][] = $row['MATR_KODS'];
            }
      }
      unset($res);  
      if (is_array($error_messages))
      {
        foreach ($error_messages as $key=>$row)
        {
          $result .=  $error_messages[$key] .' ' .implode(', ', $empty_material[$key]) . $newLine;
        }
      }
      return $result;
}

// Main form with XMLHTTP method load this code:
if (reqVar::get('xmlHttp') == 1)
{
    // if operation is DELETE , delete record from DB
    if (reqVar::get('deleteId')!='')
	  {
      dbProc::deleteActMaterialRecord(reqVar::get('deleteId'));      
      ?>
      document.all['frmMaterialTab'].submit();      
		  <?
    }

    // if operation is SAVE , save daudzumu in DB
    if (reqVar::get('saveId')!='' )
	  {
	    if (reqVar::get('amount')!='')
      {
        dbProc::updateMaterialDaudzums(reqVar::get('saveId'), reqVar::get('amount'));
        if (reqVar::get('actId')!='' && reqVar::get('wtype')!='') {
          $isNotSavedMaterials = dbProc::checkEmptyAmountInputFields($actId, reqVar::get('wtype'));
          if(!$isNotSavedMaterials) {
            ?>
              document.all["work_types"].className="flex";              
              document.all["work_types"].options[document.all["work_types"].selectedIndex].className="blackText";
            <?
          } 
          $error = getErrorMesaageString(reqVar::get('actId'), "\u2022", "\\r\\n");
           	
          ?>
          var span = document.getElementById("error_span");
          span.textContent = '<? echo $error ?>';
          
          <?
        }
      }
      if (reqVar::get('notes')!='')
      {
        $note = ((reqVar::get('notes') == 'D') ? '' : reqVar::get('notes'));
        dbProc::updateMaterialComment(reqVar::get('saveId'), $note);
      }      
      if(reqVar::get('crossection')!= '')
      {
        dbProc::updateMaterialCrossection(reqVar::get('saveId'), reqVar::get('crossection'));
      }
      if(reqVar::get('complectation')!= '')
      {
        dbProc::updateMaterialComplectation(reqVar::get('saveId'), reqVar::get('complectation'));
      }
      if (reqVar::get('work_type')!='')
      {
        dbProc::updateMaterialWorkType(reqVar::get('saveId'), reqVar::get('work_type'));
      }
      if (reqVar::get('export_type')!='')
      {
        dbProc::updateMaterialExportType(reqVar::get('saveId'), reqVar::get('export_type'));
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
      	session::set('MATR_FOR_DELETE_'.$a,$a);
      }
      else
      {
         session::del('MATR_FOR_DELETE_'.$a);
      }
      
    }

    if (isset($_GET['sort_k']) && isset($_GET['sort_o']))
    {
      ob_clean();
      $o = $_GET['sort_o'];
      if (isset($o))
      {
        session::set('project_material_order', $o);
        echo 'o = "'.$o.'";';
      }
      else
      {
        echo 'o = "";';
      }
      $k = $_GET['sort_k'];
      if ($k)
      {
        session::set('project_material_kol', $k);
        echo 'k = "'.$k.'";';
      }
      else
      {
        echo 'k = "";';
      }
    }
    exit();
}




// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isProjector ||  $projectApprover)
{
    if($actId !== false )
    {
      $oLink=new urlQuery();
      $oLink->addPrm(FORM_ID, 'f.akt.s.20');
      $oLink->addPrm('actId', $actId);
      $oLink->addPrm('isSearch', $isSearch);
      $oLink->addPrm('searchNum', $searchNum);
      $oLink->addPrm('tab', TAB_MATERIAL);
      $oLink->addPrm('isProject',1);
      $oFormMaterialTab = new Form('frmMaterialTab', 'post', $oLink->getQuery() . '#tab');
      unset($oLink);

      $oLink=new urlQuery();
      $oLink->addPrm(FORM_ID, 'f.akt.s.22');
      $oLink->addPrm(DONT_USE_GLB_TPL, '1');
      $oLink->addPrm('xmlHttp', '1');
      $oLink->addPrm('isProject',1);
      $searchLink = $oLink -> getQuery();
      unset($oLink);

      // add order params to listing
      $oLink = new urlQuery;
      $oLink -> addPrm(FORM_ID, 'f.akt.s.20');
      $oLink->addPrm('actId', $actId);
      $oLink->addPrm('isSearch', $isSearch);
      $oLink->addPrm('searchNum', $searchNum);
      $oLink->addPrm('tab', TAB_MATERIAL);
      $oLink->addPrm('work_types',$work_types); 
      $orderLink = $oLink -> getQuery();
      unset($oLink);

      // if operation is success, show success message and redirect top frame
      if (reqVar::get('successMessageTab') && $isNew === false)
      {
      	$oFormMaterialTab->addSuccess(reqVar::get('successMessageTab'));
      }

      $isReadonly   = true;
      // Ir pieejams main  anai, ja  AKTS:LIETOT JS =  Teko ais lietot js  un lietot ja loma ir  Ievad tais  un AKTS:STATUS =  Izveide  vai  Atgriezts  vai  T me .
      if(($act['RAKT_RLTT_ID'] == $userId && $isProjector || $isAdmin) && ($status == STAT_INSERT || $status == STAT_RETURN ) )
      {
        $isReadonly   = false;
      }
      $j = 0;
      //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.23');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('catalog',KL_MATERIALS);     
      $oPopLink->addPrm('work_types',$work_types);     
      $oPopLink->addPrm('st',1); 
      $favorit[$j]['TITLE'] = text::get('SEARCH_ST_MATERIAL');   ;
      $favorit[$j]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery(), false, 500, 500, true, false, true);
      unset($oPopLink);
      $j ++;
      //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.13');
      $oPopLink->addPrm('actId',$actId);
      $oPopLink->addPrm('catalog',KL_MATERIALS);
      $oPopLink->addPrm('isSearch', $isSearch);
      $oPopLink->addPrm('searchNum', $searchNum);
      $oPopLink->addPrm('work_types',$work_types); 
      $oPopLink->addPrm('isProject',1);
      $oPopLink->addPrm('st',0);
      $favorit[$j]['TITLE'] = text::get('SEARCH_NEW_FROM_LIST');   ;
      $favorit[$j]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery(), false, 500, 500, true, false, true);
      unset($oPopLink);
      $j ++;
      //Popup import no cita projekta
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.24');
      $oPopLink->addPrm('actId',$actId); 
     // $favorit[$j]['TITLE'] = text::get('IMPORT_NO_PROJECT');
     // $favorit[$j]['URL'] = RequestHandler::popupHref($oPopLink -> getQuery(), false, 500, 500, true, false, true);
 
       unset($oPopLink);
       unset($res);

      // get grupas list
      $workType=array();
      $workTypeDefinetly=array();
      $workTypeStyle=array();
      $workTypeDefinetly['X']=text::get('OTHER_MATERIAL');		
      $workType['']=text::get('EMPTY_SELECT_OPTION');		
      $res=dbProc::getWorkTypeListByWorkAndMaterials($actId);
      $q = 0;
      if (is_array($res))
      {
        foreach ($res as $row)
        {
          if($row['matr_cnt'] == 0) {
            $style = "italicText";
          } elseif ($row['matr_cnt'] > $row['filled_matr_cnt']) {
            $style = "redText";
          } else {
            $style = "blackText";
          }
          $workTypeStyle['X'] = "redText";
          $workTypeStyle[$row['KLDV_ID'].'^'.(isset($row['DRBI_WORK_TYPE_TEXT']) ? str_replace('"', '\'', $row['DRBI_WORK_TYPE_TEXT']) : 'X')] = $style;
          $workType[$row['KLDV_ID'].'^'.(isset($row['DRBI_WORK_TYPE_TEXT']) ? str_replace('"', '\'', $row['DRBI_WORK_TYPE_TEXT']) : 'X')] =$row['KLDV_NOSAUKUMS'].' '.$row['DRBI_WORK_TYPE_TEXT'];
          $workTypeDefinetly[$row['KLDV_ID'].'^'.(isset($row['DRBI_WORK_TYPE_TEXT']) ? str_replace('"', '\'', $row['DRBI_WORK_TYPE_TEXT']) : 'X')] =$row['KLDV_NOSAUKUMS'].' '.$row['DRBI_WORK_TYPE_TEXT'];
          if($q == 0 && $work_types == false) {
              $work_types =  $row['KLDV_ID'].'^'.(isset($row['DRBI_WORK_TYPE_TEXT']) ? str_replace('"', '\'', $row['DRBI_WORK_TYPE_TEXT']) : 'X');
          }  
          $q =+ 1;
        }
      }
      unset($res);
	    //print_r($workType);
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
      
      if ($oFormMaterialTab -> isFormSubmitted() ) {
        if($oFormMaterialTab->getValue('action_tt')== OP_DELETE)  {
        
          // get issue array
          $issues = array();
          $r = false;
          foreach ($_SESSION as $key => $val)
          {
            if(substr($key, 0, 16) == 'MATR_FOR_DELETE_' && !empty($val))
            {            
              $issues[] = $val;            
            }
          }
          //print_r($issues);
          if(count($issues) > 0)
          {
            foreach($issues as $a)
            {
              $r = dbProc::deleteActMaterialRecord($a);
              if($r !== false) {
                session::del('MATR_FOR_DELETE_'.$a);
              }
            }          
          }
          else {
            $oFormWorkTab->addError(text::get('ERROR_NOT_CHECKED'));
          }  
        }       
        $work_types = $oFormMaterialTab->getValue('work_types');
        if($oFormMaterialTab->getValue('action_tt')== OP_DEFAULT_ORDER)  {
          session::del('project_material_order');
          session::del('project_material_kol');          
        }
      }
      
      $aMaterials = array();
      $aMaterialExist = false;

      // add order params to listing
      $oLink = new urlQuery;
      $oLink ->addPrm(FORM_ID, 'f.akt.s.20');
      $oLink->addPrm('actId', $actId);
      $oLink->addPrm('isSearch', $isSearch);
      $oLink->addPrm('searchNum', $searchNum);
      $oLink->addPrm('tab', TAB_MATERIAL);    
      $oLink->addPrm('work_types',$work_types);         
      if (reqVar::get('tab') == 'TAB_MATERIAL') {
          $sortOrder = (session::get('project_material_order') && session::get('project_material_order') != '') ? session::get('project_material_order') : false; 
          $orderColumn = (session::get('project_material_kol') && session::get('project_material_kol') != '') ? session::get('project_material_kol') : false;
        
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
      }
      $materialCount=dbProc::getActMaterialListCount($actId, true, $work_types);
      $listing=new listing();
      $listing->setAmount($materialCount);

      $listingHtml=$listing->getHtml($oLink ->getQuery());
      unset($oLink);
     
      //Ja eksistee akta materiāli, tad nolasaam taas darbus no datu baazes
      $aMaterialDb=dbProc::getActMaterialList($actId, 
                                              false, false, true,  
                                              (session::get('project_material_order') && session::get('project_material_order') != '') ? session::get('project_material_order') : false, 
                                              $orderColumn = (session::get('project_material_kol') && session::get('project_material_kol') != '') ? session::get('project_material_kol') : false, 
                                              $work_types,
                                              $listing->getStartPosition(),
                                              $listing->getAmountOnPage());
      //print_r($aMaterialDb);
      $aMaterialExist = false;
      $matrWorkType = $work_types;
      $q = 0;
      foreach ($aMaterialDb as $material)
      {
        $material['MATR_PIEZIMES'] = ($material['MATR_PIEZIMES'] == 'NULL') ? '' : $material['MATR_PIEZIMES'];
        $aGroupMaterials[$q] = $material;         
        $aMaterialExist = true; 
        $q ++;
      }

      if(!$aMaterialExist) {
        $aGroupMaterials = array();          
      } 
  
      // error message
      $oFormMaterialTab->addElement('static', 'error_msg', '', getErrorMesaageString($actId, '&#x2022;', '<br>'));
      
      $oFormMaterialTab -> addElement('hidden', 'isSearch', '', $isSearch);
      $oFormMaterialTab -> addElement('hidden', 'searchNum', '', $searchNum);
      $oFormMaterialTab->addElement('hidden','actId','',$actId);
      $oFormMaterialTab->addElement('hidden','maxAmaunt','','100000.00');
      $oFormMaterialTab->addElement('hidden','minAmaunt','','0.00');
      $oFormMaterialTab->addElement('hidden', 'action_tt', '');

      $i = 0;
      // form elements
      
      $oFormMaterialTab -> addElement('select', 'work_types',  text::get('SINGLE_WORK_TYPE'), $matrWorkType, 
      'style="width:400px;" onchange="this.className=this.options[this.selectedIndex].className; document.forms[\'frmMaterialTab\'].submit();"', 
      '', '', $workTypeDefinetly, false, $workTypeStyle);
      
      $oFormMaterialTab->addElement('static','jsRefresh2','','<script>document.all["work_types"].className="'.(($workTypeStyle[$matrWorkType] == 'redText')? 'attention' : '').'";</script>');
    
      
      foreach ($aGroupMaterials as $j => $actMaterial)
      {  
        //echo "<pre>";	  
        //print_r($actMaterial);
		//echo "</pre>";	  
        $export_type_string = false;
        $crossection = false;
        $complectation = false;
        $complectationArray = array();
        if(substr($actMaterial['MATR_KODS'], 0, 2) == '09')
        {
          $crossection = true;
        }

        if(dbProc::isComplectationForCategory($actMaterial['MATR_KODS']))
        {
          $complectation = true;
          // get complectation list
          $complectationArray['']=text::get('EMPTY_SELECT_OPTION');		
          $res=dbProc::getProjectCategoryComplectation($actMaterial['MATR_KODS']);
          if (is_array($res))
          {
            foreach ($res as $row)
            {
              $complectationArray[$row['KMTK_KOMPLEKTACIJA']] =$row['KMTK_KOMPLEKTACIJA'];
            }
          }
          unset($res);
        }
        if (!empty($actMaterial['MATR_PROJECT_EXPORT']) && !in_array( $actMaterial['MATR_PROJECT_EXPORT'],  $type_code))
        {
          $export_type_string = true;
        }
		//echo $actMaterial['MATR_KODS'];
        $oFormMaterialTab->addElement('hidden', 'id['.$i.']', '', $actMaterial['MATR_ID']);
        $oFormMaterialTab->addElement('hidden', 'st['.$i.']', '', $actMaterial['MATR_IS_WORKER']);
        $oFormMaterialTab->addElement('label', 'code['.$i.']', '', $actMaterial['MATR_KODS']);
        $oFormMaterialTab->addElement('label', 'title['.$i.']', '', $actMaterial['MATR_NOSAUKUMS']);
        $oFormMaterialTab->addElement('label', 'unit['.$i.']', '', $actMaterial['MATR_MERVIENIBA']);
        $oFormMaterialTab->addElement('hidden', 'import_no['.$i.']', '', $actMaterial['MATR_IMPORT_NO']);
        $oFormMaterialTab->addElement('label', 'nomenklatura['.$i.']', '', $actMaterial['MATR_NOM_KODS']);
		$oFormMaterialTab->addElement('hidden', 'work_type_id['.$i.']', '', $actMaterial['MATR_WORK_TYPE']);
        $aMaterials[$j]['color'] ='#e4edd8';
        if($status == STAT_CLOSE) {
          switch ($actMaterial['MATR_NOM_STATUS']) {
            case 1:
              $aMaterials[$j]['color'] ='#70dc85';
                break;
            case 2:
              $aMaterials[$j]['color'] ='#dad7d7';
                break;
            case 3:
              $aMaterials[$j]['color'] ='#fb3f3f';
                break;
            default: 
            $aMaterials[$j]['color'] ='#e4edd8';
          }
        }
        if(!$crossection)
        {
          $oFormMaterialTab->addElement('label', 'crossection['.$i.']', '', '');
        }
        if(!$complectation)
        {
          $oFormMaterialTab->addElement('label', 'complectation['.$i.']', '', '');
        }
        
        // ajax handler link for delete
        $saveLink = new urlQuery();
        $saveLink->addPrm(FORM_ID, 'f.akt.s.22');
        $saveLink->addPrm(DONT_USE_GLB_TPL, '1');
        $saveLink->addPrm('xmlHttp', '1');
       
	  if($complectation)
	  {
		// save crossection
		$saveJs = "if(this.value != '') { 
		  var rowId = document.forms['frmMaterialTab']['id[" .$i. "]'];
		  eval(xmlHttpGetValue('" .$saveLink -> getQuery() ."&complectation='+this.value+'&saveId='+rowId.value));
		  this.style.borderColor = '#16bb24cc'; 
		  this.parentNode.prepend(sp1);
		  setTimeout(savedField, 3000, this, '#8c8c8c'); 
		}";
		  $oFormMaterialTab->addElement('select', 'complectation['.$i.']', '', $actMaterial['MATR_COMPLECTATION'], 
		  (($isReadonly)?' disabled ':'').'
		  onchange="' . $saveJs . ';return false;" onkeypress = "this.onchange();" onpaste = "this.onchange();"', '', '', $complectationArray);
		  $oFormMaterialTab -> addRule('complectation['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
	  }
	  if($crossection)
	  {
		// save crossection
		$saveJs = "if(this.value != '') { 
		  var rowId = document.forms['frmMaterialTab']['id[" .$i. "]'];
		  eval(xmlHttpGetValue('" .$saveLink -> getQuery() ."&crossection='+this.value+'&saveId='+rowId.value));
		  this.style.borderColor = '#16bb24cc'; 
		  this.parentNode.prepend(sp1);
		  setTimeout(savedField, 3000, this, '#8c8c8c'); 
		}";
		  $oFormMaterialTab->addElement('text', 'crossection['.$i.']', '', $actMaterial['MATR_CROSSECTION'], 
		  (($isReadonly)?' disabled ':'').'maxlength="20"'.'
		  onchange="' . $saveJs . ';return false;" onkeypress = "this.onchange();" onpaste = "this.onchange();"');
	  }         
		// save amount
		$saveJs = "var amount = isDoubleAuto(this.value,3); 
		if(amount != '') { 
		  if(this.parentNode.firstChild.nodeName == 'SPAN') {
			this.parentNode.removeChild(sp2);
			}
		  this.value = amount;
		  var rowId = document.forms['frmMaterialTab']['id[" .$i. "]'];
		  var actId = " .$actId. ";
		  var wtype = document.all['work_types'].value;
		  eval(xmlHttpGetValue('" .$saveLink -> getQuery() ."&amount='+this.value+'&saveId='+rowId.value+'&actId='+actId+'&wtype='+wtype));
		  this.style.background = '#ffffff'; this.style.borderColor = '#16bb24cc'; 
		  this.parentNode.prepend(sp1);
		  setTimeout(savedField, 3000, this, '#8c8c8c'); 
		} else { 
		  this.parentNode.prepend(sp2);
		}";
	  $oFormMaterialTab->addElement('text', 'amount_mat['.$i.']', '', $actMaterial['MATR_DAUDZUMS'], (($isReadonly)?' disabled ':'').'maxlength="9"'.
	  ((isset($actMaterial['MATR_DAUDZUMS'])) ? '' : ' style="background:#fda8a5;border: 1px solid #f80f07;" ') .'
	  onchange="' . $saveJs . ';return false;" onkeypress = "this.onchange();" onpaste = "this.onchange();"' );
	  
	  //$oFormMaterialTab -> addRule('amount_mat['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
	  $oFormMaterialTab -> addRule('amount_mat['.$i.']', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);
	  // check Amaunt field
	  $v1=&$oFormMaterialTab->createValidation('amaunt1Validation_'.$i, array('amount_mat['.$i.']'), 'ifonefilled');
	  // ja Amount ir definēts un > 100000
	  $r1=&$oFormMaterialTab->createRule(array('amount_mat['.$i.']', 'maxAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','<');
	  // ja Amount ir definēts un < 0
	  $r2=&$oFormMaterialTab->createRule(array('amount_mat['.$i.']', 'minAmaunt'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','>');
	  $oFormMaterialTab->addRule(array($r1, $r2), 'groupRuleAmaunt1_'.$i, 'group', $v1);
  
	  // save notes
	  $saveJs = "
		var rowId = document.forms['frmMaterialTab']['id[" .$i. "]'];
		var val = ((this.value != '') ? this.value : 'D');
		eval(xmlHttpGetValue('" .$saveLink -> getQuery() ."&notes='+val+'&saveId='+rowId.value));
		this.style.borderColor = '#16bb24cc'; 
		this.parentNode.prepend(sp1);
		setTimeout(savedField, 3000, this, '#8c8c8c'); 
	  ";
	  $oFormMaterialTab->addElement('text', 'notes['.$i.']', '', $actMaterial['MATR_PIEZIMES'], (($isReadonly)?' disabled ':'').'maxlength="250"'.'
	  onchange="' . $saveJs . ';return false;" onkeypress = "this.onchange();" onpaste = "this.onchange();"');

	  $saveJs = "if(this.value != '') { 
		var rowId = document.forms['frmMaterialTab']['id[" .$i. "]'];
		eval(xmlHttpGetValue('" .$saveLink -> getQuery() ."&work_type='+this.value+'&saveId='+rowId.value));
		this.style.borderColor = '#16bb24cc'; 
		this.parentNode.prepend(sp1);
		setTimeout(savedField, 3000, this, '#8c8c8c'); 
	  }";
	  $oFormMaterialTab -> addElement('select', 'work_type['.$i.']',  '', $actMaterial['MATR_WORK_TYPE'], (($isReadonly)?' disabled ':''). '
	  onchange="' . $saveJs . ';return false;" onkeypress = "this.onchange();" onpaste = "this.onchange();"', '', '', $workType);
	  //$oFormMaterialTab -> addRule('work_type['.$i.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
	  
	  
    if($status == STAT_CLOSE && ($isAdmin || $projectApprover)) {
		  if($export_type_string) {
            $oFormMaterialTab->addElement('label', 'export_type['.$i.']', '', $actMaterial['MATR_PROJECT_EXPORT']); 
          } else {
            // save export_type
            $saveJs = "if(this.value != '') { 
              var rowId = document.forms['frmMaterialTab']['id[" .$i. "]'];
              eval(xmlHttpGetValue('" .$saveLink -> getQuery() ."&export_type='+this.value+'&saveId='+rowId.value));
              this.style.borderColor = '#16bb24cc'; 
              this.parentNode.prepend(sp1);
              setTimeout(savedField, 3000, this, '#8c8c8c'); 
            }";
            $oFormMaterialTab -> addElement('select', 'export_type['.$i.']',  '', $actMaterial['MATR_PROJECT_EXPORT'], 
              'onchange="' . $saveJs . ';return false;" onkeypress = "this.onchange();" onpaste = "this.onchange();"', '', '', $type);            
          }
	  }
	  unset($saveLink);
	  if ($oFormMaterialTab -> isFormSubmitted()){
      $oFormMaterialTab->setNewValue('code['.$i.']',$actMaterial['MATR_KODS']);
      $oFormMaterialTab->setNewValue('title['.$i.']',$actMaterial['MATR_NOSAUKUMS']);
      $oFormMaterialTab->setNewValue('unit['.$i.']',$actMaterial['MATR_MERVIENIBA']);
      $oFormMaterialTab->setNewValue('import_no['.$i.']',$actMaterial['MATR_IMPORT_NO']);        
      $oFormMaterialTab->setNewValue('notes['.$i.']',$actMaterial['MATR_PIEZIMES']);  
      $oFormMaterialTab->setNewValue('crossection['.$i.']',$actMaterial['MATR_CROSSECTION']);
      $oFormMaterialTab->setNewValue('complectation['.$i.']',$actMaterial['MATR_COMPLECTATION']);        
      $oFormMaterialTab->setNewValue('amount_mat['.$i.']',$actMaterial['MATR_DAUDZUMS']);        
      $oFormMaterialTab->setNewValue('work_type['.$i.']',$actMaterial['MATR_WORK_TYPE']);      
      $oFormMaterialTab->setNewValue('work_type_id['.$i.']',$actMaterial['MATR_WORK_TYPE']);  
      $oFormMaterialTab -> setNewValue('id['.$i.']', $actMaterial['MATR_ID']);	
      $oFormMaterialTab->setNewValue('export_type['.$i.']',$actMaterial['MATR_PROJECT_EXPORT']);	
      $oFormMaterialTab->setNewValue('nomenklatura['.$i.']',$actMaterial['MATR_NOM_KODS']);		  
	  }

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
      
      // form buttons
      if (!$isReadonly || ($status == STAT_CLOSE && ($isAdmin )))
      {
        if (!$isReadonly)
        {
          foreach ($favorit as $i => $group)
          {
            $oFormMaterialTab->addElement('link', 'group['.$i.']', $group['TITLE'], '#', 'onClick="'.$group['URL'].'"', '');
          }
        }
        $oFormMaterialTab -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_save_material.gif', 'width="120" height="20" ');
        $oFormMaterialTab -> addElement('submitImg', 'delete_all', text::get('DELETE'), 'img/btn_delete_all_120.gif', 'width="120" height="20" onclick="if (isDeleteWithMessage(\''.text::get('WARNING_DELETE_ROW').'\')) {setValue(\'action_tt\',\''.OP_DELETE.'\');} else {return false;}"');
        $oFormMaterialTab -> addElement('submitImg', 'default_order', text::get('DEFAULT_ORDER'), 'img/btn_120_nokluseta_kartosana.gif', 'width="120" height="20" onclick="setValue(\'action_tt\',\''.OP_DEFAULT_ORDER.'\');"');
         //Popup saites sagatave
         $oPopLink=new urlQuery;
         $oPopLink->addPrm(FORM_ID, 'f.akt.s.25');
         $oPopLink->addPrm('actId',$actId);;
 
         $oFormMaterialTab -> addElement('submitImg', 'all', text::get('ALL_MATERIAL'), 'img/btn_120_all_materials.gif', 
         'width="120" height="20" onclick="if (!isEmptyFormField(\'frmMaterialTab\',\'actId\')) {'.
          RequestHandler::popupHref($oPopLink -> getQuery(), false, 800, 700).'; } return false;"');
         unset($oPopLink);         
      }

       $oFormMaterialTab -> makeHtml();
       include('f.akt.s.22.tpl');
    }



}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

/*
if($status == STAT_CLOSE && ($isAdmin || $projectApprover)) {
//echo $actMaterial['MATR_DAUDZUMS'];
$oFormMaterialTab->addElement('label', 'notes['.$i.']', '', $actMaterial['MATR_PIEZIMES'], ' maxlength="250"');
$oFormMaterialTab->addElement('label', 'amount_mat['.$i.']', '', $actMaterial['MATR_DAUDZUMS']); 
$oFormMaterialTab->addElement('label', 'work_type['.$i.']', '', $workType[$actMaterial['MATR_WORK_TYPE']]);  
$oFormMaterialTab->addElement('hidden', 'work_type_id['.$i.']', '', $actMaterial['MATR_WORK_TYPE']);

if($export_type_string) {
$oFormMaterialTab->addElement('label', 'export_type['.$i.']', '', $actMaterial['MATR_PROJECT_EXPORT']); 
} else {
// save export_type
$saveJs = "if(this.value != '') { 
  var rowId = document.forms['frmMaterialTab']['id[" .$i. "]'];
  eval(xmlHttpGetValue('" .$saveLink -> getQuery() ."&export_type='+this.value+'&saveId='+rowId.value));
  this.style.borderColor = '#16bb24cc'; 
  this.parentNode.prepend(sp1);
  setTimeout(savedField, 3000, this, '#8c8c8c'); 
}";
$oFormMaterialTab -> addElement('select', 'export_type['.$i.']',  '', $actMaterial['MATR_PROJECT_EXPORT'], 
  'onchange="' . $saveJs . ';return false;" onkeypress = "this.onchange();" onpaste = "this.onchange();"', '', '', $type);            
}
if($crossection)
{
  $oFormMaterialTab->addElement('label', 'crossection['.$i.']', '', $actMaterial['MATR_CROSSECTION']);
}
if($complectation)
{
$oFormMaterialTab->addElement('label', 'complectation['.$i.']', '', $actMaterial['MATR_COMPLECTATION']);
}
}
*/

?>