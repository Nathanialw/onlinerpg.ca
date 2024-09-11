
<?php
    include_once 'header.php';
?>

<?php
    include 'body.php';
?>

<h1 class="wrapper">Browser RPG</h1>
<!-- // if (!isset($_POST["startGame"])) { -->

<!-- // } -->
<!-- // ?> -->



<?php 
    // if (isset($_SESSION["useruid"])) {
    //     $useruid = htmlspecialchars($_SESSION["useruid"]);
    //     echo "<p>Hello there " . "$useruid" . "</p>";
    //     //<!-- the game map -->
    //     include 'game.php';
    //     //<!-- the game interface -->
        
    //     //<!-- the game chat -->
        
    // }
    if (isset($_POST["startGame"])) {
        include 'game.php';
    }    
    elseif (isset($_POST["restartGame"])) {
        include 'game.php';        
    }
    else {
        echo "<form method='post'>
                <input type='submit' name='startGame' id='startGame' class='wrapper btn btn-submit' value='Start Game'/>
            </form>";
    }
?>




<?php
    include_once 'footer.php';
?>