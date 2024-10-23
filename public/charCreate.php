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

<section id="chracterCreate"></section>

<section class='connectButton button'>
    <button id="connect" class='btn btn-center' style="margin-top: 15rem; width: 40rem; height: 7rem; font-size: 20">Connect</button>
    <br> 
    <div id="nameError" class="error-message" style="color: red; display: none;">Failed to connect.</div>
    <div id="connect-text" class="connect-message" style="color: white; display: none;">Connecting...</div>
</section>


<script src="/js/frontend/charCreate.js" type="module"></script>
<script src="/js/networking/socket.js" type="module"></script>
<script src="/js/libs/howler.core.js" type="module"></script>
<script src="/js/libs/pixi.js"></script>
