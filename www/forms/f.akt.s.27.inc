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
     
      include('f.akt.s.27.tpl');
    }
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>


