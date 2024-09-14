import { Init } from "../sound/sound.js";
Init();

export const app = new PIXI.Application();
export let viewportWidth = 41;
export let cellSize = 24;


async function Start_Game() {//13
    await app.init({ width: cellSize * viewportWidth, height: cellSize * viewportWidth })
    document.getElementById('gameCanvas').appendChild(app.canvas);
    Draw_Title_Screen()
}

function Draw_Title_Screen() {
    let title = new PIXI.Text("Online RPG", {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'});
    title.x = Set_Map_Within_Viewport(11) * cellSize;  // Assuming each cell is 24 pixels tall
    title.y = 200;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(title);
    let subtitle = new PIXI.Text("Press space to start!", {fontFamily : "'Press Start 2P'", fontSize: 16, fill : 0xff1010, align : 'center'});
    subtitle.x = Set_Map_Within_Viewport(14) * 24;  // Assuming each cell is 24 pixels tall
    subtitle.y = 300;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(subtitle);
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