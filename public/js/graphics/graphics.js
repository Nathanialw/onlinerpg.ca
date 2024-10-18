'use strict'
import { characterInfo } from '../units/unitdef.js';

export const app = new PIXI.Application();

let defaultIcon;
let hoverIcon;

let equipmentUI;
let chat;
let menu;
let tabs;
let invTabs;
let inventoryUI;
let lootUI;
let target;
let gamePanels = [];
let targetImg;
let playerImg;
export let loot = [];
export let inventory = [];
export let equipment = []
export let mainMenuSprites = []
export let gameMenuSprites = []

async function Init_Graphics() {
    const playerTexture = await PIXI.Assets.load('assets/graphics/imgs/human/male/001.jpg');
    const equipmentTexture = await PIXI.Assets.load('assets/graphics/ui/equipment/equipment.png');
    const inventoryTexture = await PIXI.Assets.load('assets/graphics/ui/inventory/inventory_body.png');
    const lootUITexture = await PIXI.Assets.load('assets/graphics/ui/loot/inventory_body.png');
    const chatTexture = await PIXI.Assets.load('assets/graphics/ui/log/chat_main_bg.png');
    const menuTexture = await PIXI.Assets.load('assets/graphics/ui/menu/main_menu.png');
    const targetTexture = await PIXI.Assets.load('assets/graphics/ui/overview/crafting_box_merge1.png');
    equipmentUI = new PIXI.Sprite(equipmentTexture);
    chat = new PIXI.Sprite(chatTexture);
    menu = new PIXI.Sprite(menuTexture);
    tabs = new PIXI.Sprite(menuTexture);
    invTabs = new PIXI.Sprite(menuTexture);
    inventoryUI = new PIXI.Sprite(inventoryTexture);
    lootUI = new PIXI.Sprite(lootUITexture);
    playerImg = new PIXI.Sprite(playerTexture);
    target = new PIXI.Sprite(targetTexture);

    //load main menu buttons
    for (let i = 0; i < 5; i++) {
        const button = await PIXI.Assets.load('assets/graphics/imgs/human/male/001.jpg');
        mainMenuSprites[i] = new PIXI.Sprite(button);
    }
        
    //load bag menu buttons
    //load game menu buttons
    for (let i = 0; i < 5; i++) {
        const button = await PIXI.Assets.load('assets/graphics/imgs/human/male/001.jpg');
        gameMenuSprites[i] = new PIXI.Sprite(button);
    }

    const panel0 = await PIXI.Assets.load('assets/graphics/ui/overview/crafting_box_merge1.png');
    gamePanels[0] = new PIXI.Sprite(panel0);
    const panel1 = await PIXI.Assets.load('assets/graphics/ui/inventory/inventory_body.png');
    gamePanels[1] = new PIXI.Sprite(panel1);
    const panel2 = await PIXI.Assets.load('assets/graphics/ui/equipment/equipment.png');
    gamePanels[2] = new PIXI.Sprite(panel2);
    const panel3 = await PIXI.Assets.load('assets/graphics/ui/overview/crafting_box_merge1.png');
    gamePanels[3] = new PIXI.Sprite(panel3);
    const panel4 = await PIXI.Assets.load('assets/graphics/ui/loot/inventory_body.png');
    gamePanels[4] = new PIXI.Sprite(panel4);

    defaultIcon = await PIXI.Assets.load('assets/graphics/mouse/cursor.png');
    hoverIcon = await PIXI.Assets.load('assets/graphics/mouse/cursor_outline_blue.png');
}

export async function Create_Canvas() {
    await app.init({resizeTo: gameCanvas});

    app.canvas.addEventListener('contextmenu', (event) => {
        event.preventDefault();
    });

    await Init_Graphics();

    document.getElementById('gameCanvas').appendChild(app.canvas);
    app.renderer.resize(gameCanvas.clientWidth, gameCanvas.clientHeight);

    // Add custom cursor styles
    // app.renderer.events.cursorStyles.default = defaultIcon;
    // app.renderer.events.cursorStyles.hover = hoverIcon;
    // const defaultIcon = await PIXI.Assets.load('assets/graphics/mouse/cursor.png');
    const defaultIcon = 'assets/graphics/mouse/cursor.png, auto';
    // Add custom cursor styles
    app.renderer.events.cursorStyles.default = defaultIcon;

    // Add an event listener to handle window resize events
    window.addEventListener('resize', () => {
        app.renderer.resize(gameCanvas.clientWidth, gameCanvas.clientHeight);
    });
}


