<?
// get user info
$userInfo = dbProc::getUserInfo($userId);
// if came back from act
$selectedId = reqVar::get('selectedId');
// if operation
if ($oForm -> isFormSubmitted())
{
   $actNumber = $oForm->getValue('number');
   $oListLink->addPrm('search', $actNumber);
   $actListLink=$oListLink ->getQuery();
   $oForm->addElement('static','jsRefresh2','','<script>reloadFrame(2, "'.$actListLink.'");</script>');
   unset($oListLink);
}
else
{
   $actNumber = '';
}

$oForm -> addElement('text', 'number', text::get('ACT_NUMBER'), isset($selectedId)?$selectedId:'', 'style="width:200px;"', false, false,false,true);

// form buttons
$oForm -> addElement('submitImg', 'search', text::get('SEARCH'), 'img/btn_meklet.gif', 'width="70" height="20"');

$oForm -> makeHtml();
include('f.akt.m.3.tpl');
?>