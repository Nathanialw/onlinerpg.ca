
<?php
    include_once 'header.php';
?>

<?php
    include 'body.php';
?>


<h1>Browser RPG</h1>

<?php 
    if (isset($_SESSION["useruid"])) {
        $useruid = htmlspecialchars($_SESSION["useruid"]);
        echo "<p>Hello there " . "$useruid" . "</p>";
    }
    ?>

    
<?php
    include 'game.php';
?>

<!-- the game map -->

<!-- the game interface -->

<!-- the game chat -->

<?php
    include_once 'footer.php';
?>