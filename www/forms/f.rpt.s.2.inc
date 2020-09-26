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
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.2');
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
	    $oLink->addPrm(FORM_ID, 'f.rpt.s.2');
	    $criteriaLink=$oLink ->getQuery();
	    unset($oLink);

        // if operation
    	if ($oForm -> isFormSubmitted())
    	{
            $oListLink=new urlQuery();
            $oListLink->addPrm(FORM_ID, 'f.rpt.s.2');
            $oListLink->addPrm('isTrase', $trase );
            $oListLink->addPrm('sign', $sign );
        }
        $searchTitle = text::toUpper(text::toUpper(text::get('REPORT_WORK_TOTAL_'.$sign).(($trase == 1) ? ' ('.text::get('TRASE').')' : '' )));
        $searchName = 'REPORT_WORK_TOTAL';
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
       // if(date("d.m.Y", strtotime("01.".$month.".".$year) ) >= date("d.m.Y", strtotime("01.07.2012") ) )
      if(strtotime("01.".$month.".".$year)  >= strtotime("01.07.2012")  )    
            $pvn = PCT_21  ;
        else
            $pvn = PCT_22  ;

        // URL  export
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.rpt.e.2');
    	$oLink->addPrm('search', $sCriteria);
        $oLink->addPrm('isTrase', $trase );
        $oLink->addPrm('sign', $sign );
        $oLink->addPrm(DONT_USE_GLB_TPL, '1');
        $exportUrl =  $oLink ->getQuery();
        unset($oLink);

        // gel list of users
		$res = dbProc::getActTotalWorkList($sCriteria, $trase, $sign);
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
       /*echo "<pre>";
        print_r($res);
        echo "</pre>";*/

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
        /*echo "<pre>";
        print_r($area);
        echo "</pre>";*/

		include('f.rpt.s.2.tpl');
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
