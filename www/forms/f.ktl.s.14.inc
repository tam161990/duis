<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAuditUser = dbProc::isUserInRole($userId, ROLE_AUDIT_USER);
$isEdUser = dbProc::isUserInRole($userId, ROLE_ED_USER);
$isAdmin = userAuthorization::isAdmin();


$editMode = reqVar::get('editMode');
$mmsId = reqVar::get('mmsId');
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

            $i = 0;
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
if ($isAdmin || $isEdUser || $isAuditUser)
{

	// bottom frame
	// if insert/update

     if($editMode)
	{


		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.14');
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

         $contract = array();
         $contract['']=text::get('EMPTY_SELECT_OPTION');
		// inicial state: mmsId=0;
		// if mmsId>0 ==> mms selected from the list
		if($mmsId != false)
		{
			// get info about voltage
			$mmsInfo = dbProc::getMMSWorkList($mmsId);
			//print_r($materialInfo);
			if(count($mmsInfo)>0)
			{
				$mms = $mmsInfo[0];
                $res=dbProc::getDuContractNo($mms['KMSD_IZPILDITAJA_KODS'], -1);

                 if (is_array($res))
                 {
                 	foreach ($res as $row)
                 	{
                 	  $contract[$row['KCNT_VV_NUMBER']]=$row['KCNT_VV_NUMBER'];
                 	}
                 }
				 unset($res);
				 
				 // get user info
				$userInfo = dbProc::getUserInfo($mms['KMSD_CREATOR']);
				if(count($userInfo) >0 )
				{
					$creator = $userInfo[0]['RLTT_VARDS']. ' ' .$userInfo[0]['RLTT_UZVARDS'];
				}

				$userInfo1 = dbProc::getUserInfo($mms['KMSD_EDITOR']);
				if(count($userInfo1) >0 )
				{
					$editor = $userInfo1[0]['RLTT_VARDS']. ' ' .$userInfo1[0]['RLTT_UZVARDS'];
				}
			}
        }

        $isDelete = false;
        if(isset($mms['IS_ACT']) && $mms['IS_ACT'] == 0)
        {
           $isDelete = true;
		}
		$isEdit = false;
		if(isset($mms['IS_APPROVED_ACT']) && $mms['IS_APPROVED_ACT'] == 0)
        {
           $isEdit = true;
		}
		
		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'mmsId', null, isset($mms['KMSD_ID'])? $mms['KMSD_ID']:'');

        $oForm -> addElement('text', 'kods',  text::get('CODE'), isset($mms['KMSD_KODS'])?$mms['KMSD_KODS']:'', 'tabindex=1 maxlength="20"' . (($mmsId || $isAuditUser)?' disabled' : ''));
		$oForm -> addRule('kods', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('text', 'designation',  text::get('MAIN_DESIGNATION'), isset($mms['KMSD_OPERATIVAS_APZIM'])?$mms['KMSD_OPERATIVAS_APZIM']:'', 'tabindex=2 maxlength="250"'.(($isAuditUser)?' disabled' : '') );
        $oForm -> addElement('text', 'worktitle',  text::get('PRINT_WORK_TITLE'), isset($mms['KMSD_WORK_TITLE'])?$mms['KMSD_WORK_TITLE']:'', 'tabindex=3 maxlength="250"'.(($isAuditUser)?' disabled' : '') );

        //datums
        $oForm -> addElement('date', 'proces_date',  text::get('PROCESS_DATE'), isset($mms['KMSD_IZPILDES_DATUMS'])?$mms['KMSD_IZPILDES_DATUMS']:dtime::now(), 'tabindex=4 maxlength="10"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addRule('proces_date', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('proces_date', text::get('ERROR_INCORRECT_DATE'),'validatedate');
  
		$oForm -> addElement('text', 'requirement_code',  text::get('REQUIREMENT_CODE'), isset($mms['KMSD_NOSACIJUMA_KODS'])?$mms['KMSD_NOSACIJUMA_KODS']:'', 'tabindex=5 maxlength="10"' . (($mmsId || $isAuditUser)?' disabled' : ''));
		$oForm -> addRule('requirement_code', text::get('ERROR_NUMERIC_VALUE'), 'numeric');

		$oForm -> addElement('text', 'requirement',  text::get('REQUIREMENT_TITLE'), isset($mms['KMSD_NOSACIJUMS'])?$mms['KMSD_NOSACIJUMS']:'', 'tabindex=6 maxlength="250"'.(($mmsId || $isAuditUser)?' disabled' : '') );

        $oForm -> addElement('text', 'edAreaCode',  text::get('ED_AREA_CODE'), isset($mms['KMSD_KEDI_KODS'])?$mms['KMSD_KEDI_KODS']:'', 'tabindex=7 maxlength="5"' . (($isAuditUser)?' disabled' : ''));
		$oForm -> addRule('edAreaCode', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('edAreaCode', text::get('ERROR_ALPHANUMERIC_VALUE'), 'alphanumeric');
		
		$oForm -> addElement('checkbox', 'priority',  text::get('PRIORITY'), isset($mms['KMSD_PRIORITATE'])?$mms['KMSD_PRIORITATE']:0, ' tabindex=8 '.(($isAuditUser)?' disabled' : ''));
		$oForm -> addElement('checkbox', 'isEpla',  text::get('TRASE'), isset($mms['KMSD_IR_EPLA'])?$mms['KMSD_IR_EPLA']:0, ' tabindex=9 '.(($isAuditUser)?' disabled' : ''));
        
        $oForm -> addElement('text', 'toid',  text::get('TO_ID'), isset($mms['KMSD_TO_ID'])?$mms['KMSD_TO_ID']:'', ' tabindex=10  maxlength="6"'.(($isAuditUser)?' disabled' : ''));
		$oForm -> addRule('toid', text::get('ERROR_ALPHANUMERIC_VALUE'), 'alphanumeric');
		
		$oForm -> addElement('text', 'technic_object',  text::get('TECHNIC_OBJECT'), isset($mms['KMSD_TEH_OBJEKTS'])?$mms['KMSD_TEH_OBJEKTS']:'', 'tabindex=11 maxlength="50"'.(($isAuditUser)?' disabled' : '') );
		$oForm -> addElement('text', 'network_element',  text::get('NETWORK_ELEMENT'), isset($mms['KMSD_TIKLA_ELEMENTS'])?$mms['KMSD_TIKLA_ELEMENTS']:'', 'tabindex=12 maxlength="250"'.(($mmsId || $isAuditUser)?' disabled' : '') );

		$oForm -> addElement('text', 'network_element_code',  text::get('NETWORK_EL_CODE'), isset($mms['KMSD_TIKLA_ELEMENTA_KLASE'])?$mms['KMSD_TIKLA_ELEMENTA_KLASE']:'', 'tabindex=13 maxlength="150"'.(($mmsId || $isAuditUser)?' disabled' : '') );
		//$oForm -> addRule('network_element_code', text::get('ERROR_NUMERIC_VALUE'), 'numeric');

        $oForm -> addElement('text', 'quantity',  text::get('MMS_QUANTITY'), isset($mms['KMSD_DAUDZUMS'])?$mms['KMSD_DAUDZUMS']:'', ' tabindex=14  maxlength="10"'.(($isAuditUser)?' disabled' : ''));
		$oForm -> addRule('quantity', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('quantity', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);
		
		$oForm -> addElement('text', 'line_count',  text::get('MMS_LINE_COUNT'), isset($mms['KMSD_VADU_SKAITS'])?$mms['KMSD_VADU_SKAITS']:'', 'tabindex=15 maxlength="10"'.(($isAuditUser)?' disabled' : '') );
		$oForm -> addRule('line_count', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('line_count', text::get('ERROR_NUMERIC_VALUE'), 'numeric');
		
		$oForm -> addElement('text', 'mms_x',  text::get('MMS_X'), isset($mms['KMSD_X'])?$mms['KMSD_X']:'', ' tabindex=16  maxlength="20"'.(($mmsId || $isAuditUser)?' disabled' : ''));
		$oForm -> addRule('mms_x', text::get('ERROR_DOUBLE_VALUE'), 'double', 8);

		$oForm -> addElement('text', 'mms_y',  text::get('MMS_Y'), isset($mms['KMSD_Y'])?$mms['KMSD_Y']:'', ' tabindex=17  maxlength="20"'.(($mmsId || $isAuditUser)?' disabled' : ''));
		$oForm -> addRule('mms_y', text::get('ERROR_DOUBLE_VALUE'), 'double', 8);

        	$oForm -> addElement('kls', 'voltage',  text::get('SINGLE_VOLTAGE'), array('classifName'=>KL_VOLTAGE_BY_CODE,'value'=>isset($mms['KMSD_KSRG_KODS'])?$mms['KMSD_KSRG_KODS']:'','readonly'=>false), 'tabindex=18 maxlength="2000"'.(($isAuditUser)?' disabled':''));
		$oForm -> addRule('voltage', text::get('ERROR_REQUIRED_FIELD'), 'required');


		$oForm -> addElement('kls', 'object',  text::get('SINGLE_OBJECT'), array('classifName'=>KL_OBJECTS_BY_CODE,'value'=>isset($mms['KMSD_KOBJ_KODS'])?$mms['KMSD_KOBJ_KODS']:'','readonly'=>false), 'tabindex=19 maxlength="2000"'.(($isAuditUser)?' disabled':''));
		//$oForm -> addElement('kls', 'sourceOfFounds',  text::get('SINGLE_SOURCE_OF_FOUNDS'), array('classifName'=>KL_SOURCE_OF_FOUNDS_BY_CODE,'value'=>isset($mms['KMSD_KFNA_KODS'])?$mms['KMSD_KFNA_KODS']: '','readonly'=>false), 'tabindex=20 maxlength="2000"'.(($mmsId || $isAuditUser)?' disabled':''));

		//datums
        $oForm -> addElement('text', 'export_date',  text::get('EXPORT_DATE'), isset($mms['KMSD_EXPORT_DATUMS'])?$mms['KMSD_EXPORT_DATUMS']:dtime::now(), 'tabindex=21 maxlength="20" disabled');
		
		// importa dati
		$oForm -> addElement('text', 'created',  text::get('CREATED'), isset($mms['KMSD_CREATED'])?$mms['KMSD_CREATED']:dtime::now(), 'tabindex=21 maxlength="20" disabled');
		$oForm -> addElement('text', 'creator',  text::get('CREATOR'), isset($creator)?$creator:'', 'tabindex=21 maxlength="20" disabled');
		$oForm -> addElement('text', 'edited',  text::get('EDITED'), isset($mms['KMSD_EDITED'])?$mms['KMSD_EDITED']:dtime::now(), 'tabindex=21 maxlength="20" disabled');
		$oForm -> addElement('text', 'editor',  text::get('EDITOR'), isset($mms)?$editor:'', 'tabindex=21 maxlength="20" disabled');

        // xmlHttp link
  		$oLink=new urlQuery();
  		$oLink->addPrm(DONT_USE_GLB_TPL, 1);
  		$oLink->addPrm(FORM_ID, 'f.ktl.s.14');

        $oForm -> addElement('kls', 'worker',  text::get('SINGL_WORK_OWNER'), array('classifName'=>KL_WORK_OWNERS,'value'=>isset($mms['KMSD_IZPILDITAJA_KODS'])?$mms['KMSD_IZPILDITAJA_KODS']:'','readonly'=>false), 'tabindex=10 maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&trase=\'+((document.all[\'isEpla\'].checked)?1:0)+\'&worker=\'+this.value+\'\'))" '.(($isAuditUser)?' disabled' : ''));
        unset($oLink);

        $oForm -> addElement('select', 'contract',  text::get('KWOI_VV_NUMBER'), isset($mms['KMSD_VV_NUMURS'])?$mms['KMSD_VV_NUMURS']:0, 'tabindex=11 '.(($isAuditUser)?' disabled' : ''), '', '', $contract);
        

		// form buttons
        if($isAdmin || $isEdUser)
        {
    		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
    		if($isEdit) {
				$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'mmsId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
				$oForm -> addElement('submitImg', 'delete_row', text::get('DELETE_ROW'), 'img/btn90_delete_row.gif', 'width="90" height="20" onclick="if (!isEmptyField(\'mmsId\') && isDeleteWithMessage(\''.text::get('WARNING_DELETE_ROW').'\')) {setValue(\'action\',\''.OP_DELETE_ROW.'\');} else {return false;}"');
			}
    		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'mmsId\');parent.frame_1.unActiveRow();'));
            
            if ($isDelete)
            {
			  $oForm -> addElement('submitImg', 'delete_work', text::get('DELETE_WORK'), 'img/btn90_delete_work.gif', 'width="90" height="20" onclick="if (!isEmptyField(\'mmsId\') && isDeleteWithMessage(\''.text::get('WARNING_DELETE_ROW').'\')) {setValue(\'action\',\''.OP_DELETE.'\');} else {return false;}"');
            }
         	$oForm -> addElement('static', 'jsButtonsControl', '', '
    			<script>
    				function refreshButton(name)
    				{
    					if (!isEmptyField(name))
    					{
							document.all["save"].src="img/btn_saglabat.gif";
							document.all["delete_row"].src="img/btn90_delete_row.gif";
							document.all["delete_work"].src="img/btn90_delete_work.gif";

    					}
    					else
    					{
    						document.all["save"].src="img/btn_saglabat_disabled.gif";
							document.all["delete_row"].src="img/btn90_delete_row_disabled.gif";
							document.all["delete_work"].src="img/btn90_delete_work_disabled.gif";
    					}
    				}
    				refreshButton("mmsId");
    			</script>
    		');
        }
		// if operation
		if ($oForm -> isFormSubmitted())
		{
			$check = true;
			$r = false;
			$checkRequiredFields = false;
            // delete
            if ($oForm->getValue('action')== OP_DELETE && $oForm -> getValue('kods') )
            {
               $r = dbProc::deleteMMSWork($oForm->getValue('kods')) ;
			}			
			// delete row
            else if ($oForm->getValue('action')== OP_DELETE_ROW && $oForm -> getValue('kods') && is_numeric($oForm->getValue('mmsId')) )
            {
			   $r = dbProc::deleteMMSWorkRow($oForm->getValue('mmsId'),
												$oForm->getValue('kods'),
												$oForm->getValue('isEpla',0)
												) ;
			}			
            // save
			else if ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('mmsId'))))
			{
    			if ($oForm -> getValue('kods') && $oForm -> getValue('edAreaCode') )
    			{
    				$checkRequiredFields = true;
    			}
    			if ($checkRequiredFields)
    			{
					
					// if all is ok, do operation
					if($check)
					{
						$r=dbProc::saveMMSWork(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('mmsId'):false),
						$oForm->getValue('kods'),
						$oForm->getValue('designation'),
						$oForm->getValue('worktitle'),						
                        $oForm->getValue('proces_date'),
                        $oForm->getValue('requirement_code'),
						$oForm->getValue('requirement'),
						$oForm->getValue('edAreaCode'),
						$oForm->getValue('worker'),
						$oForm->getValue('contract'),
						$oForm->getValue('priority',0),
						$oForm->getValue('isEpla',0),
						$oForm->getValue('toid'),
                        $oForm->getValue('technic_object'),
						$oForm->getValue('network_element'),
                        $oForm->getValue('network_element_code'),
                        $oForm->getValue('quantity'),
                        $oForm->getValue('line_count'),
                        $oForm->getValue('mms_x'),
                        $oForm->getValue('mms_y'),
                        $oForm->getValue('voltage'),
                        $oForm->getValue('object'),
                        $oForm->getValue('sourceOfFounds'),
						$oForm->getValue('export_date'),
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
    			$oLink->addPrm(FORM_ID, 'f.ktl.s.14');
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
    					$oLink->addPrm('successMessage', text::get('RECORD_WAS_DELETED'));
    					break;
    			}
    			//RequestHandler::makeRedirect($oLink->getQuery());
    		}
		}

       	$oForm -> makeHtml();
		include('f.ktl.s.14.2.tpl');
	}
    // INSERT INTO `FMK_MESSAGES` (`id`,`code`,`text`) VALUES (NULL, 'RECORD_WAS_DELETED', 'Informācija ir   veiksmīgi izdzēsta!');
     // INSERT INTO `FMK_MESSAGES` (`id`,`code`,`text`) VALUES (NULL, 'WARNING_DELETE_ROW', 'Vai tiešām vēlaties `dzēst` ierakstu?');
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
        $title = text::toUpper(text::get('SINGLE_MMS'));
        // get search column list
        $columns=dbProc::getKlklName(KL_MMS_WORKS);
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;

        // default sort column
        $defaultColumn = dbProc::getKlklDefaultColumn(KL_MMS_WORKS);

        // URL to search Zinojums by number.
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.ktl.s.14');
    	$oLink->addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		$amount=dbProc::getMMSWorkCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.ktl.s.14');
		$oLink->addPrm('editMode', 1);

		// gel list of users
		$res = dbProc::getMMSWorkList( false,
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
				$oLink->addPrm('mmsId', $row['KMSD_ID']);
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
