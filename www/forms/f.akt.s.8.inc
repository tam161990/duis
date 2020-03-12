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

// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
    $oLink=new urlQuery();
    $oLink->addPrm(FORM_ID, 'f.akt.s.8');
    $oFormPop = new Form('frmMainTab','post',$oLink->getQuery());
    unset($oLink);

    if($actId !== false && $catalog !== false &&
       ( (($catalog == KL_CALCULALATION  && $calcGroup !== false) || $catalog == KL_CALCULALATION_TR) ||
         ($catalog == KL_MATERIALS && $favoritId !== false)) ||
          ($all !== false) )
    {
      // get info about act
      $actInfo = dbProc::getActInfo($actId);
      //print_r($actInfo);
      if(count($actInfo)>0)
      {
      	$act = $actInfo[0];
        $status = $act['RAKT_STATUS'];
        $trase =  $act['RAKT_TRASE'];
      }

      $isReadonly   = true;
      // Ir pieejams mainīšanai, ja  AKTS:LIETOTĀJS = ’Tekošais lietotājs’ un lietotāja loma ir ‘Ievadītais’ un AKTS:STATUS = ‘Izveide’ vai ‘Atgriezts’ vai ‘Tāme’.
      if(($act['RAKT_RLTT_ID'] == $userId && ($isEditor || $isAdmin) && ($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ESTIMATE)) )
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

            // get info about calculation group
            if($all == 1)
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
         case  KL_CALCULALATION_TR:

            // get info about calculation group
           
            if(true/*$all == 1*/)
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
              $res = dbProc::getFreeCalculationList($calcGroup, $actId, 1, $serchText);
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
       
       if($catalog == KL_CALCULALATION OR $catalog == KL_CALCULALATION_TR)
       {
       	$oFormPop->addElement('text', 'searchCode', text::get('TITLE'), $serchText, (($isReadonly)?' disabled ':'').'maxlength="50"');
	 // form buttons
     	 if (!$isReadonly)
      	{
        		$oFormPop -> addElement('submitImg', 'search', text::get('SEARCH'),'img/btn_meklet.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_SEARCH.'\');"');
                 }
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
                            $r = dbProc::saveActWorkRecord($oFormPop->getValue('actId'), $cValue, 0);
                            break;
                          case  KL_CALCULALATION_TR:
                            $r = dbProc::saveActWorkRecord($oFormPop->getValue('actId'), $cValue, 1);
                            break;
                          case  KL_MATERIALS:
                            $r = dbProc::saveActMaterialRecord($oFormPop->getValue('actId'), $cValue);
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
                      switch ($catalog)
                      {
                          case  KL_CALCULALATION:
                          case  KL_CALCULALATION_TR:
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