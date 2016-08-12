<?php	
	
	require_once("header.php");
?>
	
	
	<div id="page1" class="page">
		<img src="rail.jpg" alt=" " style="position:absolute; top:0px; left:0px; width:1300px; height:600px; opacity:0.15;"/>
		
		<div id="top_panel"></div>
		
		<div id="title">
				<h1>Simulator of Human Operator Workload (SHOW)<img src="hal.png" width=400 align="center" /> </h1>
		</div>
		
		<br><br>

		<div id="uses">
			<h2>Use this tool to answer the following questions</h2>
		</div>
		
		<hr style="height: 0px; border-bottom: 2px solid #e9e7e5;">
		
		<div id="bullets">
			<ul style="list-style-type:circle">
				<li><h3><em>When</em> are my operators over- or under-utilized at work?</h3></li>
				<li><h3><em>Why</em> are my operators over- or under-utilized at work?</h3></li>
				<li><h3><em>How</em> might we improve operator workload, and overall system efficiency and safety?</h3></li>
			</ul>
		</div>
		
		<div id="button" >
			<hr style=" width: 60px; height: 0px; border-bottom: 2px solid #e9e7e5;">
			<hr style=" width: 60px; height: 0px; border-bottom: 2px solid #e9e7e5;">
			<hr style=" width: 60px; height: 0px; border-bottom: 2px solid #e9e7e5;">
		</div>

		
	</div>
	
	
	
	<div id="page2" class="page">
		

		<form action="create_txt.php" method="post">
					
							
			<h3 id="text_start">Enter Start Time:</h3> <br><input id="start_time" type="time" name="time1" oninput="calculate_time()">
					
			<br>
		
			<h3 id="text_stop">Enter Stop Time:</h3> <br><input id="stop_time" type="time" name="time2" oninput="calculate_time()">
			
			<br>
			<div id="totalTime" style="overflow-x:auto;"></div>
			<div id="assist" style="overflow-x:auto;"></div>
			
			<input type="submit" id="submit"></input>
					
					
					
		</form>
	</div>
	
	
	
	
	
	
	<?php
	require_once("footer.php");
	?>
	
	