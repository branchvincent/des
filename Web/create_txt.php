<html>
<body>

<style>

button[type=submit] {

    padding:5px 15px; 
    border: 2px solid #5D7B85;
    cursor:pointer;
    -webkit-border-radius: 5px;
    border-radius: 25px; 
}

</style>

<?php
	
	session_start();
	$myfile=fopen("parameters.txt", "w") or die("unable to open");
	fwrite($myfile,"output_path		/Users/Branch/Documents/Academic/Year 1/Summer/DES Code/DES/Web\n");
	$start_time=(int)substr($_POST ["time1"],0,2);
	$stop_time=(int)substr($_POST ["time2"],0,2);
	$start_min=(int)substr($_POST ["time1"],3,strlen($_POST ["time1"]));
	$stop_min=(int)substr($_POST ["time2"],3,strlen($_POST ["time2"]));
	$time=60-$start_min+$stop_min+($stop_time-$start_time-1)*60;
	
	$time=ceil($time/60);
	
	fwrite($myfile,"num_hours		".$time."\n");
	fwrite($myfile,"traffic 		");
	for($x=0;$x<$time;$x++)
	{
		fwrite($myfile,$_POST [(string)$x]." ");
	}

	fwrite($myfile,"\nnum_reps		100 \n"); 
	
	
	if(isset($_POST["extra"]))
	{
		$operator=(int)$_POST["extra"];
		$_SESSION['operator']=$operator;
	}
	else{
		$operator=0;
		$_SESSION['operator']=$operator;
	}
	if($operator==0)
	{
		fwrite($myfile,"ops				0");
	}
	else{
		fwrite($myfile,"ops				0 ".$operator);
	}
	
	fclose($myfile);
	
	echo passthru("./DES parameters.txt");
	
	include('read_csv_mod.php');
?>

	

	
</body>
</html>
  