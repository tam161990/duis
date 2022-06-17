<?
//created by Tatjana Fedorkova at 2004.12.02.
   
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isTraseUser = userAuthorization::isTrase();
$isContractUser = userAuthorization::isContract();
$isLimitCardUser = userAuthorization::isLimitcard();
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;
$isEdUser = dbProc::isUserInRole($userId, ROLE_ED_USER);
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);
$isAuditor = dbProc::isUserInRole($userId, ROLE_AUDIT_USER);
$isProjector = dbProc::isExistsUserRoleWithProject($userId) || dbProc::isUserInRole($userId, ROLE_DESIGNER);
$projectApprover = dbProc::isUserInRole($userId, ROLE_PROJ_APPROVER);

if($isContractUser)
    $isRight = true;
else //if ($isTraseUser  )
    $isRight = false;

  // EXIT LINK
$oUrl=new urlQuery();
$oUrl->addPrm(FORM_ID,'exit');
$exitUrl=$oUrl->getQuery();
unset($oUrl);

// get user info
$userInfo = dbProc::getUserInfo($userId);

if(count($userInfo) >0 )
{
  $userName = $userInfo[0]['RLTT_VARDS'];
  $userSurName = $userInfo[0]['RLTT_UZVARDS'];
  $userAuthDate = $userInfo[0]['RLTT_DATUMS'];
}
else
{
    RequestHandler::showErrorAndDie(text::get('NO_RESULT_FOUND'));
}
// jalietotajam nav lomas sist�m�, tad vinam nav tiesibas redzet si formu
if ( $isAdmin || $isSystemUser )
{
    // menu ACT
	// act main form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.akt.s.1');
	$actLink=$oLink ->getQuery();
	unset($oLink);

    // act for trase
	$oLink=new urlQuery();
    $oLink->addPrm('isTrase', '1');
   	$oLink->addPrm(FORM_ID, 'f.akt.s.1');
	$actTrLink=$oLink ->getQuery();
	unset($oLink);

	// project
	$oLink=new urlQuery();
   	$oLink->addPrm(FORM_ID, 'f.akt.s.20');
	$projectLink=$oLink ->getQuery();
	unset($oLink);

    // act advanced search form
	$oLink=new urlQuery();
	$oLink->addPrm('isSearch', '1');
	$oLink->addPrm(FORM_ID, 'f.akt.s.9');
	$actSearchLink=$oLink ->getQuery();
	unset($oLink);
    // list of acts
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'blank');
	$actListLink=$oLink ->getQuery();
	unset($oLink);

	// project advanced search form
	$oLink=new urlQuery();
	$oLink->addPrm('isSearch', '3');
	$oLink->addPrm(FORM_ID, 'f.akt.s.9');
	$projectSearchLink=$oLink ->getQuery();
	unset($oLink);
    // list of acts
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'blank');
	$actListLink=$oLink ->getQuery();
	unset($oLink);

    // write off acts
    // act writeoff search form
	$oLink=new urlQuery();
    $oLink->addPrm('isSearch', '1');
	$oLink->addPrm(FORM_ID, 'f.akt.s.14');
	$actSearchWriteoffLink=$oLink ->getQuery();
	unset($oLink);
    // list of acts
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'blank');
	$actWriteoffLink=$oLink ->getQuery();
	unset($oLink);


    // act search by number form
	$oLink=new urlQuery();
	$oLink->addPrm('isSearch', '2');
	$oLink->addPrm(FORM_ID, 'f.akt.s.9');
	$actSearchByNumberLink=$oLink ->getQuery();
	unset($oLink);
    // list of acts
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'blank');
	$actListLink=$oLink ->getQuery();
	unset($oLink);

