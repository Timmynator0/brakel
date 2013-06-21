<?php

class Database
{
    private $host;
    private $user;
    private $password;
    private $database;
    private $charset;
    private $connection;
    private $select;

    private $parameters = array();
    private $query;
    private $result;
    private $time;

    private $fireTable;

    public function __construct($host, $user, $password, $database, $charset = 'utf8')
    {
        $this->host         = $host;
        $this->user         = $user;
        $this->password     = $password;
        $this->database     = $database;
        $this->charset      = 'utf8';

        $this->connection   = mssql_connect($this->host, $this->user, $this->password);

        if (!$this->connection)
            die('Er kan geen verbinding worden gemaakt met de database.');

        $this->select       = mssql_select_db($this->database, $this->connection);
        if (!$this->select)
            die('Er kon geen database geselecteerd worden.');

        mysql_set_charset($this->charset, $this->connection);
    }

    /**
     * Adds a parameter to the current prepared query.
     *
     * @param <String> $parameter Parameter identifier.
     * @param <String> $value Parameter value.
     * @param <Boolean> $emptyToNULL If empty, set NULL.
     * @param <Boolean> $number If number, make it number.
     * 
     * @return <Database> Returns the current Database object.
     */
    public function bindValue ($parameter, $value, $emptyToNULL = true, $number = true)
    {
        switch(true)
        {
            case ctype_digit($value) && $number === true:
                $value = intval($value);
                break;
            case is_numeric($value) && $number === true:
                $value = doubleval($value);
                break;
            case is_null($value) || $emptyToNULL === true && empty($value):
                $value = 'NULL';
                break;
            default:
                $value = "'" . mysql_real_escape_string($value) . "'";
        }

        $this->parameters[':' . $parameter] = $value;
        return $this;
    }
    
    /**
     * Prepares a query.
     * 
     * @param <String> $sql MySQL query..
     * 
     * @return <Database> Returns the current Database object.
     */
    public function prepare ($sql)
    {
        $this->query = $sql;
        $this->parameters = array();

        return $this;
    }

    /**
     * Executes the query.
     *
     * @param <Boolean> $fb If true, the query will printed to the FirePHP Console.
     *
     * @return <Boolean> Gives the query result.
     */
    public function execute($fb = false, $exit = true)
    {
        $query = str_replace(array_keys($this->parameters), $this->parameters, $this->query);

        $this->result = mysql_query($query, $this->connection);

        return $this->result;
    }

    /**
     * Executes a query.
     *
     * @param <type> $sql MySQL query.
     * @param <Boolean> $fb If true, the query will printed to the FirePHP Console.
     *
     * @return <Boolean> Gives the query result.
     */
    public function query ($sql, $fb = false, $exit = true)
    {
        $this->query = $sql;
        return $this->execute($fb, $exit);
    }

    /**
     * Executes a query without stopping the script.
     *
     * @param <type> $sql MySQL query.
     * @param <Boolean> $fb If true, the query will printed to the FirePHP Console.
     *
     * @return <Boolean> Gives the query result.
     */
    public function querySafe ($sql, $fb = false)
    {
        $this->query = $sql;
        return $this->execute($fb, false);
    }

    /**
     * Fetch a result row as an associative array.
     *
     * @param <mysql_query> $result The result of the mysql_query function.
     * @return <Result> Returns an associative array of strings that corresponds to the fetched row, or FALSE if there are no more rows.
     */
    public function fetch_assoc ($result = null)
    {
        if(is_null($result))
        {
            $result = $this->result;
        }

        return mysql_fetch_assoc($result);
    }

    /**
     * Fetch a result row as an associative array, a numeric array, or both.
     *
     * @param <mysql_query> $result The result of the mysql_query function.
     * @return <Result> Returns an array of strings that corresponds to the fetched row, or FALSE if there are no more rows.
     */
    public function fetch_array ($result = null)
    {
        if(is_null($result))
        {
            $result = $this->result;
        }

        return mysql_fetch_array($result);
    }

    /**
     * Get number of rows in result.
     *
     * @param <mysql_query> $result The result of the mysql_query function.
     * @return <type> The number of rows in a result set on success or FALSE on failure.
     */
    public function num_rows ($result = null)
    {
        if(is_null($result))
        {
            $result = $this->result;
        }

        return mysql_num_rows($result);
    }

    public function insert_id ()
    {
        $insertId = mysql_insert_id($this->connection);
        if ($insertId)
        {
            return $insertId;
        }
        else
        {
            return 'asdflaslfd';
        }
        return mysql_insert_id($this->connection);
    }
}