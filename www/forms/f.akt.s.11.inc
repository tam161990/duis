<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isEDUser = dbProc::isExistsUserRole($userId);
$isSystemUser = $isEDUser || $isEditor;


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

$tame  = reqVar::get('tame');

// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
    $oLink=new urlQuery();
    $oLink->addPrm(FORM_ID, 'f.akt.s.11');
    $oFormPop = new Form('frmMain','post',$oLink->getQuery());
    unset($oLink);

    if($actId !== false && $catalog == KL_MATERIALS )
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
      if((( $act['RAKT_RLTT_ID'] == $userId && $isEditor) || $isAdmin || $isEconomist) && 
      ((($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ESTIMATE) && $tame==0 )|| 
      ($status == STAT_AUTO && $tame==1 ))
      )
      {
        $isReadonly   = false;
      }

      $showResults = false;
      $serchText = '';
      $serchTitle = '';
      $materTitle = '';
      $materId = '';
      $oFormPop -> addElement('hidden', 'searchRow', '');
      $oFormPop -> addElement('hidden', 'action', '');
      $oFormPop -> addElement('hidden', 'actId', '', $actId);
      $oFormPop -> addElement('hidden', 'catalog', '', $catalog);
      $oFormPop -> addElement('hidden', 'st', '', $st);
      $oFormPop->addElement('hidden','maxAmaunt','','1000.00');
      $oFormPop->addElement('hidden','minAmaunt','','0.00');
      $oFormPop -> addElement('hidden', 'isSearch', '', $isSearch);
      $oFormPop -> addElement('hidden', 'searchNum', '', $searchNum);
      $oFormPop->addElement('static','jsRefresh2','','');
      $oFormPop -> addElement('hidden', 'isAuto', '', $isAuto);
      $oFormPop -> addElement('hidden', 'tame', '', $tame);

      $oFormPop->addElement('text', 'searchCode', text::get('CODE'), $serchText, (($isReadonly)?' disabled ':'').'maxlength="7"');

      $oFormPop->addElement('text', 'searchTitle', text::get('NAME'), $serchTitle, (($isReadonly)?' disabled ':'').'maxlength="200"');

     // form buttons
      if (!$isReadonly)
      {
        $oFormPop -> addElement('submitImg', 'search', text::get('SEARCH'),'img/btn_meklet.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')) {setValue(\'action\',\''.OP_SEARCH.'\');} else {return false;}"');
      }
      $oFormPop -> addElement('button', 'close', '', text::get('CLOSE'), 'class="btn70" onclick="javascript:window.close();return false;"; ');

      if ($oFormPop -> isFormSubmitted() && $oFormPop->getValue('action')==OP_UPDATE)
      {
        $r = $oFormPop->getValue('searchRow');
        $isRowValid = true;
        // validate material amount value
        if ($oFormPop->getValue('amount_'.$r) == '')
        {
          // assign error message
          $oFormPop->addErrorPerElem('amount_'.$r, text::get('ERROR_REQUIRED_FIELD'));
          $isRowValid = false;
        }
        // validate material amount value
        elseif (!is_numeric($oFormPop->getValue('amount_'.$r)))
        {
          // assign error message
          $oFormPop->addErrorPerElem('amount_'.$r, text::get('ERROR_DOUBLE_VALUE'));
          $isRowValid = false;
        }
        // validate material amount value
        elseif ($oFormPop->getValue('amount_'.$r) >= 100000)
        {
          // assign error message
          $oFormPop->addErrorPerElem('amount_'.$r, text::get('ERROR_AMOUNT_VALUE'));
          $isRowValid = false;
        }
        if ($oFormPop->getValue('st') == '0')
        {
          // validate material price value
          if ($oFormPop->getValue('price_'.$r) == '')
          {
              // assign error message
              $oFormPop->addErrorPerElem('price_'.$r, text::get('ERROR_REQUIRED_FIELD'));
              $isRowValid = false;
          }
          // validate material price value
          elseif (!is_numeric($oFormPop->getValue('price_'.$r)))
          {
            // assign error message
            $oFormPop->addErrorPerElem('price_'.$r, text::get('ERROR_DOUBLE_VALUE'));
            $isRowValid = false;
          }
            // validate material price value
          elseif ($oFormPop->getValue('price_'.$r) >= 100000)
          {
            // assign error message
            $oFormPop->addErrorPerElem('price_'.$r, text::get('ERROR_AMOUNT_VALUE'));
            $isRowValid = false;
          }
        }
        if($isRowValid === false)
        {
           $showResults = true;
        }

        if($isRowValid)
        {

              $r = dbProc::saveActMaterialRecord($oFormPop->getValue('actId'),
                                                $oFormPop->getValue('id_'.$r),
                                                $oFormPop->getValue('amount_'.$r),
                                                (($oFormPop->getValue('st') == 1 ) ? $oFormPop->getValue('price'.$r) : $oFormPop->getValue('price_'.$r)),
                                                $oFormPop->getValue('tame'),
                                                (($oFormPop->getValue('st') == 1 ) ? 0 : 1));
              if(!$r)
              {
                 $oFormPop->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
              }
              else
              {
                $oRedirectLink=new urlQuery();
                $oRedirectLink->addPrm(FORM_ID, 'f.akt.s.1');
                $oRedirectLink->addPrm('actId', $oFormPop->getValue('actId'));
                $oRedirectLink->addPrm('isSearch', $oFormPop->getValue('isSearch'));
                $oRedirectLink->addPrm('searchNum', $oFormPop->getValue('searchNum'));
                $oRedirectLink->addPrm('tab', TAB_MATERIAL);
                $oRedirectLink->addPrm('tametab', TAB_MATERIAL_T);
                $oRedirectLink->addPrm('isNew', RequestHandler::getMicroTime());
                $oRedirectLink->addPrm('tame', $tame);
                $oRedirectLink->addPrm('tame_mat', $tame);
                $oFormPop -> setNewValue('jsRefresh2', '<script>window.opener.location.replace( "'.$oRedirectLink->getQuery().'" );</script>');
                //requestHandler::makeParentReplace($oRedirectLink->getQuery().'#tab');
                unset($oRedirectLink);


              }
          }
           $serchText = $oFormPop->getValue('searchCode');
                 $serchTitle = $oFormPop->getValue('searchTitle');
                 $resMater = dbProc::getFreeMatByCode($oFormPop->getValue('searchCode'), $oFormPop->getValue('actId'), $oFormPop->getValue('searchTitle'));

                 if(is_array($resMater) && count($resMater) > 0)
                 {
                    $showResults = true;

                 }
                 else
                 {
                   $oFormPop->addError(text::get('NO_SEARCH_RESULTS'));
                 }
      }


      if ($oFormPop -> isFormSubmitted() && $oFormPop->getValue('action')==OP_SEARCH &&
      ($oFormPop->getValue('searchCode') != '' || $oFormPop->getValue('searchTitle') != ''))
      {
         $serchText = $oFormPop->getValue('searchCode');
         $serchTitle = $oFormPop->getValue('searchTitle');
         $resMater = dbProc::getFreeMatByCode($oFormPop->getValue('searchCode'), $oFormPop->getValue('actId'), $oFormPop->getValue('searchTitle'));

         if(is_array($resMater) && count($resMater) > 0)
         {
            $showResults = true;
         }
         else
         {
           $oFormPop->addError(text::get('NO_SEARCH_RESULTS'));
         }
      }



      if($showResults && isset($resMater))
      {
        for ($j = 0; $j < count($resMater); $j++)
        {
          $oFormPop->addElement('label', 'title_'.$j, '', '');
          $oFormPop->addElement('hidden', 'id_'.$j, '', '');
          $oFormPop->addElement('hidden', 'price'.$j, '', '');
          if($oFormPop->getValue('action')==OP_UPDATE )
          {
                $oFormPop->addElement('text', 'amount_'.$j, '', '', (($isReadonly)?' disabled ':'').'maxlength="6"');       
                $oFormPop->addElement('text', 'price_'.$j, '', '', (($isReadonly || $st == 1)?' disabled ':'').'maxlength="6"');
                $oFormPop -> setNewValue('amount_'.$j,'');
                $oFormPop -> setNewValue('price_'.$j, '');
          }
          else
          {
            $oFormPop->addElement('text', 'amount_'.$j, '', '', (($isReadonly)?' disabled ':'').'maxlength="6"'); 
            $oFormPop->addElement('text', 'price_'.$j, '', '', (($isReadonly || $st == 1)?' disabled ':'').'maxlength="6"');  
            
          }

          // form buttons
          if (!$isReadonly)
          {
            $oFormPop -> addElement('submitImg', 'save_'.$j, text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onClick="if (!isEmptyFormField(\'frmMain\',\'actId\')) {setValue(\'action\',\''.OP_UPDATE.'\'); setValue(\'searchRow\',\''.$j.'\');} else {return false;}"');
          }
        }
      }

      if ($oFormPop -> isFormSubmitted())
      {
        
       // if($oFormPop->getValue('action')==OP_SEARCH)
       // {
          for ($j = 0; $j < count($resMater); $j++)
          {
            $oFormPop -> setNewValue('title_'.$j, $resMater[$j]['KMAT_KODS'] .' : '. $resMater[$j]['KMAT_NOSAUKUMS'].' : '. $resMater[$j]['KMAT_DAUDZUMS'].' '.$resMater[$j]['KMAT_MERVIENIBA'] );
            $oFormPop -> setNewValue('id_'.$j, $resMater[$j]['KMAT_ID']);
            $oFormPop -> setNewValue('price'.$j, $resMater[$j]['KMAT_CENA']);
            if($isEDUser || $isAdmin)
            {
                $oFormPop -> setNewValue('price_'.$j, $resMater[$j]['KMAT_CENA']);
            }           

          }
       // }

      }
      $title = text::toUpper(text::get(TAB_MATERIAL).'/'.text::get('SEARCH'));
      $oFormPop -> makeHtml();
      include('f.akt.s.11.tpl');
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