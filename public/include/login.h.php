<?php



if (isset($_POST["submit"])) {
    include '/var/www/saycum.com/private/include/login.h.php';
    
    $username = $_POST["uid"];
    $pwd = $_POST["pwd"];
    
    if (Login($username, $pwd) !== false) {
        header("location: ../login.php?error=emptyinput");
        exit();
    }
    else {
        header("location: ../login.php");
        exit();
    }
}
