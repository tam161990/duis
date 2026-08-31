<?
// RBF Acts - Works Tab (simplified version of f.akt.s.2)
$userId = userAuthorization::getUserId();
$isAdmin = userAuthorization::isAdmin();
$isRbfUser = userAuthorization::isRbfUser();
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);

// act ID
$actId  = reqVar::get('actId');
// search form
$isSearch  = reqVar::get('isSearch');
// search act by number
$searchNum  = reqVar::get('searchNum');

// Main form with XMLHTTP method load this code:
if (reqVar::get('xmlHttp') == 1)
{
    // if operation is DELETE, delete record from DB
    if (reqVar::get('deleteId') != '')
    {
       dbProc::deleteActWorkRecord(reqVar::get('deleteId'), 0); // tame=0 for RBF acts
    ?>
        rowNode = this.parentNode.parentNode;
        rowNode.parentNode.removeChild(rowNode);
    <?
    }
    exit();
}

// Only admins and RBF users have access
if ($isAdmin || $isRbfUser || $isEconomist)
{
    if($actId !== false)
    {
      $oLink = new urlQuery();
      $oLink->addPrm(FORM_ID, 'f.akt.s.30');
      $oLink->addPrm('actId', $actId);
      $oLink->addPrm('tab', 'works');
      $oLink->addPrm('isSearch', $isSearch);
      $oLink->addPrm('searchNum', $searchNum);
      $oFormWorkTab = new Form('frmRbfWorkTab', 'post', $oLink->getQuery() . '#tab');

      unset($oLink);

      // if operation is success, show success message
      if (reqVar::get('successMessageTab'))
      {
          $oFormWorkTab->addSuccess(reqVar::get('successMessageTab'));
      }

      // Get act info
      $act = array();
      $status = false;
      $actInfo = dbProc::getRbfActInfo($actId);
      if(count($actInfo) > 0)
      {
          $act = $actInfo;
          $status = $act['RAKT_STATUS'];
      }

      $isReadonly = true;
      // Edit access: if act is in "Ievads" (INSERT) or "Atgriezts" (RETURN) status and user is the author or admin
      if((($act['RAKT_RLTT_ID'] == $userId && $isRbfUser) || $isAdmin) && 
        ($status == STAT_INSERT || $status == STAT_RETURN))
      {
        $isReadonly = false;
      }
      
      // Popup link preparation
      $oPopLink = new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.33');
      $oPopLink->addPrm('actId', $actId);
      $oPopLink->addPrm('isSearch', $isSearch);
      $oPopLink->addPrm('searchNum', $searchNum);

      // Single link - ALL_WORK
      $calcGroups = array();
      $calcGroups[0]['TITLE'] = text::get('ALL_WORK');
      $calcGroups[0]['URL'] = RequestHandler::popupHref($oPopLink->getQuery().'&all=1', false, 700, 450, true, false, true);

      unset($oPopLink);

      $aWorks = array();
      $aWorkExist = false;
      
      if ($oFormWorkTab->isFormSubmitted() && $oFormWorkTab->getValue('action') != OP_EXPORT)
      {
          $isRowValid = true;
          $aChiphers = $oFormWorkTab->getValue('chipher');
          
          if(is_array($aChiphers))
          {
            $aWorkFr = array();
            foreach ($aChiphers as $i => $val)
            {
                 $aWorkFr[$i]['DRBI_KKAL_ID'] = $oFormWorkTab->getValue('kid['.$i.']');
                 $aWorkFr[$i]['DRBI_KKAL_SHIFRS'] = $oFormWorkTab->getValue('chipher['.$i.']');
                 $aWorkFr[$i]['DRBI_KKAL_NOSAUKUMS'] = $oFormWorkTab->getValue('title['.$i.']');
                 $aWorkFr[$i]['DRBI_KKAL_NORMATIVS'] = $oFormWorkTab->getValue('standart['.$i.']');
                 $aWorkFr[$i]['DRBI_MERVIENIBA'] = $oFormWorkTab->getValue('measure['.$i.']');
                 $aWorkFr[$i]['DRBI_ID'] = $oFormWorkTab->getValue('id['.$i.']');
                 $aWorkFr[$i]['DRBI_PLAN_DATE'] = $oFormWorkTab->getValue('plan_date['.$i.']');
                 $aWorkFr[$i]['KKAL_APRAKSTS'] = $oFormWorkTab->getValue('description['.$i.']');
                 $aWorkFr[$i]['DRBI_DAUDZUMS'] = $oFormWorkTab->getValue('amount['.$i.']');
                 // Calculate total as price * amount
                 $aWorkFr[$i]['DRBI_CILVEKSTUNDAS'] = $aWorkFr[$i]['DRBI_KKAL_NORMATIVS'] * $aWorkFr[$i]['DRBI_DAUDZUMS'];
                 // DRBI_ELEMENT and DRBI_PERS are not editable in RBF acts (labels only)

                 // Validate amount
                 if (empty($aWorkFr[$i]['DRBI_DAUDZUMS']) || $aWorkFr[$i]['DRBI_DAUDZUMS'] <= 0)
                 {
                     $oFormWorkTab->addErrorPerElem('amount['.$i.']', text::get('ERROR_REQUIRED_FIELD'));
                     $isRowValid = false;
                 }

                 // Validate plan date
                 if (empty($aWorkFr[$i]['DRBI_PLAN_DATE']))
                 {
                     $oFormWorkTab->addErrorPerElem('plan_date['.$i.']', text::get('ERROR_REQUIRED_FIELD'));
                     $isRowValid = false;
                 }
            }

            // Save if valid
            if ($isRowValid)
            {
                // Delete all existing work records
                $r = dbProc::deleteActWorks($actId, 0); // tame=0 for RBF acts
                
                if ($r === false)
                {
                    $oFormWorkTab->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                }
                else
                {
                    // Re-insert all work records
                    foreach($aWorkFr as $i => $work)
                    {
                        $r = dbProc::writeActWork(
                            $actId,
                            $work['DRBI_KKAL_ID'],
                            $work['DRBI_KKAL_SHIFRS'],
                            $work['DRBI_KKAL_NOSAUKUMS'],
                            $work['DRBI_KKAL_NORMATIVS'],
                            $work['DRBI_DAUDZUMS'],
                            $work['DRBI_CILVEKSTUNDAS'], // total
                            $work['DRBI_MERVIENIBA'],
                            false, // amount_kor (not used for RBF)
                            false, // edited
                            $work['DRBI_PLAN_DATE'],
                            false, // day_total (not used for RBF)
                            false, // notes
                            0,     // st (is_worker)
                            false, // work_type
                            false, // work_type_text
                            false, // export_type
                            false, // work_approve_date
                            false  // import_no
                        );
                        
                        if($r === false)
                        {
                            $oFormWorkTab->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                            break;
                        }
                    }
                    
                    if($r !== false)
                    {
                        $oLink = new urlQuery();
                        $oLink->addPrm(FORM_ID, 'f.akt.s.30');
                        $oLink->addPrm('actId', $actId);
                        $oLink->addPrm('tab', 'RBF_WORKS');
                        $oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));
                        RequestHandler::makeRedirect($oLink->getQuery() . '#tab');
                    }
                }
            }
          }
      }

      // Get work list from DB
      $aWorkDb = dbProc::getActWorkListRbf($actId, 0); // tame=0 for RBF acts

      if (is_array($aWorkDb) && count($aWorkDb) > 0)
      {
          $aWorkExist = true;
          $k = 0;
          $worksTotal = 0; // Initialize total for all works
          
          foreach ($aWorkDb as $i => $row)
          {
              $aWorks[$i] = $row;

              // ID
              $oFormWorkTab->addElement('hidden', 'id['.$k.']', '', $row['DRBI_ID']);
              $oFormWorkTab->addElement('hidden', 'kid['.$k.']', '', $row['DRBI_KKAL_ID']);
              $oFormWorkTab->addElement('hidden', 'description['.$k.']', '', $row['KKAL_APRAKSTS']);

              // Chipher (Šifrs) - always readonly
              $oFormWorkTab->addElement('label', 'chipher['.$k.']', '', $row['DRBI_KKAL_SHIFRS']);

              // Plan date (Izpildes datums) - editable when not readonly
              if(!$isReadonly)
              {
                  $oFormWorkTab->addElement('date', 'plan_date['.$k.']', '', $row['DRBI_PLAN_DATE'], (($isReadonly)?' disabled ':''));
                  $oFormWorkTab->addRule('plan_date['.$k.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
                  $oFormWorkTab->addRule('plan_date['.$k.']', text::get('ERROR_INCORRECT_DATE'),'validatedate');
              }
              else
              {
                  $oFormWorkTab->addElement('label', 'plan_date['.$k.']', '', $row['DRBI_PLAN_DATE']);
              }

              // Title (Nosaukums) - always readonly
              $oFormWorkTab->addElement('label', 'title['.$k.']', '', $row['DRBI_KKAL_NOSAUKUMS']);

              // Price (Cena) - always readonly
              $oFormWorkTab->addElement('hidden', 'standart['.$k.']', '', $row['DRBI_KKAL_NORMATIVS']);
              $oFormWorkTab->addElement('label', 'standart_display['.$k.']', '', number_format($row['DRBI_KKAL_NORMATIVS'], 2, '.', ' '));

              // Unit of measure (Mērvienība) - always readonly
              $oFormWorkTab->addElement('label', 'measure['.$k.']', '', $row['DRBI_MERVIENIBA']);

              // Amount (Daudzums) - editable when not readonly
              $row['DRBI_DAUDZUMS'] = number_format($row['DRBI_DAUDZUMS'], 3, '.', '');
              $oFormWorkTab->addElement('text', 'amount['.$k.']', '', $row['DRBI_DAUDZUMS'], (($isReadonly)?' disabled ':'').'maxlength="9"');
              $oFormWorkTab->addRule('amount['.$k.']', text::get('ERROR_REQUIRED_FIELD'), 'required');
              $oFormWorkTab->addRule('amount['.$k.']', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);

              // Total (Summa) - always readonly
              $total = $row['DRBI_KKAL_NORMATIVS'] * $row['DRBI_DAUDZUMS'];
              $worksTotal += $total; // Accumulate total
              $oFormWorkTab->addElement('label', 'total['.$k.']', '', number_format($total, 2, '.', ' '));

              // Work norm (c.st. norma) - for admins only, always readonly
              if($isAdmin)
              {
                  $workNorm = isset($row['KKNO_NORM']) ? $row['KKNO_NORM'] : '';
                  $oFormWorkTab->addElement('label', 'work_norm['.$k.']', '', $workNorm);

                  // Work norm sum (c.st. summa)
                  $workNormSum = isset($row['WORK_NORM_SUM']) ? $row['WORK_NORM_SUM'] : 0;
                  $oFormWorkTab->addElement('label', 'work_norm_sum['.$k.']', '', number_format($workNormSum, 2, '.', ''));
              }

              // Write off account (Izmaksu konts) - always readonly
              $oFormWorkTab->addElement('label', 'write_off_code['.$k.']', '', $row['KWRC_KODS']);

              // Element (Stihija) - always readonly label showing YES/NO
              $elementText = (!empty($row['DRBI_ELEMENT']) && $row['DRBI_ELEMENT'] != 0) ? text::get('YES') : text::get('NO');
              $oFormWorkTab->addElement('label', 'act_element['.$k.']', '', $elementText);

              // Pers - always readonly label showing YES/NO
              $persText = (!empty($row['DRBI_PERS']) && $row['DRBI_PERS'] != 0) ? text::get('YES') : text::get('NO');
              $oFormWorkTab->addElement('label', 'act_pers['.$k.']', '', $persText);

              // Delete button
              if(!$isReadonly)
              {
                  $delLink = new urlQuery();
                  $delLink->addPrm(FORM_ID, 'f.akt.s.31');
                  $delLink->addPrm(DONT_USE_GLB_TPL, '1');
                  $delLink->addPrm('actId', $actId);
                  $delLink->addPrm('xmlHttp', '1');
                  $delLink->addPrm('isSearch', $isSearch);
                  $delLink->addPrm('searchNum', $searchNum);

                  $delButtonJs = "if(isDelete()) { 
                      var rowId = document.forms['frmRbfWorkTab']['id[" .$k. "]'];
                      eval(xmlHttpGetValue('" .$delLink->getQuery() ."&deleteId='+rowId.value));
                    }";
              
                  $oFormWorkTab->addElement('button', 'work_del['.$k.']', '', '', 'onclick="' . $delButtonJs . ';return false;" style="background: url(img/ico_del.gif); cursor:hand; border:0px; width: 20px; height: 20px;" title="' . text::get('DELETE') . '"');
                  unset($delLink);
              }

              $k++;
          }
      }

      // Add popup links as form elements
      if(!$isReadonly)
      {
          foreach($calcGroups as $i => $group)
          {
              $oFormWorkTab->addElement('link', 'group['.$i.']', $group['TITLE'], '#', 'onClick="'.$group['URL'].'"', '');
          }
      }

      // Save button - below the links
      if(!$isReadonly && $aWorkExist)
      {
          $oFormWorkTab->addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_save_work.gif', 'width="120" height="20" ');
      }

      // Render the form
      $oFormWorkTab->makeHtml();

      // Include the template
      include('f.akt.s.31.tpl');
    }
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
