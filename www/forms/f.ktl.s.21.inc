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
		$calcMaterialId = reqVar::get('calcMaterialId');

		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.21');
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

		// inicial state: calcMaterialId=0;
		// if calcMaterialId>0 ==> voltage selected from the list
		if($calcMaterialId != false)
		{
			// get info about voltage
			$calculationMaterialInfo = dbProc::getCalculationMaterialList($calcMaterialId);
			//print_r($calculationMaterialInfo);
			if(count($calculationMaterialInfo)>0)
			{
				$calcMaterial = $calculationMaterialInfo[0];
			}
			// get user info
			$creator = '';
			$editor = '';
			$userInfo = dbProc::getUserInfo($calcMaterial['KKMT_CREATOR']);
			if(count($userInfo) >0 )
			{
				$creator = $userInfo[0]['RLTT_VARDS']. ' ' .$userInfo[0]['RLTT_UZVARDS'];
			}
			$userInfo1 = dbProc::getUserInfo($calcMaterial['KKMT_EDITOR']);
			if(count($userInfo1) >0 )
			{
				$editor = $userInfo1[0]['RLTT_VARDS']. ' ' .$userInfo1[0]['RLTT_UZVARDS'];
			}
        }

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'calcMaterialId', null, isset($calcMaterial['KKMT_ID'])? $calcMaterial['KKMT_ID']:'');

		$oForm -> addElement('text', 'chipher',  text::get('CALCULATION_CODE'), isset($calcMaterial['KKMT_KKAL_SHIFRS'])?$calcMaterial['KKMT_KKAL_SHIFRS']:'', 'tabindex=1 maxlength="5"' . (($isEdUser)?' disabled' : ''));
		$oForm -> addRule('chipher', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('chipher', text::get('ERROR_NUMERIC_VALUE'), 'numeric');

		$oForm -> addElement('text', 'calc_title',  text::get('EXPORT_CALCULATION_NAME'), isset($calcMaterial['KKAL_NOSAUKUMS'])?$calcMaterial['KKAL_NOSAUKUMS']:'', 'tabindex=2 maxlength="5"' . ((true)?' disabled' : ''));

		$oForm -> addElement('text', 'group',  text::get('MATERIAL_GROUP_CODE'), isset($calcMaterial['KKMT_KMAT_GRUPA'])?$calcMaterial['KKMT_KMAT_GRUPA']:'', 'tabindex=2 maxlength="4"' . (($isEdUser)?' disabled' : ''));
		$oForm -> addRule('group', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('group', text::get('ERROR_NUMERIC_VALUE'), 'numeric');
		
		$oForm -> addElement('text', 'subgroup',  text::get('MATERIAL_SUBGROUP_CODE'), isset($calcMaterial['KKMT_KMAT_APAKSGRUPA'])?$calcMaterial['KKMT_KMAT_APAKSGRUPA']:'', 'tabindex=3 maxlength="3"' . (($isEdUser)?' disabled' : ''));
		$oForm -> addRule('subgroup', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('subgroup', text::get('ERROR_NUMERIC_VALUE'), 'numeric');
		
		$oForm -> addElement('text', 'group_title',  text::get('MATERIAL_CATEGORY'), isset($calcMaterial['KMAT_KATEGORIJAS_NOSAUKUNS'])?$calcMaterial['KMAT_KATEGORIJAS_NOSAUKUNS']:'', 'tabindex=2 maxlength="5"' . ((true)?' disabled' : ''));

		$oForm -> addElement('text', 'matr_code',  text::get('MATERIAL_KODS'), isset($calcMaterial['KKMT_KMAT_KODS'])?$calcMaterial['KKMT_KMAT_KODS']:'', 'tabindex=4 maxlength="7"' . (($isEdUser)?' disabled' : ''));
		$oForm -> addRule('matr_code', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('matr_code', text::get('ERROR_NUMERIC_VALUE'), 'numeric');
		
		$oForm -> addElement('checkbox', 'useMaterial',  text::get('JUSE_MATERIAL'), isset($calcMaterial['KKMT_IZMANTOT_NOMENKLATURU'])?$calcMaterial['KKMT_IZMANTOT_NOMENKLATURU']:1, 'tabindex=5'.(($isEdUser)?' disabled' : ''));

		$oForm -> addElement('checkbox', 'isDefault',  text::get('DEFAULT_MATERIAL'), isset($calcMaterial['KKMT_NOKLUSETAIS'])?$calcMaterial['KKMT_NOKLUSETAIS']:1, 'tabindex=6'.(($isEdUser)?' disabled' : ''));

		$oForm -> addElement('text', 'amount',  text::get('AMOUNT'), isset($calcMaterial['KKMT_DAUDZUMS'])?$calcMaterial['KKMT_DAUDZUMS']:'1.000', 'tabindex=7 maxlength="6"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('amount', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('amount', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);

		$oForm -> addElement('checkbox', 'useLine',  text::get('USE_LINE'), isset($calcMaterial['KKMT_IZMANTOT_LINIJU'])?$calcMaterial['KKMT_IZMANTOT_LINIJU']:0, 'tabindex=8'.(($isEdUser)?' disabled' : ''));
       
        $oForm -> addElement('text', 'koeficent',  text::get('KOEFICENT'), isset($calcMaterial['KKMT_KOEFICENTS'])?$calcMaterial['KKMT_KOEFICENTS']:'1.000', 'tabindex=9 maxlength="6"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('koeficent', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('koeficent', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);

		$oForm -> addElement('checkbox', 'useCord',  text::get('USE_CORD'), isset($calcMaterial['KKMT_IZMANTOT_VADU'])?$calcMaterial['KKMT_IZMANTOT_VADU']:0, 'tabindex=10'.(($isEdUser)?' disabled' : ''));

        $oForm -> addElement('checkbox', 'isActive',  text::get('IS_ACTIVE'), isset($calcMaterial['KKMT_IR_AKTIVS'])?$calcMaterial['KKMT_IR_AKTIVS']:1, 'tabindex=11'.(($isEdUser)?' disabled' : ''));

			
		// importa dati
		$oForm -> addElement('text', 'created',  text::get('CREATED'), isset($calcMaterial['KKMT_CREATED'])?$calcMaterial['KKMT_CREATED']:dtime::now(), 'tabindex=13 maxlength="20" disabled');
		$oForm -> addElement('text', 'creator',  text::get('CREATOR'), isset($calcMaterial)?$creator:'', 'tabindex=14 maxlength="20" disabled');
		$oForm -> addElement('text', 'edited',  text::get('EDITED'), isset($calcMaterial['KKMT_EDITED'])?$calcMaterial['KKMT_EDITED']:dtime::now(), 'tabindex=15 maxlength="20" disabled');
		$oForm -> addElement('text', 'editor',  text::get('EDITOR'), isset($calcMaterial)?$editor:'', 'tabindex=16 maxlength="20" disabled');


		// form buttons
        if(!$isEdUser)
        {
    		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
    		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick=" if (!isEmptyField(\'calcMaterialId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
    		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'calcMaterialId\');parent.frame_1.unActiveRow();'));
            
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
							document.all["useCord"].checked=false;
							document.all["useLine"].checked=false;
							document.all["isActive"].checked=true;
							document.all["useMaterial"].checked=true;		
							document.all["isDefault"].checked=true;				
    					}
    				}
    				refreshButton("calcMaterialId");
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
															is_numeric($oForm->getValue('calcMaterialId'))))
			{
								
    			if ($oForm -> getValue('group') && $oForm -> getValue('amount') &&
					$oForm -> getValue('chipher') && $oForm -> getValue('koeficent') &&
					$oForm -> getValue('subgroup') && $oForm -> getValue('matr_code') )
    			{
    				$checkRequiredFields = true;
    			}
    			if ($checkRequiredFields)
    			{

					// chech that mms-calculation with same requirement, chipper and trase not set
					if (dbProc::calcMaterialWithChipherExists(
															$oForm->getValue('group'),
															$oForm->getValue('subgroup'),
															$oForm->getValue('chipher'),
															$oForm->getValue('matr_code'),															
                                                            ($oForm->getValue('action')==OP_UPDATE)?$oForm->getValue('calcMaterialId'):false)
                                                            )
					{
						$oForm->addError(text::get('ERROR_EXISTS_CALC_MATERIAL_CODE'));
						$check = false;
					}

					
					// if all is ok, do operation
					if($check)
					{


						$r=dbProc::saveCalcMaterial(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('calcMaterialId'):false),
										$oForm->getValue('chipher'),
										$oForm->getValue('group'),
										$oForm->getValue('subgroup'),
										$oForm->getValue('matr_code'),
										$oForm->getValue('useMaterial', 0),
										$oForm->getValue('isDefault', 0),
										$oForm->getValue('amount'),
										$oForm->getValue('useLine', 0),
										$oForm->getValue('koeficent'),
										$oForm->getValue('useCord', 0),
										$oForm->getValue('isActive', 0),										
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
    			$oLink->addPrm(FORM_ID, 'f.ktl.s.21');
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
		include('f.ktl.s.21.2.tpl');
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
        $title = text::toUpper(text::get('CALCULATION_MATERIAL'));
        // get search column list
        $columns=dbProc::getKlklName(KL_CALCULALATION_MATERIAL);
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;


        // default sort column
        $defaultColumn = dbProc::getKlklDefaultColumn(KL_CALCULALATION_MATERIAL);
        
        // URL to search Zinojums by number.
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.21');
    	$oLink->addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		$amount=dbProc::getCalculationMaterialCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.21');
		$oLink->addPrm('editMode', 1);

		// gel list of users
		$res = dbProc::getCalculationMaterialList( false,
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
				$oLink->addPrm('calcMaterialId', $row['KKMT_ID']);
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
