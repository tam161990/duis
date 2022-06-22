<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isEdUser = (dbProc::isUserInRole($userId, ROLE_ED_USER) || dbProc::isUserInRole($userId, ROLE_AUDIT_USER));
// by default 10 contract numbers for one DU
define('CONTRACT_MAX_COUNT', 30);
// error end warning messages for delete
$errorMsgDelete = text::get('ERROR_CONTRACT_IS_USED');
$warningMsgDelete = text::get('WARNING_DELETE_CONTRACT');

$workerCode = reqVar::get('workerCode');
$workerId = reqVar::get('workerId');

//link for frame2
$oLink2=new urlQuery();
$oLink2->addPrm(FORM_ID, 'f.ktl.s.8');
$oLink2->addPrm('editMode', 1);
$oLink2->addPrm('workerId', $workerId);

// Main form with XMLHTTP method load this code:
// used for delete record from DB
if (reqVar::get('xmlHttp') == 1)
{
	if(reqVar::get('opType') == OP_DELETE)
	{

      	if (reqVar::get('itemId')!='')
    	{
    		// if there is reletions with kls an another object => return true
    		if ($res=dbProc::isContractRelations(reqVar::get('itemId')))
    		{
    			?>
    			alert('<?=$errorMsgDelete;?>');
    			<?
    		}
    		else
    		{
    			dbProc::deleteContractNo(reqVar::get('itemId'));
    			?>
                    removeErrSpans();
		            deleteBlock(this,'empty_node',Array('contractId_','isTrase_','contractNo_'));
    			<?

    		}
    	}
    	else
    	{
    		?>
               removeErrSpans();
		       deleteBlock(this,'empty_node',Array('contractId_','isTrase_','contractNo_'));
    		<?

    	}

	}
	exit();
}



