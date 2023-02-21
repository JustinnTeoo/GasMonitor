<?php
	//setting header to json
	header('Content-Type: application/json');

	//database
	$host = "localhost";
	$user = "root";
	$password = "leejizhe";
	$dbname = "rainsensor";

	// Create connection
	$con = new mysqli($host, $user, $password, $dbname);
	// Check connection
	if ($con->connect_error) {
	die("Connection failed: " . $con->connect_error);
	}

	//query to get data from the table
	$query = sprintf("SELECT Time, Rain FROM rainsensortable ORDER BY Time");

	//execute query
	$result = $con->query($query);

	//loop through the returned data
	$data = array();
	foreach ($result as $row) {
	  $data[] = $row;
	}

	//free memory associated with result
	$result->close();

	//close connection
	$con->close();

	//now print the data
	print json_encode($data);