<?
// Created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();
$isAdmin=userAuthorization::isAdmin();
$isEditor = (userAuthorization::getWorker() != false) ? true : false;
$isProjector = dbProc::isExistsUserRoleWithProject($userId) ;
$isEconomist = dbProc::isUserInRole($userId, ROLE_ECONOMIST);
// act ID
$actId  = reqVar::get('actId');
// tab name
$tab  = reqVar::get('tab');
// search form
$isSearch  = reqVar::get('isSearch');
// search act by number
$searchNum  = reqVar::get('searchNum');
if($tab === false)
{
  $tab = TAB_WORKS;
}
$isNew  = reqVar::get('isNew');
$isProject = 1;

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



// tikai  sist?mas lietotajam vai administr?toram ir pieeja!
if ( $isAdmin || $isProjector)
{
  $oLink=new urlQuery();
  $oLink->addPrm(FORM_ID, 'f.akt.s.20');
  $oLink->addPrm('isSearch', $isSearch);
  $oLink->addPrm('searchNum', $searchNum);
  $oForm = new Form('frmMain','post',$oLink->getQuery());
  unset($oLink);

  // get user info
  $userInfo = dbProc::getUserInfo($userId);
  if(count($userInfo) >0 )
  {
  	$user = $userInfo[0];
  }

  $edarea=array();
  $edarea['']=text::get('EMPTY_SELECT_OPTION');

  $ouner = array();
  $ouner['']=text::get('EMPTY_SELECT_OPTION');

  // if operation is success, show success message and redirect top frame
  if (reqVar::get('successMessage'))
  {
  	$oForm->addSuccess(reqVar::get('successMessage'));
  	//$oForm->addElement('static','jsRefresh2','','<script>refreshFrame(1);</script>');
  }

  if (reqVar::get('errorMessage'))
  {
  	$oForm->addError(reqVar::get('errorMessage'));
  }

  // get info about system
  $systemInfo = dbProc::getSystemInfo();
  if(count($systemInfo)>0)
  {
  	$info = $systemInfo[0];
  }

  $res=dbProc::getEDAreaActivList();

  if (is_array($res))
  {
        foreach ($res as $row)
        {
            $edarea[$row['KEDI_ID']]=$row['KEDI_NOSAUKUMS'];
        }
  }
  unset($res);
  
  if($actId != false)
  {
  	// get info about voltage
  	$actInfo = dbProc::getActInfo($actId);
  	//print_r($actInfo);
  	if(count($actInfo)>0)
  	{
  		  $act = $actInfo[0];
        $status = $act['RAKT_STATUS'];
        $statusLabel =  $act['STATUS_NAME'];
        $worker = $act['RAKT_KWOI_KODS'];

        if($worker !== false) {
          $res = dbProc::getProjectorWorkerList($worker);
        }
  	}
  }
  else
  {
    // get default statuss
    $statusInfo = dbProc::getKrfkInfoByName(STAT_INSERT);
    $status = $statusInfo['KRFK_VERTIBA'];
    $statusLabel = $statusInfo['KRFK_NOZIME'];    
    $worker = userAuthorization::getWorker();

    if($isAdmin) {
      $res = dbProc::getProjectorWorkerList();
    }
  }

  if (is_array($res))
  {
    foreach ($res as $row)
    {
      $ouner[$row['RLTT_ID']]=$row['RLTT_VARDS'].' '.$row['RLTT_UZVARDS'];
    }
    unset($res);
  }
  
  

  $isReadonly   = true;
  $isReadonly1   = true;
  $isReadonlyExceptAdmin   = true;
  $isReadonlyExceptEconomist   = true;

  if($actId != false)
  {

    // Ir pieejams main??anai, ja  AKTS:LIETOT?JS = �Teko?ais lietot?js� un lietot?ja loma ir �Ievad?tais� un AKTS:STATUS = �Izveide� vai �Atgriezts� vai �T?me�.
    if(($isProjector || $isAdmin) && ($status == STAT_AUTO) )
    {
      $isReadonly   = false;
    }
    // labo autors, inženieris, administrators
    if( ($isProjector || $isAdmin)  && ($status == STAT_INSERT || $status == STAT_RETURN ) )
    {      
      $isReadonly1   = false;
    }
    // Ir pieejams main??anai, ja  �Teko?ais lietot?js� ir Sist?mas administrators 
    if($isAdmin && ($status == STAT_INSERT || $status == STAT_RETURN ) )
    {	
      $isReadonlyExceptAdmin   = false;
    }
	
    //Ir pieejams main??anai, ja   Teko?a lietot?ja loma = �Ekonomists�  un AKTS:STATUS = �Saska?o?ana�.
    if($isEconomist && $status == STAT_ACCEPT )
    {
      $isReadonlyExceptEconomist   = false;
    }
  }
  else
  {
    if($isAdmin){
      $isReadonly   = false;	 
      $isReadonlyExceptAdmin = false; 
    }  
  }

  // form elements  
  $oForm -> addElement('hidden', 'isSearch', '', $isSearch);
  $oForm -> addElement('hidden', 'searchNum', '', $searchNum);
  $oForm -> addElement('hidden', 'action', '');
  $oForm -> addElement('hidden', 'actId', null, isset($act['RAKT_ID'])? $act['RAKT_ID']:'');
  $oForm -> addElement('hidden', 'status', null, $status);
  $oForm -> addElement('label', 'statusTxt',  text::get('STATUS'), $statusLabel);
  $oForm -> addElement('hidden', 'actNumber',  '', isset($act['RAKT_NUMURS'])?$act['RAKT_NUMURS']:'');

  $oLink=new urlQuery();
  $oLink->addPrm(DONT_USE_GLB_TPL, 1);
  $oLink->addPrm(FORM_ID, 'f.akt.s.20');
  $oLink->addPrm('actId', $actId);
  $oLink->addPrm('worker', userAuthorization::getWorker() );
 
  if($actId != false)
  {
      $oForm -> addElement('label', 'actFullNumber',  text::get('ACT_NUMBER'), isset($act['RAKT_FULL_NUMBER'])?$act['RAKT_FULL_NUMBER']:''); 
  }  

  $oForm -> addElement('select', 'EDarea',  text::get('ED_AREA'), isset($act['RAKT_KEDI_ID'])?$act['RAKT_KEDI_ID']:'', ''.(($isReadonlyExceptAdmin )?' disabled':'').'', '', '', $edarea);
    
  $oForm -> addElement('select', 'ouner',  text::get('ACT_OUNER'), isset($act['RAKT_RLTT_ID'])?$act['RAKT_RLTT_ID']:'', ''.((!$isReadonlyExceptAdmin || !$isReadonly)? '' :' disabled').'', '', '', $ouner);
  
  if (!$isReadonlyExceptAdmin || !$isReadonly)
  {
    $oForm -> addRule('ouner', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }

  $oForm -> addElement('kls', 'worker',  text::get('SINGL_WORK_OWNER'), 
  array('classifName'=>KL_WORK_OWNERS,
        'value'=>isset($act['RAKT_KWOI_KODS'])?$act['RAKT_KWOI_KODS']:'',
        'readonly'=>false), 
        (($isReadonlyExceptAdmin) ? ' disabled' : '') . ' maxlength="2000" onChange="eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&worker=\'+this.value))"');

  $oForm -> addElement('text', 'numPostfix',  text::get('ACT_NUM_POSTFIX'), isset($act['RAKT_NUM_POSTFIX'])?$act['RAKT_NUM_POSTFIX']:'', 'maxlength="16" '.(($isReadonlyExceptAdmin )?' disabled':''));

  $oForm -> addElement('text', 'worktitle',  text::get('PRINT_WORK_TITLE'), isset($act['RAKT_WORK_TITLE'])?$act['RAKT_WORK_TITLE']:'', 
                        'tabindex=6 maxlength="250"'.(($isReadonlyExceptAdmin)?' disabled':''));
  
  $oForm -> addElement('text', 'year',  text::get('YEAR'), isset($act['RAKT_GADS'])?$act['RAKT_GADS']:'', 
                        'tabindex=6 maxlength="4"'.(($isReadonlyExceptAdmin)?' disabled':''));
  if (!$isReadonlyExceptAdmin)
  { 
        $oForm -> addRule('EDarea', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('worker', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('numPostfix', text::get('ERROR_REQUIRED_FIELD'), 'required');
        $oForm -> addRule('worktitle', text::get('ERROR_REQUIRED_FIELD'), 'required');       
        $oForm -> addRule('year', text::get('ERROR_REQUIRED_FIELD'), 'required');
  }
  
  // form buttons
  if (!$isReadonlyExceptAdmin || !$isReadonly)
  {
    $oForm -> addElement('submitImg', 'save', text::get('SAVE'), 'img/btn_saglabat_g.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')) {setValue(\'action\',\''.OP_UPDATE.'\');} else {setValue(\'action\',\''.OP_INSERT.'\');}"');

  }
  if (!$isReadonly)
  {

    $oForm -> addElement('clearImg', 'clear', text::get('CLEAR'), 'img/btn_attirit.gif', 'width="70" height="20"','','',array('onClick'=>'refreshField();'));
    $oForm -> addElement('static', 'jsButtonsControl', '', '
			<script>
				function refreshField()
				{

                    document.all["status"].value = "'.$status.'";
				}
				refreshField();

			</script>
		');

  }
  if (!$isReadonly1 && ($actId != false))
  {
    $oForm -> addElement('submitImg', 'export', text::get('EXPORT'), 'img/btn_nodot_saskanosanai.gif', ' height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\') && isDeleteWithMessage(\''.text::get('WARNING_EXPORT').'\')) {setValue(\'action\',\''.OP_EXPORT.'\');} else {return false;}"');
  }
  
  if (!$isReadonlyExceptEconomist)
  {
    $oForm -> addElement('submitImg', 'return', text::get('RETURN'), 'img/btn_atgriezt.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_RETURN').'\')) {setValue(\'action\',\''.OP_RETURN.'\');} else {return false;}"');
    $oForm -> addElement('submitImg', 'accept', text::get('ACCEPT'), 'img/btn_apstiprinat.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_ACCEPT').'\')) {setValue(\'action\',\''.OP_ACCEPT.'\');} else {return false;}"');
  }

  if ($isAdmin && ($actId != false) && ($status == STAT_DELETE || $status == STAT_CLOSE))
  {
    $oForm -> addElement('submitImg', 'return', text::get('RETURN'), 'img/btn_atgriezt.gif', 'width="70" height="20" onclick="if (!isEmptyFormField(\'frmMain\',\'actId\')&& isDeleteWithMessage(\''.text::get('WARNING_RETURN').'\')) {setValue(\'action\',\''.OP_RETURN_CONFIRMED.'\');} else {return false;}"');
  }
  if($actId != false)
  {
      // back button
      // act advanced search form
    	$oLink=new urlQuery();
    	$oLink->addPrm('isSearch', $isSearch);
      $oLink->addPrm('selectedId', ($isSearch == 1 || $isSearch == 3)?$actId : $searchNum);
    	$oLink->addPrm(FORM_ID, 'f.akt.s.9');
    	$actSearchLink=$oLink ->getQuery();
    	unset($oLink);
        // list of acts
    	$oLink=new urlQuery();
      $oLink->addPrm('isNumber', ($isSearch == 1 || $isSearch == 3)? 0 : $searchNum);
      $oLink->addPrm('selectedId', $actId);
      $oLink->addPrm('isProject', 1);
    	$oLink->addPrm(FORM_ID, 'f.akt.s.9');
    	$actListLink=$oLink ->getQuery();
    	unset($oLink);
        $oForm -> addElement('static', 'jsBackButtons', '', '
    			<script>
    			    function reloadBack()
                    {
                        parent["frameTop"].enableFrameControl();
                        window.top.enableResize();
                        window.top.normal();
                        reloadFrame(1,"'.$actSearchLink.'");
                        reloadFrame(2,"'.$actListLink.'");
                        reloadFrame(3,"");
                    }
    			</script>
    		');
      $oForm -> addElement('buttonImg', 'back', text::get('BACK'), 'img/btn_atpakal.gif', 'width="70" height="20" onClick="reloadBack();"');
  }
  

  if ($oForm -> isFormSubmitted())
  {
    if ($oForm->getValue('action')==OP_INSERT ||
        ($oForm->getValue('action')==OP_UPDATE  && is_numeric($oForm->getValue('actId'))) ||
        ($oForm->getValue('action')==OP_EXPORT && is_numeric($oForm->getValue('actId'))) 
        )
	  {
         $check = true;
    	    $r = false;
          $r1 = true;
          $r2 = true;
          $checkRequiredFields = false;
         
         $actNumber = false;
         if (($isEditor ||$isAdmin) && $oForm -> getValue('status') && $oForm -> getValue('EDarea') &&
             $oForm -> getValue('year')  &&  $oForm -> getValue('worker') &&  $oForm -> getValue('numPostfix') 
            )
    	{
          $checkRequiredFields = true;
    	}

        if ($isAdmin  && !$oForm -> getValue('ouner')  )
        {
              $checkRequiredFields = false;
        }

        // if all is ok, do operation
		  if($check)
		  {
		        // save
            if($oForm->getValue('action')==OP_INSERT || $oForm->getValue('action')==OP_UPDATE)
            {
                $r=dbProc::saveAct(($oForm->getValue('action')==OP_UPDATE?$oForm->getValue('actId'):false),
                false,
                ($oForm->getValue('action')==OP_INSERT)?0:false,
                date_create($oForm->getValue('year').'-01-01')->format('d.m.Y'), 
                0,
                false,
                false,
                false,
                $oForm->getValue('status'),
                ($oForm->getValue('ouner'))? $oForm->getValue('ouner'):$userId,
                false,
                false,
                false,
                $oForm->getValue('worker'),
                $oForm->getValue('EDarea'),
                1 ,
                0,
                $oForm->getValue('numPostfix'),
                $oForm->getValue('worktitle'),
                false,
                false,
                false,
                false,
                1,
                1
              );

              // get inserted record ID
              if($oForm->getValue('action')==OP_INSERT)
              {
                  $actId=dbLayer::getInsertId();
                  // saglaba lietotaja darbiibu
                  dbProc::setUserActionDate($userId, ACT_INSERT);
              }
              else
              {
                  $actId =  $oForm->getValue('actId');
                  // saglaba lietotaja darbiibu
                  dbProc::setUserActionDate($userId, ACT_UPDATE);
              }

              // save status changed time
              if($oForm->getValue('action')==OP_INSERT)
              {
                $r1 = dbProc::saveAuditRecord($actId, $userId, $oForm->getValue('status'));
              }
              if (!$r || !$r1 )
              {
                $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
              }
            }
            
            // export
            if($oForm->getValue('action')==OP_EXPORT )
            {
                $r=dbProc::saveAct($oForm->getValue('actId'),
                            false,
                            false,
                            false,
                            0,
                            false,
                            false,
                            false,
                            $oForm->getValue('status'),
                            ($oForm->getValue('ouner'))? $oForm->getValue('ouner'):$userId,
                            false,
                            false,
                            false,
                            $oForm->getValue('worker'),
                            $oForm->getValue('EDarea'),
                            1,
                            0,
                            $oForm->getValue('numPostfix'),
                            $oForm->getValue('worktitle'),
                            false,
                            false,
                            false,
                            false,
                            1,
                            1
                );

                if ($r )
                {
                  // get info about voltage
                  $actInfo = dbProc::getActInfo($oForm->getValue('actId'));
                  if(count($actInfo)>0)
                  {
                      $act = $actInfo[0];
                      $regionName = dbProc::GetRefionName($act['RAKT_KEDI_ID']);
                      $departmentName = dbProc::GetDepartmentName($act['RAKT_KEDI_ID']);
                  }
                  if( $oForm->getValue('action')==OP_EXPORT )
                  {
                    // akta sagatavi (tab tamme)
                    $pdf=new FPDF();
                    $pdf->AddFont('Arial','','arial.php');
                    $pdf->AddFont('Arial','BI','arialbi.php');
                    $pdf->AddFont('Arial','I','ariali.php');
                    $pdf->AddFont('Arial','B','arialbd.php');
                    $pdf->SetDisplayMode('real');
                    $pdf->SetAutoPageBreak(true,20);
                    $pdf->AliasNbPages();
                    $pdf->SetTitle(iconv('UTF-8', 'windows-1257',text::get('PROJECT_HEADER').' '.$act['NUMURS']));
                    $pdf->SetLeftMargin(20);
                    $pdf->AddPage();
                    $pdf->SetFont('Arial','B',10);
                    $pdf->Cell(0,0,iconv('UTF-8', 'windows-1257',text::get('PROJECT_HEADER')), 0,1,'C');
  
  
                    // Create new PHPExcel object
                    $objPHPExcel = new PHPExcel();
  
                    // create act header
                    $actHeader= array(
                      array(
                        array('', 'L', '', 8),
                        array('', 'L', '', 8)
                            ) ,
                      array(
                        array('', 'L', '', 8),
                        array('', 'L', '', 8)
                            ) ,
                      array(
  
                        array(iconv('UTF-8', 'windows-1257',dtime::dateToLvStringEmpty(date('d.m.Y'))), 'L', '', 8),
                        array(iconv('UTF-8', 'windows-1257',text::get('NUMBER_SIMBOL').'. '.$act['NUMURS']), 'R', 'B', 10)
                            ),
                      array(
                        array('', 'L', '', 8),
                        array('', 'L', '', 8)
                            ) ,
                      /*array(
                        array(iconv('UTF-8', 'windows-1257',text::get('TRASE_ACT_HEADER5')), 'L', '', 8),
                        array('', 'L', '', 8)
                            ),*/
                      array(
                        array('', 'L', '', 8),
                        array('', 'L', '', 8)
                            ) ,
                      array(
                        array(iconv('UTF-8', 'windows-1257',text::get('REPORT_WORK_OFFER').':'), 'L', '', 8),
                        array(iconv('UTF-8', 'windows-1257',text::get('REPORT_WORK_DONE').':'), 'L', '', 8)
                            ) ,
                      array(
                        array(iconv('UTF-8', 'windows-1257',text::get('ST_COMPANY_NAME').', '.text::get('REGISTRATION_SIMBOL').'. '.text::get('NUMBER_SIMBOL').': '.text::get('ST_REG_NR')), 'L', 'B', 8),
                        array(iconv('UTF-8', 'windows-1257',$act['WORKER'].', '.text::get('REGISTRATION_SIMBOL').'. '.text::get('NUMBER_SIMBOL').': '.$act['KWOI_KODS']), 'L', 'B', 8)
                            ),                     
                      array(
                        array(iconv('UTF-8', 'windows-1257', $regionName.' '.text::get('REPORT_DEPARTMENT')), 'L', 'B', 8),
                        array('', 'L', '', 8)
                            ) ,
                      array(
                        array(iconv('UTF-8', 'windows-1257',$act['KEDI_SECTION']), 'L', 'B', 8),
                        array('', 'L', '', 8)
                            ) ,
                      array(
                        array(iconv('UTF-8', 'windows-1257',text::get('WORKS_AND_TERITORY').':'), 'L', '', 8),
                        array('', 'L', '',8)
                            ) ,
                      array(
                        array(iconv('UTF-8', 'windows-1257', $regionName.' '.text::get('REPORT_REGION')), 'L', 'B', 8),
                        array('', 'L', '', 8)
                            ) ,
                      array(
                        array(iconv('UTF-8', 'windows-1257',$act['KEDI_NOSAUKUMS'] ), 'L', 'B', 8),
                        array('', 'L', '', 8)
                            ) ,
                    ) ;
                    $pdf->HeaderStyledTable($actHeader);
  
                    $pdf->SetFont('Arial','BI',8);
                    $pdf->Cell(0,8,iconv('UTF-8', 'windows-1257', $act['WORK_TITLE']),0,1);
    
                    // darbi
                    $pdf->SetFont('Arial','BI',10);
                    $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',text::get(TAB_WORKS)), 0,1);
  
                    $width=array(15,75,15,20,55);
                    $alignHeader=array('C','C','R','L');
                    $align=array('C','C','R','L');
  
                    $headers = array(
                        'DRBI_KKAL_SHIFRS' => iconv('UTF-8', 'windows-1257',text::get('CHIPHER')),
                        'DRBI_KKAL_NOSAUKUMS' => iconv('UTF-8', 'windows-1257',text::get('EXPORT_CALCULATION_NAME')),
                        'DRBI_MERVIENIBA' => iconv('UTF-8', 'windows-1257',text::get('UNIT_OF_MEASURE')),
                        'DRBI_DAUDZUMS' => iconv('UTF-8', 'windows-1257',text::get('AMOUNT')),
                        'DRBI_PIEZIMES' => iconv('UTF-8', 'windows-1257',text::get('COMMENT'))
                        );
  
                    $aWorkDb=dbProc::getActWorkList($actId);
                    $data = array();
                    foreach ($aWorkDb as $i => $work)
                    {
                      $data[$i] = array(
                        'DRBI_KKAL_SHIFRS' => $work['DRBI_KKAL_SHIFRS'],
                        'DRBI_KKAL_NOSAUKUMS' => text::returnsplit(iconv('UTF-8', 'windows-1257',$work['DRBI_KKAL_NOSAUKUMS']),  2, "\n", 60),
                        'DRBI_MERVIENIBA' => iconv('UTF-8', 'windows-1257',$work['DRBI_MERVIENIBA']),                        
                        'DRBI_DAUDZUMS' => $work['DRBI_DAUDZUMS'],
                        'DRBI_PIEZIMES' => text::returnsplit(iconv('UTF-8', 'windows-1257',$work['DRBI_PIEZIMES']),  2, "\n", 60)
                        );
                    }
                    $pdf->FancyTableTrase($headers,$data, $width, $align, $alignHeader);

                    // materiali                   
                    $pdf->SetFont('Arial','BI',10);
                    $pdf->Cell(0,10,iconv('UTF-8', 'windows-1257',text::get(TAB_MATERIAL)), 0,1);

                    $width=array(20,80,20,20,40);
                    $alignHeader=array('C','C','C','R','L');
                    $align=array('C','L','C','R','L');

                    $headers = array(
                        'MATR_KODS' => iconv('UTF-8', 'windows-1257',text::get('CODE')),
                        'MATR_NOSAUKUMS' => iconv('UTF-8', 'windows-1257',text::get('NAME')),
                        'MATR_MERVIENIBA' => iconv('UTF-8', 'windows-1257',text::get('UNIT_OF_MEASURE')),
                        'MATR_DAUDZUMS' => iconv('UTF-8', 'windows-1257',text::get('AMOUNT')),
                        'MATR_PIEZIMES' => iconv('UTF-8', 'windows-1257',text::get('COMMENT'))
                        );

                    $aMaterialDb=dbProc::getActMaterialList($actId);
                    $data = array();
                    foreach ($aMaterialDb as $i => $material)
                    {
                      $data[$i] = array(
                        'MATR_KODS' => $material['MATR_KODS'],
                        'MATR_NOSAUKUMS' => text::returnsplit(iconv('UTF-8', 'windows-1257',$material['MATR_NOSAUKUMS']),  2, "\n", 60),
                        'MATR_MERVIENIBA' => iconv('UTF-8', 'windows-1257',$material['MATR_MERVIENIBA']),
                        'MATR_DAUDZUMS' => $material['MATR_DAUDZUMS'],'MATR_CENA' => $material['MATR_CENA'],
                        'MATR_PIEZIMES' => text::returnsplit(iconv('UTF-8', 'windows-1257',$material['MATR_PIEZIMES']),  2, "\n", 60)
                        );
                    }
                    $pdf->FancyTableTrase($headers,$data, $width, $align, $alignHeader);
                   
                    $rows=dbProc::getUserInfo($userId);
                    if (count($rows)==1)
                    {
                      $actAutorName =  $rows[0]['RLTT_VARDS'].' '.$rows[0]['RLTT_UZVARDS'];
                    }
  
  
                    $actFooter = array(
                      array(
                        '',
                        ''
                          ),
                      array(
                        '',
                        ''
                          ),
                    array(
                      iconv('UTF-8', 'windows-1257',text::get('ACT_CREATER').': '.$act['AUTORS']),
                      ''
                        ),
                      array(
                      iconv('UTF-8', 'windows-1257',text::get('DATE').': '.date('d.m.Y')),
                      iconv('UTF-8', 'windows-1257',text::get('IS_NOT_ENDORSED'))
                        ),
                      array(
                      iconv('UTF-8', 'windows-1257',''),
                      iconv('UTF-8', 'windows-1257','')
                          ),                     
                      array(
                      iconv('UTF-8', 'windows-1257',$act['WORKER']),
                    ''
                        ),
                      array(
                      iconv('UTF-8', 'windows-1257',$act['AUTORS']),
                      ''
                        )
                      );
                    $pdf->FooterTablePortraitAsimetrikal($actFooter);
                    
                }

                // saglaba faila datus
                $res=dbProc::replaceFile(
                    'P'.
                    $act['NUMURS'].'_'.dtime::now().'.'.EXPORT_FILE_EXTENTION,
                    $userId, $actId,
                    FILE_EXPORT,
                    EXPORT_FILE_TYPE);
                
                if ($res)
                {
                  $idFile=dbLayer::getInsertId();
                }
                else
                {
                  $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                }
                if ($idFile!==false)
                {
                        $pdf->Output(FILES_STORE_PATH."/".$idFile, 'F');
    
                        // update act status
                        $r=dbProc::saveAct($oForm->getValue('actId'),
                                      false,false,false,false,false,false,
                                      true,
                                      STAT_ACCEPT,
                                      ($oForm->getValue('ouner'))? $oForm->getValue('ouner'):$userId,
                                      false,
                                      false,
                                      false,
                                      $oForm->getValue('worker'),
                                      $oForm->getValue('EDarea'),
                                      1,
                                      0,
                                      $oForm->getValue('numPostfix'),
                                      $oForm->getValue('worktitle'),
                                      false,
                                      false,
                                      false,
                                      false,
                                      1,
                                      1
                                    );
                        // save status changed time
                        $r1 = dbProc::saveAuditRecord($actId, $userId, STAT_ACCEPT);
                        // saglaba lietotaja darbiibu
                        dbProc::setUserActionDate($userId, ACT_EXPORT);
    
                  if (!$r || !$r1)
                  {
                    $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
                  }
                }
              }
              else
              {
                $oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
              }
            }
      }
      // if operation was compleated succefully, show success mesage and redirect current frame
		  if ($r)
		  {
          $oLink=new urlQuery();
          $oLink->addPrm(FORM_ID, 'f.akt.s.20');
          $oLink->addPrm('actId', $actId);
          $oLink->addPrm('isSearch', $isSearch);
          $oLink->addPrm('searchNum', $searchNum);
          switch($oForm->getValue('action'))
          {
            case OP_INSERT:
              $oLink->addPrm('successMessage', text::get('RECORD_WAS_ADDED'));
              break;
            case OP_UPDATE:
              $oLink->addPrm('successMessage', text::get('RECORD_WAS_SAVED'));
              break;
            case OP_EXPORT:
              $oLink->addPrm('successMessage', text::get('INFO_WAS_EXPORTED'));
              $oLink->addPrm('tab', TAB_EXPORT);
              break;
           
              }
            RequestHandler::makeRedirect($oLink->getQuery());
        }
    }
	 else
	 {
	  	$oForm->addError(text::get('ERROR_NO_ALL_INPUT_DATES'));
	 }
  }
  if (($oForm->getValue('action')==OP_RETURN && is_numeric($oForm->getValue('actId'))) ||
          ($oForm->getValue('action')==OP_ACCEPT && is_numeric($oForm->getValue('actId'))) )
	{
       	 $r = false;
         $r1 = true;
       	 $checkRequiredFields = false;
  
    }

    $oForm -> makeHtml();
    include('f.akt.s.20.tpl');

    $tabs = new tabs("akts", "");

    $tabs->start(text::get(TAB_WORKS));
    include('f.akt.s.21.inc');
    $tabs->end();
   
  	$tabs->start(text::get(TAB_MATERIAL));
    include('f.akt.s.22.inc');
    $tabs->end();  
  
    $tabs->start(text::get(TAB_EXPORT));
    include('f.akt.s.10.inc');
    $tabs->end();

    $tabs->start(text::get(TAB_AUDIT));
    include('f.akt.s.7.inc');
    $tabs->end();
    
    $tabs->active = text::get($tab);

    $tabs->run();

}
else
{
    RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>