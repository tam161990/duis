<?
// XMLHTTP handlers for dynamic content loading

$action = reqVar::get('action');

if($action == 'getRbfEmployeeVV')
{
	$employeeCode = reqVar::get('employeeCode');
	if(!empty($employeeCode))
	{
		$vvList = dbProc::getRbfEmployeeVVList($employeeCode);
		$result = array();
		foreach($vvList as $vv) {
			$result[] = array(
				'number' => $vv['RBDV_VV_NUMURS']
			);
		}
		header('Content-Type: application/json');
		echo json_encode($result);
	}
	exit;
}

if($action == 'getRbfVVTerritories')
{
	$vvNumber = reqVar::get('vvNumber');
	if(!empty($vvNumber))
	{
		$territories = dbProc::getRbfVVTerritories($vvNumber);
		$result = array();
		foreach($territories as $territory) {
			$result[] = array(
				'id' => $territory['RBTR_ID'],
				'name' => $territory['RBTR_NOSAUKUMS']
			);
		}
		header('Content-Type: application/json');
		echo json_encode($result);
	}
	exit;
}

if($action == 'getUsersByEmployee')
{
	$employeeCode = reqVar::get('employeeCode');
	if(!empty($employeeCode))
	{
		$users = dbProc::getUsersList(false, false, false, $employeeCode, false, false, 'ASC', false);
		$result = array();
		foreach($users as $user) {
			$result[] = array(
				'id' => $user['RLTT_ID'],
				'name' => $user['RLTT_VARDS'] . ' ' . $user['RLTT_UZVARDS']
			);
		}
		header('Content-Type: application/json');
		echo json_encode($result);
	}
	exit;
}

// If no action matches, return error
header('HTTP/1.1 400 Bad Request');
echo json_encode(array('error' => 'Invalid action'));
exit;
?>

