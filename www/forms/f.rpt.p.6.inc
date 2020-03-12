<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isSystemUser = dbProc::isExistsUserRole($userId);

// tikai  sistçmas lietotajam vai administrâtoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
     $sCriteria = reqVar::get('search');
     $sOrder = reqVar::get('sortOrder');
		// gel list of users
        $res = dbProc::getActFullListStatuss($sCriteria, $sOrder);
        $work = 0;
        $st_material = 0;
        $du_material = 0;
        if (is_array($res))
		{
			foreach ($res as $i=>$row)
			{
               $work = $work + $row['WORK_TOTAL'];
               $st_material = $st_material + $row['ST_MATER_TOTAL'];
               $du_material = $du_material + $row['DU_MATER_TOTAL'];
			}
		}
        $work = number_format($work,2, '.', '');
        $st_material = number_format($st_material,2, '.', '');
        $du_material = number_format($du_material, 2, '.', '');

        $searchCr = array();
        $sCr = explode("^", $sCriteria);
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
           $searchCr[] = array('label' =>  text::get('SINGLE_ACT_TYPE'), 'value' => dbProc::getActTypeName($sCr[6]));
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
           $searchCr[] = array('label' =>  text::get('ED_SECTION'), 'value' => urldecode($sCr[9]));
        }

		include('f.rpt.p.6.tpl');
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
