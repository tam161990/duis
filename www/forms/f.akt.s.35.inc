<?
// RBF advanced search form
$userId = userAuthorization::getUserId();
$isAdmin = userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;
$selectedId = reqVar::get('selectedId');

if ($isAdmin || $isSystemUser)
{
	if (reqVar::get('xmlHttp') == 1)
	{
		ob_clean();
		$employeeCode = reqVar::get('employeeCode') ? reqVar::get('employeeCode') : '-1';
		$vvNumber = reqVar::get('vvNumber') ? reqVar::get('vvNumber') : '-1';

		$vvOptions = array();
		$vvOptions[] = array('value' => '-1', 'label' => text::get('ALL'));
		$res = dbProc::getRbfActSearchVvList($employeeCode);
		if (is_array($res))
		{
			foreach ($res as $row)
			{
				$vvOptions[] = array('value' => $row['RBDV_VV_NUMURS'], 'label' => $row['RBDV_VV_NUMURS']);
			}
		}

		$territoryOptions = array();
		$territoryOptions[] = array('value' => '-1', 'label' => text::get('ALL'));
		$res = dbProc::getRbfActSearchTerritoryList($employeeCode, $vvNumber);
		if (is_array($res))
		{
			foreach ($res as $row)
			{
				$territoryOptions[] = array(
					'value' => $row['RBTR_CODE'],
					'label' => $row['RBTR_CODE'].' - '.$row['RBTR_NAME']
				);
			}
		}

		$authorOptions = array();
		$authorOptions[] = array('value' => '-1', 'label' => text::get('ALL'));
		$res = dbProc::getRbfAdminUsersList($employeeCode);
		if (is_array($res))
		{
			foreach ($res as $row)
			{
				$authorOptions[] = array(
					'value' => $row['RLTT_ID'],
					'label' => $row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS']
				);
			}
		}
		?>
		for(i=document.all["vvNumber"].length; i>=0; i--)
		{
			document.all["vvNumber"].options[i] = null;
		}
		<?
		foreach ($vvOptions as $i => $opt)
		{
			?>
			document.all["vvNumber"].options[<?=$i;?>] = new Option('<?=addslashes($opt['label']);?>', '<?=addslashes($opt['value']);?>');
			<?
		}
		?>
		document.all["vvNumber"].value = '-1';

		for(i=document.all["territoryCode"].length; i>=0; i--)
		{
			document.all["territoryCode"].options[i] = null;
		}
		<?
		foreach ($territoryOptions as $i => $opt)
		{
			?>
			document.all["territoryCode"].options[<?=$i;?>] = new Option('<?=addslashes($opt['label']);?>', '<?=addslashes($opt['value']);?>');
			<?
		}
		?>
		document.all["territoryCode"].value = '-1';

		for(i=document.all["authorId"].length; i>=0; i--)
		{
			document.all["authorId"].options[i] = null;
		}
		<?
		foreach ($authorOptions as $i => $opt)
		{
			?>
			document.all["authorId"].options[<?=$i;?>] = new Option('<?=addslashes($opt['label']);?>', '<?=addslashes($opt['value']);?>');
			<?
		}
		?>
		document.all["authorId"].value = '-1';
		<?
		exit;
	}

	$searchMode = reqVar::get('isSearch');

	// top frame: search criteria
	if ($searchMode == 1)
	{
		$oLink = new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.akt.s.35');
		$oLink->addPrm('isSearch', 1);
		$oForm = new Form('frmMain', 'post', $oLink->getQuery());
		unset($oLink);

		$oLink = new urlQuery();
		$oLink->addPrm('isReturn', '1');
		$oLink->addPrm('isSearch', 1);
		$oLink->addPrm(FORM_ID, 'f.akt.s.35');
		$criteriaLink = $oLink->getQuery();
		unset($oLink);

		$employeeCodeCurrent = reqVar::get('employeeCode') ? reqVar::get('employeeCode') : '-1';
		$vvNumberCurrent = reqVar::get('vvNumber') ? reqVar::get('vvNumber') : '-1';

		$employees = array('-1' => text::get('ALL'));
		$res = dbProc::getRbfEmployeeActiveList();
		if (is_array($res))
		{
			foreach ($res as $row)
			{
				$employees[$row['RBDU_KODS']] = $row['RBDU_KODS'].' - '.$row['RBDU_NOSAUKUMS'];
			}
		}

		$vvNumbers = array('-1' => text::get('ALL'));
		$res = dbProc::getRbfActSearchVvList($employeeCodeCurrent);
		if (is_array($res))
		{
			foreach ($res as $row)
			{
				$vvNumbers[$row['RBDV_VV_NUMURS']] = $row['RBDV_VV_NUMURS'];
			}
		}

		$territories = array('-1' => text::get('ALL'));
		$res = dbProc::getRbfActSearchTerritoryList($employeeCodeCurrent, $vvNumberCurrent);
		if (is_array($res))
		{
			foreach ($res as $row)
			{
				$territories[$row['RBTR_CODE']] = $row['RBTR_CODE'].' - '.$row['RBTR_NAME'];
			}
		}

		$actTypes = array('-1' => text::get('ALL'));
		$res = dbProc::getActTypeActivList(true);
		if (is_array($res))
		{
			foreach ($res as $row)
			{
				$actTypes[$row['KAKV_ID']] = $row['KAKV_NOSAUKUMS'];
			}
		}

		$statusList = array();
		$statusList['-1'] = text::get('ALL_STATUS');
		$res = dbProc::getKrfkName(KRFK_STATUS);
		if (is_array($res))
		{
			foreach ($res as $row)
			{
				$statusList[$row['nosaukums']] = $row['nozime'];
			}
		}

		$authors = array('-1' => text::get('ALL'));
		$res = dbProc::getRbfAdminUsersList($employeeCodeCurrent);
		if (is_array($res))
		{
			foreach ($res as $row)
			{
				$authors[$row['RLTT_ID']] = $row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS'];
			}
		}

		$criteria = array(
			'employeeCode' => '-1',
			'vvNumber' => '-1',
			'territoryCode' => '-1',
			'actType' => '-1',
			'status' => array('-1'),
			'authorId' => '-1'
		);

		if (reqVar::get('isReturn') == 1 || $selectedId)
		{
			$criteria['employeeCode'] = reqVar::get('employeeCode') ? reqVar::get('employeeCode') : '-1';
			$criteria['vvNumber'] = reqVar::get('vvNumber') ? reqVar::get('vvNumber') : '-1';
			$criteria['territoryCode'] = reqVar::get('territoryCode') ? reqVar::get('territoryCode') : '-1';
			$criteria['actType'] = reqVar::get('actType') ? reqVar::get('actType') : '-1';
			$criteria['authorId'] = reqVar::get('authorId') ? reqVar::get('authorId') : '-1';
			$statusValue = reqVar::get('status');
			if ($statusValue)
			{
				$criteria['status'] = explode('*', $statusValue);
			}
		}

		$oXmlLink = new urlQuery();
		$oXmlLink->addPrm(DONT_USE_GLB_TPL, 1);
		$oXmlLink->addPrm(FORM_ID, 'f.akt.s.35');
		$oForm->addElement('select', 'employeeCode', text::get('RBF_EMPLOYEE'), $criteria['employeeCode'], 'onChange="eval(xmlHttpGetValue(\''.$oXmlLink->getQuery().'&xmlHttp=1&employeeCode=\'+this.value+\'\'))"', '', '', $employees);
		$oForm->addElement('select', 'vvNumber', text::get('RBF_VV_NUMBER'), $criteria['vvNumber'], 'onChange="eval(xmlHttpGetValue(\''.$oXmlLink->getQuery().'&xmlHttp=1&employeeCode=\'+document.all[\'employeeCode\'].options[document.all[\'employeeCode\'].selectedIndex].value+\'&vvNumber=\'+this.value+\'\'))"', '', '', $vvNumbers);
		unset($oXmlLink);
		$oForm->addElement('select', 'territoryCode', text::get('RBF_DEPARTMENT'), $criteria['territoryCode'], '', '', '', $territories);
		$oForm->addElement('select', 'actType', text::get('SINGLE_ACT_TYPE'), $criteria['actType'], '', '', '', $actTypes);
		$oForm->addElement('select', 'authorId', text::get('RBF_AUTHOR'), $criteria['authorId'], '', '', '', $authors);
		$oForm->addElement('multiple_select', 'status', text::get('STATUS'), $criteria['status'], ' size="7"', '', '', $statusList);
		$oForm->addElement('submitImg', 'search', text::get('SEARCH'), 'img/btn_meklet.gif', 'width="70" height="20" onClick="setPosition1(\'loading\'); return true;"');

		if ($oForm->isFormSubmitted())
		{
			$criteria['employeeCode'] = $oForm->getValue('employeeCode');
			$criteria['vvNumber'] = $oForm->getValue('vvNumber');
			$criteria['territoryCode'] = $oForm->getValue('territoryCode');
			$criteria['actType'] = $oForm->getValue('actType');
			$criteria['authorId'] = $oForm->getValue('authorId');
			$criteria['status'] = $oForm->getValue('status');

			$hasAtLeastOneCriteria = (
				$criteria['employeeCode'] != '-1' ||
				$criteria['vvNumber'] != '-1' ||
				$criteria['territoryCode'] != '-1' ||
				$criteria['actType'] != '-1' ||
				$criteria['authorId'] != '-1' ||
				(is_array($criteria['status']) && !(count($criteria['status']) == 1 && $criteria['status'][0] == '-1'))
			);

			if (!$hasAtLeastOneCriteria)
			{
				$oForm->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
			}
			else
			{
				$oListLink = new urlQuery();
				$oListLink->addPrm(FORM_ID, 'f.akt.s.35');
				$oListLink->addPrm('employeeCode', $criteria['employeeCode']);
				$oListLink->addPrm('vvNumber', $criteria['vvNumber']);
				$oListLink->addPrm('territoryCode', $criteria['territoryCode']);
				$oListLink->addPrm('actType', $criteria['actType']);
				$oListLink->addPrm('authorId', $criteria['authorId']);
				$oListLink->addPrm('status', implode('*', $criteria['status']));
				$actListLink = $oListLink->getQuery();
				unset($oListLink);
				$oForm->addElement('static', 'jsRefresh2', '', '<script>reloadFrame(2, "'.$actListLink.'");</script>');
			}
		}

		$searchTitle = text::toUpper(text::get('ADVANCED_SEARCH_RBF'));
		$oForm->makeHtml();
		include('f.akt.s.35.tpl');
	}
	// bottom frame: list
	else
	{
		$employeeCode = reqVar::get('employeeCode') ? reqVar::get('employeeCode') : '-1';
		$vvNumber = reqVar::get('vvNumber') ? reqVar::get('vvNumber') : '-1';
		$territoryCode = reqVar::get('territoryCode') ? reqVar::get('territoryCode') : '-1';
		$actType = reqVar::get('actType') ? reqVar::get('actType') : '-1';
		$authorId = reqVar::get('authorId') ? reqVar::get('authorId') : '-1';
		$status = reqVar::get('status') ? reqVar::get('status') : '-1';

		$oLink = new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.akt.s.35');
		$oLink->addPrm('employeeCode', $employeeCode);
		$oLink->addPrm('vvNumber', $vvNumber);
		$oLink->addPrm('territoryCode', $territoryCode);
		$oLink->addPrm('actType', $actType);
		$oLink->addPrm('authorId', $authorId);
		$oLink->addPrm('status', $status);

		$amount = dbProc::getRbfActSearchCount($employeeCode, $vvNumber, $territoryCode, $actType, $status, $authorId);
		$listing = new listing();
		$listing->setAmount($amount);
		$listingHtml = $listing->getHtml($oLink->getQuery());
		unset($oLink);

		$res = dbProc::getRbfActSearchList(
			$listing->getStartPosition(),
			$listing->getAmountOnPage(),
			$employeeCode,
			$vvNumber,
			$territoryCode,
			$actType,
			$status,
			$authorId
		);

		$oLink = new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.akt.s.30');
		$oLink->addPrm('fromRbfSearch', 1);
		$oLink->addPrm('isSearch', 1);
		$oLink->addPrm('employeeCode', $employeeCode);
		$oLink->addPrm('vvNumber', $vvNumber);
		$oLink->addPrm('territoryCode', $territoryCode);
		$oLink->addPrm('actType', $actType);
		$oLink->addPrm('authorId', $authorId);
		$oLink->addPrm('status', $status);

		if (is_array($res))
		{
			foreach ($res as $i => $row)
			{
				$oLink->addPrm('actId', $row['RAKT_ID']);
				$res[$i]['URL'] = $oLink->getQuery();
				$res[$i]['selected'] = ($row['RAKT_ID'] == $selectedId) ? 1 : 0;
			}
		}
		unset($oLink);

		$number = $listing->getStartPosition() + 1;
		include('f.akt.s.35.1.tpl');
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
