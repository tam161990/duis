<?
$userId = userAuthorization::getUserId();
$isEdUser = (dbProc::isUserInRole($userId, ROLE_ED_USER) || dbProc::isUserInRole($userId, ROLE_AUDIT_USER));    
if (userAuthorization::isAdmin() || $isEdUser )
{
	$editMode = reqVar::get('editMode');
	// bottom frame
	// if insert/update

     if($editMode)
	{
		$regionId = reqVar::get('regionId');

		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.3');
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

		// inicial state: $regionId=0;
		// if $regionId>0 ==> region selected from the list
		if($regionId != false)
		{
			// get info about ED area
			$regionInfo = dbProc::getRegionList($regionId);

			if(count($regionInfo)>0)
			{
				$regions = $regionInfo[0];
			}
        }

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'regionId', null, isset($regions['REGI_ID'])? $regions['REGI_ID']:'');

        $oForm -> addElement('text', 'kods',  text::get('REGION'), isset($regions['REGI_KODS'])?$regions['REGI_KODS']:'', 'tabindex=1 maxlength="3"' .(($regionId || $isEdUser)?' disabled' : ''));
		$oForm -> addRule('kods', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('kods', text::get('ERROR_ALPHANUMERIC_VALUE'), 'alphanumeric');


        $oForm -> addElement('text', 'nosaukums',  text::get('NAME'), isset($regions['REGI_NOSAUKUMS'])?$regions['REGI_NOSAUKUMS']:'', 'tabindex=2 maxlength="250"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('nosaukums', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('checkbox', 'isActive',  text::get('IS_ACTIVE'), isset($regions['REGI_IR_AKTIVS'])?$regions['REGI_IR_AKTIVS']:1, 'tabindex=3'.(($isEdUser)?' disabled' : ''));

        // form buttons
        if(!$isEdUser)
        {
      		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
      		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'regionId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
      		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'regionId\');parent.frame_1.unActiveRow();'));
          
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
      				refreshButton("regionId");
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
			if ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('regionId'))))
			{
      			if ( $oForm -> getValue('kods') && $oForm -> getValue('nosaukums')  )
      			{
      				$checkRequiredFields = true;
      			}
      			if ($checkRequiredFields)
      			{

					// chech that ED area with same region and code not set
                    /*if (dbProc::edAreaWithRegionCodeExists(
                                                            $oForm->getValue('region'),
                                                            $oForm->getValue('kods'),
                                                            ($oForm->getValue('action')==OP_UPDATE)?$oForm->getValue('edAId'):false)
                                                            )
					{
						$oForm->addError(text::get('ERROR_EXISTS_ED_AREA'));
						$check = false;
					}*/

					// if all is ok, do operation
					if($check)
					{
						$r=dbProc::saveRegion(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('regionId'):false),
					   	$oForm->getValue('kods'),
						$oForm->getValue('nosaukums'),
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
    			$oLink->addPrm(FORM_ID, 'f.ktl.s.3');
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
		include('f.ktl.s.3.2.tpl');
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
        $title = text::toUpper(text::get('REGIONS'));
        // get search column list
        $columns=dbProc::getKlklName(KL_REGIONS);
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;


        // default sort column
        $defaultColumn = dbProc::getKlklDefaultColumn(KL_REGIONS);

        // URL to search Zinojums by number.
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.3');
    	$oLink->addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		$amount=dbProc::getRegionCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.3');
		$oLink->addPrm('editMode', 1);

		// gel list of users
		$res = dbProc::getRegionList( false,
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
				$oLink->addPrm('regionId', $row['REGI_ID']);
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
