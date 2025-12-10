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

		// inicial state: employeeId=0;
		// if employeeId>0 ==> employee selected from the list
		if($employeeId != false)
		{
			// get info about employee
			$employeeInfo = dbProc::getRbfEmployeeList($employeeId);
			if(count($employeeInfo)>0)
			{
				$employee = $employeeInfo[0];
			}
			
			// Get selected territories
			$selectedTerritories = array();
			$terInfo = dbProc::getRbfEmployeeTerritories($employeeId);
			if (is_array($terInfo)) {
				foreach ($terInfo as $ter) {
					$selectedTerritories[] = $ter['RBDT_RBTR_ID'];
				}
			}
        }

		// Get territories for dropdown - both NOSAUKUMS and DID_NOSAUKUMS
		$territoriesNosaukums = array();
		$territoriesDID = array();
		$terList = dbProc::getRbfTerritoryActiveList();
		if (is_array($terList)) {
			foreach ($terList as $ter) {
				$territoriesNosaukums[$ter['RBTR_ID']] = $ter['RBTR_NOSAUKUMS'];
				$territoriesDID[$ter['RBTR_ID']] = $ter['RBTR_DID_NOSAUKUMS'];
			}
		}
		
		// Determine which list to use based on VV type
		$currentVVType = isset($employee['RBDU_VV_VEIDS']) ? $employee['RBDU_VV_VEIDS'] : 'U';
		$territories = ($currentVVType == 'U') ? $territoriesNosaukums : $territoriesDID;

		// VV Types
		$vvTypes = array(
			'U' => text::get('RBF_VV_TYPE_MAINTENANCE'),
			'C' => text::get('RBF_VV_TYPE_ROAD_SURFACE')
		);

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'employeeId', null, isset($employee['RBDU_ID'])? $employee['RBDU_ID']:'');

        $oForm -> addElement('text', 'kods',  text::get('CODE'), isset($employee['RBDU_KODS'])?$employee['RBDU_KODS']:'', 'maxlength="11"' . (($employeeId || $isEdUser)?' disabled' : ''));
		$oForm -> addRule('kods', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('kods', text::get('ERROR_ALPHANUMERIC_VALUE'), 'alphanumeric');

        $oForm -> addElement('text', 'nosaukums',  text::get('NAME'), isset($employee['RBDU_NOSAUKUMS'])?$employee['RBDU_NOSAUKUMS']:'', 'maxlength="250"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('nosaukums', text::get('ERROR_REQUIRED_FIELD'), 'required');

		$oForm -> addElement('select', 'vvType',  text::get('RBF_VV_TYPE'), isset($employee['RBDU_VV_VEIDS'])?$employee['RBDU_VV_VEIDS']:'U', 'onchange="updateTerritories()"'.(($isEdUser)?' disabled' : ''), '', '', $vvTypes);
		$oForm -> addRule('vvType', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('text', 'vvNumber',  text::get('RBF_VV_NUMBER'), isset($employee['RBDU_VV_NUMURS'])?$employee['RBDU_VV_NUMURS']:'', 'maxlength="15"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('vvNumber', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('textarea', 'kontakti',  text::get('RBF_CONTACTS'), isset($employee['RBDU_KONTAKTI'])?$employee['RBDU_KONTAKTI']:'', 'rows="3"'.(($isEdUser)?' disabled' : ''));

		$oForm -> addElement('multiple_select', 'territories',  text::get('RBF_SERVICE_TERRITORY'), isset($selectedTerritories)?$selectedTerritories:array(), (($isEdUser)?' disabled ':'').'size="10"', '', '', $territories);
		$oForm -> addRule('territories', text::get('ERROR_REQUIRED_FIELD'), 'required');
		
		// Pass territory data to template as JSON for JavaScript
		$territoriesNosaukumsJSON = json_encode($territoriesNosaukums);
		$territoriesDIDJSON = json_encode($territoriesDID);

		$oForm -> addElement('checkbox', 'isActive',  text::get('IS_ACTIVE'), isset($employee['RBDU_IR_AKTIVS'])?$employee['RBDU_IR_AKTIVS']:1, ''.(($isEdUser)?' disabled' : ''));

		// form buttons
        if(!$isEdUser)
        {
    		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
    		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'employeeId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
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
			$territories = $oForm -> getValue('territories');
			if ($oForm -> getValue('kods') && $oForm -> getValue('nosaukums') && $oForm -> getValue('vvType') && $oForm -> getValue('vvNumber') && is_array($territories) && count($territories) > 0)
			{
				$checkRequiredFields = true;
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

					// Check if VV number already exists
					if (dbProc::rbfEmployeeWithVVNumberExists(
                                                            $oForm->getValue('vvNumber'),
                                                            ($oForm->getValue('action')==OP_UPDATE)?$oForm->getValue('employeeId'):false)
                                                            )
					{
						$oForm->addError(text::get('ERROR_EXISTS_RBF_EMPLOYEE_VV_NUMBER'));
						$check = false;
					}

					// if all is ok, do operation
					if($check)
					{
						$r=dbProc::saveRbfEmployee(
							($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('employeeId'):false),
							$oForm->getValue('kods'),
							$oForm->getValue('nosaukums'),
							$oForm->getValue('vvType'),
							$oForm->getValue('vvNumber'),
							$oForm->getValue('kontakti'),
							$oForm->getValue('isActive',0),
							$oForm->getValue('territories')
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
            array('kolonna'=>'RBDU_VV_NUMURS', 'nosaukums'=>text::get('RBF_VV_NUMBER'), 'def'=>0),
            array('kolonna'=>'TERRITORIES', 'nosaukums'=>text::get('RBF_SERVICE_TERRITORY'), 'def'=>0),
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
