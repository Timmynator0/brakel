<?php

function handleLogin()
{
	$username = "";
	$password = "";
	/*if(!empty($_POST['passwordBeheerder']))
	{
		$username = "Beheerder";
		$password = $_POST['passwordBeheerder'];
	}
	else if(!empty($_POST['passwordGebruiker']))
	{
		$username = "Gebruiker";
		$password = $_POST['passwordGebruiker'];
	}
	else if(!empty($_POST['passwordOnderhoud']))
	{
		$username = "Onderhoud";
		$password = $_POST['passwordOnderhoud'];
	}*/
	if(!empty($_POST['password']) && !empty($_POST['username']))
	{
		$username = $_POST['username'];
		$password = $_POST['password'];
	}
	else
	{
		$_SESSION["LoggedInAs"] = "";
		return false;
	}

	$password = trim($password);
	if(!verifyCredentials($username,$password))
	{
		$_SESSION["LoggedInAs"] = "";
	}
	else
	{
		session_start();	
		$_SESSION["LoggedInAs"] = $username;
	}
	
	return $_SESSION["LoggedInAs"];
}

function verifyCredentials($username, $password)
{
	switch($username)
	{
		case "Beheerder":
		{			
			return ($password == "Wachtwoord");
		}
		case "Gebruiker":
		{
			return ($password == "Wachtwoord");
		}
		case "Onderhoud":
		{
			return ($password == "Wachtwoord");
		}
		default:
		{
			return false;
		}
	}
}

$loggedInAs = handleLogin();
switch($loggedInAs)
{
	case "Beheerder":
	{
		//redirect to Beheerder loggedin page.
		header( 'Location: /home' );
		break;
	}
	case "Gebruiker":
	{
		//redirect to Gebruiker loggedin page.
		header( 'Location: /home' );
		break;
	}
	case "Onderhoud":
	{
		//redirect to Onderhoudsmedewerker loggedin page.
		header( 'Location: /home' );
		break;
	}
	default:
	{
		//stay on login page, but show error.
		header( 'Location: /login?error=1' );
		break;
	}
}
?>