<?php
	$file_handle=fopen('eng.csv','r');
	$count=0;
	$mean=array();
	$low_count=0;
	$normal_count=0;
	$high_count=0;
	while (! feof($file_handle) ) 
	{

		$line_of_text = fgetcsv($file_handle,1024,',');
		$num=count($line_of_text);
		$mean[$count]=$line_of_text[$num-2];
		if($mean[$count]<0.3)
		{
			$low_count++;
		}
		else
		{
			if($mean[$count]<0.7)
			{
				$normal_count++;
			}
			else
			{
				$high_count++;
			}
		}
		$count++;
	}
	$low_count=$low_count*100/$count;
	$normal_count=$normal_count*100/$count;
	$high_count=$high_count*100/$count;
	echo "Low workload state: ".$low_count." % of the total time <br><br>";
	
	echo "Normal workload state: ".$normal_count." % of the total time <br><br>";
	echo "High workload state: ".$high_count." % of the total time <br>";
	fclose($file_handle);
	
	
?>