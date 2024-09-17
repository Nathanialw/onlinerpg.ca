'use strict'
import * as PIXI from '../libs/pixi.js';

export const app = new PIXI.Application();
export let cellSize = 24;

let grey50 = 0xf8fafc;
let grey100 = 0xf1f5f9;
let grey200 = 0xe2e8f0;
let grey300 = 0xcbd5e1;
let grey400 = 0x94a3b8;
let grey500 = 0x64748b;
let grey600 = 0x475569;
let grey700 = 0x334155;
let grey800 = 0x1e293b;
let grey900 = 0x0f172a;
// let lightBlack = 0x222222;
let white = 0xffffff;
let black = 0x111111;

let footerHeight = 125;
let gameWindowOrigin_x = 0;
let gameWindowOrigin_y = 56; //3.5rem as per navbar height

export let viewportWidth = 41;
export let viewportHeight = 41;

let topPanelHeight = 10;
let topPanelWidth = viewportWidth;

let rightPanelWidth = 40;
let rightPanelHeight = viewportHeight + topPanelHeight;

let leftPanelWidth = 40;
let leftPanelHeight = viewportHeight + topPanelHeight;

let bottomPanelWidth = leftPanelWidth + rightPanelWidth + viewportWidth;
let bottomPanelHeight = (window.innerHeight / cellSize) - (viewportHeight + topPanelHeight);

let gameWindow = viewportWidth + 0;

function Set_Window_Width() {
    return (viewportWidth * cellSize) + (leftPanelWidth * cellSize) + (rightPanelWidth * cellSize);
}
function Set_Window_Height() {
    return (viewportHeight * cellSize) + (topPanelHeight * cellSize) + (bottomPanelHeight * cellSize);
}

function Get_ViewPort_Origin_x() {
    return leftPanelWidth;
}

function Get_ViewPort_Origin_y() {
    return topPanelHeight;
}

let inventory;

async function Init_Grpahics() {
    const texture = await Assets.load('assets/graphics/ui/itsmars_Inventory.png');
    inventory = new Sprite(texture);
}

// function Draw_Game_Window() {
//     let gameWindow = new PIXI.Graphics();
//     gameWindow.beginFill(0x024030);
//     gameWindow.drawRect(0, gameWindowOrigin_y, Set_Window_Width(), Set_Window_Height());
//     gameWindow.endFill();
//     app.stage.addChild(gameWindow);
// }

function Draw_Panel(x, y, w, h, backGroundColor) {
    console.log('Draw_Panel');
    let panel = new PIXI.Graphics();
    panel.beginFill(backGroundColor);  
    panel.drawRect(x, y, w, h);
    panel.endFill();
    app.stage.addChild(panel);
}

function Draw_Sprite(x, y, w, h, sprite) {
    console.log('Draw_Sprite');
    sprite.x = x;
    sprite.y = y;
    sprite.width = w;
    sprite.height = h;
    app.stage.addChild(sprite);

    sprite.texture.baseTexture.on('error', (error) => {
        console.error('Error loading texture:', error);
    });
}

// function Draw_Map_Border() {
//     let mapBorder = new PIXI.Graphics();
//     mapBorder.lineStyle(1, 0xffffff, 1);
//     mapBorder.drawRect(leftPanelWidth * cellSize, topPanelHeight * cellSize, viewportWidth * cellSize, viewportHeight * cellSize);
//     app.stage.addChild(mapBorder);
// }

// function Draw_Player_Stats() {
//     let playerStats = new PIXI.Graphics();
//     playerStats.beginFill(0x300400);
//     playerStats.drawRect(0, topPanelHeight * cellSize, leftPanelWidth * cellSize, viewportHeight * cellSize);
//     playerStats.endFill();
//     app.stage.addChild(playerStats);
// }

// function Draw_Player_Stats_Border() {
//     let playerStatsBorder = new PIXI.Graphics();
//     playerStatsBorder.lineStyle(1, 0xffffff, 1);
//     playerStatsBorder.drawRect(0, topPanelHeight * cellSize, leftPanelWidth * cellSize, viewportHeight * cellSize);
//     app.stage.addChild(playerStatsBorder);
// }


