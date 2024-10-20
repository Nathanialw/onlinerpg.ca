'use strict'
import { characterInfo } from '../units/unitdef.js';

export const app = new PIXI.Application();


export const grey50 = 0xf8fafc;
export const grey100 = 0xf1f5f9;
export const grey200 = 0xe2e8f0;
export const grey300 = 0xcbd5e1;
export const grey400 = 0x94a3b8;
export const grey500 = 0x64748b;
export const grey600 = 0x475569;
export const grey700 = 0x334155;
export const grey800 = 0x1e293b;
export const grey900 = 0x0f172a;
// const lightBlack = 0x222222;
const white = 0xffffff;
const black = 0x111111;
const black_100 = 0x222222;
const gold = 0xffd700;

let defaultIcon;
let hoverIcon;
let hoverNeutral;
let hoverAlly;
let hoverEnemy;

export let buttonHover;
export let buttonNormal;

let equipmentUI;
let chat;
let menu;
let tabs;
let invTabs;
let inventoryUI;
let target;
let gamePanels = [];
let targetImg;
let playerImg;
export let loot = [];
export let inventory = [];
export let equipment = []
export let mainMenuSprites = []
export let mainMenuText = []
export let gameMenuSprites = []
export let gameMenuText = []
export let defaultStyle;
export let hoverStyle;

let equipSlotsDefault = {
    ammo: null,
    chain: null,
    neck: null,
    wrists: null,
    arms: null,
    waist: null,
    feet: null,
    chest: null,
    back: null,
    drink: null,
    face: null,
    food: null,
    hands: null,
    mainHand: null,
    offHand: null,
    head: null,
    legs: null,
    twoHand: null,
    ring0: null,
    ring1: null,
    trinket0: null,
    trinket1: null,

    hoverEffect: null,
    ammoBorder: null,
    slotBorder: null,
}

async function Load_Texture(path) {
    const texture = await PIXI.Assets.load(path);
    return new PIXI.Sprite(texture);
}

