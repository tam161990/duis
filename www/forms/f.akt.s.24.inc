<?

// if a kataloga ACT set
if (isset($_GET['xml']) && isset($_GET['act']) && isset($_GET['op']))
{
      ob_clean();
      $o = $_GET['op'];
      $a = $_GET['act'];
      if (isset($o) && $o == OP_INSERT)
      {
      	session::set('IMPORT_ACT_'.$a,$a);
      }
      else
      {
         session::del('IMPORT_ACT_'.$a);
      }
  exit;
}


// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isProjector = dbProc::isExistsUserRoleWithProject($userId) ;
$isSystemUser = dbProc::isExistsUserRole($userId) || $isEditor;

// act ID
$actId  = reqVar::get('actId');


// tikai  sistēmas lietotajam vai administrātoram ir pieeja!
if ( $isAdmin || $isProjector)
{
    $oLink=new urlQuery();
    $oLink->addPrm(FORM_ID, 'f.akt.s.24');
    $oLink->addPrm('actId', $actId);
    $oFormPop = new Form('frmMainTab','post',$oLink->getQuery());
    unset($oLink);

    if($actId !== false )
    {
      $oLink=new urlQuery();
	    $oLink->addPrm(FORM_ID, 'f.akt.s.24');
      $searchLink = $oLink -> getQuery();
      unset($oLink);

      // get info about act
      $actInfo = dbProc::getActInfo($actId);
      //print_r($actInfo);
      if(count($actInfo)>0)
      {
      	$act = $actInfo[0];
        $status = $act['RAKT_STATUS'];
        $worker = $act['RAKT_KWOI_KODS'];
      }

      $isReadonly   = true;
      // Ir pieejams mainīšanai, ja  AKTS:LIETOTĀJS = ’Tekošais lietotājs’ un lietotāja loma ir ‘Ievadītais’ un AKTS:STATUS = ‘Izveide’ vai ‘Atgriezts’ vai ‘Tāme’.
      if(($act['RAKT_RLTT_ID'] == $userId && $isProjector || $isAdmin) && ($status == STAT_INSERT || $status == STAT_RETURN ) )
      {
        $isReadonly   = false;
      }
      
         // if operation
    	if ($oFormPop -> isFormSubmitted())
    	{
          // get acts array
          $acts = array();
          $r = false;
          foreach ($_SESSION as $key => $val)
          {
            if(substr($key, 0, 10) == 'IMPORT_ACT')
            {
              $acts[] = $val;
            }
          }
          //print_r($acts);
          if(count($acts) > 0)
          {
            $r=dbProc::importProjectWorkMaterial($actId, $acts);
          }
          else {
            $oFormPop->addError(text::get('ERROR_NOT_CHECKED'));
          }
          if($r !== false)
          {
            foreach($acts as $a)
            {
                  session::del('IMPORT_ACT_'.$a);
            }
          }
      }
      $title = text::toUpper(text::get('IMPORT_NO_PROJECT'));    
       // get grupas list           
      $res=dbProc::getProjectImportList($actId, $worker);
      //print_r($res);

      $oFormPop -> addElement('hidden', 'action', '');
      $oFormPop -> addElement('hidden', 'actId', '', $actId);

      if (!$isReadonly)
      {
        $oFormPop -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMainTab\',\'actId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {return false;}"');
       
      }    
      $oFormPop -> addElement('button', 'close', '', text::get('CLOSE'), 'class="btn70" onclick="javascript:window.close();return false;"; ');

      if ($oFormPop -> isFormSubmitted())
    	{
          $oRedirectLink=new urlQuery();
          $oRedirectLink->addPrm(FORM_ID, 'f.akt.s.20');
          $oRedirectLink->addPrm('actId', $actId);
          $oRedirectLink->addPrm('tab', TAB_WORKS);
          $oRedirectLink->addPrm('isNew', RequestHandler::getMicroTime());
          if(count($res) == 0) {
            requestHandler::makeParentReplace($oRedirectLink->getQuery().'#tab');
          } else {
            $oFormPop->addElement('static','jsRefresh2','','<script>window.opener.location.replace( "'.$oRedirectLink->getQuery().'#tab'.'" );</script>');
          }
          
          unset($oRedirectLink);
      }

      $oFormPop -> makeHtml();
      include('f.akt.s.24.tpl');
    }
    else
	{
		$oFormPop->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
	}
}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}

?>