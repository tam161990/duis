<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isEdUser = (dbProc::isUserInRole($userId, ROLE_ED_USER) || dbProc::isUserInRole($userId, ROLE_AUDIT_USER));

$workerCode = reqVar::get('id');
$editMode = reqVar::get('editMode');

if (userAuthorization::isAdmin() || $isEdUser )
{
	// bottom frame
	// if insert/update

    if($editMode)
	{
		$contactId = reqVar::get('contactId');

		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.15');
		$oLink->addPrm('id', $workerCode);
		$oLink->addPrm('editMode', 1 );
		// form inicialization
		$oForm = new Form('frmMain1','post',$oLink->getQuery());
		unset($oLink);

		// if operation is success, show success message and redirect top frame
		if (reqVar::get('successMessage'))
		{
			$oForm->addSuccess(reqVar::get('successMessage'));
			$oForm->addElement('static','jsRefresh2','','<script>refreshFrame(1);</script>');
		}

		// inicial state: contactId=0;
		// if contactId>0 ==>  selected from the list
		if($contactId != false)
		{
			// get info about voltage
			$contractInfo = dbProc::getDUcontractList($contactId);
			if(count($contractInfo)>0)
			{
				$contract = $contractInfo[0];
			}
        }

		// form elements
		$oForm -> addElement('hidden', 'action', '');	
		$oForm -> addElement('hidden', 'contractId', null, isset($contract['KCNT_ID'])? $contract['KCNT_ID']:'');
    	// trase
    	$oForm -> addElement('checkbox', 'isTrase',  text::get('TRASE'),  isset($contract['KCNT_IR_TRASE'])?$contract['KCNT_IR_TRASE']:'0', ''.(($isEdUser)?' disabled' : ''));
        // is active
    	$oForm -> addElement('checkbox', 'isActive',  text::get('IS_ACTIVE'),  isset($contract['KCNT_IR_AKTIVS'])?$contract['KCNT_IR_AKTIVS']:'0', ''.(($isEdUser)?' disabled' : ''));
		// contract no
		$oForm -> addElement('text', 'contractNo',  text::get('KWOI_VV_NUMBER'), isset($contract['KCNT_VV_NUMBER'])?$contract['KCNT_VV_NUMBER']:'', 'maxlength="250"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('contractNo', text::get('ERROR_REQUIRED_FIELD'), 'required');
    	// parakstitajs
	    $oForm -> addElement('text', 'signatory',  text::get('SIGNATORY'), isset($contract['KCNT_SIGNATORY'])?$contract['KCNT_SIGNATORY']:'', 'maxlength="250"'.(($isEdUser)?' disabled' : ''));
	    //$oForm -> addRule('signatory', text::get('ERROR_REQUIRED_FIELD'), 'required');
	   	// ed area
		$oForm -> addElement('kls', 'edArea',  text::get('SINGL_ED_AREA'), array('classifName'=>KL_ED_AREA_CODE,'value'=>isset($contract['KONT_KEDI_KODS'])?$contract['KONT_KEDI_KODS']:'','readonly'=>false), 'tabindex=13 maxlength="2000" '.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('edArea', text::get('ERROR_REQUIRED_FIELD'), 'required');
		// form buttons
		if(!$isEdUser)
        {
			$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
			$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'contractId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
			$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'contractId\');parent.frame_1.unActiveRow();'));

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
					refreshButton("contractId");
				</script>
			');
        }
		// if operation
		if ($oForm -> isFormSubmitted())
		{
			$check = true;
			$r = false;
			$checkRequiredFields = false;
			if ( $oForm -> getValue('contractNo') && $oForm -> getValue('edArea') )
			{
				$checkRequiredFields = true;
			}
			if ($checkRequiredFields)
			{
				// save
				if ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('contractId'))))
				{

					// check that title is unique
					if(dbProc::isEqualContract($oForm->getValue('contractNo'), 
												$oForm->getValue('edArea'), 
												$oForm->getValue('isTrase',0),
												(($oForm->getValue('action')==OP_UPDATE)?$oForm->getValue('contractId'):false)
					)){
    					// edd error message to incorrect element
    					$oForm->addError(text::get('ERROR_CONTRACT_EXIST'));
						$check = false;
    				}
					// if all is ok, do operation
					if($check)
					{
						$r=dbProc::saveContractNo(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('contractId'):false),
						$workerCode, 
						$oForm->getValue('isTrase',0),
						$oForm->getValue('contractNo'),
						$oForm->getValue('edArea'),
						$oForm->getValue('isActive',0),
                        $oForm->getValue('signatory')
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
					$oLink->addPrm(FORM_ID, 'f.ktl.s.15');
					$oLink->addPrm('editMode', '1');
					$oLink->addPrm('id', $workerCode);
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
		include('f.ktl.s.15.2.tpl');
		
	}
	// top frale
	else
	{ 
        // set list title
        $title = text::toUpper(text::get('KWOI_VV_NUMBER'));
        
		// inicialising of listing object
		$amount=dbProc::getDUcontractCount($workerCode);
		$listing=new listing();
		$listing->setAmount($amount);

		$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.15');
		$oLink->addPrm('isNew', '1');
		$oLink->addPrm('id', $workerCode);
		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.15');
		$oLink->addPrm('id', $workerCode);
		$oLink->addPrm('editMode', 1);

		// gel list of users
		$res = dbProc::getDUcontractList(false,
										$workerCode,
                                        $listing->getStartPosition(),
                                        $listing->getAmountOnPage());

		if (is_array($res))
		{
			foreach ($res as $i=>$row)
			{
				// add dv area Id to each link
				$oLink->addPrm('contactId', $row['KCNT_ID']);
				$res[$i]['URL']=$oLink ->getQuery();
			}
		}
		unset($oLink);

		// inicial state of users number
		$number=$listing->getStartPosition()+1;

		include('f.ktl.s.15.1.tpl');
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
