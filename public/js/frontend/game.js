import { Init } from "../sound/sound.js";
Init();

export const app = new PIXI.Application();

function Input_Name() {
    let name = prompt("Please enter your name", "Player");    
}

function Character_Select() {
    //select race: human or elf
    
    //class fighter
}


async function Start_Game() {
    await app.init({ width: 24*13, height: 24*13 })
    document.getElementById('gameCanvas').appendChild(app.canvas);
}

function Splash_Screen() {
    //display splash screen
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

        //fighter+good= paladin
        //fighter+neutral= fighter
        //fighter+evil= barbarian 

        //mage+good = priest
        //mage+neutral= mage 
        //mage+evil= warlock

    //start game
    Start_Game();
}
Splash_Screen()

export function Close_Game() {
    document.getElementById('gameCanvas').removeChild(app.canvas);    
    app.destroy(true, {children: true, texture: true, baseTexture: true});
        // Create a form element
        const form = document.createElement('form');
        form.method = 'post';
    
        // Create an input element
        const input = document.createElement('input');
        input.type = 'submit';
        input.name = 'restartGame';
        input.id = 'restartGame';
        input.className = 'wrapper btn btn-submit';
        input.value = 'Restart Game';
    
        // Append the input to the form
        form.appendChild(input);
    
        // Append the form to the gameCanvas
        document.getElementById('gameCanvas').appendChild(form);
    
}