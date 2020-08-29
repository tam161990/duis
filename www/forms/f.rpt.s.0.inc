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

        // Veikt� darba poz�ciju kopsavilkums
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
		$oLink->addPrm('isTrase', '0');
		$oLink->addPrm('sign', 'P');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.2');
    	$workTotalReportLinkP=$oLink ->getQuery();
		unset($oLink);
		// Veikt� darba poz�ciju kopsavilkums
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
		$oLink->addPrm('isTrase', '0');
		$oLink->addPrm('sign', 'E');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.2');
    	$workTotalReportLinkE=$oLink ->getQuery();
    	unset($oLink);

        // Akts par izlietotiem materi�liem
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
		$oLink->addPrm('isTrase', '0');
		$oLink->addPrm('sign', 'P');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.3');
    	$materialTotalReportLinkP=$oLink ->getQuery();
    	unset($oLink);
		// Akts par izlietotiem materi�liem
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
		$oLink->addPrm('isTrase', '0');
		$oLink->addPrm('sign', 'E');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.3');
    	$materialTotalReportLinkE=$oLink ->getQuery();
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

        // Veikt� darba poz�ciju kopsavilkums
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
		$oLink->addPrm('isTrase', '1');
		$oLink->addPrm('sign', 'P');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.2');
    	$workTrTotalReportLinkP=$oLink ->getQuery();
		unset($oLink);
		// Veikt� darba poz�ciju kopsavilkums
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
		$oLink->addPrm('isTrase', '1');
		$oLink->addPrm('sign', 'E');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.2');
    	$workTrTotalReportLinkE=$oLink ->getQuery();
    	unset($oLink);

        // Akts par izlietotiem materi�liem
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
		$oLink->addPrm('isTrase', '1');
		$oLink->addPrm('sign', 'P');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.3');
    	$materialTrTotalReportLinkP=$oLink ->getQuery();
    	unset($oLink);
		// Akts par izlietotiem materi�liem
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
		$oLink->addPrm('isTrase', '1');
		$oLink->addPrm('sign', 'E');
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.3');
    	$materialTrTotalReportLinkE=$oLink ->getQuery();
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