<?php
    session_start();
?>

<!doctype html>
<html>
    <head>
        <meta charset="UTF-8" />
        <meta http-equiv="X-UA-Compatible" content="IE=edge"/>
        <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
        <link rel="icon"       href="/assets/icons/css/all.css" title="icons"/>
        <link rel="stylesheet" href="/assets/icons/css/all.css"/>
        
        <link rel="stylesheet" href="/css/account.css">
        <link rel="stylesheet" href="/css/nav.css" />
        <link rel="stylesheet" href="/css/footer.css"/>
        <link rel="stylesheet" href="/css/style.css"/>
        <link rel="stylesheet" href="/css/game.css"/>
    </head>
    
    <body>
        <header class="nav-center" id="nav-bar">
            <div class='navbar'>
                <a href='/'><h4 class='logo'>logo</h4></a>
                <button type='button' class='bars' id='bars'>
                    <i class='fa fa-bars'></i>
                </button>
            </div>
            
            <nav>
                <ul class='nav-links' id='nav-links'>
                    <li><a href="index.php">Home</a></li> 
                    <li><a href="discover.php">About Us</a></li> 
                    <li><a href="blog.php">Find Blogs</a></li> 
                    <li><a href="/goapp">Go App</a></li> 
                    <?php 
                    if (isset($_SESSION["useruid"])) {
                        echo "<li><a href='profile.php'>Profile Page</a></li>";
                        echo "<li><a href='logout.php'>Log Out</a></li>";
                    }
                    else {
                        echo "<li><a href='signup.php'>Sign Up</a></li>";
                        echo "<li><a href='login.php'>Log in</a></li>";
                    }
                    ?>
                </ul>
            </nav>
        </header>     

        <script src="/js/frontend/nav.js"></script>            