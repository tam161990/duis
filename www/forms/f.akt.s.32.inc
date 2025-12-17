<?
// RBF Act Attachments Tab (f.akt.s.32.inc)
// Based on f.akt.s.6.inc
// Created for DUIS-549

$userId = userAuthorization::getUserId();
$isAdmin = userAuthorization::isAdmin();
$isRbfUser = userAuthorization::isRbfUser();
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);

// act ID
$actId = reqVar::get('actId');

// Check if user has access (already includes economist)
if ($isAdmin || $isRbfUser || $isEconomist)
{
    if($actId !== false)
    {
        // Get file info by act ID
        $fileInfo = dbProc::getFilesInfo($actId, FILE_EXPORT);

        // Get file link
        $oLinkFile = new urlQuery();
        $oLinkFile->addPrm(IS_GET_FILE_VARIABLE, 1);
        if (is_array($fileInfo))
        {
            foreach ($fileInfo as $i=>$row)
            {
                $oLinkFile->addPrm(GET_FILE_VARIABLE, $row['RFLS_ID']);
                $fileInfo[$i]['getFileURL'] = $oLinkFile->getQuery();
            }
        }
        unset($oLinkFile);

        include('f.akt.s.32.tpl');
    }
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>