if ((userAuthorization::isAdmin() || $isEdUser ) && $workerCode != false)
{


    $oLink=new urlQuery();
    $oLink->addPrm(FORM_ID, 'f.ktl.s.15');
    $oForm = new Form('frmMain','post',$oLink->getQuery());
    unset($oLink);

    // if operation is success, show success message and redirect top frame
    if (reqVar::get('successMessage'))
    {
    	$oForm->addSuccess(reqVar::get('successMessage'));
    	$oForm->addElement('static','jsRefresh2','','<script>window.opener.refreshFrame(1); window.opener.reloadFrame(2, "'.$oLink2 ->getQuery().'");</script>');
    }

    // xmlHttp link for delete row from search result
    $oxmlHttpLinkD = new urlQuery;
    $oxmlHttpLinkD -> addPrm(FORM_ID, 'f.ktl.s.15');
    $oxmlHttpLinkD -> addPrm('xmlHttp', '1');
    $oxmlHttpLinkD->addPrm(DONT_USE_GLB_TPL, '1');
    $oxmlHttpLinkD -> addPrm('opType', OP_DELETE);

    // if success message is set
  	if (reqVar::get('errorMessage'))
  	{
  		// add message to the form
  		$oForm->addError(reqVar::get('errorMessage'));
  	}

    // get list of contract
    $contractArray = dbProc:: getDuContractNo( $workerCode );

    // list of all records
    // if array with query records not empty
    if (is_array($contractArray) && count($contractArray)>0)
    {

    	// inicialize array for data
    	$data=array();
    	// counter
    	$i=0;
    	// filling $daa array with values from Array
    	foreach ($contractArray as $row)
    	{
    		$data[$i]['ID']=$row['KCNT_ID'];
    		$data[$i]['CONTRACT']=$row['KCNT_VV_NUMBER'];
    		$data[$i]['TRASE']=$row['KCNT_IR_TRASE'];
            $data[$i]['ED'] = $row['KONT_KEDI_KODS']  ;
			$data[$i]['ACTIVE'] = $row['KCNT_IR_AKTIVS']  ;
			$data[$i]['SIGNATORY'] = $row['KCNT_SIGNATORY']  ;
    		// increment counter
    		$i++;
    	}
    }
    else
    {
    	// if there is no records in DB, show error massage
    	$oForm->addError(text::get('ERROR_NO_RECORDS_FOUND'));
    }

    // if array data not empty
    if(isset($data) && is_array($data))
    {
    	// pievienojam tuksas vertibas massivaa sakumaa
    	while($i< CONTRACT_MAX_COUNT)
    	{
    		array_unshift($data,false);
    		$i++;
    	}
    }

    // add CONTRACT_MAX_COUNT rows to the form
    // first rows fields are emty and hidden
    // latest rows fields are filed by data values
    for ($i=0;$i< CONTRACT_MAX_COUNT;$i++)
    {


    	$oForm -> addElement('hidden', 'contractId_'.$i, '', isset($data[$i]['ID'])?$data[$i]['ID']:'' );

    	// trase
    	$oForm -> addElement('checkbox', 'isTrase_'.$i,  '',  isset($data[$i]['TRASE'])?$data[$i]['TRASE']:'0', ''.(($isEdUser)?' disabled' : ''));

        // is active
    	$oForm -> addElement('checkbox', 'isActive_'.$i,  '',  isset($data[$i]['ACTIVE'])?$data[$i]['ACTIVE']:'0', ''.(($isEdUser)?' disabled' : ''));

    	// contract no
    	$oForm -> addElement('text', 'contractNo_'.$i, '', isset($data[$i]['CONTRACT'])?$data[$i]['CONTRACT']:'', 'maxlength="20"  '.(($isEdUser)?' disabled' : ''));
	   //$oForm -> addRule('contractNo_'.$i, text::get('ERROR_REQUIRED_FIELD'), 'requiredext');
	   
	   // parakstitajs
	   $oForm -> addElement('text', 'signatory_'.$i, '', isset($data[$i]['SIGNATORY'])?$data[$i]['SIGNATORY']:'', 'maxlength="20"  '.(($isEdUser)?' disabled' : ''));

        $oForm -> addElement('kls', 'edArea_'.$i,  '', array('classifName'=>KL_ED_AREA_CODE,'value'=>isset($data[$i]['ED'])?$data[$i]['ED']:'','readonly'=>false), 'tabindex=13 maxlength="2000" '.(($isEdUser)?' disabled' : ''));
       // $oForm -> addRule('edArea_'.$i, text::get('ERROR_REQUIRED_FIELD'), 'requiredext');
    }
    $oForm -> addElement('hidden', 'workerCode', '', $workerCode );
    $oForm -> addElement('hidden', 'workerId', '', $workerId);

    // bottom buttons
    if(!$isEdUser)
    {
        $oForm -> addElement('submit', 'save', '', text::get('SAVE'), 'class="btn70" ');
    }

    $oForm -> addElement('button', 'close', '', text::get('CLOSE'), 'class="btn70" onclick="javascript:window.close();return false;"; ');

    // if form submitted
    if ($oForm -> isFormSubmitted())
    {
    	$isValis = true;
    	// validations
    	// loop form rows
    	for ($i=0;$i<CONTRACT_MAX_COUNT;$i++)
    	{
    		// get trase value
    		$oTrase = $oForm->getValue('isTrase_'.$i, 0);
    		// get title value
    		$oContractNo = $oForm->getValue('contractNo_'.$i);
            $oEd = $oForm->getValue('edArea_'.$i);
             
    		// if region & title value not empty
    		if(!empty($oContractNo) && !empty($oEd) )
    		{
    			// FOR INSERT
			if($oForm->getValue('contractId_'.$i) == '')
			{
    				// check that title is unique
    				if(dbProc::isEqualContract($oContractNo, $oEd, $oTrase))
    				{
    					// edd error message to incorrect element
    					$oForm->addErrorPerElem('contractNo_'.$i, text::get('ERROR_CONTRACT_EXIST'));
    					$isValis = false;
    				}
			}
    		}
    	}
    	// if validation is OK
    	if($isValis)
    	{
    		// inicial value for error message
    		$errorMsg = '';
    		// save info in DB
    		for ($i=0;$i<CONTRACT_MAX_COUNT;$i++)
    		{
    			// get ID of each record from hidden field
    			$id=$oForm->getValue('contractId_'.$i);
                // get region value
    		    $oTrase = $oForm->getValue('isTrase_'.$i, 0);
    		    // get title value
    		    $oContractNo = $oForm->getValue('contractNo_'.$i);
                $oEd = $oForm->getValue('edArea_'.$i);
				$oActive = $oForm->getValue('isActive_'.$i, 0);
				$oSignatory = $oForm->getValue('signatory_'.$i);

    			// if region & title value not empty
    			if(!empty($oContractNo) ) {

    				// write to the DB
    				$r=dbProc::saveContractNo($workerCode, $oTrase, $oContractNo, $oEd, $id, $oActive, $oSignatory);

    				if($r === false)
    				{
    					// if operation is not success, add info about error to Error Message
    					$errorMsg .= text::get('ERROR_IN_DB_QUERY').(dbProc::getError()).'<br>';
    				}
    				else
    				{
    					// if operation is success, update hidden field with calendar ID
    					$oForm -> setNewValue('contractId_'.$i, $id);
    				}
    			}
    		}


            /*$oRedirectLink=new urlQuery();
            $oRedirectLink->addPrm(FORM_ID, 'f.ktl.s.8');
            $oRedirectLink->addPrm('editMode', 1 );
            $oRedirectLink->addPrm('workerCode', $workerCode);

            RequestHandler::makeParentReplace($oRedirectLink->getQuery());
            unset($oRedirectLink);*/

    		// link for redirect form
    		$oLink = new urlQuery;
    		$oLink -> addPrm(FORM_ID, 'f.ktl.s.15');
    		$oLink-> addPrm('errorMessage', $errorMsg);
			$oLink-> addPrm('workerCode', $workerCode);
			$oLink-> addPrm('workerId', $workerId);
			$oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));

    		// if all write operations was success, redirect form
    		RequestHandler::makeRedirect($oLink->getQuery());
    	}
    }


    //Formas atteeloshana
    $oForm -> makeHtml();
    include('f.ktl.s.15.tpl');
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>