<?php
    include 'header.php'
?>


<section class="signup-form">
    <h2>Log in</h2>
    <div class="signup-form-form">
        <form action="includes/login.h.php" method="post"> 
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