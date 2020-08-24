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
          document.all["mat_sub_group"].options[<?=$i;?>] = new Option( '<?=$row['KMAT_APAKSGRUPAS_KODS'] .' : '. $row['KMAT_APAKSGRUPAS_NOSAUKUNS'];?>', '<?=$row['KMAT_APAKSGRUPAS_KODS'];?>');
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
          document.all["scope[]"].options[<?=$i;?>] = new Option( '<?=$row['KMAT_KODS'] .' : '. $row['KMAT_NOSAUKUMS'];?>', '<?=$row['KMAT_ID'];?>');
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
            if ($oFormPop->isFormSubmitted() && $oFormPop->getValue('action')==OP_UPDATE && $oFormPop->getValue('calc_group'))
            {
              $res=dbProc::getCalculationByGroupList($oFormPop->getValue('calc_group'));
              if (is_array($res))
              {
                  foreach ($res as $row)
               	  {
                	    $aScope[$row['KKAL_ID']] = $row['KKAL_SHIFRS'] .' : '. $row['KKAL_NOSAUKUMS'] ;
                  }
                  unset($res);
              }
            }
            break;
         
        case  KL_MATERIALS:

            // set list title
            $title = text::toUpper(text::get('ST_MATERIAL'));     
            // get grupas list           
            $res=dbProc::getWorkTypeListByWork($actId);
            if (is_array($res))
            {
              foreach ($res as $row)
              {
                $workType[$row['KLDV_ID']]=$row['KLDV_NOSAUKUMS'];
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
                $matrGroup[$row['KMAT_GRUPAS_KODS']]=$row['KMAT_GRUPAS_KODS'].' : '.$row['KMAT_GRUPAS_NOSAUKUNS'];
              }
            }
            unset($res);
    
            $matrSubGroup = array();
            $matrGroup['']=text::get('ALL');

            if ($oFormPop->isFormSubmitted() && $oFormPop->getValue('action')==OP_UPDATE && $oFormPop->getValue('mat_sub_group'))
            {
              $res=dbProc::getMaterialBySubGroup($oFormPop->getValue('mat_sub_group'));
              if (is_array($res))
              {
                  foreach ($res as $row)
               	  {
                	    $aScope[$row['KMAT_ID']] = $row['KMAT_KODS'] .' : '. $row['KMAT_NOSAUKUMS'] ;
                  }
                  unset($res);
              }
            }
           
            break;

      }

      // form elements
      $oFormPop -> addElement('hidden', 'action', '');
      $oFormPop -> addElement('hidden', 'actId', '', $actId);
      $oFormPop -> addElement('hidden', 'catalog', '', $catalog);
      $oFormPop -> addElement('multiple_select', 'scope', '', '', (($isReadonly)?' disabled ':'').' size="19" ', '', '', $aScope);
      
      // xmlHttp link
  		$oLink=new urlQuery();
  		$oLink->addPrm(DONT_USE_GLB_TPL, 1);
      $oLink->addPrm(FORM_ID, 'f.akt.s.23');
      
      if($catalog == KL_CALCULALATION )
      {

        $oFormPop -> addElement('kls', 'calc_group',  text::get('SINGL_CALCULATION_GROUP'), 
        array('classifName'=>KL_CALCULALATION_GROUP,'value'=>'','readonly'=>false), 
        'tabindex=1 maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&calc_group=\'+this.value+\'\'))"');
	      
      }
      if($catalog == KL_MATERIALS )
      {
        $oFormPop -> addElement('select', 'mat_group',  text::get('MATERIAL_GROUP'), '', 
        ' tabindex=1 maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&mat_group=\'+this.value+\'\'))"', 
        '', '', $matrGroup);

        $oFormPop -> addElement('select', 'mat_sub_group',  text::get('SUBGROUP_TITLE'), '', 
        ' tabindex=2 maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&mat_sub_group=\'+this.value+\'\'))"', 
        '', '', $matrSubGroup);
      }
      unset($oLink);

      $oFormPop -> addElement('select', 'work_type',  text::get('SINGLE_WORK_TYPE'), '', 'tabindex=2', '', '', $workType);
		  $oFormPop -> addRule('work_type', text::get('ERROR_REQUIRED_FIELD'), 'required');

      // form buttons
      if (!$isReadonly)
      {
        $oFormPop -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMainTab\',\'actId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
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
                                                                      $oFormPop->getValue('work_type'));
                                    break;                          
                                  case  KL_MATERIALS:
                                    $r = dbProc::saveActMaterialRecord($oFormPop->getValue('actId'), 
                                                                      $cValue, 
                                                                      false, false, false,
                                                                      0, '', '',
                                                                      $oFormPop->getValue('work_type')
                                                                    );
                                    break;

                                }
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