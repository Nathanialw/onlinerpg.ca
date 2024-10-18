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
        //goblins
            //forest = +dexterity +intelligence
            //cave = +dexterity +strength
            //swamp = +dexterity +constitution      
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
<section class="canvasContainer">
    <div id="gameCanvas"></div>
</section>

<section class="options-container">
    <article class='options'>    
        <ul>
            <li class="option"><button id="Human" class='btn btn-block'>Human</button></li>
            <li class="option"><button id="Elf" class='btn btn-block'>Elf</button></li>
            <!-- <li><button id="Orc" class='btn btn-submit'>Orc</button></li> -->
            <!-- <li><button id="Dwarf" class='btn btn-submit'>Dwarf</button></li> -->
            <!-- <li><button id="Goblin" class='btn btn-submit'>Goblin</button></li> -->
        </ul>

        <ul>
            <li class="option"><button id="Male" class='btn btn-block'>Male</button></li>
            <li class="option"><button id="Female" class='btn btn-block'>Female</button></li>
        </ul>

        <ul>
            <li class="option"><button id="Fighter" class='btn btn-block'>Fighter</button></li>
            <li class="option"><button id="Mystic" class='btn btn-block'>Mystic</button></li>
        </ul>

        <ul>
            <li class="option"><button id="Good" class='btn btn-block'>Good</button></li>
            <li class="option"><button id="Neutral" class='btn btn-block'>Neutral</button></li>
            <li class="option"><button id="Evil" class='btn btn-block'>Evil</button></li>
        </ul>
    </section>
</section>

<section class="hero-wrapper">
    <h1 id="hero-class" class="hero-class"></h1>
</section>

<section class='nameInput'>
    <form method='POST' id="myForm">
        <input class="form-input form-row" type="text" id="name" name="name" value="" required minlength="3" autocomplete="off">
        <br> 
    </form>
</section>

<section class='startButton'>
    <button id="startGame" class='btn btn-center'>Start Game</button>
    <br> 
    <div id="nameError" class="error-message" style="color: red; display: none;">Name must be at least 3 characters long.</div>
    <div id="loading" class="loading-message" style="color: white; display: none;"></div>
    <div id="loading-text" class="loading-message" style="color: white; display: none;">Loading...</div>
</section>

<script src="/js/frontend/charCreate.js" type="module"></script>
<script src="/js/networking/socket.js" type="module"></script>
<script src="/js/libs/howler.core.js" type="module"></script>
<script src="/js/libs/pixi.js"></script>
