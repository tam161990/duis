<?
//RBF Employees catalog
$userId = userAuthorization::getUserId();
$isEdUser = (dbProc::isUserInRole($userId, ROLE_ED_USER) || dbProc::isUserInRole($userId, ROLE_AUDIT_USER));    
if (userAuthorization::isAdmin() || $isEdUser )
{
	$editMode = reqVar::get('editMode');
	// bottom frame
	// if insert/update

     if($editMode)
	{
		$employeeId = reqVar::get('employeeId');

		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.26');
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

		// Get existing VV entries if editing
		$existingVVEntries = array();
		if($employeeId != false)
		{
			// get info about employee
			$employeeInfo = dbProc::getRbfEmployeeList($employeeId);
			if(count($employeeInfo)>0)
			{
				$employee = $employeeInfo[0];
			}
			
			// Get VV entries
			$vvInfo = dbProc::getRbfEmployeeVVEntries($employeeId);
			if (is_array($vvInfo)) {
				$existingVVEntries = $vvInfo;
			}
        }

		// Get territories for dropdown (both types)
		// For U type: use RBTR_KODS as key, RBTR_NOSAUKUMS as value
		// For C type: use RBTR_DID_KODS as key, RBTR_DID_NOSAUKUMS as value
		$territoriesNosaukums = array();
		$territoriesDID = array();
		$terList = dbProc::getRbfTerritoryActiveList();
		if (is_array($terList)) {
			foreach ($terList as $ter) {
				// For Uzturēšana (U) - use regular code and name
				$territoriesNosaukums[$ter['RBTR_KODS']] = $ter['RBTR_NOSAUKUMS'];
				// For Ceļa segumi (C) - use DID code and DID name
				// Group by RBTR_DID_KODS to show only one record per code
				if (!isset($territoriesDID[$ter['RBTR_DID_KODS']])) {
					$territoriesDID[$ter['RBTR_DID_KODS']] = $ter['RBTR_DID_NOSAUKUMS'];
				}
			}
		}

		// VV Types
		$vvTypes = array(
			'U' => text::get('RBF_VV_TYPE_MAINTENANCE'),
			'C' => text::get('RBF_VV_TYPE_ROAD_SURFACE')
		);

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'employeeId', null, isset($employee['RBDU_ID'])? $employee['RBDU_ID']:'');
		$oForm -> addElement('hidden', 'vvRowCount', '', '0');

        $oForm -> addElement('text', 'kods',  text::get('CODE'), isset($employee['RBDU_KODS'])?$employee['RBDU_KODS']:'', 'maxlength="11"' . (($employeeId || $isEdUser)?' disabled' : ''));
		$oForm -> addRule('kods', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('kods', text::get('ERROR_ALPHANUMERIC_VALUE'), 'alphanumeric');

        $oForm -> addElement('text', 'nosaukums',  text::get('NAME'), isset($employee['RBDU_NOSAUKUMS'])?$employee['RBDU_NOSAUKUMS']:'', 'maxlength="250"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('nosaukums', text::get('ERROR_REQUIRED_FIELD'), 'required');

		$oForm -> addElement('select', 'vvType',  text::get('RBF_VV_TYPE'), isset($employee['RBDU_VV_VEIDS'])?$employee['RBDU_VV_VEIDS']:'U', 'onchange="updateAllTerritories()"'.(($isEdUser)?' disabled' : ''), '', '', $vvTypes);
		$oForm -> addRule('vvType', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('textarea', 'kontakti',  text::get('RBF_CONTACTS'), isset($employee['RBDU_KONTAKTI'])?$employee['RBDU_KONTAKTI']:'', 'rows="2"'.(($isEdUser)?' disabled' : ''));

		$oForm -> addElement('checkbox', 'isActive',  text::get('IS_ACTIVE'), isset($employee['RBDU_IR_AKTIVS'])?$employee['RBDU_IR_AKTIVS']:1, ''.(($isEdUser)?' disabled' : ''));

		// Pass data to template
		$territoriesNosaukumsJSON = json_encode($territoriesNosaukums);
		$territoriesDIDJSON = json_encode($territoriesDID);
		$vvTypesJSON = json_encode($vvTypes);
		$existingVVEntriesJSON = json_encode($existingVVEntries);

		// form buttons
        if(!$isEdUser)
        {
    		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');return validateVVEntries();"');
    		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'employeeId\')) {setValue(\'action\',\''.OP_UPDATE.'\');return validateVVEntries();} else {return false;}"');
    		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'employeeId\');parent.frame_1.unActiveRow();'));

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
    				refreshButton("employeeId");
    			</script>
    		');
        }
		// if operation
		if ($oForm -> isFormSubmitted())
		{
			$check = true;
			$r = false;
			$checkRequiredFields = false;
			if ($oForm -> getValue('kods') && $oForm -> getValue('nosaukums'))
			{
				$checkRequiredFields = true;
			}
			
			// Collect VV entries from POST data
			$vvEntries = array();
			$vvRowCount = reqVar::get('vvRowCount');
			if ($vvRowCount > 0) {
				for ($i = 0; $i < $vvRowCount; $i++) {
					$vvNumber = reqVar::get('vvNumber_' . $i);
					$territory = reqVar::get('territory_' . $i);
					$contacts = reqVar::get('contacts_' . $i);
					$deleted = reqVar::get('deleted_' . $i);
					
					if ($deleted != '1' && $vvNumber && $territory) {
						$vvEntries[] = array(
							'vvNumber' => $vvNumber,
							'territory' => $territory,
							'contacts' => $contacts
						);
					}
				}
			}
			
			// Check if at least one VV entry exists
			if (count($vvEntries) == 0) {
				$oForm->addError(text::get('ERROR_MIN_ONE_VV'));
				$checkRequiredFields = false;
			}
			
			if ($checkRequiredFields)
			{
				// save
				if ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('employeeId'))))
				{
					// Check if code already exists
					if (dbProc::rbfEmployeeWithCodeExists(
                                                            $oForm->getValue('kods'),
                                                            ($oForm->getValue('action')==OP_UPDATE)?$oForm->getValue('employeeId'):false)
                                                            )
					{
						$oForm->addError(text::get('ERROR_EXISTS_RBF_EMPLOYEE_CODE'));
						$check = false;
					}

					// Check if any VV number already exists
					foreach ($vvEntries as $entry) {
						if (dbProc::rbfEmployeeWithVVNumberExists($entry['vvNumber'], $oForm->getValue('employeeId'))) {
							$oForm->addError(text::get('ERROR_EXISTS_RBF_EMPLOYEE_VV_NUMBER') . ' (' . $entry['vvNumber'] . ')');
							$check = false;
							break;
						}
					}

					// if all is ok, do operation
					if($check)
					{
						$r=dbProc::saveRbfEmployee(
							($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('employeeId'):false),
							$oForm->getValue('kods'),
							$oForm->getValue('nosaukums'),
							$oForm->getValue('vvType'),
							$oForm->getValue('kontakti'),
							$oForm->getValue('isActive',0),
							$vvEntries
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
					$oLink->addPrm(FORM_ID, 'f.ktl.s.26');
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
		include('f.ktl.s.26.2.tpl');
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
        $title = text::toUpper(text::get('RBF_EMPLOYEES'));
        // get search column list
        $columns=array(
            array('kolonna'=>'RBDU_KODS', 'nosaukums'=>text::get('CODE'), 'def'=>1),
            array('kolonna'=>'RBDU_NOSAUKUMS', 'nosaukums'=>text::get('NAME'), 'def'=>0),
            array('kolonna'=>'RBDU_VV_VEIDS_TEXT', 'nosaukums'=>text::get('RBF_VV_TYPE'), 'def'=>0),
            array('kolonna'=>'RBDU_KONTAKTI', 'nosaukums'=>text::get('RBF_CONTACTS'), 'def'=>0),
            array('kolonna'=>'VV_TERRITORIES', 'nosaukums'=>text::get('RBF_VV_ENTRIES'), 'def'=>0),
            array('kolonna'=>'RBDU_IR_AKTIVS', 'nosaukums'=>text::get('IS_ACTIVE'), 'def'=>0)
        );
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;

        // default sort column
        $defaultColumn = 'RBDU_KODS';

        // URL to search
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.26');
    	$oLink->addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		$amount=dbProc::getRbfEmployeeCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.26');
		$oLink->addPrm('editMode', 1);

		// get list of employees
		$res = dbProc::getRbfEmployeeList( false,
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
				// add employee Id to each link
				$oLink->addPrm('employeeId', $row['RBDU_ID']);
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
