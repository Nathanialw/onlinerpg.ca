<?php
require_once 'dbh.h.php';
require_once 'functions.h.php';

function Login($username, $pwd) {

    if (emptyInputLogin($username, $pwd) !== false) {
        return true;
    }
    
    // loginUser($conn, $username, $pwd);
    return false;
}