async function Init_Graphics() {  
    equipmentUI = await Load_Texture('assets/graphics/ui/equipment/equipment2.png')
    chat = await Load_Texture('assets/graphics/ui/log/chat_main_bg.png')
    menu = await Load_Texture('assets/graphics/ui/menu/main_menu.png')
    tabs = await Load_Texture('assets/graphics/ui/menu/main_menu.png')
    invTabs = await Load_Texture('assets/graphics/ui/menu/main_menu.png')
    inventoryUI = await Load_Texture('assets/graphics/ui/inventory/inventory.png')
    playerImg = await Load_Texture('assets/graphics/imgs/human/male/001.jpg')
    target = await Load_Texture('assets/graphics/ui/overview/crafting_box_merge1.png')

    //load main menu buttons
    buttonNormal = await PIXI.Assets.load('assets/graphics/menu/button/standardbut_n.png');
    buttonHover = await PIXI.Assets.load('assets/graphics/menu/button/standardbut_h.png');
    
    mainMenuSprites[0] = await  new PIXI.Sprite(buttonNormal);
    mainMenuSprites[1] = await  new PIXI.Sprite(buttonNormal);
    mainMenuSprites[2] = await  new PIXI.Sprite(buttonNormal);
    mainMenuSprites[3] = await  new PIXI.Sprite(buttonNormal);
    mainMenuSprites[4] = await  new PIXI.Sprite(buttonNormal);
        
    //load bag menu buttons
    //
    defaultStyle = {fontFamily : "'Press Start 2P'", fontSize: minimapCellSize, fill : grey50, align : 'center' }
    hoverStyle = {fontFamily : "'Press Start 2P'", fontSize: minimapCellSize, fill : gold, align : 'center' }
    mainMenuText[0] = new PIXI.Text({text: 'Quit', defaultStyle});
    mainMenuText[1] = new PIXI.Text({text: 'Restart', defaultStyle});
    mainMenuText[2] = new PIXI.Text({text: 'Options', defaultStyle});
    mainMenuText[3] = new PIXI.Text({text: 'Graphics', defaultStyle});
    mainMenuText[4] = new PIXI.Text({text: 'Sound', defaultStyle});
    //load game menu buttons
    
    gameMenuSprites[0] = await Load_Texture('assets/graphics/menu/button/standardbut_n.png');
    gameMenuSprites[1] = await Load_Texture('assets/graphics/menu/button/standardbut_n.png');
    gameMenuSprites[2] = await Load_Texture('assets/graphics/menu/button/standardbut_n.png');
    gameMenuSprites[3] = await Load_Texture('assets/graphics/menu/button/standardbut_n.png');
    gameMenuSprites[4] = await Load_Texture('assets/graphics/menu/button/standardbut_n.png');

    gameMenuText[0] = new PIXI.Text({text: 'Target', defaultStyle});
    gameMenuText[1] = new PIXI.Text({text: 'Spells', defaultStyle});
    gameMenuText[2] = new PIXI.Text({text: 'Craft', defaultStyle});
    gameMenuText[3] = new PIXI.Text({text: 'Loot', defaultStyle});
    gameMenuText[4] = new PIXI.Text({text: 'Log', defaultStyle});

    //load panel ui backgrounds
    gamePanels[0] = await Load_Texture('assets/graphics/ui/overview/crafting_box_merge1.png');
    gamePanels[1] = await Load_Texture('assets/graphics/ui/overview/tall_Panel.png');
    gamePanels[2] = await Load_Texture('assets/graphics/ui/overview/tall_Panel.png');
    gamePanels[3] = await Load_Texture('assets/graphics/ui/overview/tall_Panel.png');
    gamePanels[4] = await Load_Texture('assets/graphics/ui/overview/tall_Panel.png');

    equipSlotsDefault.ammo = await Load_Texture('assets/graphics/ui/equipment/ammo_slot.png');
    equipSlotsDefault.neck = await Load_Texture('assets/graphics/ui/equipment/empty_amulet.png');
    equipSlotsDefault.waist = await Load_Texture('assets/graphics/ui/equipment/empty_belt.png');
    equipSlotsDefault.feet = await Load_Texture('assets/graphics/ui/equipment/empty_boots.png');
    equipSlotsDefault.chest = await Load_Texture('assets/graphics/ui/equipment/empty_chest.png');
    equipSlotsDefault.back = await Load_Texture('assets/graphics/ui/equipment/empty_cloak.png');
    equipSlotsDefault.hands = await Load_Texture('assets/graphics/ui/equipment/empty_gloves.png');
    equipSlotsDefault.mainHand = await Load_Texture('assets/graphics/ui/equipment/empty_hand.png');
    equipSlotsDefault.offHand = await Load_Texture('assets/graphics/ui/equipment/empty_hand.png');
    equipSlotsDefault.head = await Load_Texture('assets/graphics/ui/equipment/empty_helmet.png');
    equipSlotsDefault.legs = await Load_Texture('assets/graphics/ui/equipment/empty_pants.png');
    equipSlotsDefault.twoHand = await Load_Texture('assets/graphics/ui/equipment/empty_ranged.png');
    equipSlotsDefault.ring0 = await Load_Texture('assets/graphics/ui/equipment/empty_ring.png');
    equipSlotsDefault.ring1 = await Load_Texture('assets/graphics/ui/equipment/empty_ring.png');
    equipSlotsDefault.trinket0 = await Load_Texture('assets/graphics/ui/equipment/empty_trinket.png');
    equipSlotsDefault.trinket1 = await Load_Texture('assets/graphics/ui/equipment/empty_trinket.png');
    
    equipSlotsDefault.chain = await Load_Texture('assets/graphics/ui/equipment/chain_link.png');
    equipSlotsDefault.hoverEffect = await Load_Texture('assets/graphics/ui/equipment/item_hover_effect.png');
    equipSlotsDefault.ammoBorder = await Load_Texture('assets/graphics/ui/equipment/slot_frame_ammo.png');
    equipSlotsDefault.slotBorder = await Load_Texture('assets/graphics/ui/equipment/slot_frame.png');

    // equipSlotsDefault.drink = await Load_Texture('assets/graphics/ui/equipment/empty_drink.png');
    // equipSlotsDefault.wrists = await Load_Texture('assets/graphics/ui/equipment/empty_armguards.png');
    // equipSlotsDefault.arms = await Load_Texture('assets/graphics/ui/equipment/empty_arms.png');
    // equipSlotsDefault.face = await Load_Texture('assets/graphics/ui/equipment/empty_face.png');
    // equipSlotsDefault.food = await Load_Texture('assets/graphics/ui/equipment/empty_food.png');
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
    defaultIcon = 'url(\'https://onlinerpg.ca/assets/graphics/mouse/cursor.png\'),auto';
    hoverIcon = 'url(\'https://onlinerpg.ca/assets/graphics/mouse/cursor_outline_blue.png\'),auto';
    hoverEnemy = 'url(\'https://onlinerpg.ca/assets/graphics/mouse/cursor_outline_red.png\'),auto';
    app.renderer.events.cursorStyles.default = defaultIcon;
    app.renderer.events.cursorStyles.hover = hoverIcon;
    app.renderer.events.cursorStyles.crosshair = hoverEnemy;
    //all cursor styles:
    //auto, default, none, context-menu, help, pointer, progress, wait, cell, crosshair, text, verticaltext, alias, copy, move, nodrop, notallowed, eresize, nresize, neresize, nwresize, sresize, seresize, swresize, wresize, nsresize, ewresize, neswresize, colresize, nwseresize, rowresize, allscroll, zoomin, zoomout, grab, grabbing

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

export async function Draw_Menu_Icons(menu, num, xOff, text) {    
    let spaceBetween = 2.2;    
    let x = xOff * cellSize + ((num * 5) + spaceBetween) * cellSize;
    let y = 0.5 * cellSize;
    let h = 1.5 * cellSize;
    let w = 4.5 * cellSize;

    // Remove_Event_Listeners(mainMenuSprites[num]);    
    // let button = await Load_Icon(iconPath);    
    // mainMenuSprites.push(new PIXI.Sprite(button));        
    Draw_Sprite(x, y, w, h, menu[num]);    
    
    //Draw the text   
    text[num].x = x + (w / 2) - (text[num].width / 2);
    text[num].y = y + (h / 2) - (text[num].height / 2);
    app.stage.addChild(text[num]);

    return {texture: menu[num], text: text[num]};
}

async function Load_Icon(path) {
    if (!path || typeof path !== 'string') {
        throw new Error('Invalid path provided to Load_Icon');
    }
    
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
    const spaceBetweenCol1 = 1 * cellSize;
    const fromTopCol1 = 5.1 * cellSize;
    const fromleftCol1 = 3.5 * cellSize;

    const spaceBetweenCol2 = .85 * cellSize;
    const fromTopCol2 = 9 * cellSize;
    const fromleftCol2 = 24.3 * cellSize;

    const spaceBetweenBottom = 1.2 * cellSize;
    const fromTopBottom = 26.5 * cellSize;
    const fromleftBottom = 9.2 * cellSize;
    
    const squareSize = w * cellSize;

    const x = 0;
    const y = (topPanelHeight / 4) * cellSize;

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
    let spaceBetweenY = .66;
    let spaceBetweenX = .91;
    let x = .88 * cellSize;
    let y = ((topPanelHeight / 2) + (leftPanelHeight * 1/2)) * cellSize;
    
    let row = Math.floor(num / 8);
    let column = num % 8;
    
    let rowPosition = y + (row * ((w + spaceBetweenY) * cellSize) + xOffset * cellSize);
    let columnPosition = x + (column * ((w + spaceBetweenX) * cellSize) + yOffset * cellSize);
    let squareSize = w * cellSize;

    Remove_Event_Listeners(inventory[num]);
    
    let inventoryIcon = await Load_Icon(iconPath);
    inventory[num] = new PIXI.Sprite(inventoryIcon);
    Draw_Sprite(columnPosition, rowPosition, squareSize, squareSize, inventory[num]);
    return inventory[num]
}

export async function Draw_Loot_Icons(iconPath, num, xOffset, yOffset, w, text) {    
    let x = (Get_Right_Panel_Origin_x() + 0.5) * cellSize
    let y = (Get_Right_Panel_Origin_y() + 1.5) * cellSize

    Remove_Event_Listeners(loot[num]);
    
    let lootIcon = await Load_Icon(iconPath);    
    loot.push(new PIXI.Sprite(lootIcon));        
    Draw_Sprite(x + (xOffset * cellSize), y + (yOffset * cellSize) + (w * num) * cellSize, w * cellSize, w * cellSize, loot[num]);        
    
    //Draw the text   

    textObject.x = x + ((3 + xOffset) * cellSize);
    textObject.y = y + ((1 + yOffset) * cellSize) + (w * num) * cellSize;
    app.stage.addChild(textObject);

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



const sidePanelWidth = 30;
export const viewportWidth = 41;
export const viewportHeight = 41;
export const topPanelHeight = 10;

const topPanelWidth = viewportWidth;

export const rightPanelWidth = sidePanelWidth;
const rightPanelHeight = viewportHeight + topPanelHeight;

export const leftPanelWidth = sidePanelWidth;
export const leftPanelHeight = viewportHeight + topPanelHeight;

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
    object.x = (Get_Right_Panel_Origin_x() + 1) * cellSize;  // Assuming each cell is 24 pixels tall
    object.y = ((Get_Right_Panel_Origin_y() + leftPanelHeight + 1) * cellSize) + (indexHeight * minimapCellSize) - (10 * minimapCellSize);  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Clear_Target() { 
    Draw_Sprite(Get_Right_Panel_Origin_x() * cellSize, ((Get_Right_Panel_Origin_y() + (topPanelHeight / 4)) * cellSize), rightPanelWidth * cellSize, ((rightPanelHeight - (topPanelHeight / 4))  * cellSize) - (20 * minimapCellSize), gamePanels[0]);
    // Draw_Sprite(Get_Right_Panel_Origin_x() * cellSize, ((Get_Right_Panel_Origin_y() + (topPanelHeight / 4)) * cellSize), rightPanelWidth * cellSize,((rightPanelHeight - (topPanelHeight / 4))  * cellSize) - (10 * minimapCellSize), target);
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
    Draw_Sprite(0, (topPanelHeight / 4) * cellSize, leftPanelWidth * cellSize, ((leftPanelHeight * 1/2)) * cellSize, equipmentUI);
    //bag slots
    Draw_Sprite(0, ((Get_Right_Panel_Origin_y() + (leftPanelHeight * 1/2) + (topPanelHeight / 4)) * cellSize), leftPanelWidth * cellSize, (topPanelHeight / 4) * cellSize, invTabs);
    //inventory
    Draw_Sprite(0, ((topPanelHeight / 2) + (leftPanelHeight * 1/2)) * cellSize, (leftPanelWidth) * cellSize, ((leftPanelHeight * 1/2) - (topPanelHeight / 2)) * cellSize, inventoryUI);


    //tab background
    Draw_Sprite(Get_Right_Panel_Origin_x() * cellSize, (Get_Right_Panel_Origin_y() * cellSize), rightPanelWidth * cellSize, (topPanelHeight / 4) * cellSize, tabs);
    //overview //pass the current sprite active
    Draw_Sprite(Get_Right_Panel_Origin_x() * cellSize, ((Get_Right_Panel_Origin_y() + (topPanelHeight / 4)) * cellSize), rightPanelWidth * cellSize, ((rightPanelHeight - (topPanelHeight / 4))  * cellSize) - (20 * minimapCellSize), gamePanels[index]);
    //chat
    Draw_Sprite(Get_Right_Panel_Origin_x() * cellSize,( (Get_Right_Panel_Origin_y() + 41) * cellSize), rightPanelWidth * cellSize, 20 * minimapCellSize, chat);

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
