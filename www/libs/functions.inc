<?
function getFileOutput( $file )
{
	ob_start();
	include( $file );
	$output = ob_get_contents();
	ob_end_clean();
	return $output;
}



?>