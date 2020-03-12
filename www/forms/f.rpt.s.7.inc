<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isSystemUser = dbProc::isExistsUserRole($userId);


// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
	$searchMode = reqVar::get('isSearch');
	// top frame
    if($searchMode)
	{
        $oLink=new urlQuery();
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.7');
    	$oLink->addPrm('isSearch', 1 );
    	// form inicialization
    	$oForm = new Form('frmMain','post',$oLink->getQuery());
    	unset($oLink);

        $oLink=new urlQuery();
	    $oLink->addPrm('isReturn', '1');
        $oLink->addPrm('isSearch', 1 );
	    $oLink->addPrm(FORM_ID, 'f.rpt.s.7');
	    $criteriaLink=$oLink ->getQuery();
	    unset($oLink);

        // if operation
    	if ($oForm -> isFormSubmitted())
    	{
            $oListLink=new urlQuery();
            $oListLink->addPrm(FORM_ID, 'f.rpt.s.7');
        }
        $searchTitle = text::toUpper(text::toUpper(text::get('REPORT_MMS_CALC')));
        $searchName = 'REPORT_MMS_CALC';
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


        // URL to search  by number.
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.rpt.s.7');
    	$oLink->addPrm('search', $sCriteria);
        $searchLink = $oLink -> getQuery();

        // URL  export
       /*	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.rpt.e.7');
    	$oLink->addPrm('search', $sCriteria);
        $oLink->addPrm(DONT_USE_GLB_TPL, '1');
        $exportUrl =  $oLink ->getQuery();
        unset($oLink);*/

        // URL  print
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.rpt.p.7');
    	$oLink->addPrm('search', $sCriteria);
        //$oLink->addPrm(DONT_USE_GLB_TPL, '1');
        $printUrl =  $oLink ->getQuery();
        unset($oLink);

        $res = array();
		// gel list of users
        $res = dbProc::getActMMSCalcList($sCriteria, 1);

        $planPrice = 0;
        $realPrice = 0;

        if (is_array($res))
		{
			foreach ($res as $i=>$row)
			{
			  $planAmount = -1;
			  $planAmount = dbProc::getMMSPlanColumnValue($row['KKAL_FIZ_RADIJUMS'], $row['RAKT_MMS_KODS']);

               $res[$i]['planAmount'] = number_format($planAmount ,2, '.', '');
               $res[$i]['planPrice']  = number_format($planAmount * $row['KKAL_PLAN_PRICE'],2, '.', '');
               if ($planAmount == -1) continue;
               $planPrice = $planPrice + $res[$i]['planPrice'];
               $realPrice = $realPrice + $row['DRBI_CILVEKSTUNDAS'];
			}
		}

        $planPrice = number_format($planPrice,2, '.', '');
        $realPrice = number_format($realPrice, 2, '.', '');

		include('f.rpt.s.7.tpl');
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
