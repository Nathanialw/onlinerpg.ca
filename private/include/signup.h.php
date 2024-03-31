<?php

require_once 'dbh.h.php';
require_once 'functions.h.php';

function CheckSubmit($name, $email, $username, $pwd, $pwdRepeat) {
    
    if (emptyInputSignup($name, $email, $username, $pwd, $pwdRepeat) !== false) {
        header("Location: ../signup.php?error=emptyinput");
        exit();   
    }
    if (invalidUid($username) !== false) {
        header("Location: ../signup.php?error=invaliduid");
        exit();
    }
    if (invalidEmail($email) !== false) {
        header("Location: ../signup.php?error=invalidemail");
        exit();
    }
    if (pwdMatch($pwd, $pwdRepeat) !== false) {
        header("Location: ../signup.php?error=passwordsdontmatch");
        exit();
    }
    // if (uidExists($conn, $username, $email) !== false) {
    //     header("Location: ../signup.php?error=usernametaken");
    //     exit();
    // }
    // createUsers($conn, $name, $email, $username, $pwd);

    header("Location: ../signup.php");
    exit();
}


    