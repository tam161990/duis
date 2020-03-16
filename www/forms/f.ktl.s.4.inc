<?
//created by Tatjana Fedorkova at 2004.12.08.
if (reqVar::get('xmlHttp') == 1)
{
   	//if is set edRegion
	if (reqVar::get('region') !== false)
	{
		// unset previouse values of edArea
		?>
		for(i=document.all["edArea"].length; i>=0; i--)
		{
			document.all["edArea"].options[i] = null;
		}
		<?
		$res=dbProc::getEDAreaListForRegion(reqVar::get('region'));
		if (is_array($res) && count($res)>0)
		{
			?>
			document.all["edArea"].options[0] = new Option('<?=text::get('EMPTY_SELECT_OPTION');?>', '');
			<?
            $i = 1;
			foreach ($res as $row)
			{
				// feel options array
				?>
				document.all["edArea"].options[<?=$i;?>] = new Option( '<?=$row['KEDI_REGIONS'].' : '.$row['KEDI_KODS'].' : '.$row['KEDI_NOSAUKUMS'];?>', '<?=$row['KEDI_ID'];?>');
                <?
                $i++;
			}
		}
        // unset previouse values of section
		?>
		for(i=document.all["section"].length; i>=0; i--)
		{
			document.all["section"].options[i] = null;
		}
		<?
		$res=dbProc::getEDSectionListForRegion(reqVar::get('region'));
		if (is_array($res) && count($res)>0)
		{
			?>
			document.all["section"].options[0] = new Option('<?=text::get('EMPTY_SELECT_OPTION');?>', '');
			<?
            $i = 1;
			foreach ($res as $row)
			{
				// feel options array
				?>
				document.all["section"].options[<?=$i;?>] = new Option( '<?=$row['KEDI_SECTION'];?>', '<?=$row['KEDI_SECTION'];?>');
                <?
                $i++;
			}
            ?>
			    document.all["section"].options[<?=$i;?>] = new Option('<?=text::get('OPERATING_PART');?>', '<?=text::get('OPERATING_PART');?>');
			<?
		}
	}
    exit;
}
$userId = userAuthorization::getUserId();
$isEdUser = (dbProc::isUserInRole($userId, ROLE_ED_USER) || dbProc::isUserInRole($userId, ROLE_AUDIT_USER));    
if (userAuthorization::isAdmin() || $isEdUser )
{
	$editMode = reqVar::get('editMode');
	// bottom frame
	// if insert/update/delete
	if($editMode)
	{



       // get position list
       $position=array();
       $position['']=text::get('EMPTY_SELECT_OPTION');
       $res=dbProc::getKrfkName(KRFK_POSITION);
       if (is_array($res))
       {
       	foreach ($res as $row)
       	{
       		$position[$row['nosaukums']]=$row['nozime'];
       	}
       }
       unset($res);

       // get region list
        $region=array();
        $region['']=text::get('EMPTY_SELECT_OPTION');
        $res=dbProc::getEDRegionList();

        if (is_array($res))
        {
          	foreach ($res as $row)
          	{
           		$region[$row['nosaukums']]=$row['nosaukums'];
           	}
        }
        unset($res);

       // get section list
       $sections=array();
       $sections['']=text::get('EMPTY_SELECT_OPTION');
       $res=dbProc::getEDAreaSectionList();
		if (is_array($res))
		{
			foreach ($res as $row)
			{
				$sections[$row['KEDI_SECTION']]=$row['KEDI_SECTION'];
			}
            $sections[text::get('OPERATING_PART')]=text::get('OPERATING_PART');
		}
       unset($res);


		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.4');
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

        // inicial state: usetrId=0;
        $usrId = reqVar::get('usrId');
		// if usrId>0 ==> user selected from the list
		if($usrId != false)
		{
			// get info about user
            $userInf = dbProc::getHarmonizedList($usrId);
			//print_r($userInf);
            if(count($userInf)>0)
			{
				$user = $userInf[0];
			}

			// get user info
			$creator = '';
			$editor = '';
			$userInfo = dbProc::getUserInfo($user['SLTT_CREATOR']);
			if(count($userInfo) >0 )
			{
				$creator = $userInfo[0]['RLTT_VARDS']. ' ' .$userInfo[0]['RLTT_UZVARDS'];
			}
			$userInfo1 = dbProc::getUserInfo($user['SLTT_CREATOR']);
			if(count($userInfo1) >0 )
			{
				$editor = $userInfo1[0]['RLTT_VARDS']. ' ' .$userInfo1[0]['RLTT_UZVARDS'];
			}
		}

        // form elements
		$oForm -> addElement('hidden', 'action', '');



		$oForm -> addElement('hidden', 'usrId', null, isset($user['SLTT_ID'])?$user['SLTT_ID']:'');


		$oForm -> addElement('text', 'name',  text::get('USER_NAME'), isset($user['SLTT_VARDS'])?$user['SLTT_VARDS']:'', 'tabindex=1 maxlength="30"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('name', text::get('ERROR_REQUIRED_FIELD'), 'required');

		$oForm -> addElement('text', 'surname',  text::get('USER_SURNAME'), isset($user['SLTT_UZVARDS'])?$user['SLTT_UZVARDS']:'', 'tabindex=2 maxlength="30"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('surname', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('text', 'department',  text::get('ED_IECIKNIS'), isset($user['SLTT_ED_IECIKNIS'])?$user['SLTT_ED_IECIKNIS']:'', 'tabindex=2 maxlength="250"'.(($isEdUser)?' disabled' : ''));
		$oForm -> addRule('department', text::get('ERROR_REQUIRED_FIELD'), 'required');

        // xmlHttp link
		$oLink=new urlQuery();
		$oLink->addPrm(DONT_USE_GLB_TPL, 1);
		$oLink->addPrm(FORM_ID, 'f.ktl.s.4');
	    $oForm -> addElement('select', 'region',  text::get('REGION'), isset($user['SLTT_REGIONS'])?$user['SLTT_REGIONS']:'', 'onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&region=\'+document.all[\'region\'].options[document.all[\'region\'].selectedIndex].value));" tabindex=4'.(($isEdUser)? ' disabled ': ''), '', '', $region);
        $oForm -> addRule('region', text::get('ERROR_REQUIRED_FIELD'), 'required');
        unset($oLink);

        $oForm -> addElement('select', 'position',  text::get('POSITION'), isset($user['SLTT_POSITION'])?$user['SLTT_POSITION']:'', 'tabindex=3 '.(($isEdUser)?' disabled' : ''), '', '', $position);
        $oForm -> addRule('position', text::get('ERROR_REQUIRED_FIELD'), 'required');

//        $oForm -> addElement('kls', 'section',  text::get('ED_SECTION'), array('classifName'=>KL_ED_SECTIONS,'value'=>isset($user['SLTT_KEDI_SECTION'])?$user['SLTT_KEDI_SECTION']:'','readonly'=>false), 'tabindex=5 maxlength="2000" ');
       $oForm -> addElement('select', 'section',  text::get('ED_SECTION'), isset($user['SLTT_KEDI_SECTION'])?$user['SLTT_KEDI_SECTION']:'', 'tabindex=5 '.(($isEdUser)?' disabled' : ''), '', '', $sections);
       $oForm -> addRule('section', text::get('ERROR_REQUIRED_FIELD'), 'required');

		$oForm -> addElement('kls', 'edArea',  text::get('SINGL_ED_AREA'), array('classifName'=>KL_ED_AREA,'value'=>isset($user['SLTT_KEDI_ID'])?$user['SLTT_KEDI_ID']:'','readonly'=>false), 'tabindex=6 maxlength="2000" '.(( $isEdUser)? ' disabled ': ''));

		$oForm -> addElement('checkbox', 'isActive',  text::get('STATUS_ACTIVE_INACTIVE'), isset($user['SLTT_IR_AKTIVS'])?$user['SLTT_IR_AKTIVS']:1, 'tabindex=7 onClick="if(!this.checked){alert(\''.text::get('WARNING_USER_NOT_ACTIVE').'\');}" '.(($isEdUser)?' disabled' : ''));

		// importa dati
		$oForm -> addElement('text', 'created',  text::get('CREATED'), isset($user['SLTT_CREATED'])?$user['SLTT_CREATED']:dtime::now(), 'tabindex=21 maxlength="20" disabled');
		$oForm -> addElement('text', 'creator',  text::get('CREATOR'), isset($creator)?$creator:'', 'tabindex=21 maxlength="20" disabled');
		$oForm -> addElement('text', 'edited',  text::get('EDITED'), isset($user['SLTT_EDITED'])?$user['SLTT_EDITED']:dtime::now(), 'tabindex=21 maxlength="20" disabled');
		$oForm -> addElement('text', 'editor',  text::get('EDITOR'), isset($editor)?$editor:'', 'tabindex=21 maxlength="20" disabled');


		// form buttons
        if(!$isEdUser)
        {
    		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
    		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'usrId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
    		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'usrId\');parent.frame_1.unActiveRow();'));

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
    				refreshButton("usrId");
    			</script>
    		');
        }
		// if operation
		if ($oForm -> isFormSubmitted())
		{
			$check = true;
			$r = false;
			$checkRequiredFields = false;
           	if ($oForm -> getValue('region') && $oForm -> getValue('name') && $oForm -> getValue('surname') && $oForm -> getValue('position') && $oForm -> getValue('section') && $oForm -> getValue('department')  )
			{
				$checkRequiredFields = true;
			}
			if ($checkRequiredFields)
			{
				// save
				if ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('usrId'))))
				{
					// chech that user with same name/surname not set
					/*if (dbProc::isHasHarmonized($oForm->getValue('name'),$oForm->getValue('surname'), ($oForm->getValue('action')==OP_UPDATE)?$oForm->getValue('usrId'):false))
					{
						$oForm->addError(text::get('ERROR_EXISTS_HARMONIZED_NAME'));
						$check = false;
					}*/


					// if all is ok, do operation
					if($check)
					{
						$r=dbProc::saveHarmonized(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('usrId'):false),
						$oForm->getValue('name'),
						$oForm->getValue('surname'),
						$oForm->getValue('edArea'),
						$oForm->getValue('isActive', 0),
						$oForm->getValue('region'),
                        $oForm->getValue('position'),
                        $oForm->getValue('department'),
						$oForm->getValue('section'),
						$userId
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
					$oLink->addPrm(FORM_ID, 'f.ktl.s.4');
					$oLink->addPrm('editMode', '1');
					switch($oForm->getValue('action'))
					{
						case OP_INSERT:
							$oLink->addPrm('successMessage', text::get('USER_WAS_ADDED'));
							break;
						case OP_UPDATE:
							$oLink->addPrm('successMessage', text::get('USER_WAS_UPDATED'));
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
		include('f.ktl.s.4.2.tpl');
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
        $title = text::toUpper(text::get('HARMONIZED'));
        // get search column list
        $columns=dbProc::getKlklName(KL_HARMONIZED);
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;


        // default sort column
        $defaultColumn = dbProc::getKlklDefaultColumn(KL_HARMONIZED);

        // URL to search Zinojums by number.
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.4');
    	$oLink->addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		$amount=dbProc::getHarmonizedCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.4');
		$oLink->addPrm('editMode', 1);

		// gel list of users
		$res = dbProc::getHarmonizedList( false,
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
				$oLink->addPrm('usrId', $row['SLTT_ID']);
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