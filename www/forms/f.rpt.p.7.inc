<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isSystemUser = dbProc::isExistsUserRole($userId);

// tikai  sistçmas lietotajam vai administrâtoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
     $sCriteria = reqVar::get('search');
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

        $searchCr = array();
        $sCr = explode("^", $sCriteria);
        if(isset($sCr[0]) && $sCr[0] != -1  )
        {
           $searchCr[] = array('label' =>  text::get('YEAR'), 'value' => $sCr[0]);
        }
         if(isset($sCr[1]) && $sCr[1] != -1  )
        {
           $searchCr[] = array('label' =>  text::get('MONTH'), 'value' => dtime::getMonthName($sCr[1]));
        }
        if(isset($sCr[2]) && $sCr[2] != -1)
        {
           $searchCr[] = array('label' =>  text::get('SINGL_WORK_OWNER'), 'value' => dbProc::getWorkOwnerNameByCode($sCr[2]));
        }
        if(isset($sCr[3]) && $sCr[3] != -1)
        {
           $searchCr[] = array('label' =>  text::get('ED_REGION'), 'value' => $sCr[3]);
        }
        if(isset($sCr[4]) && $sCr[4] != -1)
        {
           $searchCr[] = array('label' =>  text::get('ED_SECTION'), 'value' => urldecode($sCr[4])); 
        }



		include('f.rpt.p.7.tpl');
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
