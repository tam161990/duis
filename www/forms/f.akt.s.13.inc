<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isEDUser = dbProc::isExistsUserRole($userId);
$isSystemUser = $isEDUser || $isEditor;
$isProjector = dbProc::isExistsUserRoleWithProject($userId)  ;

// act ID
$actId  = reqVar::get('actId');
// catalog
$catalog  = reqVar::get('catalog');
// all material
$st  = reqVar::get('st');
// search form
$isSearch  = reqVar::get('isSearch');
// search act by number
$searchNum  = reqVar::get('searchNum');
// pievienošana projektētajiem
$isProject  = reqVar::get('isProject');

$tame  = reqVar::get('tame');

// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
    $oLink=new urlQuery();
    $oLink->addPrm(FORM_ID, 'f.akt.s.13');
    $oLink->addPrm('catalog', $catalog);
    $oFormPop = new Form('frmMain','post',$oLink->getQuery());
    unset($oLink);

    if($actId !== false &&  ($catalog == KL_CALCULALATION  || $catalog == KL_MATERIALS)  )
    {
      // get info about act
      $actInfo = dbProc::getActInfo($actId);
      //print_r($actInfo);
      if(count($actInfo)>0)
      {
      	$act = $actInfo[0];
         $status = $act['RAKT_STATUS'];
         $isAuto = $act['RAKT_IS_AUTO'];
      }

      $isReadonly   = true;
      // Ir pieejams mainīšanai, ja  AKTS:LIETOTĀJS = ’Tekošais lietotājs’ un lietotāja loma ir ‘Ievadītais’ un AKTS:STATUS = ‘Izveide’ vai ‘Atgriezts’ vai ‘Tāme’.
      if((( $act['RAKT_RLTT_ID'] == $userId && ($isEditor || $isProjector)) || $isAdmin || $isEconomist) && 
        ((($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ESTIMATE) && $tame==0 )|| 
        ($status == STAT_AUTO && $tame==1 ))
      )
      {
        $isReadonly   = false;
      }

      // get meassured list
      $meassure = array();
      $meassure['gab']='gab';
      $meassure['iep']='iep';
      $meassure['kg']='kg';
      $meassure['kom']='kom';
      $meassure['l']='l';
      $meassure['m']='m';
      $meassure['m2']='m2';
      $meassure['m3']='m3';
      $meassure['mai']='mai';
      $meassure['pac']='pac';
      $meassure['pak']='pak';
      $meassure['par']='par';
      $meassure['t']='t';
      $meassure['objekts']='objekts';
      

      if($isProject == 1) {
         // get grupas list
         $workType=array();
         $workType['']=text::get('EMPTY_SELECT_OPTION');		
         switch ($catalog )
         {
         case  KL_CALCULALATION:
               // get grupas list           
               $res=dbProc::getWorkTypeList();    
               // get grupas nokluseto vertibu 
               $defaultWork = explode('^', dbProc::getDefaultWork($actId));    
               if (is_array($res))
               {
                  foreach ($res as $row)
                  {
                     $workType[$row['KLDV_ID']]=$row['KLDV_NOSAUKUMS'];
                  }
               }
         unset($res); 
               break;         
            case  KL_MATERIALS: 
               // get grupas list             
               $res=dbProc::getWorkTypeListByWork($actId);  
               // get grupas nokluseto vertibu 
               $defaultMaterial = dbProc::getDefaultMaterial($actId);  
               if (is_array($res))
               {
                  foreach ($res as $row)
                  {
                     $workType[$row['KLDV_ID'].'^'.(isset($row['DRBI_WORK_TYPE_TEXT'])? str_replace('"', '\'', $row['DRBI_WORK_TYPE_TEXT']) : 'X')] =$row['KLDV_NOSAUKUMS'].' '.$row['DRBI_WORK_TYPE_TEXT'];
                  }
               }
         unset($res);
               break;
         }
         
      }

      $oFormPop -> addElement('hidden', 'action', '');
      $oFormPop -> addElement('hidden', 'actId', '', $actId);
      $oFormPop -> addElement('hidden', 'catalog', '', $catalog);
      $oFormPop -> addElement('hidden', 'st', '', $st);
      $oFormPop->addElement('hidden','maxAmaunt','','1000.00');
      $oFormPop->addElement('hidden','minAmaunt','','0.00');
      $oFormPop->addElement('static','jsRefresh2','','');
      $oFormPop -> addElement('hidden', 'isAuto', '', $isAuto);
      $oFormPop -> addElement('hidden', 'tame', '', $tame);
      $oFormPop -> addElement('hidden', 'isProject', '', $isProject);

      // form buttons
      $oFormPop -> addElement('button', 'close', '', text::get('CLOSE'), 'class="btn70" onclick="javascript:window.close();return false;"; ');
      if ($oFormPop -> isFormSubmitted() && $oFormPop->getValue('action')==OP_UPDATE)
      {
         $isRowValid = true;
         // validate material amount value
         if ($oFormPop->getValue('amount') == '')
         {
            // assign error message
            $oFormPop->addErrorPerElem('amount', text::get('ERROR_REQUIRED_FIELD'));
            $isRowValid = false;
         }
         // validate material amount value
         elseif (!is_numeric($oFormPop->getValue('amount')))
         {
            // assign error message
            $oFormPop->addErrorPerElem('amount', text::get('ERROR_DOUBLE_VALUE'));
            $isRowValid = false;
         }
        // validate material amount value
         elseif ($oFormPop->getValue('amount') >= 100000)
         {
            // assign error message
            $oFormPop->addErrorPerElem('amount', text::get('ERROR_AMOUNT_VALUE'));
            $isRowValid = false;
         }
        if ($oFormPop->getValue('st') == '0')
        {
            // validate material price value
            if ($oFormPop->getValue('title') == '')
            {
               // assign error message
               $oFormPop->addErrorPerElem('title', text::get('ERROR_REQUIRED_FIELD'));
               $isRowValid = false;
            }
            // validate material price value
            if ($oFormPop->getValue('mervieniba') == '')
            {
               // assign error message
               $oFormPop->addErrorPerElem('mervieniba', text::get('ERROR_REQUIRED_FIELD'));
               $isRowValid = false;
            }
            if($isProject != 1) {
               // validate material price value
               if ($oFormPop->getValue('price') == '')
               {
                  // assign error message
                  $oFormPop->addErrorPerElem('price', text::get('ERROR_REQUIRED_FIELD'));
                  $isRowValid = false;
               }
               // validate material price value
               elseif (!is_numeric($oFormPop->getValue('price')))
               {
                  // assign error message
                  $oFormPop->addErrorPerElem('price', text::get('ERROR_DOUBLE_VALUE'));
                  $isRowValid = false;
               }
               // validate material price value
               elseif ($oFormPop->getValue('price') >= 100000)
               {
                  // assign error message
                  $oFormPop->addErrorPerElem('price', text::get('ERROR_AMOUNT_VALUE'));
                  $isRowValid = false;
               }
            } else {

               if ($oFormPop->getValue('work_type') == '')
               {
                  // assign error message
                  $oFormPop->addErrorPerElem('work_type', text::get('ERROR_REQUIRED_FIELD'));
                  $isRowValid = false;
               }
            }
        }
        if($isRowValid === false)
        {
           echo 'invalid';
        }

        if($isRowValid)
        {
            switch ($catalog)
            {
               case  KL_CALCULALATION:
                  
                     // set list title
                     $r = dbProc::saveActWorkFreeRecord($oFormPop->getValue('actId'),
                                                   false,
                                                   $oFormPop->getValue('amount'),
                                                   false,
                                                   $oFormPop->getValue('tame'),
                                                   (($oFormPop->getValue('st') == 1 ) ? 0 : 1),
                                                   $oFormPop->getValue('title'),
                                                   $oFormPop->getValue('mervieniba'),
                                                   ($isProject == 1) ? $oFormPop->getValue('work_type'): false,
                                                   ($isProject == 1) ? $oFormPop->getValue('work_type_text'): false
                                                );
                     break;         
               case  KL_MATERIALS: 
                  // set list title             
                  $r = dbProc::saveActMaterialRecord($oFormPop->getValue('actId'),
                                                false,
                                                $oFormPop->getValue('amount'),
                                                ($isProject == 1) ? false : $oFormPop->getValue('price'),
                                                $oFormPop->getValue('tame'),
                                                (($oFormPop->getValue('st') == 1 ) ? 0 : 1),
                                                $oFormPop->getValue('title'),
                                                $oFormPop->getValue('mervieniba'),
                                                ($isProject == 1) ? $oFormPop->getValue('work_type'): false
                                             ); 
                  break;
               }
              
              if(!$r)
              {
                 $oFormPop->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
              }
              else
              {
                  $oRedirectLink=new urlQuery();
                  $oRedirectLink->addPrm('actId', $oFormPop->getValue('actId'));
                  $oRedirectLink->addPrm('isSearch', $oFormPop->getValue('isSearch'));
                  $oRedirectLink->addPrm('searchNum', $oFormPop->getValue('searchNum'));
                  $oRedirectLink->addPrm('tame', $tame);

                  if($isProject == 1) {
                     $oRedirectLink->addPrm(FORM_ID, 'f.akt.s.20');
                  } else {
                     $oRedirectLink->addPrm(FORM_ID, 'f.akt.s.1');
                  }
                  
                  switch ($catalog)
                  {
                     case  KL_CALCULALATION:
                        $oRedirectLink->addPrm('tab', TAB_WORKS);
                        if($isProject == 1) {
                           $oRedirectLink->addPrm('tametab', TAB_WORKS_T);
                        } 
                        break;         
                     case  KL_MATERIALS: 
                        $oRedirectLink->addPrm('tab', TAB_MATERIAL);
                        if($isProject == 1) {
                           $oRedirectLink->addPrm('tametab', TAB_MATERIAL_T);
                        } 
                        break;
                  }
                
                  $oRedirectLink->addPrm('isNew', RequestHandler::getMicroTime());
                  $oFormPop -> setNewValue('jsRefresh2', '<script>window.opener.location.replace( "'.$oRedirectLink->getQuery().'" );</script>');

                  unset($oRedirectLink);

              }
          }

      }

      $oFormPop->addElement('text', 'title', '', '',(($isReadonly)?' disabled ':'').'maxlength="250"');
      //$oFormPop->addElement('text', 'mervieniba', '', '',(($isReadonly)?' disabled ':'').'maxlength="15"');
      $oFormPop -> addElement('select', 'mervieniba',  '', '', (($isReadonly)?' disabled ':''), '', '',$meassure);
      $oFormPop->addElement('text', 'amount', '', '', (($isReadonly)?' disabled ':'').'maxlength="6"'); 
      $oFormPop->addElement('text', 'price', '', '', (($isReadonly || $st == 1)?' disabled ':'').'maxlength="6"');
      if($isProject == 1) {
         $oFormPop -> addElement('select', 'work_type',  text::get('SINGLE_WORK_TYPE'), (($catalog == KL_CALCULALATION) ? $defaultWork[0] : $defaultMaterial), 'tabindex=2', '', '', $workType);
         $oFormPop -> addRule('work_type', text::get('ERROR_REQUIRED_FIELD'), 'required');
         if($catalog == KL_CALCULALATION )
         { 
            $oFormPop->addElement('text', 'work_type_text', text::get('PROJECT_OBJECT_TITLE'), isset($defaultWork[1]) ? $defaultWork[1] : '', 'maxlength="50" tabindex=3');
         }

      } 
      // form buttons
      if (!$isReadonly)
      {
        $oFormPop -> addRule('title', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oFormPop -> addRule('mervieniba', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oFormPop -> addRule('amount', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oFormPop -> addRule('price', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oFormPop -> addRule('amount', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);
        $oFormPop -> addRule('price', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);

        $oFormPop -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
      }

      switch ($catalog)
      {
        case  KL_CALCULALATION:
            // set list title
            $title = text::toUpper(text::get('TAB_WORKS'));     
            break;         
         case  KL_MATERIALS: 
             // set list title             
             $title = text::toUpper(text::get('TAB_MATERIAL'));     
            break;
      }
      
      $oFormPop -> makeHtml();
      include('f.akt.s.13.tpl');
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