// menu CATALOGS

    // list of materials
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.1');
	$materialListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit materials form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.1');
	$oLink->addPrm('editMode', '1');
	$editMaterialLink = $oLink->getQuery();
	unset($oLink);

    // list of regions
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.3');
	$regionListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit region form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.3');
	$oLink->addPrm('editMode', '1');
	$editRegionLink = $oLink->getQuery();
	unset($oLink);

    // list of saskanotaji
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.4');
	$harmonizedListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit saskanotaji form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.4');
	$oLink->addPrm('editMode', '1');
	$editHarmonizedLink = $oLink->getQuery();
	unset($oLink);

    // list of ed area
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.5');
	$edAreaListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit ed area form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.5');
	$oLink->addPrm('editMode', '1');
	$editEdAreaLink = $oLink->getQuery();
	unset($oLink);

    // list of voltage
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.6');
	$voltageListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit voltage form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.6');
	$oLink->addPrm('editMode', '1');
	$editVoltageLink = $oLink->getQuery();
	unset($oLink);

    // list of object
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.7');
	$objectListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit object form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.7');
	$oLink->addPrm('editMode', '1');
	$editObjectLink = $oLink->getQuery();
	unset($oLink);

    // list of DU
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.8');
	$dUListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit source of founds form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.8');
	$oLink->addPrm('editMode', '1');
	$editDULink = $oLink->getQuery();
	unset($oLink);

    // list of calculation group
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.9');
	$calculationGroupListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit calculation group form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.9');
	$oLink->addPrm('editMode', '1');
	$editCalculationGroupLink = $oLink->getQuery();
	unset($oLink);

    // list of calculation
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.10');
	$calculationListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit calculation form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.10');
	$oLink->addPrm('editMode', '1');
	$editCalculationLink = $oLink->getQuery();
	unset($oLink);

     // list of trase calculation
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
    $oLink->addPrm('isTrase', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.10');
	$calculationTrListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit trase calculation form
	$oLink=new urlQuery();
    $oLink->addPrm('isTrase', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.10');
	$oLink->addPrm('editMode', '1');
	$editCalculationTrLink = $oLink->getQuery();
	unset($oLink);

    // list of act types
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.11');
	$actTypeListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit act type form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.11');
	$oLink->addPrm('editMode', '1');
	$editActTypeLink = $oLink->getQuery();
	unset($oLink);

 	// list of users
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.12');
	$userListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit/delete user form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.12');
	$oLink->addPrm('editMode', '1');
	$editUserLink = $oLink->getQuery();
	unset($oLink);

    // list of DU users
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.2');
	$userDUListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit/delete user form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.2');
	$oLink->addPrm('editMode', '1');
	$editDUUserLink = $oLink->getQuery();
	unset($oLink);

    // list of mms
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.14');
	$mmsListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit/delete mms form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.14');
	$oLink->addPrm('editMode', '1');
	$editMMSLink = $oLink->getQuery();
	unset($oLink);

	// list of mms-calculation
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.20');
	$mmsCalculationListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit mms-calculation form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.20');
	$oLink->addPrm('editMode', '1');
	$editMmsCalculationLink = $oLink->getQuery();
	unset($oLink);

	// list of сalculation-material
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.21');
	$calculationMaterialListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit сalculation-material form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.21');
	$oLink->addPrm('editMode', '1');
	$editCalculationMaterialLink = $oLink->getQuery();
	unset($oLink);

	// list work type
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.22');
	$workTypeListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit work type form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.22');
	$oLink->addPrm('editMode', '1');
	$editWorkTypeLink = $oLink->getQuery();
	unset($oLink);

	// list calc norms
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.23');
	$CalcNormsListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit calc norms form
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.ktl.s.23');
	$oLink->addPrm('editMode', '1');
	$editCalcNormsLink = $oLink->getQuery();
	unset($oLink);

    // calalog imports
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.ktl.s.13');
	$catalogImportLink=$oLink ->getQuery();
	unset($oLink);



// Report links
	// Reports main
	$oLink = new urlQuery;
	$oLink -> addPrm(FORM_ID, 'f.rpt.s.0');
	$cRepMain = $oLink -> getQuery();
	unset($oLink);

   // GPS main
	$oLink = new urlQuery;
	$oLink -> addPrm(FORM_ID, 'f.gps.s.0');
	$cGpsMain = $oLink -> getQuery();
	unset($oLink);

	// LimitCard links
	// Reports main
	$oLink = new urlQuery;
	$oLink -> addPrm(FORM_ID, 'f.lmk.s.0');
	$cLimitcardMain = $oLink -> getQuery();
	unset($oLink);

// menu OPTIONS
	// warning
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.adm.s.1');
	$warningLink=$oLink ->getQuery();
	unset($oLink);

	// users actions
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.adm.s.2');
	$userActionsLink=$oLink ->getQuery();
	unset($oLink);

	// kvikStep
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.adm.s.3');
	$kvikStepLink=$oLink ->getQuery();
	unset($oLink);

	// superadmin
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.adm.s.5');
	$superadminLink=$oLink ->getQuery();
	unset($oLink);


	// list of jobs
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'f.adm.s.4');
	$jobListLink=$oLink ->getQuery();
	unset($oLink);
	// add/edit job
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.adm.s.4');
	$oLink->addPrm('editMode', '1');
	$editJobLink = $oLink->getQuery();
	unset($oLink);

	// event log
	$oLink=new urlQuery();
	$oLink->addPrm('isSearch', '1');
	$oLink->addPrm(FORM_ID, 'f.adm.s.6');
	$eventSearchLink=$oLink ->getQuery();
	unset($oLink);
    // list of acts
	$oLink=new urlQuery();
	$oLink->addPrm('isNew', '1');
	$oLink->addPrm(FORM_ID, 'blank');
	$eventListLink=$oLink ->getQuery();
	unset($oLink);
}
else
{
    $isRight = false;
    //RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
include('f.inf.s.1.tpl');

?>