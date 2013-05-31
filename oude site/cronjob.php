<?php

define('DS',                DIRECTORY_SEPARATOR);
define('ROOT',              dirname(__FILE__) . DS);
define('CRONJOB',   		0);

require_once(ROOT . 'include.php');

$cosm = new Cosm_Feeds();
$cosm->loadData();

$ser = serialize($cosm);
file_put_contents(ROOT . '.cache', $ser);