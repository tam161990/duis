<?
// Created by Tatjana Fedorkova
if (userAuthorization::isAdmin())
{
  $oLink=new urlQuery();
  $oLink->addPrm(FORM_ID, 'f.adm.s.5');
  $oForm = new Form('frmMain','post',$oLink->getQuery());
  unset($oLink);

  // get info about system
  $systemInfo = dbProc::getSystemInfo();
  if(count($systemInfo)>0)
  {
  	$info = $systemInfo[0];
  }



  $oForm -> addElement('text', 'superadmin_name',  text::get('SUPERADMIN_NAME'), isset($info['SNFO_SUPERADMIN'])?$info['SNFO_SUPERADMIN']:'', 'tabindex=1 maxlength="50"' );
  $oForm -> addRule('superadmin_name', text::get('ERROR_REQUIRED_FIELD'), 'required');

  $oForm -> addElement('submitImg', 'submit', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20"');

  if ($oForm -> isFormSubmitted())
  {

        $r = false;

     	$r = dbProc::saveSystemInfo( '', '', $oForm->getValue('superadmin_name'));

	  	if (!$r)
	  	{
	  		$oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
	    }
  }
  $oForm -> makeHtml();
  include('f.adm.s.5.tpl');
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>