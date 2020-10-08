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

// writeoff
if (isset($_GET['xml']) && isset($_GET['import']) && $_GET['import'] == 1 && isset($_GET['act']) )
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
     $r=dbProc::importProjectWorkMaterial($_GET['act'], $acts);
  }
  if($r)
  {
    foreach($acts as $a)
    {
          session::del('IMPORT_ACT_'.$a);
    }
  }
  
 // exit;
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
    $oFormPop = new Form('frmMainTab','post',$oLink->getQuery());
    unset($oLink);

    if($actId !== false )
    {
      $oLink=new urlQuery();
	    $oLink->addPrm(FORM_ID, 'f.akt.s.24');
      $searchLink = $oLink -> getQuery();
      unset($oLink);

      $oRedirectLink=new urlQuery();
      $oRedirectLink->addPrm(FORM_ID, 'f.akt.s.20');
      $oRedirectLink->addPrm('actId', $actId);
      $oRedirectLink->addPrm('tab', TAB_WORKS);
      $oRedirectLink->addPrm('isNew', RequestHandler::getMicroTime());
      $redirectUrl = $oRedirectLink->getQuery().'#tab';

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
      
      $title = text::toUpper(text::get('IMPORT_NO_PROJECT'));    
       // get grupas list           
      $res=dbProc::getProjectImportList($actId, $worker);
      //print_r($res);
      

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