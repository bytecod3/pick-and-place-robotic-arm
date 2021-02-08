<?php

require "core.php";

if (isset($_POST['submit'])){
    // get form data
    $username = $_POST['username'];
    $password = $_POST['password'];

    // login user
    login($username, $password);

}

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1,maximum-scale=1">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/gh/lykmapipo/themify-icons@0.1.2/css/themify-icons.css">
    <link rel="stylesheet" href="styles.css">
    <title>IRSS| LOGIN</title>
</head>

<body>
<div class="form-container" >

    <form action="login.php" method="post" onsubmit="return validateLogin();">
        <div class="form-header">Robotic Arm Remote Access Login</div>

        <div class="error">
            <?php
                foreach ($errors as $err){
                    echo $err;

                }
            ?>
        </div>

        <div class="inputs">
            <div><input id="username" type="text" placeholder="Username" name="username"></div>
            <div id="username_error" class="error"></div>

            <div><input id="password" type="password" placeholder="Password" name="password"></div>
            <div id="password_error" class="error"></div>

            <div><input type="submit" name="submit" value="-->"></div>
        </div>

    </form>
</div>

<!--javascript-->
<!--<script src="main.js"></script>-->
<script src="main.js"></script>
</body>
</html>