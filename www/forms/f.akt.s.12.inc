<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;
// act ID
$actId  = reqVar::get('actId');
// lietotāju lomai "ED budžeta inženieris" būtu iespēja izdrukāt nodošanas aktu kurā materiāliem ir norādītas izmaksas
$isMaterialPrice  = reqVar::get('isMaterialPrice');


// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
    // inicial state: actId=0;
  if($actId != false)
  {
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

        // get info about material
        $aMaterialDb=dbProc::getActMaterialList($actId);

//print_r($aMaterialDb);
        $materialTotal = 0;
	$mat_cena_kopa = 0;
        foreach ($aMaterialDb as $i => $material)
        {
	    if (!isset($material['MATR_CENA_KOPA']))
                    {
                       	$aMaterialDb[$i]['MATR_CENA_KOPA'] = $material['MATR_CENA'] *  $material['MATR_DAUDZUMS'];
	       	$mat_cena_kopa  = $material['MATR_CENA'] *  $material['MATR_DAUDZUMS'];
                    }
	   else
	   {
		$mat_cena_kopa  = $material['MATR_CENA_KOPA'];
                   }
 

          if($material['MATR_IS_WORKER'] != '1' || $isMaterialPrice == 1)
              $materialTotal += $mat_cena_kopa;
        }
        $materialTotal = $materialTotal;
        $pctM =  ($materialTotal*(100+ $pvn )/ 100 ) - $materialTotal;
        $summaM = ($materialTotal*(100+ $pvn )/ 100 );

    }
  }


   include('f.akt.s.12.tpl');
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
