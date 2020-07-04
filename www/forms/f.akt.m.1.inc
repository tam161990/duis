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

        // get users list
         $usersList = array();
         if(isset($user['RLTT_KEDI_SECTION']) && !$isEdUser)
         {
            $res=dbProc::getUserSectionList($user['RLTT_KEDI_SECTION'], false);
            if (is_array($res))
            {
              $usersList['-1']=text::get('ALL');
              foreach ($res as $row)
              {
                $usersList[$row['RLTT_ID']]=$row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS'];
              }
            }
         }
         elseif(isset($user['RLTT_REGIONS']) && !$isEdUser)
         {
            $res=dbProc::getUserRegionList($user['RLTT_REGIONS'], false);
            if (is_array($res))
            {
              $usersList['-1']=text::get('ALL');
              foreach ($res as $row)
              {
                $usersList[$row['RLTT_ID']]=$row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS'];
              }
            }
         }
         elseif(isset($user['RLTT_KWOI_KODS']) && !$isEdUser)
         {
            $res=dbProc::getUserWorkerList($user['RLTT_KWOI_KODS'], false);
            if (is_array($res))
            {
              $usersList['-1']=text::get('ALL');
              foreach ($res as $row)
              {
                $usersList[$row['RLTT_ID']]=$row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS'];
              }
            }
         }
         else
         {
           $res=dbProc::getUsersList(false,false,false,false,false,false,'ASC','RLTT_VARDS, RLTT_UZVARDS');
            if (is_array($res))
            {
              $usersList['-1']=text::get('ALL');
              foreach ($res as $row)
              {
                $usersList[$row['RLTT_ID']]=$row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS'];
              }
            }
         }

        // get is finished list
        $isFinished = array();
        $isFinished['-1']=text::get('ALL');
        $isFinished['1']=text::get('YES');
        $isFinished['2']=text::get('NO');

        // get status list
       $status=array();
       $status['-1']=text::get('ALL_STATUS');
       $res=dbProc::getKrfkName(KRFK_STATUS);
       if (is_array($res))
       {
       	foreach ($res as $row)
       	{
       	  $status[$row['nosaukums']]=$row['nozime'];
       	}
       }
       unset($res);

       $searcCriteria = array();
       $workerCode = userAuthorization::getWorker();
       // if operation
    	if ($oForm -> isFormSubmitted())
    	{
           $searcCriteria['yearFrom'] = $oForm->getValue('yearFrom');
           $searcCriteria['yearUntil'] = $oForm->getValue('yearUntil');
           $searcCriteria['monthFrom'] = $oForm->getValue('monthFrom');
           $searcCriteria['monthUntil'] = $oForm->getValue('monthUntil');
           $searcCriteria['worker'] = (($isEditor)? $workerCode : $oForm->getValue('worker'));
           $searcCriteria['edRegion'] = $oForm->getValue('edRegion');

           $searcCriteria['voltage'] = $oForm->getValue('voltage');
           $searcCriteria['ouner'] = $oForm->getValue('ouner');
           $searcCriteria['type'] = $oForm->getValue('type');

           $searcCriteria['status']  = $oForm->getValue('status');
           $searcCriteria['status1']  = implode("*",$oForm->getValue('status'));
           $searcCriteria['designation'] = $oForm->getValue('designation');
           $searcCriteria['section'] = $oForm->getValue('section');
           $searcCriteria['object']  = ($searchName == 'REPORT_MATERIALS_IN_MONTH')? $oForm->getValue('object'):'';
           dbProc::replaceSearchResult($searchName, $userId,
                                $searcCriteria['yearFrom'],
                                $searcCriteria['yearUntil'],
                                $searcCriteria['monthFrom'],
                                $searcCriteria['monthUntil'],
                                $searcCriteria['worker'],
                                $searcCriteria['edRegion'],
                                '',
                                $searcCriteria['voltage'],
                                $searcCriteria['ouner'],
                                $searcCriteria['type'],
                                '',
                                $searcCriteria['status1'],
                                '',
                                $searcCriteria['object'],
                                '','','','','','','',
                                $searcCriteria['designation'],
                                $searcCriteria['section']
                                );

           $cr = '';
           foreach($searcCriteria as $s)
           {
            
                if(is_array($s)){
                    $cr .= implode('^', $s).'^';
                    
                }
                else {
                    $cr .= $s.'^';
                }
           }
           $cr = substr($cr, 0, -1);
           $oListLink->addPrm('search', $cr);
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


           $searcCriteria['yearFrom'] = isset($critery['yearFrom'])? $critery['yearFrom'] :dtime::getCurrentYear();
           $searcCriteria['yearUntil'] = isset($critery['yearUntil'])? $critery['yearUntil'] :dtime::getCurrentYear();
           $searcCriteria['monthFrom'] = isset($critery['monthFrom'])? $critery['monthFrom'] :dtime::getCurrentMonth();
           $searcCriteria['monthUntil'] = isset($critery['monthUntil'])? $critery['monthUntil'] :dtime::getCurrentMonth();

           $searcCriteria['worker'] = (($isEditor)? $workerCode : (isset($critery['worker']) ? $critery['worker'] : '-1'));
           $searcCriteria['edRegion'] = isset($critery['edRegion'])? $critery['edRegion'] :'-1';


           $searcCriteria['voltage'] = isset($critery['voltage'])? $critery['voltage'] :'-1';
           $searcCriteria['ouner'] = isset($critery['ouner'])? $critery['ouner'] :'-1';
           $searcCriteria['type'] = isset($critery['type'])? $critery['type'] :'-1';

           $searcCriteria['status']  = isset($critery['status1'])? explode("*",$critery['status1']) : array(STAT_CLOSE);
           $searcCriteria['designation']  = isset($critery['designation'])? $critery['designation'] : '';
           $searcCriteria['section']  = isset($critery['section'])? $critery['section'] : '-1';
           $searcCriteria['object'] = isset($critery['object'])? $critery['object'] :'-1';
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
        // xmlHttp link
        $oLink=new urlQuery();
        $oLink->addPrm(DONT_USE_GLB_TPL, 1);
        $oLink->addPrm(FORM_ID, 'f.akt.m.1');

        $oForm -> addElement('kls2', 'worker',  text::get('SINGL_WORK_OWNER'),  array('classifName'=>KL_WORK_OWNERS,'value'=>$searcCriteria['worker'],'readonly'=>false), (($isEditor)?' disabled ':'').'maxlength="2000"');

		    $oForm -> addElement('select', 'edRegion',  text::get('ED_REGION'), $searcCriteria['edRegion'], 'onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&edRegion=\'+document.all[\'edRegion\'].options[document.all[\'edRegion\'].selectedIndex].value));"', '', '', $edRegion);
        unset($oLink);

        $oForm -> addElement('select', 'section',  text::get('ED_SECTION'), $searcCriteria['section'], '', '', '', $section);

        $oForm -> addElement('kls2', 'voltage',  text::get('SINGLE_VOLTAGE'), array('classifName'=>KL_VOLTAGE,'value'=>$searcCriteria['voltage'],'readonly'=>false), 'maxlength="2000"');

        $oForm -> addElement('select', 'ouner',  text::get('ACT_OUNER'), $searcCriteria['ouner'], '', '', '', $usersList);

        $oForm -> addElement('kls2', 'type',  text::get('SINGLE_ACT_TYPE'), array('classifName'=>KL_ACT_TYPE_ALL,'value'=>$searcCriteria['type'],'readonly'=>false), 'maxlength="2000"');


        $oForm -> addElement('multiple_select', 'status', text::get('STATUS'), $searcCriteria['status'], ' size="7"', '', '', $status);
        if($searchName == 'REPORT_MATERIALS_IN_MONTH')
        {
              $oForm -> addElement('kls2', 'object',  text::get('SINGLE_OBJECT'), array('classifName'=>KL_OBJECTS,'value'=>$searcCriteria['object'],'readonly'=>false), 'maxlength="2000"');
        }

        if($isSearchForm)
        {
           $oForm -> addElement('text', 'designation',  text::get('MAIN_DESIGNATION'), $searcCriteria['designation'], '', false, false,false,true);
        }

       	// form buttons
       	$oForm -> addElement('submitImg', 'search', text::get('SEARCH'), 'img/btn_meklet.gif', 'width="70" height="20" onClick="setPosition1(\'loading\'); return true;"');



        $oForm -> makeHtml();
		    include('f.akt.m.1.tpl');
?>