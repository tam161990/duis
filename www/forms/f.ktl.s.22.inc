<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isEdUser = (dbProc::isUserInRole($userId, ROLE_ED_USER) || dbProc::isUserInRole($userId, ROLE_AUDIT_USER));    
if (userAuthorization::isAdmin() || $isEdUser )
{
	$editMode = reqVar::get('editMode');
	// bottom frame
	// if insert/update

     if($editMode)
	{
		$workTypeId = reqVar::get('workTypeId');

		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.22');
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

		$group=array();
		// get grupas list
		$group['']=text::get('EMPTY_SELECT_OPTION');		
		$res=dbProc::getWorkTyps();
		if (is_array($res))
		{
			foreach ($res as $row)
			{
				$group[$row['KLDV_VEIDS']]=$row['KLDV_VEIDS'];
			}
		}
		unset($res);

		// inicial state: workTypeId=0;
		// if workTypeId>0 ==> voltage selected from the list
		if($workTypeId != false)
		{
			// get info about voltage
			$workTypeInfo = dbProc::getWorkTypeList($workTypeId);
			//print_r($getWorkTypeList);
			if(count($workTypeInfo)>0)
			{
				$workType = $workTypeInfo[0];
			}
        }

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'workTypeId', null, isset($workType['KLDV_ID'])? $workType['KLDV_ID']:'');

        $oForm -> addElement('text', 'nosaukums',  text::get('NAME'), isset($workType['KLDV_NOSAUKUMS'])?$workType['KLDV_NOSAUKUMS']:'', 'maxlength="250"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('nosaukums', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('nosaukums', text::get('ERROR_MAXLENGHT_REACHED'), 'maxlength',250);

		$oForm -> addElement('select', 'type',  text::get('TYPE'), isset($workType['KLDV_VEIDS'])?$workType['KLDV_VEIDS']:'', 'tabindex=2'.(($isEdUser)? ' disabled ': ''), '', '', $group);
		$oForm -> addRule('type', text::get('ERROR_REQUIRED_FIELD'), 'required');

		$oForm -> addElement('checkbox', 'isActive',  text::get('IS_ACTIVE'), isset($workType['KLDV_IR_AKTIVS'])?$workType['KLDV_IR_AKTIVS']:1, ''.(($isEdUser)?' disabled' : ''));

		// form buttons
        if(!$isEdUser)
        {
      		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
      		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'workTypeId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
      		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'workTypeId\');parent.frame_1.unActiveRow();'));

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
      				refreshButton("workTypeId");
      			</script>
      		');
        }
		// if operation
		if ($oForm -> isFormSubmitted())
		{
			$check = true;
			$r = false;
			$checkRequiredFields = false;
			if ($oForm -> getValue('type') && $oForm -> getValue('nosaukums') )
			{
				$checkRequiredFields = true;
			}
			if ($checkRequiredFields)
			{
				// save
				if ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('workTypeId'))))
				{
					
					// if all is ok, do operation
					if($check)
					{
						$r=dbProc::saveWorkType(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('workTypeId'):false),
						$oForm->getValue('nosaukums'),
						$oForm->getValue('type'),
						$oForm->getValue('isActive',0)
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
					$oLink->addPrm(FORM_ID, 'f.ktl.s.22');
					$oLink->addPrm('editMode', '1');
					switch($oForm->getValue('action'))
					{
						case OP_INSERT:
							$oLink->addPrm('successMessage', text::get('RECORD_WAS_ADDED'));
							break;
						case OP_UPDATE:
							$oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));
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
		include('f.ktl.s.22.2.tpl');
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
        $title = text::toUpper(text::get('WORK_TYPES'));
        // get search column list
        $columns=dbProc::getKlklName(KL_WORK_TYPS);
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;

        // default sort column
        $defaultColumn = dbProc::getKlklDefaultColumn(KL_WORK_TYPS);

        // URL to search Zinojums by number.
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.22');
    	$oLink->addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		$amount=dbProc::getWorkTypeCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.22');
		$oLink->addPrm('editMode', 1);

		// gel list of users
		$res = dbProc::getWorkTypeList( false,
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
				$oLink->addPrm('workTypeId', $row['KLDV_ID']);
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
