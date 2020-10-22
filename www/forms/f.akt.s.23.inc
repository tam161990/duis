<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isProjector = dbProc::isExistsUserRoleWithProject($userId) ;
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;

// act ID
$actId  = reqVar::get('actId');
// catalog
$catalog  = reqVar::get('catalog');

// Main form with XMLHTTP method load this code:
  if (reqVar::get('xmlHttp') == 1)
  {
    if (reqVar::get('calc_group') !== false )
    {
  
      // unset previouse values of section
      ?>
      for(i=document.all["scope[]"].length; i>=0; i--)
      {
        document.all["scope[]"].options[i] = null;
      }
      <?
      $res=dbProc::getCalculationByGroupList(reqVar::get('calc_group'));
      if (is_array($res) && count($res)>0)
      {
        $i = 1;
        foreach ($res as $row)
        {
          // feel options array
          ?>
          document.all["scope[]"].options[<?=$i;?>] = new Option( '<?=$row['KKAL_SHIFRS'] .' : '. $row['KKAL_NOSAUKUMS'];?>', '<?=$row['KKAL_ID'];?>');
          <?
          $i++;
        }
      }
    }

    if (reqVar::get('mat_group') !== false )
    {
  
      // unset previouse values of section
      ?>
      for(i=document.all["mat_sub_group"].length; i>=0; i--)
      {
        document.all["mat_sub_group"].options[i] = null;
      }
      <?
      $res=dbProc::getMaterialSubGroup(reqVar::get('mat_group'));
      if (is_array($res) && count($res)>0)
      {
        $i = 1;
        foreach ($res as $row)
        {
          // feel options array
          ?>
          document.all["mat_sub_group"].options[<?=$i;?>] = new Option( '<?=$row['APAKSGRUPAS_KODS'] .' : '. $row['KMAT_APAKSGRUPAS_NOSAUKUNS'];?>', '<?=$row['KMAT_APAKSGRUPAS_KODS'];?>');
          <?
          $i++;
        }
      }
    }

    if (reqVar::get('mat_sub_group') !== false )
    {
  
      // unset previouse values of section
      ?>
      for(i=document.all["scope[]"].length; i>=0; i--)
      {
        document.all["scope[]"].options[i] = null;
      }
      <?
      $res=dbProc::getMaterialBySubGroup(reqVar::get('mat_sub_group'));
      if (is_array($res) && count($res)>0)
      {
        $i = 1;
        foreach ($res as $row)
        {
          // feel options array
          ?>
          document.all["scope[]"].options[<?=$i;?>] = new Option( '<?=$row['KMAT_KATEGORIJAS_KODS'] .' : '. $row['KMAT_KATEGORIJAS_NOSAUKUNS'];?>', '<?=$row['KMAT_ID'];?>');
          <?
          $i++;
        }
      }
    }
  
  
    exit;
  }

// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isProjector)
{
    $oLink=new urlQuery();
    $oLink->addPrm(FORM_ID, 'f.akt.s.23');
    $oFormPop = new Form('frmMainTab','post',$oLink->getQuery());
    unset($oLink);

    if($actId !== false  && ($catalog == KL_CALCULALATION  || $catalog == KL_MATERIALS) )
    {
      // get info about act
      $actInfo = dbProc::getActInfo($actId);
      //print_r($actInfo);
      if(count($actInfo)>0)
      {
      	$act = $actInfo[0];
        $status = $act['RAKT_STATUS'];
      }

      $default_kalk_gr_id = '';
      $default_matr_gr_id = '';
      $default_matr_subgr_id = '';
      $userPreferences = dbProc::getUserPreferences($actId, $userId);
      //print_r($userPreferences);
      if(is_array($userPreferences) && count($userPreferences)>0)
      {
        $default_kalk_gr_id = $userPreferences[0]['KKAL_ID'];
        $default_matr_gr_id = $userPreferences[0]['KMAT_GRUPAS_KODS'];
        $default_matr_subgr_id = $userPreferences[0]['KMAT_APAKSGRUPAS_KODS'];      
      }

      $isReadonly   = true;
      // Ir pieejams mainīšanai, ja  AKTS:LIETOTĀJS = ’Tekošais lietotājs’ un lietotāja loma ir ‘Ievadītais’ un AKTS:STATUS = ‘Izveide’ vai ‘Atgriezts’ vai ‘Tāme’.
      if(($act['RAKT_RLTT_ID'] == $userId && $isProjector || $isAdmin) && ($status == STAT_INSERT || $status == STAT_RETURN ) )
      {
        $isReadonly   = false;
      }

      $aScope=array();
      $aScope['-1']='';
     
      // get grupas list
      $workType=array();
      $workType['']=text::get('EMPTY_SELECT_OPTION');		
      
      
      switch ($catalog)
      {
        case  KL_CALCULALATION:
            // set list title
            $title = text::toUpper(text::get('ST_WORK'));    
            // get grupas nokluseto vertibu 
            $defaultWork = explode('^', dbProc::getDefaultWork($actId));
            // get grupas list           
            $res=dbProc::getWorkTypeList();
            if (is_array($res))
            {
              foreach ($res as $row)
              {
                $workType[$row['KLDV_ID']]=$row['KLDV_NOSAUKUMS'];
              }
            }
            unset($res);
            if($oFormPop->isFormSubmitted() ) {
              if ($oFormPop->getValue('action')==OP_UPDATE && $oFormPop->getValue('calc_group'))
              {
                $res=dbProc::getCalculationByGroupList($oFormPop->getValue('calc_group'));
              }
              if ($oFormPop->getValue('action')==OP_SEARCH && $oFormPop->getValue('text_part') != '')
              {
                $res = dbProc::getCalculationByText($oFormPop->getValue('text_part'));
              }
              if (isset($res) && is_array($res))
              {
                  foreach ($res as $row)
                  {
                      $aScope[$row['KKAL_ID']] = $row['KKAL_SHIFRS'] .' : '. $row['KKAL_NOSAUKUMS'] ;
                  }
                  unset($res);
              }
              else
              {
                $oFormPop->addError(text::get('NO_SEARCH_RESULTS'));
              }
              
            }
            break;
         
        case  KL_MATERIALS:

            // set list title
            $title = text::toUpper(text::get('ST_MATERIAL'));   
             // get grupas nokluseto vertibu 
            $defaultMaterial = dbProc::getDefaultMaterial($actId);  
            // get grupas list           
            $res=dbProc::getWorkTypeListByWork($actId);
            if (is_array($res))
            {
              foreach ($res as $row)
              {
                $workType[$row['KLDV_ID'].'^'.$row['DRBI_WORK_TYPE_TEXT']]=$row['KLDV_NOSAUKUMS'].' '.$row['DRBI_WORK_TYPE_TEXT'];
              }
            }
            unset($res);
            $matrGroup = array();
            $res=dbProc::getMaterialGroup();
            if (is_array($res))
            {
              $matrGroup['']=text::get('ALL');
              foreach ($res as $row)
              {
                $matrGroup[$row['KMAT_GRUPAS_KODS']]=$row['GRUPAS_KODS'].' : '.$row['KMAT_GRUPAS_NOSAUKUNS'];
              }
            }
            unset($res);

            $matrSubGroup = array();
            if(isset($default_matr_gr_id )) {
              
              $res=dbProc::getMaterialSubGroup($default_matr_gr_id);
              
              if (is_array($res))
              {
                $matrSubGroup['']=text::get('ALL');
                foreach ($res as $row)
                {
                  $matrSubGroup[$row['KMAT_APAKSGRUPAS_KODS']]=$row['APAKSGRUPAS_KODS'].' : '.$row['KMAT_APAKSGRUPAS_NOSAUKUNS'];
                }
              }
              unset($res);
            }
            
            $matrGroup['']=text::get('ALL');

            if ($oFormPop->isFormSubmitted()) {
              if ($oFormPop->getValue('action')==OP_UPDATE && $oFormPop->getValue('mat_sub_group'))
              {
                  $res=dbProc::getMaterialBySubGroup($oFormPop->getValue('mat_sub_group'));
              }
              if ($oFormPop->getValue('action')==OP_SEARCH && $oFormPop->getValue('category') != '')
              {
                $res = dbProc::getMaterialByCategory($oFormPop->getValue('category'));
              }
              if ($oFormPop->getValue('action')==OP_SEARCH && $oFormPop->getValue('text_part') != '')
              {
                $res = dbProc::getMaterialByText($oFormPop->getValue('text_part'));
              }
              if (isset($res) && is_array($res))
              {
                  foreach ($res as $row)
                  {
                      $aScope[$row['KMAT_ID']] = $row['KMAT_KATEGORIJAS_KODS'] .' : '. $row['KMAT_KATEGORIJAS_NOSAUKUNS'] ;
                  }
                  unset($res);
              }
              else
              {
                $oFormPop->addError(text::get('NO_SEARCH_RESULTS'));
              }
            }
           
            break;

      }

      
      // form elements
      $oFormPop -> addElement('hidden', 'action', '');
      $oFormPop -> addElement('hidden', 'actId', '', $actId);
      $oFormPop -> addElement('hidden', 'userId', '', $userId);
      $oFormPop -> addElement('hidden', 'catalog', '', $catalog);
      $oFormPop -> addElement('multiple_select', 'scope', '', '', (($isReadonly)?' disabled ':'').' size="15" ', '', '', $aScope);
      
      // xmlHttp link
  		$oLink=new urlQuery();
  		$oLink->addPrm(DONT_USE_GLB_TPL, 1);
      $oLink->addPrm(FORM_ID, 'f.akt.s.23');
      
      if($catalog == KL_CALCULALATION )
      {

        $oFormPop -> addElement('kls', 'calc_group',  text::get('SINGL_CALCULATION_GROUP'), 
        array('classifName'=>KL_CALCULALATION_GROUP,'value'=>$default_kalk_gr_id,'readonly'=>false), 
        'tabindex=1 maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&calc_group=\'+this.value+\'\'))"');
        
        $oFormPop->addElement('text', 'work_type_text', text::get('PROJECT_OBJECT_TITLE'), isset($defaultWork[1]) ? $defaultWork[1] : '', 'maxlength="50" tabindex=3');
      }
      if($catalog == KL_MATERIALS )
      {
        $oFormPop -> addElement('select', 'mat_group',  text::get('MATERIAL_GROUP'), $default_matr_gr_id, 
        ' tabindex=1 maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&mat_group=\'+this.value+\'\'))"', 
        '', '', $matrGroup);

        $oFormPop -> addElement('select', 'mat_sub_group',  text::get('SUBGROUP_TITLE'), $default_matr_subgr_id, 
        ' tabindex=2 maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&mat_sub_group=\'+this.value+\'\'))"', 
        '', '', $matrSubGroup);

        $oFormPop->addElement('text', 'category', text::get('MATERIAL_CATEGORY_CODE'), '', 'maxlength="50"');
        
      }
      unset($oLink);

      $oFormPop->addElement('text', 'text_part', text::get('CONTAIN_TEXT'), '', 'maxlength="50"');

      $oFormPop -> addElement('select', 'work_type',  text::get('SINGLE_WORK_TYPE'), (($catalog == KL_CALCULALATION) ? $defaultWork[0] : $defaultMaterial), 'tabindex=2', '', '', $workType);
      $oFormPop -> addRule('work_type', text::get('ERROR_REQUIRED_FIELD'), 'required');
      

      // form buttons
      if (!$isReadonly)
      {
        $oFormPop -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMainTab\',\'actId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
        $oFormPop -> addElement('submitImg', 'search_by_text', text::get('SEARCH'),'img/btn_meklet.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMainTab\',\'actId\')) {setValue(\'action\',\''.OP_SEARCH.'\');} else {return false;}"');
        if($catalog == KL_MATERIALS ){
          $oFormPop -> addElement('submitImg', 'search', text::get('SEARCH'),'img/btn_meklet.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMainTab\',\'actId\')) {setValue(\'action\',\''.OP_SEARCH.'\');} else {return false;}"');
        }
      }
    
      $oFormPop -> addElement('button', 'close', '', text::get('CLOSE'), 'class="btn70" onclick="javascript:window.close();return false;"; ');

      if ($oFormPop->isFormSubmitted() AND $oFormPop->getValue('action')==OP_UPDATE)
      {
        
            $checkRequiredFields = false;
            $r = true;
            $aListScope = $oFormPop->getValue('scope');
            if (is_array($aListScope) && count($aListScope) > 0)
			      {
                  foreach ($aListScope as $cValue)
                  {
                        if ($cValue>0)
                        {
                                switch ($catalog)
                                {
                                  case  KL_CALCULALATION:
                                    $r = dbProc::saveProjectWorkRecord($oFormPop->getValue('actId'), 
                                                                      $cValue, 
                                                                      $oFormPop->getValue('work_type'),
                                                                      $oFormPop->getValue('work_type_text'));
                                    break;                          
                                  case  KL_MATERIALS:
                                    $r = dbProc::saveProjectMaterialRecord($oFormPop->getValue('actId'), 
                                                                      $cValue, 
                                                                      $oFormPop->getValue('work_type')
                                                                    );
                                    break;

                                }
                                $r = dbProc::saveUserPreferences($oFormPop->getValue('actId'), 
                                                                  $oFormPop->getValue('userId'), 
                                                                  $oFormPop->getValue('calc_group'), 
                                                                  $oFormPop->getValue('mat_group'),
                                                                  $oFormPop->getValue('mat_sub_group'));
                                if(!$r)
                                {
                                  $oFormPop->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                                  break 1;
                                }
                                $checkRequiredFields = true;
                        }
                }
                if(!$checkRequiredFields)
                {
                    $oFormPop->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
                }
                else
                {
                   if($r)
                    {
                      $oRedirectLink=new urlQuery();
                      $oRedirectLink->addPrm(FORM_ID, 'f.akt.s.20');
                      $oRedirectLink->addPrm('actId', $oFormPop->getValue('actId'));
                      switch ($catalog)
                      {
                          case  KL_CALCULALATION:
                            $oRedirectLink->addPrm('tab', TAB_WORKS);
                            break;
                          case  KL_MATERIALS:
                            $oRedirectLink->addPrm('tab', TAB_MATERIAL);
                            break;

                      }

                      $oRedirectLink->addPrm('isNew', RequestHandler::getMicroTime());
                      requestHandler::makeParentReplace($oRedirectLink->getQuery().'#tab');
                      unset($oRedirectLink);
                   }
                }
			      }
            else
            {
              $oFormPop->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
            }

      }

      $oFormPop -> makeHtml();
      include('f.akt.s.23.tpl');
    }
    else
	{
		$oFormPop->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
	}
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>