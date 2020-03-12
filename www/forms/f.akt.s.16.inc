<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;
$isTraseUser = userAuthorization::isTrase();
// act ID
$actId  = reqVar::get('actId');
// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
    // inicial state: actId=0;
  if($actId != false)
  {
    $rows=dbProc::getUserInfo($userId);
    if (count($rows)==1)
    {
      $actAutorName =  $rows[0]['RLTT_VARDS'].' '.$rows[0]['RLTT_UZVARDS'];
    }



  	// get info about act
  	$actInfo = dbProc::getActInfo($actId);
  	//print_r($actInfo);
  	if(count($actInfo)>0)
  	{
  		$act = $actInfo[0];

         if(strtotime("01.".$act['RAKT_MENESIS'].".".$act['RAKT_GADS'])  >= strtotime("01.07.2012")  )
            $pvn = PCT_21  ;
        else
            $pvn = PCT_22  ;

        $regionName = dbProc::GetRefionName($act['RAKT_KEDI_ID']);
        $departmentName = dbProc::GetDepartmentName($act['RAKT_KEDI_ID']);


       	// get info about work
        $aWorkDb=dbProc::getActWorkList($actId);
        $workTotal = 0;
        foreach ($aWorkDb as $i => $work)
        {
           $workTotal +=  $work['DRBI_CILVEKSTUNDAS'];
        }

        $workTotal = $workTotal;
        $pct =  ($workTotal*(100+ $pvn )/ 100 ) - $workTotal;
        $summa = ($workTotal*(100+ $pvn )/ 100 );

    }
  }

   include('f.akt.s.16.tpl');
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
