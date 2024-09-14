<!-- // Purpose: Page for creating a character -->

<!-- //display splash screen
    //get name
    Input_Name();
    //get gender
        //male = +strength +intelligence
        //female = -strength -intelligence +charisma
    //get race
        //elf/human
            //elf= +vision +dexterity
            //human= +intelligence +strength
    //get class
        //fighter/mage
    //alignment
        //good/neutral/evil

        //fighter+good = paladin -> crusader -> templar
        //fighter+neutral= barbarian -> berserker -> warlord
        //fighter+evil = death knight -> dark lord -> demon lord

        //mage+good = priest -> bishop -> cardinal 
        //mage+neutral= wizard -> archmage -> sorcerer
        //mage+evil= warlock -> necromancer -> lich 
 -->

 <div id="gameCanvas"></div>

<section class='startButton'>
    <form method='post'>
        <label class="form-label" for="title">Name:</label>
        <input class="form-input form-row" type="text" id="name" name="name" required>
        <br>
        <label class="form-label" for="image">Gender:</label>
        <span class="form-adjacent">
            <select class="form-input form-row form-adjacent" id="gender" name="gender" required>
                <option value="0">Male</option>
                <option value="1">Female</option>
            </select>
        </span>
        <br>
        <label class="form-label" for="image">Race:</label>
        <span class="form-adjacent">
            <select class="form-input form-row form-adjacent" id="race" name="race" required>
                <option value="0">Human</option>
                <option value="1">Elf</option>
            </select>
        </span>
        <br>
        <label class="form-label" for="image">Class:</label>
        <span class="form-adjacent">
            <select class="form-input form-row form-adjacent" id="class" name="class" required>
                <option value="0">Fighter</option>
                <option value="1">Mage</option>
            </select>
        </span>
        <br>
        <label class="form-label" for="image">alignment:</label>
        <span class="form-adjacent">
            <select class="form-input form-row form-adjacent" id="alignment" name="alignment" required>
                <option value="0">Good</option>
                <option value="1">Neutral</option>
                <option value="2">Evil</option>
            </select>
        </span>
        <br>
        <input type='submit' name='startGame' id='startGame' class='btn btn-submit' value='Start Game'/>
    </form>
</section>

<script src="/js/frontend/charCreate.js" type="module"></script>
<script src="/js/networking/socket.js" type="module"></script>

