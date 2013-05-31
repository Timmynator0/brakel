<form id="loginForm" action="" method="post">
	<?php
		if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['login']))
		{
			$db->prepare("SELECT *
					 	  FROM   `user`
					 	  WHERE  `username` = :username
					 	  AND    `password` = :password
					 	  LIMIT 1")
			   ->bindValue('username', $_POST['username'])
			   ->bindValue('password', sha1($_POST['password']))
			   ->execute();
			if ($db->num_rows() == 1)
			{
				$_SESSION['user'] = $db->fetch_assoc();
				header('Location: /home');	
			}
			else
			{
				echo '<div class="errorLogin"><h1>Fout tijdens inloggen</h1></div>';	
			}		
		}
	?>
	<div>
		<select name="username" size="1">
			<?php
			$db->query("SELECT `username`
						FROM   `user`
						ORDER BY `username` ASC");
			while ($user = $db->fetch_assoc())
			{
				echo '<option value="' . $user['username'] . '">' . ucfirst($user['username']) . '</option>';
			}
			?>
		</select>
		<span>Gebruiker</span>
	</div>
	<div>
		<input type="password" name="password" />
		<span>Wachtwoord</span>
	</div>
	<div>
		<input type="submit" name="login" value="Inloggen" />
	</div>
</form>	