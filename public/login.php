<?php
    include 'header.php';
    include 'body.php';
?>


<?php

    if (isset($_POST["submit"])) {
        include '/var/www/onlinerpg.ca/private/include/login.h.php';
        $username = $_POST["uid"];
        $pwd = $_POST["pwd"];
        Login($username, $pwd);        
    }    
?>


<section class="signup-form">
    <h2>Log in</h2>
    <div class="signup-form-form">
        <form action="" method="post"> 
            <input type="text" name="uid" placeholder="Email or Username...">
            <input type="password" name="pwd" placeholder="Password...">
            <button type="submit" name="submit">Log In</button>
        </form>
    </div>
</section> 

<?php
if (isset($_GET["error"])) {
    $error = htmlspecialchars($_GET["error"]);
    if ($error == "emptyinput") {
        echo "<p>Fill in all fields!</p>";
    }
    else if ($error == "wronglogin") {
        echo "<p>Incorrect login info!</p>";
    }
}
?>


<?php
    include 'footer.php'
?>