<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);

if ( $isAdmin || $isEconomist)
{
  // get acts array
  $acts = array();  
  $aMaterialDb = array();

  foreach ($_SESSION as $key => $val)
  {
    if(substr($key, 0, 13) == 'WRITE_OFF_ACT')
    {
	$result = dbProc::getActWriteOffCode($val);
	if(isset($result[0]) ) $acts[$val] = $result[0];	

    }
  }
  //print_r($acts);
  if(count($acts) > 0)
  {

    // get info about material
    $aMaterialDb=dbProc::getActsFreeMaterialList($acts);
    $Totalsumma = 0;
    foreach ($aMaterialDb as $i=>$row)
    {
       $Totalsumma += $row['MATR_CENA_KOPA'];
    }
  }


   include('f.akt.s.15.tpl');
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
