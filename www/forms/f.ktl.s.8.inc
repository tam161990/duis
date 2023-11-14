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
		$workerId = reqVar::get('workerId');


		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.8');
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

		// inicial state: workerId=0;
		// if workerId>0 ==>  selected from the list
		if($workerId != false)
		{
			// get info about voltage
			$workerOwnerInfo = dbProc::getWorkOwnerList($workerId);
			//print_r($workerOwnerInfo);
			if(count($workerOwnerInfo)>0)
			{
				$worker = $workerOwnerInfo[0];
			}
        }

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'workerId', null, isset($worker['KWOI_ID'])? $worker['KWOI_ID']:'');

        $oForm -> addElement('text', 'nosaukums',  text::get('NAME'), isset($worker['KWOI_NOSAUKUMS'])?$worker['KWOI_NOSAUKUMS']:'', 'maxlength="250"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('nosaukums', text::get('ERROR_REQUIRED_FIELD'), 'required');

		$oForm -> addElement('text', 'nosaukums2',  text::get('NAME2'), isset($worker['KWOI_NOSAUKUMS2'])?$worker['KWOI_NOSAUKUMS2']:'', 'maxlength="250"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('nosaukums2', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('text', 'kods',  text::get('CODE'), isset($worker['KWOI_KODS'])?$worker['KWOI_KODS']:'', 'maxlength="13"' . (($isEdUser)?' disabled' : ''));
	 	$oForm -> addRule('kods', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('kods', text::get('ERROR_ALPHANUMERIC_VALUE'), 'alphanumeric');

        $oForm -> addElement('static', 'number',  text::get('KWOI_VV_NUMBER'), isset($worker['CONTRACT_NO'])?$worker['CONTRACT_NO']:'', 'maxlength="20"' . (($isEdUser)?' disabled' : ''));
	 	$oForm -> addRule('number', text::get('ERROR_REQUIRED_FIELD'), 'required');

       	$oForm -> addElement('static', 'trase_number',  text::get('KWOI_TRASE_VV_NUMBER'), isset($worker['CONTRACT_NO_TR'])?$worker['CONTRACT_NO_TR']:'', 'maxlength="20"' . (($isEdUser)?' disabled' : ''));

		$oForm -> addElement('checkbox', 'isActive',  text::get('IS_ACTIVE'), isset($worker['KWOI_IR_AKTIVS'])?$worker['KWOI_IR_AKTIVS']:1, ''.(($isEdUser)?' disabled' : ''));

        //$oForm -> addElement('kls', 'section',  text::get('ED_SECTION'), array('classifName'=>KL_ED_SECTIONS,'value'=>isset($worker['KWOI_ED_SECTION'])?$worker['KWOI_ED_SECTION']:'','readonly'=>false), 'tabindex=1 maxlength="2000"'.(($isEdUser)?' disabled' : ''));
        //$oForm -> addRule('section', text::get('ERROR_REQUIRED_FIELD'), 'required');

		// form buttons
        if(!$isEdUser)
        {
            if(isset($worker['KWOI_KODS']))
            {
               //Popup saites sagatave
              $oPopLink=new urlQuery;
			  $oPopLink->addPrm(url, 'f.ktl.s.15');
			  $oPopLink->addPrm(FORM_ID,'fmk_main_2_frame');			  
              $oPopLink->addPrm('id',$worker['KWOI_KODS']);

			  $oForm -> addElement('buttonImg', 'view', text::get('EDIT'), 'img/btn_edit.bmp', 'width="50" height="23" onclick="let newWin=window.open(\''.$oPopLink ->getQuery().'\', \'frmMain1\',\'toolbar=no,resizable=yes,scrollbars=yes,width=800,height=600\'); " '.(isset($worker['KWOI_KODS'])?'':' disabled '));
			  unset($oPopLink);
            }
            else
            {
                $oForm -> addElement('buttonImg', 'view', text::get('EDIT'), 'img/btn_edit.bmp', 'width="50" height="23"  '.(isset($worker['KWOI_KODS'])?'':' disabled '));

            }
    		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
    		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'workerId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
    		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'workerId\');parent.frame_1.unActiveRow();'));

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
    				refreshButton("workerId");
    			</script>
    		');
        }
		// if operation
		if ($oForm -> isFormSubmitted())
		{
			$check = true;
			$r = false;
			$checkRequiredFields = false;
			if ( $oForm -> getValue('nosaukums') && $oForm -> getValue('nosaukums2') )
			{
				$checkRequiredFields = true;
			}
			if ($checkRequiredFields)
			{
				// save
				if ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('workerId'))))
				{


					// if all is ok, do operation
					if($check)
					{
						$r=dbProc::saveWorkOwner(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('workerId'):false),

						$oForm->getValue('nosaukums'),
						$oForm->getValue('nosaukums2'),
                        $oForm->getValue('isActive',0),
                        $oForm->getValue('kods'),
			            $oForm->getValue('number') ,
                        $oForm->getValue('trase_number')

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
					$oLink->addPrm(FORM_ID, 'f.ktl.s.8');
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
		include('f.ktl.s.8.2.tpl');
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
        $title = text::toUpper(text::get('WORK_OUNERS'));
        // get search column list
        $columns=dbProc::getKlklName(KL_WORK_OWNERS);
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;


        // default sort column
        $defaultColumn = dbProc::getKlklDefaultColumn(KL_WORK_OWNERS);

        // URL to search  by number.
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.8');
    	$oLink->addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		$amount=dbProc::getWorkOwnerCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.8');
		$oLink->addPrm('editMode', 1);

		// gel list of users
		$res = dbProc::getWorkOwnerList( false,
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
				$oLink->addPrm('workerId', $row['KWOI_ID']);
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
