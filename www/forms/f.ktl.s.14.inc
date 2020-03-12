<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAuditUser = dbProc::isUserInRole($userId, ROLE_AUDIT_USER);
$isEdUser = dbProc::isUserInRole($userId, ROLE_ED_USER);
$isAdmin = userAuthorization::isAdmin();
$trase =  reqVar::get('isTrase');
if($trase != 1) $trase = 0;

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
                $res=dbProc::getDuContractNo($mms['KMSD_KWOI_KODS'], -1);

                 if (is_array($res))
                 {
                 	foreach ($res as $row)
                 	{
                 	  $contract[$row['KCNT_VV_NUMBER']]=$row['KCNT_VV_NUMBER'];
                 	}
                 }
                 unset($res);
			}
        }

        $isDelete = false;
        if(isset($mms['KMSD_IR_PABEIGTS']) && $mms['KMSD_IR_PABEIGTS'] == 0)
        {
           $isDelete = true;
        }

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'mmsId', null, isset($mms['KMSD_ID'])? $mms['KMSD_ID']:'');

        $oForm -> addElement('text', 'kods',  text::get('CODE'), isset($mms['KMSD_KODS'])?$mms['KMSD_KODS']:'', 'tabindex=1 maxlength="150"' . (($mmsId || $isAuditUser)?' disabled' : ''));
		$oForm -> addRule('kods', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('checkbox', 'isFinished',  text::get('MMS_WORK_FINISHED'), isset($mms['KMSD_IR_PABEIGTS'])?$mms['KMSD_IR_PABEIGTS']:0, ' tabindex=3 '.(($isAuditUser)?' disabled' : ''));

        $oForm -> addElement('text', 'edAreaCode',  text::get('ED_AREA_CODE'), isset($mms['KMSD_KEDI_KODS'])?$mms['KMSD_KEDI_KODS']:'', 'tabindex=2 maxlength="5"' . (($isAuditUser)?' disabled' : ''));
		$oForm -> addRule('edAreaCode', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('edAreaCode', text::get('ERROR_ALPHANUMERIC_VALUE'), 'alphanumeric');

        $oForm -> addElement('text', 'workTime',  ((isset($mms['KMSD_TRASE']) && $mms['KMSD_TRASE'] == 1) ? text::get('MMS_KOKNESE') : text::get('MAN_HOUR_STANDART_TOTAL')), isset($mms['KMSD_CILVEKSTUNDAS'])?$mms['KMSD_CILVEKSTUNDAS']:'', ' tabindex=4  maxlength="8"'.(($isAuditUser)?' disabled' : ''));
        //$oForm -> addRule('workTime', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('workTime', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);
        // check Price field
        $oForm->addElement('hidden','minTime','','0.00');
        $oForm->addElement('hidden','maxTime','','100000.00');
        $v1=&$oForm->createValidation('timeValidation', array('workTime'), 'ifonefilled');
        // ja cena ir definēta un > 100000
        $r1=&$oForm->createRule(array('workTime', 'minTime'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','>=');
        $r2=&$oForm->createRule(array('workTime', 'maxTime'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','<');
        $oForm->addRule(array($r1, $r2), 'groupRuleTime', 'group', $v1);

        $oForm -> addElement('text', 'price',  ((isset($mms['KMSD_TRASE']) && $mms['KMSD_TRASE'] == 1) ? text::get('MMS_PLAN_PAYMENT') : text::get('MATERIAL_PRICE')), isset($mms['KMSD_MATR_IZMAKSAS'])?$mms['KMSD_MATR_IZMAKSAS']:'', ' tabindex=5  maxlength="8"'.(($isAuditUser)?' disabled' : ''));
        //$oForm -> addRule('price', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('price', text::get('ERROR_DOUBLE_VALUE'), 'double', 2);
        // check Price field
        $oForm->addElement('hidden','minPrice','','0.00');
        $oForm->addElement('hidden','maxPrice','','100000.00');
        $v2=&$oForm->createValidation('priceValidation', array('price'), 'ifonefilled');
        // ja cena ir definēta un > 100000
        $r1=&$oForm->createRule(array('price', 'minPrice'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','>=');
        $r2=&$oForm->createRule(array('price', 'maxPrice'), text::get('ERROR_AMOUNT_VALUE_100000'), 'comparedouble','<');
        $oForm->addRule(array($r1, $r2), 'groupRulePrice', 'group', $v2);

        $oForm -> addElement('checkbox', 'priority',  text::get('PRIORITY'), isset($mms['KMSD_PRIORITATE'])?$mms['KMSD_PRIORITATE']:0, ' tabindex=6 '.(($isAuditUser)?' disabled' : ''));

        $oForm -> addElement('select', 'year',  text::get('YEAR'), isset($mms['KMSD_GADS'])?$mms['KMSD_GADS']:dtime::getCurrentYear(), 'tabindex=7 style="width:50;"'.(($isAuditUser)?' disabled' : ''), '', '', dtime::getYearArray());
        $oForm -> addRule('year', text::get('ERROR_REQUIRED_FIELD'), 'required');

        $oForm -> addElement('select', 'quarter',  text::get('QUARTER'), isset($mms['KMSD_CETUKSNIS'])?$mms['KMSD_CETUKSNIS']:1, 'tabindex=8 style="width:50;"'.(($isAuditUser)?' disabled' : ''), '', '', array('1'=>1,'2'=>2,'3'=>3,'4'=>4));
        $oForm -> addRule('quarter', text::get('ERROR_REQUIRED_FIELD'), 'required');

         $oForm -> addElement('checkbox', 'trase',  text::get('TRASE'), isset($mms['KMSD_TRASE'])?$mms['KMSD_TRASE']:0, ' tabindex=9 '.(($isAuditUser)?' disabled' : ''));


        // xmlHttp link
  		$oLink=new urlQuery();
  		$oLink->addPrm(DONT_USE_GLB_TPL, 1);
  		$oLink->addPrm(FORM_ID, 'f.ktl.s.14');

        $oForm -> addElement('kls', 'worker',  text::get('SINGL_WORK_OWNER'), array('classifName'=>KL_WORK_OWNERS,'value'=>isset($mms['KMSD_KWOI_KODS'])?$mms['KMSD_KWOI_KODS']:'','readonly'=>false), 'tabindex=10 maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&trase=\'+((document.all[\'trase\'].checked)?1:0)+\'&worker=\'+this.value+\'\'))" '.(($isAuditUser)?' disabled' : ''));
        unset($oLink);


        $oForm -> addElement('select', 'contract',  text::get('KWOI_VV_NUMBER'), isset($mms['KMSD_VV_NUMBER'])?$mms['KMSD_VV_NUMBER']:0, 'tabindex=11 '.(($isAuditUser)?' disabled' : ''), '', '', $contract);
                $oForm -> addElement('checkbox', 'finalize',  text::get('NOSLEGUMA_AKTS'), isset($mms['KMSD_NOSLEGUMA_AKTS'])?$mms['KMSD_NOSLEGUMA_AKTS']:0, ' tabindex=12 '.(($isAuditUser)?' disabled' : ''));


        $oForm -> addElement('uploadfile', 'fileName', text::get('FILE'), '','tabindex=11 class="flex" disabled');
        //$oForm -> addRule('fileName', text::get('ERROR_REQUIRED_FIELD'), 'required');
       $oForm -> addElement('text', 'designation',  text::get('MAIN_DESIGNATION'), isset($mms['KMSD_OPERATIVAS_APZIM'])?$mms['KMSD_OPERATIVAS_APZIM']:'', 'tabindex=15 maxlength="250"'.(($isAuditUser)?' disabled' : '') );
       $oForm -> addElement('text', 'worktitle',  text::get('PRINT_WORK_TITLE'), isset($mms['KMSD_WORK_TITLE'])?$mms['KMSD_WORK_TITLE']:'', 'tabindex=16 maxlength="250"'.(($isAuditUser)?' disabled' : '') );

        $oForm -> addElement('text', 'toidn',  text::get('TO_IDN'), isset($mms['KMSD_TO_IDN'])?$mms['KMSD_TO_IDN']:'0', ' tabindex=13  maxlength="12"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addRule('toidn', text::get('ERROR_NUMERIC_VALUE'), 'numeric');
        $oForm -> addElement('text', 'toid',  text::get('TO_ID'), isset($mms['KMSD_TO_ID'])?$mms['KMSD_TO_ID']:'', ' tabindex=14  maxlength="6"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addRule('toid', text::get('ERROR_ALPHANUMERIC_VALUE'), 'alphanumeric');

        // Z
        $oForm -> addElement('text', '1z',  '1Z', isset($mms['KMSD_1Z'])?$mms['KMSD_1Z']:'', ' style="width:55;" tabindex=12  maxlength="15"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '2z',  '2Z', isset($mms['KMSD_2Z'])?$mms['KMSD_2Z']:'', ' style="width:55;" tabindex=13  maxlength="16"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '3z',  '3Z', isset($mms['KMSD_3Z'])?$mms['KMSD_3Z']:'', ' style="width:55;" tabindex=14  maxlength="17"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '4z',  '4Z', isset($mms['KMSD_4Z'])?$mms['KMSD_4Z']:'', ' style="width:55;" tabindex=15 maxlength="18"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '5z',  '5Z', isset($mms['KMSD_5Z'])?$mms['KMSD_5Z']:'', ' style="width:55;" tabindex=16 maxlength="19"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '6z',  '6Z', isset($mms['KMSD_6Z'])?$mms['KMSD_6Z']:'', ' style="width:55;" tabindex=17 maxlength="20"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '7z',  '7Z', isset($mms['KMSD_7Z'])?$mms['KMSD_7Z']:'', ' style="width:55;" tabindex=18 maxlength="21"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '8z',  '8Z', isset($mms['KMSD_8Z'])?$mms['KMSD_8Z']:'', ' style="width:55;" tabindex=19 maxlength="22"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '9z',  '9Z', isset($mms['KMSD_9Z'])?$mms['KMSD_9Z']:'', ' style="width:55;" tabindex=20 maxlength="23"'.(($isAuditUser)?' disabled' : ''));

        // V
        $oForm -> addElement('text', '1v',  '1V', isset($mms['KMSD_1V'])?$mms['KMSD_1V']:'', ' style="width:55;" tabindex=21 maxlength="24"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '2v',  '2V', isset($mms['KMSD_2V'])?$mms['KMSD_2V']:'', ' style="width:55;" tabindex=22 maxlength="25"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '3v',  '3V', isset($mms['KMSD_3V'])?$mms['KMSD_3V']:'', ' style="width:55;" tabindex=23 maxlength="26"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '4v',  '4V', isset($mms['KMSD_4V'])?$mms['KMSD_4V']:'', ' style="width:55;" tabindex=24 maxlength="27"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '5v',  '5V', isset($mms['KMSD_5V'])?$mms['KMSD_5V']:'', ' style="width:55;" tabindex=25 maxlength="28"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '6v',  '6V', isset($mms['KMSD_6V'])?$mms['KMSD_6V']:'', ' style="width:55;" tabindex=26 maxlength="29"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '7v',  '7V', isset($mms['KMSD_7V'])?$mms['KMSD_7V']:'', ' style="width:55;" tabindex=27 maxlength="30"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '8v',  '8V', isset($mms['KMSD_8V'])?$mms['KMSD_8V']:'', ' style="width:55;" tabindex=28 maxlength="31"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '9v',  '9V', isset($mms['KMSD_9V'])?$mms['KMSD_9V']:'', ' style="width:55;" tabindex=29 maxlength="32"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '10v',  '10V', isset($mms['KMSD_10V'])?$mms['KMSD_10V']:'', ' style="width:55;" tabindex=30 maxlength="33"'.(($isAuditUser)?' disabled' : ''));
        $oForm -> addElement('text', '11v',  '11V', isset($mms['KMSD_11V'])?$mms['KMSD_11V']:'', ' style="width:55;" tabindex=31 maxlength="34"'.(($isAuditUser)?' disabled' : ''));


		// form buttons
        if($isAdmin || $isEdUser)
        {
    		$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onclick="setValue(\'action\',\''.OP_INSERT.'\');"');
    		$oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'mmsId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
    		$oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshButton(\'mmsId\');parent.frame_1.unActiveRow();'));

            if ($isDelete)
            {
              $oForm -> addElement('submitImg', 'delete', text::get('DELETE'), 'img/btn_dzest.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'mmsId\') && isDeleteWithMessage(\''.text::get('WARNING_DELETE_ROW').'\')) {setValue(\'action\',\''.OP_DELETE.'\');} else {return false;}"');
            }
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
            // delete favorits
            if ($oForm->getValue('action')== OP_DELETE )
            {
               $r = dbProc::deleteMMSWork($oForm->getValue('mmsId')) ;
            }
            // save
			elseif ($oForm->getValue('action')==OP_INSERT || ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('mmsId'))))
			{
    			if ($oForm -> getValue('kods') && $oForm -> getValue('edAreaCode') &&
                    ($oForm -> getValue('price', 0) >= 0) && ($oForm -> getValue('workTime', 0) >= 0) &&
                    $oForm -> getValue('year') && $oForm -> getValue('quarter') )
    			{
    				$checkRequiredFields = true;
    			}
    			if ($checkRequiredFields)
    			{

					// chech that ED area with same region and code not set
					if (dbProc::mmsWithCodeExists(    $oForm->getValue('kods'),
                                                            ($oForm->getValue('action')==OP_UPDATE)?$oForm->getValue('mmsId'):false)
                                                            )
					{
						$oForm->addError(text::get('ERROR_EXISTS_MMS_CODE'));
						$check = false;
					}

					// if all is ok, do operation
					if($check)
					{
						$r=dbProc::saveMMSWork(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('mmsId'):false),
						$oForm->getValue('kods'),
                        $oForm->getValue('workTime',0),
                        $oForm->getValue('price',0),
                        $oForm->getValue('quarter'),
                        $oForm->getValue('year'),
                        $oForm->getValue('priority',0),
                        $oForm->getValue('edAreaCode'),
			$oForm->getValue('isFinished',0),
			$oForm->getValue('finalize',0),      
                        $oForm->getValue('worker'),
                        $oForm->getValue('contract'),
                        $oForm->getValue('trase',0),
                        true,
                        $oForm->getValue('designation'),
	        	        $oForm->getValue('worktitle'),
                        $oForm->getValue('toidn'),
                        $oForm->getValue('toid'),
                        $oForm->getValue('1z'),
                        $oForm->getValue('2z'),
                        $oForm->getValue('3z'),
                        $oForm->getValue('4z'),
                        $oForm->getValue('5z'),
                        $oForm->getValue('6z'),
                        $oForm->getValue('7z'),
                        $oForm->getValue('8z'),
                        $oForm->getValue('9z'),
                        $oForm->getValue('1v'),
                        $oForm->getValue('2v'),
                        $oForm->getValue('3v'),
                        $oForm->getValue('4v'),
                        $oForm->getValue('5v'),
                        $oForm->getValue('6v'),
                        $oForm->getValue('7v'),
                        $oForm->getValue('8v'),
                        $oForm->getValue('9v'),
                        $oForm->getValue('10v'),
                        $oForm->getValue('11v')
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
    			RequestHandler::makeRedirect($oLink->getQuery());
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
