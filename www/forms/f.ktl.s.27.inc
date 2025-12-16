<?
//RBF Kalkulācija catalog
$userId = userAuthorization::getUserId();
$isEdUser = (dbProc::isUserInRole($userId, ROLE_ED_USER) || dbProc::isUserInRole($userId, ROLE_AUDIT_USER));    
if (userAuthorization::isAdmin() || $isEdUser )
{
	$editMode = reqVar::get('editMode');

	// XMLHTTP request to load VV numbers based on employee
	if (reqVar::get('xmlHttp') == 1)
	{
		if (reqVar::get('employeeCode') !== false)
		{
			// Clear previous values
			?>
			for(i=document.all["vvNumber"].length; i>=0; i--)
			{
				document.all["vvNumber"].options[i] = null;
			}
			for(i=document.all["section"].length; i>=0; i--)
			{
				document.all["section"].options[i] = null;
			}
			<?
			$res=dbProc::getRbfEmployeeVVList(reqVar::get('employeeCode'));
			if (is_array($res) && count($res)>0)
			{
				?>
				document.all["vvNumber"].options[0] = new Option('<?=text::get('EMPTY_SELECT_OPTION');?>', '');
				document.all["section"].options[0] = new Option('<?=text::get('EMPTY_SELECT_OPTION');?>', '');
				<?

				$i = 1;
				foreach ($res as $row)
				{
					?>
					document.all["vvNumber"].options[<?=$i;?>] = new Option( '<?=$row['RBDV_VV_NUMURS'];?>', '<?=$row['RBDV_VV_NUMURS'];?>');
					<?
					$i++;
				}
			}
		}
		
		// Load territories (sections) based on VV number
		if (reqVar::get('vvNumber') !== false)
		{
			?>
			for(i=document.all["section"].length; i>=0; i--)
			{
				document.all["section"].options[i] = null;
			}
			<?
			$res=dbProc::getRbfVVTerritories(reqVar::get('vvNumber'));
			if (is_array($res) && count($res)>0)
			{
				
				$i = 1;
				foreach ($res as $row)
				{
					?>
					document.all["section"].options[<?=$i;?>] = new Option( '<?=$row['RBTR_NOSAUKUMS'];?>', '<?=$row['RBTR_KODS'];?>');
					<?
					$i++;
				}
			}
		}
		exit;
	}

	// bottom frame
	// if insert/update
     if($editMode)
	{
		$calcId = reqVar::get('calcId');

		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.27');
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

		// Get VV numbers list
		$vvNumbers = array();
		$vvNumbers['']=text::get('EMPTY_SELECT_OPTION');

		// Get sections/territories list
		$sections = array();
		$sections['']=text::get('EMPTY_SELECT_OPTION');

		// Get employees list
		$employees = array();
		$employees['']=text::get('EMPTY_SELECT_OPTION');
		$empList = dbProc::getRbfEmployeeActiveList();
		if (is_array($empList)) {
			foreach ($empList as $emp) {
				$employees[$emp['RBDU_KODS']] = $emp['RBDU_KODS'] . ' - ' . $emp['RBDU_NOSAUKUMS'];
			}
		}

		// if calcId>0 ==> calculation selected from the list
		if($calcId != false)
		{
			// get info about calculation
			$calculationInfo = dbProc::getRbfCalculationList($calcId);
			if(count($calculationInfo)>0)
			{
				$calc = $calculationInfo[0];
				
				// Get VV numbers for selected employee
				$res=dbProc::getRbfEmployeeVVList($calc['RBKL_RBDU_KODS']);
				if (is_array($res))
				{
					foreach ($res as $row)
					{
						$vvNumbers[$row['RBDV_VV_NUMURS']]=$row['RBDV_VV_NUMURS'];
					}
				}
				unset($res);
				
				// Get territories/sections for selected VV number
				if (isset($calc['RBKL_VV_NUMBER']) && $calc['RBKL_VV_NUMBER']) {
					$res=dbProc::getRbfVVTerritories($calc['RBKL_VV_NUMBER']);
					if (is_array($res))
					{
						foreach ($res as $row)
						{
							$sections[$row['RBTR_KODS']]=$row['RBTR_NOSAUKUMS'];
						}
					}
					unset($res);
				}
			}
			
			// get user info
			$userInfo = dbProc::getUserInfo($calc['RBKL_CREATOR']);
			if(count($userInfo) >0 )
			{
				$creator = $userInfo[0]['RLTT_VARDS']. ' ' .$userInfo[0]['RLTT_UZVARDS'];
			}
			$userInfo1 = dbProc::getUserInfo($calc['RBKL_EDITOR']);
			if(count($userInfo1) >0 )
			{
				$editor = $userInfo1[0]['RLTT_VARDS']. ' ' .$userInfo1[0]['RLTT_UZVARDS'];
			}
        }

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'calcId', null, isset($calc['RBKL_ID'])? $calc['RBKL_ID']:'');

        $oForm -> addElement('text', 'shifrs',  text::get('RBF_SHIFRS'), isset($calc['RBKL_SHIFRS'])?$calc['RBKL_SHIFRS']:'', 'maxlength="5"' . (($calcId || $isEdUser)?' disabled' : ''));
		$oForm -> addRule('shifrs', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('text', 'nosaukums',  text::get('NAME'), isset($calc['RBKL_NOSAUKUMS'])?$calc['RBKL_NOSAUKUMS']:'', 'maxlength="150"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('nosaukums', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('text', 'mervieniba',  text::get('RBF_UNIT_OF_MEASURE'), isset($calc['RBKL_MERVIENIBA'])?$calc['RBKL_MERVIENIBA']:'', 'maxlength="15"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('mervieniba', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('textarea', 'apraksts', text::get('RBF_DESCRIPTION'), isset($calc['RBKL_APRAKSTS'])?$calc['RBKL_APRAKSTS']:'','rows="3"'.(($isEdUser)?' disabled' : ''));

		// xmlHttp link for VV number dropdown
		$oLink=new urlQuery();
		$oLink->addPrm(DONT_USE_GLB_TPL, 1);
		$oLink->addPrm(FORM_ID, 'f.ktl.s.27');
		$oForm -> addElement('select', 'employeeCode',  text::get('RBF_EMPLOYEE_CODE'), isset($calc['RBKL_RBDU_KODS'])?$calc['RBKL_RBDU_KODS']:'', 'onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&employeeCode=\'+this.value+\'\'))" '.(($isEdUser)?' disabled' : ''), '', '', $employees);
		$oForm -> addRule('employeeCode', text::get('ERROR_REQUIRED_FIELD'), 'required');

		$oForm -> addElement('select', 'vvNumber',  text::get('RBF_VV_NUMBER'), isset($calc['RBKL_VV_NUMBER'])?$calc['RBKL_VV_NUMBER']:'', 'onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&vvNumber=\'+this.value+\'\'))" '.(($isEdUser)?' disabled' : ''), '', '', $vvNumbers);
		$oForm -> addRule('vvNumber', text::get('ERROR_REQUIRED_FIELD'), 'required');
		unset($oLink);

        $oForm -> addElement('select', 'section',  text::get('RBF_SECTION'), isset($calc['RBKL_RBTR_CODE'])?$calc['RBKL_RBTR_CODE']:'', (($isEdUser)?' disabled' : ''), '', '', $sections);

        $oForm -> addElement('text', 'cena',  text::get('RBF_PRICE'), isset($calc['RBKL_CENA'])?$calc['RBKL_CENA']:'', 'maxlength="10"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('cena', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('cena', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);

		$oForm -> addElement('checkbox', 'isActive',  text::get('IS_ACTIVE'), isset($calc['RBKL_IR_AKTIVS'])?$calc['RBKL_IR_AKTIVS']:1, ''.(($isEdUser)?' disabled' : ''));

		// Import data fields
		$oForm -> addElement('text', 'created',  text::get('CREATED'), isset($calc['RBKL_CREATED'])?$calc['RBKL_CREATED']:dtime::now(), 'maxlength="20" disabled');
		$oForm -> addElement('text', 'creator',  text::get('CREATOR'), isset($calc)?$creator:'', 'maxlength="20" disabled');
		$oForm -> addElement('text', 'edited',  text::get('EDITED'), isset($calc['RBKL_EDITED'])?$calc['RBKL_EDITED']:dtime::now(), 'maxlength="20" disabled');
		$oForm -> addElement('text', 'editor',  text::get('EDITOR'), isset($calc)?$editor:'', 'maxlength="20" disabled');

		// form buttons
        if(!$isEdUser)
        {
    		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
    		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'calcId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
    		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'calcId\');parent.frame_1.unActiveRow();'));

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
    				refreshButton("calcId");
    			</script>
    		');
        }
		// if operation
		if ($oForm -> isFormSubmitted())
		{
			$check = true;
			$r = false;
			$checkRequiredFields = false;
			
			// Debug: show submitted values
			$debugInfo = 'Debug Values: ';
			$debugInfo .= 'shifrs=' . $oForm->getValue('shifrs') . ', ';
			$debugInfo .= 'employeeCode=' . $oForm->getValue('employeeCode') . ', ';
			$debugInfo .= 'vvNumber=' . $oForm->getValue('vvNumber') . ', ';
			$debugInfo .= 'section=' . $oForm->getValue('section') . ', ';
			$debugInfo .= 'cena=' . $oForm->getValue('cena');
			
			if ($oForm -> getValue('shifrs') && $oForm -> getValue('nosaukums') && 
			    $oForm -> getValue('mervieniba') && $oForm -> getValue('employeeCode') &&
			    $oForm -> getValue('vvNumber') && $oForm -> getValue('cena'))
			{
				$checkRequiredFields = true;
			}
			else
			{
				$oForm->addError($debugInfo);
			}
			
			if ($checkRequiredFields)
			{
				// save
				if ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('calcId'))))
				{
					// Check if calculation with same combination already exists
					if (dbProc::rbfCalculationExists(
						$oForm->getValue('vvNumber'),
						$oForm->getValue('shifrs'),
						$oForm->getValue('section'),
						($oForm->getValue('action')==OP_UPDATE)?$oForm->getValue('calcId'):false)
					)
					{
						$oForm->addError(text::get('ERROR_EXISTS_RBF_CALCULATION'));
						$check = false;
					}

					// if all is ok, do operation
					if($check)
					{
						$r=dbProc::saveRbfCalculation(
							($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('calcId'):false),
							$oForm->getValue('shifrs'),
							$oForm->getValue('nosaukums'),
							$oForm->getValue('mervieniba'),
							$oForm->getValue('apraksts'),
							$oForm->getValue('employeeCode'),
							$oForm->getValue('vvNumber'),
							$oForm->getValue('section'),
							$oForm->getValue('cena'),
							$oForm->getValue('isActive',0),
							$userId
						);

						if (!$r)
						{
							$errorMsg = dbProc::getError();
							$oForm->addError(text::get('ERROR_IN_DB_QUERY') . ($errorMsg ? ' - ' . $errorMsg : ' - No error details'));
							$oForm->addError($debugInfo);
						}
					}
				}


				// if operation was compleated succefully, show success mesage and redirect current frame
				if ($r)
				{
					$oLink=new urlQuery();
					$oLink->addPrm(FORM_ID, 'f.ktl.s.27');
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
		include('f.ktl.s.27.2.tpl');
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
        $title = text::toUpper(text::get('RBF_CALCULATIONS'));
        // get search column list
        $columns=array(
            array('kolonna'=>'RBKL_SHIFRS', 'nosaukums'=>text::get('RBF_SHIFRS'), 'def'=>1),
            array('kolonna'=>'RBKL_NOSAUKUMS', 'nosaukums'=>text::get('NAME'), 'def'=>0),
            array('kolonna'=>'EMPLOYEE_INFO', 'nosaukums'=>text::get('RBF_EMPLOYEE_CODE'), 'def'=>0),
            array('kolonna'=>'RBKL_VV_NUMBER', 'nosaukums'=>text::get('RBF_VV_NUMBER'), 'def'=>0),
            array('kolonna'=>'RBKL_SECTION', 'nosaukums'=>text::get('RBF_SECTION'), 'def'=>0),
            array('kolonna'=>'RBKL_CENA', 'nosaukums'=>text::get('RBF_PRICE'), 'def'=>0),
            array('kolonna'=>'RBKL_IR_AKTIVS', 'nosaukums'=>text::get('IS_ACTIVE'), 'def'=>0)
        );
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;

        // default sort column
        $defaultColumn = 'RBKL_SHIFRS';

        // URL to search
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.27');
    	$oLink->addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		$amount=dbProc::getRbfCalculationCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.27');
		$oLink->addPrm('editMode', 1);

		// get list of calculations
		$res = dbProc::getRbfCalculationList( false,
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
				// add calc Id to each link
				$oLink->addPrm('calcId', $row['RBKL_ID']);
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
