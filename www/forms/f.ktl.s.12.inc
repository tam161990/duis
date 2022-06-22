<?
//created by Tatjana Fedorkova at 2004.12.08.

$userId = userAuthorization::getUserId();
$isEdUser = (dbProc::isUserInRole($userId, ROLE_ED_USER) || dbProc::isUserInRole($userId, ROLE_AUDIT_USER));    
if (userAuthorization::isAdmin() || $isEdUser )
{
	$editMode = reqVar::get('editMode');
	// bottom frame
	// if insert/update/delete
	if($editMode)
	{
       
       // get roles list
       $role=array();
       $role['']=text::get('EMPTY_SELECT_OPTION');
       $res=dbProc::getKrfkName(KRFK_ROLE);
       if (is_array($res))
       {
       	foreach ($res as $row)
       	{
       		$role[$row['nosaukums']]=$row['nozime'];
       	}
       }
       unset($res);

		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.12');
		$oLink->addPrm('editMode', 1 );
		// form inicialization
		$oForm = new Form('frmMain','post',$oLink->getQuery());
		unset($oLink);

		// if operation is success, show success message and redirect top frame
		if (reqVar::get('successMessage'))
		{
			$oForm->addSuccess(reqVar::get('successMessage'));
			$oForm->addElement('static','jsRefresh2','','<script>refreshFrame(1);</script>');
		}

        // inicial state: usetrId=0;
        $usrId = reqVar::get('usrId');
		// if usrId>0 ==> user selected from the list
		if($usrId != false)
		{
			// get info about user
            $userInfo = dbProc::getUsersList($usrId);
			//print_r($userInfo);
            if(count($userInfo)>0)
			{
				$user = $userInfo[0];


                // get user info
        	    $userInfo = dbProc::getUserInfo($user['RLTT_ID']);
        	    if(count($userInfo) >0 )
        	    {
            		$userLastAction = $userInfo[0]['NOSAUKUMS'].' '.$userInfo[0]['RLTT_DATUMS'];
                }
			}
		}

        // form elements
		$oForm -> addElement('hidden', 'action', '');

        $oForm -> addElement('label', 'darbiba',  text::get('USER_LAST_ACTION'), isset($userLastAction)?$userLastAction:'');

		$oForm -> addElement('hidden', 'usrId', null, isset($user['RLTT_ID'])?$user['RLTT_ID']:'');

		$oForm -> addElement('text', 'login',  text::get('LOGIN'), isset($user['RLTT_USER_NAME'])?$user['RLTT_USER_NAME']:'', 'tabindex=4 maxlength="30"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('login', text::get('ERROR_REQUIRED_FIELD'), 'required');

		$oForm -> addElement('text', 'name',  text::get('USER_NAME'), isset($user['RLTT_VARDS'])?$user['RLTT_VARDS']:'', 'tabindex=1 maxlength="30"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('name', text::get('ERROR_REQUIRED_FIELD'), 'required');

		$oForm -> addElement('text', 'surname',  text::get('USER_SURNAME'), isset($user['RLTT_UZVARDS'])?$user['RLTT_UZVARDS']:'', 'tabindex=2 maxlength="30"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('surname', text::get('ERROR_REQUIRED_FIELD'), 'required');

		$oForm -> addElement('checkbox', 'irAdmin',  text::get('IR_ADMIN'), isset($user['RLTT_IR_ADMINS'])?$user['RLTT_IR_ADMINS']:'', 'tabindex=11'.(($isEdUser)?' disabled' : ''));

        $oForm -> addElement('select', 'role',  text::get('ROLE'), isset($user['RLTT_ROLE'])?$user['RLTT_ROLE']:'', 'tabindex=10 '.(($isEdUser)?' disabled' : ''), '', '', $role);
        unset($oLink);
		$oForm -> addElement('password', 'password', text::get('PASSWORD'), null, 'tabindex=5 maxlength="30"'.(($isEdUser)?' disabled' : ''));
        $oForm -> addRule('password', text::get('ERROR_PASSWORD_MINLENGHT_8'), 'minlength',8);

		$oForm -> addElement('password', 'password2', text::get('CONFIRM_PASSWORD'), null, 'tabindex=6 maxlength="30"'.(($isEdUser)?' disabled' : ''));
        $oForm -> addRule('password2', text::get('ERROR_PASSWORD_MINLENGHT_8'), 'minlength',8);

		$oForm -> addElement('checkbox', 'changePass',  text::get('CHANGE_PASSWORD_OK'),null,'tabindex=7 disabled'.(($isEdUser)?' disabled' : ''));

        $oForm -> addElement('kls', 'section',  text::get('ED_SECTION'), array('classifName'=>KL_ED_SECTIONS,'value'=>isset($user['RLTT_KEDI_SECTION'])?$user['RLTT_KEDI_SECTION']:'','readonly'=>false), 'tabindex=13 maxlength="2000" '.(( $isEdUser)? ' disabled ': ''));

		$oForm -> addElement('kls', 'edArea',  text::get('SINGL_ED_AREA'), array('classifName'=>KL_ED_AREA,'value'=>isset($user['RLTT_KEDI_ID'])?$user['RLTT_KEDI_ID']:'','readonly'=>false), 'tabindex=9 maxlength="2000" '.(( $isEdUser)? ' disabled ': ''));

		$oForm -> addElement('checkbox', 'isActive',  text::get('STATUS_ACTIVE_INACTIVE'), isset($user['RLTT_IR_AKTIVS'])?$user['RLTT_IR_AKTIVS']:1, 'tabindex=3 onClick="if(!this.checked){alert(\''.text::get('WARNING_USER_NOT_ACTIVE').'\');}" '.(($isEdUser)?' disabled' : ''));

		// form buttons
        if(!$isEdUser)
        {
    		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
    		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'usrId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
    		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'usrId\');parent.frame_1.unActiveRow();'));

    		$oForm -> addElement('static', 'jsButtonsControl', '', '
    			<script>
    				function refreshButton(name)
    				{
    					if (!isEmptyField(name))
    					{
    						document.all["save"].src="img/btn_saglabat.gif";
                            document.all["changePass"].disabled='.(($isEdUser)? 'true' : 'false').';

    					}
    					else
    					{
    						document.all["save"].src="img/btn_saglabat_disabled.gif";
    						document.all["changePass"].disabled=true;

    					}

    				}
    				refreshButton("usrId");
    			</script>
    		');
        }
		// if operation
		if ($oForm -> isFormSubmitted())
		{
			$check = true;
			$r = false;
			$checkRequiredFields = false;
           	if ($oForm -> getValue('login') && $oForm -> getValue('name') && $oForm -> getValue('surname') )
			{
				$checkRequiredFields = true;
			}
			if ($checkRequiredFields)
			{
				// save
				if ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('usrId'))))
				{
					// chech that user with same login name not set
					if (dbProc::isHasUserWithThisLogin($oForm->getValue('login'), ($oForm->getValue('action')==OP_UPDATE)?$oForm->getValue('usrId'):false))
					{
						$oForm->addError(text::get('ERROR_EXISTS_USER_LOGIN'));
						$check = false;
					}

					// chech that both psssword fields is not empty & are equal
					if(($oForm->getValue('action')==OP_INSERT) || ($oForm->getValue('changePass')==1))
					{
						if(reqVar::get('password') != reqVar::get('password2') || trim(reqVar::get('password2'))=='' )
						{
							$oForm -> addError(text::get('ERROR_PASSWORDS_ARE_NOT_EQUAL_OR_NOT_SET'));
							$check = false;
						}
						// chech that password contains letters, numbers and allowed simbols
						elseif(!preg_match("/^([A-Z]|[a-z]|[0-9]|_|-|@|#|%|&|=|\\$|\\^|\\*|\\+)*$/",reqVar::get('password')))
						{
							$oForm -> addError(text::get('ERROR_UNCORRECT_PASSWORD_SYMBOLS'));
							$check = false;
						}
          			}
					// if all is ok, do operation
					if($check)
					{
						$r=dbProc::saveUser(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('usrId'):false),
						$oForm->getValue('login'),
						$oForm->getValue('name'),
						$oForm->getValue('surname'),
						$oForm->getValue('irAdmin',0),
						$oForm->getValue('edArea'),
						(($oForm->getValue('action')==OP_INSERT) || ($oForm->getValue('changePass')==1))?$oForm->getValue('password'):false,
						$oForm->getValue('isActive', 0),
                        $oForm->getValue('role'),
                        '',
                        $oForm->getValue('section')
						);

						if (!$r)
						{
							$oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
						}
					}
				}

				// if operation was compleated succefully, show success mesage and redirect current frame
				if ($r)
				{
					$oLink=new urlQuery();
					$oLink->addPrm(FORM_ID, 'f.ktl.s.12');
					$oLink->addPrm('editMode', '1');
					switch($oForm->getValue('action'))
					{
						case OP_INSERT:
							$oLink->addPrm('successMessage', text::get('USER_WAS_ADDED'));
							break;
						case OP_UPDATE:
							$oLink->addPrm('successMessage', text::get('USER_WAS_UPDATED'));
							break;

					}
					RequestHandler::makeRedirect($oLink->getQuery());
				}
			}
			else
			{
				$oForm->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
			}
		}

		$oForm -> makeHtml();
		include('f.ktl.s.12.2.tpl');
	}
	// top frale
	else
	{
        // Check if this form was requested via xmlHttpRequest and search
    	if (isset($_GET['xml']) && isset($_GET['search_q']) && isset($_GET['search_c']))
    	{
    		ob_clean();
    		$q = $_GET['search_q'];
            if (isset($q) || $q == 0)
    		{
    			echo 'q = "'.trim($q).'";';
    		}
            else
            {
    			echo 'q = "";';
    		}
            $c = $_GET['search_c'];
            if ($c)
    		{
    			echo 'c = "'.$c.'";';
    		}
            else
            {
    			echo 'c = "";';
    		}
		    exit;
    	}
        if (isset($_GET['xml']) && isset($_GET['sort_k']) && isset($_GET['sort_o']))
    	{
    		ob_clean();
    		$o = $_GET['sort_o'];
            if (isset($o))
    		{
    			echo 'o = "'.$o.'";';
    		}
            else
            {
    			echo 'o = "";';
    		}
            $k = $_GET['sort_k'];
            if ($k)
    		{
    			echo 'k = "'.$k.'";';
    		}
            else
            {
    			echo 'k = "";';
    		}
		    exit;
    	}
        // set list title
        $title = text::toUpper(text::get('USERS'));
        // get search column list
        $columns=dbProc::getKlklName(KL_USERS);
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;


        // default sort column
        $defaultColumn = dbProc::getKlklDefaultColumn(KL_USERS);

        // URL to search Zinojums by number.
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.12');
    	$oLink->addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		$amount=dbProc::getUsersCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.12');
		$oLink->addPrm('editMode', 1);

		// gel list of users
		$res = dbProc::getUsersList( false, true,
                                        $listing->getStartPosition(),
                                        $listing->getAmountOnPage(),
                                        $searchText,
                                        (($searchColumn === false) ? $defaultColumn : $searchColumn),
                                        $sortOrder,
                                        $orderColumn);

		if (is_array($res))
		{
			foreach ($res as $i=>$row)
			{
				// add dv area Id to each link
				$oLink->addPrm('usrId', $row['RLTT_ID']);
				$res[$i]['URL']=$oLink ->getQuery();
			}
		}
		unset($oLink);

		// inicial state of users number
		$number=$listing->getStartPosition()+1;

		include('f.ktl.s.x.1.tpl');
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>