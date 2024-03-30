<?php

echo "0";

if (isset($_POST['submit'])) {
    
    $name = $_POST['name'];
    $email = $_POST['email'];
    $username = $_POST['uid'];
    $pwd = $_POST['pwd'];
    $pwdRepeat = $_POST['pwdrepeat'];
    
    require_once 'dbh.h.php';
    require_once 'functions.h.php';
    
    echo "1";
    if (emptyInputSignup($name, $email, $username, $pwd, $pwdRepeat) !== false) {
        header("Location: ../public/signup.php?error=emptyinput");
        echo "2";
        exit();
    }
    if (invalidUid($username) !== false) {
        echo "3";
        header("Location: ../public/signup.php?error=invaliduid");
        exit();
    }
    if (invalidEmail($email) !== false) {
        echo "4";
        header("Location: ../public/signup.php?error=invalidemail");
        exit();
    }
    if (pwdMatch($pwd, $pwdRepeat) !== false) {
        echo "5";
        header("Location: ../public/signup.php?error=passwordsdontmatch");
        exit();
    }
    if (uidExists($conn, $username, $email) !== false) {
        echo "6";
        header("Location: ../public/signup.php?error=usernametaken");
        exit();
    }
    echo "7";
    createUsers($conn, $name, $email, $username, $pwd);
}
else {
    echo "8";
    header("Location: ../public/signup.php");
    exit();
}

    