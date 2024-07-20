<?php
    include 'header.php';
    include 'body.php';

    if (isset($_POST["submit"])) {
        include '/var/www/onlinerpg.ca/private/include/signup.h.php';
    
        $name = $_POST['name'];
        $email = $_POST['email'];
        $username = $_POST['uid'];
        $pwd = $_POST['pwd'];
        $pwdRepeat = $_POST['pwdrepeat'];
        
        CheckSubmit($name, $email, $username, $pwd, $pwdRepeat);    
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
        $error = htmlspecialchars($_GET["error"]);
        if ($error == "emptyinput") {
            echo "<p>Fill in all fields!</p>";
        }
        else if ($error == "invaliduid") {
            echo "<p>Choose a proper username!</p>";
        }
        else if ($error == "invalidemail") {
            echo "<p>Choose a proper email!</p>";
        }
        else if ($error == "passwordsdontmatch") {
            echo "<p>Passwords do not match!</p>";
        }
        else if ($error == "stmtfailed") {
            echo "<p>Something went wrong, try again!</p>";
        }
        else if ($error == "usernametaken") {
            echo "<p>Username already taken!</p>";
        }
        else if ($error == "none") {
            echo "<p>You have signed up, Welcome!</p>";
        }
    }

?>


<?php
    include 'footer.php'
?>