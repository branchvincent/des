<html>
<body>
start time: <?php echo $_POST ["time1"]; ?><br>
stop time: <?php echo $_POST ["time2"]; ?><br>



<?php

	$myfile=fopen("parameters.txt", "w") or die("unable to open");
	fwrite($myfile,"output_path		/Users/Branch/Documents/Academic/Year_1/Summer/DES_Code/DES/Output \n");
	$start_time=(int)substr($_POST ["time1"],0,2);
	$stop_time=(int)substr($_POST ["time2"],0,2);
	$time=$stop_time-$start_time;
	fwrite($myfile,"num_hours		".$time."\n");
	fwrite($myfile,"traffic 		");
	for($x=0;$x<$time;$x++)
	{
		fwrite($myfile,$_POST [(string)$x]." ");
	}

	fwrite($myfile,"\n num_reps		100 \n"); 
	fwrite($myfile,"num_task_types	9");
	fclose($myfile);

?>

	<form action="trash2.php" method="post">
		<button type="submit" >Show results</button>
	</form>
</body>
</html>
  