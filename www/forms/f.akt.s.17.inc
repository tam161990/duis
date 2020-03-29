<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);

// act ID
$actId  = reqVar::get('actId');
// month
$month  = reqVar::get('month');
// year
$year  = reqVar::get('year');
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

      }
      $isReadonly   = true;
      // Ir pieejams mainīšanai, ja  AKTS:LIETOTĀJS = ’Tekošais lietotājs’ un lietotāja loma ir ‘Ievadītais’ un AKTS:STATUS = ‘Izveide’ vai ‘Atgriezts’ vai ‘Tāme’.
     if($isAdmin || $isEconomist )
      {
        $isReadonly   = false;
      }

      $masterName = dbProc::GetMasterName($act['RAKT_KEDI_ID'], 'MASTER');
      $chifName = dbProc::GetChifName($act['RAKT_KEDI_ID'], 'GROUP_CHIF');
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
      $oFormPop -> addElement('hidden', 'year', '', $year);
      $oFormPop -> addElement('hidden', 'month', '', $month);
      $oFormPop -> addElement('hidden', 'numPostfix', '', $numPostfix);
      $oFormPop -> addElement('hidden', 'toid', '', $toid);

     $oFormPop -> addElement('text', 'master',  text::get('SIGN_MASTER'), $masterName, 'maxlength="300"'.(($isReadonly)?' disabled':''));
     $oFormPop -> addRule('master', text::get('ERROR_REQUIRED_FIELD'), 'required');

      $oFormPop -> addElement('text', 'chif',  text::get('SIGN_CHIF'), $chifName, 'maxlength="300"'.(($isReadonly)?' disabled':''));
      $oFormPop -> addRule('chif', text::get('ERROR_REQUIRED_FIELD'), 'required');

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

            if($oFormPop -> getValue('master') && $oFormPop -> getValue('chif') && $oFormPop -> getValue('engineer'))
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
                            $oFormPop->getValue('month'),
                            $oFormPop->getValue('year'),
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
                            0,
                           false, 
                           $oFormPop->getValue('toid')
    					);
                if($r)
                {
                   // get info about voltage
                    $actInfo = dbProc::getActInfo($oFormPop->getValue('actId'));
                    if(count($actInfo)>0)
                    {
                        $act = $actInfo[0];
                    }
                   $regionName = dbProc::GetRefionName($act['RAKT_KEDI_ID']);
                   $departmentName = dbProc::GetDepartmentName($act['RAKT_KEDI_ID']);

                   if(strtotime("01.".$month.".".$year)  >= strtotime("01.07.2012")  )
                      $pvn = PCT_21  ;
                  else
                      $pvn = PCT_22  ;
                    // parrakstītais akts
                  $pdf=new FPDF();
                  $pdf->AddFont('Arial','','arial.php');
                  $pdf->AddFont('Arial','BI','arialbi.php');
                  $pdf->AddFont('Arial','I','ariali.php');
                  $pdf->AddFont('Arial','B','arialbd.php');
                  $pdf->SetDisplayMode('real');
                  $pdf->SetAutoPageBreak(true,20);
                  $pdf->AliasNbPages();
                  $pdf->SetTitle(iconv('UTF-8', 'windows-1257',text::get('TRASE_ACT_HEADER1').' '.$act['NUMURS']));
                  $pdf->SetLeftMargin(20);
                  $pdf->AddPage();
                  $pdf->SetFont('Arial','B',10);
                  $pdf->Cell(0,0,iconv('UTF-8', 'windows-1257',text::get('TRASE_ACT_HEADER1')), 0,1,'C');


                  // Create new PHPExcel object
                  $objPHPExcel = new PHPExcel();

                  // create act header
                  $actHeader= array(
                     array(
                       array('', 'L', '', 8),
                       array('', 'L', '', 8)
                          ) ,
                     array(
                       array('', 'L', '', 8),
                       array('', 'L', '', 8)
                          ) ,
                    array(

                       array(iconv('UTF-8', 'windows-1257',dtime::dateToLvStringEmpty($oFormPop -> getValue('start_date'))), 'L', '', 8),
                       array(iconv('UTF-8', 'windows-1257',text::get('NUMBER_SIMBOL').'. '.$act['NUMURS']), 'R', 'B', 10)
                          ),
                    array(
                       array('', 'L', '', 8),
                       array('', 'L', '', 8)
                          ) ,
                    array(
                       array(iconv('UTF-8', 'windows-1257',text::get('TRASE_ACT_HEADER5')), 'L', '', 8),
                       array('', 'L', '', 8)
                          ),
                    array(
                       array('', 'L', '', 8),
                       array('', 'L', '', 8)
                          ) ,
                    array(
                       array(iconv('UTF-8', 'windows-1257',text::get('REPORT_WORK_OFFER').':'), 'L', '', 8),
                       array(iconv('UTF-8', 'windows-1257',text::get('REPORT_WORK_DONE').':'), 'L', '', 8)
                          ) ,
                    array(
                       array(iconv('UTF-8', 'windows-1257',text::get('ST_COMPANY_NAME').', '.text::get('REGISTRATION_SIMBOL').'. '.text::get('NUMBER_SIMBOL').': '.text::get('ST_REG_NR')), 'L', 'B', 8),
                       array(iconv('UTF-8', 'windows-1257',$act['WORKER'].', '.text::get('REGISTRATION_SIMBOL').'. '.text::get('NUMBER_SIMBOL').': '.$act['KWOI_KODS']), 'L', 'B', 8)
                          ),
                    array(
                       array(iconv('UTF-8', 'windows-1257',text::get('ED_IECIKNIS').':'), 'L', '', 8),
                       array(iconv('UTF-8', 'windows-1257',text::get('WORK_DONE_AGREEMENT_NO').': '.$act['RAKT_VV_NUMBER']), 'L', '', 8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257',$regionName. ' '. text::get('REPORT_DEPARTMENT')), 'L', 'B', 8),
                       array('', 'L', '', 8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257',$act['KEDI_SECTION']), 'L', 'B', 8),
                       array('', 'L', '', 8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257',text::get('WORKS_AND_TERITORY').':'), 'L', '', 8),
                       array('', 'L', '',8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257',$regionName . ' '.text::get('REPORT_REGION')), 'L', 'B', 8),
                       array('', 'L', '', 8)
                          ) ,
                     array(
                       array(iconv('UTF-8', 'windows-1257',$act['KEDI_NOSAUKUMS'] ), 'L', 'B', 8),
                       array('', 'L', '', 8)
                          ) ,
                  ) ;
                  $pdf->HeaderStyledTable($actHeader);

                   $pdf->SetFont('Arial','BI',8);
                   $pdf->Cell(0,8,iconv('UTF-8', 'windows-1257', $act['WORK_TITLE']),0,1);

                  $actDescription = array(

                      array(
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_ACT_TYPE')).':',
                      iconv('UTF-8', 'windows-1257',$act['TYPE']),
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_OBJECT')).':',
                      iconv('UTF-8', 'windows-1257',$act['OBJECT'])
                          ),
                      array(
                      iconv('UTF-8', 'windows-1257',text::get('SINGLE_VOLTAGE')).':',
                      iconv('UTF-8', 'windows-1257',$act['SPRIEGUMS']),
                      iconv('UTF-8', 'windows-1257',text::get('EXPORT_MAIN_DESIGNATION')).':',
                      iconv('UTF-8', 'windows-1257',$act['RAKT_OPERATIVAS_APZIM'])
                          ),
	      array(
                      iconv('UTF-8', 'windows-1257',text::get('COMMENT')).':',
                      iconv('UTF-8', 'windows-1257',$act['RAKT_PIEZIMES']),
                      iconv('UTF-8', 'windows-1257',text::get('TO_ID')).':',
                      iconv('UTF-8', 'windows-1257',$act['RAKT_TO_ID'])
                          )


                      );
                  $pdf->DescriptionTableTrase($actDescription);
	/*
                  $actDetales= array(


                     array(
                       array(iconv('UTF-8', 'windows-1257',text::get('COMMENT')).':',  'L', 'B', 8),
                       array(iconv('UTF-8', 'windows-1257',$act['RAKT_PIEZIMES']), 'L', '', 8)
                          ),
                  );
                  $pdf->DescriptionAsimetricalTable($actDetales);
	*/
                  // darbi
                  $pdf->SetFont('Arial','BI',10);
                  $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',text::get(TAB_WORKS)), 0,1);

                  $width=array(20,80,20,20,20,20);
                  $alignHeader=array('R','C','R','R','R','R');
                  $align=array('R','L','R','R','R','R');

                  $headers = array(
                      'DRBI_KKAL_SHIFRS' => iconv('UTF-8', 'windows-1257',text::get('CHIPHER')),
                      'DRBI_KKAL_NOSAUKUMS' => iconv('UTF-8', 'windows-1257',text::get('EXPORT_CALCULATION_NAME')),
                      'DRBI_MERVIENIBA' => iconv('UTF-8', 'windows-1257',text::get('UNIT_OF_MEASURE')),
                      'DRBI_KKAL_NORMATIVS' => iconv('UTF-8', 'windows-1257',text::get('PRICE')),
                      'DRBI_DAUDZUMS' => iconv('UTF-8', 'windows-1257',text::get('AMOUNT')),

                      'DRBI_CILVEKSTUNDAS' => iconv('UTF-8', 'windows-1257',text::get('PRICE_TOTAL'))
                      );

                  $aWorkDb=dbProc::getActWorkList($actId);
                  $data = array();
                  $totalD = 0;
                  foreach ($aWorkDb as $i => $work)
                  {
                    $data[$i] = array(
                      'DRBI_KKAL_SHIFRS' => $work['DRBI_KKAL_SHIFRS'],
                      'DRBI_KKAL_NOSAUKUMS' => text::returnsplit(iconv('UTF-8', 'windows-1257',$work['DRBI_KKAL_NOSAUKUMS']),  2, "\n", 60),
                      'DRBI_MERVIENIBA' => iconv('UTF-8', 'windows-1257',$work['DRBI_MERVIENIBA']),
                      'DRBI_KKAL_NORMATIVS' => $work['DRBI_KKAL_NORMATIVS'],
                      'DRBI_DAUDZUMS' => $work['DRBI_DAUDZUMS'],

                      'DRBI_CILVEKSTUNDAS' => $work['DRBI_CILVEKSTUNDAS']
                      );

                    $totalD +=  $work['DRBI_CILVEKSTUNDAS'];
                  }
                  $pdf->FancyTableTrase($headers,$data, $width, $align, $alignHeader);

                  $pct =  ($totalD*(100+ $pvn )/ 100 ) - $totalD;
                  $summa = ($totalD*(100+ $pvn )/ 100 );

                  $pdf->SetFont('Arial','',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('TOTAL')).":",0,0,'R');
                  $pdf->SetFont('Arial','B',8);
                  $pdf->Cell(20,6,number_format($totalD, 2), 0,1,'R');
                   $pdf->SetFont('Arial','',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('PCT').' '. $pvn . '%').":",0,0,'R');
                  $pdf->Cell(20,6,number_format(number_format($pct,2,'.',''), 2),0,1,'R');
                  $pdf->SetFont('Arial','B',8);
                  $pdf->Cell(160,6,iconv('UTF-8', 'windows-1257',text::get('TOTAL_WITH_PCT')).":", 0,0,'R');
                  $pdf->Cell(20,6,number_format(number_format($summa,2,'.',''), 2), 0,1,'R');
                  $pdf->Cell(20,6,"", 0,1,'R');

                   $actFooter = array(
                   array(
                    iconv('UTF-8', 'windows-1257',text::get('ACT_CREATER').': '.$act['AUTORS']),
                    iconv('UTF-8', 'windows-1257',text::get('SIGN_HEADER'))
                       ),
                    array(
                   iconv('UTF-8', 'windows-1257',text::get('DATE').': '.(($oFormPop->getValue('start_date') == "") ? date('d.m.Y') : $oFormPop->getValue('start_date'))),
                   iconv('UTF-8', 'windows-1257', $act['KEDI_SECTION'] . ', '. text::get('OUNER_MASTER').' '.$oFormPop -> getValue('master'))
                       ),
                    array(
                    iconv('UTF-8', 'windows-1257',''),
                    iconv('UTF-8', 'windows-1257', $act['KEDI_SECTION'] . ', '. text::get('EXP_OUNER_CHIF').' '.$oFormPop -> getValue('chif') )
                        ),
                    array(
                    iconv('UTF-8', 'windows-1257',''),
                    iconv('UTF-8', 'windows-1257',  $departmentName .', '.dbProc::getKrfkTextByName('ENGINEER') )
                       ),
                    array(
                    iconv('UTF-8', 'windows-1257',''),
                    iconv('UTF-8', 'windows-1257', $oFormPop -> getValue('engineer') )
                       ),
                    array(
                    iconv('UTF-8', 'windows-1257',text::get('REPORT_WORKER_FINISHED').': '),
                    iconv('UTF-8', 'windows-1257','')
                       ),

                    array(
                    iconv('UTF-8', 'windows-1257',$act['WORKER']),
                    iconv('UTF-8', 'windows-1257',  $departmentName .', ' . text::get('EXP_OUNER_OPERATING_PART') )
                       ),
                    array(
                    iconv('UTF-8', 'windows-1257',$act['AUTORS']),
                    iconv('UTF-8', 'windows-1257', $depChifName )
                       ),

                     array(
                    '',
                    ''
                        ),
                    array(
                    iconv('UTF-8', 'windows-1257','__________________________________'),
                    iconv('UTF-8', 'windows-1257', '_________________________________________________')
                       ),

                    array(
                    iconv('UTF-8', 'windows-1257','               ('.strtolower(text::get('DATE')).')'),
                    iconv('UTF-8', 'windows-1257','                      ('.strtolower(text::get('DATE')).')')
                        ),

                    array(
                    iconv('UTF-8', 'windows-1257','__________________________________'),
                    iconv('UTF-8', 'windows-1257', '_________________________________________________')
                       ),
                    array(
                    iconv('UTF-8', 'windows-1257','               ('.strtolower(text::get('SIGNATURE')).')'),
                    iconv('UTF-8', 'windows-1257','                      ('.strtolower(text::get('SIGNATURE')).')')
                        )


                    );
                   $pdf->FooterTablePortraitAsimetrikal($actFooter);
                   //DUIS-291
                  if($act['RAKT_SIGNATURE'] == 'E') {
                     $pdf->Cell(0,0,iconv('UTF-8', 'windows-1257',text::get('ELRCTRONIC_SIGNATURE')), 0, 1,'C');
                   }
                  // saglaba faila datus
                   $res=dbProc::replaceFile(
                      (($trase == 1) ? 'A' : '').
                      $act['NUMURS'].'_'.dtime::now().'.'.EXPORT_FILE_EXTENTION,
                      $userId, $actId,  FILE_ESTIMATE, EXPORT_FILE_TYPE);
    		        if ($res)
    		        {
    		        	$idFile=dbLayer::getInsertId();
    		        }
    		        else
    		        {
    		        	$oFormPop->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
    		        }
                     if ($idFile!==false)
		            {
                      $pdf->Output(FILES_STORE_PATH."/".$idFile, 'F');
                      // save status changed time
                      $r1 = dbProc::saveAuditRecord($actId, $userId,  STAT_CLOSE);
                      dbProc::setUserActionDate($userId,  ACT_CLOSE);

            		  if (!$r1)
            		  {
            				$oFormPop->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
            		  }
                      // Saskaņošanas statusā -> Poga Saskaņots :ja Starpakts checkbox = false, tad tabulā KL_MMS_DARBI laukam KMSD_NOSLEGUMA_AKTS vērtība ierakstās =true attiecīgajam MMS darbam
					 $r1 = dbProc::finalizeMMS($actId);
					 if (!$r1)
        			 {
        				$oForm->addError(text::get('ERROR_IN_DB_QUERY').'!!!'.dbProc::getError());
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
                  $oRedirectLink->addPrm('tab', TAB_EXPORT);

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