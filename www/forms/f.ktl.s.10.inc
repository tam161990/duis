<?
$editMode = reqVar::get('editMode');

// Main form with XMLHTTP method load this code:
if (reqVar::get('xmlHttp') == 1)
{
	//if worker
	if (reqVar::get('worker') !== false && reqVar::get('trase') !== false)
	{

        // unset previouse values of section
		?>
		for(i=document.all["contract"].length; i>=0; i--)
		{
			document.all["contract"].options[i] = null;
		}
		<?
		$res=dbProc::getDuContractNo(reqVar::get('worker'), reqVar::get('trase'));
		if (is_array($res) && count($res)>0)
		{
			?>
  			document.all["contract"].options[0] = new Option('<?=text::get('EMPTY_SELECT_OPTION');?>', '');
  			<?

            $i = 1;
			foreach ($res as $row)
			{
				// feel options array
				?>
				document.all["contract"].options[<?=$i;?>] = new Option( '<?=$row['KCNT_VV_NUMBER'];?>', '<?=$row['KCNT_VV_NUMBER'];?>');
                <?
               	$i++;
			}
		}
	}


	exit;
}
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAuditUser = dbProc::isUserInRole($userId, ROLE_AUDIT_USER);
$isEdUser = dbProc::isUserInRole($userId, ROLE_ED_USER);
$isAdmin = userAuthorization::isAdmin();
if ($isAdmin || $isAuditUser || $isEdUser)
{

	// bottom frame
	// if insert/update
	$trase = -1;
     if($editMode)
	{
		$calcId = reqVar::get('calcId');

		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.10');
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
        // get contract list
         $contract=array();
		 $contract['']=text::get('EMPTY_SELECT_OPTION');

		// inicial state: calcId=0;
		// if calcId>0 ==> voltage selected from the list
		if($calcId != false)
		{
			// get info about voltage
			$calculationInfo = dbProc::getCalculationList($calcId);
			//print_r($calculationInfo);
			if(count($calculationInfo)>0)
			{
				 $calc = $calculationInfo[0];
				 $trase = $calc['KKAL_TRASE'];
                 $res=dbProc::getDuContractNo($calc['KKAL_KWOI_KODS'], $trase);

                 if (is_array($res))
                 {
                 	foreach ($res as $row)
                 	{
                 	  $contract[$row['KCNT_VV_NUMBER']]=$row['KCNT_VV_NUMBER'];
                 	}
                 }
                 unset($res);
			}
			// get user info
			$userInfo = dbProc::getUserInfo($calc['KKAL_CREATOR']);
			if(count($userInfo) >0 )
			{
				$creator = $userInfo[0]['RLTT_VARDS']. ' ' .$userInfo[0]['RLTT_UZVARDS'];
			}
			$userInfo1 = dbProc::getUserInfo($calc['KKAL_EDITOR']);
			if(count($userInfo1) >0 )
			{
				$editor = $userInfo1[0]['RLTT_VARDS']. ' ' .$userInfo1[0]['RLTT_UZVARDS'];
			}
        }

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'calcId', null, isset($calc['KKAL_ID'])? $calc['KKAL_ID']:'');

        $oForm -> addElement('text', 'chipher',  text::get('CHIPHER'), isset($calc['KKAL_SHIFRS'])?$calc['KKAL_SHIFRS']:'', 'tabindex=3 maxlength="5"' . (($calcId || $isEdUser)?' disabled' : ''));
		$oForm -> addRule('chipher', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('chipher', text::get('ERROR_NUMERIC_VALUE'), 'numeric');

        $oForm -> addElement('kls', 'kods',  text::get('SINGL_CALCULATION_GROUP'), array('classifName'=>KL_CALCULALATION_GROUP,'value'=>isset($calc['KKAL_GRUPAS_KODS'])?$calc['KKAL_GRUPAS_KODS']:'','readonly'=>false), 'tabindex=1 maxlength="2000"'.(($isEdUser)?' disabled' : ''));
        $oForm -> addRule('kods', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('text', 'nosaukums',  text::get('NAME'), isset($calc['KKAL_NOSAUKUMS'])?$calc['KKAL_NOSAUKUMS']:'', 'tabindex=5 maxlength="150"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('nosaukums', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('textarea', 'description', text::get('DESCRIPTION'), isset($calc['KKAL_APRAKSTS'])?$calc['KKAL_APRAKSTS']:'','tabindex=7'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('description', text::get('ERROR_MAXLENGHT_REACHED'), 'maxlength',2000);

        $oForm -> addElement('text', 'fizRadijums',  text::get('FIZ_RADIJUMS'), isset($calc['KKAL_FIZ_RADIJUMS'])?$calc['KKAL_FIZ_RADIJUMS']:'', 'tabindex=8 maxlength="4"'.(($isEdUser)?' disabled' : ''));

        $oForm -> addElement('text', 'koeficent',  text::get('KOEFICENT'), isset($calc['KKAL_KOEFICENT'])?$calc['KKAL_KOEFICENT']:'', 'tabindex=9 maxlength="6"'.(($isEdUser || $trase == 1)?' disabled' : ''));
		if($trase != 1) $oForm -> addRule('koeficent', text::get('ERROR_DOUBLE_VALUE'), 'double', 3);

        $oForm -> addElement('text', 'standart',  text::get('PLAN_PRICE'), isset($calc['KKAL_PLANA'])?$calc['KKAL_PLANA']:'', 'tabindex=2 maxlength="6"'.(($isEdUser)?' disabled' : ''));
		if($trase == 1 ) {
			$oForm -> addRule('standart', text::get('ERROR_REQUIRED_FIELD'), 'required');
			$oForm -> addRule('standart', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);
			// check Standart field
			$oForm->addElement('hidden','minStandart','','0.00');
			$oForm->addElement('hidden','maxStandart','','2000.00');
			$v1=&$oForm->createValidation('standartValidation', array('standart'), 'ifonefilled');
			// ja Cilv�kstundas normat�vs ir defin�ts un > 1000
			//$r1=&$oForm->createRule(array('standart', 'minStandart'), text::get('ERROR_AMOUNT_VALUE'), 'comparedouble','>');
			$r2=&$oForm->createRule(array('standart', 'maxStandart'), text::get('ERROR_AMOUNT_VALUE_2000'), 'comparedouble','<');
			$oForm->addRule(array( $r2), 'groupRuleStandart', 'group', $v1);
		}

        $oForm -> addElement('text', 'standart_np',  text::get('NOT_PLAN_PRICE'), isset($calc['KKAL_NEPLANA'])?$calc['KKAL_NEPLANA']:'', 'tabindex=2 maxlength="6"'.(($isEdUser)?' disabled' : ''));
		if($trase == 1 ) {
			$oForm -> addRule('standart_np', text::get('ERROR_REQUIRED_FIELD'), 'required');
			$oForm -> addRule('standart_np', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);
			// check Standart field
			$oForm->addElement('hidden','minStandart_np','','0.00');
			$oForm->addElement('hidden','maxStandart_np','','2000.00');
			$v1=&$oForm->createValidation('standartValidationNp', array('standart_np'), 'ifonefilled');
			// ja Cilv�kstundas normat�vs ir defin�ts un > 1000
			//$r1=&$oForm->createRule(array('standart', 'minStandart'), text::get('ERROR_AMOUNT_VALUE'), 'comparedouble','>');
			$r2=&$oForm->createRule(array('standart_np', 'maxStandart_np'), text::get('ERROR_AMOUNT_VALUE_2000'), 'comparedouble','<');
			$oForm->addRule(array( $r2), 'groupRuleStandart_np', 'group', $v1);
		}

        $oForm -> addElement('text', 'measure',  text::get('UNIT_OF_MEASURE'), isset($calc['KKAL_MERVIENIBA'])?$calc['KKAL_MERVIENIBA']:'', 'tabindex=4 maxlength="15"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('measure', text::get('ERROR_REQUIRED_FIELD'), 'required');

		$oForm -> addElement('checkbox', 'isEpla',  text::get('TRASE'), isset($calc['KKAL_TRASE'])?$calc['KKAL_TRASE']:0, 'tabindex=6'.(($isEdUser)?' disabled' : ''));
		$oForm -> addElement('checkbox', 'isActive',  text::get('IS_ACTIVE'), isset($calc['KKAL_IR_AKTIVS'])?$calc['KKAL_IR_AKTIVS']:1, 'tabindex=6'.(($isEdUser)?' disabled' : ''));

        // xmlHttp link
  		$oLink=new urlQuery();
  		$oLink->addPrm(DONT_USE_GLB_TPL, 1);
  		$oLink->addPrm(FORM_ID, 'f.ktl.s.10');
        $oLink->addPrm('trase', $trase);
		$oForm -> addElement('kls', 'worker',  text::get('SINGL_WORK_OWNER'), array('classifName'=>KL_WORK_OWNERS,'value'=>isset($calc['KKAL_KWOI_KODS'])?$calc['KKAL_KWOI_KODS']:'','readonly'=>false), 'tabindex=7 maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&worker=\'+this.value+\'\'))" '.(($isAuditUser)?' disabled' : ''));
		if($trase == 1) $oForm -> addRule('worker', text::get('ERROR_REQUIRED_FIELD'), 'required');
        unset($oLink);

        $oForm -> addElement('kls', 'edArea',  text::get('SINGL_ED_AREA'), array('classifName'=>KL_ED_AREA_CODE,'value'=>isset($calc['KKAL_KEDI_KODS'])?$calc['KKAL_KEDI_KODS']:'','readonly'=>false), 'tabindex=13 maxlength="2000" '.(($isAuditUser)?' disabled' : ''));
		if($trase == 1) $oForm -> addRule('edArea', text::get('ERROR_REQUIRED_FIELD'), 'required');
		
		$oForm -> addElement('select', 'contract',  text::get('KWOI_VV_NUMBER'), isset($calc['KKAL_VV_NUMBER'])?$calc['KKAL_VV_NUMBER']:0, (($isAuditUser)?' disabled' : ''), '', '', $contract);

		$oForm -> addElement('checkbox', 'element',  text::get('ELEMENT'), isset($calc['KKAL_IS_ELEMENT'])?$calc['KKAL_IS_ELEMENT']:0, 'tabindex=10'.(($isAuditUser)?' disabled' : ''));
        
		// importa dati
		$oForm -> addElement('text', 'created',  text::get('CREATED'), isset($calc['KKAL_CREATED'])?$calc['KKAL_CREATED']:dtime::now(), 'tabindex=21 maxlength="20" disabled');
		$oForm -> addElement('text', 'creator',  text::get('CREATOR'), isset($calc)?$creator:'', 'tabindex=21 maxlength="20" disabled');
		$oForm -> addElement('text', 'edited',  text::get('EDITED'), isset($calc['KKAL_EDITED'])?$calc['KKAL_EDITED']:dtime::now(), 'tabindex=21 maxlength="20" disabled');
		$oForm -> addElement('text', 'editor',  text::get('EDITOR'), isset($calc)?$editor:'', 'tabindex=21 maxlength="20" disabled');
		
		// form buttons
        if($isAdmin || $isEdUser)
        {
    		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick=" setValue(\'action\',\''.OP_INSERT.'\');"');
    		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'calcId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
    		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'calcId\');parent.frame_1.unActiveRow();'));

         	$oForm -> addElement('static', 'jsButtonsControl', '', '
                <script>
    				function refreshButton(name)
    				{
    					if (!isEmptyField(name))
    					{
    						document.all["save"].src="img/btn_saglabat.gif";
                            document.all["maxAmaunt"].value = "100000.00";
                            document.all["minAmaunt"].value = "0.00";
    					}
    					else
    					{
    						document.all["save"].src="img/btn_saglabat_disabled.gif";
                            document.all["maxAmaunt"].value = "100000.00";
                            document.all["minAmaunt"].value = "0.00";
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

            // save
		    if ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('calcId'))))
			{
			  if(($trase == 1)    &&
    			 ($oForm -> getValue('kods') && $oForm -> getValue('nosaukums') &&
                    $oForm -> getValue('chipher')  &&  $oForm -> getValue('measure') &&
                    $oForm -> getValue('edArea')  &&  $oForm -> getValue('worker') &&
                      $oForm -> getValue('standart')  &&  $oForm -> getValue('standart_np') )    )
    			{
    				$checkRequiredFields = true;
				}
				
				if(($trase == 1 || $oForm->getValue('isEpla',0) == 1 )  && $oForm->getValue('standart') >=2000 ){
					$oForm->addError(text::get('PLAN_PRICE') . ' '.strtolower(text::get('ERROR_AMOUNT_VALUE_2000')));
					$checkRequiredFields = false;
					$check = false;
				}
				if(($trase == 1 || $oForm->getValue('isEpla',0) == 1 )   && $oForm->getValue('standart_np') >= 2000){
					$oForm->addError(text::get('NOT_PLAN_PRICE') . ' '.strtolower(text::get('ERROR_AMOUNT_VALUE_2000')));
					$checkRequiredFields = false;
					$check = false;
				}
				

                if(($trase == 0)    &&
    			 ($oForm -> getValue('kods') && $oForm -> getValue('nosaukums') &&
                    $oForm -> getValue('chipher')  &&  $oForm -> getValue('measure')  )    )
    			{
    				$checkRequiredFields = true;
    			}

    			if ($checkRequiredFields)
    			{
					// chech 
					if (dbProc::calculationWithChipherExists(
						$oForm->getValue('chipher'),
						$oForm->getValue('isEpla',0),
						$oForm->getValue('edArea'),
						$oForm->getValue('worker'),
						$oForm->getValue('contract'),
						($oForm->getValue('action')==OP_UPDATE)?$oForm->getValue('calcId'):false)
						)
					{
						$oForm->addError(text::get('ERROR_EXISTS_CALCULATION_CODE'));
						$check = false;
					}
					// if all is ok, do operation
					if($check)
					{
						$r=dbProc::saveCalculation(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('calcId'):false),
							$oForm->getValue('chipher'),
							$oForm->getValue('kods'),
							$oForm->getValue('nosaukums'),
							$oForm->getValue('description'),
							$oForm->getValue('standart'),
							$oForm->getValue('standart_np'),
							$oForm->getValue('measure'),
							$oForm->getValue('isActive',0),
							$oForm->getValue('isEpla',0),
							$oForm->getValue('fizRadijums'),
							$oForm->getValue('koeficent'),
							$oForm->getValue('edArea'),
							$oForm->getValue('worker'),
							$oForm->getValue('contract'),
							$oForm->getValue('element', 0),
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
    			$oLink->addPrm(FORM_ID, 'f.ktl.s.10');
    			$oLink->addPrm('editMode', '1');
                $oLink->addPrm('isTrase', $trase);
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
		include('f.ktl.s.10.2.tpl');
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
        $title = (($trase == 1) ? text::toUpper(text::get('TRASE_KALCULATION')) : text::toUpper(text::get('CALCULATION')));
        // get search column list
        $columns=dbProc::getKlklName(($trase == 1) ? KL_CALCULALATION_TR : KL_CALCULALATION);
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;


        // default sort column
        $defaultColumn = dbProc::getKlklDefaultColumn(($trase == 1) ? KL_CALCULALATION_TR : KL_CALCULALATION);
        dbProc::getCalculationGroupActivList();
        // URL to search Zinojums by number.
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.10');
    	$oLink->addPrm('isNew', '1');
        $oLink->addPrm('isTrase', $trase);

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
        if($trase == 1)
		    $amount=dbProc::getCalculationTrCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
        else
            $amount=dbProc::getCalculationCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.10');
		$oLink->addPrm('editMode', 1);
        $oLink->addPrm('isTrase', $trase);

		// gel list of users
        if($trase == 1)
		    $res = dbProc::getCalculationTrList( false,
                                        $listing->getStartPosition(),
                                        $listing->getAmountOnPage(),
                                        $searchText,
                                        (($searchColumn === false) ? $defaultColumn : $searchColumn),
                                        $sortOrder,
                                        $orderColumn);
        else
            $res = dbProc::getCalculationList( false,
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
				$oLink->addPrm('calcId', $row['KKAL_ID']);
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
