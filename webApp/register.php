<?php

require "core.php";
$status = $status_class = "";

// verify credentials
if (isset($_POST['submit'])){
    $dataInserted = register();

    if($dataInserted){
        // send status message as successfully inserted
        $status = "User registered successfully!";
        $status_class = "success";
    }else{
        $status = "User registration failed!";
        $status_class = "error";
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1,maximum-scale=1">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/gh/lykmapipo/themify-icons@0.1.2/css/themify-icons.css">
    <link rel="stylesheet" href="styles.css">

    <title>IRSS| Register</title>
</head>

<body>
<div class="form-container" >
    <form action="register.php" method="post" onsubmit="return validateRegistration()">
        <div class="form-header">Robotic Arm Remote Access Registration</div>
        <div class="inputs">
            <div><input id="username" type="text" placeholder="Username" name="username"></div>
            <div class="error" id="username_error"></div>

            <div><input id="password" type="password" placeholder="Password" name="password"></div>
            <div class="error" id="password_error"></div>

            <div><input id="confirmpassword" type="password" placeholder="Confirm password" name="confirmpassword"></div>
            <div class="error" id="confirmpassword_error"></div>

            <div class="<?php echo $status_class; ?>" > <?php echo $status; ?> </div>
            <div><input type="submit" name="submit" value="-->"></div>
        </div>
    </form>
</div>

<script src="main.js"></script>


</body>
</html>
