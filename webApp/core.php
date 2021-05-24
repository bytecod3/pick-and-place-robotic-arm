<?php
require "database.php";

// INPUT SANITIZER
function escape_string($val){
    global $db;
    return mysqli_real_escape_string($db, trim($val));
}

// ERRORS ARRAY
$errors = array();

// USER REGISTRATION
function register(){
    // define global variables to be available in function
    global $db, $errors;

    // escape the received inputs from form
    $username = escape_string($_POST['username']);
    $password = escape_string($_POST['password']);
    $confirmed_password = escape_string($_POST['confirmpassword']);

    // perform input validation
    if (empty($username)){
        array_push($errors, "Username required.");
    }

    if (empty($password)){
        array_push($errors, "Password required.");
    }

    if (empty($confirmed_password)){
        array_push($errors,"Please confirm your password.");
    }

    if ($password != $confirmed_password){
        array_push($errors, "Passwords do not match.");
    }

    // register user if there are no errors in the form
    if (count($errors) == 0) {
        // encrypt password before storing
        $password = md5($password);

        $query = "INSERT INTO users(username, password) values('$username','$password')";
        mysqli_query($db, $query);

        return true;

    }else{
        return false;
    }
}

// LOGIN USER
function login($username, $password){
    global $db, $errors;
    
    // clean form inputs
    $username = escape_string($username);
    $password = escape_string($password);

    // validate form
    if(empty($username)){
        array_push($errors, "Username required.");
    }

    if(empty($password)){
        array_push($errors, "Password required");
    }

    // attempt login if no errors on form
    if(count($errors) == 0){
        $password = md5($password);

        $query = "SELECT * FROM users WHERE username ='$username' AND password = '$password' LIMIT 1";
        $results = mysqli_query($db, $query);

        if(mysqli_num_rows($results) == 1){
            // user found

            // assign username to variable
            $logged_in_user_id = mysqli_fetch_assoc($results);
            $uname = $logged_in_user_id['username'];

            // initialize session for the current user
            session_start();
            $_SESSION['username'] = $uname;

            // redirect to main dashboard page
            header("location: index.php");


        }else{
            // no such user
            array_push($errors, "Wrong username or password.");
            return false;
        }
    }
}