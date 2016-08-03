<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<title>Title.</title>
	</head>
	<body>
		<h1 style="color:red">My first heading</h1>
<!-- 		<button type="button" onclick="alert('Hey!')">Click Me!</button> -->
<!-- 		<button type="button" onclick="console.log('Hey')">Click Me!</button> -->
		<button type="button" onclick="clicked()">Click Me!</button>

		<form action="demo_form.asp">
			First name: <input id="input1" type="text" name="fname"><br>
			Last name: <input id="input2" type="text" name="lname"><br>
			<input type="submit" value="Submit">
		</form>
		
		<p>First paragraph.</p>
		<p>This <a href="http://www.google.com">page</a> is to google.</p>
		<p>3 paragraph. <img src="hal_logo_dark.png" width=200 /> </p>
		
		<?php
			echo 36+1;
			echo "<br>";
			echo date("m:d:y, h:i:s");
			echo "<br>";
			echo "<pre>";
			echo passthru("./DES params.txt");
			echo "</pre>";
		?>
		
		<script> 
			var a=document.getElementById("input1");	
			var b=document.getElementById("input2");
			var c=0;
			
			function clicked () {
				c++;
				console.log(c);
			}
		</script>
	</body>
</html>