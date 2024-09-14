
<?php
    include_once 'header.php';
?>

<?php
    include 'body.php';
?>

<section class="wrapper">
    <h1 class="splashContent">Browser RPG</h1>
    <p class="splashContent">Welcome to the Browser RPG game. This is a simple text-based game where you can explore the world, fight monsters, and interact with other players. To get started, click the "Start Game" button below.</p>
</section>

<?php 
    // if (isset($_SESSION["useruid"])) {
    //     $useruid = htmlspecialchars($_SESSION["useruid"]);
    //     echo "<p>Hello there " . "$useruid" . "</p>";
    //     //<!-- the game map -->
    //     include 'game.php';
    //     //<!-- the game interface -->
        
    //     //<!-- the game chat -->
        
    // }
    // if (isset($_POST["startGame"])) {
    //     include 'game.php';
    // }    
    // elseif (isset($_POST["restartGame"])) {
    //     include 'game.php';        
    // }
    if (isset($_POST["enterGame"])) {
        include 'charCreate.php';     
    }
    else {
        include 'enterGame.php';     
    }
?>




<?php
    include_once 'footer.php';
?>