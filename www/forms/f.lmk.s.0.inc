<?

$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isLimitCardUser = userAuthorization::isLimitcard();
// Report links


if($isLimitCardUser || $isAdmin)
{
		// 
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.lmk.s.1');
	$oLink->addPrm(report, 'LIMITCARD_PROJRCT_MATERIAL');
	$projectMaterialReport=$oLink ->getQuery();
	unset($oLink);
		// 
	$oLink=new urlQuery();
	$oLink->addPrm(FORM_ID, 'f.lmk.s.1');
	$oLink->addPrm(report, 'UNCOMPLETED_PROJECT_REPORT');
	$uncompletedPrReport=$oLink ->getQuery();
	unset($oLink);        
}

include('f.lmk.s.0.tpl');
?>