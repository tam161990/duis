<?
// Created by Tatjana Fedorkova
if (userAuthorization::isAdmin())
{
  $oLink=new urlQuery();
  $oLink->addPrm(FORM_ID, 'f.adm.s.7');
  $oForm = new Form('frmMain','post',$oLink->getQuery());
  unset($oLink);

  // get info about system
  $systemInfo = dbProc::getSystemInfo();
  if(count($systemInfo)>0)
  {
  	$info = $systemInfo[0];
  }



  $oForm -> addElement('text', 'inflation_persent',  text::get('INFLATION_PERCENT'), isset($info['SNFO_INFLATION'])?$info['SNFO_INFLATION']:'1', 'tabindex=1 maxlength="4"' );
  $oForm -> addRule('inflation_persent', text::get('ERROR_REQUIRED_FIELD'), 'required');
  $oForm -> addRule('inflation_persent', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);

  $oForm -> addElement('submitImg', 'submit', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20"');

  if ($oForm -> isFormSubmitted())
  {

        $r = false;

     	$r = dbProc::saveSystemInfo( '', '', '', $oForm->getValue('inflation_persent'));

	  	if (!$r)
	  	{
	  		$oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
	    }
  }
  $oForm -> makeHtml();
  include('f.adm.s.7.tpl');
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>