<?
//RBF Calculations catalog
$userId = userAuthorization::getUserId();
$isEdUser = (dbProc::isUserInRole($userId, ROLE_ED_USER) || dbProc::isUserInRole($userId, ROLE_AUDIT_USER));    
if (userAuthorization::isAdmin() || $isEdUser )
{
	$editMode = reqVar::get('editMode');
	// bottom frame
	// if insert/update

     if($editMode)
	{
		$calculationId = reqVar::get('calculationId');

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

		// inicial state: calculationId=0;
		// if calculationId>0 ==> calculation selected from the list
		if($calculationId != false)
		{
			// get info about calculation - placeholder for database call
			// $calculationInfo = dbProc::getRbfCalculationList($calculationId);
			// if(count($calculationInfo)>0)
			// {
			//	$calculation = $calculationInfo[0];
			// }
        }

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'calculationId', null, isset($calculation['ID'])? $calculation['ID']:'');

        $oForm -> addElement('text', 'kods',  text::get('CODE'), isset($calculation['KODS'])?$calculation['KODS']:'', 'maxlength="20"' . (($calculationId || $isEdUser)?' disabled' : ''));
		$oForm -> addRule('kods', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('text', 'nosaukums',  text::get('NAME'), isset($calculation['NOSAUKUMS'])?$calculation['NOSAUKUMS']:'', 'maxlength="100"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('nosaukums', text::get('ERROR_REQUIRED_FIELD'), 'required');

		$oForm -> addElement('checkbox', 'isActive',  text::get('IS_ACTIVE'), isset($calculation['IR_AKTIVS'])?$calculation['IR_AKTIVS']:1, ''.(($isEdUser)?' disabled' : ''));

		// form buttons
        if(!$isEdUser)
        {
    		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
    		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'calculationId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
    		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'calculationId\');parent.frame_1.unActiveRow();'));

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
    				refreshButton("calculationId");
    			</script>
    		');
        }
		// if operation
		if ($oForm -> isFormSubmitted())
		{
			$check = true;
			$r = false;
			$checkRequiredFields = false;
			if ($oForm -> getValue('kods') && $oForm -> getValue('nosaukums') )
			{
				$checkRequiredFields = true;
			}
			if ($checkRequiredFields)
			{
				// save
				if ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('calculationId'))))
				{
					// TODO: Add database validation
					// if (dbProc::rbfCalculationWithCodeExists(
                    //                            $oForm->getValue('kods'),
                    //                            ($oForm->getValue('action')==OP_UPDATE)?$oForm->getValue('calculationId'):false)
                    //                            )
					// {
					//	$oForm->addError(text::get('ERROR_EXISTS_CODE'));
					//	$check = false;
					// }

					// if all is ok, do operation
					if($check)
					{
						// TODO: Implement database save
						// $r=dbProc::saveRbfCalculation(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('calculationId'):false),
						// $oForm->getValue('kods'),
						// $oForm->getValue('nosaukums'),
						// $oForm->getValue('isActive',0)
						// );

						// Placeholder - remove when database is implemented
						$oForm->addError(text::get('ERROR_IN_DB_QUERY').' - Database not yet implemented for RBF Calculations');
						$r = false;

						if (!$r)
						{
							$oForm->addError(text::get('ERROR_IN_DB_QUERY'));
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
        // set list title
        $title = text::toUpper(text::get('RBF_CALCULATIONS'));
        
        // TODO: Implement listing functionality when database is ready
        // For now, show placeholder message
        
        echo '<body class="frame_1">';
        echo '<h1>'.$title.'</h1>';
        echo '<div style="padding: 20px;">';
        echo '<p>'.text::get('RBF_CALCULATIONS').' - Database implementation pending</p>';
        echo '</div>';
        echo '</body>';
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>

