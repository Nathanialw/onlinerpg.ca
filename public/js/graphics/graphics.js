'use strict'

import {app, Set_Map_Within_Viewport, cellSize} from '../frontend/game.js';

//const app = new PIXI.Application();
// await app.init({ width: 2376, height: 2352 })
// await app.init({ width: 640, height: 640 })

// document.getElementById('gameCanvas').appendChild(app.canvas);

function createTextWithBackground(textString, style, backgroundColor) {
    // Create the text object
    let text = new PIXI.Text(textString, style);
    
    // Create a new Graphics object and draw a rectangle on it
    let background = new PIXI.Graphics();
    background.fill(backgroundColor);
    background.rect(0, 0, text.width, text.height);
    
    // Create a container and add the background and text to it
    let container = new PIXI.Container();
    container.addChild(background);
    container.addChild(text);
    
    return container;
}

export function Create_Object(char, x, y) {
    let object = createTextWithBackground(char, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'}, 0x000001);
    object.x = x * cellSize;  // Assuming each cell is 24 pixels tall
    object.y = y * cellSize;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Update_Text(container, newText) {
    let textObject = container.children[1]; // Access the text object
    textObject.text = newText;
    // Update the background size if necessary
    let background = container.children[0];
    background.clear();
    background.fill(0x000001);
    background.rect(0, 0, textObject.width, textObject.height);
}

export function Update(){    
    //clear canvas
    //redraw map
}

export function Create_Map_Line(char, indexHeight) {
    let object = new PIXI.Text(char, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'});
    object.x = Set_Map_Within_Viewport() * cellSize;  // Assuming each cell is 24 pixels tall
    object.y = (Set_Map_Within_Viewport() + indexHeight) * cellSize;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}


// Add a ticker callback to move the sprite back and forth
let elapsed = 0.0;

// app.ticker.add((ticker) => {
    //     // elapsed += ticker.deltaTime;
    //     // sprite.x = 100.0 + Math.cos(elapsed/50.0) * 100.0;D
    // });
    
