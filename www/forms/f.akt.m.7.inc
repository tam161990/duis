<?
// Main form with XMLHTTP method load this code:
if (reqVar::get('xmlHttp') == 1)
{
	
  if(reqVar::get('worker'))
  {
      $res=dbProc::getProjectorWorkerList(reqVar::get('worker'));
      if (is_array($res))
      {
      ?>
        document.all['ouner'].disabled = false;
        for(i=document.all["ouner"].length; i>=0; i--)
        {
          document.all["ouner"].options[i] = null;
        }
        document.all["ouner"].options[0] = new Option( '<?=text::get('ALL');?>', '-1');
        <?
          $i = 1;
          foreach ($res as $row)
          {					 
              ?>
              document.all["ouner"].options[<?=$i;?>] = new Option( '<?=$row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS'];?>', '<?=$row['RLTT_ID'];?>');
              
              <?
              $i++;
          }	
      }
      unset($res);
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
        $isProjector = dbProc::isExistsUserRoleWithProject($userId) && !$isAdmin ;

        // if came back from act
        $selectedId = reqVar::get('selectedId');        

      	if(count($userInfo) >0 )
      	{
      		$user = $userInfo[0];
       	}
        
        // get users list
        $usersList = array();
        $usersList['-1']=text::get('ALL');
        if($isAdmin) {
          $res = dbProc::getProjectorWorkerList();
        } else {
          if(isset($user['RLTT_KWOI_KODS']) ) {
            $res = dbProc::getProjectorWorkerList($user['RLTT_KWOI_KODS']);
          }
        }
        if (is_array($res))
        {
          
          foreach ($res as $row)
          {
            $usersList[$row['RLTT_ID']]=$row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS'];
          }
        }
        unset($res);
       
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
           $searcCriteria['worker'] = (($isProjector)? ((!empty($workerCode)) ? $workerCode : -1) : $oForm->getValue('worker'));
           $searcCriteria['edCode'] = $oForm->getValue('edCode');
           $searcCriteria['ouner'] = $oForm->getValue('ouner');
           $searcCriteria['status']  = $oForm->getValue('status');
           $searcCriteria['status1']  = implode("*",$oForm->getValue('status'));
                      
           dbProc::replaceSearchResult($searchName, $userId,
                                $searcCriteria['yearFrom'],
                                '',
                                '',
                                '',
                                $searcCriteria['worker'],
                                $searcCriteria['edCode'],
                                '',
                                '',
                                $searcCriteria['ouner'],
                                '',
                                '',
                                $searcCriteria['status1'],
                                '','', '','','','','','','', '', ''
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
           $searcCriteria['worker'] = (($isEditor)? $workerCode : (isset($critery['worker']) ? $critery['worker'] : '-1'));
           $searcCriteria['edCode'] = isset($critery['edCode'])? $critery['edCode'] :'-1';
           $searcCriteria['ouner'] = isset($critery['ouner'])? $critery['ouner'] : (($isAdmin) ? '-1' : $userId) ;
           $searcCriteria['status']  = isset($critery['status1'])? explode("*",$critery['status1']) : array(STAT_CLOSE);
           
        }

        $oForm -> addElement('label', 'year',  text::get('YEAR'), '');
        $oForm -> addElement('select', 'yearFrom',  text::get('FROM'), $searcCriteria['yearFrom'], 'style="width:50;"', '', '', dtime::get5YearsInFromtArray());
        
        // xmlHttp link
        $oLink=new urlQuery();
        $oLink->addPrm(DONT_USE_GLB_TPL, 1);
        $oLink->addPrm(FORM_ID, 'f.akt.m.7');

        $oForm -> addElement('kls2', 'worker',  text::get('SINGL_WORK_OWNER'),  array('classifName'=>KL_WORK_OWNERS,'value'=>$searcCriteria['worker'],'readonly'=>false), (($isEditor)?' disabled ':'').'maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&worker=\'+this.value))"');
        unset($oLink);
		    $oForm -> addElement('kls2', 'edCode',  text::get('SINGL_ED_AREA'), array('classifName'=>KL_ED_AREA_CODE,'value'=>$searcCriteria['edCode'],'readonly'=>false), 'tabindex=13 maxlength="2000" '.(($isEdUser)?' disabled' : ''));
        
        $oForm -> addElement('select', 'ouner',  text::get('ACT_OUNER'), $searcCriteria['ouner'], '', '', '', $usersList);

        $oForm -> addElement('multiple_select', 'status', text::get('STATUS'), $searcCriteria['status'], ' size="7"', '', '', $status);
        
       	// form buttons
       	$oForm -> addElement('submitImg', 'search', text::get('SEARCH'), 'img/btn_meklet.gif', 'width="70" height="20" onClick="setPosition1(\'loading\'); return true;"');

        $oForm -> makeHtml();
		    include('f.akt.m.7.tpl');
?>