export function Draw_Title_Screen() {
    let title = new PIXI.Text("Online RPG", {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'});
    title.x = (Get_ViewPort_Origin_x() * cellSize) + Set_Map_Within_Viewport(11) * cellSize;  // Assuming each cell is 24 pixels tall
    title.y = (Get_ViewPort_Origin_y() * cellSize) + 200;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(title);
    let subtitle = new PIXI.Text("Press enter to start!", {fontFamily : "'Press Start 2P'", fontSize: 16, fill : 0xff1010, align : 'center'});
    subtitle.x = (Get_ViewPort_Origin_x() * cellSize) + Set_Map_Within_Viewport(13) * 24;  // Assuming each cell is 24 pixels tall
    subtitle.y = (Get_ViewPort_Origin_y() * cellSize) + 300;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(subtitle);
}

export async function Create_Canvas() {
    await app.init({ width: Set_Window_Width(), height: Set_Window_Height() - (footerHeight) })
    Init_Grpahics();
    app.canvas.x = 0;
    app.canvas.y = 0;
    document.getElementById('gameCanvas').appendChild(app.canvas);
}

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
    let object = createTextWithBackground(char, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : grey50, align : 'center'}, grey700);
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

export function Create_Map_Line(char, indexHeight, visionWidth) {
    // let object = createTextWithBackground(char, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : grey50, align : 'center'}, grey100);
    let object = new PIXI.Text(char, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : grey50, align : 'center'});
    object.x = (Get_ViewPort_Origin_x() + Set_Map_Within_Viewport(visionWidth)) * cellSize;  // Assuming each cell is 24 pixels tall
    object.y = (Get_ViewPort_Origin_y() + Set_Map_Within_Viewport(visionWidth) + indexHeight) * cellSize;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Draw_Vision_Background(visionWidth) {
    let x = (Get_ViewPort_Origin_x() + Set_Map_Within_Viewport(visionWidth)) * cellSize
    let y = (Get_ViewPort_Origin_y() + Set_Map_Within_Viewport(visionWidth)) * cellSize
    let w = visionWidth * cellSize;
    let h = visionWidth * cellSize;
    Draw_Panel(x, y, w, h, grey900);
}

function Set_Map_Within_Viewport(visionWidth) {
    let vision = ((viewportWidth - 1) / 2) - ((visionWidth - 1) / 2);
    return vision;
}

function Set_Player_Within_Viewport() {
    return ((viewportWidth - 1) / 2);
}

export function Draw_UI() {
    //top    
    Draw_Panel(leftPanelWidth * cellSize, 0, topPanelWidth * cellSize, topPanelHeight * cellSize, 0x0f0f0f)
    //right
    Draw_Panel((viewportWidth + leftPanelWidth) * cellSize, 0, rightPanelWidth * cellSize, rightPanelHeight * cellSize, 0x300301);
    //left
    // Draw_Panel(0, 0, leftPanelWidth * cellSize, leftPanelHeight * cellSize, 0x100030);
    Draw_Sprite(0, 0, leftPanelWidth * cellSize, leftPanelHeight * cellSize, inventory);
    //bottom
    Draw_Panel(0, (viewportHeight + topPanelHeight) * cellSize, bottomPanelWidth * cellSize, bottomPanelHeight * cellSize, 0x000050);
    //viewport
    Draw_Panel(leftPanelWidth * cellSize, (topPanelHeight * cellSize), viewportWidth * cellSize, viewportHeight * cellSize, black);
    // Draw_Map_Border();
    // Draw_Player_Stats();
    // Draw_Player_Stats_Border();

}

// Add a ticker callback to move the sprite back and forth
let elapsed = 0.0;

// app.ticker.add((ticker) => {
    //     // elapsed += ticker.deltaTime;
    //     // sprite.x = 100.0 + Math.cos(elapsed/50.0) * 100.0;D
    // });
    
