<?php

	$file_handle=fopen('results_by_type.csv','r');
	$file=fopen("mod_type_data.txt","w");
	$count=array();
	$temp_count=0;
	$ind=0;
	while (! feof($file_handle) ) 
	{
		$ind=0;
		$line_of_text = fgetcsv($file_handle,1024,',');
		$num=count($line_of_text);
		$count[$temp_count]=array();
		$count[$temp_count][$ind]=(int)$line_of_text[0];
		for($i=1;$i<$num;$i=$i+2)
		{
			$ind++;
			$count[$temp_count][$ind]=(float)$line_of_text[$i];
			
			
		}
		
		$temp_count++;
	}
	
	fclose($file_handle);
	$count[1][0]='time';
	for($i=0;$i<$ind;$i++)
	{
		$count[1][$i+1]='type'.$i;
		
	}

	for($i=1;$i<$temp_count;$i++)
	{
		for($j=0;$j<$ind;$j++)
		{
			fwrite($file,$count[$i][$j].",");
		}
		fwrite($file,$count[$i][$ind]."\n");
	}
	
	fclose($file);
	
?>

<!DOCTYPE html>
<meta charset="utf-8">
<style>

.bar {
  fill: steelblue;
}
.bar:hover {
  fill: brown;
}
.axis path {
  display: none;
}


</style>
<svg width="1024" height="500"></svg>
<script src="//d3js.org/d3.v4.min.js"></script>
<script>

var svg = d3.select("svg"),
    margin = {top: 20, right: 20, bottom: 30, left: 40},
    width = +svg.attr("width") - margin.left - margin.right,
    height = +svg.attr("height") - margin.top - margin.bottom,
    g = svg.append("g").attr("transform", "translate(" + margin.left + "," + margin.top + ")");

var x = d3.scaleBand()
    .rangeRound([0, width])
    .padding(0.4)
    .align(0.1);

var y = d3.scaleLinear()
    .rangeRound([height, 0]);

var z = d3.scaleOrdinal()
    .range(["#98abc5", "#8a89a6", "#7b6888", "#6b486b", "#a05d56", "#d0743c", "#ff8c00", "#dd843c", "#ff8ff0"]);

var stack = d3.stack();

d3.csv("mod_type_data.txt", type, function(error, data) {
  if (error) throw error;

  

  x.domain(data.map(function(d) { return d.time; }));
  y.domain([0, d3.max(data, function(d) { return d.total; })]).nice();
  z.domain(data.columns.slice(1));

  g.selectAll(".serie")
    .data(stack.keys(data.columns.slice(1))(data))
    .enter().append("g")
      .attr("class", "serie")
      .attr("fill", function(d) { return z(d.key); })
    .selectAll("rect")
    .data(function(d) { return d; })
    .enter().append("rect")
      .attr("x", function(d) { return x(d.data.time); })
      .attr("y", function(d) { return y(d[1]); })
      .attr("height", function(d) { return y(d[0]) - y(d[1]); })
      .attr("width", x.bandwidth());
	  
  g.append("g")
      .attr("class", "axis axis--x")
      .attr("transform", "translate(0," + height + ")")
      .call(d3.axisBottom(x));
	

  g.append("g")
      .attr("class", "axis axis--y")
      .call(d3.axisLeft(y).ticks(20))
    .append("text")
      .attr("x", 2)
      .attr("y", y(y.ticks(10).pop()))
      .attr("dy", "0.35em")
      .attr("text-anchor", "start")
      .attr("fill", "#000")
      .text("Utilization");

  var legend = g.selectAll(".legend")
    .data(data.columns.slice(1).reverse())
    .enter().append("g")
      .attr("class", "legend")
      .attr("transform", function(d, i) { return "translate(35," + i * 20 + ")"; })
      .style("font", "10px sans-serif");

  legend.append("rect")
      .attr("x", width - 18)
      .attr("width", 18)
      .attr("height", 18)
      .attr("fill", z);

  legend.append("text")
      .attr("x", width - 24)
      .attr("y", 9)
      .attr("dy", ".35em")
      .attr("text-anchor", "end")
      .text(function(d) { return d; });
});

function type(d, i, columns) {
  for (i = 1, t = 0; i < columns.length; ++i) t += d[columns[i]] = +d[columns[i]];
  d.total = t;
  return d;
}

</script>
