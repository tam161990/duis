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
		$matId = reqVar::get('matId');

		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.1');
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

		// inicial state: matId=0;
		// if matId>0 ==> voltage selected from the list
		if($matId != false)
		{
			// get info about voltage
			$materialInfo = dbProc::getMaterialList($matId);
			//print_r($materialInfo);
			if(count($materialInfo)>0)
			{
				$material = $materialInfo[0];
			}
        }

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'matId', null, isset($material['KMAT_ID'])? $material['KMAT_ID']:'');

        $oForm -> addElement('text', 'kods',  text::get('CODE'), isset($material['KMAT_KODS'])?$material['KMAT_KODS']:'', 'tabindex=1 maxlength="7"' . (($matId || $isEdUser)?' disabled' : ''));
		$oForm -> addRule('kods', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('kods', text::get('ERROR_ALPHANUMERIC_VALUE'), 'alphanumeric');

        $oForm -> addElement('text', 'nosaukums',  text::get('NAME'), isset($material['KMAT_NOSAUKUMS'])?$material['KMAT_NOSAUKUMS']:'', ' tabindex=3 maxlength="160"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('nosaukums', text::get('ERROR_REQUIRED_FIELD'), 'required');



        $oForm -> addElement('text', 'measure',  text::get('UNIT_OF_MEASURE'), isset($material['KMAT_MERVIENIBA'])?$material['KMAT_MERVIENIBA']:'', ' tabindex=5 maxlength="15"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('measure', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('text', 'amount',  text::get('AMOUNT'), isset($material['KMAT_DAUDZUMS'])?$material['KMAT_DAUDZUMS']:'', ' tabindex=4 maxlength="8"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('amount', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);
        // check Amount field
        $oForm->addElement('hidden','maxAmount','','100000.00');
        $v1=&$oForm->createValidation('amountValidation', array('amount'), 'ifonefilled');
        // ja mērvienība ir definēts un > 1000
        $r1=&$oForm->createRule(array('amount', 'maxAmount'), text::get('ERROR_AMOUNT_VALUE'), 'comparedouble','<');
        $oForm->addRule(array($r1), 'groupRuleAmount', 'group', $v1);

        $oForm -> addElement('text', 'price',  text::get('PRICE'), isset($material['KMAT_CENA'])?$material['KMAT_CENA']:'', ' tabindex=2  maxlength="8"'.(($isEdUser)?' disabled' : ''));
        $oForm -> addRule('price', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('price', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);
        // check Price field
        $oForm->addElement('hidden','minPrice','','0.00');
        $oForm->addElement('hidden','maxPrice','','100000.00');
        $v2=&$oForm->createValidation('priceValidation', array('price'), 'ifonefilled');
        // ja cena ir definēta un > 1000
        $r1=&$oForm->createRule(array('price', 'minPrice'), text::get('ERROR_AMOUNT_VALUE'), 'comparedouble','>');
        $r2=&$oForm->createRule(array('price', 'maxPrice'), text::get('ERROR_AMOUNT_VALUE'), 'comparedouble','<');
        $oForm->addRule(array($r1, $r2), 'groupRulePrice', 'group', $v2);

		$oForm -> addElement('checkbox', 'isActive',  text::get('IS_ACTIVE'), isset($material['KMAT_IR_AKTIVS'])?$material['KMAT_IR_AKTIVS']:1, ' tabindex=6 '.(($isEdUser)?' disabled' : ''));

		// form buttons
        if(!$isEdUser)
        {
    		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
    		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'matId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
    		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'matId\');parent.frame_1.unActiveRow();'));
           

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
    				refreshButton("matId");
    			</script>
    		');
        }
		// if operation
		if ($oForm -> isFormSubmitted())
		{
			$check = true;
			$r = false;

            // delete favorits
            if ($oForm->getValue('action')== OP_DELETE )
            {
               $favorit = dbProc::getKrfkInfo(20);

               $r = dbProc::deleteNotActivFromUserFavorit($favorit['KRFK_VERTIBA']) ;

            }
            // save
            elseif ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('matId'))))
            {
    			$checkRequiredFields = false;
    			if ($oForm -> getValue('kods') && $oForm -> getValue('nosaukums') &&
                    $oForm -> getValue('price') && $oForm -> getValue('measure') )
    			{
    				$checkRequiredFields = true;
    			}
    			if ($checkRequiredFields)
    			{

  					// chech that ED area with same region and code not set
  					if (dbProc::materialWithCodeExists(    $oForm->getValue('kods'),
                                                              ($oForm->getValue('action')==OP_UPDATE)?$oForm->getValue('matId'):false)
                                                              )
  					{
  						$oForm->addError(text::get('ERROR_EXISTS_MATERIALS_CODE'));
  						$check = false;
  					}

  					// if all is ok, do operation
  					if($check)
  					{
  						$r=dbProc::saveMaterial(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('matId'):false),
  						$oForm->getValue('kods'),
                          $oForm->getValue('nosaukums'),
                          $oForm->getValue('price'),
                          $oForm->getValue('amount'),
                          $oForm->getValue('measure'),
  						$oForm->getValue('isActive',0)
  						);

  						if (!$r)
  						{
  							$oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
  						}

    				}
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
    			$oLink->addPrm(FORM_ID, 'f.ktl.s.1');
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
		include('f.ktl.s.1.2.tpl');
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
        $title = text::toUpper(text::get('MATERIALS'));
        // get search column list
        $columns=dbProc::getKlklName(KL_MATERIALS);
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;

        // default sort column
        $defaultColumn = dbProc::getKlklDefaultColumn(KL_MATERIALS);

        // URL to search Zinojums by number.
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.1');
    	$oLink->addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		$amount=dbProc::getMaterialCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.1');
		$oLink->addPrm('editMode', 1);

		// gel list of users
		$res = dbProc::getMaterialList( false,
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
				$oLink->addPrm('matId', $row['KMAT_ID']);
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
