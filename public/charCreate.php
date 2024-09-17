<!-- // Purpose: Page for creating a character -->

<!-- //display splash screen
    //get name
    Input_Name();
    //get gender
        //male = +strength +intelligence
        //female = -strength -intelligence +charisma
    //get race
        //elf/human/orc/dwarfs
            //elf= +vision +dexterity
            //human= +intelligence +strength
            //orc= +strength +constitution -intelligence
            //dwarf= +constitution +strength -dexterity
    //get subrace
        //elves
            //wood= +dexterity +strength
            //high= +intelligence +charisma
            //dark= +dexterity +charisma
        //humans
            //nord= +strength +constitution
            //imperial= +intelligence +charisma
            //breton= +intelligence +dexterity
        //orcs
            //mountain= +strength +constitution
            //plains= +strength +dexterity 
            //swamp= +constitution +intelligence
        //dwarfs
            //mountain= +constitution +strength
            //hill= +constitution +dexterity
            //deep= +constitution +intelligence
    //get class
        //fighter/mystic
    //alignment
        //good/neutral/evil

        //fighter+good = paladin -> crusader -> templar
        //fighter+neutral= barbarian -> berserker -> warlord
        //fighter+evil = death knight -> dark lord -> demon lord

        //mystic+good = priest -> bishop -> cardinal 
        //mystic+neutral= wizard -> archmage -> sorcerer
        //mystic+evil= warlock -> necromancer -> lich 
 -->

 <div id="gameCanvas"></div>

<section class='startButton'>
    <form method='post'>
        <label class="form-label" for="name">Name:</label>
        <input class="form-input form-row" type="text" id="name" name="name" placeholder="John">
        <br>
        <label class="form-label" for="gender">Gender:</label>
        <span class="form-adjacent">
            <select class="form-input form-row form-adjacent" id="gender" name="gender" required>
                <option value="0">Male</option>
                <option value="1">Female</option>
            </select>
        </span>
        <br>
        <label class="form-label" for="race">Race:</label>
        <span class="form-adjacent">
            <select class="form-input form-row form-adjacent" id="race" name="race" required>
                <option value="7">Human</option>
                <option value="4">Elf</option>
            </select>
        </span>
        <br>
        <label class="form-label" for="class">Class:</label>
        <span class="form-adjacent">
            <select class="form-input form-row form-adjacent" id="class" name="class" required>
                <option value="0">Fighter</option>
                <option value="1">Mystic</option>
            </select>
        </span>
        <br>
        <label class="form-label" for="alignment">alignment:</label>
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
<script src="/js/libs/howler.core.js" type="module"></script>
<script src="/js/libs/pixi.js"></script>
<!-- loadScript('/js/libs/howler.core.js');
loadScript('/js/libs/pixi.js'); -->
