<?
// Created by Tatjana Fedorkova
if (userAuthorization::isAdmin())
{
  $oLink=new urlQuery();
  $oLink->addPrm(FORM_ID, 'f.adm.s.1');
  $oForm = new Form('frmMain','post',$oLink->getQuery());
  unset($oLink);

  // get info about system
  $systemInfo = dbProc::getSystemInfo();
  if(count($systemInfo)>0)
  {
  	$info = $systemInfo[0];
  }

  $oForm -> addElement('textarea', 'warning', text::get('WARNING'), isset($info['SNFO_WARNING'])?$info['SNFO_WARNING']:'','tabindex=7');
  $oForm -> addRule('warning', text::get('ERROR_MAXLENGHT_REACHED'), 'maxlength',2000);
  $oForm -> addElement('submitImg', 'submit', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20"');

  if ($oForm -> isFormSubmitted())
  {

        $r = false;
        //$r = dbProc::insertMessage($oForm->getValue('warning'));
     	$r = dbProc::saveSystemInfo($oForm->getValue('warning'));

	  	if (!$r)
	  	{
	  		$oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
	    }
  }
  $oForm -> makeHtml();
  include('f.adm.s.1.tpl');
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>