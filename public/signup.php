<?php
    include 'header.php';

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
?>

    <section class="signup-form">
        <h2>Sign Up</h2>
        <div class="signup-form-form">
            <form action="" method="post"> 
                <input type="text" name="name" placeholder="Fill name...">
                <input type="text" name="email" placeholder="Email...">
                <input type="text" name="uid" placeholder="Username...">
                <input type="password" name="pwd" placeholder="Password...">
                <input type="password" name="pwdrepeat" placeholder="Repeat password...">
                <button type="submit" name="submit">Sign Up</button>
            </form>
        </div>
    </section> 

<?php


    if (isset($_GET["error"])) {
        if ($_GET["error"] == "emptyinput") {
            echo "<p>Fill in all fields!</p>";
        }
        else if ($_GET["error"] == "invaliduid") {
            echo "<p>Choose a proper username!</p>";
        }
        else if ($_GET["error"] == "invalidemail") {
            echo "<p>Choose a proper email!</p>";
        }
        else if ($_GET["error"] == "passwordsdontmatch") {
            echo "<p>Passwords do not match!</p>";
        }
        else if ($_GET["error"] == "stmtfailed") {
            echo "<p>Something went wrong, try again!</p>";
        }
        else if ($_GET["error"] == "usernametaken") {
            echo "<p>Username already taken!</p>";
        }
        else if ($_GET["error"] == "none") {
            echo "<p>You have signed up, Welcome!</p>";
        }
    }

?>


<?php
    include 'footer.php'
?>