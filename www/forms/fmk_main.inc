<?
//created by Tatjana Fedorkova at 2004.12.02.
   
// Top frame
$oLink=new UrlQuery();
$oLink->addPrm(FORM_ID, 'f.inf.s.1');
$oLink->addPrm('isNew', '1');
$frameTopUrl = $oLink->getQuery();
unset($oLink);

// frame #1
$oLink=new UrlQuery();
$oLink->addPrm(FORM_ID, 'blank');
$oLink->addPrm('isNew', '1');
$frame1Url = $oLink->getQuery();
unset($oLink);

// frame #2
$oLink=new UrlQuery();
$oLink->addPrm(FORM_ID, 'blank');
$oLink->addPrm('isNew', '1');
$frame2Url = $oLink->getQuery();
unset($oLink);

// Buttons frame
$oLink=new UrlQuery();
$oLink->addPrm(FORM_ID, 'blank');
$oLink->addPrm('isNew', '1');
$frameButtonsUrl = $oLink->getQuery();
unset($oLink);

include('fmk_main.tpl');
?>