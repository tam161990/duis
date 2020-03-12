<?
   $sCriteria = reqVar::get('search');
   // TRASE act
   $trase =  reqVar::get('isTrase');
   $year = '';
   $month = '';
   $monthN = '';
   $worker = '';
   $workerCode = '';
   $workerNumber = '';
   $edRegion = '';
   $section = '';

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
 // if(date("d.m.Y", strtotime("01.".$monthN.".".$year) ) >= date("d.m.Y", strtotime("01.07.2012") ) )
 if(strtotime("01.".$monthN.".".$year)  >= strtotime("01.07.2012")  )     
            $pvn = PCT_21  ;
        else
            $pvn = PCT_22  ;
  if(isset($sCr[2]) && $sCr[2] != -1 )
  {
     $workerCode = $sCr[2];
     $worker =  dbProc::getWorkOwnerNameByCode($sCr[2]);
     //$workerNumber = dbProc::getWorkOwnerNumberByCode($sCr[2]);
  }
  if(isset($sCr[3]) && $sCr[3] != -1 )
  {
     $edRegion = $sCr[3];
  }
  if(isset($sCr[4]) && $sCr[4] != -1 )
  {
     $section = $sCr[4];
  }
   if(isset($sCr[5]) && $sCr[5] != -1 )
  {
     $workerNumber = $sCr[5];
  }
 // if(isset($sCr[4]) && $sCr[4] != -1 && isset($sCr[2]) && $sCr[2] != -1)
//  {
//    $workerNumber = dbProc::getWorkOwnerNumber($sCr[2], $sCr[4]);
//  }
  /*$sec = explode(',',WORKER_SECTION_EPW);
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

         // gel list of users
		$res = dbProc::getActTotalWorkList($sCriteria, $trase);
        $area = array();

        $summa = 0;
        $pct = 0;

        $Totalsumma = 0;
        $Totalpct = 0;
        $Totaltotal = 0;
        if (is_array($res))
		{
            foreach ($res as $i=>$row)
			{

               $pct =  ($row['DRBI_CILVEKSTUNDAS']*(100+ $pvn )/ 100 ) - $row['DRBI_CILVEKSTUNDAS'];
               $summa = ($row['DRBI_CILVEKSTUNDAS']*(100+ $pvn )/ 100 );
               $area[$row['WRITE_OFF_ACCOUNT']]  = array (
                'writeoftitle' => $row['WRITE_OFF_ACCOUNT'],
                'Cena' => (isset($area[$row['WRITE_OFF_ACCOUNT']]['Cena'])?$area[$row['WRITE_OFF_ACCOUNT']]['Cena']:0) + $row['DRBI_CILVEKSTUNDAS'],
                'Pct' => (isset($area[$row['WRITE_OFF_ACCOUNT']]['Pct'])?$area[$row['WRITE_OFF_ACCOUNT']]['Pct']:0) + $pct,
                'Total' => (isset($area[$row['WRITE_OFF_ACCOUNT']]['Total'])?$area[$row['WRITE_OFF_ACCOUNT']]['Total']:0) + $summa,
                'work' => array()
               );

               $Totalsumma += $row['DRBI_CILVEKSTUNDAS'];
               $Totalpct += $pct;
               $Totaltotal += $summa;

            }
            foreach ($res as $i=>$row)
			{

               $area[$row['WRITE_OFF_ACCOUNT']]['work'][$row['DRBI_KKAL_SHIFRS']]  = array (
                'code' => $row['DRBI_KKAL_SHIFRS'],
                'name' => $row['DRBI_KKAL_NOSAUKUMS'],
                'miasure' => $row['DRBI_MERVIENIBA'],
                'quantity' => (isset($area[$row['WRITE_OFF_ACCOUNT']]['work'][$row['DRBI_KKAL_SHIFRS']]['quantity'])?$area[$row['WRITE_OFF_ACCOUNT']]['work'][$row['DRBI_KKAL_SHIFRS']]['quantity']:0) + $row['DRBI_DAUDZUMS'],
                'cena' => $row['DRBI_KKAL_NORMATIVS'],
	'total' => number_format( (isset($area[$row['WRITE_OFF_ACCOUNT']]['work'][$row['DRBI_KKAL_SHIFRS']]['total'])?$area[$row['WRITE_OFF_ACCOUNT']]['work'][$row['DRBI_KKAL_SHIFRS']]['total']:0) + ( $row['DRBI_DAUDZUMS'] * $row['DRBI_KKAL_NORMATIVS']),2,'.','')
               
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
                $pdf->SetTitle(iconv('UTF-8', 'windows-1257',text::get('REPORT_WORK_TOTAL').(($trase == 1) ? ' ('.text::get('TRASE').')' : '' )));
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
                $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257', text::get('REPORT_HEADER_1').
                ' '.$edRegion .' '.text::get('REPORT_REGION').' '.$section), 0,1);

                $pdf->SetFont('Arial','B',10);
                $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',text::get('REPORT_WORK_TOTAL').(($trase == 1) ? ' ('.text::get('TRASE').')' : '' ).
                ' '.$year .'.g. '.$month), 0,1,'C');

                $width=array(20,80,40,40,40,40);
                $align=array('C','L','C','C','C','C');

                $headers = array(
                    'CHIPHER' => iconv('UTF-8', 'windows-1257',text::get('CHIPHER')),
                    'TOTAL_WORK_NAME' => iconv('UTF-8', 'windows-1257',text::get('TOTAL_WORK_NAME')),
                    'UNIT_OF_MEASURE' => iconv('UTF-8', 'windows-1257',text::get('UNIT_OF_MEASURE')),
                    'AMOUNT' => iconv('UTF-8', 'windows-1257',text::get('AMOUNT')),
                    'UNIT_PRICE' => iconv('UTF-8', 'windows-1257',text::get('UNIT_PRICE').', EUR'),
                    'PRICE' => iconv('UTF-8', 'windows-1257',text::get('PRICE').', EUR')
                    );


                if (is_array($area) && count($area) > 0)
            	{
            		foreach ($area as $row)
            		{
                        $data = array();
                        $i = 0;
                        if (is_array($row['work']) && count($row['work']) > 0)
                        {
                           foreach ($row['work'] as $r)
                           {
                               $data[$i] = array(
                                'CHIPHER' => $r['code'],
                                'TOTAL_WORK_NAME' => iconv('UTF-8', 'windows-1257',$r['name']),
                                'UNIT_OF_MEASURE' => iconv('UTF-8', 'windows-1257',$r['miasure']),
                                'AMOUNT' => $r['quantity'],
                                'UNIT_PRICE' => $r['cena'],
                                'PRICE' => $r['total']
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
                    iconv('UTF-8', 'windows-1257', $edRegion .' '.text::get('REPORT_OUNER_CHIF'))
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
   if($pdf->GetY() > 487) $pdf->AddPage('l');
                $pdf->FooterTable($actFooter);

                //$pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',text::get('EXPORT_FOOTER')), 0,1);

                // redirect output to client browser
                $pdf->Output("workreport.pdf", 'D');








?>