export function Clear_Sprite_Array(spriteArray) {
    for (let i = 0; i < spriteArray.length; i++) {
        if (spriteArray[i]) {
        }
    }
    spriteArray.length = 0; // Clear the array
}

export function Remove_Event_Listeners(sprite) {
    if (sprite && sprite.removeAllListeners) {
        sprite.removeAllListeners();
    }
}

export async function Draw_Main_Menu_Icons(menu, num, xOff) {    
    let spaceBetween = 2.2;    
    let x = xOff * cellSize + ((num * 5) + spaceBetween) * cellSize;
    let y = 0.5 * cellSize;
    let h = 1.5 * cellSize;
    let w = 4.5 * cellSize;

    // Remove_Event_Listeners(mainMenuSprites[num]);    
    // let button = await Load_Icon(iconPath);    
    // mainMenuSprites.push(new PIXI.Sprite(button));        
    Draw_Sprite(x, y, w, h, menu[num]);            
    return menu[num];
}

async function Load_Icon(path) {
    if (PIXI.Assets.cache.has(path)) {
        let icon = PIXI.Assets.cache.get(path);
        return icon;
    } else {
        let icon = await PIXI.Assets.load(path);
        PIXI.Assets.cache.set(icon)        
        return icon;
    }
}

export async function Draw_Equipment_Icons(iconPath, num, xOffset, yOffset, w) {    
    let spaceBetweenCol1 = 1 * cellSize;
    let fromTopCol1 = 5.1 * cellSize;
    let fromleftCol1 = 3.5 * cellSize;

    let spaceBetweenCol2 = .85 * cellSize;
    let fromTopCol2 = 9 * cellSize;
    let fromleftCol2 = 24.3 * cellSize;

    let spaceBetweenBottom = 1.2 * cellSize;
    let fromTopBottom = 26.5 * cellSize;
    let fromleftBottom = 9.2 * cellSize;
    
    let squareSize = w * cellSize;

    let x = 0;
    let y = (topPanelHeight / 4) * cellSize;

    let rowPosition = y;
    let columnPosition = x;
    if (num < 6) {
        rowPosition = y + fromTopCol1 + ((squareSize + spaceBetweenCol1) * num);
        columnPosition = x + fromleftCol1;
    }
    else if (num < 11) {
        let ind = num - 6;
        rowPosition = y + fromTopCol2 + ((squareSize + spaceBetweenCol2) * ind);
        columnPosition = x + fromleftCol2;
    }
    else {
        let ind = num - 11;
        rowPosition = y + fromTopBottom;
        columnPosition = x + fromleftBottom + ((squareSize + spaceBetweenBottom) * ind);
    }

    // check if equipment[num] has an event listener, remove if it does
    Remove_Event_Listeners(equipment[num]);

    let equipmentIcon = await Load_Icon(iconPath);
    equipment[num] = new PIXI.Sprite(equipmentIcon);
    Draw_Sprite(columnPosition, rowPosition, squareSize, squareSize, equipment[num]);
    return equipment[num]
}

export async function Draw_Inventory_Icons(iconPath, num, xOffset, yOffset, w) {    
    let spaceBetweenY = .4;
    let spaceBetweenX = .8;
    let x = 6;
    let y = ((topPanelHeight / 4) + (leftPanelHeight * 2 / 3)) * cellSize;
    
    let row = Math.floor(num / 4);
    let column = num % 4;
    
    let rowPosition = y + (row * ((w + spaceBetweenY) * cellSize) + xOffset * cellSize);
    let columnPosition = x + (column * ((w + spaceBetweenX) * cellSize) + yOffset * cellSize);
    let squareSize = w * cellSize;

    Remove_Event_Listeners(inventory[num]);
    
    let inventoryIcon = await Load_Icon(iconPath);
    inventory[num] = new PIXI.Sprite(inventoryIcon);
    Draw_Sprite(columnPosition, rowPosition, squareSize, squareSize, inventory[num]);
    return inventory[num]
}

