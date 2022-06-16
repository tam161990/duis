<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isLimitCardUser = userAuthorization::isLimitcard();

// tikai  lietotajam ar atbilstošam tiesībam  vai administr�toram ir pieeja!
if($isLimitCardUser || $isAdmin)
{
    
        // Check if this form was requested via xmlHttpRequest and search
    	if (isset($_GET['xml']) && isset($_GET['search_q']))
    	{
    		ob_clean();
    		$q = $_GET['search_q'];
            if (isset($q) || $q == 0)
    		{
    			echo 'q = "'.trim($q).'";';
    		}
            else
            {
    			echo 'q = "";';
    		}            
		    exit;
    	}
        if (isset($_GET['xml']) && isset($_GET['sort_k']) && isset($_GET['sort_o']))
    	{
    		ob_clean();
    		$o = $_GET['sort_o'];
            if (isset($o))
    		{
    			echo 'o = "'.$o.'";';
    		}
            else
            {
    			echo 'o = "";';
    		}
            $k = $_GET['sort_k'];
            if ($k)
    		{
    			echo 'k = "'.$k.'";';
    		}
            else
            {
    			echo 'k = "";';
    		}
		    exit;
    	}
        // set list title
        $title = text::toUpper(text::get('PROJRCT_MATERIAL_REPORT'));
        // get search column list
        $columns=dbProc::getKlklName('LIMITCARD_PROJRCT_MATERIAL');
        $searchTitle = text::get('PROJRCT_NUMBER');
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;


        // default sort column
        $defaultColumn = dbProc::getKlklDefaultColumn('LIMITCARD_PROJRCT_MATERIAL');

        // URL to search Zinojums by number.
    	$oLink = new urlQuery;
    	$oLink-> addPrm(FORM_ID, 'f.lmk.s.1');
    	$oLink-> addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		//$amount=dbProc::getCalcNormCount($searchText,
        //        (($searchColumn === false) ? $defaultColumn : $searchColumn));
        $amount = 110;
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
        unset($oLink);
        
        $res = RequestHandler::getLimitkarteReport('LIMITCARD_PROJRCT_MATERIAL', $searchText, 1, 20);

        echo "<pre>";
        print_r($res);
        echo "</pre>";

		// gel list of users
		/*$res = dbProc::getCalcNormList( false,
                                        $listing->getStartPosition(),
                                        $listing->getAmountOnPage(),
                                        $searchText,
                                        (($searchColumn === false) ? $defaultColumn : $searchColumn),
                                        $sortOrder,
                                        $orderColumn);

		*/

		// inicial state of users number
		$number=$listing->getStartPosition()+1;

		include('f.ktl.s.x.1.tpl');
    /////////////////////////////////////////
    /*
	$searchMode = reqVar::get('isSearch');
	// top frame
    if($searchMode)
	{
        $oLink=new urlQuery();
    	$oLink->addPrm(FORM_ID, 'f.lmk.s.1');
    	$oLink->addPrm('isSearch', 1 );
    	// form inicialization
    	$oForm = new Form('frmMain','post',$oLink->getQuery());
    	unset($oLink);
        
        // if operation
    	if ($oForm -> isFormSubmitted())
    	{
            $oListLink=new urlQuery();
            $oListLink->addPrm(FORM_ID, 'f.lmk.s.1');
        }
        $searchTitle = text::toUpper(text::get('PROJRCT_MATERIAL_REPORT'));
        
        $searcCriteria = array();
        $workerCode = userAuthorization::getWorker();

       // if operation
    	if ($oForm -> isFormSubmitted())
    	{
           $searcCriteria['project_code'] = $oForm->getValue('project_code');          

           $cr = '';
           foreach($searcCriteria as $s)
           {
             $cr .= $s.'^';
           }
           $cr = substr($cr, 0, -1);
           $oListLink->addPrm('search', $cr);
           $actListLink=$oListLink ->getQuery();
           $oForm->addElement('static','jsRefresh2','','<script>reloadFrame(2, "'.$actListLink.'");</script>');
           unset($oListLink);
        }
        else
        {
            $searcCriteria['project_code']  = '';
        }

        $oForm -> addElement('text', 'project_code',  text::get('PROJRCT_NUMBER'), $searcCriteria['project_code'], 'maxlength="10"');
        
       	// form buttons
       	$oForm -> addElement('submitImg', 'search', text::get('SEARCH'), 'img/btn_meklet.gif', 'width="70" height="20" onClick="setPosition1(\'loading\'); return true;"');
        $oForm -> makeHtml();
        include('f.lmk.s.1.tpl');
	}
	// bottom frale
	else
	{
	    $sCriteria = reqVar::get('search');         

        // gel list of users
		$res = dbProc::getActTotalReportList($sCriteria, $trase, $sign);
      
        /$area = array();
        
        if (is_array($res))
		{
           
		}
        echo "<pre>";
        print_r($area);
        echo "</pre>";

		include('f.lmk.s.1.tpl');
    }
    */
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
