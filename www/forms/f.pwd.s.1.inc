<?
// Created by Tatjana Fedorkova 
$userId = userAuthorization::getUserId();

$oLink=new urlQuery();
$oLink->addPrm(FORM_ID, 'f.pwd.s.1');
$oLink->addPrm('isNew', '1');
$oForm = new Form('frmMain','post',$oLink->getQuery());
unset($oLink);
$oForm -> addElement('password', 'oldPassword', text::get('OLD_PASSWORD'), null, 'maxlength="30"');
$oForm -> addRule('oldPassword', text::get('ERROR_REQUIRED_FIELD'), 'required');

$oForm -> addElement('password', 'password', text::get('NEW_PASSWORD'), null, 'maxlength="30"');
$oForm -> addRule('password', text::get('ERROR_REQUIRED_FIELD'), 'required');
$oForm -> addRule('password', text::get('ERROR_PASSWORD_MINLENGHT_8'), 'minlength',8);
$oForm -> addElement('password', 'password2', text::get('CONFIRM_PASSWORD'), null, 'maxlength="30"');
$oForm -> addRule('password2', text::get('ERROR_REQUIRED_FIELD'), 'required');
$oForm -> addRule('password2', text::get('ERROR_PASSWORD_MINLENGHT_8'), 'minlength',8);
$oForm -> addElement('submitImg', 'submit', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20"');


if ($oForm -> isFormSubmitted())
{
    if(!dbProc::isUserPassword($userId, reqVar::get('oldPassword')))
	{
		$oForm -> addError(text::get('ERROR_OLD_PASWORD_NOT_CORRECT'));
	}
    elseif(reqVar::get('password') != reqVar::get('password2') || trim(reqVar::get('password2'))=='' )
	{
		$oForm -> addError(text::get('ERROR_PASSWORDS_ARE_NOT_EQUAL'));
	}
	elseif(!preg_match("/^([A-Z]|[a-z]|[0-9]|_|-|@|#|%|&|=|\\$|\\^|\\*|\\+)*$/",reqVar::get('password')))
	{
		$oForm -> addError(text::get('ERROR_UNCORRECT_PASSWORD_SYMBOLS'));
	}
	else
	{
		if(dbProc::changeUserPassword($userId, reqVar::get('password')))
		{
			$oForm -> addSuccess(text::get('SUCCESS_PASSWORD_CHANGING'));
		}
		else
		{
			$oForm -> addError(text::get('ERROR_IN_DB_QUERY').(dbProc::getError()));
		}
	}
}
$oForm -> makeHtml();
include('f.pwd.s.1.tpl');
?>