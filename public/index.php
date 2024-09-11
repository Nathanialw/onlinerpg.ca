
<?php
    include_once 'header.php';
?>

<?php
    include 'body.php';
?>

<section>
    <h1 class="wrapper">Browser RPG</h1>
    <!-- // if (!isset($_POST["startGame"])) { -->
    <form method="post">
        <input type="submit" name="startGame" id="startGame" class="wrapper btn btn-submit" value="Start Game"/>
    </form>
    <!-- // } -->
    <!-- // ?> -->
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
        echo "<p>Hello there</p>";
        include 'game.php';
    }    
?>




<?php
    include_once 'footer.php';
?>