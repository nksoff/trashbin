<!DOCTYPE html>
<html>

	<head>
		<title>Никита Слимов - Личный сайт</title>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<meta name="description" content="Личный сайт Никиты Слимова">
		<meta name="keywords" content="Никита, Слимов, Никита С., личный сайт, обо мне">
		<!-- styles & favicons -->
		<link rel="stylesheet" type="text/css" href="/css/main.css" />
		<link rel="icon" href="/ico/favicon.ico" type="image/x-icon" />
		<link rel="shortcut icon" href="/ico/favicon.ico" type="image/x-icon" />
		<!-- scripts -->
		<script src="/js/jq.js"></script>
		<script>
			$(document).ready(function() {
				$('#about-menu a').click(function() {
					var id = '#about-' + $(this).attr('id');
					if($(id).is(':visible')) return false;
					
					$('#about-menu .active').removeClass('active');
					$(this).addClass('active');
					$('.about-info:visible').fadeOut('fast' , function() {
						$(id).fadeIn('fast');
					});
					return false;
				});
			});
		</script>
	</head>
	
	<body>
		<!-- container -->
		<div id="cont">
			<div id="header">
				<ul id="menu">
					<li> <span>Обо мне</span> </li>
					<li> <a href="/index.php?page=contacts">Контакты и фото</a> </li>
				</ul>
				<span id="logo">Сайт Никиты Слимова</span>
			</div>
			<div class="clear"></div>
			<div id="content">
				<div id="social">
					<a href="/index.php?page=twitter"><img title="Твиттер @nkslim" alt="Твиттер @nkslim" src="/ico/twi.png" /></a>
					<a href="/index.php?page=vk"><img title="Вконтакте /slimov" alt="Вконтакте /slimov" src="/ico/vkontakte.png" /></a>
				</div>
				<div id="about-menu">
					Обо мне как о 
						<a href="#" class="active" id="man">человеке</a>
						<a href="#" id="sch">школьнике</a>
						<a href="#" id="dev">разработчике и <span title="Гик — сленговое выражение, употребляемое относительно людей увлечённых технологиями, в том числе компьютерными (сообщает Википедия)">гике</span></a>
				</div>
				<div id="about-man" class="about-info">
					<span class="g">Меня зовут</span> Никита Слимов <br />
					<span class="g">А также</span> Никитуля, Никитус, Никитос, Никос, nkslim, nikita, nksoff, nks.off, ... <br />
					<span class="g">Мне</span> <?php include_once('utils/age.php') ?> лет (1997 г.)<br />
					<span class="g">Живу и учусь</span> в Москве<br />
					<span class="g">В будущем вижу себя</span> программистом, возможно сисадмином. Может быть все еще поменяется?<br />
					<span class="g">Нравится</span> сидеть за компьютером, смотреть телевизор, поспать с утра подольше, читать интересные книги и блоги, задавать глупые вопросы, есть пельмени и острое, ходить босиком, разводить бардак, качаться на стульях, ВЫкать, ломать карандаши<br />
					<span class="g">Слушаю</span> любую музыку (кроме классики), аудиокниги, изредка подкасты<br />
					<span class="g">Смотрю</span> комедии, ужастики, мульты, скетч-шоу<br />
					<span class="g">Читаю</span> классику, раньше - фантастику<br />
					<span class="g">Не верю</span> в приметы и конец света<br />
				</div>
				<div id="about-sch" class="about-info" style="display:none">
					<span class="g">Учусь</span> в школе с углубленным изучением иностраных языков (в 9 классе)<br />
					<span class="g">Оценки</span> от трех до пяти, зависят от моих стараний<br />
					<span class="g">Участвую</span> в олимпиадах (английский язык, русский язык, математика, информатика, ...) и конкурсах ("Кенгуру", "Русский медвежонок")<br />
					<span class="g">Углубляюсь</span> в физику, скорее всего буду сдавать ГИА по физике<br />
					<span class="g">Хотелось бы поступить в</span> МГТУ им. Баумана (в лучшем случае), МАИ или МГУ им. Ломоносова. Однако, еще ничего точно не решено.<br />
				</div>
				<div id="about-dev" class="about-info" style="display:none">
					<span class="g">Начинал с</span> ActionScript 3.0 + Flash (сейчас забросил)<br />
					<span class="g">Сейчас занимаюсь</span> веб разработкой. Все как у всех: HTML, CSS, JS, jQuery, Ajax, PHP, MySQL<br />
					<span class="g">В планах попробовать</span> C++ и python.<br />
					<span class="g">Пользуюсь ОСями</span> Win xp, win 7 и Ubuntu 11.04. Увлекся linux'ом. В планах попробовать Mac OS<br />
					<span class="g">Использую</span> Gnome (среда), Google Chrome, Mozilla Firefox (браузеры), Byobu Terminal (консоль с дополнениями), Tomboy (мастер заметок), Empathy (аськи-шмаськи), Gedit (текстовый редактор с дополнениями), VirtualBox (виртуализация), Git (контроль версий), Apache 2, Nginx (веб-сервера), ...<br />
					<span class="g">В ответе за</span> разную технику, несколько ноутбуков, домашний файловый сервер и виртуальный сервер<br />
				</div>
			</div>
			<div class="clear"></div>				
			<div id="footer">
				2012 &copy;
			</div>
			<div class="clear"></div>
		</div>
	</body>

</html>
