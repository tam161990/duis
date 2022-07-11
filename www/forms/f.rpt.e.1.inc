<?
   $sCriteria = reqVar::get('search');
   $trase =  reqVar::get('isTrase');
   $sign =  reqVar::get('sign');
   $year = '';
   $month = '';
   $monthN = '';
   $worker = '';
   $workerCode = '';
   $workerNumber = '';
   
   $searchCr = array();
   $sCr = explode("^", $sCriteria);
  if(isset($sCr[0]) && $sCr[0] != -1 )
  {
     $year = $sCr[0];
  }
  if(isset($sCr[1]) && $sCr[1] != -1 )
  {
    $month = dtime::getMonthName($sCr[1]);
    $monthN = $sCr[1];
  }
  //if(date("d.m.Y", strtotime("01.".$monthN.".".$year) ) >= date("d.m.Y", strtotime("01.07.2012") ) )
  if(strtotime("01.".$monthN.".".$year)  >= strtotime("01.07.2012")  )     
            $pvn = PCT_21  ;
        else
            $pvn = PCT_22  ;
  if(isset($sCr[2]) && $sCr[2] != -1 )
  {
     $workerCode = $sCr[2];
     $worker =  dbProc::getWorkOwnerNameByCode($sCr[2]);


  }
  
  if(isset($sCr[3]) && $sCr[3] != -1 )
  {
     $workerNumber = $sCr[3];
  }
 // if(isset($sCr[4]) && $sCr[4] != -1 && isset($sCr[2]) && $sCr[2] != -1)
