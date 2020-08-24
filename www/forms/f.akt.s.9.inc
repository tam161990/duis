<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;
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
        }
        $searchTitle = text::toUpper(text::toUpper(text::get('SEARCH_BY_NUMBER')));
        include('f.akt.m.3.inc');
	}
	// bottom frale
	else
	{
	    $sCriteria = reqVar::get('search');
        $isNumber = reqVar::get('isNumber');
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

       	// inicialising of listing object
		$amount= (($isNumber == 0) ? dbProc::getActCount($sCriteria) : dbProc::getActByNumberCount($sCriteria));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for redirect to act
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.akt.s.1');
        $oLink->addPrm('isSearch', ($isNumber == 0)?1:2 );
        $oLink->addPrm('searchNum', ($isNumber == 0)?false:$sCriteria );

		// gel list of users
        if($isNumber == 0)
        {   
		    $res = dbProc::getActList(  $listing->getStartPosition(),
                                        $listing->getAmountOnPage(),
                                        $sCriteria);
        }
        else
        {
            $res = dbProc::getActByNumberList( $listing->getStartPosition(),
                                        $listing->getAmountOnPage(),
                                        $sCriteria,
                                        userAuthorization::getWorker());
        }

		if (is_array($res))
		{
			foreach ($res as $i=>$row)
			{
				// add dv area Id to each link
				$oLink->addPrm('actId', $row['RAKT_ID']);
                $oLink->addPrm('isTrase', $row['RAKT_TRASE']);  
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
