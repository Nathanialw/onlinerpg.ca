<?php


if (isset($_POST["submit"])) {
    include '/var/www/saycum.com/private/include/signup.h.php';
    // Sanitize form data

    // Include the file that processes the form data
    
    $name = $_POST['name'];
    $email = $_POST['email'];
    $username = $_POST['uid'];
    $pwd = $_POST['pwd'];
    $pwdRepeat = $_POST['pwdrepeat'];
    
    $check = CheckSubmit($name, $email, $username, $pwd, $pwdRepeat);
        
    if ($check == 0) {
        header("Location: ../signup.php");
        exit();
    }
    else if ($check == 1 ) {
        header("Location: ../signup.php?error=emptyinput");
        exit();   
    }
    else if ($check == 2) {
        header("Location: ../signup.php?error=invaliduid");
        exit();
    }
    else if ($check == 3) {
        header("Location: ../signup.php?error=invalidemail");
        exit();
    }
    else if ($check == 4) {
        header("Location: ../signup.php?error=passwordsdontmatch");
        exit();
    }
    else if ($check == 5) {
        header("Location: ../signup.php?error=usernametaken");
        exit();
    }        

}