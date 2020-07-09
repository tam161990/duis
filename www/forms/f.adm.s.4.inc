<?
//created by Tatjana Fedorkova
$userId = userAuthorization::getUserId();

if (reqVar::get('xmlHttp') == 1)
{
	// http://mithrandir.ru/professional/php/php-daemons.html
	// chech process 
	// ps -aux
	if (reqVar::get('state') !== false && reqVar::get('code') != false)
	{
		$state  = reqVar::get('state');
		$code = reqVar::get('code');
		switch ($state) {
			// start
			case 1:
				$jobInfo = dbProc::getJobList($code);
				if(count($jobInfo)>0)
				{
					$command = $jobInfo[0]['PROC_KOMANDA'];
					//$command = 'php -f /u01/rcd-test/autoProc/updateActStatus.php';
					$process = new Process($command);
					$processId = $process->getPid();
					$status = $process->status(); // возвращает true или false
					if($status) {
						$r=dbProc::saveJob( $code, $processId, 1);
					}
				}
			
				//echo "PID: " . $processId . " status: " . (($status)? "RUNNIG" : "STOPED");
				break;
			// stop
			case 2:
				
				$process = new Process();
				$process->setPid($processId); 
				$status = $process->status(); // возвращает true или false
				//echo "PID: " . $processId . " status: " . (($status)? "RUNING" : "STOPED");
				$stopped = $process->stop();
				$status = $process->status(); // возвращает true или false
				//echo "PID: " . $processId . " status: " . (($status)? "RUNNIG" : "STOPED");
				break;
			// ststus
			case 3:
				
				$process = new Process();
				$process->setPid($processId); 
				$status = $process->status(); // возвращает true или false
				//echo "PID: " . $processId . " status: " . (($status)? "RUNNIG" : "STOPED");        
				break;
			default:
				//echo "chtoto poshlo ne tak";
				break;
		}
	}
	exit;
}
if (userAuthorization::isAdmin())
{
	$editMode = reqVar::get('editMode');
	// bottom frame
	// if insert/update

     if($editMode)
	{
		$jobCode = reqVar::get('jobCode');

		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.adm.s.4');
		$oLink->addPrm('editMode', 1 );
		// form inicialization
		$oForm = new Form('frmMain','post',$oLink->getQuery());
		unset($oLink);

		// if operation is success, show success message and redirect top frame
		if (reqVar::get('successMessage'))
		{
			$oForm->addSuccess(reqVar::get('successMessage'));
			$oForm->addElement('static','jsRefresh2','','<script>refreshFrame(1);</script>');
		}

		// inicial state: jobCode=0;
		// if jobCode>0 ==>  selected from the list
		if($jobCode != false)
		{
			// get info about voltage
			$jobInfo = dbProc::getJobList($jobCode);
			
			if(count($jobInfo)>0)
			{
				$job = $jobInfo[0];
			}
        }

		// form elements
		$oForm -> addElement('hidden', 'action', '');
		$oForm -> addElement('hidden', 'jobCode', null, isset($job['PROC_KODS'])? $job['PROC_KODS']:'');

		$oForm -> addElement('text', 'nosaukums',  text::get('SYSTEM_PROCESS_TITLE'), isset($job['PROC_NOSAUKUMS'])?$job['PROC_NOSAUKUMS']:'', 'maxlength="150"'.((true)?' disabled' : ''));
		
        $oForm -> addElement('text', 'comand',  text::get('SYSTEM_PROCESS_COMAND'), isset($job['PROC_KOMANDA'])?$job['PROC_KOMANDA']:'', 'maxlength="150"' . ((true)?' disabled' : ''));
		
		$oForm -> addElement('text', 'pid',  text::get('SYSTEM_PROCESS_PID'), isset($job['PROC_PID'])?$job['PROC_PID']:'', 'maxlength="30"'.((true)?' disabled' : ''));

		$oForm -> addElement('text', 'start',  text::get('SYSTEM_PROCESS_START'), isset($job['PROC_START_DATUMS'])?$job['PROC_START_DATUMS']:'', 'maxlength="30"'.((true)?' disabled' : ''));

		$oForm -> addElement('text', 'end',  text::get('SYSTEM_PROCESS_STOP'), isset($job['PROC_STOP_DATUMS'])?$job['PROC_STOP_DATUMS']:'', 'maxlength="30"'.((true)?' disabled' : ''));
        
		$oForm -> addElement('checkbox', 'isActive',  text::get('IS_ACTIVE'), isset($job['PROC_IR_AKTIVS'])?$job['PROC_IR_AKTIVS']:0, ''.((true)?' disabled' : ''));

		$oForm -> addElement('text', 'interval',  text::get('SYSTEM_PROCESS_INTERVAL'), isset($job['PROC_INTERVAL'])?$job['PROC_INTERVAL']:'300', ''.((false)?' disabled' : ''));
		$oForm -> addRule('interval', text::get('ERROR_REQUIRED_FIELD'), 'required');
		$oForm -> addRule('interval', text::get('ERROR_NUMERIC_VALUE'), 'numeric');
        
		
		// form buttons
        if(true)
        {
			 // xmlHttp link
			$oLink=new urlQuery();
			$oLink->addPrm(DONT_USE_GLB_TPL, 1);
			$oLink->addPrm(FORM_ID, 'f.adm.s.4');
			$oLink->addPrm('editMode', 1);

			$oForm -> addElement('submitImg', 'run', text::get('RUN'), 'img/btn_run.png', 'width="70" height="20" onclick=" if (!document.all[\'isActive\'].checked) {setValue(\'action\',\''.OP_JOB_RUN.'\');
				eval(xmlHttpGetValue(\''.$oLink->getQuery().'&xmlHttp=1&state=1&code=\'+document.all[\'jobCode\'].value));} else {return false;}"');
				
			unset($oLink);
			$oForm -> addElement('submitImg', 'stop', text::get('KILL'), 'img/btn_kill.png', 'width="70" height="20" onclick="if (document.all[\'isActive\'].checked) {setValue(\'action\',\''.OP_JOB_KILL.'\');} else {return false;}"');
			
			$proc_status = false;
			if(isset($job['PROC_PID']))
			{
				$proc = new Process();
				$proc->setPid($job['PROC_PID']); 
				$proc_status = $proc->status(); // возвращает true или false
			}
			$oForm -> addElement('submitImg', 'delete', text::get('DELETE'), 'img/btn_dzest'.(($proc_status) ? '_disabled' : '').'.gif', 'width="70" height="20" onclick="if (!isEmptyField(\'jobCode\') && isDeleteWithMessage(\''.text::get('WARNING_DELETE_ROW').'\')) {setValue(\'action\',\''.OP_DELETE.'\');} else {return false;}"');


         	$oForm -> addElement('static', 'jsButtonsControl', '', '
    			<script>
    				function refreshButton(name)
    				{
						
    					if (document.all[name].checked)
    					{
							document.all["run"].src="img/btn_run_disabled.png";
							document.all["stop"].src="img/btn_kill.png";    			
    						
    					}
    					else
    					{
							document.all["run"].src="img/btn_run.png";
							document.all["stop"].src="img/btn_kill_disabled.png";			
    					}
    				}
    				refreshButton("isActive");
    			</script>
    		');
        }
		// if operation
		if ($oForm -> isFormSubmitted())
		{
			
			$r = false;

			// delete
            if ($oForm->getValue('action')== OP_DELETE && $oForm -> getValue('jobCode') )
            {
				$r=dbProc::saveJob( $oForm->getValue('jobCode'),false,0 );

				if (!$r)
				{
					$oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
				}
			}			
			
			$checkRequiredFields = false;
			if ($oForm -> getValue('interval')  )
			{
				$checkRequiredFields = true;
			}
			if ($checkRequiredFields)
			{
				
				// save
				if ($oForm->getValue('action')==OP_JOB_RUN || ($oForm->getValue('action')==OP_JOB_KILL  && $oForm->getValue('jobCode')))
				{
					$jobOk = true;
					
					// get info about voltage
					$jobInfo = dbProc::getJobList($oForm->getValue('jobCode'));
					
					if(count($jobInfo)>0)
					{
						$processId = $jobInfo[0]['PROC_PID'];
					}

					// if all is ok, do operation
					if(true)
					{
						
					$r=dbProc::saveJob( $oForm->getValue('jobCode'),
											(($oForm->getValue('action')==OP_JOB_RUN)?$processId : $oForm->getValue('pid')),
											(($oForm->getValue('action')==OP_JOB_RUN)?1:0),
											$oForm->getValue('interval')
										   );
										   
										  //dbProc::updateActStatusFromKvikStep();
						if (!$r)
						{
							$oForm->addError(text::get('ERROR_IN_DB_QUERY').dbProc::getError());
						}
					}
				}


				// if operation was compleated succefully, show success mesage and redirect current frame
				if ($r)
				{
					$oLink=new urlQuery();
					$oLink->addPrm(FORM_ID, 'f.adm.s.4');
					$oLink->addPrm('editMode', '1');
					switch($oForm->getValue('action'))
					{
						case OP_JOB_RUN:
							$oLink->addPrm('successMessage', text::get('SYSTEM_PROCESS_RUNNING'));
							break;
						case OP_JOB_KILL:
							$oLink->addPrm('successMessage', text::get('SYSTEM_PROCESS_KILLED'));
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

       	$oForm -> makeHtml();
		include('f.adm.s.4.2.tpl');
	}
	// top frale
	else
	{
        // Check if this form was requested via xmlHttpRequest and search
    	if (isset($_GET['xml']) && isset($_GET['search_q']) && isset($_GET['search_c']))
    	{
    		ob_clean();
    		$q = $_GET['search_q'];
            if (isset($q) || $q == 0)
    		{
    			echo 'q = "'.trim($q).'";';
    		}
            else
            {
    			echo 'q = "";';
    		}
            $c = $_GET['search_c'];
            if ($c)
    		{
    			echo 'c = "'.$c.'";';
    		}
            else
            {
    			echo 'c = "";';
    		}
		    exit;
    	}
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
        // set list title
        $title = text::toUpper(text::get('SYSTEM_PROCESS'));
        // get search column list
        $columns=dbProc::getKlklName(KL_SYSTEM_PROCESS);
        $searchText = ((reqVar::get('search') && reqVar::get('search') != '') || reqVar::get('search') == 0) ? reqVar::get('search') : false;
        $searchColumn = (reqVar::get('column') && reqVar::get('column') != '') ? reqVar::get('column') : false;
        $sortOrder = (reqVar::get('order') && reqVar::get('order') != '') ? reqVar::get('order') : false;
        $orderColumn = (reqVar::get('kol') && reqVar::get('kol') != '') ? reqVar::get('kol') : false;


        // default sort column
        $defaultColumn = dbProc::getKlklDefaultColumn(KL_SYSTEM_PROCESS);

        // URL to search Zinojums by number.
    	$oLink = new urlQuery;
    	$oLink -> addPrm(FORM_ID, 'f.adm.s.4');
    	$oLink->addPrm('isNew', '1');

        // add search/order params to listing
        $oLink->addPrm('search', reqVar::get('search'));
        $oLink->addPrm('column', reqVar::get('column'));
        $oLink->addPrm('order', reqVar::get('order'));
        $oLink->addPrm('kol', reqVar::get('kol'));
        $searchLink = $oLink -> getQuery();

		// inicialising of listing object
		$amount=dbProc::getJobCount($searchText,
                (($searchColumn === false) ? $defaultColumn : $searchColumn));
		$listing=new listing();
		$listing->setAmount($amount);

		$listingHtml=$listing->getHtml($oLink ->getQuery());
		unset($oLink);

		//link for frame2
		$oLink=new urlQuery();
		$oLink->addPrm(FORM_ID, 'f.adm.s.4');
		$oLink->addPrm('editMode', 1);

		// gel list of users
		$res = dbProc::getJobList( false,
                                        $listing->getStartPosition(),
                                        $listing->getAmountOnPage(),
                                        $searchText,
                                        (($searchColumn === false) ? $defaultColumn : $searchColumn),
                                        $sortOrder,
                                        $orderColumn);

		if (is_array($res))
		{
			foreach ($res as $i=>$row)
			{
				// add dv area Id to each link
				$oLink->addPrm('jobCode', $row['PROC_KODS']);
				$res[$i]['URL']=$oLink ->getQuery();
			}
		}
		unset($oLink);

		// inicial state of users number
		$number=$listing->getStartPosition()+1;

		include('f.ktl.s.x.1.tpl');
	}
}
else
{
	RequestHandler::showErrorAndDie(text::get('ERROR_NOT_PERMISSION'));
}
?>
