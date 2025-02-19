<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isSystemUser = dbProc::isExistsUserRole($userId);
// TRASE act
$trase =  reqVar::get('isTrase');
$sign =  reqVar::get('sign');
// tikai  sist�mas lietotajam vai administr�toram ir pieeja!
if(true/*$isEdUser || $isAdmin*/)
{
	$searchMode = reqVar::get('isSearch');
	// top frame
    if($searchMode)
	{
        $oLink=new urlQuery();
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.1');
    	$oLink->addPrm('isSearch', 1 );
        $oLink->addPrm('isTrase', $trase );
		$oLink->addPrm('sign', $sign );
    	// form inicialization
    	$oForm = new Form('frmMain','post',$oLink->getQuery());
    	unset($oLink);

        $oLink=new urlQuery();
	    $oLink->addPrm('isReturn', '1');
        $oLink->addPrm('isSearch', 1 );
        $oLink->addPrm('isTrase', $trase );
		$oLink->addPrm('sign', $sign );
	    $oLink->addPrm(FORM_ID, 'f.rpt.s.1');
	    $criteriaLink=$oLink ->getQuery();
	    unset($oLink);

        // if operation
    	if ($oForm -> isFormSubmitted())
    	{
            $oListLink=new urlQuery();
            $oListLink->addPrm(FORM_ID, 'f.rpt.s.1');
			$oListLink->addPrm('sign', $sign );
            $oListLink->addPrm('isTrase', $trase );
        }
        $searchTitle = text::toUpper(text::toUpper(text::get('REPORT_ACT_TOTAL_'.$sign).(($trase == 1) ? ' ('.text::get('TRASE').')' : '' )));
        $searchName = 'REPORT_ACT_TOTAL';
        include('f.akt.m.4.inc');
	}
	// bottom frale
	else
	{
	    $sCriteria = reqVar::get('search');
         $year = '';
         $month = '';

         $searchCr = array();
         $sCr = explode("^", $sCriteria);
        if(isset($sCr[0]) && $sCr[0] != -1 )
        {
           $year = $sCr[0];
        }
        if(isset($sCr[1]) && $sCr[1] != -1 )
        {
          $month = $sCr[1];
        }
        //if(date("d.m.Y", strtotime("01.".$month.".".$year) ) >= date("d.m.Y", strtotime("01.07.2012") ) )
        if(strtotime("01.".$month.".".$year)  >= strtotime("01.07.2012")  )         
            $pvn = PCT_21  ;         
        else
            $pvn = PCT_22  ;
  
        // URL  export
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.rpt.e.1');
        $oLink->addPrm('isTrase', $trase );
		$oLink->addPrm('sign', $sign );
    	$oLink->addPrm('search', $sCriteria);
        $oLink->addPrm(DONT_USE_GLB_TPL, '1');
        $exportUrl =  $oLink ->getQuery();
        unset($oLink);

        // gel list of users
		$res = dbProc::getActTotalReportList($sCriteria, $trase, $sign);
        /*echo "<pre>";
        print_r($res);
        echo "</pre>";*/
        $area = array();
        $actIds = array();

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

               $actIds[] = $row['RAKT_ID'];

               $area[$row['ACTA_VEIDS']]  = array (
                'acttypetitle' => $row['ACTA_VEIDS'],
                'Cena' => (isset($area[$row['ACTA_VEIDS']]['Cena'])?$area[$row['ACTA_VEIDS']]['Cena']:0) + $totalPrice,
                'Pct' => (isset($area[$row['ACTA_VEIDS']]['Pct'])?$area[$row['ACTA_VEIDS']]['Pct']:0) + $pct,
                'Total' => (isset($area[$row['ACTA_VEIDS']]['Total'])?$area[$row['ACTA_VEIDS']]['Total']:0) + $summa,
                'work' => array()
               );               
               
               $Totalsumma += $totalPrice;
               $Totalpct += $pct;
               $Totaltotal += $summa;

            }
            foreach ($res as $i=>$row)
			{
               $approveDate = (($row['RAKT_IS_AUTO'] == 1) ? 
                                (isset($row['DRBI_APPROVE_DATE']) ? $row['DRBI_APPROVE_DATE'] :''):
                                (isset($row['AAUD_DATUMS']) ? $row['AAUD_DATUMS'] :'')
                );  
               $totalPrice =  $row['MATER_TOTAL'] + $row['WORK_TOTAL'];
               $area[$row['ACTA_VEIDS']]['act'][$row['RAKT_ID']]  = array (
                'number' => $row['NUMURS'],
                'designation' => $row['RAKT_OPERATIVAS_APZIM'],
                'date' => $approveDate,
                'work' => $row['WORK_TOTAL'],
                'material' => $row['MATER_TOTAL'],
                'total' => number_format($totalPrice,2,'.',''),
                'finished' => (($row['RAKT_IR_OBJEKTS_PABEIGTS'] == 1) ? text::get('YES') : text::get('NO'))
               );
            }

		}
        /*echo "<pre>";
        print_r($area);
        echo "</pre>";*/
        // write off summ table
        if(count($actIds) > 0) {
            $res1 = dbProc::getWriteOffSumm($sCriteria, implode(',',$actIds));
            /*echo "<pre>";
            print_r($res1);
            echo "</pre>";*/

            $WriteOffTotalsumma = 0;
            $WriteOffTotalpct = 0;
            $WriteOffTotaltotal = 0;

            if (is_array($res1))
            {
                foreach ($res1 as $i=>$row)
                {
                    $konts[$row['KWRC_KODS']]  = array (
                        'writeoftitle' => $row['KWRC_NOSAUKUMS'],
                        'Total' => $row['WRITEOFF_SUMM']
                    );

                    $WriteOffTotalsumma += $row['WRITEOFF_SUMM'];
                }
                $WriteOffTotalpct =  ($WriteOffTotalsumma*(100+ $pvn )/ 100 ) - $WriteOffTotalsumma;
                $WriteOffTotaltotal = ($WriteOffTotalsumma*(100+ $pvn )/ 100 );
            }        
        }
		include('f.rpt.s.1.tpl');
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
