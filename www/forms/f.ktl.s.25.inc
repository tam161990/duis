<?
//RBF Territories catalog
$userId = userAuthorization::getUserId();
$isEdUser = (dbProc::isUserInRole($userId, ROLE_ED_USER) || dbProc::isUserInRole($userId, ROLE_AUDIT_USER));    
if (userAuthorization::isAdmin() || $isEdUser )
{
	$editMode = reqVar::get('editMode');
	// bottom frame
	// if insert/update

     if($editMode)
	{
		$territoryId = reqVar::get('territoryId');

		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.25');
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

		// inicial state: territoryId=0;
		// if territoryId>0 ==> territory selected from the list
		if($territoryId != false)
		{
			// get info about territory
			$territoryInfo = dbProc::getRbfTerritoryList($territoryId);
			if(count($territoryInfo)>0)
			{
				$territory = $territoryInfo[0];
			}
        }

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'territoryId', null, isset($territory['RBTR_ID'])? $territory['RBTR_ID']:'');

        $oForm -> addElement('text', 'kods',  text::get('CODE'), isset($territory['RBTR_KODS'])?$territory['RBTR_KODS']:'', 'maxlength="10"' . (($territoryId || $isEdUser)?' disabled' : ''));
		$oForm -> addRule('kods', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('text', 'nosaukums',  text::get('NAME'), isset($territory['RBTR_NOSAUKUMS'])?$territory['RBTR_NOSAUKUMS']:'', 'maxlength="250"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('nosaukums', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('text', 'didKods',  text::get('RBF_PART_CODE'), isset($territory['RBTR_DID_KODS'])?$territory['RBTR_DID_KODS']:'', 'maxlength="10"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('didKods', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('text', 'didNosaukums',  text::get('RBF_DID_NAME'), isset($territory['RBTR_DID_NOSAUKUMS'])?$territory['RBTR_DID_NOSAUKUMS']:'', 'maxlength="250"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('didNosaukums', text::get('ERROR_REQUIRED_FIELD'), 'required');

		$oForm -> addElement('checkbox', 'isActive',  text::get('IS_ACTIVE'), isset($territory['RBTR_IR_AKTIVS'])?$territory['RBTR_IR_AKTIVS']:1, ''.(($isEdUser)?' disabled' : ''));

		// form buttons
        if(!$isEdUser)
        {
    		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
    		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'territoryId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
    		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'territoryId\');parent.frame_1.unActiveRow();'));

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
    				refreshButton("territoryId");
    			</script>
    		');
        }
		// if operation
		if ($oForm -> isFormSubmitted())
		{
			$check = true;
			$r = false;
			$checkRequiredFields = false;
			
			// For UPDATE: use existing data for disabled fields, for INSERT: use form values
			if ($oForm->getValue('action')==OP_UPDATE && is_numeric($oForm->getValue('territoryId'))) {
				// Updating - load territory data to fill disabled fields
				if (!isset($territory)) {
					$territoryInfo = dbProc::getRbfTerritoryList($oForm->getValue('territoryId'));
					if(count($territoryInfo)>0)
					{
						$territory = $territoryInfo[0];
					}
				}
				$kods = isset($territory['RBTR_KODS']) ? $territory['RBTR_KODS'] : '';
				$nosaukums = $oForm->getValue('nosaukums') ? $oForm->getValue('nosaukums') : (isset($territory['RBTR_NOSAUKUMS']) ? $territory['RBTR_NOSAUKUMS'] : '');
				$didKods = $oForm->getValue('didKods') ? $oForm->getValue('didKods') : (isset($territory['RBTR_DID_KODS']) ? $territory['RBTR_DID_KODS'] : '');
				$didNosaukums = $oForm->getValue('didNosaukums') ? $oForm->getValue('didNosaukums') : (isset($territory['RBTR_DID_NOSAUKUMS']) ? $territory['RBTR_DID_NOSAUKUMS'] : '');
			} else {
				// Inserting - use form values
				$kods = $oForm->getValue('kods');
				$nosaukums = $oForm->getValue('nosaukums');
				$didKods = $oForm->getValue('didKods');
				$didNosaukums = $oForm->getValue('didNosaukums');
			}
			
			if ($kods && $nosaukums && $didKods && $didNosaukums)
			{
				$checkRequiredFields = true;
			}
			if ($checkRequiredFields)
			{
				// save
				if ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('territoryId'))))
				{
					// Check if code already exists (only for INSERT)
					if ($oForm->getValue('action')==OP_INSERT && 
					    dbProc::rbfTerritoryWithCodeExists($kods, false))
					{
						$oForm->addError(text::get('ERROR_EXISTS_RBF_TERRITORY_CODE'));
						$check = false;
					}

					// if all is ok, do operation
					if($check)
					{
						// Debug: Check what we're passing
						$territoryId = ($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('territoryId'):false);
						$isActive = $oForm->getValue('isActive',0);
						
						$r=dbProc::saveRbfTerritory(
							$territoryId,
							$kods,
							$nosaukums,
							$didKods,
							$didNosaukums,
							$isActive
						);

						if ($r === false)
						{
							$oDB = new dbLayer();
							$errorMsg = $oDB->getError();
							$oForm->addError(text::get('ERROR_IN_DB_QUERY') . ($errorMsg ? ' - ' . $errorMsg : ' - No error details'));
						}
					}
				}


				// if operation was compleated succefully, show success mesage and redirect current frame
				if ($r !== false)
				{
					$oLink=new urlQuery();
					$oLink->addPrm(FORM_ID, 'f.ktl.s.25');
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
		include('f.ktl.s.25.2.tpl');
	}
	// top frame
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
        $title = text::toUpper(text::get('RBF_TERRITORIES'));
        // get search column list
        $columns=array(
            array('kolonna'=>'RBTR_KODS', 'nosaukums'=>text::get('CODE'), 'def'=>1),
            array('kolonna'=>'RBTR_NOSAUKUMS', 'nosaukums'=>text::get('NAME'), 'def'=>0),
            array('kolonna'=>'RBTR_DID_KODS', 'nosaukums'=>text::get('RBF_PART_CODE'), 'def'=>0),
            array('kolonna'=>'RBTR_DID_NOSAUKUMS', 'nosaukums'=>text::get('RBF_DID_NAME'), 'def'=>0),
            array('kolonna'=>'RBTR_IR_AKTIVS', 'nosaukums'=>text::get('IS_ACTIVE'), 'def'=>0)
        );
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;

        // default sort column
        $defaultColumn = 'RBTR_KODS';

        // URL to search
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.25');
    	$oLink->addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		$amount=dbProc::getRbfTerritoryCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.25');
		$oLink->addPrm('editMode', 1);

		// get list of territories
		$res = dbProc::getRbfTerritoryList( false,
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
				// add territory Id to each link
				$oLink->addPrm('territoryId', $row['RBTR_ID']);
				$res[$i]['URL']=$oLink ->getQuery();
			}
		}
		unset($oLink);

		// inicial state of number
		$number=$listing->getStartPosition()+1;

		include('f.ktl.s.x.1.tpl');
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
