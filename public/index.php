
<?php
    include_once 'header.php';
?>

<?php
    include 'body.php';
?>

<section>
    <h1 class="wrapper">Browser RPG</h1>
    <button type="submit" name="startGame" id="startGame btn">Start!</button>
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
    if (isset($_POST["startGame"])) {
        include 'game.php';
    }
    ?>




<?php
    include_once 'footer.php';
?>