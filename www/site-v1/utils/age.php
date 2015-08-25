<?php
	$month = 2;
	$day = 12;
	$year = 1997;
	$age = date('Y') - $year;
	if( date('m') < $month || $month == date('m') && $day < date('d')) $age--;
	echo $age;
?>
