<?
   $sCriteria = reqVar::get('search');
   $sOrder = reqVar::get('sortOrder');

   $searchCr = array();
        $sCr = explode("^", $sCriteria);
        if(isset($sCr[0]) && $sCr[0] != -1  )
        {
           $searchCr[] = text::get('YEAR').': '.$sCr[0];
        }
       if(isset($sCr[1]) && $sCr[1] != -1  && isset($sCr[2]) && $sCr[2] != -1)
        {
           $searchCr[] = text::get('MONTH').': '.dtime::getMonthName($sCr[1]).'-'.dtime::getMonthName($sCr[2]);
        }
        if(isset($sCr[3]) && $sCr[3] != -1)
        {
           $searchCr[] = text::get('SINGL_WORK_OWNER').': '.dbProc::getWorkOwnerNameByCode($sCr[3]);
        }
        if(isset($sCr[4]) && $sCr[4] != -1)
        {
           $searchCr[] = text::get('ED_REGION').': '.$sCr[4];
        }
        if(isset($sCr[5]) && $sCr[5] != -1)
        {
           $searchCr[] = text::get('SINGLE_VOLTAGE').': '.dbProc::getVoltageName($sCr[5]);
        }

        if(isset($sCr[6]) && $sCr[6] != -1)
        {
           $searchCr[] = text::get('ACT_OUNER').': '.dbProc::getUserName($sCr[6]);
        }

        $status = explode("*", $sCr[8]);
        $statusString = '';
        if($status[0] == -1)
        {
           $statusString = text::get('ALL_STATUS');
        }
        else
        {
          foreach($status as $s)
          {
              $statusInfo = dbProc::getKrfkInfoByName($s);
              $statusString .= $statusInfo['KRFK_NOZIME'].",";
          }
          $statusString  = substr($statusString, 0, -1);
        }
        $searchCr[] = text::get('STATUS').': '.$statusString;
        if(isset($sCr[9]) && $sCr[9] != -1)
        {
           $searchCr[] = text::get('SINGLE_OBJECT').': '.(($sCr[9] == 1) ? text::get('LOWVOLTAGE'): text::get('MIDDLEVOLTAGE'));
        }
        if(isset($sCr[10]) && $sCr[10] != -1)
        {
           $searchCr[] = text::get('ED_SECTION').': '.$sCr[10];
        }
   $excel = '<html><head><meta http-equiv=Content-Type content="text/html; charset=utf-8"></head><body>';

   $excel .= '<table style="font-family:Arial; font-size:9pt;">';


   $excel .= '<tr><td colspan="20" style="font-size:12pt; font-weight:bold;">'.text::get('REPORT_PHISICAL_SHOWING').'</td></tr>';
   $excel .= '<tr><td colspan="20">'.implode('; ',$searchCr).'</td></tr>';
   $excel .= '<tr>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('CODE').'</td>';
    $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('ED_REGION').'</td>';

   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('ED_IECIKNIS').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('WORK_TITLE').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('UNIT_OF_MEASURE').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('REPORT_PHISICAL_SHOWING_PLAN').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('REPORT_PHISICAL_SHOWING_DONE').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">'.text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN').'</td>';

$excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">I. '.text::get('REPORT_PHISICAL_SHOWING_PLAN').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">I. '.text::get('REPORT_PHISICAL_SHOWING_DONE').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">I. '.text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN').'</td>';

$excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">II. '.text::get('REPORT_PHISICAL_SHOWING_PLAN').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">II. '.text::get('REPORT_PHISICAL_SHOWING_DONE').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">II. '.text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN').'</td>';

$excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">III. '.text::get('REPORT_PHISICAL_SHOWING_PLAN').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">III. '.text::get('REPORT_PHISICAL_SHOWING_DONE').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">III. '.text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN').'</td>';

$excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">IV. '.text::get('REPORT_PHISICAL_SHOWING_PLAN').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">IV. '.text::get('REPORT_PHISICAL_SHOWING_DONE').'</td>';
   $excel .= '<td style="border: 1px solid black; font-size:10pt; font-weight:bold; text-align:center">IV. '.text::get('REPORT_PHISICAL_SHOWING_NOT_PLAN').'</td>';



   $excel .= '</tr>';

   // rowTitle
        $rowName = array(
                'low' => array(
                    '0' => text::get('REPORT_PHISICAL_SHOWING_STAY'),
                    '1' => text::get('REPORT_PHISICAL_SHOWING_CALC_1'),
                    '2' => text::get('REPORT_PHISICAL_SHOWING_CALC_2'),
                    '3' => text::get('REPORT_PHISICAL_SHOWING_CALC_3'),
                    '4' => text::get('REPORT_PHISICAL_SHOWING_CALC_4'),
                    '5' => text::get('REPORT_PHISICAL_SHOWING_LOW_CALC_5'),
                    '6' => text::get('REPORT_PHISICAL_SHOWING_LOW_CALC_6'),
                    '7' => text::get('REPORT_PHISICAL_SHOWING_LOW_CALC_7'),
                    '8' => text::get('REPORT_PHISICAL_SHOWING_LOW_CALC_8')
                ),
                'middle' => array(
                    '0' => text::get('REPORT_PHISICAL_SHOWING_STAY'),
                    '1' => text::get('REPORT_PHISICAL_SHOWING_CALC_1'),
                    '2' => text::get('REPORT_PHISICAL_SHOWING_CALC_2'),
                    '3' => text::get('REPORT_PHISICAL_SHOWING_CALC_3'),
                    '4' => text::get('REPORT_PHISICAL_SHOWING_CALC_4'),
                    '5' => text::get('REPORT_PHISICAL_SHOWING_MIDDLE_CALC_5'),
                    '6' => text::get('REPORT_PHISICAL_SHOWING_MIDDLE_CALC_6'),
                    '7' => text::get('REPORT_PHISICAL_SHOWING_MIDDLE_CALC_7'),
                    '8' => text::get('REPORT_PHISICAL_SHOWING_MIDDLE_CALC_8'),
                    '9' => text::get('REPORT_PHISICAL_SHOWING_MIDDLE_CALC_9'),
                    '10' => text::get('REPORT_PHISICAL_SHOWING_MIDDLE_CALC_10')
                )
        );
        $area = array();
        // define ED
        $res = dbProc::getPhisicalShowingList($sCriteria, 0);
        if (is_array($res))
        {
            foreach ($res as $i=>$row)
    	    {
                 $area[$row['KEDI_KODS']]  = array (
                        'code' => $row['KEDI_KODS'],
                        'name' => $row['KEDI_NOSAUKUMS'],
                        'region' => $row['KEDI_REGIONS'],
                        'dataRow' => array()
                 );
            }
        }
        // low voltage ($sCr[8] == 1)
        $outputRowCount = (($sCr[9] == 1) ? 9 : 11);
        $dataRowSum = array();
        for($j=0; $j<$outputRowCount; $j++)
        {
            $res = dbProc::getPhisicalShowingList($sCriteria, $j);
            $dataRow = array();

            if (is_array($res))
            {
       		    foreach ($res as $i=>$row)
                {
                    $dataRow[$j]  = array (
                  'calcMms' => $row['MMS_VOLTAGE_CALC'.$j.'_PLAN'],
                  'calcMms1' => $row['MMS_VOLTAGE_CALC'.$j.'_PLAN1'],
                  'calcMms2' => $row['MMS_VOLTAGE_CALC'.$j.'_PLAN2'],
                  'calcMms3' => $row['MMS_VOLTAGE_CALC'.$j.'_PLAN3'],
                  'calcMms4' => $row['MMS_VOLTAGE_CALC'.$j.'_PLAN4'],
                  'calcPlan' => $row['VOLTAGE_CALC'.$j.'_PLAN'],
                  'calcPlan1' => $row['VOLTAGE_CALC'.$j.'_PLAN1'],
                  'calcPlan2' => $row['VOLTAGE_CALC'.$j.'_PLAN2'],
                  'calcPlan3' => $row['VOLTAGE_CALC'.$j.'_PLAN3'],
                  'calcPlan4' => $row['VOLTAGE_CALC'.$j.'_PLAN4'],
                  'calcNotPlan' => $row['VOLTAGE_CALC'.$j.'_NOT_PLAN'],
                  'calcNotPlan1' => $row['VOLTAGE_CALC'.$j.'_NOT_PLAN1'],
                  'calcNotPlan2' => $row['VOLTAGE_CALC'.$j.'_NOT_PLAN2'],
                  'calcNotPlan3' => $row['VOLTAGE_CALC'.$j.'_NOT_PLAN3'],
                  'calcNotPlan4' => $row['VOLTAGE_CALC'.$j.'_NOT_PLAN4'],
                  'calcMeasure' => $row['VOLTAGE_CALC'.$j.'_MEASURE']
                  ) ;

                  $area[$row['KEDI_KODS']]['dataRow'][$j]  = $dataRow[$j];

                /*    $dataRowSum[$j]  = array (
                  'calcMms' => number_format((isset($dataRowSum[$j]['calcMms'])?$dataRowSum[$j]['calcMms']:0) + $row['MMS_VOLTAGE_CALC'.$j.'_PLAN'], 2, '.', ''),
                  'calcMms1' => number_format((isset($dataRowSum[$j]['calcMms1'])?$dataRowSum[$j]['calcMms1']:0) + $row['MMS_VOLTAGE_CALC'.$j.'_PLAN1'], 2, '.', ''),
                  'calcMms2' => number_format((isset($dataRowSum[$j]['calcMms2'])?$dataRowSum[$j]['calcMms2']:0) + $row['MMS_VOLTAGE_CALC'.$j.'_PLAN2'], 2, '.', ''),
                  'calcMms3' => number_format((isset($dataRowSum[$j]['calcMms3'])?$dataRowSum[$j]['calcMms3']:0) + $row['MMS_VOLTAGE_CALC'.$j.'_PLAN3'], 2, '.', ''),
                  'calcMms4' => number_format((isset($dataRowSum[$j]['calcMms4'])?$dataRowSum[$j]['calcMms4']:0) + $row['MMS_VOLTAGE_CALC'.$j.'_PLAN4'], 2, '.', ''),
                  'calcPlan' => number_format((isset($dataRowSum[$j]['calcPlan'])?$dataRowSum[$j]['calcPlan']:0) + $row['VOLTAGE_CALC'.$j.'_PLAN'], 2, '.', ''),
                  'calcPlan1' => number_format((isset($dataRowSum[$j]['calcPlan1'])?$dataRowSum[$j]['calcPlan1']:0) + $row['VOLTAGE_CALC'.$j.'_PLAN1'], 2, '.', ''),
                  'calcPlan2' => number_format((isset($dataRowSum[$j]['calcPlan2'])?$dataRowSum[$j]['calcPlan2']:0) + $row['VOLTAGE_CALC'.$j.'_PLAN2'], 2, '.', ''),
                  'calcPlan3' => number_format((isset($dataRowSum[$j]['calcPlan3'])?$dataRowSum[$j]['calcPlan3']:0) + $row['VOLTAGE_CALC'.$j.'_PLAN3'], 2, '.', ''),
                  'calcPlan4' => number_format((isset($dataRowSum[$j]['calcPlan4'])?$dataRowSum[$j]['calcPlan4']:0) + $row['VOLTAGE_CALC'.$j.'_PLAN4'], 2, '.', ''),
                  'calcNotPlan' => number_format((isset($dataRowSum[$j]['calcNotPlan'])?$dataRowSum[$j]['calcNotPlan']:0) + $row['VOLTAGE_CALC'.$j.'_NOT_PLAN'], 2, '.', ''),
                  'calcNotPlan1' => number_format((isset($dataRowSum[$j]['calcNotPlan1'])?$dataRowSum[$j]['calcNotPlan1']:0) + $row['VOLTAGE_CALC'.$j.'_NOT_PLAN1'], 2, '.', ''),
                  'calcNotPlan2' => number_format((isset($dataRowSum[$j]['calcNotPlan2'])?$dataRowSum[$j]['calcNotPlan2']:0) + $row['VOLTAGE_CALC'.$j.'_NOT_PLAN2'], 2, '.', ''),
                  'calcNotPlan3' => number_format((isset($dataRowSum[$j]['calcNotPlan3'])?$dataRowSum[$j]['calcNotPlan3']:0) + $row['VOLTAGE_CALC'.$j.'_NOT_PLAN3'], 2, '.', ''),
                  'calcNotPlan4' => number_format((isset($dataRowSum[$j]['calcNotPlan4'])?$dataRowSum[$j]['calcNotPlan4']:0) + $row['VOLTAGE_CALC'.$j.'_NOT_PLAN4'], 2, '.', ''),
                  'calcMeasure' => $row['VOLTAGE_CALC'.$j.'_MEASURE']
                  ) ;  */
                }
            }
       }
       ksort($area);

       $area['999999']  = array (
                    'code' => '999999',
                    'name' => text::get('TOTAL'),
                    'region' => '',
                    'dataRow' => $dataRowSum
                 );

       foreach ($area as $arow)
       {
        if (is_array($arow['dataRow']))
		{
			foreach ($arow['dataRow'] as $i=>$row)
			{
			  if($arow['code'] != '999999')
              {
			  $excel .= '<tr>';
              $excel .= '<td style="border: 1px solid black;">'.$arow['code'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$arow['region'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$arow['name'].'</td>';

              $excel .= '<td style="border: 1px solid black;">'.(($sCr[8] == 1) ? $rowName['low'][$i] : $rowName['middle'][$i]).'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcMeasure'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcMms'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcPlan'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcNotPlan'].'</td>';

              $excel .= '<td style="border: 1px solid black;">'.$row['calcMms1'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcPlan1'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcNotPlan1'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcMms2'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcPlan2'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcNotPlan2'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcMms3'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcPlan3'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcNotPlan3'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcMms4'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcPlan4'].'</td>';
              $excel .= '<td style="border: 1px solid black;">'.$row['calcNotPlan4'].'</td>';

              $excel .= '</tr>';
              }

			}
		}
        }

        $excel .= '</table></body></html>';

// redirect output to client browser

  header('Content-Type: application/vnd.ms-excel;');
  header('Content-Disposition: attachment;filename="myfile.xls"');
  header('Cache-Control: max-age=0');

  echo $excel;


?>