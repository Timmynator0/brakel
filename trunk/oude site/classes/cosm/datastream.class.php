<?php

class Cosm_Datastream
{
	public $_id, 
		   $_lastUpdated, 
		   $_maxValue,
		   $_currentValue,
		   $_minValue,
		   $_datapoints;

	public function __construct($data) 
	{
		$this->_id				= $data->id;
		$this->_lastUpdated 	= $data->at;
		$this->_maxValue 		= $data->max_value;
		$this->_currentValue 	= $data->current_value;
		$this->_minValue		= $data->min_value;
		$this->_datapoints		= $data->datapoints;
	}
}

?>