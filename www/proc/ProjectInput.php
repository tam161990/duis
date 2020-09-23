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
			/*issue_key			kods
			issue_status		status
			issue_type			tips
			issue_summary		saturs
			issue_designer		projketētājs
			issue_invest_year	investīciju gads
			issue_territory		atbildības teritorija*/

		files::wh_log('New project input: ' .date("d.m.Y H:i:s").PHP_EOL. 
									'issue_invest_year: '.$data->issue_invest_year.PHP_EOL.
									'issue_designer: '. (isset($data->issue_designer) ? $data->issue_designer : '').PHP_EOL.
									'issue_territory: '.(isset($data->issue_territory) ? $data->issue_territory : '').PHP_EOL.
									'issue_key:' .(isset($data->issue_key) ? $data->issue_key :'').PHP_EOL.
									'issue_summary:' .(isset($data->issue_summary) ? $data->issue_summary :'').PHP_EOL.
									'issue_type:' .(isset($data->issue_type) ? $data->issue_type :'').PHP_EOL
							);						
		//var_dump($data);
		
		$r=dbProc::saveAct(false,
			false,
			0,
			date_create(isset($data->issue_invest_year) ? $data->issue_invest_year : date("Y").'-01-01')->format('d.m.Y'), 
			0,
			false,
			false,
			false,
			STAT_AUTO,
			MAIN_ADMIN_ID,
			false,
			false,
			false,
			isset($data->issue_designer) ? $data->issue_designer : false,
			isset($data->issue_territory) ? $data->issue_territory : false,
			1 ,
			0,
			isset($data->issue_key) ? $data->issue_key : false,
			isset($data->issue_summary) ? $data->issue_summary : false,
			false,
			false,
			false,
			false,
			1,
			1,
			isset($data->issue_type) ? $data->issue_type : false
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