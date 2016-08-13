<!-- <html>
<head>
		<meta charset="UTF-8">
		<title>Title.</title> -->
		<!-- <link rel="stylesheet" href="assist1_mod.css"> -->

<?php

	session_start();

	$html_head_insertions .= '<link rel="stylesheet" href="assist_summary.css">';

	require_once('header.php');

	$low_count_0=$_SESSION['low_count_0'];
	$normal_count_0=$_SESSION['normal_count_0'];
	$high_count_0=$_SESSION['high_count_0'];
	$low_count_1=$_SESSION['low_count_1'];
	$normal_count_1=$_SESSION['normal_count_1'];
	$high_count_1=$_SESSION['high_count_1'];

	if ($_SESSION['operator1'] == -1) {
		$operator2Style = 'display:none; ';
	} else {
		$operator2Style = ' ';
	}

?>
<!-- 	
</head>

<body>
	
	<div id="page">
		<img src="rail.jpg" alt=" " style="position:absolute; top:0px; left:0px; width:1300px; height:600px; opacity:0.15;"/>
		<div id="top_panel"></div>
		
		<div id="title">
				<h1>Simulator of Human Operator Workload (SHOW)<img src="hal.png" width=400 align="middle" /> </h1>
		</div>
		
		<br><br>
		 -->
	<div id="page" class='page'>
		<div id="operators">
		
			<div id="operator1" class='stepBox'>
				<h2>On average, your engineer is projected to experience:</h2>
			
			
		
			
				<div id="bullets">
					<ul style="list-style-type:circle">
						<li><h3>low workload range for <?php echo $low_count_0*10; ?> minutes</h3></li>
						<li><h3>moderate workload range for <?php echo $normal_count_0*10; ?> minutes</h3></li>
						<li><h3>high workload range for <?php echo $high_count_0*10; ?> minutes</h3></li>
					</ul>
				</div>
			
				<form action="read_csv.php" method="post">
					<button type="submit" id="submit1">Result Analysis (Engineer)</button>
				</form>
			</div>
			
			<div id="operator2" style='<?php echo $operator2Style; ?>'>
				<h2>On average, your conductor is projected to experience:</h2>
				<div id="bullets">
					<ul style="list-style-type:circle">
						<li><h3>low workload range for <?php echo $low_count_1*10; ?> minutes</h3></li>
						<li><h3>moderate workload range for <?php echo $normal_count_1*10; ?> minutes</h3></li>
						<li><h3>high workload range for <?php echo $high_count_1*10; ?> minutes</h3></li>
					</ul>
				</div>
		
				<form action="read_csv_2.php" method="post">
					<button type="submit" id="submit2">Result Analysis (Conductor)</button>
				</form>
		    
			</div>
		
				
		</div>

	</div>
<?php
	require_once('footer.php');
?>
<!-- </body>	
</html>
 -->