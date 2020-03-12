<?
// Created by Tatjana Fedorkova
if (userAuthorization::isAdmin())
{
  $oLink=new urlQuery();
  $oLink->addPrm(FORM_ID, 'f.adm.s.3');
  $oForm = new Form('frmMain','post',$oLink->getQuery());
  unset($oLink);

  // get info about system
  $systemInfo = dbProc::getSystemInfo();
  if(count($systemInfo)>0)
  {
  	$info = $systemInfo[0];
  }



  $oForm -> addElement('text', 'link_tpl',  text::get('LINK_TEMPLATE'), isset($info['SNFO_LINK_TMPL'])?$info['SNFO_LINK_TMPL']:'', 'tabindex=1 maxlength="200"' );
  $oForm -> addRule('link_tpl', text::get('ERROR_REQUIRED_FIELD'), 'required');
  $oForm -> addRule('link_tpl', text::get('ERROR_URL_VALUE'), 'url');

  $oForm -> addElement('submitImg', 'submit', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20"');

  if ($oForm -> isFormSubmitted())
  {

        $r = false;

     	$r = dbProc::saveSystemInfo( '', $oForm->getValue('link_tpl'));

	  	if (!$r)
	  	{
	  		$oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
	    }
  }
  $oForm -> makeHtml();
  include('f.adm.s.3.tpl');
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>