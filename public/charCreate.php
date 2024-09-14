<!-- // Purpose: Page for creating a character -->

<!-- //display splash screen
    //get name
    Input_Name();
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


<section class='startButton'>
    <form method='post'>
        <label class="form-label" for="title">Name:</label>
        <input class="form-input form-row" type="text" id="name" name="name" required>
        <br>
        <label class="form-label" for="image">Race:</label>
        <span class="form-adjacent">
            <select class="form-input form-row form-adjacent" id="race" name="race" required>
                <option value="elf">Elf</option>
                <option value="human">Human</option>
            </select>
        </span>
        <br>
        <label class="form-label" for="image">Class:</label>
        <span class="form-adjacent">
            <select class="form-input form-row form-adjacent" id="class" name="class" required>
                <option value="fighter">Fighter</option>
                <option value="mage">Mage</option>
            </select>
        </span>
        <br>
        <label class="form-label" for="image">alignment:</label>
        <span class="form-adjacent">
            <select class="form-input form-row form-adjacent" id="alignment" name="alignment" required>
                <option value="good">Good</option>
                <option value="neutral">Neutral</option>
                <option value="evil">Evil</option>
            </select>
        </span>
        <br>
        <input type='submit' name='startGame' id='startGame' class='splashContent btn btn-center btn-submit' value='Start Game'/>
    </form>
</section>";        