export async function Draw_Loot_Icons(iconPath, num, xOffset, yOffset, w) {    
    let x = (leftPanelWidth / 2) * cellSize
    let y = ((topPanelHeight / 4) + (leftPanelHeight * 2/3)) * cellSize

    Remove_Event_Listeners(loot[num]);
    
    let lootIcon = await Load_Icon(iconPath);    
    loot.push(new PIXI.Sprite(lootIcon));        
    Draw_Sprite(x + (xOffset * cellSize), y + (yOffset * cellSize) + (w * num) * cellSize, w * cellSize, w * cellSize, loot[num]);        
    
    return loot[num];
}


export function Draw_Texture(x, y, sprite) {
    sprite.x = x;
    sprite.y = y;
    app.stage.addChild(sprite);

    sprite.texture.source.on('error', (error) => {
        console.error('Error loading texture:', error);
    });
}
export async function Load_Target_Image(x, y, path) {
    x += 1;
    y += 1;
    x *= cellSize;
    y *= cellSize;
    const texture = await PIXI.Assets.load(path);
    targetImg = new PIXI.Sprite(texture);
    let w = 11 * cellSize;
    let h = 11 * cellSize;
    Draw_Sprite(x, y, w, h, targetImg);
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
export let topPanelHeight = 10;

let topPanelWidth = viewportWidth;

export let rightPanelWidth = sidePanelWidth;
let rightPanelHeight = viewportHeight + topPanelHeight;

export let leftPanelWidth = sidePanelWidth;
export let leftPanelHeight = viewportHeight + topPanelHeight;

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
    let panel = new PIXI.Graphics();
    // panel.beginFill(backGroundColor);  
    // panel.drawRect(x, y, w, h);
    // panel.endFill();
    panel.rect(x, y, w, h);
    panel.fill(backGroundColor);
    app.stage.addChild(panel);
}

