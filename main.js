
/* REGISTRATION FORM VALIDATION */

function validateRegistration(){

    // get error fields
    let username_error = document.getElementById("username_error");
    let password_error = document.getElementById("password_error");
    let confirmpassword_error = document.getElementById("confirmpassword_error");

    //get form values
    let username = document.getElementById("username").value;
    let password = document.getElementById("password").value;
    let confirmpassword = document.getElementById("confirmpassword").value;


    // fields should not be empty
    if(username.length === 0){
        username_error.innerText = "Username required";
        return false;
    }else{
        username_error.innerText = "";
    }

    if(password.length === 0){
        password_error.innerText = "Password required";
        return false;
    }else{
        password_error.innerText = "";
    }

    if(password !== confirmpassword){
        confirmpassword_error.innerText = "Passwords do not match";
        return false;
    }else{
        confirmpassword_error.innerText = "";
    }

    return true;


}

/* VALIDATE LOGIN */
function validateLogin(){
    // get error div
    let username_error = document.getElementById("username_error");
    let password_error = document.getElementById("password_error");

    // get form fields
    let username = document.getElementById("username");
    let password = document.getElementById("password");

    // fields  should not be empty
    if(username.length === 0){
        username_error.innerText = "Username required.";
        return false;
    }else{
        username_error.innerText = "";
    }

    if(password.length === 0){
        password_error.innerText = "Password required.";
        return false;
    }else{
        password_error.innerText = "";
    }

    // if no errors
    return true;
}

function toggleMode(){
    // change the control option for operation status
    let armStatus = document.getElementById("status");

    if (armStatus.innerText === "Offline") {
        armStatus.innerText = "Online";
        armStatus.style.color = "green  ";
        document.getElementById("change-op-mode").innerText = "Stop";
    }else{
        armStatus.innerText = "Offline";
        armStatus.style.color = "Red";
        document.getElementById("change-op-mode").innerText = "Start";
    }
}

