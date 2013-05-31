<?php

class Debug
{
	public static function output($var_dump)
	{
		ob_start();
		echo '<pre>' , var_dump($var_dump) , '</pre>';
		exit(ob_get_clean());
	}
}