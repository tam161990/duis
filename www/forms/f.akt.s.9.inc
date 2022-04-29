<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isProjector = dbProc::isExistsUserRoleWithProject($userId) ;
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor || $isProjector;
// if came back from act
$selectedId = reqVar::get('selectedId');

// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
    $searchMode = reqVar::get('isSearch');
    
	// top frame
    if($searchMode == 1)
	{
        $oLink=new urlQuery();
    	$oLink->addPrm(FORM_ID, 'f.akt.s.9');
    	$oLink->addPrm('isSearch', 1 );
    	// form inicialization
    	$oForm = new Form('frmMain','post',$oLink->getQuery());
    	unset($oLink);

        $oLink=new urlQuery();
	    $oLink->addPrm('isReturn', '1');
        $oLink->addPrm('isSearch', 1 );
	    $oLink->addPrm(FORM_ID, 'f.akt.s.9');
	    $criteriaLink=$oLink ->getQuery();
	    unset($oLink);

         // if operation
    	if ($oForm -> isFormSubmitted())
    	{
            $oListLink=new urlQuery();
            $oListLink->addPrm(FORM_ID, 'f.akt.s.9');
            $oListLink->addPrm('isNumber', 0 );
            $oListLink->addPrm('isProject', 0 );
        }
        $searchTitle = text::toUpper(text::toUpper(text::get('ADVANCED_SEARCH')));
        $searchName = 'ADVANCED_SEARCH';
        $isSearchForm = true;
        include('f.akt.m.1.inc');
	}
    elseif($searchMode == 2)
	{
        
        $oLink=new urlQuery();
    	$oLink->addPrm(FORM_ID, 'f.akt.s.9');
    	$oLink->addPrm('isSearch', 2 );
    	// form inicialization
    	$oForm = new Form('frmMain','post',$oLink->getQuery());
    	unset($oLink);

         // if operation
    	if ($oForm -> isFormSubmitted())
    	{
            $oListLink=new urlQuery();
            $oListLink->addPrm(FORM_ID, 'f.akt.s.9');
            $oListLink->addPrm('isNumber', 1 );
            $oListLink->addPrm('isProject', 0 );
        }
        $searchTitle = text::toUpper(text::toUpper(text::get('SEARCH_BY_NUMBER')));
        include('f.akt.m.3.inc');
    }
    elseif($searchMode == 3)
	{
        

        $oLink=new urlQuery();
    	$oLink->addPrm(FORM_ID, 'f.akt.s.9');
    	$oLink->addPrm('isSearch', 3 );
    	// form inicialization
    	$oForm = new Form('frmMain','post',$oLink->getQuery());
    	unset($oLink);
       
        $oLink=new urlQuery();
	    $oLink->addPrm('isReturn', '1');
        $oLink->addPrm('isSearch', 3 );
	    $oLink->addPrm(FORM_ID, 'f.akt.s.9');
	    $criteriaLink=$oLink ->getQuery();
	    unset($oLink);

         // if operation
    	if ($oForm -> isFormSubmitted())
    	{
            $oListLink=new urlQuery();
            $oListLink->addPrm(FORM_ID, 'f.akt.s.9');
            $oListLink->addPrm('isNumber', 0 );
            $oListLink->addPrm('isProject', 1 );
        }
        $searchTitle = text::toUpper(text::toUpper(text::get('ADVANCED_PROJECT_SEARCH')));
        $searchName = 'ADVANCED_PROJECT_SEARCH';
        $isSearchForm = true;
        include('f.akt.m.7.inc');
	}
	// bottom frale
	else
	{
	    $sCriteria = reqVar::get('search');
        $isNumber = reqVar::get('isNumber');
        $isProject = reqVar::get('isProject');
        
        //echo $isNumber;
        if($selectedId)
        {
          if($isNumber != 0)
          {
            $sCriteria = $isNumber;
          }
          else
          {
            $searchCritery = dbProc::getSearchCritery($userId);
           	if(count($searchCritery) >0 )
      	    {
      		   $critery = $searchCritery[0];
            }
            $searcCriteria = array();   
            if($isProject == 0) {

            
                $searcCriteria['yearFrom'] = isset($critery['yearFrom'])? $critery['yearFrom'] :dtime::getCurrentYear();
                $searcCriteria['yearUntil'] = isset($critery['yearUntil'])? $critery['yearUntil'] :dtime::getCurrentYear();
                $searcCriteria['monthFrom'] = isset($critery['monthFrom'])? $critery['monthFrom'] :dtime::getCurrentMonth();
                $searcCriteria['monthUntil'] = isset($critery['monthUntil'])? $critery['monthUntil'] :dtime::getCurrentMonth();

                $searcCriteria['worker'] = isset($critery['worker'])? $critery['worker'] :$user['RLTT_KWOI_KODS'];
                $searcCriteria['edRegion'] = isset($critery['edRegion'])? $critery['edRegion'] :'-1';

                $searcCriteria['voltage'] = isset($critery['voltage'])? $critery['voltage'] :'-1';
                $searcCriteria['ouner'] = isset($critery['ouner'])? $critery['ouner'] :(($isEconomist || $isEditor) ? -1 : $userId);
                $searcCriteria['type'] = isset($critery['type'])? $critery['type'] :'-1';
                //$searcCriteria['isFinished'] = isset($critery['isFinished'])? $critery['isFinished'] :'-1';
                $searcCriteria['status']  = isset($critery['status'])? $critery['status'] : 'STAT_CLOSE';
                $searcCriteria['status1']  = isset($critery['status1'])? $critery['status1'] : 'STAT_CLOSE';
                $searcCriteria['designation']  = isset($critery['designation'])? $critery['designation'] : '';
                $searcCriteria['section']  = isset($critery['section'])? $critery['section'] : '-1';
                $searcCriteria['contract']  = isset($critery['contract'])? $critery['contract'] : '';

            } else {

                $searcCriteria['yearFrom'] = isset($critery['yearFrom'])? $critery['yearFrom'] :dtime::getCurrentYear();              
                $searcCriteria['worker'] = isset($critery['worker'])? $critery['worker'] :((isset($user['RLTT_KWOI_KODS'])) ? $user['RLTT_KWOI_KODS'] : -1 );
                $searcCriteria['edRegion'] = isset($critery['edRegion'])? $critery['edRegion'] :'-1';
                $searcCriteria['ouner'] = isset($critery['ouner'])? $critery['ouner'] :(($isEconomist || $isEditor) ? -1 : $userId);
                $searcCriteria['status']  = isset($critery['status'])? $critery['status'] : 'STAT_CLOSE';
                $searcCriteria['status1']  = isset($critery['status1'])? $critery['status1'] : 'STAT_CLOSE';
                
            }

            $cr = '';
            foreach($searcCriteria as $s)
            {
                $cr .= $s.'^';
            }
            $cr = substr($cr, 0, -1);
            $sCriteria  = $cr;

            }
        }

        // URL
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.akt.s.9');
        $oLink->addPrm('search', $sCriteria);
        $oLink->addPrm('isNumber', $isNumber);

       	// inicialising of listing object
        $amount= (($isNumber == 0) ? 
                    (($isProject == 0 ) ? dbProc::getActCount($sCriteria) : dbProc::getProjectCount($sCriteria)) : 
                    dbProc::getActByNumberCount($sCriteria, (($isAdmin ) ? false : userAuthorization::getWorker())));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for redirect to act
		$oLink=new urlQuery();		
        $oLink->addPrm('isProject', $isProject);
        $oLink->addPrm('searchNum', ($isNumber == 0)?false:$sCriteria );

		// gel list of users
        if($isNumber == 0)
        {   
            if($isProject == 0) {
                $res = dbProc::getActList(  $listing->getStartPosition(),
                                            $listing->getAmountOnPage(),
                                            $sCriteria);
                $oLink->addPrm('isSearch', 1 );
            } else {
                $res = dbProc::getProjectList(  $listing->getStartPosition(),
                                            $listing->getAmountOnPage(),
                                            $sCriteria);
                $oLink->addPrm('isSearch', 3 );
            }
        }
        else
        {
            $res = dbProc::getActByNumberList( $listing->getStartPosition(),
                                        $listing->getAmountOnPage(),
                                        $sCriteria,
                                        (($isAdmin ) ? false : userAuthorization::getWorker())
                                    );
            $oLink->addPrm('isSearch', 2 );
        }

		if (is_array($res))
		{
			foreach ($res as $i=>$row)
			{
                if( $row['RAKT_PROJECT'] == 1) {
                    $oLink->addPrm(FORM_ID, 'f.akt.s.20');
                } else {
                    $oLink->addPrm(FORM_ID, 'f.akt.s.1');
                    $oLink->addPrm('isTrase', $row['RAKT_TRASE']);  
                }
				// add dv area Id to each link
				$oLink->addPrm('actId', $row['RAKT_ID']);
                
				$res[$i]['URL']=$oLink ->getQuery();
                $res[$i]['selected']= ($row['RAKT_ID'] == $selectedId) ? 1 : 0;
			}
		}
		unset($oLink);

		// inicial state of users number
		$number=$listing->getStartPosition()+1;

		include('f.akt.s.9.1.tpl');
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
