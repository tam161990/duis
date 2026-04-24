<?
// RBF Act Attachments Tab (f.akt.s.32.inc)
// Based on f.akt.s.6.inc
// Created for DUIS-549
// Updated to support file uploads

$userId = userAuthorization::getUserId();
$isAdmin = userAuthorization::isAdmin();
$isRbfUser = userAuthorization::isRbfUser();
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);

// act ID
$actId = reqVar::get('actId');

// Note: $oForm is already created in parent (f.akt.s.30.inc) and available here

// Check if user has access (already includes economist)
if ($isAdmin || $isRbfUser || $isEconomist)
{
    if($actId !== false)
    {
        // Get act status to check if editing is allowed
        $act = dbProc::getRbfActInfo($actId);
        $status = isset($act['RAKT_STATUS']) ? $act['RAKT_STATUS'] : false;
        
        // Determine if user can edit files
        $canEdit = false;
        if ($isAdmin) {
            // Admin can always edit
            $canEdit = true;
        } elseif ($isEconomist) {
            // Economist can edit in INSERT, RETURN, and ACCEPT status
            $canEdit = ($status == STAT_INSERT || $status == STAT_RETURN || $status == STAT_ACCEPT);
        } elseif ($isRbfUser) {
            // RBF user can edit only in INSERT or RETURN status
            $canEdit = ($status == STAT_INSERT || $status == STAT_RETURN);
        }

        // Handle success message from redirect - check flash message first
        if (session::hasFlash('successMessage'))
        {
            $oForm->addSuccess(session::getFlash('successMessage'));
        }
        else if (reqVar::get('successMessage') !== false)
        {
            $oForm->addSuccess(reqVar::get('successMessage'));
        }
        
        // Handle file upload
        if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['upload_file']) && $canEdit)
        {
            $description = reqVar::get('file_description');
            
            if (files::isUploadFile('file_upload'))
            {
                // Validate file type
                if (files::isValidRbfFile('file_upload'))
                {
                    // Save file
                    $fileId = files::saveFile('file_upload', $description, $userId, $actId, false, FILE_RBF);
                    
                    if ($fileId !== false)
                    {
                        error_log("RBF file uploaded successfully. File ID: $fileId, Act ID: $actId, User ID: $userId");
                        
                        // Set flash message (will show once after redirect)
                        session::setFlash('successMessage', text::get('FILE_OPERATION_SUCCESS'));
                        
                        // Redirect to keep the Pielikumi tab active
                        $oUrl = new urlQuery();
                        $oUrl->addPrm('formId', 'f.akt.s.30');
                        $oUrl->addPrm('actId', $actId);
                        $oUrl->addPrm('tab', 'RBF_ATTACHMENTS');
                        RequestHandler::makeRedirect($oUrl->getQuery());
                        exit();
                    }
                    else
                    {
                        $oForm->addError(text::get('FILE_UPLOAD_FAILED'));
                        error_log("RBF file upload failed. Act ID: $actId, User ID: $userId");
                    }
                }
                else
                {
                    $oForm->addError(text::get('FILE_INVALID_TYPE'));
                }
            }
            else
            {
                $oForm->addError(text::get('FILE_NOT_SELECTED'));
            }
        }
        
        // Handle file deletion
        if (isset($_GET['delete_file']) && $canEdit)
        {
            $fileId = reqVar::get('delete_file');
            if (is_numeric($fileId))
            {
                if (files::deleteFile($fileId, FILE_RBF))
                {
                    error_log("RBF file deleted successfully. File ID: $fileId, Act ID: $actId, User ID: $userId");
                    
                    // Redirect to keep the Pielikumi tab active
                    $oUrl = new urlQuery();
                    $oUrl->addPrm('formId', 'f.akt.s.30');
                    $oUrl->addPrm('actId', $actId);
                    $oUrl->addPrm('tab', 'RBF_ATTACHMENTS');
                    $oUrl->addPrm('successMessage', text::get('FILE_OPERATION_SUCCESS'));
                    RequestHandler::makeRedirect($oUrl->getQuery());
                    exit();
                }
                else
                {
                    $oForm->addError(text::get('FILE_DELETE_FAILED'));
                    error_log("RBF file deletion failed. File ID: $fileId, Act ID: $actId, User ID: $userId");
                }
            }
        }

        // Get file info by act ID - show BOTH exported PDF (FILE_EXPORT) and uploaded files (FILE_RBF)
        $fileInfoExport = dbProc::getFilesInfo($actId, FILE_EXPORT);  // PDF from "Nodot" export
        $fileInfoRbf = dbProc::getFilesInfo($actId, FILE_RBF);         // User-uploaded files
        
        // Merge both arrays
        $fileInfo = array();
        if (is_array($fileInfoExport)) {
            $fileInfo = array_merge($fileInfo, $fileInfoExport);
        }
        if (is_array($fileInfoRbf)) {
            $fileInfo = array_merge($fileInfo, $fileInfoRbf);
        }

        // Get file link - create separate URL for each file
        if (is_array($fileInfo) && count($fileInfo) > 0)
        {
            foreach ($fileInfo as $i=>$row)
            {
                // Create new urlQuery object for each file to avoid parameter accumulation
                $oLinkFile = new urlQuery();
                $oLinkFile->addPrm(IS_GET_FILE_VARIABLE, 1);
                $oLinkFile->addPrm(GET_FILE_VARIABLE, $row['RFLS_ID']);
                
                // Determine file type based on RFLS_TYPE
                // For EXPORT type files, use 'PDF' for download handler
                // For RBF type files, use 'RBF' for download handler
                $rfls_type = isset($row['RFLS_TYPE']) ? $row['RFLS_TYPE'] : 'PDF';
                $fileType = ($rfls_type == 'EXPORT') ? 'PDF' : $rfls_type;
                $oLinkFile->addPrm('type', $fileType);
                
                $fileInfo[$i]['getFileURL'] = $oLinkFile->getQuery();
                $fileInfo[$i]['fileType'] = $rfls_type; // Store original type for delete button logic
                unset($oLinkFile);
                
                // Get file icon based on extension
                $ext = strtolower(pathinfo($row['RFLS_NOSAUKUMS'], PATHINFO_EXTENSION));
                switch($ext) {
                    case 'pdf':
                        $fileInfo[$i]['icon'] = 'ico_pdf.gif';
                        break;
                    case 'doc':
                    case 'docx':
                        $fileInfo[$i]['icon'] = 'ico_word.gif';
                        break;
                    case 'xls':
                    case 'xlsx':
                        $fileInfo[$i]['icon'] = 'ico_excel.gif';
                        break;
                    case 'jpg':
                    case 'jpeg':
                    case 'png':
                    case 'gif':
                        $fileInfo[$i]['icon'] = 'ico_image.gif';
                        break;
                    default:
                        $fileInfo[$i]['icon'] = 'ico_file.gif';
                }
            }
        }

        include('f.akt.s.32.tpl');
    }
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
