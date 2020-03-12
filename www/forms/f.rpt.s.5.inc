<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isSystemUser = dbProc::isExistsUserRole($userId);
// TRASE act
$trase =  reqVar::get('isTrase');
// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
	$searchMode = reqVar::get('isSearch');

	// top frame
    if($searchMode)
	{
        $oLink=new urlQuery();
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.5');
    	$oLink->addPrm('isSearch', 1 );
    	// form inicialization
    	$oForm = new Form('apiform','post',$oLink->getQuery());
    	unset($oLink);

        $oLink=new urlQuery();
	    $oLink->addPrm('isReturn', '1');
        $oLink->addPrm('isSearch', 1 );
	    $oLink->addPrm(FORM_ID, 'f.rpt.s.5');
	    $criteriaLink=$oLink ->getQuery();
	    unset($oLink);

        // if operation
    	if ($oForm -> isFormSubmitted())
        {

            $oListLink=new urlQuery();
            $oListLink->addPrm(FORM_ID, 'f.rpt.s.5');

        }
        $searchTitle = text::toUpper(text::toUpper(text::get('REPORT_PHISICAL_SHOWING')));
        $searchName = 'REPORT_PHISICAL_SHOWING';
        $allType = true;
        include('f.akt.m.6.inc');
	}
	// bottom frale
	else
	{

        $sCriteria = reqVar::get('search');
        $sCr = explode("^", $sCriteria);

        // URL  export
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.rpt.e.5');
    	$oLink->addPrm('search', $sCriteria);
        $oLink->addPrm(DONT_USE_GLB_TPL, '1');
        $exportUrl =  $oLink ->getQuery();
        unset($oLink);

        // URL  print
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.rpt.p.5');
    	$oLink->addPrm('search', $sCriteria);
        //$oLink->addPrm(DONT_USE_GLB_TPL, '1');
        $printUrl =  $oLink ->getQuery();
        unset($oLink);

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

            /*echo "<pre>";
            print_r($res);
            echo "</pre>";
            $dataRow = array();  */

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

        // print_r($res);



        include('f.rpt.s.5.tpl');
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