//  {
//    $workerNumber = dbProc::getWorkOwnerNumber($sCr[2], $sCr[4]);
//  }
 /* $sec = explode(',',WORKER_SECTION_EPW);
  if (is_array($sec))
   {
        $sectionText=array();
        foreach ($sec as $i => $row)
        {
            $sectionText[$i] = dbProc::getKrfkTextByName($row);
        }
   }
   if($workerCode == WORKER_CODE_ENA AND $section == WORKER_SECTION_ENA )
       $workerNumber = WORKER_TAX_ENA;
   else if($workerCode == WORKER_CODE_EPW AND in_array( $section,  $sectionText ) )
       $workerNumber = WORKER_TAX_EPW;
   else
       $workerNumber = dbProc::getWorkOwnerNumberByCode($sCr[2]);*/

        $res = dbProc::getActTotalReportList($sCriteria, $trase, $sign);
       /* echo "<pre>";
        print_r($res);
        echo "</pre>";*/
        $area = array();

        $summa = 0;
        $pct = 0;
        $totalPrice = 0;

        $Totalsumma = 0;
        $Totalpct = 0;
        $Totaltotal = 0;

        if (is_array($res))
		{
            foreach ($res as $i=>$row)
			{
               $totalPrice =  $row['MATER_TOTAL'] + $row['WORK_TOTAL'];

               $pct =  ($totalPrice*(100+ $pvn )/ 100 ) - $totalPrice;
               $summa = ($totalPrice*(100+ $pvn )/ 100 );

               $area[$row['WRITE_OFF_ACCOUNT']]  = array (
                'writeoftitle' => $row['WRITE_OFF_ACCOUNT'],
                'Cena' => (isset($area[$row['WRITE_OFF_ACCOUNT']]['Cena'])?$area[$row['WRITE_OFF_ACCOUNT']]['Cena']:0) + $totalPrice,
                'Pct' => (isset($area[$row['WRITE_OFF_ACCOUNT']]['Pct'])?$area[$row['WRITE_OFF_ACCOUNT']]['Pct']:0) + $pct,
                'Total' => (isset($area[$row['WRITE_OFF_ACCOUNT']]['Total'])?$area[$row['WRITE_OFF_ACCOUNT']]['Total']:0) + $summa,
                'work' => array()
               );

               $Totalsumma += $totalPrice;
               $Totalpct += $pct;
               $Totaltotal += $summa;

            }
            foreach ($res as $i=>$row)
			{
               $totalPrice =  $row['MATER_TOTAL'] + $row['WORK_TOTAL'];
               $area[$row['WRITE_OFF_ACCOUNT']]['act'][$row['RAKT_ID']]  = array (
                'number' => $row['NUMURS'],
                'designation' => $row['RAKT_OPERATIVAS_APZIM'],
                'date' => (isset($row['AAUD_DATUMS']) ? $row['AAUD_DATUMS'] :''),
                'work' => $row['WORK_TOTAL'],
                'material' => $row['MATER_TOTAL'],
                'total' => number_format($totalPrice,2,'.','')
               );
            }

		}
        $pdf=new FPDF('l');
                $pdf->AddFont('Arial','','arial.php');
                $pdf->AddFont('Arial','BI','arialbi.php');
                $pdf->AddFont('Arial','I','ariali.php');
                $pdf->AddFont('Arial','B','arialbd.php');
                $pdf->SetDisplayMode('real');
                $pdf->SetAutoPageBreak(true,20);
                $pdf->AliasNbPages();
                $pdf->SetTitle(iconv('UTF-8', 'windows-1257',text::get('REPORT_ACT_TOTAL').(($trase == 1) ? ' ('.text::get('TRASE').')' : '' )));
                $pdf->SetLeftMargin(20);
                $pdf->AddPage();
                $pdf->SetFont('Arial','B',10);

                $actDescription = array(
                    array(
                    iconv('UTF-8', 'windows-1257',text::get('REPORT_WORK_OFFER')).':',
                    iconv('UTF-8', 'windows-1257',text::get('REPORT_WORKER').':')
                        ),
                    array(
                    iconv('UTF-8', 'windows-1257',text::get('ST_COMPANY_NAME')),
                    iconv('UTF-8', 'windows-1257',$worker)
                        ),
                    array(
                    iconv('UTF-8', 'windows-1257',text::get('REPORT_AGREEMENT_NO').' '.$workerNumber),
                    iconv('UTF-8', 'windows-1257','')
                        )

                    );
                $pdf->HeaderTable($actDescription);

                $pdf->SetFont('Arial','B',10);
                $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257', text::get('REPORT_HEADER_1')), 0,1);

                $pdf->SetFont('Arial','B',10);
                $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',text::get('REPORT_ACT_TOTAL').(($trase == 1) ? ' ('.text::get('TRASE').')' : '' ).
                ' '.$year .'.g. '.$month), 0,1,'C');

                $width=array(20,80,40,40,40,40);
                $align=array('C','L','C','C','C','C');

                $headers = array(
                    'ACT_NUMBER' => iconv('UTF-8', 'windows-1257',text::get('ACT_NUMBER')),
                    'RAKT_OPERATIVAS_APZIM' => iconv('UTF-8', 'windows-1257',text::get('MAIN_DESIGNATION')),
                    'ACT_ACCEPT_TIME' => iconv('UTF-8', 'windows-1257',text::get('ACT_ACCEPT_TIME')),
                    'ACT_TOTAL_WORK_PRICE' => iconv('UTF-8', 'windows-1257',text::get('ACT_TOTAL_WORK_PRICE').', EUR'),
                    'ACT_TOTAL_MATER_PRICE' => iconv('UTF-8', 'windows-1257',text::get('ACT_TOTAL_MATER_PRICE').', EUR'),
                    'ACT_TOTAL_PRICE' => iconv('UTF-8', 'windows-1257',text::get('ACT_TOTAL_PRICE').', EUR')
                    );


                if (is_array($area) && count($area) > 0)
            	{
            		foreach ($area as $row)
            		{
                        $data = array();
                        $i = 0;
                        if (is_array($row['act']) && count($row['act']) > 0)
                        {
                           foreach ($row['act'] as $r)
                           {
                               $data[$i] = array(
                                'ACT_NUMBER' => $r['number'],
                                'RAKT_OPERATIVAS_APZIM' => iconv('UTF-8', 'windows-1257',$r['designation']),
                                'ACT_ACCEPT_TIME' => $r['date'],
                                'ACT_TOTAL_WORK_PRICE' => $r['work'],
                                'ACT_TOTAL_MATER_PRICE' => $r['material'],
                                'ACT_TOTAL_PRICE' => $r['total']
                                );
                                $i++;
                           }
                        }
                        $pdf->SetFont('Arial','',9);
                        $pdf->Cell(0,6,iconv('UTF-8', 'windows-1257',text::get('WRITE_OFF_ACCOUNT').
                        ": ".$row['writeoftitle']),0,1,'L');

                        $pdf->FancyTable($headers,$data, $width, $align);

                        $pdf->SetFont('Arial','B',8);
                        $pdf->Cell(220,4,iconv('UTF-8', 'windows-1257',text::get('TOTAL')).":",0,0,'R');
                        $pdf->Cell(40,4,number_format($row['Cena'], 2),0,1,'C');

                        $pdf->SetFont('Arial','B',8);
                        $pdf->Cell(220,4,iconv('UTF-8', 'windows-1257',text::get('PCT').' '. $pvn . '%').":",0,0,'R');
                        $pdf->Cell(40,4,number_format($row['Pct'], 2),0,1,'C');

                        $pdf->SetFont('Arial','B',8);
                        $pdf->Cell(220,4,iconv('UTF-8', 'windows-1257',text::get('TOTAL_WITH_PCT')).":",0,0,'R');
                        $pdf->Cell(40,4,number_format($row['Total'], 2),0,1,'C');
                    }

                }
                //$pdf->SetFont('Arial','B',8);
                $pdf->Cell(0,4,"","B",1);
		     //$pdf->Ln();


                $pdf->SetFont('Arial','B',8);
                $pdf->Cell(220,4,iconv('UTF-8', 'windows-1257',text::get('TOTAL')).":",0,0,'R');
                $pdf->Cell(40,4,number_format($Totalsumma, 2),0,1,'C');

                $pdf->SetFont('Arial','B',8);
                $pdf->Cell(220,4,iconv('UTF-8', 'windows-1257',text::get('PCT').' '. $pvn . '%').":",0,0,'R');
                $pdf->Cell(40,4,number_format($Totalpct, 2),0,1,'C');

                $pdf->SetFont('Arial','B',8);
                $pdf->Cell(220,4,iconv('UTF-8', 'windows-1257',text::get('TOTAL_WITH_PCT')).":",0,0,'R');
                $pdf->Cell(40,4,number_format($Totaltotal, 2),0,1,'C');

                $pdf->SetFont('Arial','BI',8);
                $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',text::get('REPORT_PRINT_DATE').': '.date('d.m.Y') ), 0,1);                               
 

		  $actFooter = array(
                    array(
                    iconv('UTF-8', 'windows-1257',text::get('REPORT_WORKER_FINISHED')).':',
                    iconv('UTF-8', 'windows-1257',text::get('REPORT_OUNER_ACCEPT').':')
                        ),
                    array(
                    iconv('UTF-8', 'windows-1257',$worker),
                    iconv('UTF-8', 'windows-1257',text::get('ST_COMPANY_NAME'))
                        ),
                    array(
                    iconv('UTF-8', 'windows-1257', ''),
                    iconv('UTF-8', 'windows-1257', text::get('RBF_REPORT_OUNER_CHIF'))
                        ),
                    array(
                    iconv('UTF-8', 'windows-1257','_____________________'),
                    iconv('UTF-8', 'windows-1257','_____________________')
                        ),
			array(
                    iconv('UTF-8', 'windows-1257',''),
                    iconv('UTF-8', 'windows-1257','')
                        ),

		      array(
                    iconv('UTF-8', 'windows-1257','_____________________'),
                    iconv('UTF-8', 'windows-1257','_____________________')
                        )

                    );
                if($pdf->GetY() >487) $pdf->AddPage('l');
                $pdf->FooterTable($actFooter);

				if($sign == 'E') {
					$pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',text::get('ELRCTRONIC_SIGNATURE')), 0,1);
				}

                // redirect output to client browser
                $pdf->Output("actreport.pdf", 'D');








?>