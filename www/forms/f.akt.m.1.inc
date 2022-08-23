<?

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

        // get users list
         $usersList = array();
         if(isset($user['RLTT_KEDI_SECTION']) && !$isEdUser)
         {
            $res=dbProc::getUserSectionList($user['RLTT_KEDI_SECTION']);
            if (is_array($res))
            {
              $usersList['-1']=text::get('ALL');
              foreach ($res as $row)
              {
                $usersList[$row['RLTT_ID']]=$row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS'];
              }
            }
         }
         elseif(isset($user['RLTT_KEDI_ID']) && !$isEdUser)
         {
            $res=dbProc::getUserEdList($user['RLTT_KEDI_ID']);
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
            $res=dbProc::getUserWorkerList($user['RLTT_KWOI_KODS']);
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
                if($row['RLTT_IR_AKTIVS'] == 1) {
                  $usersList[$row['RLTT_ID']]=$row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS'];
                }
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
           $searcCriteria['edCode'] = $oForm->getValue('edCode');

           $searcCriteria['voltage'] = $oForm->getValue('voltage');
           $searcCriteria['ouner'] = $oForm->getValue('ouner');
           $searcCriteria['type'] = $oForm->getValue('type');

           $searcCriteria['status']  = $oForm->getValue('status');
           $searcCriteria['status1']  = implode("*",$oForm->getValue('status'));
           $searcCriteria['designation'] = $oForm->getValue('designation');
           $searcCriteria['section'] = $oForm->getValue('section');
           if($searchName == 'REPORT_MATERIALS_IN_MONTH'){
            $searcCriteria['object']  = $oForm->getValue('object');
          } else {
            $searcCriteria['contract'] = $oForm->getValue('contract');
          }
           $searcCriteria['object']  = ($searchName == 'REPORT_MATERIALS_IN_MONTH')? $oForm->getValue('object'):'';
           
           dbProc::replaceSearchResult($searchName, $userId,
                                $searcCriteria['yearFrom'],
                                $searcCriteria['yearUntil'],
                                $searcCriteria['monthFrom'],
                                $searcCriteria['monthUntil'],
                                $searcCriteria['worker'],
                                $searcCriteria['edCode'],
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
                                $searcCriteria['section'],
                                $searcCriteria['contract']
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
           $searcCriteria['edCode'] = isset($critery['edCode'])? $critery['edCode'] :'-1';


           $searcCriteria['voltage'] = isset($critery['voltage'])? $critery['voltage'] :'-1';
           $searcCriteria['ouner'] = isset($critery['ouner'])? $critery['ouner'] :'-1';
           $searcCriteria['type'] = isset($critery['type'])? $critery['type'] :'-1';

           $searcCriteria['status']  = isset($critery['status1'])? explode("*",$critery['status1']) : array(STAT_CLOSE);
           $searcCriteria['designation']  = isset($critery['designation'])? $critery['designation'] : '';
           $searcCriteria['section']  = isset($critery['section'])? $critery['section'] : '-1';
           
           if($searchName == 'REPORT_MATERIALS_IN_MONTH'){
             $searcCriteria['object'] = isset($critery['object'])? $critery['object'] :'-1';
           } else {
             $searcCriteria['contract']  = isset($critery['contract'])? $critery['contract'] : '';
           }
           
           
        }

        // get ED section list
        $section=array();
        if(isset($user['RLTT_KEDI_SECTION']) && isset($user['RLTT_ROLE']) &&  ($isEconomist || $isViewer) )
        {
             $section[$user['RLTT_KEDI_SECTION']]=$user['RLTT_KEDI_SECTION'];
        }        
         else
         {
          $res=dbProc::getEDAreaSectionList();
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
        
        $oForm -> addElement('kls2', 'worker',  text::get('SINGL_WORK_OWNER'),  array('classifName'=>KL_WORK_OWNERS,'value'=>$searcCriteria['worker'],'readonly'=>false), (($isEditor)?' disabled ':'').'maxlength="2000"');

		    $oForm -> addElement('kls2', 'edCode',  text::get('SINGL_ED_AREA'), array('classifName'=>KL_ED_AREA_CODE,'value'=>$searcCriteria['edCode'],'readonly'=>false), 'tabindex=13 maxlength="2000" '.(($isEdUser)?' disabled' : ''));
        

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

        $oForm -> addElement('text', 'contract',  text::get('KWOI_VV_NUMBER'), $searcCriteria['contract                                               '], '', false, false,false,true);

       	// form buttons
       	$oForm -> addElement('submitImg', 'search', text::get('SEARCH'), 'img/btn_meklet.gif', 'width="70" height="20" onClick="setPosition1(\'loading\'); return true;"');



        $oForm -> makeHtml();
		    include('f.akt.m.1.tpl');
?>