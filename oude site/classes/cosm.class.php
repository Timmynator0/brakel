<?php
/**
 * Pachube API class
 * Version 1.0.0 (June 2011)
 * Requirements: PHP5, cURL, API v.1.0
 * Rewrite by Rick Doorakkers
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * ( at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * erchantability or fitness for a particular purpose. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Online: http://www.gnu.org/licenses/gpl.txt
 */

class Cosm
{
	private $_apiKey, $_feedId, $_url, $_headers;
	
	/**
	 * Constructor
	 */
	function __construct($apiKey, $feedId) 
	{
		$this->_apiKey 	= $apiKey;
		$this->_feedId  = $feedId;
		$this->_url 	= "http://api.cosm.com/v2/";
		$this->_headers = array("X-PachubeApiKey: " . $this->_apiKey);
	}
	
	/**
	 * Get data from Pachube feed.
	 * @param string feed URL
	 * @param string feed type
	 * @return string feed data
	 */
	public function getJson($start, $end, $interval, $datastreams = null)
	{ 
		if(empty($this->_apiKey))
		{
			return 401;
		}
		else 
		{
			$url = $this->_url . "feeds/" . $this->_feedId . ".json?start=" . $start . "&end=" . $end . "&interval=" . $interval;
			if (!is_null($datastreams) && count($datastreams) > 0)
			{
				$streams = implode(',', $datastreams);
				$url .= "&datastreams=" . $streams;
			}
				
			return $this->_getRequest($url);
		}
	}
	
	/**
	 * Get environment information
	 * @param int feed ID
	 * @return associative array
	 */
	public function getEnvironment($feed_id)
	{	
		$data = json_decode($this->getFeedData($feed_id), true);		
		$return_data = (!is_array($data)) ? json_decode("{\"location\":{}\"datastreams\":[{}]}") : $data;
		return $return_data;
	}
	
	/**
	 * Create GET request to Pachube (wrapper)
	 * @param string url
	 * @return response
	 */
	private function _getRequest($url)
	{		
		if(function_exists('curl_init'))
		{
			return $this->_curl($url,true);
		}
		elseif(function_exists('file_get_contents') && ini_get('allow_url_fopen'))
		{
			return $this->_get($url);		
		}
		else
		{
			return 500;
		}
	}

	/**
	 * Create PUT request to Pachube (wrapper)
	 * @param string url
	 * @param string data
	 * @return response
	 */
	private function _putRequest($url, $data)
	{	
		if(function_exists('curl_init'))
		{
			$putData = tmpfile();
			fwrite($putData, $data);
			fseek($putData, 0);

			$ch = curl_init();
			curl_setopt($ch, CURLOPT_URL, $url);
			curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
			curl_setopt($ch, CURLOPT_HTTPHEADER, $this->Pachube_headers);
			curl_setopt($ch, CURLOPT_INFILE, $putData);
			curl_setopt($ch, CURLOPT_INFILESIZE, strlen($data));
			curl_setopt($ch, CURLOPT_PUT, true);
			curl_exec($ch);
			$headers = curl_getinfo($ch);
			fclose($putData);
			curl_close($ch);

			return $headers['http_code'];
		}
		elseif(function_exists('file_put_contents') && ini_get('allow_url_fopen'))
		{
			return $this->_put($url,$data);
		}
		else
		{
			return 500;
		}
	}

	/**
	 * cURL main function
	 * @param string url
	 * @param bool authentication
	 * @return response
	 */
	private function _curl($url, $auth=false)
	{
		if(function_exists('curl_init'))
		{
			$ch = curl_init();
			curl_setopt($ch, CURLOPT_URL, $url);
			curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
			if($auth)
			{
				curl_setopt($ch, CURLOPT_HTTPHEADER, $this->_headers);
			}
			$data = curl_exec($ch);
			//$headers = curl_getinfo($ch);
			curl_close($ch);
			return $data;
		}
		else
		{
			return false;
		}
	}
	
	/**
	 * GET requests to Pachube
	 * @param string url
	 * @return response
	 */
	private function _get($url)
	{
		// Create a stream
		$opts['http']['method'] = "GET";
		$opts['http']['header'] = "X-PachubeApiKey: ".$this->_apiKey."\r\n";
		$context = stream_context_create($opts);
		// Open the file using the HTTP headers set above
		return file_get_contents($url, false, $context);
	}

	/**
	 * PUT requests to Pachube
	 * @param string url
	 * @param string data
	 * @return response
	 */
	private function _put($url,$data)
	{	
		// Create a stream
		$opts['http']['method'] = "PUT";
		$opts['http']['header'] = "X-PachubeApiKey: ".$this->_apiKey."\r\n";
		$opts['http']['header'] .= "Content-Length: " . strlen($data) . "\r\n";
		$opts['http']['content'] = $data;
		$context = stream_context_create($opts);
		// Open the file using the HTTP headers set above
		return file_get_contents($url, false, $context);
	}
	
	/**
	 * Find string between to strings
	 * @param string content where to search
	 * @param string start point
	 * @param string end point
	 * @return response
	 */
	private function _stringBetween($content, $start, $end)
	{
		$r = explode($start, $content);
		if (isset($r[1]))
		{
			$r = explode($end, $r[1]);
			return $r[0];
		}
		return '';
	}

	/**
	 * Print debug status of error
	 * @param int status code
	 */
	public function _debugStatus($status_code)
	{
		switch ($status_code)
		{			
			case 200:
				$msg = "Pachube feed successfully updated";	
				break;
			case 401:
				$msg = "Pachube API key was incorrect";
				break;
			case 404:
				$msg = "Feed ID or some other parameter does not exist";
				break;
			case 422:
				$msg = "Unprocessable Entity, semantic errors (CSV instead of XML?)";
				break;
			case 418:
				$msg = "Error in feed ID, data type or some other data";
				break;
			case 500:
				$msg = "cURL library not installed or some other internal error occured";
				break;	
			default:
				$msg = "Status code not recognised: ".$status_code;
				break;
		}
		echo $msg;		
	}
}
?>