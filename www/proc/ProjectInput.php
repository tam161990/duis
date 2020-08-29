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
	// if you are doing ajax with application-json headers
	try
	{
		$data = json_decode(file_get_contents("php://input")) ? : 'nifiga net';	

		files::wh_log('New project input: ' .date("d.m.Y H:i:s").PHP_EOL. 
									'year: '.$data->year.PHP_EOL.
									'worker: '. (isset($data->worker) ? $data->worker : '').PHP_EOL.
									'EDarea: '.(isset($data->EDarea) ? $data->EDarea : '').PHP_EOL.
									'numPostfix:' .(isset($data->numPostfix) ? $data->numPostfix :'').PHP_EOL.
									'worktitle:' .(isset($data->worktitle) ? $data->worktitle :'').PHP_EOL.
									'type:' .(isset($data->type) ? $data->type :'').PHP_EOL
							);						
		//var_dump($data);
		
		$r=dbProc::saveAct(false,
			false,
			0,
			date_create(isset($data->year) ? $data->year : date("Y").'-01-01')->format('d.m.Y'), 
			0,
			false,
			false,
			false,
			STAT_AUTO,
			MAIN_ADMIN_ID,
			false,
			false,
			false,
			isset($data->worker) ? $data->worker : false,
			isset($data->worEDareaker) ? $data->EDarea : false,
			1 ,
			0,
			isset($data->numPostfix) ? $data->numPostfix : false,
			isset($data->worktitle) ? $data->worktitle : false,
			false,
			false,
			false,
			false,
			1,
			1,
			isset($data->type) ? $data->type : false
		  );	
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