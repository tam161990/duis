<?
// RBF Acts - Add Work Popup (based on f.akt.s.8 KL_CALCULALATION part)
$userId = userAuthorization::getUserId();
$isAdmin = userAuthorization::isAdmin();
$isRbfUser = userAuthorization::isRbfUser();
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);

// act ID
$actId = reqVar::get('actId');
// all work catalog
$all = reqVar::get('all');
// search form
$isSearch = reqVar::get('isSearch');
// search act by number
$searchNum = reqVar::get('searchNum');

// Only admins, RBF users, and economists have access
if ($isAdmin || $isRbfUser || $isEconomist)
{
    $oLink = new urlQuery();
    $oLink->addPrm(FORM_ID, 'f.akt.s.33');
    $oFormPop = new Form('frmRbfWorkPop', 'post', $oLink->getQuery());
    unset($oLink);

    if($actId !== false && $all !== false)
    {
      // Get info about act
      $act = array();
      $status = false;
      $actInfo = dbProc::getActInfo($actId);
      if(count($actInfo) > 0)
      {
          $act = $actInfo[0];
          $status = $act['RAKT_STATUS'];
      }

      $isReadonly = true;
      // Edit access: if act is in "Ievads" (INSERT) or "Atgriezts" (RETURN) status and user is the author or admin
      if((($act['RAKT_RLTT_ID'] == $userId && $isRbfUser) || $isAdmin) && 
        ($status == STAT_INSERT || $status == STAT_RETURN))
      {
        $isReadonly = false;
      }

      $aScope = array();
      $aScope['-1'] = '';
      $searchText = '';

      if ($oFormPop->isFormSubmitted() && $oFormPop->getValue('action') == OP_SEARCH)
      {
          $searchText = $oFormPop->getValue('searchCode');
          unset($aScope);
          $aScope = array();
          $aScope['-1'] = '';
      }

      // Set list title
      $title = text::get('ALL_WORK');

      // Get calculation list from RBF calculation table
      $vvNumber = $act['RAKT_VV_NUMBER'];
      $employeeCode = $act['RAKT_KWOI_KODS'];
      
      $res = dbProc::getRbfCalculationListForAct($vvNumber, $employeeCode, $searchText);

      if (is_array($res) && count($res) > 0)
      {
          foreach ($res as $row)
          {
             $aScope[$row['RBKL_ID']] = $row['RBKL_SHIFRS'] .' : '. $row['RBKL_NOSAUKUMS'] .' ('.$row['RBKL_CENA'].')';
          }
      }
      unset($res);

      // Form elements
      $oFormPop->addElement('hidden', 'action', '');
      $oFormPop->addElement('hidden', 'actId', '', $actId);
      $oFormPop->addElement('hidden', 'all', '', $all);
      $oFormPop->addElement('hidden', 'isSearch', '', $isSearch);
      $oFormPop->addElement('hidden', 'searchNum', '', $searchNum);

      // Search field
      $oFormPop->addElement('text', 'searchCode', text::get('TITLE'), $searchText, (($isReadonly)?' disabled ':'').'maxlength="50"');
      
      // Search button
      if (!$isReadonly)
      {
          $oFormPop->addElement('submitImg', 'search', text::get('SEARCH'),'img/btn_meklet.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_SEARCH.'\');"');
      }

      // Multiple select for calculations
      $oFormPop->addElement('multiple_select', 'scope', '', '', (($isReadonly)?' disabled ':'').' size="19" ', '', '', $aScope);

      // Plan date field
      $oFormPop->addElement('date', 'plan_date', text::get('FINISHING_DATE'), dtime::now(), (($isReadonly)?' disabled ':''));
      $oFormPop->addRule('plan_date', text::get('ERROR_REQUIRED_FIELD'), 'required');
      $oFormPop->addRule('plan_date', text::get('ERROR_INCORRECT_DATE'),'validatedate');

      // Save button
      if (!$isReadonly)
      {
        $oFormPop->addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmRbfWorkPop\',\'actId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
      }

      // Close button
      $oFormPop->addElement('button', 'close', '', text::get('CLOSE'), 'class="btn70" onclick="javascript:window.close();return false;"; ');

      // Form is submitted - add selected calculations to act
      if ($oFormPop->isFormSubmitted() && $oFormPop->getValue('action') == OP_UPDATE)
      {
          $checkRequiredFields = false;
          $r = true;
          $aListScope = $oFormPop->getValue('scope');
          
          if (is_array($aListScope))
          {
              foreach ($aListScope as $cValue)
              {
                  if ($cValue > 0)
                  {
                      $r = dbProc::saveRbfActWorkRecord($actId, $cValue, $oFormPop->getValue('plan_date'));
                      
                      if(!$r)
                      {
                          $oFormPop->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                          break;
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
                      // Redirect parent window to works tab
                      $oRedirectLink = new urlQuery();
                      $oRedirectLink->addPrm(FORM_ID, 'f.akt.s.30');
                      $oRedirectLink->addPrm('actId', $actId);
                      $oRedirectLink->addPrm('tab', 'RBF_WORKS');
                      $oRedirectLink->addPrm('isSearch', $isSearch);
                      $oRedirectLink->addPrm('searchNum', $searchNum);
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

      // Render the form
      $oFormPop->makeHtml();

      // Include the template
      include('f.akt.s.33.tpl');
    }
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
