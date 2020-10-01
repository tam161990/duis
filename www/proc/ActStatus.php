<?
    require_once('../libs/init.inc');
        
	
    function json_response($code = 200, $message = null)
	{
		// clear the old headers
		header_remove();
		// set the actual code
		http_response_code($code);
		// set the header to make sure cache is forced
		header("Cache-Control: no-transform,public,max-age=300,s-maxage=900");
		// treat this as json
		header('Content-Type: application/json');
		$status = array(
			200 => '200 OK',
			400 => '400 Bad Request',
			422 => 'Unprocessable Entity',
			500 => '500 Internal Server Error'
			);
		// ok, validation error, or failure
		header('Status: '.$status[$code]);
		// return the encoded json
		return json_encode([ 
			'status' => $code < 300, // success or not?
			'message' => $message
			]);
	}
	ob_start();
	$r = false;
	try
	{
		// if you are doing ajax with application-json headers
		$data = json_decode(file_get_contents("php://input")) ? : 'nifiga net';	

		//var_dump($data);
		if( isset($data->issue_key) && !empty($data->issue_key) )
		{

			files::wh_log('Act status from KS: ' .date("d.m.Y H:i:s").PHP_EOL. 
										'issue_key: '.$data->issue_key.PHP_EOL.
										'issue_status: '. ((isset($data->issue_status) && !empty($data->issue_status)) ? $data->issue_status : '').PHP_EOL.
										'issue_assignee: '.((isset($data->issue_assignee) && !empty($data->issue_assignee)) ? $data->issue_assignee : '').PHP_EOL.
										'issue_end_date:' .((isset($data->issue_end_date) && !empty($data->issue_end_date))? $data->issue_end_date :'').PHP_EOL.
										'issue_accept_date:' .((isset($data->issue_accept_date) && !empty($data->issue_accept_date)) ? $data->issue_accept_date :'').PHP_EOL
								);						
		
			
			//var_dump($data);
			$r = dbProc::saveKvikStepActStatus($data->issue_key, 
										isset($data->issue_status) && !empty($data->issue_status) ? $data->issue_status : false, 
										isset($data->issue_assignee) && !empty($data->issue_assignee) ? $data->issue_assignee : false,
										isset($data->issue_end_date) && !empty($data->issue_end_date) ? substr($data->issue_end_date, 0, 10) : false,
										isset($data->issue_accept_date) && !empty($data->issue_accept_date) ? substr($data->issue_accept_date, 0, 10) : false
										);	
			
			$response = ob_get_clean();	
		}	
		else {
			$err_message = "issue_key not set";
		}
	}
	catch(Throwable $e) {

		//$trace = $e->getTrace();
		$err_message = $e->getMessage().' in '.$e->getFile().' on line '.$e->getLine();
			
	}	

		$response = ob_get_clean();	
	if( $r !== false ) {
		$response = json_response(200, "OK");
	} else {
		$response = json_response(500, "NOK: ".$err_message);
	}

		
	echo $response;
	
	
?>