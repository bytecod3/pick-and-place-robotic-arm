
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