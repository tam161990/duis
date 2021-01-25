<?
set_error_handler("errorHandler");
register_shutdown_function("shutdownHandler");

function errorHandler($error_level, $error_message, $error_file, $error_line, $error_context)
{
    $error = "lvl: " . $error_level . " | msg:" . $error_message . " | file:" . $error_file . " | ln:" . $error_line;
    switch ($error_level) {
        case E_ERROR: //1
        case E_CORE_ERROR: //16
        case E_COMPILE_ERROR://64
        case E_PARSE: //4
            mylog($error, "fatal", $error_file);
            break;
        case E_USER_ERROR: //256
        case E_RECOVERABLE_ERROR: //4096
            mylog($error, "error", $error_file);
            break;
        //case E_WARNING: //2
        case E_CORE_WARNING://22
        case E_COMPILE_WARNING://128
        case E_USER_WARNING: //512
            mylog($error, "warn", $error_file);
            break;
        case E_NOTICE: //8
        case E_USER_NOTICE: //1024
            mylog($error, "info", $error_file);
            break;
        case E_STRICT: //2048
            mylog($error, "debug", $error_file);
            break;
        default:
            //mylog($error, "warn", $error_file);
          
    }
    
}

function shutdownHandler() //will be called when php script ends.
{
$lasterror = error_get_last();
switch ($lasterror['type'])
{
    case E_ERROR:
    case E_CORE_ERROR:
    case E_COMPILE_ERROR:
    case E_USER_ERROR:
    case E_RECOVERABLE_ERROR:
    case E_CORE_WARNING:
    case E_COMPILE_WARNING:
    case E_PARSE:
        $error = "[SHUTDOWN] lvl:" . $lasterror['type'] . " | msg:" . $lasterror['message'] . " | file:" . $lasterror['file'] . " | ln:" . $lasterror['line'];
        mylog($error, "fatal", $lasterror['file']);
}
}

function mylog($error, $errlvl, $filePath)
{
    //echo $error.'<br>';
    //echo $errlvl.'<br>';
    $filename = substr($filePath, -(strlen($filePath)- strrpos($filePath, '\\')-1));
    $filenameParts = explode('.', $filename);

    dbProc::saveEvent((($errlvl == "fatal") ? 'C' : 'W'), 
                        ((dbProc::isModuleExist($filenameParts[0])) ? $filenameParts[0] : $filenameParts[1]), 
                        false, 
                        false, 
                        userAuthorization::getUserId(), 
                        $filePath,
                        false, 
                        $error);
}
?>