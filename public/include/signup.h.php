<?php

if (isset($_POST["submit"])) {
    // Sanitize form data
    $_POST = array_map('trim', $_POST);

    // Include the file that processes the form data
    include '/var/www/saycum.com/private/include/signup.h.php';
    
    if ($check = CheckSubmit($_POST)) {
        
        if (check == 1 ) {
            header("Location: ../signup.php?error=emptyinput");
            exit();   
        }
        else if (check == 2) {
            header("Location: ../signup.php?error=invaliduid");
            exit();
        }
        else if (check == 3) {
            header("Location: ../signup.php?error=invalidemail");
            exit();
        }
        else if (check == 4) {
            header("Location: ../signup.php?error=passwordsdontmatch");
            exit();
        }
        // else if (check == 5) {
        //     header("Location: ../signup.php?error=usernametaken");
        //     exit();
        // }        
    }
    
    else {
        header("Location: ../signup.php");
        exit();
    }
}