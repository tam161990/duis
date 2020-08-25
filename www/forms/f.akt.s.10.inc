<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isProjector = dbProc::isExistsUserRoleWithProject($userId) ;
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;
// act ID
$actId  = reqVar::get('actId');
$trase =  reqVar::get('isTrase');

// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isSystemUser || $isProjector)
{
	
    if($actId !== false )
    {
	   // get excel	  
		$excelInfo=dbProc::getExcelInfo($actId);
		

		// get file link
		$oLinkFile=new urlQuery();
		if($isProject == 1){
			$oLinkFile->addPrm(IS_GET_PEXCEL_FILE_VARIABLE, 1);
		} else {
			$oLinkFile->addPrm(IS_GET_EXCEL_FILE_VARIABLE, 1);
		}
		if (is_array($excelInfo))
		{
			foreach ($excelInfo as $i=>$row)
			{
				$oLinkFile->addPrm(GET_FILE_VARIABLE, $row['EFLS_ID']);
				$excelInfo[$i]['getFileURL']=$oLinkFile ->getQuery();
			}
		}
		unset($oLinkFile);
	
       // get file info by message ID
	   $fileInfo=dbProc::getFilesInfo($actId, ($trase) ? FILE_ESTIMATE : FILE_EXPORT);

	  // get file lin0
	  $oLinkFile=new urlQuery();
	  $oLinkFile->addPrm(IS_GET_FILE_VARIABLE, 1);
	  if (is_array($fileInfo))
	  {
	  	foreach ($fileInfo as $i=>$row)
	  	{
      		$oLinkFile->addPrm(GET_FILE_VARIABLE, $row['RFLS_ID']);
	  		$fileInfo[$i]['getFileURL']=$oLinkFile ->getQuery();
            if($isEditor && $isProject == 0) break;
	   	}
	  }
	  unset($oLinkFile);

      include('f.akt.s.10.tpl');
    }
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>