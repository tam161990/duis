<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isLimitCardUser = userAuthorization::isLimitcard();
$report = reqVar::get('report');

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
        switch ($report) {
            case 'LIMITCARD_PROJRCT_MATERIAL':                
                $title = text::toUpper(text::get('PROJRCT_MATERIAL_REPORT'));                
				break;			
			case 'UNCOMPLETED_PROJECT_REPORT':
				$title = text::toUpper(text::get('UNCOMPLETED_PROJECT_REPORT'));   
				break;			
		}
        // get search column list
        $columns=dbProc::getKlklName($report);
        
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
        $oLink-> addPrm('report', $report);
        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
        $listing=new listing();
        
        if($searchText !== false) {
            $reportData = RequestHandler::getLimitkarteReport($report, $searchText, 1, 1);

            $amount = $reportData['totalRecordCount']; 
            $listing->setAmount($amount);
            $listingHtml=$listing->getHtml($oLink ->getQuery());
            unset($oLink);

            $reportData = RequestHandler::getLimitkarteReport($report, $searchText, $listing->getCurrentPageNumber(), $listing->getAmountOnPage());
            $rows = $reportData['reportData'];

            if (is_array($rows))
            {
                $res = array();
                $i = 0;
                foreach ($rows as $row) {
                    $res[$i] = $row;
                    $res[$i]['itemUnitPrice'] = number_format($row['itemUnitPrice'], 2, '.', '');
                    $date = new DateTime((string)substr($row['transactionDate'], 0, strrpos($row['transactionDate'], 'T')));
                    $res[$i]['transactionDate'] =  $date->format('d.m.Y');
                    $date = new DateTime((string)substr($row['creationDate'], 0, strrpos($row['creationDate'], 'T')));
                    $res[$i]['creationDate'] =  $date->format('d.m.Y');
                    $date = new DateTime((string)substr($row['approvedDate'], 0, strrpos($row['approvedDate'], 'T')));
                    $res[$i]['approvedDate'] =  $date->format('d.m.Y');
                    $i ++;
                }
            }
        } 
		
		// inicial state of users number
		$number=$listing->getStartPosition()+1;

		include('f.ktl.s.x.1.tpl');

}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
