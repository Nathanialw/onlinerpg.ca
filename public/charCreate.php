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

 <div id="gameCanvas"></div>

<section class='startButton'>
    <form method='POST' id="myForm">
        <label class="form-label" for="name">Name:</label>
        <input class="form-input form-row" type="text" id="name" name="name" value="John">
        <br> 
    </form>

    <label for="Species: "></label>
    <button id="Human" class='btn btn-submit'>Human</button>
    <button id="Elf" class='btn btn-submit'>Elf</button>

    <label for="Gender: "></label>
    <button id="Male" class='btn btn-submit'>Male</button>
    <button id="Female" class='btn btn-submit'>Female</button>


    <label for="Class: "></label>
    <button id="Fighter" class='btn btn-submit'>Fighter</button>
    <button id="Mystic" class='btn btn-submit'>Mystic</button>

    <label for="Alignment: "></label>
    <button id="Good" class='btn btn-submit'>Good</button>
    <button id="Neutral" class='btn btn-submit'>Neutral</button>
    <button id="Evil" class='btn btn-submit'>Evil</button>

    
    <button id="startGame" class='btn btn-submit'>Start Game</button>
</section>

<script src="/js/frontend/charCreate.js" type="module"></script>
<script src="/js/networking/socket.js" type="module"></script>
<script src="/js/libs/howler.core.js" type="module"></script>
<script src="/js/libs/pixi.js"></script>
<!-- loadScript('/js/libs/howler.core.js');
loadScript('/js/libs/pixi.js'); -->
