'use strict'
import { characterInfo } from '../units/unitdef.js';

export const app = new PIXI.Application();

let equipment;
let chat;
let menu;
let inventory;
let target;
let targetImg;
let playerImg;

async function Init_Graphics() {
    const playerTexture = await PIXI.Assets.load('assets/graphics/imgs/human/male/001.jpg');
    const equipmentTexture = await PIXI.Assets.load('assets/graphics/ui/equipment/equipment.png');
    const inventoryTexture = await PIXI.Assets.load('assets/graphics/ui/inventory/inventory_body.png');
    const chatTexture = await PIXI.Assets.load('assets/graphics/ui/log/chat_main_bg.png');
    const menuTexture = await PIXI.Assets.load('assets/graphics/ui/menu/main_menu.png');
    const targetTexture = await PIXI.Assets.load('assets/graphics/ui/overview/crafting_box_merge1.png');
    equipment = new PIXI.Sprite(equipmentTexture);
    chat = new PIXI.Sprite(chatTexture);
    menu = new PIXI.Sprite(menuTexture);
    inventory = new PIXI.Sprite(inventoryTexture);
    playerImg = new PIXI.Sprite(playerTexture);
    target = new PIXI.Sprite(targetTexture);
}

export async function Load_Target_Image(x, y, path) {
    x += 1;
    y += 1;
    x *= cellSize;
    y *= cellSize;
    const texture = await PIXI.Assets.load(path);
    targetImg = new PIXI.Sprite(texture);
    let w = 8 * cellSize;
    let h = 8 * cellSize;
    Draw_Sprite(x, y, w, h, targetImg);
}

export async function Create_Canvas() {
    await app.init({resizeTo: gameCanvas});

    await Init_Graphics();

    document.getElementById('gameCanvas').appendChild(app.canvas);
    app.renderer.resize(gameCanvas.clientWidth, gameCanvas.clientHeight);

    // Add an event listener to handle window resize events
    window.addEventListener('resize', () => {
        app.renderer.resize(gameCanvas.clientWidth, gameCanvas.clientHeight);
        console.log('Resized to: ', gameCanvas.clientWidth, gameCanvas.clientHeight);
    });
}

export let cellSize = 24;
export let minimapCellSize = 12;

export function Set_Font_Size(size) {
    cellSize = size;
    minimapCellSize = size / 2;
}


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
let black_100 = 0x222222;

let sidePanelWidth = 30;
export let viewportWidth = 41;
export let viewportHeight = 41;
let topPanelHeight = 10;

let topPanelWidth = viewportWidth;

export let rightPanelWidth = sidePanelWidth;
let rightPanelHeight = viewportHeight + topPanelHeight;

let leftPanelWidth = sidePanelWidth;
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

function Get_Minimap_Origin_x() {
    return leftPanelWidth * cellSize;
}

function Get_Minimap_Origin_y() {
    return (leftPanelHeight + 7) * cellSize;
}

export function Get_Right_Panel_Origin_x() {
    return (viewportWidth + leftPanelWidth);
}

export function Get_Right_Panel_Origin_y() {
    return 0;
}

export function Get_Right_Panel_Width() {
    return rightPanelWidth * cellSize;
}


function Draw_Panel(x, y, w, h, backGroundColor) {
    console.log('Draw_Panel');
    let panel = new PIXI.Graphics();
    // panel.beginFill(backGroundColor);  
    // panel.drawRect(x, y, w, h);
    // panel.endFill();
    panel.rect(x, y, w, h);
    panel.fill(backGroundColor);
    app.stage.addChild(panel);
}

