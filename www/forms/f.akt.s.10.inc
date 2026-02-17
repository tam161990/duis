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
       // get file info by message ID
	  $fileInfo=dbProc::getAllFilesInfo($actId, ($trase) ? FILE_ESTIMATE : FILE_EXPORT);
	  //print_r( $fileInfo);

	  if (is_array($fileInfo))
	  {
	  	foreach ($fileInfo as $i=>$row)
	  	{
			// get file lin0
			$oLinkFile=new urlQuery();

			if($row['RFLS_META_INFO'] == EXPORT_FILE_TYPE) {
				$oLinkFile->addPrm(IS_GET_FILE_VARIABLE, 1);
				$fileInfo[$i]['ico'] = 'ico_pdf.gif'; 
			}

			if($row['RFLS_META_INFO'] == EXCEL_FILE_MIMETYPE) {
				if($isProject == 1){
					$oLinkFile->addPrm(IS_GET_PEXCEL_FILE_VARIABLE, 1);
				} else {
					$oLinkFile->addPrm(IS_GET_EXCEL_FILE_VARIABLE, 1);
				}
				$oLinkFile->addPrm(GET_EXEL_FILE_VARIABLE, $row['RFLS_ID']);				
				$fileInfo[$i]['ico'] = 'ico_excel.gif'; 
			}

			if($row['RFLS_META_INFO'] == XML_FILE_MIMETYPE) {
				$oLinkFile->addPrm(IS_GET_XML_FILE_VARIABLE, 1);	
				$fileInfo[$i]['ico'] = 'ico_xml.png'; 			
			}

			if($row['RFLS_META_INFO'] == JSON_FILE_MIMETYPE) {
				$oLinkFile->addPrm(IS_GET_JSON_FILE_VARIABLE, 1);	
				$fileInfo[$i]['ico'] = 'ico_json.png'; 	
				
				if($isProject == 1 && isset($row['DESCRIPTION']))	{
				   
					$description = explode('|', $row['DESCRIPTION']);
					if(is_array($description)){
						$fileInfo[$i]['status'] = $description[0];
						
						if(count($description)>1 && !empty($description[1])){
							$fileInfo[$i]['error_msg'] = str_replace(array("\"", "'"), "`", str_replace(array("\r\n", "\n", "\r"),"<br>",$description[1]));
							
						}
						
						if(count($description)>2){
							$fileInfo[$i]['project_no'] = $description[2];
						}
					}
				}
			}

			$oLinkFile->addPrm(GET_FILE_VARIABLE, $row['RFLS_ID']);
	  		$fileInfo[$i]['getFileURL']=$oLinkFile ->getQuery();
			/*if($isEditor && $isProject == 0) {
				unset($oLinkFile);
				break;
			}*/
			unset($oLinkFile);
	   	}
	  }
	  

      include('f.akt.s.10.tpl');
    }
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>