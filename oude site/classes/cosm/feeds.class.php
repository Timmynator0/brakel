<?php

class Cosm_Feeds
{
	private $_db;
	private $_rooms = array();
	
	public function __construct() 
	{
		$this->_db = Registry::get('db');
		$roomsQuery = $this->_db->query("SELECT *
								 	     FROM   `room`
								         ORDER BY `room_id` ASC");
		while ($room = $this->_db->fetch_assoc($roomsQuery))
		{
			$cosmRoom 			= new Cosm_Room();
			$cosmRoom->_id 		= $room['room_id'];
			$cosmRoom->_title 	= $room['title'];
			$cosmRoom->_feed 	= $room['feed'];
			$cosmRoom->_cosmApi = new Cosm($room['apikey'], $room['feed']);	
			
			$this->_db->prepare("SELECT *
								 FROM   `datastream`
								 WHERE  `room_id` = :room_id
								 ORDER BY `datastream_id` ASC")
					  ->bindValue('room_id', $room['room_id'])
					  ->execute();
			while ($data = $this->_db->fetch_assoc())
			{
				$cosmRoom->_datastreams[$data['datastream_id']] = $data;		
			}
			
			$this->_rooms[$room['room_id']] = $cosmRoom;
		}		
		
		Debug::output($this->_rooms);
	}
	
	public function loadData(DateTime $start = null, DateTime $end = null, $interval = 900) 
	{
		if (is_null($start)) 
		{
			$start = new DateTime();
			$start->modify('-14 days');
		}	
		
		if (is_null($end))
		{
			$end = new DateTime();
		}
			
		foreach ($this->_rooms as $room)
		{
			$api = $room['api'];
			$datastreams = array();
			
			foreach ($room['datastreams'] as $data)
			{
				$datastreams[] = $data['identifier'];	
			}
			
			if (($data = $api->getJson($start->format(DateTime::ISO8601), $end->format(DateTime::ISO8601), $interval, $datastreams)) !== false)
			{
				$json 				= json_decode($data);
				Debug::output($json);
				$this->_title 		= $json->title;
				$this->_status 		= $json->status;
				$this->_creator 	= $json->creator;
				$this->_feed 		= $json->feed;
				$this->_updated 	= $json->updated;
				
				foreach ($json->datastreams as $data)
				{	
					$this->_datastreams[$data->id] = new Cosm_Datastream($data);	
				}
				
				return $this->_datastreams;
			}
		}
				
		return false;
	}
}

?>