export function Draw_Sprite(x, y, w, h, sprite) {
    console.log('Draw_Sprite');
    sprite.x = x;
    sprite.y = y;
    sprite.width = w;
    sprite.height = h;
    app.stage.addChild(sprite);
    console.log("x" + x + " y" + y + " w" + w + " h" + h, sprite);

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

export function Draw_Title_Screen() {
    let title = new PIXI.Text("Online RPG", {fontFamily : "'Press Start 2P'", fontSize: cellSize, fill : 0xff1010, align : 'center'});
    title.x = (Get_ViewPort_Origin_x() * cellSize) + Set_Map_Within_Viewport(11) * cellSize;  // Assuming each cell is 24 pixels tall
    title.y = (Get_ViewPort_Origin_y() * cellSize) + 200;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(title);
    let subtitle = new PIXI.Text("Press enter to start!", {fontFamily : "'Press Start 2P'", fontSize: 16, fill : 0xff1010, align : 'center'});
    subtitle.x = (Get_ViewPort_Origin_x() * cellSize) + Set_Map_Within_Viewport(13) * cellSize;  // Assuming each cell is 24 pixels tall
    subtitle.y = (Get_ViewPort_Origin_y() * cellSize) + 300;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(subtitle);
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
    let object = createTextWithBackground(char, {fontFamily : "'Press Start 2P'", fontSize: cellSize, fill : grey50, align : 'center'}, grey700);
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

const color = new Map();
color.set('h', 0xffff00);
color.set('e', 0xffff00);
color.set('g', 0x00ff00);
color.set('#', 0x00ff00);
color.set('▲', 0x013220); //dark green
color.set('˛', 0x964b00); //brown
color.set('♀', white); //brown
color.set('♂', white); //brown

export function Create_Object_Sprite(char, x, y, visionWidth) {
    let object = new PIXI.Text(char, {fontFamily : "'Press Start 2P'", fontSize: cellSize, fill : color.get(char), align : 'center'});
    object.x = (Get_ViewPort_Origin_x() + Set_Map_Within_Viewport(visionWidth) + x) * cellSize;  // Assuming each cell is 24 pixels tall
    object.y = (Get_ViewPort_Origin_y() + Set_Map_Within_Viewport(visionWidth) + y) * cellSize;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Create_Combat_Log_Line(char, indexHeight) {
    let object = new PIXI.Text(char, {fontFamily : "'Press Start 2P'", fontSize: minimapCellSize, fill : grey50, align : 'center'});
    object.x = (Get_Right_Panel_Origin_x()) * cellSize;  // Assuming each cell is 24 pixels tall
    object.y = ((Get_Right_Panel_Origin_y() + leftPanelHeight) * cellSize) + (indexHeight * minimapCellSize) - (10 * minimapCellSize);  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Clear_Target() {    
    Draw_Panel(Get_Right_Panel_Origin_x() * cellSize, Get_Right_Panel_Origin_y() * cellSize, Get_Right_Panel_Width(), (leftPanelHeight * cellSize) - (10 * minimapCellSize), black);
}

export function Create_Text_Line(char, fontSize, indexHeight, x, y) {
    let object = new PIXI.Text(char, {fontFamily : "'Press Start 2P'", fontSize: fontSize, fill : grey50, align : 'center'});
    object.x = x * cellSize;  // Assuming each cell is 24 pixels tall
    object.y = (y * cellSize) + (indexHeight * fontSize);  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Create_Map_Line(char, indexHeight, visionWidth) {
    // let object = createTextWithBackground(char, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : grey50, align : 'center'}, grey100);
    let object = new PIXI.Text(char, {fontFamily : "'Press Start 2P'", fontSize: cellSize, fill : grey50, align : 'center'});
    object.x = (Get_ViewPort_Origin_x() + Set_Map_Within_Viewport(visionWidth)) * cellSize;  // Assuming each cell is 24 pixels tall
    object.y = (Get_ViewPort_Origin_y() + Set_Map_Within_Viewport(visionWidth) + indexHeight) * cellSize;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Create_MiniMap_Line(char, indexHeight) {
    // let object = createTextWithBackground(char, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : grey50, align : 'center'}, grey100);
    let object = new PIXI.Text(char, {fontFamily : "'Press Start 2P'", fontSize: minimapCellSize, fill : grey50, align : 'center'});
    object.x = (Get_Minimap_Origin_x());  // Assuming each cell is 24 pixels tall
    object.y = (Get_Minimap_Origin_y()) + (indexHeight * minimapCellSize);  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Create_MiniMap_Line_Phone(char, indexHeight) {
    // let object = createTextWithBackground(char, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : grey50, align : 'center'}, grey100);
    let object = new PIXI.Text(char, {fontFamily : "'Press Start 2P'", fontSize: minimapCellSize, fill : grey50, align : 'center'});
    object.x = (0);  // Assuming each cell is 24 pixels tall
    object.y = (0) + (indexHeight * minimapCellSize);  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Draw_Vision_Background(visionWidth) {
    let x = (Get_ViewPort_Origin_x() + Set_Map_Within_Viewport(visionWidth)) * cellSize
    let y = (Get_ViewPort_Origin_y() + Set_Map_Within_Viewport(visionWidth)) * cellSize
    let w = visionWidth * cellSize;
    let h = visionWidth * cellSize;
    Draw_Panel(x, y, w, h, 0x228b22);
}

export function Draw_Vision_Background_Phone(visionWidth) {
    let x = (0 + Set_Map_Within_Viewport(visionWidth)) * cellSize
    let y = (0 + Set_Map_Within_Viewport(visionWidth)) * cellSize
    let w = visionWidth * cellSize;
    let h = visionWidth * cellSize;
    Draw_Panel(x, y, w, h, 0x228b22);
}


function Set_Map_Within_Viewport(visionWidth) {
    let vision = ((viewportWidth - 1) / 2) - ((visionWidth - 1) / 2);
    return vision;
}

function Set_Player_Within_Viewport() {
    return ((viewportWidth - 1) / 2);
}

export function Draw_UI_Phone() {
    //top    
    Draw_Panel(leftPanelWidth * cellSize, 0, topPanelWidth * cellSize, topPanelHeight * cellSize, black)
    //right
    // Draw_Panel(Get_Right_Panel_Origin_x() * cellSize, Get_Right_Panel_Origin_y() * cellSize, rightPanelWidth * cellSize, rightPanelHeight * cellSize, black);
    //left
    // Draw_Sprite(0, 0, leftPanelWidth * cellSize, leftPanelHeight * cellSize, inventory);
    //bottom
    // Draw_Panel(0, (viewportHeight + topPanelHeight) * cellSize, bottomPanelWidth * cellSize, bottomPanelHeight * cellSize, black);
    //viewport
    Draw_Panel(0, 0, viewportWidth * cellSize, viewportHeight * cellSize, black_100);
    Draw_Stats();
    // Draw_Map_Border();
    // Draw_Player_Stats();
    // Draw_Player_Stats_Border();

}

export function Draw_UI() {
    //top    
    Draw_Panel(leftPanelWidth * cellSize, 0, topPanelWidth * cellSize, topPanelHeight * cellSize, black)
    //menu
    Draw_Sprite(0, 0, rightPanelWidth * cellSize, (topPanelHeight / 4) * cellSize, menu);
    //eqipment
    Draw_Sprite(0, (topPanelHeight / 4) * cellSize, leftPanelWidth * cellSize, (leftPanelHeight * 2/3) * cellSize, equipment);
    //inventory
    Draw_Sprite(0, ((topPanelHeight / 4) + (leftPanelHeight * 2/3)) * cellSize  , leftPanelWidth * cellSize, ((leftPanelHeight * 1/3) - (topPanelHeight / 4)) * cellSize, inventory);
    //right
    Draw_Sprite(Get_Right_Panel_Origin_x() * cellSize, (Get_Right_Panel_Origin_y() * cellSize), rightPanelWidth * cellSize, rightPanelHeight * cellSize, target);
    //bottom
    Draw_Panel(0, (viewportHeight + topPanelHeight) * cellSize, bottomPanelWidth * cellSize, bottomPanelHeight * cellSize, black);
    //viewport
    Draw_Panel(leftPanelWidth * cellSize, (topPanelHeight * cellSize), viewportWidth * cellSize, viewportHeight * cellSize, black_100);
    Draw_Stats();
    // Draw_Map_Border();
    // Draw_Player_Stats();
    // Draw_Player_Stats_Border();

}


let jj;
function Draw_Stats() {
    // Create_Object(characterInfo.Potrait, x, y);
    Draw_Sprite((leftPanelWidth + 1) * cellSize, 1 * cellSize, 8 * cellSize, 8 * cellSize, playerImg);
    
    let x = leftPanelWidth + 10;
    let y = 1;
    
    jj = Create_Object(characterInfo.Name + characterInfo.Gender, x, y);
    y += 1;
    Create_Object("Age: " + characterInfo.Age, x, y);
    y += 1;
    Create_Object(characterInfo.HeroClass, x, y);
    y += 1;
    Create_Object("AC: " + characterInfo.AC, x, y);


    x = leftPanelWidth + 20;
    y = 2;
    Create_Object("Damage: " + characterInfo.MinDamage + "/" + characterInfo.MaxDamage, x, y);
    y += 1;
    Create_Object("Speed: " + characterInfo.Speed + "/" + characterInfo.MaxSpeed, x, y);
    y += 1;
    Create_Object("Health: " + characterInfo.Health + "/" + characterInfo.MaxHealth, x, y);
}
