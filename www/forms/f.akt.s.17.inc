<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);

// act ID
$actId  = reqVar::get('actId');
// numPostfix
$numPostfix  = reqVar::get('numPostfix');
// TRASE act
$trase =  reqVar::get('isTrase');
$toid = reqVar::get('toid');
if($trase === false) $trase = 0;

// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isEconomist)
{
    $oLink=new urlQuery();
    $oLink->addPrm(FORM_ID, 'f.akt.s.17');
    $oFormPop = new Form('frmMainTab','post',$oLink->getQuery());
    unset($oLink);

    if($actId !== false )
    {
      // get info about act
      $actInfo = dbProc::getActInfo($actId);
      //print_r($actInfo);
      if(count($actInfo)>0)
      {
      	$act = $actInfo[0];
         $proces_date = $act['RAKT_IZPILDES_DATUMS'];
         $month = $act['RAKT_MENESIS'];
         $year = $act['RAKT_GADS'];
      }
      $isReadonly   = true;
      // Ir pieejams mainīšanai, ja  AKTS:LIETOTĀJS = ’Tekošais lietotājs’ un lietotāja loma ir ‘Ievadītais’ un AKTS:STATUS = ‘Izveide’ vai ‘Atgriezts’ vai ‘Tāme’.
     if($isAdmin || $isEconomist )
      {
        $isReadonly   = false;
      }

      $masterName = dbProc::GetMasterName($act['RAKT_KEDI_ID'], 'MASTER');      
      $engeneerName = dbProc::GetEngineerName($act['RAKT_KEDI_ID'], 'ENGINEER');
      $depChifName = dbProc::GetEngineerName($act['RAKT_KEDI_ID'], 'DEPARTMENT_CHIF');
      $departmentName = dbProc::GetDepartmentName($act['RAKT_KEDI_ID']);

      $rows=dbProc::getUserInfo($userId);

      if (count($rows)==1)
      {
        $actAutorName =  $rows[0]['RLTT_VARDS'].' '.$rows[0]['RLTT_UZVARDS'];
      }



      // form elements
      $oFormPop -> addElement('hidden', 'actId', '', $actId);
      $oFormPop -> addElement('hidden', 'isTrase', '', $trase);
      $oFormPop -> addElement('hidden', 'proces_date', '', $proces_date);
      $oFormPop -> addElement('hidden', 'numPostfix', '', $numPostfix);
      $oFormPop -> addElement('hidden', 'toid', '', $toid);

      $oFormPop -> addElement('text', 'master',  text::get('SIGN_MASTER'), $masterName, 'maxlength="300"'.(($isReadonly)?' disabled':''));
      $oFormPop -> addRule('master', text::get('ERROR_REQUIRED_FIELD'), 'required');

      $oFormPop -> addElement('text', 'engineer',  text::get('SIGN_ENGENEER'), $engeneerName, 'maxlength="300"'.(($isReadonly)?' disabled':''));
      $oFormPop -> addRule('engineer', text::get('ERROR_REQUIRED_FIELD'), 'required');

      //datums
      $oFormPop -> addElement('date', 'start_date',  text::get('DATE'), dtime::now(), 'maxlength="10"');
      $oFormPop -> addRule('start_date', text::get('ERROR_INCORRECT_DATE'),'validatedate');



      // form buttons
      if (!$isReadonly)
      {
        $oFormPop -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_apstiprinat.gif', 'width="70" height="20" ');
      }
      $oFormPop -> addElement('button', 'close', '', text::get('CLOSE'), 'class="btn70" onclick="javascript:window.close();return false;"; ');

      if ($oFormPop -> isFormSubmitted())
      {
            $checkRequiredFields = false;
            $r = true;

            if($oFormPop -> getValue('master') &&  $oFormPop -> getValue('engineer'))
            {
                $checkRequiredFields = true;
            }

            if(!$checkRequiredFields)
            {
                $oFormPop->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
            }
            else
            {
                  $r=dbProc::saveAct($oFormPop->getValue('actId'),
    		    			false,
                            false,
                            $oFormPop->getValue('proces_date'),
                            false,                    
                            false,
                            false,
                            false,
                            STAT_CLOSE,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            false,
                            $oFormPop->getValue('numPostfix'),
                            false,
                            false,
                            $oFormPop->getValue('start_date'),                            
                           $oFormPop->getValue('toid')
    					);
                if($r)
                {
                  $idFile = toPdf::approvedTrasePdf($actId, 
                                          $userId, 
                                          FILE_ESTIMATE,
                                          $oFormPop -> getValue('master'), 
                                          $oFormPop -> getValue('engineer'),
                                          $oFormPop -> getValue('start_date'));
                  
                  if ($idFile!==false)
		            {
                        //$pdf->Output(FILES_STORE_PATH."/".$idFile, 'F');
                        // save status changed time
                        $r1 = dbProc::saveAuditRecord($actId, $userId,  STAT_CLOSE);
                        dbProc::setUserActionDate($userId,  ACT_CLOSE);

                        if (!$r1)
                        {
                              $oFormPop->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                        }

                        // delete all files before
                        $r1 = dbProc::deleteFilesFromAct($actId, $idFile, FILE_ESTIMATE);
                        if (!$r1)
                        {
                              $oFormPop->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                        }
                    }
                    

                }
                else
                {
                   $oFormPop->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                }


               if($r && $r1)
                {
                  $oRedirectLink=new urlQuery();
                  $oRedirectLink->addPrm(FORM_ID, 'f.akt.s.1');
                  $oRedirectLink->addPrm('actId', $oFormPop->getValue('actId'));
                  $oRedirectLink->addPrm('isTrase', $oFormPop->getValue('isTrase'));
                  $oRedirectLink->addPrm('tab', TAB_ESTIMATE);

                  $oRedirectLink->addPrm('isNew', RequestHandler::getMicroTime());
                  requestHandler::makeParentReplace($oRedirectLink->getQuery().'#tab');
                  unset($oRedirectLink);
               }
            }


      }

      $oFormPop -> makeHtml();
      include('f.akt.s.17.tpl');
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