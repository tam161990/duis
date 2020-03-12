<?
// Main form with XMLHTTP method load this code:
if (reqVar::get('xmlHttp') == 1)
{
	//if is set edRegion
	if (reqVar::get('edRegion') !== false)
	{

        // unset previouse values of section
		?>
		for(i=document.all["section"].length; i>=0; i--)
		{
			document.all["section"].options[i] = null;
		}
		<?
		$res=dbProc::getEDSectionListForRegion(reqVar::get('edRegion'));
		if (is_array($res) && count($res)>0)
		{
			?>
			document.all["section"].options[0] = new Option('<?=text::get('ALL');?>', '-1');
			<?
            $i = 1;
			foreach ($res as $row)
			{
				// feel options array
				?>
				document.all["section"].options[<?=$i;?>] = new Option( '<?=$row['KEDI_SECTION'];?>', '<?=$row['KEDI_SECTION'];?>');
                <?
                $i++;
			}
		}
	}


	exit;
}
         // get user info
      	$userInfo = dbProc::getUserInfo($userId);
        $isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);
        $isAdmin=userAuthorization::isAdmin();

       $searcCriteria = array();
       $workerCode = userAuthorization::getWorker();
       if(count($userInfo) >0 )
      	{
      		$user = $userInfo[0];
       	}


         // get ED region list
         $edRegion=array();
         $initRegion = '-1';
         $j = 0;
         if(isset($user['RLTT_REGIONS']) && isset($user['RLTT_ROLE']) && ($isEconomist || $isViewer) )
         {
            $edRegion[$user['RLTT_REGIONS']]=$user['RLTT_REGIONS'];
            $initRegion = $user['RLTT_REGIONS'];
         }
         elseif(isset($user['RLTT_KEDI_SECTION']) && isset($user['RLTT_ROLE']) &&  ($isEconomist || $isViewer) )
         {
              $region = dbProc::getEDRegionBySection($user['RLTT_KEDI_SECTION']) ;
              $edRegion[$region]=$region;
         }
         else
         {
           $edRegion['-1']=text::get('ALL');
           $res=dbProc::getEDRegionList();
           if (is_array($res))
           {
           	foreach ($res as $row)
           	{
			if($j == 0)
                	{
                     	$initRegion = $row['nosaukums'];
                	}
           		$edRegion[$row['nosaukums']]=$row['nosaukums'];
			$j++;
           	}
           }
         }
         unset($res);
       // if operation
    	if ($oForm -> isFormSubmitted())
    	{
           $searcCriteria['yearFrom'] = $oForm->getValue('yearFrom');
           $searcCriteria['yearUntil'] = $oForm->getValue('yearUntil');
           $searcCriteria['monthFrom'] = $oForm->getValue('monthFrom');
           $searcCriteria['monthUntil'] = $oForm->getValue('monthUntil');
           $searcCriteria['worker'] = $oForm->getValue('worker');
           $searcCriteria['writeoff'] = $oForm->getValue('writeoff');
           $searcCriteria['edRegion'] = $oForm->getValue('edRegion');
           $searcCriteria['section'] = $oForm->getValue('section');

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

           $searcCriteria['yearFrom'] = dtime::getCurrentYear();
           $searcCriteria['yearUntil'] = dtime::getCurrentYear();
           $searcCriteria['monthFrom'] = dtime::getCurrentMonth();
           $searcCriteria['monthUntil'] = dtime::getCurrentMonth();
           $searcCriteria['worker'] = '-1';
           $searcCriteria['writeoff'] = '-1';
           $searcCriteria['edRegion'] = '-1';
           $searcCriteria['section']  = '-1';
        }

        // get ED section list
        $section=array();
        if(isset($user['RLTT_KEDI_SECTION']) && isset($user['RLTT_ROLE']) &&  ($isEconomist || $isViewer) )
        {
             $section[$user['RLTT_KEDI_SECTION']]=$user['RLTT_KEDI_SECTION'];
        }
        elseif(isset($user['RLTT_REGIONS']) && isset($user['RLTT_ROLE']) && ($isEconomist || $isViewer) )
        {
            $res=dbProc::getEDSectionListForRegion($user['RLTT_REGIONS']);
			if (is_array($res))
			{
			    $section['-1']=text::get('ALL');
				foreach ($res as $row)
				{
					$section[$row['KEDI_SECTION']]=$row['KEDI_SECTION'];
				}
			}
         }
         else
         {
            $res=dbProc::getEDSectionListForRegion((($searcCriteria['edRegion'] == '-1') ? $initRegion : $searcCriteria['edRegion']));
            if (is_array($res))
            {
                $section['-1']=text::get('ALL');
             	foreach ($res as $row)
             	{
              	    $section[$row['KEDI_SECTION']]=$row['KEDI_SECTION'];
                }
            }
         }
        unset($res);

        $oForm -> addElement('label', 'year',  text::get('YEAR'), '');
        $oForm -> addElement('select', 'yearFrom',  text::get('FROM'), $searcCriteria['yearFrom'], 'style="width:50;"', '', '', dtime::getYearArray());
        $oForm -> addElement('select', 'yearUntil',  text::get('UNTIL'), $searcCriteria['yearUntil'], 'style="width:50;"', '', '', dtime::getYearArray());

        $oForm -> addElement('label', 'month',  text::get('MONTH'), '');
        $oForm -> addElement('select', 'monthFrom',  text::get('FROM'), $searcCriteria['monthFrom'], 'style="width:70;"', '', '', dtime::getMonthArray());
        $oForm -> addElement('select', 'monthUntil',  text::get('UNTIL'), $searcCriteria['monthUntil'], 'style="width:70;"', '', '', dtime::getMonthArray());
        $oForm -> addElement('kls2', 'worker',  text::get('SINGL_WORK_OWNER'),  array('classifName'=>KL_WORK_OWNERS,'value'=>$searcCriteria['worker'],'readonly'=>false), 'maxlength="2000"');
        $oForm -> addElement('kls2', 'writeoff',  text::get('WRITE_OFF_ACCOUNT'),  array('classifName'=>KL_WRITEOFF,'value'=>$searcCriteria['writeoff'],'readonly'=>false), 'maxlength="2000"');

        // xmlHttp link
		$oLink=new urlQuery();
		$oLink->addPrm(DONT_USE_GLB_TPL, 1);
		$oLink->addPrm(FORM_ID, 'f.akt.m.2');

        $oForm -> addElement('select', 'edRegion',  text::get('ED_REGION'), $searcCriteria['edRegion'], 'onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&edRegion=\'+document.all[\'edRegion\'].options[document.all[\'edRegion\'].selectedIndex].value));"', '', '', $edRegion);
        unset($oLink);

        $oForm -> addElement('select', 'section',  text::get('ED_SECTION'), $searcCriteria['section'], '', '', '', $section);

       	// form buttons
       	$oForm -> addElement('submitImg', 'search', text::get('SEARCH'), 'img/btn_meklet.gif', 'width="70" height="20" onClick="setPosition1(\'loading\'); return true;"');

        $oForm -> makeHtml();
		include('f.akt.m.2.tpl');
?>