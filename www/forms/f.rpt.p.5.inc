<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isSystemUser = dbProc::isExistsUserRole($userId);

// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
     $sCriteria = reqVar::get('search');
     $sCr = explode("^", $sCriteria);
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
                        'name' => $row['ED'],
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
                  /*  $dataRow[$j]  = array (
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

                  $area[$row['KEDI_KODS']]['dataRow'][$j]  = $dataRow[$j];*/

                    $dataRowSum[$j]  = array (
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
                  ) ;
                }
            }
       }
       ksort($area);
       $area = array();
       $area['999999']  = array (
                        'code' => '999999',
                        'name' => text::get('TOTAL'),
                        'dataRow' => $dataRowSum
                 );


       if(isset($sCr[0]) && $sCr[0] != -1  )
        {
           $searchCr[] = array('label' =>  text::get('YEAR'), 'value' => $sCr[0]);
        }
         if(isset($sCr[1]) && $sCr[1] != -1  && isset($sCr[2]) && $sCr[2] != -1)
        {
           $searchCr[] = array('label' =>  text::get('MONTH'), 'value' => dtime::getMonthName($sCr[1]).'-'.dtime::getMonthName($sCr[2]));
        }
        if(isset($sCr[3]) && $sCr[3] != -1)
        {
           $searchCr[] = array('label' =>  text::get('SINGL_WORK_OWNER'), 'value' => dbProc::getWorkOwnerNameByCode($sCr[3]));
        }
        if(isset($sCr[4]) && $sCr[4] != -1)
        {
           $searchCr[] = array('label' =>  text::get('ED_REGION'), 'value' => $sCr[4]);
        }
        if(isset($sCr[5]) && $sCr[5] != -1)
        {
           $searchCr[] = array('label' =>  text::get('SINGLE_VOLTAGE'), 'value' => dbProc::getVoltageName($sCr[5]));
        }
        if(isset($sCr[6]) && $sCr[6] != -1)
        {
           $searchCr[] = array('label' =>  text::get('ACT_OUNER'), 'value' => dbProc::getUserName($sCr[6]));
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
        $searchCr[] = array('label' =>  text::get('STATUS'), 'value' => $statusString);
        if(isset($sCr[9]) && $sCr[9] != -1)
        {
           $searchCr[] = array('label' =>  text::get('SINGLE_OBJECT'), 'value' => (($sCr[9] == 1) ? text::get('LOWVOLTAGE'): text::get('MIDDLEVOLTAGE')));
        }

        if(isset($sCr[10]) && $sCr[10] != -1)
        {
           $searchCr[] = array('label' =>  text::get('ED_SECTION'), 'value' => urldecode($sCr[10]));
        }

		include('f.rpt.p.5.tpl');
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
