<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isPpaUser = userAuthorization::isPpaReport();
$report = reqVar::get('report');

// tikai  lietotajam ar atbilstošam tiesībam  vai administr�toram ir pieeja!
if($isPpaUser || $isAdmin)
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

    // set list title
    $title = text::toUpper(text::get('PPA')); 
    // get search column list
    $columns=dbProc::getKlklName('PPA');
    $report = 'PPA';
    
    $searchTitle = text::get('ROJRCT_CODE');
    $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
    

    // default sort column
    $defaultColumn = dbProc::getKlklDefaultColumn('PPA');

    // URL to search Zinojums by number.
    $oLink = new urlQuery;
    $oLink-> addPrm(FORM_ID, 'f.ppa.s.1');
    $oLink-> addPrm('isNew', '1');
    $oLink-> addPrm('report', $report);
    // add search/order params to listing
    $oLink->addPrm('search', reqVar::get('search'));
    $searchLink = $oLink -> getQuery();
    unset($oLink);

    if($searchText !== false) {
        $reportData = RequestHandler::getPPAReport($searchText, 1, 30);            
        $rows = $reportData['reportData'];

        if (is_array($rows))
        {
            $res = array();
            $i = 0;
            $total2 = 0;
            foreach ($rows as $row) {
                $res[$i] = $row;
                $date = new DateTime((string)substr($row['ExpectedExecutionDate'], 0, strrpos($row['ExpectedExecutionDate'], 'T')));
                $res[$i]['ExpectedExecutionDate'] =  $date->format('d.m.Y');                    
                $i ++;					
            }
        }
    } 
    
    include('f.ktl.s.x.1.tpl');

}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
