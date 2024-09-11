<?php
require_once 'dbh.h.php';
require_once 'functions.h.php';

function Login($username, $pwd) {

    if (emptyInputLogin($username, $pwd) !== false) {
        header("location: login.php?error=emptyinput");
        echo "empty input";        
        exit();
    }
    
    // loginUser($conn, $username, $pwd);
    header("location: ../login.php");
    echo "login user";
    exit();
}
