<?

$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isLimitCardUser = userAuthorization::isLimitcard();
// Report links


    if($isLimitCardUser || $isAdmin)
    {
         // 
		$oLink=new urlQuery();
		$oLink->addPrm('isSearch', '1');
    	$oLink->addPrm(FORM_ID, 'f.lmk.s.1');
    	$projectMaterialReport=$oLink ->getQuery();
    	unset($oLink);
		 // 
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', '1');
    	$oLink->addPrm(FORM_ID, 'f.lmk.s.2');
    	$uncompletedPrReport=$oLink ->getQuery();
    	unset($oLink);

        
    }

include('f.lmk.s.0.tpl');
?>