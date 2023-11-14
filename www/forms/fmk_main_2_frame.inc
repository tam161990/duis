<?
//created by Tatjana Fedorkova at 2004.12.02.
$url  = reqVar::get('url'); 
$id = reqVar::get('id');
// frame #1
$oLink=new UrlQuery();
$oLink->addPrm(FORM_ID, $url);
$oLink->addPrm('id', $id);
$oLink->addPrm('isNew', '1');
$frame1Url = $oLink->getQuery();
unset($oLink);

// frame #2
$oLink=new UrlQuery();
$oLink->addPrm(FORM_ID, $url);
$oLink->addPrm('isNew', '1');
$oLink->addPrm('editMode',1);
$oLink->addPrm('id',$id);
$frame2Url = $oLink->getQuery();
unset($oLink);

include('fmk_main_2_frame.tpl');
?>