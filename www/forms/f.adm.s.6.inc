<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();

// tikai  sist�mas lietotajam vai administr�toram ir pieeja!
if($isAdmin)
{
	$searchMode = reqVar::get('isSearch');
	// top frame
    if($searchMode)
	{
        $oLink=new urlQuery();
    	$oLink->addPrm(FORM_ID, 'f.adm.s.6');
    	$oLink->addPrm('isSearch', 1 );
    	// form inicialization
    	$oForm = new Form('frmMain','post',$oLink->getQuery());
    	unset($oLink);

        $oLink=new urlQuery();
	    $oLink->addPrm('isReturn', '1');
        $oLink->addPrm('isSearch', 1 );
	    $oLink->addPrm(FORM_ID, 'f.adm.s.6');
	    $criteriaLink=$oLink ->getQuery();
	    unset($oLink);

        // if operation
    	if ($oForm -> isFormSubmitted())
    	{
            $oListLink=new urlQuery();
            $oListLink->addPrm(FORM_ID, 'f.adm.s.6');
        }
        $searchTitle = text::toUpper(text::toUpper(text::get('EVENT_LOG')));
        $searchName = 'EVENT_LOG';
        
        include('f.akt.m.8.inc');
	}
	// bottom frale
	else
	{
	    $sCriteria = reqVar::get('search');
        // gel list
		$res = dbProc::getEventList($sCriteria);
        /*echo "<pre>";
        print_r($res);
        echo "</pre>"; */

		include('f.adm.s.6.tpl');
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
