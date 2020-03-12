<?

$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isEdUser = dbProc::isUserInRole($userId, ROLE_ED_USER);

$oLink=new urlQuery();
$oLink->addPrm(FORM_ID, 'f.gps.s.0');
$oForm = new Form('frmMain','post',$oLink->getQuery());
unset($oLink);

if($isEdUser || $isAdmin || $isEditor)
{
  	#################
	## Files block##
	#################

	// if delete file button was pressed and is set deleted file ID => delete file
	if(reqVar::get('deleteFile'))
	{
		if(files::deleteGpsFile(reqVar::get('deleteFile')) === false)
		{
			$oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
		}
		else
		{
			$oForm->addSuccess(text::get('FILE_WAS_DELETED'));
		}
	}

	// get file info by message ID
	$fileInfo=dbProc::getGpsFilesInfo();

	// delete file link
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.gps.s.0');

	// get file link
	$oLinkFile=new urlQuery();
	$oLinkFile->addPrm(IS_GET_GPS_FILE_VARIABLE, 1);


	if (is_array($fileInfo))
	{
		foreach ($fileInfo as $i=>$row)
		{

			$oLinkFile->addPrm(GET_GPS_FILE_VARIABLE, $row['GFLS_ID']);

            $fileInfo[$i]['GFLS_REGION']  = (($fileInfo[$i]['GFLS_REGION'] == '-1')? "" : $fileInfo[$i]['GFLS_REGION']);
			$fileInfo[$i]['getFileURL']=$oLinkFile ->getQuery();
			 // anly project admin and file owner has access to delete file
			if($isEdUser || $isAdmin)
			{
				$oLink->addPrm('deleteFile', $row['GFLS_ID']);
				$fileInfo[$i]['deleteURL']=$oLink ->getQuery();
			}
			else
			{
				$fileInfo[$i]['deleteURL'] = false;
			}
		}
	}
	unset($oLink);
	unset($oLinkFile);

   // get ED region list
   $rgionOptions = "<option  value='-1'>".text::get('ALL')."</option>";

     $res=dbProc::getEDRegionList();
     if (is_array($res))
     {
     	foreach ($res as $row)
     	{

     		$rgionOptions .= "<option  value='".$row['nosaukums']."'>".$row['nosaukums']."</option>";

     	}
        $rgionOptions .= "<option  value='RPR'>RPR</option>";  
     }
   unset($res);

    $oForm -> addElement('hidden', 'fileFieldId', null, ($oForm->getValue('fileFieldId')?$oForm->getValue('fileFieldId'):0));


    // form buttons
    $oForm -> addElement('submitImg', 'addFile', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20" onClick="addFileBlock(); return false;"');
  	$oForm -> addElement('submitImg', 'add', text::get('ADD'), 'img/btn_pievienot.gif', 'width="70" height="20"');

    $fileRowsCount = 0;
  	// if operation
    if ($oForm -> isFormSubmitted())
    {
        // save files
        $fileSaved = true;
        if($oForm->getValue('fileFieldId') > 0)
        {
        	$savedFilesArray = array();
        	for($i = $oForm->getValue('fileFieldId'); $i>= 1; $i--)
        	{
        		if(files::isUploadFile('fileName_'.$i))
        		{
        		    $fileId =  files::saveGpsFile('fileName_'.$i, $oForm->getValue('edRegion_'.$i));
        			$savedFilesArray[$i]= $fileId;
        			if($savedFilesArray[$i] != false)
        			{
        				$fileDescription[$i] = $oForm->getValue('edRegion_'.$i);
        			}
        			else
        			{
        				$fileDescription[$i] = "-1";
        				$fileSaved = false;
        			}
        		}
        	}
        	if($fileSaved)
        	{
        		$fileRowsCount = count($savedFilesArray);
        	}
        	else
        	{
        		foreach ($savedFilesArray as $value)
        		{
        			($value != false)?files::deleteGpsFile($value):'';
        		}
        	}
        }
        if(!$fileSaved)
    	{
    		// show error and delete all previouse inserts
    		$oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
    	}
    	else
    	{

    		$oLink=new urlQuery();
    		$oLink->addPrm(FORM_ID, 'f.gps.s.0');
    	   	RequestHandler::makeRedirect($oLink->getQuery());
    	}
    }

    $oForm -> makeHtml();
    include('f.gps.s.0.tpl');
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>