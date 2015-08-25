<?php
//опасаемся ошибок
error_reporting(E_ALL ^ E_NOTICE ^ E_DEPRECATED);
//получаем название страницы
$page = trim($_GET['page'], '/');
//если пусто - обо мне
if($page == '') $page = 'about';
//разрешенные страницы
$allowed = array(
	'twitter',
	'vk',
	'contacts',
	'about'
);
//узнаем - есть ли такая страница
if(in_array($page, $allowed)) {
	//да, есть!
	include_once('pages/'.$page.'.php');
}
else
{
	//нет, рапортуем 404 ошибку
	header("HTTP/1.1 404 Not Found");
	header("Status: 404 Not Found");
	include_once('pages/404.php');
}
?>
