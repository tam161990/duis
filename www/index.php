<?

// created by Tatjana Fedorkova


// -----------------------------------------------------------------------------
// include libs
// -----------------------------------------------------------------------------
require_once('./libs/init.inc');

// -----------------------------------------------------------------------------
// if debug mode = true, saving start work time
// -----------------------------------------------------------------------------
if (DEBUG_MODE)
{
  	$startMicroTime=RequestHandler::getMicroTime();
}

// -----------------------------------------------------------------------------
// FrameWork run
// -----------------------------------------------------------------------------
ob_start();

RequestHandler::run();

$c=ob_get_contents();
ob_end_clean();
echo $c;

// -----------------------------------------------------------------------------
// if debug mode = true, show debug info
// -----------------------------------------------------------------------------
if (DEBUG_MODE)
{
	echo "\n\n\n".'<!--'."\n\n";
	echo $_SERVER['REQUEST_URI']."\n";
	echo RequestHandler::getMicroTime()-$startMicroTime."\n";
	echo "\n\n\n".'-->';
}

?>