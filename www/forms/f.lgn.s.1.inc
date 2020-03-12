<?
// get info about system
$systemInfo = dbProc::getSystemInfo();
if(count($systemInfo)>0)
{
  	$info = $systemInfo[0];
}


$oForm = new Form('frmLogin','post','/');
$oForm -> addElement('text', 'login', text::get('LOGIN'), RequestHandler::getLastAccessLogin(), 'maxlength="30" style="margin-left:30px;width:200px;border: 1px solid #d1d1d1"',false, false,false,true);
$oForm -> addRule('login', text::get('ERROR_REQUIRED_FIELD'), 'required');
$oForm -> addElement('password', 'password', text::get('PASSWORD'), null, 'maxlength="30" style="margin-left:30px;width:200px; border: 1px solid #d1d1d1"',false, false,false,true);
$oForm -> addRule('password', text::get('ERROR_REQUIRED_FIELD'), 'required');

$oForm -> addElement('literal', 'warningIcon', '', isset($info['SNFO_WARNING'])? '<img src="img/ico_attention.gif" alt="" width="41" height="37" class="block">':'');
$oForm -> addElement('literal', 'warning', '', isset($info['SNFO_WARNING'])? nl2br($info['SNFO_WARNING']):'');


$oForm -> addElement('literal', 'instruction', text::get('LOGIN_INSTRUCTION'), '');
$oForm -> addElement('literal', 'problem', text::get('LOGIN_PROBLEM'), '');



$oForm -> addElement('submitImg', 'submit', text::get('CONNECT'), 'img/btn_pieslegties.gif', 'width="70" height="20"');

if ($oForm -> isFormSubmitted())
{
	if(dbProc::isExistsUserLoginAndPassword($oForm -> getValue('login'), $oForm -> getValue('password')) && dbProc::isUserNotInRole($oForm -> getValue('login'),$oForm -> getValue('password')))
	{
		$oForm -> addError(text::get('ERROR_USER_HAVE_NO_RIGHTS'));
	}
	else
	{
		$oForm -> addError(text::get('ERROR_INCORRECT_LOGIN_OR_PASSWORD'));
	}
}
$oForm -> makeHtml();
include('f.lgn.s.1.tpl');
?>