export function Draw_Sprite(x, y, w, h, sprite) {
    if (!sprite) {
        console.error("Texture is not loaded");
        return;
    }

    sprite.x = x;
    sprite.y = y;
    sprite.width = w;
    sprite.height = h;
    app.stage.addChild(sprite);

    sprite.texture.source.on('error', (error) => {
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
    let text = new PIXI.Text({text: textString, style});
    
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

const yellow = 0xffff00;
const green =  0x00ff00;
const green_dark = 0x013220;
const brown_dark = 0x964b00;
const brown = 0x8b4513;

const color = new Map();
color.set('h', yellow);
color.set('e', yellow);
color.set('g', green);
color.set('#', green);
color.set('▲', green_dark); //dark green
color.set('˛', brown_dark); //brown
color.set('ô', brown); //brown
color.set('♀', white); //brown
color.set('♂', white); //brown

export function Create_Combat_Log_Line(char, indexHeight) {
    const style = {fontFamily : "'Press Start 2P'", fontSize: minimapCellSize, fill : grey50, align : 'center'}
    let object = new PIXI.Text({text: char, style});
    object.x = (Get_Right_Panel_Origin_x()) * cellSize;  // Assuming each cell is 24 pixels tall
    object.y = ((Get_Right_Panel_Origin_y() + leftPanelHeight) * cellSize) + (indexHeight * minimapCellSize) - (10 * minimapCellSize);  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Clear_Target() { 
    Draw_Sprite(Get_Right_Panel_Origin_x() * cellSize, ((Get_Right_Panel_Origin_y() + (topPanelHeight / 4)) * cellSize), rightPanelWidth * cellSize,((rightPanelHeight - (topPanelHeight / 4))  * cellSize) - (10 * minimapCellSize), target);
}

export function Create_Text_Line(char, fontSize, indexHeight, x, y) {
    const style = {fontFamily : "'Press Start 2P'", fontSize: fontSize, fill : grey50, align : 'center'};
    let object = new PIXI.Text({text: char, style});
    object.x = x * cellSize;  // Assuming each cell is 24 pixels tall
    object.y = (y * cellSize) + (indexHeight * fontSize);  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Create_Map_Line(char, indexHeight, visionWidth) {
    let style = {fontFamily : "'Press Start 2P'", fontSize: cellSize, fill : grey50, align : 'center'}
    let object = new PIXI.Text({text: char, style});
    object.x = (Get_ViewPort_Origin_x() + Set_Map_Within_Viewport(visionWidth)) * cellSize;  // Assuming each cell is 24 pixels tall
    object.y = (Get_ViewPort_Origin_y() + Set_Map_Within_Viewport(visionWidth) + indexHeight) * cellSize;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Create_Object_Sprite(char, x, y, visionWidth) {
    const style = {fontFamily : "'Press Start 2P'", fontSize: cellSize, fill : color.get(char), align : 'center'}
    let object = new PIXI.Text({text: char, style});
    object.x = (Get_ViewPort_Origin_x() + Set_Map_Within_Viewport(visionWidth) + x) * cellSize;  // Assuming each cell is 24 pixels tall
    object.y = (Get_ViewPort_Origin_y() + Set_Map_Within_Viewport(visionWidth) + y) * cellSize;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Create_MiniMap_Line(char, indexHeight) {
    // let object = createTextWithBackground(char, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : grey50, align : 'center'}, grey100);
    const style = {fontFamily : "'Press Start 2P'", fontSize: minimapCellSize, fill : grey50, align : 'center'}
    let object = new PIXI.Text({text: char, style});
    object.x = (Get_Minimap_Origin_x());  // Assuming each cell is 24 pixels tall
    object.y = (Get_Minimap_Origin_y()) + (indexHeight * minimapCellSize);  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Create_MiniMap_Line_Phone(char, indexHeight) {
    // let object = createTextWithBackground(char, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : grey50, align : 'center'}, grey100);
    const style = {fontFamily : "'Press Start 2P'", fontSize: minimapCellSize, fill : grey50, align : 'center'}
    let object = new PIXI.Text({text: char, style});
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
    // Draw_Sprite(0, 0, leftPanelWidth * cellSize, leftPanelHeight * cellSize, inventoryUI);
    //bottom
    // Draw_Panel(0, (viewportHeight + topPanelHeight) * cellSize, bottomPanelWidth * cellSize, bottomPanelHeight * cellSize, black);
    //viewport
    Draw_Panel(0, 0, viewportWidth * cellSize, viewportHeight * cellSize, black_100);
    Draw_Stats();
    // Draw_Map_Border();
    // Draw_Player_Stats();
    // Draw_Player_Stats_Border();

}

export function Draw_UI(index) {
    //top    
    Draw_Panel(leftPanelWidth * cellSize, 0, topPanelWidth * cellSize, topPanelHeight * cellSize, black)
    
    //menu background
    Draw_Sprite(0, 0, leftPanelWidth * cellSize, (topPanelHeight / 4) * cellSize, menu);
    //eqipment
    Draw_Sprite(0, (topPanelHeight / 4) * cellSize, leftPanelWidth * cellSize, ((leftPanelHeight * 2/3) - (topPanelHeight / 4)) * cellSize, equipmentUI);
    //tabs
    Draw_Sprite(0, ((Get_Right_Panel_Origin_y() + (leftPanelHeight * 2/3)) * cellSize), leftPanelWidth * cellSize, (topPanelHeight / 4) * cellSize, invTabs);
    //inventory
    Draw_Sprite(0, ((topPanelHeight / 4) + (leftPanelHeight * 2/3)) * cellSize, (leftPanelWidth / 2) * cellSize, ((leftPanelHeight * 1/3) - (topPanelHeight / 4)) * cellSize, inventoryUI);
    //loot
    Draw_Sprite((leftPanelWidth / 2) * cellSize, ((topPanelHeight / 4) + (leftPanelHeight * 2/3)) * cellSize, (leftPanelWidth / 2) * cellSize, ((leftPanelHeight * 1/3) - (topPanelHeight / 4)) * cellSize, lootUI);
    
    //tab background
    Draw_Sprite(Get_Right_Panel_Origin_x() * cellSize, (Get_Right_Panel_Origin_y() * cellSize), rightPanelWidth * cellSize, (topPanelHeight / 4) * cellSize, tabs);
    //overview //pass the current sprite active
    Draw_Sprite(Get_Right_Panel_Origin_x() * cellSize, ((Get_Right_Panel_Origin_y() + (topPanelHeight / 4)) * cellSize), rightPanelWidth * cellSize,((rightPanelHeight - (topPanelHeight / 4))  * cellSize) - (10 * minimapCellSize), gamePanels[index]);
    
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
