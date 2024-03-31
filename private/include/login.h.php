<?php
require_once 'dbh.h.php';
require_once 'functions.h.php';

function Login($username, $pwd) {

    if (emptyInputLogin($username, $pwd) !== false) {
        header("location: login.php?error=emptyinput");
        exit();
    }
    
    // loginUser($conn, $username, $pwd);
    return false;
}
