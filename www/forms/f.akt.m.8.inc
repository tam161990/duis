<?

    $isSearchForm = isset($isSearchForm)? $isSearchForm : false;
    // get user info
    $userInfo = dbProc::getUserInfo($userId);        
    $isAdmin=userAuthorization::isAdmin();
    
    if(count($userInfo) >0 )
    {
        $user = $userInfo[0];
    }
    $searcCriteria = array();
    
    
    // if operation
    if ($oForm -> isFormSubmitted())
    {
        $r = false;

        // delete
        if ($oForm->getValue('action')== OP_DELETE  )
        {
            $r=dbProc::deleteEventLog( );
            if ($r === false)
            {
                $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
            }
        }			
            
        $searcCriteria['type'] = $oForm->getValue('type');
        $searcCriteria['section'] = $oForm->getValue('section');
        $searcCriteria['ouner'] = $oForm->getValue('ouner');

        dbProc::replaceSearchResult($searchName, $userId,
                            '',
                            '',
                            '',
                            '',
                            '',
                            '',
                            '',
                            '',
                            $searcCriteria['ouner'],
                            $searcCriteria['type'],
                            '',
                            '',
                            '',
                            '',
                            '','','','','','','',
                            '',
                            $searcCriteria['section']
                            );

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
        if (reqVar::get('isReturn') == 1 )
        {
            $searchCritery = dbProc::getSearchCritery($userId);
            if(count($searchCritery) >0 )
            {
                $critery = $searchCritery[0];
            }

        }
        $searcCriteria['ouner'] = isset($critery['ouner']) ? $critery['ouner'] : '-1';
        $searcCriteria['type'] = isset($critery['type'])? $critery['type'] :'-1';
        $searcCriteria['section']  = isset($critery['section'])? $critery['section'] : '-1';

    }

    // get type list
    $types = array();
    $types['-1']=text::get('ALL');
    $types['A']=text::get('EVENT_TYPE_ACTIVITY');
    $types['W']=text::get('EVENT_TYPE_WARNING');
    $types['C']=text::get('EVENT_TYPE_CRITICAL');

    // get module list
    $sections = array();
    $res=dbProc::getAllModules();
    if (is_array($res))
    {
        $sections['-1']=text::get('ALL');
        foreach ($res as $row)
        {
            $sections[$row['EVMD_MODULE']]=text::get($row['EVMD_MODULE']);;
        }
    }
    unset($res);

    // get users list
    $usersList = array();
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
    unset($res);
    $oForm -> addElement('hidden', 'action', '');
    $oForm -> addElement('select', 'type',  text::get('TYPE'), $searcCriteria['type'], '', '', '', $types);
    $oForm -> addElement('select', 'section',  text::get('EVENT_MODULE'), $searcCriteria['section'], '', '', '', $sections);
    $oForm -> addElement('select', 'ouner',  text::get('USER'), $searcCriteria['ouner'], '', '', '', $usersList);

    // form buttons
    $oForm -> addElement('submitImg', 'search', text::get('SEARCH'), 'img/btn_meklet.gif', 'width="70" height="20" onClick="setPosition1(\'loading\'); return true;"');

    $oForm -> addElement('submitImg', 'delete', text::get('DELETE'), 'img/btn_dzest.gif', 'width="70" height="20" onclick="if (isDeleteWithMessage(\''.text::get('WARNING_DELETE_ROW').'\')) {setValue(\'action\',\''.OP_DELETE.'\');} else {return false;}"');

    $oForm -> makeHtml();
    include('f.akt.m.8.tpl');
?>