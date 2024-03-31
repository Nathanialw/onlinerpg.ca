<?php


function CheckSubmit($_POST) {
    $name = $_POST['name'];
    $email = $_POST['email'];
    $username = $_POST['uid'];
    $pwd = $_POST['pwd'];
    $pwdRepeat = $_POST['pwdrepeat'];
    
    require_once 'dbh.h.php';
    require_once 'functions.h.php';
    
    if (emptyInputSignup($name, $email, $username, $pwd, $pwdRepeat) !== false) {
       return 1;
    }
    if (invalidUid($username) !== false) {
        return 2;
    }
    if (invalidEmail($email) !== false) {
        return 3;
    }
    if (pwdMatch($pwd, $pwdRepeat) !== false) {
        return 4;
    }
    // if (uidExists($conn, $username, $email) !== false) {
    //     header("Location: ../signup.php?error=usernametaken");
    //     exit();
    // }
    // createUsers($conn, $name, $email, $username, $pwd);
}


    