<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;
// act ID
$actId  = reqVar::get('actId');


// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
    if($actId !== false )
    {
       // get file info by message ID
	   $fileInfo=dbProc::getFilesInfo($actId, FILE_ESTIMATE);

	  // get file link
	  $oLinkFile=new urlQuery();
	  $oLinkFile->addPrm(IS_GET_FILE_VARIABLE, 1);
	  if (is_array($fileInfo))
	  {
	  	foreach ($fileInfo as $i=>$row)
	  	{
      		$oLinkFile->addPrm(GET_FILE_VARIABLE, $row['RFLS_ID']);
	  		$fileInfo[$i]['getFileURL']=$oLinkFile ->getQuery();
            if($isEditor) break;
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