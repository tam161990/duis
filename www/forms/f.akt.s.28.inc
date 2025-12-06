<?
// Created by 
// Export estimate file statistics to Excel

$userId = userAuthorization::getUserId();
$isAdmin = userAuthorization::isAdmin();
$isProjector = dbProc::isExistsUserRoleWithProject($userId);
$isSystemUser = dbProc::isExistsUserRole($userId);

// Estimate ID
$estimateId = reqVar::get('estimateId');

// Only system user or administrator has access!
if ($isAdmin || $isProjector || $isSystemUser)
{
    if ($estimateId !== false)
    {
        // Get estimate file info
        $estimateInfo = dbProc::getEstimateFileInfo($estimateId);
        
        if ($estimateInfo !== false)
        {
            $actId = $estimateInfo['ESTM_RAKT_ID'];
            $excelFileId = $estimateInfo['ESTM_EXCEL_FILE_ID'];
            
            // Check if Excel file already exists
            if (!empty($excelFileId) && file_exists(EXCEL_FILES_STORE_PATH . '/' . $excelFileId))
            {
                // Send the pre-generated Excel file to user
                files::sendFile($excelFileId, true, 'EXCEL');
                exit(); // Ensure no additional output after file is sent
            }
            else
            {
                // Generate Excel file on-demand
                $excelFileId = toExcel::exportEstimateStatistics($estimateId, $userId, $actId);
                
                if ($excelFileId !== false)
                {
                    // Save Excel file ID to estimate_files table for future use
                    dbProc::updateEstimateFileExcelId($estimateId, $excelFileId);
                    
                    // Send the Excel file to user
                    files::sendFile($excelFileId, true, 'EXCEL');
                    exit(); // Ensure no additional output after file is sent
                }
                else
                {
                    RequestHandler::showErrorAndDie(text::get('ERROR_CREATING_EXCEL'));
                }
            }
        }
        else
        {
            RequestHandler::showErrorAndDie(text::get('ERROR_ESTIMATE_FILE_NOT_FOUND'));
        }
    }
    else
    {
        RequestHandler::showErrorAndDie(text::get('ERROR_ESTIMATE_ID_NOT_PROVIDED'));
    }
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>


