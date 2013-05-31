<?php

class Registry {

    private static $_registry = array();

    public static function set($identifier, $value)
    {
        self::$_registry[$identifier] = $value;
    }

    public static function get($identifier)
    {
        if(!isset(self::$_registry[$identifier]))
            throw new FatalError('De waarde ' . $identifier . ' bestaat niet in het register');

        return self::$_registry[$identifier];
    }
}