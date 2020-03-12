<?

//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);

// if a kataloga ACT set
if (isset($_GET['xml']) && isset($_GET['act']) && isset($_GET['op']))
{
      ob_clean();
      $o = $_GET['op'];
      $a = $_GET['act'];
      if (isset($o) && $o == OP_INSERT)
      {
      	session::set('WRITE_OFF_ACT_'.$a,$a);
      }
      else
      {
         session::del('WRITE_OFF_ACT_'.$a);
      }
  exit;
}

// writeoff
if (isset($_GET['xml']) && isset($_GET['writeoff']) && $_GET['writeoff'] == 1)
{
  // get acts array
  $acts = array();
  $r = false;
  foreach ($_SESSION as $key => $val)
  {
    if(substr($key, 0, 13) == 'WRITE_OFF_ACT')
    {
       $acts[] = $val;
    }
  }
  //print_r($acts);
  if(count($acts) > 0)
  {
     $r=dbProc::writeOffActsMaterial($acts);
  }
  if($r)
  {
    foreach($acts as $a)
    {
          session::del('WRITE_OFF_ACT_'.$a);
    }
  }
  //exit;
}
if ( $isAdmin || $isEconomist)
{
	$searchMode = reqVar::get('isSearch');

	// top frame
    if($searchMode == 1)
	{
        $oLink=new urlQuery();
        $oLink->addPrm('isSearch', '1');
    	$oLink->addPrm(FORM_ID, 'f.akt.s.14');
    	// form inicialization
    	$oForm = new Form('frmMain','post',$oLink->getQuery());
    	unset($oLink);

        $oLink=new urlQuery();
        $oLink->addPrm('isSearch', '1');
	    $oLink->addPrm(FORM_ID, 'f.akt.s.14');
	    $criteriaLink=$oLink ->getQuery();
	    unset($oLink);

         // if operation
    	if ($oForm -> isFormSubmitted())
    	{
            foreach ($_SESSION as $key => $val)
            {
              if(substr($key, 0, 13) == 'WRITE_OFF_ACT')
              {
                 session::del('WRITE_OFF_ACT_'.$val);
              }
            }
            $oListLink=new urlQuery();
            $oListLink->addPrm('isSearch', '0');
            $oListLink->addPrm(FORM_ID, 'f.akt.s.14');

        }
        $searchTitle = text::toUpper(text::toUpper(text::get('WRITE_OFF_ACT')));
        $searchName = 'WRITE_OFF_ACT';
        $isSearchForm = true;
        include('f.akt.m.2.inc');

    }
	// bottom frale
	else
	{

      $oLink=new urlQuery();
      $oLink->addPrm('isSearch', '0');
	  $oLink->addPrm(FORM_ID, 'f.akt.s.14');
      $searchLink = $oLink -> getQuery();
      unset($oLink);

       //Popup saites sagatave
      $oPopLink=new urlQuery;
      $oPopLink->addPrm(FORM_ID, 'f.akt.s.15');


      $sCriteria = reqVar::get('search');
      // reload frame 2
      $oLink=new urlQuery();
      $oLink->addPrm('isSearch', '0');
	  $oLink->addPrm(FORM_ID, 'f.akt.s.14');
      $oLink->addPrm('search', $sCriteria);
      $searchResultLink = $oLink -> getQuery();
      unset($oLink);

      /*$searcCriteria = array();
      $searcCriteria['yearFrom'] = dtime::getCurrentYear();
      $searcCriteria['yearUntil'] = dtime::getCurrentYear();
      $searcCriteria['monthFrom'] = dtime::getCurrentMonth();
      $searcCriteria['monthUntil'] = dtime::getCurrentMonth();
      $searcCriteria['worker'] = '-1';
       $searcCriteria['writeoff'] = '-1';
       $cr = '';
       foreach($searcCriteria as $s)
       {
         $cr .= $s.'^';
       }
       $cr = substr($cr, 0, -1);
       $sCriteria  = $cr;*/

       $res = dbProc::getActWriteOffList($sCriteria);

		include('f.akt.s.14.tpl');
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
