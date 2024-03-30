<?php
if (isset($_POST["submit"])) {
        $_POST = array_map('trim', $_POST);
        echo $_POST["name"];
        echo $_POST["email"];
        echo $_POST["uid"];
        echo $_POST["pwd"];
        echo $_POST["pwdrepeat"];
        include '/var/www/saycum.com/private/signup.h.php';
    }