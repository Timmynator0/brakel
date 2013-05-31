//var pachubeApiKey = '0xLlVS6eD5mcdyWbUSmfBdhVxoBXvCFWcUTAvgg_GHd4dQAXeFYugAnNSMtGqDxXGK3BDZeziqSnfQaSEwLu36V4PiMvemJfXUuSeXcdzFIUgsdkG7vCDxO5F5DvDCU4';

function updateData()
{
	return;
	//Image	
	var noCache = '&amp;NoCacheVar='+ new Date().getTime();
	$('#feedImage').attr('src', 'https://api.pachube.com/v2/feeds/47260/datastreams/temperature.png?width=702&amp;height=250&amp;colour=2E5FA2&amp;duration=1hours&amp;detailed_grid=true&amp;show_axis_labels=true&amp;timezone=Amsterdam'+noCache);
	
	/*Numbers	
	$.ajax({url: 'https://api.pachube.com/v2/feeds/47260.json?datastreams=temperature' + noCache,
		dataType: 'json',
		headers: { 'X-PachubeApiKey' : pachubeApiKey },
		success: function(json) {
			var curVal = json.datastreams[0].current_value;
			var minVal = json.datastreams[0].min_value;
			var maxVal = json.datastreams[0].max_value;
			var html = '<table><tr><td>current value</td><td>' + curVal + '</td></tr><tr><td>min value</td><td>' + minVal + '</td></tr><tr><td>max value</td><td>' + maxVal + '</td></tr></table>';
			$('#divTextData').html(html);
		}
	});*/
}

function getHistory()
{
	return;
	// Get Data
	var noCache = '&amp;NoCacheVar='+ new Date().getTime();
	$.ajax({url: 'https://api.pachube.com/v2/feeds/47260.json?datastreams=temperature&amp;duration=1hours&amp;interval=60' + noCache,
		dataType: 'json',
		headers: { 'X-PachubeApiKey' : pachubeApiKey },
		success: function(json) {
		
			var data = json.datastreams[0].datapoints;
			var items = [];
			
			// Convert data format
			$.each(data, function(key, val) {
				var tempArr = [];
				var d = new Date(Date.parse(val.at));
				tempArr.push( d );			
				tempArr.push( parseFloat(val.value) );
				items.push( tempArr );
			});
			
			//console.log(items);			
			plotToGraph(items);		
		}
	});
}

var plotGraph1;
function plotToGraph(items)
{
	var minDateString = items[0][0];
	if(plotGraph1 == null)
	{
		var titleXAxis = 'Tijd';
		var titleYAxis = 'Temperatuur';	
		
		plotGraph1 = $.jqplot("chartTemperature", [items], {
			animate: true,
			background:'#F0F8FF',
			gridLineColor:'#DFDFDF',
			cursor: {
				show: true,
				zoom: true,
				looseZoom: true,
				showTooltip: false
			},
			series:[ {
				pointLabels: {
					show: false
				}
			}],
			axes: {
				xaxis: {
					label: titleXAxis,
					renderer: $.jqplot.DateAxisRenderer,
					tickRenderer: $.jqplot.CanvasAxisTickRenderer,
					numberTicks: 12,
					min: minDateString,
					tickOptions: {
						formatString: '%H:%M',
						angle: -30
					},
					rendererOptions: {
						forceTickAt0: true
					},
					autoscale: true
				},
				yaxis: {
					label: titleYAxis,
					tickRenderer: $.jqplot.CanvasAxisTickRenderer,
					tickOptions: {
						formatString: "%.2f"
					},
					rendererOptions: {
						forceTickAt0: true
					},
					autoscale: true
				}
			},
			highlighter: {
				show: true, 
				showLabel: true, 
				tooltipAxes: 'y',
				sizeAdjust: 7.5 , tooltipLocation : 'ne'
			}
		});
	}
	else
	{
		plotGraph1.series[0].data = items;
		plotGraph1.axes.xaxis.min = minDateString;
		plotGraph1.replot();
	}
}

function navigateTo(page)
{
	$('#pages').children('div').not('#'+page).fadeOut(300);
	$('#pages').children('#'+page).fadeIn(300);
	return false;
}

function showMessage(page)
{
	var url = 'pages/' + page + '.html';
	$.colorbox({ href:url });
	return false;
}

$(document).ready(function() {
	updateData();
	getHistory();
	//setInterval(updateData, 5000);
	//setInterval(getHistory, 5000);			
});