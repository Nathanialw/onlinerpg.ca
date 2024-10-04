<?php
    session_start();
?>

<!doctype html>
<html lang="en">
    <head>
        <title>Browser RPG, an ASCII game where you explore and fight monsters</title>
        <meta name="description" content="Browser RPG game in the vein of rogue. An ASCII-graphics roguelike game where you can explore the world and fight monsters and level up.">
        <meta http-equiv="Content-Security-Policy" content="script-src 'self' https://ajax.googleapis.com; 'nonce-<?php echo $nonce; ?>'; object-src 'none'" >
        <meta http-equiv="X-UA-Compatible" content="IE=edge"/>
        <meta charset="UTF-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0"/>

        <script src="https://ajax.googleapis.com/ajax/libs/webfont/1.6.26/webfont.js" nonce="<?php echo $nonce; ?>">></script>
        <script src="/js/frontend/webfont-loader.js"></script>
        
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