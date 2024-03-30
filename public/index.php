
<?php
    include_once 'header.php';
?>

<h1>Browser RPG</h1>

<?php 
    if (isset($_SESSION["useruid"])) {
        echo "<p>Hello there " . $_SESSION["useruid"] . "</p>";
    }
?>

<!-- the game map -->

<!-- the game interface -->

<!-- the game chat -->

<?php
    include_once 'footer.php';
?>