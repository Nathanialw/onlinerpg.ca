<?php
    include 'header.php'

    if (isset($_POST["submit"])) {
        include '/var/www/saycum.com/private/include/login.h.php';
        
        $username = $_POST["uid"];
        $pwd = $_POST["pwd"];
        
        if (Login($username, $pwd) !== false) {
            header("location: ../login.php?error=emptyinput");
            exit();
        }
        else {
            header("location: ../login.php");
            exit();
        }
    }
    
?>


<section class="signup-form">
    <h2>Log in</h2>
    <div class="signup-form-form">
        <form action="include/login.h.php" method="post"> 
            <input type="text" name="uid" placeholder="Email or Username...">
            <input type="password" name="pwd" placeholder="Password...">
            <button type="submit" name="submit">Log In</button>
        </form>
    </div>
</section> 


<?php
if (isset($_GET["error"])) {
    if ($_GET["error"] == "emptyinput") {
        echo "<p>Fill in all fields!</p>";
    }
    else if ($_GET["error"] == "wronglogin") {
        echo "<p>Incorrect login info!</p>";
    }
}
?>


<?php
    include 'footer.php'
?>