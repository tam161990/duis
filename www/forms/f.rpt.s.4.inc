<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isSystemUser = dbProc::isExistsUserRole($userId);
// TRASE act
   $trase =  reqVar::get('isTrase');
define ('COLUMN_VOLTAGE','s.KSRG_NOSAUKUMS');
define ('COLUMN_FINANSESANAS_AVOTS','f.KFNA_NOSAUKUMS');

// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isSystemUser)
{
	$searchMode = reqVar::get('isSearch');
	// top frame
    if($searchMode)
	{
        $oLink=new urlQuery();
    	$oLink->addPrm(FORM_ID, 'f.rpt.s.4');
    	$oLink->addPrm('isSearch', 1 );
        $oLink->addPrm('isTrase', $trase );
    	// form inicialization
    	$oForm = new Form('frmMain','post',$oLink->getQuery());
    	unset($oLink);

        $oLink=new urlQuery();
	    $oLink->addPrm('isReturn', '1');
        $oLink->addPrm('isSearch', 1 );
        $oLink->addPrm('isTrase', $trase );
	    $oLink->addPrm(FORM_ID, 'f.rpt.s.4');
	    $criteriaLink=$oLink ->getQuery();
	    unset($oLink);

        // if operation
    	if ($oForm -> isFormSubmitted())
    	{
            $oListLink=new urlQuery();
            $oListLink->addPrm(FORM_ID, 'f.rpt.s.4');
            $oListLink->addPrm('isTrase', $trase );
        }
        $searchTitle = text::toUpper(text::toUpper(text::get('REPORT_MAIN_ACT').(($trase == 1) ? ' ('.text::get('TRASE').')' : '' )));
        $searchName = 'REPORT_MAIN_ACT';
        include('f.akt.m.5.inc');
	}
	// bottom frale
	else
	{
        // Check if this form was requested via xmlHttpRequest and sort
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

	    $sCriteria = reqVar::get('search');
        $sOrder = reqVar::get('sortOrder');

        $sortColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderString = '';

        if($sOrder === false || $sOrder == '')
        {
          if($sortColumn !== false && $sortOrder !== false)
          {
            $aOrder = array();
            $aOrder[0] = $sortColumn.' '.$sortOrder;
          }
        }
        else
        {
          if($sortColumn !== false && $sortOrder !== false)
          {
            if(strpos($sOrder, ',') === false)
            {
              $aOrder = array();
              $aOrder[0] = $sOrder;
              $aOrder[1] = $sortColumn.' '.$sortOrder;
            }
            else
            {
              $aOrder = array();
              $aOrder[0] = $sortColumn.' '.$sortOrder;
            }
          }
        }

        if(isset($aOrder) && is_array($aOrder) && count($aOrder) > 0)
        {
            $orderString = implode(',', $aOrder);
        }

        // URL to search Zinojums by number.
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.rpt.s.4');
    	$oLink->addPrm('search', $sCriteria);
        $oLink->addPrm('isTrase', $trase );
        $oLink->addPrm('sortOrder', $orderString);
        $searchLink = $oLink -> getQuery();

        // URL  export
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.rpt.e.4');
    	$oLink->addPrm('search', $sCriteria);
        $oLink->addPrm('isTrase', $trase );
        $oLink->addPrm('sortOrder', $orderString);
        $oLink->addPrm(DONT_USE_GLB_TPL, '1');
        $exportUrl =  $oLink ->getQuery();
        unset($oLink);

        // URL  print
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.rpt.p.4');
        $oLink->addPrm('isTrase', $trase );
    	$oLink->addPrm('search', $sCriteria);       
        $oLink->addPrm('sortOrder', $orderString);
        //$oLink->addPrm(DONT_USE_GLB_TPL, '1');
        $printUrl =  $oLink ->getQuery();
        unset($oLink);

		// gel list of users
		$res = dbProc::getActFullList($sCriteria, $orderString, $trase);
        $work = 0;
        $st_material = 0;
        $du_material = 0;
        if (is_array($res))
		{
			foreach ($res as $i=>$row)
			{
               $work = $work + $row['WORK_TOTAL'];
               $st_material = $st_material + $row['ST_MATER_TOTAL'];
               $du_material = $du_material + $row['DU_MATER_TOTAL'];
			}
		}
        $work = number_format($work,2, '.', '');
        $st_material = number_format($st_material,2, '.', '');
        $du_material = number_format($du_material, 2, '.', '');

		include('f.rpt.s.4.tpl');
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
