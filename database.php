<?php
try {
    $db = mysqli_connect("localhost", "edwin", "edwin", "wazirobot");
}catch(Exception $e){
    echo $e;
}
