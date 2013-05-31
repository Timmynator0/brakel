<?php

define('CLASSES',           ROOT . 'classes' . DS);
define('PAGES',				ROOT . 'pages' . DS);

$config = array(
				'db_host'  		=> 'localhost',
				'db_database'	=> 'projectweb_brak',
				'db_user'		=> 'projectweb_brak',
				'db_password'   => 'y78UWcax'
				);
				
function autoloadClasses ($name)
{
    $path = CLASSES . str_replace('_', DS, strtolower($name)) . '.class.php';
    if (file_exists($path))
    {
        require_once $path;
        return true;
    }
    else
    {
        return false;
    }
}
spl_autoload_register('autoloadClasses');

// If magic_quotes_gpc is turned on, we need to strip the slashes.
if (get_magic_quotes_gpc())
{
    function stripslashes_array($array)
    {
        return is_array($array) ? array_map('stripslashes_array', $array) : stripslashes($array);
    }

    $_GET       = stripslashes_array($_GET);
    $_POST      = stripslashes_array($_POST);
    $_COOKIE    = stripslashes_array($_COOKIE);
}

$db = new Database($config['db_host'], $config['db_user'], $config['db_password'], $config['db_database']);
Registry::set('db', $db);


if (!defined('CRONJOB'))
{
	if (file_exists(ROOT . '.cache'))
	{
		$file = file_get_contents(ROOT . '.cache');
		$cosm = unserialize($file);
	}
	else
	{
		$cosm = new Cosm_Feeds();
		$cosm->loadData();
		
		$ser = serialize($cosm);
		file_put_contents(ROOT . '.cache', $ser);
	}
}

?>