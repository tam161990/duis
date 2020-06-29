<?
$projectId = reqVar::get('projectId');

$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEdUser = dbProc::isUserInRole($userId, ROLE_ED_USER);
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);
// Report links


    if(true/*$isEdUser || $isAdmin*/)
    {
         // Darbu izpildes aktu kopsavilkums (fiziskais paraksts)
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
        $oLink->addPrm('isTrase', '0');
		$oLink->addPrm('sign', 'P');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.1');
    	$actTotalReportLinkP=$oLink ->getQuery();
    	unset($oLink);
		 // Darbu izpildes aktu kopsavilkums (e-paraksts)
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
        $oLink->addPrm('isTrase', '0');
		$oLink->addPrm('sign', 'E');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.1');
    	$actTotalReportLinkE=$oLink ->getQuery();
    	unset($oLink);

        // Veiktâ darba pozîciju kopsavilkums
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
         $oLink->addPrm('isTrase', '0');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.2');
    	$workTotalReportLink=$oLink ->getQuery();
    	unset($oLink);

        // Akts par izlietotiem materiâliem
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
         $oLink->addPrm('isTrase', '0');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.3');
    	$materialTotalReportLink=$oLink ->getQuery();
    	unset($oLink);

        // act summary
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
         $oLink->addPrm('isTrase', '0');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.4');
    	$actMainReportLink=$oLink ->getQuery();
    	unset($oLink);

        // pfisical showing
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
         $oLink->addPrm('isTrase', '0');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.5');
    	$workPhisicalShowingReportLink=$oLink ->getQuery();
    	unset($oLink);

        // act summary all ststuss
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.6');
    	$actMainReportStstusLink=$oLink ->getQuery();
    	unset($oLink);



        ///////////////////////////
        //TRASES
        //////////////////////////
        // Darbu izpildes aktu kopsavilkums (fiziskais paraksts)
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
        $oLink->addPrm('isTrase', '1');
		$oLink->addPrm('sign', 'P');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.1');
    	$actTrTotalReportLinkP=$oLink ->getQuery();
    	unset($oLink);
		// Darbu izpildes aktu kopsavilkums (e-paraksts)
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
        $oLink->addPrm('isTrase', '1');
		$oLink->addPrm('sign', 'E');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.1');
    	$actTrTotalReportLinkE=$oLink ->getQuery();
    	unset($oLink);

        // Veiktâ darba pozîciju kopsavilkums
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
        $oLink->addPrm('isTrase', '1');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.2');
    	$workTrTotalReportLink=$oLink ->getQuery();
    	unset($oLink);

        // Akts par izlietotiem materiâliem
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
        $oLink->addPrm('isTrase', '1');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.3');
    	$materialTrTotalReportLink=$oLink ->getQuery();
    	unset($oLink);

        // act summary
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
        $oLink->addPrm('isTrase', '1');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.4');
    	$actTrMainReportLink=$oLink ->getQuery();
    	unset($oLink);

        // mms izpilde
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
        $oLink->addPrm('isTrase', '1');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.7');
    	$actTrMmsCalc=$oLink ->getQuery();
    	unset($oLink);
    }

include('f.rpt.s.0.tpl');
?>