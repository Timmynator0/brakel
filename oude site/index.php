<?php 
	ob_start(); 
	session_start();	
?>
<!DOCTYPE html>
<html lang="nl">
	<head>
		<title>Nieuwe interface Brakel</title>
		
		<meta name="viewport" content="initial-scale = 1.0,maximum-scale = 1.0" />
		<meta name="apple-mobile-web-app-capable" content="yes" />
		
		<link rel="apple-touch-icon" href="/images/icon_57.png"/>
		<link rel="apple-touch-icon" sizes="72x72" href="/images/icon_72.png" />  
		<link rel="apple-touch-icon" sizes="114x114" href="/images/icon_114.png" />  
		<link rel="shortcut icon" type="image/x-icon" href="/favicon.ico" />
		<link rel="icon" type="image/x-icon" href="/favicon.ico" />
		
		<link rel="stylesheet" type="text/css" href="/css/style.css" />
		<link rel="stylesheet" href="/css/add2home.css" />
		<link rel="stylesheet" type="text/css" href="/css/jquery-ui.custom.css" />
		
		<script type="text/javascript" src="/scripts/jquery-latest.min.js"></script>
		<script type="text/javascript" src="/scripts/jquery-ui.min.js"></script>
		<script type="application/javascript" src="/scripts/add2home.js"></script>
		<script type="text/javascript">
			var iWebkit;if(!iWebkit){iWebkit=window.onload=function(){function fullscreen(){var a=document.getElementsByTagName("a");for(var i=0;i<a.length;i++){if(a[i].className.match("noeffect")){}else{a[i].onclick=function(){window.location=this.getAttribute("href");return false}}}}function hideURLbar(){window.scrollTo(0,0.9)}iWebkit.init=function(){fullscreen();hideURLbar()};iWebkit.init()}}
		</script>
	</head>
	<body>
		<div id="container">
			<img id="headerImage" src="/images/header_image.png" alt="Header" />
			<header>
				<div class="top">
					<a href=""><img src="/images/logo.png" alt="Logo" /></a>
				</div>
				<div class="middle">
					<div>
						<img src="/images/icon_daglicht.jpg" /><span>Daglicht</span>
					</div>
					<div>
						<img src="/images/icon_ventilatie.jpg" /><span>Ventilatie</span>
					</div>
					<div>
						<img src="/images/icon_brand.jpg" /><span>Brandveiligheid</span>
					</div>
					<div>
						<img src="/images/icon_onderhoud.jpg" /><span>Onderhoud</span>
					</div>
				</div>
				<div class="bottom"></div>			
			</header>
			<div id="content">
				<?php
					
					define('DS',                DIRECTORY_SEPARATOR);
					define('ROOT',              dirname(__FILE__) . DS);
					require_once(ROOT . 'include.php');
					
					if (isset($_SESSION['user']))
					{					
						switch ($_GET['page'])
						{
							case 'home':
								require_once(PAGES . 'home.php');
								break;
							case 'alarm':
								require_once(PAGES . 'alarm.php');
								break;
							case 'groepen':
								require_once(PAGES . 'groepen.php');
								break;
							case 'luchtkwaliteit':
								require_once(PAGES . 'luchtkwaliteit.php');
								break;
							case 'lux':
								require_once(PAGES . 'lux.php');
								break;
							case 'meteo':
								require_once(PAGES . 'meteo.php');
								break;
							case 'schakelkast':
								require_once(PAGES . 'schakelkast.php');
								break;
							case 'temperatuur':
								require_once(PAGES . 'temperatuur.php');
								break;
							case 'vochtigheid':
								require_once(PAGES . 'vochtigheid.php');
								break;
							default:
								require_once(PAGES . 'login.php');	
							
						}
					}
					else
					{
						require_once(PAGES . 'login.php');	
					}
				?>				
			</div>
			<div id="footer" <?php if (!isset($_SESSION['user'])) { echo('class="hideButtons"'); } ?> >
				<ul>
					<li <?php if($_GET["page"] == "home") { echo('class="active"'); } ?> ><a href="/home" class="home">Home</a></li>
					<li <?php if($_GET["page"] == "temperatuur") { echo('class="active"'); } ?> ><a href="/temperatuur" class="temperatuur">Temperatuur</a></li>
					<li <?php if($_GET["page"] == "meteo") { echo('class="active"'); } ?> ><a href="/meteo" class="meteo">Meteo</a></li>
					<li <?php if($_GET["page"] == "vochtigheid") { echo('class="active"'); } ?> ><a href="/vochtigheid" class="vochtigheid">Relatieve Luchtvochtigheid</a></li>
					<li <?php if($_GET["page"] == "groepen") { echo('class="active"'); } ?> ><a href="/groepen" class="groepen">Sturing groepen</a></li>
					<li <?php if($_GET["page"] == "schakelkast") { echo('class="active"'); } ?> ><a href="/schakelkast" class="schakelkast">Status schakelkast</a></li>
					<li <?php if($_GET["page"] == "luchtkwaliteit") { echo('class="active"'); } ?> ><a href="/luchtkwaliteit" class="luchtkwaliteit">Luchtkwaliteit</a></li>
					<li <?php if($_GET["page"] == "lux") { echo('class="active"'); } ?> ><a href="/lux" class="lux">Lichtintensiteit</a></li>
					<li <?php if($_GET["page"] == "alarm") { echo('class="active"'); } ?> ><a href="/alarm" class="alarm">Brandmelding</a></li>
				</ul>
			</div>
		</div>
	</body>
</html>
<? echo(ob_get_clean()); ?>