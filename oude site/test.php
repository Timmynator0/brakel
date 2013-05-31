<?php

define('DS',                DIRECTORY_SEPARATOR);
define('ROOT',              dirname(__FILE__) . DS);

require_once(ROOT . 'include.php');

echo '<pre>' , var_dump($cosm) , '</pre>';