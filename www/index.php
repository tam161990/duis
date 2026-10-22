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
// Check if already logged in
// -----------------------------------------------------------------------------
session::start();

// If not logged in, show simple login form
if (!userAuthorization::isLogin())
{
    // Check if login form submitted
    if (isset($_POST['login']) && isset($_POST['passw']))
    {
        if (userAuthorization::login($_POST['login'], $_POST['passw']))
        {
            setcookie(COOKIE_LOGIN, $_POST['login'], time()+60*60*24*30);
            header('Location: ?formId=fmk_main&fakeVar=');
            exit;
        }
        else
        {
            $loginError = true;
        }
    }
    
    // Show login form
    ?>
    <!DOCTYPE html>
    <html>
    <head>
        <meta charset="utf-8">
        <title>DUIS - Login</title>
        <link rel="stylesheet" href="/css/styles.css" type="text/css" />
    </head>
    <body style="display: flex; align-items: center; justify-content: center; height: 100vh; background: #f0f0f0;">
        <div style="background: white; padding: 30px; border-radius: 8px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); min-width: 300px;">
            <h2 style="margin: 0 0 20px 0; color: #333;">Darbuzņēmēju informācijas sistēma</h2>
            <?php if (isset($loginError)): ?>
                <div style="background: #ffebee; border: 1px solid #ef5350; padding: 10px; margin-bottom: 15px; border-radius: 4px; color: #c62828;">
                    Nepareizs lietotājvārds vai parole!
                </div>
            <?php endif; ?>
            <form method="POST" action="">
                <div style="margin-bottom: 15px;">
                    <label style="display: block; margin-bottom: 5px; color: #666;">Lietotājvārds:</label>
                    <input type="text" name="login" required style="width: 100%; padding: 8px; border: 1px solid #ddd; border-radius: 4px; box-sizing: border-box;">
                </div>
                <div style="margin-bottom: 20px;">
                    <label style="display: block; margin-bottom: 5px; color: #666;">Parole:</label>
                    <input type="password" name="passw" required style="width: 100%; padding: 8px; border: 1px solid #ddd; border-radius: 4px; box-sizing: border-box;">
                </div>
                <button type="submit" style="width: 100%; padding: 10px; background: #1976d2; color: white; border: none; border-radius: 4px; cursor: pointer; font-size: 14px;">
                    Ienākt
                </button>
            </form>
        </div>
    </body>
    </html>
    <?php
    exit;
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
