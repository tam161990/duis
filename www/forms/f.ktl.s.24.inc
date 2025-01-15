<?
$userId = userAuthorization::getUserId();
$isEdUser = (dbProc::isUserInRole($userId, ROLE_ED_USER) || dbProc::isUserInRole($userId, ROLE_AUDIT_USER));    
if (userAuthorization::isAdmin() || $isEdUser )
{
	$editMode = reqVar::get('editMode');
	// bottom frame
	// if insert/update

     if($editMode)
	{
		$writeOffCodeId = reqVar::get('writeOffCodeId');

		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.24');
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
		
		if($writeOffCodeId != false)
		{
			// get info about ED area
			$writeOffCodeInfo = dbProc::getWriteOffCodesList($writeOffCodeId);
			//print_r($edAreaInfo);
			if(count($writeOffCodeInfo)>0)
			{
				$writeOffCode = $writeOffCodeInfo[0];
			}
			// get user info
			$creator = '';
			$editor = '';
			$userInfo = dbProc::getUserInfo($writeOffCode['KWRC_CREATOR']);
			if(count($userInfo) >0 )
			{
				$creator = $userInfo[0]['RLTT_VARDS']. ' ' .$userInfo[0]['RLTT_UZVARDS'];
			}
			$userInfo1 = dbProc::getUserInfo($writeOffCode['KWRC_EDITOR']);
			if(count($userInfo1) >0 )
			{
				$editor = $userInfo1[0]['RLTT_VARDS']. ' ' .$userInfo1[0]['RLTT_UZVARDS'];
			}
        }

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'writeOffCodeId', null, isset($writeOffCode['KWRC_ID'])? $writeOffCode['KWRC_ID']:'');        

		$oForm -> addElement('text', 'kalculk_kods',  text::get('CALCULATION_CODE'), isset($writeOffCode['KWRC_KKAL_SHIFRS'])?$writeOffCode['KWRC_KKAL_SHIFRS']:'', 'tabindex=1 maxlength="5"' . (($writeOffCodeId || $isEdUser)?' disabled' : ''));
		$oForm -> addRule('kalculk_kods', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('kalculk_kods', text::get('ERROR_ALPHANUMERIC_VALUE'), 'alphanumeric');

        $oForm -> addElement('text', 'kalk_nosaukums',  text::get('EXPORT_CALCULATION_NAME'), isset($writeOffCode['KWRC_KKAL_NOSAUKUMS'])?$writeOffCode['KWRC_KKAL_NOSAUKUMS']:'', 'tabindex=2 maxlength="150"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('kalk_nosaukums', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('text', 'kods',  text::get('WRITE_OFF_CODE'), isset($writeOffCode['KWRC_KODS'])?$writeOffCode['KWRC_KODS']:'', 'tabindex=3 maxlength="7"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('kods', text::get('ERROR_REQUIRED_FIELD'), 'required');
  $oForm -> addRule('kods', text::get('ERROR_NUMERIC_VALUE'), 'numeric');
        
        $oForm -> addElement('text', 'nosaukums',  text::get('WRITE_OFF_TITLE'), isset($writeOffCode['KWRC_NOSAUKUMS'])?$writeOffCode['KWRC_NOSAUKUMS']:'', 'tabindex=4 maxlength="150"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('nosaukums', text::get('ERROR_REQUIRED_FIELD'), 'required');

		// importa dati
		$oForm -> addElement('text', 'created',  text::get('CREATED'), isset($writeOffCode['KWRC_CREATED'])?$writeOffCode['KWRC_CREATED']:dtime::now(), 'tabindex=21 maxlength="20" disabled');
		$oForm -> addElement('text', 'creator',  text::get('CREATOR'), isset($creator)?$creator:'', 'tabindex=21 maxlength="20" disabled');
		$oForm -> addElement('text', 'edited',  text::get('EDITED'), isset($writeOffCode['KWRC_EDITED'])?$writeOffCode['KWRC_EDITED']:dtime::now(), 'tabindex=21 maxlength="20" disabled');
		$oForm -> addElement('text', 'editor',  text::get('EDITOR'), isset($editor)?$editor:'', 'tabindex=21 maxlength="20" disabled');


		// form buttons
        if(!$isEdUser)
        {
      		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
      		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'writeOffCodeId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
      		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'writeOffCodeId\');parent.frame_1.unActiveRow();'));
          
           	$oForm -> addElement('static', 'jsButtonsControl', '', '
      			<script>
      				function refreshButton(name)
      				{
      					if (!isEmptyField(name))
      					{
      						document.all["save"].src="img/btn_saglabat.gif";

      					}
      					else
      					{
      						document.all["save"].src="img/btn_saglabat_disabled.gif";

      					}
      				}
      				refreshButton("writeOffCodeId");
      			</script>
      		');
        }
		// if operation
		if ($oForm -> isFormSubmitted())
		{
			$check = true;
			$r = false;
			$checkRequiredFields = false;
            
            // save
			if ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('writeOffCodeId'))))
			{
      			if ( $oForm -> getValue('kods') && $oForm -> getValue('kalculk_kods') &&
                      $oForm -> getValue('nosaukums') && $oForm -> getValue('kalk_nosaukums') )
      			{
      				$checkRequiredFields = true;
      			}
      			if ($checkRequiredFields)
      			{

					// chech that ED area with same code not set
					if (dbProc::writeOffCodesCodeExists(
                                                            $oForm->getValue('kods'),
                                                            ($oForm->getValue('action')==OP_UPDATE)?$oForm->getValue('writeOffCodeId'):false)
                                                            )
					{
						$oForm->addError(text::get('ERROR_EXISTS_WRITE_OFF_CODE'));
						$check = false;
					}

					// if all is ok, do operation
					if($check)
					{
						$r=dbProc::saveWriteOffCode(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('writeOffCodeId'):false),
						$oForm->getValue('kods'),
						$oForm->getValue('nosaukums'),
                        $oForm->getValue('kalculk_kods') ,
                        $oForm->getValue('kalk_nosaukums') ,
						$userId
						);

						if (!$r)
						{
							$oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
						}
					}
				}
			}
			else
			{
				$oForm->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
			}
            // if operation was compleated succefully, show success mesage and redirect current frame
    		if ($r)
    		{
    			$oLink=new urlQuery();
    			$oLink->addPrm(FORM_ID, 'f.ktl.s.24');
    			$oLink->addPrm('editMode', '1');
    			switch($oForm->getValue('action'))
    			{
    				case OP_INSERT:
    					$oLink->addPrm('successMessage', text::get('RECORD_WAS_ADDED'));
    					break;
    				case OP_UPDATE:
    					$oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));
    					break;
                    case OP_DELETE:
    					$oLink->addPrm('successMessage', text::get('FAVORITS_IS_CLENED'));
    					break;
    			}
    			RequestHandler::makeRedirect($oLink->getQuery());
    		}
		}

       	$oForm -> makeHtml();
		include('f.ktl.s.24.2.tpl');
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
        $title = text::toUpper(text::get('WRITE_OFF_CODES'));
        // get search column list
        $columns=dbProc::getKlklName(KL_WRITEOFF_CODES);
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;


        // default sort column
        $defaultColumn = dbProc::getKlklDefaultColumn(KL_WRITEOFF_CODES);
        
        // URL to search Zinojums by number.
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.24');
    	$oLink->addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		$amount=dbProc::getWriteOffCodesCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
        
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.24');
		$oLink->addPrm('editMode', 1);

		// gel list of users
		$res = dbProc::getWriteOffCodesList( false,
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
				$oLink->addPrm('writeOffCodeId', $row['KWRC_ID']);
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
