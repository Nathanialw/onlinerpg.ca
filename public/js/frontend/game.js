import { Init } from "../sound/sound.js";
Init();

export const app = new PIXI.Application();
export let viewportWidth = 41;
export let cellSize = 24;

function Input_Name() {
    let name = prompt("Please enter your name", "Player");    
}

function Character_Select() {
    //select race: human or elf
    
    //class fighter
}


async function Start_Game() {//13
    await app.init({ width: cellSize * viewportWidth, height: cellSize * viewportWidth })
    document.getElementById('gameCanvas').appendChild(app.canvas);
}

function Splash_Screen() {
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

export function Set_Map_Within_Viewport(visionWidth) {
    let vision = ((viewportWidth - 1) / 2) - ((visionWidth - 1) / 2);
    return vision;
}

export function Set_Player_Withing_Viewport() {
    
    return ((viewportWidth - 1) / 2);
}