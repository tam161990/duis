<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;

// act ID
$actId  = reqVar::get('actId');
// catalog
$catalog  = reqVar::get('catalog');
// calculation group code
$calcGroup  = reqVar::get('calcGroup');

// region
$region  = reqVar::get('region');
// all personal
$all  = reqVar::get('all');
// search form
$isSearch  = reqVar::get('isSearch');
// search act by number
$searchNum  = reqVar::get('searchNum');

// TRASE act
$trase =  reqVar::get('isTrase');
if($trase === false) $trase = 0;

$tame  = reqVar::get('tame');
$estimate  = reqVar::get('estimate');

// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
    $oLink=new urlQuery();
    $oLink->addPrm(FORM_ID, 'f.akt.s.8');
    $oFormPop = new Form('frmMainTab','post',$oLink->getQuery());
    unset($oLink);

    if( $actId !== false && $catalog !== false &&
       ( ($catalog == KL_CALCULALATION  && ($calcGroup !== false|| $trase || $estimate == 1 )) ||
         ($catalog == KL_MATERIALS && $favoritId !== false) ||
          ($all !== false) 
        ))
    {
      // get info about act
      $actInfo = dbProc::getActInfo($actId);
      //print_r($actInfo);
      if(count($actInfo)>0)
      {
      	$act = $actInfo[0];
        $status = $act['RAKT_STATUS'];
        $trase =  $act['RAKT_TRASE'];
        $isAuto = $act['RAKT_IS_AUTO'];
      }

      $isReadonly   = true;
      // Ir pieejams mainīšanai, ja  AKTS:LIETOTĀJS = ’Tekošais lietotājs’ un lietotāja loma ir ‘Ievadītais’ un AKTS:STATUS = ‘Izveide’ vai ‘Atgriezts’ vai ‘Tāme’.
      if((( $act['RAKT_RLTT_ID'] == $userId && $isEditor) || $isAdmin || $isEconomist) && 
      ($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ESTIMATE || ($status == STAT_AUTO && $tame==1 ) )
      )
      {
        $isReadonly   = false;
      }
       
      $aScope=array();
      $aScope['-1']='';
      $serchText = '';

      if ($oFormPop -> isFormSubmitted() && $oFormPop->getValue('action')==OP_SEARCH )
      {
	              $serchText = $oFormPop->getValue('searchCode');
                unset($aScope);
	              $aScope=array();
      	        $aScope['-1']='';
      }


      switch ($catalog)
      {
        case  KL_CALCULALATION:
          
            if($estimate == 1) {
              // set list title
              $title = strtoupper(text::get(TAB_ESTIMATE)). ' ' .text::get(TAB_WORKS_T);
              // get calculation from estimate
              $res = dbProc::getEstimatedCalculation($actId);
              if (is_array($res))
              {
                  foreach ($res as $row)
               	  {
                	   $aScope[$row['KKAL_ID']] = $row['KKAL_SHIFRS'] .' : '. $row['KKAL_NOSAUKUMS'] .' ('.$row['KKAL_NORMATIVS'].')';
                  }
              }
              unset($res);
              $oFormPop -> addElement('hidden', 'estimate', '', $estimate);
            }
	   elseif($trase)
           {
          
              // set list title
              $title = text::toUpper(text::get('TRASE_WORK'));
              // get calculation by calculation group code
              $res = dbProc::getALLCalculationList($actId, 1, $serchText);
              if (is_array($res))
              {
                foreach ($res as $row)
                {
                      $aScope[$row['KKAL_ID']] = $row['KKAL_SHIFRS'] .' : '. $row['KKAL_NOSAUKUMS'] .' ('.$row['KKAL_NORMATIVS'].')';
                }
              }
              unset($res);
              $oFormPop -> addElement('hidden', 'all', '', $all);
            }
            // get info about calculation group
            elseif($all == 1)
            {

              // set list title
              $title = text::toUpper(text::get('ALL_WORK'));
              // get calculation by calculation group code
              $res = dbProc::getALLCalculationList($actId, 0, $serchText);
              if (is_array($res))
              {
                  foreach ($res as $row)
               	{
                	    $aScope[$row['KKAL_ID']] = $row['KKAL_SHIFRS'] .' : '. $row['KKAL_NOSAUKUMS'] .' ('.$row['KKAL_NORMATIVS'].')';
                  }
              }
              unset($res);
              $oFormPop -> addElement('hidden', 'all', '', $all);
            }
            else
            {
              $calcGrInfo = dbProc::getCalculationGroupInfo($calcGroup);
              if(count($calcGrInfo)>0)
              {
              	$group = $calcGrInfo[0];
                $groupTitle = $group['KKLG_NOSAUKUMS'];
              }
              // set list title
              $title = text::toUpper($groupTitle);
              // get calculation by calculation group code
              $res = dbProc::getFreeCalculationList($calcGroup, $actId, 0, $serchText);
              if (is_array($res))
              {
                  foreach ($res as $row)
               	{
                	    $aScope[$row['KKAL_ID']] = $row['KKAL_SHIFRS'] .' : '. $row['KKAL_NOSAUKUMS'] .' ('.$row['KKAL_NORMATIVS'].')';
                  }
              }
              unset($res);
              $oFormPop -> addElement('hidden', 'calcGroup', '', $calcGroup);
            }
            break;
        case  KL_MATERIALS:


            // set list title
            $title = text::toUpper($favoritTitle);
            // get material by favorit ID
            $res = dbProc::getFreeMatFavoritList($favoritId, $actId);
            if (is_array($res))
            {
                foreach ($res as $row)
             	{
              	    $aScope[$row['KMAT_ID']] = $row['KMAT_KODS'] .' : '. $row['KMAT_NOSAUKUMS'].' : '. $row['KMAT_DAUDZUMS'].' '.$row['KMAT_MERVIENIBA'] .' : '.$row['KMAT_CENA'].' EUR';
                }
            }
            unset($res);
            $oFormPop -> addElement('hidden', 'favoritId', '', $favoritId);
            break;

      }

      // form elements
      $oFormPop -> addElement('hidden', 'action', '');
      $oFormPop -> addElement('hidden', 'actId', '', $actId);
      $oFormPop -> addElement('hidden', 'isTrase', '', $trase);
      $oFormPop -> addElement('hidden', 'catalog', '', $catalog);
      $oFormPop -> addElement('hidden', 'isSearch', '', $isSearch);
      $oFormPop -> addElement('hidden', 'searchNum', '', $searchNum);
      $oFormPop -> addElement('multiple_select', 'scope', '', '', (($isReadonly)?' disabled ':'').' size="19" ', '', '', $aScope);
      $oFormPop -> addElement('hidden', 'isAuto', '', $isAuto);
      $oFormPop -> addElement('hidden', 'tame', '', $tame);

      if($catalog == KL_CALCULALATION)
      {
       	$oFormPop->addElement('text', 'searchCode', text::get('TITLE'), $serchText, (($isReadonly)?' disabled ':'').'maxlength="50"');
	      // form buttons
     	 if (!$isReadonly)
      	{
        		$oFormPop -> addElement('submitImg', 'search', text::get('SEARCH'),'img/btn_meklet.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_SEARCH.'\');"');
        }
      }
      if($catalog == KL_CALCULALATION )
      {
        //datums
       $oFormPop -> addElement('date', 'plan_date',  text::get('FINISHING_DATE'), dtime::now(), (($isReadonly)?' disabled ':''));
       $oFormPop -> addRule('plan_date', text::get('ERROR_REQUIRED_FIELD'), 'required');
       $oFormPop -> addRule('plan_date', text::get('ERROR_INCORRECT_DATE'),'validatedate');

     }
     else {
       $oFormPop -> addElement('select', 'plan_date',  text::get('FINISHING_DATE'), '', (($isReadonly)?' disabled ':'').' ', '','', $days);
       $oFormPop -> addRule('plan_date', text::get('ERROR_REQUIRED_FIELD'), 'required');
     }


      // form buttons
      if (!$isReadonly)
      {
        $oFormPop -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMainTab\',\'actId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
      }
    
      $oFormPop -> addElement('button', 'close', '', text::get('CLOSE'), 'class="btn70" onclick="javascript:window.close();return false;"; ');

      if ($oFormPop -> isFormSubmitted() AND $oFormPop->getValue('action')==OP_UPDATE)
      {
            $checkRequiredFields = false;
            $r = true;
            $aListScope = $oFormPop->getValue('scope');
            if (is_array($aListScope))
			{

				foreach ($aListScope as $cValue)
			    {
					if ($cValue>0)
					{
                        switch ($catalog)
                        {
                          case  KL_CALCULALATION:
                            $r = dbProc::saveActWorkRecord($oFormPop->getValue('actId'), $cValue, $trase, $tame, $oFormPop->getValue('plan_date'));
                            break;                         
                          case  KL_MATERIALS:
                            $r = dbProc::saveActMaterialRecord($oFormPop->getValue('actId'), $cValue, false, false, $tame);
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
                      $oRedirectLink->addPrm(FORM_ID, 'f.akt.s.1');
                      $oRedirectLink->addPrm('actId', $oFormPop->getValue('actId'));
                      $oRedirectLink->addPrm('isTrase', $oFormPop->getValue('isTrase'));
                      $oRedirectLink->addPrm('isSearch', $oFormPop->getValue('isSearch'));
                      $oRedirectLink->addPrm('searchNum', $oFormPop->getValue('searchNum'));
                      $oRedirectLink->addPrm('tame', $tame);
                      $oRedirectLink->addPrm('tame_mat', $tame);
                      switch ($catalog)
                      {
                        case  KL_CALCULALATION:
                          $oRedirectLink->addPrm('tab', TAB_WORKS);
                          $oRedirectLink->addPrm('tametab', strtoupper(text::get(TAB_ESTIMATE)). ' ' .TAB_WORKS_T);
                          break;
                        case  KL_MATERIALS:
                          $oRedirectLink->addPrm('tab', TAB_MATERIAL);
                          $oRedirectLink->addPrm('tametab', TAB_MATERIAL_T);
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
      include('f.akt.s.8.tpl');
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