<?
require_once(dirname(__FILE__).'/../config/main.conf.php');  
require_once(dirname(__FILE__).'/../libs/dbLayer/dbLayer.class');
require_once(dirname(__FILE__).'/../libs/dbProc/dbProc.class');	
require_once(dirname(__FILE__).'/../libs/text/text.class');
require_once(dirname(__FILE__).'/../libs/requestHandler/requestHandler.class');
require_once(dirname(__FILE__).'/../libs/process/Process.class');  
require_once(dirname(__FILE__).'/../libs/files/files.class');
require_once(dirname(__FILE__).'/../libs/fpdf/fpdf.php');
require_once(dirname(__FILE__).'/../libs/export/toPdf.class');
require_once(dirname(__FILE__).'/../libs/export/toExcel.class');
require_once(dirname(__FILE__).'/../libs/datetime/dtime.class');
//require_once(dirname(__FILE__).'/../libs/errorhandling.php');
require_once(dirname(__FILE__).'/../libs/rbf/RbfActProcessor.class');

$processId;
$interval = 86400;

while(true) {
	try {
        // Create processor instance and run
        $processor = new RbfActProcessor();
        $processor->process();
        // Exit with appropriate code (1 if errors, 0 if success)
        exit($processor->hasErrors() ? 1 : 0);  // Exit successfully
	} catch (Exception $e) {        
		files::wh_log('RbfActProcessor: ' .date("d.m.Y H:i:s").PHP_EOL.$e->getMessage());						
	}   
    
    

    // get info about job
    $jobInfo = dbProc::getJobList(PROC_UPLOAD_RBF_DATA);			
    if(count($jobInfo)>0)
    {
        $processId = $jobInfo[0]['PROC_PID'];
        $interval = $jobInfo[0]['PROC_INTERVAL'];
        $isStoped = ($jobInfo[0]['PROC_IR_AKTIVS'] == 0) ? true  : false ;
    }
    // pārbaude, vai jobs nav apturēts
    if($isStoped) break;

    // Время сна Демона между итерациями (зависит от потребностей системы)
    sleep($interval); //sec   
}

$r=dbProc::saveJob(PROC_UPLOAD_RBF_DATA, false, 0, $interval);
// gadijumā, ja jobs ir bijis apturēts, nokilot arī procesu
$process = new Process();
$process->setPid($processId); 
$stopped = $process->stop();



?>