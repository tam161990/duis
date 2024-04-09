<?
$trase = isset($trase)? $trase : reqVar::get('isTrase');
// Main form with XMLHTTP method load this code:
if (reqVar::get('xmlHttp') == 1)
{
	//if is set edRegion
	
    //if is set worker
	if (reqVar::get('worker') !== false)
	{
	    // unset previouse values of section
		?>
		for(i=document.all["contract"].length; i>=0; i--)
		{
			document.all["contract"].options[i] = null;
		}
		<?
		$res=dbProc::getDuContractNo(reqVar::get('worker'), reqVar::get('trase'), true);
		if (is_array($res) && count($res)>0)
		{

            $i = 0;
			foreach ($res as $row)
			{
				// feel options array
				?>
				document.all["contract"].options[<?=$i;?>] = new Option( '<?=$row['KEDI_NOSAUKUMS'] . ': '. $row['KCNT_VV_NUMBER'];?>', '<?=$row['KCNT_VV_NUMBER'].'|'.$row['KONT_KEDI_KODS'];?>');
                <?
                $i++;
			}
		}
	}
	exit;
}
    $isSearchForm = isset($isSearchForm)? $isSearchForm : false;
    // get user info
    $userInfo = dbProc::getUserInfo($userId);
    $isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);
    $isViewer = dbProc::isUserInRole($userId, ROLE_VIEWER);
    $isAdmin=userAuthorization::isAdmin();
    $isEditor = (userAuthorization::getWorker() != false) ? true : false;
    $isEdUser = dbProc::isUserInRole($userId, ROLE_ED_USER);
    // if came back from act
    $selectedId = reqVar::get('selectedId');
    if(count($userInfo) >0 )
    {
        $user = $userInfo[0];
    }

    $searcCriteria = array();
    $workerCode = userAuthorization::getWorker();

    // if operation
    if ($oForm -> isFormSubmitted())
    {
        $searcCriteria['year'] = $oForm->getValue('year');
        $searcCriteria['month'] = $oForm->getValue('month');
        $searcCriteria['worker'] = (($isEditor)? $workerCode : $oForm->getValue('worker'));
        $contr = explode('|',$oForm->getValue('contract'));
        $searcCriteria['contract'] = $contr[0];
        $searcCriteria['edarea'] = $contr[1];
        $searcCriteria['one_contract'] = $oForm->getValue('one_contract', 0);

        dbProc::replaceSearchResult($searchName, $userId,
                            $searcCriteria['year'],
                            '',
                            $searcCriteria['month'],
                            '',
                            $searcCriteria['worker'],
                            $searcCriteria['edarea'],
                            '',
                            '',
                            '',
                            '',
                            $searcCriteria['one_contract'],                            
                            '',
                            '',
                            '',
                            '','','','','','','',
                            '',
                            '',
                            $searcCriteria['contract']
                            );

        $cr = '';
        foreach($searcCriteria as $s)
        {
            $cr .= $s.'^';
        }
        $cr = substr($cr, 0, -1);
        $oListLink->addPrm('search', $cr);
        $oListLink->addPrm('trase', $trase);
        $actListLink=$oListLink ->getQuery();
        $oForm->addElement('static','jsRefresh2','','<script>reloadFrame(2, "'.$actListLink.'");</script>');
        unset($oListLink);
    }
    else
    {
        if (reqVar::get('isReturn') == 1 || $selectedId)
        {
            $searchCritery = dbProc::getSearchCritery($userId);
            if(count($searchCritery) >0 )
            {
                $critery = $searchCritery[0];
            }

        }


        $searcCriteria['year'] = isset($critery['yearFrom'])? $critery['yearFrom'] :dtime::getCurrentYear();

        $searcCriteria['month'] = isset($critery['monthFrom'])? $critery['monthFrom'] :dtime::getCurrentMonth();

        $searcCriteria['worker'] = (($isEditor)? $workerCode : (isset($critery['worker']) ? $critery['worker'] : '-1'));
        
        $searcCriteria['contract']  = isset($critery['contract'])? $critery['contract'] . '|'.$searcCriteria['edarea'] : '-1';

        $searcCriteria['one_contract']  = isset($critery['isFinished'])? $critery['isFinished']  : '0';

    }

    // get worker list
    $worker=array();
    $j = 0;
    $res=dbProc::getWorkOwnerWithActivContractList();
            if (is_array($res))
            {
                foreach ($res as $row)
                {
                    $worker[$row['KWOI_KODS']]=$row['KWOI_NOSAUKUMS'];
                    if($j == 0)
                    {
                        $initWorker =  $row['KWOI_KODS'];
                    }
                    $j++;
                }
            }
    unset($res);

    // get contract list
    $contract = array();
    $res=dbProc::getDuContractNo((($searcCriteria['worker'] == '-1')? $initWorker : $searcCriteria['worker']), $trase, true);
    if (is_array($res))
    {
        foreach ($res as $row)
        {
            $contract[$row['KCNT_VV_NUMBER'].'|'.$row['KONT_KEDI_KODS']] = $row['KEDI_NOSAUKUMS'] . ': '. $row['KCNT_VV_NUMBER'];
        }
    }
    unset($res);

    $oForm -> addElement('select', 'year',  text::get('YEAR'), $searcCriteria['year'], 'style="width:50;"', '', '', dtime::getYearArray());

    $oForm -> addElement('select', 'month',  text::get('MONTH'), $searcCriteria['month'], 'style="width:70;"', '', '', dtime::getMonthArray());

    // xmlHttp link
    $oLink=new urlQuery();
    $oLink->addPrm(DONT_USE_GLB_TPL, 1);
    $oLink->addPrm(FORM_ID, 'f.akt.m.4');
    $oLink->addPrm('trase', $trase );


    //echo $searcCriteria['worker'];
    $oForm -> addElement('select', 'worker',  text::get('SINGL_WORK_OWNER'), $searcCriteria['worker'],  (($isEditor)?' disabled ':'').'  onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&worker=\'+this.value))"', '', '', $worker);
    unset($oLink);
    //$oForm -> addElement('kls3', 'worker',  text::get('SINGL_WORK_OWNER'),  array('classifName'=>KL_WORK_OWNERS,'value'=>$searcCriteria['worker'],'readonly'=>false), (($isEditor)?' disabled ':'').'maxlength="2000"');
    $oForm -> addElement('select', 'contract',  text::get('KWOI_VV_NUMBER'), $searcCriteria['contract'], '', '', '', $contract);
    
    $oForm -> addElement('checkbox', 'one_contract',  text::get('ALL_ED_AREAS_IN_CONTRACT'), $searcCriteria['one_contract'], '');
    // form buttons
    $oForm -> addElement('submitImg', 'search', text::get('SEARCH'), 'img/btn_meklet.gif', 'width="70" height="20" onClick="setPosition1(\'loading\'); return true;"');

    $oForm -> makeHtml();
    include('f.akt.m.4.tpl');
?>