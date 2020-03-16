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
		$mmsCalcId = reqVar::get('mmsCalcId');

		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.20');
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

		// inicial state: mmsCalcId=0;
		// if mmsCalcId>0 ==> voltage selected from the list
		if($mmsCalcId != false)
		{
			// get info about voltage
			$mmsCalculationInfo = dbProc::getmmsCalculationList($mmsCalcId);
			//print_r($mmsCalculationInfo);
			if(count($mmsCalculationInfo)>0)
			{
				$mmsCalc = $mmsCalculationInfo[0];
			}
			// get user info
			$userInfo = dbProc::getUserInfo($mmsCalc['KMKL_CREATOR']);
			if(count($userInfo) >0 )
			{
				$creator = $userInfo[0]['RLTT_VARDS']. ' ' .$userInfo[0]['RLTT_UZVARDS'];
			}
			$userInfo1 = dbProc::getUserInfo($mmsCalc['KMKL_EDITOR']);
			if(count($userInfo1) >0 )
			{
				$editor = $userInfo1[0]['RLTT_VARDS']. ' ' .$userInfo1[0]['RLTT_UZVARDS'];
			}
        }

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'mmsCalcId', null, isset($mmsCalc['KMKL_ID'])? $mmsCalc['KMKL_ID']:'');

		$oForm -> addElement('text', 'requirement',  text::get('MMS_REQUIREMENT_CODE'), isset($mmsCalc['KMKL_KMSD_NOSACIJUMA_KODS'])?$mmsCalc['KMKL_KMSD_NOSACIJUMA_KODS']:'', 'tabindex=1 maxlength="11"' . (($isEdUser)?' disabled' : ''));
		$oForm -> addRule('requirement', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('requirement', text::get('ERROR_NUMERIC_VALUE'), 'numeric');

        $oForm -> addElement('text', 'chipher',  text::get('CALCULATION_CODE'), isset($mmsCalc['KMKL_KKAL_SHIFRS'])?$mmsCalc['KMKL_KKAL_SHIFRS']:'', 'tabindex=2 maxlength="5"' . (($isEdUser)?' disabled' : ''));
		$oForm -> addRule('chipher', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('chipher', text::get('ERROR_NUMERIC_VALUE'), 'numeric');
		
		$oForm -> addElement('text', 'title',  text::get('EXPORT_CALCULATION_NAME'), isset($mmsCalc['KKAL_NOSAUKUMS'])?$mmsCalc['KKAL_NOSAUKUMS']:'', 'tabindex=2 maxlength="5"' . ((true)?' disabled' : ''));
		
		$oForm -> addElement('checkbox', 'isDefault10',  text::get('DEFAULT_VOLTAGE_10'), isset($mmsCalc['KMKL_NOKL_SPRIEGUMS_10'])?$mmsCalc['KMKL_NOKL_SPRIEGUMS_10']:1, 'tabindex=3'.(($isEdUser)?' disabled' : ''));

		$oForm -> addElement('checkbox', 'isDefaultNot10',  text::get('DEFAULT_VOLTAGE_NOT_10'), isset($mmsCalc['KMKL_NOKL_SPRIEGUMS_NE_10'])?$mmsCalc['KMKL_NOKL_SPRIEGUMS_NE_10']:1, 'tabindex=4'.(($isEdUser)?' disabled' : ''));

		$oForm -> addElement('text', 'amount',  text::get('AMOUNT'), isset($mmsCalc['KMKL_DAUDZUMS'])?$mmsCalc['KMKL_DAUDZUMS']:'1.000', 'tabindex=5 maxlength="6"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('amount', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('amount', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);

		$oForm -> addElement('checkbox', 'useLine',  text::get('USE_LINE'), isset($mmsCalc['KMKL_IZMANTOT_LINIJU'])?$mmsCalc['KMKL_IZMANTOT_LINIJU']:0, 'tabindex=6'.(($isEdUser)?' disabled' : ''));
       
        $oForm -> addElement('text', 'koeficent',  text::get('KOEFICENT'), isset($mmsCalc['KMKL_KOEFICENTS'])?$mmsCalc['KMKL_KOEFICENTS']:'1.000', 'tabindex=7 maxlength="6"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('koeficent', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('koeficent', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);

		$oForm -> addElement('checkbox', 'useCord',  text::get('USE_CORD'), isset($mmsCalc['KMKL_IZMANTOT_VADU'])?$mmsCalc['KMKL_IZMANTOT_VADU']:0, 'tabindex=8'.(($isEdUser)?' disabled' : ''));

        $oForm -> addElement('checkbox', 'isActive',  text::get('IS_ACTIVE'), isset($mmsCalc['KMKL_IR_AKTIVS'])?$mmsCalc['KMKL_IR_AKTIVS']:1, 'tabindex=9'.(($isEdUser)?' disabled' : ''));

		$oForm -> addElement('checkbox', 'isEpla',  text::get('IS_EPLA'), isset($mmsCalc['KMKL_TRASE'])?$mmsCalc['KMKL_TRASE']:0, 'tabindex=10'.(($isEdUser)?' disabled' : ''));
		
		// importa dati
		$oForm -> addElement('text', 'created',  text::get('CREATED'), isset($mmsCalc['KMKL_CREATED'])?$mmsCalc['KMKL_CREATED']:dtime::now(), 'tabindex=11 maxlength="20" disabled');
		$oForm -> addElement('text', 'creator',  text::get('CREATOR'), isset($mmsCalc)?$creator:'', 'tabindex=12 maxlength="20" disabled');
		$oForm -> addElement('text', 'edited',  text::get('EDITED'), isset($mmsCalc['KMKL_EDITED'])?$mmsCalc['KMKL_EDITED']:dtime::now(), 'tabindex=13 maxlength="20" disabled');
		$oForm -> addElement('text', 'editor',  text::get('EDITOR'), isset($mmsCalc)?$editor:'', 'tabindex=14 maxlength="20" disabled');


		// form buttons
        if(!$isEdUser)
        {
    		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
    		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick=" if (!isEmptyField(\'mmsCalcId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
    		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'mmsCalcId\');parent.frame_1.unActiveRow();'));
            
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
							document.all["isEpla"].checked=false;	
							document.all["useCord"].checked=false;
							document.all["useLine"].checked=false;
							document.all["isActive"].checked=true;
							document.all["isDefault10"].checked=true;		
							document.all["isDefaultNot10"].checked=true;				
    					}
    				}
    				refreshButton("mmsCalcId");
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
			if ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && 
															is_numeric($oForm->getValue('mmsCalcId'))))
			{
								
    			if ($oForm -> getValue('requirement') && $oForm -> getValue('amount') &&
                    $oForm -> getValue('chipher') && $oForm -> getValue('koeficent')  )
    			{
    				$checkRequiredFields = true;
    			}
    			if ($checkRequiredFields)
    			{

					// chech that mms-calculation with same requirement, chipper and trase not set
					if (dbProc::mmsCalculationWithChipherExists(
                                                            $oForm->getValue('requirement'),
															$oForm->getValue('chipher'),
															$oForm->getValue('isEpla', 0),
                                                            ($oForm->getValue('action')==OP_UPDATE)?$oForm->getValue('mmsCalcId'):false)
                                                            )
					{
						$oForm->addError(text::get('ERROR_EXISTS_MMS_CALCULATION_CODE'));
						$check = false;
					}

					
					// if all is ok, do operation
					if($check)
					{


						$r=dbProc::saveMmsCalculation(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('mmsCalcId'):false),
										$oForm->getValue('requirement'),
										$oForm->getValue('chipher'),
										$oForm->getValue('isDefault10', 0),
										$oForm->getValue('isDefaultNot10', 0),
										$oForm->getValue('amount'),
										$oForm->getValue('useLine', 0),
										$oForm->getValue('koeficent'),
										$oForm->getValue('useCord', 0),
										$oForm->getValue('isActive', 0),
										$oForm->getValue('isEpla', 0),
										$userId
						);

						if (!$r)
						{
							$oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
						}
					}
				}
				else
				{
					$oForm->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
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
    			$oLink->addPrm(FORM_ID, 'f.ktl.s.20');
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
		include('f.ktl.s.20.2.tpl');
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
        $title = text::toUpper(text::get('MMS_CALCULATION'));
        // get search column list
        $columns=dbProc::getKlklName(KL_MMS_WORK_CALCULALATION);
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;


        // default sort column
        $defaultColumn = dbProc::getKlklDefaultColumn(KL_MMS_WORK_CALCULALATION);
        
        // URL to search Zinojums by number.
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.20');
    	$oLink->addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		$amount=dbProc::getmmsCalculationCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.20');
		$oLink->addPrm('editMode', 1);

		// gel list of users
		$res = dbProc::getmmsCalculationList( false,
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
				$oLink->addPrm('mmsCalcId', $row['KMKL_ID']);
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
