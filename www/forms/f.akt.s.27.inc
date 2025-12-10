<?
// Created by 
$userId = userAuthorization::getUserId();
$isAdmin = userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isProjector = dbProc::isExistsUserRoleWithProject($userId);
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;

// act ID
$actId = reqVar::get('actId');

// Only system user or administrator has access!
if ($isAdmin || $isProjector || $isSystemUser)
{
    if ($actId !== false)
    {
       // Get estimate files info by act ID
       $estimateFilesInfo = dbProc::getEstimateFilesByActId($actId);
       if (is_array($estimateFilesInfo))
       {
           foreach ($estimateFilesInfo as $i=>$row)
           {
            $excelFileId = $row['ESTM_EXCEL_FILE_ID'];
            
            // Check if Excel file already exists
            if (empty($excelFileId) && !file_exists(EXCEL_FILES_STORE_PATH . '/' . $excelFileId))
            {
                // Generate Excel file on-demand
                $excelFileId = toExcel::exportEstimateStatistics($estimateId, $userId, $actId);
                
                if ($excelFileId !== false)
                {
                    // Save Excel file ID to estimate_files table for future use
                    dbProc::updateEstimateFileExcelId($estimateId, $excelFileId);
                    
                }
                else
                {
                    RequestHandler::showErrorAndDie(text::get('ERROR_CREATING_EXCEL'));
                }
            }

             // get file lin0
             $oLinkFile=new urlQuery();
             $oLinkFile->addPrm(IS_GET_PEXCEL_FILE_VARIABLE, 1);
             $oLinkFile->addPrm(GET_FILE_VARIABLE, $excelFileId);
             $estimateFilesInfo[$i]['getFileURL']=$oLinkFile ->getQuery();
             unset($oLinkFile);
            }
       }
     
      include('f.akt.s.27.tpl');
    }
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>



