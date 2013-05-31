var chart, currentTime;

$(document).ready(function() {
	Highcharts.setOptions({
		global: {
			useUTC: false
		}
	});

	chart = new Highcharts.Chart({
		chart: {
			renderTo: 'temperature_chart',
			defaultSeriesType: 'spline',
			marginRight: 10,
			backgroundColor: 'transparent',
			zoomType: 'x',
			events: {
				load: function() {

					// set up the updating of the chart each second
					var series = this.series[0];
					var series2 = this.series[1];
					setInterval(function() {				
						currentTime = new Date();
						$.getJSON('http://api.pachube.com/v2/feeds/47259.json?key=' + key + '&rCache=' + currentTime.getTime(), 
							  	function(json) {
							  		var d = Date.parse(json.updated);
									var temp = json.datastreams[0].current_value;
							  		
							  		series.addPoint( [currentTime.getTime(), parseFloat(temp) ], true, true );
							  	}
						);

						key = '0xLlVS6eD5mcdyWbUSmfBdhVxoBXvCFWcUTAvgg_GHd4dQAXeFYugAnNSMtGqDxXGK3BDZeziqSnfQaSEwLu36V4PiMvemJfXUuSeXcdzFIUgsdkG7vCDxO5F5DvDCU4';
						$.getJSON('http://api.pachube.com/v2/feeds/47260.json?key=' + key + '&rCache=' + currentTime.getTime(), 
							  	function(json) {
							  		var d = Date.parse(json.updated);
									var temp = json.datastreams[0].current_value;
							  		
							  		series2.addPoint( [currentTime.getTime(), parseFloat(temp) ], true, true );
							  	}
						);
					}, 30000);
				}
			}
		},
		title: {
			text: ''
		},
		xAxis: {
			type: 'datetime',
			tickPixelInterval: 120,
			title: {
				text: 'Datum',
				style: {
					color: '#FFFFFF'
				}
			},
		},
		yAxis: {
			title: {
				text: 'Temperatuur',
				style: {
					color: '#FFFFFF'
				}
			},
			plotLines: [{
				value: 0,
				width: 1,
				color: '#FFFFFF'
			}]
		},
		legend: {
			itemStyle: {
				color: '#FFFFFF'
			}
		},
		tooltip: {
			formatter: function() {
					return Highcharts.dateFormat('%Y-%m-%d %H:%M:%S', this.x) +'<br/>'+
					Highcharts.numberFormat(this.y, 2);
			}
		},
		series: [
			{
				name: 'Temperatuur 1'
			},
			{
				name: 'Temperatuur 2'
			}
		]
	});
	
	currentTime = new Date();
	$.getJSON('http://api.pachube.com/v2/feeds/47259.json?key=' + key + '&amp;duration=1hours&amp;interval=30&amp;rCache=' + currentTime.getTime(), 
		  	function(json) {
		  		var data = json.datastreams[0].datapoints;
		  		var items = [];
		  		
				$.each(data, function(key, val) {
					var d = Date.parse(val.at);
					items.push( [ d, parseFloat(val.value) ] );
				});
				chart.series[0].setData( items );
		  	}
	);
	
	key = '0xLlVS6eD5mcdyWbUSmfBdhVxoBXvCFWcUTAvgg_GHd4dQAXeFYugAnNSMtGqDxXGK3BDZeziqSnfQaSEwLu36V4PiMvemJfXUuSeXcdzFIUgsdkG7vCDxO5F5DvDCU4';
	$.getJSON('http://api.pachube.com/v2/feeds/47260.json?key=' + key + '&amp;duration=1hours&amp;interval=30&amp;rCache=' + currentTime.getTime(), 
		  	function(json) {
		  		var data = json.datastreams[0].datapoints;
		  		var items = [];
		  		
				$.each(data, function(key, val) {
					var d = Date.parse(val.at);
					items.push( [ d, parseFloat(val.value) ] );
				});
				chart.series[1].setData( items );
		  	}
	);
});