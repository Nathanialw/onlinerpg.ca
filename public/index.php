
<?php
    include_once 'header.php';
?>

<?php
    include 'body.php';
?>

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
    
    include 'charCreate.php';         
?>




<?php
    include_once 'footer.php';
?>